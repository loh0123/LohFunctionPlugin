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
	
	virtual bool IsSupportedForNetworking() const override;

public:

	UFUNCTION()
	virtual void InitializeComponent();

	UFUNCTION()
	virtual void UninitializeComponent() {};

	UFUNCTION()
	virtual void Reset() {  };

public:
	
	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanAddItem(const FLFPInventoryItem& ItemData) const;
	virtual bool CanAddItem_Implementation(const FLFPInventoryItem& ItemData) const { return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanRemoveItem(const FLFPInventoryItem& ItemData) const;
	virtual bool CanRemoveItem_Implementation(const FLFPInventoryItem& ItemData) const { return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanUpdateItem(const FLFPInventoryItem& ItemData) const;
	virtual bool CanUpdateItem_Implementation(const FLFPInventoryItem& ItemData) const { return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanFindItem(const FLFPInventoryItem& ItemData) const;
	virtual bool CanFindItem_Implementation(const FLFPInventoryItem& ItemData) const { return true; }



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
	bool CanMergeItemOnSlot(const FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, const FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const;
	virtual bool CanMergeItemOnSlot_Implementation(const FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, const FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const { return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanTransferItemOnSlot(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& ItemData) const;
	virtual bool CanTransferItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& ItemData) const { return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanUpdateItemOnSlot(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const;
	virtual bool CanUpdateItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const { return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanFindItemOnSlot(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const;
	virtual bool CanFindItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const { return true; }

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
	bool ProcessMergeItem(UPARAM(ref) FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, UPARAM(ref) FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const;
	virtual bool ProcessMergeItem_Implementation(UPARAM(ref) FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, UPARAM(ref) FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const { return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool ProcessUpdateItem(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;
	virtual bool ProcessUpdateItem_Implementation(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const { return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool ProcessFindItem(const FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;
	virtual bool ProcessFindItem_Implementation(const FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const { return true; }

	// Categorize Modifier

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	FGameplayTagContainer GetItemAllowSlotNameList(const FLFPInventoryItem& ItemData) const;
	virtual FGameplayTagContainer GetItemAllowSlotNameList_Implementation(const FLFPInventoryItem& ItemData) const { return FGameplayTagContainer(); }

	// Sort Modifier

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanSlotNameBeSort(const FGameplayTag& SlotName) const;
	virtual bool CanSlotNameBeSort_Implementation(const FGameplayTag& SlotName) const { return true; }

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanItemSortHigherThan(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB, const FGameplayTag& SortTag) const;
	virtual bool CanItemSortHigherThan_Implementation(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB, const FGameplayTag& SortTag) const { return true; }

public:

	UFUNCTION(BlueprintPure, Category = "LFPItemInventoryFunction | Getter")
	ULFPInventoryComponent* GetOwner() const;
};
