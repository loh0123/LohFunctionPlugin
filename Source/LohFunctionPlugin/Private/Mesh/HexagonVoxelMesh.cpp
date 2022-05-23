// Fill out your copyright notice in the Description page of Project Settings.


#include "Mesh/HexagonVoxelMesh.h"
#include "./Math/LFPGridLibrary.h"
#include "GeometryCore/Public/DynamicMesh/MeshNormals.h"
#include "GeometryCore/Public/DynamicMesh/MeshTangents.h"


void UHexagonVoxelMesh::UpdateVertices()
{
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

	}, EDynamicMeshChangeType::MeshVertexChange, EDynamicMeshAttributeChangeFlags::VertexPositions, false);

	return;
}

void UHexagonVoxelMesh::UpdateTriangles()
{
	if (!MeshData.TrianglesNeedUpdate) return; // No Need To Update !!!

	TArray<FLFPVoxelTriangleUpdateData> UpdateDataList;

	TArray<int32> LocalVerticesIndex;

	TArray<int32> LocalNeighbourList;

	for (int32 Z = 0; Z < MeshData.GridSize.Z; Z++)
	{
		for (int32 Y = 0; Y < MeshData.GridSize.Y; Y++)
		{
			for (int32 X = 0; X < MeshData.GridSize.X; X++)
			{
				const int32 GridIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(X, Y, Z), MeshData.GridSize);

				if (!MeshData.TriangleDataList[GridIndex].NeedUpdate) continue; // Check Block Need Update

				if (!IsBlockNeedRender(GridIndex)) continue; // Check Block Is Visible

				FindBlockVertices(FIntVector(X, Y, Z), LocalVerticesIndex);

				FindBlockNeighbour(FIntVector(X, Y, Z), LocalNeighbourList);

				UpdateDataList.Add(FLFPVoxelTriangleUpdateData());

				for (int32 LoopIndex = 0; LoopIndex < 6; LoopIndex++)
				{
					if (IsBlockFaceVisible(GridIndex, LocalNeighbourList[LoopIndex]))
						AddHexagonWall(LocalVerticesIndex, UpdateDataList.Last(0).NewTriangleList, UpdateDataList.Last(0).NewUVList, LoopIndex);
				}

				if (IsBlockFaceVisible(GridIndex, LocalNeighbourList[6])) AddHexagonRoof(LocalVerticesIndex, UpdateDataList.Last(0).NewTriangleList, UpdateDataList.Last(0).NewUVList, 0);
				if (IsBlockFaceVisible(GridIndex, LocalNeighbourList[7])) AddHexagonRoof(LocalVerticesIndex, UpdateDataList.Last(0).NewTriangleList, UpdateDataList.Last(0).NewUVList, 1);
			
				MeshData.TriangleDataList[GridIndex].NeedUpdate = false; // Mark Update As Completed
			}
		}
	}

	if (UpdateDataList.Num() > 0)
	{
		EditMesh([&](FDynamicMesh3& EditMesh)
		{
			for (auto& UpdateData : UpdateDataList)
			{
				MeshData.TriangleDataList[UpdateData.GridIndex].MeshTriangleIndex.Reserve(UpdateData.NewTriangleList.Num());

				for (FIntVector& Triangle : UpdateData.NewTriangleList)
				{
					MeshData.TriangleDataList[UpdateData.GridIndex].MeshTriangleIndex.Add(EditMesh.AppendTriangle(Triangle, 0));
				}

				if (EditMesh.HasAttributes() && 0 < EditMesh.Attributes()->NumUVLayers())
				{
					UE::Geometry::FDynamicMeshUVOverlay* UVOverlay = EditMesh.Attributes()->GetUVLayer(0);
					if (UVOverlay != nullptr)
					{

						for (int32 TriIndex = 0; TriIndex < MeshData.TriangleDataList[UpdateData.GridIndex].MeshTriangleIndex.Num(); TriIndex++)
						{
							const int32 UVIndex = TriIndex * 3;
							const int32 TriangleID = MeshData.TriangleDataList[UpdateData.GridIndex].MeshTriangleIndex[TriIndex];

							int32 Elem0 = UVOverlay->AppendElement(UpdateData.NewUVList[UVIndex]);
							int32 Elem1 = UVOverlay->AppendElement(UpdateData.NewUVList[UVIndex + 1]);
							int32 Elem2 = UVOverlay->AppendElement(UpdateData.NewUVList[UVIndex + 2]);
							UVOverlay->SetTriangle(TriangleID, UE::Geometry::FIndex3i(Elem0, Elem1, Elem2), true);
						}
					}
				}

				UE::Geometry::FMeshNormals::InitializeMeshToPerTriangleNormals(&EditMesh);

				if (EditMesh.Attributes()->HasTangentSpace() == false)
				{
					EditMesh.Attributes()->EnableTangents();
				}

				UE::Geometry::FComputeTangentsOptions TangentOptions;
				TangentOptions.bAveraged = true;

				UE::Geometry::FMeshTangentsd Tangents(&EditMesh);
				Tangents.ComputeTriVertexTangents(
					EditMesh.Attributes()->PrimaryNormals(),
					EditMesh.Attributes()->GetUVLayer(0),
					TangentOptions);
				Tangents.CopyToOverlays(EditMesh);
			}

		}, EDynamicMeshChangeType::GeneralEdit, EDynamicMeshAttributeChangeFlags::Unknown, false);
	}

	MeshData.TrianglesNeedUpdate = false;
}

void UHexagonVoxelMesh::AddHexagonWall(const TArray<int32>& VertexIndexList, TArray<FIntVector>& TrianglesList, TArray<FVector2f>& UVList, const int32 ID)
{
	check(ID >= 0 && ID <= 5); // Terminate Unreal If WallID Is Invalid

	double Jump = ID % 2 == 1 ? 0.5 : 0.0;

	UVList.Append({
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

	TrianglesList.Append({
		FIntVector(VertexIndexList[Ind02], VertexIndexList[Ind01], VertexIndexList[Ind03]),
		FIntVector(VertexIndexList[Ind02], VertexIndexList[Ind03], VertexIndexList[Ind04])
		});

	return;
}

void UHexagonVoxelMesh::AddHexagonRoof(const TArray<int32>& VertexIndexList, TArray<FIntVector>& TrianglesList, TArray<FVector2f>& UVList, const int32 ID)
{
	FGeometryScriptUVTriangle UVData01;
	FGeometryScriptUVTriangle UVData02;
	FGeometryScriptUVTriangle UVData03;
	FGeometryScriptUVTriangle UVData04;

	if (ID == 0)
	{
		TrianglesList.Append({
			FIntVector(VertexIndexList[7], VertexIndexList[6] , VertexIndexList[11]),
			FIntVector(VertexIndexList[7], VertexIndexList[11] , VertexIndexList[10]),
			FIntVector(VertexIndexList[8], VertexIndexList[7], VertexIndexList[10]),
			FIntVector(VertexIndexList[9], VertexIndexList[8] , VertexIndexList[10])
			});

		UVList.Append({
			FVector2f(0.125, 1),
			FVector2f(0.125, 0.5),
			FVector2f(0, 0.75),

			FVector2f(0.125, 1),
			FVector2f(0.35, 0.5),
			FVector2f(0.125, 0.5),

			FVector2f(0.35, 1),
			FVector2f(0.35, 0.5),
			FVector2f(0.125, 1),

			FVector2f(0.5, 0.75),
			FVector2f(0.35, 1),
			FVector2f(0.35, 0.5)
		});
	}
	else
	{
		TrianglesList.Append({
			FIntVector(VertexIndexList[1], VertexIndexList[5] , VertexIndexList[0]),
			FIntVector(VertexIndexList[1], VertexIndexList[4] , VertexIndexList[5]),
			FIntVector(VertexIndexList[2], VertexIndexList[4], VertexIndexList[1]),
			FIntVector(VertexIndexList[3], VertexIndexList[4] , VertexIndexList[2])
			});

		UVList.Append({
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

	return;
}

void UHexagonVoxelMesh::MarkTrianglesDataForUpdate(const int32 GridIndex)
{
	check(GridIndex < MeshData.MaxIndex && GridIndex >= 0);

	EditMesh([&](FDynamicMesh3& EditMesh)
	{
		for (int32 TriangleIndex : MeshData.TriangleDataList[GridIndex].MeshTriangleIndex)
		{
			EditMesh.RemoveTriangle(TriangleIndex, false);
		}

	}, EDynamicMeshChangeType::DeformationEdit, EDynamicMeshAttributeChangeFlags::MeshTopology, false);

	MeshData.TriangleDataList[GridIndex] = FLFPVoxelTriangleData();

	return;
}

void UHexagonVoxelMesh::FindBlockNeighbour(const FIntVector GridLocation, TArray<int32>& NeighbourIndexList)
{
	TArray<FIntVector> RuleChecker;

	NeighbourIndexList.SetNum(8);

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
		if (ULFPGridLibrary::IsLocationValid(RuleChecker[Index] + GridLocation, MeshData.GridSize))
			NeighbourIndexList[Index] = ULFPGridLibrary::GridLocationToIndex(RuleChecker[Index] + GridLocation, MeshData.GridSize);
		else
			NeighbourIndexList[Index] = INDEX_NONE;
	}
}

void UHexagonVoxelMesh::FindBlockVertices(const FIntVector GridLocation, TArray<int32>& VerticesIndexList)
{
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

bool UHexagonVoxelMesh::IsBlockFaceVisible(const int32 FromGridIndex, const int32 ToGridIndex) const
{
	return !MeshData.RenderNameList.Contains(MeshData.GridData[ToGridIndex].BlockName); // Not In Render List
}

bool UHexagonVoxelMesh::IsBlockNeedRender(const int32 GridIndex) const
{
	return MeshData.RenderNameList.Contains(MeshData.GridData[GridIndex].BlockName);  // Not In Render List;
}
