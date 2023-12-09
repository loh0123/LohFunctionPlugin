// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LFPItemInventoryFunction.h"
#include "LFPItemInventoryBasicFunction.generated.h"

USTRUCT(Blueprintable)
struct FLFPItemBasicData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default)
		int32 MaxStack = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default)
		FGameplayTagContainer Catergorize = FGameplayTagContainer();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default)
		int32 MaxAttachSlots = INDEX_NONE;
};

/**
 * 
 */
UCLASS(BlueprintType)
class LOHFUNCTIONPLUGINITEM_API ULFPItemInventoryBasicFunction : public ULFPItemInventoryFunction
{
	GENERATED_BODY()

public:

	virtual bool CanAddItem_Implementation(const FLFPInventoryChange& ChangeData) const override;

	virtual bool CanRemoveItem_Implementation(const FLFPInventoryChange& ChangeData) const override;

	virtual bool CanSwapItem_Implementation(const FLFPInventoryChange& ChangeDataA, const FLFPInventoryChange& ChangeDataB) const override;

	// Process Modifier

	virtual bool ProcessAddItem_Implementation(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const override;

	virtual bool ProcessRemoveItem_Implementation(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const override;

	virtual bool ProcessSwapItem_Implementation(UPARAM(ref) FLFPInventoryItem& ItemDataA, const FLFPInventoryIndex& InventoryIndexA, UPARAM(ref) FLFPInventoryItem& ItemDataB, const FLFPInventoryIndex& InventoryIndexB) const override;

	// Catergorize Modifier

	virtual FGameplayTagContainer GetInventoryIndexCatergorize_Implementation(const FLFPInventoryChange& ChangeData) const override;

	// Check Modifier

	virtual bool CanItemSortHigherThan_Implementation(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB, const FGameplayTag& SortTag) const override;

	virtual bool CanItemUseInventoryIndex_Implementation(const FLFPInventoryChange& ChangeData, const ELFPInventoryOperation Operation) const override;

	virtual bool DoInventoryIndexContainItem_Implementation(const FLFPInventoryChange& ChangeData) const override;

public:

	UPROPERTY(EditDefaultsOnly, Category = "LFPItemInventoryBasicFunction | Setting")
		bool bHasStack = false;

	UPROPERTY(EditDefaultsOnly, Category = "LFPItemInventoryBasicFunction | Setting")
		bool bHasQuality = false;

	UPROPERTY(EditDefaultsOnly, Category = "LFPItemInventoryBasicFunction | Setting")
		bool bHasAttachSlots = false;

	UPROPERTY(EditDefaultsOnly, Category = "LFPItemInventoryBasicFunction | Setting")
		bool bHasIndexCatergorize = false;

	UPROPERTY(EditDefaultsOnly, Category = "LFPItemInventoryBasicFunction | Setting", meta = (RequiredAssetDataTags = "RowStructure=/Script/LohFunctionPluginItem.LFPItemBasicData"))
		TObjectPtr<UDataTable> ItemDataTable = nullptr;
	
};
