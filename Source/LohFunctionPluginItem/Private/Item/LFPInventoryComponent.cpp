// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#include "Item/LFPInventoryComponent.h"
#include "Item/LFPInventoryInterface.h"
#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
ULFPInventoryComponent::ULFPInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULFPInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ULFPInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULFPInventoryComponent::AddItem(const FLFPInventoryChange& ChangeData, const FGameplayTag EventTag)
{
}

void ULFPInventoryComponent::RemoveItem(const FLFPInventoryChange& ChangeData, const FGameplayTag EventTag)
{
}

void ULFPInventoryComponent::SwapItem(const FLFPInventorySwap& SwapData, const FGameplayTag EventTag)
{
}

void ULFPInventoryComponent::SortItem(const FGameplayTag SortTag, const FGameplayTag EventTag)
{
}

void ULFPInventoryComponent::ClearInventory(const FGameplayTagContainer SlotNames, const FGameplayTag EventTag)
{
}

bool ULFPInventoryComponent::ContainItem(const FLFPInventoryItem& ItemData, const FLFPInventoryIndex& InventoryIndex) const
{
	return false;
}

bool ULFPInventoryComponent::ContainItemList(const TArray<FLFPInventoryItem>& ItemDataList, const FLFPInventoryIndex& InventoryIndex, const bool bPartially) const
{
	return false;
}

bool ULFPInventoryComponent::IsSlotAvailable(const FLFPInventoryIndex& InventoryIndex) const
{
	return false;
}

bool ULFPInventoryComponent::IsItemSortPriorityHigherThan(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB) const
{
	return false;
}

bool ULFPInventoryComponent::IsSlotNameValid(const FGameplayTag SlotName) const
{
	return false;
}

bool ULFPInventoryComponent::IsSlotHasCatergorize(const FGameplayTagContainer Catergorizes, const int32 SlotIndex, const FGameplayTag SlotName) const
{
	return false;
}

FLFPInventoryItem ULFPInventoryComponent::GetSlotItem(const int32 SlotIndex, const FGameplayTag SlotName) const
{
	return FLFPInventoryItem();
}

bool ULFPInventoryComponent::FindItemIndexList(TArray<FLFPInventoryIndex>& ItemIndexList, const FLFPInventoryItem& ItemData, const FGameplayTagContainer SlotNames, const FGameplayTagContainer Catergorizes) const
{
	return false;
}

bool ULFPInventoryComponent::FindItemDataList(TArray<FLFPInventoryItem>& ItemIndexList, const FLFPInventoryItem& ItemData, const FGameplayTagContainer SlotNames, const FGameplayTagContainer Catergorizes) const
{
	return false;
}

FJsonObjectWrapper ULFPInventoryComponent::ExportJson(const FGameplayTagContainer SlotNames) const
{
	return FJsonObjectWrapper();
}

bool ULFPInventoryComponent::ImportJson(const FJsonObjectWrapper& JsonData, const FGameplayTagContainer SlotNames)
{
	return false;
}
