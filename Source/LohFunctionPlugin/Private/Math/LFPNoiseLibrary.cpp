// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#include "Math/LFPNoiseLibrary.h"
#include "Kismet/KismetMathLibrary.h"

FLFPNoiseTable ULFPNoiseLibrary::CreateNoiseTable( const FRandomStream& Seed )
{
	FLFPNoiseTable NewTable;

	NewTable.NoiseData.SetNum(256);

	for ( float& Item : NewTable.NoiseData )
	{
		Item = Seed.GetFraction();
	}

	return NewTable;
}

float ULFPNoiseLibrary::GetFloatNoise( const FLFPNoiseTable& NoiseTable , const FIntVector Location )
{
	if ( NoiseTable.NoiseData.Num() != 256 )
	{
		return 0.0f;
	}

	const float a = NoiseTable.NoiseData[(Location.X < 0
		                                      ? 256 - FMath::Abs(Location.X)
		                                      : Location.X) % 256];
	const float b = NoiseTable.NoiseData[((Location.Y < 0
		                                       ? 256 - FMath::Abs(Location.Y)
		                                       : Location.Y) + 64) % 256];
	const float c = NoiseTable.NoiseData[((Location.Z < 0
		                                       ? 256 - FMath::Abs(Location.Z)
		                                       : Location.Z) + 128) % 256];

	const float Result = NoiseTable.NoiseData[static_cast< int32 >((a + b + c) * 256) % 256];

	return Result;
}

FVector ULFPNoiseLibrary::GetVectorNoise( const FLFPNoiseTable& NoiseTable , const FIntVector Location )
{
	if ( NoiseTable.NoiseData.Num() != 256 )
	{
		return FVector(0, 0, 0);
	}

	const float a = NoiseTable.NoiseData[(Location.X < 0
		                                      ? 256 - FMath::Abs(Location.X)
		                                      : Location.X) % 256];
	const float b = NoiseTable.NoiseData[((Location.Y < 0
		                                       ? 256 - FMath::Abs(Location.Y)
		                                       : Location.Y) + 64) % 256];
	const float c = NoiseTable.NoiseData[((Location.Z < 0
		                                       ? 256 - FMath::Abs(Location.Z)
		                                       : Location.Z) + 128) % 256];

	const FVector Result = FVector(NoiseTable.NoiseData[static_cast< int32 >((a + b + c) * 256) % 256], NoiseTable.NoiseData[(static_cast< int32 >((a + b + c) * 256) + 16) % 256], NoiseTable.NoiseData[(static_cast< int32 >((a + b + c) * 256) + 32) % 256]);

	return Result;
}

FVector ULFPNoiseLibrary::GetDirectionNoise( const FLFPNoiseTable& NoiseTable , const FIntVector Location )
{
	if ( NoiseTable.NoiseData.Num() != 256 )
	{
		return FVector(0, 0, 0);
	}

	const float a = NoiseTable.NoiseData[(Location.X < 0
		                                      ? 256 - FMath::Abs(Location.X)
		                                      : Location.X) % 256];
	const float b = NoiseTable.NoiseData[((Location.Y < 0
		                                       ? 256 - FMath::Abs(Location.Y)
		                                       : Location.Y) + 64) % 256];
	const float c = NoiseTable.NoiseData[((Location.Z < 0
		                                       ? 256 - FMath::Abs(Location.Z)
		                                       : Location.Z) + 128) % 256];

	const FRotator Result = FRotator(NoiseTable.NoiseData[static_cast< int32 >((a + b + c) * 256) % 256] * 360, NoiseTable.NoiseData[(static_cast< int32 >((a + b + c) * 256) + 16) % 256] * 360, NoiseTable.NoiseData[(static_cast< int32 >((a + b + c) * 256) + 32) % 256] * 360);

	return UKismetMathLibrary::GetForwardVector(Result);
}

float ULFPNoiseLibrary::GetLerpNoise( const FLFPNoiseTable& NoiseTable , const FVector& Location )
{
	const FIntVector StartLocation = FIntVector(FMath::TruncToInt(Location.X), FMath::TruncToInt(Location.Y), FMath::TruncToInt(Location.Z));
	const FVector    AlphaLocation = FVector(Location.X - StartLocation.X, Location.Y - StartLocation.Y, Location.Z - StartLocation.Z);

	const float Down  = FMath::Lerp(GetFloatNoise(NoiseTable, StartLocation + FIntVector(0, 0, 0)), GetFloatNoise(NoiseTable, StartLocation + FIntVector(1, 0, 0)), AlphaLocation.X);
	const float DownY = FMath::Lerp(GetFloatNoise(NoiseTable, StartLocation + FIntVector(0, 1, 0)), GetFloatNoise(NoiseTable, StartLocation + FIntVector(1, 1, 0)), AlphaLocation.X);
	const float Up    = FMath::Lerp(GetFloatNoise(NoiseTable, StartLocation + FIntVector(0, 0, 1)), GetFloatNoise(NoiseTable, StartLocation + FIntVector(1, 0, 1)), AlphaLocation.X);
	const float UpY   = FMath::Lerp(GetFloatNoise(NoiseTable, StartLocation + FIntVector(0, 1, 1)), GetFloatNoise(NoiseTable, StartLocation + FIntVector(1, 1, 1)), AlphaLocation.X);

	return FMath::Lerp(FMath::Lerp(Down, DownY, AlphaLocation.Y), FMath::Lerp(Up, UpY, AlphaLocation.Y), AlphaLocation.Z);
}

FVector ULFPNoiseLibrary::GetLerpVectorNoise( const FLFPNoiseTable& NoiseTable , const FVector& Location )
{
	const FIntVector StartLocation = FIntVector(FMath::TruncToInt(Location.X), FMath::TruncToInt(Location.Y), FMath::TruncToInt(Location.Z));
	const FVector    AlphaLocation = FVector(Location.X - StartLocation.X, Location.Y - StartLocation.Y, Location.Z - StartLocation.Z);

	const FVector Down  = FMath::Lerp(GetVectorNoise(NoiseTable, StartLocation + FIntVector(0, 0, 0)), GetVectorNoise(NoiseTable, StartLocation + FIntVector(1, 0, 0)), AlphaLocation.X);
	const FVector DownY = FMath::Lerp(GetVectorNoise(NoiseTable, StartLocation + FIntVector(0, 1, 0)), GetVectorNoise(NoiseTable, StartLocation + FIntVector(1, 1, 0)), AlphaLocation.X);
	const FVector Up    = FMath::Lerp(GetVectorNoise(NoiseTable, StartLocation + FIntVector(0, 0, 1)), GetVectorNoise(NoiseTable, StartLocation + FIntVector(1, 0, 1)), AlphaLocation.X);
	const FVector UpY   = FMath::Lerp(GetVectorNoise(NoiseTable, StartLocation + FIntVector(0, 1, 1)), GetVectorNoise(NoiseTable, StartLocation + FIntVector(1, 1, 1)), AlphaLocation.X);

	return FMath::Lerp(FMath::Lerp(Down, DownY, AlphaLocation.Y), FMath::Lerp(Up, UpY, AlphaLocation.Y), AlphaLocation.Z);
}

FVector ULFPNoiseLibrary::GetLerpDirectionNoise( const FLFPNoiseTable& NoiseTable , const FVector& Location )
{
	const FIntVector StartLocation = FIntVector(FMath::TruncToInt(Location.X), FMath::TruncToInt(Location.Y), FMath::TruncToInt(Location.Z));
	const FVector    AlphaLocation = FVector(Location.X - StartLocation.X, Location.Y - StartLocation.Y, Location.Z - StartLocation.Z);

	const FVector Down  = FMath::Lerp(GetDirectionNoise(NoiseTable, StartLocation + FIntVector(0, 0, 0)), GetDirectionNoise(NoiseTable, StartLocation + FIntVector(1, 0, 0)), AlphaLocation.X);
	const FVector DownY = FMath::Lerp(GetDirectionNoise(NoiseTable, StartLocation + FIntVector(0, 1, 0)), GetDirectionNoise(NoiseTable, StartLocation + FIntVector(1, 1, 0)), AlphaLocation.X);
	const FVector Up    = FMath::Lerp(GetDirectionNoise(NoiseTable, StartLocation + FIntVector(0, 0, 1)), GetDirectionNoise(NoiseTable, StartLocation + FIntVector(1, 0, 1)), AlphaLocation.X);
	const FVector UpY   = FMath::Lerp(GetDirectionNoise(NoiseTable, StartLocation + FIntVector(0, 1, 1)), GetDirectionNoise(NoiseTable, StartLocation + FIntVector(1, 1, 1)), AlphaLocation.X);

	return FMath::Lerp(FMath::Lerp(Down, DownY, AlphaLocation.Y), FMath::Lerp(Up, UpY, AlphaLocation.Y), AlphaLocation.Z);
}

float ULFPNoiseLibrary::MixLerpNoise( const FLFPNoiseTable& NoiseTable , const FVector& Location , const TArray< FLFPNoiseMixTable >& MixTable )
{
	float ReturnValue = 0.0f;

	for ( const FLFPNoiseMixTable& Value : MixTable )
	{
		ReturnValue += GetLerpNoise(NoiseTable, Location * Value.Multiply) * Value.MixValue;
	}

	return ReturnValue;
}

FVector ULFPNoiseLibrary::MixLerpVector( const FLFPNoiseTable& NoiseTable , const FVector& Location , const TArray< FLFPNoiseMixTable >& MixTable )
{
	FVector ReturnValue = FVector(0.0f);

	for ( const FLFPNoiseMixTable& Value : MixTable )
	{
		ReturnValue += GetLerpVectorNoise(NoiseTable, Location * Value.Multiply) * Value.MixValue;
	}

	return ReturnValue;
}

FVector ULFPNoiseLibrary::MixLerpDirection( const FLFPNoiseTable& NoiseTable , const FVector& Location , const TArray< FLFPNoiseMixTable >& MixTable )
{
	FVector ReturnValue = FVector(0.0f);

	for ( const FLFPNoiseMixTable& Value : MixTable )
	{
		ReturnValue += GetLerpDirectionNoise(NoiseTable, Location * Value.Multiply) * Value.MixValue;
	}

	return ReturnValue;
}

FLFPNearbyVectorData ULFPNoiseLibrary::VectorAlgo( const FLFPNoiseTable& NoiseTable , const FIntVector& CurrentLocation , const FVector& Location , const bool bUseVectorLength , const float ClampRange , const bool bIgnoreZ )
{
	const FVector CurrentNoiseDirection = GetVectorNoise(NoiseTable, CurrentLocation) * ClampRange;
	const FVector CurrentFloatLocation  = FVector(CurrentLocation) + CurrentNoiseDirection;

	if ( bUseVectorLength )
	{
		const FVector LenghtVector = Location - CurrentFloatLocation;

		return FLFPNearbyVectorData(
			LenghtVector.X + LenghtVector.Y + (bIgnoreZ
				                                   ? 0
				                                   : LenghtVector.Y)
			,
			CurrentLocation,
			CurrentNoiseDirection
			);
	}

	return FLFPNearbyVectorData(
		bIgnoreZ
			? FVector::Dist2D(Location, CurrentFloatLocation)
			: FVector::Dist(Location, CurrentFloatLocation)
		,
		CurrentLocation,
		CurrentNoiseDirection
		);
}

FLFPNearbyVectorData ULFPNoiseLibrary::GetNearbySingleVectorNoise( const FLFPNoiseTable& NoiseTable , const FVector& Location , const bool bUseVectorLength , const float ClampRange , const bool bIgnoreZ )
{
	FLFPNearbyVectorData Data;

	const FIntVector GridLocation = FIntVector(FMath::Floor(Location.X), FMath::Floor(Location.Y), FMath::Floor(Location.Z));

	for ( int32 Z =
		      bIgnoreZ
			      ? 0
			      : -1 ;
	      Z <=
	      (bIgnoreZ
		       ? 0
		       : 1) ;
	      Z++ )
	{
		for ( int32 Y = -1 ; Y <= 1 ; Y++ )
		{
			for ( int32 X = -1 ; X <= 1 ; X++ )
			{
				const FIntVector CurrentLocation = GridLocation + FIntVector(X, Y, Z);

				const FLFPNearbyVectorData CurrentData = VectorAlgo(NoiseTable, CurrentLocation, Location, bUseVectorLength, ClampRange, bIgnoreZ);

				if ( Data.NearbyDistance < 0 || CurrentData < Data )
				{
					Data = CurrentData;
				}
			}
		}
	}

	return Data;
}

float ULFPNoiseLibrary::GetNearbyVectorDistance( const FLFPNoiseTable& NoiseTable , const FVector& Location , const bool bCompareSecondary , const bool bUseVectorLength , const float ClampRange , const bool bIgnoreZ )
{
	FLFPNearbyVectorData DataA , DataB;

	const FIntVector GridLocation = FIntVector(FMath::Floor(Location.X), FMath::Floor(Location.Y), FMath::Floor(Location.Z));

	for ( int32 Z =
		      bIgnoreZ
			      ? 0
			      : -1 ;
	      Z <=
	      (bIgnoreZ
		       ? 0
		       : 1) ;
	      Z++ )
	{
		for ( int32 Y = -1 ; Y <= 1 ; Y++ )
		{
			for ( int32 X = -1 ; X <= 1 ; X++ )
			{
				const FIntVector CurrentLocation = GridLocation + FIntVector(X, Y, Z);

				const FLFPNearbyVectorData CurrentData = VectorAlgo(NoiseTable, CurrentLocation, Location, bUseVectorLength, ClampRange, bIgnoreZ);

				if ( DataA.NearbyDistance < 0 || CurrentData < DataA )
				{
					DataB = DataA;
					DataA = CurrentData;
				}

			}
		}
	}

	return bCompareSecondary
		       ? FMath::Abs(DataA.NearbyDistance - DataB.NearbyDistance)
		       : DataA.NearbyDistance;
}

void ULFPNoiseLibrary::GetNearbyVectorNoise( TArray< FLFPNearbyVectorData >& ReturnData , const FLFPNoiseTable& NoiseTable , const FVector& Location , const bool bUseVectorLength , const float ClampRange , const bool bIgnoreZ )
{
	const FIntVector GridLocation = FIntVector(FMath::Floor(Location.X), FMath::Floor(Location.Y), FMath::Floor(Location.Z));

	ReturnData.Empty(27);

	for ( int32 Z =
		      bIgnoreZ
			      ? 0
			      : -1 ;
	      Z <=
	      (bIgnoreZ
		       ? 0
		       : 1) ;
	      Z++ )
	{
		for ( int32 Y = -1 ; Y <= 1 ; Y++ )
		{
			for ( int32 X = -1 ; X <= 1 ; X++ )
			{
				const FIntVector           CurrentLocation = GridLocation + FIntVector(X, Y, Z);
				const FLFPNearbyVectorData CurrentData     = VectorAlgo(NoiseTable, CurrentLocation, Location, bUseVectorLength, ClampRange, bIgnoreZ);

				ReturnData.Add(CurrentData);
			}
		}
	}

	ReturnData.Sort();
}
