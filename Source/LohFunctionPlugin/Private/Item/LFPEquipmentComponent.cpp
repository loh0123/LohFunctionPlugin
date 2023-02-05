// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#include "Item/LFPEquipmentComponent.h"
#include "Item/LFPInventoryRelatedInterface.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
ULFPEquipmentComponent::ULFPEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void ULFPEquipmentComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ULFPEquipmentComponent, EquipmentSlotList, COND_None, REPNOTIFY_Always);
}


// Called when the game starts
void ULFPEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(GetOwner()))
	{
		ULFPInventoryComponent* InvComp = ILFPInventoryRelatedInterface::Execute_GetInventoryComponent(GetOwner());

		if (IsValid(InvComp))
		{
			SetInventoryComponent(InvComp);
		}
	}
}

void ULFPEquipmentComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (bUnequipOnEndPlay)
		for (int32 Index = 0; Index < EquipmentSlotList.Num(); Index++)
		{
			if (EquipmentSlotList[Index] != INDEX_NONE) UnequipItem(Index, -1, "EndPlay");
		}

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
		for (int32 Index = 0; Index < EquipmentSlotList.Num(); Index++)
		{
			if (EquipmentSlotList[Index] != INDEX_NONE) OnEquipItem.Broadcast(InventoryComponent->GetInventorySlot(EquipmentSlotList[Index]), Index, EquipmentSlotList[Index], "Serialize");
		}
	}
}

void ULFPEquipmentComponent::SetInventoryComponent(ULFPInventoryComponent* Component)
{
	if (IsValid(InventoryComponent))
	{
		InventoryComponent->OnAddItem.RemoveDynamic(this, &ULFPEquipmentComponent::OnInventoryAddItem);
		InventoryComponent->OnRemoveItem.RemoveDynamic(this, &ULFPEquipmentComponent::OnInventoryRemoveItem);
		InventoryComponent->OnSwapItem.RemoveDynamic(this, &ULFPEquipmentComponent::OnInventorySwapItem);
	}

	InventoryComponent = Component;

	if (IsValid(Component))
	{
		InventoryComponent->OnAddItem.AddDynamic(this, &ULFPEquipmentComponent::OnInventoryAddItem);
		InventoryComponent->OnRemoveItem.AddDynamic(this, &ULFPEquipmentComponent::OnInventoryRemoveItem);
		InventoryComponent->OnSwapItem.AddDynamic(this, &ULFPEquipmentComponent::OnInventorySwapItem);
	}

	return;
}

bool ULFPEquipmentComponent::EquipItem(const int32 EquipmentSlotIndex, const int32 InventorySlotIndex, const int32 ToInventorySlotIndex, const FString EventInfo)
{
	if (IsValid(InventoryComponent) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : EquipItem InventoryComponent is not valid"));

		return false;
	}

	if (InventoryComponent->IsInventorySlotItemValid(InventorySlotIndex) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : EquipItem IsInventorySlotItemValid is not valid"));

		return false;
	}

	if (EquipmentSlotIndex >= MaxEquipmentSlotAmount)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : EquipItem EquipmentSlotIndex is not valid"));

		return false;
	}

	if (CanEquipItem(InventoryComponent->GetInventorySlot(InventorySlotIndex), EquipmentSlotIndex, InventorySlotIndex, EventInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : EquipItem CanEquipItem return false"));

		return false;
	}

	if (GetEquipmentSlot(EquipmentSlotIndex).ItemTag != FGameplayTag::EmptyTag)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : EquipItem EquipmentSlotIndex is currently occupied"));

		return false;
	}

	if (ToInventorySlotIndex >= 0 && InventoryComponent->SwapItem(InventorySlotIndex, ToInventorySlotIndex, EventInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : EquipItem SwapItem return false"));

		return false;
	}

	if (EquipmentSlotList.Num() < EquipmentSlotIndex + 1) EquipmentSlotList.SetNum(EquipmentSlotIndex + 1);

	const int32 UseInvSlot = ToInventorySlotIndex >= 0 ? ToInventorySlotIndex : InventorySlotIndex;

	EquipmentSlotList[EquipmentSlotIndex] = UseInvSlot;

	InventoryComponent->AddItemLock(UseInvSlot, FName("Equipment"));

	OnEquipItem.Broadcast(InventoryComponent->GetInventorySlot(UseInvSlot), EquipmentSlotIndex, UseInvSlot, EventInfo);

	return true;
}

bool ULFPEquipmentComponent::UnequipItem(const int32 EquipmentSlotIndex, const int32 ToInventorySlotIndex, const FString EventInfo)
{
	if (IsValid(InventoryComponent) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : UnequipItem InventoryComponent is not valid"));

		return false;
	}

	if (IsEquipmentSlotItemValid(EquipmentSlotIndex) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : UnequipItem IsEquipmentSlotItemValid return false"));

		return false;
	}

	if (CanUnequipItem(GetEquipmentSlot(EquipmentSlotIndex), EquipmentSlotIndex, EquipmentSlotList[EquipmentSlotIndex], EventInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : UnequipItem CanUnequipItem return false"));

		return false;
	}

	if (InventoryComponent->GetInventorySlot(ToInventorySlotIndex).ItemTag != FGameplayTag::EmptyTag)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : UnequipItem ToInventorySlotIndex is currently occupied"));

		return false;
	}

	InventoryComponent->RemoveItemLock(EquipmentSlotList[EquipmentSlotIndex], FName("Equipment"));

	if (ToInventorySlotIndex >= 0 && InventoryComponent->SwapItem(EquipmentSlotList[EquipmentSlotIndex], ToInventorySlotIndex, EventInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : EquipItem SwapItem return false"));

		InventoryComponent->AddItemLock(EquipmentSlotList[EquipmentSlotIndex], FName("Equipment"));

		return false;
	}

	const int32 InvIndex = ToInventorySlotIndex >= 0 ? ToInventorySlotIndex : EquipmentSlotList[EquipmentSlotIndex];

	EquipmentSlotList[EquipmentSlotIndex] = -1;

	OnUnequipItem.Broadcast(InventoryComponent->GetInventorySlot(InvIndex), EquipmentSlotIndex, InvIndex, EventInfo);

	return true;
}

void ULFPEquipmentComponent::OnInventoryAddItem(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo)
{
}

void ULFPEquipmentComponent::OnInventoryRemoveItem(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo)
{
}

void ULFPEquipmentComponent::OnInventorySwapItem(const FLFPInventoryItemData& FromItemData, const int32 FromSlot, const FLFPInventoryItemData& ToItemData, const int32 ToSlot, const FString& EventInfo)
{
	const int32 ItemAIndex = FindEquipmentSlotIndex(FromSlot);
	const int32 ItemBIndex = FindEquipmentSlotIndex(ToSlot);

	if (ItemAIndex != INDEX_NONE)
	{
		EquipmentSlotList[ItemAIndex] = ToSlot;
	}

	if (ItemBIndex != INDEX_NONE)
	{
		EquipmentSlotList[ItemBIndex] = FromSlot;
	}
}

int32 ULFPEquipmentComponent::FindEquipmentSlotIndex(const int32 InventorySlotIndex) const
{
	if (IsValid(InventoryComponent) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : FindEquipmentSlotIndex InventoryComponent is not valid"));

		return INDEX_NONE;
	}

	if (InventoryComponent->IsInventorySlotItemValid(InventorySlotIndex) == false)
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
