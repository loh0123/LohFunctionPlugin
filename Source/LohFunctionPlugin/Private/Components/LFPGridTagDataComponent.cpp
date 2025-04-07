// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/LFPGridTagDataComponent.h"

#include "Data/LFPGridSetting.h"
#include "Math/LFPGridLibrary.h"

// Sets default values for this component's properties
ULFPGridTagDataComponent::ULFPGridTagDataComponent( )
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void ULFPGridTagDataComponent::BeginPlay( )
{
	if ( IsValid(GridSetting) )
	{
		DataIndexSize   = GridSetting->GetDataIndexSize();
		ChunkIndexSize  = GridSetting->GetChunkIndexSize();
		RegionIndexSize = GridSetting->GetRegionIndexSize();
	}

	Super::BeginPlay();
}

// Called every frame
void ULFPGridTagDataComponent::TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

ULFPGridSetting* ULFPGridTagDataComponent::GetGridSetting( ) const
{
	return GridSetting;
}

FIntVector ULFPGridTagDataComponent::ToGridPosition( const FIntVector GridIndex , const bool bRound ) const
{
	if ( IsValid(GridSetting) == false )
	{
		return FIntVector();
	}

	const FIntVector RegionPos(ULFPGridLibrary::ToGridLocation(GridIndex.X, GridSetting->GetRegionGridSize(), bRound));
	const FIntVector ChuckPos(ULFPGridLibrary::ToGridLocation(GridIndex.Y, GridSetting->GetChunkGridSize(), bRound));
	const FIntVector GridPos(ULFPGridLibrary::ToGridLocation(GridIndex.Z, GridSetting->GetDataGridSize(), bRound));

	return (RegionPos * GridSetting->GetChunkGridSize() * GridSetting->GetDataGridSize()) + (ChuckPos * GridSetting->GetDataGridSize()) + GridPos;
}

FIntVector ULFPGridTagDataComponent::ToGridIndex( FIntVector GridPosition , const bool bRound ) const
{
	auto DivideVector = [&] ( const FIntVector& A , const FIntVector& B )
	{
		return FIntVector(A.X / B.X, A.Y / B.Y, A.Z / B.Z);
	};

	const FIntVector TotalSize(GridSetting->GetRegionGridSize() * GridSetting->GetChunkGridSize() * GridSetting->GetDataGridSize());

	if ( bRound )
	{
		GridPosition.X %= TotalSize.X;
		GridPosition.Y %= TotalSize.Y;
		GridPosition.Z %= TotalSize.Z;

		if ( GridPosition.X < 0 )
		{
			GridPosition.X += TotalSize.X;
		}
		if ( GridPosition.Y < 0 )
		{
			GridPosition.Y += TotalSize.Y;
		}
		if ( GridPosition.Z < 0 )
		{
			GridPosition.Z += TotalSize.Z;
		}
	}
	else if ( ULFPGridLibrary::IsGridLocationValid(GridPosition, TotalSize) == false )
	{
		return FIntVector::NoneValue;
	}

	const FIntVector RegionPos(DivideVector(GridPosition, GridSetting->GetChunkGridSize() * GridSetting->GetDataGridSize()));
	const FIntVector ChuckPos(DivideVector(GridPosition, GridSetting->GetDataGridSize()));

	return FIntVector(ULFPGridLibrary::ToGridIndex(RegionPos, GridSetting->GetRegionGridSize()), ULFPGridLibrary::ToGridIndex(ChuckPos, GridSetting->GetChunkGridSize()), ULFPGridLibrary::ToGridIndex(GridPosition, GridSetting->GetDataGridSize(), true));
}

FIntVector ULFPGridTagDataComponent::AddOffsetToGridIndex( FIntVector GridIndex , const FIntVector Offset , const bool bRound ) const
{
	GridIndex = ToGridPosition(GridIndex, bRound);
	GridIndex += Offset;
	return ToGridIndex(GridIndex, bRound);
}
