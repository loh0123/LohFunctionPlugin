// Copyright by Loh Zhi Kang


#include "Inventory/LFPInventoryComponent.h"

// Sets default values for this component's properties
ULFPInventoryComponent::ULFPInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULFPInventoryComponent::BeginPlay()
{
	Super::BeginPlay();


	EquipmentSlotList.SetNum(MaxEquipmentSlotAmount);
	// ...
	
}


// Called every frame
void ULFPInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool ULFPInventoryComponent::AddItem(const FLFPInventoryItemData& ItemData, int32 SlotIndex, const FString EventInfo)
{
	if (SlotIndex == INDEX_NONE && GetEmptyInventorySlot(SlotIndex) == false) return false;

	if (SlotIndex >= MaxInventorySlotAmount || ItemData.ItemID == NAME_None || GetInventorySlot(SlotIndex).ItemID != NAME_None || CanAddItem(ItemData, SlotIndex, EventInfo) == false) return false;

	if (InventorySlotList.Num() <= SlotIndex) InventorySlotList.SetNum(SlotIndex + 1);

	InventorySlotList[SlotIndex] = ItemData;

	OnAddItem.Broadcast(ItemData, SlotIndex, EventInfo);

	return true;
}

bool ULFPInventoryComponent::RemoveItem(FLFPInventoryItemData& RemovedItemData, const int32 SlotIndex, const bool bIsEquipItem, const FString EventInfo)
{
	if (bIsEquipItem ? IsEquipmentSlotIndexValid(SlotIndex) == false : IsInventorySlotIndexValid(SlotIndex) == false) return false;

	if (bIsEquipItem)
	{
		RemovedItemData = EquipmentSlotList[SlotIndex];

		/* Check if this equipment is sync with inventory item */
		if (RemovedItemData.SyncSlotIndex != INDEX_NONE)
		{
			check(InventorySlotList.IsValidIndex(RemovedItemData.SyncSlotIndex));

			RemovedItemData = InventorySlotList[RemovedItemData.SyncSlotIndex];

			check(RemovedItemData.ItemID != NAME_None);
		}
	}
	else
	{
		RemovedItemData = InventorySlotList[SlotIndex];
	}

	if (RemovedItemData.ItemID == NAME_None || CanRemoveItem(bIsEquipItem ? EquipmentSlotList[SlotIndex] : InventorySlotList[SlotIndex], SlotIndex, EventInfo) == false) return false;

	if (bIsEquipItem)
	{
		/* Check if this equipment is sync with inventory item */
		if (EquipmentSlotList[SlotIndex].SyncSlotIndex != INDEX_NONE) 
		{ 
			InventorySlotList[EquipmentSlotList[SlotIndex].SyncSlotIndex] = FLFPInventoryItemData(); 

			TrimInventorySlotList(EquipmentSlotList[SlotIndex].SyncSlotIndex);
		}

		EquipmentSlotList[SlotIndex] = FLFPInventoryItemData();
	}
	else
	{
		if (InventorySlotList[SlotIndex].SyncSlotIndex != INDEX_NONE) EquipmentSlotList[InventorySlotList[SlotIndex].SyncSlotIndex] = FLFPInventoryItemData();

		InventorySlotList[SlotIndex] = FLFPInventoryItemData();

		TrimInventorySlotList(SlotIndex);
	}

	OnRemoveItem.Broadcast(RemovedItemData, SlotIndex, EventInfo);

	return true;
}

bool ULFPInventoryComponent::EquipItem(const int32 InventorySlotIndex, const int32 EquipmentSlotIndex, const bool bSyncSlot, const FString EventInfo)
{
	if (IsInventorySlotIndexValid(InventorySlotIndex) == false || 
		IsEquipmentSlotIndexValid(EquipmentSlotIndex) == false ||
		InventorySlotList[InventorySlotIndex].ItemID == NAME_None ||
		CanEquipItem(InventorySlotList[InventorySlotIndex], InventorySlotIndex, EquipmentSlotIndex, bSyncSlot, EventInfo) == false
		) 
		return false;

	if (InventorySlotList[InventorySlotIndex].SyncSlotIndex != INDEX_NONE)
	{
		if (UnequipItem(InventorySlotList[InventorySlotIndex].SyncSlotIndex, INDEX_NONE, EventInfo) == false) return false;
	}

	if (EquipmentSlotList[EquipmentSlotIndex].ItemID != NAME_None || EquipmentSlotList[EquipmentSlotIndex].SyncSlotIndex != INDEX_NONE)
	{
		if (UnequipItem(EquipmentSlotIndex, INDEX_NONE, EventInfo) == false) return false;
	}

	if (bSyncSlot)
	{
		EquipmentSlotList[EquipmentSlotIndex].SyncSlotIndex = InventorySlotIndex;

		InventorySlotList[InventorySlotIndex].SyncSlotIndex = EquipmentSlotIndex;
	}
	else
	{
		EquipmentSlotList[EquipmentSlotIndex] = InventorySlotList[InventorySlotIndex];

		InventorySlotList[InventorySlotIndex] = FLFPInventoryItemData();

		TrimInventorySlotList(InventorySlotIndex);
	}

	OnEquipItem.Broadcast(bSyncSlot ? InventorySlotList[InventorySlotIndex] : EquipmentSlotList[EquipmentSlotIndex], EquipmentSlotIndex, EventInfo);

	return true;
}

bool ULFPInventoryComponent::UnequipItem(const int32 EquipmentSlotIndex, const int32 ToInventorySlotIndex, const FString EventInfo)
{
	if (IsEquipmentSlotIndexValid(EquipmentSlotIndex) == false ||
		(EquipmentSlotList[EquipmentSlotIndex].ItemID != NAME_None || EquipmentSlotList[EquipmentSlotIndex].SyncSlotIndex != INDEX_NONE) == false ||
		CanUnequipItem(
			EquipmentSlotList[EquipmentSlotIndex].SyncSlotIndex != INDEX_NONE ? InventorySlotList[EquipmentSlotList[EquipmentSlotIndex].SyncSlotIndex] : EquipmentSlotList[EquipmentSlotIndex], 
			EquipmentSlotIndex,
			EventInfo
		) == false
		)
		return false;

	FLFPInventoryItemData EquipmentData;

	if (EquipmentSlotList[EquipmentSlotIndex].SyncSlotIndex != INDEX_NONE)
	{
		EquipmentData = InventorySlotList[EquipmentSlotList[EquipmentSlotIndex].SyncSlotIndex];

		InventorySlotList[EquipmentSlotList[EquipmentSlotIndex].SyncSlotIndex].SyncSlotIndex = INDEX_NONE;

		EquipmentSlotList[EquipmentSlotIndex].SyncSlotIndex = INDEX_NONE;
	}
	else
	{
		if (AddItem(EquipmentSlotList[EquipmentSlotIndex], ToInventorySlotIndex, EventInfo) == false) return false;

		EquipmentData = EquipmentSlotList[EquipmentSlotIndex];

		EquipmentSlotList[EquipmentSlotIndex] = FLFPInventoryItemData();
	}

	OnUnequipItem.Broadcast(EquipmentData, EquipmentSlotIndex, EventInfo);

	return true;
}

bool ULFPInventoryComponent::SwapItem(const int32 FromSlot, const int32 ToSlot, const FString EventInfo)
{
	if (FromSlot == ToSlot || CanSwapItem(FromSlot, ToSlot, EventInfo) == false) return false;

	int32 MinIndex = FMath::Min(FromSlot, ToSlot);
	int32 MaxIndex = FMath::Max(FromSlot, ToSlot);

	if (InventorySlotList.Num() <= MaxIndex) InventorySlotList.SetNum(MaxIndex + 1);

	InventorySlotList.Swap(MinIndex, MaxIndex);

	OnSwapItem.Broadcast(InventorySlotList[ToSlot], FromSlot, InventorySlotList[FromSlot], ToSlot, EventInfo);

	TrimInventorySlotList(FMath::Max(FromSlot, ToSlot));

	return true;
}

void ULFPInventoryComponent::SortInventory(const FString EventInfo)
{
	InventorySlotList.Sort([&](const FLFPInventoryItemData& ItemDataA, const FLFPInventoryItemData& ItemDataB)
		{
			return InventorySortFunction(ItemDataA, ItemDataB, EventInfo);
		});

	TrimInventorySlotList(InventorySlotList.Num() - 1);

	OnItemSortEvent.Broadcast();
}

void ULFPInventoryComponent::TrimInventorySlotList(const int32 FromSlot)
{
	if (IsInventorySlotIndexValid(FromSlot) == false || IsInventorySlotIndexValid(FromSlot + 1))
	{
		return;
	}

	while (InventorySlotList.Num() > 0 && InventorySlotList[InventorySlotList.Num() - 1].ItemID == NAME_None)
	{
		InventorySlotList.RemoveAt(InventorySlotList.Num() - 1, 1, false);
	}

	InventorySlotList.Shrink();
}

bool ULFPInventoryComponent::GetEmptyInventorySlot(int32& SlotIndex) const
{
	if (InventorySlotList.Num() > 0) 
		for (SlotIndex = 0; SlotIndex < InventorySlotList.Num(); SlotIndex++)
		{
			if (InventorySlotList[SlotIndex].ItemID == NAME_None)
			{
				return true;
			}
		}

	SlotIndex = SlotIndex + 1 < MaxInventorySlotAmount ? SlotIndex + 1 : INDEX_NONE;

	return SlotIndex != INDEX_NONE;
}

bool ULFPInventoryComponent::GetItemListWithID(TArray<int32>& ItemIndexList, const FName ID, const bool bEquipment) const
{
	const TArray<FLFPInventoryItemData>& CurrentList = bEquipment ? EquipmentSlotList : InventorySlotList;

	for (int32 Index = 0; Index < CurrentList.Num(); Index++)
	{
		if (CurrentList[Index].ItemID == ID)
		{
			ItemIndexList.Add(Index);
		}
	}

	return ItemIndexList.IsEmpty() == false;
}
