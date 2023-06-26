// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Item/LFPInventoryComponent.h"
#include "LFPInventoryInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULFPInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LOHFUNCTIONPLUGINITEM_API ILFPInventoryInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "LFPInventoryInterface")
		bool CanInventoryAddItem(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const;
		virtual bool CanInventoryAddItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "LFPInventoryInterface")
		bool CanInventoryRemoveItem(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const;
		virtual bool CanInventoryRemoveItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "LFPInventoryInterface")
		bool CanInventorySwapItem(const FLFPInventoryItemData& FromItemData, const int32 FromSlot, const FLFPInventoryItemData& ToItemData, const int32 ToSlot, const FString& EventInfo) const;
		virtual bool CanInventorySwapItem_Implementation(const FLFPInventoryItemData& FromItemData, const int32 FromSlot, const FLFPInventoryItemData& ToItemData, const int32 ToSlot, const FString& EventInfo) const;
};
