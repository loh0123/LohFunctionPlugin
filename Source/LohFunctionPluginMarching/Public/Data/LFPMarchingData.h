// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LFPMarchingMeshSet.h"
#include "LFPMarchingData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LOHFUNCTIONPLUGINMARCHING_API ULFPMarchingData : public UDataAsset
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting")
	TSoftObjectPtr< ULFPMarchingMeshSet > MeshSet = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting")
	FIntVector MarchingSize = FIntVector(100);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting|GridSize")
	FIntVector SectionGridSize = FIntVector(2);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting")
	bool bDisableChuckFaceCulling = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting")
	bool bDisableRegionFaceCulling = false;

public:

	FORCEINLINE ULFPMarchingMeshSet* GetMeshSet( ) const { return MeshSet.LoadSynchronous(); }

	FORCEINLINE FVector GetMarchingSize( ) const { return FVector(MarchingSize); }

	FORCEINLINE const FIntVector& GetSectionGridSize( ) const { return SectionGridSize; }

	FORCEINLINE int32 GetSectionIndexSize( ) const { return SectionGridSize.X * SectionGridSize.Y * SectionGridSize.Z; }

	FORCEINLINE bool IsChunkFaceCullingDisable( ) const { return bDisableChuckFaceCulling; }

	FORCEINLINE bool IsRegionFaceCullingDisable( ) const { return bDisableRegionFaceCulling; }
};
