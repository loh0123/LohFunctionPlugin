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

	if (MaxInventorySlotAmount == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("ULFPInventoryComponent : MaxInventorySlotAmount Is 0"));

		return;
	}

	for (const auto& SlotName : InventorySlotNameList)
	{
		if (SlotName.Value.X <= 0 || SlotName.Value.Y > MaxInventorySlotAmount || SlotName.Value.X > SlotName.Value.Y)
		{
			UE_LOG(LogTemp, Error, TEXT("ULFPInventoryComponent : InventorySlotName (%s) Is Invalid : Please Make Sure X Is Min, Y Is Max, Y Is Smaller Than MaxInventorySlotAmount And X Is Bigger Than -1"), *SlotName.Key.ToString());
		}
	}
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

bool ULFPInventoryComponent::AddItemWithSlotIndex(UPARAM(ref) FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (ItemData.ItemName.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : AddItemWithSlotIndex ItemData Tag is empty"));

		return false;
	}

	if (IsInventorySlotAvailable(SlotIndex, GetInventorySlot(SlotIndex), ItemData) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : AddItemWithSlotIndex IsInventorySlotAvailable return false"));

		return false;
	}

	if (CanAddItem(ItemData, SlotIndex, EventInfo) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : AddItemWithSlotIndex CanAddItem return false"));

		return false;
	}

	if (InventorySlotItemList.IsValidIndex(SlotIndex) == false)
	{
		InventorySlotItemList.SetNum(SlotIndex + 1);
	}

	const FLFPInventoryItemData OldItemData = InventorySlotItemList[SlotIndex];

	const bool bIsCompleted = ProcessAddItem(InventorySlotItemList[SlotIndex], ItemData, SlotIndex, EventInfo);

	BroadcastItemEvent(SlotIndex, OldItemData, InventorySlotItemList[SlotIndex], EventInfo);

	return true;
}

bool ULFPInventoryComponent::AddItemWithSlotName(UPARAM(ref) FLFPInventoryItemData& ItemData, const FName Slotname, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (HasInventorySlotName(Slotname) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : AddItemWithSlotName HasInventorySlotName return false"));

		return false;
	}

	TArray<int32> ItemIndexList;

	if (FindAvailableInventorySlot(ItemIndexList, ItemData, Slotname) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : AddItemWithSlotName FindAvailableInventorySlot return false"));

		return false;
	}

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

		if (bIsCompleted)
		{
			return true;
		}
	}

	return false;
}

bool ULFPInventoryComponent::AddItemList(UPARAM(ref) TArray<FLFPInventoryItemData>& ItemDataList, const FName Slotname, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (HasInventorySlotName(Slotname) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : AddItemList HasInventorySlotName return false")); 
		
		return false;
	}

	bool bIsAllValid = true;

	for (FLFPInventoryItemData& ItemData : ItemDataList)
	{
		if (AddItemWithSlotName(ItemData, Slotname, EventInfo) == false)
		{
			bIsAllValid = false;
		}
	}

	return bIsAllValid;
}

bool ULFPInventoryComponent::RemoveItemWithSlotIndex(UPARAM(ref) FLFPInventoryItemData& ItemData, const int32 SlotIndex, const bool bForce, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (ItemData.ItemName.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : RemoveItemWithSlotIndex RemovedItemData Tag is empty"));

		return false;
	}

	if (GetInventorySlot(SlotIndex).ItemName.IsEqual(ItemData.ItemName) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : RemoveItemWithSlotIndex ItemData Name Not Same"));

		return false;
	}

	if (bForce == false)
	{
		if (CanRemoveItem(InventorySlotItemList[SlotIndex], SlotIndex, EventInfo) == false)
		{
			UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : RemoveItemWithSlotIndex CanRemoveItem Return False"));

			return false;
		}
	}

	const FLFPInventoryItemData OldItemData = InventorySlotItemList[SlotIndex];

	const bool bIsCompleted = ProcessRemoveItem(InventorySlotItemList[SlotIndex], ItemData, SlotIndex, EventInfo);

	BroadcastItemEvent(SlotIndex, OldItemData, InventorySlotItemList[SlotIndex], EventInfo);

	return true;
}

bool ULFPInventoryComponent::RemoveItemWithSlotName(UPARAM(ref) FLFPInventoryItemData& ItemData, const FName Slotname, const bool bForce, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (HasInventorySlotName(Slotname) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : RemoveItemWithSlotName HasInventorySlotName return false"));

		return false;
	}

	TArray<int32> ItemIndexList;

	if (FindItemListWithItemName(ItemIndexList, ItemData.ItemName, Slotname) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : RemoveItemWithSlotName FindItemListWithItemName return false"));

		return false;
	}

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

		if (bIsCompleted)
		{
			return true;
		}
	}

	return false;
}

bool ULFPInventoryComponent::RemoveItemList(UPARAM(ref) TArray<FLFPInventoryItemData>& RemovedItemDataList, const FName Slotname, const bool bForce, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (HasInventorySlotName(Slotname) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : RemoveItemList HasInventorySlotName return false"));

		return false;
	}

	bool bIsAllValid = true;

	for (FLFPInventoryItemData& ItemData : RemovedItemDataList)
	{
		if (RemoveItemWithSlotName(ItemData, Slotname, bForce, EventInfo) == false)
		{
			bIsAllValid = false;
		}
	}

	return bIsAllValid;
}

void ULFPInventoryComponent::ClearInventory(const bool bForce, const FName SlotName, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return; // Prevent this function to run on client

	for (int32 SlotIndex = 0; SlotIndex < InventorySlotItemList.Num(); SlotIndex++)
	{
		FLFPInventoryItemData RemoveData = GetInventorySlot(SlotIndex);

		RemoveItemWithSlotIndex(RemoveData, SlotIndex, bForce, EventInfo);
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

bool ULFPInventoryComponent::SwapItemToAvailable(const int32 FromSlot, const FName SlotName, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (IsInventorySlotItemValid(FromSlot))
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : SwapItemToAvailable FromSlot item is not valid"));

		return false;
	}

	TArray<int32> SwapIndexList;

	if (FindAvailableInventorySlot(SwapIndexList, InventorySlotItemList[FromSlot], SlotName) == false)
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

	FLFPInventoryItemData RemoveFromData = GetInventorySlot(FromSlot);
	FLFPInventoryItemData RemoveToData = ToInventory->GetInventorySlot(ToSlot);

	FLFPInventoryItemData AddFromData = RemoveFromData;
	FLFPInventoryItemData AddToData = RemoveToData;

	if (ToSlot != INDEX_NONE) ToInventory->RemoveItemWithSlotIndex(RemoveToData, ToSlot, false, EventInfo);
	if (FromSlot != INDEX_NONE) RemoveItemWithSlotIndex(RemoveFromData, FromSlot, false, EventInfo);

	if (FromSlot != INDEX_NONE) ToInventory->AddItemWithSlotIndex(AddFromData, ToSlot, EventInfo);
	if (ToSlot != INDEX_NONE) AddItemWithSlotIndex(AddToData, FromSlot, EventInfo);

	return true;
}

void ULFPInventoryComponent::SortInventory(const FName SlotName, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return; // Prevent this function to run on client

	if (HasInventorySlotName(SlotName) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : SortInventory SlotName Not Found"));

		return;
	}

	const auto& SlotRange = InventorySlotNameList.FindChecked(SlotName);

	Sort(InventorySlotItemList.GetData() + SlotRange.X, FMath::Min(InventorySlotItemList.Num() - SlotRange.X, SlotRange.Y - SlotRange.X), [&](const FLFPInventoryItemData& ItemDataA, const FLFPInventoryItemData& ItemDataB)
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

bool ULFPInventoryComponent::FindAvailableInventorySlot(TArray<int32>& SlotList, const FLFPInventoryItemData& ForItem, const FName SlotName, const FString EventInfo) const
{
	if (HasInventorySlotName(SlotName) == false) return false;

	const FIntPoint SlotRange = InventorySlotNameList.FindChecked(SlotName);

	bool IsValidOutput = false;

	for (int32 SlotIndex = SlotRange.X; SlotIndex <= SlotRange.Y; SlotIndex++)
	{
		if (IsInventorySlotAvailable(SlotIndex, GetInventorySlot(SlotIndex), ForItem) == false) continue;

		SlotList.Add(SlotIndex);

		IsValidOutput = true;
	}

	return IsValidOutput;
}

bool ULFPInventoryComponent::FindInventorySlotWithName(TArray<int32>& SlotList, const FName SlotName, const FString EventInfo) const
{
	if (HasInventorySlotName(SlotName) == false) return false;

	const auto& SlotRange = InventorySlotNameList.FindChecked(SlotName);

	SlotList.Reserve(SlotList.Num() + FMath::Min(SlotRange.Y, MaxInventorySlotAmount));

	for (int32 SlotIndex = SlotRange.X; SlotIndex <= SlotRange.Y; SlotIndex++)
	{
		SlotList.Add(SlotIndex);
	}

	return true;
}

bool ULFPInventoryComponent::FindItemListWithTag(TArray<int32>& SlotList, const FGameplayTag SlotTag, const FName SlotName, const FString EventInfo) const
{
	if (HasInventorySlotName(SlotName) == false) return false;

	const FIntPoint SlotRange = InventorySlotNameList.FindChecked(SlotName);

	bool IsValidOutput = false;

	for (int32 SlotIndex = SlotRange.X; SlotIndex <= SlotRange.Y; SlotIndex++)
	{
		if (IsInventorySlotHasTag(SlotIndex, SlotTag) == false) continue;

		SlotList.Add(SlotIndex);

		IsValidOutput = true;
	}

	return IsValidOutput;
}

bool ULFPInventoryComponent::FindItemListWithItemName(TArray<int32>& ItemIndexList, const FName ItemName, const FName SlotName) const
{
	if (HasInventorySlotName(SlotName) == false) return false;

	const FIntPoint SlotRange = InventorySlotNameList.FindChecked(SlotName);

	bool IsValidOutput = false;

	for (int32 SlotIndex = SlotRange.X; SlotIndex <= SlotRange.Y; SlotIndex++)
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
