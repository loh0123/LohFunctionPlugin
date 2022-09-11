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

#include "Helper/LFPWorldGrid.h"

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

int32 ULFPWorldGrid::WordlLocationToIndex(const FVector& Location) const
{
	return ULFPGridLibrary::GridLocationToIndex(WordlLocationToGridLocation(Location), GridSize);
}

FIntVector ULFPWorldGrid::WordlLocationToGridLocation(const FVector& Location) const
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

bool ULFPWorldGrid::GridLocationToWorldLocation(const FIntVector Location, const bool AddHalfGap, FVector& ReturnLocation, FRotator& ReturnRotation) const
{
	if (!ULFPGridLibrary::IsLocationValid(Location, GridSize)) return false;

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

bool ULFPWorldGrid::IndexToWorldLocation(const int32 Index, const bool AddHalfGap, FVector& ReturnLocation, FRotator& ReturnRotation) const
{
	return GridLocationToWorldLocation(ULFPGridLibrary::IndexToGridLocation(Index, GridSize), AddHalfGap, ReturnLocation, ReturnRotation);
}
