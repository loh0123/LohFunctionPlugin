#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "IPAddressAsyncResolve.h"
#include "LFPStreamSocketSubsystem.generated.h"

UENUM( BlueprintType )
enum class ELFPStreamDIsconnectFlags : uint8
{
	LFP_User			UMETA( DisplayName = "User" ) ,
	LFP_NoConnection	UMETA( DisplayName = "NoConnection" ) ,
	LFP_LoseConnection	UMETA( DisplayName = "LoseConnection" ) ,
};

UENUM( BlueprintType )
enum class ELFPStreamSocketState : uint8
{
	LFP_Idel			UMETA( DisplayName = "Idel" ) ,
	LFP_IncomingPkg		UMETA( DisplayName = "Incoming Package" ) ,
	LFP_Closing			UMETA( DisplayName = "Closing" ) ,
};

USTRUCT( BlueprintType )
struct FLFPStreamSocketPackageInfo
{
	GENERATED_BODY()

public:

	UPROPERTY()
	uint32 PackageSize = 0;
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
	bool bNoDelay = false;

	UPROPERTY( BlueprintReadWrite , Category = "LFPTCPSocketSetting" )
	float TimeOutSecond = 3.0f;

	UPROPERTY( BlueprintReadWrite , Category = "LFPTCPSocketSetting" )
	float PingInterval = 1.0f;
};

USTRUCT()
struct FLFPStreamSocketPtrHandle
{
	GENERATED_BODY()

public:

	FLFPStreamSocketPtrHandle() : SocketLookUpID( GlobalID++ )
	{
	}

	FLFPStreamSocketPtrHandle( FSocket* NewSocket ) : Socket( NewSocket ) , SocketLookUpID( GlobalID++ )
	{
		MarkActive();
	}

private:

	static uint32 GlobalID;

public:

	FSocket* Socket = nullptr;

	ELFPStreamSocketState State = ELFPStreamSocketState::LFP_Idel;

public:

	UPROPERTY()
	FLFPStreamSocketPackageInfo CurrentPackageInfo = FLFPStreamSocketPackageInfo();

	UPROPERTY()
	uint8 CurrentPingFailedAttempt = 0;

	UPROPERTY()
	float ActiveDelayTime = 0;

	UPROPERTY()
	float LastActiveTime = 0;

	UPROPERTY()
	int32 LastBtyeSendOrReceive = 0;

	UPROPERTY()
	uint32 SocketLookUpID = 0;

public:

	static uint32 GetNextID()
	{
		return GlobalID;
	}

public:

	FORCEINLINE bool IsValid() const
	{
		return Socket != nullptr;
	}

	FORCEINLINE bool IsClosing() const
	{
		return State == ELFPStreamSocketState::LFP_Closing;
	}

	FORCEINLINE bool IsIncomingPackage() const
	{
		return State == ELFPStreamSocketState::LFP_IncomingPkg;
	}

	FORCEINLINE void MarkActive( const float Delay = 3.0f )
	{
		ActiveDelayTime = Delay;

		LastActiveTime = FPlatformTime::Seconds();
	}

	FORCEINLINE bool IsActive() const
	{
		return FPlatformTime::Seconds() - LastActiveTime < ActiveDelayTime;
	}

	FORCEINLINE uint32 GetID() const
	{
		return SocketLookUpID;
	}
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
	bool bInitilized = false;

public:

	UPROPERTY()
	FLFPStreamSocketPtrHandle MainSocket = FLFPStreamSocketPtrHandle();

	UPROPERTY()
	TArray<FLFPStreamSocketPtrHandle> ClientSocket = TArray<FLFPStreamSocketPtrHandle>();

public:

	FORCEINLINE bool IsListenServer() const
	{
		return SocketSetting.MaxListenConnection > 0;
	}

	FORCEINLINE FLFPStreamSocketPtrHandle* GetClientSocketPtr( const int32 ClientID )
	{
		return ClientSocket.FindByPredicate( [&] ( const FLFPStreamSocketPtrHandle& SocketPtrData )
											 {
												 return SocketPtrData.GetID() == ClientID;
											 }
		);
	}

	FORCEINLINE const FLFPStreamSocketPtrHandle* GetClientSocketPtr( const int32 ClientID ) const
	{
		return ClientSocket.FindByPredicate( [&] ( const FLFPStreamSocketPtrHandle& SocketPtrData )
											 {
												 return SocketPtrData.GetID() == ClientID;
											 }
		);
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

	FORCEINLINE FLFPStreamSocketData* GetSocketData( const int32 SocketID );

	FORCEINLINE const FLFPStreamSocketData* GetSocketData( const int32 SocketID ) const;

	FORCEINLINE FLFPStreamSocketPtrHandle* GetSocketPtr( const int32 SocketID , const int32 ClientID = -1 );

	FORCEINLINE const FLFPStreamSocketPtrHandle* GetSocketPtr( const int32 SocketID , const int32 ClientID = -1 ) const;

protected:

	FORCEINLINE void TryInitializeSocket( FLFPStreamSocketData& SocketData , const TSharedRef<FInternetAddr>& Endpoint );

	FORCEINLINE void TryConnectClient( FLFPStreamSocketData& SocketData );

	FORCEINLINE void TryReceiveClientData( FLFPStreamSocketData& SocketData ) const;

	FORCEINLINE void TryReceiveServerData( FLFPStreamSocketData& SocketData ) const;

	FORCEINLINE void PingSocketClient( FLFPStreamSocketData& SocketData ) const;

	FORCEINLINE void PingSocketServer( FLFPStreamSocketData& SocketData ) const;

	FORCEINLINE void CleanUpSocket( FLFPStreamSocketData& SocketData , const bool bForce = false );

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
	TArray<FLFPStreamSocketData> SocketList = TArray<FLFPStreamSocketData>();

	ISocketSubsystem* SocketSubsystem = nullptr;
};

