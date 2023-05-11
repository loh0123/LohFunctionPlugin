// Copyright by Loh Zhi Kang


#include "Voxel/LFPVoxelRendererComponent.h"
#include "Voxel/LFPVoxelRendererSceneProxy.h"
#include "DistanceFieldAtlas.h"
#include "MeshCardRepresentation.h"
#include "Math/LFPGridLibrary.h"

using namespace UE::Tasks;

FLFPVoxelPaletteData FLFPVoxelPaletteData::EmptyData = FLFPVoxelPaletteData();

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

	// ...

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

	ThreadResult.Reset();

	ThreadOutput = {};
}

void ULFPVoxelRendererComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsValid(VoxelContainer) == false) return;

	if (Status.bIsVoxelAttributeDirty && IsValid(AttributesTexture))
	{
		Status.bIsVoxelAttributeDirty = false;

		const FIntVector DataColorGridSize = VoxelContainer->GetSetting().GetVoxelGrid() + FIntVector(2);
		const int32 DataColorSize = DataColorGridSize.X * DataColorGridSize.Y * DataColorGridSize.Z;

		TArray<FColor> AttributeList;

		AttributeList.SetNum(DataColorSize);

		ParallelFor(DataColorSize, [&](const int32 Index) {
			const FIntVector VoxelGlobalGridLocation = (ULFPGridLibrary::ToGridLocation(Index, DataColorGridSize) - FIntVector(1)) + VoxelContainer->ToVoxelGlobalPosition(FIntVector(RegionIndex, ChuckIndex, 0));
			const FIntVector VoxelGridIndex = VoxelContainer->ToVoxelGlobalIndex(VoxelGlobalGridLocation);

			const FLFPVoxelPaletteData& VoxelPalette = VoxelContainer->GetVoxelPaletteRef(VoxelGridIndex.X, VoxelGridIndex.Y, VoxelGridIndex.Z);

			AttributeList[Index] = GetVoxelAttribute(VoxelPalette);
			}, EParallelForFlags::BackgroundPriority);

		ULFPRenderLibrary::UpdateTexture2D(AttributesTexture, AttributeList);
	}

	if (Status.bIsVoxelMeshDirty)
	{
		Status.bIsVoxelMeshDirty = false;

		ULFPVoxelContainerComponent* CurrentContainer = VoxelContainer;
		FLFPVoxelRendererSetting CurrentSetting = GenerationSetting;

		ThreadOutput = 
			Launch(UE_SOURCE_LOCATION, [&, CurrentContainer, CurrentSetting]
			{ 
				FReadScopeLock Lock(CurrentContainer->ContainerThreadLock);

				TSharedPtr<FLFPVoxelRendererThreadResult> TargetThreadResult = MakeShared<FLFPVoxelRendererThreadResult>();

				GenerateBatchFaceData(CurrentContainer, TargetThreadResult);

				if (CurrentSetting.bGenerateSimpleCollisionData) GenerateSimpleCollisionData(CurrentContainer, TargetThreadResult);
				if (CurrentSetting.bGenerateLumenData) GenerateLumenData(CurrentContainer, TargetThreadResult);

				return TargetThreadResult;
			}, ETaskPriority::BackgroundNormal);

		Status.bIsRenderDirty = true;
	}

	if (Status.bIsRenderDirty && ThreadOutput.IsCompleted())
	{
		ThreadResult = ThreadOutput.GetResult();

		UpdateBounds();

		MarkRenderStateDirty();

		if (GenerationSetting.bGenerateCollisionData) RebuildPhysicsData();

		SetComponentTickEnabled(false);

		OnVoxelRendererUpdate.Broadcast();
	}
}

bool ULFPVoxelRendererComponent::InitializeRenderer(const int32 NewRegionIndex, const int32 NewChuckIndex, ULFPVoxelContainerComponent* NewVoxelContainer)
{
	if (IsValid(NewVoxelContainer) == false) return false;

	ReleaseRenderer();

	VoxelContainer = NewVoxelContainer;

	FLFPVoxelChuckDelegate Delegate;

	Delegate.VoxelChuckUpdateEvent.BindUObject(this, &ULFPVoxelRendererComponent::OnChuckUpdate);

	if (VoxelContainer->AddRenderChuck(NewRegionIndex, NewChuckIndex, Delegate))
	{
		RegionIndex = NewRegionIndex;

		ChuckIndex = NewChuckIndex;

		VoxelContainer->InitializeVoxelChuck(NewRegionIndex, NewChuckIndex);

		const FIntPoint VoxelTextureSize(VoxelContainer->GetSetting().GetVoxelGrid().X + 2, (VoxelContainer->GetSetting().GetVoxelGrid().Y + 2) * (VoxelContainer->GetSetting().GetVoxelGrid().Z + 2));

		AttributesTexture = ULFPRenderLibrary::CreateTexture2D(VoxelTextureSize, TF_Nearest);

		return true;
	}

	return false;
}

bool ULFPVoxelRendererComponent::ReleaseRenderer()
{
	if (IsValid(VoxelContainer) == false) return false;

	VoxelContainer->RemoveRenderChuck(RegionIndex, ChuckIndex);

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
	if (IsValid(VoxelContainer) && VoxelContainer->IsChuckInitialized(RegionIndex, ChuckIndex))
	{
		Status.bIsVoxelMeshDirty = true;

		SetComponentTickEnabled(true);
	}
	else
	{
		UE_LOG(LFPVoxelRendererComponent, Warning, TEXT("Voxel Mesh Can't Be Update Because Voxel Container Is Not Valid"));
	}
}

void ULFPVoxelRendererComponent::UpdateAttribute()
{
	if (IsValid(VoxelContainer) && VoxelContainer->IsChuckInitialized(RegionIndex, ChuckIndex))
	{
		Status.bIsVoxelAttributeDirty = true;

		SetComponentTickEnabled(true);
	}
	else
	{
		UE_LOG(LFPVoxelRendererComponent, Warning, TEXT("Voxel Color Can't Be Update Because Voxel Container Is Not Valid"));
	}
}

void ULFPVoxelRendererComponent::OnChuckUpdate(const FLFPChuckUpdateAction& Data)
{
	if (Data.bIsVoxelTagDirty) UpdateAttribute();

	if (Data.bIsVoxelNameDirty) UpdateMesh();
}

/**********************/
/** Material Handling */

void ULFPVoxelRendererComponent::SetMaterialList(const TArray<UMaterialInterface*>& Material)
{
	if (Material.IsEmpty() == false)
	{
		for (int k = 0; k < Material.Num(); ++k)
		{
			SetMaterial(k, Material[k]);
		}
	}
	else
	{
		UE_LOG(LFPVoxelRendererComponent, Warning, TEXT("Can't Set Material Because Array Is Empty"));
	}
}

void ULFPVoxelRendererComponent::GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials) const
{
	OutMaterials.Append(MaterialList);
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
	return MaterialList.Num();
}

UMaterialInterface* ULFPVoxelRendererComponent::GetMaterial(int32 ElementIndex) const
{
	return MaterialList.IsValidIndex(ElementIndex) ? MaterialList[ElementIndex] : nullptr;
}

void ULFPVoxelRendererComponent::SetMaterial(int32 ElementIndex, UMaterialInterface* Material)
{
	check(ElementIndex >= 0);

	if (ElementIndex >= MaterialList.Num())
	{
		MaterialList.SetNum(ElementIndex + 1, false);
	}

	MaterialList[ElementIndex] = IsValid(Material) ? Material : UMaterial::GetDefaultMaterial(MD_Surface);

	if (IsValid(VoxelContainer))
	{
		UpdateMesh();
		UpdateAttribute();
	}
}

UMaterialInstanceDynamic* ULFPVoxelRendererComponent::CreateDynamicMaterialInstance(int32 ElementIndex, UMaterialInterface* SourceMaterial, FName OptionalName)
{
	UMaterialInstanceDynamic* MID = Super::CreateDynamicMaterialInstance(ElementIndex, SourceMaterial, OptionalName);

	if (IsValid(MID))
	{
		MID->SetTextureParameterValue("AttributesTexture", AttributesTexture);

		if (IsValid(VoxelContainer)) MID->SetVectorParameterValue("VoxelChuckSize", FVector(VoxelContainer->GetSetting().GetVoxelGrid()));
	}

	return MID;
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

bool ULFPVoxelRendererComponent::IsFaceVisible(const FLFPVoxelPaletteData& FromPaletteData, const FLFPVoxelPaletteData& ToPaletteData) const
{
	const int32 CurrentIndex = GetVoxelMaterialIndex(FromPaletteData);

	return CurrentIndex != INDEX_NONE && CurrentIndex != GetVoxelMaterialIndex(ToPaletteData);
}

void ULFPVoxelRendererComponent::GenerateBatchFaceData(ULFPVoxelContainerComponent* TargetVoxelContainer, TSharedPtr<FLFPVoxelRendererThreadResult>& TargetThreadResult)
{
	const double StartTime = FPlatformTime::Seconds();

	const FLFPVoxelContainerSetting& VoxelSetting = TargetVoxelContainer->GetSetting();

	TargetThreadResult->SectionData.Init(FLFPVoxelRendererSectionData(VoxelSetting.GetVoxelGrid()), FMath::Max(GetNumMaterials(), 1));

	const auto& PushFaceData = [&](TMap<FIntVector, FIntPoint>& BatchDataMap, FInt32Rect& CurrentBatchFaceData, int32& CurrentBatchMaterial) {
		const FIntVector TargetMax = FIntVector(CurrentBatchFaceData.Max.X - 1, CurrentBatchFaceData.Max.Y, CurrentBatchMaterial);
		const FIntPoint* TargetMin = BatchDataMap.Find(TargetMax);

		if (TargetMin != nullptr && TargetMin->Y == CurrentBatchFaceData.Min.Y)
		{
			FIntPoint NewMin = BatchDataMap.FindAndRemoveChecked(TargetMax);

			CurrentBatchFaceData.Min.X = NewMin.X;
		}

		BatchDataMap.Add(FIntVector(CurrentBatchFaceData.Max.X, CurrentBatchFaceData.Max.Y, CurrentBatchMaterial), CurrentBatchFaceData.Min);
		CurrentBatchMaterial = INDEX_NONE;
	};

	//ParallelFor(6, [&](const int32 DirectionIndex) {
	for (int32 DirectionIndex = 0; DirectionIndex < 6; DirectionIndex++)
	{
		const FIntVector FaceLoopDirection = LFPVoxelRendererConstantData::FaceLoopDirectionList[DirectionIndex];

		const int32 LoopU = VoxelSetting.GetVoxelGrid()[FaceLoopDirection.X];
		const int32 LoopV = VoxelSetting.GetVoxelGrid()[FaceLoopDirection.Y];
		const int32 LoopI = VoxelSetting.GetVoxelGrid()[FaceLoopDirection.Z];

		//ParallelFor(LoopI, [&](const int32 I) {
		for (int32 I = 0; I < LoopI; I++)
		{
			TMap<FIntVector, FIntPoint> BatchDataMap;

			FInt32Rect CurrentBatchFaceData(INDEX_NONE, INDEX_NONE);

			int32 CurrentBatchMaterial = INDEX_NONE;

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

					const int32 CurrentIndex = ULFPGridLibrary::ToGridIndex(CurrentPos, VoxelSetting.GetVoxelGrid());

					const FIntVector CurrentGlobalPos = TargetVoxelContainer->ToVoxelGlobalPosition(FIntVector(RegionIndex, ChuckIndex, CurrentIndex));

					const FIntVector TargetGlobalPos = CurrentGlobalPos + LFPVoxelRendererConstantData::FaceDirection[DirectionIndex].Up;

					const FIntVector TargetGlobalIndex = TargetVoxelContainer->ToVoxelGlobalIndex(TargetGlobalPos);

					const FLFPVoxelPaletteData& SelfVoxelPalette = TargetVoxelContainer->GetVoxelPaletteRef(RegionIndex, ChuckIndex, CurrentIndex);

					/** Check Do We Ignore Border Data And Always Fill The Face */
					const FLFPVoxelPaletteData& TargetVoxelPalette = 
						GenerationSetting.bFillChuckFace && (RegionIndex != TargetGlobalIndex.X || ChuckIndex != TargetGlobalIndex.Y) ? 
						FLFPVoxelPaletteData::EmptyData 
						: 
						TargetVoxelContainer->GetVoxelPaletteRef(TargetGlobalIndex.X, TargetGlobalIndex.Y, TargetGlobalIndex.Z);

					/*************************************************/

					if (IsFaceVisible(SelfVoxelPalette, TargetVoxelPalette))
					{
						const int32 CurrentMaterialIndex = GetVoxelMaterialIndex(SelfVoxelPalette);

						if (CurrentBatchFaceData.Max.X != U && CurrentBatchMaterial != INDEX_NONE)
						{
							PushFaceData(BatchDataMap, CurrentBatchFaceData, CurrentBatchMaterial);
						}

						if (CurrentBatchMaterial == CurrentMaterialIndex)
						{
							CurrentBatchFaceData.Max.Y += 1;
						}
						else if (CurrentBatchMaterial != INDEX_NONE)
						{
							PushFaceData(BatchDataMap, CurrentBatchFaceData, CurrentBatchMaterial);
						}

						if (CurrentBatchMaterial == INDEX_NONE)
						{
							CurrentBatchFaceData = FInt32Rect(U, V, U, V);
							CurrentBatchMaterial = CurrentMaterialIndex;
						}
					}
					else if (CurrentBatchMaterial != INDEX_NONE)
					{
						PushFaceData(BatchDataMap, CurrentBatchFaceData, CurrentBatchMaterial);
					}

				}
			}

			if (CurrentBatchMaterial != INDEX_NONE)
			{
				PushFaceData(BatchDataMap, CurrentBatchFaceData, CurrentBatchMaterial);
			}

			for (const auto& BatchData : BatchDataMap)
			{
				TargetThreadResult->SectionData[BatchData.Key.Z].GetVoxelFaceData(DirectionIndex, I).FaceDataList.Add(FInt32Rect(BatchData.Value, FIntPoint(BatchData.Key.X, BatchData.Key.Y)));
				TargetThreadResult->SectionData[BatchData.Key.Z].TriangleCount += 2;
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

	if (GenerationSetting.bPrintGenerateTime) UE_LOG(LogTemp, Warning, TEXT("BatchFace Generate Time Use : %f"), (float)(FPlatformTime::Seconds() - StartTime));
}

void ULFPVoxelRendererComponent::GenerateSimpleCollisionData(ULFPVoxelContainerComponent* TargetVoxelContainer, TSharedPtr<FLFPVoxelRendererThreadResult>& TargetThreadResult)
{
	const double StartTime = FPlatformTime::Seconds();

	const FLFPVoxelContainerSetting& VoxelSetting = VoxelContainer->GetSetting();

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
	for (int32 Z = 0; Z < VoxelSetting.GetVoxelGrid().Z; Z++)
	{
		for (int32 Y = 0; Y < VoxelSetting.GetVoxelGrid().Y; Y++)
		{
			for (int32 X = 0; X < VoxelSetting.GetVoxelGrid().X; X++)
			{
				/***************** Identify Data *****************/
				const FIntVector CurrentPos(X, Y, Z);

				const int32 CurrentIndex = ULFPGridLibrary::ToGridIndex(CurrentPos, VoxelSetting.GetVoxelGrid());

				const bool IsSelfSolid = GetVoxelMaterialIndex(TargetVoxelContainer->GetVoxelPaletteRef(RegionIndex, ChuckIndex, CurrentIndex)) >= 0;
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

	const FVector BoxHalfSize = TargetVoxelContainer->GetSetting().GetVoxelHalfSize();
	const FVector BoxSize = BoxHalfSize * 2;
	const FVector RenderOffset = -TargetVoxelContainer->GetSetting().GetVoxelHalfBounds();

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

	if (GenerationSetting.bPrintGenerateTime) UE_LOG(LogTemp, Warning, TEXT("Collision Generate Time Use : %f"), (float)(FPlatformTime::Seconds() - StartTime));
}

void ULFPVoxelRendererComponent::GenerateLumenData(ULFPVoxelContainerComponent* TargetVoxelContainer, TSharedPtr<FLFPVoxelRendererThreadResult>& TargetThreadResult)
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
		FLFPDFBrickTask(const int32 InBrickLength, const FVector& InBrickVoxelSize, const int32 InBrickIndex, const FVector& InBrickSpaceLocation, const FLFPVoxelContainerSetting& InContainerSetting, const FLFPDFMipInfo& InMipInfo, const TArray<FLFPCacheAccelerationInfo>& InAccelerationInfoList, const float InLocalToVolumeScale, const FIntVector InCheckSize, const int32 InSizeHalfOffset)
			: BrickLength(InBrickLength), BrickIndex(InBrickIndex), BrickSpaceLocation(InBrickSpaceLocation), BrickVoxelSize(InBrickVoxelSize), ContainerSetting(InContainerSetting), MipInfo(InMipInfo), AccelerationInfoList(InAccelerationInfoList), LocalToVolumeScale(InLocalToVolumeScale), CheckSize(InCheckSize), SizeHalfOffset(InSizeHalfOffset)
		{}

		FORCEINLINE float GetDistanceToClosetSurface(const FVector& LocalLocation) const
		{
			const FVector VoxelSize = ContainerSetting.GetVoxelHalfSize() * 2;
			const FVector LocalSpace = LocalLocation / VoxelSize;
			const FIntVector GridLocation = FIntVector(FMath::FloorToInt32(LocalSpace.X), FMath::FloorToInt32(LocalSpace.Y), FMath::FloorToInt32(LocalSpace.Z));
			const int32 FullGridIndex = ULFPGridLibrary::ToGridIndex(GridLocation + FIntVector(SizeHalfOffset), CheckSize);
			//const int32 GridIndex = ULFPGridLibrary::ToGridIndex(GridLocation, ContainerSetting.GetVoxelGrid());

			checkf(FullGridIndex >= 0, TEXT("Error Index : %s"), *GridLocation.ToString());

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
		const FLFPVoxelContainerSetting& ContainerSetting;
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
	const FLFPVoxelContainerSetting ContainerSetting = TargetVoxelContainer->GetSetting();

	const FVector& VoxelSize = ContainerSetting.GetVoxelHalfSize() * 2;

	const FVector TargetDimensions = FVector(ContainerSetting.GetVoxelGrid()) * (double(GenerationSetting.LumenQuality) / 8.0);

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

	const float BoundExpand = 5.0f;

	const FBox LocalBounds = FBox(-ContainerSetting.GetVoxelHalfBounds() - BoundExpand, ContainerSetting.GetVoxelHalfBounds() + BoundExpand);

	const FBox LocalSpaceMeshBounds(LocalBounds.ExpandBy(
		LocalBounds.GetSize() / FVector(MinIndirectionDimensions * DistanceField::UniqueDataBrickSize - FIntVector(2 * 0.25f))
	));

	const int32 BrickLength = DistanceField::BrickSize * DistanceField::BrickSize * DistanceField::BrickSize;

	const float LocalToVolumeScale = 1.0f / LocalSpaceMeshBounds.GetExtent().GetMax();
	const float LocalToVoxelScale = 1.0f / ContainerSetting.GetVoxelHalfSize().GetMax();
	/////////////////

	/* Calculate MaxCheckDistance */
	FLFPDFMipInfo MinMipInfo(MinIndirectionDimensions, LocalSpaceMeshBounds, LocalToVolumeScale);

	const int32 MaxCheckDistance = FMath::CeilToInt(MinMipInfo.LocalSpaceTraceDistance * LocalToVoxelScale);

	const FVector MinBrickOffset = MinMipInfo.DistanceFieldVolumeBounds.Min + ContainerSetting.GetVoxelHalfBounds();

	const int32 SizeOffset = FMath::DivideAndRoundUp(MinBrickOffset.GetAbsMax(), ContainerSetting.GetVoxelHalfSize().GetAbsMax() * 2) * 2;
	const int32 SizeHalfOffset = SizeOffset / 2;

	const FIntVector CheckSize(
		ContainerSetting.GetVoxelGrid().X + SizeOffset,
		ContainerSetting.GetVoxelGrid().Y + SizeOffset,
		ContainerSetting.GetVoxelGrid().Z + SizeOffset
	);

	const int32 CheckLength = CheckSize.X * CheckSize.Y * CheckSize.Z;

	/** Acceleration Data To Speed Up Calculation */
	TArray<FLFPCacheAccelerationInfo> AccelerationInfoList;
	{
		AccelerationInfoList.Init(FLFPCacheAccelerationInfo(), CheckLength);

		/** Generate Material Index List */
		for (int32 Index = 0; Index < CheckLength; Index++)
		{
			const FIntVector VoxelPosition(ULFPGridLibrary::ToGridLocation(Index, CheckSize) - FIntVector(SizeHalfOffset));

			AccelerationInfoList[Index].MaterialIndex = GetVoxelMaterialIndex(TargetVoxelContainer->GetVoxelPalette(RegionIndex, ChuckIndex, ULFPGridLibrary::ToGridIndex(VoxelPosition, ContainerSetting.GetVoxelGrid())));
		}

		ParallelFor(CheckLength, [&](const int32 Index) {
			FLFPCacheAccelerationInfo& CurrentCacheInfo = AccelerationInfoList[Index];

			const FIntVector CacheLocation = ULFPGridLibrary::ToGridLocation(Index, CheckSize) - FIntVector(SizeHalfOffset);

			/** Generate Trace Distance */
			{
				for (CurrentCacheInfo.TraceDistance = 1; CurrentCacheInfo.TraceDistance <= MaxCheckDistance; CurrentCacheInfo.TraceDistance++)
				{
					bool bIsHit = false;

					for (int32 Z = CacheLocation.Z - CurrentCacheInfo.TraceDistance; Z <= CacheLocation.Z + CurrentCacheInfo.TraceDistance; Z++)
					{
						for (int32 Y = CacheLocation.Y - CurrentCacheInfo.TraceDistance; Y <= CacheLocation.Y + CurrentCacheInfo.TraceDistance; Y++)
						{
							for (int32 X = CacheLocation.X - CurrentCacheInfo.TraceDistance; X <= CacheLocation.X + CurrentCacheInfo.TraceDistance; X++)
							{
								const int32 CheckGridIndex = ULFPGridLibrary::ToGridIndex(FIntVector(X, Y, Z) + FIntVector(SizeHalfOffset), CheckSize);
								const int32 CheckMaterial = CheckGridIndex == INDEX_NONE ? INDEX_NONE : AccelerationInfoList[CheckGridIndex].MaterialIndex;

								if (CheckMaterial != CurrentCacheInfo.MaterialIndex)
								{
									bIsHit = true;

									break;
								}

								if (Z != CacheLocation.Z - CurrentCacheInfo.TraceDistance && Z != CacheLocation.Z + CurrentCacheInfo.TraceDistance && Y != CacheLocation.Y - CurrentCacheInfo.TraceDistance && Y != CacheLocation.Y + CurrentCacheInfo.TraceDistance && X == CacheLocation.X - CurrentCacheInfo.TraceDistance)
								{
									X = CacheLocation.X + CurrentCacheInfo.TraceDistance - 1;
								}
							}

							if (bIsHit) break;
						}

						if (bIsHit) break;
					}

					if (bIsHit) break;
				}
			}

			/** Generate Trace Box */
			{
				for (int32 SectionIndex = 0; SectionIndex < TargetThreadResult->SectionData.Num(); SectionIndex++)
				{
					TargetThreadResult->SectionData[SectionIndex].GenerateDistanceBoxData(CacheLocation, SectionIndex == CurrentCacheInfo.MaterialIndex, CurrentCacheInfo.TraceDistance, CurrentCacheInfo.TraceBoxList);
				}

				for (FBox& TraceBox : CurrentCacheInfo.TraceBoxList)
				{
					TraceBox.Min *= ContainerSetting.GetVoxelHalfSize() * 2;
					TraceBox.Max *= ContainerSetting.GetVoxelHalfSize() * 2;

					TraceBox.Min += ContainerSetting.GetVoxelHalfSize();
					TraceBox.Max += ContainerSetting.GetVoxelHalfSize();
				}
			}
		}, EParallelForFlags::Unbalanced | EParallelForFlags::BackgroundPriority);
	}

	{
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
			const FVector BrickOffset = MipInfo.DistanceFieldVolumeBounds.Min + ContainerSetting.GetVoxelHalfBounds();
			//const FVector BrickOffset = FVector(0.0f);

			//checkf(false, TEXT("%s"), *(MipInfo.DistanceFieldVolumeBounds.Min + ContainerSetting.GetVoxelHalfBounds()).ToString());

			//UE_LOG(LogTemp, Warning, TEXT("The integer value is: %d"), CheckRange);

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
					ContainerSetting,
					MipInfo,
					AccelerationInfoList,
					LocalToVolumeScale,
					CheckSize,
					SizeHalfOffset
				));
			}

			ParallelFor(BrickTaskList.Num(), [&BrickTaskList](int32 TaskIndex)
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
	}

	{
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
					FVector(LocalBounds.Min.X, LocalBounds.Min.Y, (CoverIndex.X * ContainerSetting.GetVoxelHalfSize().Z * 2) - ContainerSetting.GetVoxelHalfBounds().Z - BoundExpand),
					FVector(LocalBounds.Max.X, LocalBounds.Max.Y, (CoverIndex.Y * ContainerSetting.GetVoxelHalfSize().Z * 2) - ContainerSetting.GetVoxelHalfBounds().Z + BoundExpand)
				);

				if (DirectionIndex == 0) LumenBox = LumenBox.ShiftBy(FVector(0.0f, 0.0f, ContainerSetting.GetVoxelHalfSize().Z) * 2.0f);
				break;

			case 1: case 3:
				LumenBox = FBox(
					FVector((CoverIndex.X * ContainerSetting.GetVoxelHalfSize().X * 2) - ContainerSetting.GetVoxelHalfBounds().X - BoundExpand, LocalBounds.Min.Y, LocalBounds.Min.Z),
					FVector((CoverIndex.Y * ContainerSetting.GetVoxelHalfSize().X * 2) - ContainerSetting.GetVoxelHalfBounds().X + BoundExpand, LocalBounds.Max.Y, LocalBounds.Max.Z)
				);

				if (DirectionIndex == 3) LumenBox = LumenBox.ShiftBy(FVector(ContainerSetting.GetVoxelHalfSize().X, 0.0f, 0.0f) * 2.0f);
				break;

			case 2: case 4:
				LumenBox = FBox(
					FVector(LocalBounds.Min.X, (CoverIndex.X * ContainerSetting.GetVoxelHalfSize().Y * 2) - ContainerSetting.GetVoxelHalfBounds().Y - BoundExpand, LocalBounds.Min.Z),
					FVector(LocalBounds.Max.X, (CoverIndex.Y * ContainerSetting.GetVoxelHalfSize().Y * 2) - ContainerSetting.GetVoxelHalfBounds().Y + BoundExpand, LocalBounds.Max.Z)
				);

				if (DirectionIndex == 2) LumenBox = LumenBox.ShiftBy(FVector(0.0f, ContainerSetting.GetVoxelHalfSize().Y, 0.0f) * 2.0f);
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
				ContainerSetting.GetVoxelGrid()[FaceData.ID.X],
				ContainerSetting.GetVoxelGrid()[FaceData.ID.Y],
				ContainerSetting.GetVoxelGrid()[FaceData.ID.Z]
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
	}

	if (GenerationSetting.bPrintGenerateTime) UE_LOG(LogTemp, Warning, TEXT("Lumen Generate Time Use : %f"), (float)(FPlatformTime::Seconds() - StartTime));
}

FColor ULFPVoxelRendererComponent::GetVoxelAttribute(const FLFPVoxelPaletteData& VoxelPalette) const
{
	return VoxelPalette.VoxelName.IsNone() ? FColor(255) : FColor(0);
}

int32 ULFPVoxelRendererComponent::GetVoxelMaterialIndex(const FLFPVoxelPaletteData& VoxelPalette) const
{
	return VoxelPalette.VoxelName == FName("Dirt") ? 0 : VoxelPalette.VoxelName == FName("Grass") && GetNumMaterials() >= 0 ? 1 : INDEX_NONE;
}

/**********************/
/** Rendering Handling */

FPrimitiveSceneProxy* ULFPVoxelRendererComponent::CreateSceneProxy()
{
	return ThreadResult.IsValid() && ThreadResult->SectionData.Num() > 0 ? new FLFPVoxelRendererSceneProxy(this) : nullptr;
}

FBoxSphereBounds ULFPVoxelRendererComponent::CalcBounds(const FTransform& LocalToWorld) const
{
	FBox VoxelBox;

	if (IsValid(VoxelContainer) && ThreadResult.IsValid())
	{
		VoxelBox = FBox(-VoxelContainer->GetSetting().GetVoxelHalfBounds(), VoxelContainer->GetSetting().GetVoxelHalfBounds());
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
	
	const FVector3f VoxelHalfSize = FVector3f(VoxelContainer->GetSetting().GetVoxelHalfSize());
	const FVector3f VoxelRenderOffset = FVector3f(-VoxelContainer->GetSetting().GetVoxelHalfBounds() + VoxelContainer->GetSetting().GetVoxelHalfSize());
	
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
	return ThreadResult.IsValid() && ThreadResult->SectionData.Num() > 0;
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
