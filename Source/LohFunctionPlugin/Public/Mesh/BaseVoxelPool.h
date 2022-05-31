// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "UDynamicMesh.h"
#include "BaseVoxelMesh.h"
#include "BaseVoxelPool.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Transient)
class LOHFUNCTIONPLUGIN_API UBaseVoxelPool : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "BaseVoxelPool | Function")
		virtual void SetupVoxelPool(const FIntVector NewPoolGridSize, const int32 NewAllowMeshSize, const FVector NewMainMeshSize, const FIntVector NewMainGridSize, TSubclassOf<UBaseVoxelMesh> VoxelType);

	UFUNCTION(BlueprintCallable, Category = "BaseVoxelPool | Function")
		FORCEINLINE void ProcessVoxelUpdate(const int32 Count);


	FORCEINLINE FLFPVoxelMeshData& GetPoolVoxelData(const int32 PoolIndex);

	FORCEINLINE int32 PoolVoxelLocationToPoolIndex(const FIntVector PoolVoxelLocation) const;

	FORCEINLINE FIntVector PoolVoxelLocationToVoxelLocation(const FIntVector PoolVoxelLocation) const;

	FORCEINLINE void MarkTrianglesDataForUpdate(const FIntVector& PoolVoxelLocation);

	FORCEINLINE void MarkTrianglesDataListForUpdate(const TSet<FIntVector>& PoolVoxelLocationList);

	FORCEINLINE bool IsBlockVisible(const FIntVector PoolVoxelLocation) const;


	FORCEINLINE void AddVoxelUpdate(TObjectPtr<UBaseVoxelMesh> VoxelMesh);

public:
	
	UFUNCTION(BlueprintCallable, Category = "BaseVoxelPool")
		UBaseVoxelMesh* RequestMesh(const FIntVector PoolLocation);

	
	UFUNCTION(BlueprintCallable, Category = "BaseVoxelPool")
		void ReturnMesh(UBaseVoxelMesh* Mesh);

	
	UFUNCTION(BlueprintCallable, Category = "BaseVoxelPool")
		void ReturnAllMeshes();

	
	UFUNCTION(BlueprintCallable, Category = "BaseVoxelPool")
		void FreeAllMeshes();

protected:
	UPROPERTY() TArray<TObjectPtr<UBaseVoxelMesh>> UpdateList;

	/** Meshes in the pool that are available */
	UPROPERTY() TArray<TObjectPtr<UBaseVoxelMesh>> CachedMeshes;

	UPROPERTY() TMap<int32,TObjectPtr<UBaseVoxelMesh>> ActiveMeshes;

	/** All meshes the pool has allocated */
	UPROPERTY() TSet<TObjectPtr<UBaseVoxelMesh>> AllCreatedMeshes;

public:

	UPROPERTY() TArray<FLFPVoxelMeshData> PoolVoxelData;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseVoxelPool | Setting")
		FIntVector PoolGridSize = FIntVector(1);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseVoxelPool | Setting")
		int32 PoolSize = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseVoxelPool | Setting")
		int32 AllowMeshSize = 100;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseVoxelPool | Setting")
		FVector MainMeshSize = FVector(400, 346.4, 300);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseVoxelPool | Setting")
		FIntVector MainGridSize = FIntVector(1);
};
