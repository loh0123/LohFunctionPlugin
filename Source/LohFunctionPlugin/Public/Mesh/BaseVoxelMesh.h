// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "UDynamicMesh.h"
#include "GeometryScriptingCore/Public/GeometryScript/GeometryScriptTypes.h"
#include "Components/DynamicMeshComponent.h"
#include "BaseVoxelMesh.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(BaseVoxelMesh, Warning, All);

class UBaseVoxelPool;

USTRUCT()
struct FLFPVoxelTriangleUpdateData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() int32 GridIndex = -1;

	UPROPERTY() TArray<FIntVector> NewTriangleList;

	UPROPERTY() TArray<int32> NewTriangleGroupList;

	UPROPERTY() TArray<FVector2f> NewUVList;
};

USTRUCT(BlueprintType)
struct FLFPVoxelGridData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelGridData")
		FName BlockName = FName("Air");

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelGridData")
		TArray<FVector2D> CustomData = {};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelGridData")
		int32 MaterialID = 0;
};

USTRUCT(BlueprintType)
struct FLFPVoxelTriangleData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelTriangleData")
		TArray<int32> MeshTriangleIndex = {};
};

USTRUCT(BlueprintType)
struct FLFPVoxelMeshData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelData")
		TArray<FLFPVoxelGridData> GridData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelData | Setting")
		FVector MeshSize = FVector(400, 346.4, 300);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelData | Setting")
		FIntVector GridSize = FIntVector(1);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelData | Setting")
		TSet<FName> IgnoreNameList = { FName("Air") };




	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPVoxelData | Cache")
		FIntVector VertexSize = FIntVector(INDEX_NONE);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPVoxelData | Cache")
		int32 MaxIndex = INDEX_NONE;

	UPROPERTY(VisibleAnywhere, Category = "LFPVoxelData | Cache")
		TArray<FLFPVoxelTriangleData> TriangleDataList = {};

	UPROPERTY(VisibleAnywhere, Category = "LFPVoxelData | Cache")
		TSet<int32> DataUpdateList = {};
};

/**
 *  This class is the base of voxel and is design to be override
 */
UCLASS()
class LOHFUNCTIONPLUGIN_API UBaseVoxelMesh : public UDynamicMesh
{
	GENERATED_BODY()

public:

	virtual void SetupPool(UBaseVoxelPool* NewVoxelPool, const FIntVector NewPoolLocation, const int32 NewPoolIndex);

	virtual void ClearPool();

	virtual void SetupMesh(const FVector MeshSize, const FIntVector GridSize, const TSet<FName>& IgnoreNameList, const TArray<FLFPVoxelGridData>& GridData);

	virtual void SetVoxelGridData(const FIntVector GridLocation, const FLFPVoxelGridData& GridData, const bool bUpdateMesh);

	virtual void SetVoxelGridDataList(const TArray<FIntVector>& GridLocationList, const TArray<FLFPVoxelGridData>& GridDataList, const bool bUpdateMesh);

	virtual void UpdateMesh() { unimplemented(); }  // Override This


	FORCEINLINE void MarkTrianglesDataForUpdate(const FIntVector GridLocation);

protected:

	FORCEINLINE FLFPVoxelMeshData& GetVoxelMeshData();

	FORCEINLINE const FLFPVoxelMeshData& GetVoxelMeshData() const;



	FORCEINLINE void UpdateVertices() { unimplemented(); }  // Override This

	FORCEINLINE void UpdateTriangles();

	FORCEINLINE void MarkTrianglesDataForUpdate(const FIntVector GridLocation, FLFPVoxelMeshData& MeshData);

	FORCEINLINE void MarkTrianglesDataListForUpdate(const TSet<FIntVector>& GridLocationList);

	FORCEINLINE void FindBlockNeighbour(const FIntVector GridLocation, TArray<FIntVector>& NeighbourLocationList) { unimplemented(); }  // Override This

	FORCEINLINE void FindBlockVertices(const FIntVector GridLocation, TArray<int32>& VerticesIndexList) { unimplemented(); }  // Override This

	FORCEINLINE bool IsBlockVisible(const int32 GridIndex) const;

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "BaseVoxelMesh | Varaible") FLFPVoxelMeshData LocalVoxelData;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "BaseVoxelMesh | Varaible") UBaseVoxelPool* VoxelPool;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "BaseVoxelMesh | Varaible") FIntVector PoolLocation = FIntVector::NoneValue;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "BaseVoxelMesh | Varaible") FIntVector PoolVoxelLocation = FIntVector::NoneValue;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "BaseVoxelMesh | Varaible") int32 PoolIndex = INDEX_NONE;
};
