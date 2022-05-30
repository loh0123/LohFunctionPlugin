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

		void SetupPool(TObjectPtr<UBaseVoxelPool> NewVoxelPool, const FIntVector NewPoolLocation, const int32 NewPoolIndex) override;

	UFUNCTION(BlueprintCallable, Category = "HexagonVoxelMesh | Function")
		void SetupMesh(const FVector MeshSize, const FIntVector GridSize, const TSet<FName>& IgnoreNameList, const TArray<FLFPVoxelGridData>& GridData) override;

	UFUNCTION(BlueprintCallable, Category = "HexagonVoxelMesh | Function")
		void SetVoxelGridData(const FIntVector GridLocation, const FLFPVoxelGridData& GridData, const bool bUpdateMesh = true) override;

	UFUNCTION(BlueprintCallable, Category = "HexagonVoxelMesh | Function")
		void SetVoxelGridDataList(const TArray<FIntVector>& GridLocationList, const TArray<FLFPVoxelGridData>& GridDataList, const bool bUpdateMesh = true) override;

	UFUNCTION(BlueprintCallable, Category = "HexagonVoxelMesh | Function")
		void SetVoxelGridDataListWithSingleData(const TArray<FIntVector>& GridLocationList, const FLFPVoxelGridData& GridData, const bool bUpdateMesh) override;

	UFUNCTION(BlueprintCallable, Category = "HexagonVoxelMesh | Function")
		void SetAllVoxelGridDataWithSingleData(const FLFPVoxelGridData& GridData, const bool bUpdateMesh) override;

	UFUNCTION(BlueprintCallable, Category = "HexagonVoxelMesh | Function")
		void SetVoxelGridAreaData(const int32 OriginGridIndex, const FIntVector Range, const FLFPVoxelGridData& GridData, const bool bUpdateMesh = true);

		void UpdateMesh_Internal() override { if (GetVoxelMeshData().VertexSize.GetMax() == INDEX_NONE) UpdateVertices();  UpdateTriangles(); }

	UFUNCTION(BlueprintCallable, Category = "HexagonVoxelMesh | Function")
		void UpdateMesh() { Super::UpdateMesh(); };

protected:

	void UpdateVertices();

	void UpdateTriangles();

	FORCEINLINE void AddHexagonWall(const TArray<int32>& VertexIndexList, FLFPVoxelTriangleUpdateData& UpdateData, const int32 ID);

	FORCEINLINE void AddHexagonRoof(const TArray<int32>& VertexIndexList, FLFPVoxelTriangleUpdateData& UpdateData, const int32 ID);

	FORCEINLINE void FindBlockNeighbour(const FIntVector GridLocation, TArray<FIntVector>& NeighbourLocationList);

	FORCEINLINE void FindBlockVertices(const FIntVector GridLocation, TArray<int32>& VerticesIndexList);

};
