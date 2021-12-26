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

bool ULFPGridSystem::MarkLocation_Internal(FIntVector Locations, const int32& Data, const bool& FlipX, const bool& FlipY, const bool& FlipZ, const FIntVector& MaxRange, const FIntVector& MinRange)
{
	if (FlipX) { Locations.X = (MaxRange.X - Locations.X) + MinRange.X; }
	if (FlipY) { Locations.Y = (MaxRange.Y - Locations.Y) + MinRange.Y; }
	if (FlipZ) { Locations.Z = (MaxRange.Z - Locations.Z) + MinRange.Z; }

	if (!IsLocationValid_Internal(Locations)) return false;

	int32 Index = GridEvent.AddIndex.IndexOfByKey(GridLocationToIndex(Locations));

	if (Index == INDEX_NONE)
	{
		GridEvent.AddIndex.Emplace(GridLocationToIndex(Locations));
		GridEvent.AddData.Emplace(Data);
	}
	else
	{
		GridEvent.AddData[Index] = Data;
	}

	GridEvent.RemoveIndex.RemoveSingle(GridLocationToIndex(Locations));

	IsEventDirty = true;

	return true;
}

bool ULFPGridSystem::UnmarkLocation_Internal(FIntVector Locations, const bool& FlipX, const bool& FlipY, const bool& FlipZ, const FIntVector& MaxRange, const FIntVector& MinRange)
{
	if (FlipX) { Locations.X = (MaxRange.X - Locations.X) + MinRange.X; }
	if (FlipY) { Locations.Y = (MaxRange.Y - Locations.Y) + MinRange.Y; }
	if (FlipZ) { Locations.Z = (MaxRange.Z - Locations.Z) + MinRange.Z; }

	if (!IsLocationValid_Internal(Locations)) return false;

	if (!GridEvent.RemoveIndex.Contains(GridLocationToIndex(Locations)))
	{
		GridEvent.RemoveIndex.Emplace(GridLocationToIndex(Locations));
	}

	int32 Index = GridEvent.AddIndex.IndexOfByKey(GridLocationToIndex(Locations));

	if (Index != INDEX_NONE)
	{
		GridEvent.AddIndex.RemoveAt(Index);
		GridEvent.AddData.RemoveAt(Index);
	}

	IsEventDirty = true;

	return true;
}

void ULFPGridSystem::GetMaxRange(const TArray<FVector>& Locations, const FVector& Offset, TArray<FIntVector>& ReturnConv, FIntVector& Max, FIntVector& Min)
{
	ReturnConv.Empty(Locations.Num());
	Max = FIntVector(0);
	Min = FIntVector(INT_MAX);

	for (const FVector& Item : Locations)
	{
		const int32 Index = ReturnConv.Add(WordlLocationToGridLocation(Item + Offset));

		if (Max.X < ReturnConv[Index].X) Max.X = ReturnConv[Index].X;
		if (Max.Y < ReturnConv[Index].Y) Max.Y = ReturnConv[Index].Y;
		if (Max.Z < ReturnConv[Index].Z) Max.Z = ReturnConv[Index].Z;

		if (Min.X > ReturnConv[Index].X) Min.X = ReturnConv[Index].X;
		if (Min.Y > ReturnConv[Index].Y) Min.Y = ReturnConv[Index].Y;
		if (Min.Z > ReturnConv[Index].Z) Min.Z = ReturnConv[Index].Z;
	}

	return;
}

bool ULFPGridSystem::IsLocationMarked(const FVector Location)
{
	FIntVector GridLoc = WordlLocationToGridLocation(Location);

	if (!IsLocationValid_Internal(GridLoc)) return false;

	SyncEvent();

	return GridData[GridLocationToIndex(GridLoc)] != INDEX_NONE;
}

bool ULFPGridSystem::IsLocationsMarked(const TArray<FVector>& Locations, const FVector& Offset, const bool FlipX, const bool FlipY, const bool FlipZ)
{
	SyncEvent();

	TArray<FIntVector> ConvArray;
	FIntVector MaxData;
	FIntVector MinData;

	GetMaxRange(Locations, Offset, ConvArray, MaxData, MinData);

	for (int32 i = 0; i < Locations.Num(); i++)
	{
		if (FlipX) { ConvArray[i].X = (MaxData.X - ConvArray[i].X) + MinData.X; }
		if (FlipY) { ConvArray[i].Y = (MaxData.Y - ConvArray[i].Y) + MinData.Y; }
		if (FlipZ) { ConvArray[i].Z = (MaxData.Z - ConvArray[i].Z) + MinData.Z; }

		if (!IsLocationValid_Internal(ConvArray[i])) continue;

		if (GridData[GridLocationToIndex(ConvArray[i])] != INDEX_NONE)
		{
			return true;
		}
	}

	return false;
}

bool ULFPGridSystem::MarkLocation(const FVector Location, const int32 Data)
{
	return MarkLocation_Internal(WordlLocationToGridLocation(Location), Data, false, false, false, FIntVector(0), FIntVector(0));
}

bool ULFPGridSystem::MarkLocations(const TArray<FVector>& Locations, const FVector& Offset, const int32 Data, const bool FlipX, const bool FlipY, const bool FlipZ)
{
	TArray<FIntVector> ConvArray;
	FIntVector MaxData;
	FIntVector MinData;

	GetMaxRange(Locations, Offset, ConvArray, MaxData, MinData);
	
	for (const FIntVector& Item : ConvArray)
	{
		MarkLocation_Internal(Item, Data, FlipX, FlipY, FlipZ, MaxData, MinData);
	}

	return Locations.Num() > 0;
}

bool ULFPGridSystem::UnmarkLocation(const FVector Location)
{
	return UnmarkLocation_Internal(WordlLocationToGridLocation(Location), false, false, false, FIntVector(0), FIntVector(0));
}

bool ULFPGridSystem::UnmarkLocations(const TArray<FVector>& Locations, const FVector& Offset, const bool FlipX, const bool FlipY, const bool FlipZ)
{
	TArray<FIntVector> ConvArray;
	FIntVector MaxData;
	FIntVector MinData;

	GetMaxRange(Locations, Offset, ConvArray, MaxData, MinData);

	for (const FIntVector& Item : ConvArray)
	{
		UnmarkLocation_Internal(Item, FlipX, FlipY, FlipZ, MaxData, MinData);
	}

	return Locations.Num() > 0;
}

int32 ULFPGridSystem::GetLocationData(const FVector Location)
{
	FIntVector GridLoc = WordlLocationToGridLocation(Location);

	if (!IsLocationValid_Internal(GridLoc)) return INDEX_NONE;

	SyncEvent();

	return GridData[GridLocationToIndex(GridLoc)];
}

bool ULFPGridSystem::GetGridWorldLocation(const FIntVector Location, FVector& ReturnLocation, FRotator& ReturnRotation) const
{
	if (!IsLocationValid_Internal(Location)) return false;

	ReturnRotation = FRotator(0);

	switch (GridType)
	{
		case ELFPGridType::Rectangular:
			ReturnLocation = FVector(Location.X * GridGap.X, Location.Y * GridGap.Y, Location.Z * GridGap.Z);
			break;
		case ELFPGridType::Hexagon:
			ReturnLocation = FVector(Location.X * GridGap.X, (Location.Y * GridGap.Y) + ((Location.X + 1) % 2 == 1 ? 0.0f : GridGap.Y * 0.5f), Location.Z * GridGap.Z);
			break;
		case ELFPGridType::Triangle:
			ReturnLocation = FVector(Location.X * (GridGap.X * 0.5), Location.Y * GridGap.Y, Location.Z * GridGap.Z);
			if ((Location.X + 1) % 2 == 0) { ReturnRotation = FRotator(0, 180, 0); }
			break;
	}

	ReturnLocation += GetComponentLocation();

	return true;
}

bool ULFPGridSystem::GetGridWorldLocationWithIndex(const int32 Index, FVector& ReturnLocation, FRotator& ReturnRotation) const
{
	return GetGridWorldLocation(IndexToGridLocation(Index), ReturnLocation, ReturnRotation);
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

