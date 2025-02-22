// Copyright (c) 2023-2025 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#include "Components/LFPMarchingDataComponent.h"

#include "Math/LFPGridLibrary.h"

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

FIntVector ULFPMarchingDataComponent::ToChunkedDataIndex( const FIntVector& GlobalPosition ) const
{
	if ( GlobalPosition.GetMin() < 0 )
	{
		return FIntVector::NoneValue;
	}

	const FIntVector FullChuckSize = ChunkGridSize * DataGridSize;

	const int32 RegionIndex = ULFPGridLibrary::ToGridIndex(FIntVector(GlobalPosition.X / FullChuckSize.X, GlobalPosition.Y / FullChuckSize.Y, GlobalPosition.Z / FullChuckSize.Z), RegionGridSize);

	if ( RegionIndex == INDEX_NONE )
	{
		return FIntVector::NoneValue;
	}

	const int32 ChuckIndex = ULFPGridLibrary::ToGridIndex(FIntVector(GlobalPosition.X / DataGridSize.X, GlobalPosition.Y / DataGridSize.Y, GlobalPosition.Z / DataGridSize.Z), ChunkGridSize, true);
	const int32 DataIndex  = ULFPGridLibrary::ToGridIndex(GlobalPosition, DataGridSize, true);

	return FIntVector(RegionIndex, ChuckIndex, DataIndex);
}

FIntVector ULFPMarchingDataComponent::ToGlobalPosition(  const FIntVector& LocalPosition , const int32 RegionIndex , const int32 ChunkIndex ) const
{
	const FIntVector FullChuckSize = ChunkGridSize * DataGridSize;

	const FIntVector RegionPos = ULFPGridLibrary::ToGridLocation(RegionIndex, RegionGridSize) * FullChuckSize;
	const FIntVector ChuckPos  = ULFPGridLibrary::ToGridLocation(ChunkIndex, ChunkGridSize) * DataGridSize;

	return RegionPos + ChuckPos + LocalPosition;
}

uint8 ULFPMarchingDataComponent::GenerateMarchingID(  const FIntVector& GlobalPosition , const FGameplayTag& IncludeTag ) const
{
	uint8 MarchingID = 0;

	int32 Index = 0;

	for ( int32 Index_Z = 0 ; Index_Z < 2 ; Index_Z++ )
	{
		for ( int32 Index_Y = 0 ; Index_Y < 2 ; Index_Y++ )
		{
			for ( int32 Index_X = 0 ; Index_X < 2 ; Index_X++ )
			{
				const FIntVector TargetPosition = GlobalPosition + FIntVector(Index_X, Index_Y, Index_Z);

				if ( const FIntVector IndexList = ToChunkedDataIndex(TargetPosition) ; IndexList.X != INDEX_NONE && GetDataTag(IndexList.X, IndexList.Y, IndexList.Z).MatchesTag(IncludeTag) )
				{
					MarchingID |= (1 << Index);
				}

				Index++;
			}
		}
	}

	return MarchingID;
}

TArray<uint8> ULFPMarchingDataComponent::GenerateMarchingIDList( const FIntVector& StartGlobalPosition, const FIntVector& EndGlobalPosition, const FGameplayTag& IncludeTag ) const
{
	TArray<uint8> ResultList = TArray<uint8>();

	const FIntVector TotalLoop = EndGlobalPosition - StartGlobalPosition;

	ResultList.Reserve(TotalLoop.X * TotalLoop.Y * TotalLoop.Z);

	for ( int32 Index_Z = StartGlobalPosition.Z ; Index_Z <= EndGlobalPosition.Z ; Index_Z++ )
	{
		for ( int32 Index_Y = StartGlobalPosition.Y ; Index_Y <= EndGlobalPosition.Y ; Index_Y++ )
		{
			for ( int32 Index_X = StartGlobalPosition.X ; Index_X <= EndGlobalPosition.X ; Index_X++ )
			{
				ResultList.Add(GenerateMarchingID(FIntVector(Index_X, Index_Y, Index_Z), IncludeTag));
			}
		}
	}

	return ResultList;
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


