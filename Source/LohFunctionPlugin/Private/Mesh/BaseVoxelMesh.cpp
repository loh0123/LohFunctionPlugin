// Copyright by Loh Zhi Kang


#include "Mesh/BaseVoxelMesh.h"
#include "./Math/LFPGridLibrary.h"
#include "TargetInterfaces/MaterialProvider.h" //FComponentMaterialSet
#include "GeometryCore/Public/DynamicMesh/MeshNormals.h"
#include "GeometryCore/Public/DynamicMesh/MeshTangents.h"
#include "Container/LFPVoxelData.h"
#include "Runtime/Core/Public/Async/ParallelFor.h"

DEFINE_LOG_CATEGORY(BaseVoxelMesh);

DECLARE_STATS_GROUP(TEXT("HexagonVoxelMesh Performance Counter"), STATGROUP_VoxelMesh, STATCAT_Advanced);

DECLARE_CYCLE_STAT(TEXT("MeshUpdateTrianglesMeshCounter"), STAT_MeshUpdateTrianglesMeshCounter, STATGROUP_VoxelMesh);

using namespace UE::Geometry;

UBaseVoxelMesh::UBaseVoxelMesh(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	return;
}

void UBaseVoxelMesh::SetupMesh(ULFPVoxelData* NewVoxelData, const int32 NewChuckIndex)
{
	if (!NewVoxelData || !NewVoxelData->IsChuckIndexValid(NewChuckIndex)) return;

	if (VoxelData) VoxelData->DisconnectEvent(ChuckIndex);

	Reset();

	VoxelData = NewVoxelData;
	ChuckIndex = NewChuckIndex;
	SectionTriangleList.Reset();

	VerticesList.Empty();

	VertexSize = FIntVector::NoneValue;

	TriangleDataList.Empty();
	TriangleDataList.SetNum(NewVoxelData->GetChuckVoxelLength());

	DataUpdateList.Empty(NewVoxelData->GetChuckVoxelLength());
	DataUpdateList.Reserve(NewVoxelData->GetChuckVoxelLength());

	SectionTriangleList.SetNum(NewVoxelData->GetSectionCount());

	for (int32 TriIndex = 0; TriIndex < NewVoxelData->GetChuckVoxelLength(); TriIndex++)
	{
		DataUpdateList.Add(TriIndex);
	}

	NewVoxelData->GetPoolAttribute(NewChuckIndex, ChuckGridLocation, StartVoxelLocation, MeshSize, VoxelGridSize);

	EditMesh([&](FDynamicMesh3& EditMesh)
		{
			EditMesh.Attributes()->SetNumUVLayers(8);
			EditMesh.Attributes()->EnableMaterialID();
			EditMesh.Attributes()->EnableTangents();

		}, EDynamicMeshChangeType::GeneralEdit, EDynamicMeshAttributeChangeFlags::Unknown, false);

	if (NewVoxelData->IsChuckInitialized(NewChuckIndex) == false) NewVoxelData->InitializeChuck(NewChuckIndex);

	NewVoxelData->MarkChuckForUpdate(NewChuckIndex);

	return;
}

void UBaseVoxelMesh::MarkTrianglesDataForUpdate(const int32 VoxelIndex)
{
	DataUpdateList.Add(VoxelIndex);

	VoxelData->MarkChuckForUpdate(ChuckIndex);

	return;
}

int32 UBaseVoxelMesh::GetVoxelSectionCount() const
{
	return VoxelData ? VoxelData->GetSectionCount() : INDEX_NONE;
}

bool UBaseVoxelMesh::isVoxelDataValid() const
{
	return VoxelData != nullptr;
}


void UBaseVoxelMesh::UpdateTriangles(const TArray<FLFPVoxelTriangleUpdateData>& UpdateDataList)
{
	TSet<int32> SectionUpdateList;

	if (DataUpdateList.Num() > 0)
	EditMesh([&](FDynamicMesh3& EditMesh)
		{
			SCOPE_CYCLE_COUNTER(STAT_MeshUpdateTrianglesMeshCounter);

			TObjectPtr<FDynamicMeshMaterialAttribute> MaterialIDs = EditMesh.Attributes()->GetMaterialID();

			for (int32 DataIndex : DataUpdateList)
			{
				for (int32 TriangleIndex : TriangleDataList[DataIndex].MeshTriangleIndex)
				{
					int MatIdx;
					MaterialIDs->GetValue(TriangleIndex, &MatIdx);

					SectionTriangleList[MatIdx].TriangleIndexList.Remove(TriangleIndex);

					EditMesh.RemoveTriangle(TriangleIndex);
				}

				TriangleDataList[DataIndex].MeshTriangleIndex.Empty();
			}

			if (UpdateDataList.Num() == 0) return;

			TArray<TObjectPtr<FDynamicMeshUVOverlay>> UVOverlayList;

			UVOverlayList.SetNum(8);

			for (int32 UVLayerID = 0; UVLayerID < 8; UVLayerID++)
			{
				UVOverlayList[UVLayerID] = EditMesh.Attributes()->GetUVLayer(UVLayerID);
			}

			int32 GroupID = 0;

			const TArray<FLFPVoxelAttribute>& VoxelElementDataList = VoxelData->GetVoxelData(ChuckIndex);

			for (auto& UpdateData : UpdateDataList)
			{
				if (UpdateData.GridIndex == INDEX_NONE) continue;

				SectionUpdateList.Add(UpdateData.MaterialID);

				TriangleDataList[UpdateData.GridIndex].MeshTriangleIndex.Reserve(UpdateData.NewTriangleList.Num());

				for (int32 TriangleID = 0; TriangleID < UpdateData.NewTriangleList.Num(); TriangleID++)
				{
					FIntVector TriVertexIndex;

					TriVertexIndex.X = EditMesh.AppendVertex(VerticesList[UpdateData.NewTriangleList[TriangleID].X]);
					TriVertexIndex.Y = EditMesh.AppendVertex(VerticesList[UpdateData.NewTriangleList[TriangleID].Y]);
					TriVertexIndex.Z = EditMesh.AppendVertex(VerticesList[UpdateData.NewTriangleList[TriangleID].Z]);

					const int32 TriIndex = EditMesh.AppendTriangle(TriVertexIndex, UpdateData.NewTriangleGroupList[TriangleID]);

					SectionTriangleList[UpdateData.MaterialID].TriangleIndexList.Add(TriIndex);

					TriangleDataList[UpdateData.GridIndex].MeshTriangleIndex.Add(TriIndex);

					const int32 UVIndex = TriangleID * 3;

					int Elem0 = UVOverlayList[0]->AppendElement(UpdateData.NewUVList[UVIndex]);
					int Elem1 = UVOverlayList[0]->AppendElement(UpdateData.NewUVList[UVIndex + 1]);
					int Elem2 = UVOverlayList[0]->AppendElement(UpdateData.NewUVList[UVIndex + 2]);
					UVOverlayList[0]->SetTriangle(TriIndex, FIndex3i(Elem0, Elem1, Elem2), true);

					for (int32 CustomDataUV = 1; CustomDataUV < FMath::Min(VoxelElementDataList[UpdateData.GridIndex].CustomData.Num() + 1, 8); CustomDataUV++)
					{
						Elem0 = UVOverlayList[CustomDataUV]->AppendElement(FVector2f(VoxelElementDataList[UpdateData.GridIndex].CustomData[CustomDataUV - 1]));
						Elem1 = UVOverlayList[CustomDataUV]->AppendElement(FVector2f(VoxelElementDataList[UpdateData.GridIndex].CustomData[CustomDataUV - 1]));
						Elem2 = UVOverlayList[CustomDataUV]->AppendElement(FVector2f(VoxelElementDataList[UpdateData.GridIndex].CustomData[CustomDataUV - 1]));
						UVOverlayList[CustomDataUV]->SetTriangle(TriIndex, FIndex3i(Elem0, Elem1, Elem2), true);
					}

					MaterialIDs->SetValue(TriIndex, UpdateData.MaterialID);
				}
			}

			FMeshNormals::InitializeMeshToPerTriangleNormals(&EditMesh);

			if (!SectionUpdateList.IsEmpty()) OnVoxelSectionUpdate.Broadcast(SectionUpdateList);

		}, EDynamicMeshChangeType::GeneralEdit, EDynamicMeshAttributeChangeFlags::Unknown, false);

	DataUpdateList.Empty();

	return;
}

bool UBaseVoxelMesh::IsBlockVisible(const FIntVector GridLocation, const int32 SelfMaterialID) const
{
	return VoxelData->GetVoxelData(GridLocation + StartVoxelLocation).IsVisible ? VoxelData->GetVoxelData(GridLocation + StartVoxelLocation).MaterialID == SelfMaterialID : false;
}

