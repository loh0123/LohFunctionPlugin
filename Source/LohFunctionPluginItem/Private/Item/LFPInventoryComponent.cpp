// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#include "Item/LFPInventoryComponent.h"
#include "Item/LFPInventoryInterface.h"
#include "LFPItemInventoryFunction.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LFPInventoryComponent);


// Sets default values for this component's properties
ULFPInventoryComponent::ULFPInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent = true;
	// ...
}


// Called when the game starts
void ULFPInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void ULFPInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ULFPInventoryComponent, FunctionList);
}

// Called every frame
void ULFPInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULFPInventoryComponent::InitializeComponent()
{
	Super::InitializeComponent();

	check(GetOwner());

	/* For Supporting Function List Object Replication */
	for (auto& FunctionObj : FunctionList)
	{
		check(FunctionObj.Get()->GetOuter());

		AddReplicatedSubObject(FunctionObj.Get());
	}
	////////////////////////////////////////////////////
}

void ULFPInventoryComponent::UninitializeComponent()
{
	Super::UninitializeComponent();

	/* For Supporting Function List Object Replication */
	for (auto& FunctionObj : FunctionList)
	{
		RemoveReplicatedSubObject(FunctionObj.Get());
	}
	////////////////////////////////////////////////////
}

bool ULFPInventoryComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	/* For Supporting Function List Object Replication */
	for (auto& FunctionObj : FunctionList)
	{
		Channel->ReplicateSubobject(FunctionObj.Get(), *Bunch, *RepFlags);
	}
	////////////////////////////////////////////////////

	return true;
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
	const TFunctionRef<bool(const FLFPInventoryChange& ChangeData, const FLFPInventoryKey& InventoryKey)> CheckerFunction,
	const TFunctionRef<bool(const FLFPInventoryChange& ChangeData, const FLFPInventoryKey& InventoryKey)> IndexFunction,
	const TFunction<void(const FLFPInventoryChange& OldData, const FLFPInventoryKey& InventoryKey)> EventFunction,
	const TFunction<void(const FLFPInventoryKey& InventoryKey)> OnSlotNameEnd
) const
{
	UE_LOG(LFPInventoryComponent, Log, TEXT("ProcessInventoryIndex Start"));

	int32 SlotDataIndex = INDEX_NONE;

	for (const FLFPInventorySlot& SlotData : InventorySlot)
	{
		SlotDataIndex++;

		if (SearchIndex.IsTagMatch(SlotData.SlotName) == false) 
		{
			UE_LOG(LFPInventoryComponent, Log, TEXT("ProcessInventoryIndex Skip Index Bacause Tag : %s"), *SearchIndex.ToString());

			continue; // Tag Not Match Any One On Search
		}

		if (SlotData.SlotMaxIndex > INDEX_NONE && SearchIndex.SlotIndex >= SlotData.SlotMaxIndex)
		{
			UE_LOG(LFPInventoryComponent, Log, TEXT("ProcessInventoryIndex Skip Index Bacause Index OverFlow : %s"), *SearchIndex.ToString());

			continue; // Index Is Not With In Slot Allow Range
		}

		// If SearchIndex.SlotIndex Is Invalid Than Loop All SlotData Item And Additional Index
		int32 Index				= SearchIndex.SlotIndex <= INDEX_NONE ?						0 : SearchIndex.SlotIndex;
		const int32 MaxIndex	= SearchIndex.SlotIndex <= INDEX_NONE ? SlotData.GetNextNum() : SearchIndex.SlotIndex;
		//

		UE_LOG(LFPInventoryComponent, Log, TEXT("ProcessInventoryIndex SlotData Start : Name = %s | StartIndex = %d | EndIndex = %d"), *SlotData.SlotName.ToString(), Index, MaxIndex);

		for (Index; Index <= MaxIndex; Index++)
		{
			const FLFPInventoryChange ChangeData(FLFPInventoryIndex(Index, SlotData.SlotName), SlotData.GetItemCopy(Index));
			const FLFPInventoryKey InventoryKey(Index, SlotDataIndex);

			if (CheckerFunction(ChangeData, InventoryKey) == false) continue;

			const bool bIsSuccess = IndexFunction(ChangeData, InventoryKey);

			EventFunction(ChangeData, InventoryKey);

			if (bIsSuccess) 
			{
				UE_LOG(LFPInventoryComponent, Log, TEXT("ProcessInventoryIndex Success : %s"), *ChangeData.InventoryIndex.ToString());

				return true;
			}
		}

		UE_LOG(LFPInventoryComponent, Log, TEXT("ProcessInventoryIndex SlotData End : %s"), *SlotData.SlotName.ToString());
	}

	UE_LOG(LFPInventoryComponent, Log, TEXT("ProcessInventoryIndex Fail"));

	return false;
}

bool ULFPInventoryComponent::ProcessInventoryFunction(const TFunctionRef<bool(const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)> RunFunction) const
{
	for (const auto& FunctionObj : FunctionList)
	{
		if (IsValid(FunctionObj) == false) continue;

		if (RunFunction(FunctionObj) == false) return false;
	}

	return true;
}



bool ULFPInventoryComponent::AddItem(const FLFPInventorySearchChange& SearchChangeData, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (SearchChangeData.IsValid() == false) 
	{
		UE_LOG(LFPInventoryComponent, Warning, TEXT("SearchChangeData Is Not Valid On ( AddItem )"));

		return false;
	}

	FLFPInventoryItem ProcessData = SearchChangeData.ItemData;

	const bool bProcessSuccess = ProcessInventoryIndex(
		SearchChangeData.SearchIndex,
		[&](const FLFPInventoryChange& ChangeData, const FLFPInventoryKey& InventoryKey)
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
		[&](const FLFPInventoryChange& ChangeData, const FLFPInventoryKey& InventoryKey)
		{
			return ProcessAddItem(GetSlotItemRef(InventoryKey), ProcessData, ChangeData.InventoryIndex);
		},
		[&](const FLFPInventoryChange& OldData, const FLFPInventoryKey& InventoryKey)
		{
			auto& NewData = GetSlotItemConst(InventoryKey);

			if (EventTag.IsValid() && OldData.ItemData != NewData) // Don't Send Event If Tag Is Not Valid Or No Change (Prevent Network Overload)
			{
				SendAddDelegateEvent(OldData.InventoryIndex, NewData, OldData.ItemData, EventTag);
			}
		}
	);

	return bProcessSuccess;
}

bool ULFPInventoryComponent::RemoveItem(const FLFPInventorySearchChange& SearchChangeData, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (SearchChangeData.IsValid() == false)
	{
		UE_LOG(LFPInventoryComponent, Warning, TEXT("SearchChangeData Is Not Valid On ( RemoveItem )"));

		return false;
	}

	FLFPInventoryItem ProcessData = SearchChangeData.ItemData;

	const bool bProcessSuccess = ProcessInventoryIndex(
		SearchChangeData.SearchIndex,
		[&](const FLFPInventoryChange& ChangeData, const FLFPInventoryKey& InventoryKey)
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
		[&](const FLFPInventoryChange& ChangeData, const FLFPInventoryKey& InventoryKey)
		{
			return ProcessRemoveItem(GetSlotItemRef(InventoryKey), ProcessData, ChangeData.InventoryIndex);
		},
		[&](const FLFPInventoryChange& OldData, const FLFPInventoryKey& InventoryKey)
		{
			auto& NewData = GetSlotItemConst(InventoryKey);

			if (EventTag.IsValid() && OldData.ItemData != NewData) // Don't Send Event If Tag Is Not Valid Or No Change (Prevent Network Overload)
			{
				SendRemoveDelegateEvent(OldData.InventoryIndex, NewData, OldData.ItemData, EventTag);
			}
		},
		[&](const FLFPInventoryKey& InventoryKey)
		{
			ClearSlotEmptyItem(InventoryKey.SlotNameIndex);
		}
	);

	return bProcessSuccess;
}

bool ULFPInventoryComponent::SwapItem(const FLFPInventorySearchSwap& SearchSwapData, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	const bool bAllProcessSuccess = ProcessInventoryIndex(
		SearchSwapData.TargetIndex,
		[&](const FLFPInventoryChange& ChangeDataA, const FLFPInventoryKey& InventoryKey)
		{
			return ChangeDataA.ItemData.IsValid();
		},
		[&](const FLFPInventoryChange& ChangeDataA, const FLFPInventoryKey& InventoryKeyA)
		{
			GetSlotItemRef(InventoryKeyA); // Update Array Num To Prevent Null Ref

			const bool bSingleProcessSuccess = ProcessInventoryIndex(
				SearchSwapData.ToIndex,
				[&](const FLFPInventoryChange& ChangeDataB, const FLFPInventoryKey& InventoryKeyB)
				{
					if (ChangeDataA.InventoryIndex == ChangeDataB.InventoryIndex)
					{
						return false;
					}

					if (CanItemUseInventoryIndex(ChangeDataB, OnSwap) == false)
					{
						return false;
					}

					if (CanSwapItem(ChangeDataA, ChangeDataB) == false)
					{
						return false;
					}

					return true;
				},
				[&](const FLFPInventoryChange& ChangeDataB, const FLFPInventoryKey& InventoryKeyB)
				{
					auto& ItemRefB = GetSlotItemRef(InventoryKeyB);
					auto& ItemRefA = GetSlotItemRef(InventoryKeyA); // Refresh Because Item B Maybe Changing The Array Size

					return ProcessSwapItem(ItemRefA, ChangeDataA.InventoryIndex, ItemRefB, ChangeDataB.InventoryIndex);
				},
				[&](const FLFPInventoryChange& OldDataB, const FLFPInventoryKey& InventoryKeyB)
				{
					auto& NewData = GetSlotItemConst(InventoryKeyB);

					if (EventTag.IsValid() && OldDataB.ItemData != NewData) // Don't Send Event If Tag Is Not Valid Or No Change (Prevent Network Overload)
					{
						SendSwapDelegateEvent(OldDataB.InventoryIndex, NewData, OldDataB.ItemData, EventTag);
					}
				}
			);

			return bSingleProcessSuccess;
		},
		[&](const FLFPInventoryChange& OldDataA, const FLFPInventoryKey& InventoryKeyA)
		{
			auto& NewData = GetSlotItemConst(InventoryKeyA);

			if (EventTag.IsValid() && OldDataA.ItemData != NewData) // Don't Send Event If Tag Is Not Valid Or No Change (Prevent Network Overload)
			{
				SendRemoveDelegateEvent(OldDataA.InventoryIndex, NewData, OldDataA.ItemData, EventTag);
			}
		},
		[&](const FLFPInventoryKey& InventoryKey)
		{
			ClearSlotEmptyItem(InventoryKey.SlotNameIndex);
		}
	);

	return bAllProcessSuccess;
}

bool ULFPInventoryComponent::SortItem(const FGameplayTag SortTag, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	return false;
}

void ULFPInventoryComponent::ClearInventory(const FGameplayTagContainer SlotNames, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return; // Prevent this function to run on client

	const bool bProcessSuccess = ProcessInventoryIndex(
		FLFPInventorySearchIndex(INDEX_NONE, SlotNames),
		[&](const FLFPInventoryChange& ChangeData, const FLFPInventoryKey& InventoryKey)
		{
			return ChangeData.ItemData.IsValid();
		},
		[&](const FLFPInventoryChange& ChangeData, const FLFPInventoryKey& InventoryKey)
		{
			GetSlotItemRef(InventoryKey) = FLFPInventoryItem();

			return false;
		}, 
		[&](const FLFPInventoryChange& OldData, const FLFPInventoryKey& InventoryKey)
		{
			if (EventTag.IsValid()) // Don't Send Event If Tag Is Not Valid (Prevent Network Overload)
			{
				SendRemoveDelegateEvent(OldData.InventoryIndex, GetSlotItemConst(InventoryKey), OldData.ItemData, EventTag);
			}
		},
		[&](const FLFPInventoryKey& InventoryKey)
		{
			ClearSlotEmptyItem(InventoryKey.SlotNameIndex);
		}
	);

	return;
}

ULFPItemInventoryFunction* ULFPInventoryComponent::GetFunctionObject(const TSubclassOf<ULFPItemInventoryFunction> FunctionClass) const
{
	if (FunctionClass == nullptr) return nullptr;

	for (auto& FunctionObj : FunctionList)
	{
		if (IsValid(FunctionObj) == false) continue;

		if (FunctionObj.GetClass() == FunctionClass.Get())
		{
			return FunctionObj;
		}
	}

	return nullptr;
}

bool ULFPInventoryComponent::CanAddItem(const FLFPInventoryChange& ChangeData) const
{
	const bool bSuccess = ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			return FunctionObj->CanAddItem(this, ChangeData);
		}
	);

	return bSuccess;
}

bool ULFPInventoryComponent::CanRemoveItem(const FLFPInventoryChange& ChangeData) const
{
	const bool bSuccess = ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			return FunctionObj->CanRemoveItem(this, ChangeData);
		}
	);

	return bSuccess;
}

bool ULFPInventoryComponent::CanSwapItem(const FLFPInventoryChange& ChangeDataA, const FLFPInventoryChange& ChangeDataB) const
{
	const bool bSuccess = ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			return FunctionObj->CanSwapItem(this, ChangeDataA, ChangeDataB);
		}
	);

	return bSuccess;
}

bool ULFPInventoryComponent::ProcessAddItem(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	const bool bSuccess = ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			return FunctionObj->ProcessAddItem(this, ItemData, ProcessData, InventoryIndex);
		}
	);

	return bSuccess;
}

bool ULFPInventoryComponent::ProcessRemoveItem(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	const bool bSuccess = ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			return FunctionObj->ProcessRemoveItem(this, ItemData, ProcessData, InventoryIndex);
		}
	);

	return bSuccess;
}

bool ULFPInventoryComponent::ProcessSwapItem(UPARAM(ref)FLFPInventoryItem& ItemDataA, const FLFPInventoryIndex& InventoryIndexA, UPARAM(ref)FLFPInventoryItem& ItemDataB, const FLFPInventoryIndex& InventoryIndexB) const
{
	const bool bSuccess = ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			return FunctionObj->ProcessSwapItem(this, ItemDataA, InventoryIndexA, ItemDataB, InventoryIndexB);
		}
	);

	return bSuccess;
}

FGameplayTagContainer ULFPInventoryComponent::GetInventoryIndexCatergorize(const FLFPInventoryChange& ChangeData) const
{
	FGameplayTagContainer Result = FGameplayTagContainer();

	const bool bSuccess = ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			Result.AppendTags(FunctionObj->GetInventoryIndexCatergorize(this, ChangeData));

			return true;
		}
	);

	return Result;
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
	const bool bIsSucess = ProcessInventoryIndex(
		SearchIndex,
		[&](const FLFPInventoryChange& ChangeData, const FLFPInventoryKey& InventoryKey)
		{
			return ChangeData.ItemData == ItemData.ItemTag;
		},
		[&](const FLFPInventoryChange& ChangeData, const FLFPInventoryKey& InventoryKey)
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

	const bool bIsSucess = ProcessInventoryIndex(
		SearchIndex,
		[&](const FLFPInventoryChange& ChangeData, const FLFPInventoryKey& InventoryKey)
		{
			return ChangeData.ItemData.IsValid();
		},
		[&](const FLFPInventoryChange& ChangeData, const FLFPInventoryKey& InventoryKey)
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
		if (Slot.SlotName == InventoryIndex.SlotName) return Slot.GetItemCopy(InventoryIndex.SlotIndex);
	}

	return FLFPInventoryItem();
}

const FLFPInventoryItem& ULFPInventoryComponent::GetSlotItemConst(const FLFPInventoryKey& InventoryKey) const
{
	return InventorySlot[InventoryKey.SlotNameIndex].GetItemConst(InventoryKey.SlotIndex);
}

FLFPInventoryItem& ULFPInventoryComponent::GetSlotItemRef(const FLFPInventoryKey& InventoryKey)
{
	return InventorySlot[InventoryKey.SlotNameIndex].GetItemRef(InventoryKey.SlotIndex);
}

void ULFPInventoryComponent::ClearSlotEmptyItem(const int32 SlotNameKey)
{
	InventorySlot[SlotNameKey].ClearEmptyItem();
}



bool ULFPInventoryComponent::FindInventoryIndexList(TArray<FLFPInventoryIndex>& InventoryIndexList, const FLFPInventoryItem& ItemData, const FGameplayTagContainer SlotNames, const FGameplayTagContainer Catergorizes, const bool bContainAllCatergorize, const int32 MaxListItem) const
{
	if (ItemData.IsValid() == false)
	{
		return false;
	}

	int32 ItemCount = 0;

	ProcessInventoryIndex(
		FLFPInventorySearchIndex(INDEX_NONE, SlotNames),
		[&](const FLFPInventoryChange& ChangeData, const FLFPInventoryKey& InventoryKey)
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
		[&](const FLFPInventoryChange& ChangeData, const FLFPInventoryKey& InventoryKey)
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

	ProcessInventoryIndex(
		FLFPInventorySearchIndex(INDEX_NONE, SlotNames),
		[&](const FLFPInventoryChange& ChangeData, const FLFPInventoryKey& InventoryKey)
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
		[&](const FLFPInventoryChange& ChangeData, const FLFPInventoryKey& InventoryKey)
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
