// Copyright (c) 2023-2024 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetStringLibrary.h"
#include "GameplayTagContainer.h"
#include "LohFunctionPluginLibrary.h"
#include "LFPItemFunctionLibrary.generated.h"

USTRUCT(BlueprintType)
struct FLFPInventoryMeta : public FLFPCompactMetaData
{
	GENERATED_BODY()

	FLFPInventoryMeta() {}

	FLFPInventoryMeta(const FGameplayTag& Tag) : Super(Tag) {}

	FLFPInventoryMeta(const FGameplayTag& Tag, const FString& Data) : Super(Tag) { SetDataAsString(Data); }
};

USTRUCT(BlueprintType)
struct FLFPInventoryItem
{
	GENERATED_BODY()

	FLFPInventoryItem() {}

	FLFPInventoryItem(const FGameplayTag& Tag) : ItemTag(Tag), MetaData(TArray<FLFPInventoryMeta>()) {}

	FLFPInventoryItem(const FLFPInventoryItem& Other) : ItemTag(Other.ItemTag), MetaData(Other.MetaData) {}

public:

	static FLFPInventoryItem EmptyItem;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default, meta = (Categories = "Item.Identifier"))
	FGameplayTag ItemTag = FGameplayTag();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	TArray<FLFPInventoryMeta> MetaData = TArray<FLFPInventoryMeta>();

public:

	FORCEINLINE bool IsValid() const { return ItemTag.IsValid(); }

	FORCEINLINE	bool MatchesTag(const FGameplayTag& Tag) const { return ItemTag.MatchesTag(Tag); }

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

	FORCEINLINE	bool HasMetaData(const FGameplayTag& Tag) const { return MetaData.IndexOfByKey(Tag) != INDEX_NONE; }

	FORCEINLINE	const FLFPInventoryMeta* GetMetaData(const FGameplayTag& Tag) const
	{ 
		int32 ReturnIndex(MetaData.IndexOfByKey(Tag));

		return ReturnIndex != INDEX_NONE ? &MetaData[ReturnIndex] : nullptr;
	}

	FORCEINLINE	const TArray<FLFPInventoryMeta>& GetMetaDataList() const
	{
		return MetaData;
	}

	FORCEINLINE	void SetMetaData(const FLFPInventoryMeta& Data, const bool bUniqueOnly = false)
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

public:

	UFUNCTION(BlueprintPure, Category = "LohFunctionPluginLibrary")
	static bool IsMetaDataSame(const FLFPInventoryItem& ItemA, const FLFPInventoryItem& ItemB, const FGameplayTag MetaTag);

	UFUNCTION(BlueprintPure, Category = "LohFunctionPluginLibrary")
	static bool HasMetaData(const FLFPInventoryItem& Item, const FGameplayTag MetaTag);

	UFUNCTION(BlueprintPure, Category = "LohFunctionPluginLibrary")
	static FString GetMetaDataAsString(const FLFPInventoryItem& Item, const FGameplayTag MetaTag);

	UFUNCTION(BlueprintPure, Category = "LohFunctionPluginLibrary")
	static int32 GetMetaDataAsNumber(const FLFPInventoryItem& Item, const FGameplayTag MetaTag, const int32 DefaultValue = 0);

	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary")
	static void SetMetaData(UPARAM(ref) FLFPInventoryItem& Item, const FLFPInventoryMeta& Data);

	UFUNCTION(BlueprintPure, Category = "LohFunctionPluginLibrary")
	static FGameplayTag GetItemTag(UPARAM(ref) FLFPInventoryItem& Item);

	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary")
	static void SetItemTag(UPARAM(ref) FLFPInventoryItem& Item, const FGameplayTag ItemTag);
	
};
