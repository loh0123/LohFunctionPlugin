// Fill out your copyright notice in the Description page of Project Settings.


#include "LFPItemInventoryBasicFunction.h"
#include "LFPItemFunctionLibrary.h"

DEFINE_LOG_CATEGORY(LFPItemInventoryBasicFunction);

bool ULFPItemInventoryBasicFunction::CanAddItem_Implementation(const FLFPInventoryItem& ItemData) const
{
	const FLFPItemBasicData* TableData = GetDataTableRow(ItemData.ItemTag);

	if (TableData == nullptr) return false;

	return true;
}

bool ULFPItemInventoryBasicFunction::CanRemoveItem_Implementation(const FLFPInventoryItem& ItemData) const
{
	const FLFPItemBasicData* TableData = GetDataTableRow(ItemData.ItemTag);

	if (TableData == nullptr) return false;

	return true;
}

bool ULFPItemInventoryBasicFunction::CanSwapItem_Implementation(const FLFPInventoryItem& FromItem, const FLFPInventoryItem& ToItem) const
{
	if (FromItem.IsValid() == false && ToItem.IsValid() == false)
	{
		return false;
	}

	if (FromItem.IsValid())
	{
		const FLFPItemBasicData* TableData = GetDataTableRow(FromItem.ItemTag);

		if (TableData == nullptr) return false;
	}

	if (ToItem.IsValid())
	{
		const FLFPItemBasicData* TableData = GetDataTableRow(ToItem.ItemTag);

		if (TableData == nullptr) return false;
	}

	return true;
}

bool ULFPItemInventoryBasicFunction::CanUpdateItem_Implementation(const FLFPInventoryItem& ItemData) const
{
	const FLFPItemBasicData* TableData = GetDataTableRow(ItemData.ItemTag);

	if (TableData == nullptr) return false;

	return true;
}


bool ULFPItemInventoryBasicFunction::CanAddItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const
{
	// Ensure CurrentData Is Empty Or Match ProcessData Type
	if (CurrentData.ItemTag.IsValid() && CurrentData.ItemTag != ProcessData.ItemTag) return false;

	// Get Table Data ///////////////////////////////
	const FLFPItemBasicData* TableData = GetDataTableRow(ProcessData.ItemTag);

	if (TableData == nullptr) return false;
	//////////////////////////////////////////////////

	/* Check Item Allow On This Index */
	if (TableData->DoItemAllowOnSlot(InventoryIndex.SlotName) == false)
	{
		return false;
	}

	/* Check Item Meta Number Match */
	for (const FGameplayTag& MathIntTag : TableData->MatchIntTagList)
	{
		if (ULFPItemFunctionLibrary::GetMetaDataAsNumber(CurrentData, MathIntTag) != ULFPItemFunctionLibrary::GetMetaDataAsNumber(ProcessData, MathIntTag))
		{
			return false;
		}
	}

	/* Check Item Is Full */
	if (TableData->MaxStack != INDEX_NONE && TableData->StackTag.IsValid() && TableData->MaxStack <= ULFPItemFunctionLibrary::GetMetaDataAsNumber(CurrentData, TableData->StackTag, 1)) return false;

	return true;
}

bool ULFPItemInventoryBasicFunction::CanRemoveItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const
{
	// Ensure CurrentData Is Valid And Match ProcessData Type
	if (CurrentData.ItemTag.IsValid() == false || CurrentData.ItemTag != ProcessData.ItemTag) return false;

	// Get Table Data ///////////////////////////////
	const FLFPItemBasicData* TableData = GetDataTableRow(ProcessData.ItemTag);

	if (TableData == nullptr) return false;
	//////////////////////////////////////////////////

	/* Check Item Meta Number Match */
	for (const FGameplayTag& MathIntTag : TableData->MatchIntTagList)
	{
		if (ULFPItemFunctionLibrary::GetMetaDataAsNumber(CurrentData, MathIntTag) != ULFPItemFunctionLibrary::GetMetaDataAsNumber(ProcessData, MathIntTag))
		{
			return false;
		}
	}

	return true;
}

bool ULFPItemInventoryBasicFunction::CanSwapItemOnSlot_Implementation(const FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, const FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const
{
	const FLFPItemBasicData* FromTableData = GetDataTableRow(FromItem.ItemTag);
	const FLFPItemBasicData* ToTableData = GetDataTableRow(ToItem.ItemTag);

	if (FromTableData != nullptr && FromTableData->DoItemAllowOnSlot(ToIndex.SlotName) == false)
	{
		return false;
	}

	if (ToTableData != nullptr && ToTableData->DoItemAllowOnSlot(FromIndex.SlotName) == false)
	{
		return false;
	}

	return true;
}

bool ULFPItemInventoryBasicFunction::CanUpdateItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const
{
	// Ensure CurrentData Is Valid And Match ProcessData Type
	if (CurrentData.ItemTag.IsValid() == false || CurrentData.ItemTag != ProcessData.ItemTag) return false;

	// Get Table Data ///////////////////////////////
	const FLFPItemBasicData* TableData = GetDataTableRow(ProcessData.ItemTag);

	if (TableData == nullptr) return false;
	//////////////////////////////////////////////////

	/* Check Item Allow On This Index */
	if (TableData->DoItemAllowOnSlot(InventoryIndex.SlotName) == false)
	{
		return false;
	}

	/* Check Item Meta Number Match */
	for (const FGameplayTag& MathIntTag : TableData->MatchIntTagList)
	{
		if (ULFPItemFunctionLibrary::GetMetaDataAsNumber(CurrentData, MathIntTag) != ULFPItemFunctionLibrary::GetMetaDataAsNumber(ProcessData, MathIntTag))
		{
			return false;
		}
	}

	return true;
}

bool ULFPItemInventoryBasicFunction::ProcessAddItem_Implementation(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	// Get Table Data ///////////////////////////////
	const FLFPItemBasicData* TableData = GetDataTableRow(ProcessData.ItemTag);

	if (TableData == nullptr) return true;
	//////////////////////////////////////////////////

	// Process Stack Function ///////////////////////
	const int32 CurrentStack = ItemData.IsValid()		? ULFPItemFunctionLibrary::GetMetaDataAsNumber(ItemData, TableData->StackTag, 1) : 0;
	const int32 ProcessStack = ProcessData.IsValid()	? ULFPItemFunctionLibrary::GetMetaDataAsNumber(ProcessData, TableData->StackTag, 1) : 0;
	const int32 MaxStack = TableData->MaxStack;

	const int32 NextStack =			MaxStack != INDEX_NONE ? FMath::Min(MaxStack, CurrentStack + ProcessStack)			: CurrentStack + ProcessStack;
	const int32 NextProcessStack =	MaxStack != INDEX_NONE ? FMath::Max(0, (CurrentStack + ProcessStack) - NextStack)	: 0;

	// Check Current Slot Is Empty
	if (ItemData.IsValid() == false)
	{
		ItemData = ProcessData; // Override ItemData With ProcessData ( Meta Data Include ) This Give All Meta Data That Is Not Stack Into Inventory ( Only Doing This If The Slot Is Empty )
	}

	ULFPItemFunctionLibrary::SetMetaDataAsNumber(ItemData, TableData->StackTag, NextStack); // Set Item Stack To Correct Number
	ULFPItemFunctionLibrary::SetMetaDataAsNumber(ProcessData, TableData->StackTag, NextProcessStack); // Decrease Stack On Process Data
	////////////////////////////////////////////////

	/* Clear ProcessData Tag If Stack Is Empty To Prevent It Been Treated As 1 Stack */
	if (NextProcessStack <= 0)
	{
		ProcessData = FLFPInventoryItem();
	}

	return NextProcessStack <= 0;
}

bool ULFPItemInventoryBasicFunction::ProcessRemoveItem_Implementation(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	// Get Table Data ///////////////////////////////
	const FLFPItemBasicData* TableData = GetDataTableRow(ProcessData.ItemTag);

	if (TableData == nullptr) return true;
	//////////////////////////////////////////////////

	// Process Stack Function ///////////////////////
	const int32 CurrentStack = ItemData.IsValid()		? ULFPItemFunctionLibrary::GetMetaDataAsNumber(ItemData, TableData->StackTag, 1) : 0;
	const int32 ProcessStack = ProcessData.IsValid()	? ULFPItemFunctionLibrary::GetMetaDataAsNumber(ProcessData, TableData->StackTag, 1) : 0;

	const int32 NextStack =			CurrentStack - ProcessStack;
	const int32 NextProcessStack =	NextStack < 0 ? FMath::Abs(NextStack) : 0;

	ULFPItemFunctionLibrary::SetMetaDataAsNumber(ItemData, TableData->StackTag, FMath::Max(0, NextStack));
	ULFPItemFunctionLibrary::SetMetaDataAsNumber(ProcessData, TableData->StackTag, NextProcessStack);
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

bool ULFPItemInventoryBasicFunction::ProcessSwapItem_Implementation(UPARAM(ref)FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, UPARAM(ref)FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const
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

bool ULFPItemInventoryBasicFunction::ProcessUpdateItem_Implementation(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	// Get Table Data ///////////////////////////////
	const FLFPItemBasicData* TableData = GetDataTableRow(ProcessData.ItemTag);

	if (TableData == nullptr) return true;
	//////////////////////////////////////////////////

	const int32 CurrentStack = ULFPItemFunctionLibrary::GetMetaDataAsNumber(ItemData, TableData->StackTag, 1);
	const int32 ProcessStack = ULFPItemFunctionLibrary::GetMetaDataAsNumber(ProcessData, TableData->StackTag, 1);

	ItemData = ProcessData;

	ULFPItemFunctionLibrary::SetMetaDataAsNumber(ItemData, TableData->StackTag, CurrentStack);
	ULFPItemFunctionLibrary::SetMetaDataAsNumber(ProcessData, TableData->StackTag, ProcessStack - 1);

	/* Clear ProcessData Tag If Stack Is Empty To Prevent It Been Treated As 1 Stack */
	if (ProcessStack - 1 <= 0)
	{
		ProcessData = FLFPInventoryItem();
	}

	return ProcessStack - 1 <= 0;
}

FGameplayTagContainer ULFPItemInventoryBasicFunction::GetItemCatergorize_Implementation(const FLFPInventoryItem& ItemData) const
{
	const FLFPItemBasicData* TableData = GetDataTableRow(ItemData.ItemTag);

	if (TableData == nullptr) return FGameplayTagContainer();

	return TableData->Categorize;
}

FLFPInventorySearch ULFPItemInventoryBasicFunction::GetItemInventorySearch_Implementation(const FLFPInventoryItem& ItemData) const
{
	const FLFPItemBasicData* TableData = GetDataTableRow(ItemData.ItemTag);

	if (TableData == nullptr) return FLFPInventorySearch();

	return TableData->AllowedInventorySearch;
}

const FLFPItemBasicData* ULFPItemInventoryBasicFunction::GetDataTableRow(const FGameplayTag& RowTag) const
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
