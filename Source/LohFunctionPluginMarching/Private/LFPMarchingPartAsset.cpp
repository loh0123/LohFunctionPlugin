// Fill out your copyright notice in the Description page of Project Settings.


#include "LFPMarchingPartAsset.h"
#include "UObject/ObjectSaveContext.h"
#include "LohFunctionPluginMarchingLibrary.h"

FPrimaryAssetId ULFPMarchingPartAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(TEXT("LFPMarchingPartAsset"), GetFName());
}

void ULFPMarchingPartAsset::PreSave(FObjectPreSaveContext ObjectSaveContext)
{
	GeneratePartKey();

	Super::PreSave(ObjectSaveContext);
}

void ULFPMarchingPartAsset::GeneratePartKey()
{
	if (PartKeyList.IsEmpty()) return;

	FLFHashBoxGridKey TargetKey = PartKeyList.Array()[0];

	PartKeyList.Empty();

	for (int32 Index = 0; Index < 4; Index++)
	{
		PartKeyList.Add(TargetKey);

		TargetKey = TargetKey.RotateIDByZ();
	}

	return;
}

