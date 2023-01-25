// Copyright by Loh Zhi Kang


#include "Inventory/LFPEquipmentComponent.h"
#include "Inventory/LFPInventoryRelatedInterface.h"
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

bool ULFPEquipmentComponent::SetInventoryComponent(ULFPInventoryComponent* Component)
{
	InventoryComponent = Component;

	return IsValid(InventoryComponent);
}

bool ULFPEquipmentComponent::EquipItem(const int32 EquipmentSlotIndex, const int32 InventorySlotIndex, const int32 ToInventorySlotIndex, const FString EventInfo)
{
	if (IsValid(InventoryComponent) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : EquipItem InventoryComponent is not valid"));

		return false;
	}

	if (InventoryComponent->IsInventorySlotIndexValid(InventorySlotIndex) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : EquipItem InventorySlotIndex is not valid"));

		return false;
	}

	if (EquipmentSlotIndex >= MaxEquipmentSlotAmount)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : EquipItem EquipmentSlotIndex is not valid"));

		return false;
	}

	if (InventoryComponent->GetInventorySlot(InventorySlotIndex).ItemTag == FGameplayTag::EmptyTag)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : EquipItem InventorySlot ItemData Tag is empty"));

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

	if (IsEquipmentSlotIndexValid(EquipmentSlotIndex) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : UnequipItem EquipmentSlotIndex is not valid"));

		return false;
	}

	if (GetEquipmentSlot(EquipmentSlotIndex).ItemTag == FGameplayTag::EmptyTag)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : UnequipItem EquipmentSlot is empty"));

		return false;
	}

	if (CanUnequipItem(GetEquipmentSlot(EquipmentSlotIndex), EquipmentSlotIndex, EquipmentSlotList[EquipmentSlotIndex], EventInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : UnequipItem CanUnequipItem return false"));

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
