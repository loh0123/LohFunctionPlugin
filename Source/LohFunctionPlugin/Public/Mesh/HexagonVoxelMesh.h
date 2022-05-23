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

	void UpdateMesh() override { if (MeshData.VertexSize.GetMax() == 0) UpdateVertices(); if (MeshData.TrianglesNeedUpdate) UpdateTriangles(); }

protected:

	void UpdateVertices();

	void UpdateTriangles();

	FORCEINLINE void AddHexagonWall(const TArray<int32>& VertexIndexList, TArray<FIntVector>& TrianglesList, TArray<FVector2f>& UVList, const int32 ID);

	FORCEINLINE void AddHexagonRoof(const TArray<int32>& VertexIndexList, TArray<FIntVector>& TrianglesList, TArray<FVector2f>& UVList, const int32 ID);

	FORCEINLINE void MarkTrianglesDataForUpdate(const int32 GridIndex);

	FORCEINLINE void FindBlockNeighbour(const FIntVector GridLocation, TArray<int32>& NeighbourIndexList);

	FORCEINLINE void FindBlockVertices(const FIntVector GridLocation, TArray<int32>& VerticesIndexList);

	FORCEINLINE bool IsBlockFaceVisible(const int32 FromGridIndex, const int32 ToGridIndex) const;

	FORCEINLINE bool IsBlockNeedRender(const int32 GridIndex) const;

};
