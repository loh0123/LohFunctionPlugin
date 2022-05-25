// Fill out your copyright notice in the Description page of Project Settings.


#include "Mesh/BaseVoxelMesh.h"
#include "./Math/LFPGridLibrary.h"

DEFINE_LOG_CATEGORY(BaseVoxelMesh);

void UBaseVoxelMesh::SetupMesh(const FVector MeshSize, const FIntVector GridSize, const TSet<FName>& RenderNameList, const TArray<FLFPVoxelGridData>& GridData)
{
	// Clean Up Every Data
	Reset();
	MeshData = FLFPVoxelMeshData();
	//////////////////////


	MeshData.MeshSize = MeshSize;
	MeshData.GridSize = GridSize;
	MeshData.RenderNameList = RenderNameList;

	MeshData.MaxIndex = GridSize.X * GridSize.Y * GridSize.Z;

	MeshData.GridData = GridData;
	MeshData.GridData.SetNum(MeshData.MaxIndex);
	MeshData.TriangleDataList.SetNum(MeshData.MaxIndex);

	MeshData.TriangleUpdateList.Reserve(MeshData.MaxIndex);


	for (int32 TriIndex = 0; TriIndex < FMath::Min(MeshData.MaxIndex, GridData.Num()); TriIndex++)
	{
		MeshData.TriangleUpdateList.Add(TriIndex);
	}

	UpdateMesh();

	return;
}


void UBaseVoxelMesh::MarkTrianglesDataForUpdate(const int32 GridIndex)
{
	check(GridIndex < MeshData.MaxIndex&& GridIndex >= 0);

	if (MeshData.TriangleDataList[GridIndex].MeshTriangleIndex.Num() > 0) EditMesh([&](FDynamicMesh3& EditMesh)
	{
		for (int32 TriangleIndex : MeshData.TriangleDataList[GridIndex].MeshTriangleIndex)
		{
			EditMesh.RemoveTriangle(TriangleIndex, false);
		}

	}, EDynamicMeshChangeType::DeformationEdit, EDynamicMeshAttributeChangeFlags::MeshTopology, false);

	MeshData.TriangleDataList[GridIndex] = FLFPVoxelTriangleData();

	MeshData.TriangleUpdateList.Add(GridIndex);

	return;
}