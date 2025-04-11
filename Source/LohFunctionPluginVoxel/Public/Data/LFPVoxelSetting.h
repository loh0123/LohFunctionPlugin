// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LFPVoxelSetting.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LOHFUNCTIONPLUGINVOXEL_API ULFPVoxelSetting : public UDataAsset
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting|VoxelSetting")
	FIntVector VoxelSize = FIntVector(100);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting|VoxelSetting")
	bool bDisableChuckFaceCulling = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting|VoxelSetting")
	bool bDisableRegionFaceCulling = false;

public:

	FORCEINLINE FVector GetVoxelSize( ) const { return FVector(VoxelSize); }

	FORCEINLINE bool IsChunkFaceCullingDisable( ) const { return bDisableChuckFaceCulling; }

	FORCEINLINE bool IsRegionFaceCullingDisable( ) const { return bDisableRegionFaceCulling; }
};
