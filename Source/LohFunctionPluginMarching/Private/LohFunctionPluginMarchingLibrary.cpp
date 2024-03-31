// Fill out your copyright notice in the Description page of Project Settings.


#include "LohFunctionPluginMarchingLibrary.h"
#include "Engine/AssetManager.h"
#include "LFPMarchingPartAsset.h"

TMap<FLFPMarchingPartKey, class ULFPMarchingPartAsset*> ULohFunctionPluginMarchingLibrary::GenerateMarchingMap()
{
	TArray<UObject*> AssetList;

	TArray<FPrimaryAssetId> PrimaryAssetIdList;

	UAssetManager& AssetmanagerPtr = UAssetManager::Get();

	AssetmanagerPtr.GetPrimaryAssetIdList(TEXT("LFPMarchingPartAsset"), PrimaryAssetIdList);

	AssetmanagerPtr.LoadPrimaryAssets(PrimaryAssetIdList)->WaitUntilComplete();

	AssetmanagerPtr.GetPrimaryAssetObjectList(TEXT("LFPMarchingPartAsset"), AssetList);

	TMap<FLFPMarchingPartKey, ULFPMarchingPartAsset*> Result;

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

TArray<uint8> ULohFunctionPluginMarchingLibrary::GenerateBitMatrixNumberTop(const uint8 BitList)
{
	uint32 EditableList = BitList;

	const FIntPoint SwapList[6] =
	{
		FIntPoint(0,1),
		FIntPoint(1,3),
		FIntPoint(3,2),
		FIntPoint(4,5),
		FIntPoint(5,7),
		FIntPoint(7,6)
	};

	TArray<uint8> ResultList = { BitList };

	for (int32 LoopCount = 0; LoopCount < 3; LoopCount++)
	{
		for (int32 Index = 0; Index < 6; Index++)
		{
			const FIntPoint& SwapParm = SwapList[Index];

			FBitReference FirstBit(EditableList, 1 << (SwapParm.X & (NumBitsPerDWORD - 1)));
			FBitReference SecondBit(EditableList, 1 << (SwapParm.Y & (NumBitsPerDWORD - 1)));

			const bool TempBool = FirstBit;

			FirstBit = SecondBit;
			SecondBit = TempBool;
		}

		ResultList.Add(uint8(EditableList));
	}

	return ResultList;
}

FLFPMarchingPartKey ULohFunctionPluginMarchingLibrary::MakeMarchingPartKey(const TArray<bool>& ConnectPointList, const FGameplayTag ObjectTag)
{
	uint32 BitList;

	for (int32 Index = 0; Index < 8; Index++)
	{
		if (ConnectPointList.IsValidIndex(Index) == false) continue;

		FBitReference Bit(BitList, 1 << (Index & (NumBitsPerDWORD - 1))); 
		Bit = ConnectPointList[Index];
	}

	return FLFPMarchingPartKey(BitList, ObjectTag);
}
