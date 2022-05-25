// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mesh/BaseVoxelMesh.h"
#include "HexagonVoxelMesh.generated.h"

/**
 * 
 */
UCLASS()
class LOHFUNCTIONPLUGIN_API UHexagonVoxelMesh : public UBaseVoxelMesh
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "HexagonVoxelMesh | Function")
	void SetVoxelGridData(const FIntVector GridLocation, const FLFPVoxelGridData GridData, const bool bUpdateMesh = true);

	UFUNCTION(BlueprintCallable, Category = "HexagonVoxelMesh | Function")
	void SetVoxelGridDataList(const TArray<FIntVector>& GridLocation, const TArray<FLFPVoxelGridData>& GridData, const bool bUpdateMesh = true);

	void UpdateMesh() override { if (MeshData.VertexSize.GetMax() == INDEX_NONE) UpdateVertices();  UpdateTriangles(); }

protected:

	void UpdateVertices();

	void UpdateTriangles();

	FORCEINLINE void AddHexagonWall(const TArray<int32>& VertexIndexList, FLFPVoxelTriangleUpdateData& UpdateData, const int32 ID);

	FORCEINLINE void AddHexagonRoof(const TArray<int32>& VertexIndexList, FLFPVoxelTriangleUpdateData& UpdateData, const int32 ID);

	FORCEINLINE void FindBlockNeighbour(const FIntVector GridLocation, TArray<int32>& NeighbourIndexList);

	FORCEINLINE void FindBlockVertices(const FIntVector GridLocation, TArray<int32>& VerticesIndexList);

	FORCEINLINE bool IsBlockFaceVisible(const int32 FromGridIndex, const int32 ToGridIndex) const;

	FORCEINLINE bool IsBlockNeedRender(const int32 GridIndex) const;

};
