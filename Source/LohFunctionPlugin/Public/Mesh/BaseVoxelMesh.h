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

	UPROPERTY() int32 GridIndex = INDEX_NONE;

	UPROPERTY() TArray<FIntVector> NewTriangleList;

	UPROPERTY() TArray<int32> NewTriangleGroupList;

	UPROPERTY() TArray<FVector2f> NewUVList;
};

USTRUCT(BlueprintType)
struct FLFPVoxelGridData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelGridData")
		bool IsVisible = false;

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

	FLFPVoxelMeshData() {}

	FLFPVoxelMeshData(const FLFPVoxelMeshData& Data) : GridData(Data.GridData), MeshSize(Data.MeshSize), GridSize(Data.GridSize) {}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelData")
		TArray<FLFPVoxelGridData> GridData = {};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelData | Setting")
		FVector MeshSize = FVector(400, 346.4, 300);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelData | Setting")
		FIntVector GridSize = FIntVector(1);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelData")
		bool IsInitialized = false;



	UPROPERTY(VisibleAnywhere, Category = "LFPVoxelData | Cache")
		TArray<FVector> VerticesList = {};

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPVoxelData | Cache")
		FIntVector VertexSize = FIntVector::NoneValue;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPVoxelData | Cache")
		int32 MaxIndex = INDEX_NONE;

	UPROPERTY(VisibleAnywhere, Category = "LFPVoxelData | Cache")
		TArray<FLFPVoxelTriangleData> TriangleDataList = {};

	UPROPERTY(VisibleAnywhere, Category = "LFPVoxelData | Cache")
		TSet<int32> DataUpdateList = {};

	FORCEINLINE void Unload()
	{
		VerticesList.Empty();
		VertexSize = FIntVector::NoneValue;
		MaxIndex = INDEX_NONE;
		TriangleDataList.Empty();
		DataUpdateList.Empty();
	}

	FORCEINLINE void Load()
	{
		MaxIndex = GridSize.X * GridSize.Y * GridSize.Z;
		TriangleDataList.SetNum(MaxIndex);
		GridData.SetNum(MaxIndex);

		DataUpdateList.Reserve(MaxIndex);

		for (int32 TriIndex = 0; TriIndex < FMath::Min(MaxIndex, GridData.Num()); TriIndex++)
		{
			DataUpdateList.Add(TriIndex);
		}
	}
};

/**
 *  This class is the base of voxel and is design to be override
 */
UCLASS()
class LOHFUNCTIONPLUGIN_API UBaseVoxelMesh : public UDynamicMesh
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVoxelBeginGenerator, UBaseVoxelMesh*, VoxelMesh);

public:

	UPROPERTY(BlueprintAssignable)
		FOnVoxelBeginGenerator OnBeginGenerator;

public:

	virtual void SetupPool(TObjectPtr<UBaseVoxelPool> NewVoxelPool, const FIntVector NewPoolLocation, const int32 NewPoolIndex);

	virtual void ClearPool();

	virtual void SetupMesh(const FVector MeshSize, const FIntVector GridSize, const TArray<FLFPVoxelGridData>& GridData);

	virtual void SetVoxelGridData(const FIntVector GridLocation, const FLFPVoxelGridData& GridData, const bool bUpdateMesh);

	virtual void SetVoxelGridDataList(const TArray<FIntVector>& GridLocationList, const TArray<FLFPVoxelGridData>& GridDataList, const bool bUpdateMesh);

	virtual void SetVoxelGridDataListWithSingleData(const TArray<FIntVector>& GridLocationList, const FLFPVoxelGridData& GridData, const bool bUpdateMesh);

	virtual void SetAllVoxelGridDataWithSingleData(const FLFPVoxelGridData& GridData, const bool bUpdateMesh);

	virtual void UpdateMesh_Internal() { unimplemented(); }  // Override This


	FORCEINLINE void UpdateMesh();

	FORCEINLINE void MarkTrianglesDataForUpdate(const FIntVector GridLocation);

	FORCEINLINE void MarkTrianglesDataListForUpdate(const TSet<FIntVector>& GridLocationList);

	FORCEINLINE void MarkAllTrianglesDataForUpdate();


	FORCEINLINE const FLFPVoxelMeshData& GetVoxelMeshData() const;


	FORCEINLINE bool IsInitialized() const;

	FORCEINLINE void SetInitialized(const bool Value);

protected:

	FORCEINLINE FLFPVoxelMeshData& GetVoxelMeshData();


	FORCEINLINE void UpdateVertices() { unimplemented(); }  // Override This

	FORCEINLINE void UpdateTriangles();

	FORCEINLINE void FindBlockNeighbour(const FIntVector GridLocation, TArray<FIntVector>& NeighbourLocationList) { unimplemented(); }  // Override This

	FORCEINLINE void FindBlockVertices(const FIntVector GridLocation, TArray<int32>& VerticesIndexList) { unimplemented(); }  // Override This

	FORCEINLINE bool IsBlockVisible(const FIntVector GridLocation, const int32 SelfMaterialID) const;

private:

	UPROPERTY() FLFPVoxelMeshData LocalVoxelData;

	UPROPERTY() TObjectPtr<UBaseVoxelPool> VoxelPool;

	UPROPERTY() FIntVector PoolLocation = FIntVector::NoneValue;

	UPROPERTY() FIntVector PoolVoxelLocation = FIntVector::NoneValue;

	UPROPERTY() int32 PoolIndex = INDEX_NONE;


};
