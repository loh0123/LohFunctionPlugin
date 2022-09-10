// Copyright by Loh Zhi Kang


#include "Voxel/LFPBaseVoxelMeshComponent.h"
#include "./Math/LFPGridLibrary.h"
#include "PhysicsEngine/PhysicsSettings.h"
#include "Voxel/LFPBaseVoxelMeshSceneProxy.h"
#include "MeshCardRepresentation.h"

DEFINE_LOG_CATEGORY(LFPVoxelMeshComponentLog);

FVoxelMeshRenderData::~FVoxelMeshRenderData()
{
	delete LumenCardData;
}

ULFPBaseVoxelMeshComponent::ULFPBaseVoxelMeshComponent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;
	//PrimaryComponentTick.bRunOnAnyThread = true;

}

void ULFPBaseVoxelMeshComponent::SetVoxelContainer(ULFPVoxelContainer* NewVoxelContainer, const int32 NewChuckIndex, const FVector NewVoxelHalfSize, const FName InitializeName)
{
	VoxelContainer = NewVoxelContainer;

	if (VoxelContainer != nullptr && VoxelContainer->IsChuckIndexValid(NewChuckIndex))
	{
		ChuckIndex = NewChuckIndex;

		VoxelStartLocation = VoxelContainer->GetChuckStartVoxelLocation(ChuckIndex);

		VoxelHalfSize = NewVoxelHalfSize.GetMin() >= 10.0f ? NewVoxelHalfSize : FVector(100);

		VoxelContainer->ConnectVoxelUpdateEvent(ChuckIndex, this, &ULFPBaseVoxelMeshComponent::UpdateVoxelMesh);

		VoxelContainer->InitializeOrUpdateChuck(ChuckIndex, InitializeName);
	}
	else
	{
		UE_LOG(LFPVoxelMeshComponentLog, Warning, TEXT("Can't Setup Voxel Container Because Is Null Or Invalid Chuck"));
	}
}

void ULFPBaseVoxelMeshComponent::SetVoxelMaterial(const TArray<UMaterialInterface*>& Material)
{
	if (Material.IsEmpty() == false)
	{
		for (int k = 0; k < Material.Num(); ++k)
		{
			SetMaterial(k, Material[k]);
		}

		UpdateVoxelMesh();
	}
	else
	{
		UE_LOG(LFPVoxelMeshComponentLog, Warning, TEXT("Can't Set Material Because Array Is Empty"));
	}
}

void ULFPBaseVoxelMeshComponent::UpdateVoxelMesh()
{
	if (VoxelContainer == nullptr)
	{
		UE_LOG(LFPVoxelMeshComponentLog, Warning, TEXT("Voxel Mesh Can't Be Update Because Voxel Container Is Null"));

		return;
	}

	bIsVoxelMeshDirty = true;
}

void ULFPBaseVoxelMeshComponent::AddVoxelFace(FVoxelMeshSectionData& EditMesh, const int32 VoxelIndex, const FVector3f VoxelLocation, const FVector2f UVOffset, const int32 FaceIndex, const FColor VoxelColor)
{
	const uint32 StartIndex = EditMesh.VertexList.Num();

	bool FlipTriangleIndex = false;

	switch (FaceIndex)
	{
	case 0 : EditMesh.VertexList.Append({ 
		FVector3f( VoxelHalfSize.X,-VoxelHalfSize.Y, VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X,-VoxelHalfSize.Y, VoxelHalfSize.Z) + VoxelLocation,
		FVector3f( VoxelHalfSize.X, VoxelHalfSize.Y, VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X, VoxelHalfSize.Y, VoxelHalfSize.Z) + VoxelLocation,
		FVector3f( VoxelHalfSize.X, VoxelHalfSize.Y, VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X,-VoxelHalfSize.Y, VoxelHalfSize.Z) + VoxelLocation,
		});
		break;
	case 1 : EditMesh.VertexList.Append({
		FVector3f(-VoxelHalfSize.X,-VoxelHalfSize.Y, VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X,-VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X, VoxelHalfSize.Y, VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X, VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X, VoxelHalfSize.Y, VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X,-VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		});
		break;
	case 2 : EditMesh.VertexList.Append({
		FVector3f(-VoxelHalfSize.X, VoxelHalfSize.Y, VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X, VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f( VoxelHalfSize.X, VoxelHalfSize.Y, VoxelHalfSize.Z) + VoxelLocation,
		FVector3f( VoxelHalfSize.X, VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f( VoxelHalfSize.X, VoxelHalfSize.Y, VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X, VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		});
		break;
	case 3 : EditMesh.VertexList.Append({
		FVector3f( VoxelHalfSize.X, VoxelHalfSize.Y, VoxelHalfSize.Z) + VoxelLocation,
		FVector3f( VoxelHalfSize.X, VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f( VoxelHalfSize.X,-VoxelHalfSize.Y, VoxelHalfSize.Z) + VoxelLocation,
		FVector3f( VoxelHalfSize.X,-VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f( VoxelHalfSize.X,-VoxelHalfSize.Y, VoxelHalfSize.Z) + VoxelLocation,
		FVector3f( VoxelHalfSize.X, VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		});
		break;
	case 4 : EditMesh.VertexList.Append({
		FVector3f( VoxelHalfSize.X,-VoxelHalfSize.Y, VoxelHalfSize.Z) + VoxelLocation,
		FVector3f( VoxelHalfSize.X,-VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X,-VoxelHalfSize.Y, VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X,-VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X,-VoxelHalfSize.Y, VoxelHalfSize.Z) + VoxelLocation,
		FVector3f( VoxelHalfSize.X,-VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		});
		break;
	case 5 : EditMesh.VertexList.Append({
		FVector3f(-VoxelHalfSize.X,-VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f( VoxelHalfSize.X,-VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X, VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f( VoxelHalfSize.X, VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X, VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f( VoxelHalfSize.X,-VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		});
		break;
	}

	if (FlipTriangleIndex)
	{
		EditMesh.TriangleIndexList.Append({ 5 + StartIndex,4 + StartIndex,3 + StartIndex,2 + StartIndex,1 + StartIndex, StartIndex });
	}
	else
	{
		EditMesh.TriangleIndexList.Append({ StartIndex,1 + StartIndex,2 + StartIndex,3 + StartIndex,4 + StartIndex,5 + StartIndex });
	}

	FVector2f UVSize = FVector2f(VoxelUVSize) * FVector2f(1.0f / 3.0f, 0.5f);

	EditMesh.UVList.Append({ 
		(FVector2f(0.0f,0.0f) + UVOffset) * UVSize,
		(FVector2f(0.0f,1.0f) + UVOffset) * UVSize,
		(FVector2f(1.0f,0.0f) + UVOffset) * UVSize,
		(FVector2f(1.0f,1.0f) + UVOffset) * UVSize,
		(FVector2f(1.0f,0.0f) + UVOffset) * UVSize,
		(FVector2f(0.0f,1.0f) + UVOffset) * UVSize 
		});

	EditMesh.VoxelColorList.Append({ VoxelColor ,VoxelColor });

	/* Add Index Trace */
	EditMesh.VoxelIndexList.Append({ VoxelIndex, VoxelIndex });

	EditMesh.TriangleCount += 2;
}

int32 ULFPBaseVoxelMeshComponent::GetVoxelLength() const
{
	return VoxelContainer != nullptr ? VoxelContainer->GetContainerSetting().VoxelLength : INDEX_NONE;
}

void ULFPBaseVoxelMeshComponent::GetVoxelAttributeList(TArray<FLFPVoxelAttributeV2>& VoxelAttributeList, TBitArray<>& VisibleList)
{
	check(VoxelContainer != nullptr);
	check(VoxelContainer->IsChuckInitialized(ChuckIndex));

	VoxelAttributeList.Empty(VoxelContainer->GetContainerSetting().VoxelLength);
	VisibleList.Init(false, VoxelContainer->GetContainerSetting().VoxelLength);

	int32 Index = 0;

	for (const FName& VoxelName : VoxelContainer->GetVoxelNameList(ChuckIndex))
	{
		VoxelAttributeList.Add(VoxelContainer->GetVoxelAttributeByName(VoxelName));

		VisibleList[Index++] = VoxelContainer->IsVoxelVisibleByName(VoxelName);
	}
}

void ULFPBaseVoxelMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (bIsVoxelMeshDirty)
	{
		if (bIsGeneratingMesh == false)
		{
			bIsGeneratingMesh = true;

			bIsVoxelMeshDirty = false;

			FBox LocalBound = GetVoxelMeshBound();

			AsyncTask(ENamedThreads::AnyNormalThreadNormalTask, [LocalVoxelContainer = VoxelContainer, LocalBound, this]()
				{
					if (IsValid(this) == false)
					{
						return;
					}

					//TArray<FVoxelMeshSectionData> NewVoxelMesh;
					//TArray<FTransform> NewVoxelDistanceFieldInstance;

					FVoxelMeshRenderData* NewRenderData = new FVoxelMeshRenderData();

					NewRenderData->Sections.Init(FVoxelMeshSectionData(), FMath::Max(GetNumMaterials(), 1));
					NewRenderData->LumenBox.Init(FBox(EForceInit::ForceInitToZero), 6);

					TArray<FIntVector> FaceCheckDirection = {
						FIntVector(0,0,1),
						FIntVector(-1,0,0),
						FIntVector(0,1,0),
						FIntVector(1,0,0),
						FIntVector(0,-1,0),
						FIntVector(0,0,-1),
					};

					TArray<FVector2f> FaceUVStartOffset = {
						FVector2f(0,0),
						FVector2f(1,0),
						FVector2f(2,0),
						FVector2f(2,1),
						FVector2f(1,1),
						FVector2f(0,1),
					};

					TArray<FVector> SurfaceScale = {
						FVector(1,1,0),
						FVector(0,1,1),
						FVector(1,0,1),
						FVector(0,1,1),
						FVector(1,0,1),
						FVector(1,1,0),
					};

					TArray<int32> SurfaceDirectionID = {
						5,0,3,1,2,4
					};

					FRWScopeLock ReadLock(LocalVoxelContainer->GetContainerThreadLock(), SLT_ReadOnly);

					const TArray<FName> VoxelNameList = LocalVoxelContainer->GetVoxelNameList(ChuckIndex);

					NewRenderData->DistanceFieldInstanceData.Reserve(LocalVoxelContainer->GetContainerSetting().VoxelLength);

					for (int32 VoxelIndex = 0; VoxelIndex < LocalVoxelContainer->GetContainerSetting().VoxelLength && IsValid(this); VoxelIndex++)
					{
						const FIntVector VoxelGridLocation = ULFPGridLibrary::IndexToGridLocation(VoxelIndex, LocalVoxelContainer->GetContainerSetting().VoxelGridSize);

						const FVector3f VoxelLocation = ((FVector3f)VoxelGridLocation) * ((FVector3f)VoxelHalfSize * 2);

						const FLFPVoxelAttributeV2& VoxelAttribute = LocalVoxelContainer->GetVoxelAttributeByName(VoxelNameList[VoxelIndex]);

						const FVector2f VoxelUVOffset = FVector2f(VoxelAttribute.UVOffset);

						if (LocalVoxelContainer->IsVoxelVisibleByName(VoxelNameList[VoxelIndex]))
						{
							bool HasFace = false;

							FBox LocalVoxelBound = FBox::BuildAABB(FVector3d(VoxelLocation), VoxelHalfSize + BoundExpand);

							for (int32 FaceIndex = 0; FaceIndex < 6; FaceIndex++)
							{
								if (LocalVoxelContainer->IsVoxelVisible(LocalVoxelContainer->VoxelGridLocationToVoxelGridIndex(VoxelGridLocation + FaceCheckDirection[FaceIndex] + VoxelStartLocation)) == false)
								{
									const int32 MaterialID = VoxelAttribute.MaterialID < GetNumMaterials() ? VoxelAttribute.MaterialID : 0;

									AddVoxelFace(NewRenderData->Sections[MaterialID], VoxelIndex, VoxelLocation, FaceUVStartOffset[FaceIndex] + VoxelUVOffset, FaceIndex, VoxelAttribute.VertexColor);

									HasFace = true;

									/* Generate Lumen Box */
									{
										FVector MinSurface = LocalVoxelBound.Min * SurfaceScale[FaceIndex];
										FVector MaxSurface = LocalVoxelBound.Max * SurfaceScale[FaceIndex];

										FVector CardOriginOffset = (FVector(VoxelLocation) * (FVector(FaceCheckDirection[FaceIndex]).GetAbs())) + (VoxelHalfSize * FVector(FaceCheckDirection[FaceIndex]));
										FVector Extention = BoundExpand * FVector(FaceCheckDirection[FaceIndex]).GetAbs();

										MinSurface += CardOriginOffset - Extention;
										MaxSurface += CardOriginOffset + Extention;

										if (NewRenderData->LumenBox[FaceIndex].IsValid)
										{
											if (NewRenderData->LumenBox[FaceIndex].Min.X > MinSurface.X) NewRenderData->LumenBox[FaceIndex].Min.X = MinSurface.X;
											if (NewRenderData->LumenBox[FaceIndex].Min.Y > MinSurface.Y) NewRenderData->LumenBox[FaceIndex].Min.Y = MinSurface.Y;
											if (NewRenderData->LumenBox[FaceIndex].Min.Z > MinSurface.Z) NewRenderData->LumenBox[FaceIndex].Min.Z = MinSurface.Z;
											
											if (NewRenderData->LumenBox[FaceIndex].Max.X < MaxSurface.X) NewRenderData->LumenBox[FaceIndex].Max.X = MaxSurface.X;
											if (NewRenderData->LumenBox[FaceIndex].Max.Y < MaxSurface.Y) NewRenderData->LumenBox[FaceIndex].Max.Y = MaxSurface.Y;
											if (NewRenderData->LumenBox[FaceIndex].Max.Z < MaxSurface.Z) NewRenderData->LumenBox[FaceIndex].Max.Z = MaxSurface.Z;
										}
										else
										{
											NewRenderData->LumenBox[FaceIndex] = FBox(MinSurface, MaxSurface);
										}
									}
								}
							}

							if (HasFace)
							{
								NewRenderData->DistanceFieldInstanceData.Add(FTransform(FVector(VoxelLocation)));
							}
						}
					}

					/* Fill In Lumen Data */
					{
						NewRenderData->LumenCardData = new FCardRepresentationData();

						NewRenderData->LumenCardData->MeshCardsBuildData.MaxLODLevel = 0;

						NewRenderData->LumenCardData->MeshCardsBuildData.Bounds = LocalBound;

						for (int32 Index = 0; Index < 6; Index++)
						{
							if (NewRenderData->LumenBox[Index].IsValid == false) continue;

							FLumenCardBuildData LumenCard;

							LumenCard.AxisAlignedDirectionIndex = SurfaceDirectionID[Index];

							LumenCard.LODLevel = 0;

							FVector BoxExtent = NewRenderData->LumenBox[Index].GetExtent();

							switch (Index)
							{
							case 0:
								LumenCard.OBB.Extent = FVector3f(BoxExtent.X, BoxExtent.Y, BoxExtent.Z);
								LumenCard.OBB.AxisX = FVector3f(1.0f, 0.0f, 0.0f);
								LumenCard.OBB.AxisY = FVector3f(0.0f, 1.0f, 0.0f);
								LumenCard.OBB.AxisZ = FVector3f(0.0f, 0.0f, 1.0f);
								break;
							case 1:
								LumenCard.OBB.Extent = FVector3f(BoxExtent.Z, BoxExtent.Y, BoxExtent.X);
								LumenCard.OBB.AxisX = FVector3f(0.0f, 0.0f, 1.0f);
								LumenCard.OBB.AxisY = FVector3f(0.0f, 1.0f, 0.0f);
								LumenCard.OBB.AxisZ = FVector3f(-1.0f, 0.0f, 0.0f);
								break;
							case 2:
								LumenCard.OBB.Extent = FVector3f(BoxExtent.Z, BoxExtent.X, BoxExtent.Y);
								LumenCard.OBB.AxisX = FVector3f(0.0f, 0.0f, 1.0f);
								LumenCard.OBB.AxisY = FVector3f(1.0f, 0.0f, 0.0f);
								LumenCard.OBB.AxisZ = FVector3f(0.0f, 1.0f, 0.0f);
								break;
							case 3:
								LumenCard.OBB.Extent = FVector3f(BoxExtent.Z, BoxExtent.Y, BoxExtent.X);
								LumenCard.OBB.AxisX = FVector3f(0.0f, 0.0f, 1.0f);
								LumenCard.OBB.AxisY = FVector3f(0.0f, -1.0f, 0.0f);
								LumenCard.OBB.AxisZ = FVector3f(1.0f, 0.0f, 0.0f);
								break;
							case 4:
								LumenCard.OBB.Extent = FVector3f(BoxExtent.Z, BoxExtent.X, BoxExtent.Y);
								LumenCard.OBB.AxisX = FVector3f(0.0f, 0.0f, 1.0f);
								LumenCard.OBB.AxisY = FVector3f(-1.0f, 0.0f, 0.0f);
								LumenCard.OBB.AxisZ = FVector3f(0.0f, -1.0f, 0.0f);
								break;
							case 5:
								LumenCard.OBB.Extent = FVector3f(BoxExtent.X, BoxExtent.Y, BoxExtent.Z);
								LumenCard.OBB.AxisX = FVector3f(-1.0f, 0.0f, 0.0f);
								LumenCard.OBB.AxisY = FVector3f(0.0f, 1.0f, 0.0f);
								LumenCard.OBB.AxisZ = FVector3f(0.0f, 0.0f, -1.0f);
								break;
							}

							LumenCard.OBB.Origin = FVector3f(NewRenderData->LumenBox[Index].GetCenter());

							NewRenderData->LumenCardData->MeshCardsBuildData.CardBuildData.Add(LumenCard);
						}
					}

					NewRenderData->DistanceFieldInstanceData.Shrink();

					AsyncTask(ENamedThreads::GameThread, [RenderData = NewRenderData, this]() {
						if (IsValid(this) == false) return;

						bIsGeneratingMesh = false;

						bool bIsVoxelMeshValid = false;

						for (const FVoxelMeshSectionData& Buffer : RenderData->Sections)
						{
							if (Buffer.TriangleCount > 0)
							{
								bIsVoxelMeshValid = true;
							}
						}

						if (bIsVoxelMeshValid)
						{
							VoxelMeshRenderData = RenderData;

							if (IsValid(DistanceFieldMesh)) VoxelMeshRenderData->DistanceFieldMeshData = DistanceFieldMesh->GetRenderData()->LODResources[0].DistanceFieldData;
						}
						else
						{
							VoxelMeshRenderData = nullptr;

							delete RenderData;
						}

						MarkRenderStateDirty();
						RebuildPhysicsData();
						});

				}
			);
		}
	}
}

FPrimitiveSceneProxy* ULFPBaseVoxelMeshComponent::CreateSceneProxy()
{
	if (VoxelMeshRenderData && VoxelMeshRenderData->Sections.Num() == GetNumMaterials() && GetNumMaterials() != 0)
	{
		return new FLFPBaseVoxelMeshSceneProxy(this);
	}
	else
	{
		return nullptr;
	}
}

FBoxSphereBounds ULFPBaseVoxelMeshComponent::CalcBounds(const FTransform& LocalToWorld) const
{
	FBoxSphereBounds Ret(GetVoxelMeshBound().TransformBy(LocalToWorld));
	Ret.BoxExtent *= BoundsScale;
	Ret.SphereRadius *= BoundsScale;

	return Ret;
}

void ULFPBaseVoxelMeshComponent::GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials) const
{
	OutMaterials.Append(BaseMaterials);
}

UMaterialInterface* ULFPBaseVoxelMeshComponent::GetMaterialFromCollisionFaceIndex(int32 FaceIndex, int32& SectionIndex) const
{
	UMaterialInterface* Result = nullptr;
	SectionIndex = 0;

	if (VoxelMeshRenderData && FaceIndex >= 0)
	{
		// Look for section that corresponds to the supplied face
		int32 TotalFaceCount = 0;

		for (int32 SectionIdx = 0; SectionIdx < VoxelMeshRenderData->Sections.Num(); SectionIdx++)
		{
			const FVoxelMeshSectionData& Section = VoxelMeshRenderData->Sections[SectionIdx];
			
			TotalFaceCount += Section.TriangleCount;

			if (FaceIndex < TotalFaceCount)
			{
				// Get the current material for it, from this component
				Result = GetMaterial(SectionIdx);
				SectionIndex = SectionIdx;
				break;
			}
		}
	}

	return Result;
}

int32 ULFPBaseVoxelMeshComponent::GetNumMaterials() const
{
	return BaseMaterials.Num();
}

UMaterialInterface* ULFPBaseVoxelMeshComponent::GetMaterial(int32 ElementIndex) const
{
	return (ElementIndex >= 0 && ElementIndex < BaseMaterials.Num()) ? BaseMaterials[ElementIndex] : nullptr;
}

void ULFPBaseVoxelMeshComponent::SetMaterial(int32 ElementIndex, UMaterialInterface* Material)
{
	check(ElementIndex >= 0);
	if (ElementIndex >= BaseMaterials.Num())
	{
		BaseMaterials.SetNum(ElementIndex + 1, false);
	}
	BaseMaterials[ElementIndex] = Material;
}

bool ULFPBaseVoxelMeshComponent::GetPhysicsTriMeshData(FTriMeshCollisionData* CollisionData, bool InUseAllTriData)
{
	if (VoxelMeshRenderData == nullptr) return false;

	int32 VertexBase = 0; // Base vertex index for current section

// See if we should copy UVs
	bool bCopyUVs = UPhysicsSettings::Get()->bSupportUVFromHitResults;
	if (bCopyUVs)
	{
		CollisionData->UVs.AddZeroed(1); // only one UV channel
	}

	// For each section..
	for (int32 SectionIdx = 0; SectionIdx < VoxelMeshRenderData->Sections.Num(); SectionIdx++)
	{
		if (VoxelMeshRenderData->Sections[SectionIdx].TriangleCount == 0)
		{
			continue;
		}

		FVoxelMeshSectionData& Section = VoxelMeshRenderData->Sections[SectionIdx];

		CollisionData->Vertices.Append(Section.VertexList);

		if (bCopyUVs) CollisionData->UVs[0].Append(Section.UVList);

		// Copy triangle data
		const int32 NumVertexs = Section.VertexList.Num();
		for (int32 TriIdx = 0; TriIdx < NumVertexs; TriIdx += 3)
		{
			// Need to add base offset for indices
			FTriIndices Triangle;
			Triangle.v0 = Section.TriangleIndexList[TriIdx + 0] + VertexBase;
			Triangle.v1 = Section.TriangleIndexList[TriIdx + 1] + VertexBase;
			Triangle.v2 = Section.TriangleIndexList[TriIdx + 2] + VertexBase;
			CollisionData->Indices.Add(Triangle);

			// Also store material info
			CollisionData->MaterialIndices.Add(SectionIdx);
		}

		// Remember the base index that new verts will be added from in next section
		VertexBase = CollisionData->Vertices.Num();
	}

	CollisionData->bFlipNormals = true;
	CollisionData->bDeformableMesh = false;
	CollisionData->bFastCook = false;

	return true;
}

bool ULFPBaseVoxelMeshComponent::ContainsPhysicsTriMeshData(bool InUseAllTriData) const
{
	return VoxelMeshRenderData != nullptr;
}

bool ULFPBaseVoxelMeshComponent::WantsNegXTriMesh()
{
	return false;
}

UBodySetup* ULFPBaseVoxelMeshComponent::GetBodySetup()
{
	if (MeshBodySetup == nullptr)
	{
		MeshBodySetup = CreateBodySetup();
	}

	return MeshBodySetup;
}

UBodySetup* ULFPBaseVoxelMeshComponent::CreateBodySetup()
{
	UBodySetup* NewBodySetup = NewObject<UBodySetup>(this, NAME_None, (IsTemplate() ? RF_Public | RF_ArchetypeObject : RF_NoFlags));
	NewBodySetup->BodySetupGuid = FGuid::NewGuid();

	NewBodySetup->bGenerateMirroredCollision = false;
	NewBodySetup->CollisionTraceFlag = ECollisionTraceFlag::CTF_UseComplexAsSimple;

	return NewBodySetup;
}

void ULFPBaseVoxelMeshComponent::RebuildPhysicsData()
{
	if (MeshBodySetup->CurrentCookHelper)
	{
		bIsBodyInvalid = true;
	}
	else
	{
		MeshBodySetup->CreatePhysicsMeshesAsync(FOnAsyncPhysicsCookFinished::CreateUObject(this, &ULFPBaseVoxelMeshComponent::FinishPhysicsAsyncCook, MeshBodySetup.Get()));
	}
}

void ULFPBaseVoxelMeshComponent::FinishPhysicsAsyncCook(bool bSuccess, UBodySetup* FinishedBodySetup)
{
	if (bIsBodyInvalid)
	{
		bIsBodyInvalid = false;

		RecreatePhysicsState();

		RebuildPhysicsData();
	}
	else if (bSuccess)
	{
		RecreatePhysicsState();
	}
}
