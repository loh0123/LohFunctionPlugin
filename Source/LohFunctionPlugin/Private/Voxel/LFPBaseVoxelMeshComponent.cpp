// Copyright (c) 2022 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#include "Voxel/LFPBaseVoxelMeshComponent.h"
#include "./Math/LFPGridLibrary.h"
#include "Voxel/LFPBaseVoxelMeshSceneProxy.h"
#include "MeshCardRepresentation.h"
#include "Containers/ContainerAllocationPolicies.h"
#include "Kismet/KismetMathLibrary.h"
#include "Misc/QueuedThreadPoolWrapper.h"
#include "Render/LFPRenderLibrary.h"

DEFINE_LOG_CATEGORY(LFPVoxelMeshComponentLog);

FLFPBaseVoxelMeshLumenData::~FLFPBaseVoxelMeshLumenData()
{
	if (LumenCardData)
	{
		delete LumenCardData;
	}

	if (DistanceFieldMeshData)
	{
		delete DistanceFieldMeshData;
	}

	DistanceFieldMeshData = nullptr;
	LumenCardData = nullptr;
}

ULFPBaseVoxelMeshComponent::ULFPBaseVoxelMeshComponent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

	//bComputeFastLocalBounds = true;
}

void ULFPBaseVoxelMeshComponent::BeginDestroy()
{
	if (RenderTask && RenderTask->IsDone() == false)
	{
		RenderTask->EnsureCompletion(false);
	}

	if (LumenTask && LumenTask->IsDone() == false)
	{
		LumenTask->EnsureCompletion(false);
	}

	RenderData = nullptr;

	LumenData = nullptr;

	Super::BeginDestroy();
}

void ULFPBaseVoxelMeshComponent::SetVoxelContainer(const TArray<UMaterialInterface*>& Material, ULFPVoxelContainer* NewVoxelContainer, const int32 NewChuckIndex, const FName InitializeName)
{
	if (IsValid(NewVoxelContainer) && NewVoxelContainer->IsChuckIndexValid(NewChuckIndex))
	{
		if (Material.IsEmpty() == false)
		{
			for (int k = 0; k < Material.Num(); ++k)
			{
				SetMaterial(k, Material[k]);
			}
		}

		/* This Clean Up Color Map If Valid */
		if (IsValid(VoxelColorTexture))
		{
			VoxelColorTexture->MarkAsGarbage();

			VoxelColorTexture = nullptr;
		}

		/* This Clean Up Data Map If Valid */
		if (IsValid(VoxelDataTexture))
		{
			VoxelDataTexture->MarkAsGarbage();

			VoxelDataTexture = nullptr;
		}

		/* This Setup Texture */
		{
			const FIntVector VoxelGridSize = NewVoxelContainer->GetContainerSetting().VoxelGridSize;

			const FIntPoint VoxelTextureSize(VoxelGridSize.X + 2, (VoxelGridSize.Y + 2) * (VoxelGridSize.Z + 2));

			VoxelColorTexture = ULFPRenderLibrary::CreateTexture2D(VoxelTextureSize, TF_Nearest);
			VoxelDataTexture = ULFPRenderLibrary::CreateTexture2D(VoxelTextureSize, TF_Nearest);
		}

		/* This Setup Voxel */
		{
			VoxelContainer = NewVoxelContainer;

			ChuckInfo = VoxelContainer->GetChuckInfo(NewChuckIndex);

			VoxelContainer->ConnectVoxelUpdateEvent(NewChuckIndex, this, &ULFPBaseVoxelMeshComponent::UpdateVoxelMesh, &ULFPBaseVoxelMeshComponent::UpdateVoxelAttribute);

			VoxelContainer->FindOrAddChuckWriteAction(NewChuckIndex);
		}
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
		UpdateVoxelAttribute();
	}
	else
	{
		UE_LOG(LFPVoxelMeshComponentLog, Warning, TEXT("Can't Set Material Because Array Is Empty"));
	}
}

void ULFPBaseVoxelMeshComponent::UpdateVoxelMesh()
{
	if (IsValid(VoxelContainer) && VoxelContainer->IsChuckInitialized(ChuckInfo.ChuckIndex))
	{
		ChuckStatus.bIsVoxelMeshDirty = true;
	}
	else
	{
		UE_LOG(LFPVoxelMeshComponentLog, Warning, TEXT("Voxel Mesh Can't Be Update Because Voxel Container Is Not Valid"));
	}
}

void ULFPBaseVoxelMeshComponent::UpdateVoxelAttribute()
{
	if (IsValid(VoxelContainer) && VoxelContainer->IsChuckInitialized(ChuckInfo.ChuckIndex))
	{
		ChuckStatus.bIsVoxelAttributeDirty = true;
	}
	else
	{
		UE_LOG(LFPVoxelMeshComponentLog, Warning, TEXT("Voxel Color Can't Be Update Because Voxel Container Is Not Valid"));
	}
}

void ULFPBaseVoxelMeshComponent::BeginPlay()
{
	Super::BeginPlay();
}

void ULFPBaseVoxelMeshComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (RenderTask)
	{
		RenderTask->Cancel();
	}
	
	if (LumenTask)
	{
		LumenTask->Cancel();
	}

	if (IsValid(VoxelColorTexture))
	{
		VoxelColorTexture->MarkAsGarbage();

		VoxelColorTexture = nullptr;
	}

	if (IsValid(VoxelDataTexture))
	{
		VoxelDataTexture->MarkAsGarbage();

		VoxelDataTexture = nullptr;
	}

	if (IsValid(VoxelContainer))
	{
		VoxelContainer->DiconnectVoxelUpdateEvent(ChuckInfo.ChuckIndex);

		VoxelContainer = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}

void ULFPBaseVoxelMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (ChuckStatus.bIsVoxelAttributeDirty)
	{
		ChuckStatus.bIsVoxelAttributeDirty = false;

		const FIntVector DataColorGridSize = VoxelContainer->GetContainerSetting().VoxelGridSize + FIntVector(2);
		const int32 DataColorSize = DataColorGridSize.X * DataColorGridSize.Y * DataColorGridSize.Z;

		TArray<FColor> ColorList;
		TArray<FColor> AttributeList;

		ColorList.SetNum(DataColorSize);
		AttributeList.SetNum(DataColorSize);

		ParallelFor(DataColorSize,
			[&](const int32 Index) 
			{
				const FIntVector VoxelGlobalGridLocation = (ULFPGridLibrary::ToGridLocation(Index, DataColorGridSize) - FIntVector(1)) + ChuckInfo.StartVoxelLocation;
				const FLFPVoxelGridIndex VoxelGridIndex = VoxelContainer->ToVoxelGridIndex(VoxelGlobalGridLocation);

				const FName& VoxelName = VoxelContainer->GetVoxelName(VoxelGridIndex);
				const FLFPVoxelDynamicAttributeData& VoxelAttribute = VoxelContainer->GetVoxelDynamicAttribute(VoxelGridIndex);

				ColorList[Index] = VoxelAttribute.VoxelColor;
				
				AttributeList[Index].R = VoxelContainer->GetVoxelStaticAttributeByName(VoxelName).TextureOffset;
				AttributeList[Index].G = VoxelAttribute.VoxelStatus;
				AttributeList[Index].B = VoxelAttribute.VoxelType;
				AttributeList[Index].A = VoxelContainer->IsVoxelVisibleByName(VoxelName) ? 255 : 0;
			}
		);

		ULFPRenderLibrary::UpdateTexture2D(VoxelColorTexture, ColorList);
		ULFPRenderLibrary::UpdateTexture2D(VoxelDataTexture, AttributeList);
	}

	if (ChuckStatus.bIsVoxelMeshDirty && (RenderTask == nullptr || RenderTask->IsDone()))
	{
		ChuckStatus.bIsGeneratingMesh = true;

		ChuckStatus.bIsVoxelMeshDirty = false;

		FLFPBaseBoxelRenderParam RenderParam;

		RenderParam.LocalBounds = GetLocalBounds().ExpandBy(ChuckSetting.BoundExpand);
		RenderParam.LocalChuckInfo = ChuckInfo;
		RenderParam.LocalChuckSetting = ChuckSetting;
		RenderParam.LocalVoxelContainer = VoxelContainer;
		RenderParam.SectionSize = FMath::Max(GetNumMaterials(), 1);
		RenderParam.SharePtr = this;
		RenderParam.MaterialNum = GetNumMaterials();

		if (RenderTask == nullptr)
		{
			RenderTask = new FAsyncTask<FLFPBaseBoxelRenderTask>(RenderParam);
		}
		else
		{
			RenderTask->GetTask().RenderParam = RenderParam;
		}

		RenderTask->StartBackgroundTask();
	}

	if (ChuckStatus.bIsLumenDataDirty && (RenderTask == nullptr || RenderTask->IsDone()) && (LumenTask == nullptr || LumenTask->IsDone()))
	{
		if (ChuckStatus.LumenDelay > 0)
		{
			ChuckStatus.LumenDelay--;
		}
		else
		{
			ChuckStatus.bIsLumenDataDirty = false;
			ChuckStatus.bIsGeneratingLumen = true;
			ChuckStatus.LumenDelay = 30;

			FLFPBaseBoxelLumenParam LumenParam;

			//LumenParam.LODSectionData = new FStaticMeshLODResources();
			LumenParam.SharePtr = this;
			LumenParam.LocalBounds = GetLocalBounds().ExpandBy(ChuckSetting.BoundExpand);
			LumenParam.LocalChuckSetting = ChuckSetting;
			LumenParam.VoxelMaterialList = RenderData->VoxelMaterialList;
			LumenParam.VoxelSetting = VoxelContainer->GetContainerSetting();

			if (LumenTask == nullptr)
			{
				LumenTask = new FAsyncTask<FLFPBaseBoxelLumenTask>(LumenParam);
			}
			else
			{
				LumenTask->GetTask().LumenParam = LumenParam;
			}

			LumenTask->StartBackgroundTask();
		}
	}
}

void ULFPBaseVoxelMeshComponent::AddVoxelFace(FLFPBaseVoxelMeshRenderData& RenderParam, const int32 VoxelIndex, const FIntVector VoxelGridLocation, const FVector VoxelLocation, const FIntVector VoxelGlobalGridLocation, const int32 FaceIndex, const ULFPVoxelContainer* LocalVoxelContainer, const FLFPVoxelStaticAttributeData& VoxelAttribute, const FVector& LocalVoxelHalfSize)
{
	auto& EditMesh = RenderParam.Sections[RenderParam.VoxelMaterialList[VoxelIndex] - 1];

	/* Handle Index Data */
	{
		const uint32 StartIndex = EditMesh.VertexList.Num();

		EditMesh.TriangleIndexList.Append({ StartIndex, 1 + StartIndex, 2 + StartIndex, 3 + StartIndex, 4 + StartIndex, 5 + StartIndex });
	}

	/* Handle Vertex Data */
	{
		const FVector2f MinVertex = FVector2f(-1.0f);
		const FVector2f MaxVertex = FVector2f(1.0f);

		const TArray<FVector3f> VertexList =
		{
			FVector3f((ConstantData.VertexRotationList[FaceIndex].RotateVector(FVector(MinVertex.X, MinVertex.Y, 1.0f)) * LocalVoxelHalfSize) + VoxelLocation),
			FVector3f((ConstantData.VertexRotationList[FaceIndex].RotateVector(FVector(MaxVertex.X, MinVertex.Y, 1.0f)) * LocalVoxelHalfSize) + VoxelLocation),
			FVector3f((ConstantData.VertexRotationList[FaceIndex].RotateVector(FVector(MinVertex.X, MaxVertex.Y, 1.0f)) * LocalVoxelHalfSize) + VoxelLocation),
			FVector3f((ConstantData.VertexRotationList[FaceIndex].RotateVector(FVector(MaxVertex.X, MaxVertex.Y, 1.0f)) * LocalVoxelHalfSize) + VoxelLocation)
		};

		EditMesh.VertexList.Append({
			VertexList[1],
			VertexList[0],
			VertexList[3],
			VertexList[2],
			VertexList[3],
			VertexList[0],
		});

		RenderParam.LocalBounds.IsValid = true;

		for (const FVector3f& Vertex : VertexList)
		{
			RenderParam.LocalBounds += FVector(Vertex);
		}
	}

	/* Handle UV Data */
	{
		const FIntPoint& VoxelUVRound = LocalVoxelContainer->GetContainerSetting().VoxelUVRound;

		FIntPoint VoxelUVPosition = FIntPoint(VoxelGlobalGridLocation[ConstantData.FaceUVPositionMapping[FaceIndex].X], VoxelGlobalGridLocation[ConstantData.FaceUVPositionMapping[FaceIndex].Y]);

		VoxelUVPosition = FIntPoint((VoxelUVPosition.Y % VoxelUVRound.X), VoxelUVRound.Y - 1 - (VoxelUVPosition.X % VoxelUVRound.Y)); // Rotate The UV To Correct Position

		const FVector2f MinUVFaceOffset = FVector2f(VoxelUVPosition    ) / FVector2f(VoxelUVRound);
		const FVector2f MaxUVFaceOffset = FVector2f(VoxelUVPosition + 1) / FVector2f(VoxelUVRound);

		const FVector2f MinUVOffset = FVector2f(ConstantData.FaceUVStartOffset[FaceIndex]) + MinUVFaceOffset;
		const FVector2f MaxUVOffset = FVector2f(ConstantData.FaceUVStartOffset[FaceIndex]) + MaxUVFaceOffset;

		EditMesh.UVList.Append({
			FVector2f(MinUVOffset.X, MinUVOffset.Y),
			FVector2f(MinUVOffset.X, MaxUVOffset.Y),
			FVector2f(MaxUVOffset.X, MinUVOffset.Y),
			FVector2f(MaxUVOffset.X, MaxUVOffset.Y),
			FVector2f(MaxUVOffset.X, MinUVOffset.Y),
			FVector2f(MinUVOffset.X, MaxUVOffset.Y)
		});
	}

	/* Handle Edge And Point UV Data */
	{
		const TArray<uint8> VoxelEdgeList =
		{
			CheckVoxelDirectionVisible(LocalVoxelContainer , VoxelAttribute.MaterialID, VoxelGlobalGridLocation, ConstantData.FaceDirection[FaceIndex].Forward, ConstantData.FaceDirection[FaceIndex].Up),
			CheckVoxelDirectionVisible(LocalVoxelContainer , VoxelAttribute.MaterialID, VoxelGlobalGridLocation, ConstantData.FaceDirection[FaceIndex].Right, ConstantData.FaceDirection[FaceIndex].Up),
			CheckVoxelDirectionVisible(LocalVoxelContainer , VoxelAttribute.MaterialID, VoxelGlobalGridLocation, ConstantData.FaceDirection[FaceIndex].Forward * -1, ConstantData.FaceDirection[FaceIndex].Up),
			CheckVoxelDirectionVisible(LocalVoxelContainer , VoxelAttribute.MaterialID, VoxelGlobalGridLocation, ConstantData.FaceDirection[FaceIndex].Right * -1, ConstantData.FaceDirection[FaceIndex].Up),
		};

		const TArray<uint8> VoxelPointList =
		{
			(VoxelEdgeList[0] != 0 || VoxelEdgeList[3] != 0) ? uint8(0) : CheckVoxelDirectionVisible(LocalVoxelContainer, VoxelAttribute.MaterialID, VoxelGlobalGridLocation, (ConstantData.FaceDirection[FaceIndex].Forward	 ) + (ConstantData.FaceDirection[FaceIndex].Right * -1), ConstantData.FaceDirection[FaceIndex].Up),
			(VoxelEdgeList[0] != 0 || VoxelEdgeList[1] != 0) ? uint8(0) : CheckVoxelDirectionVisible(LocalVoxelContainer, VoxelAttribute.MaterialID, VoxelGlobalGridLocation, (ConstantData.FaceDirection[FaceIndex].Forward     ) + (ConstantData.FaceDirection[FaceIndex].Right     ), ConstantData.FaceDirection[FaceIndex].Up),
			(VoxelEdgeList[2] != 0 || VoxelEdgeList[1] != 0) ? uint8(0) : CheckVoxelDirectionVisible(LocalVoxelContainer, VoxelAttribute.MaterialID, VoxelGlobalGridLocation, (ConstantData.FaceDirection[FaceIndex].Forward * -1) + (ConstantData.FaceDirection[FaceIndex].Right     ), ConstantData.FaceDirection[FaceIndex].Up),
			(VoxelEdgeList[2] != 0 || VoxelEdgeList[3] != 0) ? uint8(0) : CheckVoxelDirectionVisible(LocalVoxelContainer, VoxelAttribute.MaterialID, VoxelGlobalGridLocation, (ConstantData.FaceDirection[FaceIndex].Forward * -1) + (ConstantData.FaceDirection[FaceIndex].Right * -1), ConstantData.FaceDirection[FaceIndex].Up),
		};

		const uint8 EdgeCount = (VoxelEdgeList[0] != 0 ? 1 : 0) + (VoxelEdgeList[1] != 0 ? 1 : 0) + (VoxelEdgeList[2] != 0 ? 1 : 0) + (VoxelEdgeList[3] != 0 ? 1 : 0);
		const uint8 PointCount = (VoxelPointList[0] != 0 ? 1 : 0) + (VoxelPointList[1] != 0 ? 1 : 0) + (VoxelPointList[2] != 0 ? 1 : 0) + (VoxelPointList[3] != 0 ? 1 : 0);

		int32 RotationIndex = 0;

		FVector2f TexPos = FVector2f(-1.0f, 0.0f);

		/* This Handle Edge UV */
		{
			RotationIndex = 0;

			TexPos = FVector2f(-1.0f, 0.0f);

			if (EdgeCount != 0)
			{
				const bool bIsSeperate =
					VoxelEdgeList[0] != 0 && VoxelEdgeList[2] != 0 && VoxelEdgeList[1] == 0 && VoxelEdgeList[3] == 0 ||
					VoxelEdgeList[1] != 0 && VoxelEdgeList[3] != 0 && VoxelEdgeList[0] == 0 && VoxelEdgeList[2] == 0;

				for (int32 Index = 0; Index < 4; Index++)
				{
					int32 PreIndex = (Index + 3) % 4;

					if (VoxelEdgeList[PreIndex] == 0 && VoxelEdgeList[Index] != 0)
					{
						RotationIndex = Index + 1;

						break;
					}
				}

				if (bIsSeperate)
				{
					TexPos = FVector2f(4.0f, 0.0f);
				}
				else
				{
					switch (EdgeCount)
					{
					case 1: TexPos = FVector2f(0.0f, 0.0f); break;
					case 2: TexPos = FVector2f(1.0f, 0.0f); break;
					case 3: TexPos = FVector2f(2.0f, 0.0f); break;
					case 4: TexPos = FVector2f(3.0f, 0.0f); break;
					}
				}
			}

			const TArray<FVector2f> UVPosList =
			{
				(FVector2f(0.5f,-0.5f).GetRotated(RotationIndex * -90.0f) + FVector2f(0.5f)),
				(FVector2f(-0.5f,-0.5f).GetRotated(RotationIndex * -90.0f) + FVector2f(0.5f)),
				(FVector2f(0.5f, 0.5f).GetRotated(RotationIndex * -90.0f) + FVector2f(0.5f)),
				(FVector2f(-0.5f, 0.5f).GetRotated(RotationIndex * -90.0f) + FVector2f(0.5f)),
			};

			EditMesh.EdgeUVList.Append({
				UVPosList[0] + TexPos,
				UVPosList[1] + TexPos,
				UVPosList[2] + TexPos,
				UVPosList[3] + TexPos,
				UVPosList[2] + TexPos,
				UVPosList[1] + TexPos
				});
		}

		/* This Handle Point UV */
		{
			RotationIndex = 0;

			TexPos = FVector2f(-1.0f, 0.0f);

			if (PointCount != 0)
			{
				const bool bIsSeperate =
					VoxelPointList[0] != 0 && VoxelPointList[2] != 0 && VoxelPointList[1] == 0 && VoxelPointList[3] == 0 ||
					VoxelPointList[1] != 0 && VoxelPointList[3] != 0 && VoxelPointList[0] == 0 && VoxelPointList[2] == 0;

				for (int32 Index = 0; Index < 4; Index++)
				{
					int32 PreIndex = (Index + 3) % 4;

					if (VoxelPointList[PreIndex] == 0 && VoxelPointList[Index] != 0)
					{
						RotationIndex = Index + 1;

						break;
					}
				}

				if (bIsSeperate)
				{
					TexPos = FVector2f(4.0f, 1.0f);
				}
				else
				{
					switch (PointCount)
					{
					case 1: TexPos = FVector2f(0.0f, 1.0f); break;
					case 2: TexPos = FVector2f(1.0f, 1.0f); break;
					case 3: TexPos = FVector2f(2.0f, 1.0f); break;
					case 4: TexPos = FVector2f(3.0f, 1.0f); break;
					}
				}
			}

			const TArray<FVector2f> UVPosList =
			{
				(FVector2f(0.5f,-0.5f).GetRotated(RotationIndex * -90.0f) + FVector2f(0.5f)),
				(FVector2f(-0.5f,-0.5f).GetRotated(RotationIndex * -90.0f) + FVector2f(0.5f)),
				(FVector2f(0.5f, 0.5f).GetRotated(RotationIndex * -90.0f) + FVector2f(0.5f)),
				(FVector2f(-0.5f, 0.5f).GetRotated(RotationIndex * -90.0f) + FVector2f(0.5f)),
			};

			EditMesh.PointUVList.Append({
				UVPosList[0] + TexPos,
				UVPosList[1] + TexPos,
				UVPosList[2] + TexPos,
				UVPosList[3] + TexPos,
				UVPosList[2] + TexPos,
				UVPosList[1] + TexPos
			});
		}
	}

	/* Handle Position UV Data */
	{
		const FIntPoint ColorMapSize = FIntPoint(LocalVoxelContainer->GetContainerSetting().VoxelGridSize.X, LocalVoxelContainer->GetContainerSetting().VoxelGridSize.Y * LocalVoxelContainer->GetContainerSetting().VoxelGridSize.Z);
		
		const FIntPoint CurrentIntUVPos = FIntPoint(VoxelGridLocation.X, VoxelGridLocation.Y + (LocalVoxelContainer->GetContainerSetting().VoxelGridSize.Y * VoxelGridLocation.Z));
		
		const FVector2f UVPos = FVector2f(CurrentIntUVPos) / FVector2f(ColorMapSize);
		
		EditMesh.PositionUVList.Append({
			UVPos,
			UVPos,
			UVPos,
			UVPos,
			UVPos,
			UVPos
			});
	}

	EditMesh.VoxelColorList.Append({
		VoxelAttribute.VertexColor,
		VoxelAttribute.VertexColor,
		VoxelAttribute.VertexColor,
		VoxelAttribute.VertexColor,
		VoxelAttribute.VertexColor,
		VoxelAttribute.VertexColor,
	});

	EditMesh.TriangleCount += 2;
}

uint8 ULFPBaseVoxelMeshComponent::CheckVoxelDirectionVisible(const ULFPVoxelContainer* LocalVoxelContainer, const int32 MateriaID, const FIntVector From, const FIntVector Direction, const FIntVector Up) const
{
	if (LocalVoxelContainer->IsVoxelVisible(LocalVoxelContainer->ToVoxelGridIndex(From + Direction + Up), MateriaID))
	{
		return 1;
	}
	else if (LocalVoxelContainer->IsVoxelVisible(LocalVoxelContainer->ToVoxelGridIndex(From + Direction), MateriaID))
	{
		return 0;
	}
	else
	{
		return 2;
	}
}

FPrimitiveSceneProxy* ULFPBaseVoxelMeshComponent::CreateSceneProxy()
{
	return (RenderData && RenderData->Sections.Num() == GetNumMaterials() && GetNumMaterials() != 0) ? new FLFPBaseVoxelMeshSceneProxy(this) : nullptr;
}

FBoxSphereBounds ULFPBaseVoxelMeshComponent::CalcBounds(const FTransform& LocalToWorld) const
{
	FBox VoxelBox;

	if (IsValid(VoxelContainer) && RenderData != nullptr)
	{
		VoxelBox = RenderData->LocalBounds.ExpandBy(ChuckSetting.BoundExpand);
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
	OutMaterials.Append(MaterialList);
}

UMaterialInterface* ULFPBaseVoxelMeshComponent::GetMaterialFromCollisionFaceIndex(int32 FaceIndex, int32& SectionIndex) const
{
	UMaterialInterface* Result = nullptr;
	SectionIndex = 0;

	if (RenderData && FaceIndex >= 0)
	{
		// Look for section that corresponds to the supplied face
		int32 TotalFaceCount = 0;

		for (int32 SectionIdx = 0; SectionIdx < RenderData->Sections.Num(); SectionIdx++)
		{
			const FLFPBaseVoxelMeshSectionData& Section = RenderData->Sections[SectionIdx];

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
	return MaterialList.Num();
}

UMaterialInterface* ULFPBaseVoxelMeshComponent::GetMaterial(int32 ElementIndex) const
{
	return MaterialList.IsValidIndex(ElementIndex) ? MaterialList[ElementIndex] : nullptr;
}

void ULFPBaseVoxelMeshComponent::SetMaterial(int32 ElementIndex, UMaterialInterface* Material)
{
	check(ElementIndex >= 0);

	if (ElementIndex >= MaterialList.Num())
	{
		MaterialList.SetNum(ElementIndex + 1, false);
	}

	MaterialList[ElementIndex] = IsValid(Material) ? Material : UMaterial::GetDefaultMaterial(MD_Surface);
}

bool ULFPBaseVoxelMeshComponent::GetPhysicsTriMeshData(FTriMeshCollisionData* CollisionData, bool InUseAllTriData)
{
	if (RenderData == nullptr) return false;

	int32 VertexBase = 0; // Base vertex index for current section

	CollisionData->UVs.AddZeroed(1);

	// For each section..
	for (int32 SectionIdx = 0; SectionIdx < RenderData->Sections.Num(); SectionIdx++)
	{
		if (RenderData->Sections[SectionIdx].TriangleCount == 0)
		{
			continue;
		}

		FLFPBaseVoxelMeshSectionData& Section = RenderData->Sections[SectionIdx];

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
	return RenderData != nullptr;
}

bool ULFPBaseVoxelMeshComponent::WantsNegXTriMesh()
{
	return false;
}

UBodySetup* ULFPBaseVoxelMeshComponent::GetBodySetup()
{
	if (IsValid(BodySetup) == false)
	{
		BodySetup = CreateBodySetup();
	}

	return BodySetup;
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
	if (BodySetup->CurrentCookHelper)
	{
		ChuckStatus.bIsBodyInvalid = true;
	}
	else
	{
		BodySetup->CreatePhysicsMeshesAsync(FOnAsyncPhysicsCookFinished::CreateUObject(this, &ULFPBaseVoxelMeshComponent::FinishPhysicsAsyncCook, BodySetup.Get()));
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

void FLFPBaseBoxelLumenTask::DoWork()
{
	ULFPBaseVoxelMeshComponent* OwnerPtr = LumenParam.SharePtr;

	FLFPBaseVoxelMeshLumenData* NewLumenData = new FLFPBaseVoxelMeshLumenData();

	NewLumenData->LumenCardData = GenerateLumenCard();

	NewLumenData->DistanceFieldMeshData = GenerateDistanceField();

	if (IsValid(OwnerPtr) && OwnerPtr->HasBegunPlay())
		AsyncTask(ENamedThreads::GameThread, [NewLumenData, SharePtr = TWeakObjectPtr<ULFPBaseVoxelMeshComponent>(LumenParam.SharePtr)]() {
			ULFPBaseVoxelMeshComponent* OwnerPtr = SharePtr.Get();

			if (SharePtr.IsValid() == false || IsValid(OwnerPtr) == false || OwnerPtr->HasBegunPlay() == false)
			{
				delete NewLumenData;
			}
			else
			{
				OwnerPtr->LumenData = NewLumenData;

				if (OwnerPtr->LumenData->DistanceFieldMeshData == nullptr || OwnerPtr->LumenData->LumenCardData == nullptr)
				{
					OwnerPtr->LumenData = nullptr;
				}

				OwnerPtr->ChuckStatus.bIsGeneratingLumen = false;
				OwnerPtr->MarkRenderStateDirty();
			}
		});
	else
		delete NewLumenData;

	LumenParam.Reset();

	return;
}

FDistanceFieldVolumeData* FLFPBaseBoxelLumenTask::GenerateDistanceField()
{
	//const double StartTime = FPlatformTime::Seconds();

	FDistanceFieldVolumeData* DistanceFieldMeshData = new FDistanceFieldVolumeData();
	
	const FVector& VoxelSize = LumenParam.VoxelSetting.VoxelHalfSize * 2;

	const FVector TargetDimensions = FVector(LumenParam.VoxelSetting.VoxelGridSize) * (double(LumenParam.LocalChuckSetting.VoxelPerDistanceField) / 8.0);

	const FIntVector MaxIndirectionDimensions(
		FMath::Clamp(FMath::RoundToInt32(TargetDimensions.X), 1, int32(DistanceField::MaxIndirectionDimension)),
		FMath::Clamp(FMath::RoundToInt32(TargetDimensions.Y), 1, int32(DistanceField::MaxIndirectionDimension)),
		FMath::Clamp(FMath::RoundToInt32(TargetDimensions.Z), 1, int32(DistanceField::MaxIndirectionDimension))
	);

	FBox LocalSpaceMeshBounds(LumenParam.LocalBounds.GetBox());
	{
		const FVector DesiredDimensions = FVector(LocalSpaceMeshBounds.GetSize() * FVector((float)DistanceField::UniqueDataBrickSize));
		
		const float CentralDifferencingExpandInVoxels = .25f;
		const FVector TexelObjectSpaceSize = LocalSpaceMeshBounds.GetSize() / FVector(MaxIndirectionDimensions * DistanceField::UniqueDataBrickSize - FIntVector(2 * CentralDifferencingExpandInVoxels));
		LocalSpaceMeshBounds = LocalSpaceMeshBounds.ExpandBy(TexelObjectSpaceSize);
	}
	
	const int32 BrickLength = DistanceField::BrickSize * DistanceField::BrickSize * DistanceField::BrickSize;

	DistanceFieldMeshData->AssetName = "Voxel Mesh";
	DistanceFieldMeshData->LocalSpaceMeshBounds = LocalSpaceMeshBounds;
	DistanceFieldMeshData->bMostlyTwoSided = true;
	
	const float LocalToVolumeScale = 1.0f / LocalSpaceMeshBounds.GetExtent().GetMax();
	const float LocalToVoxelScale = 1.0f / (LumenParam.VoxelSetting.VoxelHalfSize.GetMax() * LumenParam.LocalChuckSetting.VoxelDistanceFieldJump);
	
	TArray<uint8> StreamableMipData;
	
	for (int32 MipIndex = 0; MipIndex < DistanceField::NumMips; MipIndex++)
	{
		FSparseDistanceFieldMip& OutMip = DistanceFieldMeshData->Mips[MipIndex];
	
		const FIntVector IndirectionDimensions = FIntVector(
			FMath::DivideAndRoundUp(MaxIndirectionDimensions.X, 1 << MipIndex),
			FMath::DivideAndRoundUp(MaxIndirectionDimensions.Y, 1 << MipIndex),
			FMath::DivideAndRoundUp(MaxIndirectionDimensions.Z, 1 << MipIndex)
		);
	
		const int32 IndirectionDimensionsLength = IndirectionDimensions.X * IndirectionDimensions.Y * IndirectionDimensions.Z;
	
		TArray<uint8> DistanceFieldBrickData;
		TArray<uint32> IndirectionTable;
	
		IndirectionTable.Init(DistanceField::InvalidBrickIndex, IndirectionDimensionsLength);

		FLFPDFMipInfo MipInfo;
	
		SetDistanceFieldMipInfo(OutMip, IndirectionDimensions, LocalSpaceMeshBounds, LocalToVolumeScale, MipInfo);
	

		const FVector BrickSpaceSize = MipInfo.DistanceFieldVolumeBounds.GetSize() / FVector(IndirectionDimensions);
		const FVector BrickVoxelSize = BrickSpaceSize / DistanceField::UniqueDataBrickSize;
		const FVector BrickOffset = MipInfo.DistanceFieldVolumeBounds.Min + LumenParam.VoxelSetting.HalfRenderBound;

		const int32 CheckRange = FMath::CeilToInt(MipInfo.LocalSpaceTraceDistance * LocalToVoxelScale);

		UE_LOG(LogTemp, Warning, TEXT("The integer value is: %d"), CheckRange);

		struct FLFPDFBrickTask
		{
			FLFPDFBrickTask(const int32 InBrickLength, const FVector& InBrickVoxelSize, const int32 InBrickIndex, const FVector& InBrickSpaceLocation, const int32 InCheckRange, const float InLocalSpaceTraceDistance, const float InLocalToVolumeScale, const FVector2D& InDistanceFieldToVolumeScaleBias, const FLFPBaseBoxelLumenTask* InOwner)
				: BrickLength(InBrickLength), BrickIndex(InBrickIndex), BrickSpaceLocation(InBrickSpaceLocation), BrickVoxelSize(InBrickVoxelSize), CheckRange(InCheckRange), LocalSpaceTraceDistance(InLocalSpaceTraceDistance), LocalToVolumeScale(InLocalToVolumeScale), DistanceFieldToVolumeScaleBias(InDistanceFieldToVolumeScaleBias), Owner(InOwner)
			{}

			void DoTask()
			{
				BrickDataList.Init(0, BrickLength);

				for (int32 DataIndex = 0; DataIndex < 512 /* Brick Length */; DataIndex++)
				{
					const FIntVector DataLocation(ULFPGridLibrary::ToGridLocation(DataIndex, FIntVector(DistanceField::BrickSize)));
				
					const FVector BrickVoxelLocation = (FVector(DataLocation) * BrickVoxelSize) + BrickSpaceLocation;
				
					const float ClosetPoint = Owner->GetDistanceToClosetSurface(BrickVoxelLocation, LocalSpaceTraceDistance, CheckRange);
				
					// Transform to the tracing shader's Volume space
					const float VolumeSpaceDistance = ClosetPoint * LocalToVolumeScale;
					// Transform to the Distance Field texture's space
					const float RescaledDistance = (VolumeSpaceDistance - DistanceFieldToVolumeScaleBias.Y) / DistanceFieldToVolumeScaleBias.X;
				
					BrickDataList[DataIndex] = FMath::Clamp<int32>(FMath::FloorToInt(RescaledDistance * 255.0f + .5f), 0, 255);
				
					BrickMaxDistance = FMath::Max(BrickMaxDistance, BrickDataList[DataIndex]);
					BrickMinDistance = FMath::Min(BrickMinDistance, BrickDataList[DataIndex]);
				}
			}

			const int32 BrickLength;
			const int32 BrickIndex;
			const FVector BrickSpaceLocation;
			const FVector BrickVoxelSize;
			const int32 CheckRange;
			const float LocalSpaceTraceDistance;
			const float LocalToVolumeScale;
			const FVector2D DistanceFieldToVolumeScaleBias;
			const FLFPBaseBoxelLumenTask* Owner;

			TArray<uint8> BrickDataList;
			uint8 BrickMaxDistance = (MIN_uint8);
			uint8 BrickMinDistance = (MAX_uint8);
		};

		TArray<FLFPDFBrickTask> BrickTaskList;
		BrickTaskList.Reserve(IndirectionDimensionsLength);

		for (int32 BrickIndex = 0; BrickIndex < IndirectionDimensionsLength; BrickIndex++)
		{
			const FIntVector BrickLocation = (ULFPGridLibrary::ToGridLocation(BrickIndex, IndirectionDimensions));
			const FVector BrickSpaceLocation = (FVector(BrickLocation) * BrickSpaceSize) + BrickOffset;

			BrickTaskList.Add(FLFPDFBrickTask(
				BrickLength,
				BrickVoxelSize,
				BrickIndex,
				BrickSpaceLocation,
				CheckRange,
				MipInfo.LocalSpaceTraceDistance,
				LocalToVolumeScale,
				MipInfo.DistanceFieldToVolumeScaleBias,
				this
			));
		}

		EParallelForFlags Flags = EParallelForFlags::BackgroundPriority | EParallelForFlags::Unbalanced;

		ParallelForTemplate(BrickTaskList.Num(), [&BrickTaskList](int32 TaskIndex)
			{
				BrickTaskList[TaskIndex].DoTask();
			}, Flags);

		TArray<FLFPDFBrickTask*> ValidBricks;
		ValidBricks.Empty(BrickTaskList.Num());

		for (int32 TaskIndex = 0; TaskIndex < BrickTaskList.Num(); TaskIndex++)
		{
			if (BrickTaskList[TaskIndex].BrickMinDistance < MAX_uint8 && BrickTaskList[TaskIndex].BrickMaxDistance > MIN_uint8)
			{
				ValidBricks.Add(&BrickTaskList[TaskIndex]);
			}
		}

		const uint32 BrickSizeBytes = BrickLength * GPixelFormats[DistanceField::DistanceFieldFormat].BlockBytes;
		DistanceFieldBrickData.Empty(BrickSizeBytes * ValidBricks.Num());
		DistanceFieldBrickData.AddUninitialized(BrickSizeBytes* ValidBricks.Num());

		for (int32 BrickIndex = 0; BrickIndex < ValidBricks.Num(); BrickIndex++)
		{
			const FLFPDFBrickTask& Brick = *ValidBricks[BrickIndex];
			const int32 IndirectionIndex = Brick.BrickIndex;
			IndirectionTable[IndirectionIndex] = BrickIndex;

			const uint32 CopySize = Brick.BrickDataList.Num() * Brick.BrickDataList.GetTypeSize();

			check(BrickSizeBytes == CopySize);
			FPlatformMemory::Memcpy(&DistanceFieldBrickData[BrickIndex * BrickSizeBytes], Brick.BrickDataList.GetData(), CopySize);
		}
	
		const int32 IndirectionTableBytes = IndirectionTable.Num() * IndirectionTable.GetTypeSize();
		const int32 MipDataBytes = IndirectionTableBytes + DistanceFieldBrickData.Num();
	
		if (MipIndex == DistanceField::NumMips - 1)
		{
			DistanceFieldMeshData->AlwaysLoadedMip.Empty(MipDataBytes);
			DistanceFieldMeshData->AlwaysLoadedMip.AddUninitialized(MipDataBytes);
	
			FPlatformMemory::Memcpy(&DistanceFieldMeshData->AlwaysLoadedMip[0], IndirectionTable.GetData(), IndirectionTableBytes);
	
			if (DistanceFieldBrickData.Num() > 0)
			{
				FPlatformMemory::Memcpy(&DistanceFieldMeshData->AlwaysLoadedMip[IndirectionTableBytes], DistanceFieldBrickData.GetData(), DistanceFieldBrickData.Num());
			}

		}
		else
		{
			OutMip.BulkOffset = StreamableMipData.Num();
			StreamableMipData.AddUninitialized(MipDataBytes);
			OutMip.BulkSize = StreamableMipData.Num() - OutMip.BulkOffset;
			checkf(OutMip.BulkSize > 0, TEXT("BulkSize was 0 for Voxel Mesh with %ux%ux%u indirection"), IndirectionDimensions.X, IndirectionDimensions.Y, IndirectionDimensions.Z);
			
			FPlatformMemory::Memcpy(&StreamableMipData[OutMip.BulkOffset], IndirectionTable.GetData(), IndirectionTableBytes);
			
			if (DistanceFieldBrickData.Num() > 0)
			{
				FPlatformMemory::Memcpy(&StreamableMipData[OutMip.BulkOffset + IndirectionTableBytes], DistanceFieldBrickData.GetData(), DistanceFieldBrickData.Num());
			}
		}
	
		OutMip.NumDistanceFieldBricks = ValidBricks.Num();
	}
	
	DistanceFieldMeshData->StreamableMips.Lock(LOCK_READ_WRITE);
	uint8* Ptr = (uint8*)DistanceFieldMeshData->StreamableMips.Realloc(StreamableMipData.Num());
	FMemory::Memcpy(Ptr, StreamableMipData.GetData(), StreamableMipData.Num());
	DistanceFieldMeshData->StreamableMips.Unlock();
	DistanceFieldMeshData->StreamableMips.SetBulkDataFlags(BULKDATA_Force_NOT_InlinePayload);

	//UE_LOG(LogTemp, Warning, TEXT("Voxel Mesh Distance Field Generate Time Use : %f"), (float)(FPlatformTime::Seconds() - StartTime));

	return DistanceFieldMeshData;
}

void FLFPBaseBoxelLumenTask::SetDistanceFieldMipInfo(FSparseDistanceFieldMip& DistanceMip, const FIntVector& IndirectionDimensions, const FBox& LocalSpaceMeshBounds, const float LocalToVolumeScale, FLFPDFMipInfo& MipsInfo)
{	 
	// Expand to guarantee one voxel border for gradient reconstruction using bilinear filtering
	MipsInfo.TexelObjectSpaceSize = LocalSpaceMeshBounds.GetSize() / FVector(IndirectionDimensions * DistanceField::UniqueDataBrickSize - FIntVector(2 * DistanceField::MeshDistanceFieldObjectBorder));
	MipsInfo.DistanceFieldVolumeBounds = LocalSpaceMeshBounds.ExpandBy(MipsInfo.TexelObjectSpaceSize);

	MipsInfo.IndirectionVoxelSize = MipsInfo.DistanceFieldVolumeBounds.GetSize() / FVector(IndirectionDimensions);
	MipsInfo.VolumeSpaceDistanceFieldVoxelSize = MipsInfo.IndirectionVoxelSize * LocalToVolumeScale / FVector(DistanceField::UniqueDataBrickSize);
	MipsInfo.MaxDistanceForEncoding = MipsInfo.VolumeSpaceDistanceFieldVoxelSize.Size() * DistanceField::BandSizeInVoxels;
	MipsInfo.LocalSpaceTraceDistance = MipsInfo.MaxDistanceForEncoding / LocalToVolumeScale;
	MipsInfo.DistanceFieldToVolumeScaleBias = FVector2D(2.0f * MipsInfo.MaxDistanceForEncoding, -MipsInfo.MaxDistanceForEncoding);

	DistanceMip.DistanceFieldToVolumeScaleBias = MipsInfo.DistanceFieldToVolumeScaleBias;
	DistanceMip.IndirectionDimensions = IndirectionDimensions;

	// Account for the border voxels we added
	const FVector VirtualUVMin = FVector(DistanceField::MeshDistanceFieldObjectBorder) / FVector(IndirectionDimensions * DistanceField::UniqueDataBrickSize);
	const FVector VirtualUVSize = FVector(IndirectionDimensions * DistanceField::UniqueDataBrickSize - FIntVector(2 * DistanceField::MeshDistanceFieldObjectBorder)) / FVector(IndirectionDimensions * DistanceField::UniqueDataBrickSize);

	const FVector VolumePositionExtent = LocalSpaceMeshBounds.GetExtent() * LocalToVolumeScale;

	// [-VolumePositionExtent, VolumePositionExtent] -> [VirtualUVMin, VirtualUVMin + VirtualUVSize]
	DistanceMip.VolumeToVirtualUVScale = VirtualUVSize / (2 * VolumePositionExtent);
	DistanceMip.VolumeToVirtualUVAdd = VolumePositionExtent * DistanceMip.VolumeToVirtualUVScale + VirtualUVMin;
}

float FLFPBaseBoxelLumenTask::GetDistanceToClosetSurface(const FVector& LocalLocation, const float MaxDistance, const int32 CheckRange) const
{
	const FVector VoxelSize = LumenParam.VoxelSetting.VoxelHalfSize * 2;
	const FVector LocalSpace = LocalLocation / VoxelSize;
	const FIntVector GridLocation = FIntVector(FMath::FloorToInt32(LocalSpace.X), FMath::FloorToInt32(LocalSpace.Y), FMath::FloorToInt32(LocalSpace.Z));
	const int32 GridIndex = ULFPGridLibrary::ToIndex(GridLocation, LumenParam.VoxelSetting.VoxelGridSize);
	const uint8 SelfMaterial = GridIndex == INDEX_NONE ? 0 : LumenParam.VoxelMaterialList[GridIndex];

	float ClosetDistance = MaxDistance;


	for (int32 IndexZ = -CheckRange; IndexZ <= CheckRange; IndexZ++)
	{
		for (int32 IndexY = -CheckRange; IndexY <= CheckRange; IndexY++)
		{
			for (int32 IndexX = -CheckRange; IndexX <= CheckRange; IndexX++)
			{
				const FIntVector CheckVoxelDirection = FIntVector(IndexX, IndexY, IndexZ);
				const FIntVector CheckVoxelLocation = GridLocation + CheckVoxelDirection;
	
				const int32 CheckGridIndex = ULFPGridLibrary::ToIndex(CheckVoxelLocation, LumenParam.VoxelSetting.VoxelGridSize);
				const uint8 CheckMaterial = CheckGridIndex == INDEX_NONE ? 0 : LumenParam.VoxelMaterialList[CheckGridIndex];
	
				if (CheckMaterial != SelfMaterial)
				{
					const FBox VoxelBox = FBox::BuildAABB((FVector(CheckVoxelLocation) * VoxelSize) + LumenParam.VoxelSetting.VoxelHalfSize, LumenParam.VoxelSetting.VoxelHalfSize);
	
					ClosetDistance = FMath::Min(ClosetDistance, FMath::Sqrt(VoxelBox.ComputeSquaredDistanceToPoint(LocalLocation)) * LumenParam.LocalChuckSetting.VoxelDistanceMultiply);
				}
			}
		}
	}

	return SelfMaterial != 0 ? ClosetDistance * -1 : ClosetDistance;
}

FCardRepresentationData* FLFPBaseBoxelLumenTask::GenerateLumenCard()
{
	auto SetCoverIndex = [&](FIntPoint& CoverIndex, int32 Index)
	{
		if (Index <= -1)
		{
			CoverIndex = FIntPoint(INDEX_NONE);
		}
		else if (CoverIndex.GetMin() == INDEX_NONE)
		{
			CoverIndex = FIntPoint(Index);
		}
		else if (CoverIndex.X > Index)
		{
			CoverIndex.X = Index;
		}
		else if (CoverIndex.Y < Index)
		{
			CoverIndex.Y = Index;
		}
	};

	auto CheckFaceVisible = [&](const FIntVector& From, const FIntVector& Direction)
	{
		const int32 SelfMaterial = LumenParam.VoxelMaterialList[ULFPGridLibrary::ToIndex(From, LumenParam.VoxelSetting.VoxelGridSize)];

		if (ULFPGridLibrary::IsLocationValid(From + Direction, LumenParam.VoxelSetting.VoxelGridSize))
		{
			const int32 CheckMaterial = LumenParam.VoxelMaterialList[ULFPGridLibrary::ToIndex(From + Direction, LumenParam.VoxelSetting.VoxelGridSize)];

			return SelfMaterial != 0 && SelfMaterial != CheckMaterial;
		}

		return SelfMaterial != 0;
	};

	auto AddCardBuild = [&](TArray<FLumenCardBuildData>& CardBuildList, const FIntPoint& CoverIndex, const FBox& Bounds, const int32 DirectionIndex)
	{
		FBox LumenBox; 

		switch (DirectionIndex)
		{
		case 0:
		case 5:
			LumenBox = FBox(
				FVector(Bounds.Min.X, Bounds.Min.Y, (CoverIndex.X * LumenParam.VoxelSetting.VoxelHalfSize.Z * 2) - LumenParam.VoxelSetting.HalfRenderBound.Z - LumenParam.LocalChuckSetting.BoundExpand),
				FVector(Bounds.Max.X, Bounds.Max.Y, (CoverIndex.Y * LumenParam.VoxelSetting.VoxelHalfSize.Z * 2) - LumenParam.VoxelSetting.HalfRenderBound.Z + LumenParam.LocalChuckSetting.BoundExpand)
			);

			if (DirectionIndex == 0) LumenBox = LumenBox.ShiftBy(FVector(0.0f, 0.0f, LumenParam.VoxelSetting.VoxelHalfSize.Z) * 2.0f);
			break;

		case 1:
		case 3:
			LumenBox = FBox(
				FVector((CoverIndex.X * LumenParam.VoxelSetting.VoxelHalfSize.X * 2) - LumenParam.VoxelSetting.HalfRenderBound.X - LumenParam.LocalChuckSetting.BoundExpand, Bounds.Min.Y, Bounds.Min.Z),
				FVector((CoverIndex.Y * LumenParam.VoxelSetting.VoxelHalfSize.X * 2) - LumenParam.VoxelSetting.HalfRenderBound.X + LumenParam.LocalChuckSetting.BoundExpand, Bounds.Max.Y, Bounds.Max.Z)
			);

			if (DirectionIndex == 3) LumenBox = LumenBox.ShiftBy(FVector(LumenParam.VoxelSetting.VoxelHalfSize.X, 0.0f, 0.0f) * 2.0f);
			break;

		case 2:
		case 4:
			LumenBox = FBox(
				FVector(Bounds.Min.X, (CoverIndex.X * LumenParam.VoxelSetting.VoxelHalfSize.Y * 2) - LumenParam.VoxelSetting.HalfRenderBound.Y - LumenParam.LocalChuckSetting.BoundExpand, Bounds.Min.Z),
				FVector(Bounds.Max.X, (CoverIndex.Y * LumenParam.VoxelSetting.VoxelHalfSize.Y * 2) - LumenParam.VoxelSetting.HalfRenderBound.Y + LumenParam.LocalChuckSetting.BoundExpand, Bounds.Max.Z)
			);
			if (DirectionIndex == 2) LumenBox = LumenBox.ShiftBy(FVector(0.0f, LumenParam.VoxelSetting.VoxelHalfSize.Y, 0.0f) * 2.0f);
			break;
		}

		FLumenCardBuildData BuildData;

		BuildData.AxisAlignedDirectionIndex = LumenParam.SharePtr->ConstantData.SurfaceDirectionID[DirectionIndex];
		BuildData.LODLevel = 0;

		LumenParam.SharePtr->ConstantData.FaceDirection[DirectionIndex].SetAxis(
			BuildData.OBB.AxisX,
			BuildData.OBB.AxisY,
			BuildData.OBB.AxisZ
		);

		BuildData.OBB.Origin = FVector3f(LumenBox.GetCenter());
		BuildData.OBB.Extent = FVector3f(LumenParam.SharePtr->ConstantData.VertexRotationList[DirectionIndex].UnrotateVector(LumenBox.GetExtent()).GetAbs());

		CardBuildList.Add(BuildData);

		return;
	};

	//const double StartTime = FPlatformTime::Seconds();

	FCardRepresentationData* LumenCardData = new FCardRepresentationData();

	const FBox& Bounds = LumenParam.LocalBounds.GetBox();

	LumenCardData->MeshCardsBuildData.Bounds = Bounds;
	LumenCardData->MeshCardsBuildData.MaxLODLevel = 0;

	check(LumenCardData);

	TArray<FLumenCardBuildData>& CardBuildList = LumenCardData->MeshCardsBuildData.CardBuildData;

	struct FLFPFaceListData
	{
		FLFPFaceListData(const FIntVector InID, const int32 InFaceID, const bool InbIsReverse) : ID(InID), FaceID(InFaceID), bIsReverse(InbIsReverse) {}

		const FIntVector ID = FIntVector(0, 1, 2);
		const int32 FaceID = 0;
		const bool bIsReverse = false;
	};

	const TArray<FLFPFaceListData> FaceList =
	{
		FLFPFaceListData(FIntVector(0, 1, 2), 0, true),
		FLFPFaceListData(FIntVector(2, 1, 0), 1, false),
		FLFPFaceListData(FIntVector(2, 0, 1), 2, true),
		FLFPFaceListData(FIntVector(2, 1, 0), 3, true),
		FLFPFaceListData(FIntVector(2, 0, 1), 4, false),
		FLFPFaceListData(FIntVector(0, 1, 2), 5, false),
	};

	for (const FLFPFaceListData& FaceData : FaceList)
	{
		const FIntVector VoxelDimension = FIntVector(
			LumenParam.VoxelSetting.VoxelGridSize[FaceData.ID.X],
			LumenParam.VoxelSetting.VoxelGridSize[FaceData.ID.Y],
			LumenParam.VoxelSetting.VoxelGridSize[FaceData.ID.Z]
		);

		const int32 VoxelPlaneLength = VoxelDimension.X * VoxelDimension.Y;
	
		FIntPoint CoverIndex = FIntPoint(INDEX_NONE);

		TBitArray<> BlockMap = TBitArray(false, VoxelPlaneLength);
	
		for (int32 DepthIndex = FaceData.bIsReverse ? VoxelDimension.Z - 1 : 0; FaceData.bIsReverse ? DepthIndex > -1 : DepthIndex < VoxelDimension.Z; FaceData.bIsReverse ? DepthIndex-- : DepthIndex++)
		{
			StartCheck:

			for (int32 X = 0; X < VoxelDimension.X; X++)
			{
				for (int32 Y = 0; Y < VoxelDimension.Y; Y++)
				{
					FIntVector VoxelGridLocation;
					VoxelGridLocation[FaceData.ID.X] = X;
					VoxelGridLocation[FaceData.ID.Y] = Y;
					VoxelGridLocation[FaceData.ID.Z] = DepthIndex;

					const int32 VoxelPlaneIndex = X + (Y * VoxelDimension.X);

					const bool bIsFaceVisible = CheckFaceVisible(VoxelGridLocation, LumenParam.SharePtr->ConstantData.FaceDirection[FaceData.FaceID].Up);

					if (BlockMap[VoxelPlaneIndex])
					{
						if (bIsFaceVisible)
						{
							AddCardBuild(CardBuildList, CoverIndex, Bounds, FaceData.FaceID);

							/* Reset */
							BlockMap = TBitArray(false, VoxelPlaneLength);

							SetCoverIndex(CoverIndex, INDEX_NONE);

							goto StartCheck;
						}
					}
					else if (bIsFaceVisible)
					{	
						BlockMap[VoxelPlaneIndex] = bIsFaceVisible;

						SetCoverIndex(CoverIndex, DepthIndex);	
					}
				}
			}
		}

		if (CoverIndex.GetMin() != INDEX_NONE)
		{
			AddCardBuild(CardBuildList, CoverIndex, Bounds, FaceData.FaceID);
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("Voxel Mesh Lumen Card Generate Time Use : %f"), (float)(FPlatformTime::Seconds() - StartTime));

	return LumenCardData;
}

void FLFPBaseBoxelRenderTask::DoWork()
{
	ULFPBaseVoxelMeshComponent* OwnerPtr = RenderParam.SharePtr;

	FLFPBaseVoxelMeshRenderData* NewRenderData = new FLFPBaseVoxelMeshRenderData();

	RenderParam.LocalVoxelContainer->SetContainerThreadReading(true);

	FRWScopeLock ReadLock(RenderParam.LocalVoxelContainer->GetContainerThreadLock(), SLT_ReadOnly);

	NewRenderData->Sections.Init(FLFPBaseVoxelMeshSectionData(), RenderParam.SectionSize);

	const TArray<FName>& VoxelNameList = RenderParam.LocalVoxelContainer->GetVoxelNameList(RenderParam.LocalChuckInfo.ChuckIndex);

	const FVector VoxelHalfSize = RenderParam.LocalVoxelContainer->GetContainerSetting().VoxelHalfSize;
	const FVector VoxelRenderOffset = -RenderParam.LocalVoxelContainer->GetContainerSetting().HalfRenderBound + RenderParam.LocalVoxelContainer->GetContainerSetting().VoxelHalfSize;
	const FIntPoint VoxelUVRound = RenderParam.LocalVoxelContainer->GetContainerSetting().VoxelUVRound;

	FIntVector LumenBatch = RenderParam.LocalVoxelContainer->GetContainerSetting().VoxelGridSize / 4;

	if (LumenBatch.X == 0) LumenBatch.X = 1;
	if (LumenBatch.Y == 0) LumenBatch.Y = 1;
	if (LumenBatch.Z == 0) LumenBatch.Z = 1;

	NewRenderData->VoxelMaterialList.Init(0, RenderParam.LocalVoxelContainer->GetContainerSetting().VoxelLength);

	for (int32 VoxelIndex = 0; VoxelIndex < RenderParam.LocalVoxelContainer->GetContainerSetting().VoxelLength; VoxelIndex++)
	{
		const FIntVector VoxelGridLocation = ULFPGridLibrary::ToGridLocation(VoxelIndex, RenderParam.LocalVoxelContainer->GetContainerSetting().VoxelGridSize);

		const FVector VoxelLocation = (FVector(VoxelGridLocation) * (VoxelHalfSize * 2)) + VoxelRenderOffset;

		const FLFPVoxelStaticAttributeData& VoxelAttribute = RenderParam.LocalVoxelContainer->GetVoxelStaticAttributeByName(VoxelNameList[VoxelIndex]);

		if (RenderParam.LocalVoxelContainer->IsVoxelVisibleByName(VoxelNameList[VoxelIndex]))
		{
			const FBox VoxelBounds = FBox::BuildAABB(FVector3d(VoxelLocation), VoxelHalfSize);

			NewRenderData->VoxelMaterialList[VoxelIndex] = (VoxelAttribute.MaterialID < RenderParam.MaterialNum ? VoxelAttribute.MaterialID + 1 : 1);

			for (int32 FaceIndex = 0; FaceIndex < 6; FaceIndex++)
			{
				const FIntVector VoxelGlobalGridLocation = VoxelGridLocation + RenderParam.LocalChuckInfo.StartVoxelLocation;

				if (RenderParam.LocalVoxelContainer->IsVoxelVisible(RenderParam.LocalVoxelContainer->ToVoxelGridIndex(VoxelGlobalGridLocation + OwnerPtr->ConstantData.FaceDirection[FaceIndex].Up), RenderParam.LocalVoxelContainer->GetVoxelStaticAttributeByName(VoxelNameList[VoxelIndex]).MaterialID) == false)
				{
					OwnerPtr->AddVoxelFace(*NewRenderData, VoxelIndex, VoxelGridLocation, VoxelLocation, VoxelGlobalGridLocation, FaceIndex, RenderParam.LocalVoxelContainer, VoxelAttribute, VoxelHalfSize);
				}
			}
		}
	}

	RenderParam.LocalVoxelContainer->SetContainerThreadReading(false);

	if (IsValid(OwnerPtr) && OwnerPtr->HasBegunPlay())
		AsyncTask(ENamedThreads::GameThread, [NewRenderData, SharePtr = TWeakObjectPtr<ULFPBaseVoxelMeshComponent>(RenderParam.SharePtr)]() {
			ULFPBaseVoxelMeshComponent* OwnerPtr = SharePtr.Get();
			
			if (SharePtr.IsValid() == false || IsValid(OwnerPtr) == false || OwnerPtr->HasBegunPlay() == false)
			{
				delete NewRenderData;
			}
			else
			{
				bool bIsVoxelMeshValid = false;

				for (const FLFPBaseVoxelMeshSectionData& Buffer : NewRenderData->Sections)
				{
					if (Buffer.TriangleCount > 0)
					{
						bIsVoxelMeshValid = true;
					}
				}

				if (bIsVoxelMeshValid)
				{
					OwnerPtr->RenderData = NewRenderData;

					OwnerPtr->ChuckStatus.bIsLumenDataDirty = true;
				}
				else
				{
					OwnerPtr->RenderData = nullptr;

					delete NewRenderData;
				}

				OwnerPtr->ChuckStatus.bIsGeneratingMesh = false;

				OwnerPtr->UpdateBounds();
				OwnerPtr->MarkRenderStateDirty();
				OwnerPtr->RebuildPhysicsData();
			}
		});
	else
		delete NewRenderData;
}
