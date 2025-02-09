// Fill out your copyright notice in the Description page of Project Settings.

#include "Library/LFPMarchingFunctionLibrary.h"

#include "Components/LFPChunkedTagDataComponent.h"
#include "Math/LFPGridLibrary.h"

FIntVector ULFPMarchingFunctionLibrary::GetRegionChunkAndDataIndex( const FIntVector& Position , const FIntVector& RegionSize , const FIntVector& ChuckSize , const FIntVector& DataSize )
{
	if ( Position.GetMin() < 0 )
	{
		return FIntVector::NoneValue;
	}

	const FIntVector FullChuckSize = ChuckSize * DataSize;

	const int32 RegionIndex = ULFPGridLibrary::ToGridIndex(FIntVector(Position.X / FullChuckSize.X, Position.Y / FullChuckSize.Y, Position.Z / FullChuckSize.Z), RegionSize);

	if ( RegionIndex == INDEX_NONE )
	{
		return FIntVector::NoneValue;
	}

	const int32 ChuckIndex = ULFPGridLibrary::ToGridIndex(FIntVector(Position.X / ChuckSize.X, Position.Y / ChuckSize.Y, Position.Z / ChuckSize.Z), ChuckSize, true);
	const int32 DataIndex  = ULFPGridLibrary::ToGridIndex(Position, DataSize, true);

	return FIntVector(RegionIndex, ChuckIndex, DataIndex);
}

uint8 ULFPMarchingFunctionLibrary::GetMarchingIDByValidTag( const ULFPChunkedTagDataComponent* DataComponent , const FIntVector& Position , const FIntVector& RegionSize , const FIntVector& ChuckSize , const FIntVector& DataSize )
{
	if ( IsValid(DataComponent) == false )
	{
		return 0;
	}

	uint8 MarchingID = 0;

	int32 Index = 0;

	for ( int32 Index_Z = 0 ; Index_Z < 2 ; Index_Z++ )
	{
		for ( int32 Index_Y = 0 ; Index_Y < 2 ; Index_Y++ )
		{
			for ( int32 Index_X = 0 ; Index_X < 2 ; Index_X++ )
			{
				const FIntVector TargetPosition = Position + FIntVector(Index_X, Index_Y, Index_Z);

				const FIntVector IndexList = GetRegionChunkAndDataIndex(TargetPosition, RegionSize, ChuckSize, DataSize);

				if ( IndexList.X != INDEX_NONE && DataComponent->GetDataTag(IndexList.X, IndexList.Y, IndexList.Z).IsValid() )
				{
					MarchingID |= (1 << Index);
				}

				Index++;
			}
		}
	}

	return MarchingID;
}
