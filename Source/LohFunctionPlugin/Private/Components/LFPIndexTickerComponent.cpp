// Copyright by Loh Zhi Kang


#include "Components/LFPIndexTickerComponent.h"

// Sets default values for this component's properties
ULFPIndexTickerComponent::ULFPIndexTickerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
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

	if (bAllowAutoRandomTick || bAllowAutoScheduledTick)
	{
		CallTick(bAllowAutoRandomTick, bAllowAutoScheduledTick);
	}
}

void ULFPIndexTickerComponent::CallTick(const bool bRandomTick, const bool bScheduledTick)
{
	for (auto& CurrentGroupData : TickList)
	{
		if (bRandomTick)
		{
			for (int32 TickCount = 0; TickCount < RandomTickCount; TickCount++)
			{
				const int32 CurrentRandomTickIndex = GetCacheRandomTickIndex(CurrentGroupData.Value);

				if (CurrentRandomTickIndex == INDEX_NONE)
				{
					break;
				}

				auto& TickData = CurrentGroupData.Value.RandomTickList[CurrentRandomTickIndex];

				if (TickData.DecreaseDelay())
				{
					if (TickData.TryRunTicker(CurrentGroupData.Key, this, CurrentRandomTickIndex, false) == false)
					{
						OnRandomTick.Broadcast(CurrentRandomTickIndex, CurrentGroupData.Key);
					}
					else
					{
						TickData.Ticker = nullptr;
					}
				}
			}
		}

		if (bScheduledTick)
		{
			TArray<int32> RemoveTickIndexList;

			for (auto& TickData : CurrentGroupData.Value.ScheduledTickList)
			{
				if (TickData.Value.DecreaseDelay())
				{
					if (TickData.Value.TryRunTicker(CurrentGroupData.Key, this, TickData.Key, true) == false)
					{
						OnScheduledTick.Broadcast(TickData.Key, CurrentGroupData.Key);
					}
					else
					{
						OnScheduledRemove.Broadcast(TickData.Key, CurrentGroupData.Key);

						RemoveTickIndexList.Add(TickData.Key);
					}
				}
			}

			for (const int32 TickIndex : RemoveTickIndexList)
			{
				CurrentGroupData.Value.ScheduledTickList.Remove(TickIndex);
			}
		}
	}

	return;
}

void ULFPIndexTickerComponent::SetRandomTickData(const FLFPIndexTickData& TickData, const int32 TickIndex, const FIntPoint GroupIndex)
{
	auto& GroupData = TickList.FindOrAdd(GroupIndex, FLFPIndexTickGroupData(RandomTickMaxIndex, GroupIndex.Y));

	GroupData.ScheduledTickList.Add(TickIndex, TickData);

	OnRandomTickUpdated.Broadcast(TickIndex, GroupIndex);
}

void ULFPIndexTickerComponent::ScheduledTickIndex(const FLFPIndexTickData& TickData, const int32 TickIndex, const FIntPoint GroupIndex)
{
	if (TickIndex < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LFPIndexTickerComponent : AddTickIndex TickIndex Invalid"));

		return;
	}

	auto& GroupData = TickList.FindOrAdd(GroupIndex, FLFPIndexTickGroupData(RandomTickMaxIndex, GroupIndex.Y));

	GroupData.ScheduledTickList.Add(TickIndex, TickData);

	OnScheduledAdded.Broadcast(TickIndex, GroupIndex);
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

void ULFPIndexTickerComponent::SaveGroupList(UPARAM(ref) TMap<FIntPoint, FLFPIndexTickGroupData>& SaveVariable, const TArray<FIntPoint>& GroupIndexList, const bool bUnload)
{
	TArray<FIntPoint> RemoveIndexList;

	for (const FIntPoint& GroupIndex : GroupIndexList)
	{
		if (TickList.Contains(GroupIndex))
		{
			SaveVariable.Add(GroupIndex, TickList.FindChecked(GroupIndex));

			if (bUnload) RemoveIndexList.Add(GroupIndex);
		}
	}

	for (const FIntPoint& RemoveGroup : RemoveIndexList)
	{
		TickList.Remove(RemoveGroup);
	}

	return;
}

int32 ULFPIndexTickerComponent::GetCacheRandomTickIndex(FLFPIndexTickGroupData& Data)
{
	if (RandomTickMaxIndex <= 0)
	{
		return INDEX_NONE;
	}

	if (CacheRandomTickList.Num() != RandomTickMaxIndex)
	{
		CacheRandomTickList.SetNum(RandomTickMaxIndex);

		for (int32 Index = 0; Index < RandomTickMaxIndex; Index++)
		{
			CacheRandomTickList[Index] = Index;
		}

		FRandomStream RandomSeed = FRandomStream(RandomTickSeed);

		for (int32 Index = 0; Index < RandomTickMaxIndex; Index++)
		{
			CacheRandomTickList.Swap(Index, RandomSeed.RandHelper(RandomTickMaxIndex - 1));
		}
	}

	if (CacheRandomTickList.IsValidIndex(Data.RandomTickIndex) == false)
	{
		Data.RandomTickIndex = 0;
	}
	
	return CacheRandomTickList[Data.RandomTickIndex++];
}

ULFPTickerObject* ULFPIndexTickerComponent::GetRandomTicker(const FIntPoint GroupIndex, const int32 TickIndex) const
{
	return nullptr;
}

