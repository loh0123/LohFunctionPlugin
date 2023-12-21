// Fill out your copyright notice in the Description page of Project Settings.


#include "LFPItemFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "Kismet/KismetStringLibrary.h"

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
