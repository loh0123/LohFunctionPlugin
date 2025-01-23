#include "Subsystem/LFPStreamSocketSubsystem.h"
#include "IPAddress.h"
#include "Async/Async.h"
#include "SocketSubsystem.h"
#include "Common/TcpSocketBuilder.h"

uint32 FLFPStreamSocketPtrHandle::GlobalID = 0;

bool FLFPStreamSocketData::TryInitializeSocket ( ISocketSubsystem* SocketSubsystem , const TSharedRef <FInternetAddr>& Endpoint )
{
	const FString MainDescription = SocketSetting.SocketDescription + FString ( " : Main Socket" );

	MainSocket = SocketSubsystem->CreateSocket ( NAME_Stream , *MainDescription , Endpoint->GetProtocolType ( ) );

	if ( MainSocket.IsValid ( ) == false )
	{
		MainSocket.MarkClosing ( ELFPStreamDisconnectFlags::LFP_SubsystemInvalid );

		UE_LOG ( LogTemp , Error , TEXT( "ULFPStreamSocketSubsystem : %s : Main Socket create failed" ) , *MainDescription );

		return false;
	}

	bool Error = false;

	if ( IsListenServer ( ) )
	{
		Error |=
				!MainSocket.Socket->SetReuseAddr ( SocketSetting.bSocketReusable ) ||
				!MainSocket.Socket->SetRecvErr ( ) ||
				!MainSocket.Socket->Bind ( Endpoint.Get ( ) ) ||
				!MainSocket.Socket->SetLinger ( SocketSetting.LingerTime > 0.0f , SocketSetting.LingerTime ) ||
				!MainSocket.Socket->SetNonBlocking ( true ) ||
				!MainSocket.Socket->SetNoDelay ( SocketSetting.bNoDelay ) ||
				!MainSocket.Socket->Listen ( SocketSetting.MaxListenConnection );
	}
	else // Try To Connect Server On Initialize
	{
		Error |=
				!MainSocket.Socket->SetRecvErr ( ) ||
				!MainSocket.Socket->SetLinger ( SocketSetting.LingerTime > 0.0f , SocketSetting.LingerTime ) ||
				!MainSocket.Socket->SetNonBlocking ( true ) ||
				!MainSocket.Socket->SetNoDelay ( SocketSetting.bNoDelay ) ||
				!MainSocket.Socket->Connect ( Endpoint.Get ( ) );
	}

	if ( Error )
	{
		UE_LOG ( LogTemp , Error , TEXT( "ULFPStreamSocketSubsystem : %s : Main Socket ( %d ) create failed as configured" ) , *MainDescription , MainSocket.GetID() );

		MainSocket.MarkClosing ( ELFPStreamDisconnectFlags::LFP_FailToCreate );

		return false;
	}

	UE_LOG ( LogTemp , Log , TEXT( "ULFPStreamSocketSubsystem : Main Socket ( %d ) Currently On %s " ) , MainSocket.GetID() , IsListenServer() ? TEXT( "Listening" ) : TEXT( "Connected" ) );

	MainSocket.MarkActive ( SocketSetting.TimeOutSecond );

	int32 OutNewSize;

	if ( SocketSetting.BufferReadSize > 0 && MainSocket.Socket->SetReceiveBufferSize ( SocketSetting.BufferReadSize , OutNewSize ) )
	{
		UE_LOG ( LogTemp , Log , TEXT( "ULFPStreamSocketSubsystem : Main Socket ( %d ) Read Buffer Size %d " ) , MainSocket.GetID() , OutNewSize );
	}

	if ( SocketSetting.BufferWriteSize > 0 && MainSocket.Socket->SetSendBufferSize ( SocketSetting.BufferWriteSize , OutNewSize ) )
	{
		UE_LOG ( LogTemp , Log , TEXT( "ULFPStreamSocketSubsystem : Main Socket ( %d ) Write Buffer Size %d " ) , MainSocket.GetID() , OutNewSize );
	}

	bInitialized = true; // All normal pass

	return true;
}

int32 FLFPStreamSocketData::TryConnectClient ( ISocketSubsystem* SocketSubsystem )
{
	if ( bool bHasPendingConnection = false ; MainSocket.Socket->HasPendingConnection ( bHasPendingConnection ) && bHasPendingConnection )
	{
		const FString ConnectDescription = SocketSetting.SocketDescription + FString::Printf ( TEXT ( " : Client Socket ID ( %d )" ) , FLFPStreamSocketPtrHandle::GetNextID ( ) );

		TSharedRef <FInternetAddr> Addr = SocketSubsystem->CreateInternetAddr ( );

		FSocket* NewSocket = MainSocket.Socket->Accept ( *Addr , ConnectDescription );

		if ( NewSocket != nullptr )
		{
			NewSocket->SetRecvErr ( );
			NewSocket->SetNonBlocking ( );
			NewSocket->SetNoDelay ( SocketSetting.bNoDelay );

			UE_LOG ( LogTemp , Log , TEXT( "ULFPStreamSocketSubsystem : Connected Client ( %s ) On Socket ( %d ) : Addr ( %s )" ) , *ConnectDescription , MainSocket.GetID() , *( Addr.Get().ToString( true ) ) );

			return ClientSocketList.Add_GetRef ( NewSocket ).GetID ( );
		}
		UE_LOG ( LogTemp , Warning , TEXT( "ULFPStreamSocketSubsystem : Connect Fail Client ( %s ) On Socket ( %d ) : Addr ( %s )" ) , *ConnectDescription , MainSocket.GetID() , *( Addr.Get().ToString( true ) ) );
	}

	return INDEX_NONE;
}

bool FLFPStreamSocketData::TryReceiveClientData ( const int32 ClientID , TArray <uint8>& ReceiveBuffer )
{
	FLFPStreamSocketPtrHandle& ClientSocket = ClientSocketList[ ClientID ];

	/** Socket is not valid */
	if ( ClientSocket.IsValid ( ) == false || ClientSocket.IsClosing ( ) )
	{
		return false;
	}

	uint32 MinBufferNeeded = ClientSocket.IsIncomingPackage ( )
		                         ? ClientSocket.CurrentPackageInfo.PackageSize
		                         : sizeof ( FLFPStreamSocketPackageInfo );

	/** Is data available ? */
	if ( uint32 BufferSize = 0 ; ClientSocket.Socket->HasPendingData ( BufferSize ) && BufferSize >= MinBufferNeeded )
	{
		ReceiveBuffer.SetNumUninitialized ( MinBufferNeeded );

		if ( int32 ReadBytes = 0 ; ClientSocket.Socket->Recv ( ReceiveBuffer.GetData ( ) , ReceiveBuffer.Num ( ) , ReadBytes ) )
		{
			ClientSocket.MarkActive ( SocketSetting.TimeOutSecond );

			if ( ClientSocket.IsIncomingPackage ( ) )
			{
				ClientSocket.MarkIdle ( );

				return true;
			}
			
			FMemoryReader PkgReader ( ReceiveBuffer );

			FLFPStreamSocketPackageInfo::StaticStruct ( )->SerializeBin ( PkgReader , &ClientSocket.CurrentPackageInfo );

			if ( ClientSocket.CurrentPackageInfo.PackageSize > 0 )
			{
				ClientSocket.MarkIncomingPackage ( );

				UE_LOG ( LogTemp , Log , TEXT( "ULFPStreamSocketSubsystem : Client Index ( %d ) On Socket ( %d ) : PkgIncoming ( Size : %d )" ) , ClientID , MainSocket.GetID() , ClientSocket.CurrentPackageInfo.PackageSize );
			}
		}
	}

	return false;
}

bool FLFPStreamSocketData::TryReceiveServerData ( TArray <uint8>& ReceiveBuffer )
{
	if ( MainSocket.IsValid ( ) == false || MainSocket.IsClosing ( ) )
	{
		return false;
	}

	uint32 MinBufferNeeded = MainSocket.IsIncomingPackage ( )
		                         ? MainSocket.CurrentPackageInfo.PackageSize
		                         : sizeof ( FLFPStreamSocketPackageInfo );

	if ( uint32 BufferSize = 0 ; MainSocket.Socket->HasPendingData ( BufferSize ) && BufferSize >= MinBufferNeeded )
	{
		ReceiveBuffer.SetNumUninitialized ( MinBufferNeeded );

		if ( int32 ReadBytes = 0 ; MainSocket.Socket->Recv ( ReceiveBuffer.GetData ( ) , ReceiveBuffer.Num ( ) , ReadBytes ) )
		{
			MainSocket.MarkActive ( SocketSetting.TimeOutSecond );

			if ( MainSocket.IsIncomingPackage ( ) )
			{
				MainSocket.MarkIdle ( );

				return true;
			}

			FMemoryReader PkgReader ( ReceiveBuffer );

			FLFPStreamSocketPackageInfo::StaticStruct ( )->SerializeBin ( PkgReader , &MainSocket.CurrentPackageInfo );

			if ( MainSocket.CurrentPackageInfo.PackageSize > 0 )
			{
				MainSocket.MarkIncomingPackage ( );
			}
		}
	}

	return false;
}

void FLFPStreamSocketData::PingSocketClient ( TArray <int32>& ReconnectingClientIDList )
{
	TArray <uint8> PkgData;
	{
		FLFPStreamSocketPackageInfo PkgInfo;

		PkgInfo.PackageSize = 0;

		FMemoryWriter PkgWriter ( PkgData , false );

		FLFPStreamSocketPackageInfo::StaticStruct ( )->SerializeBin ( PkgWriter , &PkgInfo );
	}

	for ( FLFPStreamSocketPtrHandle& SocketPtr : ClientSocketList )
	{
		if ( SocketPtr.IsValid ( ) == false || SocketPtr.IsClosing ( ) || SocketPtr.IsActive ( ) )
		{
			continue;
		}

		SocketPtr.MarkActive ( SocketSetting.PingInterval );

		if ( SocketPtr.Socket->Send ( PkgData.GetData ( ) , PkgData.Num ( ) , SocketPtr.LastBytesSendOrReceive ) )
		{
			SocketPtr.CurrentPingFailedAttempt = 0;
		}
		else
		{
			SocketPtr.CurrentPingFailedAttempt += 1;

			if ( SocketPtr.CurrentPingFailedAttempt >= SocketSetting.MaxReconnectAttempt )
			{
				SocketPtr.MarkClosing ( ELFPStreamDisconnectFlags::LFP_LoseConnection );
			}
			else
			{
				UE_LOG ( LogTemp , Warning , TEXT( "ULFPStreamSocketSubsystem : Reconnecting Client ( %d ) On Socket ( %d )" ) , SocketPtr.GetID() , MainSocket.GetID() );

				ReconnectingClientIDList.Add ( SocketPtr.GetID ( ) );
			}
		}
	}
}

bool FLFPStreamSocketData::PingSocketServer ( )
{
	if ( MainSocket.Socket->GetConnectionState ( ) != SCS_Connected )
	{
		return false;
	}

	TArray <uint8> PkgData;
	{
		FLFPStreamSocketPackageInfo PkgInfo;

		PkgInfo.PackageSize = 0;

		FMemoryWriter PkgWriter ( PkgData , false );

		FLFPStreamSocketPackageInfo::StaticStruct ( )->SerializeBin ( PkgWriter , &PkgInfo );
	}

	FLFPStreamSocketPtrHandle& SocketPtr = MainSocket;

	if ( SocketPtr.IsValid ( ) == false || SocketPtr.IsClosing ( ) || SocketPtr.IsActive ( ) )
	{
		return false;
	}

	SocketPtr.MarkActive ( SocketSetting.PingInterval );

	if ( SocketPtr.Socket->Send ( PkgData.GetData ( ) , PkgData.Num ( ) , SocketPtr.LastBytesSendOrReceive ) )
	{
		SocketPtr.CurrentPingFailedAttempt = 0;
	}
	else
	{
		SocketPtr.CurrentPingFailedAttempt += 1;

		if ( SocketPtr.CurrentPingFailedAttempt >= SocketSetting.MaxReconnectAttempt )
		{
			SocketPtr.MarkClosing ( ELFPStreamDisconnectFlags::LFP_LoseConnection );
		}
		else
		{
			UE_LOG ( LogTemp , Warning , TEXT( "ULFPStreamSocketSubsystem : Reconnecting On Socket ( %d )" ) , SocketPtr.GetID() );

			return false;
		}
	}

	return true;
}

void FLFPStreamSocketData::CloseUpSocket ( ISocketSubsystem* SocketSubsystem , const bool bForce )
{
	if ( MainSocket.IsValid ( ) && ( MainSocket.IsClosing ( ) || bForce ) )
	{
		SocketSubsystem->DestroySocket ( MainSocket.Socket );

		MainSocket.Socket = nullptr;

		MainSocket.MarkClosed ( );

		UE_LOG ( LogTemp , Log , TEXT( "ULFPStreamSocketSubsystem : Disconnected Socket %d On Code ( %d )" ) , MainSocket.GetID() , MainSocket.LastBytesSendOrReceive );
	}

	for ( int32 ClientIndex = 0 ; ClientIndex < ClientSocketList.Num ( ) ; ClientIndex++ )
	{
		FLFPStreamSocketPtrHandle& ClientSocket = ClientSocketList[ ClientIndex ];

		// Socket already closed
		if ( ClientSocket.HasClosed ( ) )
		{
			continue;
		}

		if ( ClientSocket.IsValid ( ) && ( ClientSocket.IsClosing ( ) || bForce ) )
		{
			SocketSubsystem->DestroySocket ( ClientSocket.Socket );

			ClientSocket.Socket = nullptr;
		}

		// Socket invalid close it now
		if ( ClientSocket.IsValid ( ) == false )
		{
			ClientSocket.MarkClosed ( );

			UE_LOG ( LogTemp , Log , TEXT( "ULFPStreamSocketSubsystem : Disconnected Client %d From Socket %d On Code ( %d )" ) , ClientSocket.GetID() , MainSocket.GetID() , ClientSocket.LastBytesSendOrReceive );
		}
	}
}

void FLFPStreamSocketData::CleanUpClientSocket ( )
{
	ClientSocketList.RemoveAll ( [&] ( const FLFPStreamSocketPtrHandle& ClientSocket ) { return ClientSocket.HasClosed ( ); } );
}

void ULFPStreamSocketSubsystem::Initialize ( FSubsystemCollectionBase& Collection )
{
	Super::Initialize ( Collection );

	SocketSubsystem = ISocketSubsystem::Get ( PLATFORM_SOCKETSUBSYSTEM );

	if ( SocketSubsystem == nullptr )
	{
		UE_LOG ( LogTemp , Error , TEXT( "ULFPStreamSocketSubsystem : SocketSubsystem is nullptr" ) );
	}
}

void ULFPStreamSocketSubsystem::Tick ( float DeltaTime )
{
	Super::Tick ( DeltaTime );

	if ( SocketSubsystem == nullptr )
	{
		return;
	}

	for ( auto& SocketData : SocketList )
	{
		if ( SocketData.MainSocket.IsClosing ( ) )
		{
			continue;
		}

		if ( SocketData.bInitialized == false )
		{
			continue;
		}

		if ( SocketData.MainSocket.IsValid ( ) == false )
		{
			SocketData.MainSocket.MarkClosing ( ELFPStreamDisconnectFlags::LFP_None );

			continue;
		}

		// Is Server
		if ( SocketData.IsListenServer ( ) )
		{
			TryConnectClient ( SocketData );

			TryReceiveClientData ( SocketData );

			PingSocketClient ( SocketData );
		}
		else
		{
			TryReceiveServerData ( SocketData );

			PingSocketClient ( SocketData );
		}
	}

	SocketList.RemoveAll ( [&] ( FLFPStreamSocketData& SocketData )
	                      {
		                      CleanUpSocket ( SocketData );

		                      return SocketData.HasClosed ( );
	                      }
	                     );
}

void ULFPStreamSocketSubsystem::Deinitialize ( )
{
	Super::Deinitialize ( );

	for ( auto& SocketData : SocketList )
	{
		CleanUpSocket ( SocketData , true );
	}

	SocketList.Empty ( );
}

TStatId ULFPStreamSocketSubsystem::GetStatId ( ) const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT ( ULFPStreamSocketSubsystem , STATGROUP_Tickables );
}

FLFPStreamSocketData* ULFPStreamSocketSubsystem::GetSocketData ( const int32 SocketID )
{
	return SocketList.FindByPredicate ( [&] ( const FLFPStreamSocketData& SocketData )
	                                   {
		                                   return SocketData.MainSocket.GetID ( ) == SocketID;
	                                   }
	                                  );
}

const FLFPStreamSocketData* ULFPStreamSocketSubsystem::GetSocketData ( const int32 SocketID ) const
{
	return SocketList.FindByPredicate ( [&] ( const FLFPStreamSocketData& SocketData )
	                                   {
		                                   return SocketData.MainSocket.GetID ( ) == SocketID;
	                                   }
	                                  );
}

FLFPStreamSocketPtrHandle* ULFPStreamSocketSubsystem::GetSocketPtr ( const int32 SocketID , const int32 ClientID )
{
	if ( FLFPStreamSocketData* SocketData = GetSocketData ( SocketID ) ; SocketData != nullptr )
	{
		if ( ClientID > 0 )
		{
			return SocketData->GetClientSocketPtr ( ClientID );
		}
		return &SocketData->MainSocket;
	}

	return nullptr;
}

const FLFPStreamSocketPtrHandle* ULFPStreamSocketSubsystem::GetSocketPtr ( const int32 SocketID , const int32 ClientID ) const
{
	if ( const FLFPStreamSocketData* SocketData = GetSocketData ( SocketID ) ; SocketData != nullptr )
	{
		if ( ClientID > 0 )
		{
			return SocketData->GetClientSocketPtr ( ClientID );
		}
		return &SocketData->MainSocket;
	}

	return nullptr;
}

void ULFPStreamSocketSubsystem::TryConnectClient ( FLFPStreamSocketData& SocketData ) const
{
	if ( const int32 NewClientID = SocketData.TryConnectClient ( SocketSubsystem ) ; NewClientID != INDEX_NONE )
	{
		OnConnected.Broadcast ( SocketData.MainSocket.GetID ( ) , NewClientID );
	}
}

void ULFPStreamSocketSubsystem::TryReceiveClientData ( FLFPStreamSocketData& SocketData ) const
{
	for ( int32 ClientID = 0 ; ClientID < SocketData.ClientSocketList.Num ( ) ; ClientID++ )
	{
		if ( TArray <uint8> ReceiveDataList ; SocketData.TryReceiveClientData ( ClientID , ReceiveDataList ) )
		{
			OnDataReceived.Broadcast ( SocketData.MainSocket.GetID ( ) , ClientID , ReceiveDataList );
		}
	}
}

void ULFPStreamSocketSubsystem::TryReceiveServerData ( FLFPStreamSocketData& SocketData ) const
{
	if ( TArray <uint8> ReceiveDataList ; SocketData.TryReceiveServerData ( ReceiveDataList ) )
	{
		OnDataReceived.Broadcast ( SocketData.MainSocket.GetID ( ) , INDEX_NONE , ReceiveDataList );
	}
}

void ULFPStreamSocketSubsystem::PingSocketClient ( FLFPStreamSocketData& SocketData ) const
{
	TArray <int32> ReconnectingClientIDList;

	SocketData.PingSocketClient ( ReconnectingClientIDList );

	for ( const int32 ReconnectingClientID : ReconnectingClientIDList )
	{
		OnReconnecting.Broadcast ( SocketData.MainSocket.GetID ( ) , ReconnectingClientID );
	}
}

void ULFPStreamSocketSubsystem::PingSocketServer ( FLFPStreamSocketData& SocketData ) const
{
	if ( SocketData.PingSocketServer ( ) == false )
	{
		OnReconnecting.Broadcast ( SocketData.MainSocket.GetID ( ) , INDEX_NONE );
	}
}

void ULFPStreamSocketSubsystem::CleanUpSocket ( FLFPStreamSocketData& SocketData , const bool bForce ) const
{
	const int32 SocketID = SocketData.MainSocket.GetID ( );

	SocketData.CloseUpSocket ( SocketSubsystem , bForce );

	if ( SocketData.HasClosed ( ) && SocketData.IsListenServer ( ) == false )
	{
		OnDisconnected.Broadcast ( SocketID , INDEX_NONE , SocketData.MainSocket.GetDisconnectedReason ( ) );
	}

	for ( const auto ClientSocket : SocketData.ClientSocketList )
	{
		if ( ClientSocket.HasClosed ( ) == false )
		{
			continue;
		}

		OnDisconnected.Broadcast ( SocketID , ClientSocket.GetID ( ) , ClientSocket.GetDisconnectedReason ( ) );
	}

	SocketData.CleanUpClientSocket ( );
}

bool ULFPStreamSocketSubsystem::IsSocketValid ( const int32 SocketID , const int32 ClientID ) const
{
	const FLFPStreamSocketPtrHandle* PtrHandle = GetSocketPtr ( SocketID , ClientID );

	return PtrHandle != nullptr && PtrHandle->IsValid ( );
}

int32 ULFPStreamSocketSubsystem::CreateSocket ( const FLFPStreamSocketSetting& SocketSetting )
{
	if ( SocketSubsystem == nullptr )
	{
		return INDEX_NONE;
	}

	FLFPStreamSocketData& NewSocketData = SocketList.AddDefaulted_GetRef ( );

	NewSocketData.SocketSetting = SocketSetting;

	TWeakObjectPtr <ULFPStreamSocketSubsystem> OwnerObj = this;
	const int32                                SocketID = NewSocketData.MainSocket.GetID ( );

	FAsyncGetAddressInfoCallback CallbackFunc = [OwnerObj , SocketID] ( const FAddressInfoResult& Results )
	{
		AsyncTask ( ENamedThreads::GameThread , [OwnerObj , SocketID , Results]
		            {
			            if ( OwnerObj.IsValid ( ) == false )
			            {
				            return;
			            }

			            if ( FLFPStreamSocketData* SocketData = OwnerObj->GetSocketData ( SocketID ) ; SocketData != nullptr )
			            {
				            if ( Results.Results.IsValidIndex ( 0 ) == false )
				            {
					            SocketData->MainSocket.MarkClosing ( ELFPStreamDisconnectFlags::LFP_NoConnection );

					            return;
				            }

				            if ( SocketData->TryInitializeSocket ( OwnerObj->SocketSubsystem , Results.Results[ 0 ].Address ) && SocketData->IsListenServer ( ) == false )
				            {
					            // Call to notify client is connected to server
					            OwnerObj->OnConnected.Broadcast ( SocketData->MainSocket.GetID ( ) , INDEX_NONE );
				            }
			            }
		            }
		          );
	};

	SocketSubsystem->GetAddressInfoAsync ( CallbackFunc , *NewSocketData.SocketSetting.IP , *FString::FromInt ( NewSocketData.SocketSetting.Port ) , EAddressInfoFlags::Default , NAME_None , SOCKTYPE_Streaming );

	return SocketID;
}

bool ULFPStreamSocketSubsystem::DestroySocket ( const int32 SocketID , const int32 ClientID )
{
	if ( FLFPStreamSocketData* SocketData = GetSocketData ( SocketID ) ; SocketData != nullptr )
	{
		if ( ClientID < 0 )
		{
			SocketData->MainSocket.MarkClosing ( ELFPStreamDisconnectFlags::LFP_User );
		}
		else if ( FLFPStreamSocketPtrHandle* SocketHandle = SocketData->GetClientSocketPtr ( ClientID ) ; SocketHandle != nullptr )
		{
			SocketHandle->MarkClosing ( ELFPStreamDisconnectFlags::LFP_User );
		}
		else
		{
			return false;
		}

		CleanUpSocket ( *SocketData );

		return true;
	}

	return false;
}

bool ULFPStreamSocketSubsystem::SendData ( const TArray <uint8>& Data , const int32 SocketID , const int32 ClientID )
{
	if ( FLFPStreamSocketData* SocketData = GetSocketData ( SocketID ) ; SocketData != nullptr )
	{
		TArray <uint8> PkgData;
		{
			FLFPStreamSocketPackageInfo PkgInfo;

			PkgInfo.PackageSize = Data.Num ( );

			FMemoryWriter PkgWriter ( PkgData , false );

			FLFPStreamSocketPackageInfo::StaticStruct ( )->SerializeBin ( PkgWriter , &PkgInfo );
		}

		bool bSuccessfullySendData = true;

		if ( SocketData->IsListenServer ( ) )
		{
			for ( int32 LoopClientIndex = 0 ; LoopClientIndex < SocketData->ClientSocketList.Num ( ) ; LoopClientIndex++ )
			{
				FLFPStreamSocketPtrHandle& ClientSocket = SocketData->ClientSocketList[ LoopClientIndex ];

				if ( ClientSocket.GetID ( ) != ClientID && ClientID > 0 )
				{
					continue;
				}

				if ( ClientSocket.IsValid ( ) == false || ClientSocket.IsClosing ( ) )
				{
					UE_LOG ( LogTemp , Error , TEXT( "ULFPStreamSocketSubsystem : SendData Failed Client Socket Invalid Or Closing : %d : %d" ) , SocketID , LoopClientIndex );

					continue;
				}

				// Send PkgInfo
				if ( ClientSocket.Socket->Send ( PkgData.GetData ( ) , PkgData.Num ( ) , ClientSocket.LastBytesSendOrReceive ) == false )
				{
					UE_LOG ( LogTemp , Error , TEXT( "ULFPStreamSocketSubsystem : SendData Failed To Send PkgInfo : %d : %d" ) , SocketID , LoopClientIndex );

					bSuccessfullySendData = false;

					continue;
				}

				// Send Data
				if ( ClientSocket.Socket->Send ( Data.GetData ( ) , Data.Num ( ) , ClientSocket.LastBytesSendOrReceive ) == false )
				{
					bSuccessfullySendData = false;
				}
				else
				{
					ClientSocket.MarkActive ( SocketData->SocketSetting.TimeOutSecond );
				}
			}
		}
		else
		{
			if ( SocketData->MainSocket.IsValid ( ) == false || SocketData->MainSocket.IsClosing ( ) )
			{
				UE_LOG ( LogTemp , Error , TEXT( "ULFPStreamSocketSubsystem : SendData Failed MainSocket Invalid Or Closing : %d" ) , SocketID );

				bSuccessfullySendData = false;
			}
			else
			{
				// Send PkgInfo
				if ( SocketData->MainSocket.Socket->Send ( PkgData.GetData ( ) , PkgData.Num ( ) , SocketData->MainSocket.LastBytesSendOrReceive ) == false )
				{
					UE_LOG ( LogTemp , Error , TEXT( "ULFPStreamSocketSubsystem : SendData Failed To Send PkgInfo : %d " ) , SocketID );

					bSuccessfullySendData = false;
				}
				// Send Data
				else if ( SocketData->MainSocket.Socket->Send ( Data.GetData ( ) , Data.Num ( ) , SocketData->MainSocket.LastBytesSendOrReceive ) == false )
				{
					bSuccessfullySendData = false;
				}
				else
				{
					SocketData->MainSocket.MarkActive ( SocketData->SocketSetting.TimeOutSecond );
				}
			}
		}

		return bSuccessfullySendData;
	}
	UE_LOG ( LogTemp , Error , TEXT( "ULFPStreamSocketSubsystem : SendData Failed Socket Index Invalid : %d : %d" ) , SocketID , ClientID );

	return false;
}
