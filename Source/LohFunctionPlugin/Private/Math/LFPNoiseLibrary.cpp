// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#include "Math/LFPNoiseLibrary.h"
#include "Kismet/KismetMathLibrary.h"

FLFPNoiseTable ULFPNoiseLibrary::CreateNoiseTable(const FRandomStream& Seed)
{
	FLFPNoiseTable NewTable;

	NewTable.NoiseData.SetNum(256);

	for (float& Item : NewTable.NoiseData)
	{
		Item = Seed.FRand();
	}

	return NewTable;
}

float ULFPNoiseLibrary::GetFloatNoise(const FLFPNoiseTable& NoiseTable, const FIntVector Location, const bool bRoundNoise)
{
	if (NoiseTable.NoiseData.Num() != 256)
	{
		return 0.0f;
	}

	const float a = NoiseTable.NoiseData[(Location.X < 0 ? 256 - FMath::Abs(Location.X) : Location.X) % 256];
	const float b = NoiseTable.NoiseData[((Location.Y < 0 ? 256 - FMath::Abs(Location.Y) : Location.Y) + 64) % 256];
	const float c = NoiseTable.NoiseData[((Location.Z < 0 ? 256 - FMath::Abs(Location.Z) : Location.Z) + 128) % 256];

	const float Result = NoiseTable.NoiseData[((int32)((a + b + c) * 256)) % 256];

	return bRoundNoise ? FMath::RoundToFloat(Result) : Result;
}

FVector ULFPNoiseLibrary::GetVectorNoise(const FLFPNoiseTable& NoiseTable, const FIntVector Location, const bool bRoundNoise)
{
	if (NoiseTable.NoiseData.Num() != 256)
	{
		return FVector(0, 0, 0);
	}

	float a = NoiseTable.NoiseData[(Location.X < 0 ? 256 - FMath::Abs(Location.X) : Location.X) % 256];
	float b = NoiseTable.NoiseData[((Location.Y < 0 ? 256 - FMath::Abs(Location.Y) : Location.Y) + 64) % 256];
	float c = NoiseTable.NoiseData[((Location.Z < 0 ? 256 - FMath::Abs(Location.Z) : Location.Z) + 128) % 256];

	const FVector Result = FVector(NoiseTable.NoiseData[((int32)((a + b + c) * 256)) % 256], NoiseTable.NoiseData[((int32)((a + b + c) * 256) + 16) % 256], NoiseTable.NoiseData[((int32)((a + b + c) * 256) + 32) % 256]);

	return bRoundNoise ? FVector(FMath::RoundToFloat(Result.X), FMath::RoundToFloat(Result.Y), FMath::RoundToFloat(Result.Z)) : Result;
}

FVector ULFPNoiseLibrary::GetDirectionNoise(const FLFPNoiseTable& NoiseTable, const FIntVector Location, const bool bRoundNoise)
{
	if (NoiseTable.NoiseData.Num() != 256)
	{
		return FVector(0, 0, 0);
	}

	float a = NoiseTable.NoiseData[(Location.X < 0 ? 256 - FMath::Abs(Location.X) : Location.X) % 256];
	float b = NoiseTable.NoiseData[((Location.Y < 0 ? 256 - FMath::Abs(Location.Y) : Location.Y) + 64) % 256];
	float c = NoiseTable.NoiseData[((Location.Z < 0 ? 256 - FMath::Abs(Location.Z) : Location.Z) + 128) % 256];

	const FRotator Result = FRotator(NoiseTable.NoiseData[((int32)((a + b + c) * 256)) % 256] * 360, NoiseTable.NoiseData[((int32)((a + b + c) * 256) + 16) % 256] * 360, NoiseTable.NoiseData[((int32)((a + b + c) * 256) + 32) % 256] * 360);

	return
		UKismetMathLibrary::GetForwardVector(bRoundNoise ? FRotator(
			FMath::RoundToFloat(Result.Pitch / 90) * 90, 
			FMath::RoundToFloat(Result.Yaw / 90) * 90, 
			FMath::RoundToFloat(Result.Roll / 90) * 90
		)
		:
		Result
		);
}

float ULFPNoiseLibrary::GetLerpNoise(const FLFPNoiseTable& NoiseTable, const FVector Location, const bool bRoundSourceNoise)
{
	FIntVector StartLocation = FIntVector(FMath::TruncToInt(Location.X), FMath::TruncToInt(Location.Y), FMath::TruncToInt(Location.Z));
	FVector AlphaLocation = FVector(Location.X - StartLocation.X, Location.Y - StartLocation.Y, Location.Z - StartLocation.Z);

	float Down =	FMath::Lerp(GetFloatNoise(NoiseTable, StartLocation + FIntVector(0, 0, 0), bRoundSourceNoise), GetFloatNoise(NoiseTable, StartLocation + FIntVector(1, 0, 0), bRoundSourceNoise), AlphaLocation.X);
	float DownY =	FMath::Lerp(GetFloatNoise(NoiseTable, StartLocation + FIntVector(0, 1, 0), bRoundSourceNoise), GetFloatNoise(NoiseTable, StartLocation + FIntVector(1, 1, 0), bRoundSourceNoise), AlphaLocation.X);
	float Up =		FMath::Lerp(GetFloatNoise(NoiseTable, StartLocation + FIntVector(0, 0, 1), bRoundSourceNoise), GetFloatNoise(NoiseTable, StartLocation + FIntVector(1, 0, 1), bRoundSourceNoise), AlphaLocation.X);
	float UpY =		FMath::Lerp(GetFloatNoise(NoiseTable, StartLocation + FIntVector(0, 1, 1), bRoundSourceNoise), GetFloatNoise(NoiseTable, StartLocation + FIntVector(1, 1, 1), bRoundSourceNoise), AlphaLocation.X);

	return FMath::Lerp(FMath::Lerp(Down, DownY, AlphaLocation.Y), FMath::Lerp(Up, UpY, AlphaLocation.Y), AlphaLocation.Z);
}

FVector ULFPNoiseLibrary::GetLerpVectorNoise(const FLFPNoiseTable& NoiseTable, const FVector Location, const bool bRoundSourceNoise)
{
	FIntVector StartLocation = FIntVector(FMath::TruncToInt(Location.X), FMath::TruncToInt(Location.Y), FMath::TruncToInt(Location.Z));
	FVector AlphaLocation = FVector(Location.X - StartLocation.X, Location.Y - StartLocation.Y, Location.Z - StartLocation.Z);

	FVector Down =	FMath::Lerp(GetVectorNoise(NoiseTable, StartLocation + FIntVector(0, 0, 0), bRoundSourceNoise), GetVectorNoise(NoiseTable, StartLocation + FIntVector(1, 0, 0), bRoundSourceNoise), AlphaLocation.X);
	FVector DownY = FMath::Lerp(GetVectorNoise(NoiseTable, StartLocation + FIntVector(0, 1, 0), bRoundSourceNoise), GetVectorNoise(NoiseTable, StartLocation + FIntVector(1, 1, 0), bRoundSourceNoise), AlphaLocation.X);
	FVector Up =	FMath::Lerp(GetVectorNoise(NoiseTable, StartLocation + FIntVector(0, 0, 1), bRoundSourceNoise), GetVectorNoise(NoiseTable, StartLocation + FIntVector(1, 0, 1), bRoundSourceNoise), AlphaLocation.X);
	FVector UpY =	FMath::Lerp(GetVectorNoise(NoiseTable, StartLocation + FIntVector(0, 1, 1), bRoundSourceNoise), GetVectorNoise(NoiseTable, StartLocation + FIntVector(1, 1, 1), bRoundSourceNoise), AlphaLocation.X);

	return FMath::Lerp(FMath::Lerp(Down, DownY, AlphaLocation.Y), FMath::Lerp(Up, UpY, AlphaLocation.Y), AlphaLocation.Z);
}

FVector ULFPNoiseLibrary::GetLerpDirectionNoise(const FLFPNoiseTable& NoiseTable, const FVector Location, const bool bRoundSourceNoise)
{
	FIntVector StartLocation = FIntVector(FMath::TruncToInt(Location.X), FMath::TruncToInt(Location.Y), FMath::TruncToInt(Location.Z));
	FVector AlphaLocation = FVector(Location.X - StartLocation.X, Location.Y - StartLocation.Y, Location.Z - StartLocation.Z);

	FVector Down =	FMath::Lerp(GetDirectionNoise(NoiseTable, StartLocation + FIntVector(0, 0, 0), bRoundSourceNoise), GetDirectionNoise(NoiseTable, StartLocation + FIntVector(1, 0, 0), bRoundSourceNoise), AlphaLocation.X);
	FVector DownY = FMath::Lerp(GetDirectionNoise(NoiseTable, StartLocation + FIntVector(0, 1, 0), bRoundSourceNoise), GetDirectionNoise(NoiseTable, StartLocation + FIntVector(1, 1, 0), bRoundSourceNoise), AlphaLocation.X);
	FVector Up =	FMath::Lerp(GetDirectionNoise(NoiseTable, StartLocation + FIntVector(0, 0, 1), bRoundSourceNoise), GetDirectionNoise(NoiseTable, StartLocation + FIntVector(1, 0, 1), bRoundSourceNoise), AlphaLocation.X);
	FVector UpY =	FMath::Lerp(GetDirectionNoise(NoiseTable, StartLocation + FIntVector(0, 1, 1), bRoundSourceNoise), GetDirectionNoise(NoiseTable, StartLocation + FIntVector(1, 1, 1), bRoundSourceNoise), AlphaLocation.X);

	return FMath::Lerp(FMath::Lerp(Down, DownY, AlphaLocation.Y), FMath::Lerp(Up, UpY, AlphaLocation.Y), AlphaLocation.Z);
}

float ULFPNoiseLibrary::MixLerpNoise(const FLFPNoiseTable& NoiseTable, FVector Location, const TArray<FLFPNoiseMixTable>& MixTable)
{
	float ReturnValue = 0.0f;

	for (const FLFPNoiseMixTable& Value : MixTable)
	{
		ReturnValue += GetLerpNoise(NoiseTable, Location * Value.Multiply, Value.bRoundSourceNoise) * Value.MixValue;
	}

	return ReturnValue;
}

FVector ULFPNoiseLibrary::MixLerpVector(const FLFPNoiseTable& NoiseTable, FVector Location, const TArray<FLFPNoiseMixTable>& MixTable)
{
	FVector ReturnValue = FVector(0.0f);

	for (const FLFPNoiseMixTable& Value : MixTable)
	{
		ReturnValue += GetLerpVectorNoise(NoiseTable, Location * Value.Multiply, Value.bRoundSourceNoise) * Value.MixValue;
	}

	return ReturnValue;
}

FVector ULFPNoiseLibrary::MixLerpDirection(const FLFPNoiseTable& NoiseTable, FVector Location, const TArray<FLFPNoiseMixTable>& MixTable)
{
	FVector ReturnValue = FVector(0.0f);

	for (const FLFPNoiseMixTable& Value : MixTable)
	{
		ReturnValue += GetLerpDirectionNoise(NoiseTable, Location * Value.Multiply, Value.bRoundSourceNoise) * Value.MixValue;
	}

	return ReturnValue;
}

FLFPNearbyVectorData ULFPNoiseLibrary::GetNearbySingleVectorNoise(const FLFPNoiseTable& NoiseTable, const bool IgnoreZ, const FVector Location, const bool bRoundSourceNoise)
{
	FLFPNearbyVectorData Data;

	FIntVector GridLocation = FIntVector(FMath::Floor(Location.X), FMath::Floor(Location.Y), FMath::Floor(Location.Z));

	FVector Local = Location - FVector(GridLocation);

	for (int32 Z = (IgnoreZ ? 0 : -1); Z <= (IgnoreZ ? 0 : 1); Z++)
	for (int32 Y = -1; Y <= 1; Y++)
	for (int32 X = -1; X <= 1; X++)
	{
		FIntVector CurrentLocation = GridLocation + FIntVector(X, Y, Z);
		FVector CurrentNoiseDirection = GetVectorNoise(NoiseTable, CurrentLocation, bRoundSourceNoise);

		FLFPNearbyVectorData CurrentData(
			IgnoreZ ? FVector::Dist2D(Location, FVector(CurrentLocation) + CurrentNoiseDirection) : FVector::Dist(Location, FVector(CurrentLocation) + CurrentNoiseDirection),
			CurrentLocation,
			CurrentNoiseDirection
		);

		if (Data.NearbyDistance < 0 || CurrentData < Data)
		{
			Data = CurrentData;
		}
	}

	return Data;
}

void ULFPNoiseLibrary::GetNearbyVectorNoise(const FLFPNoiseTable& NoiseTable, const FVector Location, const bool IgnoreZ, TArray<FLFPNearbyVectorData>& ReturnData, const bool bRoundSourceNoise)
{
	FIntVector GridLocation = FIntVector(FMath::Floor(Location.X), FMath::Floor(Location.Y), FMath::Floor(Location.Z));

	FVector Local = Location - FVector(GridLocation);

	ReturnData.Empty(27);

	for (int32 Z = (IgnoreZ ? 0 : -1); Z <= (IgnoreZ ? 0 : 1); Z++)
	for (int32 Y = -1; Y <= 1; Y++)
	for (int32 X = -1; X <= 1; X++)
	{
		FIntVector CurrentLocation = GridLocation + FIntVector(X, Y, Z);
		FVector CurrentNoiseDirection = GetVectorNoise(NoiseTable, CurrentLocation, bRoundSourceNoise);

		ReturnData.Add(FLFPNearbyVectorData(
			IgnoreZ ? FVector::Dist2D(Location, FVector(CurrentLocation) + CurrentNoiseDirection) : FVector::Dist(Location, FVector(CurrentLocation) + CurrentNoiseDirection),
			CurrentLocation,
			CurrentNoiseDirection
		));
	}

	ReturnData.Sort();

	return;
}
