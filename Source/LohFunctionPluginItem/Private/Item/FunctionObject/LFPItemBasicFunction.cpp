// Copyright (c) 2023-2024 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#include "Item/FunctionObject/LFPItemBasicFunction.h"
#include "LFPItemFunctionLibrary.h"

bool ULFPItemBasicFunction::CanAddItem_Implementation(const FLFPInventoryItem& ItemData) const
{
	return GetDataTableRow(ItemData.ItemTag) != nullptr;
}

bool ULFPItemBasicFunction::CanRemoveItem_Implementation(const FLFPInventoryItem& ItemData) const
{
	return GetDataTableRow(ItemData.ItemTag) != nullptr;
}

bool ULFPItemBasicFunction::CanSwapItem_Implementation(const FLFPInventoryItem& FromItem, const FLFPInventoryItem& ToItem) const
{
	const FLFPItemBasicData* FromTableData = GetDataTableRow(FromItem.ItemTag);
	const FLFPItemBasicData* ToTableData = GetDataTableRow(ToItem.ItemTag);

	return FromTableData != nullptr || ToTableData != nullptr;
}

bool ULFPItemBasicFunction::CanUpdateItem_Implementation(const FLFPInventoryItem& ItemData) const
{
	return GetDataTableRow(ItemData.ItemTag) != nullptr;
}

bool ULFPItemBasicFunction::CanContainItem_Implementation(const FLFPInventoryItem& ItemData) const
{
	return GetDataTableRow(ItemData.ItemTag) != nullptr;
}


bool ULFPItemBasicFunction::CanAddItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const
{
	// Ensure CurrentData Is Empty Or Match ProcessData Type
	if (CurrentData.ItemTag.IsValid() && CurrentData.ItemTag != ProcessData.ItemTag) return false;

	// Get Table Data ///////////////////////////////
	const FLFPItemBasicData* TableData = GetDataTableRow(ProcessData.ItemTag);

	if (TableData == nullptr) return true;
	//////////////////////////////////////////////////

	if (TableData->DoItemAllowOnSlot(InventoryIndex.SlotName) == false) return false; // Check AllowOnSlot Because The CurrentData Migth Be Empty

	if (TableData->DoItemMetaMatch(CurrentData, ProcessData) == false) return false;

	if (TableData->DoItemReachMaxStack(CurrentData)) return false;

	return true;
}

bool ULFPItemBasicFunction::CanRemoveItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const
{
	// Ensure CurrentData Is Valid And Match ProcessData Type
	if (CurrentData.ItemTag.IsValid() == false || CurrentData.ItemTag != ProcessData.ItemTag) return false;

	// Get Table Data ///////////////////////////////
	const FLFPItemBasicData* TableData = GetDataTableRow(ProcessData.ItemTag);

	if (TableData == nullptr) return true;
	//////////////////////////////////////////////////

	if (TableData->DoItemMetaMatch(CurrentData, ProcessData) == false) return false;

	return true;
}

bool ULFPItemBasicFunction::CanSwapItemOnSlot_Implementation(const FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, const FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const
{
	const FLFPItemBasicData* FromTableData = GetDataTableRow(FromItem.ItemTag);
	const FLFPItemBasicData* ToTableData = GetDataTableRow(ToItem.ItemTag);

	if (FromTableData != nullptr && FromTableData->DoItemAllowOnSlot(ToIndex.SlotName) == false) return false;

	if (ToTableData != nullptr && ToTableData->DoItemAllowOnSlot(FromIndex.SlotName) == false) return false;

	return true;
}

bool ULFPItemBasicFunction::CanUpdateItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const
{
	// Ensure CurrentData Is Valid And Match ProcessData Type
	if (CurrentData.ItemTag.IsValid() == false || CurrentData.ItemTag != ProcessData.ItemTag) return false;

	// Get Table Data ///////////////////////////////
	const FLFPItemBasicData* TableData = GetDataTableRow(ProcessData.ItemTag);

	if (TableData == nullptr) return true;
	//////////////////////////////////////////////////

	if (TableData->DoItemMetaMatch(CurrentData, ProcessData) == false) return false;

	return true;
}

bool ULFPItemBasicFunction::CanContainItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const
{
	// Ensure CurrentData Is Valid And Match ProcessData Type
	if (CurrentData.ItemTag.IsValid() == false || CurrentData.ItemTag != ProcessData.ItemTag) return false;

	// Get Table Data ///////////////////////////////
	const FLFPItemBasicData* TableData = GetDataTableRow(ProcessData.ItemTag);

	if (TableData == nullptr) return true;
	//////////////////////////////////////////////////

	if (TableData->DoItemMetaMatch(CurrentData, ProcessData) == false) return false;

	return true;
}


bool ULFPItemBasicFunction::ProcessAddItem_Implementation(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	// Get Table Data ///////////////////////////////
	const FLFPItemBasicData* TableData = GetDataTableRow(ProcessData.ItemTag);

	if (TableData == nullptr) return true;
	//////////////////////////////////////////////////

	// Process Stack Function ///////////////////////
	const int32 CurrentStack = ItemData.IsValid()		? TableData->GetStackAmount(ItemData)		: 0;
	const int32 ProcessStack = ProcessData.IsValid()	? TableData->GetStackAmount(ProcessData)	: 0;

	const int32 NextStack =			TableData->ClampToMaxStack(CurrentStack + ProcessStack);
	const int32 NextProcessStack =	(CurrentStack + ProcessStack) - NextStack;

	// Check Current Slot Is Empty
	if (ItemData.IsValid() == false)
	{
		ItemData = ProcessData; // Override ItemData With ProcessData ( Meta Data Include ) This Give All Meta Data That Is Not Stack Into Inventory ( Only Doing This If The Slot Is Empty )
	}

	TableData->SetStackAmount(ItemData, NextStack); // Set Item Stack To Correct Number
	TableData->SetStackAmount(ProcessData, NextProcessStack); // Decrease Stack On Process Data
	////////////////////////////////////////////////

	/* Clear ProcessData Tag If Stack Is Empty To Prevent It Been Treated As 1 Stack */
	if (NextProcessStack <= 0)
	{
		ProcessData = FLFPInventoryItem();
	}

	return NextProcessStack <= 0;
}

bool ULFPItemBasicFunction::ProcessRemoveItem_Implementation(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	// Get Table Data ///////////////////////////////
	const FLFPItemBasicData* TableData = GetDataTableRow(ProcessData.ItemTag);

	if (TableData == nullptr) return true;
	//////////////////////////////////////////////////

	// Process Stack Function ///////////////////////
	const int32 CurrentStack = ItemData.IsValid()		? TableData->GetStackAmount(ItemData)		: 0;
	const int32 ProcessStack = ProcessData.IsValid()	? TableData->GetStackAmount(ProcessData)	: 0;

	const int32 NextStack =			CurrentStack - ProcessStack;
	const int32 NextProcessStack =	NextStack < 0 ? FMath::Abs(NextStack) : 0;

	TableData->SetStackAmount(ItemData, NextStack);
	TableData->SetStackAmount(ProcessData, NextProcessStack);
	////////////////////////////////////////////////

	/* If Stack Is Going To Be Empty Than Clear Item */
	if (NextStack <= 0)
	{
		ItemData = FLFPInventoryItem();
	}

	/* Clear ProcessData Tag If Stack Is Empty To Prevent It Been Treated As 1 Stack */
	if (NextProcessStack <= 0)
	{
		ProcessData = FLFPInventoryItem();
	}

	return NextProcessStack <= 0;
}

bool ULFPItemBasicFunction::ProcessSwapItem_Implementation(UPARAM(ref)FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, UPARAM(ref)FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const
{
	if (FromItem.MatchesTag(ToItem.ItemTag) && CanAddItemOnSlot(ToIndex, ToItem, FromItem))
	{
		return ProcessAddItem(ToItem, FromItem, ToIndex);
	}

	FLFPInventoryItem TempItem = FromItem;

	FromItem = ToItem;
	ToItem = TempItem;

	return true;
}

bool ULFPItemBasicFunction::ProcessUpdateItem_Implementation(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	// Get Table Data ///////////////////////////////
	const FLFPItemBasicData* TableData = GetDataTableRow(ProcessData.ItemTag);

	if (TableData == nullptr) return true;
	//////////////////////////////////////////////////

	const int32 CurrentStack = ItemData.IsValid() ? TableData->GetStackAmount(ItemData) : 0;
	const int32 ProcessStack = ProcessData.IsValid() ? TableData->GetStackAmount(ProcessData) : 0;

	ItemData = ProcessData; // Override

	TableData->SetStackAmount(ItemData, CurrentStack);
	TableData->SetStackAmount(ProcessData, ProcessStack - 1);

	/* Clear ProcessData Tag If Stack Is Empty To Prevent It Been Treated As 1 Stack */
	if (ProcessStack - 1 <= 0) ProcessData = FLFPInventoryItem();

	return ProcessStack - 1 <= 0;
}

bool ULFPItemBasicFunction::ProcessContainItem_Implementation(const FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	// Get Table Data ///////////////////////////////
	const FLFPItemBasicData* TableData = GetDataTableRow(ProcessData.ItemTag);

	if (TableData == nullptr) return true;
	//////////////////////////////////////////////////

	// Process Stack Function ///////////////////////
	const int32 CurrentStack = ItemData.IsValid()		? TableData->GetStackAmount(ItemData)		: 0;
	const int32 ProcessStack = ProcessData.IsValid()	? TableData->GetStackAmount(ProcessData)	: 0;

	const int32 NextStack = CurrentStack - ProcessStack;
	const int32 NextProcessStack = NextStack < 0 ? FMath::Abs(NextStack) : 0;

	TableData->SetStackAmount(ProcessData, NextProcessStack);
	////////////////////////////////////////////////

	/* Clear ProcessData Tag If Stack Is Empty To Prevent It Been Treated As 1 Stack */
	if (NextProcessStack <= 0)
	{
		ProcessData = FLFPInventoryItem();
	}

	return NextProcessStack <= 0;
}


FGameplayTagContainer ULFPItemBasicFunction::GetItemCatergorize_Implementation(const FLFPInventoryItem& ItemData) const
{
	const FLFPItemBasicData* TableData = GetDataTableRow(ItemData.ItemTag);

	if (TableData == nullptr) return FGameplayTagContainer();

	return TableData->GetCategorize();
}

FLFPInventorySearch ULFPItemBasicFunction::GetItemInventorySearch_Implementation(const FLFPInventoryItem& ItemData) const
{
	const FLFPItemBasicData* TableData = GetDataTableRow(ItemData.ItemTag);

	if (TableData == nullptr) return FLFPInventorySearch();

	return TableData->GetAllowedInventorySearch();
}

bool ULFPItemBasicFunction::CanItemSortHigherThan_Implementation(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB, const FGameplayTag& SortTag) const
{
	return ItemDataA.IsValid() && ItemDataB.IsValid() == false;
}

const FLFPItemBasicData* ULFPItemBasicFunction::GetDataTableRow(const FGameplayTag& RowTag) const
{
	uint8* TableRawData = ItemDataTable->FindRowUnchecked(RowTag.GetTagName());

	if (TableRawData == nullptr)
	{
		return nullptr; // Item Not Exist
	}

	const FLFPItemBasicData* TableData = reinterpret_cast<FLFPItemBasicData*>(TableRawData);

	if (TableData == nullptr)
	{
		return nullptr; // Item Not Same Type
	}

	return TableData;
}
