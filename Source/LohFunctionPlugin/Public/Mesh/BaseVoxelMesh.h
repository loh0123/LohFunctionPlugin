// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "UDynamicMesh.h"
#include "GeometryScriptingCore/Public/GeometryScript/GeometryScriptTypes.h"
#include "BaseVoxelMesh.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(BaseVoxelMesh, Warning, All);

USTRUCT()
struct FLFPVoxelTriangleUpdateData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() int32 GridIndex = -1;

	UPROPERTY() TArray<FIntVector> NewTriangleList;

	UPROPERTY() TArray<FVector2f> NewUVList;
};

USTRUCT(BlueprintType)
struct FLFPVoxelGridData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelGridData")
		FName BlockName = FName("Air");

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelGridData")
		TArray<FVector2D> UVData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelGridData")
		int32 MaterialID = 0;
};

USTRUCT(BlueprintType)
struct FLFPVoxelTriangleData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelTriangleData")
		TArray<int32> MeshTriangleIndex = {};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelTriangleData")
		bool NeedUpdate = true;
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
		TSet<FName> RenderNameList = {};



	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPVoxelData | Cache")
		bool TrianglesNeedUpdate = true;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPVoxelData | Cache")
		FIntVector VertexSize = FIntVector(-1);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPVoxelData | Cache")
		int32 MaxIndex = -1;

	UPROPERTY(VisibleAnywhere, Category = "LFPVoxelData | Cache")
		TArray<FLFPVoxelTriangleData> TriangleDataList = {};
};

/**
 *  This class is the base of voxel and is design to be override
 */
UCLASS()
class LOHFUNCTIONPLUGIN_API UBaseVoxelMesh : public UDynamicMesh
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "BaseVoxelMesh | Function")
		void SetupMesh(const FVector MeshSize, const FIntVector GridSize, const TSet<FName>& RenderNameList, const TArray<FLFPVoxelGridData>& GridData);

	UFUNCTION(BlueprintCallable, Category = "BaseVoxelMesh | Function")
		void SetVoxelGridData(const FIntVector GridLocation, const FLFPVoxelGridData GridData, const bool bUpdateMesh = true);

	UFUNCTION(BlueprintCallable, Category = "BaseVoxelMesh | Function")
		void SetVoxelGridDataList(const TArray<FIntVector>& GridLocation, const TArray<FLFPVoxelGridData>& GridData, const bool bUpdateMesh = true);

	UFUNCTION(BlueprintCallable, Category = "BaseVoxelMesh | Function") // (Virtual Function Is Costly To Call) (This Is The Bridge To Other Class Function)
		virtual void UpdateMesh() { UE_LOG(BaseVoxelMesh, Warning, TEXT("UpdateMesh Is Running On Base")); }  // Override This

protected:

	UFUNCTION()
		void UpdateVertices() { UE_LOG(BaseVoxelMesh, Warning, TEXT("UpdateVertices Is Running On Base")); }  // Override This

	UFUNCTION()
		void UpdateTriangles() { UE_LOG(BaseVoxelMesh, Warning, TEXT("UpdateTriangles Is Running On Base")); }  // Override This

	UFUNCTION()
		FORCEINLINE void MarkTrianglesDataForUpdate(const int32 GridIndex) { UE_LOG(BaseVoxelMesh, Warning, TEXT("MarkTrianglesDataForUpdate Is Running On Base")); }  // Override This

	UFUNCTION()
		FORCEINLINE void FindBlockNeighbour(const FIntVector GridLocation, TArray<int32>& NeighbourIndexList) { UE_LOG(BaseVoxelMesh, Warning, TEXT("FindBlockNeighbour Is Running On Base")); }  // Override This

	UFUNCTION()
		FORCEINLINE void FindBlockVertices(const FIntVector GridLocation, TArray<int32>& VerticesIndexList) { UE_LOG(BaseVoxelMesh, Warning, TEXT("FindBlockVertices Is Running On Base")); }  // Override This

	UFUNCTION()
		FORCEINLINE bool IsBlockFaceVisible(const int32 FromGridIndex, const int32 ToGridIndex) const { UE_LOG(BaseVoxelMesh, Warning, TEXT("IsBlockFaceVisible Is Running On Base")); return false; }  // Override This

	UFUNCTION()
		FORCEINLINE bool IsBlockNeedRender(const int32 GridIndex) const { UE_LOG(BaseVoxelMesh, Warning, TEXT("IsBlockNeedRender Is Running On Base")); return false; }  // Override This

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "BaseVoxelMesh | Varaible") FLFPVoxelMeshData MeshData;
	
};
