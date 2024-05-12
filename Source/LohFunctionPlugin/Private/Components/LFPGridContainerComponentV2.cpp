// Copyright by Loh Zhi Kang

#include "Components/LFPGridContainerComponentV2.h"
#include "./Math/LFPGridLibrary.h"
#include "Serialization/ArchiveProxy.h"
#include "Serialization/NameAsStringProxyArchive.h"
#include "Serialization/ArchiveSaveCompressedProxy.h"
#include "Serialization/ArchiveLoadCompressedProxy.h"
#include "UObject/ReflectedTypeAccessors.h"


// Sets default values for this component's properties
ULFPGridContainerComponentV2::ULFPGridContainerComponentV2()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	// ...
}


// Called when the game starts
void ULFPGridContainerComponentV2::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ULFPGridContainerComponentV2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool ULFPGridContainerComponentV2::IsRegionPositionValid(const int32 RegionIndex) const
{
	return RegionDataList.IsValidIndex(RegionIndex);
}

bool ULFPGridContainerComponentV2::IsRegionInitialized(const int32 RegionIndex) const
{
	return IsRegionPositionValid(RegionIndex) && RegionDataList[RegionIndex].IsInitialized();
}

bool ULFPGridContainerComponentV2::IsChuckPositionValid(const int32 RegionIndex, const int32 ChuckIndex) const
{
	return IsRegionInitialized(RegionIndex) && RegionDataList[RegionIndex].IsChuckValidIndex(ChuckIndex);
}

bool ULFPGridContainerComponentV2::IsChuckInitialized(const int32 RegionIndex, const int32 ChuckIndex) const
{
	return IsChuckPositionValid(RegionIndex, ChuckIndex) && RegionDataList[RegionIndex].GetChuckChecked(ChuckIndex).IsInitialized();
}

bool ULFPGridContainerComponentV2::IsPalettePositionValid(const int32 RegionIndex, const int32 ChuckIndex, const int32 PaletteIndex) const
{
	return IsChuckInitialized(RegionIndex, ChuckIndex) && RegionDataList[RegionIndex].GetChuckChecked(ChuckIndex).IsValidIndex(PaletteIndex);
}

bool ULFPGridContainerComponentV2::SetPaletteTag(const int32 RegionIndex, const int32 ChuckIndex, const int32 PaletteIndex, const FGameplayTag Tag)
{
	if (IsPalettePositionValid(RegionIndex, ChuckIndex, PaletteIndex) == false)
	{
		return false;
	}

	RegionDataList[RegionIndex].GetChuckChecked(ChuckIndex).SetIndexTag(PaletteIndex, Tag);

	return true;
}

bool ULFPGridContainerComponentV2::SetPaletteData(const int32 RegionIndex, const int32 ChuckIndex, const int32 PaletteIndex, const FLFPCompactMetaData& Data)
{
	if (IsPalettePositionValid(RegionIndex, ChuckIndex, PaletteIndex) == false)
	{
		return false;
	}

	RegionDataList[RegionIndex].GetChuckChecked(ChuckIndex).SetIndexMeta(PaletteIndex, Data);

	return true;
}

FGameplayTag ULFPGridContainerComponentV2::GetPaletteTag(const int32 RegionIndex, const int32 ChuckIndex, const int32 PaletteIndex) const
{
	if (IsPalettePositionValid(RegionIndex, ChuckIndex, PaletteIndex) == false)
	{
		return FGameplayTag();
	}

	return RegionDataList[RegionIndex].GetChuckChecked(ChuckIndex).GetIndexTag(PaletteIndex);
}

FLFPCompactMetaData ULFPGridContainerComponentV2::GetPaletteData(const int32 RegionIndex, const int32 ChuckIndex, const int32 PaletteIndex) const
{
	if (IsPalettePositionValid(RegionIndex, ChuckIndex, PaletteIndex) == false)
	{
		return FGameplayTag();
	}

	const auto MetaData = RegionDataList[RegionIndex].GetChuckChecked(ChuckIndex).GetIndexMeta(PaletteIndex);

	return MetaData == nullptr ? FLFPCompactMetaData() : *MetaData;
}
