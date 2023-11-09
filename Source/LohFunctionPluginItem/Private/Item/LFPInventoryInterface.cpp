// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#include "Item/LFPInventoryInterface.h"

bool ILFPInventoryInterface::CanInventoryAddItem_Implementation() const
{
    return true;
}

bool ILFPInventoryInterface::CanInventoryRemoveItem_Implementation() const
{
    return true;
}

bool ILFPInventoryInterface::CanInventorySwapItem_Implementation() const
{
    return true;
}
