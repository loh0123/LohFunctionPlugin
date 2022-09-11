// MIT License
// 
// Copyright(c) 2022 loh0123
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright noticeand this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#include "Helper/LFPTickManager.h"
#include "TimerManager.h"
#include "Engine/World.h"

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

	if (TickActorList.Num() == 0 || CurrentCallCount != 0) return;

	if (CurrentTickDelay <= 0.0f)
		SendTick();
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
	for (int32 Index = 0; Index < TickPerCall; Index++)
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
				CurrentArrayIndex = (CurrentArrayIndex + 1) % TickActorList.Num();
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

