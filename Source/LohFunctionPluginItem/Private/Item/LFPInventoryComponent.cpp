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

void ULFPInventoryComponent::SendSwapDelegateEvent_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const
{
	OnSwapItem.Broadcast(InventoryIndex, NewData, OldData, EventTag);
	OnUpdateItem.Broadcast(InventoryIndex, NewData, OldData, EventTag);
}

bool ULFPInventoryComponent::ProcessInventoryIndex(
	const FLFPInventorySearchIndex& SearchIndex, 
	const TFunctionRef<bool(const FLFPInventoryChange& ChangeData)> CheckerFunction, 
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
		if (SearchIndex.IsTagMatch(SlotData.SlotName) == false) continue; // Tag Not Match Any One On Search

		if (SearchIndex.SlotIndex >= SlotData.SlotMaxIndex) continue; // Index Is Not With In Slot Allow Range

		// If SearchIndex.SlotIndex Is Invalid Than Loop All SlotData Item And Additional Index
		int32 Index				= SearchIndex.SlotIndex <= INDEX_NONE ?						0 : SearchIndex.SlotIndex;
		const int32 MaxIndex	= SearchIndex.SlotIndex <= INDEX_NONE ? SlotData.GetNextNum() : SearchIndex.SlotIndex;
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

		SlotData.ClearEmptyItem();
	}

	return false;
}

bool ULFPInventoryComponent::ProcessInventoryIndexConst(const FLFPInventorySearchIndex& SearchIndex, const TFunctionRef<bool(const FLFPInventoryChange& ChangeData)> CheckerFunction, const TFunctionRef<bool(const FLFPInventoryChange& ChangeData)> IndexFunction) const
{
	auto ProcessIndex = [&](const int32 Index, const FLFPInventorySlot& SlotData)
		{
			const FLFPInventoryIndex InventoryIndex(Index, SlotData.SlotName);
			const FLFPInventoryChange ChangeData(InventoryIndex, SlotData.GetItemCopy(Index));

			if (CheckerFunction(ChangeData) == false)
			{
				return 1;
			}

			if (IndexFunction(ChangeData)) return 0;

			return 2;
		};

	for (const FLFPInventorySlot& SlotData : InventorySlot)
	{
		if (SearchIndex.IsTagMatch(SlotData.SlotName) == false) continue; // Tag Not Match Any One On Search

		if (SearchIndex.SlotIndex >= SlotData.SlotMaxIndex) continue; // Index Is Not With In Slot Allow Range

		// If SearchIndex.SlotIndex Is Invalid Than Loop All SlotData Item
		int32 Index				= SearchIndex.SlotIndex <= INDEX_NONE ?							0 : SearchIndex.SlotIndex;
		const int32 MaxIndex	= SearchIndex.SlotIndex <= INDEX_NONE ? SlotData.GetItemNum() - 1 : SearchIndex.SlotIndex;
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
		[&](const FLFPInventoryChange& ChangeData)
		{
			if (CanItemUseInventoryIndex(FLFPInventoryChange(ChangeData.InventoryIndex, ProcessData), OnAdd) == false)
			{
				return false;
			}

			if (CanAddItem(ChangeData) == false)
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
		[&](const FLFPInventoryChange& ChangeData)
		{
			if (CanItemUseInventoryIndex(FLFPInventoryChange(ChangeData.InventoryIndex, ProcessData), OnRemove) == false)
			{
				return false;
			}

			if (CanRemoveItem(ChangeData) == false)
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
		[&](const FLFPInventoryChange& ChangeDataA)
		{
			return ChangeDataA.ItemData.IsValid();
		},
		[&](FLFPInventoryItem& ItemDataA, const FLFPInventoryIndex InventoryIndexA)
		{
			const bool bSingleProcessSuccess = ProcessInventoryIndex(
				SearchSwapData.ToIndex,
				[&](const FLFPInventoryChange& ChangeDataB)
				{
					if (InventoryIndexA == ChangeDataB.InventoryIndex)
					{
						return false;
					}

					if (CanItemUseInventoryIndex(FLFPInventoryChange(ChangeDataB.InventoryIndex, ItemDataA), OnSwap) == false)
					{
						return false;
					}

					if (CanSwapItem(FLFPInventoryChange(InventoryIndexA, ItemDataA), ChangeDataB) == false)
					{
						return false;
					}

					return true;
				},
				[&](FLFPInventoryItem& ItemDataB, const FLFPInventoryIndex InventoryIndexB)
				{
					return ProcessSwapItem(ItemDataA, InventoryIndexA, ItemDataB, InventoryIndexB);
				},
				[&](const FLFPInventoryIndex InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData)
				{
					if (EventTag.IsValid()) // Don't Send Event If Tag Is Not Valid (Prevent Network Overload)
					{
						SendSwapDelegateEvent(InventoryIndex, NewData, OldData, EventTag);
					}
				}
			);

			return bSingleProcessSuccess;
		},
		[&](const FLFPInventoryIndex InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData)
		{
			if (EventTag.IsValid()) // Don't Send Event If Tag Is Not Valid (Prevent Network Overload)
			{
				SendSwapDelegateEvent(InventoryIndex, NewData, OldData, EventTag);
			}
		}
	);

	return bAllProcessSuccess;
}

bool ULFPInventoryComponent::SortItem(const FGameplayTag SortTag, const FGameplayTag EventTag)
{
	return false;
}

void ULFPInventoryComponent::ClearInventory(const FGameplayTagContainer SlotNames, const FGameplayTag EventTag)
{
	const bool bProcessSuccess = ProcessInventoryIndex(
		FLFPInventorySearchIndex(INDEX_NONE, SlotNames),
		[&](const FLFPInventoryChange& ChangeData)
		{
			return ChangeData.ItemData.IsValid();
		},
		[&](FLFPInventoryItem& ItemData, const FLFPInventoryIndex InventoryIndex)
		{
			ItemData = FLFPInventoryItem();

			return false;
		},
		[&](const FLFPInventoryIndex InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData)
		{
			if (EventTag.IsValid()) // Don't Send Event If Tag Is Not Valid (Prevent Network Overload)
			{
				SendRemoveDelegateEvent(InventoryIndex, NewData, OldData, EventTag);
			}
		}
	);

	return;
}



bool ULFPInventoryComponent::CanAddItem_Implementation(const FLFPInventoryChange& ChangeData) const
{
	return true;
}

bool ULFPInventoryComponent::CanRemoveItem_Implementation(const FLFPInventoryChange& ChangeData) const
{
	return true;
}

bool ULFPInventoryComponent::CanSwapItem_Implementation(const FLFPInventoryChange& ChangeDataA, const FLFPInventoryChange& ChangeDataB) const
{
	return true;
}



bool ULFPInventoryComponent::ProcessAddItem_Implementation(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	ItemData = ProcessData;

	return true;
}

bool ULFPInventoryComponent::ProcessRemoveItem_Implementation(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	ItemData = FLFPInventoryItem();

	return true;
}

bool ULFPInventoryComponent::ProcessSwapItem_Implementation(UPARAM(ref)FLFPInventoryItem& ItemDataA, const FLFPInventoryIndex InventoryIndexA, UPARAM(ref)FLFPInventoryItem& ItemDataB, const FLFPInventoryIndex InventoryIndexB) const
{
	FLFPInventoryItem ItemA = ItemDataA;
	FLFPInventoryItem ItemB = ItemDataB;

	ItemDataA = ItemB;
	ItemDataB = ItemA;

	return true;
}



FGameplayTagContainer ULFPInventoryComponent::GetInventoryIndexCatergorize_Implementation(const FLFPInventoryChange& ChangeData) const
{
	return FGameplayTagContainer();
}



bool ULFPInventoryComponent::CanItemSortHigherThan_Implementation(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB, const FGameplayTag& SortTag) const
{
	return false;
}

bool ULFPInventoryComponent::CanItemUseInventoryIndex_Implementation(const FLFPInventoryChange& ChangeData, const ELFPInventoryOperation Operation) const
{
	return true;
}

bool ULFPInventoryComponent::DoInventoryIndexContainItem_Implementation(const FLFPInventoryChange& ChangeData) const
{
	return GetSlotItem(ChangeData.InventoryIndex) == ChangeData.ItemData;
}



bool ULFPInventoryComponent::ContainItem(const FLFPInventoryItem& ItemData, const FLFPInventorySearchIndex& SearchIndex) const
{
	const bool bIsSucess = ProcessInventoryIndexConst(
		SearchIndex,
		[&](const FLFPInventoryChange& ChangeData)
		{
			return ChangeData.ItemData == ItemData.ItemTag;
		},
		[&](const FLFPInventoryChange& ChangeData)
		{
			return DoInventoryIndexContainItem(FLFPInventoryChange(ChangeData.InventoryIndex, ItemData));
		}
	);


	return bIsSucess;
}

bool ULFPInventoryComponent::ContainItemList(const TArray<FLFPInventoryItem>& ItemDataList, const FLFPInventorySearchIndex& SearchIndex, const bool bPartially) const
{
	for (const auto& ItemData : ItemDataList)
	{
		const bool bIsSearchComplete = ContainItem(ItemData, SearchIndex);

		if (bPartially)
		{
			if (bIsSearchComplete) return true;
		}
		else if (bIsSearchComplete == false)
		{
			break;
		}
	}

	return false;
}

bool ULFPInventoryComponent::ContainCatergorize(const FGameplayTagContainer Catergorizes, const FLFPInventorySearchIndex& SearchIndex, const bool bContainAll, const bool bCombineSearch) const
{
	FGameplayTagContainer TotalCatergorizes = FGameplayTagContainer::EmptyContainer;

	const bool bIsSucess = ProcessInventoryIndexConst(
		SearchIndex,
		[&](const FLFPInventoryChange& ChangeData)
		{
			return ChangeData.ItemData.IsValid();
		},
		[&](const FLFPInventoryChange& ChangeData)
		{
			if (bContainAll == false) return GetInventoryIndexCatergorize(ChangeData).HasAny(Catergorizes);

			if (bCombineSearch == false) return GetInventoryIndexCatergorize(ChangeData).HasAll(Catergorizes);

			TotalCatergorizes.AppendTags(GetInventoryIndexCatergorize(ChangeData));

			return TotalCatergorizes.HasAll(Catergorizes);
		}
	);


	return bIsSucess;
}

bool ULFPInventoryComponent::IsSlotNameValid(const FGameplayTag SlotName) const
{
	for (const auto& Slot : InventorySlot)
	{
		if (Slot.SlotName.MatchesTag(SlotName)) return true;
	}

	return false;
}



FLFPInventoryItem ULFPInventoryComponent::GetSlotItem(const FLFPInventoryIndex& InventoryIndex) const
{
	for (const auto& Slot : InventorySlot)
	{
		if (Slot.SlotName.MatchesTag(InventoryIndex.SlotName)) return Slot.GetItemCopy(InventoryIndex.SlotIndex);
	}

	return FLFPInventoryItem();
}



bool ULFPInventoryComponent::FindInventoryIndexList(TArray<FLFPInventoryIndex>& InventoryIndexList, const FLFPInventoryItem& ItemData, const FGameplayTagContainer SlotNames, const FGameplayTagContainer Catergorizes, const bool bContainAllCatergorize, const int32 MaxListItem) const
{
	if (ItemData.IsValid() == false)
	{
		return false;
	}

	int32 ItemCount = 0;

	ProcessInventoryIndexConst(
		FLFPInventorySearchIndex(INDEX_NONE, SlotNames),
		[&](const FLFPInventoryChange& ChangeData)
		{
			// Check Catergorizes
			if (Catergorizes.IsEmpty() == false)
			{
				if ((bContainAllCatergorize ? 
						GetInventoryIndexCatergorize(ChangeData).HasAll(Catergorizes) 
						: 
						GetInventoryIndexCatergorize(ChangeData).HasAny(Catergorizes)
					) == false)
				{
					return false;
				}
			}

			return true;
		},
		[&](const FLFPInventoryChange& ChangeData)
		{
			if (DoInventoryIndexContainItem(FLFPInventoryChange(ChangeData.InventoryIndex, ItemData)))
			{
				InventoryIndexList.Add(ChangeData.InventoryIndex);

				ItemCount++;
			}

			return MaxListItem != INDEX_NONE ? MaxListItem <= ItemCount : false;
		}
	);

	return ItemCount != 0;
}

bool ULFPInventoryComponent::FindItemDataList(TArray<FLFPInventoryItem>& ItemIndexList, const FLFPInventoryItem& ItemData, const FGameplayTagContainer SlotNames, const FGameplayTagContainer Catergorizes, const bool bContainAllCatergorize, const int32 MaxListItem) const
{
	if (ItemData.IsValid() == false)
	{
		return false;
	}

	int32 ItemCount = 0;

	ProcessInventoryIndexConst(
		FLFPInventorySearchIndex(INDEX_NONE, SlotNames),
		[&](const FLFPInventoryChange& ChangeData)
		{
			// Check Catergorizes
			if (Catergorizes.IsEmpty() == false)
			{
				if ((bContainAllCatergorize ?
					GetInventoryIndexCatergorize(ChangeData).HasAll(Catergorizes)
					:
					GetInventoryIndexCatergorize(ChangeData).HasAny(Catergorizes)
					) == false)
				{
					return false;
				}
			}

			return true;
		},
		[&](const FLFPInventoryChange& ChangeData)
		{
			if (DoInventoryIndexContainItem(FLFPInventoryChange(ChangeData.InventoryIndex, ItemData)))
			{
				ItemIndexList.Add(ChangeData.ItemData);

				ItemCount++;
			}

			return MaxListItem != INDEX_NONE ? MaxListItem <= ItemCount : false;
		}
	);

	return ItemCount != 0;
}



FJsonObjectWrapper ULFPInventoryComponent::ExportJson(const FGameplayTagContainer SlotNames) const
{
	return FJsonObjectWrapper();
}

bool ULFPInventoryComponent::ImportJson(const FJsonObjectWrapper& JsonData, const FGameplayTagContainer SlotNames)
{
	return false;
}
