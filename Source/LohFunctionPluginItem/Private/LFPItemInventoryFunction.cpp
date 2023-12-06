// Fill out your copyright notice in the Description page of Project Settings.


#include "LFPItemInventoryFunction.h"
#include "Item/LFPInventoryComponent.h"

bool ULFPItemInventoryFunction::CanAddItem_Implementation(const ULFPInventoryComponent* InventoryComponent, const FLFPInventoryChange& ChangeData) const
{
	return true;
}

bool ULFPItemInventoryFunction::CanRemoveItem_Implementation(const ULFPInventoryComponent* InventoryComponent, const FLFPInventoryChange& ChangeData) const
{
	return true;
}

bool ULFPItemInventoryFunction::CanSwapItem_Implementation(const ULFPInventoryComponent* InventoryComponent, const FLFPInventoryChange& ChangeDataA, const FLFPInventoryChange& ChangeDataB) const
{
	return true;
}

bool ULFPItemInventoryFunction::ProcessAddItem_Implementation(const ULFPInventoryComponent* InventoryComponent, UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	return true;
}

bool ULFPItemInventoryFunction::ProcessRemoveItem_Implementation(const ULFPInventoryComponent* InventoryComponent, UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	return true;
}

bool ULFPItemInventoryFunction::ProcessSwapItem_Implementation(const ULFPInventoryComponent* InventoryComponent, UPARAM(ref)FLFPInventoryItem& ItemDataA, const FLFPInventoryIndex& InventoryIndexA, UPARAM(ref)FLFPInventoryItem& ItemDataB, const FLFPInventoryIndex& InventoryIndexB) const
{
	return true;
}

FGameplayTagContainer ULFPItemInventoryFunction::GetInventoryIndexCatergorize_Implementation(const ULFPInventoryComponent* InventoryComponent, const FLFPInventoryChange& ChangeData) const
{
	return FGameplayTagContainer();
}
