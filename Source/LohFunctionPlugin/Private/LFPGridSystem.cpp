// Copyright by Loh Zhi Kang


#include "LFPGridSystem.h"

// Sets default values for this component's properties
ULFPGridSystem::ULFPGridSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULFPGridSystem::BeginPlay()
{
	Super::BeginPlay();

	GridData.Reserve(GridSize.X * GridSize.Y * GridSize.Z);

	for (int32 i = 0; i < GridSize.X * GridSize.Y * GridSize.Z; i++)
	{
		GridData.Emplace(INDEX_NONE);
	}
	
	return;
}


// Called every frame
void ULFPGridSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SyncEvent();
}

bool ULFPGridSystem::IsLocationMarked(const FVector Location)
{
	FIntVector GridLoc = WordlLocationToGridLocation(Location);

	if (!IsLocationValid(GridLoc)) return false;

	SyncEvent();

	return GridData[GridLocationToIndex(GridLoc)] != INDEX_NONE;
}

bool ULFPGridSystem::IsLocationsMarked(const TArray<FVector>& Locations)
{
	SyncEvent();

	for (int32 i = 0; i < Locations.Num(); i++)
	{
		FIntVector GridLoc = WordlLocationToGridLocation(Locations[i]);

		if (!IsLocationValid(GridLoc)) continue;

		if (GridData[GridLocationToIndex(GridLoc)] != INDEX_NONE)
		{
			return true;
		}
	}

	return false;
}

bool ULFPGridSystem::MarkLocation(const FVector Location, const int32 Data)
{
	FIntVector GridLoc = WordlLocationToGridLocation(Location);

	if (!IsLocationValid(GridLoc)) return false;

	int32 Index = GridEvent.AddIndex.IndexOfByKey(GridLocationToIndex(GridLoc));

	if (Index == INDEX_NONE)
	{
		GridEvent.AddIndex.Emplace(GridLocationToIndex(GridLoc));
		GridEvent.AddData.Emplace(Data);
	}
	else
	{
		GridEvent.AddData[Index] = Data;
	}

	GridEvent.RemoveIndex.RemoveSingle(GridLocationToIndex(GridLoc));

	IsEventDirty = true;

	return true;
}

bool ULFPGridSystem::MarkLocations(const TArray<FVector>& Locations, const int32 Data)
{
	for (const FVector& Item : Locations)
	{
		MarkLocation(Item, Data);
	}

	return Locations.Num() > 0;
}

bool ULFPGridSystem::UnmarkLocation(const FVector Location)
{
	FIntVector GridLoc = WordlLocationToGridLocation(Location);

	if (!IsLocationValid(GridLoc)) return false;

	if (!GridEvent.RemoveIndex.Contains(GridLocationToIndex(GridLoc)))
	{
		GridEvent.RemoveIndex.Emplace(GridLocationToIndex(GridLoc));
	}

	int32 Index = GridEvent.AddIndex.IndexOfByKey(GridLocationToIndex(GridLoc));

	if (Index != INDEX_NONE)
	{
		GridEvent.AddIndex.RemoveAt(Index);
		GridEvent.AddData.RemoveAt(Index);
	}

	IsEventDirty = true;

	return true;
}

bool ULFPGridSystem::UnmarkLocations(const TArray<FVector>& Locations)
{
	for (const FVector& Item : Locations)
	{
		UnmarkLocation(Item);
	}

	return Locations.Num() > 0;
}

int32 ULFPGridSystem::GetLocationData(const FVector Location)
{
	FIntVector GridLoc = WordlLocationToGridLocation(Location);

	if (!IsLocationValid(GridLoc)) return INDEX_NONE;

	SyncEvent();

	return GridData[GridLocationToIndex(GridLoc)];
}

bool ULFPGridSystem::GetGridWorldLocation(const FIntVector Location, FVector& ReturnLocation, FRotator& ReturnRotation) const
{
	if (!IsLocationValid(Location)) return false;

	ReturnRotation = FRotator(0);

	switch (GridType)
	{
		case ELFPGridType::Rectangular:
			ReturnLocation = FVector(Location.X * GridGap.X, Location.Y * GridGap.Y, Location.Z * GridGap.Z);
			break;
		case ELFPGridType::Hexagon:
			ReturnLocation = FVector(Location.X * GridGap.X, (Location.Y * GridGap.Y) + ((Location.X + 1) % 2 == 0 ? 0.0f : GridGap.Y * 0.5f), Location.Z * GridGap.Z);
			break;
		case ELFPGridType::Triangle:
			ReturnLocation = FVector(Location.X * (GridGap.X * 0.5), Location.Y * GridGap.Y, Location.Z * GridGap.Z);
			if ((Location.X + 1) % 2 == 0) { ReturnRotation = FRotator(0, 180, 0); }
			break;
	}

	return true;
}

void ULFPGridSystem::UpdateEvent_Implementation(const FLGPGridSystemEvent& Data)
{
	for (int32 i = 0; i < Data.AddData.Num(); i++)
	{
		GridData[Data.AddIndex[i]] = Data.AddData[i];
	}

	for (int32 i = 0; i < Data.RemoveIndex.Num(); i++)
	{
		GridData[Data.RemoveIndex[i]] = INDEX_NONE;
	}

	GridEvent = FLGPGridSystemEvent();

	IsEventDirty = false;

	return;
}

