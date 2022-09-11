// MIT License
// 
// Copyright(c) 2022 loh0123
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright noticeand this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
		FVector NearbyPoint;

	FORCEINLINE bool operator<(const FLFPNearbyVectorData& Other) const { return NearbyDistance < Other.NearbyDistance; }
	FORCEINLINE bool operator<(const float& Other) const { return NearbyDistance < Other; }
};

/**
 *
 */
UCLASS()
class LOHFUNCTIONPLUGIN_API ULFPNoiseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "LFPMathLibrary | Noise")
		static FLFPNoiseTable CreateNoiseTable(const FRandomStream& Seed);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Noise")
		static float GetFloatNoise(const FLFPNoiseTable& NoiseTable, const FIntVector Location);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Noise")
		static FVector GetVectorNoise(const FLFPNoiseTable& NoiseTable, const FIntVector Location);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Noise")
		static FVector GetDirectionNoise(const FLFPNoiseTable& NoiseTable, const FIntVector Location);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Noise")
		static float GetLerpNoise(const FLFPNoiseTable& NoiseTable, const FVector Location);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Noise")
		static FVector GetLerpVectorNoise(const FLFPNoiseTable& NoiseTable, const FVector Location);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Noise")
		static FVector GetLerpDirectionNoise(const FLFPNoiseTable& NoiseTable, const FVector Location);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Noise")
		static float MixLerpNoise(const FLFPNoiseTable& NoiseTable, FVector Location, const TArray<FLFPNoiseMixTable>& MixTable);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Noise")
		static FVector MixLerpVector(const FLFPNoiseTable& NoiseTable, FVector Location, const TArray<FLFPNoiseMixTable>& MixTable);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Noise")
		static FVector MixLerpDirection(const FLFPNoiseTable& NoiseTable, FVector Location, const TArray<FLFPNoiseMixTable>& MixTable);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Noise")
		static FLFPNearbyVectorData GetNearbySingleVectorNoise(const FLFPNoiseTable& NoiseTable, const bool IgnoreZ, const FVector Location);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Noise")
		static void GetNearbyVectorNoise(const FLFPNoiseTable& NoiseTable, const FVector Location, const bool IgnoreZ, TArray<FLFPNearbyVectorData>& ReturnData);
};
