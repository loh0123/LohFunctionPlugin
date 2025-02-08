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

	const FIntVector LoopVectorList[8] =
		{
			FIntVector(0, 0, 0)
			, FIntVector(0, 1, 0)
			, FIntVector(1, 0, 0)
			, FIntVector(1, 1, 0)
			, FIntVector(0, 0, 1)
			, FIntVector(0, 1, 1)
			, FIntVector(1, 0, 1)
			, FIntVector(1, 1, 1)
		};

	uint8 MarchingID = 0;

	for ( int32 Index = 0 ; Index < 8 ; ++Index )
	{
		const FIntVector TargetPosition = Position + LoopVectorList[Index];

		const FIntVector IndexList = GetRegionChunkAndDataIndex(TargetPosition, RegionSize, ChuckSize, DataSize);

		if ( IndexList.X != INDEX_NONE && DataComponent->GetDataTag(IndexList.X, IndexList.Y, IndexList.Z).IsValid() )
		{
			MarchingID |= (1 << Index);
		}
	}

	return MarchingID;
}
