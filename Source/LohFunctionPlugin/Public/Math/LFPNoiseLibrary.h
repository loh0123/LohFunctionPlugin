// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LFPNoiseLibrary.generated.h"


USTRUCT(BlueprintType)
struct FLFPNoiseMixTable
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPNoiseMixTable")
		FVector Multiply = FVector(1.0f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPNoiseMixTable")
		float MixValue = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPNoiseMixTable")
		bool bRoundSourceNoise = false;
};

USTRUCT(BlueprintType)
struct FLFPNoiseTable
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPNoiseTable")
		TArray<float> NoiseData;
};

USTRUCT(BlueprintType)
struct FLFPNearbyVectorData
{
	GENERATED_USTRUCT_BODY()

	FLFPNearbyVectorData() {}
	FLFPNearbyVectorData(const float Dis, const FIntVector Vec, const FVector Point) : NearbyDistance(Dis), NearbyVector(Vec), NearbyPoint(Point) {}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPNearbyVectorData")
		float NearbyDistance = -1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPNearbyVectorData")
		FIntVector NearbyVector = FIntVector(-1);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPNearbyVectorData")
		FVector NearbyPoint = FVector(0);

	FORCEINLINE bool operator<(const FLFPNearbyVectorData& Other) const { return NearbyDistance < Other.NearbyDistance; }
	FORCEINLINE bool operator<(const float& Other) const { return NearbyDistance < Other; }
};

/**
 *
 */
UCLASS(meta = (BlueprintThreadSafe))
class LOHFUNCTIONPLUGIN_API ULFPNoiseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "LFPMathLibrary | Noise")
		static FLFPNoiseTable CreateNoiseTable(const FRandomStream& Seed);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Noise")
		static float GetFloatNoise(const FLFPNoiseTable& NoiseTable, const FIntVector Location, const bool bRoundNoise = false);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Noise")
		static FVector GetVectorNoise(const FLFPNoiseTable& NoiseTable, const FIntVector Location, const bool bRoundNoise = false);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Noise")
		static FVector GetDirectionNoise(const FLFPNoiseTable& NoiseTable, const FIntVector Location, const bool bRoundNoise = false);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Noise")
		static float GetLerpNoise(const FLFPNoiseTable& NoiseTable, const FVector Location, const bool bRoundSourceNoise = false);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Noise")
		static FVector GetLerpVectorNoise(const FLFPNoiseTable& NoiseTable, const FVector Location, const bool bRoundSourceNoise = false);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Noise")
		static FVector GetLerpDirectionNoise(const FLFPNoiseTable& NoiseTable, const FVector Location, const bool bRoundSourceNoise = false);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Noise")
		static float MixLerpNoise(const FLFPNoiseTable& NoiseTable, FVector Location, const TArray<FLFPNoiseMixTable>& MixTable);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Noise")
		static FVector MixLerpVector(const FLFPNoiseTable& NoiseTable, FVector Location, const TArray<FLFPNoiseMixTable>& MixTable);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Noise")
		static FVector MixLerpDirection(const FLFPNoiseTable& NoiseTable, FVector Location, const TArray<FLFPNoiseMixTable>& MixTable);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Noise")
		static FLFPNearbyVectorData GetNearbySingleVectorNoise(const FLFPNoiseTable& NoiseTable, const bool IgnoreZ, const FVector Location, const bool bRoundSourceNoise = false);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Noise")
		static void GetNearbyVectorNoise(const FLFPNoiseTable& NoiseTable, const FVector Location, const bool IgnoreZ, TArray<FLFPNearbyVectorData>& ReturnData, const bool bRoundSourceNoise = false);
};
