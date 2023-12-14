// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/LFPInventoryComponent.h"
#include "GameplayTagContainer.h"
#include "LFPItemInventoryFunction.generated.h"

class ULFPInventoryComponent;

/**
 * 
 */
UCLASS(Blueprintable, Abstract, EditInlineNew)
class LOHFUNCTIONPLUGINITEM_API ULFPItemInventoryFunction : public UObject
{
	GENERATED_BODY()

public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual int32 GetFunctionCallspace(UFunction* Function, FFrame* Stack) override;

	virtual bool CallRemoteFunction(UFunction* Function, void* Parms, struct FOutParmRec* OutParms, FFrame* Stack) override;

public:
	
	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanAddItem(const FLFPInventoryItem& ItemData) const;
	virtual bool CanAddItem_Implementation(const FLFPInventoryItem& ItemData) const { return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanRemoveItem(const FLFPInventoryItem& ItemData) const;
	virtual bool CanRemoveItem_Implementation(const FLFPInventoryItem& ItemData) const { return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanSwapItem(const FLFPInventoryItem& FromItem, const FLFPInventoryItem& ToItem) const;
	virtual bool CanSwapItem_Implementation(const FLFPInventoryItem& FromItem, const FLFPInventoryItem& ToItem) const { return true; }



	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanAddItemOnSlot(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const;
	virtual bool CanAddItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const { return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanRemoveItemOnSlot(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const;
	virtual bool CanRemoveItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const { return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanSwapItemOnSlot(const FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, const FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const;
	virtual bool CanSwapItemOnSlot_Implementation(const FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, const FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const { return true; }

	// Process Modifier

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool ProcessAddItem(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;
	virtual bool ProcessAddItem_Implementation(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const { return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool ProcessRemoveItem(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;
	virtual bool ProcessRemoveItem_Implementation(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const { return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool ProcessSwapItem(UPARAM(ref) FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, UPARAM(ref) FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const;
	virtual bool ProcessSwapItem_Implementation(UPARAM(ref) FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, UPARAM(ref) FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const { return true; }

	// Catergorize Modifier

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	FGameplayTagContainer GetItemCatergorize(const FLFPInventoryItem& ItemData) const;
	virtual FGameplayTagContainer GetItemCatergorize_Implementation(const FLFPInventoryItem& ItemData) const { return FGameplayTagContainer(); }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	FLFPInventorySearch GetItemInventorySearch(const FLFPInventoryItem& ItemData) const;
	virtual FLFPInventorySearch GetItemInventorySearch_Implementation(const FLFPInventoryItem& ItemData) const { return FLFPInventorySearch(); }

	// Check Modifier

	//UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	//bool CanItemSortHigherThan(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB, const FGameplayTag& SortTag) const;
	//virtual bool CanItemSortHigherThan_Implementation(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB, const FGameplayTag& SortTag) const { return false; }

public:

	UFUNCTION(BlueprintPure, Category = "LFPItemInventoryFunction | Getter")
	ULFPInventoryComponent* GetOwner() const;
};
