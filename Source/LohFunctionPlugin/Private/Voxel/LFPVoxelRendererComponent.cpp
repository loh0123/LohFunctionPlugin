// Copyright by Loh Zhi Kang


#include "Voxel/LFPVoxelRendererComponent.h"
#include "Render/LFPRenderLibrary.h"
#include "Math/LFPGridLibrary.h"

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
}


// Called every frame
void ULFPVoxelRendererComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (Status.bIsVoxelAttributeDirty)
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

				const FLFPVoxelPaletteData VoxelPalette = VoxelContainer->GetVoxelPalette(VoxelGridIndex.X, VoxelGridIndex.Y, VoxelGridIndex.Z);

				AttributeList[Index] = GetVoxelAttribute(VoxelPalette);
			}
		);

		if (IsValid(AttributesTexture)) ULFPRenderLibrary::UpdateTexture2D(AttributesTexture, AttributeList);
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

		if (VoxelContainer->IsChuckInitialized(NewRegionIndex, NewChuckIndex) == false)
		{
			VoxelContainer->InitializeVoxelChuck(NewRegionIndex, NewChuckIndex);
		}

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

void ULFPVoxelRendererComponent::SetMaterialList(const TArray<UMaterialInterface*>& Material)
{
	if (Material.IsEmpty() == false)
	{
		for (int k = 0; k < Material.Num(); ++k)
		{
			SetMaterial(k, Material[k]);
		}

		UpdateMesh();
		UpdateAttribute();
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

void ULFPVoxelRendererComponent::OnChuckUpdate(const FLFPChuckUpdateAction& Data)
{
	if (Data.bIsVoxelAttributeDirty)
	{
		UpdateAttribute();
	}

	if (Data.bIsVoxelMeshDirty)
	{
		UpdateMesh();
	}
}

FColor ULFPVoxelRendererComponent::GetVoxelAttribute(const FLFPVoxelPaletteData& VoxelPalette) const
{
	return FColor(0);
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
