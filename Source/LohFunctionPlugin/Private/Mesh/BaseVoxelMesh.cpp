// Copyright by Loh Zhi Kang


#include "Mesh/BaseVoxelMesh.h"
#include "./Math/LFPGridLibrary.h"
#include "TargetInterfaces/MaterialProvider.h" //FComponentMaterialSet
#include "Container/LFPVoxelData.h"
#include "Runtime/Core/Public/Async/ParallelFor.h"

DEFINE_LOG_CATEGORY(BaseVoxelMesh);

void UBaseVoxelMesh::SetupMesh(ULFPVoxelData* NewVoxelData, const int32 NewChuckIndex)
{
	if (!NewVoxelData || !NewVoxelData->IsChuckIndexValid(NewChuckIndex)) return;

	if (VoxelData) VoxelData->DisconnectEvent(ChuckIndex);

	Reset();

	VoxelData = NewVoxelData;
	ChuckIndex = NewChuckIndex;

	VerticesList.Empty();

	VertexSize = FIntVector::NoneValue;

	TriangleDataList.Empty();
	TriangleDataList.SetNum(NewVoxelData->GetChuckVoxelLength());

	DataUpdateList.Empty(NewVoxelData->GetChuckVoxelLength());
	DataUpdateList.Reserve(NewVoxelData->GetChuckVoxelLength());

	for (int32 TriIndex = 0; TriIndex < NewVoxelData->GetChuckVoxelLength(); TriIndex++)
	{
		DataUpdateList.Add(TriIndex);
	}

	NewVoxelData->GetPoolAttribute(NewChuckIndex, ChuckGridLocation, StartVoxelLocation, MeshSize, VoxelGridSize);

	NewVoxelData->InitializeChuck(NewChuckIndex);

	return;
}

void UBaseVoxelMesh::MarkTrianglesDataForUpdate(const int32 VoxelIndex)
{
	DataUpdateList.Add(VoxelIndex);

	VoxelData->MarkChuckForUpdate(ChuckIndex);

	return;
}


void UBaseVoxelMesh::UpdateTriangles()
{
	if (DataUpdateList.Num() > 0)
		EditMesh([&](FDynamicMesh3& EditMesh)
		{
			for (int32 DataIndex : DataUpdateList)
			{
				for (int32 TriangleIndex : TriangleDataList[DataIndex].MeshTriangleIndex)
				{
					EditMesh.RemoveTriangle(TriangleIndex);
				}

				TriangleDataList[DataIndex] = FLFPVoxelTriangleData();
			}

		}, EDynamicMeshChangeType::GeneralEdit, EDynamicMeshAttributeChangeFlags::Unknown, true);

	return;
}

bool UBaseVoxelMesh::IsBlockVisible(const FIntVector GridLocation, const int32 SelfMaterialID) const
{
	return VoxelData->GetVoxelData(GridLocation + StartVoxelLocation).IsVisible ? VoxelData->GetVoxelData(GridLocation + StartVoxelLocation).MaterialID == SelfMaterialID : false;
}

