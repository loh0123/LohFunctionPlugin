// Fill out your copyright notice in the Description page of Project Settings.


#include "LohFunctionPluginMarchingLibrary.h"
#include "Engine/AssetManager.h"
#include "LFPMarchingPartAsset.h"

TMap<FLFHashBoxGridKey, class ULFPMarchingPartAsset*> ULohFunctionPluginMarchingLibrary::GenerateMarchingMap()
{
	TArray<UObject*> AssetList;

	TArray<FPrimaryAssetId> PrimaryAssetIdList;

	UAssetManager& AssetmanagerPtr = UAssetManager::Get();

	AssetmanagerPtr.GetPrimaryAssetIdList(TEXT("LFPMarchingPartAsset"), PrimaryAssetIdList);

	AssetmanagerPtr.LoadPrimaryAssets(PrimaryAssetIdList)->WaitUntilComplete();

	AssetmanagerPtr.GetPrimaryAssetObjectList(TEXT("LFPMarchingPartAsset"), AssetList);

	TMap<FLFHashBoxGridKey, ULFPMarchingPartAsset*> Result;

	for (UObject* Asset : AssetList)
	{
		ULFPMarchingPartAsset* PartAsset = Cast<ULFPMarchingPartAsset>(Asset);

		if (IsValid(PartAsset) == false) continue;

		for (const auto& PartKey : PartAsset->PartKeyList)
		{
			Result.Add(PartKey, PartAsset);
		}
	}

	return Result;
}
