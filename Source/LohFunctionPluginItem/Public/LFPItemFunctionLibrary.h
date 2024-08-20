// Copyright (c) 2023-2024 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetStringLibrary.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "LohFunctionPluginLibrary.h"
#include "LFPItemFunctionLibrary.generated.h"

USTRUCT(BlueprintType)
struct LOHFUNCTIONPLUGINITEM_API FLFPInventoryItem
{
	GENERATED_BODY()

	FLFPInventoryItem() {}

	FLFPInventoryItem(const FGameplayTag& Tag) : ItemTag(Tag), MetaData(TArray<FLFPCompactMetaData>()) {}

	FLFPInventoryItem(const FLFPInventoryItem& Other) : ItemTag(Other.ItemTag), MetaData(Other.MetaData) {}

public:

	static FLFPInventoryItem EmptyItem;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default, meta = (Categories = "Item.Identifier"))
	FGameplayTag ItemTag = FGameplayTag();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	TArray<FLFPCompactMetaData> MetaData = TArray<FLFPCompactMetaData>();

public:

	FORCEINLINE bool IsValid() const { return ItemTag.IsValid() && UGameplayTagsManager::Get().RequestGameplayTag(ItemTag.GetTagName()).IsValid(); }

	FORCEINLINE	bool MatchesTag(const FGameplayTag& Tag) const { return ItemTag.MatchesTag(Tag); }

	FORCEINLINE	bool MatchesAnyTag(const FGameplayTagContainer& TagList) const { return ItemTag.MatchesAny(TagList); }

	// Item Tag

	FORCEINLINE const FGameplayTag& GetItemTag() const
	{
		return ItemTag;
	}

	FORCEINLINE	void SetItemTag(const FGameplayTag& Tag)
	{
		ItemTag = Tag;

		if (ItemTag.IsValid() == false)
		{
			MetaData.Empty();
		}

		return;
	}

	// Meta Data

	FORCEINLINE	bool ContainMetaData(const FGameplayTag& Tag) const { return MetaData.IndexOfByKey(Tag) != INDEX_NONE; }

	FORCEINLINE	const FLFPCompactMetaData* GetMetaData(const FGameplayTag& Tag) const
	{ 
		int32 ReturnIndex(MetaData.IndexOfByKey(Tag));

		return ReturnIndex != INDEX_NONE ? &MetaData[ReturnIndex] : nullptr;
	}

	FORCEINLINE	const TArray<FLFPCompactMetaData>& GetMetaDataList() const
	{
		return MetaData;
	}

	FORCEINLINE	void SetMetaData(const FLFPCompactMetaData& Data, const bool bUniqueOnly = false)
	{
		int32 ReturnIndex(MetaData.IndexOfByKey(Data.MetaTag));

		if (ReturnIndex != INDEX_NONE)
		{
			if (bUniqueOnly == false) MetaData[ReturnIndex] = Data;
		}
		else
		{
			MetaData.Add(Data);
		}
	}

	FORCEINLINE	bool RemoveMetaData(const FGameplayTag& Tag)
	{
		int32 ReturnIndex(MetaData.IndexOfByKey(Tag));

		if (ReturnIndex != INDEX_NONE)
		{
			MetaData.RemoveAt(ReturnIndex);

			return true;
		}

		return false;
	}

	// Append Meta Data

	FORCEINLINE void AppendMetaDataInt(const TMap<FGameplayTag, int32>& DataMap, const bool bUniqueOnly = false);

	FORCEINLINE void AppendMetaDataFloat(const TMap<FGameplayTag, float>& DataMap, const bool bUniqueOnly = false);

	FORCEINLINE void AppendMetaDataString(const TMap<FGameplayTag, FString>& DataMap, const bool bUniqueOnly = false);

	FORCEINLINE void AppendMetaDataBoolean(const TMap<FGameplayTag, bool>& DataMap, const bool bUniqueOnly = false);

	// String

	FORCEINLINE	FString ToString() const
	{
		FString ReturnText = ItemTag.ToString();

		for (const auto& Meta : MetaData)
		{
			ReturnText += Meta.ToString();
		}

		return ReturnText;
	}


	FORCEINLINE	bool operator==(const FGameplayTag& Tag) const { return ItemTag == Tag; }

	FORCEINLINE	bool operator!=(const FGameplayTag& Tag) const { return ItemTag != Tag; }

	FORCEINLINE	bool operator==(const FLFPInventoryItem& Other) const { return ItemTag == Other.ItemTag && MetaData == Other.MetaData; }

	FORCEINLINE	bool operator!=(const FLFPInventoryItem& Other) const { return ItemTag != Other.ItemTag || MetaData != Other.MetaData; }

	FORCEINLINE	FLFPInventoryItem& operator=(const FLFPInventoryItem& Other)
	{
		ItemTag = Other.ItemTag;
		MetaData = Other.MetaData;

		return *this;
	}
};

/**
 * 
 */
UCLASS()
class LOHFUNCTIONPLUGINITEM_API ULFPItemFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public: // Checker

	UFUNCTION(BlueprintPure, Category = "LohFunctionPluginLibrary")
	static bool IsMetaDataSame(const FLFPInventoryItem& ItemA, const FLFPInventoryItem& ItemB, const FGameplayTag MetaTag);

	UFUNCTION(BlueprintPure, Category = "LohFunctionPluginLibrary")
	static bool ContainMetaData(const FLFPInventoryItem& Item, const FGameplayTag MetaTag);

	/* Check Is Item Contain All Meta Data And Equal Or Bigger Than The Cost  */
	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary")
	static bool CheckMetaDataCost(const FLFPInventoryItem& Item, const TMap<FGameplayTag, int32>& IntCostDataMap, const TMap<FGameplayTag, float>& FloatCostDataMap);

public: // Getter

	UFUNCTION(BlueprintPure, Category = "LohFunctionPluginLibrary")
	static FLFPCompactMetaData GetMetaData(const FLFPInventoryItem& Item, const FGameplayTag MetaTag);

	UFUNCTION(BlueprintPure, Category = "LohFunctionPluginLibrary")
	static FString GetMetaDataAsString(const FLFPInventoryItem& Item, const FGameplayTag MetaTag);

	UFUNCTION(BlueprintPure, Category = "LohFunctionPluginLibrary")
	static int32 GetMetaDataAsNumber(const FLFPInventoryItem& Item, const FGameplayTag MetaTag, const int32 DefaultValue = 0);

	UFUNCTION(BlueprintPure, Category = "LohFunctionPluginLibrary")
	static FGameplayTag GetItemTag(UPARAM(ref) FLFPInventoryItem& Item);

public: // Setter

	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary")
	static void SetMetaData(UPARAM(ref) FLFPInventoryItem& Item, const FLFPCompactMetaData& Data);

	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary")
	static void SetItemTag(UPARAM(ref) FLFPInventoryItem& Item, const FGameplayTag ItemTag);
	
	/* Subtract The Cost From Item Meta Data */
	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary")
	static void ConsumeMetaDataCost(UPARAM(ref) FLFPInventoryItem& Item, const TMap<FGameplayTag, int32>& IntCostDataMap, const TMap<FGameplayTag, float>& FloatCostDataMap);
};
