// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "GeometryFramework/Public/UDynamicMesh.h"
#include "GeometryScriptingCore/Public/GeometryScript/GeometryScriptTypes.h"
#include "DynamicHexaVoxel.generated.h"

USTRUCT(BlueprintType)
struct FLFPVoxelBlockData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelData")
		bool IsVisible = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelData")
		uint8 RenderLayer = 0;
};

USTRUCT(BlueprintType)
struct FLFPVoxelTriData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelTriData")
		FGeometryScriptIndexList MeshTriangleIndex = FGeometryScriptIndexList();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelTriData")
		TArray<FGeometryScriptUVTriangle> MeshUVList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelTriData")
		bool IsDirty = true;
};

USTRUCT(BlueprintType)
struct FLFPVoxelData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelData")
		TArray<FLFPVoxelBlockData> GridData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelData | Setting") 
		FVector MeshSize = FVector(400,346.4,300);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelData | Setting") 
		FIntVector GridSize = FIntVector(1);



	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelData | Cache")
		FIntVector VertexSize = FIntVector(-1);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelData | Cache")
		int32 MaxIndex = -1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelData | Cache")
		FGeometryScriptIndexList MeshVertexIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelData | Cache")
		TArray<FLFPVoxelTriData> MeshTriangleData;
};


/**
 * 
 */
UCLASS(Blueprintable)
class LOHFUNCTIONPLUGIN_API UDynamicHexaVoxel : public UDynamicMesh
{
	GENERATED_BODY()

public:

	UDynamicHexaVoxel();

	UFUNCTION(BlueprintCallable, Category = "DynamicHexaVoxel | Function")
		void SetupVoxel(const FVector MeshSize, const FIntVector GridSize, FIntVector& VertexSize, int32& MaxIndex) {
			VoxelData.MeshSize = MeshSize;
			VoxelData.GridSize = GridSize;
			VertexSize = VoxelData.VertexSize;
			MaxIndex = VoxelData.MaxIndex;

			VoxelData.GridData.SetNum(VoxelData.GridSize.Z * VoxelData.GridSize.Y * VoxelData.GridSize.X);
			VoxelData.MeshTriangleData.SetNum(VoxelData.GridSize.Z * VoxelData.GridSize.Y * VoxelData.GridSize.X);

			

			return;
		}

	UFUNCTION(BlueprintCallable, Category = "DynamicHexaVoxel | Function")
		bool SetVoxelData(const FIntVector Location, const bool IsVisible);

	UFUNCTION(BlueprintCallable, Category = "DynamicHexaVoxel | Function")
		void UpdateVertexs();

	UFUNCTION(BlueprintCallable, Category = "DynamicHexaVoxel | Function")
		void UpdateTriangles();
	
	UFUNCTION(BlueprintCallable, Category = "DynamicHexaVoxel | Function")
		void GetHexagonVertexIndexBP(const FIntVector HexagonPos, TArray<int32>& VertexIndex) { VertexIndex.SetNum(12); GetHexagonVertexIndex(HexagonPos, VertexIndex); }

	FORCEINLINE bool IsBlockVisible(const FIntVector Location) const;

	FORCEINLINE bool IsTrianglesVisible(const FIntVector From, const FIntVector To) const;

	FORCEINLINE void GetHexagonVertexIndex(const FIntVector HexagonPos, TArray<int32>& VertexIndexList);

	FORCEINLINE void ProcessHexagonNeighbour(const FIntVector HexagonPos, TFunctionRef<void(const FIntVector&, const int32&)> ProcessFunc);

	FORCEINLINE void BuildHexaWall(const TArray<int32>& VertexIndexList, FGeometryScriptTriangleList& TrianglesList, TArray<FGeometryScriptUVTriangle>& UVList, const int32 WallID);
																					
	FORCEINLINE void BuildHexaRoof(const TArray<int32>& VertexIndexList, FGeometryScriptTriangleList& TrianglesList, TArray<FGeometryScriptUVTriangle>& UVList, const bool IsTop);

public:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "DynamicHexaVoxel | Varaible")
		FLFPVoxelData VoxelData;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "DynamicHexaVoxel | Varaible")
		bool HasDirtyTriangles = true;
};
