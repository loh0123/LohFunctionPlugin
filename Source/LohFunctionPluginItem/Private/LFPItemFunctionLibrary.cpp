// Fill out your copyright notice in the Description page of Project Settings.


#include "LFPItemFunctionLibrary.h"

bool ULFPItemFunctionLibrary::HasMetaData(const FLFPInventoryItem& Item, const FGameplayTag MetaTag)
{
	return Item.HasMetaData(MetaTag);
}

FString ULFPItemFunctionLibrary::GetMetaData(const FLFPInventoryItem& Item, const FGameplayTag MetaTag)
{
	return Item.GetMetaData(MetaTag);
}

void ULFPItemFunctionLibrary::SetMetaData(UPARAM(ref) FLFPInventoryItem& Item, const FLFPInventoryMeta& Data)
{
	Item.SetMetaData(Data);
}
