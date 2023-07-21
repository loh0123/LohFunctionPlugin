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

	DOREPLIFETIME_CONDITION_NOTIFY(ULFPInventoryComponent, InventorySlotItemList, COND_None, REPNOTIFY_Always);
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

	if (Ar.IsSaveGame())
	{
		Ar << InventorySlotItemList;

		if (Ar.IsLoading())
		{
			int32 Index = 0;

			for (const FLFPInventoryItemData& Item : InventorySlotItemList)
			{
				if (Item.ItemName.IsNone() == false)
				{
					OnAddItem.Broadcast(Item, Index, FString("Serialize"));
				}

				Index++;
			}
		}
	}
}

void ULFPInventoryComponent::BroadcastItemEvent(const int32 SlotIndex, const FLFPInventoryItemData& OldItemData, const FLFPInventoryItemData& NewItemData, const FString& EventInfo) const
{
	if (OldItemData.ItemName.IsNone() && (NewItemData.ItemName.IsNone() == false))
	{
		OnAddItem.Broadcast(OldItemData, SlotIndex, EventInfo);
	}
	else if (NewItemData.ItemName.IsNone() && (OldItemData.ItemName.IsNone() == false))
	{
		OnRemoveItem.Broadcast(OldItemData, SlotIndex, EventInfo);
	}

	OnUpdateItem.Broadcast(OldItemData, InventorySlotItemList[SlotIndex], SlotIndex, EventInfo);
}

bool ULFPInventoryComponent::AddItem(FLFPInventoryItemData ItemData, FLFPInventoryItemIndexData& ItemIndexData, const int32 StartSlot, const int32 EndSlot, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (ItemData.ItemName.IsNone())
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

	ItemIndexData.ItemName = ItemData.ItemName;

	for (const auto& SlotIndex : ItemIndexList)
	{
		if (CanAddItem(ItemData, SlotIndex, EventInfo) == false)
		{
			continue;
		}

		if (InventorySlotItemList.IsValidIndex(SlotIndex) == false)
		{
			InventorySlotItemList.SetNum(SlotIndex + 1);
		}

		const FLFPInventoryItemData OldItemData = InventorySlotItemList[SlotIndex];

		const bool bIsCompleted = ProcessAddItem(InventorySlotItemList[SlotIndex], ItemData, SlotIndex, EventInfo);

		BroadcastItemEvent(SlotIndex, OldItemData, InventorySlotItemList[SlotIndex], EventInfo);

		ItemIndexData.InventoryChangeMap.Add(SlotIndex, OldItemData);

		if (bIsCompleted)
		{
			break;
		}
	}

	ItemIndexData.LeaveItemData = ItemData;

	return true;
}

bool ULFPInventoryComponent::AddItemWithSlotName(FLFPInventoryItemData ItemData, FLFPInventoryItemIndexData& ItemIndexData, const FName Slotname, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (HasInventorySlotName(Slotname) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : AddItem HasInventorySlotName return false"));

		return false;
	}

	const FIntPoint& SearchSlotRange = InventorySlotNameList.FindChecked(Slotname);

	return AddItem(ItemData, ItemIndexData, SearchSlotRange.X, SearchSlotRange.Y, EventInfo);
}

bool ULFPInventoryComponent::AddItemList(const TArray<FLFPInventoryItemData>& ItemDataList, TArray<FLFPInventoryItemIndexData>& ItemIndexList, const FName Slotname, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (HasInventorySlotName(Slotname) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : AddItemList HasInventorySlotName return false")); 
		
		return false;
	}

	const FIntPoint& SearchSlotRange = InventorySlotNameList.FindChecked(Slotname);

	int32 Index = 0;

	bool ReturnList = true;

	ItemIndexList.SetNum(ItemDataList.Num());

	for (const auto& ItemData : ItemDataList)
	{
		ItemIndexList[Index].ItemIndex = Index;

		if (AddItem(ItemData, ItemIndexList[Index], SearchSlotRange.X, SearchSlotRange.Y, EventInfo) == false)
		{
			ReturnList = false;
		}

		Index++;
	}

	return ReturnList;
}

bool ULFPInventoryComponent::RemoveItem(FLFPInventoryItemData ItemData, FLFPInventoryItemIndexData& ItemIndexData, const int32 StartSlot, const int32 EndSlot, const bool bForce, const bool bCheckAllRemove, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (ItemData.ItemName.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : RemoveItem RemovedItemData Tag is empty"));

		return false;
	}

	TArray<int32> ItemIndexList;

	if (FindItemListWithItemName(ItemIndexList, ItemData.ItemName, StartSlot, EndSlot) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : RemoveItem FindItemListWithItemName return false"));

		return false;
	}

	ItemIndexData.ItemName = ItemData.ItemName;

	ItemIndexData.InventoryChangeMap.Reserve(ItemIndexList.Num());

	for (const auto& SlotIndex : ItemIndexList)
	{
		if (bForce == false)
		{
			if (CanRemoveItem(InventorySlotItemList[SlotIndex], SlotIndex, EventInfo) == false)
			{
				continue;
			}
		}

		const FLFPInventoryItemData OldItemData = InventorySlotItemList[SlotIndex];

		const bool bIsCompleted = ProcessRemoveItem(InventorySlotItemList[SlotIndex], ItemData, SlotIndex, EventInfo);

		BroadcastItemEvent(SlotIndex, OldItemData, InventorySlotItemList[SlotIndex], EventInfo);

		ItemIndexData.InventoryChangeMap.Add(SlotIndex, OldItemData);

		if (bIsCompleted)
		{
			break;
		}
	}

	ItemIndexData.LeaveItemData = ItemData;

	return true;
}

bool ULFPInventoryComponent::RemoveItemWithSlotName(FLFPInventoryItemData ItemData, FLFPInventoryItemIndexData& ItemIndexData, const FName Slotname, const bool bForce, const bool bCheckAllRemove, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (HasInventorySlotName(Slotname) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : RemoveItem HasInventorySlotName return false"));

		return false;
	}

	const FIntPoint& SearchSlotRange = InventorySlotNameList.FindChecked(Slotname);

	return RemoveItem(ItemData, ItemIndexData, SearchSlotRange.X, SearchSlotRange.Y, bForce, bCheckAllRemove, EventInfo);
}

bool ULFPInventoryComponent::RemoveItemList(const TArray<FLFPInventoryItemData>& RemovedItemDataList, TArray<FLFPInventoryItemIndexData>& ItemIndexList, const FName Slotname, const bool bForce, const bool bCheckAllRemove, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (HasInventorySlotName(Slotname) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : RemoveItemList HasInventorySlotName return false"));

		return false;
	}

	const FIntPoint& SearchSlotRange = InventorySlotNameList.FindChecked(Slotname);

	int32 Index = 0;

	bool ReturnList = true;

	ItemIndexList.SetNum(RemovedItemDataList.Num());

	for (const auto& RemovedItemData : RemovedItemDataList)
	{
		ItemIndexList[Index].ItemIndex = Index;

		if (RemoveItem(RemovedItemData, ItemIndexList[Index], SearchSlotRange.X, SearchSlotRange.Y, bForce, bCheckAllRemove, EventInfo) == false)
		{
			ReturnList = bCheckAllRemove == false;
		}

		Index++;
	}

	return ReturnList;
}

void ULFPInventoryComponent::ClearInventory(const bool bForce, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return; // Prevent this function to run on client

	for (int32 SlotIndex = 0; SlotIndex < InventorySlotItemList.Num(); SlotIndex++)
	{
		FLFPInventoryItemData RemoveData = GetInventorySlot(SlotIndex);

		FLFPInventoryItemIndexData ItemIndexData;

		RemoveItem(RemoveData, ItemIndexData, SlotIndex, SlotIndex, bForce, false, EventInfo);
	}

	TrimInventorySlotList(InventorySlotItemList.Num() - 1);

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
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : SwapItem Slot index is not valid"));

		return false;
	}

	if (InventorySlotItemList.Num() <= MaxIndex) InventorySlotItemList.SetNum(MaxIndex + 1);

	if (CanSwapItem(InventorySlotItemList[FromSlot], FromSlot, InventorySlotItemList[ToSlot], ToSlot, EventInfo) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : SwapItem CanSwapItem return false"));

		TrimInventorySlotList(InventorySlotItemList.Num() - 1);

		return false;
	}

	const FLFPInventoryItemData ItemA = InventorySlotItemList[FromSlot];
	const FLFPInventoryItemData ItemB = InventorySlotItemList[ToSlot];

	ProcessSwapItem(InventorySlotItemList[FromSlot], FromSlot, InventorySlotItemList[ToSlot], ToSlot, EventInfo);

	OnSwapItem.Broadcast(ItemA, FromSlot, ItemB, ToSlot, EventInfo);

	OnUpdateItem.Broadcast(ItemA, InventorySlotItemList[FromSlot], FromSlot, EventInfo);
	OnUpdateItem.Broadcast(ItemB, InventorySlotItemList[ToSlot], ToSlot, EventInfo);

	TrimInventorySlotList(MaxIndex);

	return true;
}

bool ULFPInventoryComponent::SwapItemToAvailable(const int32 FromSlot, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (IsInventorySlotItemValid(FromSlot))
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : SwapItemToAvailable FromSlot item is not valid"));

		return false;
	}

	TArray<int32> SwapIndexList;

	if (FindAvailableInventorySlot(SwapIndexList, InventorySlotItemList[FromSlot], -1, -1) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : SwapItemToAvailable FindAvailableInventorySlot return false"));

		return false;
	}

	for (const auto& SlotIndex : SwapIndexList)
	{
		if (CanSwapItem(InventorySlotItemList[FromSlot], FromSlot, InventorySlotItemList[SlotIndex], SlotIndex, EventInfo) == false)
		{
			continue;
		}

		if (InventorySlotItemList.IsValidIndex(SlotIndex) == false)
		{
			InventorySlotItemList.SetNum(SlotIndex + 1);
		}

		const FLFPInventoryItemData ItemA = InventorySlotItemList[FromSlot];
		const FLFPInventoryItemData ItemB = InventorySlotItemList[SlotIndex];

		ProcessSwapItem(InventorySlotItemList[FromSlot], FromSlot, InventorySlotItemList[SlotIndex], SlotIndex, EventInfo);

		OnSwapItem.Broadcast(ItemA, FromSlot, ItemB, SlotIndex, EventInfo);

		OnUpdateItem.Broadcast(ItemA, InventorySlotItemList[FromSlot], FromSlot, EventInfo);
		OnUpdateItem.Broadcast(ItemB, InventorySlotItemList[SlotIndex], SlotIndex, EventInfo);

		TrimInventorySlotList(SlotIndex);

		return true;
	}

	UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : SwapItemToAvailable Swap fail"));

	return false;
}

bool ULFPInventoryComponent::TransferItem(ULFPInventoryComponent* ToInventory, const int32 FromSlot, const int32 ToSlot, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (IsValid(ToInventory) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : TransferItem ToInventory Is Invalid"));

		return false;
	}

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

	if (ToSlot != INDEX_NONE) ToInventory->RemoveItem(ToData, ItemIndexData, ToSlot, ToSlot, false, false, EventInfo);
	if (FromSlot != INDEX_NONE) RemoveItem(FromData, ItemIndexData, FromSlot, FromSlot, false, false, EventInfo);

	if (FromSlot != INDEX_NONE) ToInventory->AddItem(FromData, ItemIndexData, ToSlot, ToSlot, EventInfo);
	if (ToSlot != INDEX_NONE) AddItem(ToData, ItemIndexData, FromSlot, FromSlot, EventInfo);

	return true;
}

void ULFPInventoryComponent::SortInventory(const FIntPoint SortRange, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return; // Prevent this function to run on client

	if (IsInventorySlotIndexValid(SortRange.X) == false || IsInventorySlotIndexValid(SortRange.Y) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : SortInventory InventorySlotItemList is empty or SortRange is not valid"));

		return;
	}

	Sort(InventorySlotItemList.GetData() + SortRange.X, FMath::Min(InventorySlotItemList.Num() - SortRange.X, SortRange.Y - SortRange.X), [&](const FLFPInventoryItemData& ItemDataA, const FLFPInventoryItemData& ItemDataB)
		{
			return IsItemSortPriorityHigher(ItemDataA, ItemDataB, EventInfo);
		});

	TrimInventorySlotList(InventorySlotItemList.Num() - 1);

	OnItemSortEvent.Broadcast();
}

void ULFPInventoryComponent::TrimInventorySlotList(const int32 FromSlot)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return; // Prevent this function to run on client

	if (IsInventorySlotIndexValid(FromSlot) == false || IsInventorySlotIndexValid(FromSlot + 1))
	{
		return;
	}

	while (InventorySlotItemList.Num() > 0 && InventorySlotItemList[InventorySlotItemList.Num() - 1].ItemName.IsNone())
	{
		InventorySlotItemList.RemoveAt(InventorySlotItemList.Num() - 1, 1, false);
	}

	InventorySlotItemList.Shrink();
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
	if (GetInventorySlot(SlotIndex).ItemName.IsNone()) return false;

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

bool ULFPInventoryComponent::IsInventorySlotHasName(const int32 Index, const FName SlotName) const
{
	if (HasInventorySlotName(SlotName) == false) return false;

	const auto& SlotRange = InventorySlotNameList.FindChecked(SlotName);

	return (SlotRange.X >= Index && SlotRange.Y <= Index);
}

bool ULFPInventoryComponent::FindAvailableInventorySlot(TArray<int32>& SlotList, const FLFPInventoryItemData& ForItem, int32 StartSlot, int32 EndSlot, const FString EventInfo) const
{
	if (EndSlot == INDEX_NONE) EndSlot = MaxInventorySlotAmount - 1;

	if (EndSlot >= MaxInventorySlotAmount || StartSlot >= MaxInventorySlotAmount) return false;

	if (StartSlot < 0) StartSlot = 0;

	bool IsValidOutput = false;

	for (int32 SlotIndex = StartSlot; SlotIndex <= EndSlot; SlotIndex++)
	{
		if (IsInventorySlotAvailable(SlotIndex, GetInventorySlot(SlotIndex), ForItem) == false) continue;

		SlotList.Add(SlotIndex);

		IsValidOutput = true;
	}

	return IsValidOutput;
}

bool ULFPInventoryComponent::FindInventorySlotWithName(TArray<int32>& SlotList, const FName SlotName, int32 StartSlot, int32 EndSlot, const FString EventInfo) const
{
	if (EndSlot == INDEX_NONE) EndSlot = MaxInventorySlotAmount - 1;

	if (EndSlot >= MaxInventorySlotAmount || StartSlot >= MaxInventorySlotAmount) return false;

	if (StartSlot < 0) StartSlot = 0;

	if (HasInventorySlotName(SlotName) == false) return false;

	const auto& SlotRange = InventorySlotNameList.FindChecked(SlotName);

	bool IsValidOutput = false;

	SlotList.Reserve(SlotList.Num() + FMath::Min(SlotRange.Y, MaxInventorySlotAmount));

	for (int32 Index = FMath::Max(SlotRange.X, StartSlot); Index <= FMath::Min(SlotRange.Y, EndSlot); Index++)
	{
		SlotList.Add(Index);

		IsValidOutput = true;
	}

	return IsValidOutput;
}

bool ULFPInventoryComponent::FindItemListWithTag(TArray<int32>& SlotList, const FGameplayTag SlotTag, int32 StartSlot, int32 EndSlot, const FString EventInfo) const
{
	if (EndSlot == INDEX_NONE) EndSlot = MaxInventorySlotAmount - 1;

	if (EndSlot >= MaxInventorySlotAmount || StartSlot >= MaxInventorySlotAmount) return false;

	if (StartSlot < 0) StartSlot = 0;

	bool IsValidOutput = false;

	for (int32 SlotIndex = StartSlot; SlotIndex <= EndSlot; SlotIndex++)
	{
		if (IsInventorySlotHasTag(SlotIndex, SlotTag) == false) continue;

		SlotList.Add(SlotIndex);

		IsValidOutput = true;
	}

	return IsValidOutput;
}

bool ULFPInventoryComponent::FindItemListWithItemName(TArray<int32>& ItemIndexList, const FName ItemName, int32 StartSlot, int32 EndSlot) const
{
	if (EndSlot == INDEX_NONE) EndSlot = InventorySlotItemList.Num() - 1;

	if (StartSlot == INDEX_NONE) StartSlot = 0;

	if (StartSlot < 0 || EndSlot >= InventorySlotItemList.Num()) return false;

	bool IsValidOutput = false;

	for (int32 SlotIndex = StartSlot; SlotIndex <= EndSlot; SlotIndex++)
	{
		if (InventorySlotItemList[SlotIndex].ItemName.IsEqual(ItemName) == false) continue;
		
		ItemIndexList.Add(SlotIndex);

		IsValidOutput = true;
	}

	return IsValidOutput;
}

void ULFPInventoryComponent::OnInventorySlotItemListRep_Implementation(const TArray<FLFPInventoryItemData>& OldValue)
{
	const int32 MaxSize = FMath::Max(OldValue.Num(), InventorySlotItemList.Num());

	for (int32 Index = 0; Index < MaxSize; Index++)
	{
		const FLFPInventoryItemData& OldData = OldValue.IsValidIndex(Index) ? OldValue[Index] : FLFPInventoryItemData::EmptyInventoryItemData;

		if (GetInventorySlot(Index) != OldData)
		{
			OnUpdateItem.Broadcast(OldData, GetInventorySlot(Index), Index, "");
		}
	}
}
