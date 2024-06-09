#include "Components/LFPHashBoxGridComponent.h"
#include <Math/LFPGridLibrary.h>

// Sets default values for this component's properties
ULFPHashBoxGridComponent::ULFPHashBoxGridComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULFPHashBoxGridComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULFPHashBoxGridComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULFPHashBoxGridComponent::SetGridSize(const FIntVector NewSize)
{
	GridSize = NewSize;
}

void ULFPHashBoxGridComponent::UpdateGridIndex(const int32 GridIndex)
{
	const FIntVector GridPosition = ULFPGridLibrary::ToGridLocation(GridIndex, GridSize);

	if (GridPosition == FIntVector(INDEX_NONE))
	{
		return;
	}

	const FIntVector LoopHashList[] =
	{
		FIntVector(0,0,0),
		FIntVector(1,0,0),
		FIntVector(0,1,0),
		FIntVector(1,1,0),
		FIntVector(0,0,1),
		FIntVector(1,0,1),
		FIntVector(0,1,1),
		FIntVector(1,1,1)
	};

	FLFHashBoxGridKey HashKey = FLFHashBoxGridKey();

	HashKey.ObjectTag = GetGridTag(GridPosition);

	for (const auto& HashPointData : HashPointMap)
	{
		for (int32 Index = 0; Index < 8; Index++)
		{
			HashKey.SetConnectOccupation(Index, GetGridOccupation(GridPosition + HashPointData.Value + LoopHashList[Index], HashPointData.Value + LoopHashList[Index], HashPointData.Key));
		}

		OnHashBoxGridPointUpdate.Broadcast(HashPointData.Key, HashKey);
	}
}

