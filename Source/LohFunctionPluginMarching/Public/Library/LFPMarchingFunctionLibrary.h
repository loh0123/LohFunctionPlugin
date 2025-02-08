// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LFPMarchingFunctionLibrary.generated.h"

class ULFPChunkedTagDataComponent;
/**
 * 
 */
UCLASS()
class LOHFUNCTIONPLUGINMARCHING_API ULFPMarchingFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Marching")
	static FIntVector GetRegionChunkAndDataIndex( const FIntVector& Position , const FIntVector& RegionSize , const FIntVector& ChuckSize , const FIntVector& DataSize );

	UFUNCTION(BlueprintCallable, Category = "Marching")
	static uint8 GetMarchingIDByValidTag( const ULFPChunkedTagDataComponent* DataComponent , const FIntVector& Position , const FIntVector& RegionSize , const FIntVector& ChuckSize , const FIntVector& DataSize );

};
