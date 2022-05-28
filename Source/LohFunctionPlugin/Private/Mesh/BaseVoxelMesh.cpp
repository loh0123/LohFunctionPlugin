// Fill out your copyright notice in the Description page of Project Settings.


#include "Mesh/BaseVoxelMesh.h"
#include "./Math/LFPGridLibrary.h"
#include "Mesh/VoxelPoolBase.h"
#include "TargetInterfaces/MaterialProvider.h" //FComponentMaterialSet

DEFINE_LOG_CATEGORY(BaseVoxelMesh);

void UBaseVoxelMesh::SetupMesh(const FVector MeshSize, const FIntVector GridSize, const TSet<FName>& RenderNameList, const TArray<FLFPVoxelGridData>& GridData)
{
	FLFPVoxelMeshData& MeshData = GetVoxelMeshData();

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

	MeshData.DataUpdateList.Reserve(MeshData.MaxIndex);


	for (int32 TriIndex = 0; TriIndex < FMath::Min(MeshData.MaxIndex, GridData.Num()); TriIndex++)
	{
		MeshData.DataUpdateList.Add(TriIndex);
	}

	return;
}

void UBaseVoxelMesh::SetVoxelGridData(const FIntVector GridLocation, const FLFPVoxelGridData& GridData, const bool bUpdateMesh)
{
	FLFPVoxelMeshData& MeshData = GetVoxelMeshData();

	checkf(ULFPGridLibrary::IsLocationValid(GridLocation, MeshData.GridSize), TEXT("Not allow invalid location (SetVoxelGridData)"));

	// Replace Data In Array
	MeshData.GridData[ULFPGridLibrary::GridLocationToIndex(GridLocation,MeshData.GridSize)] = GridData;

	return;
}


void UBaseVoxelMesh::SetVoxelGridDataList(const TArray<FIntVector>& GridLocationList, const TArray<FLFPVoxelGridData>& GridDataList, const bool bUpdateMesh)
{
	FLFPVoxelMeshData& MeshData = GetVoxelMeshData();

	for (const FIntVector& GridLocation : GridLocationList)
	{
		checkf(ULFPGridLibrary::IsLocationValid(GridLocation, MeshData.GridSize), TEXT("Not allow invalid location on array (SetVoxelGridDataList)"));

		// Find Index
		const int32 GridIndex = ULFPGridLibrary::GridLocationToIndex(GridLocation, MeshData.GridSize);

		// Replace Data In Array
		MeshData.GridData[GridIndex] = GridDataList[GridIndex];
	}

	return;
}


void UBaseVoxelMesh::UpdateTriangles()
{
	FLFPVoxelMeshData& MeshData = GetVoxelMeshData();

	if (MeshData.DataUpdateList.Num() > 0)
		EditMesh([&](FDynamicMesh3& EditMesh)
		{
			for (int32 DataIndex : MeshData.DataUpdateList)
			{
				for (int32 TriangleIndex : MeshData.TriangleDataList[DataIndex].MeshTriangleIndex)
				{
					EditMesh.RemoveTriangle(TriangleIndex, false);
				}

				MeshData.TriangleDataList[DataIndex] = FLFPVoxelTriangleData();
			}

		}, EDynamicMeshChangeType::GeneralEdit, EDynamicMeshAttributeChangeFlags::Unknown, false);

	return;
}


void UBaseVoxelMesh::MarkTrianglesDataForUpdate(const FIntVector& GridLocation, FLFPVoxelMeshData& MeshData)
{
	if (ULFPGridLibrary::IsLocationValid(GridLocation, MeshData.GridSize))
		MeshData.DataUpdateList.Add(ULFPGridLibrary::GridLocationToIndex(GridLocation, MeshData.GridSize));
	else
	{
		// ToDo : Make Out Bound Update Function
	}

	return;
}

void UBaseVoxelMesh::MarkTrianglesDataListForUpdate(const TSet<FIntVector>& GridLocationList)
{
	FLFPVoxelMeshData& MeshData = GetVoxelMeshData();

	for (const FIntVector& GridLocation : GridLocationList)
	{
		MarkTrianglesDataForUpdate(GridLocation, MeshData);
	}

	return;
}

bool UBaseVoxelMesh::IsBlockVisible(const int32 GridIndex) const
{
	return GetVoxelMeshData().RenderNameList.Contains(GetVoxelMeshData().GridData[GridIndex].BlockName);  // Not In Render List;
}

