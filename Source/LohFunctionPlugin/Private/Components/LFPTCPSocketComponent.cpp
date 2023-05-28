// Copyright by Loh Zhi Kang


#include "Components/LFPTCPSocketComponent.h"
#include "IPAddress.h"
#include "Async/Async.h"
#include "IPAddressAsyncResolve.h"

// Sets default values for this component's properties
ULFPTCPSocketComponent::ULFPTCPSocketComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULFPTCPSocketComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void ULFPTCPSocketComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for (auto& Socket : SocketList)
	{
		Socket->Stop();
	}

	SocketList.Empty();
}


// Called every frame
void ULFPTCPSocketComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}

void ULFPTCPSocketComponent::ResizeSocketList()
{
	while (SocketList.IsEmpty() == false && SocketList.Last()->IsStopped())
	{
		SocketList.RemoveAt(SocketList.Num() - 1, 1, false);
	}

	SocketList.Shrink();
}

int32 ULFPTCPSocketComponent::CreateSocket(FLFPTCPSocketSetting InSocketSetting)
{
	ResizeSocketList();

	if (InSocketSetting.MaxConnection < 0) InSocketSetting.MaxConnection = INDEX_NONE;

	if (InSocketSetting.TickInterval <= 0.0f) InSocketSetting.TickInterval = 0.0f;
	if (InSocketSetting.ReconnectTime < 1.0f) InSocketSetting.ReconnectTime = 1.0f;

	int32 SocketID = INDEX_NONE;

	for (SocketID = 0; SocketID < SocketList.Num(); SocketID++)
	{
		if (SocketList[SocketID]->IsStopped() == false) continue;

		break;
	}

	if (SocketID == INDEX_NONE) SocketID = SocketList.Num();

	TSharedRef<FLFPTcpSocket> NewServer(new FLFPTcpSocket(SocketID, this, InSocketSetting));

	if (SocketList.IsValidIndex(SocketID))
	{
		SocketList[SocketID] = NewServer;
	}
	else
	{
		SocketList.Add(NewServer);
	}

	return SocketID;
}

bool ULFPTCPSocketComponent::SendData(const TArray<uint8>& Data, const int32 SocketID, const int32 ClientID)
{
	if (SocketList.IsValidIndex(SocketID) == false) return false;

	/** Lock critical to prevent nullptr on run */
	FScopeLock Lock(&SocketList[SocketID]->GetCriticalSection());

	if (SocketList[SocketID]->GetConnectedSocket(ClientID) == nullptr) return false;

	int32 BtyeSended = 0;

	return SocketList[SocketID]->GetConnectedSocket(ClientID)->Send(Data.GetData(), Data.Num(), BtyeSended);
}

bool FLFPTcpSocket::Init()
{
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);

	if (SocketSubsystem == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("FLFPTcpSocket : %s : SocketSubsystem is nullptr"), *SocketSetting.MainDesc);

		return false;
	}

	auto ResolveInfo = SocketSubsystem->GetHostByName(TCHAR_TO_ANSI(*SocketSetting.IP));

	/** Wait for the ip to return */
	while (ResolveInfo->IsComplete() == false);

	if (ResolveInfo->GetErrorCode() != 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FLFPTcpSocket : %s : DNS resolve error code %d"), *SocketSetting.MainDesc, ResolveInfo->GetErrorCode());

		return false;
	}

	Endpoint->SetRawIp(ResolveInfo->GetResolvedAddress().GetRawIp());
	Endpoint->SetPort(SocketSetting.Port);

	if (MainSocket == nullptr)
	{
		if (SocketSetting.MaxConnection > 0)
		{
			MainSocket = FTcpSocketBuilder(SocketSetting.MainDesc)
				.AsReusable(SocketSetting.bSocketReusable)
				.BoundToEndpoint(FIPv4Endpoint(Endpoint))
				.Listening(SocketSetting.MaxConnection)
				.WithSendBufferSize(SocketSetting.BufferMaxSize)
				.WithReceiveBufferSize(SocketSetting.BufferMaxSize);

			ConnectedSocketList.Init(nullptr, SocketSetting.MaxConnection);

			if (Component.IsValid() && MainSocket != nullptr) Component->OnConnected.Broadcast(SocketID, INDEX_NONE);
		}
		else
		{
			MainSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, SocketSetting.MainDesc, false);

			//Set Send Buffer Size
			MainSocket->SetSendBufferSize(SocketSetting.BufferMaxSize, SocketSetting.BufferMaxSize);
			MainSocket->SetReceiveBufferSize(SocketSetting.BufferMaxSize, SocketSetting.BufferMaxSize);
		}
	}

	return (MainSocket != nullptr);
}

uint32 FLFPTcpSocket::Run()
{
	TSharedRef<FInternetAddr> RemoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	TWeakObjectPtr<ULFPTCPSocketComponent> LocalComponent = Component;

	const bool bIsServer = SocketSetting.MaxConnection > 0;

	TArray<uint8> ReconnectAttemptList;

	ReconnectAttemptList.Init(SocketSetting.ReconnectAttempt, FMath::Max(1, SocketSetting.MaxConnection));

	const int32 LocalSocketID = SocketID;

	while (IsStopped() == false)
	{
		if (bIsServer)
		{
			//Do we have clients trying to connect? connect them
			bool bHasPendingConnection;
			if (MainSocket->HasPendingConnection(bHasPendingConnection) && bHasPendingConnection)
			{
				TSharedPtr<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
				FSocket* Client = MainSocket->Accept(*Addr, SocketSetting.ConnectedDesc);

				int32 ClientID = INDEX_NONE;

				/** Find invalid or null socket */
				for (FSocket*& ClientSocket : ConnectedSocketList)
				{
					ClientID++;

					if (IsSocketConnected(ClientSocket)) continue;

					/** Close the socket if it is valid but not connected */
					CloseSocket(ELFPTCPDIsconnectFlags::LFP_LoseConnection, ClientID);

					ClientSocket = Client;

					Async(EAsyncExecution::TaskGraphMainThread, [LocalComponent, LocalSocketID, ClientID] {
						if (LocalComponent.IsValid()) LocalComponent->OnConnected.Broadcast(LocalSocketID, ClientID);
						});

					break;
				}
			}

			int32 ClientID = INDEX_NONE;

			//Check each endpoint for data
			for (FSocket*& ClientSocket : ConnectedSocketList)
			{
				ClientID++;

				/** Socket is not valid */
				if (ClientSocket == nullptr) continue;

				uint32 BufferSize = 0;

				/** Is data available ? */
				if (ClientSocket->HasPendingData(BufferSize))
				{
					TArray<uint8> ReceiveBuffer;

					ReceiveBuffer.SetNumUninitialized(BufferSize);

					int32 ReadBtyes = 0;
					ClientSocket->Recv(ReceiveBuffer.GetData(), ReceiveBuffer.Num(), ReadBtyes);

					const int32 LocalID = SocketID;

					//Pass the reference to be used on game thread
					AsyncTask(ENamedThreads::GameThread, [LocalComponent, LocalID, ClientID, ReceiveBuffer]()
						{
							if (LocalComponent.IsValid()) LocalComponent->OnDataReceived.Broadcast(LocalID, ClientID, ReceiveBuffer);
						});
				}

				/** Check Connection */
				if (IsSocketConnected(ClientSocket))
				{
					uint8 Dummy = 0;
					int32 ErrorCode = 0;

					ClientSocket->SetNonBlocking(true);

					if (ClientSocket->Recv(&Dummy, 1, ErrorCode, ESocketReceiveFlags::Peek) == false)
					{
						if (ReconnectAttemptList[ClientID] == 0)
						{
							CloseSocket(ELFPTCPDIsconnectFlags::LFP_LoseConnection, ClientID);
						}
						else
						{
							ReconnectAttemptList[ClientID]--;

							Async(EAsyncExecution::TaskGraphMainThread, [LocalComponent, LocalSocketID, ClientID] {
								if (LocalComponent.IsValid()) LocalComponent->OnReconnected.Broadcast(LocalSocketID, ClientID);
								});

							//reconnect attempt every 3 sec
							FPlatformProcess::Sleep(SocketSetting.ReconnectTime);
						}
					}
					else
					{
						ReconnectAttemptList[ClientID] = SocketSetting.ReconnectAttempt;
					}

					ClientSocket->SetNonBlocking(false);
				}
				else
				{
					CloseSocket(ELFPTCPDIsconnectFlags::LFP_LoseConnection, ClientID);
				}
			}
		}
		else
		{
			/** Check Connection */
			if (IsSocketConnected(MainSocket))
			{
				uint8 Dummy = 0;
				int32 ErrorCode = 0;

				MainSocket->SetNonBlocking(true);

				if (MainSocket->Recv(&Dummy, 1, ErrorCode, ESocketReceiveFlags::Peek) == false)
				{
					if (ReconnectAttemptList[0] == 0)
					{
						EndCode = ELFPTCPDIsconnectFlags::LFP_LoseConnection;

						return 2;
					}

					ReconnectAttemptList[0]--;

					Async(EAsyncExecution::TaskGraphMainThread, [LocalComponent, LocalSocketID] {
						if (LocalComponent.IsValid()) LocalComponent->OnReconnected.Broadcast(LocalSocketID, INDEX_NONE);
						});

					//reconnect attempt every 3 sec
					FPlatformProcess::Sleep(SocketSetting.ReconnectTime);
				}
				else
				{
					ReconnectAttemptList[0] = SocketSetting.ReconnectAttempt;
				}

				MainSocket->SetNonBlocking(false);
			}
			/** Try to connect if no connection */
			else
			{
				if (ReconnectAttemptList[0] == 0)
				{
					EndCode = ELFPTCPDIsconnectFlags::LFP_NoConnection;

					return 1;
				}

				ReconnectAttemptList[0]--;

				Async(EAsyncExecution::TaskGraphMainThread, [LocalComponent, LocalSocketID] {
					if (LocalComponent.IsValid()) LocalComponent->OnReconnected.Broadcast(LocalSocketID, INDEX_NONE);
					});

				if (MainSocket->Connect(*Endpoint))
				{
					Async(EAsyncExecution::TaskGraphMainThread, [LocalComponent, LocalSocketID] {
						if (LocalComponent.IsValid()) LocalComponent->OnConnected.Broadcast(LocalSocketID, INDEX_NONE);
						});

					ReconnectAttemptList[0] = SocketSetting.ReconnectAttempt;

					continue;
				}

				//reconnect attempt every 3 sec
				FPlatformProcess::Sleep(SocketSetting.ReconnectTime);

				continue;
			}

			uint32 BufferSize = 0;

			/** Do we have any data incoming, if true than receive data */
			if (MainSocket->HasPendingData(BufferSize))
			{
				TArray<uint8> ReceiveBuffer;

				ReceiveBuffer.SetNumUninitialized(BufferSize);

				int32 ReadBtyes = 0;
				MainSocket->Recv(ReceiveBuffer.GetData(), ReceiveBuffer.Num(), ReadBtyes);

				const int32 LocalID = SocketID;

				//Pass the reference to be used on game thread
				AsyncTask(ENamedThreads::GameThread, [LocalComponent, LocalID, ReceiveBuffer]()
					{
						if (LocalComponent.IsValid()) LocalComponent->OnDataReceived.Broadcast(LocalID, INDEX_NONE, ReceiveBuffer);
					});
			}
		}

		//sleep until there is data
		MainSocket->Wait(ESocketWaitConditions::WaitForReadOrWrite, FTimespan(SocketSetting.TickInterval * 1000.0f));
	}

	EndCode = ELFPTCPDIsconnectFlags::LFP_User;

	return 0;
}

void FLFPTcpSocket::Stop()
{
	bStopping = true;
}

void FLFPTcpSocket::Exit()
{
	CloseSocket(EndCode);

	for (int32 LocalCLientID = 0; LocalCLientID < ConnectedSocketList.Num(); LocalCLientID++)
	{
		CloseSocket(EndCode, LocalCLientID);
	}

	ConnectedSocketList.Empty();

	bStopping = true;
}

bool FLFPTcpSocket::IsStopped() const
{
	return bStopping;
}

FSocket* FLFPTcpSocket::GetConnectedSocket(const int32 ID)
{
	if (ID == INDEX_NONE) return MainSocket;

	if (ConnectedSocketList.IsValidIndex(ID) == false) return nullptr;

	return ConnectedSocketList[ID];
}

FCriticalSection& FLFPTcpSocket::GetCriticalSection()
{
	return CriticalSection;
}

bool FLFPTcpSocket::IsSocketConnected(FSocket* InSocket) const
{
	return (InSocket != nullptr && (InSocket->GetConnectionState() == ESocketConnectionState::SCS_Connected));
}

bool FLFPTcpSocket::CloseSocket(const ELFPTCPDIsconnectFlags DIsconnectFlags, const int32 ClientID)
{
	/** Lock critical for socket clean up */
	FScopeLock Lock(&CriticalSection);

	bool bResult = false;

	TWeakObjectPtr<ULFPTCPSocketComponent> LocalComponent = Component;
	auto LocalSetting = SocketSetting;
	const int32 LocalSocketID = SocketID;

	if (ClientID == INDEX_NONE && MainSocket != nullptr)
	{
		bResult = MainSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(MainSocket);
		MainSocket = nullptr;
	}
	else if (IsSocketConnected(MainSocket) && ConnectedSocketList.IsValidIndex(ClientID) && ConnectedSocketList[ClientID] != nullptr)
	{
		bResult = ConnectedSocketList[ClientID]->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ConnectedSocketList[ClientID]);
		ConnectedSocketList[ClientID] = nullptr;
	}

	if (bResult)
	{
		Async(EAsyncExecution::TaskGraphMainThread, [LocalComponent, DIsconnectFlags, LocalSetting, LocalSocketID, ClientID] {
			if (LocalComponent.IsValid()) LocalComponent->OnDisconnected.Broadcast(DIsconnectFlags, LocalSetting, LocalSocketID, ClientID);
			});
	}

	return bResult;
}
