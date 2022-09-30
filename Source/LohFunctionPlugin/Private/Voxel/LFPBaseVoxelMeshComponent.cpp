// Copyright (c) 2022 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#include "Voxel/LFPBaseVoxelMeshComponent.h"
#include "./Math/LFPGridLibrary.h"
#include "Voxel/LFPBaseVoxelMeshSceneProxy.h"
#include "MeshCardRepresentation.h"
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

	Super::BeginDestroy();
}

void ULFPBaseVoxelMeshComponent::SetVoxelContainer(ULFPVoxelContainer* NewVoxelContainer, const int32 NewChuckIndex, const FName InitializeName)
{
	if (IsValid(NewVoxelContainer) && NewVoxelContainer->IsChuckIndexValid(NewChuckIndex))
	{
		if (!MeshUtilities)
		{
			MeshUtilities = &FModuleManager::Get().LoadModuleChecked<IMeshUtilities>(TEXT("MeshUtilities"));
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

		/* THis Setup Texture */
		{
			const FIntVector VoxelGridSize = NewVoxelContainer->GetContainerSetting().VoxelGridSize;

			VoxelColorTexture = ULFPRenderLibrary::CreateTexture2D(FIntPoint(VoxelGridSize.X, VoxelGridSize.Y * VoxelGridSize.Z), TF_Nearest);
			VoxelDataTexture = ULFPRenderLibrary::CreateTexture2D(FIntPoint(VoxelGridSize.X + 2, (VoxelGridSize.Y + 2) * (VoxelGridSize.Z + 2)), TF_Nearest);
		}

		/* This Setup Voxel */
		{
			VoxelContainer = NewVoxelContainer;

			ChuckInfo = VoxelContainer->GetChuckInfo(NewChuckIndex);

			VoxelContainer->ConnectVoxelUpdateEvent(NewChuckIndex, this, &ULFPBaseVoxelMeshComponent::UpdateVoxelMesh, &ULFPBaseVoxelMeshComponent::UpdateVoxelColor);

			VoxelContainer->InitializeOrUpdateChuck(NewChuckIndex, InitializeName);
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
		ChuckStatus.bIsVoxelDataDirty = true;
	}
	else
	{
		UE_LOG(LFPVoxelMeshComponentLog, Warning, TEXT("Voxel Mesh Can't Be Update Because Voxel Container Is Not Valid"));
	}
}

void ULFPBaseVoxelMeshComponent::UpdateVoxelColor()
{
	if (IsValid(VoxelContainer))
	{
		ChuckStatus.bIsVoxelColorDirty = true;
	}
	else
	{
		UE_LOG(LFPVoxelMeshComponentLog, Warning, TEXT("Voxel Color Can't Be Update Because Voxel Container Is Not Valid"));
	}
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

	RenderData = nullptr;
	LumenData = nullptr;

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

	Super::EndPlay(EndPlayReason);
}

void ULFPBaseVoxelMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (ChuckStatus.bIsVoxelColorDirty)
	{
		ChuckStatus.bIsVoxelColorDirty = false;

		ULFPRenderLibrary::UpdateTexture2D(VoxelColorTexture, VoxelContainer->GetVoxelColorList(ChuckInfo.ChuckIndex));
	}

	if (ChuckStatus.bIsVoxelDataDirty)
	{
		ChuckStatus.bIsVoxelDataDirty = false;

		const FIntVector DataColorGridSize = VoxelContainer->GetContainerSetting().VoxelGridSize + FIntVector(2);
		const int32 DataColorSize = DataColorGridSize.X * DataColorGridSize.Y * DataColorGridSize.Z;

		TArray<FColor> DataColorList;

		DataColorList.SetNum(DataColorSize);

		ParallelFor(DataColorSize,
			[&](const int32 Index) 
			{
				const FIntVector VoxelGlobalGridLocation = (ULFPGridLibrary::IndexToGridLocation(Index, DataColorGridSize) - FIntVector(1)) + ChuckInfo.StartVoxelLocation;

				const FName& VoxelName = VoxelContainer->GetVoxelName(VoxelContainer->VoxelGridLocationToVoxelGridIndex(VoxelGlobalGridLocation));
				
				DataColorList[Index].R = VoxelContainer->GetVoxelAttributeByName(VoxelName).TextureOffset;
				DataColorList[Index].A = VoxelContainer->IsVoxelVisibleByName(VoxelName) ? 255 : 0;
			}
		);

		ULFPRenderLibrary::UpdateTexture2D(VoxelDataTexture, DataColorList);
	}

	if (ChuckStatus.bIsVoxelMeshDirty && (RenderTask == nullptr || RenderTask->IsDone()))
	{
		ChuckStatus.bIsGeneratingMesh = true;

		ChuckStatus.bIsVoxelMeshDirty = false;

		FLFPBaseBoxelRenderParam RenderParam;

		RenderParam.LocalBounds = GetLocalBounds();
		RenderParam.LocalChuckInfo = ChuckInfo;
		RenderParam.LocalChuckSetting = ChuckSetting;
		RenderParam.LocalVoxelContainer = VoxelContainer;
		RenderParam.SectionSize = FMath::Max(GetNumMaterials(), 1);
		RenderParam.SharePtr = this;

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
		ChuckStatus.bIsLumenDataDirty = false;
		ChuckStatus.bIsGeneratingLumen = true;

		FLFPBaseBoxelLumenParam LumenParam;

		LumenParam.LODSectionData = new FStaticMeshLODResources();
		LumenParam.SharePtr = this;
		LumenParam.LocalBounds = GetLocalBounds();
		LumenParam.LocalChuckSetting = ChuckSetting;

		for (int32 SectionIndex = 0; SectionIndex < RenderData->Sections.Num(); SectionIndex++)
		{
			{
				FStaticMeshSection Section;
				Section.MaterialIndex = SectionIndex;

				LumenParam.LODSectionData->Sections.Add(Section);
			}

			{
				FSignedDistanceFieldBuildMaterialData MaterialData;
				// Default material blend mode
				MaterialData.BlendMode = BLEND_Opaque;
				MaterialData.bTwoSided = false;

				if (IsValid(GetMaterial(SectionIndex)))
				{
					MaterialData.BlendMode = GetMaterial(SectionIndex)->GetBlendMode();
					MaterialData.bTwoSided = GetMaterial(SectionIndex)->IsTwoSided();
				}

				if (MaterialData.bTwoSided)
				{
					LumenParam.bIsTwoSide = true;
				}

				LumenParam.LocalMaterialBlendModes.Add(MaterialData);
			}

			{
				const FLFPBaseVoxelMeshSectionData& SectionData = RenderData->Sections[SectionIndex];

				LumenParam.LocalSourceMeshData.VertexPositions.Append(SectionData.VertexList);

				const uint32 StartIndex = LumenParam.LocalSourceMeshData.TriangleIndices.Num();

				LumenParam.LocalSourceMeshData.TriangleIndices.Reserve(LumenParam.LocalSourceMeshData.TriangleIndices.Num() + SectionData.TriangleIndexList.Num());

				for (const uint32 TriangleIndex : SectionData.TriangleIndexList)
				{
					LumenParam.LocalSourceMeshData.TriangleIndices.Add(TriangleIndex + StartIndex);
				}
			}
		}

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

void ULFPBaseVoxelMeshComponent::AddVoxelFace(FLFPBaseVoxelMeshSectionData& EditMesh, FBox& LocalBounds, const int32 VoxelIndex, const FIntVector VoxelGridLocation, const FVector VoxelLocation, const FIntVector VoxelGlobalGridLocation, const int32 FaceIndex, const ULFPVoxelContainer* LocalVoxelContainer, const FLFPVoxelAttributeV2& VoxelAttribute, const FVector& LocalVoxelHalfSize)
{
	/* Handle Index Data */
	{
		const uint32 StartIndex = EditMesh.VertexList.Num();

		EditMesh.TriangleIndexList.Append({ StartIndex, 1 + StartIndex, 2 + StartIndex, 3 + StartIndex, 4 + StartIndex, 5 + StartIndex });
	}

	/* Handle Vertex Data */
	{
		const FVector3f MinVertex = FVector3f(-LocalVoxelHalfSize.X, -LocalVoxelHalfSize.Y, LocalVoxelHalfSize.Z);
		const FVector3f MaxVertex = FVector3f(LocalVoxelHalfSize);

		const TArray<FVector3f> VertexList =
		{
			FVector3f(ConstantData.VertexRotationList[FaceIndex].RotateVector(FVector(MinVertex.X, MinVertex.Y, MaxVertex.Z)) + VoxelLocation),
			FVector3f(ConstantData.VertexRotationList[FaceIndex].RotateVector(FVector(MaxVertex.X, MinVertex.Y, MaxVertex.Z)) + VoxelLocation),
			FVector3f(ConstantData.VertexRotationList[FaceIndex].RotateVector(FVector(MinVertex.X, MaxVertex.Y, MaxVertex.Z)) + VoxelLocation),
			FVector3f(ConstantData.VertexRotationList[FaceIndex].RotateVector(FVector(MaxVertex.X, MaxVertex.Y, MaxVertex.Z)) + VoxelLocation)
		};

		EditMesh.VertexList.Append({
			VertexList[1],
			VertexList[0],
			VertexList[3],
			VertexList[2],
			VertexList[3],
			VertexList[0],
		});

		LocalBounds.IsValid = true;

		for (const FVector3f& Vertex : VertexList)
		{
			LocalBounds += FVector(Vertex);
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
	if (LocalVoxelContainer->IsVoxelVisible(LocalVoxelContainer->VoxelGridLocationToVoxelGridIndex(From + Direction + Up), MateriaID))
	{
		return 1;
	}
	else if (LocalVoxelContainer->IsVoxelVisible(LocalVoxelContainer->VoxelGridLocationToVoxelGridIndex(From + Direction), MateriaID))
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
	if (RenderData && RenderData->Sections.Num() == GetNumMaterials() && GetNumMaterials() != 0)
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

	if (LumenParam.LocalSourceMeshData.IsValid())
	{
		NewLumenData->DistanceFieldMeshData = new FDistanceFieldVolumeData();

		NewLumenData->LumenCardData = new FCardRepresentationData();;

		FQueuedThreadPoolTaskGraphWrapper SDPPool(ENamedThreads::AnyBackgroundThreadNormalTask);

		OwnerPtr->MeshUtilities->GenerateSignedDistanceFieldVolumeData(
			"VoxelMesh",
			LumenParam.LocalSourceMeshData,
			*LumenParam.LODSectionData,
			SDPPool,
			LumenParam.LocalMaterialBlendModes,
			LumenParam.LocalBounds,
			LumenParam.LocalChuckSetting.DistanceFieldResolution,
			LumenParam.bIsTwoSide,
			*NewLumenData->DistanceFieldMeshData
		);

		/* Fill In Lumen Data */
		OwnerPtr->MeshUtilities->GenerateCardRepresentationData(
			"VoxelMesh",
			LumenParam.LocalSourceMeshData,
			*LumenParam.LODSectionData,
			SDPPool,
			LumenParam.LocalMaterialBlendModes,
			LumenParam.LocalBounds,
			NewLumenData->DistanceFieldMeshData,
			LumenParam.LocalChuckSetting.LumenCardAmount,
			LumenParam.bIsTwoSide,
			*NewLumenData->LumenCardData
		);
	}

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

void FLFPBaseBoxelRenderTask::DoWork()
{
	ULFPBaseVoxelMeshComponent* OwnerPtr = RenderParam.SharePtr;

	FLFPBaseVoxelMeshRenderData* NewRenderData = new FLFPBaseVoxelMeshRenderData();

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

	for (int32 VoxelIndex = 0; VoxelIndex < RenderParam.LocalVoxelContainer->GetContainerSetting().VoxelLength; VoxelIndex++)
	{
		const FIntVector VoxelGridLocation = ULFPGridLibrary::IndexToGridLocation(VoxelIndex, RenderParam.LocalVoxelContainer->GetContainerSetting().VoxelGridSize);

		const FVector VoxelLocation = (FVector(VoxelGridLocation) * (VoxelHalfSize * 2)) + VoxelRenderOffset;

		const FLFPVoxelAttributeV2& VoxelAttribute = RenderParam.LocalVoxelContainer->GetVoxelAttributeByName(VoxelNameList[VoxelIndex]);

		if (RenderParam.LocalVoxelContainer->IsVoxelVisibleByName(VoxelNameList[VoxelIndex]))
		{
			const FBox VoxelBounds = FBox::BuildAABB(FVector3d(VoxelLocation), VoxelHalfSize);

			for (int32 FaceIndex = 0; FaceIndex < 6; FaceIndex++)
			{
				const FIntVector VoxelGlobalGridLocation = VoxelGridLocation + RenderParam.LocalChuckInfo.StartVoxelLocation;

				if (RenderParam.LocalVoxelContainer->IsVoxelVisible(RenderParam.LocalVoxelContainer->VoxelGridLocationToVoxelGridIndex(VoxelGlobalGridLocation + OwnerPtr->ConstantData.FaceDirection[FaceIndex].Up), RenderParam.LocalVoxelContainer->GetVoxelAttributeByName(VoxelNameList[VoxelIndex]).MaterialID) == false)
				{
					const int32 MaterialID = VoxelAttribute.MaterialID < OwnerPtr->GetNumMaterials() ? VoxelAttribute.MaterialID : 0;

					OwnerPtr->AddVoxelFace(NewRenderData->Sections[MaterialID], NewRenderData->LocalBounds, VoxelIndex, VoxelGridLocation, VoxelLocation, VoxelGlobalGridLocation, FaceIndex, RenderParam.LocalVoxelContainer, VoxelAttribute, VoxelHalfSize);
				}
			}
		}
	}

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
