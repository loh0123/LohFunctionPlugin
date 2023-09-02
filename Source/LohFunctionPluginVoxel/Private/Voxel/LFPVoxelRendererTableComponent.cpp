// Fill out your copyright notice in the Description page of Project Settings.


#include "Voxel/LFPVoxelRendererTableComponent.h"

void ULFPVoxelRendererTableComponent::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(VoxelTypeTable))
	{
		if (VoxelTypeTable->GetRowStruct()->IsChildOf(FLFPVoxelTypeTable::StaticStruct()) == false)
		{
			VoxelTypeTable = nullptr;

			UE_LOG(LFPVoxelRendererComponent, Warning, TEXT("VoxelTypeTable Is Not Using Struct ( FLFPVoxelTypeTable )"));
		}
	}

	if (IsValid(VoxelAttributeTable))
	{
		if (VoxelAttributeTable->GetRowStruct()->IsChildOf(FLFPVoxelAttributeTable::StaticStruct()) == false)
		{
			VoxelAttributeTable = nullptr;

			UE_LOG(LFPVoxelRendererComponent, Warning, TEXT("VoxelAttributeTable Is Not Using Struct ( FLFPVoxelAttributeTable )"));
		}
	}
}

FColor ULFPVoxelRendererTableComponent::GetVoxelAttribute(const FLFPGridPaletteData& VoxelPalette, const TMap<FName, uint8>& TagDataList) const
{
	if (IsValid(VoxelTypeTable) == false) return FColor(0);

	const auto VoxelType = reinterpret_cast<FLFPVoxelTypeTable*>(VoxelTypeTable->FindRowUnchecked(VoxelPalette.Name));

	FColor VoxelColor = VoxelType != nullptr ? VoxelType->VoxelDefaultColor : GetGenerationSetting().EmptyVoxelNameColor;

	if (IsValid(VoxelAttributeTable) == false) return VoxelColor;

	for (int32 TagIndex = 0; TagIndex < VoxelPalette.TagList.Num(); TagIndex++)
	{
		const auto VoxelAttribute = reinterpret_cast<FLFPVoxelAttributeTable*>(VoxelAttributeTable->FindRowUnchecked(VoxelPalette.TagList[TagIndex]));

		if (VoxelAttribute == nullptr)
		{
			continue;
		}

		FColor CurrentColor = VoxelAttribute->VoxelColor;

		const uint8* TagData = TagDataList.Find(VoxelPalette.TagList[TagIndex]);

		if (TagData != nullptr)
		{
			FColor CurrentData = VoxelAttribute->VoxelData;

			CurrentData.R *= *TagData;
			CurrentData.G *= *TagData;
			CurrentData.B *= *TagData;
			CurrentData.A *= *TagData;

			CurrentColor += CurrentData;
		}

		if (VoxelAttribute != nullptr)
		{
			switch (VoxelAttribute->Operation)
			{
			case ELFPVoxelAttributeOperation::Addition: VoxelColor += CurrentColor; break;
			case ELFPVoxelAttributeOperation::Override: VoxelColor = CurrentColor; break;
			case ELFPVoxelAttributeOperation::Blend:
			{
				VoxelColor += CurrentColor;
				VoxelColor.R *= 0.5f;
				VoxelColor.G *= 0.5f;
				VoxelColor.B *= 0.5f;
				VoxelColor.A *= 0.5f;
			}
			break;
			case ELFPVoxelAttributeOperation::Min:
			{
				VoxelColor.R = FMath::Min(CurrentColor.R, VoxelColor.R);
				VoxelColor.G = FMath::Min(CurrentColor.G, VoxelColor.G);
				VoxelColor.B = FMath::Min(CurrentColor.B, VoxelColor.B);
				VoxelColor.A = FMath::Min(CurrentColor.A, VoxelColor.A);
			}
			break;
			case ELFPVoxelAttributeOperation::Max:
			{
				VoxelColor.R = FMath::Max(CurrentColor.R, VoxelColor.R);
				VoxelColor.G = FMath::Max(CurrentColor.G, VoxelColor.G);
				VoxelColor.B = FMath::Max(CurrentColor.B, VoxelColor.B);
				VoxelColor.A = FMath::Max(CurrentColor.A, VoxelColor.A);
			}
			break;
			}
		}
	}

	return VoxelColor;
}

int32 ULFPVoxelRendererTableComponent::GetVoxelMaterialIndex(const FLFPGridPaletteData& VoxelPalette) const
{
	if (IsValid(VoxelTypeTable) == false) return INDEX_NONE;

	const auto VoxelType = reinterpret_cast<FLFPVoxelTypeTable*>(VoxelTypeTable->FindRowUnchecked(VoxelPalette.Name));

	return VoxelType != nullptr ? VoxelType->VoxelMaterial : INDEX_NONE;
}

bool ULFPVoxelRendererTableComponent::CanUpdateMesh(const FLFPChuckUpdateAction& Data) const
{
	if (IsValid(VoxelTypeTable))
	{
		for (const auto& ChangeData : Data.GridChangeNameList)
		{
			const auto VoxelTypeOld = reinterpret_cast<FLFPVoxelTypeTable*>(VoxelTypeTable->FindRowUnchecked(ChangeData.FromName));
			const auto VoxelTypeNew = reinterpret_cast<FLFPVoxelTypeTable*>(VoxelTypeTable->FindRowUnchecked(ChangeData.ToName));

			const int32 MaterialIDOld = VoxelTypeOld != nullptr ? VoxelTypeOld->VoxelMaterial : INDEX_NONE;
			const int32 MaterialIDNew = VoxelTypeNew != nullptr ? VoxelTypeNew->VoxelMaterial : INDEX_NONE;

			if (MaterialIDOld != MaterialIDNew) return true;
		}

		return false;
	}
	else
	{
		return Super::CanUpdateMesh(Data);
	}
}
