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
		FLFPInventorySearch InventorySearch = FLFPInventorySearch();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default)
		FGameplayTagContainer Categorize = FGameplayTagContainer();
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

	//virtual bool CanSwapItem_Implementation(const FLFPInventoryChange& ChangeDataA, const FLFPInventoryChange& ChangeDataB) const override;


	virtual bool CanAddItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const;

	virtual bool CanRemoveItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const;

	//// Process Modifier

	virtual bool ProcessAddItem_Implementation(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const override;

	virtual bool ProcessRemoveItem_Implementation(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const override;

	//virtual bool ProcessSwapItem_Implementation(UPARAM(ref) FLFPInventoryItem& ItemDataA, const FLFPInventoryIndex& InventoryIndexA, UPARAM(ref) FLFPInventoryItem& ItemDataB, const FLFPInventoryIndex& InventoryIndexB) const override;

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
