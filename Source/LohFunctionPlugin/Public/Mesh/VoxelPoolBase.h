// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UDynamicMesh.h"
#include "BaseVoxelMesh.h"
#include "VoxelPoolBase.generated.h"

/**
 * 
 */
UCLASS()
class LOHFUNCTIONPLUGIN_API UVoxelPoolBase : public UDynamicMeshPool
{
	GENERATED_BODY()
	
		FORCEINLINE bool IsBlockVisible(const FIntVector PoolLocation) const { return false; };

	FORCEINLINE void MarkTrianglesDataListForUpdate(const TSet<FIntVector>& PoolLocationList) {};
};
