// Fill out your copyright notice in the Description page of Project Settings.


#include "Mesh/DynamicHexaVoxel.h"
#include "GeometryScriptingCore/Public/GeometryScript/MeshBasicEditFunctions.h"
#include "GeometryScriptingCore/Public/GeometryScript/ListUtilityFunctions.h"
#include "GeometryScriptingCore/Public/GeometryScript/MeshUVFunctions.h"
#include "GeometryScriptingCore/Public/GeometryScript/MeshNormalsFunctions.h"
#include "./Math/LFPGridLibrary.h"


UDynamicHexaVoxel::UDynamicHexaVoxel()
{
}

bool UDynamicHexaVoxel::SetVoxelData(const FIntVector Location, const bool IsVisible)
{
	if (!ULFPGridLibrary::IsLocationValid(Location, VoxelData.GridSize)) return false;

	FDynamicMeshChangeInfo ChangeInfo;
	ChangeInfo.Type = EDynamicMeshChangeType::GeneralEdit;
	ChangeInfo.Flags = EDynamicMeshAttributeChangeFlags::Unknown;
	
	PreMeshChangedEvent.Broadcast(this, ChangeInfo);

	const int32 Index = ULFPGridLibrary::GridLocationToIndex(Location, VoxelData.GridSize);

	VoxelData.GridData[Index].IsVisible = IsVisible;

	int DeleteCount = -1;
	
	if (VoxelData.MeshTriangleData[Index].MeshTriangleIndex.List.IsValid())
	{
		//UGeometryScriptLibrary_MeshBasicEditFunctions::DeleteTrianglesFromMesh(this, VoxelData.MeshTriangleData[Index].MeshTriangleIndex, DeleteCount, true);

		EditMesh([&](FDynamicMesh3& EditMesh)
			{
				for (int32 TriangleID : *VoxelData.MeshTriangleData[Index].MeshTriangleIndex.List)
				{
					EditMesh.RemoveTriangle(TriangleID, false, false);
				}
			}, EDynamicMeshChangeType::GeneralEdit, EDynamicMeshAttributeChangeFlags::Unknown, true);
	}
	
	VoxelData.MeshTriangleData[Index] = FLFPVoxelTriData();
	
	ProcessHexagonNeighbour(Location, [&](const FIntVector NeighbourPos, const int32 NeighbourIndex) {
		if (ULFPGridLibrary::IsLocationValid(NeighbourPos, VoxelData.GridSize))
		{
			int32 NeightbourIndex = ULFPGridLibrary::GridLocationToIndex(NeighbourPos, VoxelData.GridSize);
	
			if (VoxelData.MeshTriangleData[NeightbourIndex].MeshTriangleIndex.List.IsValid())
			{
				//UGeometryScriptLibrary_MeshBasicEditFunctions::DeleteTrianglesFromMesh(this, VoxelData.MeshTriangleData[NeightbourIndex].MeshTriangleIndex, DeleteCount, true);

				EditMesh([&](FDynamicMesh3& EditMesh)
				{
					for (int32 TriangleID : *VoxelData.MeshTriangleData[NeightbourIndex].MeshTriangleIndex.List)
					{
						EditMesh.RemoveTriangle(TriangleID, false, false);
					}
				}, EDynamicMeshChangeType::GeneralEdit, EDynamicMeshAttributeChangeFlags::Unknown, true);
			}
	
			VoxelData.MeshTriangleData[NeightbourIndex] = FLFPVoxelTriData();
		}
		});

	HasDirtyTriangles = true;

	MeshChangedEvent.Broadcast(this, ChangeInfo);
	
	MeshModifiedBPEvent.Broadcast(this);

	return true;
}

void UDynamicHexaVoxel::UpdateVertexs()
{
	FGeometryScriptVectorList MeshVertex;

	MeshVertex.Reset();

	const TArray<FVector> PointList = {
		FVector(0							,VoxelData.MeshSize.Y * 0.5	,0),
		FVector(VoxelData.MeshSize.X * 0.25	,0							,0),
		FVector(VoxelData.MeshSize.X * 0.75	,0							,0),
		FVector(VoxelData.MeshSize.X		,VoxelData.MeshSize.Y * 0.5	,0),
	};

	VoxelData.MaxIndex = (2 + (VoxelData.GridSize.X * 2)) * (1 + VoxelData.GridSize.Y) * (1 + VoxelData.GridSize.Z);

	VoxelData.VertexSize = FIntVector((VoxelData.GridSize.X * 2) + 2, VoxelData.GridSize.Y + 1, VoxelData.GridSize.Z * 2);

	MeshVertex.List->Reserve(VoxelData.MaxIndex);

	for (int32 Z = 0; Z < VoxelData.VertexSize.Z; Z++)
	{
		for (int32 Y = 0; Y < VoxelData.VertexSize.Y; Y++)
		{
			for (int32 X = 0; X < VoxelData.VertexSize.X; X++)
			{
				const FVector CurrentHexaPos = (FVector(X / 4, Y, Z / 2) * (VoxelData.MeshSize + FVector(VoxelData.MeshSize.X * 0.5, 0, 0)) + FVector(0, 0, Z % 2 == 1 ? VoxelData.MeshSize.Z : 0));

				MeshVertex.List->Add(PointList[X % 4] + CurrentHexaPos);
			}
		}
	}

	UGeometryScriptLibrary_MeshBasicEditFunctions::AddVerticesToMesh(this, MeshVertex, VoxelData.MeshVertexIndex, false);

	return;
}

void UDynamicHexaVoxel::UpdateTriangles()
{
	// This Function Are Currently On Debug

	if (!HasDirtyTriangles) return;

	FDynamicMeshChangeInfo ChangeInfo;
	ChangeInfo.Type = EDynamicMeshChangeType::GeneralEdit;
	ChangeInfo.Flags = EDynamicMeshAttributeChangeFlags::Unknown;

	PreMeshChangedEvent.Broadcast(this, ChangeInfo);

	FGeometryScriptTriangleList TrianglesList;

	TArray<int32> LocalHexagonIndex;

	bool IsValid = false;

	for (int32 Z = 0; Z < VoxelData.GridSize.Z; Z++)
	{
		for (int32 Y = 0; Y < VoxelData.GridSize.Y; Y++)
		{
			for (int32 X = 0; X < VoxelData.GridSize.X; X++)
			{
				const int32 Index = ULFPGridLibrary::GridLocationToIndex(FIntVector(X, Y, Z), VoxelData.GridSize);

				if (!VoxelData.MeshTriangleData[Index].IsDirty) continue; // Check Block Need Update

				if (!IsBlockVisible(FIntVector(X, Y, Z))) continue; // Check Block Is Visible

				TrianglesList.Reset();

				GetHexagonVertexIndex(FIntVector(X, Y, Z), LocalHexagonIndex);

				ProcessHexagonNeighbour(FIntVector(X, Y, Z), [&](const FIntVector NeighbourPos, const int32 NeighbourID) {
						bool IsEmpty = IsTrianglesVisible(FIntVector(X, Y, Z), NeighbourPos);

						switch (NeighbourID)
						{
							case 6: if (IsEmpty) BuildHexaRoof(LocalHexagonIndex, TrianglesList, VoxelData.MeshTriangleData[Index].MeshUVList, true); break;
							case 7: if (IsEmpty) BuildHexaRoof(LocalHexagonIndex, TrianglesList, VoxelData.MeshTriangleData[Index].MeshUVList, false); break;
							default: if (IsEmpty) BuildHexaWall(LocalHexagonIndex, TrianglesList, VoxelData.MeshTriangleData[Index].MeshUVList, NeighbourID); break;
						}
					});

				if (TrianglesList.List->Num() > 0)
				{
					UGeometryScriptLibrary_MeshBasicEditFunctions::AddTrianglesToMesh(this, TrianglesList, VoxelData.MeshTriangleData[Index].MeshTriangleIndex, 0, true);

					for (int32 UVIndex = 0; UVIndex < VoxelData.MeshTriangleData[Index].MeshUVList.Num(); UVIndex++)
					{
						UGeometryScriptLibrary_MeshUVFunctions::SetMeshTriangleUVs(this, 0, *(VoxelData.MeshTriangleData[Index].MeshTriangleIndex.List->GetData() + UVIndex), VoxelData.MeshTriangleData[Index].MeshUVList[UVIndex], IsValid, true);
					}
				}

				VoxelData.MeshTriangleData[Index].IsDirty = false;
			}
		}
	}

	UGeometryScriptLibrary_MeshNormalsFunctions::SetPerFaceNormals(this);
	
	FGeometryScriptTangentsOptions Option;
	
	Option.Type = EGeometryScriptTangentTypes::PerTriangle;
	Option.UVLayer = 0;
	
	UGeometryScriptLibrary_MeshNormalsFunctions::ComputeTangents(this, Option);

	HasDirtyTriangles = false;

	MeshChangedEvent.Broadcast(this, ChangeInfo);

	MeshModifiedBPEvent.Broadcast(this);

	return;
}

bool UDynamicHexaVoxel::IsBlockVisible(const FIntVector Location) const
{
	check(ULFPGridLibrary::IsLocationValid(Location, VoxelData.GridSize));

	if (!VoxelData.GridData[ULFPGridLibrary::GridLocationToIndex(Location, VoxelData.GridSize)].IsVisible) return false; // Is Air

	return true;
}

bool UDynamicHexaVoxel::IsTrianglesVisible(const FIntVector From, const FIntVector To) const
{
	check(ULFPGridLibrary::IsLocationValid(From, VoxelData.GridSize));

	if (!ULFPGridLibrary::IsLocationValid(To, VoxelData.GridSize)) return true; // Is Over Bound

	if (!VoxelData.GridData[ULFPGridLibrary::GridLocationToIndex(To, VoxelData.GridSize)].IsVisible) return true; // Is Air

	if (VoxelData.GridData[ULFPGridLibrary::GridLocationToIndex(From, VoxelData.GridSize)].RenderLayer != VoxelData.GridData[ULFPGridLibrary::GridLocationToIndex(To, VoxelData.GridSize)].RenderLayer)
		return true; // Is Different Layer

	return false;
}

void UDynamicHexaVoxel::GetHexagonVertexIndex(const FIntVector HexagonPos, TArray<int32>& VertexIndexList)
{
	//check(HexagonIndex >= 0 && HexagonIndex < HexagonMaxIndex); // Terminate Unreal If HexagonIndex Is Out Of Bounds

	//const FIntVector GridPos = FIntVector(HexagonIndex % HexagonGridSize.X, (HexagonIndex / HexagonGridSize.X) % HexagonGridSize.Y, HexagonIndex / (HexagonGridSize.X * HexagonGridSize.Y));

	VertexIndexList.SetNum(12);

	const bool IsSecond = HexagonPos.X % 2 == 1;

	const int32 Index = (HexagonPos.Z * (VoxelData.VertexSize.X * VoxelData.VertexSize.Y * 2)) + (HexagonPos.Y * VoxelData.VertexSize.X) + (((HexagonPos.X / 2) * 4) + (HexagonPos.X % 2 == 1 ? 2 + VoxelData.VertexSize.X : 0));

	if (IsSecond)
	{
		VertexIndexList[0] = Index;
		VertexIndexList[1] = Index + 1 - VoxelData.VertexSize.X;
		VertexIndexList[2] = Index + 2 - VoxelData.VertexSize.X;
		VertexIndexList[3] = Index + 3;
		VertexIndexList[4] = Index + 2;
		VertexIndexList[5] = Index + 1;

		VertexIndexList[6]  = (VoxelData.VertexSize.X * VoxelData.VertexSize.Y) + Index;
		VertexIndexList[7]  = (VoxelData.VertexSize.X * VoxelData.VertexSize.Y) + Index + 1 - VoxelData.VertexSize.X;
		VertexIndexList[8]  = (VoxelData.VertexSize.X * VoxelData.VertexSize.Y) + Index + 2 - VoxelData.VertexSize.X;
		VertexIndexList[9]  = (VoxelData.VertexSize.X * VoxelData.VertexSize.Y) + Index + 3;
		VertexIndexList[10] = (VoxelData.VertexSize.X * VoxelData.VertexSize.Y) + Index + 2;
		VertexIndexList[11] = (VoxelData.VertexSize.X * VoxelData.VertexSize.Y) + Index + 1;
	}
	else
	{
		VertexIndexList[0] = Index;
		VertexIndexList[1] = Index + 1;
		VertexIndexList[2] = Index + 2;
		VertexIndexList[3] = Index + 3;
		VertexIndexList[4] = Index + 2 + VoxelData.VertexSize.X;
		VertexIndexList[5] = Index + 1 + VoxelData.VertexSize.X;

		VertexIndexList[6]  = (VoxelData.VertexSize.X * VoxelData.VertexSize.Y) + Index;
		VertexIndexList[7]  = (VoxelData.VertexSize.X * VoxelData.VertexSize.Y) + Index + 1;
		VertexIndexList[8]  = (VoxelData.VertexSize.X * VoxelData.VertexSize.Y) + Index + 2;
		VertexIndexList[9]  = (VoxelData.VertexSize.X * VoxelData.VertexSize.Y) + Index + 3;
		VertexIndexList[10] = (VoxelData.VertexSize.X * VoxelData.VertexSize.Y) + Index + 2 + VoxelData.VertexSize.X;
		VertexIndexList[11] = (VoxelData.VertexSize.X * VoxelData.VertexSize.Y) + Index + 1 + VoxelData.VertexSize.X;
	}

	return;
}

void UDynamicHexaVoxel::ProcessHexagonNeighbour(const FIntVector HexagonPos, TFunctionRef<void(const FIntVector&, const int32&)> ProcessFunc)
{
	TArray<FIntVector> RuleChecker;

	if (HexagonPos.X % 2 == 1)
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
		ProcessFunc(HexagonPos + RuleChecker[Index],Index);
	}
}

void UDynamicHexaVoxel::BuildHexaWall(const TArray<int32>& VertexIndexList, FGeometryScriptTriangleList& TrianglesList, TArray<FGeometryScriptUVTriangle>& UVList, const int32 WallID)
{
	check(WallID >= 0 && WallID <= 5); // Terminate Unreal If WallID Is Invalid

	double Jump = WallID % 2 == 1 ? 0.5 : 0.0;

	FGeometryScriptUVTriangle UVData01;
	FGeometryScriptUVTriangle UVData02;

	UVData01.UV0 = FVector2D(Jump + 0.5, 0);
	UVData01.UV1 = FVector2D(Jump + 0, 0);
	UVData01.UV2 = FVector2D(Jump + 0, 0.5);
	
	UVData02.UV0 = FVector2D(Jump + 0.5, 0);
	UVData02.UV1 = FVector2D(Jump + 0, 0.5);
	UVData02.UV2 = FVector2D(Jump + 0.5, 0.5);

	const int32 Ind01 = WallID;
	const int32 Ind02 = WallID == 5 ? 0 : WallID + 1;
	const int32 Ind03 = WallID + 6;
	const int32 Ind04 = WallID == 5 ? 6 : WallID + 7;

	TrianglesList.List->Append({ 
		FIntVector(VertexIndexList[Ind02], VertexIndexList[Ind01], VertexIndexList[Ind03]),
		FIntVector(VertexIndexList[Ind02], VertexIndexList[Ind03], VertexIndexList[Ind04])
		});

	UVList.Append({ UVData01,UVData02 });

	return;
}

void UDynamicHexaVoxel::BuildHexaRoof(const TArray<int32>& VertexIndexList, FGeometryScriptTriangleList& TrianglesList, TArray<FGeometryScriptUVTriangle>& UVList, const bool IsTop)
{
	FGeometryScriptUVTriangle UVData01;
	FGeometryScriptUVTriangle UVData02;
	FGeometryScriptUVTriangle UVData03;
	FGeometryScriptUVTriangle UVData04;

	if (IsTop)
	{
		TrianglesList.List->Append({ 
			FIntVector(VertexIndexList[7], VertexIndexList[6] , VertexIndexList[11]),
			FIntVector(VertexIndexList[7], VertexIndexList[11] , VertexIndexList[10]),
			FIntVector(VertexIndexList[8], VertexIndexList[7], VertexIndexList[10]),
			FIntVector(VertexIndexList[9], VertexIndexList[8] , VertexIndexList[10]) 
			});

		UVData01.UV0 = FVector2D(0.125, 1);
		UVData01.UV2 = FVector2D(0.125, 0.5);
		UVData01.UV1 = FVector2D(0, 0.75);

		UVData02.UV0 = FVector2D(0.125, 1);
		UVData02.UV2 = FVector2D(0.35, 0.5);
		UVData02.UV1 = FVector2D(0.125, 0.5);

		UVData03.UV0 = FVector2D(0.35, 1);
		UVData03.UV2 = FVector2D(0.35, 0.5);
		UVData03.UV1 = FVector2D(0.125, 1);

		UVData04.UV0 = FVector2D(0.5, 0.75);
		UVData04.UV2 = FVector2D(0.35, 1);
		UVData04.UV1 = FVector2D(0.35, 0.5);
	}
	else
	{
		TrianglesList.List->Append({ 
			FIntVector(VertexIndexList[1], VertexIndexList[5] , VertexIndexList[0]),
			FIntVector(VertexIndexList[1], VertexIndexList[4] , VertexIndexList[5]),
			FIntVector(VertexIndexList[2], VertexIndexList[4], VertexIndexList[1]),
			FIntVector(VertexIndexList[3], VertexIndexList[4] , VertexIndexList[2])
			});

		UVData01.UV0 = FVector2D(0.625, 1);
		UVData01.UV1 = FVector2D(0.625, 0.5);
		UVData01.UV2 = FVector2D(0.5, 0.75);

		UVData02.UV0 = FVector2D(0.625, 1);
		UVData02.UV1 = FVector2D(0.85, 0.5);
		UVData02.UV2 = FVector2D(0.625, 0.5);
		
		UVData03.UV0 = FVector2D(0.85, 1);
		UVData03.UV1 = FVector2D(0.85, 0.5);
		UVData03.UV2 = FVector2D(0.625, 1);
		
		UVData04.UV0 = FVector2D(1, 0.75);
		UVData04.UV1 = FVector2D(0.85, 1);
		UVData04.UV2 = FVector2D(0.85, 0.5);
	}

	UVList.Append({ UVData01,UVData02,UVData03,UVData04 });

	return;
}
