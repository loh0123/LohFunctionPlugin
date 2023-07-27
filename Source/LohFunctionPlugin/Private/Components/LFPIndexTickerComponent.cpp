// Copyright by Loh Zhi Kang


#include "Components/LFPIndexTickerComponent.h"

// Sets default values for this component's properties
ULFPIndexTickerComponent::ULFPIndexTickerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	// ...
}


// Called when the game starts
void ULFPIndexTickerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULFPIndexTickerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CallTick() == false && bAllowAutoTick) SetComponentTickEnabled(false);
}

bool ULFPIndexTickerComponent::CallTick()
{
	TArray<FIntPoint> RemoveIndexList;

	for (auto& CurrentGroupData : TickList)
	{
		CurrentGroupData.Value.Tick(OnTick, OnIndexRemove, CurrentGroupData.Key, this, MaxTickerRunPerGroup);

		if (CurrentGroupData.Value.CanRemove()) RemoveIndexList.Add(CurrentGroupData.Key);
	}

	for (auto& RemoveIndex : RemoveIndexList)
	{
		OnGroupRemove.Broadcast(RemoveIndex);

		TickList.Remove(RemoveIndex);
	}

	return TickList.IsEmpty() == false;
}

void ULFPIndexTickerComponent::AddTickIndex(const FLFPIndexTickData& TickData, const int32 TickIndex, const FIntPoint GroupIndex)
{
	if (TickData.Amount == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : TickData Amount Can't Be Zero"), *GetName());

		return;
	}

	const bool HasGroup = TickList.Contains(GroupIndex);

	auto& GroupData = TickList.FindOrAdd(GroupIndex);

	if (HasGroup == false) OnGroupAdded.Broadcast(GroupIndex);

	if (GroupData.MemberList.Contains(TickIndex))
	{
		GroupData.MemberList.FindChecked(TickIndex) = TickData;

		OnIndexUpdated.Broadcast(TickIndex, TickData.TickName, GroupIndex);
	}
	else
	{
		GroupData.MemberList.Add(TickIndex, TickData);

		OnIndexAdded.Broadcast(TickIndex, TickData.TickName, GroupIndex);

		TickData.TryStartTicker(GroupIndex, this, TickIndex);
	}

	if (bAllowAutoTick) SetComponentTickEnabled(true);
}

bool ULFPIndexTickerComponent::RemoveTickIndex(const int32 TickIndex, const FIntPoint GroupIndex)
{
	auto GroupData = TickList.Find(GroupIndex);

	if (GroupData == nullptr || GroupData->MemberList.Contains(TickIndex) == false) return false;

	auto& Member = GroupData->MemberList.FindChecked(TickIndex);

	Member.TryEndTicker(GroupIndex, this, TickIndex);

	GroupData->MemberList.Remove(TickIndex);

	return true;
}

void ULFPIndexTickerComponent::LoadGroupList(const TMap<FIntPoint, FLFPIndexTickGroupData>& SaveVariable, const TArray<FIntPoint>& GroupIndexList)
{
	for (const FIntPoint& GroupIndex : GroupIndexList)
	{
		if (SaveVariable.Contains(GroupIndex) == false) continue;

		TickList.Add(GroupIndex, SaveVariable.FindChecked(GroupIndex));
	}

	return;
}

void ULFPIndexTickerComponent::SaveGroupList(TMap<FIntPoint, FLFPIndexTickGroupData>& SaveVariable, const TArray<FIntPoint>& GroupIndexList)
{
	for (const FIntPoint& GroupIndex : GroupIndexList)
	{
		if (TickList.Contains(GroupIndex))
		{
			SaveVariable.Add(GroupIndex, SaveVariable.FindChecked(GroupIndex));
		}
		else
		{
			SaveVariable.Remove(GroupIndex);
		}
	}

	return;
}

