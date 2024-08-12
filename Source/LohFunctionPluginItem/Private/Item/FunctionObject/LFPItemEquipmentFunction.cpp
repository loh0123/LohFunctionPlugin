// Copyright (c) 2023-2024 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#include "Item/FunctionObject/LFPItemEquipmentFunction.h"
#include "Net/UnrealNetwork.h"

void ULFPItemEquipmentFunction::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ULFPItemEquipmentFunction, SelectorList);

	DOREPLIFETIME(ULFPItemEquipmentFunction, LockSlotNameList);

	DOREPLIFETIME(ULFPItemEquipmentFunction, InactiveSlotNameList);
}

void ULFPItemEquipmentFunction::InitializeComponent()
{
	Super::InitializeComponent();

	GetOwner()->OnItemChange.AddDynamic(this, &ULFPItemEquipmentFunction::OnInventoryUpdateItem);
}

void ULFPItemEquipmentFunction::UninitializeComponent()
{
	Super::UninitializeComponent();

	GetOwner()->OnItemChange.RemoveDynamic(this, &ULFPItemEquipmentFunction::OnInventoryUpdateItem);
}

bool ULFPItemEquipmentFunction::CanAddItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const
{
	/* Skip Slot Name Because Not Process By This Module */
	if (IsEquipmentSlot(InventoryIndex.SlotName) == false) return true;

	if (IsSlotNameLock(InventoryIndex.SlotName)) return false;

	const FLFPItemEquipmentData* TableData = GetDataTableRow(ProcessData.GetItemTag());

	if (TableData == nullptr) return false;

	/* Is Item Not Suppose To Be On This Index  */
	if (TableData->IsInventoryIndexAllow(InventoryIndex) == false) return false;

	return true;
}

bool ULFPItemEquipmentFunction::CanRemoveItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const
{
	/* Skip Slot Name Because Not Process By This Module */
	if (IsEquipmentSlot(InventoryIndex.SlotName) == false) return true;

	if (IsSlotNameLock(InventoryIndex.SlotName)) return false;

	const FLFPItemEquipmentData* TableData = GetDataTableRow(ProcessData.GetItemTag());

	if (TableData == nullptr) return false;

	/* Is Item Not Suppose To Be On This Index  */
	if (TableData->IsInventoryIndexAllow(InventoryIndex) == false) return false;

	return true;
}

bool ULFPItemEquipmentFunction::CanSwapItemOnSlot_Implementation(const FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, const FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const
{
	/* Skip Slot Name Because Not Process By This Module */
	if (IsEquipmentSlot(FromIndex.SlotName))
	{
		if (IsSlotNameLock(FromIndex.SlotName)) return false;

		const FLFPItemEquipmentData* TableData = GetDataTableRow(FromItem.GetItemTag());

		if (TableData == nullptr) return false;

		/* Is Item Not Suppose To Be On This Index  */
		if (TableData->IsInventoryIndexAllow(ToIndex) == false) return false;
	}

	/* Skip Slot Name Because Not Process By This Module */
	if (IsEquipmentSlot(ToIndex.SlotName))
	{
		if (IsSlotNameLock(ToIndex.SlotName)) return false;

		const FLFPItemEquipmentData* TableData = GetDataTableRow(ToItem.GetItemTag());

		if (TableData == nullptr) return false;

		/* Is Item Not Suppose To Be On This Index  */
		if (TableData->IsInventoryIndexAllow(FromIndex) == false) return false;
	}

	return true;
}

bool ULFPItemEquipmentFunction::CanSlotNameBeSort_Implementation(const FGameplayTag& SlotName) const
{
	/* Equipment Slot Can't Be Sort */
	return IsEquipmentSlot(SlotName) == false;
}

void ULFPItemEquipmentFunction::SendSelectorDelegateEvent(const FGameplayTag& SlotName, const int32 OldIndex, const int32 NewIndex, const FGameplayTag& EventTag) const
{
	if (GetOwner()->GetOwner()->GetLocalRole() != ROLE_Authority) return;

	const auto& OldEquipment = GetOwner()->GetSlotItem(FLFPInventoryIndex(OldIndex, SlotName));
	const auto& NewEquipment = GetOwner()->GetSlotItem(FLFPInventoryIndex(NewIndex, SlotName));

	if (OldEquipment.IsValid())
	{
		OnUnequipItem.Broadcast(
			FLFPInventoryItemOperationData(
				ELFPInventoryItemEvent::Inventory_None,
				FLFPInventoryIndex(OldIndex, SlotName),
				OldEquipment,
				OldEquipment,
				EventTag
			)
		);
	}

	if (NewEquipment.IsValid())
	{
		OnEquipItem.Broadcast(
			FLFPInventoryItemOperationData(
				ELFPInventoryItemEvent::Inventory_None,
				FLFPInventoryIndex(NewIndex, SlotName),
				NewEquipment,
				NewEquipment,
				EventTag
			)
		);
	}

	OnSlotSelectionChanged.Broadcast(SlotName, OldIndex, NewIndex, EventTag);

	CLIENT_SendSelectorDelegateEvent(SlotName, OldIndex, NewIndex, EventTag);
}

void ULFPItemEquipmentFunction::SendSlotLockChanged(const FGameplayTag& SlotName, const bool IsLock, const FGameplayTag& EventTag) const
{
	OnSlotLockChanged.Broadcast(SlotName, IsLock, EventTag);

	CLIENT_SendSlotLockChanged(SlotName, IsLock, EventTag);
}

void ULFPItemEquipmentFunction::SendSlotActiveChanged(const FGameplayTag& SlotName, const bool IsInactive, const FGameplayTag& EventTag) const
{
	const FLFPInventorySlotList& InventorySlotList = GetOwner()->GetInventorySlotList();

	if (IsInactive)
	{
		GetOwner()->ProcessInventoryIndex(
			SlotName.GetSingleTagContainer(),
			[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex)
			{
				const auto& SlotItem = InventorySlotList.GetSlotItemConst(InventoryInternalIndex);

				/* Skip Empty Item */
				if (SlotItem.IsValid() == false) return false;

				OnUnequipItem.Broadcast(FLFPInventoryItemOperationData(ELFPInventoryItemEvent::Inventory_None, InventoryIndex, SlotItem, SlotItem, EventTag));

				return false;
			});
	}
	else
	{
		GetOwner()->ProcessInventoryIndex(
			SlotName.GetSingleTagContainer(),
			[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex)
			{
				const auto& SlotItem = InventorySlotList.GetSlotItemConst(InventoryInternalIndex);

				/* Skip Empty Item */
				if (SlotItem.IsValid() == false) return false;

				OnEquipItem.Broadcast(FLFPInventoryItemOperationData(ELFPInventoryItemEvent::Inventory_None, InventoryIndex, SlotItem, SlotItem, EventTag));

				return false;
			});
	}

	OnSlotActiveChanged.Broadcast(SlotName, IsInactive, EventTag);

	CLIENT_SendSlotActiveChanged(SlotName, IsInactive, EventTag);
}

void ULFPItemEquipmentFunction::CLIENT_SendSelectorDelegateEvent_Implementation(const FGameplayTag& SlotName, const int32 OldIndex, const int32 NewIndex, const FGameplayTag& EventTag) const
{
	const auto& OldEquipment = GetOwner()->GetSlotItem(FLFPInventoryIndex(OldIndex, SlotName));
	const auto& NewEquipment = GetOwner()->GetSlotItem(FLFPInventoryIndex(NewIndex, SlotName));

	if (OldEquipment.IsValid())
	{
		OnUnequipItem.Broadcast(
			FLFPInventoryItemOperationData(
				ELFPInventoryItemEvent::Inventory_None,
				FLFPInventoryIndex(OldIndex, SlotName),
				OldEquipment,
				OldEquipment,
				EventTag
				)
		);
	}

	if (NewEquipment.IsValid())
	{
		OnEquipItem.Broadcast(
			FLFPInventoryItemOperationData(
				ELFPInventoryItemEvent::Inventory_None,
				FLFPInventoryIndex(NewIndex, SlotName),
				NewEquipment,
				NewEquipment,
				EventTag
			)
		);
	}

	OnSlotSelectionChanged.Broadcast(SlotName, OldIndex, NewIndex, EventTag);
}

void ULFPItemEquipmentFunction::CLIENT_SendSlotLockChanged_Implementation(const FGameplayTag& SlotName, const bool IsLock, const FGameplayTag& EventTag) const
{
	OnSlotLockChanged.Broadcast(SlotName, IsLock, EventTag);
}

void ULFPItemEquipmentFunction::CLIENT_SendSlotActiveChanged_Implementation(const FGameplayTag& SlotName, const bool IsInactive, const FGameplayTag& EventTag) const
{
	const FLFPInventorySlotList& InventorySlotList = GetOwner()->GetInventorySlotList();

	if (IsInactive)
	{
		GetOwner()->ProcessInventoryIndex(
			SlotName.GetSingleTagContainer(),
			[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex)
			{
				const auto& SlotItem = InventorySlotList.GetSlotItemConst(InventoryInternalIndex);

				/* Skip Empty Item */
				if (SlotItem.IsValid() == false) return false;

				OnUnequipItem.Broadcast(FLFPInventoryItemOperationData(ELFPInventoryItemEvent::Inventory_None, InventoryIndex, SlotItem, SlotItem, EventTag));

				return false;
			});
	}
	else
	{
		GetOwner()->ProcessInventoryIndex(
			SlotName.GetSingleTagContainer(),
			[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex)
			{
				const auto& SlotItem = InventorySlotList.GetSlotItemConst(InventoryInternalIndex);

				/* Skip Empty Item */
				if (SlotItem.IsValid() == false) return false;

				OnEquipItem.Broadcast(FLFPInventoryItemOperationData(ELFPInventoryItemEvent::Inventory_None, InventoryIndex, SlotItem, SlotItem, EventTag));

				return false;
			});
	}

	OnSlotActiveChanged.Broadcast(SlotName, IsInactive, EventTag);
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


bool ULFPItemEquipmentFunction::SelectIndex(const FLFPInventoryIndex& InventoryIndex, const FGameplayTag EventTag)
{
	if (IsValid(GetOwner()) == false || GetOwner()->IsInventoryIndexValid(InventoryIndex) == false)
	{
		return false;
	}

	const auto SelectorPtr = SelectorList.FindByPredicate([&](const FLFPItemEquipmentSelector& Selector) {return Selector.IsEquipmentSlotNameMatch(InventoryIndex.SlotName); });

	if (SelectorPtr == nullptr)
	{
		return false;
	}

	const int32 OldIndex = SelectorPtr->GetCurrentSelection();

	SelectorPtr->SetCurrentSelection(InventoryIndex.SlotItemIndex);

	SendSelectorDelegateEvent(SelectorPtr->GetEquipmentSlotName(), OldIndex, SelectorPtr->GetCurrentSelection(), EventTag);

	return true;
}


bool ULFPItemEquipmentFunction::SetSlotNameLock(UPARAM(meta = (Categories = "Item.SlotName")) const FGameplayTag SlotName, const bool IsLock,  const FGameplayTag EventTag)
{
	/* Skip Slot Name Because Not Process By This Module */
	if (IsEquipmentSlot(SlotName) == false) return false;

	if (GetOwner() == nullptr) return false;

	if (IsLock == (LockSlotNameList.HasTag(SlotName) == false))
	{
		if (IsLock)
		{
			LockSlotNameList.AddTag(SlotName);
		}
		else
		{
			LockSlotNameList.RemoveTag(SlotName);
		}

		SendSlotLockChanged(SlotName, IsLock, EventTag);
	}

	return true;
}

void ULFPItemEquipmentFunction::SetSlotNameListLock(UPARAM(meta = (Categories = "Item.SlotName")) const FGameplayTagContainer SlotNameList, const bool IsLock,  const FGameplayTag EventTag)
{
	for (const FGameplayTag& SlotName : SlotNameList)
	{
		SetSlotNameLock(SlotName, IsLock, EventTag);
	}

	return;
}

bool ULFPItemEquipmentFunction::SetSlotNameInactive(UPARAM(meta = (Categories = "Item.SlotName")) const FGameplayTag SlotName, const bool IsInactive,  const FGameplayTag EventTag)
{
	/* Skip Slot Name Because Not Process By This Module */
	if (IsEquipmentSlot(SlotName) == false) return false;

	if (GetOwner() == nullptr) return false;

	if (IsInactive == (InactiveSlotNameList.HasTag(SlotName) == false))
	{
		if (IsInactive) 
		{
			InactiveSlotNameList.AddTag(SlotName);
		}
		else
		{
			InactiveSlotNameList.RemoveTag(SlotName);
		}

		SendSlotActiveChanged(SlotName, IsInactive, EventTag);
	}

	return true;
}

void ULFPItemEquipmentFunction::SetSlotNameListInactive(UPARAM(meta = (Categories = "Item.SlotName")) const FGameplayTagContainer SlotNameList, const bool IsInactive,  const FGameplayTag EventTag)
{
	for (const FGameplayTag& SlotName : SlotNameList)
	{
		SetSlotNameInactive(SlotName, IsInactive, EventTag);
	}

	return;
}


bool ULFPItemEquipmentFunction::IsIndexSelected(const FLFPInventoryIndex& InventoryIndex) const
{
	const int32 SelectedIndex = GetSelectedIndex(InventoryIndex.SlotName);

	if (SelectedIndex == INDEX_NONE)
	{
		return false;
	}

	return SelectedIndex == InventoryIndex.SlotItemIndex;
}

bool ULFPItemEquipmentFunction::IsSelectorSlot(const FGameplayTag Slot) const
{
	return SelectorList.ContainsByPredicate([&](const FLFPItemEquipmentSelector& Selector) {return Selector.IsEquipmentSlotNameMatch(Slot); });
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

int32 ULFPItemEquipmentFunction::GetSelectedIndex(const FGameplayTag Slot) const
{
	const auto SelectorPtr = SelectorList.FindByPredicate(
		[&](const FLFPItemEquipmentSelector& Selector) 
		{
			return Selector.IsEquipmentSlotNameMatch(Slot); 
		}
	);

	if (SelectorPtr == nullptr)
	{
		return INDEX_NONE;
	}

	return SelectorPtr->GetCurrentSelection();
}

void ULFPItemEquipmentFunction::OnInventoryUpdateItem(const FLFPInventoryItemOperationData& ItemOperationData)
{
	/* Skip Slot Name Because Not Process By This Module */
	if (IsEquipmentSlot(ItemOperationData.InventoryIndex.SlotName) == false) return;

	/* Slot Name Don't Trigger Event */
	if (IsSlotNameInactive(ItemOperationData.InventoryIndex.SlotName)) return;

	/* Not Currently Selected */
	if (IsSelectorSlot(ItemOperationData.InventoryIndex.SlotName) && IsIndexSelected(ItemOperationData.InventoryIndex) == false) return;

	if (ItemOperationData.OldData.IsValid())
	{
		OnUnequipItem.Broadcast(ItemOperationData);
	}

	if (ItemOperationData.NewData.IsValid())
	{
		OnEquipItem.Broadcast(ItemOperationData);
	}
}
