// Copyright (c) 2023-2025 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LFPMarchingFunctionLibrary.generated.h"

class ULFPMarchingDataComponent;
class ULFPChunkedTagDataComponent;
/**
 * 
 */
UCLASS()
class LOHFUNCTIONPLUGINMARCHING_API ULFPMarchingFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "LFPMarchingLibrary|ID")
	static bool GetMarchingIDBit( const uint8 MarchingID , const int32 BitIndex );

	UFUNCTION(BlueprintCallable, Category = "LFPMarchingLibrary|ID")
	static void SetMarchingIDBit( uint8& MarchingID , const int32 BitIndex , const bool bNewValue );

	UFUNCTION(BlueprintCallable, Category = "LFPMarchingLibrary|Rotation")
	static uint8 RotateMarchingIDByX( const uint8 MarchingID , const bool bReverse );

	UFUNCTION(BlueprintCallable, Category = "LFPMarchingLibrary|Rotation")
	static uint8 RotateMarchingIDByY( const uint8 MarchingID , const bool bReverse );

	UFUNCTION(BlueprintCallable, Category = "LFPMarchingLibrary|Rotation")
	static uint8 RotateMarchingIDByZ( const uint8 MarchingID , const bool bReverse );

	UFUNCTION(BlueprintCallable, Category = "LFPMarchingLibrary|Rotation")
	static uint8 RotateMarchingID( const uint8 MarchingID , const FIntVector& Rotation );

	UFUNCTION(BlueprintCallable, Category = "LFPMarchingLibrary|Function")
	static uint8 CalculateDualGridMarchingID( const uint8 FullMarchingID , const int32 CalculateIndex );

public:

	UFUNCTION(BlueprintPure, Category = "Marching")
	static FIntVector ToChunkedDataIndex( const ULFPMarchingDataComponent* DataComponent , const FIntVector& GlobalPosition );

	UFUNCTION(BlueprintCallable, Category = "Marching", meta=(AutoCreateRefTerm="IncludeTag, GlobalPosition"))
	static uint8 GetMarchingIDByGlobalPosition( const ULFPMarchingDataComponent* DataComponent , const FIntVector& GlobalPosition , const FGameplayTag& IncludeTag );

	UFUNCTION(BlueprintCallable, Category = "Marching", meta=(AutoCreateRefTerm="IncludeTag, LocalPosition"))
	static uint8 GetMarchingIDByLocalPosition( const ULFPMarchingDataComponent* DataComponent , const FIntVector& LocalPosition , const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& IncludeTag );
};
