// Copyright by Loh Zhi Kang


#include "Voxel/LFPVoxelRendererComponent.h"
#include "Voxel/LFPVoxelRendererSceneProxy.h"
#include "Math/LFPGridLibrary.h"

FLFPVoxelPaletteData FLFPVoxelPaletteData::EmptyData = FLFPVoxelPaletteData();

//using namespace UE::Tasks;

DEFINE_LOG_CATEGORY(LFPVoxelRendererComponent);

// Sets default values for this component's properties
ULFPVoxelRendererComponent::ULFPVoxelRendererComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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
}


// Called every frame
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

		ParallelFor(DataColorSize,
			[&](const int32 Index)
			{
				const FIntVector VoxelGlobalGridLocation = (ULFPGridLibrary::ToGridLocation(Index, DataColorGridSize) - FIntVector(1)) + VoxelContainer->ToVoxelGlobalPosition(FIntVector(RegionIndex, ChuckIndex, 0));
				const FIntVector VoxelGridIndex = VoxelContainer->ToVoxelGlobalIndex(VoxelGlobalGridLocation);

				const FLFPVoxelPaletteData& VoxelPalette = VoxelContainer->GetVoxelPaletteRef(VoxelGridIndex.X, VoxelGridIndex.Y, VoxelGridIndex.Z);

				AttributeList[Index] = GetVoxelAttribute(VoxelPalette);
			}
		);

		ULFPRenderLibrary::UpdateTexture2D(AttributesTexture, AttributeList);
	}

	if (Status.bIsVoxelMeshDirty && WorkThread.IsCompleted()) GenerateBatchFaceData();
}

bool ULFPVoxelRendererComponent::Test(const FIntVector& LocalPosition, const int32 Range, TArray<FBox>& ReturnList, TArray<FTransform>& OriginReturnList)
{
	if (IsValid(VoxelContainer) == false || ThreadResult.IsValid() == false) return false;

	UE_LOG(LogTemp, Warning, TEXT("Section value is: %d"), ThreadResult->SectionData.Num());

	const int32 LocalIndex = ULFPGridLibrary::ToIndex(LocalPosition, VoxelContainer->GetSetting().GetVoxelGrid());

	const int32 CurrentMaterialIndex = LocalIndex != INDEX_NONE ? GetVoxelMaterialIndex(VoxelContainer->GetVoxelPalette(RegionIndex, ChuckIndex, LocalIndex)) : INDEX_NONE;

	int32 LoopIndex = 0;

	for (const auto& Section : ThreadResult->SectionData)
	{
		Section.GenerateDistanceBoxData(LocalPosition, CurrentMaterialIndex == LoopIndex, Range, ReturnList);

		LoopIndex++;
	}

	OriginReturnList.Reserve(ReturnList.Num());

	for (const FBox& Return : ReturnList)
	{
		OriginReturnList.Add(
			FTransform(
				FRotator(),
				(Return.GetCenter() * VoxelContainer->GetSetting().GetVoxelHalfSize() * 2) - VoxelContainer->GetSetting().GetVoxelHalfBounds() + VoxelContainer->GetSetting().GetVoxelHalfSize(),
				Return.GetExtent() * VoxelContainer->GetSetting().GetVoxelHalfSize() * 2
			)
		);
	}

	return true;
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

bool ULFPVoxelRendererComponent::IsFaceVisible(const FLFPVoxelPaletteData& FromPaletteData, const FLFPVoxelPaletteData& ToPaletteData) const
{
	const int32 CurrentIndex = GetVoxelMaterialIndex(FromPaletteData);

	return CurrentIndex != INDEX_NONE && CurrentIndex != GetVoxelMaterialIndex(ToPaletteData);
}

void ULFPVoxelRendererComponent::SetMaterialList(const TArray<UMaterialInterface*>& Material)
{
	if (Material.IsEmpty() == false)
	{
		for (int k = 0; k < Material.Num(); ++k)
		{
			SetMaterial(k, Material[k]);
		}

		if (IsValid(VoxelContainer))
		{
			UpdateMesh();
			UpdateAttribute();
		}
	}
	else
	{
		UE_LOG(LFPVoxelRendererComponent, Warning, TEXT("Can't Set Material Because Array Is Empty"));
	}
}

void ULFPVoxelRendererComponent::UpdateMesh()
{
	if (IsValid(VoxelContainer) && VoxelContainer->IsChuckInitialized(RegionIndex, ChuckIndex))
	{
		Status.bIsVoxelMeshDirty = true;
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
	}
	else
	{
		UE_LOG(LFPVoxelRendererComponent, Warning, TEXT("Voxel Color Can't Be Update Because Voxel Container Is Not Valid"));
	}
}

void ULFPVoxelRendererComponent::GenerateBatchFaceData()
{
	//Status.bIsGeneratingMesh = true;

	Status.bIsVoxelMeshDirty = false;

	//WorkThread = Launch(
	//	UE_SOURCE_LOCATION,
	//	[] { UE_LOG(LogTemp, Log, TEXT("Hello Tasks!")); }
	//);

	//FReadScopeLock Lock(VoxelContainer->ContainerThreadLock);

	const FLFPVoxelContainerSetting VoxelSetting(VoxelContainer->GetSetting());

	ThreadResult = MakeShared<FLFPVoxelRendererThreadResult>();

	ThreadResult->SectionData.Init(FLFPVoxelRendererSectionData(VoxelSetting.GetVoxelGrid()), FMath::Max(GetNumMaterials(), 1));

	const FIntVector ChuckStartPos = VoxelContainer->ToVoxelGlobalPosition(FIntVector(RegionIndex, ChuckIndex, 0));

	const auto& PushFaceData = [&](TMap<FIntVector, FInt32Rect>& BatchDataMap, FInt32Rect& CurrentBatchFaceData, int32& CurrentBatchMaterial) {
		const FInt32Rect* TargetData = BatchDataMap.Find(FIntVector(CurrentBatchFaceData.Max.X - 1, CurrentBatchFaceData.Max.Y, CurrentBatchMaterial));

		if (TargetData != nullptr && TargetData->Min.Y == CurrentBatchFaceData.Min.Y)
		{
			FInt32Rect NewData = BatchDataMap.FindAndRemoveChecked(FIntVector(CurrentBatchFaceData.Max.X - 1, CurrentBatchFaceData.Max.Y, CurrentBatchMaterial));

			CurrentBatchFaceData.Min.X = NewData.Min.X;
			CurrentBatchFaceData.Min.Y = NewData.Min.Y;
		}

		BatchDataMap.Add(FIntVector(CurrentBatchFaceData.Max.X, CurrentBatchFaceData.Max.Y, CurrentBatchMaterial), CurrentBatchFaceData);
		CurrentBatchMaterial = INDEX_NONE;
	};

	for (int32 DirectionIndex = 0; DirectionIndex < 6; DirectionIndex++)
	{
		const FIntVector FaceLoopDirection = LFPVoxelRendererConstantData::FaceLoopDirectionList[DirectionIndex];

		const int32 LoopU = VoxelSetting.GetVoxelGrid()[FaceLoopDirection.X];
		const int32 LoopV = VoxelSetting.GetVoxelGrid()[FaceLoopDirection.Y];
		const int32 LoopI = VoxelSetting.GetVoxelGrid()[FaceLoopDirection.Z];

		for (int32 I = 0; I < LoopI; I++)
		{
			TMap<FIntVector, FInt32Rect> BatchDataMap;

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

					FIntVector NextPos;

					NextPos[FaceLoopDirection.X] = U;
					NextPos[FaceLoopDirection.Y] = V + 1;
					NextPos[FaceLoopDirection.Z] = I;

					const int32 CurrentIndex = ULFPGridLibrary::ToIndex(CurrentPos, VoxelSetting.GetVoxelGrid());

					const FIntVector CurrentGlobalPos = VoxelContainer->ToVoxelGlobalPosition(FIntVector(RegionIndex, ChuckIndex, CurrentIndex));

					const FIntVector TargetGlobalPos = CurrentGlobalPos + LFPVoxelRendererConstantData::FaceDirection[DirectionIndex].Up;

					const FIntVector TargetGlobalIndex = VoxelContainer->ToVoxelGlobalIndex(TargetGlobalPos);

					const FLFPVoxelPaletteData& SelfVoxelPalette = VoxelContainer->GetVoxelPaletteRef(RegionIndex, ChuckIndex, CurrentIndex);
					const FLFPVoxelPaletteData& TargetVoxelPalette = VoxelContainer->GetVoxelPaletteRef(TargetGlobalIndex.X, TargetGlobalIndex.Y, TargetGlobalIndex.Z);

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
						else if (CurrentBatchMaterial == INDEX_NONE)
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
				ThreadResult->SectionData[BatchData.Key.Z].GetVoxelFaceData(DirectionIndex, I).FaceDataList.Add(BatchData.Value);
				ThreadResult->SectionData[BatchData.Key.Z].TriangleCount += 2;
			}
		}
	}

	UpdateBounds();
	MarkRenderStateDirty();
	RebuildPhysicsData();
}

void ULFPVoxelRendererComponent::OnChuckUpdate(const FLFPChuckUpdateAction& Data)
{
	UpdateAttribute();

	UpdateMesh();
}

FColor ULFPVoxelRendererComponent::GetVoxelAttribute(const FLFPVoxelPaletteData& VoxelPalette) const
{
	return FColor(0);
}

int32 ULFPVoxelRendererComponent::GetVoxelMaterialIndex(const FLFPVoxelPaletteData& VoxelPalette) const
{
	return VoxelPalette.VoxelName == FName("Dirt") ? 0 : INDEX_NONE;
}

TSharedPtr<FLFPVoxelRendererThreadResult>& ULFPVoxelRendererComponent::GetThreadResult()
{
	return ThreadResult;
}

FPrimitiveSceneProxy* ULFPVoxelRendererComponent::CreateSceneProxy()
{
	return ThreadResult.IsValid() && ThreadResult->SectionData.Num() > 0 ? new FLFPVoxelRendererSceneProxy(this) : nullptr;
}

FBoxSphereBounds ULFPVoxelRendererComponent::CalcBounds(const FTransform& LocalToWorld) const
{
	FBox VoxelBox;

	if (IsValid(VoxelContainer) && WorkThread.IsCompleted() && ThreadResult.IsValid())
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

void ULFPVoxelRendererComponent::GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials) const
{
	OutMaterials.Append(MaterialList);
}

//UMaterialInterface* ULFPVoxelRendererComponent::GetMaterialFromCollisionFaceIndex(int32 FaceIndex, int32& SectionIndex) const
//{
//	UMaterialInterface* Result = nullptr;
//	SectionIndex = 0;
//
//	if (RenderData && FaceIndex >= 0)
//	{
//		// Look for section that corresponds to the supplied face
//		int32 TotalFaceCount = 0;
//
//		for (int32 SectionIdx = 0; SectionIdx < RenderData->Sections.Num(); SectionIdx++)
//		{
//			const FLFPBaseVoxelMeshSectionData& Section = RenderData->Sections[SectionIdx];
//
//			TotalFaceCount += Section.TriangleCount;
//
//			if (FaceIndex < TotalFaceCount)
//			{
//				// Get the current material for it, from this component
//				Result = GetMaterial(SectionIdx);
//
//				SectionIndex = SectionIdx;
//
//				break;
//			}
//		}
//	}
//
//	return Result;
//}

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
	CollisionData->bFastCook = false;

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
	NewBodySetup->CollisionTraceFlag = ECollisionTraceFlag::CTF_UseComplexAsSimple;

	return NewBodySetup;
}

void ULFPVoxelRendererComponent::RebuildPhysicsData()
{
	if (BodySetup->CurrentCookHelper)
	{
		Status.bIsBodyInvalid = true;
	}
	else
	{
		BodySetup->CreatePhysicsMeshesAsync(FOnAsyncPhysicsCookFinished::CreateUObject(this, &ULFPVoxelRendererComponent::FinishPhysicsAsyncCook, BodySetup.Get()));
	}
}

void ULFPVoxelRendererComponent::FinishPhysicsAsyncCook(bool bSuccess, UBodySetup* FinishedBodySetup)
{
	if (bSuccess)
	{
		RecreatePhysicsState();
	}

	if (Status.bIsBodyInvalid)
	{
		Status.bIsBodyInvalid = false;

		RebuildPhysicsData();
	}
}
