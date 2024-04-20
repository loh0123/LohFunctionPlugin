// Copyright (c) 2023-2024 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#include "Item/LFPInventoryComponent.h"
#include "Item/FunctionObject/LFPItemInventoryFunction.h"
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
	ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			check(FunctionObj.Get()->GetOuter());

			AddReplicatedSubObject(FunctionObj.Get());

			FunctionObj.Get()->InitializeComponent();

			return true;
		}
	);
	////////////////////////////////////////////////////
}

void ULFPInventoryComponent::UninitializeComponent()
{
	Super::UninitializeComponent();

	/* For Supporting Function List Object Replication */
	ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			RemoveReplicatedSubObject(FunctionObj.Get());

			FunctionObj.Get()->UninitializeComponent();

			return true;
		}
	);
	////////////////////////////////////////////////////
}

bool ULFPInventoryComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	/* For Supporting Function List Object Replication */
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			Channel->ReplicateSubobject(FunctionObj.Get(), *Bunch, *RepFlags);

			return true;
		}
	);
	////////////////////////////////////////////////////
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

void ULFPInventoryComponent::SendTransferDelegateEvent_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const
{
	OnTransferItem.Broadcast(InventoryIndex, NewData, OldData, EventTag);
	OnUpdateItem.Broadcast(InventoryIndex, NewData, OldData, EventTag);
}

void ULFPInventoryComponent::SendUpdateDelegateEvent_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const
{
	OnUpdateItem.Broadcast(InventoryIndex, NewData, OldData, EventTag);
}


const FLFPInventorySlotList& ULFPInventoryComponent::GetInventorySlotList() const
{
	return InventorySlot;
}

bool ULFPInventoryComponent::ProcessInventoryIndex(
	const FLFPInventorySearch& InventoryCategorize,
	const TFunctionRef<bool(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex)> IndexFunction,
	const bool bUseMaxIndex,
	const TFunction<void(const int32 SlotListIndex)> OnSlotNameEnd
) const
{
	UE_LOG(LFPInventoryComponent, VeryVerbose, TEXT("ProcessInventoryIndex Start"));

	for (int32 SlotDataIndex = 0; SlotDataIndex < InventorySlot.GetSlotListConst().Num(); SlotDataIndex++)
	{
		const FLFPInventorySlot& SlotData = InventorySlot.GetSlotListConst()[SlotDataIndex];

		if (InventoryCategorize.IsTagMatch(SlotData.SlotName) == false)
		{
			UE_LOG(LFPInventoryComponent, Verbose, TEXT("ProcessInventoryIndex Skip Slot Bacause Tag : %s"), *InventoryCategorize.ToString());

			continue; // Tag Not Match Any One On Search
		}

		// If SearchIndex.SlotIndex Is Invalid Than Loop All SlotData Item And Additional Index
		int32 Index				= 0;
		const int32 MaxIndex	= bUseMaxIndex ? SlotData.GetMaxNum(ExtraLoopSlot) : SlotData.GetItemNum();
		//

		UE_LOG(LFPInventoryComponent, Verbose, TEXT("ProcessInventoryIndex SlotData Start : Name = %s | StartIndex = %d | EndIndex = %d"), *SlotData.SlotName.ToString(), Index, MaxIndex);

		for (Index; Index <= MaxIndex; Index++)
		{
			const FLFPInventoryIndex InventoryIndex(Index, SlotData.SlotName);
			const FLFPInventoryInternalIndex InventoryInternalIndex((InventorySlot.ToInventoryIndexInternal(FLFPInventoryIndex(Index, SlotData.SlotName))));

			if (InventoryInternalIndex.IsValid() == false) continue;

			if (InventoryCategorize.IsCatergorizesMatch(GetIndexCatergorize(InventoryInternalIndex)) == false)
			{
				UE_LOG(LFPInventoryComponent, Verbose, TEXT("ProcessInventoryIndex Skip Index Bacause Catergorizes Not Match : %s"), *InventoryCategorize.ToString());

				continue; // Tag Not Match Any One On Search
			}

			if (IndexFunction(InventoryIndex, InventoryInternalIndex))
			{
				UE_LOG(LFPInventoryComponent, Verbose, TEXT("ProcessInventoryIndex Success : %s"), *InventoryIndex.ToString());

				return true;
			}
		}

		UE_LOG(LFPInventoryComponent, Verbose, TEXT("ProcessInventoryIndex SlotData End : %s"), *SlotData.SlotName.ToString());

		if (OnSlotNameEnd) OnSlotNameEnd(SlotDataIndex);
	}

	UE_LOG(LFPInventoryComponent, VeryVerbose, TEXT("ProcessInventoryIndex Fail"));

	return false;
}

bool ULFPInventoryComponent::ProcessInventoryFunction(const TFunctionRef<bool(const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)> RunFunction) const
{
	for (const auto& FunctionObj : FunctionList)
	{
		if (IsValid(FunctionObj) == false)
		{
			UE_LOG(LFPInventoryComponent, Warning, TEXT("InitializeComponent : FunctionObj Invalids"));

			continue;
		}

		if (RunFunction(FunctionObj) == false) return false;
	}

	if (FunctionList.IsEmpty())
	{
		UE_LOG(LFPInventoryComponent, Warning, TEXT("ProcessInventoryFunction FunctionList Is Empty"));

		return false;
	}

	return true;
}


bool ULFPInventoryComponent::AddItem_Internal(const FLFPInventoryIndex& InventoryIndex, FLFPInventoryItem& ProcessItemData, const FGameplayTag& EventTag)
{
	const FLFPInventoryInternalIndex InventoryInternalIndex((InventorySlot.ToInventoryIndexInternal(InventoryIndex)));

	if (InventoryInternalIndex.IsValid() == false) return false;

	FLFPInventoryItem OldItemData = InventorySlot.GetSlotItemConst(InventoryInternalIndex);

	if (CanAddItemOnSlot(InventoryIndex, OldItemData, ProcessItemData) == false) return false;

	FLFPInventoryItem& NewItemData = InventorySlot.GetSlotItemRef(InventoryInternalIndex);

	const bool bSuccess = ProcessAddItem(NewItemData, ProcessItemData, InventoryIndex);

	if (EventTag.IsValid() && OldItemData != NewItemData) // Don't Send Event If Tag Is Not Valid Or No Change (Prevent Network Overload)
	{
		SendAddDelegateEvent(InventoryIndex, NewItemData, OldItemData, EventTag);
	}

	return bSuccess;
}

bool ULFPInventoryComponent::AddItem_Internal_Check(const FLFPInventoryIndex& InventoryIndex, FLFPInventoryItem& ProcessItemData) const
{
	const FLFPInventoryInternalIndex InventoryInternalIndex((InventorySlot.ToInventoryIndexInternal(InventoryIndex)));

	if (InventoryInternalIndex.IsValid() == false) return false;

	FLFPInventoryItem TestItem = InventorySlot.GetSlotItemConst(InventoryInternalIndex);

	if (CanAddItemOnSlot(InventoryIndex, TestItem, ProcessItemData) == false) return false;

	return ProcessAddItem(TestItem, ProcessItemData, InventoryIndex);
}

bool ULFPInventoryComponent::RemoveItem_Internal(const FLFPInventoryIndex& InventoryIndex, FLFPInventoryItem& ProcessItemData, const FGameplayTag& EventTag)
{
	const FLFPInventoryInternalIndex InventoryInternalIndex((InventorySlot.ToInventoryIndexInternal(InventoryIndex)));

	if (InventoryInternalIndex.IsValid() == false) return false;

	FLFPInventoryItem OldItemData = InventorySlot.GetSlotItemConst(InventoryInternalIndex);

	if (CanRemoveItemOnSlot(InventoryIndex, OldItemData, ProcessItemData) == false) return false;

	FLFPInventoryItem& NewItemData = InventorySlot.GetSlotItemRef(InventoryInternalIndex);

	const bool bSuccess = ProcessRemoveItem(NewItemData, ProcessItemData, InventoryIndex);

	if (EventTag.IsValid() && OldItemData != NewItemData) // Don't Send Event If Tag Is Not Valid Or No Change (Prevent Network Overload)
	{
		SendRemoveDelegateEvent(InventoryIndex, NewItemData, OldItemData, EventTag);
	}

	InventorySlot.ClearSlotEmptyItem(InventoryInternalIndex.SlotListIndex);

	return bSuccess;
}

bool ULFPInventoryComponent::RemoveItem_Internal_Check(const FLFPInventoryIndex& InventoryIndex, FLFPInventoryItem& ProcessItemData) const
{
	const FLFPInventoryInternalIndex InventoryInternalIndex((InventorySlot.ToInventoryIndexInternal(InventoryIndex)));

	if (InventoryInternalIndex.IsValid() == false) return false;

	FLFPInventoryItem TestItem = InventorySlot.GetSlotItemConst(InventoryInternalIndex);

	if (CanRemoveItemOnSlot(InventoryIndex, TestItem, ProcessItemData) == false) return false;

	return ProcessRemoveItem(TestItem, ProcessItemData, InventoryIndex);
}

bool ULFPInventoryComponent::SwapItem_Internal(const FLFPInventoryIndex& FromIndex, const FLFPInventoryIndex& ToIndex, const FGameplayTag& EventTag)
{
	const FLFPInventoryInternalIndex FromInventoryInternalIndex((InventorySlot.ToInventoryIndexInternal(FromIndex)));
	const FLFPInventoryInternalIndex ToInventoryInternalIndex((InventorySlot.ToInventoryIndexInternal(ToIndex)));

	if (FromInventoryInternalIndex.IsValid() == false) return false;
	if (ToInventoryInternalIndex.IsValid() == false) return false;

	const FLFPInventoryItem& CopyFromItem = InventorySlot.GetSlotItemConst(FromInventoryInternalIndex);
	const FLFPInventoryItem& CopyToItem = InventorySlot.GetSlotItemConst(ToInventoryInternalIndex);

	if (CanSwapItem(CopyFromItem, CopyToItem) == false) return false;

	if (CanSwapItemOnSlot(CopyFromItem, FromIndex, CopyToItem, ToIndex) == false) return false;

	// Reserve Index To Prevent Array Change After Getting Ref
	InventorySlot.ReserveItemIndex(FromInventoryInternalIndex);
	InventorySlot.ReserveItemIndex(ToInventoryInternalIndex);

	FLFPInventoryItem& FromData =	InventorySlot.GetSlotItemRef(FromInventoryInternalIndex);
	FLFPInventoryItem& ToData =		InventorySlot.GetSlotItemRef(ToInventoryInternalIndex);

	const bool bSuccess = ProcessSwapItem(FromData, FromIndex, ToData, ToIndex);

	if (EventTag.IsValid() && CopyFromItem != FromData) // Don't Send Event If Tag Is Not Valid Or No Change (Prevent Network Overload)
	{
		SendSwapDelegateEvent(FromIndex, FromData, CopyFromItem, EventTag);
	}

	if (EventTag.IsValid() && CopyToItem != ToData) // Don't Send Event If Tag Is Not Valid Or No Change (Prevent Network Overload)
	{
		SendSwapDelegateEvent(ToIndex, ToData, CopyToItem, EventTag);
	}

	InventorySlot.ClearSlotEmptyItem(FromInventoryInternalIndex.SlotListIndex);
	InventorySlot.ClearSlotEmptyItem(ToInventoryInternalIndex.SlotListIndex);

	return bSuccess;
}

bool ULFPInventoryComponent::Transfer_Index_Internal(const FLFPInventoryIndex& FromIndex, const FLFPInventoryIndex& ToIndex, ULFPInventoryComponent* TargetInventoryComponent, const FGameplayTag EventTag)
{
	const FLFPInventoryInternalIndex FromInventoryInternalIndex((InventorySlot.ToInventoryIndexInternal(FromIndex)));

	if (FromInventoryInternalIndex.IsValid() == false) return false;

	if (InventorySlot.IsSlotItemValid(FromInventoryInternalIndex) == false) return false;

	FLFPInventoryItem& RefOfFrom = InventorySlot.GetSlotItemRef(FromInventoryInternalIndex);
	FLFPInventoryItem CopyOfFrom = RefOfFrom;

	const bool bSuccess = TargetInventoryComponent->AddItemByIndex(ToIndex, RefOfFrom, EventTag);

	if (EventTag.IsValid() && CopyOfFrom != RefOfFrom) // Don't Send Event If Tag Is Not Valid Or No Change (Prevent Network Overload)
	{
		SendTransferDelegateEvent(FromIndex, RefOfFrom, CopyOfFrom, EventTag);
	}

	return bSuccess;
}

bool ULFPInventoryComponent::Transfer_Search_Internal(const FLFPInventoryIndex& FromIndex, const FLFPInventorySearch& ToSearch, ULFPInventoryComponent* TargetInventoryComponent, const FGameplayTag EventTag)
{
	const FLFPInventoryInternalIndex FromInventoryInternalIndex((InventorySlot.ToInventoryIndexInternal(FromIndex)));

	if (FromInventoryInternalIndex.IsValid() == false) return false;

	if (InventorySlot.IsSlotItemValid(FromInventoryInternalIndex) == false) return false;

	FLFPInventoryItem& RefOfFrom = InventorySlot.GetSlotItemRef(FromInventoryInternalIndex);
	FLFPInventoryItem CopyOfFrom = RefOfFrom;

	const bool bSuccess = TargetInventoryComponent->AddItemBySearch(ToSearch, RefOfFrom, EventTag);

	if (EventTag.IsValid() && CopyOfFrom != RefOfFrom) // Don't Send Event If Tag Is Not Valid Or No Change (Prevent Network Overload)
	{
		SendTransferDelegateEvent(FromIndex, RefOfFrom, CopyOfFrom, EventTag);
	}

	return bSuccess;
}

bool ULFPInventoryComponent::UpdateItem_Internal(const FLFPInventoryIndex& InventoryIndex, FLFPInventoryItem& ProcessItemData, const FGameplayTag& EventTag)
{
	const FLFPInventoryInternalIndex InventoryInternalIndex((InventorySlot.ToInventoryIndexInternal(InventoryIndex)));

	if (InventoryInternalIndex.IsValid() == false) return false;

	if (CanUpdateItemOnSlot(InventoryIndex, InventorySlot.GetSlotItemConst(InventoryInternalIndex), ProcessItemData) == false) return false;

	FLFPInventoryItem OldItemData = InventorySlot.GetSlotItemConst(InventoryInternalIndex);
	FLFPInventoryItem& NewItemData = InventorySlot.GetSlotItemRef(InventoryInternalIndex);

	const bool bSuccess = ProcessUpdateItem(NewItemData, ProcessItemData, InventoryIndex);

	if (EventTag.IsValid() && OldItemData != NewItemData) // Don't Send Event If Tag Is Not Valid Or No Change (Prevent Network Overload)
	{
		SendUpdateDelegateEvent(InventoryIndex, NewItemData, OldItemData, EventTag);
	}

	return bSuccess;
}

bool ULFPInventoryComponent::ContainItem_Internal(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex, FLFPInventoryItem& ProcessItemData) const
{
	if (CanContainItemOnSlot(InventoryIndex, InventorySlot.GetSlotItemConst(InventoryInternalIndex), ProcessItemData) == false) return false;

	return ProcessContainItem(InventorySlot.GetSlotItemConst(InventoryInternalIndex), ProcessItemData, InventoryIndex);
}

bool ULFPInventoryComponent::FindItem_Internal(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex, FLFPInventoryItem& ProcessItemData) const
{
	if (CanContainItemOnSlot(InventoryIndex, InventorySlot.GetSlotItemConst(InventoryInternalIndex), ProcessItemData) == false) return false;

	ProcessContainItem(InventorySlot.GetSlotItemConst(InventoryInternalIndex), ProcessItemData, InventoryIndex);

	return true;
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
		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex)
		{
			return AddItem_Internal(InventoryIndex, ItemData, EventTag);
		}, 
		true);
}

bool ULFPInventoryComponent::AddItemListBySearch(const FLFPInventorySearch& InventorySearch, UPARAM(ref)TArray<FLFPInventoryItem>& ItemDataList, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	bool bIsSuccess = true;

	for (FLFPInventoryItem& ItemData : ItemDataList)
	{
		if (AddItemBySearch(InventorySearch, ItemData, EventTag) == false)
		{
			bIsSuccess = false;
		}
	}

	return bIsSuccess;
}

bool ULFPInventoryComponent::AddItemByIndex(const FLFPInventoryIndex& InventoryIndex, UPARAM(ref) FLFPInventoryItem& ItemData, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (CanAddItem(ItemData) == false) return false;

	return AddItem_Internal(InventoryIndex, ItemData, EventTag);
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
		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex)
		{
			return RemoveItem_Internal(InventoryIndex, ItemData, EventTag);
		},
		false,
		[&](const int32 SlotListIndex)
		{
			InventorySlot.ClearSlotEmptyItem(SlotListIndex);
		});
}

bool ULFPInventoryComponent::RemoveItemListBySearch(const FLFPInventorySearch& InventorySearch, UPARAM(ref)TArray<FLFPInventoryItem>& ItemDataList, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	bool bIsSuccess = true;

	for (FLFPInventoryItem& ItemData : ItemDataList)
	{
		if (RemoveItemBySearch(InventorySearch, ItemData, EventTag) == false)
		{
			bIsSuccess = false;
		}
	}

	return bIsSuccess;
}

bool ULFPInventoryComponent::RemoveItemByIndex(const FLFPInventoryIndex& InventoryIndex, UPARAM(ref) FLFPInventoryItem& ItemData, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (CanRemoveItem(ItemData) == false) return false;

	return RemoveItem_Internal(InventoryIndex, ItemData, EventTag);
}


bool ULFPInventoryComponent::SwapItemToIndex(const FLFPInventoryIndex& FromIndex, const FLFPInventoryIndex& ToIndex, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	return SwapItem_Internal(FromIndex, ToIndex, EventTag);
}

bool ULFPInventoryComponent::SwapItemToSearch(const FLFPInventoryIndex& FromIndex, const FLFPInventorySearch& ToSearch, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	return ProcessInventoryIndex(
		ToSearch,
		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex)
		{
			return SwapItemToIndex(FromIndex, InventoryIndex, EventTag);
		},
		true);
}


bool ULFPInventoryComponent::TransferItemToIndex(const FLFPInventoryIndex& FromIndex, const FLFPInventoryIndex& ToIndex, ULFPInventoryComponent* TargetInventoryComponent, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	return Transfer_Index_Internal(FromIndex, ToIndex, TargetInventoryComponent, EventTag);
}

bool ULFPInventoryComponent::TransferItemToSearch(const FLFPInventoryIndex& FromIndex, const FLFPInventorySearch& ToSearch, ULFPInventoryComponent* TargetInventoryComponent, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	return Transfer_Search_Internal(FromIndex, ToSearch, TargetInventoryComponent, EventTag);
}


bool ULFPInventoryComponent::UpdateItem(UPARAM(ref)FLFPInventoryItem& ItemData, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	return UpdateItemBySearch(GetItemInventorySearch(ItemData), ItemData, EventTag);
}

bool ULFPInventoryComponent::UpdateItemBySearch(const FLFPInventorySearch& InventorySearch, UPARAM(ref)FLFPInventoryItem& ItemData, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (CanUpdateItem(ItemData) == false) return false;

	return ProcessInventoryIndex(
		InventorySearch,
		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex)
		{
			return UpdateItem_Internal(InventoryIndex, ItemData, EventTag);
		});
}

bool ULFPInventoryComponent::UpdateItemByIndex(const FLFPInventoryIndex& InventoryIndex, UPARAM(ref)FLFPInventoryItem& ItemData, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (CanUpdateItem(ItemData) == false) return false;

	return UpdateItem_Internal(InventoryIndex, ItemData, EventTag);
}


bool ULFPInventoryComponent::SortItem(const FLFPInventorySearch& InventorySearch, UPARAM(meta = (Categories = "Item.Sort")) const FGameplayTag SortTag, UPARAM(meta = (Categories = "Item.Event")) const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	InventorySlot.SortSlot(
		InventorySearch,
		[&](const FGameplayTag& SlotName)
		{
			return CanSlotNameBeSort(SlotName);
		},
		[&](const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB)
		{
			return CanItemSortHigherThan(ItemDataA, ItemDataB, SortTag);
		}
	);

	return true;
}

void ULFPInventoryComponent::ClearInventory(UPARAM(meta = (Categories = "Item.SlotName")) const FGameplayTagContainer SlotNames, UPARAM(meta = (Categories = "Item.Event")) const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return; // Prevent this function to run on client

	const bool bProcessSuccess = ProcessInventoryIndex(
		FLFPInventorySearch(SlotNames),
		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex)
		{
			if (InventorySlot.IsSlotItemValid(InventoryInternalIndex) == false)
			{
				return false;
			}

			InventorySlot.GetSlotItemRef(InventoryInternalIndex) = FLFPInventoryItem();

			return false;
		},
		false,
		[&](const int32 SlotListIndex)
		{
			InventorySlot.ClearSlotEmptyItem(SlotListIndex);
		}
	);

	return;
}


ULFPItemInventoryFunction* ULFPInventoryComponent::GetFunctionObject(const TSubclassOf<ULFPItemInventoryFunction> FunctionClass) const
{
	if (FunctionClass == nullptr) return nullptr;

	ULFPItemInventoryFunction* ReturnPtr = nullptr;

	ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			if (FunctionObj.GetClass() == FunctionClass.Get())
			{
				ReturnPtr = FunctionObj;

				/* Stop The Loop Using False */
				return false;
			}

			return true;
		}
	);

	return ReturnPtr;
}


bool ULFPInventoryComponent::CanAddItem(const FLFPInventoryItem& ItemData) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			const bool bSuccess = FunctionObj->CanAddItem(ItemData);

			if (bSuccess == false)
			{
				UE_LOG(LFPInventoryComponent, Verbose, TEXT("CanAddItem Fail : FunctionObj = %s | ItemData = %s"), *FunctionObj->GetName(), *ItemData.ToString());
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::CanRemoveItem(const FLFPInventoryItem& ItemData) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			const bool bSuccess = FunctionObj->CanRemoveItem(ItemData);

			if (bSuccess == false)
			{
				UE_LOG(LFPInventoryComponent, Verbose, TEXT("CanRemoveItem Fail : FunctionObj = %s | ItemData = %s"), *FunctionObj->GetName(), *ItemData.ToString());
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::CanSwapItem(const FLFPInventoryItem& FromItem, const FLFPInventoryItem& ToItem) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			const bool bSuccess = FunctionObj->CanSwapItem(FromItem, ToItem);

			if (bSuccess == false)
			{
				UE_LOG(LFPInventoryComponent, Verbose, TEXT("CanSwapItem Fail : FunctionObj = %s | FromItem = %s | ToItem = %s"), *FunctionObj->GetName(), *FromItem.ToString(), *ToItem.ToString());
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::CanUpdateItem(const FLFPInventoryItem& ItemData) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			const bool bSuccess = FunctionObj->CanUpdateItem(ItemData);

			if (bSuccess == false)
			{
				UE_LOG(LFPInventoryComponent, Verbose, TEXT("CanUpdateItem Fail : FunctionObj = %s | ItemData = %s"), *FunctionObj->GetName(), *ItemData.ToString());
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::CanContainItem(const FLFPInventoryItem& ItemData) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			const bool bSuccess = FunctionObj->CanContainItem(ItemData);

			if (bSuccess == false)
			{
				UE_LOG(LFPInventoryComponent, Verbose, TEXT("CanContainItem Fail : FunctionObj = %s | ItemData = %s"), *FunctionObj->GetName(), *ItemData.ToString());
			}

			return bSuccess;
		}
	);
}


bool ULFPInventoryComponent::CanAddItemOnSlot(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			const bool bSuccess = FunctionObj->CanAddItemOnSlot(InventoryIndex, CurrentData, ProcessData);

			if (bSuccess == false)
			{
				UE_LOG(LFPInventoryComponent, Verbose, TEXT("CanAddItemOnSlot Fail : FunctionObj = %s | InventoryIndex = %s"), *FunctionObj->GetName(), *InventoryIndex.ToString());
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::CanRemoveItemOnSlot(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			const bool bSuccess = FunctionObj->CanRemoveItemOnSlot(InventoryIndex, CurrentData, ProcessData);

			if (bSuccess == false)
			{
				UE_LOG(LFPInventoryComponent, Verbose, TEXT("CanRemoveItemOnSlot Fail : FunctionObj = %s | InventoryIndex = %s"), *FunctionObj->GetName(), *InventoryIndex.ToString());
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::CanSwapItemOnSlot(const FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, const FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			const bool bSuccess = FunctionObj->CanSwapItemOnSlot(FromItem, FromIndex, ToItem, ToIndex);

			if (bSuccess == false)
			{
				UE_LOG(LFPInventoryComponent, Verbose, TEXT("CanSwapItemOnSlot Fail : FunctionObj = %s | FromIndex = %s | ToIndex = %s"), *FunctionObj->GetName(), *FromIndex.ToString(), *ToIndex.ToString());
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::CanUpdateItemOnSlot(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			const bool bSuccess = FunctionObj->CanUpdateItemOnSlot(InventoryIndex, CurrentData, ProcessData);

			if (bSuccess == false)
			{
				UE_LOG(LFPInventoryComponent, Verbose, TEXT("CanUpdateItemOnSlot Fail : FunctionObj = %s | InventoryIndex = %s"), *FunctionObj->GetName(), *InventoryIndex.ToString());
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::CanContainItemOnSlot(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			const bool bSuccess = FunctionObj->CanContainItemOnSlot(InventoryIndex, CurrentData, ProcessData);

			if (bSuccess == false)
			{
				UE_LOG(LFPInventoryComponent, Verbose, TEXT("CanContainItemOnSlot Fail : FunctionObj = %s | InventoryIndex = %s"), *FunctionObj->GetName(), *InventoryIndex.ToString());
			}

			return bSuccess;
		}
	);
}


bool ULFPInventoryComponent::ProcessAddItem(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			const bool bSuccess = FunctionObj->ProcessAddItem(ItemData, ProcessData, InventoryIndex);

			if (bSuccess == false)
			{
				UE_LOG(LFPInventoryComponent, VeryVerbose, TEXT("ProcessAddItem Fail : FunctionObj = %s | InventoryIndex = %s"), *FunctionObj->GetName(), *InventoryIndex.ToString());
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::ProcessRemoveItem(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			const bool bSuccess = FunctionObj->ProcessRemoveItem(ItemData, ProcessData, InventoryIndex);

			if (bSuccess == false)
			{
				UE_LOG(LFPInventoryComponent, VeryVerbose, TEXT("ProcessRemoveItem Fail : FunctionObj = %s | InventoryIndex = %s"), *FunctionObj->GetName(), *InventoryIndex.ToString());
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::ProcessSwapItem(UPARAM(ref)FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, UPARAM(ref)FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			const bool bSuccess = FunctionObj->ProcessSwapItem(FromItem, FromIndex, ToItem, ToIndex);

			if (bSuccess == false)
			{
				UE_LOG(LFPInventoryComponent, VeryVerbose, TEXT("ProcessSwapItem Fail : FunctionObj = %s | FromIndex = %s | ToIndex = %s"), *FunctionObj->GetName(), *FromIndex.ToString(), *ToIndex.ToString());
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::ProcessUpdateItem(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			const bool bSuccess = FunctionObj->ProcessUpdateItem(ItemData, ProcessData, InventoryIndex);

			if (bSuccess == false)
			{
				UE_LOG(LFPInventoryComponent, VeryVerbose, TEXT("ProcessUpdateItem Fail : FunctionObj = %s | InventoryIndex = %s"), *FunctionObj->GetName(), *InventoryIndex.ToString());
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::ProcessContainItem(const FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			const bool bSuccess = FunctionObj->ProcessContainItem(ItemData, ProcessData, InventoryIndex);

			if (bSuccess == false)
			{
				UE_LOG(LFPInventoryComponent, VeryVerbose, TEXT("ProcessContainItem Fail : FunctionObj = %s | InventoryIndex = %s"), *FunctionObj->GetName(), *InventoryIndex.ToString());
			}

			return bSuccess;
		}
	);
}


FGameplayTagContainer ULFPInventoryComponent::GetIndexCatergorize(const FLFPInventoryInternalIndex& InventoryIndex) const
{
	return GetItemCatergorize(InventorySlot.GetSlotItemConst(InventoryIndex));
}

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

bool ULFPInventoryComponent::CanSlotNameBeSort(const FGameplayTag& SlotName) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			return FunctionObj->CanSlotNameBeSort(SlotName);
		}
	);
}

bool ULFPInventoryComponent::CanItemSortHigherThan(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB, const FGameplayTag& SortTag) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			return FunctionObj->CanItemSortHigherThan(ItemDataA, ItemDataB, SortTag);
		}
	);
}


bool ULFPInventoryComponent::ContainItem(FLFPInventoryItem ItemData, const FLFPInventorySearch& InventorySearch) const
{
	if (CanContainItem(ItemData) == false) return false;

	return ProcessInventoryIndex(
		InventorySearch,
		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex)
		{
			return ContainItem_Internal(InventoryIndex, InventoryInternalIndex, ItemData);
		});
}

bool ULFPInventoryComponent::ContainItemList(const TArray<FLFPInventoryItem>& ItemDataList, const FLFPInventorySearch& InventorySearch, const bool bPartially) const
{
	for (const auto& ItemData : ItemDataList)
	{
		const bool bIsSearchComplete = ContainItem(ItemData, InventorySearch);

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


bool ULFPInventoryComponent::IsSlotNameValid(const FGameplayTag SlotName) const
{
	for (const auto& Slot : InventorySlot.GetSlotListConst())
	{
		if (Slot.SlotName.MatchesTag(SlotName)) return true;
	}

	return false;
}

bool ULFPInventoryComponent::IsInventoryIndexReserved(const FLFPInventoryIndex& InventoryIndex) const
{
	const FLFPInventoryInternalIndex InventoryInternalIndex((InventorySlot.ToInventoryIndexInternal(InventoryIndex)));

	if (InventoryInternalIndex.IsValid() == false) return false;

	return InventorySlot.IsSlotIndexValid(InventoryInternalIndex);
}



FLFPInventoryItem ULFPInventoryComponent::GetSlotItem(const FLFPInventoryIndex& InventoryIndex) const
{
	const FLFPInventoryInternalIndex InventoryInternalIndex((InventorySlot.ToInventoryIndexInternal(InventoryIndex)));

	if (InventoryInternalIndex.IsValid() == false) return FLFPInventoryItem::EmptyItem;

	return InventorySlot.GetSlotItemConst(InventoryInternalIndex);
}



bool ULFPInventoryComponent::FindInventoryIndexList(TArray<FLFPInventoryIndex>& InventoryIndexList, FLFPInventoryItem ItemData, const FLFPInventorySearch& InventorySearch, const int32 MaxListItem) const
{
	/* Find Use Same Logic As Contain Item */
	if (CanContainItem(ItemData) == false) return false;

	int32 CurrentAmount = 0;

	ProcessInventoryIndex(
		InventorySearch,
		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex)
		{
			if (FindItem_Internal(InventoryIndex, InventoryInternalIndex, ItemData))
			{
				InventoryIndexList.Add(InventoryIndex);

				CurrentAmount += 1;
			}

			return ItemData.IsValid() == false || (MaxListItem > 0 ? MaxListItem <= CurrentAmount : false);
		});

	return CurrentAmount > 0;
}

bool ULFPInventoryComponent::FindItemDataList(TArray<FLFPInventoryItem>& ItemIndexList, FLFPInventoryItem ItemData, const FLFPInventorySearch& InventorySearch, const int32 MaxListItem) const
{
	/* Find Use Same Logic As Contain Item */
	if (CanContainItem(ItemData) == false) return false;

	int32 CurrentAmount = 0;

	ProcessInventoryIndex(
		InventorySearch,
		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex)
		{
			if (FindItem_Internal(InventoryIndex, InventoryInternalIndex, ItemData))
			{
				ItemIndexList.Add(InventorySlot.GetSlotItemConst(InventoryInternalIndex));

				CurrentAmount += 1;
			}

			return ItemData.IsValid() == false || MaxListItem > 0 ? MaxListItem <= CurrentAmount : false;
		});

	return CurrentAmount > 0;
}


