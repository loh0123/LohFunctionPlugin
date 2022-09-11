// Copyright (c) 2022 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LFPGridLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LOHFUNCTIONPLUGIN_API ULFPGridLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		static bool IsLocationValid(const FIntVector& Location, const FIntVector& GridSize);

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		static bool IsOnGridEdge(const FIntVector& Location, const FIntVector& GridSize);
	
	UFUNCTION(BlueprintPure, Category = "LFPGridLibrary")
		static int32 GridLocationToIndex(const FIntVector& Location, const FIntVector& GridSize);

	UFUNCTION(BlueprintCallable, Category = "LFPGridLibrary")
		static TArray<int32> GridLocationsToIndex(const TArray<FIntVector>& GridLocations, const FIntVector Offset, const FIntVector& GridSize);

	UFUNCTION(BlueprintPure, Category = "LFPGridLibrary")
		static FIntVector IndexToGridLocation(const int32& Index, const FIntVector& GridSize);

	UFUNCTION(BlueprintCallable, Category = "LFPGridLibrary")
		static TArray<FIntVector> IndexsToGridLocation(const TArray<int32>& Indexs, const int32 Offset, const FIntVector& GridSize);


	UFUNCTION(BlueprintCallable, Category = "LFPGridLibrary")
		static TArray<int32> SectionGridIndex(const FIntVector SectionSize, const TSet<int32>& IgnoreIndexs, const FIntVector& GridSize);

	UFUNCTION(BlueprintCallable, Category = "LFPGridLibrary")
		static TArray<int32> RandomSectionGridIndex(const int32 Amount, const FIntVector SectionSize, const TSet<int32>& IgnoreIndexs, const FRandomStream& Seed, const FIntVector& GridSize);


	UFUNCTION(BlueprintCallable, Category = "LFPGridLibrary")
		static TArray<int32> GetGridAreaIndex(const int32 Index, const FIntVector Offset, const FIntVector AreaSize, const FIntVector& GridSize);
};
