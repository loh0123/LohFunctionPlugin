// Copyright by Loh Zhi Kang


#include "Terrain/LFPTerrainSystem.h"

// Sets default values for this component's properties
ULFPTerrainSystem::ULFPTerrainSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULFPTerrainSystem::BeginPlay()
{
	Super::BeginPlay();

	// Initialize Grid Array
	TerrainData.SetNum(GridSize.X * GridSize.Y * GridSize.Z);
}


// Called every frame
void ULFPTerrainSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsEventDirty)
	{
		UpdateEvent(TerrainEvent);
	}
}

FIntVector ULFPTerrainSystem::WorldToTerrainLocation(FVector Location) const
{
	FVector LocalPos = (Location - GetComponentLocation()) / GridGap;

	return FIntVector(FMath::FloorToInt(LocalPos.X), FMath::FloorToInt(LocalPos.Y), FMath::FloorToInt(LocalPos.Z));
}

FVector ULFPTerrainSystem::TerrainToWorldLocation(FIntVector Location) const
{
	return GetComponentLocation() + (FVector(Location) * GridGap) + (GridGap * 0.5);
}

bool ULFPTerrainSystem::IsTerrainLocationValid(FIntVector Location) const
{
	return Location.X >= 0 && Location.Y >= 0 && Location.Z >= 0 && Location.X < GridSize.X && Location.Y < GridSize.Y && Location.Z < GridSize.Z;
}

bool ULFPTerrainSystem::AddTerrain(const FLGPTerrainData Data)
{
	if (!IsTerrainLocationValid(Data.GridPosition)) return false;

	TerrainEvent.RemoveList.RemoveSingleSwap(Data.GridPosition);

	TerrainEvent.AddList.Emplace(Data);

	IsEventDirty = true;

	return true;
}

bool ULFPTerrainSystem::RemoveTerrain(const FIntVector GridPosition)
{
	if (!IsTerrainLocationValid(GridPosition)) return false;

	TerrainEvent.AddList.RemoveSingleSwap(GridPosition);

	TerrainEvent.RemoveList.Emplace(GridPosition);

	IsEventDirty = true;

	return true;
}

bool ULFPTerrainSystem::GetTerrain(const FIntVector GridPosition, FLGPTerrainData& ReturnData)
{
	if (!IsTerrainLocationValid(GridPosition)) return false;

	if (IsEventDirty) UpdateEvent(TerrainEvent);

	ReturnData = TerrainData[GridLocationToIndex(GridPosition)];

	return true;
}

void ULFPTerrainSystem::UpdateEvent_Implementation(const FLGPTerrainSystemEvent& Data)
{
	IsEventDirty = false;

	for (const FLGPTerrainData& Item : Data.AddList)
	{
		TerrainData[GridLocationToIndex(Item.GridPosition)] = Item;
	}

	for (const FIntVector& Item : Data.RemoveList)
	{
		TerrainData[GridLocationToIndex(Item)] = FLGPTerrainData(Item);
	}

	OnAddTerrain.Broadcast(TerrainEvent.AddList);
	OnRemoveTerrain.Broadcast(TerrainEvent.RemoveList);

	TerrainEvent = FLGPTerrainSystemEvent();

	return;
}

