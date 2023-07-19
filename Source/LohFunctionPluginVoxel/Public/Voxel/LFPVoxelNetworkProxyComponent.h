// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LFPVoxelNetworkProxyComponent.generated.h"

class ULFPGridContainerComponent;
class ULFPTCPSocketComponent;


USTRUCT(BlueprintType)
struct FLFPVoxelNetworkProxySendInfo
{
	GENERATED_BODY()

public:

	UPROPERTY() TSet<FIntPoint> ChuckList = TSet<FIntPoint>();
};

USTRUCT(BlueprintType)
struct FLFPVoxelNetworkProxyReceiveInfo
{
	GENERATED_BODY()

public:

	UPROPERTY() TArray<uint8> Data = TArray<uint8>();

	UPROPERTY() int32 DataSendAmount = 0;

	UPROPERTY() int32 DataSize = INDEX_NONE;

public:

	FORCEINLINE bool HasDataInfo() const
	{
		return DataSize != INDEX_NONE;
	}

	FORCEINLINE bool IsDataComplete() const
	{
		return HasDataInfo() && DataSize <= Data.Num();
	}

	FORCEINLINE float GetDataCompleteness() const
	{
		return float(Data.Num()) / float(DataSize);
	}
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGINVOXEL_API ULFPVoxelNetworkProxyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPVoxelNetworkProxyComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UFUNCTION(BlueprintPure, Category = "LFPVoxelNetworkProxyComponent | Function")
		float GetDataCompleteness(const int32 ClientID) const;

public:

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelNetworkProxyComponent | Function")
		bool SetupProxy(ULFPGridContainerComponent* InVoxelContainer, ULFPTCPSocketComponent* InNetworkSocket, const FLFPTCPSocketSetting SocketSetting);

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelNetworkProxyComponent | Function")
		bool RequestChuckData(const int32 RegionIndex, const int32 ChuckIndex, const int32 ClientID);

public:

	UFUNCTION()
		void OnChuckUpdate(const int32 RegionIndex, const int32 ChuckIndex, const FLFPGridUpdateAction& VoxelUpdateAction);

	UFUNCTION()
		void OnNetworkMessage(const int32 SocketID, const int32 ClientID, const TArray<uint8>& Bytes);

protected:  // Runtime Data

	UPROPERTY()
		TMap<int32, FLFPVoxelNetworkProxyReceiveInfo> IncomeDataMap;

	UPROPERTY()
		TMap<int32, FLFPVoxelNetworkProxySendInfo> ChuckUpdateQueue;

	UPROPERTY()
		TObjectPtr<ULFPGridContainerComponent> VoxelContainer;

	UPROPERTY()
		TObjectPtr<ULFPTCPSocketComponent> NetworkSocket;

	UPROPERTY()
		int32 SocketIndex = INDEX_NONE;

	UPROPERTY()
		bool bIsServer = true;
};
