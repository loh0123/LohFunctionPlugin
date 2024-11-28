#include "Subsystem/LFPStreamSocketSubsystem.h"
#include "IPAddress.h"
#include "Async/Async.h"
#include "IPAddressAsyncResolve.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "SocketSubsystem.h"
#include "Common/TcpSocketBuilder.h"

void ULFPStreamSocketSubsystem::Initialize( FSubsystemCollectionBase& Collection )
{
	Super::Initialize( Collection );

	SocketSubsystem = ISocketSubsystem::Get( PLATFORM_SOCKETSUBSYSTEM );

	if ( SocketSubsystem == nullptr )
	{
		UE_LOG( LogTemp , Error , TEXT( "ULFPStreamSocketSubsystem : SocketSubsystem is nullptr" ) );

		return;
	}
}

void ULFPStreamSocketSubsystem::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if ( SocketSubsystem == nullptr )
	{
		return;
	}

	for ( auto& SocketData : SocketList )
	{
		if ( SocketData.bClosing )
		{
			continue;
		}

		if ( SocketData.bInitilized == false )
		{
			continue;
		}

		if ( SocketData.MainSocket == nullptr )
		{
			SocketData.bClosing = true; // Remove this Socket

			continue;
		}

		// Is Server
		if ( SocketData.IsListenServer() )
		{
			TryConnectClient( SocketData );

			TryReceiveClientData( SocketData );

			CheckSocketClientKeepAlive( SocketData );
		}
		else
		{
			TryConnectServer( SocketData );

			TryReceiveServerData( SocketData );

			CheckSocketServerKeepAlive( SocketData );
		}
	}

	SocketList.RemoveAll( [&] ( FLFPStreamSocketData& SocketData )
						  {
							  if ( SocketData.bClosing == false )
							  {
								  return false;
							  }

							  CloseSocket( SocketData );

							  return true;
						  }
	);
}

void ULFPStreamSocketSubsystem::Deinitialize()
{
	Super::Deinitialize();

	for ( auto& SocketData : SocketList )
	{
		CloseSocket( SocketData );
	}

	SocketList.Empty();
}

TStatId ULFPStreamSocketSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT( ULFPStreamSocketSubsystem , STATGROUP_Tickables );
}

void ULFPStreamSocketSubsystem::TryInitializeSocket( FLFPStreamSocketData& SocketData , const TSharedRef<FInternetAddr>& Endpoint )
{
	const FString MainDescription = SocketData.SocketSetting.SocketDescription + FString( " : Main Socket" );

	SocketData.MainSocket = SocketSubsystem->CreateSocket( NAME_Stream , *MainDescription , Endpoint->GetProtocolType() );

	if ( SocketData.MainSocket == nullptr )
	{
		SocketData.bClosing = true; // Remove this Socket

		UE_LOG( LogTemp , Error , TEXT( "ULFPStreamSocketSubsystem : %s : Main Socket create failed" ) , *MainDescription );

		return;
	}

	bool Error =
		!SocketData.MainSocket->SetReuseAddr( SocketData.SocketSetting.bSocketReusable ) ||
		!SocketData.MainSocket->SetRecvErr() ||
		!SocketData.MainSocket->Bind( Endpoint.Get() ) ||
		!SocketData.MainSocket->SetNonBlocking( true );

	// Is server
	if ( Error == false )
	{
		if ( SocketData.IsListenServer() )
		{
			Error = !SocketData.MainSocket->Listen( SocketData.SocketSetting.MaxListenConnection );
		}
		else // Try Connect To Server On Initialize
		{
			Error = !SocketData.MainSocket->Connect( Endpoint.Get() );
		}
	}

	if ( Error )
	{
		UE_LOG( LogTemp , Error , TEXT( "ULFPStreamSocketSubsystem : %s : Main Socket create failed as configured" ) , *MainDescription );

		SocketSubsystem->DestroySocket( SocketData.MainSocket );

		SocketData.MainSocket = nullptr;

		SocketData.bClosing = true; // Remove this Socket
	}
	else
	{
		int32 OutNewSize;

		if ( SocketData.SocketSetting.BufferReadSize > 0 )
		{
			SocketData.MainSocket->SetReceiveBufferSize( SocketData.SocketSetting.BufferReadSize , OutNewSize );
		}

		if ( SocketData.SocketSetting.BufferWriteSize > 0 )
		{
			SocketData.MainSocket->SetSendBufferSize( SocketData.SocketSetting.BufferWriteSize , OutNewSize );
		}
	}

	SocketData.bInitilized = true; // All normal pass
}

void ULFPStreamSocketSubsystem::TryConnectClient( FLFPStreamSocketData& SocketData )
{
	if ( bool bHasPendingConnection = false; SocketData.MainSocket->HasPendingConnection( bHasPendingConnection ) && bHasPendingConnection )
	{
		const FString ConnectDescription = SocketData.SocketSetting.SocketDescription + FString::Printf( TEXT( " : Client Socket ID ( %d )" ) , SocketData.ClientSocket.Num() );

		TSharedRef<FInternetAddr> Addr = SocketSubsystem->CreateInternetAddr();

		FSocket* NewSocket = SocketData.MainSocket->Accept( *Addr , ConnectDescription );

		if ( NewSocket != nullptr )
		{
			NewSocket->SetRecvErr();
			NewSocket->SetNonBlocking();

			OnConnected.Broadcast( SocketData.SocketLookUpID , SocketData.ClientSocket.Add( NewSocket ) );
		}
	}
}

void ULFPStreamSocketSubsystem::TryConnectServer( FLFPStreamSocketData& SocketData )
{
	if ( SocketData.CurrentReconnectAttempt >= SocketData.SocketSetting.MaxReconnectAttempt )
	{
		SocketData.bClosing = true;

		return;
	}

	TSharedRef<FInternetAddr> Addr = SocketSubsystem->CreateInternetAddr();

	SocketData.MainSocket->GetAddress( *Addr );

	if ( Addr->IsValid() == false )
	{
		SocketData.bClosing = true;

		return;
	}

	SocketData.CurrentReconnectAttempt += 1;

	if ( SocketData.MainSocket->Connect( *Addr ) )
	{
		SocketData.CurrentReconnectAttempt = 0;

		OnConnected.Broadcast( SocketData.SocketLookUpID , INDEX_NONE );
	}
	else
	{
		OnReconnecting.Broadcast( SocketData.SocketLookUpID , INDEX_NONE );
	}
}

void ULFPStreamSocketSubsystem::TryReceiveClientData( FLFPStreamSocketData& SocketData ) const
{
	for ( int32 ClientIndex = 0; ClientIndex < SocketData.ClientSocket.Num(); ClientIndex++ )
	{
		FSocket* ClientSocket = SocketData.ClientSocket[ ClientIndex ];

		/** Socket is not valid */
		if ( ClientSocket == nullptr ) continue;

		/** Is data available ? */
		if ( uint32 BufferSize = 0; ClientSocket->HasPendingData( BufferSize ) )
		{
			TArray<uint8> ReceiveBuffer;

			ReceiveBuffer.SetNumUninitialized( BufferSize );

			int32 ReadBtyes = 0;

			ClientSocket->Recv( ReceiveBuffer.GetData() , ReceiveBuffer.Num() , ReadBtyes );

			OnDataReceived.Broadcast( SocketData.SocketLookUpID , ClientIndex , ReceiveBuffer );
		}
	}
}

void ULFPStreamSocketSubsystem::TryReceiveServerData( FLFPStreamSocketData& SocketData ) const
{
	if ( uint32 DataSize = 0; SocketData.MainSocket->HasPendingData( DataSize ) )
	{
		TArray<uint8> ReceiveBuffer;

		ReceiveBuffer.SetNumUninitialized( DataSize );

		int32 ReadBtyes = 0;
		SocketData.MainSocket->Recv( ReceiveBuffer.GetData() , ReceiveBuffer.Num() , ReadBtyes );

		OnDataReceived.Broadcast( SocketData.SocketLookUpID , INDEX_NONE , ReceiveBuffer );
	}
}

void ULFPStreamSocketSubsystem::CheckSocketClientKeepAlive( FLFPStreamSocketData& SocketData )
{
}

void ULFPStreamSocketSubsystem::CheckSocketServerKeepAlive( FLFPStreamSocketData& SocketData )
{
}

void ULFPStreamSocketSubsystem::CloseSocket( FLFPStreamSocketData& SocketData , const int32 ClientID )
{
	if ( ClientID >= 0 )
	{
		if ( SocketData.ClientSocket.IsValidIndex( ClientID ) == false )
		{
			return;
		}

		SocketSubsystem->DestroySocket( SocketData.ClientSocket[ ClientID ] );

		SocketData.ClientSocket.RemoveAt( ClientID );

		OnDisconnected.Broadcast( SocketData.SocketLookUpID , ClientID , ELFPStreamDIsconnectFlags::LFP_StreamSocket_User );

		return;
	}

	if ( SocketData.MainSocket != nullptr )
	{
		SocketSubsystem->DestroySocket( SocketData.MainSocket );

		SocketData.MainSocket = nullptr;

		OnDisconnected.Broadcast( SocketData.SocketLookUpID , INDEX_NONE , ELFPStreamDIsconnectFlags::LFP_StreamSocket_User );
	}

	for ( int32 ClientIndex = 0; ClientIndex < SocketData.ClientSocket.Num(); ClientIndex++ )
	{
		FSocket* ClientSocket = SocketData.ClientSocket[ ClientIndex ];

		if ( ClientSocket == nullptr )
		{
			continue;
		}

		SocketSubsystem->DestroySocket( ClientSocket );

		OnDisconnected.Broadcast( SocketData.SocketLookUpID , ClientIndex , ELFPStreamDIsconnectFlags::LFP_StreamSocket_User );
	}

	SocketData.ClientSocket.Empty();
}

bool ULFPStreamSocketSubsystem::IsSocketValid( const int32 SocketID , const int32 ClientID ) const
{
	for ( const FLFPStreamSocketData& SocketData : SocketList )
	{
		if ( SocketData.SocketLookUpID != SocketID )
		{
			continue;
		}

		return ClientID < 0 || SocketList[ SocketID ].ClientSocket.IsValidIndex( ClientID );
	}

	return false;
}

int32 ULFPStreamSocketSubsystem::CreateSocket( const FLFPStreamSocketSetting& SocketSetting )
{
	if ( SocketSubsystem == nullptr )
	{
		return INDEX_NONE;
	}

	FLFPStreamSocketData& NewSocketData = SocketList.AddDefaulted_GetRef();

	NewSocketData.SocketSetting = SocketSetting;
	NewSocketData.SocketLookUpID = CurrentLookUpID;

	CurrentLookUpID += 1;

	TWeakObjectPtr<ULFPStreamSocketSubsystem> OwnerObj = this;
	const int32 SocketID = NewSocketData.SocketLookUpID;

	FAsyncGetAddressInfoCallback CallbackFunc = [OwnerObj , SocketID] ( const FAddressInfoResult& Results )
		{
			AsyncTask( ENamedThreads::GameThread , [OwnerObj , SocketID , Results]
					   {
						   if ( OwnerObj.IsValid() == false )
						   {
							   return;
						   }

						   for ( FLFPStreamSocketData& SocketData : OwnerObj->SocketList )
						   {
							   if ( SocketData.SocketLookUpID == SocketID )
							   {
								   if ( Results.Results.IsValidIndex( 0 ) == false )
								   {
									   SocketData.bClosing = true;

									   return;
								   }

								   OwnerObj->TryInitializeSocket( SocketData , Results.Results[ 0 ].Address );

								   return;
							   }
						   }
					   }
			);
		};

	SocketSubsystem->GetAddressInfoAsync( CallbackFunc , *NewSocketData.SocketSetting.IP , *FString::FromInt( NewSocketData.SocketSetting.Port ) , EAddressInfoFlags::Default , NAME_None , ESocketType::SOCKTYPE_Streaming );

	return NewSocketData.SocketLookUpID;
}

bool ULFPStreamSocketSubsystem::DestroySocket( const int32 SocketID , const int32 ClientID )
{
	for ( FLFPStreamSocketData& SocketData : SocketList )
	{
		if ( SocketData.SocketLookUpID != SocketID )
		{
			continue;
		}

		CloseSocket( SocketData , ClientID );

		return true;
	}

	return false;
}

bool ULFPStreamSocketSubsystem::SendData( const TArray<uint8>& Data , const int32 SocketID , const int32 ClientID )
{
	if ( SocketList.IsValidIndex( SocketID ) == false )
	{
		UE_LOG( LogTemp , Error , TEXT( "FLFPTcpSocket : SendData Failed Socket Index Invalid : %d : %d" ) , SocketID , ClientID );

		return false;
	}

	for ( FLFPStreamSocketData& TargetSocketData : SocketList )
	{
		if ( TargetSocketData.SocketLookUpID != SocketID )
		{
			continue;
		}

		int32 BtyeSended = 0;

		bool bIsSended = true;

		if ( TargetSocketData.IsListenServer() )
		{
			for ( int32 LoopClientID = 0; LoopClientID < TargetSocketData.ClientSocket.Num(); LoopClientID++ )
			{
				if ( ClientID != INDEX_NONE && LoopClientID != ClientID )
				{
					continue;
				}

				FSocket* ClientSocket = TargetSocketData.ClientSocket[ LoopClientID ];

				if ( ClientSocket == nullptr )
				{
					UE_LOG( LogTemp , Error , TEXT( "ULFPStreamSocketSubsystem : SendData Failed Client Socket Null : %d : %d" ) , SocketID , ClientID );

					continue;
				}

				bIsSended &= ClientSocket->Send( Data.GetData() , Data.Num() , BtyeSended );
			}
		}
		else
		{
			if ( TargetSocketData.MainSocket == nullptr )
			{
				UE_LOG( LogTemp , Error , TEXT( "ULFPStreamSocketSubsystem : SendData Failed Main Socket Null : %d" ) , SocketID );

				bIsSended = false;
			}
			else
			{
				bIsSended &= TargetSocketData.MainSocket->Send( Data.GetData() , Data.Num() , BtyeSended );
			}
		}

		return bIsSended;
	}

	return false;
}

