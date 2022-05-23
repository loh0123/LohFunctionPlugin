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

	UpdateMesh();

	return;
}

void UBaseVoxelMesh::SetVoxelGridData(const FIntVector GridLocation, const FLFPVoxelGridData GridData, const bool bUpdateMesh)
{
	if (!ULFPGridLibrary::IsLocationValid(GridLocation, MeshData.GridSize)) return;

	// Find Index On The Array
	const int32 GridIndex = ULFPGridLibrary::GridLocationToIndex(GridLocation, MeshData.GridSize);

	// Replace Data In Array
	MeshData.GridData[GridIndex] = GridData;

	// Mark Cache To Be Clean Up
	MarkTrianglesDataForUpdate(GridIndex);

	// Find Neighbour On GridLocation
	TArray<int32> NeighbourIndexList;
	FindBlockNeighbour(GridLocation, NeighbourIndexList);
	/////////////////////////////////

	// Mark Neighbour Cache To Be Clean Up
	for (int32 NeighbourIndex : NeighbourIndexList)
	{
		MarkTrianglesDataForUpdate(NeighbourIndex);
	}

	// Check If Update Mesh Is Needed
	if (bUpdateMesh) UpdateMesh();

	return;
}

void UBaseVoxelMesh::SetVoxelGridDataList(const TArray<FIntVector>& GridLocation, const TArray<FLFPVoxelGridData>& GridData, const bool bUpdateMesh)
{
	TSet<int32> MarkIndexList;

	MarkIndexList.Reserve(GridLocation.Num());

	for (int32 LoopIndex = 0; LoopIndex < GridLocation.Num(); LoopIndex++)
	{
		if (!ULFPGridLibrary::IsLocationValid(GridLocation[LoopIndex], MeshData.GridSize)) continue;

		// Find Index On The Array
		const int32 GridIndex = ULFPGridLibrary::GridLocationToIndex(GridLocation[LoopIndex], MeshData.GridSize);

		// Replace Data In Array
		MeshData.GridData[GridIndex] = GridData.IsValidIndex(LoopIndex) ? GridData[LoopIndex] : FLFPVoxelGridData();

		// Add Index To MarkList
		MarkIndexList.Add(GridIndex);

		// Find Neighbour On GridLocation
		TArray<int32> NeighbourIndexList;
		FindBlockNeighbour(GridLocation[LoopIndex], NeighbourIndexList);
		/////////////////////////////////

		// Add Neighbour Index To MarkList
		MarkIndexList.Append(NeighbourIndexList);
	}

	// Mark All Index In MarkList To Be Clean Up
	for (int32 MarkIndex : MarkIndexList)
	{
		MarkTrianglesDataForUpdate(MarkIndex);
	}

	return;
}