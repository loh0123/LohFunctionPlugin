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


void ULFPInventoryComponent::SendItemDelegateEvent(const FLFPInventoryItemOperationData& ItemOperationData) const
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return;

	OnItemChange.Broadcast(ItemOperationData);

	CLIENT_SendItemDelegateEvent(ItemOperationData);
}

void ULFPInventoryComponent::CLIENT_SendItemDelegateEvent_Implementation(const FLFPInventoryItemOperationData& ItemOperationData) const
{
	OnItemChange.Broadcast(ItemOperationData);
}

const FLFPInventorySlotList& ULFPInventoryComponent::GetInventorySlotList() const
{
	return InventorySlot;
}

bool ULFPInventoryComponent::ProcessInventoryIndex(
	const FGameplayTagContainer& InventorySlotNameList,
	const TFunctionRef<bool(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex)>& IndexFunction,
	const bool bUseMaxIndex,
	const TFunction<void(const int32 SlotListIndex)> OnSlotNameEnd
) const
{
	UE_LOG(LFPInventoryComponent, VeryVerbose, TEXT("ProcessInventoryIndex Start"));

	for (int32 SlotDataIndex = 0; SlotDataIndex < InventorySlot.GetSlotListConst().Num(); SlotDataIndex++)
	{
		const FLFPInventorySlot& SlotData = InventorySlot.GetSlotListConst()[SlotDataIndex];

		if (SlotData.SlotName.MatchesAny(InventorySlotNameList) == false)
		{
			UE_LOG(LFPInventoryComponent, Verbose, TEXT("ProcessInventoryIndex Skip Slot Bacause Name Not Match : %s"), *InventorySlotNameList.ToString());

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

			//if (InventoryCategorize.IsCatergorizesMatch(GetIndexCatergorize(InventoryInternalIndex)) == false)
			//{
			//	UE_LOG(LFPInventoryComponent, Verbose, TEXT("ProcessInventoryIndex Skip Index Bacause Catergorizes Not Match : %s"), *InventoryCategorize.ToString());

			//	continue; // Tag Not Match Any One On Search
			//}

			if (IndexFunction(InventoryIndex, InventoryInternalIndex))
			{
				UE_LOG(LFPInventoryComponent, Verbose, TEXT("ProcessInventoryIndex Success : %s"), *InventoryIndex.ToString());

				if (OnSlotNameEnd) OnSlotNameEnd(SlotDataIndex);

				return true;
			}
		}

		UE_LOG(LFPInventoryComponent, Verbose, TEXT("ProcessInventoryIndex SlotData End : %s"), *SlotData.SlotName.ToString());

		if (OnSlotNameEnd) OnSlotNameEnd(SlotDataIndex);
	}

	UE_LOG(LFPInventoryComponent, VeryVerbose, TEXT("ProcessInventoryIndex Fail"));

	return false;
}

bool ULFPInventoryComponent::ProcessItemOperation(
	const FGameplayTagContainer& InventorySlotNameList, 
	TArray<FLFPInventoryItem>& ItemDataList, 
	const TFunctionRef<bool(const FLFPInventoryItem& ItemData)>& CheckerFunction,
	const TFunctionRef<bool(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InternalIndex, FLFPInventoryItem& ItemData)>& IndexFunction,
	const bool bStopOnFail,
	const bool bUseMaxIndex
) const
{
	bool bIsSuccess = true;

	for (FLFPInventoryItem& ItemData : ItemDataList)
	{
		if (ItemData.IsValid() == false)
		{
			UE_LOG(LFPInventoryComponent, Warning, TEXT("ProcessItemOperation Skip Invalid Item"));

			continue;
		}

		if (CheckerFunction(ItemData) == false)
		{
			bIsSuccess = false;

			if (bStopOnFail)
			{
				return bIsSuccess;
			}

			continue;
		}

		/* Filter Out Disallow Slot Name List */
		const FGameplayTagContainer ItemAllowSlotNameList = GetItemAllowSlotNameList(ItemData, InventorySlotNameList);

		bIsSuccess = bIsSuccess && ProcessInventoryIndex(
			ItemAllowSlotNameList,
			[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex)
			{
				return IndexFunction(InventoryIndex, InventoryInternalIndex, ItemData);
			},
			bUseMaxIndex
		);

		if (bStopOnFail && bIsSuccess == false)
		{
			return bIsSuccess;
		}
	}

	return bIsSuccess;
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

	FLFPInventoryItem& NewItemData = InventorySlot.GetSlotItemRef(InventoryInternalIndex, true);

	const bool bSuccess = ProcessAddItem(NewItemData, ProcessItemData, InventoryIndex);

	InventorySlot.AddPendingEvent(FLFPInventoryItemOperationData(ELFPInventoryItemEvent::Inventory_Add, InventoryIndex, NewItemData, OldItemData, EventTag));

	return bSuccess;
}

bool ULFPInventoryComponent::RemoveItem_Internal(const FLFPInventoryIndex& InventoryIndex, FLFPInventoryItem& ProcessItemData, const FGameplayTag& EventTag)
{
	const FLFPInventoryInternalIndex InventoryInternalIndex((InventorySlot.ToInventoryIndexInternal(InventoryIndex)));

	if (InventoryInternalIndex.IsValid() == false) return false;

	FLFPInventoryItem OldItemData = InventorySlot.GetSlotItemConst(InventoryInternalIndex);

	if (CanRemoveItemOnSlot(InventoryIndex, OldItemData, ProcessItemData) == false) return false;

	FLFPInventoryItem& NewItemData = InventorySlot.GetSlotItemRef(InventoryInternalIndex, true);

	const bool bSuccess = ProcessRemoveItem(NewItemData, ProcessItemData, InventoryIndex);

	InventorySlot.AddPendingEvent(FLFPInventoryItemOperationData(ELFPInventoryItemEvent::Inventory_Remove, InventoryIndex, NewItemData, OldItemData, EventTag));

	return bSuccess;
}

bool ULFPInventoryComponent::SwapItem_Internal(const FLFPInventoryInternalIndex& FromIndex, const FLFPInventoryInternalIndex& ToIndex, const FGameplayTag& EventTag)
{
	if (FromIndex == ToIndex) return false;

	if (FromIndex.IsValid() == false) return false;
	if (ToIndex.IsValid() == false) return false;

	const FLFPInventoryItem& CopyFromItem = InventorySlot.GetSlotItemConst(FromIndex);
	const FLFPInventoryItem& CopyToItem = InventorySlot.GetSlotItemConst(ToIndex);

	if (CanSwapItemOnSlot(CopyFromItem, FromIndex.ToInventoryIndex(), CopyToItem, ToIndex.ToInventoryIndex()) == false) return false;

	FLFPInventoryItem& FromData =	InventorySlot.GetSlotItemRef(FromIndex, true);
	FLFPInventoryItem& ToData =		InventorySlot.GetSlotItemRef(ToIndex, true);

	const bool bSuccess = ProcessSwapItem(FromData, FromIndex.ToInventoryIndex(), ToData, ToIndex.ToInventoryIndex());

	InventorySlot.AddPendingEvent(FLFPInventoryItemOperationData(ELFPInventoryItemEvent::Inventory_Swap, FromIndex.ToInventoryIndex(), FromData, CopyFromItem, EventTag));
	InventorySlot.AddPendingEvent(FLFPInventoryItemOperationData(ELFPInventoryItemEvent::Inventory_Swap, ToIndex.ToInventoryIndex(), ToData, CopyToItem, EventTag));

	return bSuccess;
}

bool ULFPInventoryComponent::MergeItem_Internal(const FLFPInventoryInternalIndex& FromIndex, const FLFPInventoryInternalIndex& ToIndex, const FGameplayTag& EventTag)
{
	if (FromIndex == ToIndex) return false;

	if (FromIndex.IsValid() == false) return false;
	if (ToIndex.IsValid() == false) return false;

	const FLFPInventoryItem& CopyFromItem = InventorySlot.GetSlotItemConst(FromIndex);
	const FLFPInventoryItem& CopyToItem = InventorySlot.GetSlotItemConst(ToIndex);

	if (CanMergeItemOnSlot(CopyFromItem, FromIndex.ToInventoryIndex(), CopyToItem, ToIndex.ToInventoryIndex()) == false) return false;

	FLFPInventoryItem& FromData = InventorySlot.GetSlotItemRef(FromIndex, true);
	FLFPInventoryItem& ToData = InventorySlot.GetSlotItemRef(ToIndex, true);

	const bool bSuccess = ProcessMergeItem(FromData, FromIndex.ToInventoryIndex(), ToData, ToIndex.ToInventoryIndex());

	InventorySlot.AddPendingEvent(FLFPInventoryItemOperationData(ELFPInventoryItemEvent::Inventory_Merge, FromIndex.ToInventoryIndex(), FromData, CopyFromItem, EventTag));
	InventorySlot.AddPendingEvent(FLFPInventoryItemOperationData(ELFPInventoryItemEvent::Inventory_Merge, ToIndex.ToInventoryIndex(), ToData, CopyToItem, EventTag));

	return bSuccess;
}

bool ULFPInventoryComponent::Transfer_Index_Internal(const FLFPInventoryIndex& FromIndex, const FLFPInventoryIndex& ToIndex, ULFPInventoryComponent* TargetInventoryComponent, const bool bMustFullyTransfer, const FGameplayTag EventTag)
{
	const FLFPInventoryInternalIndex FromInventoryInternalIndex((InventorySlot.ToInventoryIndexInternal(FromIndex)));

	if (FromInventoryInternalIndex.IsValid() == false) return false;

	if (InventorySlot.IsSlotItemValid(FromInventoryInternalIndex) == false) return false;

	FLFPInventoryItem& RefOfFrom = InventorySlot.GetSlotItemRef(FromInventoryInternalIndex, true);
	FLFPInventoryItem CopyOfFrom = RefOfFrom;

	if (CanTransferItemOnSlot(FromIndex, RefOfFrom) == false) return false;

	const bool bSuccess = TargetInventoryComponent->AddItemByIndex(ToIndex, RefOfFrom, bMustFullyTransfer, EventTag);

	InventorySlot.AddPendingEvent(FLFPInventoryItemOperationData(ELFPInventoryItemEvent::Inventory_Transfer, FromIndex, RefOfFrom, CopyOfFrom, EventTag));

	return bSuccess;
}

bool ULFPInventoryComponent::Transfer_SlotName_Internal(const FLFPInventoryIndex& FromIndex, const FGameplayTagContainer& ToSlotNameList, ULFPInventoryComponent* TargetInventoryComponent, const bool bMustFullyTransfer, const FGameplayTag EventTag)
{
	const FLFPInventoryInternalIndex FromInventoryInternalIndex((InventorySlot.ToInventoryIndexInternal(FromIndex)));

	if (FromInventoryInternalIndex.IsValid() == false) return false;

	if (InventorySlot.IsSlotItemValid(FromInventoryInternalIndex) == false) return false;

	FLFPInventoryItem& RefOfFrom = InventorySlot.GetSlotItemRef(FromInventoryInternalIndex, true);
	FLFPInventoryItem CopyOfFrom = RefOfFrom;

	if (CanTransferItemOnSlot(FromIndex, RefOfFrom) == false) return false;

	const bool bSuccess = TargetInventoryComponent->AddItemBySlotName(ToSlotNameList, RefOfFrom, bMustFullyTransfer, EventTag);

	InventorySlot.AddPendingEvent(FLFPInventoryItemOperationData(ELFPInventoryItemEvent::Inventory_Transfer, FromIndex, RefOfFrom, CopyOfFrom, EventTag));

	return bSuccess;
}

bool ULFPInventoryComponent::UpdateItem_Internal(const FLFPInventoryIndex& InventoryIndex, FLFPInventoryItem& ProcessItemData, const FGameplayTag& EventTag)
{
	const FLFPInventoryInternalIndex InventoryInternalIndex((InventorySlot.ToInventoryIndexInternal(InventoryIndex)));

	if (InventoryInternalIndex.IsValid() == false) return false;

	if (CanUpdateItemOnSlot(InventoryIndex, InventorySlot.GetSlotItemConst(InventoryInternalIndex), ProcessItemData) == false) return false;

	FLFPInventoryItem OldItemData = InventorySlot.GetSlotItemConst(InventoryInternalIndex);
	FLFPInventoryItem& NewItemData = InventorySlot.GetSlotItemRef(InventoryInternalIndex, true);

	const bool bSuccess = ProcessUpdateItem(NewItemData, ProcessItemData, InventoryIndex);

	InventorySlot.AddPendingEvent(FLFPInventoryItemOperationData(ELFPInventoryItemEvent::Inventory_Update, InventoryIndex, NewItemData, OldItemData, EventTag));

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


bool ULFPInventoryComponent::AddItem(UPARAM(ref) FLFPInventoryItem& ItemData, const bool bMustFullyAdd, const FGameplayTag EventTag)
{
	return AddItemBySlotName(GetItemAllowSlotNameList(ItemData), ItemData, bMustFullyAdd, EventTag);
}

bool ULFPInventoryComponent::AddItemList(UPARAM(ref) TArray<FLFPInventoryItem>& ItemDataList, const bool bMustFullyAdd, const FGameplayTag EventTag)
{
	FGameplayTagContainer SearchSlotNameList = FGameplayTagContainer();

	bool bIsSuccess = true;

	for (FLFPInventoryItem& ItemData : ItemDataList)
	{
		SearchSlotNameList.AppendTags(GetItemAllowSlotNameList(ItemData));
	}

	return AddItemListBySlotName(SearchSlotNameList, ItemDataList, bMustFullyAdd, EventTag);
}

bool ULFPInventoryComponent::AddItemBySlotName(const FGameplayTagContainer InventorySlotNameList, UPARAM(ref) FLFPInventoryItem& ItemData, const bool bMustFullyAdd, const FGameplayTag EventTag)
{
	TArray<FLFPInventoryItem> ItemDataList = { ItemData };

	const bool bIsSuccess = AddItemListBySlotName(InventorySlotNameList, ItemDataList, bMustFullyAdd, EventTag);

	if (ItemDataList.IsValidIndex(0))
	{
		ItemData = ItemDataList[0];
	}
	else
	{
		ItemData = FLFPInventoryItem();
	}

	return bIsSuccess;
}

bool ULFPInventoryComponent::AddItemListBySlotName(const FGameplayTagContainer InventorySlotNameList, UPARAM(ref)TArray<FLFPInventoryItem>& ItemDataList, const bool bMustFullyAdd, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	const bool bIsSuccess = ProcessItemOperation(
		InventorySlotNameList,
		ItemDataList,
		[&](const FLFPInventoryItem& ItemData)
		{
			return CanAddItem(ItemData);
		},
		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex, FLFPInventoryItem& ItemData)
		{
			return AddItem_Internal(InventoryIndex, ItemData, EventTag);
		},
		bMustFullyAdd,
		true
	);

	/* Apply Inventory Item Change */
	if (bIsSuccess || bMustFullyAdd == false)
	{
		InventorySlot.ApplyPendingChange([&](const FLFPInventoryItemOperationData& OperationData) { SendItemDelegateEvent(OperationData); });
	}
	else
	{
		InventorySlot.ClearPendingChange();
	}

	return bIsSuccess;
}

bool ULFPInventoryComponent::AddItemByIndex(const FLFPInventoryIndex& InventoryIndex, UPARAM(ref) FLFPInventoryItem& ItemData, const bool bMustFullyAdd, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (CanAddItem(ItemData) == false) return false;

	const bool bIsSuccess = AddItem_Internal(InventoryIndex, ItemData, EventTag);

	if (bIsSuccess || bMustFullyAdd == false)
	{
		InventorySlot.ApplyPendingChange([&](const FLFPInventoryItemOperationData& OperationData) { SendItemDelegateEvent(OperationData); });
	}
	else
	{
		InventorySlot.ClearPendingChange();
	}

	return bIsSuccess;
}


bool ULFPInventoryComponent::RemoveItem(UPARAM(ref) FLFPInventoryItem& ItemData, const bool bMustFullyRemove, const FGameplayTag EventTag)
{
	return RemoveItemBySlotName(GetItemAllowSlotNameList(ItemData), ItemData, bMustFullyRemove, EventTag);
}

bool ULFPInventoryComponent::RemoveItemList(UPARAM(ref)TArray<FLFPInventoryItem>& ItemDataList, const bool bMustFullyRemove, const FGameplayTag EventTag)
{
	FGameplayTagContainer SearchSlotNameList = FGameplayTagContainer();

	bool bIsSuccess = true;

	for (FLFPInventoryItem& ItemData : ItemDataList)
	{
		SearchSlotNameList.AppendTags(GetItemAllowSlotNameList(ItemData));
	}

	return RemoveItemListBySlotName(SearchSlotNameList, ItemDataList, bMustFullyRemove, EventTag);
}

bool ULFPInventoryComponent::RemoveItemBySlotName(const FGameplayTagContainer InventorySlotNameList, UPARAM(ref) FLFPInventoryItem& ItemData, const bool bMustFullyRemove, const FGameplayTag EventTag)
{
	TArray<FLFPInventoryItem> ItemDataList = { ItemData };

	const bool bIsSuccess = RemoveItemListBySlotName(InventorySlotNameList, ItemDataList, bMustFullyRemove, EventTag);

	if (ItemDataList.IsValidIndex(0))
	{
		ItemData = ItemDataList[0];
	}
	else
	{
		ItemData = FLFPInventoryItem();
	}

	return bIsSuccess;
}

bool ULFPInventoryComponent::RemoveItemListBySlotName(const FGameplayTagContainer InventorySlotNameList, UPARAM(ref)TArray<FLFPInventoryItem>& ItemDataList, const bool bMustFullyRemove, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	const bool bIsSuccess = ProcessItemOperation(
		InventorySlotNameList,
		ItemDataList,
		[&](const FLFPInventoryItem& ItemData)
		{
			return CanRemoveItem(ItemData);
		},
		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex, FLFPInventoryItem& ItemData)
		{
			return RemoveItem_Internal(InventoryIndex, ItemData, EventTag);
		},
		bMustFullyRemove,
		true
	);

	/* Apply Inventory Item Change */
	if (bIsSuccess || bMustFullyRemove == false)
	{
		InventorySlot.ApplyPendingChange([&](const FLFPInventoryItemOperationData& OperationData) { SendItemDelegateEvent(OperationData); });
	}
	else
	{
		InventorySlot.ClearPendingChange();
	}

	return bIsSuccess;
}

bool ULFPInventoryComponent::RemoveItemByIndex(const FLFPInventoryIndex& InventoryIndex, UPARAM(ref) FLFPInventoryItem& ItemData, const bool bMustFullyRemove, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (CanRemoveItem(ItemData) == false) return false;

	const bool bIsSuccess = RemoveItem_Internal(InventoryIndex, ItemData, EventTag);

	if (bIsSuccess || bMustFullyRemove == false)
	{
		InventorySlot.ApplyPendingChange([&](const FLFPInventoryItemOperationData& OperationData) { SendItemDelegateEvent(OperationData); });
	}
	else
	{
		InventorySlot.ClearPendingChange();
	}

	return bIsSuccess;
}


bool ULFPInventoryComponent::SwapItemByIndex(const FLFPInventoryIndex& FromIndex, const FLFPInventoryIndex& ToIndex, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	const FLFPInventoryInternalIndex FromIndexInternal = InventorySlot.ToInventoryIndexInternal(FromIndex);
	const FLFPInventoryInternalIndex ToIndexInternal = InventorySlot.ToInventoryIndexInternal(ToIndex);

	const bool bIsSuccess = SwapItem_Internal(FromIndexInternal, ToIndexInternal, EventTag);

	/* Apply Inventory Item Change */
	InventorySlot.ApplyPendingChange([&](const FLFPInventoryItemOperationData& OperationData) { SendItemDelegateEvent(OperationData); });

	return bIsSuccess;
}


bool ULFPInventoryComponent::MergeItemByIndex(const FLFPInventoryIndex& FromIndex, const FLFPInventoryIndex& ToIndex, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	const FLFPInventoryInternalIndex FromIndexInternal = InventorySlot.ToInventoryIndexInternal(FromIndex);
	const FLFPInventoryInternalIndex ToIndexInternal = InventorySlot.ToInventoryIndexInternal(ToIndex);

	const bool bIsSuccess = MergeItem_Internal(FromIndexInternal, ToIndexInternal, EventTag);

	/* Apply Inventory Item Change */
	InventorySlot.ApplyPendingChange([&](const FLFPInventoryItemOperationData& OperationData) { SendItemDelegateEvent(OperationData); });

	return bIsSuccess;
}

bool ULFPInventoryComponent::MergeItemBySlotName(const FLFPInventoryIndex& FromIndex, const FGameplayTagContainer ToSlotNameList, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	const FLFPInventoryInternalIndex FromIndexInternal = InventorySlot.ToInventoryIndexInternal(FromIndex);

	/* Use To Get Allow Slot Name List */
	TArray<FLFPInventoryItem> ItemDataList = { InventorySlot.GetSlotItemConst(FromIndexInternal) };

	const bool bIsSuccess = ProcessItemOperation(
		ToSlotNameList,
		ItemDataList,
		[&](const FLFPInventoryItem& ItemData)
		{
			return true;
		},
		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex, FLFPInventoryItem& ItemData)
		{
			return MergeItem_Internal(FromIndexInternal, InventoryInternalIndex, EventTag);
		},
		false,
		true
	);

	/* Apply Inventory Item Change */
	InventorySlot.ApplyPendingChange([&](const FLFPInventoryItemOperationData& OperationData) { SendItemDelegateEvent(OperationData); });

	return bIsSuccess;
}


bool ULFPInventoryComponent::TransferItemByIndex(const FLFPInventoryIndex& FromIndex, const FLFPInventoryIndex& ToIndex, ULFPInventoryComponent* TargetInventoryComponent, const bool bMustFullyTransfer, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	const bool bIsSuccess = Transfer_Index_Internal(FromIndex, ToIndex, TargetInventoryComponent, bMustFullyTransfer, EventTag);

	/* Apply Inventory Item Change */
	if (bIsSuccess || bMustFullyTransfer == false)
	{
		InventorySlot.ApplyPendingChange([&](const FLFPInventoryItemOperationData& OperationData) { SendItemDelegateEvent(OperationData); });
	}
	else
	{
		InventorySlot.ClearPendingChange();
	}

	return bIsSuccess;
}

bool ULFPInventoryComponent::TransferItemBySlotName(const FLFPInventoryIndex& FromIndex, const FGameplayTagContainer ToSlotNameList, ULFPInventoryComponent* TargetInventoryComponent, const bool bMustFullyTransfer, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	const bool bIsSuccess = Transfer_SlotName_Internal(FromIndex, ToSlotNameList, TargetInventoryComponent, bMustFullyTransfer, EventTag);

	/* Apply Inventory Item Change */
	if (bIsSuccess || bMustFullyTransfer == false)
	{
		InventorySlot.ApplyPendingChange([&](const FLFPInventoryItemOperationData& OperationData) { SendItemDelegateEvent(OperationData); });
	}
	else
	{
		InventorySlot.ClearPendingChange();
	}

	return bIsSuccess;
}

//bool ULFPInventoryComponent::ExchangeItemBySearch(const FLFPInventorySearch& TakeInventorySearch, UPARAM(ref)FLFPInventoryItem& TakeItemData, const FLFPInventorySearch& GiveInventorySearch, UPARAM(ref)FLFPInventoryItem& GiveItemData, const FGameplayTag EventTag)
//{
//	FLFPInventoryItem CheckItem = TakeItemData;
//
//	if (CanRemoveItemBySearch(TakeInventorySearch, CheckItem) == false)
//	{
//		return false;
//	}
//
//	if (RemoveItemBySearch(TakeInventorySearch, TakeItemData, EventTag))
//	{
//		return AddItemBySearch(GiveInventorySearch, GiveItemData, EventTag);
//	}
//	else
//	{
//		UE_LOG(LFPInventoryComponent, Error, TEXT("ExchangeItemBySearch Fail : RemoveItemBySearch Suppose To Be Success"));
//	}
//
//	return false;
//}
//
//bool ULFPInventoryComponent::ExchangeItemListBySearch(const FLFPInventorySearch& TakeInventorySearch, UPARAM(ref) TArray<FLFPInventoryItem>& TakeItemDataList, const FLFPInventorySearch& GiveInventorySearch, UPARAM(ref) TArray<FLFPInventoryItem>& GiveItemDataList, const FGameplayTag EventTag)
//{
//	TArray<FLFPInventoryItem> CheckItemList = TakeItemDataList;
//
//	if (CanRemoveItemListBySearch(TakeInventorySearch, CheckItemList) == false)
//	{
//		return false;
//	}
//
//	if (RemoveItemListBySearch(TakeInventorySearch, TakeItemDataList, EventTag))
//	{
//		return AddItemListBySearch(GiveInventorySearch, GiveItemDataList, EventTag);
//	}
//	else
//	{
//		UE_LOG(LFPInventoryComponent, Error, TEXT("ExchangeItemListBySearch Fail : RemoveItemListBySearch Suppose To Be Success"));
//	}
//
//	return false;
//}


bool ULFPInventoryComponent::UpdateItem(UPARAM(ref)FLFPInventoryItem& ItemData, const FGameplayTag EventTag)
{
	return UpdateItemBySlotName(GetItemAllowSlotNameList(ItemData), ItemData, EventTag);
}

bool ULFPInventoryComponent::UpdateItemBySlotName(const FGameplayTagContainer InventorySlotNameList, UPARAM(ref)FLFPInventoryItem& ItemData, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	TArray<FLFPInventoryItem> ItemDataList = { ItemData };

	const bool bIsSuccess = ProcessItemOperation(
		InventorySlotNameList,
		ItemDataList,
		[&](const FLFPInventoryItem& TargetItemData)
		{
			return CanUpdateItem(TargetItemData);
		},
		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex, FLFPInventoryItem& TargetItemData)
		{
			return UpdateItem_Internal(InventoryIndex, TargetItemData, EventTag);
		},
		true,
		true
	);

	if (ItemDataList.IsValidIndex(0))
	{
		ItemData = ItemDataList[0];
	}
	else
	{
		ItemData = FLFPInventoryItem();
	}

	/* Apply Inventory Item Change */
	if (bIsSuccess)
	{
		InventorySlot.ApplyPendingChange([&](const FLFPInventoryItemOperationData& OperationData) { SendItemDelegateEvent(OperationData); });
	}
	else
	{
		InventorySlot.ClearPendingChange();
	}

	return bIsSuccess;
}

bool ULFPInventoryComponent::UpdateItemByIndex(const FLFPInventoryIndex& InventoryIndex, UPARAM(ref)FLFPInventoryItem& ItemData, const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (CanUpdateItem(ItemData) == false) return false;

	const bool bIsSuccess = UpdateItem_Internal(InventoryIndex, ItemData, EventTag);

	if (bIsSuccess)
	{
		InventorySlot.ApplyPendingChange([&](const FLFPInventoryItemOperationData& OperationData) { SendItemDelegateEvent(OperationData); });
	}
	else
	{
		InventorySlot.ClearPendingChange();
	}

	return bIsSuccess;
}


bool ULFPInventoryComponent::SortItem(const FGameplayTagContainer InventorySlotNameList, UPARAM(meta = (Categories = "Item.Sort")) const FGameplayTag SortTag, UPARAM(meta = (Categories = "Item.Event")) const FGameplayTag EventTag)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	InventorySlot.SortSlot(
		InventorySlotNameList,
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
		SlotNames,
		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex)
		{
			if (InventorySlot.IsSlotItemValid(InventoryInternalIndex) == false)
			{
				return false;
			}

			InventorySlot.GetSlotItemRef(InventoryInternalIndex, false) = FLFPInventoryItem();

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

bool ULFPInventoryComponent::CanMergeItemOnSlot(const FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, const FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			const bool bSuccess = FunctionObj->CanMergeItemOnSlot(FromItem, FromIndex, ToItem, ToIndex);

			if (bSuccess == false)
			{
				UE_LOG(LFPInventoryComponent, Verbose, TEXT("CanMergeItemOnSlot Fail : FunctionObj = %s | FromIndex = %s | ToIndex = %s"), *FunctionObj->GetName(), *FromIndex.ToString(), *ToIndex.ToString());
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::CanTransferItemOnSlot(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& ItemData) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			const bool bSuccess = FunctionObj->CanTransferItemOnSlot(InventoryIndex, ItemData);

			if (bSuccess == false)
			{
				UE_LOG(LFPInventoryComponent, Verbose, TEXT("CanTransferItemOnSlot Fail : FunctionObj = %s | InventoryIndex = %s"), *FunctionObj->GetName(), *InventoryIndex.ToString());
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

bool ULFPInventoryComponent::ProcessMergeItem(UPARAM(ref)FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, UPARAM(ref)FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const
{
	return ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			const bool bSuccess = FunctionObj->ProcessMergeItem(FromItem, FromIndex, ToItem, ToIndex);

			if (bSuccess == false)
			{
				UE_LOG(LFPInventoryComponent, VeryVerbose, TEXT("ProcessMergeItem Fail : FunctionObj = %s | FromIndex = %s | ToIndex = %s"), *FunctionObj->GetName(), *FromIndex.ToString(), *ToIndex.ToString());
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

FGameplayTagContainer ULFPInventoryComponent::GetItemAllowSlotNameList(const FLFPInventoryItem& ItemData, const FGameplayTagContainer& FilterList) const
{
	FGameplayTagContainer Result = FGameplayTagContainer();

	ProcessInventoryFunction(
		[&](const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)
		{
			Result.AppendTags(FunctionObj->GetItemAllowSlotNameList(ItemData));

			return true;
		}
	);

	return FilterList.IsEmpty() ? Result : Result.Filter(FilterList);
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

//bool ULFPInventoryComponent::CanAddItemBySlotName(const FGameplayTagContainer InventorySlotNameList, UPARAM(ref)FLFPInventoryItem& ItemData) const
//{
//	if (CanAddItem(ItemData) == false) return false;
//
//	return ProcessInventoryIndex(
//		InventorySearch,
//		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex)
//		{
//			return AddItem_Internal_Check(InventoryIndex, ItemData);
//		},
//		true);
//}
//
//bool ULFPInventoryComponent::CanAddItemListBySlotName(const FGameplayTagContainer InventorySlotNameList, UPARAM(ref)TArray<FLFPInventoryItem>& ItemDataList) const
//{
//	bool bIsSuccess = true;
//
//	for (FLFPInventoryItem& ItemData : ItemDataList)
//	{
//		if (CanAddItemBySearch(InventorySearch, ItemData) == false)
//		{
//			bIsSuccess = false;
//		}
//	}
//
//	return bIsSuccess;
//}
//
//bool ULFPInventoryComponent::CanAddItemByIndex(const FLFPInventoryIndex& InventoryIndex, UPARAM(ref) FLFPInventoryItem& ItemData) const
//{
//	if (CanAddItem(ItemData) == false) return false;
//
//	return AddItem_Internal_Check(InventoryIndex, ItemData);
//}
//
//bool ULFPInventoryComponent::CanRemoveItemBySlotName(const FGameplayTagContainer InventorySlotNameList, UPARAM(ref)FLFPInventoryItem& ItemData) const
//{
//	if (CanRemoveItem(ItemData) == false) return false;
//
//	return ProcessInventoryIndex(
//		InventorySearch,
//		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex)
//		{
//			return RemoveItem_Internal_Check(InventoryIndex, ItemData);
//		},
//		true);
//}
//
//bool ULFPInventoryComponent::CanRemoveItemListBySlotName(const FGameplayTagContainer InventorySlotNameList, UPARAM(ref)TArray<FLFPInventoryItem>& ItemDataList) const
//{
//	bool bIsSuccess = true;
//
//	for (FLFPInventoryItem& ItemData : ItemDataList)
//	{
//		if (CanRemoveItemBySearch(InventorySearch, ItemData) == false)
//		{
//			bIsSuccess = false;
//		}
//	}
//
//	return bIsSuccess;
//}
//
//bool ULFPInventoryComponent::CanRemoveItemByIndex(const FLFPInventoryIndex& InventoryIndex, UPARAM(ref) FLFPInventoryItem& ItemData) const
//{
//	if (CanRemoveItem(ItemData) == false) return false;
//
//	return RemoveItem_Internal_Check(InventoryIndex, ItemData);
//}


bool ULFPInventoryComponent::ContainItem(FLFPInventoryItem ItemData, const FGameplayTagContainer InventorySlotNameList) const
{
	if (CanContainItem(ItemData) == false) return false;

	return ProcessInventoryIndex(
		InventorySlotNameList,
		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex)
		{
			return ContainItem_Internal(InventoryIndex, InventoryInternalIndex, ItemData);
		});
}

bool ULFPInventoryComponent::ContainItemList(const TArray<FLFPInventoryItem>& ItemDataList, const FGameplayTagContainer InventorySlotNameList, const bool bPartially) const
{
	for (const auto& ItemData : ItemDataList)
	{
		const bool bIsSearchComplete = ContainItem(ItemData, InventorySlotNameList);

		if (bPartially)
		{
			if (bIsSearchComplete) return true;
		}
		else if (bIsSearchComplete == false)
		{
			return false;
		}
	}

	return true;
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



const FLFPInventoryItem& ULFPInventoryComponent::GetSlotItem(const FLFPInventoryIndex& InventoryIndex) const
{
	const FLFPInventoryInternalIndex InventoryInternalIndex((InventorySlot.ToInventoryIndexInternal(InventoryIndex)));

	if (InventoryInternalIndex.IsValid() == false) return FLFPInventoryItem::EmptyItem;

	return InventorySlot.GetSlotItemConst(InventoryInternalIndex);
}



bool ULFPInventoryComponent::FindInventoryIndexList(TArray<FLFPInventoryIndex>& InventoryIndexList, FLFPInventoryItem ItemData, const FGameplayTagContainer InventorySlotNameList, const int32 MaxListItem) const
{
	int32 CurrentAmount = 0;

	TArray<FLFPInventoryItem> ItemDataList = { ItemData };

	const bool bIsSuccess = ProcessItemOperation(
		InventorySlotNameList,
		ItemDataList,
		[&](const FLFPInventoryItem& TargetItemData)
		{
			return CanContainItem(ItemData);
		},
		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex, FLFPInventoryItem& TargetItemData)
		{
			if (FindItem_Internal(InventoryIndex, InventoryInternalIndex, TargetItemData))
			{
				InventoryIndexList.Add(InventoryIndex);

				CurrentAmount += 1;
			}

			return ItemData.IsValid() == false || (MaxListItem > 0 ? MaxListItem <= CurrentAmount : false);
		},
		false,
		true
	);

	return CurrentAmount > 0;
}

bool ULFPInventoryComponent::FindItemDataList(TArray<FLFPInventoryItem>& ItemIndexList, FLFPInventoryItem ItemData, const FGameplayTagContainer InventorySlotNameList, const int32 MaxListItem) const
{
	/* Find Use Same Logic As Contain Item */
	if (CanContainItem(ItemData) == false) return false;

	int32 CurrentAmount = 0;

	ProcessInventoryIndex(
		InventorySlotNameList,
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
