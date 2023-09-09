// Copyright by Loh Zhi Kang


#include "Voxel/LFPVoxelRendererComponent.h"
#include "Voxel/LFPVoxelRendererSceneProxy.h"
#include "Components/LFPGridContainerComponent.h"
#include "DistanceFieldAtlas.h"
#include "MaterialDomain.h"
#include "MeshCardBuild.h"
#include "Math/LFPGridLibrary.h"

using namespace UE::Tasks;

FLFPGridPaletteData FLFPGridPaletteData::EmptyData = FLFPGridPaletteData();

uint32 FLFPVoxelRendererStatus::CurrentDynamicAmount = 1;

uint32 FLFPVoxelRendererStatus::CurrentStaticAmount = 1;

DEFINE_LOG_CATEGORY(LFPVoxelRendererComponent);

/** Core Handling */

// Sets default values for this component's properties
ULFPVoxelRendererComponent::ULFPVoxelRendererComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.01f;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	// ...
}

// Called when the game starts
void ULFPVoxelRendererComponent::BeginPlay()
{
	Super::BeginPlay();

	Status.DynamicUpdateDelay = GenerationSetting.DynamicUpdateDelayPerComponent;
	Status.StaticUpdateDelay = GenerationSetting.StaticUpdateDelayPerComponent;
}

void ULFPVoxelRendererComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	ReleaseRenderer();

	if (IsValid(BodySetup))
	{
		BodySetup->InvalidatePhysicsData();
		BodySetup = nullptr;
	}

	ThreadOutput.Wait();

	ThreadResult.Reset();

	ThreadOutput = {};
}

void ULFPVoxelRendererComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsValid(VoxelContainer) == false) return;

	if (AttributeOutput.IsCompleted() && Status.CanUpdateAttribute() && IsValid(AttributesTexture))
	{
		AttributeOutput =
			Launch(UE_SOURCE_LOCATION,
				[&,
				CurrentContainer = VoxelContainer,
				CurrentSetting = GenerationSetting,
				DataColorGridSize = VoxelContainer->GetSetting().GetPaletteGrid(),
				RegionIndexList = Status.VoxelAttributeDirtyHeightList.Array(),
				CurrentTexture = AttributesTexture]
				{
					const int32 DataColorSize = DataColorGridSize.X * DataColorGridSize.Y * DataColorGridSize.Z;

					const int32 BufferSize = 4;

					const double TaskTime = FPlatformTime::Seconds();

					if (IsValid(this) == false) return;

					FReadScopeLock Lock(CurrentContainer->ContainerThreadLock);

					const int32 RegionLength = DataColorGridSize.X * DataColorGridSize.Y;

					uint8* AttributeDataList = new uint8[RegionLength * RegionIndexList.Num() * BufferSize];
					FUpdateTextureRegion2D* RegionUpdateList = new FUpdateTextureRegion2D[RegionIndexList.Num()];
					int32 RegionAmount = RegionIndexList.Num();

					int32 CurrentPixelIndex = 0;

					for (int32 ScrIndex = 0; ScrIndex < RegionIndexList.Num(); ScrIndex++)
					{
						const int32 StartIndex = RegionIndexList[ScrIndex] * RegionLength;
						const int32 EndIndex = (RegionIndexList[ScrIndex] + 1) * RegionLength;

						for (int32 Index = StartIndex; Index < EndIndex; Index++)
						{
							const FIntVector VoxelGlobalGridLocation = ULFPGridLibrary::ToGridLocation(Index, DataColorGridSize) + VoxelContainer->ToGridGlobalPosition(FIntVector(RegionIndex, ChuckIndex, 0));
							const FIntVector VoxelGridIndex = VoxelContainer->ToGridGlobalIndex(VoxelGlobalGridLocation);

							const FLFPGridPaletteData& VoxelPalette = VoxelContainer->GetGridPaletteRef(VoxelGridIndex.X, VoxelGridIndex.Y, VoxelGridIndex.Z);

							TMap<FName, uint8> TagDataList;

							if (VoxelGridIndex.Z >= 0) VoxelContainer->GetGridChuckRef(VoxelGridIndex.X, VoxelGridIndex.Y).GetTagDataList(VoxelGridIndex.Z, TagDataList);

							const FColor CacheAttributeData = GetVoxelAttribute(VoxelPalette, TagDataList);

							const int32 PixelPos = CurrentPixelIndex * BufferSize;

							*(AttributeDataList + PixelPos) = CacheAttributeData.B;
							*(AttributeDataList + PixelPos + 1) = CacheAttributeData.G;
							*(AttributeDataList + PixelPos + 2) = CacheAttributeData.R;
							*(AttributeDataList + PixelPos + 3) = CacheAttributeData.A;

							CurrentPixelIndex++;
						}

						const int32 TexturePosY = DataColorGridSize.Y * RegionIndexList[ScrIndex];
						const int32 ScrPosY = DataColorGridSize.Y * ScrIndex;

						*(RegionUpdateList + ScrIndex) = FUpdateTextureRegion2D(0, TexturePosY, 0, ScrPosY, DataColorGridSize.X, DataColorGridSize.Y);
					}

					ULFPRenderLibrary::UpdateTexture2D(AttributesTexture, AttributeDataList, RegionUpdateList, RegionAmount);

					if (GenerationSetting.bPrintGenerateTime) UE_LOG(LogTemp, Warning, TEXT("Attribute Data Time Use : %f"), (float)(FPlatformTime::Seconds() - TaskTime));

					return;
				}, ETaskPriority::High, EExtendedTaskPriority::Inline);

		Status.VoxelAttributeDirtyHeightList.Empty();
	}

	if (ThreadOutput.IsCompleted() == false) return;

	/** Is Tick Logic Cooling Down Or Is Not Rendering */
	if (Status.DecreaseTickCounter() == false) return;

	switch (Status.GetCurrentRenderMode())
	{
	case ELFPVoxelRendererMode::LFP_Dynamic:
	case ELFPVoxelRendererMode::LFP_Static:
	{
		if (Status.GetCurrentRenderMode() == ELFPVoxelRendererMode::LFP_Dynamic)
		{
			ThreadOutput =
				Launch(UE_SOURCE_LOCATION, [&, CurrentContainer = VoxelContainer, CurrentSetting = GenerationSetting]
					{
						TSharedPtr<FLFPVoxelRendererThreadResult> TargetThreadResult = MakeShared<FLFPVoxelRendererThreadResult>();

						if (IsValid(this) == false) return TargetThreadResult;

						FReadScopeLock Lock(CurrentContainer->ContainerThreadLock);

						GenerateBatchFaceData(CurrentContainer, TargetThreadResult, CurrentSetting);

						if (CurrentSetting.bGenerateSimpleCollisionData) GenerateSimpleCollisionData(CurrentContainer, TargetThreadResult, CurrentSetting);

						TargetThreadResult->bIsDynamic = true;

						return TargetThreadResult;
					}, ETaskPriority::High, EExtendedTaskPriority::Inline);
		}
		else
		{
			TArray<bool> MaterialLumenSupportList;
			{
				MaterialLumenSupportList.Init(true, GetNumMaterials());

				for (int32 Index = 0; Index < MaterialLumenSupportList.Num(); Index++)
				{
					if (IsValid(GetMaterial(Index))) MaterialLumenSupportList[Index] = GetMaterial(Index)->GetMaterial()->BlendMode != EBlendMode::BLEND_Translucent && GetMaterial(Index)->GetMaterial()->BlendMode != EBlendMode::BLEND_TranslucentColoredTransmittance;
				}
			}

			ThreadOutput =
				Launch(UE_SOURCE_LOCATION, [&, CurrentContainer = VoxelContainer, CurrentSetting = GenerationSetting, MaterialLumenSupportList, CurrentThreadResult = ThreadResult]
					{
						TSharedPtr<FLFPVoxelRendererThreadResult> TargetThreadResult = CurrentThreadResult;

						if (IsValid(this) == false) return TargetThreadResult;

						FReadScopeLock Lock(CurrentContainer->ContainerThreadLock);

						if (CurrentSetting.bGenerateLumenData) GenerateLumenData(CurrentContainer, TargetThreadResult, CurrentSetting, MaterialLumenSupportList);

						TargetThreadResult->bIsDynamic = false;

						return TargetThreadResult;
					}, ETaskPriority::High, EExtendedTaskPriority::Inline);
		}

		Status.UpdateRenderMode(ELFPVoxelRendererMode::LFP_Render);
	}
	break;
	case ELFPVoxelRendererMode::LFP_Render:
	{
		ThreadResult = ThreadOutput.GetResult();

		check(ThreadResult.IsValid());

		UpdateBounds();

		MarkRenderStateDirty();

		if (GenerationSetting.HasCollision()) RebuildPhysicsData();

		Status.UpdateNextRenderMode();
	}
	break;
	case ELFPVoxelRendererMode::LFP_None:
	{
		Status.UpdateNextRenderMode();

		OnVoxelRendererUpdate.Broadcast();

		SetComponentTickEnabled(Status.HasRenderDirty());
	}
	break;
	}
}

bool ULFPVoxelRendererComponent::InitializeRenderer(const int32 NewRegionIndex, const int32 NewChuckIndex, ULFPGridContainerComponent* NewVoxelContainer, TArray<UMaterialInstanceDynamic*>& OutDynamicMaterial)
{
	if (IsValid(NewVoxelContainer) == false) return false;

	ReleaseRenderer();

	VoxelContainer = NewVoxelContainer;

	{
		FLFPGridChuckDelegate& Delegate = VoxelContainer->AddRenderChuck(NewRegionIndex, NewChuckIndex);

		Delegate.AddUObject(this, &ULFPVoxelRendererComponent::OnChuckUpdate);

		RegionIndex = NewRegionIndex;

		ChuckIndex = NewChuckIndex;

		VoxelContainer->InitializeGridChuck(NewRegionIndex, NewChuckIndex);
	}

	{
		const FIntPoint VoxelTextureSize(VoxelContainer->GetSetting().GetPaletteGrid().X, VoxelContainer->GetSetting().GetPaletteGrid().Y * VoxelContainer->GetSetting().GetPaletteGrid().Z);

		AttributesTexture = ULFPRenderLibrary::CreateTexture2D(VoxelTextureSize, TF_Nearest, false);

		OutDynamicMaterial = UpdateMaterialTexture();

		const int32 RegionAmount = VoxelContainer->GetSetting().GetPaletteGrid().Z;

		TSet<int32> UpdateRegionList;

		UpdateRegionList.Reserve(RegionAmount);

		for (int32 Index = 0; Index < RegionAmount; Index++)
		{
			UpdateRegionList.Add(Index);
		}

		Status.MarkAttributeDirty(UpdateRegionList);
	}

	return true;
}

bool ULFPVoxelRendererComponent::ReleaseRenderer()
{
	if (IsValid(VoxelContainer) == false) return false;

	ThreadOutput.Wait();

	ThreadOutput = {};

	AttributeOutput.Wait();

	AttributeOutput = {};

	VoxelContainer->RemoveRenderChuck(RegionIndex, ChuckIndex, this);

	VoxelContainer = nullptr;

	RegionIndex = INDEX_NONE;
	ChuckIndex = INDEX_NONE;

	if (IsValid(AttributesTexture))
	{
		AttributesTexture->ReleaseResource();
		AttributesTexture->MarkAsGarbage();
		AttributesTexture = nullptr;
	}

	return true;
}

void ULFPVoxelRendererComponent::UpdateMesh()
{
	if (IsValid(VoxelContainer) == false)
	{
		UE_LOG(LFPVoxelRendererComponent, Warning, TEXT("Voxel Mesh Can't Be Update Because Voxel Container Is Not Valid"));

		return;
	}

	if (VoxelContainer->IsChuckInitialized(RegionIndex, ChuckIndex))
	{
		Status.MarkRendererModeDirty();

		SetComponentTickEnabled(true);

		OnVoxelMeshUpdate.Broadcast();
	}
}

void ULFPVoxelRendererComponent::UpdateAttribute(const TArray<int32>& DirtyIndexList)
{
	if (IsValid(VoxelContainer) == false)
	{
		UE_LOG(LFPVoxelRendererComponent, Warning, TEXT("Voxel Color Can't Be Update Because Voxel Container Is Not Valid"));

		return;
	}

	if (VoxelContainer->IsChuckInitialized(RegionIndex, ChuckIndex))
	{
		TSet<int32> HeightList;

		for (const int32 DirtyIndex : DirtyIndexList)
		{
			HeightList.Add(ULFPGridLibrary::ToGridLocation(DirtyIndex, VoxelContainer->GetSetting().GetPaletteGrid()).Z);
		}

		Status.MarkAttributeDirty(HeightList);

		SetComponentTickEnabled(true);

		OnVoxelAttributesUpdate.Broadcast();
	}
}

void ULFPVoxelRendererComponent::SetDisableFaceCulling(const bool bChuck, const bool bRegion)
{
	GenerationSetting.bDisableChuckFaceCulling = bChuck;
	GenerationSetting.bDisableRegionFaceCulling = bRegion;

	UpdateMesh();
}

int32 ULFPVoxelRendererComponent::ToGridIndex(const FVector Location) const
{
	if (IsValid(VoxelContainer) == false)
	{
		return INDEX_NONE;
	}

	const FVector MaxLocation = (GenerationSetting.VoxelHalfSize * 2.0f);
	const FVector CorrectlLocation = ((Location - GetComponentLocation()) + (FVector(VoxelContainer->GetSetting().GetPaletteGrid()) * GenerationSetting.VoxelHalfSize)) / (GenerationSetting.VoxelHalfSize * 2.0f);

	if (CorrectlLocation.GetMin() < 0.0f || CorrectlLocation.X > MaxLocation.X || CorrectlLocation.Y > MaxLocation.Y || CorrectlLocation.Z > MaxLocation.Z)
	{
		return INDEX_NONE;
	}

	return ULFPGridLibrary::ToGridIndex(FIntVector(FMath::FloorToInt(CorrectlLocation.X), FMath::FloorToInt(CorrectlLocation.Y), FMath::FloorToInt(CorrectlLocation.Z)), VoxelContainer->GetSetting().GetPaletteGrid());
}

FVector ULFPVoxelRendererComponent::ToWorldLocation(const int32 GridIndex) const
{
	if (IsValid(VoxelContainer) == false || GridIndex < 0 || GridIndex >= VoxelContainer->GetSetting().GetGridLength())
	{
		return FVector(-1.0f);
	}

	const FIntVector GridLocation = ULFPGridLibrary::ToGridLocation(GridIndex, VoxelContainer->GetSetting().GetPaletteGrid());

	return (GetComponentLocation() - (FVector(VoxelContainer->GetSetting().GetPaletteGrid()) * GenerationSetting.VoxelHalfSize)) + (FVector(GridLocation) * GenerationSetting.VoxelHalfSize * 2.0f) + GenerationSetting.VoxelHalfSize;
}

void ULFPVoxelRendererComponent::OnChuckUpdate(const FLFPChuckUpdateAction& Data)
{
	if (CanUpdateMesh(Data)) UpdateMesh();

	if (CanUpdateAttribute(Data)) UpdateAttribute(Data.GridDirtyIndexList.Array());
}

bool ULFPVoxelRendererComponent::CanUpdateMesh(const FLFPChuckUpdateAction& Data) const
{
	return Data.GridChangeNameList.IsEmpty() == false;
}

bool ULFPVoxelRendererComponent::CanUpdateAttribute(const FLFPChuckUpdateAction& Data) const
{
	return Data.GridDirtyIndexList.IsEmpty() == false;
}

/**********************/
/** Material Handling */

void ULFPVoxelRendererComponent::SetMaterialList(const TArray<UMaterialInterface*>& Material)
{
	if (Material.IsEmpty() == false)
	{
		for (int32 Index = 0; Index < Material.Num(); Index++)
		{
			CreateDynamicMaterialInstance(Index, Material[Index]);
		}
	}
	else
	{
		UE_LOG(LFPVoxelRendererComponent, Warning, TEXT("Can't Set Material Because Array Is Empty"));
	}
}

UMaterialInterface* ULFPVoxelRendererComponent::GetMaterialFromCollisionFaceIndex(int32 FaceIndex, int32& SectionIndex) const
{
	UMaterialInterface* Result = nullptr;
	SectionIndex = 0;

	if (ThreadResult.IsValid() && FaceIndex >= 0)
	{
		// Look for section that corresponds to the supplied face
		int32 TotalFaceCount = 0;

		for (int32 SectionIdx = 0; SectionIdx < ThreadResult->SectionData.Num(); SectionIdx++)
		{
			const auto& Section = ThreadResult->SectionData[SectionIdx];

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

int32 ULFPVoxelRendererComponent::GetNumMaterials() const
{
	return Super::GetNumOverrideMaterials();
}

void ULFPVoxelRendererComponent::SetMaterial(int32 ElementIndex, UMaterialInterface* Material)
{
	Super::SetMaterial(ElementIndex, IsValid(Material) ? Material : UMaterial::GetDefaultMaterial(MD_Surface));

	if (IsValid(VoxelContainer))
	{
		UpdateMesh();
	}
}

UMaterialInstanceDynamic* ULFPVoxelRendererComponent::CreateDynamicMaterialInstance(int32 ElementIndex, UMaterialInterface* SourceMaterial, FName OptionalName)
{
	UMaterialInstanceDynamic* MID = Super::CreateDynamicMaterialInstance(ElementIndex, SourceMaterial, OptionalName);

	if (IsValid(MID))
	{
		MID->SetTextureParameterValue("VoxelAttributesTexture", AttributesTexture);

		if (IsValid(VoxelContainer)) 
		{
			MID->SetVectorParameterValue("VoxelChuckSize", FVector(VoxelContainer->GetSetting().GetPaletteGrid()));
			MID->SetVectorParameterValue("VoxelBlockSize", FVector(GetGenerationSetting().VoxelHalfSize * 2));
		}
	}

	return MID;
}

TArray<UMaterialInstanceDynamic*> ULFPVoxelRendererComponent::UpdateMaterialTexture()
{
	TArray<UMaterialInstanceDynamic*> Result;

	Result.Reserve(GetNumMaterials());

	for (int32 MaterialIndex = 0; MaterialIndex < GetNumMaterials(); MaterialIndex++)
	{
		Result.Add(CreateDynamicMaterialInstance(MaterialIndex));
	}

	return Result;
}

/**********************/
/** Share Data Generation Handling */

const FLFPVoxelRendererSetting& ULFPVoxelRendererComponent::GetGenerationSetting() const
{
	return GenerationSetting;
}

const TSharedPtr<FLFPVoxelRendererThreadResult>& ULFPVoxelRendererComponent::GetThreadResult()
{
	return ThreadResult;
}

bool ULFPVoxelRendererComponent::IsFaceVisible(const FLFPGridPaletteData& FromPaletteData, const FLFPGridPaletteData& ToPaletteData) const
{
	const int32 CurrentIndex = GetVoxelMaterialIndex(FromPaletteData);

	return CurrentIndex != INDEX_NONE && CurrentIndex != GetVoxelMaterialIndex(ToPaletteData);
}

void ULFPVoxelRendererComponent::GenerateBatchFaceData(ULFPGridContainerComponent* TargetVoxelContainer, TSharedPtr<FLFPVoxelRendererThreadResult>& TargetThreadResult, const FLFPVoxelRendererSetting& TargetGenerationSetting)
{
	if (IsValid(TargetVoxelContainer) == false || TargetThreadResult.IsValid() == false) return;

	const double StartTime = FPlatformTime::Seconds();

	const FLFPGridPaletteContainerSetting& VoxelSetting = TargetVoxelContainer->GetSetting();

	//TargetThreadResult->SectionData.Init(FLFPVoxelRendererSectionData(VoxelSetting.GetPaletteGrid()), FMath::Max(GetNumMaterials(), 1));

	int32 MaxMaterialIndex = 1;

	const auto& PushFaceData = [&](TMap<FIntVector, FIntPoint>& BatchDataMap, FInt32Rect& CurrentBatchFaceData, int32& CurrentBatchMaterial) {
		const FIntVector TargetMax = FIntVector(CurrentBatchFaceData.Max.X - 1, CurrentBatchFaceData.Max.Y, CurrentBatchMaterial);
		const FIntPoint* TargetMin = BatchDataMap.Find(TargetMax);

		if (TargetMin != nullptr && TargetMin->Y == CurrentBatchFaceData.Min.Y)
		{
			FIntPoint NewMin = BatchDataMap.FindAndRemoveChecked(TargetMax);

			CurrentBatchFaceData.Min.X = NewMin.X;
		}

		BatchDataMap.Add(FIntVector(CurrentBatchFaceData.Max.X, CurrentBatchFaceData.Max.Y, CurrentBatchMaterial), CurrentBatchFaceData.Min);

		if (MaxMaterialIndex < CurrentBatchMaterial) MaxMaterialIndex = CurrentBatchMaterial;

		CurrentBatchMaterial = INDEX_NONE;
	};

	//ParallelFor(6, [&](const int32 DirectionIndex) {
	for (int32 DirectionIndex = 0; DirectionIndex < 6; DirectionIndex++)
	{
		const FIntVector FaceLoopDirection = LFPVoxelRendererConstantData::FaceLoopDirectionList[DirectionIndex];

		const int32 LoopU = VoxelSetting.GetPaletteGrid()[FaceLoopDirection.X];
		const int32 LoopV = VoxelSetting.GetPaletteGrid()[FaceLoopDirection.Y];
		const int32 LoopI = VoxelSetting.GetPaletteGrid()[FaceLoopDirection.Z];

		//ParallelFor(LoopI, [&](const int32 I) {
		for (int32 I = 0; I < LoopI; I++)
		{
			TMap<FIntVector, FIntPoint> BatchDataMap;
			TMap<FIntVector, FIntPoint> HiddenBatchDataMap;

			FInt32Rect CurrentBatchFaceData(INDEX_NONE, INDEX_NONE);

			int32 CurrentBatchMaterial = INDEX_NONE;

			bool bPreHiddenFace = false;

			for (int32 U = 0; U < LoopU; U++)
			{
				for (int32 V = 0; V < LoopV; V++)
				{
					/***************** Identify Data *****************/
					const FIntPoint CurrentFacePos(U, V);

					FIntVector CurrentPos;

					CurrentPos[FaceLoopDirection.X] = U;
					CurrentPos[FaceLoopDirection.Y] = V;
					CurrentPos[FaceLoopDirection.Z] = I;

					const int32 CurrentIndex = ULFPGridLibrary::ToGridIndex(CurrentPos, VoxelSetting.GetPaletteGrid());

					const FIntVector CurrentGlobalPos = TargetVoxelContainer->ToGridGlobalPosition(FIntVector(RegionIndex, ChuckIndex, CurrentIndex));

					const FIntVector TargetGlobalPos = CurrentGlobalPos + LFPVoxelRendererConstantData::FaceDirection[DirectionIndex].Up;

					const FIntVector TargetGlobalIndex = TargetVoxelContainer->ToGridGlobalIndex(TargetGlobalPos);

					const FLFPGridPaletteData& SelfVoxelPalette = TargetVoxelContainer->GetGridPaletteRef(RegionIndex, ChuckIndex, CurrentIndex);

					/** Check Do We Ignore Border Data And Always Fill The Face */
					const bool bForceRender = (TargetGenerationSetting.bDisableChuckFaceCulling && ChuckIndex != TargetGlobalIndex.Y) || (TargetGenerationSetting.bDisableRegionFaceCulling && RegionIndex != TargetGlobalIndex.X);

					const FLFPGridPaletteData& TargetVoxelPalette = bForceRender ? FLFPGridPaletteData::EmptyData : TargetVoxelContainer->GetGridPaletteRef(TargetGlobalIndex.X, TargetGlobalIndex.Y, TargetGlobalIndex.Z);

					const bool bCurrentVisible = IsFaceVisible(SelfVoxelPalette, TargetVoxelPalette);
					const bool bCurrentHiddenFace = bCurrentVisible == false && (ChuckIndex != TargetGlobalIndex.Y || RegionIndex != TargetGlobalIndex.X);

					/*************************************************/

					if (bCurrentVisible || bCurrentHiddenFace)
					{
						const int32 CurrentMaterialIndex = GetVoxelMaterialIndex(SelfVoxelPalette);

						if ((CurrentBatchFaceData.Max.X != U || bPreHiddenFace != bCurrentHiddenFace) && CurrentBatchMaterial != INDEX_NONE)
						{
							PushFaceData(bPreHiddenFace ? HiddenBatchDataMap : BatchDataMap, CurrentBatchFaceData, CurrentBatchMaterial);
						}

						if (CurrentBatchMaterial == CurrentMaterialIndex)
						{
							CurrentBatchFaceData.Max.Y += 1;
						}
						else if (CurrentBatchMaterial != INDEX_NONE)
						{
							PushFaceData(bPreHiddenFace ? HiddenBatchDataMap : BatchDataMap, CurrentBatchFaceData, CurrentBatchMaterial);
						}

						if (CurrentBatchMaterial == INDEX_NONE)
						{
							CurrentBatchFaceData = FInt32Rect(U, V, U, V);
							CurrentBatchMaterial = CurrentMaterialIndex;
							bPreHiddenFace = bCurrentHiddenFace;
						}
					}
					else if (CurrentBatchMaterial != INDEX_NONE)
					{
						PushFaceData(bPreHiddenFace ? HiddenBatchDataMap : BatchDataMap, CurrentBatchFaceData, CurrentBatchMaterial);
					}
				}
			}

			if (CurrentBatchMaterial != INDEX_NONE)
			{
				PushFaceData(bPreHiddenFace ? HiddenBatchDataMap : BatchDataMap, CurrentBatchFaceData, CurrentBatchMaterial);
			}

			TargetThreadResult->SectionData.Reserve(MaxMaterialIndex + 1);

			/** Fill Up Section If Not Enought */
			while (TargetThreadResult->SectionData.IsValidIndex(MaxMaterialIndex) == false)
			{
				TargetThreadResult->SectionData.Add(FLFPVoxelRendererSectionData(VoxelSetting.GetPaletteGrid()));
			}

			for (const auto& BatchData : BatchDataMap)
			{
				TargetThreadResult->SectionData[BatchData.Key.Z].GetVoxelFaceData(DirectionIndex, I).FaceDataList.Add(FInt32Rect(BatchData.Value, FIntPoint(BatchData.Key.X, BatchData.Key.Y)));
				TargetThreadResult->SectionData[BatchData.Key.Z].TriangleCount += 2;
			}

			for (const auto& BatchData : HiddenBatchDataMap)
			{
				TargetThreadResult->SectionData[BatchData.Key.Z].GetVoxelFaceData(DirectionIndex, I).HiddenFaceDataList.Add(FInt32Rect(BatchData.Value, FIntPoint(BatchData.Key.X, BatchData.Key.Y)));
			}
		}
	}

	for (auto& Section : TargetThreadResult->SectionData)
	{
		for (auto& Data : Section.DataList)
		{
			//Section.TriangleCount += Data.FaceDataList.Num() * 2;
			Data.FaceDataList.Shrink();
		}
	}

	if (TargetGenerationSetting.bPrintGenerateTime) UE_LOG(LogTemp, Warning, TEXT("BatchFace Generate Time Use : %f"), (float)(FPlatformTime::Seconds() - StartTime));
}

void ULFPVoxelRendererComponent::GenerateSimpleCollisionData(ULFPGridContainerComponent* TargetVoxelContainer, TSharedPtr<FLFPVoxelRendererThreadResult>& TargetThreadResult, const FLFPVoxelRendererSetting& TargetGenerationSetting)
{
	if (IsValid(TargetVoxelContainer) == false || TargetThreadResult.IsValid() == false) return;

	const double StartTime = FPlatformTime::Seconds();

	const FLFPGridPaletteContainerSetting& VoxelSetting = TargetVoxelContainer->GetSetting();

	TMap<FIntVector, FIntVector> BatchDataMap;

	TPair<FIntVector, FIntVector> CurrentBatchData(INDEX_NONE, INDEX_NONE);

	bool IsBatchValid = false;

	const auto& PushData = [&]() {
		{
			const FIntVector TargetMax = CurrentBatchData.Key - FIntVector(0, 1, 0);
			const FIntVector* TargetMinPtr = BatchDataMap.Find(TargetMax);

			if (TargetMinPtr != nullptr && TargetMinPtr->X == CurrentBatchData.Value.X && TargetMinPtr->Z == CurrentBatchData.Value.Z)
			{
				const FIntVector TargetMin = BatchDataMap.FindAndRemoveChecked(TargetMax);

				CurrentBatchData.Value.Y = TargetMin.Y;
			}
		}

		{
			const FIntVector TargetMax = CurrentBatchData.Key - FIntVector(0, 0, 1);
			const FIntVector* TargetMinPtr = BatchDataMap.Find(TargetMax);

			if (TargetMinPtr != nullptr && TargetMinPtr->X == CurrentBatchData.Value.X && TargetMinPtr->Y == CurrentBatchData.Value.Y)
			{
				const FIntVector TargetMin = BatchDataMap.FindAndRemoveChecked(TargetMax);

				CurrentBatchData.Value.Z = TargetMin.Z;
			}
		}
	
		BatchDataMap.Add(CurrentBatchData.Key, CurrentBatchData.Value);
		IsBatchValid = false;
	};

	/** Generate Batch Data Map */
	for (int32 Z = 0; Z < VoxelSetting.GetPaletteGrid().Z; Z++)
	{
		for (int32 Y = 0; Y < VoxelSetting.GetPaletteGrid().Y; Y++)
		{
			for (int32 X = 0; X < VoxelSetting.GetPaletteGrid().X; X++)
			{
				/***************** Identify Data *****************/
				const FIntVector CurrentPos(X, Y, Z);

				const int32 CurrentIndex = ULFPGridLibrary::ToGridIndex(CurrentPos, VoxelSetting.GetPaletteGrid());

				const bool IsSelfSolid = GetVoxelMaterialIndex(TargetVoxelContainer->GetGridPaletteRef(RegionIndex, ChuckIndex, CurrentIndex)) >= 0;
				/*************************************************/

				if (IsSelfSolid)
				{
					if ((CurrentBatchData.Key.Y != Y || CurrentBatchData.Key.Z != Z) && IsBatchValid)
					{
						PushData();
					}

					if (IsBatchValid)
					{
						CurrentBatchData.Key.X += 1;
					}
					else
					{
						CurrentBatchData.Key = CurrentPos;
						CurrentBatchData.Value = CurrentPos;
						IsBatchValid = true;
					}
				}
				else if (IsBatchValid)
				{
					PushData();
				}
			}
		}
	}

	if (IsBatchValid)
	{
		PushData();
	}

	const FVector BoxHalfSize = GetGenerationSetting().VoxelHalfSize;
	const FVector BoxSize = BoxHalfSize * 2;
	const FVector RenderOffset = -(BoxHalfSize * FVector(TargetVoxelContainer->GetSetting().GetPaletteGrid()));

	/** Add To Result */
	for (const auto& BatchData : BatchDataMap)
	{
		const FVector MinPos = FVector(BatchData.Value) * BoxSize;
		const FVector MaxPos = FVector(BatchData.Key + FIntVector(1)) * BoxSize;
		const FVector Scale = (MaxPos - MinPos);
		const FVector Center = FMath::Lerp(MinPos, MaxPos, 0.5f) + RenderOffset;

		FKBoxElem CurrentBoxElem(Scale.X, Scale.Y, Scale.Z);
		FKConvexElem CurrentConverElem;

		CurrentBoxElem.Center = FMath::Lerp(MinPos, MaxPos, 0.5f) + RenderOffset;

		TargetThreadResult->CollisionData.BoxElems.Add(CurrentBoxElem);
		//TargetThreadResult->CollisionData.ConvexElems.Add(CurrentConverElem);
	}

	if (TargetGenerationSetting.bPrintGenerateTime) UE_LOG(LogTemp, Warning, TEXT("Collision Generate Time Use : %f"), (float)(FPlatformTime::Seconds() - StartTime));
}

void ULFPVoxelRendererComponent::GenerateLumenData(ULFPGridContainerComponent* TargetVoxelContainer, TSharedPtr<FLFPVoxelRendererThreadResult>& TargetThreadResult, const FLFPVoxelRendererSetting& TargetGenerationSetting, const TArray<bool>& MaterialLumenSupportList)
{
	if (IsValid(TargetVoxelContainer) == false || TargetThreadResult.IsValid() == false) return;

	const double StartTime = FPlatformTime::Seconds();

	/** Custom Struct For Lumen And Distance Field */
	struct FLFPDFMipInfo
	{
		FLFPDFMipInfo() {}

		FLFPDFMipInfo(const FIntVector& IndirectionDimensions, const FBox& LocalSpaceMeshBounds, const float LocalToVolumeScale)
		{
			// Expand to guarantee one voxel border for gradient reconstruction using bilinear filtering
			TexelObjectSpaceSize = LocalSpaceMeshBounds.GetSize() / FVector(IndirectionDimensions * DistanceField::UniqueDataBrickSize - FIntVector(2 * DistanceField::MeshDistanceFieldObjectBorder));
			DistanceFieldVolumeBounds = LocalSpaceMeshBounds.ExpandBy(TexelObjectSpaceSize);

			IndirectionVoxelSize = DistanceFieldVolumeBounds.GetSize() / FVector(IndirectionDimensions);
			VolumeSpaceDistanceFieldVoxelSize = IndirectionVoxelSize * LocalToVolumeScale / FVector(DistanceField::UniqueDataBrickSize);
			MaxDistanceForEncoding = VolumeSpaceDistanceFieldVoxelSize.Size() * DistanceField::BandSizeInVoxels;
			LocalSpaceTraceDistance = MaxDistanceForEncoding / LocalToVolumeScale;
			DistanceFieldToVolumeScaleBias = FVector2D(2.0f * MaxDistanceForEncoding, -MaxDistanceForEncoding);
		}

		FVector TexelObjectSpaceSize;
		FBox DistanceFieldVolumeBounds;

		FVector IndirectionVoxelSize;
		FVector VolumeSpaceDistanceFieldVoxelSize;
		float MaxDistanceForEncoding;
		float LocalSpaceTraceDistance;
		FVector2D DistanceFieldToVolumeScaleBias;

		FORCEINLINE void SetSparseDistanceFieldMip(FSparseDistanceFieldMip& DistanceMip, const FIntVector& IndirectionDimensions, const FBox& LocalSpaceMeshBounds, const float LocalToVolumeScale)
		{
			DistanceMip.DistanceFieldToVolumeScaleBias = DistanceFieldToVolumeScaleBias;
			DistanceMip.IndirectionDimensions = IndirectionDimensions;

			// Account for the border voxels we added
			const FVector VirtualUVMin = FVector(DistanceField::MeshDistanceFieldObjectBorder) / FVector(IndirectionDimensions * DistanceField::UniqueDataBrickSize);
			const FVector VirtualUVSize = FVector(IndirectionDimensions * DistanceField::UniqueDataBrickSize - FIntVector(2 * DistanceField::MeshDistanceFieldObjectBorder)) / FVector(IndirectionDimensions * DistanceField::UniqueDataBrickSize);

			const FVector VolumePositionExtent = LocalSpaceMeshBounds.GetExtent() * LocalToVolumeScale;

			// [-VolumePositionExtent, VolumePositionExtent] -> [VirtualUVMin, VirtualUVMin + VirtualUVSize]
			DistanceMip.VolumeToVirtualUVScale = VirtualUVSize / (2 * VolumePositionExtent);
			DistanceMip.VolumeToVirtualUVAdd = VolumePositionExtent * DistanceMip.VolumeToVirtualUVScale + VirtualUVMin;
		}
	};

	struct FLFPCacheAccelerationInfo
	{
		TArray<FBox> TraceBoxList = TArray<FBox>();
		int32 TraceDistance = INDEX_NONE;
		int32 MaterialIndex = INDEX_NONE;
	};

	struct FLFPDFBrickTask
	{
		FLFPDFBrickTask(const int32 InBrickLength, const FVector& InBrickVoxelSize, const int32 InBrickIndex, const FVector& InBrickSpaceLocation, const FVector& InVoxelSize, const FLFPDFMipInfo& InMipInfo, const TArray<FLFPCacheAccelerationInfo>& InAccelerationInfoList, const float InLocalToVolumeScale, const FIntVector InCheckSize, const int32 InSizeHalfOffset)
			: BrickLength(InBrickLength), BrickIndex(InBrickIndex), BrickSpaceLocation(InBrickSpaceLocation), BrickVoxelSize(InBrickVoxelSize), VoxelSize(InVoxelSize), MipInfo(InMipInfo), AccelerationInfoList(InAccelerationInfoList), LocalToVolumeScale(InLocalToVolumeScale), CheckSize(InCheckSize), SizeHalfOffset(InSizeHalfOffset)
		{}

		FORCEINLINE float GetDistanceToClosetSurface(const FVector& LocalLocation) const
		{
			const FVector LocalSpace = LocalLocation / VoxelSize;
			const FIntVector GridLocation = FIntVector(FMath::FloorToInt32(LocalSpace.X), FMath::FloorToInt32(LocalSpace.Y), FMath::FloorToInt32(LocalSpace.Z));
			const int32 FullGridIndex = ULFPGridLibrary::ToGridIndex(GridLocation + FIntVector(SizeHalfOffset), CheckSize);
			//const int32 GridIndex = ULFPGridLibrary::ToGridIndex(GridLocation, ContainerSetting.GetPaletteGrid());

			checkf(FullGridIndex >= 0, TEXT("Error Index : %s : %d : %s : %s : %s"), *GridLocation.ToString(), SizeHalfOffset, *VoxelSize.ToString(), *LocalLocation.ToString(), *BrickSpaceLocation.ToString());

			const FLFPCacheAccelerationInfo& CurrentInfo = AccelerationInfoList[FullGridIndex];

			double ClosetDistance = FMath::Square(MipInfo.LocalSpaceTraceDistance);
			
			//const FBox TestBox(FVector(0), ContainerSetting.GetVoxelHalfBounds() * 2);

			//ClosetDistance = FMath::Min(TestBox.ComputeSquaredDistanceToPoint(LocalLocation), ClosetDistance);

			for (const FBox& TraceBox : CurrentInfo.TraceBoxList)
			{
				ClosetDistance = FMath::Min(TraceBox.ComputeSquaredDistanceToPoint(LocalLocation), ClosetDistance);
			}

			ClosetDistance = FMath::Sqrt(ClosetDistance);

			return CurrentInfo.MaterialIndex != INDEX_NONE ? ClosetDistance * -1 : ClosetDistance;
			//return TestBox.IsInsideOrOn(LocalLocation) ? ClosetDistance * -1 : ClosetDistance;
		};

		FORCEINLINE void DoTask()
		{
			BrickDataList.Init(0, BrickLength);

			for (int32 DataIndex = 0; DataIndex < 512 /* Brick Length */; DataIndex++)
			{
				const FIntVector DataLocation(ULFPGridLibrary::ToGridLocation(DataIndex, FIntVector(DistanceField::BrickSize)));

				const FVector BrickVoxelLocation = (FVector(DataLocation) * BrickVoxelSize) + BrickSpaceLocation;

				const float ClosetPoint = GetDistanceToClosetSurface(BrickVoxelLocation);

				// Transform to the tracing shader's Volume space
				const float VolumeSpaceDistance = ClosetPoint * LocalToVolumeScale;
				// Transform to the Distance Field texture's space
				const float RescaledDistance = (VolumeSpaceDistance - MipInfo.DistanceFieldToVolumeScaleBias.Y) / MipInfo.DistanceFieldToVolumeScaleBias.X;

				BrickDataList[DataIndex] = FMath::Clamp<int32>(FMath::FloorToInt(RescaledDistance * 255.0f + .5f), 0, 255);

				BrickMaxDistance = FMath::Max(BrickMaxDistance, BrickDataList[DataIndex]);
				BrickMinDistance = FMath::Min(BrickMinDistance, BrickDataList[DataIndex]);
			}

			if (BrickMinDistance == MAX_uint8 || BrickMaxDistance == MIN_uint8)
			{
				BrickDataList.Empty();
			}
		}

		const int32 BrickLength;
		const int32 BrickIndex;
		const FVector BrickSpaceLocation;
		const FVector BrickVoxelSize;
		const FVector VoxelSize;
		const FLFPDFMipInfo& MipInfo;
		const TArray<FLFPCacheAccelerationInfo>& AccelerationInfoList;
		const float LocalToVolumeScale;
		const FIntVector CheckSize;
		const int32 SizeHalfOffset;

		TArray<uint8> BrickDataList;
		uint8 BrickMaxDistance = (MIN_uint8);
		uint8 BrickMinDistance = (MAX_uint8);
	};
	/////////////////////////////////////////////////

	/** Begin Data */
	const FLFPGridPaletteContainerSetting ContainerSetting = TargetVoxelContainer->GetSetting();

	const FVector VoxelSize = TargetGenerationSetting.VoxelHalfSize * 2;
	const FVector VoxelHalfBounds = TargetGenerationSetting.VoxelHalfSize * FVector(TargetVoxelContainer->GetSetting().GetPaletteGrid());

	const FVector TargetDimensions = FVector(ContainerSetting.GetPaletteGrid()) * (double(TargetGenerationSetting.LumenQuality) / 8.0);

	const FIntVector MaxIndirectionDimensions(
		FMath::Clamp(FMath::RoundToInt32(TargetDimensions.X), 1, int32(DistanceField::MaxIndirectionDimension)),
		FMath::Clamp(FMath::RoundToInt32(TargetDimensions.Y), 1, int32(DistanceField::MaxIndirectionDimension)),
		FMath::Clamp(FMath::RoundToInt32(TargetDimensions.Z), 1, int32(DistanceField::MaxIndirectionDimension))
	);

	const FIntVector MinIndirectionDimensions = FIntVector(
		FMath::DivideAndRoundUp(MaxIndirectionDimensions.X, 1 << (DistanceField::NumMips - 1)),
		FMath::DivideAndRoundUp(MaxIndirectionDimensions.Y, 1 << (DistanceField::NumMips - 1)),
		FMath::DivideAndRoundUp(MaxIndirectionDimensions.Z, 1 << (DistanceField::NumMips - 1))
	);

	const float BoundExpand = TargetGenerationSetting.VoxelHalfSize.GetMax() * TargetGenerationSetting.LumenBoundMultipy;

	const FBox LocalBounds = FBox(-VoxelHalfBounds, VoxelHalfBounds);

	const FBox LocalSpaceMeshBounds(LocalBounds.ExpandBy(
		LocalBounds.GetSize() / FVector(MinIndirectionDimensions * DistanceField::UniqueDataBrickSize - FIntVector(2 * 0.25f))
	));

	const int32 BrickLength = DistanceField::BrickSize * DistanceField::BrickSize * DistanceField::BrickSize;

	const float LocalToVolumeScale = 1.0f / LocalSpaceMeshBounds.GetExtent().GetMax();
	const float LocalToVoxelScale = 1.0f / TargetGenerationSetting.VoxelHalfSize.GetMax();
	/////////////////

	/* Calculate MaxCheckDistance */
	FLFPDFMipInfo MinMipInfo(MinIndirectionDimensions, LocalSpaceMeshBounds, LocalToVolumeScale);

	const FVector MinBrickOffset = MinMipInfo.DistanceFieldVolumeBounds.Min + VoxelHalfBounds;

	const int32 SizeHalfOffset = FMath::DivideAndRoundUp(MinBrickOffset.GetAbs(), TargetGenerationSetting.VoxelHalfSize.GetAbs() * 2).GetMax();
	const int32 SizeOffset = SizeHalfOffset * 2;

	const FIntVector CheckSize(
		ContainerSetting.GetPaletteGrid().X + SizeOffset,
		ContainerSetting.GetPaletteGrid().Y + SizeOffset,
		ContainerSetting.GetPaletteGrid().Z + SizeOffset
	);

	const int32 CheckLength = CheckSize.X * CheckSize.Y * CheckSize.Z;

	/** Acceleration Data To Speed Up Calculation */
	TArray<FLFPCacheAccelerationInfo> AccelerationInfoList;
	{
		const double TaskTime = FPlatformTime::Seconds();

		AccelerationInfoList.Init(FLFPCacheAccelerationInfo(), CheckLength);

		/** Generate Material Index List */
		for (int32 Index = 0; Index < CheckLength; Index++)
		{
			const FIntVector VoxelPosition(ULFPGridLibrary::ToGridLocation(Index, CheckSize) - FIntVector(SizeHalfOffset));

			const int32 MaterialIndex = GetVoxelMaterialIndex(TargetVoxelContainer->GetGridPaletteRef(RegionIndex, ChuckIndex, ULFPGridLibrary::ToGridIndex(VoxelPosition, ContainerSetting.GetPaletteGrid())));

			if (MaterialLumenSupportList.IsValidIndex(MaterialIndex) == false || MaterialLumenSupportList[MaterialIndex])
			{
				AccelerationInfoList[Index].MaterialIndex = MaterialIndex;
			}
		}

		if (TargetGenerationSetting.bPrintGenerateTime) UE_LOG(LogTemp, Warning, TEXT("Lumen AccelerationInfoList Get Data Time Use : %f"), (float)(FPlatformTime::Seconds() - TaskTime));

		const int32 MaxCheckDistance = FMath::CeilToInt(MinMipInfo.LocalSpaceTraceDistance * LocalToVoxelScale);

		/*for (int32 Index = 0; Index  < CheckLength; Index ++)*/
		ParallelFor(TEXT("ParallelFor : Voxel Renderer Distance Field Acceleration Info"), CheckLength, 4, [&](const int32 Index)
		{
			//const double SubTaskTime = FPlatformTime::Seconds();

			FLFPCacheAccelerationInfo& CurrentCacheInfo = AccelerationInfoList[Index];

			const FIntVector CacheLocation = ULFPGridLibrary::ToGridLocation(Index, CheckSize) - FIntVector(SizeHalfOffset);

			const int32 CurrentMaxCheckDistance = FMath::Min(MaxCheckDistance, FMath::Max(CacheLocation.GetMax(), (ContainerSetting.GetPaletteGrid() - CacheLocation).GetMax()));

			/** Generate Trace Distance */
			{
				//for (CurrentCacheInfo.TraceDistance = 1; CurrentCacheInfo.TraceDistance <= CurrentMaxCheckDistance; CurrentCacheInfo.TraceDistance++)
				//{
				//	bool bIsHit = false;
				//
				//	for (int32 Z = CacheLocation.Z - CurrentCacheInfo.TraceDistance; Z <= CacheLocation.Z + CurrentCacheInfo.TraceDistance; Z++)
				//	{
				//		for (int32 Y = CacheLocation.Y - CurrentCacheInfo.TraceDistance; Y <= CacheLocation.Y + CurrentCacheInfo.TraceDistance; Y++)
				//		{
				//			for (int32 X = CacheLocation.X - CurrentCacheInfo.TraceDistance; X <= CacheLocation.X + CurrentCacheInfo.TraceDistance; X++)
				//			{
				//				const int32 CheckGridIndex = ULFPGridLibrary::ToGridIndex(FIntVector(X, Y, Z) + FIntVector(SizeHalfOffset), CheckSize);
				//				const int32 CheckMaterial = CheckGridIndex == INDEX_NONE ? INDEX_NONE : AccelerationInfoList[CheckGridIndex].MaterialIndex;
				//
				//				if (CheckMaterial != CurrentCacheInfo.MaterialIndex)
				//				{
				//					bIsHit = true;
				//
				//					break;
				//				}
				//
				//				if (Z != CacheLocation.Z - CurrentCacheInfo.TraceDistance && Z != CacheLocation.Z + CurrentCacheInfo.TraceDistance && Y != CacheLocation.Y - CurrentCacheInfo.TraceDistance && Y != CacheLocation.Y + CurrentCacheInfo.TraceDistance && X == CacheLocation.X - CurrentCacheInfo.TraceDistance)
				//				{
				//					X = CacheLocation.X + CurrentCacheInfo.TraceDistance - 1;
				//				}
				//			}
				//
				//			if (bIsHit) break;
				//		}
				//
				//		if (bIsHit) break;
				//	}
				//
				//	if (bIsHit) break;
				//}

				for (CurrentCacheInfo.TraceDistance = 1; CurrentCacheInfo.TraceDistance <= CurrentMaxCheckDistance; CurrentCacheInfo.TraceDistance++)
				{
					for (int32 SectionIndex = 0; SectionIndex < TargetThreadResult->SectionData.Num(); SectionIndex++)
					{
						TargetThreadResult->SectionData[SectionIndex].GenerateDistanceBoxData(CacheLocation, SectionIndex == CurrentCacheInfo.MaterialIndex, CurrentCacheInfo.TraceDistance, CurrentCacheInfo.TraceBoxList);
					}

					if (CurrentCacheInfo.TraceBoxList.IsValidIndex(0))
					{
						break;
					}
				}
			}

			//const double SubTaskTimeTwo = FPlatformTime::Seconds();

			/** Generate Trace Box */
			if (CurrentCacheInfo.TraceDistance <= CurrentMaxCheckDistance)
			{
				//for (int32 SectionIndex = 0; SectionIndex < TargetThreadResult->SectionData.Num(); SectionIndex++)
				//{
				//	TargetThreadResult->SectionData[SectionIndex].GenerateDistanceBoxData(CacheLocation, SectionIndex == CurrentCacheInfo.MaterialIndex, CurrentCacheInfo.TraceDistance, CurrentCacheInfo.TraceBoxList);
				//}

				for (FBox& TraceBox : CurrentCacheInfo.TraceBoxList)
				{
					TraceBox.Min *= TargetGenerationSetting.VoxelHalfSize * 2;
					TraceBox.Max *= TargetGenerationSetting.VoxelHalfSize * 2;

					TraceBox.Min += TargetGenerationSetting.VoxelHalfSize;
					TraceBox.Max += TargetGenerationSetting.VoxelHalfSize;
				}
			}

			//if (TargetGenerationSetting.bPrintGenerateTime && (float)(FPlatformTime::Seconds() - SubTaskTime) > 0.001f) UE_LOG(LogTemp, Warning, TEXT("Lumen AccelerationInfoList Error : %f : %f : Index = %d : TraceDistance = %d : %d"), (float)(FPlatformTime::Seconds() - SubTaskTime), (float)(FPlatformTime::Seconds() - SubTaskTimeTwo), Index, CurrentCacheInfo.TraceDistance, CurrentMaxCheckDistance);
		}, EParallelForFlags::Unbalanced | EParallelForFlags::BackgroundPriority);

		if (TargetGenerationSetting.bPrintGenerateTime) UE_LOG(LogTemp, Warning, TEXT("Lumen AccelerationInfoList Use Time : %f"), (float)(FPlatformTime::Seconds() - TaskTime));
	}

	{
		const double TaskTime = FPlatformTime::Seconds();

		TargetThreadResult->DistanceFieldMeshData = MakeShared<FDistanceFieldVolumeData>();

		TargetThreadResult->DistanceFieldMeshData->AssetName = "Voxel Mesh";
		TargetThreadResult->DistanceFieldMeshData->LocalSpaceMeshBounds = LocalSpaceMeshBounds;
		TargetThreadResult->DistanceFieldMeshData->bMostlyTwoSided = true;

		TArray<uint8> StreamableMipData;

		/** Generate Mip */
		for (int32 MipIndex = 0; MipIndex < DistanceField::NumMips; MipIndex++)
		{
			//const double MipStartTime = FPlatformTime::Seconds();

			FSparseDistanceFieldMip& OutMip = TargetThreadResult->DistanceFieldMeshData->Mips[MipIndex];

			const FIntVector IndirectionDimensions = FIntVector(
				FMath::DivideAndRoundUp(MaxIndirectionDimensions.X, 1 << MipIndex),
				FMath::DivideAndRoundUp(MaxIndirectionDimensions.Y, 1 << MipIndex),
				FMath::DivideAndRoundUp(MaxIndirectionDimensions.Z, 1 << MipIndex)
			);

			const int32 IndirectionDimensionsLength = IndirectionDimensions.X * IndirectionDimensions.Y * IndirectionDimensions.Z;

			TArray<uint8> DistanceFieldBrickData;
			TArray<uint32> IndirectionTable;

			IndirectionTable.Init(DistanceField::InvalidBrickIndex, IndirectionDimensionsLength);

			FLFPDFMipInfo MipInfo(IndirectionDimensions, LocalSpaceMeshBounds, LocalToVolumeScale);

			MipInfo.SetSparseDistanceFieldMip(OutMip, IndirectionDimensions, LocalSpaceMeshBounds, LocalToVolumeScale);

			const FVector BrickSpaceSize = MipInfo.DistanceFieldVolumeBounds.GetSize() / FVector(IndirectionDimensions);
			const FVector BrickVoxelSize = BrickSpaceSize / DistanceField::UniqueDataBrickSize;
			const FVector BrickOffset = MipInfo.DistanceFieldVolumeBounds.Min + VoxelHalfBounds;
			//const FVector BrickOffset = FVector(0.0f);

			//checkf(false, TEXT("%s"), *(MipInfo.DistanceFieldVolumeBounds.Min + ContainerSetting.GetVoxelHalfBounds()).ToString());

			//UE_LOG(LogTemp, Warning, TEXT("The integer value is: %d"), CheckRange);

			TArray<FLFPDFBrickTask> BrickTaskList;
			BrickTaskList.Reserve(IndirectionDimensionsLength);

			for (int32 BrickIndex = 0; BrickIndex < IndirectionDimensionsLength; BrickIndex++)
			{
				const FIntVector BrickLocation = (ULFPGridLibrary::ToGridLocation(BrickIndex, IndirectionDimensions));
				const FVector BrickSpaceLocation = (FVector(BrickLocation) * BrickSpaceSize) + BrickOffset;

				//checkf((BrickSpaceLocation / (ContainerSetting.GetVoxelHalfSize() * 2)).GetMin() + SizeHalfOffset >= 0.0f, TEXT("Error Size : %s : %s : %lg : %lg"), *BrickOffset.ToString(), *MinBrickOffset.ToString(), MinBrickOffset.GetAbsMax(), ContainerSetting.GetVoxelHalfSize().GetAbsMax() * 2);

				BrickTaskList.Add(FLFPDFBrickTask(
					BrickLength,
					BrickVoxelSize,
					BrickIndex,
					BrickSpaceLocation,
					VoxelSize,
					MipInfo,
					AccelerationInfoList,
					LocalToVolumeScale,
					CheckSize,
					SizeHalfOffset
				));
			}

			ParallelFor(TEXT("ParallelFor : Voxel Renderer Distance Field Brick"), BrickTaskList.Num(), IndirectionDimensions.GetMax(), [&BrickTaskList](int32 TaskIndex)
				{
					BrickTaskList[TaskIndex].DoTask();
				}, EParallelForFlags::Unbalanced | EParallelForFlags::BackgroundPriority);

			TArray<FLFPDFBrickTask*> ValidBricks;
			ValidBricks.Empty(BrickTaskList.Num());

			for (int32 TaskIndex = 0; TaskIndex < BrickTaskList.Num(); TaskIndex++)
			{
				if (BrickTaskList[TaskIndex].BrickDataList.IsEmpty() == false) ValidBricks.Add(&BrickTaskList[TaskIndex]);
			}

			const uint32 BrickSizeBytes = BrickLength * GPixelFormats[DistanceField::DistanceFieldFormat].BlockBytes;
			DistanceFieldBrickData.Empty(BrickSizeBytes * ValidBricks.Num());
			DistanceFieldBrickData.AddUninitialized(BrickSizeBytes * ValidBricks.Num());

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
				TargetThreadResult->DistanceFieldMeshData->AlwaysLoadedMip.Empty(MipDataBytes);
				TargetThreadResult->DistanceFieldMeshData->AlwaysLoadedMip.AddUninitialized(MipDataBytes);

				FPlatformMemory::Memcpy(&TargetThreadResult->DistanceFieldMeshData->AlwaysLoadedMip[0], IndirectionTable.GetData(), IndirectionTableBytes);

				if (DistanceFieldBrickData.Num() > 0)
				{
					FPlatformMemory::Memcpy(&TargetThreadResult->DistanceFieldMeshData->AlwaysLoadedMip[IndirectionTableBytes], DistanceFieldBrickData.GetData(), DistanceFieldBrickData.Num());
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

			//UE_LOG(LogTemp, Warning, TEXT("Voxel Mesh Distance Field Mip %d Generate Time Use : %f with Range Of %d and %d Brick"), MipIndex, (float)(FPlatformTime::Seconds() - MipStartTime), CheckRange, BrickTaskList.Num());
		}

		TargetThreadResult->DistanceFieldMeshData->StreamableMips.Lock(LOCK_READ_WRITE);
		uint8* Ptr = (uint8*)TargetThreadResult->DistanceFieldMeshData->StreamableMips.Realloc(StreamableMipData.Num());
		FMemory::Memcpy(Ptr, StreamableMipData.GetData(), StreamableMipData.Num());
		TargetThreadResult->DistanceFieldMeshData->StreamableMips.Unlock();
		TargetThreadResult->DistanceFieldMeshData->StreamableMips.SetBulkDataFlags(BULKDATA_Force_NOT_InlinePayload);

		if (TargetGenerationSetting.bPrintGenerateTime) UE_LOG(LogTemp, Warning, TEXT("Lumen Bulk Data Time Use : %f"), (float)(FPlatformTime::Seconds() - TaskTime));
	}

	{
		const double TaskTime = FPlatformTime::Seconds();

		TargetThreadResult->LumenCardData = MakeShared<FCardRepresentationData>();

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
			const FLFPCacheAccelerationInfo& CurrentInfo = AccelerationInfoList[ULFPGridLibrary::ToGridIndex(From + FIntVector(SizeHalfOffset), CheckSize)];

			if (ULFPGridLibrary::IsGridLocationValid(From + Direction + FIntVector(SizeHalfOffset), CheckSize))
			{
				const FLFPCacheAccelerationInfo& CheckInfo = AccelerationInfoList[ULFPGridLibrary::ToGridIndex(From + Direction + FIntVector(SizeHalfOffset), CheckSize)];

				return CurrentInfo.MaterialIndex != INDEX_NONE && CurrentInfo.MaterialIndex != CheckInfo.MaterialIndex;
			}

			return CurrentInfo.MaterialIndex != INDEX_NONE;
		};

		auto AddCardBuild = [&](TArray<FLumenCardBuildData>& CardBuildList, const FIntPoint& CoverIndex, const int32 DirectionIndex)
		{
			FBox LumenBox;

			switch (DirectionIndex)
			{
			case 0: case 5:
				LumenBox = FBox(
					FVector(LocalBounds.Min.X, LocalBounds.Min.Y, (CoverIndex.X * TargetGenerationSetting.VoxelHalfSize.Z * 2) - VoxelHalfBounds.Z - BoundExpand),
					FVector(LocalBounds.Max.X, LocalBounds.Max.Y, (CoverIndex.Y * TargetGenerationSetting.VoxelHalfSize.Z * 2) - VoxelHalfBounds.Z + BoundExpand)
				);

				if (DirectionIndex == 0) LumenBox = LumenBox.ShiftBy(FVector(0.0f, 0.0f, TargetGenerationSetting.VoxelHalfSize.Z) * 2.0f);
				break;

			case 1: case 3:
				LumenBox = FBox(
					FVector((CoverIndex.X * TargetGenerationSetting.VoxelHalfSize.X * 2) - VoxelHalfBounds.X - BoundExpand, LocalBounds.Min.Y, LocalBounds.Min.Z),
					FVector((CoverIndex.Y * TargetGenerationSetting.VoxelHalfSize.X * 2) - VoxelHalfBounds.X + BoundExpand, LocalBounds.Max.Y, LocalBounds.Max.Z)
				);

				if (DirectionIndex == 3) LumenBox = LumenBox.ShiftBy(FVector(TargetGenerationSetting.VoxelHalfSize.X, 0.0f, 0.0f) * 2.0f);
				break;

			case 2: case 4:
				LumenBox = FBox(
					FVector(LocalBounds.Min.X, (CoverIndex.X * TargetGenerationSetting.VoxelHalfSize.Y * 2) - VoxelHalfBounds.Y - BoundExpand, LocalBounds.Min.Z),
					FVector(LocalBounds.Max.X, (CoverIndex.Y * TargetGenerationSetting.VoxelHalfSize.Y * 2) - VoxelHalfBounds.Y + BoundExpand, LocalBounds.Max.Z)
				);

				if (DirectionIndex == 2) LumenBox = LumenBox.ShiftBy(FVector(0.0f, TargetGenerationSetting.VoxelHalfSize.Y, 0.0f) * 2.0f);
				break;
			}

			FLumenCardBuildData BuildData;

			BuildData.AxisAlignedDirectionIndex = LFPVoxelRendererConstantData::SurfaceDirectionID[DirectionIndex];

			LFPVoxelRendererConstantData::FaceDirection[DirectionIndex].SetAxis(
				BuildData.OBB.AxisX,
				BuildData.OBB.AxisY,
				BuildData.OBB.AxisZ
			);

			BuildData.OBB.Origin = FVector3f(LumenBox.GetCenter());
			BuildData.OBB.Extent = FVector3f(LFPVoxelRendererConstantData::VertexRotationList[DirectionIndex].UnrotateVector(LumenBox.GetExtent()).GetAbs());

			CardBuildList.Add(BuildData);

			return;
		};

		//const double StartTime = FPlatformTime::Seconds();

		TargetThreadResult->LumenCardData->MeshCardsBuildData.Bounds = LocalBounds;

		TArray<FLumenCardBuildData>& CardBuildList = TargetThreadResult->LumenCardData->MeshCardsBuildData.CardBuildData;

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
				ContainerSetting.GetPaletteGrid()[FaceData.ID.X],
				ContainerSetting.GetPaletteGrid()[FaceData.ID.Y],
				ContainerSetting.GetPaletteGrid()[FaceData.ID.Z]
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

						const bool bIsFaceVisible = CheckFaceVisible(VoxelGridLocation, LFPVoxelRendererConstantData::FaceDirection[FaceData.FaceID].Up);

						if (BlockMap[VoxelPlaneIndex])
						{
							if (bIsFaceVisible)
							{
								AddCardBuild(CardBuildList, CoverIndex, FaceData.FaceID);

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
				AddCardBuild(CardBuildList, CoverIndex, FaceData.FaceID);
			}
		}

		if (TargetGenerationSetting.bPrintGenerateTime) UE_LOG(LogTemp, Warning, TEXT("Lumen Card Data Time Use : %f"), (float)(FPlatformTime::Seconds() - TaskTime));
	}

	if (TargetGenerationSetting.bPrintGenerateTime) UE_LOG(LogTemp, Warning, TEXT("Lumen Generate Time Use : %f"), (float)(FPlatformTime::Seconds() - StartTime));
}

FColor ULFPVoxelRendererComponent::GetVoxelAttribute(const FLFPGridPaletteData& VoxelPalette, const TMap<FName, uint8>& TagDataList) const
{
	return VoxelPalette.Name.IsNone() ? GetGenerationSetting().EmptyVoxelNameColor : FColor(255);
}

int32 ULFPVoxelRendererComponent::GetVoxelMaterialIndex(const FLFPGridPaletteData& VoxelPalette) const
{
	return VoxelPalette.Name == FName("Dirt") ? 0 : VoxelPalette.Name == FName("Grass") && GetNumMaterials() >= 0 ? 1 : INDEX_NONE;
}

/**********************/
/** Rendering Handling */

FPrimitiveSceneProxy* ULFPVoxelRendererComponent::CreateSceneProxy()
{
	return ThreadResult.IsValid() && ThreadResult->SectionData.Num() > 0 ? new FLFPVoxelRendererSceneProxy(this, ThreadResult->bIsDynamic) : nullptr;
}

FBoxSphereBounds ULFPVoxelRendererComponent::CalcBounds(const FTransform& LocalToWorld) const
{
	FBox VoxelBox;

	if (IsValid(VoxelContainer) && ThreadResult.IsValid())
	{
		const FVector VoxelHalfBounds = GetGenerationSetting().VoxelHalfSize * FVector(VoxelContainer->GetSetting().GetPaletteGrid());
		VoxelBox = FBox(-VoxelHalfBounds, VoxelHalfBounds);
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

/**********************/
/** Collision Handling */

bool ULFPVoxelRendererComponent::GetTriMeshSizeEstimates(FTriMeshCollisionDataEstimates& OutTriMeshEstimates, bool bInUseAllTriData) const
{
	if (ThreadResult.IsValid() == false || ThreadResult->SectionData.Num() == 0) return false;

	// For each section..
	for (int32 SectionIdx = 0; SectionIdx < ThreadResult->SectionData.Num(); SectionIdx++)
	{
		if (ThreadResult->SectionData[SectionIdx].TriangleCount == 0)
		{
			continue;
		}

		OutTriMeshEstimates.VerticeCount += ThreadResult->SectionData[SectionIdx].TriangleCount * 3;
	}

	return true;
}

bool ULFPVoxelRendererComponent::GetPhysicsTriMeshData(FTriMeshCollisionData* CollisionData, bool InUseAllTriData)
{
	if (ThreadResult.IsValid() == false || ThreadResult->SectionData.Num() == 0) return false;
	
	const FVector3f VoxelHalfSize = FVector3f(GetGenerationSetting().VoxelHalfSize);
	const FVector3f VoxelHalfBounds = VoxelHalfSize * FVector3f(VoxelContainer->GetSetting().GetPaletteGrid());
	const FVector3f VoxelRenderOffset = FVector3f(-VoxelHalfBounds + VoxelHalfSize);
	
	// For each section..
	for (int32 SectionIdx = 0; SectionIdx < ThreadResult->SectionData.Num(); SectionIdx++)
	{
		if (ThreadResult->SectionData[SectionIdx].TriangleCount == 0)
		{
			continue;
		}
	
		ThreadResult->SectionData[SectionIdx].GenerateCollisionData(VoxelHalfSize, VoxelRenderOffset, SectionIdx, CollisionData);
	}
	
	CollisionData->bFlipNormals = true;
	CollisionData->bDeformableMesh = false;
	CollisionData->bFastCook = true;
	
	return true;
}

bool ULFPVoxelRendererComponent::ContainsPhysicsTriMeshData(bool InUseAllTriData) const
{
	if (ThreadResult.IsValid() == false || ThreadResult->bIsDynamic == false) return false;

	for (const auto& Section : ThreadResult->SectionData)
	{
		if (Section.TriangleCount > 0) return true;
	}

	return false;
}

bool ULFPVoxelRendererComponent::WantsNegXTriMesh()
{
	return false;
}

UBodySetup* ULFPVoxelRendererComponent::GetBodySetup()
{
	if (IsValid(BodySetup) == false)
	{
		BodySetup = CreateBodySetup();
	}

	return BodySetup;
}

UBodySetup* ULFPVoxelRendererComponent::CreateBodySetup()
{
	UBodySetup* NewBodySetup = NewObject<UBodySetup>(this, NAME_None, (IsTemplate() ? RF_Public | RF_ArchetypeObject : RF_NoFlags));
	NewBodySetup->BodySetupGuid = FGuid::NewGuid();

	NewBodySetup->bGenerateMirroredCollision = false;
	NewBodySetup->bDoubleSidedGeometry = true;

	NewBodySetup->CollisionTraceFlag = GenerationSetting.CollisionTraceFlag;

	return NewBodySetup;
}

void ULFPVoxelRendererComponent::RebuildPhysicsData()
{
	if (IsValid(BodySetup) == false)
	{
		BodySetup = CreateBodySetup();
	}

	if (BodySetup->CurrentCookHelper)
	{
		Status.bIsBodyInvalid = true;
	}
	else if (ThreadResult.IsValid())
	{
		BodySetup->CreatePhysicsMeshesAsync(FOnAsyncPhysicsCookFinished::CreateUObject(this, &ULFPVoxelRendererComponent::FinishPhysicsAsyncCook, BodySetup.Get()));
	}
}

void ULFPVoxelRendererComponent::FinishPhysicsAsyncCook(bool bSuccess, UBodySetup* FinishedBodySetup)
{
	if (bSuccess)
	{
		BodySetup->CollisionTraceFlag = GenerationSetting.CollisionTraceFlag;

		BodySetup->AggGeom.BoxElems = ThreadResult->CollisionData.BoxElems;

		RecreatePhysicsState();
	}

	if (Status.bIsBodyInvalid)
	{
		Status.bIsBodyInvalid = false;

		RebuildPhysicsData();
	}
}

/**********************/
/**********************/
