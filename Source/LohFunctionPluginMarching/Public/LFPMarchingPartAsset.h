// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include <LohFunctionPlugin/Public/Components/LFPHashBoxGridComponent.h>
#include "LFPMarchingPartAsset.generated.h"

UCLASS(Blueprintable)
class LOHFUNCTIONPLUGINMARCHING_API ULFPMarchingPartAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LFPMarchingPartAsset | Event")
		void OnGenerate(UObject* Caller, const FTransform& InTransform);
		virtual void OnGenerate_Implementation(UObject* Caller, const FTransform& InTransform) { return; }

protected:

	UFUNCTION(CallInEditor, Category = "LFPMarchingPartAsset | Function")
		void GeneratePartKey();

public:

	UPROPERTY(EditDefaultsOnly, Category = "LFPMarchingPartAsset | Setting")
		TSet<FLFHashBoxGridKey> PartKeyList = TSet<FLFHashBoxGridKey>();

};
