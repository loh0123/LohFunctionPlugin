// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "SocketSubsystem.h"
#include "Common/TcpSocketBuilder.h"
#include "Components/ActorComponent.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "LFPTCPSocketComponent.generated.h"


UENUM(BlueprintType)
enum class ELFPTCPDIsconnectFlags : uint8
{
	LFP_User			UMETA(DisplayName = "User"),
	LFP_NoConnection	UMETA(DisplayName = "NoConnection"),
	LFP_LoseConnection	UMETA(DisplayName = "LoseConnection"),
};

USTRUCT(BlueprintType)
struct FLFPTCPSocketSetting
{
	GENERATED_BODY()

public:

	/** How many time to try reconnect. */
	UPROPERTY(BlueprintReadWrite, Category = "LFPTCPSocketSetting")
		uint8 ReconnectAttempt = 15;

	/** Soceket listen amount, if -1 than switch to client mode. */
	UPROPERTY(BlueprintReadWrite, Category = "LFPTCPSocketSetting")
		int32 MaxConnection = INDEX_NONE;

	/** Soceket read and write buffer size. */
	UPROPERTY(BlueprintReadWrite, Category = "LFPTCPSocketSetting")
		int32 BufferMaxSize = 2 * 1024 * 1024;

	/** Holds the server / client IP. */
	UPROPERTY(BlueprintReadWrite, Category = "LFPTCPSocketSetting")
		FString Desc;

	/** Holds the server / client IP. */
	UPROPERTY(BlueprintReadWrite, Category = "LFPTCPSocketSetting")
		FString IP;

	/** Holds the server / client port. */
	UPROPERTY(BlueprintReadWrite, Category = "LFPTCPSocketSetting")
		int32 Port;

	/** How much time before trying to reconnect. */
	UPROPERTY(BlueprintReadWrite, Category = "LFPTCPSocketSetting")
		float ReconnectTime = 3.0f;

	/** Holds the time to sleep between checking for pending connections. */
	UPROPERTY(BlueprintReadWrite, Category = "LFPTCPSocketSetting")
		float TickInterval = 0.01f;

	/** Holds a flag indicating if the bound address can be used by other sockets. */
	UPROPERTY(BlueprintReadWrite, Category = "LFPTCPSocketSetting")
		bool bSocketReusable;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLFPTCPSocketEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLFPTCPSocketDIsconnect, const ELFPTCPDIsconnectFlags, DIsconnectFlags, const FLFPTCPSocketSetting, SocketSetting);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FLFPTCPSocketMessage, const TArray<uint8>&, FromIP, const int32, FromPort, const TArray<uint8>&, Bytes);

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTcpConnectionAccepted, const TArray<uint8>&, IPAddress);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTcpDataReceive, const TArray<uint8>&, Data);

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

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UFUNCTION(BlueprintCallable, Category = "LFPTCPSocketComponent | Function")
		int32 AddTcpServerList(const int32 MaxConnection, const FString IPAddress, const int32 Port, const float TickInterval);

	UFUNCTION(BlueprintCallable, Category = "LFPTCPSocketComponent | Function")
		void ConnectToServer(FLFPTCPSocketSetting InSocketSetting);

public:

	UPROPERTY(BlueprintAssignable, Category = "LFPTCPSocketComponent | Events")
		FLFPTCPSocketEvent OnConnected;

	UPROPERTY(BlueprintAssignable, Category = "LFPTCPSocketComponent | Events")
		FLFPTCPSocketEvent OnReconnected;

	UPROPERTY(BlueprintAssignable, Category = "LFPTCPSocketComponent | Events")
		FLFPTCPSocketDIsconnect OnDisconnected;

	UPROPERTY(BlueprintAssignable, Category = "LFPTCPSocketComponent | Events")
		FLFPTCPSocketMessage OnDataReceived;

private:

	TArray<TSharedRef<class FLFPTcpSocket>> SocketList;

	TArray<int32> InvalidSocketList;
};

/**  */
class FLFPTcpSocket : public FRunnable, public TSharedFromThis<FLFPTcpSocket>
{
public:

	FLFPTcpSocket(ULFPTCPSocketComponent* NewComponent, const FLFPTCPSocketSetting& InSocketSetting)
		: bStopping(false)
		, Component(NewComponent)
		, SocketSetting(InSocketSetting)
		, MainSocket(nullptr)
		, Thread(nullptr)
		, ConnectedSocketList({})
		, Endpoint(ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr())
		, EndCode(ELFPTCPDIsconnectFlags::LFP_User)
	{
		Thread = FRunnableThread::Create(this, TEXT("FLFPTcpSocket"), 8 * 1024, TPri_Normal);
	}

	~FLFPTcpSocket()
	{
		Component = nullptr;

		if (Thread != nullptr)
		{
			Thread->Kill(true);
			delete Thread;
		}

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
	}

public:

	virtual bool Init() override;

	virtual uint32 Run() override;

	virtual void Stop() override;

	virtual void Exit() override;

	FORCEINLINE bool IsSocketConnected(FSocket* InSocket) const;

private:

	/** Is this socket closing. */
	bool bStopping = false;

	/** Component that create the socket. */
	TWeakObjectPtr<ULFPTCPSocketComponent> Component;

	/** This contain all socket setting */
	FLFPTCPSocketSetting SocketSetting;

	/** Holds the main socket. */
	FSocket* MainSocket;

	/** Holds the thread object. */
	FRunnableThread* Thread;

	/** Holds the connected socket. */
	TArray<FSocket*> ConnectedSocketList;

	/** Holds the server endpoint. */
	TSharedRef<FInternetAddr> Endpoint;

	ELFPTCPDIsconnectFlags EndCode = ELFPTCPDIsconnectFlags::LFP_User;
};
