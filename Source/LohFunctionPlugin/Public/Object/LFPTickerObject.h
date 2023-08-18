// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LFPTickerObject.generated.h"

class ULFPIndexTickerComponent;

/**
 * 
 */
UCLASS(Blueprintable)
class LOHFUNCTIONPLUGIN_API ULFPTickerObject : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintNativeEvent)
		void OnExecute(const FIntPoint& TickGroup, const int32 TickIndex, ULFPIndexTickerComponent* Caller) const;
		virtual void OnExecute_Implementation(const FIntPoint& TickGroup, const int32 TickIndex, ULFPIndexTickerComponent* Caller) const {}
};
