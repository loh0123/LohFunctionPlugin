// Copyright by Loh Zhi Kang


#include "Components/LFPIndexTickManager.h"

// Sets default values for this component's properties
ULFPIndexTickManager::ULFPIndexTickManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	// ...
}


// Called when the game starts
void ULFPIndexTickManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULFPIndexTickManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CallTick() == false && bAllowAutoTick) SetComponentTickEnabled(false);
}

bool ULFPIndexTickManager::CallTick()
{
	TArray<int32> RemoveIndexList;

	for (auto& CurrentGroupData : TickList)
	{
		CurrentGroupData.Value.Tick(OnTick, OnIndexRemove, CurrentGroupData.Key);

		if (CurrentGroupData.Value.CanRemove()) RemoveIndexList.Add(CurrentGroupData.Key);
	}

	for (auto& RemoveIndex : RemoveIndexList)
	{
		OnGroupRemove.Broadcast(RemoveIndex);

		TickList.Remove(RemoveIndex);
	}

	return TickList.IsEmpty() == false;
}

void ULFPIndexTickManager::AddTickIndex(const FLFPIndexTickData& TickData, const int32 GroupIndex)
{
	if (TickData.Amount == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : TickData Amount Can't Be Zero"), *GetName());

		return;
	}

	const bool HasGroup = TickList.Contains(GroupIndex);

	auto GroupData = TickList.FindOrAdd(GroupIndex);

	if (HasGroup == false) OnGroupAdded.Broadcast(GroupIndex);

	const int32 Index = GroupData.Members.Find(TickData);

	if (Index != INDEX_NONE)
	{
		GroupData.Members[Index] = TickData;

		OnIndexUpdated.Broadcast(TickData.Index, GroupIndex);
	}
	else
	{
		GroupData.Members.Add(TickData);

		OnIndexAdded.Broadcast(TickData.Index, GroupIndex);
	}

	if (bAllowAutoTick) SetComponentTickEnabled(true);
}

bool ULFPIndexTickManager::RemoveTickIndex(const int32 TickIndex, const int32 GroupIndex)
{
	auto GroupData = TickList.Find(GroupIndex);

	if (GroupData == nullptr) return false;

	const bool bRemoved = GroupData->Members.RemoveSingleSwap(FLFPIndexTickData(TickIndex)) == 1;

	return bRemoved;
}

bool ULFPIndexTickManager::LoadGroup(const TMap<int32, FLFPIndexTickGroupData>& SaveVariable, const int32 GroupIndex)
{
	if (SaveVariable.Contains(GroupIndex) == false) return false;

	TickList.Add(GroupIndex, SaveVariable.FindChecked(GroupIndex));

	return true;
}

bool ULFPIndexTickManager::SaveGroup(TMap<int32, FLFPIndexTickGroupData>& SaveVariable, const int32 GroupIndex)
{
	if (TickList.Contains(GroupIndex) == false && SaveVariable.Contains(GroupIndex) == false) return false;

	if (TickList.Contains(GroupIndex))
	{
		SaveVariable.Add(GroupIndex, SaveVariable.FindChecked(GroupIndex));
	}
	else
	{
		SaveVariable.Remove(GroupIndex);
	}

	return true;
}

