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

bool ULFPInventoryComponent::AddItem(FLFPInventoryItemData ItemData, FLFPInventoryItemIndexData& ItemIndexData, const int32 StartSlot, const int32 EndSlot, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (ItemData.ItemTag == FGameplayTag::EmptyTag)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : AddItem ItemData Tag is empty"));

		return false;
	}

	TArray<int32> ItemIndexList;

	if (FindAvailableInventorySlot(ItemIndexList, ItemData, StartSlot, EndSlot) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : AddItem FindAvailableInventorySlot return false"));

		return false;
	}

	ItemIndexData.ItemTag = ItemData.ItemTag;

	for (const auto& SlotIndex : ItemIndexList)
	{
		if (CanAddItem(ItemData, SlotIndex, EventInfo) == false)
		{
			continue;
		}

		if (InventorySlotList.IsValidIndex(SlotIndex) == false)
		{
			InventorySlotList.SetNum(SlotIndex + 1);
		}

		const FLFPInventoryItemData OldItemData = InventorySlotList[SlotIndex];

		ProcessAddItem(InventorySlotList[SlotIndex], ItemData, SlotIndex, EventInfo);

		if (OldItemData.ItemTag.IsValid() == false)
		{
			OnAddItem.Broadcast(InventorySlotList[SlotIndex], SlotIndex, EventInfo);
		}

		OnUpdateItem.Broadcast(OldItemData, InventorySlotList[SlotIndex], SlotIndex, EventInfo);

		ItemIndexData.InventoryChangeMap.Add(SlotIndex, InventorySlotList[SlotIndex]);

		if (ItemData.ItemTag.IsValid() == false)
		{
			return true;
		}
	}

	ItemIndexData.LeaveItemData = ItemData;

	return true;
}

bool ULFPInventoryComponent::AddItemList(const TArray<FLFPInventoryItemData>& ItemDataList, TArray<FLFPInventoryItemIndexData>& ItemIndexList, const TArray<FIntPoint>& SearchSlotRangeList, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	int32 Index = 0;

	bool ReturnList = true;

	ItemIndexList.SetNum(ItemDataList.Num());

	for (const auto& ItemData : ItemDataList)
	{
		const FIntPoint SearchSlotRange = SearchSlotRangeList.IsValidIndex(Index) ? SearchSlotRangeList[Index] : FIntPoint(-1);

		ItemIndexList[Index].ItemIndex = Index;

		if (AddItem(ItemData, ItemIndexList[Index], SearchSlotRange.X, SearchSlotRange.Y, EventInfo) == false)
		{
			ReturnList = false;
		}

		Index++;
	}

	return ReturnList;
}

bool ULFPInventoryComponent::RemoveItem(FLFPInventoryItemData ItemData, FLFPInventoryItemIndexData& ItemIndexData, const int32 StartSlot, const int32 EndSlot, const bool bForce, const bool bCheckAllRemove, const bool bApplyChange, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (ItemData.ItemTag == FGameplayTag::EmptyTag)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : RemoveItem RemovedItemData Tag is empty"));

		return false;
	}

	TArray<int32> ItemIndexList;

	if (FindItemListWithItemTag(ItemIndexList, ItemData.ItemTag, StartSlot, EndSlot) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : RemoveItem FindItemListWithItemTag return false"));

		return false;
	}

	ItemIndexData.ItemTag = ItemData.ItemTag;

	ItemIndexData.InventoryChangeMap.Reserve(ItemIndexList.Num());

	for (const auto& SlotIndex : ItemIndexList)
	{
		if (bForce == false)
		{
			if (CanRemoveItem(InventorySlotList[SlotIndex], SlotIndex, EventInfo) == false)
			{
				continue;
			}
		}

		ItemIndexData.InventoryChangeMap.Add(SlotIndex, InventorySlotList[SlotIndex]);

		ProcessRemoveItem(ItemIndexData.InventoryChangeMap.Add(SlotIndex, InventorySlotList[SlotIndex]), ItemData, SlotIndex, EventInfo);

		if (ItemData.ItemTag.IsValid() == false)
		{
			break;
		}
	}

	ItemIndexData.LeaveItemData = ItemData;

	if (ItemData.ItemTag.IsValid() == false || bCheckAllRemove == false)
	{
		if (bApplyChange)
		{
			for (const auto& SlotChangeData : ItemIndexData.InventoryChangeMap)
			{
				const FLFPInventoryItemData OldItemData = InventorySlotList[SlotChangeData.Key];

				InventorySlotList[SlotChangeData.Key] = SlotChangeData.Value;

				if (InventorySlotList[SlotChangeData.Key].ItemTag.IsValid() == false)
				{
					OnRemoveItem.Broadcast(OldItemData, SlotChangeData.Key, EventInfo);
				}

				OnUpdateItem.Broadcast(OldItemData, InventorySlotList[SlotChangeData.Key], SlotChangeData.Key, EventInfo);
			}
		}

		return true;
	}

	UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : RemoveItem Not all item can be remove"));

	return false;
}

bool ULFPInventoryComponent::RemoveItemList(const TArray<FLFPInventoryItemData>& RemovedItemDataList, TArray<FLFPInventoryItemIndexData>& ItemIndexList, const TArray<FIntPoint>& SearchSlotRangeList, const bool bForce, const bool bCheckAllRemove, const bool bApplyChange, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	int32 Index = 0;

	bool ReturnList = true;

	ItemIndexList.SetNum(RemovedItemDataList.Num());

	for (const auto& RemovedItemData : RemovedItemDataList)
	{
		const FIntPoint SearchSlotRange = SearchSlotRangeList.IsValidIndex(Index) ? SearchSlotRangeList[Index] : FIntPoint(-1);

		ItemIndexList[Index].ItemIndex = Index;

		if (RemoveItem(RemovedItemData, ItemIndexList[Index], SearchSlotRange.X, SearchSlotRange.Y, bForce, bCheckAllRemove, false, EventInfo) == false)
		{
			ReturnList = false;
		}

		Index++;
	}

	if ((ReturnList || bCheckAllRemove == false) && bApplyChange)
	{
		for (const auto& InventoryChange : ItemIndexList)
		{
			for (const auto& SlotChangeData : InventoryChange.InventoryChangeMap)
			{
				const FLFPInventoryItemData OldItemData = InventorySlotList[SlotChangeData.Key];

				InventorySlotList[SlotChangeData.Key] = SlotChangeData.Value;

				if (InventorySlotList[SlotChangeData.Key].ItemTag.IsValid() == false)
				{
					OnRemoveItem.Broadcast(OldItemData, SlotChangeData.Key, EventInfo);
				}

				OnUpdateItem.Broadcast(OldItemData, InventorySlotList[SlotChangeData.Key], SlotChangeData.Key, EventInfo);
			}
		}
	}

	return ReturnList;
}

void ULFPInventoryComponent::ClearInventory(const bool bForce, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return; // Prevent this function to run on client

	for (int32 SlotIndex = 0; SlotIndex < InventorySlotList.Num(); SlotIndex++)
	{
		FLFPInventoryItemData RemoveData = GetInventorySlot(SlotIndex);

		FLFPInventoryItemIndexData ItemIndexData;

		RemoveItem(RemoveData, ItemIndexData, SlotIndex, SlotIndex, bForce, false, true, EventInfo);
	}

	TrimInventorySlotList(InventorySlotList.Num() - 1);

	return;
}

bool ULFPInventoryComponent::SwapItem(const int32 FromSlot, const int32 ToSlot, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

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
		//UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : SwapItem CanSwapItem return false"));

		TrimInventorySlotList(InventorySlotList.Num() - 1);

		return false;
	}

	const FLFPInventoryItemData ItemA = InventorySlotList[FromSlot];
	const FLFPInventoryItemData ItemB = InventorySlotList[ToSlot];

	ProcessSwapItem(InventorySlotList[FromSlot], FromSlot, InventorySlotList[ToSlot], ToSlot, EventInfo);

	OnSwapItem.Broadcast(ItemA, FromSlot, ItemB, ToSlot, EventInfo);

	OnUpdateItem.Broadcast(ItemA, InventorySlotList[FromSlot], FromSlot, EventInfo);
	OnUpdateItem.Broadcast(ItemB, InventorySlotList[ToSlot], ToSlot, EventInfo);

	TrimInventorySlotList(MaxIndex);

	return true;
}

bool ULFPInventoryComponent::TransferItem(ULFPInventoryComponent* ToInventory, const int32 FromSlot, const int32 ToSlot, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (ToInventory->IsInventorySlotItemValid(ToSlot) && ToInventory->CanRemoveItem(ToInventory->GetInventorySlot(ToSlot), ToSlot, EventInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : SwapItemFromOther ToInventory CanRemoveItem return false"));

		return false;
	}

	if (IsInventorySlotItemValid(FromSlot) && ToInventory->CanAddItem(GetInventorySlot(FromSlot), ToSlot, EventInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : SwapItemFromOther ToInventory CanAddItem return false"));

		return false;
	}

	if (IsInventorySlotItemValid(FromSlot) && CanRemoveItem(GetInventorySlot(FromSlot), FromSlot, EventInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : SwapItemFromOther CanRemoveItem return false"));

		return false;
	}

	if (ToInventory->IsInventorySlotItemValid(ToSlot) && CanAddItem(ToInventory->GetInventorySlot(ToSlot), FromSlot, EventInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : SwapItemFromOther CanAddItem return false"));

		return false;
	}

	FLFPInventoryItemData FromData = GetInventorySlot(FromSlot);
	FLFPInventoryItemData ToData = ToInventory->GetInventorySlot(ToSlot);

	FLFPInventoryItemIndexData ItemIndexData;

	if (ToSlot != INDEX_NONE) ToInventory->RemoveItem(ToData, ItemIndexData, ToSlot, ToSlot, false, false, true, EventInfo);
	if (FromSlot != INDEX_NONE) RemoveItem(FromData, ItemIndexData, FromSlot, FromSlot, false, false, true, EventInfo);

	if (FromSlot != INDEX_NONE) ToInventory->AddItem(FromData, ItemIndexData, ToSlot, ToSlot, EventInfo);
	if (ToSlot != INDEX_NONE) AddItem(ToData, ItemIndexData, FromSlot, FromSlot, EventInfo);

	return true;
}

void ULFPInventoryComponent::SortInventory(const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return; // Prevent this function to run on client

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
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return; // Prevent this function to run on client

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

bool ULFPInventoryComponent::CanAddItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const
{
	for (auto& CheckFunc : CheckComponentList)
	{
		if (IsValid(CheckFunc) && CheckFunc->Implements<ULFPInventoryInterface>() && ILFPInventoryInterface::Execute_CanInventoryAddItem(CheckFunc, ItemData, SlotIndex, EventInfo) == false) return false;
	}

	return true;
}

bool ULFPInventoryComponent::CanRemoveItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const
{
	if (GetInventorySlot(SlotIndex).ItemTag == FGameplayTag::EmptyTag) return false;

	for (auto& CheckFunc : CheckComponentList)
	{
		if (IsValid(CheckFunc) && CheckFunc->Implements<ULFPInventoryInterface>() && ILFPInventoryInterface::Execute_CanInventoryRemoveItem(CheckFunc, ItemData, SlotIndex, EventInfo) == false) return false;
	}

	return true;
}

bool ULFPInventoryComponent::CanSwapItem_Implementation(const FLFPInventoryItemData& FromItemData, const int32 FromSlot, const FLFPInventoryItemData& ToItemData, const int32 ToSlot, const FString& EventInfo) const
{
	if (IsInventorySlotAvailable(FromSlot, FLFPInventoryItemData::EmptyInventoryItemData, ToItemData) == false || IsInventorySlotAvailable(ToSlot, FLFPInventoryItemData::EmptyInventoryItemData, FromItemData) == false)
	{
		return false;
	}

	for (auto& CheckFunc : CheckComponentList)
	{
		if (IsValid(CheckFunc) && CheckFunc->Implements<ULFPInventoryInterface>() && ILFPInventoryInterface::Execute_CanInventorySwapItem(CheckFunc, FromItemData, FromSlot, ToItemData, ToSlot, EventInfo) == false) return false;
	}

	return true;
}

bool ULFPInventoryComponent::FindAvailableInventorySlot(TArray<int32>& AvailableSlotList, const FLFPInventoryItemData& ForItem, int32 StartSlot, int32 EndSlot, const FString EventInfo) const
{
	if (EndSlot == INDEX_NONE) EndSlot = MaxInventorySlotAmount - 1;

	if (EndSlot >= MaxInventorySlotAmount || StartSlot >= MaxInventorySlotAmount) return false;

	if (StartSlot < 0) StartSlot = 0;

	for (int32 SlotIndex = StartSlot; SlotIndex <= EndSlot; SlotIndex++)
	{
		if (IsInventorySlotAvailable(SlotIndex, GetInventorySlot(SlotIndex), ForItem) == false) continue;

		AvailableSlotList.Add(SlotIndex);
	}

	return AvailableSlotList.Num() > 0;
}

bool ULFPInventoryComponent::FindItemListWithItemTag(TArray<int32>& ItemIndexList, const FGameplayTag ItemTag, int32 StartSlot, int32 EndSlot) const
{
	if (EndSlot == INDEX_NONE) EndSlot = InventorySlotList.Num() - 1;

	if (StartSlot == INDEX_NONE) StartSlot = 0;

	if (StartSlot < 0 || EndSlot >= InventorySlotList.Num()) return false;

	for (int32 SlotIndex = StartSlot; SlotIndex <= EndSlot; SlotIndex++)
	{
		if (InventorySlotList[SlotIndex].ItemTag.MatchesTag(ItemTag))
		{
			ItemIndexList.Add(SlotIndex);
		}
	}

	return ItemIndexList.Num() > 0;
}

void ULFPInventoryComponent::OnInventorySlotRep_Implementation(const TArray<FLFPInventoryItemData>& OldValue)
{
	const int32 MaxSize = FMath::Max(OldValue.Num(), InventorySlotList.Num());

	for (int32 Index = 0; Index < MaxSize; Index++)
	{
		const FLFPInventoryItemData& OldData = OldValue.IsValidIndex(Index) ? OldValue[Index] : FLFPInventoryItemData::EmptyInventoryItemData;

		if (GetInventorySlot(Index) != OldData)
		{
			OnUpdateItem.Broadcast(OldData, GetInventorySlot(Index), Index, "");
		}
	}
}
