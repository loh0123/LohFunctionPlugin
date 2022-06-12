// Copyright by Loh Zhi Kang


#include "Mesh/HexagonVoxelMesh.h"
#include "./Math/LFPGridLibrary.h"
#include "GeometryCore/Public/DynamicMesh/MeshNormals.h"
#include "GeometryCore/Public/DynamicMesh/MeshTangents.h"
#include "DynamicMesh/Public/GroupTopology.h"
#include "Container/LFPVoxelData.h"
#include "Runtime/Core/Public/Async/ParallelFor.h"


DECLARE_STATS_GROUP(TEXT("HexagonVoxelMesh Performance Counter"), STATGROUP_HexagonVoxelMesh, STATCAT_Advanced);

DECLARE_CYCLE_STAT(TEXT("MeshUpdateTrianglesCounter"), STAT_MeshUpdateTrianglesCounter, STATGROUP_HexagonVoxelMesh);

DECLARE_CYCLE_STAT(TEXT("MeshUpdateTrianglesDataCounter"), STAT_MeshUpdateTrianglesDataCounter, STATGROUP_HexagonVoxelMesh);

DECLARE_CYCLE_STAT(TEXT("MeshUpdateTrianglesMeshCounter"), STAT_MeshUpdateTrianglesMeshCounter, STATGROUP_HexagonVoxelMesh);

DECLARE_CYCLE_STAT(TEXT("MeshVertexUpdateCounter"), STAT_MeshVertexUpdateCounter, STATGROUP_HexagonVoxelMesh);

DECLARE_CYCLE_STAT(TEXT("MeshOperationCounter"), STAT_MeshOperationCounter, STATGROUP_HexagonVoxelMesh);


using namespace UE::Geometry;

void UHexagonVoxelMesh::SetupMesh(ULFPVoxelData* NewVoxelData, const int32 NewChuckIndex)
{
	if (NewChuckIndex < 0 || NewChuckIndex >= NewVoxelData->GetPoolLength()) return;

	NewVoxelData->GetVoxelDataUpdateEvent(NewChuckIndex).BindUFunction(this, FName("MarkVoxelDataForUpdate"));

	Super::SetupMesh(NewVoxelData, NewChuckIndex);

	EditMesh([&](FDynamicMesh3& EditMesh)
		{
			EditMesh.Attributes()->SetNumUVLayers(8);

			if (!EditMesh.Attributes()->HasMaterialID())
			{
				EditMesh.Attributes()->EnableMaterialID();
			}

			if (EditMesh.Attributes()->HasTangentSpace() == false)
			{
				EditMesh.Attributes()->EnableTangents();
			}

		}, EDynamicMeshChangeType::GeneralEdit, EDynamicMeshAttributeChangeFlags::Unknown, false);

	UpdateMesh();

	return;
}

void UHexagonVoxelMesh::MarkVoxelDataForUpdate(const int32 VoxelIndex)
{
	FIntVector VoxelLocation = ULFPGridLibrary::IndexToGridLocation(VoxelIndex, VoxelGridSize);

	// Find Neighbour On GridLocation
	TArray<FIntVector> UpdateList;
	FindBlockNeighbour(VoxelLocation, UpdateList);
	/////////////////////////////////

	MarkTrianglesDataForUpdate(VoxelIndex);

	for (const FIntVector& UpdateLocation : UpdateList)
	{
		if (ULFPGridLibrary::IsLocationValid(UpdateLocation, VoxelGridSize))
		{
			MarkTrianglesDataForUpdate(ULFPGridLibrary::GridLocationToIndex(UpdateLocation, VoxelGridSize));
		}
		else
		{
			FIntVector VoxelGridLocation = UpdateLocation + StartVoxelLocation;

			int32 TargetChuckIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X / VoxelGridSize.X, VoxelGridLocation.Y / VoxelGridSize.Y, VoxelGridLocation.Z / VoxelGridSize.Z), VoxelData->GetPoolGridSize());
			int32 VoxelChuckIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X % VoxelGridSize.X, VoxelGridLocation.Y % VoxelGridSize.Y, VoxelGridLocation.Z % VoxelGridSize.Z), VoxelGridSize);

			if (VoxelData->IsChuckIndexValid(TargetChuckIndex) && VoxelChuckIndex >= 0 && VoxelChuckIndex < VoxelData->GetChuckVoxelLength())
			{
				VoxelData->GetVoxelMeshUpdateEvent(TargetChuckIndex).ExecuteIfBound(VoxelChuckIndex);
			}
		}
	}

	return;
}

void UHexagonVoxelMesh::UpdateMesh()
{
	if (VertexSize.GetMax() == INDEX_NONE) UpdateVertices();  
	
	UpdateTriangles();

	return;
}

void UHexagonVoxelMesh::UpdateVertices()
{
	SCOPE_CYCLE_COUNTER(STAT_MeshVertexUpdateCounter);

	//TArray<FVector> MeshVertex;

	const TArray<FVector> PointList = {
		FVector(0					,MeshSize.Y * 0.5	,0),
		FVector(MeshSize.X * 0.25	,0							,0),
		FVector(MeshSize.X * 0.75	,0							,0),
		FVector(MeshSize.X			,MeshSize.Y * 0.5	,0),
	};

	VertexSize = FIntVector((VoxelGridSize.X * 2) + 2, VoxelGridSize.Y + 1, VoxelGridSize.Z * 2);

	const int32 VertexIndexSize = VertexSize.X * VertexSize.Y * VertexSize.Z;

	VerticesList.SetNum(VertexIndexSize);

	ParallelFor(VertexIndexSize, [&](const int32 LoopIndex) {
		const FIntVector VertexLocation = ULFPGridLibrary::IndexToGridLocation(LoopIndex, VertexSize);
	
		const FVector CurrentHexaPos = (FVector(VertexLocation.X / 4, VertexLocation.Y, VertexLocation.Z / 2) * (MeshSize + FVector(MeshSize.X * 0.5, 0, 0)) + FVector(0, 0, VertexLocation.Z % 2 == 1 ? MeshSize.Z : 0));
	
		VerticesList[LoopIndex] = (PointList[VertexLocation.X % 4] + CurrentHexaPos);
		});

	return;
}

void UHexagonVoxelMesh::UpdateTriangles()
{
	SCOPE_CYCLE_COUNTER(STAT_MeshUpdateTrianglesCounter);

	Super::UpdateTriangles();

	if (DataUpdateList.Num() == 0) return; // no need to update !!!

	TArray<FLFPVoxelTriangleUpdateData> UpdateDataList;

	int32 GroupID = 0;
	
	TArray<int32> DataUpdateListArray = DataUpdateList.Array();
	
	{
		SCOPE_CYCLE_COUNTER(STAT_MeshUpdateTrianglesDataCounter);

		UpdateDataList.SetNum(DataUpdateListArray.Num());

		ParallelFor(DataUpdateListArray.Num(), [&](const int32 LoopIndex) {
			const FIntVector GridLocation = ULFPGridLibrary::IndexToGridLocation(DataUpdateListArray[LoopIndex], VoxelGridSize);

			const int32 SelfMaterialID = VoxelData->GetVoxelData(ChuckIndex, DataUpdateListArray[LoopIndex]).MaterialID;

			if (IsBlockVisible(GridLocation, SelfMaterialID))
			{
				TArray<int32> LocalVerticesIndex;

				TArray<FIntVector> LocalNeighbourList;

				FindBlockVertices(GridLocation, LocalVerticesIndex);

				FindBlockNeighbour(GridLocation, LocalNeighbourList);

				FLFPVoxelTriangleUpdateData UpdateData;

				UpdateData.GridIndex = DataUpdateListArray[LoopIndex];

				for (int32 FaceIndex = 0; FaceIndex < 8; FaceIndex++)
				{
					if (IsBlockVisible(LocalNeighbourList[FaceIndex], SelfMaterialID)) continue;

					if (FaceIndex >= 6)
						AddHexagonRoof(LocalVerticesIndex, UpdateData, FaceIndex - 6);
					else
						AddHexagonWall(LocalVerticesIndex, UpdateData, FaceIndex);
				}

				UpdateDataList[LoopIndex] = UpdateData;
			}
			});
	}

	DataUpdateList.Empty(VoxelData->GetChuckVoxelLength());

	if (UpdateDataList.Num() > 0)
	{
		EditMesh([&](FDynamicMesh3& EditMesh)
		{
			SCOPE_CYCLE_COUNTER(STAT_MeshUpdateTrianglesMeshCounter);
		
			TArray<TObjectPtr<FDynamicMeshUVOverlay>> UVOverlayList;
		
			UVOverlayList.SetNum(8);
		
			for (int32 UVLayerID = 0; UVLayerID < 8; UVLayerID++)
			{
				UVOverlayList[UVLayerID] = EditMesh.Attributes()->GetUVLayer(UVLayerID);
			}
		
			int32 GroupID = 0;
		
			TObjectPtr<FDynamicMeshMaterialAttribute> MaterialIDs = EditMesh.Attributes()->GetMaterialID();
		
			for (auto& UpdateData : UpdateDataList)
			{
				if (UpdateData.GridIndex == INDEX_NONE) continue;
		
				TriangleDataList[UpdateData.GridIndex].MeshTriangleIndex.Reserve(UpdateData.NewTriangleList.Num());
			
				for (int32 TriangleID = 0; TriangleID < UpdateData.NewTriangleList.Num(); TriangleID++)
				{
					FIntVector TriVertexIndex;
		
					TriVertexIndex.X = EditMesh.AppendVertex(VerticesList[UpdateData.NewTriangleList[TriangleID].X]);
					TriVertexIndex.Y = EditMesh.AppendVertex(VerticesList[UpdateData.NewTriangleList[TriangleID].Y]);
					TriVertexIndex.Z = EditMesh.AppendVertex(VerticesList[UpdateData.NewTriangleList[TriangleID].Z]);
		
					const int32 TriIndex = EditMesh.AppendTriangle(TriVertexIndex, UpdateData.NewTriangleGroupList[TriangleID]);
			
					TriangleDataList[UpdateData.GridIndex].MeshTriangleIndex.Add(TriIndex);
			
					const int32 UVIndex = TriangleID * 3;
					
					int32 Elem0 = UVOverlayList[0]->AppendElement(UpdateData.NewUVList[UVIndex]);
					int32 Elem1 = UVOverlayList[0]->AppendElement(UpdateData.NewUVList[UVIndex + 1]);
					int32 Elem2 = UVOverlayList[0]->AppendElement(UpdateData.NewUVList[UVIndex + 2]);
					UVOverlayList[0]->SetTriangle(TriIndex, FIndex3i(Elem0, Elem1, Elem2), true);
					
					for (int32 CustomDataUV = 1; CustomDataUV < FMath::Min(VoxelData->GetVoxelData(ChuckIndex, UpdateData.GridIndex).CustomData.Num() + 1,8); CustomDataUV++)
					{
						Elem0 = UVOverlayList[CustomDataUV]->AppendElement(FVector2f(VoxelData->GetVoxelData(ChuckIndex, UpdateData.GridIndex).CustomData[CustomDataUV - 1]));
						Elem1 = UVOverlayList[CustomDataUV]->AppendElement(FVector2f(VoxelData->GetVoxelData(ChuckIndex, UpdateData.GridIndex).CustomData[CustomDataUV - 1]));
						Elem2 = UVOverlayList[CustomDataUV]->AppendElement(FVector2f(VoxelData->GetVoxelData(ChuckIndex, UpdateData.GridIndex).CustomData[CustomDataUV - 1]));
						UVOverlayList[CustomDataUV]->SetTriangle(TriIndex, FIndex3i(Elem0, Elem1, Elem2), true);
					}
			
					MaterialIDs->SetValue(TriIndex, VoxelData->GetVoxelData(ChuckIndex, UpdateData.GridIndex).MaterialID);
				}
			}
		
			FMeshNormals::InitializeMeshToPerTriangleNormals(&EditMesh);
		
		}, EDynamicMeshChangeType::MeshChange, EDynamicMeshAttributeChangeFlags::Unknown, false);
	}
}

void UHexagonVoxelMesh::AddHexagonWall(const TArray<int32>& VertexIndexList, FLFPVoxelTriangleUpdateData& UpdateData, const int32 ID)
{
	check(ID >= 0 && ID <= 5); // Terminate Unreal If WallID Is Invalid

	double Jump = ID % 2 == 1 ? 0.5 : 0.0;

	UpdateData.NewUVList.Append({
		FVector2f(Jump + 0.5, 0),
		FVector2f(Jump + 0, 0),
		FVector2f(Jump + 0, 0.5),

		FVector2f(Jump + 0.5, 0),
		FVector2f(Jump + 0, 0.5),
		FVector2f(Jump + 0.5, 0.5)
	});

	const int32 Ind01 = ID;
	const int32 Ind02 = ID == 5 ? 0 : ID + 1;
	const int32 Ind03 = ID + 6;
	const int32 Ind04 = ID == 5 ? 6 : ID + 7;

	UpdateData.NewTriangleList.Append({
		FIntVector(VertexIndexList[Ind02], VertexIndexList[Ind01], VertexIndexList[Ind03]),
		FIntVector(VertexIndexList[Ind02], VertexIndexList[Ind03], VertexIndexList[Ind04])
	});

	UpdateData.NewTriangleGroupList.Append({
		ID + 2,
		ID + 2,
	});

	return;
}

void UHexagonVoxelMesh::AddHexagonRoof(const TArray<int32>& VertexIndexList, FLFPVoxelTriangleUpdateData& UpdateData, const int32 ID)
{
	if (ID == 0)
	{
		UpdateData.NewTriangleList.Append({
			FIntVector(VertexIndexList[7], VertexIndexList[6] , VertexIndexList[11]),
			FIntVector(VertexIndexList[7], VertexIndexList[11] , VertexIndexList[10]),
			FIntVector(VertexIndexList[8], VertexIndexList[7], VertexIndexList[10]),
			FIntVector(VertexIndexList[9], VertexIndexList[8] , VertexIndexList[10])
			});

		UpdateData.NewUVList.Append({
			FVector2f(0.125, 1),
			FVector2f(0, 0.75),
			FVector2f(0.125, 0.5),

			FVector2f(0.125, 1),
			FVector2f(0.125, 0.5),
			FVector2f(0.35, 0.5),
			
			FVector2f(0.35, 1),
			FVector2f(0.125, 1),
			FVector2f(0.35, 0.5),
			
			FVector2f(0.5, 0.75),
			FVector2f(0.35, 0.5),
			FVector2f(0.35, 1),
		});
	}
	else
	{
		UpdateData.NewTriangleList.Append({
			FIntVector(VertexIndexList[1], VertexIndexList[5] , VertexIndexList[0]),
			FIntVector(VertexIndexList[1], VertexIndexList[4] , VertexIndexList[5]),
			FIntVector(VertexIndexList[2], VertexIndexList[4], VertexIndexList[1]),
			FIntVector(VertexIndexList[3], VertexIndexList[4] , VertexIndexList[2])
			});

		UpdateData.NewUVList.Append({
			FVector2f(0.625, 1),
			FVector2f(0.625, 0.5),
			FVector2f(0.5, 0.75),

			FVector2f(0.625, 1),
			FVector2f(0.85, 0.5),
			FVector2f(0.625, 0.5),

			FVector2f(0.85, 1),
			FVector2f(0.85, 0.5),
			FVector2f(0.625, 1),

			FVector2f(1, 0.75),
			FVector2f(0.85, 1),
			FVector2f(0.85, 0.5)
		});
	}

	UpdateData.NewTriangleGroupList.Append({
		ID,
		ID,
		ID,
		ID,
	});

	return;
}

void UHexagonVoxelMesh::FindBlockNeighbour(const FIntVector GridLocation, TArray<FIntVector>& NeighbourLocationList)
{
	NeighbourLocationList.SetNum(8);

	if (GridLocation.X % 2 == 1)
	{
		NeighbourLocationList = {
			GridLocation + FIntVector(-1,0,0),
			GridLocation + FIntVector(0,-1,0),
			GridLocation + FIntVector(1,0,0),
			GridLocation + FIntVector(1,1,0),
			GridLocation + FIntVector(0,1,0),
			GridLocation + FIntVector(-1,1,0),
			GridLocation + FIntVector(0,0,1),
			GridLocation + FIntVector(0,0,-1),
		};
	}
	else
	{
		NeighbourLocationList = {
			GridLocation + FIntVector(-1,-1,0),
			GridLocation + FIntVector(0,-1,0),
			GridLocation + FIntVector(1,-1,0),
			GridLocation + FIntVector(1,0,0),
			GridLocation + FIntVector(0,1,0),
			GridLocation + FIntVector(-1,0,0),
			GridLocation + FIntVector(0,0,1),
			GridLocation + FIntVector(0,0,-1),
		};
	}

	return;
}

void UHexagonVoxelMesh::FindBlockVertices(const FIntVector GridLocation, TArray<int32>& VerticesIndexList)
{
	VerticesIndexList.SetNum(12);

	const bool IsSecond = GridLocation.X % 2 == 1;

	const int32 StartVertexIndex = (GridLocation.Z * (VertexSize.X * VertexSize.Y * 2)) + (GridLocation.Y * VertexSize.X) + (((GridLocation.X / 2) * 4) + (GridLocation.X % 2 == 1 ? 2 + VertexSize.X : 0));

	if (IsSecond)
	{
		VerticesIndexList[0] = StartVertexIndex;
		VerticesIndexList[1] = StartVertexIndex + 1 - VertexSize.X;
		VerticesIndexList[2] = StartVertexIndex + 2 - VertexSize.X;
		VerticesIndexList[3] = StartVertexIndex + 3;
		VerticesIndexList[4] = StartVertexIndex + 2;
		VerticesIndexList[5] = StartVertexIndex + 1;

		VerticesIndexList[6] =  (VertexSize.X * VertexSize.Y) + StartVertexIndex;
		VerticesIndexList[7] =  (VertexSize.X * VertexSize.Y) + StartVertexIndex + 1 - VertexSize.X;
		VerticesIndexList[8] =  (VertexSize.X * VertexSize.Y) + StartVertexIndex + 2 - VertexSize.X;
		VerticesIndexList[9] =  (VertexSize.X * VertexSize.Y) + StartVertexIndex + 3;
		VerticesIndexList[10] = (VertexSize.X * VertexSize.Y) + StartVertexIndex + 2;
		VerticesIndexList[11] = (VertexSize.X * VertexSize.Y) + StartVertexIndex + 1;
	}
	else
	{
		VerticesIndexList[0] = StartVertexIndex;
		VerticesIndexList[1] = StartVertexIndex + 1;
		VerticesIndexList[2] = StartVertexIndex + 2;
		VerticesIndexList[3] = StartVertexIndex + 3;
		VerticesIndexList[4] = StartVertexIndex + 2 + VertexSize.X;
		VerticesIndexList[5] = StartVertexIndex + 1 + VertexSize.X;

		VerticesIndexList[6] =  (VertexSize.X * VertexSize.Y) + StartVertexIndex;
		VerticesIndexList[7] =  (VertexSize.X * VertexSize.Y) + StartVertexIndex + 1;
		VerticesIndexList[8] =  (VertexSize.X * VertexSize.Y) + StartVertexIndex + 2;
		VerticesIndexList[9] =  (VertexSize.X * VertexSize.Y) + StartVertexIndex + 3;
		VerticesIndexList[10] = (VertexSize.X * VertexSize.Y) + StartVertexIndex + 2 + VertexSize.X;
		VerticesIndexList[11] = (VertexSize.X * VertexSize.Y) + StartVertexIndex + 1 + VertexSize.X;
	}

	return;
}