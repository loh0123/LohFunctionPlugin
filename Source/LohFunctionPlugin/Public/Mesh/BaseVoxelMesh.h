// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "UDynamicMesh.h"
#include "GeometryScriptingCore/Public/GeometryScript/GeometryScriptTypes.h"
#include "Components/DynamicMeshComponent.h"
#include "BaseVoxelMesh.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(BaseVoxelMesh, Warning, All);

class UBaseVoxelPool;
class ULFPVoxelData;

USTRUCT()
struct FLFPVoxelTriangleUpdateData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() int32 GridIndex = INDEX_NONE;

	UPROPERTY() TArray<FIntVector> NewTriangleList;

	UPROPERTY() TArray<int32> NewTriangleGroupList;

	UPROPERTY() TArray<FVector2f> NewUVList;
};

USTRUCT(BlueprintType)
struct FLFPVoxelTriangleData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelTriangleData")
		TArray<int32> MeshTriangleIndex = {};
};

/**
 *  This class is the base of voxel and is design to be override
 */
UCLASS()
class LOHFUNCTIONPLUGIN_API UBaseVoxelMesh : public UDynamicMesh
{
	GENERATED_BODY()

public:

	virtual void SetupMesh(ULFPVoxelData* NewVoxelData, const int32 NewChuckIndex);

	UFUNCTION(BlueprintCallable) virtual void UpdateMesh() { unimplemented(); }  // Override This

	UFUNCTION(BlueprintCallable) FORCEINLINE void MarkTrianglesDataForUpdate(const int32 VoxelIndex);

protected:

	FORCEINLINE void UpdateVertices() { unimplemented(); }  // Override This

	FORCEINLINE void UpdateTriangles();

	FORCEINLINE void FindBlockNeighbour(const FIntVector GridLocation, TArray<FIntVector>& NeighbourLocationList) { unimplemented(); }  // Override This

	FORCEINLINE void FindBlockVertices(const FIntVector GridLocation, TArray<int32>& VerticesIndexList) { unimplemented(); }  // Override This

	FORCEINLINE bool IsBlockVisible(const FIntVector GridLocation, const int32 SelfMaterialID) const;

protected:

	UPROPERTY() TObjectPtr<ULFPVoxelData> VoxelData;

	UPROPERTY() FIntVector ChuckGridLocation = FIntVector::NoneValue;

	UPROPERTY() FIntVector StartVoxelLocation = FIntVector::NoneValue;

	UPROPERTY() int32 ChuckIndex = INDEX_NONE;

	UPROPERTY() FVector MeshSize = FVector(400, 346.4, 300);

	UPROPERTY() FIntVector VoxelGridSize = FIntVector(1);


protected:

	UPROPERTY(VisibleAnywhere, Category = "LFPVoxelData | Cache")
		TArray<FVector> VerticesList = {};

	UPROPERTY(VisibleAnywhere, Category = "LFPVoxelData | Cache")
		FIntVector VertexSize = FIntVector::NoneValue;

	UPROPERTY(VisibleAnywhere, Category = "LFPVoxelData | Cache")
		TArray<FLFPVoxelTriangleData> TriangleDataList = {};

	UPROPERTY(VisibleAnywhere, Category = "LFPVoxelData | Cache")
		TSet<int32> DataUpdateList = {};


};
