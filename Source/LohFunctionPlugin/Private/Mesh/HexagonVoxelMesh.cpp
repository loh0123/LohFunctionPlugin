// Copyright by Loh Zhi Kang


#include "Mesh/HexagonVoxelMesh.h"
#include "./Math/LFPGridLibrary.h"
#include "GeometryCore/Public/DynamicMesh/MeshNormals.h"
#include "GeometryCore/Public/DynamicMesh/MeshTangents.h"
#include "DynamicMesh/Public/GroupTopology.h"
#include "DynamicMesh/Public/Operations/MeshBevel.h"
#include "Mesh/BaseVoxelPool.h"


using namespace UE::Geometry;

void UHexagonVoxelMesh::SetupPool(UBaseVoxelPool* NewVoxelPool, const FIntVector NewPoolLocation, const int32 NewPoolIndex)
{
	Super::SetupPool(NewVoxelPool, NewPoolLocation, NewPoolIndex);

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
}

void UHexagonVoxelMesh::SetupMesh(const FVector MeshSize, const FIntVector GridSize, const TSet<FName>& IgnoreNameList, const TArray<FLFPVoxelGridData>& GridData)
{
	Super::SetupMesh(MeshSize, GridSize, IgnoreNameList, GridData);

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

void UHexagonVoxelMesh::SetVoxelGridData(const FIntVector GridLocation, const FLFPVoxelGridData& GridData, const bool bUpdateMesh)
{
	FLFPVoxelMeshData& MeshData = GetVoxelMeshData();

	if (!ULFPGridLibrary::IsLocationValid(GridLocation, MeshData.GridSize)) return;

	Super::SetVoxelGridData(GridLocation, GridData, bUpdateMesh);

	// Find Neighbour On GridLocation
	TArray<FIntVector> UpdateList;
	FindBlockNeighbour(GridLocation, UpdateList);
	/////////////////////////////////

	UpdateList.Add(GridLocation); // Add this location to be update too !!!

	// Mark Neighbour Cache To Be Clean Up
	MarkTrianglesDataListForUpdate(TSet(UpdateList));

	// Check If Update Mesh Is Needed
	if (bUpdateMesh) UpdateMesh();

	return;
}

void UHexagonVoxelMesh::SetVoxelGridDataList(const TArray<FIntVector>& GridLocationList, const TArray<FLFPVoxelGridData>& GridData, const bool bUpdateMesh)
{
	FLFPVoxelMeshData& MeshData = GetVoxelMeshData();

	Super::SetVoxelGridDataList(GridLocationList, GridData, bUpdateMesh);

	// Collect all update location //////////////////////////////////////////////////
	TArray<FIntVector> UpdateList;
	TSet<FIntVector> TotalUpdateList;

	for (const FIntVector& LoopVector : GridLocationList)
	{
		if (!ULFPGridLibrary::IsLocationValid(LoopVector, MeshData.GridSize)) continue;

		FindBlockNeighbour(LoopVector, UpdateList);

		TotalUpdateList.Append(UpdateList);

		TotalUpdateList.Add(LoopVector);
	}

	// Mark location to be clean up
	MarkTrianglesDataListForUpdate(TotalUpdateList);
	///////////////////////////////////////////////////////////////////////////////////

	// Check if update mesh is needed
	if (bUpdateMesh) UpdateMesh();

	return;
}

void UHexagonVoxelMesh::SetAllVoxelGridData(const FLFPVoxelGridData& GridData, const bool bUpdateMesh)
{
	FLFPVoxelMeshData& MeshData = GetVoxelMeshData();

	TArray<FIntVector> GridLocationList;
	TArray<FLFPVoxelGridData> GridDataList;

	GridLocationList.Reserve(MeshData.MaxIndex);

	GridDataList.Init(GridData, MeshData.MaxIndex);

	for (int32 Index = 0; Index < MeshData.MaxIndex; Index++)
	{
		GridLocationList.Add(ULFPGridLibrary::IndexToGridLocation(Index, MeshData.GridSize));
	}

	SetVoxelGridDataList(GridLocationList, GridDataList, bUpdateMesh);

	return;
}

void UHexagonVoxelMesh::SetVoxelGridAreaData(const int32 OriginGridIndex, const FIntVector Range, const FLFPVoxelGridData& GridData, const bool bUpdateMesh)
{
	FLFPVoxelMeshData& MeshData = GetVoxelMeshData();

	TArray<FIntVector> GridLocationList;
	TArray<FLFPVoxelGridData> GridDataList;

	const FIntVector RealSize = (Range * 2) + FIntVector(1);

	GridLocationList.Reserve(RealSize.X * RealSize.Y * RealSize.Z);

	for (int32 Z = -Range.Z; Z <= Range.Z; Z++)
	{
		for (int32 Y = -Range.Y; Y <= Range.Y; Y++)
		{
			for (int32 X = -Range.X; X <= Range.X; X++)
			{
				const FIntVector TargetLoc = FIntVector(X, Y, Z) + ULFPGridLibrary::IndexToGridLocation(OriginGridIndex, MeshData.GridSize);

				GridLocationList.Add(TargetLoc);
			}
		}
	}

	GridDataList.Init(GridData, GridLocationList.Num());

	SetVoxelGridDataList(GridLocationList, GridDataList, bUpdateMesh);

	return;
}

void UHexagonVoxelMesh::UpdateVertices()
{
	FLFPVoxelMeshData& MeshData = GetVoxelMeshData();

	TArray<FVector> MeshVertex;

	const TArray<FVector> PointList = {
		FVector(0							,MeshData.MeshSize.Y * 0.5	,0),
		FVector(MeshData.MeshSize.X * 0.25	,0							,0),
		FVector(MeshData.MeshSize.X * 0.75	,0							,0),
		FVector(MeshData.MeshSize.X			,MeshData.MeshSize.Y * 0.5	,0),
	};

	MeshData.VertexSize = FIntVector((MeshData.GridSize.X * 2) + 2, MeshData.GridSize.Y + 1, MeshData.GridSize.Z * 2);

	MeshVertex.Reserve(MeshData.VertexSize.X * MeshData.VertexSize.Y * MeshData.VertexSize.Z);

	for (int32 Z = 0; Z < MeshData.VertexSize.Z; Z++)
	{
		for (int32 Y = 0; Y < MeshData.VertexSize.Y; Y++)
		{
			for (int32 X = 0; X < MeshData.VertexSize.X; X++)
			{
				const FVector CurrentHexaPos = (FVector(X / 4, Y, Z / 2) * (MeshData.MeshSize + FVector(MeshData.MeshSize.X * 0.5, 0, 0)) + FVector(0, 0, Z % 2 == 1 ? MeshData.MeshSize.Z : 0));

				MeshVertex.Add(PointList[X % 4] + CurrentHexaPos);
			}
		}
	}

	if (MeshVertex.Num() == 0) return; // Stop If No Vertex To Be Added

	EditMesh([&](FDynamicMesh3& EditMesh)
	{
		for (FVector& Position : MeshVertex)
		{
			int32 NewVertexIndex = EditMesh.AppendVertex(Position);
		}

	}, EDynamicMeshChangeType::GeneralEdit, EDynamicMeshAttributeChangeFlags::Unknown, false);

	return;
}

void UHexagonVoxelMesh::UpdateTriangles()
{
	Super::UpdateTriangles();

	FLFPVoxelMeshData& MeshData = GetVoxelMeshData();

	if (MeshData.DataUpdateList.Num() == 0) return; // no need to update !!!

	TArray<FLFPVoxelTriangleUpdateData> UpdateDataList;

	TArray<int32> LocalVerticesIndex;

	TArray<FIntVector> LocalNeighbourList;

	int32 GroupID = 0;

	for (const int32 GridIndex : MeshData.DataUpdateList)
	{
		if (!IsBlockVisible(GridIndex)) continue; // Check block is visible

		const FIntVector GridLocation = ULFPGridLibrary::IndexToGridLocation(GridIndex, MeshData.GridSize);

		FindBlockVertices(GridLocation, LocalVerticesIndex);

		FindBlockNeighbour(GridLocation, LocalNeighbourList);

		UpdateDataList.Add(FLFPVoxelTriangleUpdateData());

		UpdateDataList.Last(0).GridIndex = GridIndex;

		for (int32 LoopIndex = 0; LoopIndex < 8; LoopIndex++)
		{
			if (ULFPGridLibrary::IsLocationValid(LocalNeighbourList[LoopIndex], MeshData.GridSize))
			{
				if (IsBlockVisible(ULFPGridLibrary::GridLocationToIndex(LocalNeighbourList[LoopIndex], MeshData.GridSize))) continue;
			}
			else
			{
				if (VoxelPool && VoxelPool->IsBlockVisible(LocalNeighbourList[LoopIndex] + PoolVoxelLocation)) continue;
			}

			if(LoopIndex >= 6) 
				AddHexagonRoof(LocalVerticesIndex, UpdateDataList.Last(0), LoopIndex - 6);
			else 
				AddHexagonWall(LocalVerticesIndex, UpdateDataList.Last(0), LoopIndex);
		}
	}

	MeshData.DataUpdateList.Empty(MeshData.MaxIndex);

	if (UpdateDataList.Num() > 0)
	{
		EditMesh([&](FDynamicMesh3& EditMesh)
		{
			TArray<FDynamicMeshUVOverlay*> UVOverlayList;
	
			UVOverlayList.SetNum(8);

			for (int32 UVLayerID = 0; UVLayerID < 8; UVLayerID++)
			{
				UVOverlayList[UVLayerID] = EditMesh.Attributes()->GetUVLayer(UVLayerID);
			}
	
			int32 GroupID = 0;

			FDynamicMeshMaterialAttribute* MaterialIDs = EditMesh.Attributes()->GetMaterialID();
	
			for (auto& UpdateData : UpdateDataList)
			{
				MeshData.TriangleDataList[UpdateData.GridIndex].MeshTriangleIndex.Reserve(UpdateData.NewTriangleList.Num());
			
				for (int32 TriangleID = 0; TriangleID < UpdateData.NewTriangleList.Num(); TriangleID++)
				{
					const int32 TriIndex = EditMesh.AppendTriangle(UpdateData.NewTriangleList[TriangleID], UpdateData.NewTriangleGroupList[TriangleID]);
			
					MeshData.TriangleDataList[UpdateData.GridIndex].MeshTriangleIndex.Add(TriIndex);
			
					const int32 UVIndex = TriangleID * 3;
					
					int32 Elem0 = UVOverlayList[0]->AppendElement(UpdateData.NewUVList[UVIndex]);
					int32 Elem1 = UVOverlayList[0]->AppendElement(UpdateData.NewUVList[UVIndex + 1]);
					int32 Elem2 = UVOverlayList[0]->AppendElement(UpdateData.NewUVList[UVIndex + 2]);
					UVOverlayList[0]->SetTriangle(TriIndex, FIndex3i(Elem0, Elem1, Elem2), true);
					
					for (int32 CustomDataUV = 1; CustomDataUV < FMath::Min(MeshData.GridData[UpdateData.GridIndex].CustomData.Num() + 1,8); CustomDataUV++)
					{
						Elem0 = UVOverlayList[CustomDataUV]->AppendElement(FVector2f(MeshData.GridData[UpdateData.GridIndex].CustomData[CustomDataUV - 1]));
						Elem1 = UVOverlayList[CustomDataUV]->AppendElement(FVector2f(MeshData.GridData[UpdateData.GridIndex].CustomData[CustomDataUV - 1]));
						Elem2 = UVOverlayList[CustomDataUV]->AppendElement(FVector2f(MeshData.GridData[UpdateData.GridIndex].CustomData[CustomDataUV - 1]));
						UVOverlayList[CustomDataUV]->SetTriangle(TriIndex, FIndex3i(Elem0, Elem1, Elem2), true);
					}
			
					MaterialIDs->SetValue(TriIndex, MeshData.GridData[UpdateData.GridIndex].MaterialID);
				}
			}

			FMeshNormals::InitializeMeshToPerTriangleNormals(&EditMesh);
	
		}, EDynamicMeshChangeType::MeshChange, EDynamicMeshAttributeChangeFlags::Unknown, true);
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
	FLFPVoxelMeshData& MeshData = GetVoxelMeshData();

	TArray<FIntVector> RuleChecker;

	NeighbourLocationList.SetNum(8);

	if (GridLocation.X % 2 == 1)
	{
		RuleChecker = {
			FIntVector(-1,0,0),
			FIntVector(0,-1,0),
			FIntVector(1,0,0),
			FIntVector(1,1,0),
			FIntVector(0,1,0),
			FIntVector(-1,1,0),
			FIntVector(0,0,1),
			FIntVector(0,0,-1),
		};
	}
	else
	{
		RuleChecker = {
			FIntVector(-1,-1,0),
			FIntVector(0,-1,0),
			FIntVector(1,-1,0),
			FIntVector(1,0,0),
			FIntVector(0,1,0),
			FIntVector(-1,0,0),
			FIntVector(0,0,1),
			FIntVector(0,0,-1),
		};
	}

	for (int32 Index = 0; Index < 8; Index++)
	{
		NeighbourLocationList[Index] = RuleChecker[Index] + GridLocation;
	}

	return;
}

void UHexagonVoxelMesh::FindBlockVertices(const FIntVector GridLocation, TArray<int32>& VerticesIndexList)
{
	FLFPVoxelMeshData& MeshData = GetVoxelMeshData();

	VerticesIndexList.SetNum(12);

	const bool IsSecond = GridLocation.X % 2 == 1;

	const int32 StartVertexIndex = (GridLocation.Z * (MeshData.VertexSize.X * MeshData.VertexSize.Y * 2)) + (GridLocation.Y * MeshData.VertexSize.X) + (((GridLocation.X / 2) * 4) + (GridLocation.X % 2 == 1 ? 2 + MeshData.VertexSize.X : 0));

	if (IsSecond)
	{
		VerticesIndexList[0] = StartVertexIndex;
		VerticesIndexList[1] = StartVertexIndex + 1 - MeshData.VertexSize.X;
		VerticesIndexList[2] = StartVertexIndex + 2 - MeshData.VertexSize.X;
		VerticesIndexList[3] = StartVertexIndex + 3;
		VerticesIndexList[4] = StartVertexIndex + 2;
		VerticesIndexList[5] = StartVertexIndex + 1;

		VerticesIndexList[6] =  (MeshData.VertexSize.X * MeshData.VertexSize.Y) + StartVertexIndex;
		VerticesIndexList[7] =  (MeshData.VertexSize.X * MeshData.VertexSize.Y) + StartVertexIndex + 1 - MeshData.VertexSize.X;
		VerticesIndexList[8] =  (MeshData.VertexSize.X * MeshData.VertexSize.Y) + StartVertexIndex + 2 - MeshData.VertexSize.X;
		VerticesIndexList[9] =  (MeshData.VertexSize.X * MeshData.VertexSize.Y) + StartVertexIndex + 3;
		VerticesIndexList[10] = (MeshData.VertexSize.X * MeshData.VertexSize.Y) + StartVertexIndex + 2;
		VerticesIndexList[11] = (MeshData.VertexSize.X * MeshData.VertexSize.Y) + StartVertexIndex + 1;
	}
	else
	{
		VerticesIndexList[0] = StartVertexIndex;
		VerticesIndexList[1] = StartVertexIndex + 1;
		VerticesIndexList[2] = StartVertexIndex + 2;
		VerticesIndexList[3] = StartVertexIndex + 3;
		VerticesIndexList[4] = StartVertexIndex + 2 + MeshData.VertexSize.X;
		VerticesIndexList[5] = StartVertexIndex + 1 + MeshData.VertexSize.X;

		VerticesIndexList[6] =  (MeshData.VertexSize.X * MeshData.VertexSize.Y) + StartVertexIndex;
		VerticesIndexList[7] =  (MeshData.VertexSize.X * MeshData.VertexSize.Y) + StartVertexIndex + 1;
		VerticesIndexList[8] =  (MeshData.VertexSize.X * MeshData.VertexSize.Y) + StartVertexIndex + 2;
		VerticesIndexList[9] =  (MeshData.VertexSize.X * MeshData.VertexSize.Y) + StartVertexIndex + 3;
		VerticesIndexList[10] = (MeshData.VertexSize.X * MeshData.VertexSize.Y) + StartVertexIndex + 2 + MeshData.VertexSize.X;
		VerticesIndexList[11] = (MeshData.VertexSize.X * MeshData.VertexSize.Y) + StartVertexIndex + 1 + MeshData.VertexSize.X;
	}

	return;
}