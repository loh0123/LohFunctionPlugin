// Copyright by Loh Zhi Kang


#include "Helper/LFPTickManager.h"
#include "TimerManager.h"

// Sets default values for this component's properties
ULFPTickManager::ULFPTickManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULFPTickManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULFPTickManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TickActorList.Num() == 0) return;

	if (CurrentTickDelay <= 0.0f)
	{
		SendTick();
	}
	else
		CurrentTickDelay -= DeltaTime;
}

int32 ULFPTickManager::SendTick()
{
	if (!IsActive() || TickActorList.Num() == 0 || !GetOwner()) return -1;

	CurrentCallCount = TickCount;

	CurrentTickDelay = TickDelay;

	SendTickInternal();

	return (CurrentArrayIndex + TickCount) % TickActorList.Num();
}

void ULFPTickManager::SendTickInternal()
{
	for (int32 Index = 0; Index < FMath::Min(TickPerCall, TickCount); Index++)
	{
		// Auto Remove Nullptr
		while (TickActorList.Num() != 0)
		{
			// Reset Index if Out Of Bounds
			CurrentArrayIndex = TickActorList.Num() <= CurrentArrayIndex ? 0 : CurrentArrayIndex;

			if (TickActorList[CurrentArrayIndex])
			{
				TickActorList[CurrentArrayIndex]->CallFunctionByNameWithArguments(*CallFunctionName, OutputDeviceNull, nullptr, true);
				// (Add One To Index) and (Check Is Out Of Bound)
				if (++CurrentArrayIndex >= TickActorList.Num()) CurrentArrayIndex = 0;
				break; // Jump Back To For Loop
			}

			TickActorList.RemoveAtSwap(CurrentArrayIndex, 1, false); // Remove Null Pointer
		}

		// Break If On Index End
		if (--CurrentCallCount == 0 || TickActorList.Num() == 0) break;
	}

	// Set To Run Next Tick If Needed
	if (CurrentCallCount != 0) GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ULFPTickManager::SendTickInternal);

	// Shrink The Array For Memory Saving
	TickActorList.Shrink();

	return;
}

bool ULFPTickManager::AddTickActor(AActor* Actor, const bool IsRandom, const bool CheckDuplication)
{
	if (!Actor) return false;

	if (CheckDuplication && TickActorList.Contains(Actor)) return true;

	TickActorList.EmplaceAt(IsRandom ? Seed.RandHelper(TickActorList.Num()) : TickActorList.Num(), Actor);

	return true;
}

bool ULFPTickManager::RemoveTickActor(AActor* Actor, const bool RemoveAll)
{
	if (!Actor) return false;

	if (RemoveAll)
		TickActorList.RemoveSwap(Actor);
	else
		TickActorList.RemoveSingleSwap(Actor);

	return true;
}

