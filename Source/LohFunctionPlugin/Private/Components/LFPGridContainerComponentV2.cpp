// Copyright by Loh Zhi Kang

#include "Components/LFPGridContainerComponentV2.h"

DEFINE_LOG_CATEGORY(LFPGridContainerComponentV2);
DEFINE_LOG_CATEGORY(LFPGridChuckDataV2);

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

	Setting.InitSetting();

	ReinitializeRegion();
}


// Called every frame
void ULFPGridContainerComponentV2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (UpdateChuckData() == false) return;

	SetComponentTickEnabled(false);
}

bool ULFPGridContainerComponentV2::UpdateChuckData()
{
	if (ChuckUpdateStateList.IsEmpty()) return true;

	if (ContainerThreadLock.TryWriteLock() == false) return false;

	for (const auto& ChuckUpdate : ChuckUpdateStateList)
	{
		/** Check Is Valid */
		if (IsRegionPositionValid(ChuckUpdate.Key.X) == false) 
		{
			UE_LOG(LFPGridContainerComponentV2, Warning, TEXT("UpdateChuckData Region Index Invalid %s"), *ChuckUpdate.Key.ToString());

			continue;
		}

		/** Region Initialization */
		if (IsRegionInitialized(ChuckUpdate.Key.X) == false)
		{
			UE_LOG(LFPGridContainerComponentV2, Log, TEXT("ULFPGridContainerComponentV2 : UpdateChuckData Allocating Region %d"), ChuckUpdate.Key.X);

			RegionDataList[ChuckUpdate.Key.X].InitRegionData(Setting.GetChuckLength());

			OnGridContainerRegionInitialized.Broadcast(ChuckUpdate.Key.X);
		}

		/** Check Is Valid */
		if (IsChuckPositionValid(ChuckUpdate.Key.X, ChuckUpdate.Key.Y) == false)
		{
			UE_LOG(LFPGridContainerComponentV2, Warning, TEXT("UpdateChuckData Chuck Index Invalid %s"), *ChuckUpdate.Key.ToString());

			continue;
		}

		/** Chuck Initialization */
		if (IsChuckInitialized(ChuckUpdate.Key.X, ChuckUpdate.Key.Y) == false)
		{
			UE_LOG(LFPGridContainerComponentV2, Log, TEXT("ULFPGridContainerComponentV2 : UpdateChuckData Allocating Chuck %d On Region %d"), ChuckUpdate.Key.X, ChuckUpdate.Key.Y);

			RegionDataList[ChuckUpdate.Key.X].GetChuckChecked(ChuckUpdate.Key.Y).InitChuckData(Setting.GetPaletteLength(), ChuckUpdate.Value.InitializeTag);

			OnGridContainerChuckInitialized.Broadcast(ChuckUpdate.Key.X, ChuckUpdate.Key.Y);
		}

		for (const auto& TagChangeData : ChuckUpdate.Value.TagChangeList)
		{
			RegionDataList[ChuckUpdate.Key.X].GetChuck(ChuckUpdate.Key.Y)->SetIndexTag(TagChangeData.Key, TagChangeData.Value);
		}

		for (const auto& DataChange : ChuckUpdate.Value.DataChangeList)
		{
			for (const auto& MetaChangeData : DataChange.Value.GetItemList())
			{
				RegionDataList[ChuckUpdate.Key.X].GetChuck(ChuckUpdate.Key.Y)->SetIndexMeta(DataChange.Key, MetaChangeData);
			}
		}

		OnGridContainerChuckUpdated.Broadcast(ChuckUpdate.Key.X, ChuckUpdate.Key.Y);
	}

	ContainerThreadLock.WriteUnlock();

	return true;
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

void ULFPGridContainerComponentV2::ReinitializeRegion()
{
	if (Setting.IsValid() == false)
	{
		UE_LOG(LFPGridContainerComponentV2, Warning, TEXT("Setting Is Invalid"));

		return;
	}

	ContainerThreadLock.WriteLock();

	RegionDataList.SetNum(Setting.GetRegionLength());

	ContainerThreadLock.WriteUnlock();
}

bool ULFPGridContainerComponentV2::InitializeData(const int32 RegionIndex, const int32 ChuckIndex, const FGameplayTag StartTag, const bool bOverride)
{
	if (IsRegionPositionValid(RegionIndex) == false)
	{
		return false;
	}

	auto& ChuckUpdateData = ChuckUpdateStateList.FindOrAdd(FIntPoint(RegionIndex, ChuckIndex));

	ChuckUpdateData.SetInitializeTag(StartTag);

	SetComponentTickEnabled(true);

	//if (IsRegionInitialized(RegionIndex) == false)
	//{
	//	UE_LOG(LFPGridContainerComponentV2, Log, TEXT("ULFPGridContainerComponentV2 : InitializeData Allocating Region %d"), RegionIndex);

	//	RegionDataList[RegionIndex].InitRegionData(Setting.GetChuckLength());

	//	OnGridContainerRegionInitialized.Broadcast(RegionIndex);
	//}

	//if (IsChuckPositionValid(RegionIndex, ChuckIndex) == false)
	//{
	//	return false;
	//}

	//if (IsChuckInitialized(RegionIndex, ChuckIndex) == false || bOverride)
	//{
	//	UE_LOG(LFPGridContainerComponentV2, Log, TEXT("ULFPGridContainerComponentV2 : InitializeData Allocating Chuck %d On Region %d"), ChuckIndex, RegionIndex);

	//	RegionDataList[RegionIndex].GetChuckChecked(ChuckIndex).InitChuckData(Setting.GetPaletteLength(), StartTag);

	//	OnGridContainerChuckInitialized.Broadcast(RegionIndex, ChuckIndex);

	//	return true;
	//}

	//return false;

	return true;
}

bool ULFPGridContainerComponentV2::SetPaletteTag(const int32 RegionIndex, const int32 ChuckIndex, const int32 PaletteIndex, const FGameplayTag Tag)
{
	if (IsPalettePositionValid(RegionIndex, ChuckIndex, PaletteIndex) == false)
	{
		return false;
	}

	auto& ChuckUpdateData = ChuckUpdateStateList.FindOrAdd(FIntPoint(RegionIndex, ChuckIndex));

	ChuckUpdateData.AddTagChange(PaletteIndex, Tag);

	SetComponentTickEnabled(true);

	return true;
}

bool ULFPGridContainerComponentV2::SetPaletteTagList(const int32 RegionIndex, const int32 ChuckIndex, const TArray<int32>& PaletteIndexList, const FGameplayTag Tag)
{
	if (IsChuckInitialized(RegionIndex, ChuckIndex) == false)
	{
		return false;
	}

	bool bAllValid = true;

	for (const int32& PalleteIndex : PaletteIndexList)
	{
		if (SetPaletteTag(RegionIndex, ChuckIndex, PalleteIndex, Tag) == false)
		{
			bAllValid = false;
		}
	}

	if (bAllValid == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPGridContainerComponentV2 : %s : SetPaletteTagList Has Invalid Index "), *GetOwner()->GetName());
	}

	return bAllValid;
}

bool ULFPGridContainerComponentV2::SetPaletteData(const int32 RegionIndex, const int32 ChuckIndex, const int32 PaletteIndex, const FLFPCompactMetaData& Data)
{
	if (IsPalettePositionValid(RegionIndex, ChuckIndex, PaletteIndex) == false)
	{
		return false;
	}

	auto& ChuckUpdateData = ChuckUpdateStateList.FindOrAdd(FIntPoint(RegionIndex, ChuckIndex));

	ChuckUpdateData.AddDataChange(PaletteIndex, Data);

	SetComponentTickEnabled(true);

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
