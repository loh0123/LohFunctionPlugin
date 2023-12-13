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

	DOREPLIFETIME(ULFPInventoryComponent, InventorySlot);

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



//void ULFPInventoryComponent::SendAddDelegateEvent_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const
//{
//	OnAddItem.Broadcast(InventoryIndex, NewData, OldData, EventTag);
//	OnUpdateItem.Broadcast(InventoryIndex, NewData, OldData, EventTag);
//}
//
//void ULFPInventoryComponent::SendRemoveDelegateEvent_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const
//{
//	OnAddItem.Broadcast(InventoryIndex, NewData, OldData, EventTag);
//	OnUpdateItem.Broadcast(InventoryIndex, NewData, OldData, EventTag);
//}
//
//void ULFPInventoryComponent::SendSwapDelegateEvent_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const
//{
//	OnSwapItem.Broadcast(InventoryIndex, NewData, OldData, EventTag);
//	OnUpdateItem.Broadcast(InventoryIndex, NewData, OldData, EventTag);
//}

bool ULFPInventoryComponent::ProcessInventoryIndex(
	const FLFPInventorySearch& InventoryCategorize,
	const TFunctionRef<bool(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CopyItemData, const FLFPInventoryKey& InventoryKey)> IndexFunction,
	const TFunction<void(const FLFPInventoryKey& InventoryKey)> OnSlotNameEnd
) const
{
	UE_LOG(LFPInventoryComponent, Log, TEXT("ProcessInventoryIndex Start"));

	int32 SlotDataIndex = INDEX_NONE;

	for (const FLFPInventorySlot& SlotData : InventorySlot)
	{
		SlotDataIndex++;

		if (InventoryCategorize.IsTagMatch(SlotData.SlotName) == false)
		{
			UE_LOG(LFPInventoryComponent, Log, TEXT("ProcessInventoryIndex Skip Index Bacause Tag : %s"), *InventoryCategorize.ToString());

			continue; // Tag Not Match Any One On Search
		}

		// If SearchIndex.SlotIndex Is Invalid Than Loop All SlotData Item And Additional Index
		int32 Index				= 0;
		const int32 MaxIndex	= SlotData.GetNextNum();
		//

		UE_LOG(LFPInventoryComponent, Log, TEXT("ProcessInventoryIndex SlotData Start : Name = %s | StartIndex = %d | EndIndex = %d"), *SlotData.SlotName.ToString(), Index, MaxIndex);

		for (Index; Index <= MaxIndex; Index++)
		{
			const FLFPInventoryIndex InventoryIndex(Index, SlotData.SlotName);

			if (IndexFunction(InventoryIndex, SlotData.GetItemCopy(Index), FLFPInventoryKey(Index, SlotDataIndex)))
			{
				UE_LOG(LFPInventoryComponent, Log, TEXT("ProcessInventoryIndex Success : %s"), *InventoryIndex.ToString());

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


bool ULFPInventoryComponent::AddItem_Internal(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CopyItemData, const FLFPInventoryKey& InventoryKey, FLFPInventoryItem& ProcessItemData, const FGameplayTag& EventTag)
{
	if (CanAddItemOnSlot(InventoryIndex, CopyItemData, ProcessItemData) == false) return false;

	auto& NewData = GetSlotItemRef(InventoryKey);

	const bool bSuccess = ProcessAddItem(NewData, ProcessItemData, InventoryIndex);

	//if (EventTag.IsValid() && CopyItemData != NewData) // Don't Send Event If Tag Is Not Valid Or No Change (Prevent Network Overload)
	//{
	//	SendAddDelegateEvent(InventoryIndex, NewData, CopyItemData, EventTag);
	//}

	return bSuccess;
}

bool ULFPInventoryComponent::AddItem_Internal_Check(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CopyItemData, const FLFPInventoryKey& InventoryKey, FLFPInventoryItem& ProcessItemData) const
{
	if (CanAddItemOnSlot(InventoryIndex, CopyItemData, ProcessItemData) == false) return false;

	FLFPInventoryItem TestItem = CopyItemData;

	return ProcessAddItem(TestItem, ProcessItemData, InventoryIndex);
}

bool ULFPInventoryComponent::RemoveItem_Internal(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CopyItemData, const FLFPInventoryKey& InventoryKey, FLFPInventoryItem& ProcessItemData, const FGameplayTag& EventTag)
{
	if (CanRemoveItemOnSlot(InventoryIndex, CopyItemData, ProcessItemData) == false) return false;

	auto& NewData = GetSlotItemRef(InventoryKey);

	const bool bSuccess = ProcessRemoveItem(NewData, ProcessItemData, InventoryIndex);

	//if (EventTag.IsValid() && CopyItemData != NewData) // Don't Send Event If Tag Is Not Valid Or No Change (Prevent Network Overload)
	//{
	//	SendRemoveDelegateEvent(InventoryIndex, NewData, CopyItemData, EventTag);
	//}

	return bSuccess;
}

bool ULFPInventoryComponent::RemoveItem_Internal_Check(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CopyItemData, const FLFPInventoryKey& InventoryKey, FLFPInventoryItem& ProcessItemData) const
{
	if (CanRemoveItemOnSlot(InventoryIndex, CopyItemData, ProcessItemData) == false) return false;

	FLFPInventoryItem TestItem = CopyItemData;

	return ProcessRemoveItem(TestItem, ProcessItemData, InventoryIndex);
}


bool ULFPInventoryComponent::AddItem(UPARAM(ref) FLFPInventoryItem& ItemData, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	return AddItemBySearch(GetItemInventorySearch(ItemData), ItemData, EventTag);
}

bool ULFPInventoryComponent::AddItemList(UPARAM(ref) TArray<FLFPInventoryItem>& ItemDataList, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	bool bIsSuccess = true;

	for (FLFPInventoryItem& ItemData : ItemDataList)
	{
		if (AddItemBySearch(GetItemInventorySearch(ItemData), ItemData, EventTag) == false)
		{
			bIsSuccess = false;
		}
	}

	return bIsSuccess;
}

bool ULFPInventoryComponent::AddItemBySearch(const FLFPInventorySearch& InventorySearch, UPARAM(ref) FLFPInventoryItem& ItemData, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (CanAddItem(ItemData) == false) return false;

	return ProcessInventoryIndex(
		InventorySearch,
		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CopyItemData, const FLFPInventoryKey& InventoryKey)
		{
			return AddItem_Internal(InventoryIndex, CopyItemData, InventoryKey, ItemData, EventTag);
		});
}

bool ULFPInventoryComponent::AddItemByIndex(const FLFPInventoryIndex& InventoryIndex, UPARAM(ref) FLFPInventoryItem& ItemData, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (CanAddItem(ItemData) == false) return false;

	const FLFPInventoryKey InvKey = GetInventoryKey(InventoryIndex);

	if (InvKey.IsValid() == false) return false;

	return AddItem_Internal(InventoryIndex, GetSlotItemCopy(InvKey), InvKey, ItemData, EventTag);
}


bool ULFPInventoryComponent::RemoveItem(UPARAM(ref) FLFPInventoryItem& ItemData, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	return RemoveItemBySearch(GetItemInventorySearch(ItemData), ItemData, EventTag);
}

bool ULFPInventoryComponent::RemoveItemList(UPARAM(ref)TArray<FLFPInventoryItem>& ItemDataList, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	bool bIsSuccess = true;

	for (FLFPInventoryItem& ItemData : ItemDataList)
	{
		if (RemoveItemBySearch(GetItemInventorySearch(ItemData), ItemData, EventTag) == false)
		{
			bIsSuccess = false;
		}
	}

	return bIsSuccess;
}

bool ULFPInventoryComponent::RemoveItemBySearch(const FLFPInventorySearch& InventorySearch, UPARAM(ref) FLFPInventoryItem& ItemData, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (CanRemoveItem(ItemData) == false) return false;

	return ProcessInventoryIndex(
		InventorySearch,
		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CopyItemData, const FLFPInventoryKey& InventoryKey)
		{
			return RemoveItem_Internal(InventoryIndex, CopyItemData, InventoryKey, ItemData, EventTag);
		});
}

bool ULFPInventoryComponent::RemoveItemByIndex(const FLFPInventoryIndex& InventoryIndex, UPARAM(ref) FLFPInventoryItem& ItemData, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (CanRemoveItem(ItemData) == false) return false;

	const FLFPInventoryKey InvKey = GetInventoryKey(InventoryIndex);

	if (InvKey.IsValid() == false) return false;

	return RemoveItem_Internal(InventoryIndex, GetSlotItemCopy(InvKey), InvKey, ItemData, EventTag);
}


//bool ULFPInventoryComponent::SwapItem(const FLFPInventorySearchSwap& SearchSwapData, const FGameplayTag EventTag)
//{
//	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client
//
//	const bool bAllProcessSuccess = ProcessInventoryIndex(
//		SearchSwapData.FromIndex,
//		[&](const FLFPInventoryChange& ChangeDataA, const FLFPInventoryKey& InventoryKey)
//		{
//			return ChangeDataA.ItemData.IsValid();
//		},
//		[&](const FLFPInventoryChange& ChangeDataA, const FLFPInventoryKey& InventoryKeyA)
//		{
//			GetSlotItemRef(InventoryKeyA); // Update Array Num To Prevent Null Ref
//
//			const bool bSingleProcessSuccess = ProcessInventoryIndex(
//				SearchSwapData.ToIndex,
//				[&](const FLFPInventoryChange& ChangeDataB, const FLFPInventoryKey& InventoryKeyB)
//				{
//					if (ChangeDataA.InventoryIndex == ChangeDataB.InventoryIndex)
//					{
//						return false;
//					}
//
//					if (CanItemUseInventoryIndex(ChangeDataB, ChangeDataA.ItemData, OnSwap) == false)
//					{
//						return false;
//					}
//
//					if (CanSwapItem(ChangeDataA, ChangeDataB) == false)
//					{
//						return false;
//					}
//
//					return true;
//				},
//				[&](const FLFPInventoryChange& ChangeDataB, const FLFPInventoryKey& InventoryKeyB)
//				{
//					auto& ItemRefB = GetSlotItemRef(InventoryKeyB);
//					auto& ItemRefA = GetSlotItemRef(InventoryKeyA); // Refresh Because Item B Maybe Changing The Array Size
//
//					return ProcessSwapItem(ItemRefA, ChangeDataA.InventoryIndex, ItemRefB, ChangeDataB.InventoryIndex);
//				},
//				[&](const FLFPInventoryChange& OldDataB, const FLFPInventoryKey& InventoryKeyB)
//				{
//					auto& NewData = GetSlotItemConst(InventoryKeyB);
//
//					if (EventTag.IsValid() && OldDataB.ItemData != NewData) // Don't Send Event If Tag Is Not Valid Or No Change (Prevent Network Overload)
//					{
//						SendSwapDelegateEvent(OldDataB.InventoryIndex, NewData, OldDataB.ItemData, EventTag);
//					}
//				}
//			);
//
//			return bSingleProcessSuccess;
//		},
//		[&](const FLFPInventoryChange& OldDataA, const FLFPInventoryKey& InventoryKeyA)
//		{
//			auto& NewData = GetSlotItemConst(InventoryKeyA);
//
//			if (EventTag.IsValid() && OldDataA.ItemData != NewData) // Don't Send Event If Tag Is Not Valid Or No Change (Prevent Network Overload)
//			{
//				SendSwapDelegateEvent(OldDataA.InventoryIndex, NewData, OldDataA.ItemData, EventTag);
//			}
//		},
//		[&](const FLFPInventoryKey& InventoryKey)
//		{
//			ClearSlotEmptyItem(InventoryKey.SlotNameIndex);
//		}
//	);
//
//	return bAllProcessSuccess;
//}
//
//bool ULFPInventoryComponent::TransferItem(const FLFPInventorySearchTransfer& SearchTransferData, ULFPInventoryComponent* TargetInventoryComponent, const FGameplayTag EventTag)
//{
//	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client
//
//	if (IsValid(TargetInventoryComponent) == false)
//	{
//		UE_LOG(LFPInventoryComponent, Warning, TEXT("TargetInventoryComponent Is Not Valid On ( TransferItem )"));
//
//		return false;
//	}
//
//	if (SearchTransferData.IsValid() == false)
//	{
//		UE_LOG(LFPInventoryComponent, Warning, TEXT("SearchTransferData Is Not Valid On ( TransferItem )"));
//
//		return false;
//	}
//
//	FLFPInventorySearchChange FromChange(SearchTransferData.FromIndex, SearchTransferData.ItemData);
//	FLFPInventorySearchChange ToChange(SearchTransferData.ToIndex, SearchTransferData.ItemData);
//
//	if (CheckItem(FromChange, true) == false || TargetInventoryComponent->CheckItem(ToChange, false) == false)
//	{
//		UE_LOG(LFPInventoryComponent, Warning, TEXT("TransferItem Check Fail"));
//
//		return false;
//	}
//
//	RemoveItem(FromChange, EventTag);
//
//	TargetInventoryComponent->AddItem(ToChange, EventTag);
//
//	return true;
//}

bool ULFPInventoryComponent::SortItem(const FGameplayTag SortTag, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	return false;
}

void ULFPInventoryComponent::ClearInventory(const FGameplayTagContainer SlotNames, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return; // Prevent this function to run on client

	const bool bProcessSuccess = ProcessInventoryIndex(
		FLFPInventorySearch(SlotNames),
		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CopyItemData, const FLFPInventoryKey& InventoryKey)
		{
			if (CopyItemData.IsValid() == false)
			{
				return false;
			}

			GetSlotItemRef(InventoryKey) = FLFPInventoryItem();

			return false;
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

bool ULFPInventoryComponent::CanAddItem(const FLFPInventoryItem& ItemData) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			return FunctionObj->CanAddItem(ItemData);
		}
	);
}

bool ULFPInventoryComponent::CanRemoveItem(const FLFPInventoryItem& ItemData) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			return FunctionObj->CanRemoveItem(ItemData);
		}
	);
}

//bool ULFPInventoryComponent::CanSwapItem(const FLFPInventoryIndex& FromIndex, const FLFPInventoryIndex& ToIndex) const
//{
//	return ProcessInventoryFunction(
//		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
//		{
//			return FunctionObj->CanSwapItem(FromIndex, ToIndex);
//		}
//	);
//}

bool ULFPInventoryComponent::CanAddItemOnSlot(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			return FunctionObj->CanAddItemOnSlot(InventoryIndex, CurrentData, ProcessData);
		}
	);
}

bool ULFPInventoryComponent::CanRemoveItemOnSlot(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			return FunctionObj->CanRemoveItemOnSlot(InventoryIndex, CurrentData, ProcessData);
		}
	);
}

//bool ULFPInventoryComponent::CanSwapItemOnSlot(const FLFPInventoryIndex& FromInventoryIndex, const FLFPInventoryItem& FromData, const FLFPInventoryIndex& ToInventoryIndex, const FLFPInventoryItem& ToData) const
//{
//	return ProcessInventoryFunction(
//		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
//		{
//			return FunctionObj->CanSwapItemOnSlot(FromInventoryIndex, FromData, ToInventoryIndex, ToData);
//		}
//	);
//}

bool ULFPInventoryComponent::ProcessAddItem(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			return FunctionObj->ProcessAddItem(ItemData, ProcessData, InventoryIndex);
		}
	);
}

bool ULFPInventoryComponent::ProcessRemoveItem(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			return FunctionObj->ProcessRemoveItem(ItemData, ProcessData, InventoryIndex);
		}
	);
}

//bool ULFPInventoryComponent::ProcessSwapItem(UPARAM(ref)FLFPInventoryItem& ItemDataA, const FLFPInventoryIndex& InventoryIndexA, UPARAM(ref)FLFPInventoryItem& ItemDataB, const FLFPInventoryIndex& InventoryIndexB) const
//{
//	return ProcessInventoryFunction(
//		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
//		{
//			return FunctionObj->ProcessSwapItem(ItemDataA, InventoryIndexA, ItemDataB, InventoryIndexB);
//		}
//	);
//}

FGameplayTagContainer ULFPInventoryComponent::GetItemCatergorize(const FLFPInventoryItem& ItemData) const
{
	FGameplayTagContainer Result = FGameplayTagContainer();

	ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			Result.AppendTags(FunctionObj->GetItemCatergorize(ItemData));

			return true;
		}
	);

	return Result;
}

FLFPInventorySearch ULFPInventoryComponent::GetItemInventorySearch(const FLFPInventoryItem& ItemData) const
{
	FLFPInventorySearch Result = FLFPInventorySearch();

	ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			Result += FunctionObj->GetItemInventorySearch(ItemData);

			return true;
		}
	);

	return Result;
}

//bool ULFPInventoryComponent::CanItemSortHigherThan(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB, const FGameplayTag& SortTag) const
//{
//	return ProcessInventoryFunction(
//		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
//		{
//			return FunctionObj->CanItemSortHigherThan(ItemDataA, ItemDataB, SortTag);
//		}
//	);
//}
//
//
//bool ULFPInventoryComponent::ContainItem(const FLFPInventoryItem& ItemData, const FLFPInventorySearch& InventorySearch) const
//{
//	FLFPInventoryItem ProcessData = ItemData;
//
//	return ProcessInventoryIndex(
//		InventorySearch,
//		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CopyItemData, const FLFPInventoryKey& InventoryKey)
//		{
//			return RemoveItem_Internal_Check(InventoryIndex, CopyItemData, InventoryKey, ProcessData);
//		}
//	);
//}
//
//bool ULFPInventoryComponent::ContainItemList(const TArray<FLFPInventoryItem>& ItemDataList, const FLFPInventorySearch& InventorySearch, const bool bPartially) const
//{
//	for (const auto& ItemData : ItemDataList)
//	{
//		const bool bIsSearchComplete = ContainItem(ItemData, InventorySearch);
//
//		if (bPartially)
//		{
//			if (bIsSearchComplete) return true;
//		}
//		else if (bIsSearchComplete == false)
//		{
//			break;
//		}
//	}
//
//	return false;
//}
//
//bool ULFPInventoryComponent::ContainItemCatergorize(const FGameplayTagContainer Catergorizes, const FLFPInventorySearch& InventorySearch, const bool bContainAll, const bool bCombineSearch) const
//{
//	FGameplayTagContainer TotalCatergorizes = FGameplayTagContainer::EmptyContainer;
//
//	const bool bIsSucess = ProcessInventoryIndex(
//		InventorySearch,
//		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CopyItemData, const FLFPInventoryKey& InventoryKey)
//		{
//			if (CopyItemData.IsValid() == false) return false;
//
//			if (bContainAll == false) return GetItemCatergorize(CopyItemData).HasAny(Catergorizes);
//
//			if (bCombineSearch == false) return GetItemCatergorize(CopyItemData).HasAll(Catergorizes);
//
//			TotalCatergorizes.AppendTags(GetItemCatergorize(CopyItemData));
//
//			return TotalCatergorizes.HasAll(Catergorizes);
//		}
//	);
//
//
//	return bIsSucess;
//}
//
//bool ULFPInventoryComponent::IsSlotNameValid(const FGameplayTag SlotName) const
//{
//	for (const auto& Slot : InventorySlot)
//	{
//		if (Slot.SlotName.MatchesTag(SlotName)) return true;
//	}
//
//	return false;
//}



FLFPInventoryItem ULFPInventoryComponent::GetSlotItem(const FLFPInventoryIndex& InventoryIndex) const
{
	for (const auto& Slot : InventorySlot)
	{
		if (Slot.SlotName == InventoryIndex.SlotName) return Slot.GetItemCopy(InventoryIndex.SlotIndex);
	}

	return FLFPInventoryItem();
}

FLFPInventoryKey ULFPInventoryComponent::GetInventoryKey(const FLFPInventoryIndex& InventoryIndex) const
{
	for (int32 Index = 0; Index < InventorySlot.Num(); Index++)
	{
		if (InventorySlot[Index].SlotName == InventoryIndex.SlotName) return FLFPInventoryKey(InventoryIndex.SlotIndex, Index);
	}

	return FLFPInventoryKey();
}

FLFPInventoryItem ULFPInventoryComponent::GetSlotItemCopy(const FLFPInventoryKey& InventoryKey) const
{
	return InventorySlot[InventoryKey.SlotNameIndex].GetItemCopy(InventoryKey.SlotIndex);
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



//bool ULFPInventoryComponent::FindInventoryIndexList(TArray<FLFPInventoryIndex>& InventoryIndexList, const FLFPInventoryItem& ItemData, const FGameplayTagContainer SlotNames, const FGameplayTagContainer Catergorizes, const bool bContainAllCatergorize, const int32 MaxListItem) const
//{
//	if (ItemData.IsValid() == false)
//	{
//		return false;
//	}
//
//	int32 ItemCount = 0;
//
//	FLFPInventoryItem ProcessData = ItemData;
//
//	ProcessInventoryIndex(
//		FLFPInventorySearch(SlotNames),
//		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CopyItemData, const FLFPInventoryKey& InventoryKey)
//		{
//			// Check Catergorizes
//			if (Catergorizes.IsEmpty() == false)
//			{
//				if ((bContainAllCatergorize ? 
//					GetItemCatergorize(CopyItemData).HasAll(Catergorizes)
//						: 
//					GetItemCatergorize(CopyItemData).HasAny(Catergorizes)
//					) == false)
//				{
//					return false;
//				}
//			}
//
//			if (RemoveItem_Internal_Check(InventoryIndex, CopyItemData, InventoryKey, ProcessData))
//			{
//				InventoryIndexList.Add(InventoryIndex);
//
//				ItemCount++;
//			}
//
//			return MaxListItem != INDEX_NONE ? MaxListItem <= ItemCount : false;
//		}
//	);
//
//	return ItemCount != 0;
//}
//
//bool ULFPInventoryComponent::FindItemDataList(TArray<FLFPInventoryItem>& ItemIndexList, const FLFPInventoryItem& ItemData, const FGameplayTagContainer SlotNames, const FGameplayTagContainer Catergorizes, const bool bContainAllCatergorize, const int32 MaxListItem) const
//{
//	if (ItemData.IsValid() == false)
//	{
//		return false;
//	}
//
//	int32 ItemCount = 0;
//
//	FLFPInventoryItem ProcessData = ItemData;
//
//	ProcessInventoryIndex(
//		FLFPInventorySearch(SlotNames),
//		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CopyItemData, const FLFPInventoryKey& InventoryKey)
//		{
//			// Check Catergorizes
//			if (Catergorizes.IsEmpty() == false)
//			{
//				if ((bContainAllCatergorize ?
//					GetItemCatergorize(CopyItemData).HasAll(Catergorizes)
//					:
//					GetItemCatergorize(CopyItemData).HasAny(Catergorizes)
//					) == false)
//				{
//					return false;
//				}
//			}
//
//			if (RemoveItem_Internal_Check(InventoryIndex, CopyItemData, InventoryKey, ProcessData))
//			{
//				ItemIndexList.Add(CopyItemData);
//
//				ItemCount++;
//			}
//
//			return MaxListItem != INDEX_NONE ? MaxListItem <= ItemCount : false;
//		}
//	);
//
//	return ItemCount != 0;
//}
