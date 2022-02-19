// Copyright by Loh Zhi Kang

#include "Helper/LFPGridArrayHelper.h"

// Sets default values for this component's properties
ULFPGridArrayHelper::ULFPGridArrayHelper()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULFPGridArrayHelper::BeginPlay()
{
	Super::BeginPlay();

	GridArratSize = GridSize.X * GridSize.Y * GridSize.Z;

	return;
}


// Called every frame
void ULFPGridArrayHelper::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

int32 ULFPGridArrayHelper::GridLocationToIndex(const FIntVector& Location) const
{
	return Location.X + (Location.Y * GridSize.X) + (Location.Z * (GridSize.X * GridSize.Y));
}

TArray<int32> ULFPGridArrayHelper::GridLocationsToIndex(const TArray<FIntVector>& GridLocations, const FIntVector Offset) const
{
	TArray<int32> ReturnData;

	for (const FIntVector Item : GridLocations)
	{
		if (!IsLocationValid(Item + Offset)) continue;

		ReturnData.Add(GridLocationToIndex(Item + Offset));
	}

	return ReturnData;
}

FIntVector ULFPGridArrayHelper::IndexToGridLocation(const int32& Index) const
{
	FIntVector ReturnData;

	ReturnData.Z = Index / (GridSize.X * GridSize.Y);
	ReturnData.Y = (Index / GridSize.X) - (ReturnData.Z * GridSize.Y);
	ReturnData.X = (Index - (ReturnData.Y * GridSize.X)) - (ReturnData.Z * (GridSize.X * GridSize.Y));

	return ReturnData;
}

TArray<FIntVector> ULFPGridArrayHelper::IndexsToGridLocation(const TArray<int32>& Indexs, const int32 Offset) const
{
	TArray<FIntVector> ReturnData;

	for (const int32 Item : Indexs)
	{
		if (GridArratSize <= Item || Item < 0) continue;

		ReturnData.Add(IndexToGridLocation(Item));
	}

	return ReturnData;
}

int32 ULFPGridArrayHelper::WordlLocationToIndex(const FVector& Location) const
{
	return GridLocationToIndex(WordlLocationToGridLocation(Location));
}

FIntVector ULFPGridArrayHelper::WordlLocationToGridLocation(const FVector& Location) const
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

bool ULFPGridArrayHelper::GetGridWorldLocation(const FIntVector Location, const bool AddHalfGap, FVector& ReturnLocation, FRotator& ReturnRotation) const
{
	if (!IsLocationValid(Location)) return false;

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

	ReturnLocation += AddHalfGap ? GetComponentLocation() + (GridGap * 0.5) : GetComponentLocation();

	return true;
}

bool ULFPGridArrayHelper::GetGridWorldLocationWithIndex(const int32 Index, const bool AddHalfGap, FVector& ReturnLocation, FRotator& ReturnRotation) const
{
	return GetGridWorldLocation(IndexToGridLocation(Index), AddHalfGap, ReturnLocation, ReturnRotation);
}

TArray<int32> ULFPGridArrayHelper::SectionGridIndex(const FIntVector SectionSize, const TSet<int32>& IgnoreIndexs) const
{
	TArray<int32> ReturnData;

	if (SectionSize.GetMin() <= 0) return ReturnData;

	FIntVector Size = FIntVector(GridSize.X / SectionSize.X, GridSize.Y / SectionSize.Y, GridSize.Z / SectionSize.Z);

	ReturnData.Reserve(Size.X * Size.Y * Size.Z);

	// Fill Unvisit List With Index
	for (int32 Z = 0; Z < GridSize.Z; Z += SectionSize.Z)
	for (int32 Y = 0; Y < GridSize.Y; Y += SectionSize.Y)
	for (int32 X = 0; X < GridSize.X; X += SectionSize.X)
	{
		int32 Index = GridLocationToIndex(FIntVector(X, Y, Z));

		if (!IgnoreIndexs.Contains(Index)) ReturnData.Add(Index);
	}

	return ReturnData;
}

TArray<int32> ULFPGridArrayHelper::RandomSectionGridIndex(const int32 Amount, const FIntVector SectionSize, const TSet<int32>& IgnoreIndexs, const FRandomStream& Seed) const
{
	TArray<int32> ReturnData;

	if (SectionSize.GetMin() <= 0) return ReturnData;

	FIntVector Size = FIntVector(GridSize.X / SectionSize.X, GridSize.Y / SectionSize.Y, GridSize.Z / SectionSize.Z);

	// Setup Unvist List
	TArray<int32> UnVisit;
	// Reserve List To Fill Faster
	UnVisit.Reserve(GridArratSize);
	// Fill Unvisit List With Index
	for (int32 Z = 0; Z < GridSize.Z; Z += SectionSize.Z)
	for (int32 Y = 0; Y < GridSize.Y; Y += SectionSize.Y)
	for (int32 X = 0; X < GridSize.X; X += SectionSize.X)
	{
		int32 Index = GridLocationToIndex(FIntVector(X, Y, Z));

		if (!IgnoreIndexs.Contains(Index)) UnVisit.Add(Index);
	}	

	// Shuffle Array Item
	for (int32 i = 0; i < UnVisit.Num(); i++)
	{
		UnVisit.Swap(i, Seed.RandRange(0, UnVisit.Num() - 1));
	}

	ReturnData.Reserve(Amount);

	for (int32 i = 0; i < Amount; i++)
	{
		ReturnData.Add(UnVisit.Pop());
	}

	return ReturnData;
}

TArray<int32> ULFPGridArrayHelper::GetAreaIndex(const int32 Index, const FIntVector Offset, const FIntVector AreaSize) const
{
	FIntVector StartLoc = IndexToGridLocation(Index) + Offset;
	TArray<int32> ReturnData;

	ReturnData.Reserve(((AreaSize.X * AreaSize.Y * AreaSize.Z) * 2) + 1);

	for (int32 Z = -AreaSize.Z; Z <= AreaSize.Z; Z++)
	for (int32 Y = -AreaSize.Y; Y <= AreaSize.Y; Y++)
	for (int32 X = -AreaSize.X; X <= AreaSize.X; X++)
	{
		FIntVector LoopLoc = FIntVector(X, Y, Z) + StartLoc;

		if (IsLocationValid(LoopLoc))
		{
			ReturnData.Add(GridLocationToIndex(LoopLoc));
		}
	}

	return ReturnData;
}

