// Copyright (c) 2023-2024 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "CoreMinimal.h"
#include "Item/FunctionObject/LFPItemInventoryFunction.h"
#include "LFPItemBasicFunction.generated.h"

USTRUCT(Blueprintable)
struct FLFPItemBasicData : public FTableRowBase
{
	GENERATED_BODY()

protected:

	/* Use To Find Stack Meta In Item */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default|Stack")
		FGameplayTag StackTag = FGameplayTag();

	/* Maximum Stack An Item Can Reach, Use -1 If Infinite */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default|Stack")
		int32 MaxStack = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default|Attach")
		FGameplayTag AttachSlotsTag = FGameplayTag();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default|Attach")
		int32 MaxAttachSlots = INDEX_NONE;
	
	/* Check All The Meta Match Other Item ( Can't Use Parent Tag ) */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		FGameplayTagContainer MatchMetaTagList = FGameplayTagContainer();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		FGameplayTagContainer AllowedInventorySlotNameList = FGameplayTagContainer();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		FGameplayTagContainer Categorize = FGameplayTagContainer();

public:

	FORCEINLINE bool DoItemAllowOnSlot(const FGameplayTag& SlotName) const
	{
		return SlotName.MatchesAny(AllowedInventorySlotNameList);
	}

	FORCEINLINE bool DoItemMetaMatch(const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const
	{
		if (CurrentData.IsValid() == false || ProcessData.IsValid() == false) return true;

		for (const FGameplayTag& MathIntTag : MatchMetaTagList)
		{
			if (ULFPItemFunctionLibrary::IsMetaDataSame(CurrentData, ProcessData, MathIntTag) == false)
			{
				return false;
			}
		}

		return true;
	}

	FORCEINLINE bool DoItemReachMaxStack(const FLFPInventoryItem& CurrentData) const
	{
		return MaxStack != INDEX_NONE && StackTag.IsValid() && CurrentData.IsValid() && MaxStack <= ULFPItemFunctionLibrary::GetMetaDataAsNumber(CurrentData, StackTag, 1);
	}


	FORCEINLINE int32 GetStackAmount(const FLFPInventoryItem& CurrentData) const
	{
		return ULFPItemFunctionLibrary::GetMetaDataAsNumber(CurrentData, StackTag, 1);
	}

	FORCEINLINE void SetStackAmount(FLFPInventoryItem& CurrentData, const int32 NewStack) const
	{
		FLFPCompactMetaData NewData(StackTag);

		NewData.SetDataAsInt(NewStack);

		ULFPItemFunctionLibrary::SetMetaData(CurrentData, NewData);
	}

	FORCEINLINE int32 ClampToMaxStack(const int32 Stack) const
	{
		return FMath::Max(MaxStack != INDEX_NONE ? FMath::Min(MaxStack, Stack) : Stack, 0);
	}


	FORCEINLINE const FGameplayTagContainer& GetAllowInventorySlotNameList() const
	{
		return AllowedInventorySlotNameList;
	}

	FORCEINLINE const FGameplayTagContainer& GetCategorize() const
	{
		return Categorize;
	}
};

/**
 * 
 */
UCLASS(BlueprintType)
class LOHFUNCTIONPLUGINITEM_API ULFPItemBasicFunction : public ULFPItemInventoryFunction
{
	GENERATED_BODY()

public:

	virtual bool CanAddItem_Implementation(const FLFPInventoryItem& ItemData) const override;

	virtual bool CanRemoveItem_Implementation(const FLFPInventoryItem& ItemData) const override;

	virtual bool CanUpdateItem_Implementation(const FLFPInventoryItem& ItemData) const override;

	virtual bool CanFindItem_Implementation(const FLFPInventoryItem& ItemData) const override;


	virtual bool CanAddItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const override;

	virtual bool CanRemoveItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const override;

	virtual bool CanSwapItemOnSlot_Implementation(const FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, const FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const override;

	virtual bool CanMergeItemOnSlot_Implementation(const FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, const FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const override;

	virtual bool CanUpdateItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const override;

	virtual bool CanFindItemOnSlot_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const override;

	//// Process Modifier

	virtual bool ProcessAddItem_Implementation(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const override;

	virtual bool ProcessRemoveItem_Implementation(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const override;

	virtual bool ProcessSwapItem_Implementation(UPARAM(ref) FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, UPARAM(ref) FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const override;

	virtual bool ProcessMergeItem_Implementation(UPARAM(ref) FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, UPARAM(ref) FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const override;

	virtual bool ProcessUpdateItem_Implementation(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const override;

	virtual bool ProcessFindItem_Implementation(const FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const override;

	//// Categorize Modifier

	virtual FGameplayTagContainer GetItemCategorize_Implementation(const FLFPInventoryItem& ItemData) const override;

	virtual FGameplayTagContainer GetItemAllowSlotNameList_Implementation(const FLFPInventoryItem& ItemData) const override;

	//// Check Modifier

	virtual bool CanItemSortHigherThan_Implementation(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB, const FGameplayTag& SortTag) const override;

protected:

	FORCEINLINE const FLFPItemBasicData* GetDataTableRow(const FGameplayTag& RowTag) const;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LFPItemBasicFunction | Setting", meta = (RequiredAssetDataTags = "RowStructure=/Script/LohFunctionPluginItem.LFPItemBasicData"))
		TObjectPtr<UDataTable> ItemDataTable = nullptr;
	
};
