#include "Subsystem/LFPStreamSocketSubsystem.h"
#include "IPAddress.h"
#include "Async/Async.h"
#include "IPAddressAsyncResolve.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "SocketSubsystem.h"
#include "Common/TcpSocketBuilder.h"

uint32 FLFPStreamSocketPtrHandle::GlobalID = 0;

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
		if ( SocketData.MainSocket.IsClosing() )
		{
			continue;
		}

		if ( SocketData.bInitilized == false )
		{
			continue;
		}

		if ( SocketData.MainSocket.IsValid() == false )
		{
			SocketData.MainSocket.State = ELFPStreamSocketState::LFP_Closing;

			continue;
		}

		// Is Server
		if ( SocketData.IsListenServer() )
		{
			TryConnectClient( SocketData );

			TryReceiveClientData( SocketData );

			PingSocketClient( SocketData );
		}
		else
		{
			TryReceiveServerData( SocketData );

			PingSocketServer( SocketData );
		}
	}

	SocketList.RemoveAll( [&] ( FLFPStreamSocketData& SocketData )
						  {
							  CleanUpSocket( SocketData );

							  return SocketData.MainSocket.IsValid() == false;
						  }
	);
}

void ULFPStreamSocketSubsystem::Deinitialize()
{
	Super::Deinitialize();

	for ( auto& SocketData : SocketList )
	{
		CleanUpSocket( SocketData , true );
	}

	SocketList.Empty();
}

TStatId ULFPStreamSocketSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT( ULFPStreamSocketSubsystem , STATGROUP_Tickables );
}

FLFPStreamSocketData* ULFPStreamSocketSubsystem::GetSocketData( const int32 SocketID )
{
	return SocketList.FindByPredicate( [&] ( const FLFPStreamSocketData& SocketData )
									   {
										   return SocketData.MainSocket.GetID() == SocketID;
									   }
	);
}

const FLFPStreamSocketData* ULFPStreamSocketSubsystem::GetSocketData( const int32 SocketID ) const
{
	return SocketList.FindByPredicate( [&] ( const FLFPStreamSocketData& SocketData )
									   {
										   return SocketData.MainSocket.GetID() == SocketID;
									   }
	);
}

FLFPStreamSocketPtrHandle* ULFPStreamSocketSubsystem::GetSocketPtr( const int32 SocketID , const int32 ClientID )
{
	if ( FLFPStreamSocketData* SocketData = GetSocketData( SocketID ); SocketData != nullptr )
	{
		if ( ClientID > 0 )
		{
			return SocketData->GetClientSocketPtr( ClientID );
		}
		else
		{
			return &SocketData->MainSocket;
		}
	}

	return nullptr;
}

const FLFPStreamSocketPtrHandle* ULFPStreamSocketSubsystem::GetSocketPtr( const int32 SocketID , const int32 ClientID ) const
{
	if ( const FLFPStreamSocketData* SocketData = GetSocketData( SocketID ); SocketData != nullptr )
	{
		if ( ClientID > 0 )
		{
			return SocketData->GetClientSocketPtr( ClientID );
		}
		else
		{
			return &SocketData->MainSocket;
		}
	}

	return nullptr;
}

void ULFPStreamSocketSubsystem::TryInitializeSocket( FLFPStreamSocketData& SocketData , const TSharedRef<FInternetAddr>& Endpoint )
{
	const FString MainDescription = SocketData.SocketSetting.SocketDescription + FString( " : Main Socket" );

	SocketData.MainSocket = SocketSubsystem->CreateSocket( NAME_Stream , *MainDescription , Endpoint->GetProtocolType() );

	if ( SocketData.MainSocket.IsValid() == false )
	{
		SocketData.MainSocket.State = ELFPStreamSocketState::LFP_Closing;

		UE_LOG( LogTemp , Error , TEXT( "ULFPStreamSocketSubsystem : %s : Main Socket create failed" ) , *MainDescription );

		return;
	}

	bool Error = false;

	if ( SocketData.IsListenServer() )
	{
		Error |=
			!SocketData.MainSocket.Socket->SetReuseAddr( SocketData.SocketSetting.bSocketReusable ) ||
			!SocketData.MainSocket.Socket->SetRecvErr() ||
			!SocketData.MainSocket.Socket->Bind( Endpoint.Get() ) ||
			!SocketData.MainSocket.Socket->SetLinger( true , 3.0f ) ||
			!SocketData.MainSocket.Socket->SetNonBlocking( true ) ||
			!SocketData.MainSocket.Socket->Listen( SocketData.SocketSetting.MaxListenConnection );
	}
	else // Try Connect To Server On Initialize
	{
		Error |=
			!SocketData.MainSocket.Socket->SetRecvErr() ||
			!SocketData.MainSocket.Socket->SetLinger( true , 3.0f ) ||
			!SocketData.MainSocket.Socket->SetNonBlocking( true ) ||
			!SocketData.MainSocket.Socket->Connect( Endpoint.Get() );
	}

	if ( Error )
	{
		UE_LOG( LogTemp , Error , TEXT( "ULFPStreamSocketSubsystem : %s : Main Socket ( %d ) create failed as configured" ) , *MainDescription , SocketData.MainSocket.GetID() );

		SocketData.MainSocket.State = ELFPStreamSocketState::LFP_Closing;
	}
	else
	{
		UE_LOG( LogTemp , Log , TEXT( "ULFPStreamSocketSubsystem : Main Socket ( %d ) Currently On %s " ) , SocketData.MainSocket.GetID() , SocketData.IsListenServer() ? TEXT( "Listening" ) : TEXT( "Connected" ) );

		SocketData.MainSocket.MarkActive( SocketData.SocketSetting.TimeOutSecond );

		int32 OutNewSize;

		if ( SocketData.SocketSetting.BufferReadSize > 0 && SocketData.MainSocket.Socket->SetReceiveBufferSize( SocketData.SocketSetting.BufferReadSize , OutNewSize ) )
		{
			UE_LOG( LogTemp , Log , TEXT( "ULFPStreamSocketSubsystem : Main Socket ( %d ) Read Buffer Size %d " ) , SocketData.MainSocket.GetID() , OutNewSize );
		}

		if ( SocketData.SocketSetting.BufferWriteSize > 0 && SocketData.MainSocket.Socket->SetSendBufferSize( SocketData.SocketSetting.BufferWriteSize , OutNewSize ) )
		{
			UE_LOG( LogTemp , Log , TEXT( "ULFPStreamSocketSubsystem : Main Socket ( %d ) Write Buffer Size %d " ) , SocketData.MainSocket.GetID() , OutNewSize );
		}
	}

	SocketData.bInitilized = true; // All normal pass
}

void ULFPStreamSocketSubsystem::TryConnectClient( FLFPStreamSocketData& SocketData )
{
	if ( bool bHasPendingConnection = false; SocketData.MainSocket.Socket->HasPendingConnection( bHasPendingConnection ) && bHasPendingConnection )
	{
		const FString ConnectDescription = SocketData.SocketSetting.SocketDescription + FString::Printf( TEXT( " : Client Socket ID ( %d )" ) , FLFPStreamSocketPtrHandle::GetNextID() );

		TSharedRef<FInternetAddr> Addr = SocketSubsystem->CreateInternetAddr();

		FSocket* NewSocket = SocketData.MainSocket.Socket->Accept( *Addr , ConnectDescription );

		if ( NewSocket != nullptr )
		{
			NewSocket->SetRecvErr();
			NewSocket->SetNonBlocking();

			OnConnected.Broadcast( SocketData.MainSocket.GetID() , SocketData.ClientSocket.Add_GetRef( NewSocket ).GetID() );

			UE_LOG( LogTemp , Log , TEXT( "ULFPStreamSocketSubsystem : Connected Client ( %s ) On Socket ( %d ) : Addr ( %s )" ) , *ConnectDescription , SocketData.MainSocket.GetID() , *( Addr.Get().ToString( true ) ) );
		}
		else
		{
			UE_LOG( LogTemp , Warning , TEXT( "ULFPStreamSocketSubsystem : Connect Fail Client ( %s ) On Socket ( %d ) : Addr ( %s )" ) , *ConnectDescription , SocketData.MainSocket.GetID() , *( Addr.Get().ToString( true ) ) );
		}
	}
}

void ULFPStreamSocketSubsystem::TryReceiveClientData( FLFPStreamSocketData& SocketData ) const
{
	for ( int32 ClientIndex = 0; ClientIndex < SocketData.ClientSocket.Num(); ClientIndex++ )
	{
		FLFPStreamSocketPtrHandle& ClientSocket = SocketData.ClientSocket[ ClientIndex ];

		/** Socket is not valid */
		if ( ClientSocket.IsValid() == false || ClientSocket.IsClosing() ) continue;

		/** Is data available ? */
		if ( uint32 BufferSize = 0; ClientSocket.Socket->HasPendingData( BufferSize ) )
		{
			TArray<uint8> ReceiveBuffer;

			ReceiveBuffer.SetNumUninitialized( BufferSize );

			int32 ReadBtyes = 0;

			if ( ClientSocket.Socket->Recv( ReceiveBuffer.GetData() , ReceiveBuffer.Num() , ReadBtyes ) )
			{
				ClientSocket.MarkActive( SocketData.SocketSetting.TimeOutSecond );

				OnDataReceived.Broadcast( SocketData.MainSocket.GetID() , ClientIndex , ReceiveBuffer );
			}
		}
	}
}

void ULFPStreamSocketSubsystem::TryReceiveServerData( FLFPStreamSocketData& SocketData ) const
{
	if ( uint32 DataSize = 0; SocketData.MainSocket.Socket->HasPendingData( DataSize ) )
	{
		TArray<uint8> ReceiveBuffer;

		ReceiveBuffer.SetNumUninitialized( DataSize );

		int32 ReadBtyes = 0;

		if ( SocketData.MainSocket.Socket->Recv( ReceiveBuffer.GetData() , ReceiveBuffer.Num() , ReadBtyes ) )
		{
			SocketData.MainSocket.MarkActive( SocketData.SocketSetting.TimeOutSecond );

			OnDataReceived.Broadcast( SocketData.MainSocket.GetID() , INDEX_NONE , ReceiveBuffer );
		}
	}
}

void ULFPStreamSocketSubsystem::PingSocketClient( FLFPStreamSocketData& SocketData )
{
	TArray<uint8> SendData = { 0 };

	for ( FLFPStreamSocketPtrHandle& SocketPtr : SocketData.ClientSocket )
	{
		if ( SocketPtr.IsValid() == false || SocketPtr.IsClosing() || SocketPtr.IsActive() )
		{
			continue;
		}

		SocketPtr.MarkActive( SocketData.SocketSetting.PingInterval );

		if ( SocketPtr.Socket->Send( SendData.GetData() , SendData.Num() , SocketPtr.LastBtyeSendOrReceive ) )
		{
			SocketPtr.CurrentPingFailedAttempt = 0;
		}
		else
		{
			SocketPtr.CurrentPingFailedAttempt += 1;

			if ( SocketPtr.CurrentPingFailedAttempt >= SocketData.SocketSetting.MaxReconnectAttempt )
			{
				SocketPtr.State = ELFPStreamSocketState::LFP_Closing;
			}
			else
			{
				UE_LOG( LogTemp , Warning , TEXT( "ULFPStreamSocketSubsystem : Reconnecting Client ( %d ) On Socket ( %d )" ) , SocketPtr.GetID() , SocketData.MainSocket.GetID() );

				OnReconnecting.Broadcast( SocketData.MainSocket.GetID() , SocketPtr.GetID() );
			}
		}
	}
}

void ULFPStreamSocketSubsystem::PingSocketServer( FLFPStreamSocketData& SocketData )
{
	if ( SocketData.MainSocket.Socket->GetConnectionState() != ESocketConnectionState::SCS_Connected )
	{
		return;
	}

	TArray<uint8> SendData = { 0 };

	FLFPStreamSocketPtrHandle& SocketPtr = SocketData.MainSocket;

	if ( SocketPtr.IsValid() == false || SocketPtr.IsClosing() || SocketPtr.IsActive() )
	{
		return;
	}

	SocketPtr.MarkActive( SocketData.SocketSetting.PingInterval );

	if ( SocketPtr.Socket->Send( SendData.GetData() , SendData.Num() , SocketPtr.LastBtyeSendOrReceive ) )
	{
		SocketPtr.CurrentPingFailedAttempt = 0;
	}
	else
	{
		SocketPtr.CurrentPingFailedAttempt += 1;

		if ( SocketPtr.CurrentPingFailedAttempt >= SocketData.SocketSetting.MaxReconnectAttempt )
		{
			SocketPtr.State = ELFPStreamSocketState::LFP_Closing;
		}
		else
		{
			UE_LOG( LogTemp , Warning , TEXT( "ULFPStreamSocketSubsystem : Reconnecting On Socket ( %d )" ) , SocketPtr.GetID() );

			OnReconnecting.Broadcast( SocketPtr.GetID() , INDEX_NONE );
		}
	}
}

void ULFPStreamSocketSubsystem::CleanUpSocket( FLFPStreamSocketData& SocketData , const bool bForce )
{
	if ( SocketData.MainSocket.IsValid() && ( SocketData.MainSocket.IsClosing() || bForce ) )
	{
		SocketSubsystem->DestroySocket( SocketData.MainSocket.Socket );

		SocketData.MainSocket.Socket = nullptr;

		OnDisconnected.Broadcast( SocketData.MainSocket.GetID() , INDEX_NONE , ELFPStreamDIsconnectFlags::LFP_User );

		UE_LOG( LogTemp , Log , TEXT( "ULFPStreamSocketSubsystem : Disconnected Socket %d On Code ( %d )" ) , SocketData.MainSocket.GetID() , SocketData.MainSocket.LastBtyeSendOrReceive );
	}

	for ( int32 ClientIndex = 0; ClientIndex < SocketData.ClientSocket.Num(); ClientIndex++ )
	{
		FLFPStreamSocketPtrHandle& ClientSocket = SocketData.ClientSocket[ ClientIndex ];

		if ( ClientSocket.IsValid() == false || ( ClientSocket.IsClosing() == false && bForce == false ) )
		{
			continue;
		}

		SocketSubsystem->DestroySocket( ClientSocket.Socket );

		ClientSocket.Socket = nullptr;

		OnDisconnected.Broadcast( SocketData.MainSocket.GetID() , ClientIndex , ELFPStreamDIsconnectFlags::LFP_User );

		UE_LOG( LogTemp , Log , TEXT( "ULFPStreamSocketSubsystem : Disconnected Client %d From Socket %d On Code ( %d )" ) , ClientSocket.GetID() , SocketData.MainSocket.GetID() , ClientSocket.LastBtyeSendOrReceive );
	}

	SocketData.ClientSocket.RemoveAll( [&] ( const FLFPStreamSocketPtrHandle& ClientSocket ) { return ClientSocket.IsValid() == false; } );
}

bool ULFPStreamSocketSubsystem::IsSocketValid( const int32 SocketID , const int32 ClientID ) const
{
	const FLFPStreamSocketPtrHandle* PtrHandle = GetSocketPtr( SocketID , ClientID );

	return PtrHandle != nullptr && PtrHandle->IsValid();
}

int32 ULFPStreamSocketSubsystem::CreateSocket( const FLFPStreamSocketSetting& SocketSetting )
{
	if ( SocketSubsystem == nullptr )
	{
		return INDEX_NONE;
	}

	FLFPStreamSocketData& NewSocketData = SocketList.AddDefaulted_GetRef();

	NewSocketData.SocketSetting = SocketSetting;

	TWeakObjectPtr<ULFPStreamSocketSubsystem> OwnerObj = this;
	const int32 SocketID = NewSocketData.MainSocket.GetID();

	FAsyncGetAddressInfoCallback CallbackFunc = [OwnerObj , SocketID] ( const FAddressInfoResult& Results )
		{
			AsyncTask( ENamedThreads::GameThread , [OwnerObj , SocketID , Results]
					   {
						   if ( OwnerObj.IsValid() == false )
						   {
							   return;
						   }

						   if ( FLFPStreamSocketData* SocketData = OwnerObj->GetSocketData( SocketID ); SocketData != nullptr )
						   {
							   if ( Results.Results.IsValidIndex( 0 ) == false )
							   {
								   SocketData->MainSocket.State = ELFPStreamSocketState::LFP_Closing;

								   return;
							   }

							   OwnerObj->TryInitializeSocket( *SocketData , Results.Results[ 0 ].Address );
						   }
					   }
			);
		};

	SocketSubsystem->GetAddressInfoAsync( CallbackFunc , *NewSocketData.SocketSetting.IP , *FString::FromInt( NewSocketData.SocketSetting.Port ) , EAddressInfoFlags::Default , NAME_None , ESocketType::SOCKTYPE_Streaming );

	return SocketID;
}

bool ULFPStreamSocketSubsystem::DestroySocket( const int32 SocketID , const int32 ClientID )
{
	if ( FLFPStreamSocketData* SocketData = GetSocketData( SocketID ); SocketData != nullptr )
	{
		if ( ClientID < 0 )
		{
			SocketData->MainSocket.State = ELFPStreamSocketState::LFP_Closing;
		}
		else if ( FLFPStreamSocketPtrHandle* SocketHandle = SocketData->GetClientSocketPtr( ClientID ); SocketHandle != nullptr )
		{
			SocketHandle->State = ELFPStreamSocketState::LFP_Closing;
		}
		else
		{
			return false;
		}

		CleanUpSocket( *SocketData );

		return true;
	}

	return false;
}

bool ULFPStreamSocketSubsystem::SendData( const TArray<uint8>& Data , const int32 SocketID , const int32 ClientID )
{
	if ( FLFPStreamSocketData* SocketData = GetSocketData( SocketID ); SocketData != nullptr )
	{
		bool bIsSended = true;

		if ( SocketData->IsListenServer() )
		{
			for ( int32 LoopClientIndex = 0; LoopClientIndex < SocketData->ClientSocket.Num(); LoopClientIndex++ )
			{
				FLFPStreamSocketPtrHandle& ClientSocket = SocketData->ClientSocket[ LoopClientIndex ];

				if ( ClientSocket.GetID() != ClientID && ClientID > 0 )
				{
					continue;
				}

				if ( ClientSocket.IsValid() == false || ClientSocket.IsClosing() )
				{
					UE_LOG( LogTemp , Error , TEXT( "ULFPStreamSocketSubsystem : SendData Failed Client Socket Invalid Or Closing : %d : %d" ) , SocketID , LoopClientIndex );

					continue;
				}

				const bool bIsSuccess = ClientSocket.Socket->Send( Data.GetData() , Data.Num() , ClientSocket.LastBtyeSendOrReceive );

				bIsSended &= bIsSuccess;

				if ( bIsSuccess )
				{
					ClientSocket.MarkActive( SocketData->SocketSetting.TimeOutSecond );
				}
			}
		}
		else
		{
			if ( SocketData->MainSocket.IsValid() == false || SocketData->MainSocket.IsClosing() )
			{
				UE_LOG( LogTemp , Error , TEXT( "ULFPStreamSocketSubsystem : SendData Failed MainSocket Invalid Or Closing : %d" ) , SocketID );

				bIsSended = false;
			}
			else
			{
				const bool bIsSuccess = SocketData->MainSocket.Socket->Send( Data.GetData() , Data.Num() , SocketData->MainSocket.LastBtyeSendOrReceive );

				bIsSended &= bIsSuccess;

				if ( bIsSuccess )
				{
					SocketData->MainSocket.MarkActive( SocketData->SocketSetting.TimeOutSecond );
				}
			}
		}

		return bIsSended;
	}
	else
	{
		UE_LOG( LogTemp , Error , TEXT( "FLFPTcpSocket : SendData Failed Socket Index Invalid : %d : %d" ) , SocketID , ClientID );
	}

	return false;
}

