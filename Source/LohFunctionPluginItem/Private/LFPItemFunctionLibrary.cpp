// Copyright (c) 2023-2024 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#include "LFPItemFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"

FLFPInventoryItem FLFPInventoryItem::EmptyItem = FLFPInventoryItem();

bool ULFPItemFunctionLibrary::HasMetaData(const FLFPInventoryItem& Item, const FGameplayTag MetaTag)
{
	return Item.HasMetaData(MetaTag);
}

FString ULFPItemFunctionLibrary::GetMetaData(const FLFPInventoryItem& Item, const FGameplayTag MetaTag)
{
	return Item.GetMetaData(MetaTag);
}

int32 ULFPItemFunctionLibrary::GetMetaDataAsNumber(const FLFPInventoryItem& Item, const FGameplayTag MetaTag, const int32 DefaultValue)
{
	return Item.HasMetaData(MetaTag) ? UKismetStringLibrary::Conv_StringToInt(Item.GetMetaData(MetaTag)) : DefaultValue;
}

void ULFPItemFunctionLibrary::MergeMetaData(UPARAM(ref)FLFPInventoryItem& Item, const FLFPInventoryItem& Other, const bool bUniqueOnly)
{
	for (const FLFPInventoryMeta& OtherMetaData : Other.MetaData)
	{
		Item.SetMetaData(OtherMetaData, bUniqueOnly);
	}
}

void ULFPItemFunctionLibrary::SetMetaData(UPARAM(ref) FLFPInventoryItem& Item, const FLFPInventoryMeta& Data)
{
	Item.SetMetaData(Data);
}

void ULFPItemFunctionLibrary::SetMetaDataAsNumber(UPARAM(ref)FLFPInventoryItem& Item, const FGameplayTag MetaTag, const int32 Data)
{
	Item.SetMetaData(FLFPInventoryMeta(MetaTag, FString::FromInt(Data)));
}
