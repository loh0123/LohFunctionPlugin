// Copyright by Loh Zhi Kang


#include "Helper/LFPRandomTickHelper.h"
#include <Runtime/Core/Public/Misc/OutputDeviceNull.h>

// Sets default values for this component's properties
ULFPRandomTickHelper::ULFPRandomTickHelper()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULFPRandomTickHelper::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULFPRandomTickHelper::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentTickDelay <= 0.0f)
	{
		CurrentTickDelay = TickDelay;

		for (int32 i = 0; i < TickCount; i++)
		{
			SendTick();
		}
	}
	else
		CurrentTickDelay -= DeltaTime;
}

AActor* ULFPRandomTickHelper::SendTick()
{
	if (TickActorList.Num() == 0) return nullptr;

	AActor* ReturnActor = nullptr;

	while (TickActorList.Num() != 0)
	{
		if (TickActorList[CurrentArrayIndex])
		{
			ReturnActor = TickActorList[CurrentArrayIndex];
			// (Add One To Index) and (Check Is Out Of Bound)
			if (++CurrentArrayIndex >= TickActorList.Num()) CurrentArrayIndex = 0;
			break; // Jump Back To For Loop
		}

		TickActorList.RemoveAtSwap(CurrentArrayIndex, 1, false); // Remove Null Pointer
	}

	TickActorList.Shrink();

	if (ReturnActor)
	{
		FOutputDeviceNull OutputDeviceNull;

		ReturnActor->CallFunctionByNameWithArguments(*CallFunctionName, OutputDeviceNull, nullptr, true);
	}

	return ReturnActor;
}

bool ULFPRandomTickHelper::AddTickActor(AActor* Actor, const bool CheckDuplication)
{
	if (!Actor) return false;

	if (CheckDuplication && TickActorList.Contains(Actor)) return true;

	TickActorList.EmplaceAt(Seed.RandHelper(TickActorList.Num()), Actor);

	return true;
}

bool ULFPRandomTickHelper::RemoveTickActor(AActor* Actor, const bool RemoveAll)
{
	if (!Actor) return false;

	if (RemoveAll)
		TickActorList.RemoveSwap(Actor);
	else
		TickActorList.RemoveSingleSwap(Actor);

	return true;
}

