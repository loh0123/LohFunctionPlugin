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
		CurrentGroupData.Value.Tick(OnTick, OnIndexRemove, CurrentGroupData.Key, this, RandomTickCount);

		if (CurrentGroupData.Value.CanRemove()) RemoveIndexList.Add(CurrentGroupData.Key);
	}

	for (auto& RemoveIndex : RemoveIndexList)
	{
		OnGroupRemove.Broadcast(RemoveIndex);

		TickList.Remove(RemoveIndex);
	}

	return TickList.IsEmpty() == false;
}

void ULFPIndexTickerComponent::AddTickIndex(const FLFPIndexTickData& TickData, const bool bIsRandomTick, const FIntPoint GroupIndex)
{
	if (TickData.IsDataValid() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("LFPIndexTickerComponent : AddTickIndex TickData Invalid"));

		return;
	}

	const bool HasGroup = TickList.Contains(GroupIndex);

	auto& GroupData = TickList.FindOrAdd(GroupIndex);

	if (HasGroup == false) OnGroupAdded.Broadcast(GroupIndex);

	if (bIsRandomTick)
	{
		GroupData.RandomTickList.Add(TickData);
	}
	else
	{
		GroupData.ScheduledTickList.Add(TickData);

		TickData.TryStartTicker(GroupIndex, this);
	}

	if (bAllowAutoTick) SetComponentTickEnabled(true);
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

