// Copyright (c) 2023-2024 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#include "LFPItemFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"

FLFPInventoryItem FLFPInventoryItem::EmptyItem = FLFPInventoryItem();

bool ULFPItemFunctionLibrary::IsMetaDataSame(const FLFPInventoryItem& ItemA, const FLFPInventoryItem& ItemB, const FGameplayTag MetaTag)
{
	auto MetaDataA = ItemA.GetMetaData(MetaTag);
	auto MetaDataB = ItemB.GetMetaData(MetaTag);

	const FLFPCompactMetaData EmptyData;

	return (MetaDataA == nullptr ? EmptyData : *MetaDataA) == (MetaDataB == nullptr ? EmptyData : *MetaDataB);
}

bool ULFPItemFunctionLibrary::HasMetaData(const FLFPInventoryItem& Item, const FGameplayTag MetaTag)
{
	return Item.HasMetaData(MetaTag);
}

FString ULFPItemFunctionLibrary::GetMetaDataAsString(const FLFPInventoryItem& Item, const FGameplayTag MetaTag)
{
	auto MetaData = Item.GetMetaData(MetaTag);

	return MetaData != nullptr ? MetaData->GetDataAsString() : FString();
}

int32 ULFPItemFunctionLibrary::GetMetaDataAsNumber(const FLFPInventoryItem& Item, const FGameplayTag MetaTag, const int32 DefaultValue)
{
	auto MetaData = Item.GetMetaData(MetaTag);

	return MetaData != nullptr ? MetaData->GetDataAsInt() : DefaultValue;
}

void ULFPItemFunctionLibrary::SetMetaData(UPARAM(ref) FLFPInventoryItem& Item, const FLFPCompactMetaData& Data)
{
	Item.SetMetaData(Data);
}

FGameplayTag ULFPItemFunctionLibrary::GetItemTag(UPARAM(ref)FLFPInventoryItem& Item)
{
	return Item.GetItemTag();
}

void ULFPItemFunctionLibrary::SetItemTag(UPARAM(ref)FLFPInventoryItem& Item, const FGameplayTag ItemTag)
{
	Item.SetItemTag(ItemTag);
}
