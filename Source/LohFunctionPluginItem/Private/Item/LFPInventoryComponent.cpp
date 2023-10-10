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
	DOREPLIFETIME_CONDITION_NOTIFY(ULFPInventoryComponent, SelectedSlotIndexList, COND_None, REPNOTIFY_Always);
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
		if (SlotName.Value.X < 0 || SlotName.Value.Y > MaxInventorySlotAmount || SlotName.Value.X > SlotName.Value.Y)
		{
			UE_LOG(LogTemp, Error, TEXT("ULFPInventoryComponent : InventorySlotName (%s) Is Invalid : Please Make Sure X Is Min, Y Is Max, Y Is Smaller Than MaxInventorySlotAmount And X Is Bigger Than -1"), *SlotName.Key.ToString());
		}
	}

	InventorySlotNameList.Add(FGameplayTag::RequestGameplayTag("Item.SlotNames.All"), FIntPoint(0, MaxInventorySlotAmount - 1));
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
				if (Item.HasItem())
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
	if (OldItemData.IsEmpty() && NewItemData.HasItem())
	{
		OnAddItem.Broadcast(OldItemData, SlotIndex, EventInfo);
	}
	else if (NewItemData.IsEmpty() && OldItemData.HasItem())
	{
		OnRemoveItem.Broadcast(OldItemData, SlotIndex, EventInfo);
	}

	OnUpdateItem.Broadcast(OldItemData, InventorySlotItemList[SlotIndex], SlotIndex, EventInfo);
}

bool ULFPInventoryComponent::AddItem(UPARAM(ref)FLFPInventoryItemData& ItemData, int32 SlotIndex, FGameplayTag SlotName, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (ItemData.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : AddItem ItemData Tag is empty"));

		return false;
	}

	if (HasInventorySlotName(SlotName) == false) SlotName = FGameplayTag::RequestGameplayTag("Inventory.SlotName.All");

	if (SlotIndex >= 0)
	{
		SlotIndex = FindInventorySlotIndexWithName(SlotName, SlotIndex);

		if (IsInventorySlotAvailable(SlotIndex, GetInventorySlot(SlotIndex), ItemData) == false)
		{
			UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : AddItem IsInventorySlotAvailable return false"));

			return false;
		}

		if (CanAddItem(ItemData, SlotIndex, EventInfo) == false)
		{
			UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : AddItem CanAddItem return false"));

			return false;
		}

		if (InventorySlotItemList.IsValidIndex(SlotIndex) == false)
		{
			InventorySlotItemList.SetNum(SlotIndex + 1);
		}

		const FLFPInventoryItemData OldItemData = InventorySlotItemList[SlotIndex];

		const bool bIsCompleted = ProcessAddItem(InventorySlotItemList[SlotIndex], ItemData, SlotIndex, EventInfo);

		BroadcastItemEvent(SlotIndex, OldItemData, InventorySlotItemList[SlotIndex], EventInfo);

		return bIsCompleted;
	}
	else
	{
		TArray<int32> ItemIndexList;

		if (FindAvailableInventorySlot(ItemIndexList, ItemData, SlotName) == false)
		{
			UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : AddItem FindAvailableInventorySlot return false"));

			return false;
		}

		for (const auto& ItemIndex : ItemIndexList)
		{
			if (CanAddItem(ItemData, ItemIndex, EventInfo) == false)
			{
				continue;
			}

			if (InventorySlotItemList.IsValidIndex(ItemIndex) == false)
			{
				InventorySlotItemList.SetNum(ItemIndex + 1);
			}

			const FLFPInventoryItemData OldItemData = InventorySlotItemList[ItemIndex];

			const bool bIsCompleted = ProcessAddItem(InventorySlotItemList[ItemIndex], ItemData, ItemIndex, EventInfo);

			BroadcastItemEvent(ItemIndex, OldItemData, InventorySlotItemList[ItemIndex], EventInfo);

			if (bIsCompleted)
			{
				return true;
			}
		}
	}

	return false;
}

bool ULFPInventoryComponent::AddItemList(UPARAM(ref) TArray<FLFPInventoryItemData>& ItemDataList, FGameplayTag SlotName, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (HasInventorySlotName(SlotName) == false) SlotName = FGameplayTag::RequestGameplayTag("Inventory.SlotName.All");

	bool bIsAllValid = true;

	for (FLFPInventoryItemData& ItemData : ItemDataList)
	{
		if (AddItem(ItemData, INDEX_NONE, SlotName, EventInfo) == false)
		{
			bIsAllValid = false;
		}
	}

	return bIsAllValid;
}

bool ULFPInventoryComponent::RemoveItem(UPARAM(ref)FLFPInventoryItemData& ItemData, int32 SlotIndex, FGameplayTag SlotName, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (ItemData.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : RemoveItem ItemData Tag is empty"));

		return false;
	}

	if (HasInventorySlotName(SlotName) == false) SlotName = FGameplayTag::RequestGameplayTag("Inventory.SlotName.All");

	if (SlotIndex >= 0)
	{
		SlotIndex = FindInventorySlotIndexWithName(SlotName, SlotIndex);

		if (GetInventorySlot(SlotIndex).IsItemEqual(ItemData) == false)
		{
			UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : RemoveItem ItemData Name Not Same"));

			return false;
		}

		if (CanRemoveItem(InventorySlotItemList[SlotIndex], SlotIndex, EventInfo) == false)
		{
			UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : RemoveItem CanRemoveItem Return False"));

			return false;
		}

		const FLFPInventoryItemData OldItemData = InventorySlotItemList[SlotIndex];

		const bool bIsCompleted = ProcessRemoveItem(InventorySlotItemList[SlotIndex], ItemData, SlotIndex, EventInfo);

		BroadcastItemEvent(SlotIndex, OldItemData, InventorySlotItemList[SlotIndex], EventInfo);

		return bIsCompleted;
	}
	else
	{
		TArray<int32> ItemIndexList;

		if (FindItemListWithItemTag(ItemIndexList, ItemData.GetItemTag(), SlotName) == false)
		{
			UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : RemoveItem FindItemListWithItemName return false"));

			return false;
		}

		for (const auto& ItemIndex : ItemIndexList)
		{
			if (CanRemoveItem(InventorySlotItemList[ItemIndex], ItemIndex, EventInfo) == false)
			{
				continue;
			}

			const FLFPInventoryItemData OldItemData = InventorySlotItemList[ItemIndex];

			const bool bIsCompleted = ProcessRemoveItem(InventorySlotItemList[ItemIndex], ItemData, ItemIndex, EventInfo);

			BroadcastItemEvent(ItemIndex, OldItemData, InventorySlotItemList[ItemIndex], EventInfo);

			if (bIsCompleted)
			{
				return true;
			}
		}
	}

	return false;
}

bool ULFPInventoryComponent::RemoveItemList(UPARAM(ref) TArray<FLFPInventoryItemData>& RemovedItemDataList, FGameplayTag SlotName, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (HasInventorySlotName(SlotName) == false) SlotName = FGameplayTag::RequestGameplayTag("Inventory.SlotName.All");

	bool bIsAllValid = true;

	for (FLFPInventoryItemData& ItemData : RemovedItemDataList)
	{
		if (RemoveItem(ItemData, INDEX_NONE, SlotName, EventInfo) == false)
		{
			bIsAllValid = false;
		}
	}

	return bIsAllValid;
}

void ULFPInventoryComponent::ClearInventory(FGameplayTag SlotName, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return; // Prevent this function to run on client

	if (HasInventorySlotName(SlotName) == false) SlotName = FGameplayTag::RequestGameplayTag("Item.SlotNames.All");

	TArray<int32> ItemIndexList;

	if (FindInventorySlotIndexListWithName(ItemIndexList, SlotName) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : ClearInventory FindInventorySlotIndexListWithName return false"));

		return;
	}

	for (const auto& SlotIndex : ItemIndexList)
	{
		const FLFPInventoryItemData OldItemData = InventorySlotItemList[SlotIndex];

		InventorySlotItemList[SlotIndex] = FLFPInventoryItemData();;

		BroadcastItemEvent(SlotIndex, OldItemData, InventorySlotItemList[SlotIndex], EventInfo);
	}

	TrimInventorySlotList();

	return;
}

bool ULFPInventoryComponent::SwapItem(int32 FromSlotIndex, FGameplayTag FromSlotName, int32 ToSlotIndex, FGameplayTag ToSlotName, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	TArray<int32> SwapFromIndexList;
	TArray<int32> SwapToIndexList;

	if (FromSlotIndex < INDEX_NONE || FromSlotIndex > MaxInventorySlotAmount)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : SwapItem FromSlotIndex is not valid"));

		return false;
	}

	if (ToSlotIndex < INDEX_NONE || ToSlotIndex > MaxInventorySlotAmount)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : SwapItem ToSlotIndex is not valid"));

		return false;
	}

	if (HasInventorySlotName(FromSlotName) == false) FromSlotName = FGameplayTag::RequestGameplayTag("Item.SlotNames.All");

	if (HasInventorySlotName(ToSlotName) == false) ToSlotName = FGameplayTag::RequestGameplayTag("Item.SlotNames.All");

	if (FromSlotIndex != INDEX_NONE)
	{
		SwapFromIndexList.Add(FindInventorySlotIndexWithName(FromSlotName, FromSlotIndex));
	}
	else
	{
		FindInventorySlotIndexListWithName(SwapFromIndexList, FromSlotName);
	}

	if (ToSlotIndex != INDEX_NONE)
	{
		SwapToIndexList.Add(FindInventorySlotIndexWithName(ToSlotName, ToSlotIndex));
	}
	else
	{
		FindInventorySlotIndexListWithName(SwapToIndexList, ToSlotName);
	}

	int32 CompleteAmount = 0;
	int32 MaxAmount = 0;

	const bool bMultipleSwap = SwapFromIndexList.Num() > 1 || SwapToIndexList.Num() > 1;

	for (const auto& CurrentFromSlotIndex : SwapFromIndexList)
	{
		if (IsInventorySlotItemValid(CurrentFromSlotIndex) == false)
		{
			CompleteAmount++;

			continue;
		}

		for (const auto& CurrentToSlotIndex : SwapToIndexList)
		{
			if (InventorySlotItemList.IsValidIndex(CurrentToSlotIndex) == false) InventorySlotItemList.SetNum(CurrentToSlotIndex + 1);

			if (CanSwapItem(InventorySlotItemList[CurrentFromSlotIndex], CurrentFromSlotIndex, InventorySlotItemList[CurrentToSlotIndex], CurrentToSlotIndex, EventInfo) == false)
			{
				continue;
			}

			MaxAmount = FMath::Max(CurrentToSlotIndex, MaxAmount);

			const FLFPInventoryItemData ItemA = InventorySlotItemList[CurrentFromSlotIndex];
			const FLFPInventoryItemData ItemB = InventorySlotItemList[CurrentToSlotIndex];

			const bool bIsCompleteSwap = ProcessSwapItem(InventorySlotItemList[CurrentFromSlotIndex], CurrentFromSlotIndex, InventorySlotItemList[CurrentToSlotIndex], CurrentToSlotIndex, bMultipleSwap, EventInfo);

			OnSwapItem.Broadcast(ItemA, CurrentFromSlotIndex, ItemB, CurrentToSlotIndex, EventInfo);

			OnUpdateItem.Broadcast(ItemA, InventorySlotItemList[CurrentFromSlotIndex], CurrentFromSlotIndex, EventInfo);
			OnUpdateItem.Broadcast(ItemB, InventorySlotItemList[CurrentToSlotIndex], CurrentToSlotIndex, EventInfo);

			if (bIsCompleteSwap)
			{
				CompleteAmount++;

				break;
			}
		}
	}

	TrimInventorySlotList();

	return SwapFromIndexList.Num() == CompleteAmount;
}

bool ULFPInventoryComponent::TransferItem(ULFPInventoryComponent* ToInventory, const int32 FromSlotIndex, FGameplayTag FromSlotName, const int32 ToSlotIndex, FGameplayTag ToSlotName, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (IsValid(ToInventory) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : TransferItem ToInventory Is Invalid"));

		return false;
	}

	TArray<int32> SwapFromIndexList;

	if (FromSlotIndex < INDEX_NONE || FromSlotIndex > MaxInventorySlotAmount)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : TransferItem FromSlotIndex is not valid"));

		return false;
	}

	if (ToSlotIndex < INDEX_NONE || ToSlotIndex > ToInventory->MaxInventorySlotAmount)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : TransferItem ToSlotIndex is not valid"));

		return false;
	}

	if (HasInventorySlotName(FromSlotName) == false) FromSlotName = FGameplayTag::RequestGameplayTag("Item.SlotNames.All");

	if (HasInventorySlotName(ToSlotName) == false) ToSlotName = FGameplayTag::RequestGameplayTag("Item.SlotNames.All");

	if (FromSlotIndex != INDEX_NONE)
	{
		SwapFromIndexList.Add(FindInventorySlotIndexWithName(FromSlotName, FromSlotIndex));
	}
	else
	{
		FindInventorySlotIndexListWithName(SwapFromIndexList, FromSlotName);
	}

	int32 CompleteAmount = 0;

	for (const auto& CurrentFromSlotIndex : SwapFromIndexList)
	{
		if (IsInventorySlotItemValid(CurrentFromSlotIndex) == false)
		{
			CompleteAmount++;

			continue;
		}

		FLFPInventoryItemData RemoveItemData = InventorySlotItemList[CurrentFromSlotIndex].Copy();
		FLFPInventoryItemData CacheItem = InventorySlotItemList[CurrentFromSlotIndex].Copy();

		if (RemoveItem(RemoveItemData, CurrentFromSlotIndex, FromSlotName, EventInfo) == false)
		{
			continue;
		}

		if (ToInventory->AddItem(CacheItem, ToSlotIndex, ToSlotName, EventInfo) == false)
		{
			AddItem(CacheItem, CurrentFromSlotIndex, FromSlotName, EventInfo);
		}

		CompleteAmount++;
	}

	return SwapFromIndexList.Num() == CompleteAmount;
}

void ULFPInventoryComponent::SortInventory(FGameplayTag SlotName, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return; // Prevent this function to run on client

	if (HasInventorySlotName(SlotName) == false) SlotName = FGameplayTag::RequestGameplayTag("Item.SlotNames.All");

	const auto& SlotRange = InventorySlotNameList.FindChecked(SlotName);

	TArrayRange<FLFPInventoryItemData> ArrayRange(InventorySlotItemList.GetData() + SlotRange.X, FMath::Min(InventorySlotItemList.Num() - SlotRange.X, SlotRange.Y - SlotRange.X));

	Algo::Sort(ArrayRange, [&](const FLFPInventoryItemData& ItemDataA, const FLFPInventoryItemData& ItemDataB)
		{
			return IsItemSortPriorityHigher(ItemDataA, ItemDataB, EventInfo);
		});

	TrimInventorySlotList();

	OnItemSortEvent.Broadcast();
}

void ULFPInventoryComponent::TrimInventorySlotList()
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return; // Prevent this function to run on client

	if (InventorySlotItemList.IsEmpty())
	{
		return;
	}

	while (InventorySlotItemList.Num() > 0 && InventorySlotItemList[InventorySlotItemList.Num() - 1].IsEmpty())
	{
		InventorySlotItemList.RemoveAt(InventorySlotItemList.Num() - 1, 1, false);
	}

	InventorySlotItemList.Shrink();
}

bool ULFPInventoryComponent::SelectSlotIndex(const int32 SlotIndex, const bool bAddToList)
{
	if (IsInventorySlotIndexValid(SlotIndex) == false) return false;

	if (bAddToList == false)
	{
		SelectedSlotIndexList.Empty(1);
	}

	SelectedSlotIndexList.Add(SlotIndex);

	return true;
}

bool ULFPInventoryComponent::SelectSlotName(const FGameplayTag SlotName, const bool bAddToList)
{
	if (HasInventorySlotName(SlotName) == false) return false;

	if (bAddToList == false)
	{
		SelectedSlotIndexList.Empty();
	}

	const auto& SlotNameRange = InventorySlotNameList.FindChecked(SlotName);

	for (int32 SlotIndex = SlotNameRange.X; SlotIndex <= SlotNameRange.Y; SlotIndex++)
	{
		SelectedSlotIndexList.Add(SlotIndex);
	}

	return true;
}

bool ULFPInventoryComponent::DeselectSlotIndex(const int32 SlotIndex)
{
	if (IsInventorySlotIndexValid(SlotIndex) == false) return false;

	return SelectedSlotIndexList.Remove(SlotIndex) > 0;
}

bool ULFPInventoryComponent::DeselectSlotName(const FGameplayTag SlotName)
{
	if (HasInventorySlotName(SlotName) == false) return false;

	const auto& SlotNameRange = InventorySlotNameList.FindChecked(SlotName);

	return SelectedSlotIndexList.RemoveAll([&](const int32 SlotIndex) 
		{
			return SlotNameRange.X <= SlotIndex || SlotNameRange.Y >= SlotIndex;
		}) > 0;
}

const TArray<int32>& ULFPInventoryComponent::GetSelectedSlotIndexList() const
{
	return SelectedSlotIndexList;
}

int32 ULFPInventoryComponent::GetSelectedSlotIndex(const int32 ListIndex) const
{
	return SelectedSlotIndexList.IsValidIndex(ListIndex) ? SelectedSlotIndexList[ListIndex] : INDEX_NONE;
}

int32 ULFPInventoryComponent::GetSelectedSlotIndexListLength() const
{
	return SelectedSlotIndexList.Num();
}

const FLFPInventoryItemData& ULFPInventoryComponent::GetSelectedSlotItem(const int32 ListIndex) const
{
	return GetInventorySlot(GetSelectedSlotIndex(ListIndex));
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
	if (GetInventorySlot(SlotIndex).IsEmpty()) return false;

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

bool ULFPInventoryComponent::IsInventorySlotHasName(const int32 Index, const FGameplayTag SlotName) const
{
	if (HasInventorySlotName(SlotName) == false) return false;

	const auto& SlotRange = InventorySlotNameList.FindChecked(SlotName);

	return (SlotRange.X <= Index && SlotRange.Y >= Index);
}

bool ULFPInventoryComponent::HaveItemsAtSlotName(const TArray<FLFPInventoryItemData>& ItemList, const FGameplayTag SlotName) const
{
	if (HasInventorySlotName(SlotName) == false) return false;

	TArray<FLFPInventoryItemData> CacheList;

	CacheList.Reserve(ItemList.Num());

	for (const FLFPInventoryItemData& Item : ItemList)
	{
		if (Item.IsEmpty())
		{
			continue;
		}

		CacheList.Add(Item.Copy());
	}

	const auto& SlotRange = InventorySlotNameList.FindChecked(SlotName);

	for (FLFPInventoryItemData& CacheItem : CacheList)
	{
		bool bIsComplete = false;

		for (int32 SlotIndex = SlotRange.X; SlotIndex <= SlotRange.Y; SlotIndex++)
		{
			const FLFPInventoryItemData& SlotItem = GetInventorySlot(SlotIndex);

			if (SlotItem.IsItemEqual(CacheItem))
			{
				FLFPInventoryItemData CacheSlotItem = SlotItem.Copy();

				if (ProcessRemoveItem(CacheItem, CacheSlotItem, SlotIndex, "HaveItemsAtSlotName"))
				{
					bIsComplete = true;

					break;
				}
			}
		}

		if (bIsComplete == false)
		{
			return false;
		}
	}

	return true;
}

bool ULFPInventoryComponent::FindAvailableInventorySlot(TArray<int32>& SlotList, const FLFPInventoryItemData& ForItem, const FGameplayTag SlotName) const
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

int32 ULFPInventoryComponent::FindInventorySlotIndexWithName(const FGameplayTag SlotName, const int32 SlotRangeIndex) const
{
	if (HasInventorySlotName(SlotName) == false) return INDEX_NONE;

	const FIntPoint SlotRange = InventorySlotNameList.FindChecked(SlotName);

	const int32 FinalIndex = SlotRangeIndex + SlotRange.X;

	return FinalIndex > SlotRange.Y ? INDEX_NONE : FinalIndex;
}

bool ULFPInventoryComponent::FindInventorySlotIndexListWithName(TArray<int32>& SlotList, const FGameplayTag SlotName) const
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

bool ULFPInventoryComponent::FindItemListWithCategorizeTag(TArray<int32>& SlotList, const FGameplayTag SlotTag, const FGameplayTag SlotName) const
{
	if (HasInventorySlotName(SlotName) == false) return false;

	const FIntPoint SlotRange = InventorySlotNameList.FindChecked(SlotName);

	bool IsValidOutput = false;

	for (int32 SlotIndex = SlotRange.X; SlotIndex <= SlotRange.Y; SlotIndex++)
	{
		if (IsInventorySlotHasCategorize(SlotIndex, SlotTag) == false) continue;

		SlotList.Add(SlotIndex);

		IsValidOutput = true;
	}

	return IsValidOutput;
}

bool ULFPInventoryComponent::FindItemListWithItemTag(TArray<int32>& ItemIndexList, const FGameplayTag ItemTag, const FGameplayTag SlotName) const
{
	if (HasInventorySlotName(SlotName) == false) return false;

	const FIntPoint SlotRange = InventorySlotNameList.FindChecked(SlotName);

	bool IsValidOutput = false;

	for (int32 SlotIndex = SlotRange.X; SlotIndex <= SlotRange.Y; SlotIndex++)
	{
		if (GetInventorySlot(SlotIndex).IsItemEqual(ItemTag) == false) continue;
		
		ItemIndexList.Add(SlotIndex);

		IsValidOutput = true;
	}

	return IsValidOutput;
}

const FLFPInventoryItemData& ULFPInventoryComponent::GetInventorySlot(const int32 Index, FGameplayTag StartSlotName) const
{
	if (HasInventorySlotName(StartSlotName) == false) StartSlotName = FGameplayTag::RequestGameplayTag("Item.SlotNames.All");

	const int32 TargetIndex = FindInventorySlotIndexWithName(StartSlotName, Index);

	return IsInventorySlotIndexValid(TargetIndex) ? InventorySlotItemList[TargetIndex] : FLFPInventoryItemData::EmptyInventoryItemData;
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

void ULFPInventoryComponent::OnSelectedSlotIndexListRep_Implementation(const TArray<int32>& OldValue)
{
}
