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
		void OnScheduledExecute(const FIntPoint& TickGroup, const int32 TickIndex, ULFPIndexTickerComponent* Caller) const;
		virtual void OnScheduledExecute_Implementation(const FIntPoint& TickGroup, const int32 TickIndex, ULFPIndexTickerComponent* Caller) const {}

	UFUNCTION(BlueprintNativeEvent)
		void OnRandomExecute(const FIntPoint& TickGroup, const int32 TickIndex, ULFPIndexTickerComponent* Caller) const;
		virtual void OnRandomExecute_Implementation(const FIntPoint& TickGroup, const int32 TickIndex, ULFPIndexTickerComponent* Caller) const {}
};
