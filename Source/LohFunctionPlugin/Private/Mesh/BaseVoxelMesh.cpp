// Copyright by Loh Zhi Kang


#include "Mesh/BaseVoxelMesh.h"
#include "./Math/LFPGridLibrary.h"
#include "Mesh/BaseVoxelPool.h"
#include "TargetInterfaces/MaterialProvider.h" //FComponentMaterialSet
#include "Runtime/Core/Public/Async/ParallelFor.h"

DEFINE_LOG_CATEGORY(BaseVoxelMesh);

void UBaseVoxelMesh::SetupPool(TObjectPtr<UBaseVoxelPool> NewVoxelPool, const FIntVector NewPoolLocation, const int32 NewPoolIndex)
{
	checkf(NewVoxelPool, TEXT("Voxel Pool Can't Be Invalid"));

	VoxelPool = NewVoxelPool;
	PoolLocation = NewPoolLocation;
	PoolIndex = NewPoolIndex;

	FLFPVoxelMeshData& MeshData = NewVoxelPool->PoolVoxelData[NewPoolIndex];

	PoolVoxelLocation = FIntVector(NewPoolLocation.X * MeshData.GridSize.X, NewPoolLocation.Y * MeshData.GridSize.Y, NewPoolLocation.Z * MeshData.GridSize.Z);

	MeshData.GridData.SetNum(MeshData.MaxIndex);
	MeshData.TriangleDataList.SetNum(MeshData.MaxIndex);

	MeshData.DataUpdateList.Reserve(MeshData.MaxIndex);

	for (int32 TriIndex = 0; TriIndex < MeshData.MaxIndex; TriIndex++)
	{
		MeshData.DataUpdateList.Add(TriIndex);
	}
	
	return;
}

void UBaseVoxelMesh::ClearPool()
{
	checkf(VoxelPool, TEXT("Voxel Pool Already Is Invalid"));

	FLFPVoxelMeshData& MeshData = GetVoxelMeshData();

	MeshData.Unload();

	VoxelPool = nullptr;
	PoolLocation = FIntVector::NoneValue;
	PoolVoxelLocation = FIntVector::NoneValue;
	PoolIndex = INDEX_NONE;

	return;
}

void UBaseVoxelMesh::SetupMesh(const FVector MeshSize, const FIntVector GridSize, const TArray<FLFPVoxelGridData>& GridData)
{
	FLFPVoxelMeshData& MeshData = GetVoxelMeshData();

	// Clean Up Every Data
	Reset();
	MeshData = FLFPVoxelMeshData();
	//////////////////////

	MeshData.MeshSize = MeshSize;
	MeshData.GridSize = GridSize;

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

	if (!ULFPGridLibrary::IsLocationValid(GridLocation, MeshData.GridSize)) return;

	// Replace Data In Array
	MeshData.GridData[ULFPGridLibrary::GridLocationToIndex(GridLocation,MeshData.GridSize)] = GridData;

	return;
}


void UBaseVoxelMesh::SetVoxelGridDataList(const TArray<FIntVector>& GridLocationList, const TArray<FLFPVoxelGridData>& GridDataList, const bool bUpdateMesh)
{
	FLFPVoxelMeshData& MeshData = GetVoxelMeshData();

	ParallelFor(GridLocationList.Num(), [&](const int32 LoopIndex) {
		if (ULFPGridLibrary::IsLocationValid(GridLocationList[LoopIndex], MeshData.GridSize))
		{
			// Find Index
			const int32 GridIndex = ULFPGridLibrary::GridLocationToIndex(GridLocationList[LoopIndex], MeshData.GridSize);

			// Replace Data In Array
			MeshData.GridData[GridIndex] = GridDataList.IsValidIndex(LoopIndex) ? GridDataList[LoopIndex] : FLFPVoxelGridData();
		}
	});

	return;
}

void UBaseVoxelMesh::SetVoxelGridDataListWithSingleData(const TArray<FIntVector>& GridLocationList, const FLFPVoxelGridData& GridData, const bool bUpdateMesh)
{
	FLFPVoxelMeshData& MeshData = GetVoxelMeshData();

	ParallelFor(GridLocationList.Num(), [&](const int32 LoopIndex) {
		if (ULFPGridLibrary::IsLocationValid(GridLocationList[LoopIndex], MeshData.GridSize))
		{
			// Find Index
			const int32 GridIndex = ULFPGridLibrary::GridLocationToIndex(GridLocationList[LoopIndex], MeshData.GridSize);

			// Replace Data In Array
			MeshData.GridData[GridIndex] = GridData;
		}
	});

	return;
}

void UBaseVoxelMesh::SetAllVoxelGridDataWithSingleData(const FLFPVoxelGridData& GridData, const bool bUpdateMesh)
{
	FLFPVoxelMeshData& MeshData = GetVoxelMeshData();

	ParallelFor(MeshData.MaxIndex, [&](const int32 GridIndex) {
		// Replace Data In Array
		MeshData.GridData[GridIndex] = GridData;
	});

	return;
}

void UBaseVoxelMesh::UpdateMesh()
{
	if (VoxelPool) 
		VoxelPool->AddVoxelUpdate(this); 
	else 
		UpdateMesh_Internal(); 
	
	return;
}

void UBaseVoxelMesh::MarkTrianglesDataForUpdate(const FIntVector GridLocation)
{
	FLFPVoxelMeshData& MeshData = GetVoxelMeshData();

	if (ULFPGridLibrary::IsLocationValid(GridLocation, MeshData.GridSize))
	{
		MeshData.DataUpdateList.Add(ULFPGridLibrary::GridLocationToIndex(GridLocation, MeshData.GridSize));
	}
	else if (VoxelPool)
	{
		VoxelPool->MarkTrianglesDataForUpdate(GridLocation + PoolVoxelLocation);
	}

	return;
}

void UBaseVoxelMesh::MarkTrianglesDataListForUpdate(const TSet<FIntVector>& GridLocationList)
{
	FLFPVoxelMeshData& MeshData = GetVoxelMeshData();

	TSet<FIntVector> OutBoundList;

	for (const FIntVector& GridLocation : GridLocationList)
	{
		if (ULFPGridLibrary::IsLocationValid(GridLocation, MeshData.GridSize))
		{
			MeshData.DataUpdateList.Add(ULFPGridLibrary::GridLocationToIndex(GridLocation, MeshData.GridSize));
		}
		else
		{
			OutBoundList.Add(GridLocation + PoolVoxelLocation);
		}
	}

	if (VoxelPool) VoxelPool->MarkTrianglesDataListForUpdate(OutBoundList);

	return;
}

void UBaseVoxelMesh::MarkAllTrianglesDataForUpdate()
{
	FLFPVoxelMeshData& MeshData = GetVoxelMeshData();

	TSet<FIntVector> OutBoundList;

	for (int32 Z = -1; Z < MeshData.GridSize.Z + 1; Z++)
	{
		for (int32 Y = -1; Y < MeshData.GridSize.Y + 1; Y++)
		{
			for (int32 X = -1; X < MeshData.GridSize.X + 1; X++)
			{
				const FIntVector GridLocation = FIntVector(X, Y, Z);

				if (ULFPGridLibrary::IsLocationValid(GridLocation, MeshData.GridSize))
				{
					MeshData.DataUpdateList.Add(ULFPGridLibrary::GridLocationToIndex(GridLocation, MeshData.GridSize));
				}
				else
				{
					OutBoundList.Add(GridLocation + PoolVoxelLocation);
				}
			}

		}
	}

	if (VoxelPool) VoxelPool->MarkTrianglesDataListForUpdate(OutBoundList);
}

const FLFPVoxelMeshData& UBaseVoxelMesh::GetVoxelMeshData() const
{
	return VoxelPool ? VoxelPool->PoolVoxelData[PoolIndex] : LocalVoxelData;
}

FLFPVoxelMeshData& UBaseVoxelMesh::GetVoxelMeshData()
{
	return VoxelPool ? VoxelPool->PoolVoxelData[PoolIndex] : LocalVoxelData;
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
					EditMesh.RemoveTriangle(TriangleIndex);
				}

				MeshData.TriangleDataList[DataIndex] = FLFPVoxelTriangleData();
			}

		}, EDynamicMeshChangeType::GeneralEdit, EDynamicMeshAttributeChangeFlags::Unknown, true);

	return;
}

bool UBaseVoxelMesh::IsBlockVisible(const FIntVector GridLocation) const
{
	const FLFPVoxelMeshData& MeshData = GetVoxelMeshData();

	if (ULFPGridLibrary::IsLocationValid(GridLocation, MeshData.GridSize))
	{
		return MeshData.GridData[ULFPGridLibrary::GridLocationToIndex(GridLocation, GetVoxelMeshData().GridSize)].IsVisible;
	}
	else if (VoxelPool) // If connected to voxel pool than check location on it
	{
		return VoxelPool->IsBlockVisible(GridLocation + PoolVoxelLocation);
	}

	return false;
}

