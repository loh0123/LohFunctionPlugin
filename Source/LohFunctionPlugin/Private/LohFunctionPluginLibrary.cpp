// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#include "LohFunctionPluginLibrary.h"
#include "LohFunctionPlugin.h"
#include "Misc/OutputDeviceNull.h"

bool ULohFunctionPluginLibrary::ContainPoint(const FLFPIntPointList& List, const int32 Index)
{
	return List.ContainIndex(Index);
}

void ULohFunctionPluginLibrary::AddPoint(UPARAM(ref)FLFPIntPointList& List, const FIntPoint Range)
{
	List.Add(Range);
}

void ULohFunctionPluginLibrary::RemovePoint(UPARAM(ref)FLFPIntPointList& List, const FIntPoint Range)
{
	List.Remove(Range);
}

TArray<uint8> ULohFunctionPluginLibrary::GenerateBitMatrixNumberTop(const uint8 BitList)
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

FGameplayTag ULohFunctionPluginLibrary::GetGameplayTagFromName(const FName TagName)
{
	return FGameplayTag::RequestGameplayTag(TagName, false);
}
