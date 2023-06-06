// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LFPVoxelNetworkProxyComponent.generated.h"

class ULFPVoxelContainerComponent;
class ULFPTCPSocketComponent;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPVoxelNetworkProxyComponent : public UActorComponent
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

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelNetworkProxyComponent | Function")
		bool SetupProxy(ULFPVoxelContainerComponent* InVoxelContainer, ULFPTCPSocketComponent* InNetworkSocket, const FLFPTCPSocketSetting SocketSetting, const bool InbIsServer = true);

public:

	UFUNCTION()
		void OnChuckUpdate(const int32 RegionIndex, const int32 ChuckIndex, const FLFPVoxelUpdateAction& VoxelUpdateAction);

	UFUNCTION()
		void OnNetworkMessage(const int32 SocketID, const int32 ClientID, const TArray<uint8>& Bytes);

protected:  // Runtime Data

	UPROPERTY()
		TSet<FIntVector> ChuckUpdateQueue;

	UPROPERTY()
		TObjectPtr<ULFPVoxelContainerComponent> VoxelContainer;

	UPROPERTY()
		TObjectPtr<ULFPTCPSocketComponent> NetworkSocket;

	UPROPERTY()
		int32 SocketIndex = INDEX_NONE;

	UPROPERTY()
		bool bIsServer = true;
};
