// Copyright (c) 2022 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#include "Voxel/LFPBaseVoxelMeshComponent.h"
#include "./Math/LFPGridLibrary.h"
//#include "PhysicsEngine/PhysicsSettings.h"
#include "Voxel/LFPBaseVoxelMeshSceneProxy.h"
#include "MeshCardRepresentation.h"
#include "Kismet/KismetMathLibrary.h"

DEFINE_LOG_CATEGORY(LFPVoxelMeshComponentLog);

FBaseVoxelMeshRenderData::~FBaseVoxelMeshRenderData()
{
	if (LumenCardData != nullptr) delete LumenCardData;
}

ULFPBaseVoxelMeshComponent::ULFPBaseVoxelMeshComponent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;
}



void ULFPBaseVoxelMeshComponent::SetVoxelContainer(ULFPVoxelContainer* NewVoxelContainer, const int32 NewChuckIndex, const FName InitializeName)
{
	VoxelContainer = NewVoxelContainer;

	if (IsValid(VoxelContainer) && VoxelContainer->IsChuckIndexValid(NewChuckIndex))
	{
		ChuckInfo = VoxelContainer->GetChuckInfo(NewChuckIndex);

		VoxelContainer->ConnectVoxelUpdateEvent(NewChuckIndex, this, &ULFPBaseVoxelMeshComponent::UpdateVoxelMesh);

		VoxelContainer->InitializeOrUpdateChuck(NewChuckIndex, InitializeName);
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
	if (IsValid(VoxelContainer))
	{
		ChuckStatus.bIsVoxelMeshDirty = true;
	}
	else
	{
		UE_LOG(LFPVoxelMeshComponentLog, Warning, TEXT("Voxel Mesh Can't Be Update Because Voxel Container Is Not Valid"));
	}
}

void ULFPBaseVoxelMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (ChuckStatus.bIsVoxelMeshDirty)
	{
		if (ChuckStatus.bIsGeneratingMesh == false)
		{
			ChuckStatus.bIsGeneratingMesh = true;

			ChuckStatus.bIsVoxelMeshDirty = false;

			const FBoxSphereBounds LocalBounds = GetLocalBounds();

			const int32 SectionSize = FMath::Max(GetNumMaterials(), 1);

			AsyncTask(ENamedThreads::AnyNormalThreadNormalTask, [LocalVoxelContainer = VoxelContainer, LocalChuckInfo = ChuckInfo, LocalBounds, SectionSize, this]()
				{
					if (IsValid(this) == false || IsValid(LocalVoxelContainer) == false)
					{
						return;
					}

					FRWScopeLock ReadLock(LocalVoxelContainer->GetContainerThreadLock(), SLT_ReadOnly);

					FBaseVoxelMeshRenderData* NewRenderData = new FBaseVoxelMeshRenderData();

					NewRenderData->Sections.Init(FBaseVoxelMeshSectionData(), SectionSize);
					NewRenderData->DistanceFieldInstanceData.Reserve(LocalVoxelContainer->GetContainerSetting().VoxelLength);

					const TArray<FName>& VoxelNameList = LocalVoxelContainer->GetVoxelNameList(LocalChuckInfo.ChuckIndex);

					const FVector VoxelHalfSize = LocalVoxelContainer->GetContainerSetting().VoxelHalfSize;
					const FVector VoxelRenderOffset = -LocalVoxelContainer->GetContainerSetting().HalfRenderBound + LocalVoxelContainer->GetContainerSetting().VoxelHalfSize;

					FIntVector LumenBatch = LocalVoxelContainer->GetContainerSetting().VoxelGridSize / 4;
					
					if (LumenBatch.X == 0) LumenBatch.X = 1;
					if (LumenBatch.Y == 0) LumenBatch.Y = 1;
					if (LumenBatch.Z == 0) LumenBatch.Z = 1;

					TMap<FIntPoint, FBox> LumenBox;

					for (int32 VoxelIndex = 0; VoxelIndex < LocalVoxelContainer->GetContainerSetting().VoxelLength && IsValid(this); VoxelIndex++)
					{
						const FIntVector VoxelGridLocation = ULFPGridLibrary::IndexToGridLocation(VoxelIndex, LocalVoxelContainer->GetContainerSetting().VoxelGridSize);

						const FVector VoxelLocation = (FVector(VoxelGridLocation) * (VoxelHalfSize * 2)) + VoxelRenderOffset;

						const FLFPVoxelAttributeV2& VoxelAttribute = LocalVoxelContainer->GetVoxelAttributeByName(VoxelNameList[VoxelIndex]);

						const FVector2D VoxelUVOffset = VoxelAttribute.UVOffset;

						if (LocalVoxelContainer->IsVoxelVisibleByName(VoxelNameList[VoxelIndex]))
						{
							bool HasFace = false;

							const FBox VoxelBounds = FBox::BuildAABB(FVector3d(VoxelLocation), VoxelHalfSize);

							for (int32 FaceIndex = 0; FaceIndex < 6; FaceIndex++)
							{
								if (LocalVoxelContainer->IsVoxelVisible(LocalVoxelContainer->VoxelGridLocationToVoxelGridIndex(VoxelGridLocation + VoxelMeshConstantData.FaceCheckDirection[FaceIndex] + LocalChuckInfo.StartVoxelLocation)) == false)
								{
									const int32 MaterialID = VoxelAttribute.MaterialID < GetNumMaterials() ? VoxelAttribute.MaterialID : 0;

									AddVoxelFace(NewRenderData->Sections[MaterialID], VoxelIndex, VoxelLocation, VoxelUVOffset, FaceIndex, VoxelAttribute.VertexColor, VoxelHalfSize);

									AddLumenBox(LumenBox, VoxelLocation, FaceIndex, VoxelHalfSize, VoxelGridLocation, VoxelBounds, LumenBatch);

									HasFace = true;
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

						NewRenderData->LumenCardData->MeshCardsBuildData.Bounds = LocalBounds.GetBox();

						for (const auto& LumenBoxMap : LumenBox)
						{
							FLumenCardBuildData LumenCard;

							LumenCard.AxisAlignedDirectionIndex = VoxelMeshConstantData.SurfaceDirectionID[LumenBoxMap.Key.X];

							LumenCard.LODLevel = 0;

							FVector BoxExtent = LumenBoxMap.Value.GetExtent();

							LumenCard.OBB.Extent = FVector3f(VoxelMeshConstantData.VertexRotationList[LumenBoxMap.Key.X].UnrotateVector(BoxExtent).GetAbs());

							FRotationMatrix44f R(FRotator3f(VoxelMeshConstantData.VertexRotationList[LumenBoxMap.Key.X]));
							R.GetScaledAxes(LumenCard.OBB.AxisX, LumenCard.OBB.AxisY, LumenCard.OBB.AxisZ);

							LumenCard.OBB.Origin = FVector3f(LumenBoxMap.Value.GetCenter());

							NewRenderData->LumenCardData->MeshCardsBuildData.CardBuildData.Add(LumenCard);
						}
					}

					NewRenderData->DistanceFieldInstanceData.Shrink();

					AsyncTask(ENamedThreads::GameThread, [RenderData = NewRenderData, this]() {
						if (IsValid(this) == false) return;

						ChuckStatus.bIsGeneratingMesh = false;

						bool bIsVoxelMeshValid = false;

						for (const FBaseVoxelMeshSectionData& Buffer : RenderData->Sections)
						{
							if (Buffer.TriangleCount > 0)
							{
								bIsVoxelMeshValid = true;
							}
						}

						if (bIsVoxelMeshValid)
						{
							VoxelMeshRenderData = RenderData;

							if (IsValid(VoxelDistanceFieldMesh))
								VoxelMeshRenderData->DistanceFieldMeshData = VoxelDistanceFieldMesh->GetRenderData()->LODResources[0].DistanceFieldData;
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

void ULFPBaseVoxelMeshComponent::AddVoxelFace(FBaseVoxelMeshSectionData& EditMesh, const int32 VoxelIndex, const FVector VoxelLocation, const FVector2D UVOffset, const int32 FaceIndex, const FColor VoxelColor, const FVector LocalVoxelHalfSize)
{
	{
		const uint32 StartIndex = EditMesh.VertexList.Num();

		EditMesh.TriangleIndexList.Append({ StartIndex,1 + StartIndex,2 + StartIndex,3 + StartIndex,4 + StartIndex,5 + StartIndex });
	}

	EditMesh.VertexList.Append({
		FVector3f(VoxelMeshConstantData.VertexRotationList[FaceIndex].RotateVector(FVector( LocalVoxelHalfSize.X,-LocalVoxelHalfSize.Y, LocalVoxelHalfSize.Z)) + VoxelLocation),
		FVector3f(VoxelMeshConstantData.VertexRotationList[FaceIndex].RotateVector(FVector(-LocalVoxelHalfSize.X,-LocalVoxelHalfSize.Y, LocalVoxelHalfSize.Z)) + VoxelLocation),
		FVector3f(VoxelMeshConstantData.VertexRotationList[FaceIndex].RotateVector(FVector( LocalVoxelHalfSize.X, LocalVoxelHalfSize.Y, LocalVoxelHalfSize.Z)) + VoxelLocation),
		FVector3f(VoxelMeshConstantData.VertexRotationList[FaceIndex].RotateVector(FVector(-LocalVoxelHalfSize.X, LocalVoxelHalfSize.Y, LocalVoxelHalfSize.Z)) + VoxelLocation),
		FVector3f(VoxelMeshConstantData.VertexRotationList[FaceIndex].RotateVector(FVector( LocalVoxelHalfSize.X, LocalVoxelHalfSize.Y, LocalVoxelHalfSize.Z)) + VoxelLocation),
		FVector3f(VoxelMeshConstantData.VertexRotationList[FaceIndex].RotateVector(FVector(-LocalVoxelHalfSize.X,-LocalVoxelHalfSize.Y, LocalVoxelHalfSize.Z)) + VoxelLocation),
	});

	{
		const FVector2f UVSize = FVector2f(1.0f / 3.0f, 0.5f);
		const FVector2f FaceUVOffset = FVector2f(VoxelMeshConstantData.FaceUVStartOffset[FaceIndex] + UVOffset);

		EditMesh.UVList.Append({
			(FVector2f(0.0f,0.0f) + FaceUVOffset) * UVSize,
			(FVector2f(0.0f,1.0f) + FaceUVOffset) * UVSize,
			(FVector2f(1.0f,0.0f) + FaceUVOffset) * UVSize,
			(FVector2f(1.0f,1.0f) + FaceUVOffset) * UVSize,
			(FVector2f(1.0f,0.0f) + FaceUVOffset) * UVSize,
			(FVector2f(0.0f,1.0f) + FaceUVOffset) * UVSize
		});
	}

	EditMesh.VoxelColorList.Append({ VoxelColor ,VoxelColor });

	/* Add Index Trace */
	EditMesh.VoxelIndexList.Append({ VoxelIndex, VoxelIndex });

	EditMesh.TriangleCount += 2;
}

void ULFPBaseVoxelMeshComponent::AddLumenBox(TMap<FIntPoint, FBox>& LumenBox, const FVector VoxelLocation, const int32 FaceIndex, const FVector VoxelHalfSize, const FIntVector VoxelGridLocation, const FBox VoxelBounds, const FIntVector LumenBatch)
{
	FVector MinSurface = VoxelBounds.Min * VoxelMeshConstantData.SurfaceScale[FaceIndex];
	FVector MaxSurface = VoxelBounds.Max * VoxelMeshConstantData.SurfaceScale[FaceIndex];

	FVector CardOriginOffset = (VoxelLocation * FVector(VoxelMeshConstantData.FaceCheckDirection[FaceIndex]).GetAbs()) + (VoxelHalfSize * FVector(VoxelMeshConstantData.FaceCheckDirection[FaceIndex]));
	FVector Extention = VoxelMeshConstantData.LumenUpOffset * FVector(VoxelMeshConstantData.FaceCheckDirection[FaceIndex]).GetAbs();

	MinSurface += CardOriginOffset - Extention;
	MaxSurface += CardOriginOffset + Extention;

	int32 VoxelSurfaceIndex = 0;

	switch (FaceIndex)
	{
	    case 0: if (VoxelGridLocation.Z != 0) VoxelSurfaceIndex = VoxelGridLocation.Z / LumenBatch.Z; break;
		case 1: if (VoxelGridLocation.X != 0) VoxelSurfaceIndex = VoxelGridLocation.X / LumenBatch.X; break;
		case 2: if (VoxelGridLocation.Y != 0) VoxelSurfaceIndex = VoxelGridLocation.Y / LumenBatch.Y; break;
		case 3: if (VoxelGridLocation.X != 0) VoxelSurfaceIndex = VoxelGridLocation.X / LumenBatch.X; break;
		case 4: if (VoxelGridLocation.Y != 0) VoxelSurfaceIndex = VoxelGridLocation.Y / LumenBatch.Y; break;
		case 5: if (VoxelGridLocation.Z != 0) VoxelSurfaceIndex = VoxelGridLocation.Z / LumenBatch.Z; break;
	}

	if (LumenBox.Contains(FIntPoint(FaceIndex, VoxelSurfaceIndex)))
	{
		FBox& LocalLumenBox = LumenBox.FindChecked(FIntPoint(FaceIndex, VoxelSurfaceIndex));

		if (LocalLumenBox.Min.X > MinSurface.X) LocalLumenBox.Min.X = MinSurface.X;
		if (LocalLumenBox.Min.Y > MinSurface.Y) LocalLumenBox.Min.Y = MinSurface.Y;
		if (LocalLumenBox.Min.Z > MinSurface.Z) LocalLumenBox.Min.Z = MinSurface.Z;

		if (LocalLumenBox.Max.X < MaxSurface.X) LocalLumenBox.Max.X = MaxSurface.X;
		if (LocalLumenBox.Max.Y < MaxSurface.Y) LocalLumenBox.Max.Y = MaxSurface.Y;
		if (LocalLumenBox.Max.Z < MaxSurface.Z) LocalLumenBox.Max.Z = MaxSurface.Z;
	}
	else
	{
		LumenBox.Add(FIntPoint(FaceIndex, VoxelSurfaceIndex), FBox(MinSurface, MaxSurface));
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
	FBox VoxelBox;

	if (IsValid(VoxelContainer))
	{
		FRWScopeLock ReadLock(VoxelContainer->GetContainerThreadLock(), SLT_ReadOnly);

		const FVector& VoxelSize = VoxelContainer->GetContainerSetting().HalfRenderBound;

		VoxelBox = FBox(-VoxelSize, VoxelSize);
	}
	else
	{
		VoxelBox = FBox(-FVector(100.0f), FVector(100.0f));
	}

	FBoxSphereBounds Ret(VoxelBox.TransformBy(LocalToWorld));
	Ret.BoxExtent *= BoundsScale;
	Ret.SphereRadius *= BoundsScale;

	return Ret;
}

void ULFPBaseVoxelMeshComponent::GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials) const
{
	OutMaterials.Append(VoxelMaterialList);
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
			const FBaseVoxelMeshSectionData& Section = VoxelMeshRenderData->Sections[SectionIdx];

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
	return VoxelMaterialList.Num();
}

UMaterialInterface* ULFPBaseVoxelMeshComponent::GetMaterial(int32 ElementIndex) const
{
	return VoxelMaterialList.IsValidIndex(ElementIndex) ? VoxelMaterialList[ElementIndex] : nullptr;
}

void ULFPBaseVoxelMeshComponent::SetMaterial(int32 ElementIndex, UMaterialInterface* Material)
{
	check(ElementIndex >= 0);

	if (ElementIndex >= VoxelMaterialList.Num())
	{
		VoxelMaterialList.SetNum(ElementIndex + 1, false);
	}

	VoxelMaterialList[ElementIndex] = IsValid(Material) ? Material : UMaterial::GetDefaultMaterial(MD_Surface);
}

bool ULFPBaseVoxelMeshComponent::GetPhysicsTriMeshData(FTriMeshCollisionData* CollisionData, bool InUseAllTriData)
{
	if (VoxelMeshRenderData == nullptr) return false;

	int32 VertexBase = 0; // Base vertex index for current section

	CollisionData->UVs.AddZeroed(1);

	// For each section..
	for (int32 SectionIdx = 0; SectionIdx < VoxelMeshRenderData->Sections.Num(); SectionIdx++)
	{
		if (VoxelMeshRenderData->Sections[SectionIdx].TriangleCount == 0)
		{
			continue;
		}

		FBaseVoxelMeshSectionData& Section = VoxelMeshRenderData->Sections[SectionIdx];

		CollisionData->Vertices.Append(Section.VertexList);
		CollisionData->UVs[0].Append(Section.UVList);

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
	if (IsValid(VoxelMeshBodySetup) == false)
	{
		VoxelMeshBodySetup = CreateBodySetup();
	}

	return VoxelMeshBodySetup;
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
	if (VoxelMeshBodySetup->CurrentCookHelper)
	{
		ChuckStatus.bIsBodyInvalid = true;
	}
	else
	{
		VoxelMeshBodySetup->CreatePhysicsMeshesAsync(FOnAsyncPhysicsCookFinished::CreateUObject(this, &ULFPBaseVoxelMeshComponent::FinishPhysicsAsyncCook, VoxelMeshBodySetup.Get()));
	}
}

void ULFPBaseVoxelMeshComponent::FinishPhysicsAsyncCook(bool bSuccess, UBodySetup* FinishedBodySetup)
{
	if (ChuckStatus.bIsBodyInvalid)
	{
		ChuckStatus.bIsBodyInvalid = false;

		RecreatePhysicsState();

		RebuildPhysicsData();
	}
	else if (bSuccess)
	{
		RecreatePhysicsState();
	}
}

