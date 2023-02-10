// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#include "Item/LFPInventoryComponent.h"
#include "Item/LFPInventoryInterface.h"
#include "Net/UnrealNetwork.h"


const FLFPInventoryItemData FLFPInventoryItemData::EmptyInventoryItemData = FLFPInventoryItemData();


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

int32 ULFPInventoryComponent::AddItem(FLFPInventoryItemData ItemData, int32 SlotIndex, const FString EventInfo)
{
	do
	{
		if (ItemData.ItemTag == FGameplayTag::EmptyTag)
		{
			UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : AddItem ItemData Tag is empty"));

			return INDEX_NONE;
		}

		if ((SlotIndex = FindAddableInventorySlot(SlotIndex, ItemData)) == INDEX_NONE)
		{
			UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : AddItem GetAvailableInventorySlot return false"));

			return INDEX_NONE;
		}

		if (InventorySlotList.Num() <= SlotIndex) InventorySlotList.SetNum(SlotIndex + 1);

		if (GetInventorySlot(SlotIndex).ItemTag.IsValid())
		{
			InventorySlotList[SlotIndex] = ProcessAddItem(ItemData, SlotIndex, EventInfo);

			OnUpdateItem.Broadcast(InventorySlotList[SlotIndex], SlotIndex, EventInfo);
		}

	} while (GetInventorySlot(SlotIndex).ItemTag.IsValid() && ItemData.ItemTag.IsValid());

	if (ItemData.ItemTag.IsValid())
	{
		InventorySlotList[SlotIndex] = ProcessAddItem(ItemData, SlotIndex, EventInfo);

		OnAddItem.Broadcast(ItemData, SlotIndex, EventInfo);

		return SlotIndex;
	}

	return INDEX_NONE;
}

TArray<int32> ULFPInventoryComponent::AddItemList(const TArray<FLFPInventoryItemData>& ItemDataList, int32 SlotIndex, const FString EventInfo)
{
	TArray<int32> ReturnList;

	for (const auto& ItemData : ItemDataList)
	{
		ReturnList.Add(AddItem(ItemData, SlotIndex, EventInfo));
	}

	return ReturnList;
}

bool ULFPInventoryComponent::RemoveItem(FLFPInventoryItemData& RemovedItemData, const int32 SlotIndex, const bool bForce, const FString EventInfo)
{
	if (IsInventorySlotItemValid(SlotIndex) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : RemoveItem IsInventorySlotItemValid return false"));

		return false;
	}

	if (bForce == false)
	{
		if (IsInventorySlotIndexLock(SlotIndex))
		{
			UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : RemoveItem Item is lock"));

			return false;
		}

		if (CanRemoveItem(InventorySlotList[SlotIndex], SlotIndex, EventInfo) == false)
		{
			UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : RemoveItem CanRemoveItem return false"));

			return false;
		}
	}

	RemovedItemData = InventorySlotList[SlotIndex];

	InventorySlotList[SlotIndex] = ProcessRemoveItem(InventorySlotList[SlotIndex], SlotIndex, EventInfo);

	TrimInventorySlotList(SlotIndex);

	OnRemoveItem.Broadcast(RemovedItemData, SlotIndex, EventInfo);

	return true;
}

void ULFPInventoryComponent::RemoveItemList(TArray<FLFPInventoryItemData>& RemovedItemDataList, const TArray<int32> SlotIndexList, const bool bForce, const FString EventInfo)
{
	for (const int32 SlotIndex : SlotIndexList)
	{
		FLFPInventoryItemData RemoveItemData = FLFPInventoryItemData();

		RemoveItem(RemoveItemData, SlotIndex, bForce, EventInfo);

		RemovedItemDataList.Add(RemoveItemData);
	}

	return;
}

void ULFPInventoryComponent::ClearInventory(const bool bForce, const FString EventInfo)
{
	TArray<int32> SlotIndexList;

	for (int32 SlotIndex = 0; SlotIndex < InventorySlotList.Num(); SlotIndex++)
	{
		if (bForce == false)
		{
			if (IsInventorySlotIndexLock(SlotIndex))
			{
				UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : RemoveItemList Item is lock"));

				continue;
			}

			if (CanRemoveItem(InventorySlotList[SlotIndex], SlotIndex, EventInfo) == false)
			{
				UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : RemoveItemList CanRemoveItem return false"));

				continue;
			}
		}

		SlotIndexList.Add(SlotIndex);
	}

	int32 MaxSlotIndex = INDEX_NONE;

	for (const int32 SlotIndex : SlotIndexList)
	{
		FLFPInventoryItemData OldItemData = InventorySlotList[SlotIndex];

		InventorySlotList[SlotIndex] = ProcessRemoveItem(InventorySlotList[SlotIndex], SlotIndex, EventInfo);

		OnRemoveItem.Broadcast(OldItemData, SlotIndex, EventInfo);

		if (SlotIndex > MaxSlotIndex) MaxSlotIndex = SlotIndex;
	}

	TrimInventorySlotList(MaxSlotIndex);

	return;
}

bool ULFPInventoryComponent::SwapItem(const int32 FromSlot, const int32 ToSlot, const FString EventInfo)
{
	int32 MinIndex = FMath::Min(FromSlot, ToSlot);
	int32 MaxIndex = FMath::Max(FromSlot, ToSlot);

	if (FromSlot == ToSlot)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : SwapItem Can't swap to same slot"));

		return false;
	}

	if (MinIndex < 0 || MaxIndex >= MaxInventorySlotAmount)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : SwapItem Slot index is greater or smaller"));

		return false;
	}

	if (InventorySlotList.Num() <= MaxIndex) InventorySlotList.SetNum(MaxIndex + 1);

	if (CanSwapItem(InventorySlotList[FromSlot], FromSlot, InventorySlotList[ToSlot], ToSlot, EventInfo) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : SwapItem CanSwapItem return false"));

		TrimInventorySlotList(InventorySlotList.Num() - 1);

		return false;
	}

	if (InventorySlotList.Num() <= MaxIndex) InventorySlotList.SetNum(MaxIndex + 1);

	InventorySlotList.Swap(MinIndex, MaxIndex);

	OnSwapItem.Broadcast(InventorySlotList[ToSlot], FromSlot, InventorySlotList[FromSlot], ToSlot, EventInfo);

	TrimInventorySlotList(MaxIndex);

	return true;
}

bool ULFPInventoryComponent::SwapItemFromOther(ULFPInventoryComponent* Other, const int32 FromSlot, const int32 ToSlot, const FString EventInfo)
{
	if (Other->IsInventorySlotIndexLock(FromSlot))
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : SwapItemFromOther Other InventorySlotIndex is Lock"));

		return false;
	}

	if (Other->CanRemoveItem(Other->GetInventorySlot(FromSlot), FromSlot, EventInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : SwapItemFromOther Other CanRemoveItem return false"));

		return false;
	}

	if (Other->CanAddItem(GetInventorySlot(ToSlot), FromSlot, EventInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : SwapItemFromOther Other CanAddItem return false"));

		return false;
	}

	if (IsInventorySlotIndexLock(ToSlot))
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : SwapItemFromOther InventorySlotIndex is Lock"));

		return false;
	}

	if (CanRemoveItem(GetInventorySlot(ToSlot), ToSlot, EventInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : SwapItemFromOther CanRemoveItem return false"));

		return false;
	}

	if (CanAddItem(Other->GetInventorySlot(FromSlot), ToSlot, EventInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : SwapItemFromOther CanAddItem return false"));

		return false;
	}

	FLFPInventoryItemData FromData;
	FLFPInventoryItemData ToData;

	Other->RemoveItem(FromData, FromSlot, false, EventInfo);
	RemoveItem(ToData, ToSlot, false, EventInfo);

	Other->AddItem(ToData, FromSlot, EventInfo);
	AddItem(FromData, ToSlot, EventInfo);

	return true;
}

void ULFPInventoryComponent::SortInventory(const FString EventInfo)
{
	if (IsInventorySlotIndexValid(StartInventorySlotIndex) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : SortInventory InventorySlotList is empty or smaller than StartInventorySlotIndex"));

		return;
	}

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
	if (IsInventorySlotItemValid(SlotIndex) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : AddItemLock IsInventorySlotItemValid return false"));

		return false;
	}

	InventorySlotList[SlotIndex].LockList.AddUnique(LockName);

	return true;
}

bool ULFPInventoryComponent::RemoveItemLock(const int32 SlotIndex, const FName LockName)
{
	if (IsInventorySlotItemValid(SlotIndex) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : RemoveItemLock IsInventorySlotItemValid return false"));

		return false;
	}

	InventorySlotList[SlotIndex].LockList.RemoveSingleSwap(LockName);

	return true;
}

bool ULFPInventoryComponent::CanAddItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const
{
	if (GetInventorySlot(SlotIndex).ItemTag != FGameplayTag::EmptyTag) return false;

	for (auto& CheckFunc : CheckComponentList)
	{
		if (IsValid(CheckFunc) && CheckFunc->Implements<ULFPInventoryInterface>() && ILFPInventoryInterface::Execute_CanInventoryAddItem(CheckFunc, ItemData, SlotIndex, EventInfo) == false) return false;
	}

	return true;
}

bool ULFPInventoryComponent::CanRemoveItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const
{
	for (auto& CheckFunc : CheckComponentList)
	{
		if (IsValid(CheckFunc) && CheckFunc->Implements<ULFPInventoryInterface>() && ILFPInventoryInterface::Execute_CanInventoryRemoveItem(CheckFunc, ItemData, SlotIndex, EventInfo) == false) return false;
	}

	return true;
}

bool ULFPInventoryComponent::CanSwapItem_Implementation(const FLFPInventoryItemData& FromItemData, const int32 FromSlot, const FLFPInventoryItemData& ToItemData, const int32 ToSlot, const FString& EventInfo) const
{
	for (auto& CheckFunc : CheckComponentList)
	{
		if (IsValid(CheckFunc) && CheckFunc->Implements<ULFPInventoryInterface>() && ILFPInventoryInterface::Execute_CanInventorySwapItem(CheckFunc, FromItemData, FromSlot, ToItemData, ToSlot, EventInfo) == false) return false;
	}

	return true;
}

int32 ULFPInventoryComponent::FindAddableInventorySlot(int32 SlotIndex, const FLFPInventoryItemData& ForItem, int32 EndIndex, const FString EventInfo) const
{
	if (EndIndex == INDEX_NONE) EndIndex = MaxInventorySlotAmount - 1;

	if (EndIndex >= MaxInventorySlotAmount || SlotIndex >= MaxInventorySlotAmount) return INDEX_NONE;

	if (SlotIndex < 0) SlotIndex = StartInventorySlotIndex;

	for (SlotIndex; SlotIndex <= EndIndex; SlotIndex++)
	{
		if (IsInventorySlotIndexLock(SlotIndex)) continue;

		if (IsInventorySlotAvailable(SlotIndex, GetInventorySlot(SlotIndex), ForItem) == false) continue;

		if (CanAddItem(ForItem, SlotIndex, EventInfo) == false) continue;

		return SlotIndex;
	}

	return INDEX_NONE;
}

bool ULFPInventoryComponent::FindItemListWithItemTag(TArray<int32>& ItemIndexList, const FGameplayTag ItemTag, const int32 StartIndex, int32 EndIndex) const
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
