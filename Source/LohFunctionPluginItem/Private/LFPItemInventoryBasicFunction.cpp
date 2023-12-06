// Fill out your copyright notice in the Description page of Project Settings.


#include "LFPItemInventoryBasicFunction.h"

bool ULFPItemInventoryBasicFunction::CanAddItem_Implementation(const ULFPInventoryComponent* InventoryComponent, const FLFPInventoryChange& ChangeData) const
{
	return false;
}

bool ULFPItemInventoryBasicFunction::CanRemoveItem_Implementation(const ULFPInventoryComponent* InventoryComponent, const FLFPInventoryChange& ChangeData) const
{
	return false;
}

bool ULFPItemInventoryBasicFunction::CanSwapItem_Implementation(const ULFPInventoryComponent* InventoryComponent, const FLFPInventoryChange& ChangeDataA, const FLFPInventoryChange& ChangeDataB) const
{
	return false;
}

bool ULFPItemInventoryBasicFunction::ProcessAddItem_Implementation(const ULFPInventoryComponent* InventoryComponent, UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	return false;
}

bool ULFPItemInventoryBasicFunction::ProcessRemoveItem_Implementation(const ULFPInventoryComponent* InventoryComponent, UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	return false;
}

bool ULFPItemInventoryBasicFunction::ProcessSwapItem_Implementation(const ULFPInventoryComponent* InventoryComponent, UPARAM(ref)FLFPInventoryItem& ItemDataA, const FLFPInventoryIndex& InventoryIndexA, UPARAM(ref)FLFPInventoryItem& ItemDataB, const FLFPInventoryIndex& InventoryIndexB) const
{
	return false;
}

FGameplayTagContainer ULFPItemInventoryBasicFunction::GetInventoryIndexCatergorize_Implementation(const ULFPInventoryComponent* InventoryComponent, const FLFPInventoryChange& ChangeData) const
{
	return FGameplayTagContainer();
}
