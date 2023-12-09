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

	virtual bool CanAddItem_Implementation(const ULFPInventoryComponent* InventoryComponent, const FLFPInventoryChange& ChangeData) const;

	virtual bool CanRemoveItem_Implementation(const ULFPInventoryComponent* InventoryComponent, const FLFPInventoryChange& ChangeData) const;

	virtual bool CanSwapItem_Implementation(const ULFPInventoryComponent* InventoryComponent, const FLFPInventoryChange& ChangeDataA, const FLFPInventoryChange& ChangeDataB) const;

	// Process Modifier

	virtual bool ProcessAddItem_Implementation(const ULFPInventoryComponent* InventoryComponent, UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;

	virtual bool ProcessRemoveItem_Implementation(const ULFPInventoryComponent* InventoryComponent, UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;

	virtual bool ProcessSwapItem_Implementation(const ULFPInventoryComponent* InventoryComponent, UPARAM(ref) FLFPInventoryItem& ItemDataA, const FLFPInventoryIndex& InventoryIndexA, UPARAM(ref) FLFPInventoryItem& ItemDataB, const FLFPInventoryIndex& InventoryIndexB) const;

	// Catergorize Modifier

	virtual FGameplayTagContainer GetInventoryIndexCatergorize_Implementation(const ULFPInventoryComponent* InventoryComponent, const FLFPInventoryChange& ChangeData) const;

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
