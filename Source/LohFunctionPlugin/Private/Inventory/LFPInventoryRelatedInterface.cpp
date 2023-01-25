// Copyright by Loh Zhi Kang


#include "Inventory/LFPInventoryRelatedInterface.h"

// Add default functionality here for any ILFPInventoryRelatedInterface functions that are not pure virtual.

ULFPInventoryComponent* ILFPInventoryRelatedInterface::GetInventoryComponent_Implementation()
{
	return nullptr;
}

ULFPEquipmentComponent* ILFPInventoryRelatedInterface::GetEquipmentComponent_Implementation()
{
	return nullptr;
}

TArray<ULFPItemMutatorComponent*> ILFPInventoryRelatedInterface::GetItemMutatorComponent_Implementation()
{
	return TArray<ULFPItemMutatorComponent*>();
}
