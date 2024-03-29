// Copyright (c) 2023-2024 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

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

	virtual void InitializeComponent();

	virtual void UninitializeComponent() {};

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
	bool CanUpdateItem(const FLFPInventoryItem& ItemData) const;
	virtual bool CanUpdateItem_Implementation(const FLFPInventoryItem& ItemData) const { return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanContainItem(const FLFPInventoryItem& ItemData) const;
	virtual bool CanContainItem_Implementation(const FLFPInventoryItem& ItemData) const { return true; }



	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanAddItemOnSlot(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const;
	virtual bool CanAddItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const { return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanRemoveItemOnSlot(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const;
	virtual bool CanRemoveItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const { return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanSwapItemOnSlot(const FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, const FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const;
	virtual bool CanSwapItemOnSlot_Implementation(const FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, const FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const { return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanUpdateItemOnSlot(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const;
	virtual bool CanUpdateItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const { return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanContainItemOnSlot(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const;
	virtual bool CanContainItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const { return true; }

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

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool ProcessUpdateItem(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;
	virtual bool ProcessUpdateItem_Implementation(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const { return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool ProcessContainItem(const FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;
	virtual bool ProcessContainItem_Implementation(const FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const { return true; }

	// Catergorize Modifier

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	FGameplayTagContainer GetItemCatergorize(const FLFPInventoryItem& ItemData) const;
	virtual FGameplayTagContainer GetItemCatergorize_Implementation(const FLFPInventoryItem& ItemData) const { return FGameplayTagContainer(); }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	FLFPInventorySearch GetItemInventorySearch(const FLFPInventoryItem& ItemData) const;
	virtual FLFPInventorySearch GetItemInventorySearch_Implementation(const FLFPInventoryItem& ItemData) const { return FLFPInventorySearch(); }

	// Sort Modifier

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanSlotNameBeSort(const FGameplayTag& SlotName) const;
	virtual bool CanSlotNameBeSort_Implementation(const FGameplayTag& SlotName) const { return false; }

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanItemSortHigherThan(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB, const FGameplayTag& SortTag) const;
	virtual bool CanItemSortHigherThan_Implementation(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB, const FGameplayTag& SortTag) const { return false; }

public:

	UFUNCTION(BlueprintPure, Category = "LFPItemInventoryFunction | Getter")
	ULFPInventoryComponent* GetOwner() const;
};
