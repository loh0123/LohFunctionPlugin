// Copyright (c) 2023-2024 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "CoreMinimal.h"
#include "Item/FunctionObject/LFPItemInventoryFunction.h"
#include "GameplayTagContainer.h"
#include "LFPItemEquipmentFunction.generated.h"

USTRUCT(Blueprintable)
struct FLFPItemEquipmentData : public FTableRowBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default|Stack")
	TArray<FLFPInventoryIndex> AllowInventoryIndex = TArray<FLFPInventoryIndex>();

public:

	FORCEINLINE bool IsInventoryIndexAllow(const FLFPInventoryIndex& InventoryIndex) const { return AllowInventoryIndex.Contains(InventoryIndex); }
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLFPEquipmentItemEvent, const FLFPInventoryItemOperationData&, ItemOperationData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FLFPEquipmentChangeEvent, const FGameplayTag&, SlotName, const bool, Value, const FGameplayTag&, EventTag);

/**
 * 
 */
UCLASS()
class LOHFUNCTIONPLUGINITEM_API ULFPItemEquipmentFunction : public ULFPItemInventoryFunction
{
	GENERATED_BODY()

public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

	virtual void InitializeComponent() override;

	virtual void UninitializeComponent() override;

public:

	virtual bool CanAddItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const override;

	virtual bool CanRemoveItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const override;

	virtual bool CanSwapItemOnSlot_Implementation(const FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, const FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const override;

	// Check Modifier

	virtual bool CanSlotNameBeSort_Implementation(const FGameplayTag& SlotName) const override;

protected:

	UFUNCTION(NetMulticast, Reliable)
	void SendSlotLockChanged(const FGameplayTag& SlotName, const bool IsLock, const FGameplayTag& EventTag) const;
	void SendSlotLockChanged_Implementation(const FGameplayTag& SlotName, const bool IsLock, const FGameplayTag& EventTag) const;

	UFUNCTION(NetMulticast, Reliable)
	void SendSlotActiveChanged(const FGameplayTag& SlotName, const bool IsInactive, const FGameplayTag& EventTag) const;
	void SendSlotActiveChanged_Implementation(const FGameplayTag& SlotName, const bool IsInactive, const FGameplayTag& EventTag) const;

protected:

	FORCEINLINE const FLFPItemEquipmentData* GetDataTableRow(const FGameplayTag& RowTag) const;

public:

	UFUNCTION(BlueprintCallable, Category = "LFPItemBasicFunction | Function")
	bool SetSlotNameLock(UPARAM(meta = (Categories = "Item.SlotName")) const FGameplayTag SlotName, const bool IsLock, UPARAM(meta = (Categories = "Item.Event"))  const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, Category = "LFPItemBasicFunction | Function")
	void SetSlotNameListLock(UPARAM(meta = (Categories = "Item.SlotName")) const FGameplayTagContainer SlotNameList, const bool IsLock, UPARAM(meta = (Categories = "Item.Event"))  const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, Category = "LFPItemBasicFunction | Function")
	bool SetSlotNameInactive(UPARAM(meta = (Categories = "Item.SlotName")) const FGameplayTag SlotName, const bool IsInactive, UPARAM(meta = (Categories = "Item.Event"))  const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, Category = "LFPItemBasicFunction | Function")
	void SetSlotNameListInactive(UPARAM(meta = (Categories = "Item.SlotName")) const FGameplayTagContainer SlotNameList, const bool IsInactive, UPARAM(meta = (Categories = "Item.Event"))  const FGameplayTag EventTag);

public:

	UFUNCTION(BlueprintPure, Category = "LFPItemBasicFunction | Function", meta = (GameplayTagFilter = "Item.Event"))
	FORCEINLINE bool IsEquipmentSlot(const FGameplayTag Slot) const;

	UFUNCTION(BlueprintPure, Category = "LFPItemBasicFunction | Function", meta = (GameplayTagFilter = "Item.Event"))
	FORCEINLINE bool IsSlotNameLock(const FGameplayTag Slot) const;

	UFUNCTION(BlueprintPure, Category = "LFPItemBasicFunction | Function", meta = (GameplayTagFilter = "Item.Event"))
	FORCEINLINE bool IsSlotNameInactive(const FGameplayTag Slot) const;

public: // Event

	UFUNCTION() void OnInventoryUpdateItem(const FLFPInventoryItemOperationData& ItemOperationData);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LFPItemBasicFunction | Setting", meta = (RequiredAssetDataTags = "RowStructure=/Script/LohFunctionPluginItem.LFPItemEquipmentData"))
	TObjectPtr<UDataTable> ItemDataTable = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "LFPItemBasicFunction | Setting", meta = (Categories = "Item.SlotName"))
	FGameplayTagContainer EquipmentSlotNameList = FGameplayTagContainer::EmptyContainer;

	/* Slot Can't Equip Or Unequip */
	UPROPERTY(EditDefaultsOnly, Category = "LFPItemBasicFunction | Cache", Replicated, meta = (Categories = "Item.SlotName"))
	FGameplayTagContainer LockSlotNameList = FGameplayTagContainer::EmptyContainer;

	/* Slot Won't Trigger Event And Will Send Unequip Event To Any On SlotName */
	UPROPERTY(EditDefaultsOnly, Category = "LFPItemBasicFunction | Cache", Replicated, meta = (Categories = "Item.SlotName"))
	FGameplayTagContainer InactiveSlotNameList = FGameplayTagContainer::EmptyContainer;

public:

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPEquipmentComponent | Delegate")
	FLFPEquipmentItemEvent OnEquipItem;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPEquipmentComponent | Delegate")
	FLFPEquipmentItemEvent OnUnequipItem;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPEquipmentComponent | Delegate")
	FLFPEquipmentChangeEvent OnSlotLockChanged;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPEquipmentComponent | Delegate")
	FLFPEquipmentChangeEvent OnSlotActiveChanged;
};
