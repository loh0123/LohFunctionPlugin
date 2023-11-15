// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#include "Item/LFPInventoryComponent.h"
#include "Item/LFPInventoryInterface.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LFPInventoryComponent);


// Sets default values for this component's properties
ULFPInventoryComponent::ULFPInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULFPInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ULFPInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void ULFPInventoryComponent::SendAddDelegateEvent_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const
{
	OnAddItem.Broadcast(InventoryIndex, NewData, OldData, EventTag);
	OnUpdateItem.Broadcast(InventoryIndex, NewData, OldData, EventTag);
}

void ULFPInventoryComponent::SendRemoveDelegateEvent_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const
{
	OnAddItem.Broadcast(InventoryIndex, NewData, OldData, EventTag);
	OnUpdateItem.Broadcast(InventoryIndex, NewData, OldData, EventTag);
}

void ULFPInventoryComponent::SendSwapDelegateEvent_Implementation(const FLFPInventoryChange& NewData, const FLFPInventoryChange& OldData, const FGameplayTag& EventTag) const
{
	OnSwapItem.Broadcast(NewData, OldData, EventTag);
	OnUpdateItem.Broadcast(NewData.InventoryIndex, NewData.ItemData, OldData.ItemData, EventTag);
	OnUpdateItem.Broadcast(OldData.InventoryIndex, OldData.ItemData, NewData.ItemData, EventTag);
}

bool ULFPInventoryComponent::ProcessInventoryIndex(
	const FLFPInventorySearchIndex& SearchIndex, 
	const TFunctionRef<bool(const FLFPInventoryChange& ChnageData)> CheckerFunction, 
	const TFunctionRef<bool(FLFPInventoryItem& ItemData, const FLFPInventoryIndex InventoryIndex)> IndexFunction, 
	const TFunctionRef<void(const FLFPInventoryIndex InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData)> EventFunction
)
{
	auto ProcessIndex = [&](const int32 Index, FLFPInventorySlot& SlotData)
		{
			const FLFPInventoryIndex InventoryIndex(Index, SlotData.SlotName);
			const FLFPInventoryChange ChangeData(InventoryIndex, SlotData.GetItemCopy(Index));

			if (CheckerFunction(ChangeData) == false) 
			{
				return 1;
			}

			int32 ReturnCode = 2;

			FLFPInventoryItem& SlotDataItem = SlotData.GetItemRef(Index);

			if (IndexFunction(SlotDataItem, InventoryIndex)) ReturnCode = 0;

			if (SlotDataItem.ItemTag.IsValid() == false) SlotDataItem.MetaData = FJsonObjectWrapper(); // If Tag Is None Than Clear MetaData

			EventFunction(InventoryIndex, SlotDataItem, ChangeData.ItemData);

			return ReturnCode;
		};

	for (FLFPInventorySlot& SlotData : InventorySlot)
	{
		if (SlotData.SlotName.MatchesAny(SearchIndex.SlotNames) == false) continue; // Tag Not Match Any One On Search

		if (SearchIndex.SlotIndex >= SlotData.SlotMaxIndex) continue; // Index Is Not With In Slot Allow Range

		// If SearchIndex.SlotIndex Is Invalid Than Loop All SlotData Item
		int32 Index				= SearchIndex.SlotIndex <= INDEX_NONE ?						0 : SearchIndex.SlotIndex;
		const int32 MaxIndex	= SearchIndex.SlotIndex <= INDEX_NONE ? SlotData.GetItemNum() : SearchIndex.SlotIndex;
		//

		for (Index; Index <= MaxIndex; Index++)
		{
			switch (ProcessIndex(Index, SlotData))
			{
			case 0: return true;
			case 1: continue;
			case 2: break;
			}
		}
	}

	return false;
}



bool ULFPInventoryComponent::AddItem(const FLFPInventorySearchChange& SearchChangeData, const FGameplayTag EventTag)
{
	if (SearchChangeData.IsValid() == false) 
	{
		UE_LOG(LFPInventoryComponent, Warning, TEXT("SearchChangeData Is Not Valid On ( AddItem )"));

		return false;
	}

	FLFPInventoryItem ProcessData = SearchChangeData.ItemData;

	const bool bProcessSuccess = ProcessInventoryIndex(
		SearchChangeData.SearchIndex,
		[&](const FLFPInventoryChange& ChnageData)
		{
			if (CanItemUseInventoryIndex(FLFPInventoryChange(ChnageData.InventoryIndex, ProcessData), OnAdd) == false)
			{
				return false;
			}

			if (CanAddItem(ChnageData) == false)
			{
				return false;
			}

			return true;
		},
		[&](FLFPInventoryItem& ItemData, const FLFPInventoryIndex InventoryIndex)
		{
			return ProcessAddItem(ItemData, ProcessData, InventoryIndex);
		},
		[&](const FLFPInventoryIndex InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData)
		{
			if (EventTag.IsValid() && OldData != NewData) // Don't Send Event If Tag Is Not Valid Or No Change (Prevent Network Overload)
			{
				SendAddDelegateEvent(InventoryIndex, NewData, OldData, EventTag);
			}
		}
	);

	return bProcessSuccess;
}

bool ULFPInventoryComponent::RemoveItem(const FLFPInventorySearchChange& SearchChangeData, const FGameplayTag EventTag)
{
	if (SearchChangeData.IsValid() == false)
	{
		UE_LOG(LFPInventoryComponent, Warning, TEXT("SearchChangeData Is Not Valid On ( RemoveItem )"));

		return false;
	}

	FLFPInventoryItem ProcessData = SearchChangeData.ItemData;

	const bool bProcessSuccess = ProcessInventoryIndex(
		SearchChangeData.SearchIndex,
		[&](const FLFPInventoryChange& ChnageData)
		{
			if (CanItemUseInventoryIndex(FLFPInventoryChange(ChnageData.InventoryIndex, ProcessData), OnRemove) == false)
			{
				return false;
			}

			if (CanRemoveItem(ChnageData) == false)
			{
				return false;
			}

			return true;
		},
		[&](FLFPInventoryItem& ItemData, const FLFPInventoryIndex InventoryIndex)
		{
			return ProcessRemoveItem(ItemData, ProcessData, InventoryIndex);
		},
		[&](const FLFPInventoryIndex InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData)
		{
			if (EventTag.IsValid() && OldData != NewData) // Don't Send Event If Tag Is Not Valid Or No Change (Prevent Network Overload)
			{
				SendRemoveDelegateEvent(InventoryIndex, NewData, OldData, EventTag);
			}
		}
	);

	return bProcessSuccess;
}

bool ULFPInventoryComponent::SwapItem(const FLFPInventorySearchSwap& SearchSwapData, const FGameplayTag EventTag)
{
	const bool bAllProcessSuccess = ProcessInventoryIndex(
		SearchSwapData.TargetIndex,
		[&](const FLFPInventoryChange& ChnageDataA)
		{
			return ChnageDataA.ItemData.IsValid();
		},
		[&](FLFPInventoryItem& ItemDataA, const FLFPInventoryIndex InventoryIndexA)
		{
			const bool bSingleProcessSuccess = ProcessInventoryIndex(
				SearchSwapData.ToIndex,
				[&](const FLFPInventoryChange& ChnageDataB)
				{
					if (InventoryIndexA == ChnageDataB.InventoryIndex)
					{
						return false;
					}

					if (CanItemUseInventoryIndex(FLFPInventoryChange(ChnageDataB.InventoryIndex, ItemDataA), OnSwap) == false)
					{
						return false;
					}

					if (CanSwapItem(FLFPInventoryChange(InventoryIndexA, ItemDataA), ChnageDataB) == false)
					{
						return false;
					}

					return true;
				},
				[&](FLFPInventoryItem& ItemDataB, const FLFPInventoryIndex InventoryIndexB)
				{
					return ProcessSwapItem(ItemDataA, InventoryIndexA, ItemDataB, InventoryIndexB);
				},
				[&](const FLFPInventoryIndex InventoryIndexB, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData)
				{
					if (EventTag.IsValid()) // Don't Send Event If Tag Is Not Valid (Prevent Network Overload)
					{
						SendSwapDelegateEvent(FLFPInventoryChange(InventoryIndexA, OldData), FLFPInventoryChange(InventoryIndexB, NewData), EventTag);
					}
				}
			);

			return bSingleProcessSuccess;
		},
		[&](const FLFPInventoryIndex InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData)
		{
			
		}
	);

	return bAllProcessSuccess;
}

bool ULFPInventoryComponent::SortItem(const FGameplayTag SortTag, const FGameplayTag EventTag)
{
	return false;
}

bool ULFPInventoryComponent::ClearInventory(const FGameplayTagContainer SlotNames, const FGameplayTag EventTag)
{
	return false;
}



bool ULFPInventoryComponent::CanAddItem_Implementation(const FLFPInventoryChange& ChnageData) const
{
	return false;
}

bool ULFPInventoryComponent::CanRemoveItem_Implementation(const FLFPInventoryChange& ChnageData) const
{
	return false;
}

bool ULFPInventoryComponent::CanSwapItem_Implementation(const FLFPInventoryChange& ChnageDataA, const FLFPInventoryChange& ChnageDataB) const
{
	return false;
}



bool ULFPInventoryComponent::ProcessAddItem_Implementation(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	return false;
}

bool ULFPInventoryComponent::ProcessRemoveItem_Implementation(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	return false;
}

bool ULFPInventoryComponent::ProcessSwapItem_Implementation(UPARAM(ref)FLFPInventoryItem& ItemDataA, const FLFPInventoryIndex InventoryIndexA, UPARAM(ref)FLFPInventoryItem& ItemDataB, const FLFPInventoryIndex InventoryIndexB) const
{
	return false;
}



bool ULFPInventoryComponent::CanItemSortHigherThan_Implementation(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB) const
{
	return false;
}

bool ULFPInventoryComponent::CanItemUseInventoryIndex_Implementation(const FLFPInventoryChange& ChangeData, const ELFPInventoryOperation Operation) const
{
	return false;
}



bool ULFPInventoryComponent::ContainItem(const FLFPInventoryItem& ItemData, const FLFPInventoryIndex& InventoryIndex) const
{
	return false;
}

bool ULFPInventoryComponent::ContainItemList(const TArray<FLFPInventoryItem>& ItemDataList, const FLFPInventoryIndex& InventoryIndex, const bool bPartially) const
{
	return false;
}

bool ULFPInventoryComponent::IsInventoryIndexHasCatergorize(const FGameplayTagContainer Catergorizes, const FLFPInventoryIndex& InventoryIndex) const
{
	return false;
}

bool ULFPInventoryComponent::IsSlotNameValid(const FGameplayTag SlotName) const
{
	return false;
}



FLFPInventoryItem ULFPInventoryComponent::GetSlotItem(const int32 SlotIndex, const FGameplayTag SlotName) const
{
	return FLFPInventoryItem();
}



bool ULFPInventoryComponent::FindInventoryIndexList(TArray<FLFPInventoryIndex>& InventoryIndexList, const FLFPInventoryItem& ItemData, const FGameplayTagContainer SlotNames, const FGameplayTagContainer Catergorizes) const
{
	return false;
}

bool ULFPInventoryComponent::FindItemDataList(TArray<FLFPInventoryItem>& ItemIndexList, const FLFPInventoryItem& ItemData, const FGameplayTagContainer SlotNames, const FGameplayTagContainer Catergorizes) const
{
	return false;
}



FJsonObjectWrapper ULFPInventoryComponent::ExportJson(const FGameplayTagContainer SlotNames) const
{
	return FJsonObjectWrapper();
}

bool ULFPInventoryComponent::ImportJson(const FJsonObjectWrapper& JsonData, const FGameplayTagContainer SlotNames)
{
	return false;
}
