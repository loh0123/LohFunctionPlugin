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

bool ULFPGridSystem::MarkLocation_Internal(FIntVector Locations, const int32& Data)
{
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

bool ULFPGridSystem::UnmarkLocation_Internal(FIntVector Locations)
{
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

void ULFPGridSystem::GetMaxRange(const TArray<FVector>& Locations, const FIntVector& Rotation, const FVector& Offset, TArray<FIntVector>& ReturnConv, FIntVector& Max, FIntVector& Min)
{
	ReturnConv.Empty(Locations.Num());
	Max = FIntVector(0);
	Min = FIntVector(INT_MAX);

	for (const FVector& Item : Locations)
	{
		const int32 Index = ReturnConv.Add(WordlLocationToGridLocation(FRotator(Rotation.Y * 90, Rotation.Z * 90, Rotation.X * 90).RotateVector(Item) + Offset));

		if (Max.X < ReturnConv[Index].X) Max.X = ReturnConv[Index].X;
		if (Max.Y < ReturnConv[Index].Y) Max.Y = ReturnConv[Index].Y;
		if (Max.Z < ReturnConv[Index].Z) Max.Z = ReturnConv[Index].Z;

		if (Min.X > ReturnConv[Index].X) Min.X = ReturnConv[Index].X;
		if (Min.Y > ReturnConv[Index].Y) Min.Y = ReturnConv[Index].Y;
		if (Min.Z > ReturnConv[Index].Z) Min.Z = ReturnConv[Index].Z;
	}

	return;
}

int32 ULFPGridSystem::GridLocationToIndex(const FIntVector& Location) const
{
	return Location.X + (Location.Y * GridSize.X) + (Location.Z * (GridSize.X * GridSize.Y));
}

FIntVector ULFPGridSystem::IndexToGridLocation(const int32& Index) const
{
	FIntVector ReturnData;

	ReturnData.Z = Index / (GridSize.X * GridSize.Y);
	ReturnData.Y = (Index / GridSize.X) - (ReturnData.Z * GridSize.Y);
	ReturnData.X = (Index - (ReturnData.Y * GridSize.X)) - (ReturnData.Z * (GridSize.X * GridSize.Y));

	return ReturnData;
}

FIntVector ULFPGridSystem::WordlLocationToGridLocation(const FVector& Location) const
{
	if (Location.GetMin() < 0.0f) return FIntVector(INT_MIN);

	FVector LocalLocation;

	switch (GridType)
	{
	case ELFPGridType::Rectangular:
		LocalLocation = (Location - GetComponentLocation()) / GridGap;
		break;
	case ELFPGridType::Hexagon:
		LocalLocation = (Location - GetComponentLocation()) / GridGap;
		if ((FMath::FloorToInt(LocalLocation.X) + 1) % 2 == 0) LocalLocation.Y -= 0.5f;
		break;
	case ELFPGridType::Triangle:
		LocalLocation = (Location - GetComponentLocation()) / (GridGap * FVector(0.5, 1, 1));
		break;
	}

	return FIntVector(FMath::FloorToInt(LocalLocation.X), FMath::FloorToInt(LocalLocation.Y), FMath::FloorToInt(LocalLocation.Z));
}

bool ULFPGridSystem::IsLocationMarked(const FVector Location)
{
	FIntVector GridLoc = WordlLocationToGridLocation(Location);

	if (!IsLocationValid_Internal(GridLoc)) return false;

	SyncEvent();

	return GridData[GridLocationToIndex(GridLoc)] != INDEX_NONE;
}

bool ULFPGridSystem::IsLocationsMarked(const TArray<FVector>& Locations, const FIntVector& Rotation, const FVector& Offset, const bool MarkInvalid)
{
	SyncEvent();

	TArray<FIntVector> ConvArray;
	FIntVector MaxData;
	FIntVector MinData;

	GetMaxRange(Locations, Rotation, Offset, ConvArray, MaxData, MinData);

	if (!IsLocationValid_Internal(MaxData)) return MarkInvalid;
	if (!IsLocationValid_Internal(MinData)) return MarkInvalid;

	for (int32 i = 0; i < Locations.Num(); i++)
	{
		if (GridData[GridLocationToIndex(ConvArray[i])] != INDEX_NONE)
		{
			return true;
		}
	}

	return false;
}

bool ULFPGridSystem::MarkLocation(const FVector Location, const int32 Data)
{
	return MarkLocation_Internal(WordlLocationToGridLocation(Location), Data);
}

bool ULFPGridSystem::MarkLocations(const TArray<FVector>& Locations, const FIntVector& Rotation, const FVector& Offset, const int32 Data)
{
	TArray<FIntVector> ConvArray;
	FIntVector MaxData;
	FIntVector MinData;

	GetMaxRange(Locations, Rotation, Offset, ConvArray, MaxData, MinData);

	if (!IsLocationValid_Internal(MaxData)) return false;
	if (!IsLocationValid_Internal(MinData)) return false;
	
	for (const FIntVector& Item : ConvArray)
	{
		MarkLocation_Internal(Item, Data);
	}

	return Locations.Num() > 0;
}

bool ULFPGridSystem::UnmarkLocation(const FVector Location)
{
	return UnmarkLocation_Internal(WordlLocationToGridLocation(Location));
}

bool ULFPGridSystem::UnmarkLocations(const TArray<FVector>& Locations, const FIntVector& Rotation, const FVector& Offset)
{
	TArray<FIntVector> ConvArray;
	FIntVector MaxData;
	FIntVector MinData;

	GetMaxRange(Locations, Rotation, Offset, ConvArray, MaxData, MinData);

	if (!IsLocationValid_Internal(MaxData)) return false;
	if (!IsLocationValid_Internal(MinData)) return false;

	for (const FIntVector& Item : ConvArray)
	{
		UnmarkLocation_Internal(Item);
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

bool ULFPGridSystem::TryFitTemplate(const TArray<FVector>& Template, const FVector& Offset, FIntVector& NeedRotation, const bool CanRotateX, const bool CanRotateY, const bool CanRotateZ)
{
	if (!IsLocationValid_Internal(WordlLocationToGridLocation(Offset))) return false;

	for (uint8 Z = 0; Z < (CanRotateZ ? 4 : 1); Z++)
	for (uint8 Y = 0; Y < (CanRotateY ? 4 : 1); Y++)
	for (uint8 X = 0; X < (CanRotateX ? 4 : 1); X++)
	{
		NeedRotation = FIntVector(X, Y, Z);

		if (!IsLocationsMarked(Template, NeedRotation, Offset, true)) return true;
	}

	return false;
}

bool ULFPGridSystem::TryFitTemplates(const TArray<FVector>& Template, const TArray<FVector>& Offsets, FVector& FitOffset, FIntVector& NeedRotation, const bool CanRotateX, const bool CanRotateY, const bool CanRotateZ)
{
	for (const FVector& Offset : Offsets)
	{
		FitOffset = Offset;

		if (TryFitTemplate(Template, FitOffset, NeedRotation, CanRotateX, CanRotateY, CanRotateZ)) return true;
	}

	return false;
}

bool ULFPGridSystem::TryFitTemplateNear(const TArray<FVector>& Template, const FVector& Offset, const FIntVector& CheckSize, FVector& FitOffset, FIntVector& NeedRotation, const bool CanRotateX, const bool CanRotateY, const bool CanRotateZ)
{
	for (int32 Z = -CheckSize.Z; Z <= CheckSize.Z; Z++)
	for (int32 Y = -CheckSize.Y; Y <= CheckSize.Y; Y++)
	for (int32 X = -CheckSize.X; X <= CheckSize.X; X++)
	{
		FitOffset = (FVector(X, Y, Z) * GridGap) + Offset;

		if (TryFitTemplate(Template, FitOffset, NeedRotation, CanRotateX, CanRotateY, CanRotateZ)) return true;
	}

	return false;
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

