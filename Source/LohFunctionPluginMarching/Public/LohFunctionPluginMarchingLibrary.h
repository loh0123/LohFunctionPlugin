// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <LohFunctionPlugin/Public/Components/LFPHashBoxGridComponent.h>
#include "LohFunctionPluginMarchingLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LOHFUNCTIONPLUGINMARCHING_API ULohFunctionPluginMarchingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginMarchingLibrary | Function")
		static TMap<FLFHashBoxGridKey, class ULFPMarchingPartAsset*> GenerateMarchingMap();
};
