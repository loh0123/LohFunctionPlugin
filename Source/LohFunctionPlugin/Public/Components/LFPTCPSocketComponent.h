// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "SocketSubsystem.h"
#include "Common/TcpSocketBuilder.h"
#include "Components/ActorComponent.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "LFPTCPSocketComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTcpConnectionAccepted, const TArray<uint8>&, IPAddress);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTcpDataReceive, const TArray<uint8>&, Data);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPTCPSocketComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPTCPSocketComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public: /** Delegate */

	UPROPERTY(BlueprintAssignable, Category = "LFPTCPSocketComponent | Delegate")
		FOnTcpConnectionAccepted OnTcpConnectionAccepted;

	UPROPERTY(BlueprintAssignable, Category = "LFPTCPSocketComponent | Delegate")
		FOnTcpDataReceive OnTcpDataReceive;
};

/**  */
class FLFPSocketListener : public FRunnable
{
	FLFPSocketListener(ULFPTCPSocketComponent* NewComponent, int32 NewMaxConnection, const FIPv4Endpoint& LocalEndpoint, const FTimespan& InSleepTime = FTimespan::FromSeconds(1), bool bInReusable = true)
		: Component(NewComponent)
		, MaxConnection(NewMaxConnection)
		, Endpoint(LocalEndpoint)
		, SleepTime(InSleepTime)
		, Socket(nullptr)
		, bStopping(false)
		, bSocketReusable(bInReusable)
	{
		Thread = FRunnableThread::Create(this, TEXT("FLFPSocketListener"), 8 * 1024, TPri_Normal);
	}

	~FLFPSocketListener()
	{
		Component = nullptr;

		if (Thread != nullptr)
		{
			Thread->Kill(true);
			delete Thread;
		}

		if (Socket != nullptr)
		{
			ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
			Socket = nullptr;
		}
	}

public:

	const FIPv4Endpoint& GetLocalEndpoint() const
	{
		return Endpoint;
	}

	FSocket* GetSocket() const
	{
		return Socket;
	}

	bool IsActive() const
	{
		return ((Socket != nullptr) && !bStopping);
	}

public:

	virtual bool Init() override
	{
		if (Socket == nullptr)
		{
			Socket = FTcpSocketBuilder(TEXT("FLFPSocketListener server"))
				.AsReusable(bSocketReusable)
				.BoundToEndpoint(Endpoint)
				.Listening(MaxConnection)
				.WithSendBufferSize(2 * 1024 * 1024);
		}

		return (Socket != nullptr);
	}

	virtual uint32 Run() override
	{
		TSharedRef<FInternetAddr> RemoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

		const bool bHasZeroSleepTime = (SleepTime == FTimespan::Zero());

		while (!bStopping)
		{
			auto TargetComp = Component;

			bool Pending = false;

			if (Socket->HasPendingConnection(Pending) && Pending)
			{
				Socket->Accept(*RemoteAddress, TEXT("FLFPSocketListener client accepted"));

				AsyncTask(ENamedThreads::GameThread, [TargetComp, RemoteAddress]() {
					TargetComp->OnTcpConnectionAccepted.Broadcast(RemoteAddress.Get().GetRawIp());
				});
			}
			else
			{
				if (IsValid(Component) && IsValid(Component->GetOwner())) UE_LOG(LogTemp, Log, TEXT("TCP connection failed : %s"), *Component->GetOwner()->GetName());

				break;
			}

			uint32 PendingDataSize = 0;

			if (Socket->HasPendingData(PendingDataSize) && PendingDataSize != 0)
			{
				TArray<uint8> RecData;

				int32 BytesRead = 0;

				RecData.SetNumUninitialized(PendingDataSize);

				if (Socket->Recv(RecData.GetData(), PendingDataSize, BytesRead))
				{
					AsyncTask(ENamedThreads::GameThread, [TargetComp, RecData]() {
						TargetComp->OnTcpDataReceive.Broadcast(RecData);
						});
				}
				else
				{
					if (IsValid(Component) && IsValid(Component->GetOwner())) UE_LOG(LogTemp, Log, TEXT("TCP data read failed : %s : PendingDataSize = %d : BytesRead = %d"), *Component->GetOwner()->GetName(), PendingDataSize, BytesRead);

					break;
				}
			}

			FPlatformProcess::Sleep(SleepTime.GetSeconds());
		}

		return 0;
	}

	virtual void Stop() override
	{
		bStopping = true;
	}

	virtual void Exit() override { }

private:

	TObjectPtr<ULFPTCPSocketComponent> Component;

	int32 MaxConnection = 8;

	/** Holds the server endpoint. */
	FIPv4Endpoint Endpoint;

	/** Holds the time to sleep between checking for pending connections. */
	FTimespan SleepTime;

	/** Holds the server socket. */
	FSocket* Socket;

	/** Holds a flag indicating that the thread is stopping. */
	bool bStopping;

	/** Holds a flag indicating if the bound address can be used by other sockets. */
	bool bSocketReusable;

	/** Holds the thread object. */
	FRunnableThread* Thread;
};
