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

	const FLFPMarchingPartKey TargetKey = PartKeyList.Array()[0];

	const auto BtyeArray = ULohFunctionPluginMarchingLibrary::GenerateBitMatrixNumberTop(TargetKey.ConnectID);

	TArray<FLFPMarchingPartKey> Result;

	for (const uint8 Btye : BtyeArray)
	{
		Result.Add(FLFPMarchingPartKey(Btye, TargetKey.ObjectTag));
	}

	PartKeyList.Empty(4);

	PartKeyList.Append(Result);

	return;
}

