// Copyright by Loh Zhi Kang

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

float ULFPNoiseLibrary::GetFloatNoise(const FLFPNoiseTable& NoiseTable, const FIntVector Location)
{
	if (NoiseTable.NoiseData.Num() != 256)
	{
		return 0.0f;
	}

	float a = NoiseTable.NoiseData[Location.X % 256];
	float b = NoiseTable.NoiseData[(Location.Y + 64) % 256];
	float c = NoiseTable.NoiseData[(Location.Z + 128) % 256];

	return NoiseTable.NoiseData[((int32)((a + b + c) * 256)) % 256];
}

FVector ULFPNoiseLibrary::GetVectorNoise(const FLFPNoiseTable& NoiseTable, const FIntVector Location)
{
	if (NoiseTable.NoiseData.Num() != 256)
	{
		return FVector(0, 0, 0);
	}

	float a = NoiseTable.NoiseData[Location.X % 256];
	float b = NoiseTable.NoiseData[(Location.Y + 64) % 256];
	float c = NoiseTable.NoiseData[(Location.Z + 128) % 256];

	return FVector(NoiseTable.NoiseData[((int32)((a + b + c) * 256)) % 256], NoiseTable.NoiseData[((int32)((a + b + c) * 256) + 16) % 256], NoiseTable.NoiseData[((int32)((a + b + c) * 256) + 32) % 256]);
}

FVector ULFPNoiseLibrary::GetDirectionNoise(const FLFPNoiseTable& NoiseTable, const FIntVector Location)
{
	if (NoiseTable.NoiseData.Num() != 256)
	{
		return FVector(0, 0, 0);
	}

	float a = NoiseTable.NoiseData[Location.X % 256];
	float b = NoiseTable.NoiseData[(Location.Y + 64) % 256];
	float c = NoiseTable.NoiseData[(Location.Z + 128) % 256];

	return UKismetMathLibrary::GetForwardVector(FRotator(NoiseTable.NoiseData[((int32)((a + b + c) * 256)) % 256] * 360, NoiseTable.NoiseData[((int32)((a + b + c) * 256) + 16) % 256] * 360, NoiseTable.NoiseData[((int32)((a + b + c) * 256) + 32) % 256] * 360));
}

float ULFPNoiseLibrary::GetLerpNoise(const FLFPNoiseTable& NoiseTable, const FVector Location)
{
	FIntVector StartLocation = FIntVector(FMath::TruncToInt(Location.X), FMath::TruncToInt(Location.Y), FMath::TruncToInt(Location.Z));
	FVector AlphaLocation = FVector(Location.X - StartLocation.X, Location.Y - StartLocation.Y, Location.Z - StartLocation.Z);

	float Down = FMath::Lerp(GetFloatNoise(NoiseTable, StartLocation + FIntVector(0, 0, 0)), GetFloatNoise(NoiseTable, StartLocation + FIntVector(1, 0, 0)), AlphaLocation.X);
	float DownY = FMath::Lerp(GetFloatNoise(NoiseTable, StartLocation + FIntVector(0, 1, 0)), GetFloatNoise(NoiseTable, StartLocation + FIntVector(1, 1, 0)), AlphaLocation.X);
	float Up = FMath::Lerp(GetFloatNoise(NoiseTable, StartLocation + FIntVector(0, 0, 1)), GetFloatNoise(NoiseTable, StartLocation + FIntVector(1, 0, 1)), AlphaLocation.X);
	float UpY = FMath::Lerp(GetFloatNoise(NoiseTable, StartLocation + FIntVector(0, 1, 1)), GetFloatNoise(NoiseTable, StartLocation + FIntVector(1, 1, 1)), AlphaLocation.X);

	return FMath::Lerp(FMath::Lerp(Down, DownY, AlphaLocation.Y), FMath::Lerp(Up, UpY, AlphaLocation.Y), AlphaLocation.Z);
}

FVector ULFPNoiseLibrary::GetLerpVectorNoise(const FLFPNoiseTable& NoiseTable, const FVector Location)
{
	FIntVector StartLocation = FIntVector(FMath::TruncToInt(Location.X), FMath::TruncToInt(Location.Y), FMath::TruncToInt(Location.Z));
	FVector AlphaLocation = FVector(Location.X - StartLocation.X, Location.Y - StartLocation.Y, Location.Z - StartLocation.Z);

	FVector Down = FMath::Lerp(GetVectorNoise(NoiseTable, StartLocation + FIntVector(0, 0, 0)), GetVectorNoise(NoiseTable, StartLocation + FIntVector(1, 0, 0)), AlphaLocation.X);
	FVector DownY = FMath::Lerp(GetVectorNoise(NoiseTable, StartLocation + FIntVector(0, 1, 0)), GetVectorNoise(NoiseTable, StartLocation + FIntVector(1, 1, 0)), AlphaLocation.X);
	FVector Up = FMath::Lerp(GetVectorNoise(NoiseTable, StartLocation + FIntVector(0, 0, 1)), GetVectorNoise(NoiseTable, StartLocation + FIntVector(1, 0, 1)), AlphaLocation.X);
	FVector UpY = FMath::Lerp(GetVectorNoise(NoiseTable, StartLocation + FIntVector(0, 1, 1)), GetVectorNoise(NoiseTable, StartLocation + FIntVector(1, 1, 1)), AlphaLocation.X);

	return FMath::Lerp(FMath::Lerp(Down, DownY, AlphaLocation.Y), FMath::Lerp(Up, UpY, AlphaLocation.Y), AlphaLocation.Z);
}

FVector ULFPNoiseLibrary::GetLerpDirectionNoise(const FLFPNoiseTable& NoiseTable, const FVector Location)
{
	FIntVector StartLocation = FIntVector(FMath::TruncToInt(Location.X), FMath::TruncToInt(Location.Y), FMath::TruncToInt(Location.Z));
	FVector AlphaLocation = FVector(Location.X - StartLocation.X, Location.Y - StartLocation.Y, Location.Z - StartLocation.Z);

	FVector Down = FMath::Lerp(GetDirectionNoise(NoiseTable, StartLocation + FIntVector(0, 0, 0)), GetDirectionNoise(NoiseTable, StartLocation + FIntVector(1, 0, 0)), AlphaLocation.X);
	FVector DownY = FMath::Lerp(GetDirectionNoise(NoiseTable, StartLocation + FIntVector(0, 1, 0)), GetDirectionNoise(NoiseTable, StartLocation + FIntVector(1, 1, 0)), AlphaLocation.X);
	FVector Up = FMath::Lerp(GetDirectionNoise(NoiseTable, StartLocation + FIntVector(0, 0, 1)), GetDirectionNoise(NoiseTable, StartLocation + FIntVector(1, 0, 1)), AlphaLocation.X);
	FVector UpY = FMath::Lerp(GetDirectionNoise(NoiseTable, StartLocation + FIntVector(0, 1, 1)), GetDirectionNoise(NoiseTable, StartLocation + FIntVector(1, 1, 1)), AlphaLocation.X);

	return FMath::Lerp(FMath::Lerp(Down, DownY, AlphaLocation.Y), FMath::Lerp(Up, UpY, AlphaLocation.Y), AlphaLocation.Z);
}

float ULFPNoiseLibrary::MixLerpNoise(const FLFPNoiseTable& NoiseTable, FVector Location, const TArray<FLFPNoiseMixTable>& MixTable)
{
	float ReturnValue = 0.0f;

	for (const FLFPNoiseMixTable& Value : MixTable)
	{
		ReturnValue += GetLerpNoise(NoiseTable, Location * Value.Multiply) * Value.MixValue;
	}

	return ReturnValue;
}

FVector ULFPNoiseLibrary::MixLerpVector(const FLFPNoiseTable& NoiseTable, FVector Location, const TArray<FLFPNoiseMixTable>& MixTable)
{
	FVector ReturnValue = FVector(0.0f);

	for (const FLFPNoiseMixTable& Value : MixTable)
	{
		ReturnValue += GetLerpVectorNoise(NoiseTable, Location * Value.Multiply) * Value.MixValue;
	}

	return ReturnValue;
}

FVector ULFPNoiseLibrary::MixLerpDirection(const FLFPNoiseTable& NoiseTable, FVector Location, const TArray<FLFPNoiseMixTable>& MixTable)
{
	FVector ReturnValue = FVector(0.0f);

	for (const FLFPNoiseMixTable& Value : MixTable)
	{
		ReturnValue += GetLerpDirectionNoise(NoiseTable, Location * Value.Multiply) * Value.MixValue;
	}

	return ReturnValue;
}
