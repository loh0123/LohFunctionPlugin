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

bool ULFPItemFunctionLibrary::ContainMetaData(const FLFPInventoryItem& Item, const FGameplayTag MetaTag)
{
	return Item.ContainMetaData(MetaTag);
}

bool ULFPItemFunctionLibrary::CheckMetaDataCost(const FLFPInventoryItem& Item, const TMap<FGameplayTag, int32>& IntCostDataMap, const TMap<FGameplayTag, float>& FloatCostDataMap)
{
	for (const auto& CostData : IntCostDataMap)
	{
		const auto MetaData = Item.GetMetaData(CostData.Key);

		if (MetaData == nullptr)
		{
			return false;
		}

		if (MetaData->GetDataType() != ELFPCompactMetaType::LFP_Int)
		{
			return false;
		}

		if (MetaData->GetDataAsInt() < CostData.Value)
		{
			return false;
		}
	}

	for (const auto& CostData : FloatCostDataMap)
	{
		const auto MetaData = Item.GetMetaData(CostData.Key);

		if (MetaData == nullptr)
		{
			return false;
		}

		if (MetaData->GetDataType() != ELFPCompactMetaType::LFP_Int)
		{
			return false;
		}

		if (MetaData->GetDataAsInt() < CostData.Value)
		{
			return false;
		}
	}

	return true;
}

FLFPCompactMetaData ULFPItemFunctionLibrary::GetMetaData(const FLFPInventoryItem& Item, const FGameplayTag MetaTag)
{
	auto MetaData = Item.GetMetaData(MetaTag);

	return MetaData != nullptr ? *MetaData : FLFPCompactMetaData();
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

FGameplayTag ULFPItemFunctionLibrary::GetItemTag(UPARAM(ref)FLFPInventoryItem& Item)
{
	return Item.GetItemTag();
}

void ULFPItemFunctionLibrary::SetMetaData(UPARAM(ref) FLFPInventoryItem& Item, const FLFPCompactMetaData& Data)
{
	Item.SetMetaData(Data);
}

void ULFPItemFunctionLibrary::SetItemTag(UPARAM(ref)FLFPInventoryItem& Item, const FGameplayTag ItemTag)
{
	Item.SetItemTag(ItemTag);
}

void ULFPItemFunctionLibrary::ConsumeMetaDataCost(UPARAM(ref)FLFPInventoryItem& Item, const TMap<FGameplayTag, int32>& IntCostDataMap, const TMap<FGameplayTag, float>& FloatCostDataMap)
{
	for (const auto& CostData : IntCostDataMap)
	{
		const auto MetaData = Item.GetMetaData(CostData.Key);

		if (MetaData == nullptr)
		{
			continue;
		}

		if (MetaData->GetDataType() != ELFPCompactMetaType::LFP_Int)
		{
			continue;
		}

		FLFPCompactMetaData NewMetaData(CostData.Key);

		NewMetaData.SetDataAsInt(MetaData->GetDataAsInt() - CostData.Value);

		Item.SetMetaData(NewMetaData);
	}

	for (const auto& CostData : FloatCostDataMap)
	{
		const auto MetaData = Item.GetMetaData(CostData.Key);

		if (MetaData == nullptr)
		{
			continue;
		}

		if (MetaData->GetDataType() != ELFPCompactMetaType::LFP_Float)
		{
			continue;
		}

		FLFPCompactMetaData NewMetaData(CostData.Key);

		NewMetaData.SetDataAsFloat(MetaData->GetDataAsFloat() - CostData.Value);

		Item.SetMetaData(NewMetaData);
	}
}

void FLFPInventoryItem::AppendMetaDataInt(const TMap<FGameplayTag, int32>& DataMap, const bool bUniqueOnly)
{
	for (const auto& RawMetaData : DataMap)
	{
		FLFPCompactMetaData NewMetaData(RawMetaData.Key);

		NewMetaData.SetDataAsInt(RawMetaData.Value);

		SetMetaData(NewMetaData, bUniqueOnly);
	}
}

void FLFPInventoryItem::AppendMetaDataFloat(const TMap<FGameplayTag, float>& DataMap, const bool bUniqueOnly)
{
	for (const auto& RawMetaData : DataMap)
	{
		FLFPCompactMetaData NewMetaData(RawMetaData.Key);

		NewMetaData.SetDataAsFloat(RawMetaData.Value);

		SetMetaData(NewMetaData, bUniqueOnly);
	}
}

void FLFPInventoryItem::AppendMetaDataString(const TMap<FGameplayTag, FString>& DataMap, const bool bUniqueOnly)
{
	for (const auto& RawMetaData : DataMap)
	{
		FLFPCompactMetaData NewMetaData(RawMetaData.Key);

		NewMetaData.SetDataAsString(RawMetaData.Value);

		SetMetaData(NewMetaData, bUniqueOnly);
	}
}

void FLFPInventoryItem::AppendMetaDataBoolean(const TMap<FGameplayTag, bool>& DataMap, const bool bUniqueOnly)
{
	for (const auto& RawMetaData : DataMap)
	{
		FLFPCompactMetaData NewMetaData(RawMetaData.Key);

		NewMetaData.SetDataAsBool(RawMetaData.Value);

		SetMetaData(NewMetaData, bUniqueOnly);
	}
}
