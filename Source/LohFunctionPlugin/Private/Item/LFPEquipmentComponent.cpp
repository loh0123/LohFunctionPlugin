// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#include "Item/LFPEquipmentComponent.h"
#include "Item/LFPItemComponentInterface.h"
//#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
ULFPEquipmentComponent::ULFPEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

//void ULFPEquipmentComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	//DOREPLIFETIME_CONDITION_NOTIFY(ULFPEquipmentComponent, EquipmentSlotList, COND_None, REPNOTIFY_Always);
//}


// Called when the game starts
void ULFPEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(GetOwner()) && GetOwner()->Implements<ULFPItemComponentInterface>())
	{
		ULFPInventoryComponent* InvComp = ILFPItemComponentInterface::Execute_GetInventoryComponent(GetOwner());

		if (IsValid(InvComp))
		{
			SetInventoryComponent(InvComp);
		}
	}
}

void ULFPEquipmentComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	SetInventoryComponent(nullptr);
}


// Called every frame
void ULFPEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULFPEquipmentComponent::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsLoading())
	{
		RunEquipOnAllSlot();
	}
}

void ULFPEquipmentComponent::SetInventoryComponent(ULFPInventoryComponent* Component)
{
	if (IsValid(InventoryComponent))
	{
		InventoryComponent->OnAddItem.RemoveDynamic(this, &ULFPEquipmentComponent::OnInventoryAddItem);
		InventoryComponent->OnRemoveItem.RemoveDynamic(this, &ULFPEquipmentComponent::OnInventoryRemoveItem);
		InventoryComponent->OnSwapItem.RemoveDynamic(this, &ULFPEquipmentComponent::OnInventorySwapItem);

		InventoryComponent->CheckComponentList.Remove(this);
	}

	InventoryComponent = Component;

	if (IsValid(Component))
	{
		InventoryComponent->OnAddItem.AddDynamic(this, &ULFPEquipmentComponent::OnInventoryAddItem);
		InventoryComponent->OnRemoveItem.AddDynamic(this, &ULFPEquipmentComponent::OnInventoryRemoveItem);
		InventoryComponent->OnSwapItem.AddDynamic(this, &ULFPEquipmentComponent::OnInventorySwapItem);

		InventoryComponent->CheckComponentList.Add(this);
		
		RunEquipOnAllSlot();
	}

	return;
}

bool ULFPEquipmentComponent::AddEquipmentSlot(const int32 InventorySlotIndex, const FString EventInfo)
{
	if (IsValid(InventoryComponent) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : AddEquipmentSlot InventoryComponent is not valid"));

		return false;
	}

	if (InventoryComponent->IsInventorySlotIndexValid(InventorySlotIndex) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : AddEquipmentSlot InventorySlotIndex is not valid"));

		return false;
	}

	if (EquipmentSlotList.Contains(InventorySlotIndex))
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPEquipmentComponent : AddEquipmentSlot InventorySlotIndex is already exist"));

		return false;
	}

	EquipmentSlotList.Add(InventorySlotIndex);

	if (InventoryComponent->GetInventorySlot(InventorySlotIndex).ItemTag != FGameplayTag::EmptyTag)
	{
		OnEquipItem.Broadcast(InventoryComponent->GetInventorySlot(InventorySlotIndex), EquipmentSlotList.Num() - 1, InventorySlotIndex, EventInfo);
	}

	return true;
}

bool ULFPEquipmentComponent::RemoveEquipmentSlot(const int32 InventorySlotIndex, const FString EventInfo)
{
	if (IsValid(InventoryComponent) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : RemoveEquipmentSlot InventoryComponent is not valid"));

		return false;
	}

	if (InventoryComponent->IsInventorySlotIndexValid(InventorySlotIndex) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : RemoveEquipmentSlot InventorySlotIndex is not valid"));

		return false;
	}

	const int32 EquipmentIndex = EquipmentSlotList.Find(InventorySlotIndex);

	if (EquipmentIndex == INDEX_NONE)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPEquipmentComponent : RemoveEquipmentSlot InventorySlotIndex is not exist"));

		return false;
	}

	EquipmentSlotList.RemoveAt(EquipmentIndex);

	if (InventoryComponent->GetInventorySlot(InventorySlotIndex).ItemTag != FGameplayTag::EmptyTag)
	{
		OnEquipItem.Broadcast(InventoryComponent->GetInventorySlot(InventorySlotIndex), EquipmentIndex, InventorySlotIndex, EventInfo);
	}

	return true;
}

void ULFPEquipmentComponent::RunEquipOnAllSlot() const
{
	if (IsValid(InventoryComponent) == false) return;

	int32 Index = 0;

	for (auto& EquipmentSlot : EquipmentSlotList)
	{
		if (InventoryComponent->GetInventorySlot(EquipmentSlot).ItemTag == FGameplayTag::EmptyTag) continue;

		OnEquipItem.Broadcast(InventoryComponent->GetInventorySlot(EquipmentSlot), Index++, EquipmentSlot, "RunEquipOnAllSlot");
	}
}

void ULFPEquipmentComponent::OnInventoryAddItem(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo)
{
	int32 EquipmentSlotIndex = FindEquipmentSlotIndex(SlotIndex);

	if (EquipmentSlotIndex == INDEX_NONE) return;

	OnEquipItem.Broadcast(ItemData, EquipmentSlotIndex, SlotIndex, EventInfo);
}

void ULFPEquipmentComponent::OnInventoryRemoveItem(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo)
{
	int32 EquipmentSlotIndex = FindEquipmentSlotIndex(SlotIndex);

	if (EquipmentSlotIndex == INDEX_NONE) return;

	OnUnequipItem.Broadcast(ItemData, EquipmentSlotIndex, SlotIndex, EventInfo);
}

void ULFPEquipmentComponent::OnInventorySwapItem(const FLFPInventoryItemData& FromItemData, const int32 FromSlot, const FLFPInventoryItemData& ToItemData, const int32 ToSlot, const FString& EventInfo)
{
	int32 EquipmentSlotIndexA = FindEquipmentSlotIndex(FromSlot);
	int32 EquipmentSlotIndexB = FindEquipmentSlotIndex(ToSlot);

	if (EquipmentSlotIndexA != INDEX_NONE)
	{
		OnUnequipItem.Broadcast(FromItemData, EquipmentSlotIndexA, FromSlot, EventInfo);
		OnEquipItem.Broadcast(ToItemData, EquipmentSlotIndexA, ToSlot, EventInfo);
	}

	if (EquipmentSlotIndexB != INDEX_NONE)
	{
		OnUnequipItem.Broadcast(ToItemData, EquipmentSlotIndexB, ToSlot, EventInfo);
		OnEquipItem.Broadcast(FromItemData, EquipmentSlotIndexB, FromSlot, EventInfo);
	}

	return;
}

bool ULFPEquipmentComponent::CanInventoryAddItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const
{
	int32 EquipmentSlotIndex = FindEquipmentSlotIndex(SlotIndex);

	/* Slot is not an equipment slot */
	if (EquipmentSlotIndex == INDEX_NONE) return true;

	return CanEquipItem(ItemData, EquipmentSlotIndex, SlotIndex, EventInfo);
}

bool ULFPEquipmentComponent::CanInventoryRemoveItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const
{
	int32 EquipmentSlotIndex = FindEquipmentSlotIndex(SlotIndex);

	/* Slot is not an equipment slot */
	if (EquipmentSlotIndex == INDEX_NONE) return true;

	return CanUnequipItem(ItemData, EquipmentSlotIndex, SlotIndex, EventInfo);
}

bool ULFPEquipmentComponent::CanInventorySwapItem_Implementation(const FLFPInventoryItemData& FromItemData, const int32 FromSlot, const FLFPInventoryItemData& ToItemData, const int32 ToSlot, const FString& EventInfo) const
{
	int32 EquipmentSlotIndexA = FindEquipmentSlotIndex(FromSlot);
	int32 EquipmentSlotIndexB = FindEquipmentSlotIndex(ToSlot);

	if (EquipmentSlotIndexA != INDEX_NONE)
	{
		if (FromItemData.ItemTag.IsValid() && CanUnequipItem(FromItemData, EquipmentSlotIndexA, FromSlot, EventInfo) == false) return false;
		if (ToItemData.ItemTag.IsValid() && CanEquipItem(ToItemData, EquipmentSlotIndexA, ToSlot, EventInfo) == false) return false;
	}

	if (EquipmentSlotIndexB != INDEX_NONE)
	{
		if (ToItemData.ItemTag.IsValid() && CanUnequipItem(ToItemData, EquipmentSlotIndexB, ToSlot, EventInfo) == false) return false;
		if (FromItemData.ItemTag.IsValid() && CanEquipItem(FromItemData, EquipmentSlotIndexB, FromSlot, EventInfo) == false) return false;
	}

	return true;
}

int32 ULFPEquipmentComponent::FindEquipmentSlotIndex(const int32 InventorySlotIndex) const
{
	if (IsValid(InventoryComponent) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : FindEquipmentSlotIndex InventoryComponent is not valid"));

		return INDEX_NONE;
	}

	if (InventoryComponent->IsInventorySlotIndexValid(InventorySlotIndex) == false)
	{
		return INDEX_NONE;
	}

	for (int32 EquipmentSlotIndex = 0; EquipmentSlotIndex < EquipmentSlotList.Num(); EquipmentSlotIndex++)
	{
		if (InventorySlotIndex == EquipmentSlotList[EquipmentSlotIndex])
		{
			return EquipmentSlotIndex;
		}
	}

	return INDEX_NONE;
}
