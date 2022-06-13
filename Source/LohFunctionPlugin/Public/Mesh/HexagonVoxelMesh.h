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
		void SetupMesh(ULFPVoxelData* NewVoxelData, const int32 NewChuckIndex) override;

	FORCEINLINE void MarkVoxelDataForUpdate(const int32 VoxelIndex, const bool IsNotSingle);

	FORCEINLINE void UpdateMesh();

protected:

	void UpdateVertices();

	void UpdateTriangles();

	FORCEINLINE void AddHexagonWall(const TArray<int32>& VertexIndexList, FLFPVoxelTriangleUpdateData& UpdateData, const int32 ID);

	FORCEINLINE void AddHexagonRoof(const TArray<int32>& VertexIndexList, FLFPVoxelTriangleUpdateData& UpdateData, const int32 ID);

	FORCEINLINE void FindBlockNeighbour(const FIntVector GridLocation, TArray<FIntVector>& NeighbourLocationList);

	FORCEINLINE void FindBlockVertices(const FIntVector GridLocation, TArray<int32>& VerticesIndexList);

};

