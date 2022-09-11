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
