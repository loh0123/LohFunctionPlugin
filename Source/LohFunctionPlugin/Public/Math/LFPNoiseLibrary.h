// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LFPNoiseLibrary.generated.h"


USTRUCT(BlueprintType)
struct FLFPNoiseMixTable
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector Multiply = FVector(1.0f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MixValue = 1.0f;
};

USTRUCT(BlueprintType)
struct FLFPNoiseTable
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<float> NoiseData;
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

	UFUNCTION(BlueprintCallable, Category = "LFPMathLibrary | Noise")
		static float GetFloatNoise(const FLFPNoiseTable& NoiseTable, const FIntVector Location);

	UFUNCTION(BlueprintCallable, Category = "LFPMathLibrary | Noise")
		static FVector GetVectorNoise(const FLFPNoiseTable& NoiseTable, const FIntVector Location);

	UFUNCTION(BlueprintCallable, Category = "LFPMathLibrary | Noise")
		static FVector GetDirectionNoise(const FLFPNoiseTable& NoiseTable, const FIntVector Location);

	UFUNCTION(BlueprintCallable, Category = "LFPMathLibrary | Noise")
		static float GetLerpNoise(const FLFPNoiseTable& NoiseTable, const FVector Location);

	UFUNCTION(BlueprintCallable, Category = "LFPMathLibrary | Noise")
		static FVector GetLerpVectorNoise(const FLFPNoiseTable& NoiseTable, const FVector Location);

	UFUNCTION(BlueprintCallable, Category = "LFPMathLibrary | Noise")
		static FVector GetLerpDirectionNoise(const FLFPNoiseTable& NoiseTable, const FVector Location);

	UFUNCTION(BlueprintCallable, Category = "LFPMathLibrary | Noise")
		static float MixLerpNoise(const FLFPNoiseTable& NoiseTable, FVector Location, const TArray<FLFPNoiseMixTable>& MixTable);

	UFUNCTION(BlueprintCallable, Category = "LFPMathLibrary | Noise")
		static FVector MixLerpVector(const FLFPNoiseTable& NoiseTable, FVector Location, const TArray<FLFPNoiseMixTable>& MixTable);

	UFUNCTION(BlueprintCallable, Category = "LFPMathLibrary | Noise")
		static FVector MixLerpDirection(const FLFPNoiseTable& NoiseTable, FVector Location, const TArray<FLFPNoiseMixTable>& MixTable);
};
