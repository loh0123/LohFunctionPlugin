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

	bool CheckList[27] = {};

	FLFHashBoxGridKey HashKey = FLFHashBoxGridKey();

	HashKey.ObjectTag = GetGridTag(GridPosition);

	if (GetGridOccupation(GridPosition, FIntVector(0), HashKey.ObjectTag))
	{
		for (int32 Index = 0; Index < 27; Index++)
		{
			const FIntVector LocalCheckPostion = ULFPGridLibrary::ToGridLocation(Index, FIntVector(3)) - FIntVector(1);

			CheckList[Index] = GetGridOccupation(GridPosition + LocalCheckPostion, LocalCheckPostion, HashKey.ObjectTag);
		}

		/* Edge Check */
		for (int32 Index = 0; Index < 27; Index++)
		{
			const FIntVector LocalCheckPostion = ULFPGridLibrary::ToGridLocation(Index, FIntVector(3)) - FIntVector(1);

			if (CheckList[Index] == false)
			{
				continue;
			}

			int32 DifferenceIndex = 0;

			for (int32 VectorIndex = 0; VectorIndex < 3; VectorIndex++)
			{
				if (LocalCheckPostion[VectorIndex] != 0)
				{
					DifferenceIndex++;
				}
			}

			if (DifferenceIndex > 1)
			{
				for (int32 VectorIndex = 0; VectorIndex < 3; VectorIndex++)
				{
					if (LocalCheckPostion[VectorIndex] != 0)
					{
						FIntVector CopyPos = LocalCheckPostion;

						CopyPos[VectorIndex] = 0;

						if (CheckList[ULFPGridLibrary::ToGridIndex(CopyPos + FIntVector(1), FIntVector(3))] == false)
						{
							CheckList[Index] = false;

							break;
						}
					}
				}
			}
		}
	}

	for (int32 HashPoint = 0; HashPoint < 8; HashPoint++)
	{
		const FIntVector LocalHashPoint = ULFPGridLibrary::ToGridLocation(HashPoint, FIntVector(2));

		for (int32 Index = 0; Index < 8; Index++)
		{
			const FIntVector LocalCheckPostion = ULFPGridLibrary::ToGridLocation(Index, FIntVector(2));

			HashKey.SetConnectOccupation(Index, CheckList[ULFPGridLibrary::ToGridIndex(LocalHashPoint  + LocalCheckPostion, FIntVector(3))]);
		}

		OnHashBoxGridPointUpdate.Broadcast(HashKey);
	}
}

