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

	TickList.RemoveAllSwap([&](FLFPIndexTickData& CurrentTickIndex)
		{
			if (CurrentTickIndex.CanTick())
			{
				OnTick.Broadcast(CurrentTickIndex.Index);

				return true;
			}

			CurrentTickIndex.DecreaseInterval();

			return false;
		});
}

void ULFPIndexTickManager::AddTickIndex(const FLFPIndexTickData& TickData)
{
	const int32 Index = TickList.Find(TickData);

	if (Index != INDEX_NONE)
	{
		TickList[Index].Interval = TickData.Interval;
	}
	else
	{
		TickList.Add(TickData);
	}

	SetComponentTickEnabled(true);
}

bool ULFPIndexTickManager::RemoveTickIndex(const int32 TickIndex)
{
	const bool bRemoved = TickList.RemoveSingleSwap(FLFPIndexTickData(TickIndex)) == 1;

	if (TickList.IsEmpty()) SetComponentTickEnabled(false);

	return bRemoved;
}
