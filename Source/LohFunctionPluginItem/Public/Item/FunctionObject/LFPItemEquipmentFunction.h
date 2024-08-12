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
struct LOHFUNCTIONPLUGINITEM_API FLFPItemEquipmentData : public FTableRowBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default|Stack")
	TArray<FLFPInventoryIndex> AllowInventoryIndexList = TArray<FLFPInventoryIndex>();

public:

	FORCEINLINE bool IsInventoryIndexAllow(const FLFPInventoryIndex& InventoryIndex) const
	{
		return AllowInventoryIndexList.ContainsByPredicate(
			[&](const FLFPInventoryIndex& AllowInventoryIndex)
			{
				return
					AllowInventoryIndex.SlotName == InventoryIndex.SlotName
					&&
					(
						AllowInventoryIndex.SlotItemIndex < 0
						||
						AllowInventoryIndex.SlotItemIndex == InventoryIndex.SlotItemIndex
						);
			}
		);
	}
};

USTRUCT(BlueprintType)
struct LOHFUNCTIONPLUGINITEM_API FLFPItemEquipmentSelector
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default, meta = (Categories = "Item.SlotName"))
	FGameplayTag EquipmentSlotName = FGameplayTag();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default)
	int32 CurrentSelection = INDEX_NONE;

public:

	FORCEINLINE FLFPInventoryIndex GetInventoryIndex() const { return FLFPInventoryIndex(CurrentSelection, EquipmentSlotName); } const

		FORCEINLINE FGameplayTag GetEquipmentSlotName() const { return EquipmentSlotName; } const

		FORCEINLINE bool IsEquipmentSlotNameMatch(const FGameplayTag& Tag) const { return Tag.MatchesTag(EquipmentSlotName); }

	FORCEINLINE int32 GetCurrentSelection() const { return CurrentSelection; }

	FORCEINLINE int32 SetCurrentSelection(const int32 NewCurrentSelection) { CurrentSelection = NewCurrentSelection; return CurrentSelection; }
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLFPEquipmentItemEvent, const FLFPInventoryItemOperationData&, ItemOperationData);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FLFPEquipmentChangeEvent, const FGameplayTag&, SlotName, const bool, Value, const FGameplayTag&, EventTag);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FLFPEquipmentSelectorEvent, const FGameplayTag&, SlotName, const int32, OldSelectedIndex, const int32, NewSelectedIndex, const FGameplayTag&, EventTag);

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

private: // Delegate Function

	UFUNCTION()
	void SendSelectorDelegateEvent(const FGameplayTag& SlotName, const int32 OldIndex, const int32 NewIndex, const FGameplayTag& EventTag) const;

	UFUNCTION()
	void SendSlotLockChanged(const FGameplayTag& SlotName, const bool IsLock, const FGameplayTag& EventTag) const;

	UFUNCTION()
	void SendSlotActiveChanged(const FGameplayTag& SlotName, const bool IsInactive, const FGameplayTag& EventTag) const;

private: // Delegate Network Function

	UFUNCTION(Client, Reliable)
	void CLIENT_SendSelectorDelegateEvent(const FGameplayTag& SlotName, const int32 OldIndex, const int32 NewIndex, const FGameplayTag& EventTag) const;
	void CLIENT_SendSelectorDelegateEvent_Implementation(const FGameplayTag& SlotName, const int32 OldIndex, const int32 NewIndex, const FGameplayTag& EventTag) const;

	UFUNCTION(NetMulticast, Reliable)
	void CLIENT_SendSlotLockChanged(const FGameplayTag& SlotName, const bool IsLock, const FGameplayTag& EventTag) const;
	void CLIENT_SendSlotLockChanged_Implementation(const FGameplayTag& SlotName, const bool IsLock, const FGameplayTag& EventTag) const;

	UFUNCTION(NetMulticast, Reliable)
	void CLIENT_SendSlotActiveChanged(const FGameplayTag& SlotName, const bool IsInactive, const FGameplayTag& EventTag) const;
	void CLIENT_SendSlotActiveChanged_Implementation(const FGameplayTag& SlotName, const bool IsInactive, const FGameplayTag& EventTag) const;

protected:

	FORCEINLINE const FLFPItemEquipmentData* GetDataTableRow(const FGameplayTag& RowTag) const;

public:

	UFUNCTION(BlueprintCallable, Category = "LFPItemBasicFunction | Function")
	bool SelectIndex(const FLFPInventoryIndex& InventoryIndex, const FGameplayTag EventTag);

public:

	UFUNCTION(BlueprintCallable, Category = "LFPItemBasicFunction | Function")
	bool SetSlotNameLock(UPARAM(meta = (Categories = "Item.SlotName")) const FGameplayTag SlotName, const bool IsLock, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, Category = "LFPItemBasicFunction | Function")
	void SetSlotNameListLock(UPARAM(meta = (Categories = "Item.SlotName")) const FGameplayTagContainer SlotNameList, const bool IsLock, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, Category = "LFPItemBasicFunction | Function")
	bool SetSlotNameInactive(UPARAM(meta = (Categories = "Item.SlotName")) const FGameplayTag SlotName, const bool IsInactive, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, Category = "LFPItemBasicFunction | Function")
	void SetSlotNameListInactive(UPARAM(meta = (Categories = "Item.SlotName")) const FGameplayTagContainer SlotNameList, const bool IsInactive, const FGameplayTag EventTag);

public:

	UFUNCTION(BlueprintPure, Category = "LFPItemBasicFunction | Function")
	bool IsIndexSelected(const FLFPInventoryIndex& InventoryIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPItemBasicFunction | Function", meta = (GameplayTagFilter = "Item.SlotName"))
	bool IsSelectorSlot(const FGameplayTag Slot) const;

	UFUNCTION(BlueprintPure, Category = "LFPItemBasicFunction | Function", meta = (GameplayTagFilter = "Item.SlotName"))
	bool IsEquipmentSlot(const FGameplayTag Slot) const;

	UFUNCTION(BlueprintPure, Category = "LFPItemBasicFunction | Function", meta = (GameplayTagFilter = "Item.SlotName"))
	bool IsSlotNameLock(const FGameplayTag Slot) const;

	UFUNCTION(BlueprintPure, Category = "LFPItemBasicFunction | Function", meta = (GameplayTagFilter = "Item.SlotName"))
	bool IsSlotNameInactive(const FGameplayTag Slot) const;

public:

	UFUNCTION(BlueprintPure, Category = "LFPItemBasicFunction | Function")
	int32 GetSelectedIndex(const FGameplayTag Slot) const;

public: // Event

	UFUNCTION() void OnInventoryUpdateItem(const FLFPInventoryItemOperationData& ItemOperationData);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LFPItemBasicFunction | Setting", meta = (RequiredAssetDataTags = "RowStructure=/Script/LohFunctionPluginItem.LFPItemEquipmentData"))
	TObjectPtr<UDataTable> ItemDataTable = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "LFPItemBasicFunction | Setting", Replicated)
	TArray<FLFPItemEquipmentSelector> SelectorList = TArray<FLFPItemEquipmentSelector>();

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
	FLFPEquipmentSelectorEvent OnSlotSelectionChanged;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPEquipmentComponent | Delegate")
	FLFPEquipmentChangeEvent OnSlotLockChanged;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPEquipmentComponent | Delegate")
	FLFPEquipmentChangeEvent OnSlotActiveChanged;
};
