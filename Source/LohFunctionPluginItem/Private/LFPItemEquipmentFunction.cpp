// Fill out your copyright notice in the Description page of Project Settings.


#include "LFPItemEquipmentFunction.h"
#include "Net/UnrealNetwork.h"

void ULFPItemEquipmentFunction::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ULFPItemEquipmentFunction, LockSlotNameList);

	DOREPLIFETIME(ULFPItemEquipmentFunction, InactiveSlotNameList);
}

void ULFPItemEquipmentFunction::InitializeComponent()
{
	Super::InitializeComponent();

	GetOwner()->OnUpdateItem.AddDynamic(this, &ULFPItemEquipmentFunction::OnInventoryUpdateItem);
}

void ULFPItemEquipmentFunction::UninitializeComponent()
{
	Super::UninitializeComponent();

	GetOwner()->OnUpdateItem.RemoveDynamic(this, &ULFPItemEquipmentFunction::OnInventoryUpdateItem);
}

bool ULFPItemEquipmentFunction::CanAddItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const
{
	/* Skip Slot Name Because Not Process By This Module */
	if (IsEquipmentSlot(InventoryIndex.SlotName) == false) return true;

	if (IsSlotNameLock(InventoryIndex.SlotName)) return false;

	const FLFPItemEquipmentData* TableData = GetDataTableRow(ProcessData.ItemTag);

	if (TableData == nullptr) return false;

	/* Is Item Not Suppose To Be On This Index  */
	if (TableData->IsInventoryIndexAllowed(InventoryIndex) == false) return false;

	return true;
}

bool ULFPItemEquipmentFunction::CanRemoveItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const
{
	/* Skip Slot Name Because Not Process By This Module */
	if (IsEquipmentSlot(InventoryIndex.SlotName) == false) return true;

	if (IsSlotNameLock(InventoryIndex.SlotName)) return false;

	const FLFPItemEquipmentData* TableData = GetDataTableRow(ProcessData.ItemTag);

	if (TableData == nullptr) return false;

	/* Is Item Not Suppose To Be On This Index  */
	if (TableData->IsInventoryIndexAllowed(InventoryIndex) == false) return false;

	return true;
}

bool ULFPItemEquipmentFunction::CanSwapItemOnSlot_Implementation(const FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, const FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const
{
	/* Skip Slot Name Because Not Process By This Module */
	if (IsEquipmentSlot(FromIndex.SlotName))
	{
		if (IsSlotNameLock(FromIndex.SlotName)) return false;

		const FLFPItemEquipmentData* TableData = GetDataTableRow(FromItem.ItemTag);

		if (TableData == nullptr) return false;

		/* Is Item Not Suppose To Be On This Index  */
		if (TableData->IsInventoryIndexAllowed(ToIndex) == false) return false;
	}

	/* Skip Slot Name Because Not Process By This Module */
	if (IsEquipmentSlot(ToIndex.SlotName))
	{
		if (IsSlotNameLock(ToIndex.SlotName)) return false;

		const FLFPItemEquipmentData* TableData = GetDataTableRow(ToItem.ItemTag);

		if (TableData == nullptr) return false;

		/* Is Item Not Suppose To Be On This Index  */
		if (TableData->IsInventoryIndexAllowed(FromIndex) == false) return false;
	}

	return true;
}

bool ULFPItemEquipmentFunction::CanSlotNameBeSort_Implementation(const FGameplayTag& SlotName) const
{
	/* Equipment Slot Can't Be Sort */
	return IsEquipmentSlot(SlotName) == false;
}

const FLFPItemEquipmentData* ULFPItemEquipmentFunction::GetDataTableRow(const FGameplayTag& RowTag) const
{
	uint8* TableRawData = ItemDataTable->FindRowUnchecked(RowTag.GetTagName());

	if (TableRawData == nullptr)
	{
		return nullptr; // Item Not Exist
	}

	const FLFPItemEquipmentData* TableData = reinterpret_cast<FLFPItemEquipmentData*>(TableRawData);

	if (TableData == nullptr)
	{
		return nullptr; // Item Not Same Type
	}

	return TableData;
}

bool ULFPItemEquipmentFunction::SetSlotNameLock(UPARAM(meta = (Categories = "Item.SlotName")) const FGameplayTag SlotName, const bool IsLock, UPARAM(meta = (Categories = "Item.Event"))  const FGameplayTag EventTag)
{
	/* Skip Slot Name Because Not Process By This Module */
	if (IsEquipmentSlot(SlotName) == false) return false;

	if (GetOwner() == nullptr) return false;

	if (IsLock)
	{
		if (InactiveSlotNameList.HasTag(SlotName) == false) 
		{
			LockSlotNameList.AddTag(SlotName);
		}
	}
	else
	{
		if (InactiveSlotNameList.HasTag(SlotName))
		{
			LockSlotNameList.RemoveTag(SlotName);
		}
	}

	return true;
}

void ULFPItemEquipmentFunction::SetSlotNameListLock(UPARAM(meta = (Categories = "Item.SlotName")) const FGameplayTagContainer SlotNameList, const bool IsLock, UPARAM(meta = (Categories = "Item.Event"))  const FGameplayTag EventTag)
{
	for (const FGameplayTag& SlotName : SlotNameList)
	{
		SetSlotNameLock(SlotName, IsLock, EventTag);
	}

	return;
}

bool ULFPItemEquipmentFunction::SetSlotNameInactive(UPARAM(meta = (Categories = "Item.SlotName")) const FGameplayTag SlotName, const bool IsInactive, UPARAM(meta = (Categories = "Item.Event"))  const FGameplayTag EventTag)
{
	/* Skip Slot Name Because Not Process By This Module */
	if (IsEquipmentSlot(SlotName) == false) return false;

	if (GetOwner() == nullptr) return false;

	const FLFPInventorySlotList& InventorySlotList = GetOwner()->GetInventorySlotList();

	if (IsInactive)
	{
		if (InactiveSlotNameList.HasTag(SlotName) == false)
		{
			InactiveSlotNameList.AddTag(SlotName);

			GetOwner()->ProcessInventoryIndex(
				SlotName,
				[&](const FLFPInventoryIndex& InventoryIndex)
				{
					const auto& SlotItem = InventorySlotList.GetSlotItemConst(InventoryIndex);

					/* Skip Empty Item */
					if (SlotItem.IsValid() == false) return false;

					OnUnequipItem.Broadcast(InventoryIndex, SlotItem, SlotItem, EventTag);

					return false;
				});
		}
	}
	else
	{
		if (InactiveSlotNameList.HasTag(SlotName))
		{
			InactiveSlotNameList.RemoveTag(SlotName);

			GetOwner()->ProcessInventoryIndex(
				SlotName,
				[&](const FLFPInventoryIndex& InventoryIndex)
				{
					const auto& SlotItem = InventorySlotList.GetSlotItemConst(InventoryIndex);

					/* Skip Empty Item */
					if (SlotItem.IsValid() == false) return false;

					OnEquipItem.Broadcast(InventoryIndex, SlotItem, SlotItem, EventTag);

					return false;
				});
		}
	}

	return true;
}

void ULFPItemEquipmentFunction::SetSlotNameListInactive(UPARAM(meta = (Categories = "Item.SlotName")) const FGameplayTagContainer SlotNameList, const bool IsInactive, UPARAM(meta = (Categories = "Item.Event"))  const FGameplayTag EventTag)
{
	for (const FGameplayTag& SlotName : SlotNameList)
	{
		SetSlotNameInactive(SlotName, IsInactive, EventTag);
	}

	return;
}

bool ULFPItemEquipmentFunction::IsEquipmentSlot(const FGameplayTag Slot) const
{
	return Slot.MatchesAny(EquipmentSlotNameList);
}

bool ULFPItemEquipmentFunction::IsSlotNameLock(const FGameplayTag Slot) const
{
	return Slot.MatchesAny(LockSlotNameList);
}

bool ULFPItemEquipmentFunction::IsSlotNameInactive(const FGameplayTag Slot) const
{
	return Slot.MatchesAny(InactiveSlotNameList);
}

void ULFPItemEquipmentFunction::OnInventoryUpdateItem(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag)
{
	/* Skip Slot Name Because Not Process By This Module */
	if (IsEquipmentSlot(InventoryIndex.SlotName) == false) return;

	/* Slot Name Don't Trigger Event */
	if (IsSlotNameInactive(InventoryIndex.SlotName)) return;

	if (OldData.IsValid())
	{
		OnUnequipItem.Broadcast(InventoryIndex, NewData, OldData, EventTag);
	}

	if (NewData.IsValid())
	{
		OnEquipItem.Broadcast(InventoryIndex, NewData, OldData, EventTag);
	}
}
