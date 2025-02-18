// Copyright (c) 2023-2025 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#include "Library/LFPMarchingFunctionLibrary.h"
#include "Components/LFPChunkedTagDataComponent.h"
#include "Components/LFPMarchingDataComponent.h"
#include "Math/LFPGridLibrary.h"

bool ULFPMarchingFunctionLibrary::GetMarchingIDBit( const uint8 MarchingID , const int32 BitIndex )
{
	check(BitIndex >= 0 || BitIndex <= 7);

	return (MarchingID & 1 << (BitIndex & 8 - 1)) != 0;
}

void ULFPMarchingFunctionLibrary::SetMarchingIDBit( uint8& MarchingID , const int32 BitIndex , const bool bNewValue )
{
	check(BitIndex >= 0 || BitIndex <= 7);

	if ( bNewValue )
	{
		MarchingID |= 1 << (BitIndex & 7);
	}
	else
	{
		MarchingID &= ~(1 << (BitIndex & 7));
	}
}

uint8 ULFPMarchingFunctionLibrary::RotateMarchingIDByX( const uint8 MarchingID , const bool bReverse )
{
	constexpr int32 SwapList[6][2] =
		{
			{
				0
				, 2
			}
			, {
				2
				, 6
			}
			, {
				6
				, 4
			}
			, {
				1
				, 3
			}
			, {
				3
				, 7
			}
			, {
				7
				, 5
			}
		};

	uint8 ReturnValue = MarchingID;

	for ( int32 Index = bReverse
		                    ? 5
		                    : 0 ; Index < 6 && Index >= 0 ; bReverse
			                                                    ? Index--
			                                                    : Index++ )
	{
		const bool TempBool = GetMarchingIDBit(ReturnValue, SwapList[Index][0]);

		SetMarchingIDBit(ReturnValue, SwapList[Index][0], GetMarchingIDBit(ReturnValue, SwapList[Index][1]));
		SetMarchingIDBit(ReturnValue, SwapList[Index][1], TempBool);
	}

	return ReturnValue;
}

uint8 ULFPMarchingFunctionLibrary::RotateMarchingIDByY( const uint8 MarchingID , const bool bReverse )
{
	constexpr int32 SwapList[6][2] =
		{
			{
				0
				, 4
			}
			, {
				4
				, 5
			}
			, {
				5
				, 1
			}
			, {
				2
				, 6
			}
			, {
				6
				, 7
			}
			, {
				7
				, 3
			}
		};

	uint8 ReturnValue = MarchingID;

	for ( int32 Index = bReverse
		                    ? 5
		                    : 0 ; Index < 6 && Index >= 0 ; bReverse
			                                                    ? Index--
			                                                    : Index++ )
	{
		const bool TempBool = GetMarchingIDBit(ReturnValue, SwapList[Index][0]);

		SetMarchingIDBit(ReturnValue, SwapList[Index][0], GetMarchingIDBit(ReturnValue, SwapList[Index][1]));
		SetMarchingIDBit(ReturnValue, SwapList[Index][1], TempBool);
	}

	return ReturnValue;
}

uint8 ULFPMarchingFunctionLibrary::RotateMarchingIDByZ( const uint8 MarchingID , const bool bReverse )
{
	constexpr int32 SwapList[6][2] =
		{
			{
				0
				, 2
			}
			, {
				2
				, 3
			}
			, {
				3
				, 1
			}
			, {
				4
				, 6
			}
			, {
				6
				, 7
			}
			, {
				7
				, 5
			}
			,
		};

	uint8 ReturnValue = MarchingID;

	for ( int32 Index = bReverse
		                    ? 5
		                    : 0 ; Index < 6 && Index >= 0 ; bReverse
			                                                    ? Index--
			                                                    : Index++ )
	{
		const bool TempBool = GetMarchingIDBit(ReturnValue, SwapList[Index][0]);

		SetMarchingIDBit(ReturnValue, SwapList[Index][0], GetMarchingIDBit(ReturnValue, SwapList[Index][1]));
		SetMarchingIDBit(ReturnValue, SwapList[Index][1], TempBool);
	}

	return ReturnValue;
}

uint8 ULFPMarchingFunctionLibrary::RotateMarchingID( const uint8 MarchingID , const FIntVector& Rotation )
{
	uint8 ReturnValue = MarchingID;

	const bool bReverseX = Rotation.X < 0;
	const bool bReverseY = Rotation.Y < 0;
	const bool bReverseZ = Rotation.Z < 0;

	FIntVector ABSRotation = FIntVector(FMath::Abs(Rotation.X), FMath::Abs(Rotation.Y), FMath::Abs(Rotation.Z));

	for ( int32 Count = 0 ; Count < ABSRotation.X ; Count++ )
	{
		ReturnValue = RotateMarchingIDByX(ReturnValue, bReverseX);
	}

	for ( int32 Count = 0 ; Count < ABSRotation.Y ; Count++ )
	{
		ReturnValue = RotateMarchingIDByY(ReturnValue, bReverseY);
	}

	for ( int32 Count = 0 ; Count < ABSRotation.Z ; Count++ )
	{
		ReturnValue = RotateMarchingIDByZ(ReturnValue, bReverseZ);
	}

	return ReturnValue;
}

uint8 ULFPMarchingFunctionLibrary::CalculateDualGridMarchingID( const uint8 FullMarchingID , const int32 CalculateIndex )
{
	if ( FullMarchingID == 255 || FullMarchingID == 0 )
	{
		return 0; /* Fill so skip */
	}

	if ( GetMarchingIDBit(FullMarchingID, CalculateIndex) == false )
	{
		return 0; /* CalculateIndex Empty */
	}

	constexpr uint8 DefaultFilterList[8] =
		{
			23
			, 43
			, 77
			, 142
			, 113
			, 178
			, 212
			, 232
		};

	constexpr uint8 CheckMap[8][3] =
		{
			{
				6
				, 18
				, 20
			}
			, {
				9
				, 33
				, 40
			}
			, {
				9
				, 65
				, 72
			}
			, {
				6
				, 130
				, 132
			}
			, {
				96
				, 33
				, 65
			}
			, {
				144
				, 18
				, 130
			}
			, {
				144
				, 20
				, 132
			}
			, {
				96
				, 40
				, 72
			}
			,
		};

	constexpr uint8 ApplyMap[8][3] =
		{
			{
				8
				, 32
				, 64
			}
			, {
				4
				, 16
				, 128
			}
			, {
				2
				, 16
				, 128
			}
			, {
				1
				, 32
				, 64
			}
			, {
				128
				, 2
				, 4
			}
			, {
				64
				, 1
				, 8
			}
			, {
				32
				, 1
				, 8
			}
			, {
				16
				, 2
				, 4
			}
			,
		};

	uint8 CurrentFilter = DefaultFilterList[CalculateIndex];

	for ( int32 Step = 0 ; Step < 3 ; Step++ )
	{
		const uint8 CheckByte = CheckMap[CalculateIndex][Step];
		const uint8 ApplyByte = ApplyMap[CalculateIndex][Step];

		if ( (FullMarchingID & CheckByte) == CheckByte )
		{
			CurrentFilter |= ApplyByte;
		}
	}

	return FullMarchingID & CurrentFilter;
}

FIntVector ULFPMarchingFunctionLibrary::ToChunkedDataIndex( const ULFPMarchingDataComponent* DataComponent , const FIntVector& GlobalPosition )
{
	if ( IsValid(DataComponent) == false )
	{
		return FIntVector::NoneValue;
	}

	if ( GlobalPosition.GetMin() < 0 )
	{
		return FIntVector::NoneValue;
	}

	const FIntVector& RegionSize = DataComponent->GetRegionGridSize();
	const FIntVector& ChunkSize  = DataComponent->GetChunkGridSize();
	const FIntVector& DataSize   = DataComponent->GetDataGridSize();

	const FIntVector FullChuckSize = ChunkSize * DataSize;

	const int32 RegionIndex = ULFPGridLibrary::ToGridIndex(FIntVector(GlobalPosition.X / FullChuckSize.X, GlobalPosition.Y / FullChuckSize.Y, GlobalPosition.Z / FullChuckSize.Z), RegionSize);

	if ( RegionIndex == INDEX_NONE )
	{
		return FIntVector::NoneValue;
	}

	const int32 ChuckIndex = ULFPGridLibrary::ToGridIndex(FIntVector(GlobalPosition.X / DataSize.X, GlobalPosition.Y / DataSize.Y, GlobalPosition.Z / DataSize.Z), ChunkSize, true);
	const int32 DataIndex  = ULFPGridLibrary::ToGridIndex(GlobalPosition, DataSize, true);

	return FIntVector(RegionIndex, ChuckIndex, DataIndex);
}

uint8 ULFPMarchingFunctionLibrary::GetMarchingIDByGlobalPosition( const ULFPMarchingDataComponent* DataComponent , const FIntVector& GlobalPosition , const FGameplayTag& IncludeTag )
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
				const FIntVector TargetPosition = GlobalPosition + FIntVector(Index_X, Index_Y, Index_Z);

				if ( const FIntVector IndexList = ToChunkedDataIndex(DataComponent, TargetPosition) ; IndexList.X != INDEX_NONE && DataComponent->GetDataTag(IndexList.X, IndexList.Y, IndexList.Z).MatchesTag(IncludeTag) )
				{
					MarchingID |= (1 << Index);
				}

				Index++;
			}
		}
	}

	return MarchingID;
}

uint8 ULFPMarchingFunctionLibrary::GetMarchingIDByLocalPosition( const ULFPMarchingDataComponent* DataComponent , const FIntVector& LocalPosition , const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& IncludeTag )
{
	if ( IsValid(DataComponent) == false )
	{
		return 0;
	}

	if ( LocalPosition.GetMin() < 0 )
	{
		return 0;
	}

	const FIntVector& RegionSize = DataComponent->GetRegionGridSize();
	const FIntVector& ChunkSize  = DataComponent->GetChunkGridSize();
	const FIntVector& DataSize   = DataComponent->GetDataGridSize();

	const FIntVector FullChuckSize = ChunkSize * DataSize;

	const FIntVector RegionPos = ULFPGridLibrary::ToGridLocation(RegionIndex, RegionSize) * FullChuckSize;
	const FIntVector ChuckPos  = ULFPGridLibrary::ToGridLocation(ChunkIndex, ChunkSize) * DataSize;

	return GetMarchingIDByGlobalPosition(DataComponent, RegionPos + ChuckPos + LocalPosition, IncludeTag);
}
