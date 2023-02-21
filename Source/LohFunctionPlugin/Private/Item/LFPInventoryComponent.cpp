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

int32 ULFPInventoryComponent::AddItem(FLFPInventoryItemData ItemData, const FIntPoint SearchSlotRange, const FString EventInfo)
{
	if (ItemData.ItemTag == FGameplayTag::EmptyTag)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : AddItem ItemData Tag is empty"));

		return INDEX_NONE;
	}

	TArray<int32> ItemIndexList;

	if (FindAvailableInventorySlot(ItemIndexList, SearchSlotRange, ItemData) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : AddItem FindAvailableInventorySlot return false"));

		return INDEX_NONE;
	}

	for (const auto& SlotIndex : ItemIndexList)
	{
		if (CanAddItem(ItemData, SlotIndex, EventInfo) == false)
		{
			continue;
		}

		if (InventorySlotList.IsValidIndex(SlotIndex) == false) InventorySlotList.SetNum(SlotIndex + 1);

		const FLFPInventoryItemData OldItemData = InventorySlotList[SlotIndex];

		ProcessAddItem(InventorySlotList[SlotIndex], ItemData, SlotIndex, EventInfo);

		if (OldItemData.ItemTag.IsValid() == false)
		{
			OnAddItem.Broadcast(InventorySlotList[SlotIndex], SlotIndex, EventInfo);
		}

		OnUpdateItem.Broadcast(OldItemData, InventorySlotList[SlotIndex], SlotIndex, EventInfo);

		if (ItemData.ItemTag.IsValid() == false)
		{
			return SlotIndex;
		}
	}

	return INDEX_NONE;
}

TArray<int32> ULFPInventoryComponent::AddItemList(const TArray<FLFPInventoryItemData>& ItemDataList, const TArray<FIntPoint>& SearchSlotRangeList, const FString EventInfo)
{
	int32 Index = 0;

	TArray<int32> ReturnList;

	for (const auto& ItemData : ItemDataList)
	{
		const FIntPoint SearchSlotRange = SearchSlotRangeList.IsValidIndex(Index) ? SearchSlotRangeList[Index] : FIntPoint(-1);

		ReturnList.Add(AddItem(ItemData, SearchSlotRange, EventInfo));

		Index++;
	}

	return ReturnList;
}

int32 ULFPInventoryComponent::RemoveItem(FLFPInventoryItemData RemovedItemData, const FIntPoint SearchSlotRange, const bool bForce, const FString EventInfo)
{
	if (RemovedItemData.ItemTag == FGameplayTag::EmptyTag)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPInventoryComponent : RemoveItem RemovedItemData Tag is empty"));

		return INDEX_NONE;
	}

	TArray<int32> ItemIndexList;

	if (FindItemListWithItemTag(ItemIndexList, RemovedItemData.ItemTag, SearchSlotRange) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPInventoryComponent : RemoveItem FindItemListWithItemTag return false"));

		return INDEX_NONE;
	}

	for (const auto& SlotIndex : ItemIndexList)
	{
		if (bForce == false)
		{
			if (CanRemoveItem(InventorySlotList[SlotIndex], SlotIndex, EventInfo) == false)
			{
				continue;
			}
		}

		const FLFPInventoryItemData OldItemData = InventorySlotList[SlotIndex];

		ProcessRemoveItem(InventorySlotList[SlotIndex], RemovedItemData, SlotIndex, EventInfo);

		if (InventorySlotList[SlotIndex].ItemTag.IsValid() == false)
		{
			OnRemoveItem.Broadcast(OldItemData, SlotIndex, EventInfo);
		}

		OnUpdateItem.Broadcast(OldItemData, InventorySlotList[SlotIndex], SlotIndex, EventInfo);

		if (RemovedItemData.ItemTag.IsValid() == false)
		{
			return SlotIndex;
		}
	}

	return INDEX_NONE;
}

TArray<int32> ULFPInventoryComponent::RemoveItemList(const TArray<FLFPInventoryItemData>& RemovedItemDataList, const TArray<FIntPoint>& SearchSlotRangeList, const bool bForce, const FString EventInfo)
{
	int32 Index = 0;

	TArray<int32> ReturnList;

	for (const auto& RemovedItemData : RemovedItemDataList)
	{
		const FIntPoint SearchSlotRange = SearchSlotRangeList.IsValidIndex(Index) ? SearchSlotRangeList[Index] : FIntPoint(-1);

		ReturnList.Add(RemoveItem(RemovedItemData, SearchSlotRange, bForce, EventInfo));

		Index++;
	}

	return ReturnList;
}

void ULFPInventoryComponent::ClearInventory(const bool bForce, const FString EventInfo)
{
	for (int32 SlotIndex = 0; SlotIndex < InventorySlotList.Num(); SlotIndex++)
	{
		FLFPInventoryItemData RemoveData = FLFPInventoryItemData();

		RemoveItem(RemoveData, SlotIndex, bForce, EventInfo);
	}

	TrimInventorySlotList(InventorySlotList.Num() - 1);

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

	const FLFPInventoryItemData ItemA = InventorySlotList[FromSlot];
	const FLFPInventoryItemData ItemB = InventorySlotList[ToSlot];

	ProcessSwapItem(InventorySlotList[FromSlot], FromSlot, InventorySlotList[ToSlot], ToSlot, EventInfo);

	OnSwapItem.Broadcast(ItemA, FromSlot, ItemB, ToSlot, EventInfo);

	OnUpdateItem.Broadcast(ItemA, InventorySlotList[FromSlot], FromSlot, EventInfo);
	OnUpdateItem.Broadcast(ItemB, InventorySlotList[ToSlot], ToSlot, EventInfo);

	TrimInventorySlotList(MaxIndex);

	return true;
}

bool ULFPInventoryComponent::SwapItemFromOther(ULFPInventoryComponent* Other, const int32 FromSlot, const int32 ToSlot, const FString EventInfo)
{
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

bool ULFPInventoryComponent::CanAddItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const
{
	for (const auto& IgnoreRange : IgnoreInventorySlotList)
		if (SlotIndex >= IgnoreRange.X && SlotIndex <= IgnoreRange.Y)
		{
			return false;
		}

	for (auto& CheckFunc : CheckComponentList)
	{
		if (IsValid(CheckFunc) && CheckFunc->Implements<ULFPInventoryInterface>() && ILFPInventoryInterface::Execute_CanInventoryAddItem(CheckFunc, ItemData, SlotIndex, EventInfo) == false) return false;
	}

	return true;
}

bool ULFPInventoryComponent::CanRemoveItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const
{
	for (const auto& IgnoreRange : IgnoreInventorySlotList)
		if (SlotIndex >= IgnoreRange.X && SlotIndex <= IgnoreRange.Y)
		{
			return false;
		}

	if (GetInventorySlot(SlotIndex).ItemTag == FGameplayTag::EmptyTag) return false;

	for (auto& CheckFunc : CheckComponentList)
	{
		if (IsValid(CheckFunc) && CheckFunc->Implements<ULFPInventoryInterface>() && ILFPInventoryInterface::Execute_CanInventoryRemoveItem(CheckFunc, ItemData, SlotIndex, EventInfo) == false) return false;
	}

	return true;
}

bool ULFPInventoryComponent::CanSwapItem_Implementation(const FLFPInventoryItemData& FromItemData, const int32 FromSlot, const FLFPInventoryItemData& ToItemData, const int32 ToSlot, const FString& EventInfo) const
{
	for (const auto& IgnoreRange : IgnoreInventorySlotList)
		if ((FromSlot >= IgnoreRange.X && FromSlot <= IgnoreRange.Y) || (ToSlot >= IgnoreRange.X && ToSlot <= IgnoreRange.Y))
		{
			return false;
		}

	for (auto& CheckFunc : CheckComponentList)
	{
		if (IsValid(CheckFunc) && CheckFunc->Implements<ULFPInventoryInterface>() && ILFPInventoryInterface::Execute_CanInventorySwapItem(CheckFunc, FromItemData, FromSlot, ToItemData, ToSlot, EventInfo) == false) return false;
	}

	return true;
}

bool ULFPInventoryComponent::FindAvailableInventorySlot(TArray<int32>& AvailableSlotList, FIntPoint SearchSlotRange, const FLFPInventoryItemData& ForItem, const FString EventInfo) const
{
	if (SearchSlotRange.Y == INDEX_NONE) SearchSlotRange.Y = MaxInventorySlotAmount - 1;

	if (SearchSlotRange.Y >= MaxInventorySlotAmount || SearchSlotRange.X >= MaxInventorySlotAmount) return false;

	if (SearchSlotRange.X < 0) SearchSlotRange.X = 0;

	for (SearchSlotRange.X; SearchSlotRange.X <= SearchSlotRange.Y; SearchSlotRange.X++)
	{
		if (IsInventorySlotAvailable(SearchSlotRange.X, GetInventorySlot(SearchSlotRange.X), ForItem) == false) continue;

		AvailableSlotList.Add(SearchSlotRange.X);
	}

	return AvailableSlotList.Num() > 0;
}

bool ULFPInventoryComponent::FindItemListWithItemTag(TArray<int32>& ItemIndexList, const FGameplayTag ItemTag, FIntPoint SearchSlotRange) const
{
	if (SearchSlotRange.Y == INDEX_NONE) SearchSlotRange.Y = InventorySlotList.Num() - 1;

	if (SearchSlotRange.X == INDEX_NONE) SearchSlotRange.X = 0;

	if (SearchSlotRange.X < 0 || SearchSlotRange.Y >= InventorySlotList.Num()) return false;

	for (SearchSlotRange.X; SearchSlotRange.X <= SearchSlotRange.Y; SearchSlotRange.X++)
	{
		if (InventorySlotList[SearchSlotRange.X].ItemTag.MatchesTag(ItemTag))
		{
			ItemIndexList.Add(SearchSlotRange.X);
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
