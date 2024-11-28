#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "IPAddressAsyncResolve.h"
#include "LFPStreamSocketSubsystem.generated.h"

UENUM( BlueprintType )
enum class ELFPStreamDIsconnectFlags : uint8
{
	LFP_StreamSocket_User			UMETA( DisplayName = "User" ) ,
	LFP_StreamSocket_NoConnection	UMETA( DisplayName = "NoConnection" ) ,
	LFP_StreamSocket_LoseConnection	UMETA( DisplayName = "LoseConnection" ) ,
};

USTRUCT( BlueprintType )
struct FLFPStreamSocketSetting
{
	GENERATED_BODY()

public:

	/** How many time to try reconnect. */
	UPROPERTY( BlueprintReadWrite , Category = "LFPTCPSocketSetting" )
	uint8 MaxReconnectAttempt = 15;

	/** Soceket listen amount, if -1 than switch to client mode. */
	UPROPERTY( BlueprintReadWrite , Category = "LFPTCPSocketSetting" )
	int32 MaxListenConnection = INDEX_NONE;

	UPROPERTY( BlueprintReadWrite , Category = "LFPTCPSocketSetting" )
	int32 BufferWriteSize = 0;

	UPROPERTY( BlueprintReadWrite , Category = "LFPTCPSocketSetting" )
	int32 BufferReadSize = 0;

	/** Holds the socket description. */
	UPROPERTY( BlueprintReadWrite , Category = "LFPTCPSocketSetting" )
	FString SocketDescription = FString( "" );

	/** Holds the server / client IP. */
	UPROPERTY( BlueprintReadWrite , Category = "LFPTCPSocketSetting" )
	FString IP = FString( "" );

	/** Holds the server / client port. */
	UPROPERTY( BlueprintReadWrite , Category = "LFPTCPSocketSetting" )
	int32 Port = 0;

	/** Holds a flag indicating if the bound address can be used by other sockets. */
	UPROPERTY( BlueprintReadWrite , Category = "LFPTCPSocketSetting" )
	bool bSocketReusable = true;

	UPROPERTY( BlueprintReadWrite , Category = "LFPTCPSocketSetting" )
	bool bKeppAlive = false;

	UPROPERTY( BlueprintReadWrite , Category = "LFPTCPSocketSetting" )
	float KeppAliveInterval = 10.0f;
};

USTRUCT()
struct FLFPStreamSocketData
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FLFPStreamSocketSetting SocketSetting = FLFPStreamSocketSetting();

public:

	UPROPERTY()
	uint32 SocketLookUpID = 0;

	UPROPERTY()
	uint8 CurrentReconnectAttempt = 0;

	UPROPERTY()
	float NextRunTime = 0;

	UPROPERTY()
	bool bInitilized = false;

	UPROPERTY()
	bool bClosing = false;

public:

	FSocket* MainSocket = nullptr;

	TArray<FSocket*> ClientSocket = TArray<FSocket*>();

public:

	FORCEINLINE bool IsListenServer() const
	{
		return SocketSetting.MaxListenConnection > 0;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FLFPStreamSocketEvent , const int32 , SocketID , const int32 , ClientID );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FLFPStreamSocketDisconnect , const int32 , SocketID , const int32 , ClientID , const ELFPStreamDIsconnectFlags , DIsconnectFlags );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FLFPStreamSocketMessage , const int32 , SocketID , const int32 , ClientID , const TArray<uint8>& , Bytes );

UCLASS()
class LOHFUNCTIONPLUGIN_API ULFPStreamSocketSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

protected:

	virtual void Initialize( FSubsystemCollectionBase& Collection ) override;

	virtual void Tick( float DeltaTime ) override;

	virtual void Deinitialize() override;

	virtual TStatId GetStatId() const override;

public:

	UPROPERTY( BlueprintAssignable , Category = "LFPStreamSocketSubsystem | Events" )
	FLFPStreamSocketEvent OnConnected;

	UPROPERTY( BlueprintAssignable , Category = "LFPStreamSocketSubsystem | Events" )
	FLFPStreamSocketEvent OnReconnecting;

	UPROPERTY( BlueprintAssignable , Category = "LFPStreamSocketSubsystem | Events" )
	FLFPStreamSocketDisconnect OnDisconnected;

	UPROPERTY( BlueprintAssignable , Category = "LFPStreamSocketSubsystem | Events" )
	FLFPStreamSocketMessage OnDataReceived;

protected:

	FORCEINLINE void TryInitializeSocket( FLFPStreamSocketData& SocketData , const TSharedRef<FInternetAddr>& Endpoint );

	FORCEINLINE void TryConnectClient( FLFPStreamSocketData& SocketData );

	FORCEINLINE void TryConnectServer( FLFPStreamSocketData& SocketData );

	FORCEINLINE void TryReceiveClientData( FLFPStreamSocketData& SocketData ) const;

	FORCEINLINE void TryReceiveServerData( FLFPStreamSocketData& SocketData ) const;

	FORCEINLINE void CheckSocketClientKeepAlive( FLFPStreamSocketData& SocketData );

	FORCEINLINE void CheckSocketServerKeepAlive( FLFPStreamSocketData& SocketData );

	FORCEINLINE void CloseSocket( FLFPStreamSocketData& SocketData , const int32 ClientID = -1 );

public:

	UFUNCTION( BlueprintPure , Category = "LFPStreamSocketSubsystem | Function" )
	bool IsSocketValid( const int32 SocketID , const int32 ClientID = -1 ) const;

public:

	UFUNCTION( BlueprintCallable , Category = "LFPStreamSocketSubsystem | Function" )
	int32 CreateSocket( const FLFPStreamSocketSetting& SocketSetting );

	UFUNCTION( BlueprintCallable , Category = "LFPStreamSocketSubsystem | Function" )
	bool DestroySocket( const int32 SocketID , const int32 ClientID = -1 );

	UFUNCTION( BlueprintCallable , Category = "LFPStreamSocketSubsystem | Function" )
	bool SendData( const TArray<uint8>& Data , const int32 SocketID , const int32 ClientID = -1 );

private:

	UPROPERTY()
	uint32 CurrentLookUpID = 0;

	UPROPERTY()
	TArray<FLFPStreamSocketData> SocketList = TArray<FLFPStreamSocketData>();

	ISocketSubsystem* SocketSubsystem = nullptr;
};

/**  */
class FLFPStreamSocketWorker : public FRunnable , public TSharedFromThis<FLFPStreamSocketWorker>
{
	//public:
	//
	//	FLFPStreamSocket( const int32 InID , ULFPTCPSocketComponent* NewComponent , const FLFPTCPSocketSetting& InSocketSetting )
	//		: SocketID( InID )
	//		, bStopping( false )
	//		, Component( NewComponent )
	//		, SocketSetting( InSocketSetting )
	//		, MainSocket( nullptr )
	//		, Thread( nullptr )
	//		, ConnectedSocketList( {} )
	//		, Endpoint( ISocketSubsystem::Get( PLATFORM_SOCKETSUBSYSTEM )->CreateInternetAddr() )
	//		, EndCode( ELFPTCPDIsconnectFlags::LFP_User )
	//	{
	//		Thread = FRunnableThread::Create( this , TEXT( "FLFPTcpSocket" ) , 8 * 1024 , TPri_Normal );
	//	}
	//
	//	~FLFPTcpSocket()
	//	{
	//		Component = nullptr;
	//
	//		if ( Thread != nullptr )
	//		{
	//			Thread->Kill( true );
	//			delete Thread;
	//		}
	//
	//		for ( auto& ClientSocket : ConnectedSocketList )
	//		{
	//			if ( ClientSocket == nullptr ) continue;
	//
	//			ClientSocket->Close();
	//			//ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ClientSocket);
	//			ClientSocket = nullptr;
	//		}
	//
	//		if ( MainSocket != nullptr )
	//		{
	//			MainSocket->Close();
	//			//ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(MainSocket);
	//			MainSocket = nullptr;
	//		}
	//	}
	//
	//public:
	//
	//	virtual bool Init() override;
	//
	//	virtual uint32 Run() override;
	//
	//	virtual void Stop() override;
	//
	//	virtual void Exit() override;
	//
	//public:
	//
	//	FORCEINLINE bool IsStopped() const;
	//
	//	FORCEINLINE TSharedPtr<FSocket> GetConnectedSocket( const int32 ID );
	//
	//	FORCEINLINE bool RequestDisconnectClient( const int32 ID );
	//
	//private:
	//
	//	FORCEINLINE bool IsSocketConnected( const TSharedPtr<FSocket>& InSocket ) const;
	//
	//	FORCEINLINE bool CloseSocket( const ELFPTCPDIsconnectFlags DIsconnectFlags , const int32 ClientID = -1 );
	//
	//private:
	//
	//	TQueue<int32 , EQueueMode::Spsc> DisconnectQueue;
	//
	//	/** For identify socket. */
	//	int32 SocketID = INDEX_NONE;
	//
	//	/** Is this socket closing. */
	//	FThreadSafeBool bStopping = false;
	//
	//	/** Component that create the socket. */
	//	TWeakObjectPtr<ULFPTCPSocketComponent> Component;
	//
	//	/** This contain all socket setting */
	//	FLFPTCPSocketSetting SocketSetting;
	//
	//	/** Holds the main socket. */
	//	TSharedPtr<FSocket , ESPMode::ThreadSafe> MainSocket;
	//
	//	/** Holds the thread object. */
	//	FRunnableThread* Thread;
	//
	//	/** Holds the connected socket. */
	//	TArray<TSharedPtr<FSocket , ESPMode::ThreadSafe>> ConnectedSocketList;
	//
	//	/** Holds the server endpoint. */
	//	TSharedRef<FInternetAddr> Endpoint;
	//
	//	ELFPTCPDIsconnectFlags EndCode = ELFPTCPDIsconnectFlags::LFP_User;
};

