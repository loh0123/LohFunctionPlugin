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
	}
}

int32 ULFPInventoryComponent::AddItem(const FLFPInventoryItemData& ItemData, int32 SlotIndex, const FString EventInfo)
{
	if ((SlotIndex = GetAvailableInventorySlot(SlotIndex, ItemData)) == INDEX_NONE)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : AddItem GetAvailableInventorySlot return false"));

		return INDEX_NONE;
	}

	if (ItemData.ItemTag == FGameplayTag::EmptyTag)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : AddItem ItemData Tag is empty"));

		return INDEX_NONE;
	}

	if (CanAddItem(ItemData, SlotIndex, EventInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : AddItem CanAddItem return false"));

		return INDEX_NONE;
	}

	if (InventorySlotList.Num() <= SlotIndex) InventorySlotList.SetNum(SlotIndex + 1);

	InventorySlotList[SlotIndex] = ItemData;

	OnAddItem.Broadcast(ItemData, SlotIndex, EventInfo);

	return SlotIndex;
}

bool ULFPInventoryComponent::RemoveItem(FLFPInventoryItemData& RemovedItemData, const int32 SlotIndex, const FString EventInfo)
{
	if (IsInventorySlotIndexValid(SlotIndex) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : RemoveItem IsInventorySlotIndexValid return false"));

		return false;
	}

	if (GetInventorySlot(SlotIndex).ItemTag == FGameplayTag::EmptyTag)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : RemoveItem ItemData Tag is empty"));

		return false;
	}

	if (IsInventorySlotIndexLock(SlotIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : RemoveItem Item is lock"));

		return false;
	}

	if (CanRemoveItem(InventorySlotList[SlotIndex], SlotIndex, EventInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : RemoveItem CanRemoveItem return false"));

		return false;
	}

	RemovedItemData = InventorySlotList[SlotIndex];

	InventorySlotList[SlotIndex] = FLFPInventoryItemData();

	TrimInventorySlotList(SlotIndex);

	OnRemoveItem.Broadcast(RemovedItemData, SlotIndex, EventInfo);

	return true;
}

bool ULFPInventoryComponent::SwapItem(const int32 FromSlot, const int32 ToSlot, const FString EventInfo)
{
	int32 MinIndex = FMath::Min(FromSlot, ToSlot);
	int32 MaxIndex = FMath::Max(FromSlot, ToSlot);

	/* Check Slot is lock */
	if (IsInventorySlotIndexLock(FromSlot) || IsInventorySlotIndexLock(ToSlot)) return false;

	if (FromSlot == ToSlot || MinIndex < 0 || MaxIndex >= MaxInventorySlotAmount || CanSwapItem(FromSlot, ToSlot, EventInfo) == false) return false;

	if (InventorySlotList.Num() <= MaxIndex) InventorySlotList.SetNum(MaxIndex + 1);

	InventorySlotList.Swap(MinIndex, MaxIndex);

	OnSwapItem.Broadcast(InventorySlotList[ToSlot], FromSlot, InventorySlotList[FromSlot], ToSlot, EventInfo);

	TrimInventorySlotList(FMath::Max(FromSlot, ToSlot));

	return true;
}

bool ULFPInventoryComponent::SwapItemFromOther(ULFPInventoryComponent* Other, const int32 FromSlot, const int32 ToSlot, const FString EventInfo)
{
	if (
		Other->IsInventorySlotIndexLock(FromSlot) ||
		Other->CanRemoveItem(Other->GetInventorySlot(FromSlot), FromSlot, EventInfo) == false ||
		Other->CanAddItem(GetInventorySlot(ToSlot), FromSlot, EventInfo) == false ||
		IsInventorySlotIndexLock(ToSlot) ||
		CanRemoveItem(GetInventorySlot(ToSlot), ToSlot, EventInfo) == false ||
		CanAddItem(Other->GetInventorySlot(FromSlot), ToSlot, EventInfo) == false
		)
		return false;

	FLFPInventoryItemData FromData = FLFPInventoryItemData();
	FLFPInventoryItemData ToData = FLFPInventoryItemData();

	Other->RemoveItem(FromData, FromSlot, EventInfo);
	RemoveItem(ToData, ToSlot, EventInfo);

	Other->AddItem(ToData, FromSlot, EventInfo);
	AddItem(FromData, ToSlot, EventInfo);

	return true;
}

void ULFPInventoryComponent::SortInventory(const FString EventInfo)
{
	if (InventorySlotList.IsValidIndex(StartInventorySlotIndex) == false) return;

	Sort(InventorySlotList.GetData() + StartInventorySlotIndex, InventorySlotList.Num() - StartInventorySlotIndex, [&](const FLFPInventoryItemData& ItemDataA, const FLFPInventoryItemData& ItemDataB)
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

bool ULFPInventoryComponent::AddItemLock(const int32 SlotIndex, const FName LockName)
{
	if (IsInventorySlotIndexValid(SlotIndex) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : AddItemLock IsInventorySlotIndexValid return false"));

		return false;
	}

	InventorySlotList[SlotIndex].LockList.AddUnique(LockName);

	return true;
}

bool ULFPInventoryComponent::RemoveItemLock(const int32 SlotIndex, const FName LockName)
{
	if (IsInventorySlotIndexValid(SlotIndex) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : RemoveItemLock IsInventorySlotIndexValid return false"));

		return false;
	}

	InventorySlotList[SlotIndex].LockList.RemoveSingleSwap(LockName);

	return true;
}

int32 ULFPInventoryComponent::GetAvailableInventorySlot(int32 SlotIndex, const FLFPInventoryItemData& ForItem, int32 EndIndex) const
{
	if (EndIndex == INDEX_NONE) EndIndex = MaxInventorySlotAmount - 1;

	if (EndIndex >= MaxInventorySlotAmount || SlotIndex >= MaxInventorySlotAmount) return INDEX_NONE;

	if (SlotIndex < 0) SlotIndex = StartInventorySlotIndex;

	for (SlotIndex; SlotIndex <= EndIndex; SlotIndex++)
	{
		if (InventorySlotList.Num() <= SlotIndex) return SlotIndex;

		if (IsInventorySlotIndexLock(SlotIndex) == false && IsInventorySlotAvailable(SlotIndex, InventorySlotList[SlotIndex], ForItem)) return SlotIndex;
	}

	return INDEX_NONE;
}

bool ULFPInventoryComponent::GetItemListWithItemTag(TArray<int32>& ItemIndexList, const FGameplayTag ItemTag, const int32 StartIndex, int32 EndIndex) const
{
	if (EndIndex == INDEX_NONE) EndIndex = InventorySlotList.Num() - 1;

	if (StartIndex < 0 || EndIndex >= InventorySlotList.Num()) return false;

	for (int32 SlotIndex = StartIndex; SlotIndex <= EndIndex; SlotIndex++)
	{
		if (InventorySlotList[SlotIndex].ItemTag.MatchesTag(ItemTag))
		{
			ItemIndexList.Add(SlotIndex);
		}
	}

	return ItemIndexList.IsEmpty() == false;
}
