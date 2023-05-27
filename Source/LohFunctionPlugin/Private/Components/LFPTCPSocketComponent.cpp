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

	InvalidSocketList.Heapify();

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

int32 ULFPTCPSocketComponent::AddTcpServerList(const int32 MaxConnection, const FString IPAddress, const int32 Port, const float TickInterval)
{
	//bool bIsValid = false;
	//
	//TSharedRef<FInternetAddr> RemoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	//RemoteAddress->SetIp(*IPAddress, bIsValid);
	//RemoteAddress->SetPort(Port);
	//
	//if (bIsValid == false) return INDEX_NONE;
	//
	//
	//TSharedRef<FLFPTcpSocket> NewServer(new FLFPTcpSocket(this, MaxConnection, FIPv4Endpoint(RemoteAddress), TickInterval, true));
	//
	//int32 TargetIndex = INDEX_NONE;
	//
	//if (InvalidTcpServerList.IsEmpty() == false)
	//{
	//	InvalidTcpServerList.HeapPop(TargetIndex);
	//
	//	TcpServerList[TargetIndex] = NewServer;
	//}
	//else
	//{
	//	TargetIndex = TcpServerList.Add(NewServer);
	//}

	//return TargetIndex;

	return 0;
}

void ULFPTCPSocketComponent::ConnectToServer(FLFPTCPSocketSetting InSocketSetting)
{
	/** Connect to server don't need other socket to connect to here */
	InSocketSetting.MaxConnection = INDEX_NONE;

	if (InSocketSetting.TickInterval <= 0.0f) InSocketSetting.TickInterval = 0.0f;
	if (InSocketSetting.ReconnectTime < 1.0f) InSocketSetting.ReconnectTime = 1.0f;

	TSharedRef<FLFPTcpSocket> NewServer(new FLFPTcpSocket(this, InSocketSetting));

	int32 TargetIndex = INDEX_NONE;
	
	if (InvalidSocketList.IsEmpty() == false)
	{
		InvalidSocketList.HeapPop(TargetIndex);
	
		SocketList[TargetIndex] = NewServer;
	}
	else
	{
		TargetIndex = SocketList.Add(NewServer);
	}
}

bool FLFPTcpSocket::Init()
{
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);

	if (SocketSubsystem == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("FLFPTcpSocket : SocketSubsystem is nullptr"));

		return false;
	}

	auto ResolveInfo = SocketSubsystem->GetHostByName(TCHAR_TO_ANSI(*SocketSetting.IP));

	/** Wait for the ip to return */
	while (ResolveInfo->IsComplete() == false);

	if (ResolveInfo->GetErrorCode() != 0)
	{
		UE_LOG(LogTemp, Error, TEXT("FLFPTcpSocket : DNS resolve error code %d"), ResolveInfo->GetErrorCode());

		return false;
	}

	Endpoint->SetRawIp(ResolveInfo->GetResolvedAddress().GetRawIp());
	Endpoint->SetPort(SocketSetting.Port);

	if (MainSocket == nullptr)
	{
		if (SocketSetting.MaxConnection > 0)
		{
			MainSocket = FTcpSocketBuilder(SocketSetting.Desc)
				.AsReusable(SocketSetting.bSocketReusable)
				.BoundToEndpoint(FIPv4Endpoint(Endpoint))
				.Listening(8)
				.WithSendBufferSize(SocketSetting.BufferMaxSize)
				.WithReceiveBufferSize(SocketSetting.BufferMaxSize);
		}
		else
		{
			MainSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, SocketSetting.Desc, false);

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

	uint8 ReconnectAttempt = SocketSetting.ReconnectAttempt;

	while (bStopping == false)
	{
		if (bIsServer)
		{

		}
		else
		{
			/** Try to connect if no connection */
			if (IsSocketConnected(MainSocket) == false)
			{
				if (ReconnectAttempt == 0)
				{
					EndCode = ELFPTCPDIsconnectFlags::LFP_NoConnection;

					return 1;
				}

				ReconnectAttempt--;

				Async(EAsyncExecution::TaskGraphMainThread, [LocalComponent] {
					if (LocalComponent.IsValid()) LocalComponent->OnReconnected.Broadcast();
					});

				if (MainSocket->Connect(*Endpoint))
				{
					Async(EAsyncExecution::TaskGraphMainThread, [LocalComponent] {
						if (LocalComponent.IsValid()) LocalComponent->OnConnected.Broadcast();
						});

					ReconnectAttempt = SocketSetting.ReconnectAttempt;

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

				TSharedRef<FInternetAddr> LocalEndpoint = Endpoint;

				//Pass the reference to be used on game thread
				AsyncTask(ENamedThreads::GameThread, [LocalComponent, LocalEndpoint, ReceiveBuffer]()
					{
						if (LocalComponent.IsValid()) LocalComponent->OnDataReceived.Broadcast(LocalEndpoint->GetRawIp(), LocalEndpoint->GetPort(), ReceiveBuffer);
					});
			}

			//sleep until there is data
			MainSocket->Wait(ESocketWaitConditions::WaitForReadOrWrite, FTimespan(SocketSetting.TickInterval * 1000.0f));

			/** Check Connection */
			{
				uint8 Dummy = 0;
				int32 ErrorCode = 0;

				MainSocket->SetNonBlocking(true);

				if (MainSocket->Recv(&Dummy, 1, ErrorCode, ESocketReceiveFlags::Peek) == false)
				{
					if (ReconnectAttempt == 0)
					{
						EndCode = ELFPTCPDIsconnectFlags::LFP_LoseConnection;

						return 2;
					}

					ReconnectAttempt--;

					Async(EAsyncExecution::TaskGraphMainThread, [LocalComponent] {
						if (LocalComponent.IsValid()) LocalComponent->OnReconnected.Broadcast();
						});

					//reconnect attempt every 3 sec
					FPlatformProcess::Sleep(SocketSetting.ReconnectTime);
				}
				else
				{
					ReconnectAttempt = SocketSetting.ReconnectAttempt;
				}

				MainSocket->SetNonBlocking(false);
			}
		}
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
	TWeakObjectPtr<ULFPTCPSocketComponent> LocalComponent = Component;
	auto LocalEndCode = EndCode;
	auto LocalSetting = SocketSetting;

	Async(EAsyncExecution::TaskGraphMainThread, [LocalComponent, LocalEndCode, LocalSetting] {
		if (LocalComponent.IsValid()) LocalComponent->OnDisconnected.Broadcast(LocalEndCode, LocalSetting);
		});

	if (MainSocket != nullptr)
	{
		MainSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(MainSocket);
		MainSocket = nullptr;
	}

	for (FSocket*& ClientSocket : ConnectedSocketList)
	{
		ClientSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ClientSocket);
		ClientSocket = nullptr;
	}

	ConnectedSocketList.Empty();
}

bool FLFPTcpSocket::IsSocketConnected(FSocket* InSocket) const
{
	return (InSocket && (InSocket->GetConnectionState() == ESocketConnectionState::SCS_Connected));
}
