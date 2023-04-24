// Copyright (c) 2022 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#include "Components/LFPWorldGrid.h"

// Sets default values for this component's properties
ULFPWorldGrid::ULFPWorldGrid()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULFPWorldGrid::BeginPlay()
{
	Super::BeginPlay();

	return;
}


// Called every frame
void ULFPWorldGrid::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

int32 ULFPWorldGrid::WorldLocationToIndex(const FVector& Location) const
{
	return ULFPGridLibrary::ToGridIndex(WorldLocationToGridLocation(Location), GridSize);
}

FIntVector ULFPWorldGrid::WorldLocationToGridLocation(const FVector& Location) const
{
	// if (Location.GetMin() < 0.0f) return FIntVector(INT_MIN);

	FVector LocalLocation;

	const FVector ComponentLocation = bCenterOrigin ? Location - GetComponentLocation() + GetVolumeSize(true) : Location - GetComponentLocation();

	switch (GridType)
	{
	case ELFPGridType::Rectangular:
		LocalLocation = ComponentLocation / GridGap;
		break;
	case ELFPGridType::Hexagon:
		LocalLocation = ComponentLocation / GridGap;
		if ((FMath::FloorToInt(LocalLocation.X) + 1) % 2 == 0) LocalLocation.Y -= 0.5f;
		break;
	case ELFPGridType::Triangle:
		LocalLocation = ComponentLocation / (GridGap * FVector(0.5, 1, 1));
		break;
	}

	return FIntVector(FMath::FloorToInt(LocalLocation.X), FMath::FloorToInt(LocalLocation.Y), FMath::FloorToInt(LocalLocation.Z));
}

bool ULFPWorldGrid::GridLocationToWorldLocation(const FIntVector Location, const bool AddHalfGap, FVector& ReturnLocation, FRotator& ReturnRotation) const
{
	if (!ULFPGridLibrary::IsGridLocationValid(Location, GridSize)) return false;

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

	if (bCenterOrigin) ReturnLocation -= GetVolumeSize(true) - (GridGap * 0.5);

	ReturnLocation += AddHalfGap ? GetComponentLocation() + (GridGap * 0.5) : GetComponentLocation();

	return true;
}

bool ULFPWorldGrid::IndexToWorldLocation(const int32 Index, const bool AddHalfGap, FVector& ReturnLocation, FRotator& ReturnRotation) const
{
	return GridLocationToWorldLocation(ULFPGridLibrary::ToGridLocation(Index, GridSize), AddHalfGap, ReturnLocation, ReturnRotation);
}
