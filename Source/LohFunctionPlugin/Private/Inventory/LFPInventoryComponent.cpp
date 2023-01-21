// Copyright by Loh Zhi Kang


#include "Inventory/LFPInventoryComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
ULFPInventoryComponent::ULFPInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void ULFPInventoryComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ULFPInventoryComponent, EquipmentSlotList, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULFPInventoryComponent, InventorySlotList, COND_None, REPNOTIFY_Always);
}


// Called when the game starts
void ULFPInventoryComponent::BeginPlay()
{
	Super::BeginPlay();


	// EquipmentSlotList.SetNum(MaxEquipmentSlotAmount);
	// ...
	
}


// Called every frame
void ULFPInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULFPInventoryComponent::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsLoading())
	{
		int32 Index = 0;

		for (const FLFPInventoryItemData& Item : InventorySlotList)
		{
			if (Item.ItemTag != FGameplayTag::EmptyTag)
			{
				OnAddItem.Broadcast(Item, Index, FString("Serialize"));
			}

			Index++;
		}

		Index = 0;

		for (const FLFPInventoryItemData& Equipment : EquipmentSlotList)
		{
			if (Equipment.ItemTag != FGameplayTag::EmptyTag || Equipment.SyncSlotIndex != INDEX_NONE)
			{
				OnEquipItem.Broadcast(Equipment.SyncSlotIndex != INDEX_NONE ? InventorySlotList[Equipment.SyncSlotIndex] : Equipment, Index, FString("Serialize"));
			}

			Index++;
		}
	}
}

int32 ULFPInventoryComponent::AddItem(const FLFPInventoryItemData& ItemData, int32 SlotIndex, const FString EventInfo)
{
	if (SlotIndex == INDEX_NONE && GetAvailableInventorySlot(SlotIndex, ItemData) == false) return INDEX_NONE;

	if (SlotIndex >= MaxInventorySlotAmount || ItemData.ItemTag == FGameplayTag::EmptyTag || CanAddItem(ItemData, SlotIndex, EventInfo) == false) return INDEX_NONE;

	if (InventorySlotList.Num() <= SlotIndex) InventorySlotList.SetNum(SlotIndex + 1);

	InventorySlotList[SlotIndex] = ItemData;

	OnAddItem.Broadcast(ItemData, SlotIndex, EventInfo);

	return SlotIndex;
}

bool ULFPInventoryComponent::RemoveItem(FLFPInventoryItemData& RemovedItemData, int32 SlotIndex, const bool bIsEquipItem, const FString EventInfo)
{
	/* Check is SlotIndex valid */
	if (bIsEquipItem ? IsEquipmentSlotIndexValid(SlotIndex) == false : IsInventorySlotIndexValid(SlotIndex) == false) return false;

	/* Check is Slot not empty */
	if (bIsEquipItem ? GetEquipmentSlot(SlotIndex).ItemTag == FGameplayTag::EmptyTag : GetInventorySlot(SlotIndex).ItemTag == FGameplayTag::EmptyTag) return false;

	/* Check Item can be remove */
	if (CanRemoveItem(bIsEquipItem ? EquipmentSlotList[SlotIndex] : InventorySlotList[SlotIndex], SlotIndex, bIsEquipItem, EventInfo) == false) return false;

	/* Check is Item equip and Unequip it */
	if (bIsEquipItem || InventorySlotList[SlotIndex].SyncSlotIndex != INDEX_NONE) SlotIndex = UnequipItem(bIsEquipItem ? SlotIndex : InventorySlotList[SlotIndex].SyncSlotIndex, INDEX_NONE, EventInfo);

	if (SlotIndex == INDEX_NONE) return false;

	RemovedItemData = InventorySlotList[SlotIndex];

	InventorySlotList[SlotIndex] = FLFPInventoryItemData();

	TrimInventorySlotList(SlotIndex);

	OnRemoveItem.Broadcast(RemovedItemData, SlotIndex, EventInfo);

	return true;
}

bool ULFPInventoryComponent::EquipItem(const int32 InventorySlotIndex, const int32 EquipmentSlotIndex, const bool bSyncSlot, const FString EventInfo)
{
	if (IsInventorySlotIndexValid(InventorySlotIndex) == false || 
		MaxEquipmentSlotAmount <= EquipmentSlotIndex ||
		InventorySlotList[InventorySlotIndex].ItemTag == FGameplayTag::EmptyTag ||
		CanEquipItem(InventorySlotList[InventorySlotIndex], InventorySlotIndex, EquipmentSlotIndex, bSyncSlot, EventInfo) == false
		) 
		return false;

	if (IsEquipmentSlotIndexValid(EquipmentSlotIndex) && InventorySlotList[InventorySlotIndex].SyncSlotIndex != INDEX_NONE)
	{
		if (UnequipItem(InventorySlotList[InventorySlotIndex].SyncSlotIndex, INDEX_NONE, EventInfo) == false) return false;
	}

	if (IsEquipmentSlotIndexValid(EquipmentSlotIndex) && (EquipmentSlotList[EquipmentSlotIndex].ItemTag != FGameplayTag::EmptyTag || EquipmentSlotList[EquipmentSlotIndex].SyncSlotIndex != INDEX_NONE))
	{
		if (UnequipItem(EquipmentSlotIndex, INDEX_NONE, EventInfo) == false) return false;
	}

	if (EquipmentSlotList.Num() < EquipmentSlotIndex + 1) EquipmentSlotList.SetNum(EquipmentSlotIndex + 1);

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

int32 ULFPInventoryComponent::UnequipItem(const int32 EquipmentSlotIndex, int32 ToInventorySlotIndex, const FString EventInfo)
{
	int32 OutItemIndex = INDEX_NONE;

	if (IsEquipmentSlotIndexValid(EquipmentSlotIndex) == false ||
		(EquipmentSlotList[EquipmentSlotIndex].ItemTag != FGameplayTag::EmptyTag || EquipmentSlotList[EquipmentSlotIndex].SyncSlotIndex != INDEX_NONE) == false ||
		CanUnequipItem(
			EquipmentSlotList[EquipmentSlotIndex].SyncSlotIndex != INDEX_NONE ? InventorySlotList[EquipmentSlotList[EquipmentSlotIndex].SyncSlotIndex] : EquipmentSlotList[EquipmentSlotIndex], 
			EquipmentSlotIndex,
			EventInfo
		) == false
		)
		return OutItemIndex;

	FLFPInventoryItemData EquipmentData;

	if (EquipmentSlotList[EquipmentSlotIndex].SyncSlotIndex != INDEX_NONE)
	{
		OutItemIndex = EquipmentSlotList[EquipmentSlotIndex].SyncSlotIndex;

		EquipmentData = InventorySlotList[EquipmentSlotList[EquipmentSlotIndex].SyncSlotIndex];

		InventorySlotList[EquipmentSlotList[EquipmentSlotIndex].SyncSlotIndex].SyncSlotIndex = INDEX_NONE;

		EquipmentSlotList[EquipmentSlotIndex].SyncSlotIndex = INDEX_NONE;
	}
	else
	{
		OutItemIndex = AddItem(EquipmentSlotList[EquipmentSlotIndex], ToInventorySlotIndex, EventInfo);

		if (OutItemIndex == INDEX_NONE) return OutItemIndex;

		EquipmentData = EquipmentSlotList[EquipmentSlotIndex];

		EquipmentSlotList[EquipmentSlotIndex] = FLFPInventoryItemData();
	}

	OnUnequipItem.Broadcast(EquipmentData, EquipmentSlotIndex, EventInfo);

	return OutItemIndex;
}

bool ULFPInventoryComponent::SwapItem(const int32 FromSlot, const int32 ToSlot, const FString EventInfo)
{
	int32 MinIndex = FMath::Min(FromSlot, ToSlot);
	int32 MaxIndex = FMath::Max(FromSlot, ToSlot);

	if (FromSlot == ToSlot || MinIndex < 0 || MaxIndex >= MaxInventorySlotAmount || CanSwapItem(FromSlot, ToSlot, EventInfo) == false) return false;

	if (InventorySlotList.Num() <= MaxIndex) InventorySlotList.SetNum(MaxIndex + 1);

	InventorySlotList.Swap(MinIndex, MaxIndex);

	if (InventorySlotList[FromSlot].SyncSlotIndex != INDEX_NONE) EquipmentSlotList[InventorySlotList[FromSlot].SyncSlotIndex].SyncSlotIndex = FromSlot;
	if (InventorySlotList[ToSlot].SyncSlotIndex != INDEX_NONE) EquipmentSlotList[InventorySlotList[ToSlot].SyncSlotIndex].SyncSlotIndex = ToSlot;

	OnSwapItem.Broadcast(InventorySlotList[ToSlot], FromSlot, InventorySlotList[FromSlot], ToSlot, EventInfo);

	TrimInventorySlotList(FMath::Max(FromSlot, ToSlot));

	return true;
}

bool ULFPInventoryComponent::SwapItemFromOther(ULFPInventoryComponent* Other, const int32 FromSlot, const int32 ToSlot, const FString EventInfo)
{
	if (
		Other->CanRemoveItem(Other->GetInventorySlot(FromSlot), FromSlot, false, EventInfo) == false ||
		Other->CanAddItem(GetInventorySlot(ToSlot), FromSlot, EventInfo) == false ||
		CanRemoveItem(GetInventorySlot(ToSlot), ToSlot, false, EventInfo) == false ||
		CanAddItem(Other->GetInventorySlot(FromSlot), ToSlot, EventInfo) == false
		)
		return false;

	FLFPInventoryItemData FromData = FLFPInventoryItemData();
	FLFPInventoryItemData ToData = FLFPInventoryItemData();

	Other->RemoveItem(FromData, FromSlot, false, EventInfo);
	RemoveItem(ToData, ToSlot, false, EventInfo);

	Other->AddItem(ToData, FromSlot, EventInfo);
	AddItem(FromData, ToSlot, EventInfo);

	return true;
}

void ULFPInventoryComponent::SortInventory(const FString EventInfo)
{
	InventorySlotList.Sort([&](const FLFPInventoryItemData& ItemDataA, const FLFPInventoryItemData& ItemDataB)
		{
			return IsItemSortPriorityHigher(ItemDataA, ItemDataB, EventInfo);
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

	while (InventorySlotList.Num() > 0 && InventorySlotList[InventorySlotList.Num() - 1].ItemTag == FGameplayTag::EmptyTag)
	{
		InventorySlotList.RemoveAt(InventorySlotList.Num() - 1, 1, false);
	}

	InventorySlotList.Shrink();
}

bool ULFPInventoryComponent::GetAvailableInventorySlot(int32& SlotIndex, const FLFPInventoryItemData& ForItem, const int32 StartIndex, int32 EndIndex) const
{
	if (EndIndex == INDEX_NONE) EndIndex = InventorySlotList.Num() - 1;

	if (StartIndex < 0 || EndIndex >= InventorySlotList.Num()) return false;

	if (InventorySlotList.Num() > 0) 
		for (SlotIndex = StartIndex; SlotIndex <= EndIndex; SlotIndex++)
		{
			if (IsInventorySlotAvailable(SlotIndex, InventorySlotList[SlotIndex], ForItem))
			{
				return true;
			}
		}
	else
		SlotIndex = INDEX_NONE;

	SlotIndex = SlotIndex + 1 < MaxInventorySlotAmount ? SlotIndex + 1 : INDEX_NONE;

	return SlotIndex != INDEX_NONE;
}

bool ULFPInventoryComponent::GetItemListWithItemTag(TArray<int32>& ItemIndexList, const FGameplayTag ItemTag, const bool bEquipment, const int32 StartIndex, int32 EndIndex) const
{
	if (EndIndex == INDEX_NONE) EndIndex = InventorySlotList.Num() - 1;

	if (StartIndex < 0 || EndIndex >= InventorySlotList.Num()) return false;

	const TArray<FLFPInventoryItemData>& CurrentList = bEquipment ? EquipmentSlotList : InventorySlotList;

	for (int32 SlotIndex = StartIndex; SlotIndex <= EndIndex; SlotIndex++)
	{
		if (CurrentList[SlotIndex].ItemTag.MatchesTag(ItemTag))
		{
			ItemIndexList.Add(SlotIndex);
		}
	}

	return ItemIndexList.IsEmpty() == false;
}
