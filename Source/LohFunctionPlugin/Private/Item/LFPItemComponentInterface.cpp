// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#include "Item/LFPItemComponentInterface.h"

// Add default functionality here for any ILFPInventoryRelatedInterface functions that are not pure virtual.

ULFPInventoryComponent* ILFPItemComponentInterface::GetInventoryComponent_Implementation()
{
	return nullptr;
}

ULFPEquipmentComponent* ILFPItemComponentInterface::GetEquipmentComponent_Implementation()
{
	return nullptr;
}

TArray<ULFPItemMutatorComponent*> ILFPItemComponentInterface::GetItemMutatorComponent_Implementation()
{
	return TArray<ULFPItemMutatorComponent*>();
}
