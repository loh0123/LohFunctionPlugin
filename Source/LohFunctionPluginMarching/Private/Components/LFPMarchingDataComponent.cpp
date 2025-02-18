// Copyright (c) 2023-2025 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#include "Components/LFPMarchingDataComponent.h"

// Sets default values for this component's properties
ULFPMarchingDataComponent::ULFPMarchingDataComponent( )
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void ULFPMarchingDataComponent::BeginPlay( )
{
	DataIndexSize   = DataGridSize.X * DataGridSize.Y * DataGridSize.Z;
	ChunkIndexSize  = ChunkGridSize.X * ChunkGridSize.Y * ChunkGridSize.Z;
	RegionIndexSize = RegionGridSize.X * RegionGridSize.Y * RegionGridSize.Z;

	Super::BeginPlay();
}

// Called every frame
void ULFPMarchingDataComponent::TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

const FIntVector& ULFPMarchingDataComponent::GetDataGridSize( ) const
{
	return DataGridSize;
}

const FIntVector& ULFPMarchingDataComponent::GetChunkGridSize( ) const
{
	return ChunkGridSize;
}

const FIntVector& ULFPMarchingDataComponent::GetRegionGridSize( ) const
{
	return RegionGridSize;
}
