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
		uint8 MaxReconnectAttempt = 15;

	/** Soceket listen amount, if -1 than switch to client mode. */
	UPROPERTY(BlueprintReadWrite, Category = "LFPTCPSocketSetting")
		int32 MaxConnection = INDEX_NONE;

	/** Soceket read and write buffer size. */
	UPROPERTY(BlueprintReadWrite, Category = "LFPTCPSocketSetting")
		int32 BufferMaxSize = 2 * 1024 * 1024;

	/** Holds the main socket description. */
	UPROPERTY(BlueprintReadWrite, Category = "LFPTCPSocketSetting")
		FString ServerDescription = FString("");

	/** Holds the connected socket description. */
	UPROPERTY(BlueprintReadWrite, Category = "LFPTCPSocketSetting")
		FString ClientDescription = FString("");

	/** Holds the server / client IP. */
	UPROPERTY(BlueprintReadWrite, Category = "LFPTCPSocketSetting")
		FString IP = FString("");

	/** Holds the server / client port. */
	UPROPERTY(BlueprintReadWrite, Category = "LFPTCPSocketSetting")
		int32 Port = 0;

	/** How much time before trying to reconnect. */
	UPROPERTY(BlueprintReadWrite, Category = "LFPTCPSocketSetting")
		float ReconnectTime = 3.0f;

	/** Holds the time to sleep between checking for pending connections. */
	UPROPERTY(BlueprintReadWrite, Category = "LFPTCPSocketSetting")
		float TickInterval = 0.01f;

	/** Holds a flag indicating if the bound address can be used by other sockets. */
	UPROPERTY(BlueprintReadWrite, Category = "LFPTCPSocketSetting")
		bool bSocketReusable = true;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLFPTCPSocketEvent, const int32, SocketID, const int32, ClientID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FLFPTCPSocketDisconnect, const ELFPTCPDIsconnectFlags, DIsconnectFlags, const FLFPTCPSocketSetting, SocketSetting, const int32, SocketID, const int32, ClientID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FLFPTCPSocketMessage, const int32, SocketID, const int32, ClientID, const TArray<uint8>&, Bytes);

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

	UFUNCTION(BlueprintPure, Category = "LFPTCPSocketComponent | Function")
		bool IsSocketValid(const int32 SocketID, const int32 ClientID = -1) const;

public:

	UFUNCTION(BlueprintCallable, Category = "LFPTCPSocketComponent | Function")
		void ResizeSocketList();

	UFUNCTION(BlueprintCallable, Category = "LFPTCPSocketComponent | Function")
		int32 CreateSocket(FLFPTCPSocketSetting InSocketSetting);

	UFUNCTION(BlueprintCallable, Category = "LFPTCPSocketComponent | Function")
		bool DestroySocket(const int32 SocketID, const int32 ClientID = -1);

	UFUNCTION(BlueprintCallable, Category = "LFPTCPSocketComponent | Function")
		bool SendData(const TArray<uint8>& Data, const int32 SocketID, const int32 ClientID = -1);

public:

	UPROPERTY(BlueprintAssignable, Category = "LFPTCPSocketComponent | Events")
		FLFPTCPSocketEvent OnConnected;

	UPROPERTY(BlueprintAssignable, Category = "LFPTCPSocketComponent | Events")
		FLFPTCPSocketEvent OnReconnected;

	UPROPERTY(BlueprintAssignable, Category = "LFPTCPSocketComponent | Events")
		FLFPTCPSocketDisconnect OnDisconnected;

	UPROPERTY(BlueprintAssignable, Category = "LFPTCPSocketComponent | Events")
		FLFPTCPSocketMessage OnDataReceived;

private:

	TArray<TSharedRef<class FLFPTcpSocket>> SocketList;
};

/**  */
class FLFPTcpSocket : public FRunnable, public TSharedFromThis<FLFPTcpSocket>
{
public:

	FLFPTcpSocket(const int32 InID, ULFPTCPSocketComponent* NewComponent, const FLFPTCPSocketSetting& InSocketSetting)
		: SocketID(InID)
		, bStopping(false)
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

		for (auto& ClientSocket : ConnectedSocketList)
		{
			if (ClientSocket == nullptr) continue;

			ClientSocket->Close();
			//ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ClientSocket);
			ClientSocket = nullptr;
		}

		if (MainSocket != nullptr)
		{
			MainSocket->Close();
			//ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(MainSocket);
			MainSocket = nullptr;
		}
	}

public:

	virtual bool Init() override;

	virtual uint32 Run() override;

	virtual void Stop() override;

	virtual void Exit() override;

public:

	FORCEINLINE bool IsStopped() const;

	FORCEINLINE TSharedPtr<FSocket> GetConnectedSocket(const int32 ID);

	FORCEINLINE bool RequestDisconnectClient(const int32 ID);

private:

	FORCEINLINE bool IsSocketConnected(const TSharedPtr<FSocket>& InSocket) const;

	FORCEINLINE bool CloseSocket(const ELFPTCPDIsconnectFlags DIsconnectFlags, const int32 ClientID = -1);

private:

	TQueue<int32, EQueueMode::Spsc> DisconnectQueue;

	/** For identify socket. */
	int32 SocketID = INDEX_NONE;

	/** Is this socket closing. */
	std::atomic<bool> bStopping = false;

	/** Component that create the socket. */
	TWeakObjectPtr<ULFPTCPSocketComponent> Component;

	/** This contain all socket setting */
	FLFPTCPSocketSetting SocketSetting;

	/** Holds the main socket. */
	TSharedPtr<FSocket, ESPMode::ThreadSafe> MainSocket;

	/** Holds the thread object. */
	FRunnableThread* Thread;

	/** Holds the connected socket. */
	TArray<TSharedPtr<FSocket, ESPMode::ThreadSafe>> ConnectedSocketList;

	/** Holds the server endpoint. */
	TSharedRef<FInternetAddr> Endpoint;

	ELFPTCPDIsconnectFlags EndCode = ELFPTCPDIsconnectFlags::LFP_User;
};
