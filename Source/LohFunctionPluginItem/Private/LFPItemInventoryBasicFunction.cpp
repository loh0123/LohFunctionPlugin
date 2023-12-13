// Fill out your copyright notice in the Description page of Project Settings.


#include "LFPItemInventoryBasicFunction.h"
#include "LFPItemFunctionLibrary.h"

DEFINE_LOG_CATEGORY(LFPItemInventoryBasicFunction);

bool ULFPItemInventoryBasicFunction::CanAddItem_Implementation(const FLFPInventoryItem& ItemData) const
{
	const FLFPItemBasicData* TableData = GetDataTableRow(ItemData.ItemTag);

	if (TableData == nullptr) return false;

	return ItemData.IsValid();
}

bool ULFPItemInventoryBasicFunction::CanRemoveItem_Implementation(const FLFPInventoryItem& ItemData) const
{
	const FLFPItemBasicData* TableData = GetDataTableRow(ItemData.ItemTag);

	if (TableData == nullptr) return false;

	return ItemData.IsValid();
}

bool ULFPItemInventoryBasicFunction::CanAddItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const
{
	// Ensure CurrentData Is Empty Or Match ProcessData Type
	if (CurrentData.ItemTag.IsValid() && CurrentData.ItemTag != ProcessData.ItemTag) return false;

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

bool ULFPItemInventoryBasicFunction::ProcessAddItem_Implementation(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	// Get Table Data ///////////////////////////////
	const FLFPItemBasicData* TableData = GetDataTableRow(ItemData.ItemTag);

	if (TableData == nullptr) return false;
	//////////////////////////////////////////////////

	// Process Stack Function ///////////////////////
	const int32 CurrentStack = ItemData.IsValid()		? ULFPItemFunctionLibrary::GetMetaDataAsNumber(ItemData, TableData->StackTag, 1) : 0;
	const int32 ProcessStack = ProcessData.IsValid()	? ULFPItemFunctionLibrary::GetMetaDataAsNumber(ProcessData, TableData->StackTag, 1) : 0;
	const int32 MaxStack = TableData->MaxStack;

	const int32 NextStack =			MaxStack != INDEX_NONE ? FMath::Min(MaxStack, CurrentStack + ProcessStack)			: CurrentStack + ProcessStack;
	const int32 NextProcessStack =	MaxStack != INDEX_NONE ? FMath::Max(0, (CurrentStack + ProcessStack) - NextStack)	: 0;

	ItemData.ItemTag = ProcessData.ItemTag; // Override The Tag If Empty

	ULFPItemFunctionLibrary::MergeMetaData(ItemData, ProcessData); // Merge Other Tag On ProcessData Together
	ULFPItemFunctionLibrary::SetMetaDataAsNumber(ItemData, TableData->StackTag, NextStack);
	ULFPItemFunctionLibrary::SetMetaDataAsNumber(ProcessData, TableData->StackTag, NextProcessStack);
	////////////////////////////////////////////////

	/* Clear ProcessData Tag If Stack Is Empty To Prevent It Been Treated As 1 Stack */
	if (NextProcessStack <= 0)
	{
		ProcessData.ItemTag = FGameplayTag::EmptyTag;
	}

	return NextProcessStack == 0;
}

bool ULFPItemInventoryBasicFunction::ProcessRemoveItem_Implementation(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	// Get Table Data ///////////////////////////////
	const FLFPItemBasicData* TableData = GetDataTableRow(ItemData.ItemTag);

	if (TableData == nullptr) return false;
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
		ProcessData.ItemTag = FGameplayTag::EmptyTag;
	}

	return NextProcessStack == 0;
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

	return TableData->InventorySearch;
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
