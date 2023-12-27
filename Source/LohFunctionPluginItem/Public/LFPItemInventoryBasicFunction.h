// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LFPItemInventoryFunction.h"
#include "LFPItemInventoryBasicFunction.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LFPItemInventoryBasicFunction, Log, All);

USTRUCT(Blueprintable)
struct FLFPItemBasicData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default)
		FGameplayTag StackTag = FGameplayTag();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default)
		int32 MaxStack = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default)
		FGameplayTag AttachSlotsTag = FGameplayTag();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default)
		int32 MaxAttachSlots = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default)
		FGameplayTagContainer MatchIntTagList = FGameplayTagContainer();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default)
		FLFPInventorySearch AllowedInventorySearch = FLFPInventorySearch();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default)
		FGameplayTagContainer Categorize = FGameplayTagContainer();

public:

	FORCEINLINE bool DoItemAllowOnSlot(const FGameplayTag& SlotName) const
	{
		return AllowedInventorySearch.IsValid() == false || SlotName.MatchesAny(AllowedInventorySearch.SlotNames);
	}

	FORCEINLINE bool DoItemMatch(const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const
	{
		if (CurrentData.IsValid() == false || ProcessData.IsValid() == false) return true;

		for (const FGameplayTag& MathIntTag : MatchIntTagList)
		{
			if (ULFPItemFunctionLibrary::GetMetaData(CurrentData, MathIntTag) != ULFPItemFunctionLibrary::GetMetaData(ProcessData, MathIntTag))
			{
				return false;
			}
		}

		return true;
	}
};

/**
 * 
 */
UCLASS(BlueprintType)
class LOHFUNCTIONPLUGINITEM_API ULFPItemInventoryBasicFunction : public ULFPItemInventoryFunction
{
	GENERATED_BODY()

public:

	virtual bool CanAddItem_Implementation(const FLFPInventoryItem& ItemData) const;

	virtual bool CanRemoveItem_Implementation(const FLFPInventoryItem& ItemData) const;

	virtual bool CanSwapItem_Implementation(const FLFPInventoryItem& FromItem, const FLFPInventoryItem& ToItem) const override;

	virtual bool CanUpdateItem_Implementation(const FLFPInventoryItem& ItemData) const;


	virtual bool CanAddItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const;

	virtual bool CanRemoveItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const;

	virtual bool CanSwapItemOnSlot_Implementation(const FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, const FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const;

	virtual bool CanUpdateItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const;

	//// Process Modifier

	virtual bool ProcessAddItem_Implementation(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const override;

	virtual bool ProcessRemoveItem_Implementation(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const override;

	virtual bool ProcessSwapItem_Implementation(UPARAM(ref) FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, UPARAM(ref) FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const override;

	virtual bool ProcessUpdateItem_Implementation(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const override;

	//// Catergorize Modifier

	virtual FGameplayTagContainer GetItemCatergorize_Implementation(const FLFPInventoryItem& ItemData) const;

	virtual FLFPInventorySearch GetItemInventorySearch_Implementation(const FLFPInventoryItem& ItemData) const;

	//// Check Modifier

	//virtual bool CanItemSortHigherThan_Implementation(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB, const FGameplayTag& SortTag) const override;

protected:

	FORCEINLINE const FLFPItemBasicData* GetDataTableRow(const FGameplayTag& RowTag) const;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "LFPItemInventoryBasicFunction | Setting", meta = (RequiredAssetDataTags = "RowStructure=/Script/LohFunctionPluginItem.LFPItemBasicData"))
		TObjectPtr<UDataTable> ItemDataTable = nullptr;
	
};
