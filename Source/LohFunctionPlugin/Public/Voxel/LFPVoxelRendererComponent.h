// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/MeshComponent.h"
#include "Voxel/LFPVoxelContainerComponent.h"
#include "LFPVoxelRendererComponent.generated.h"

class ULFPVoxelContainerComponent;

/**
 * 
 */
UCLASS()
class LOHFUNCTIONPLUGIN_API ULFPVoxelRendererComponent : public UMeshComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULFPVoxelRendererComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelRendererComponent | Setter")
		FORCEINLINE bool InitializeRenderer(const int32 RegionIndex, const int32 ChuckIndex, ULFPVoxelContainerComponent* NewVoxelContainer);

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelRendererComponent | Setter")
		FORCEINLINE bool ReleaseRenderer();

public:

	UFUNCTION()
		FORCEINLINE void OnChuckUpdate(const FLFPChuckUpdateAction& Data);

public:

	UPROPERTY(BlueprintReadOnly, Category = "LFPVoxelRendererComponent | Cache")
		TObjectPtr<ULFPVoxelContainerComponent> VoxelContainer = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "LFPVoxelRendererComponent | Cache")
		int32 RegionIndex = INDEX_NONE;
		
	UPROPERTY(BlueprintReadOnly, Category = "LFPVoxelRendererComponent | Cache")
		int32 ChuckIndex = INDEX_NONE;
	
};
