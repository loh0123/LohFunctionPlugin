// Fill out your copyright notice in the Description page of Project Settings.


#include "LFPItemInventoryBasicFunction.h"

bool ULFPItemInventoryBasicFunction::CanAddItem_Implementation(const FLFPInventoryChange& ChangeData) const
{
	return false;
}

bool ULFPItemInventoryBasicFunction::CanRemoveItem_Implementation(const FLFPInventoryChange& ChangeData) const
{
	return false;
}

bool ULFPItemInventoryBasicFunction::CanSwapItem_Implementation(const FLFPInventoryChange& ChangeDataA, const FLFPInventoryChange& ChangeDataB) const
{
	return false;
}

bool ULFPItemInventoryBasicFunction::ProcessAddItem_Implementation(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	return false;
}

bool ULFPItemInventoryBasicFunction::ProcessRemoveItem_Implementation(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	return false;
}

bool ULFPItemInventoryBasicFunction::ProcessSwapItem_Implementation(UPARAM(ref)FLFPInventoryItem& ItemDataA, const FLFPInventoryIndex& InventoryIndexA, UPARAM(ref)FLFPInventoryItem& ItemDataB, const FLFPInventoryIndex& InventoryIndexB) const
{
	return false;
}

FGameplayTagContainer ULFPItemInventoryBasicFunction::GetInventoryIndexCatergorize_Implementation(const FLFPInventoryChange& ChangeData) const
{
	return FGameplayTagContainer();
}

bool ULFPItemInventoryBasicFunction::CanItemSortHigherThan_Implementation(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB, const FGameplayTag& SortTag) const
{
	return false;
}

bool ULFPItemInventoryBasicFunction::CanItemUseInventoryIndex_Implementation(const FLFPInventoryChange& ChangeData, const ELFPInventoryOperation Operation) const
{
	return true;
}

bool ULFPItemInventoryBasicFunction::DoInventoryIndexContainItem_Implementation(const FLFPInventoryChange& ChangeData) const
{
	return IsValid(GetOwner()) ? GetOwner()->GetSlotItem(ChangeData.InventoryIndex) == ChangeData.ItemData : false;
}
