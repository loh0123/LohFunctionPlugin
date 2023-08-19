#include "Item/LFPEquipmentComponent.h"
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

	DOREPLIFETIME_CONDITION_NOTIFY(ULFPEquipmentComponent, InventoryComponent, COND_None, REPNOTIFY_Always);
}


// Called when the game starts
void ULFPEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(GetOwner()) && bAutoSetup)
	{
		ULFPInventoryComponent* InvComp = GetOwner()->FindComponentByClass<ULFPInventoryComponent>();

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
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return; // Prevent this function to run on client

	if (IsValid(InventoryComponent))
	{
		InventoryComponent->OnUpdateItem.RemoveDynamic(this, &ULFPEquipmentComponent::OnInventoryUpdateItem);

		InventoryComponent->CheckComponentList.Remove(this);
	}

	InventoryComponent = Component;

	if (IsValid(Component))
	{
		InventoryComponent->OnUpdateItem.AddDynamic(this, &ULFPEquipmentComponent::OnInventoryUpdateItem);

		InventoryComponent->CheckComponentList.Add(this);
		
		RunEquipOnAllSlot();
	}

	return;
}

bool ULFPEquipmentComponent::AddEquipmentSlotName(const FName InventorySlotName, const bool bIsSlotActive, const bool bIsSlotLock, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (IsValid(InventoryComponent) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : AddEquipmentSlotName InventoryComponent is not valid"));

		return false;
	}

	if (InventoryComponent->HasInventorySlotName(InventorySlotName) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : AddEquipmentSlotName InventorySlotName is not valid"));

		return false;
	}

	TArray<int32> SlotIndexList;

	if (InventoryComponent->FindInventorySlotWithName(SlotIndexList, InventorySlotName, EventInfo) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : AddEquipmentSlotName FindInventorySlotWithName return false"));

		return false;
	}

	bool bHasAllSuccess = true;

	for (const int32 SlotIndex : SlotIndexList)
	{
		if (AddEquipmentSlot(SlotIndex, bIsSlotActive, bIsSlotLock, EventInfo) == false)
		{
			bHasAllSuccess = false;
		}
	}

	return bHasAllSuccess;
}

bool ULFPEquipmentComponent::AddEquipmentSlot(const int32 InventorySlotIndex, const bool bIsSlotActive, const bool bIsSlotLock, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

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

	const auto& CurrentItemData = InventoryComponent->GetInventorySlot(InventorySlotIndex);

	if (CurrentItemData.ItemName.IsNone() == false && CanEquipItem(CurrentItemData, EquipmentSlotList.Num(), InventorySlotIndex, EventInfo) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPEquipmentComponent : AddEquipmentSlot InventorySlotIndex Item Cant Equip"));

		return false;
	}

	const int32 EquipmentSlotIndex = EquipmentSlotList.Add(FLFPEquipmentSlotData(InventorySlotIndex, bIsSlotActive, bIsSlotLock));

	OnInventoryUpdateItem(FLFPInventoryItemData(), CurrentItemData, EquipmentSlotIndex, EventInfo);

	return true;
}

bool ULFPEquipmentComponent::RemoveEquipmentSlot(const int32 InventorySlotIndex, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (IsValid(InventoryComponent) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : RemoveEquipmentSlot InventoryComponent is not valid"));

		return false;
	}

	if (InventoryComponent->IsInventorySlotItemValid(InventorySlotIndex) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : RemoveEquipmentSlot IsInventorySlotItemValid return false"));

		return false;
	}

	const int32 EquipmentIndex = EquipmentSlotList.Find(InventorySlotIndex);

	if (EquipmentIndex == INDEX_NONE)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPEquipmentComponent : RemoveEquipmentSlot InventorySlotIndex is not exist"));

		return false;
	}

	const auto& CurrentItemData = InventoryComponent->GetInventorySlot(InventorySlotIndex);

	if (CurrentItemData.ItemName.IsNone() == false && CanUnequipItem(CurrentItemData, EquipmentIndex, InventorySlotIndex, EventInfo) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPEquipmentComponent : RemoveEquipmentSlot InventorySlotIndex Item Cant Unequip"));

		return false;
	}

	OnEquipItem.Broadcast(InventoryComponent->GetInventorySlot(InventorySlotIndex), EquipmentIndex, InventorySlotIndex, EventInfo);

	OnInventoryUpdateItem(CurrentItemData, FLFPInventoryItemData(), EquipmentIndex, EventInfo);

	EquipmentSlotList.RemoveAt(EquipmentIndex);

	return true;
}

bool ULFPEquipmentComponent::TryEquipItem(const int32 InventorySlotIndex, const bool bToActiveSlotOnly, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (IsValid(InventoryComponent) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : TryEquipItem InventoryComponent is not valid"));

		return false;
	}

	if (InventoryComponent->IsInventorySlotItemValid(InventorySlotIndex) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPEquipmentComponent : TryEquipItem InventorySlotIndex is empty"));

		return false;
	}

	for (const auto& EquipmentSlot : EquipmentSlotList)
	{
		if ((bToActiveSlotOnly == false) && (EquipmentSlot.bIsActive == false)) continue;

		if (InventoryComponent->SwapItem(InventorySlotIndex, EquipmentSlot.SlotIndex, EventInfo)) return true;
	}

	UE_LOG(LogTemp, Display, TEXT("ULFPEquipmentComponent : TryEquipItem No equipment slot available for this item"));

	return false;
}

bool ULFPEquipmentComponent::TryUnequipItem(const int32 EquipmentSlotIndex, const FName Slotname, const FString EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (IsValid(InventoryComponent) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : TryUnequipItem InventoryComponent is not valid"));

		return false;
	}

	if (IsEquipmentSlotIndexValid(EquipmentSlotIndex) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : TryUnequipItem EquipmentSlotIndex is not valid"));

		return false;
	}

	if (InventoryComponent->IsInventorySlotItemValid(EquipmentSlotList[EquipmentSlotIndex].SlotIndex) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : TryUnequipItem EquipmentSlotIndex is Empty"));

		return false;
	}

	return InventoryComponent->SwapItemToAvailable(EquipmentSlotList[EquipmentSlotIndex].SlotIndex, Slotname, EventInfo);
}

bool ULFPEquipmentComponent::SetEquipmentSlotActive(const int32 EquipmentSlotIndex, const bool bIsSlotActive, const FString& EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (IsEquipmentSlotIndexValid(EquipmentSlotIndex) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : SetEquipmentSlotActive EquipmentSlotIndex is not valid"));

		return false;
	}

	if (EquipmentSlotList[EquipmentSlotIndex].bIsActive != bIsSlotActive)
	{
		const auto& EquipmentData = GetEquipmentSlot(EquipmentSlotIndex);

		if (InventoryComponent->IsInventorySlotItemValid(EquipmentSlotList[EquipmentSlotIndex].SlotIndex))
		{
			if (bIsSlotActive)
			{
				OnEquipItem.Broadcast(EquipmentData, EquipmentSlotIndex, EquipmentSlotList[EquipmentSlotIndex].SlotIndex, EventInfo);
			}
			else
			{
				OnUnequipItem.Broadcast(EquipmentData, EquipmentSlotIndex, EquipmentSlotList[EquipmentSlotIndex].SlotIndex, EventInfo);
			}
		}

		EquipmentSlotList[EquipmentSlotIndex].bIsActive = bIsSlotActive;

		OnItemActiveChanged.Broadcast(EquipmentData, EquipmentSlotIndex, EquipmentSlotList[EquipmentSlotIndex].SlotIndex, EquipmentSlotList[EquipmentSlotIndex].bIsActive, EventInfo);
	}

	return true;
}

bool ULFPEquipmentComponent::SetEquipmentSlotLock(const int32 EquipmentSlotIndex, const bool bIsSlotLock, const FString& EventInfo)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (IsEquipmentSlotIndexValid(EquipmentSlotIndex) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : SetEquipmentSlotLock EquipmentSlotIndex is not valid"));

		return false;
	}

	if (EquipmentSlotList[EquipmentSlotIndex].bIsLock != bIsSlotLock)
	{
		const auto& EquipmentData = GetEquipmentSlot(EquipmentSlotIndex);

		EquipmentSlotList[EquipmentSlotIndex].bIsLock = bIsSlotLock;

		OnItemLockChanged.Broadcast(EquipmentData, EquipmentSlotIndex, EquipmentSlotList[EquipmentSlotIndex].SlotIndex, EquipmentSlotList[EquipmentSlotIndex].bIsLock, EventInfo);
	}

	return true;
}

void ULFPEquipmentComponent::RunEquipOnAllSlot(const FString& EventInfo) const
{
	if (IsValid(InventoryComponent) == false) return;

	int32 Index = 0;

	for (const auto& EquipmentSlot : EquipmentSlotList)
	{
		if (EquipmentSlot.bIsActive == false) continue;

		if (InventoryComponent->GetInventorySlot(EquipmentSlot.SlotIndex).ItemName.IsNone()) continue;

		OnEquipItem.Broadcast(InventoryComponent->GetInventorySlot(EquipmentSlot.SlotIndex), Index++, EquipmentSlot.SlotIndex, EventInfo);
	}
}

void ULFPEquipmentComponent::OnInventoryUpdateItem(const FLFPInventoryItemData& OldItemData, const FLFPInventoryItemData& NewItemData, const int32 SlotIndex, const FString& EventInfo)
{
	const auto EquipmentSlotIndex = FindEquipmentSlotIndex(SlotIndex);

	if (EquipmentSlotIndex == INDEX_NONE) return;

	if (OldItemData != NewItemData)
	{
		if (OldItemData.ItemName.IsNone() == false)
		{
			OnUnequipItem.Broadcast(OldItemData, EquipmentSlotIndex.SlotIndex, SlotIndex, EventInfo);
		}

		if (NewItemData.ItemName.IsNone() == false)
		{
			OnEquipItem.Broadcast(NewItemData, EquipmentSlotIndex.SlotIndex, SlotIndex, EventInfo);
		}
	}
}

bool ULFPEquipmentComponent::CanInventoryAddItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const
{
	const auto EquipmentSlotIndex = FindEquipmentSlotIndex(SlotIndex);

	/* Slot is not an equipment slot */
	if (EquipmentSlotIndex == INDEX_NONE) return true;

	return CanEquipItem(ItemData, EquipmentSlotIndex.SlotIndex, SlotIndex, EventInfo);
}

bool ULFPEquipmentComponent::CanInventoryRemoveItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const
{
	const auto EquipmentSlotIndex = FindEquipmentSlotIndex(SlotIndex);

	/* Slot is not an equipment slot */
	if (EquipmentSlotIndex == INDEX_NONE) return true;

	return CanUnequipItem(ItemData, EquipmentSlotIndex.SlotIndex, SlotIndex, EventInfo);
}

bool ULFPEquipmentComponent::CanInventorySwapItem_Implementation(const FLFPInventoryItemData& FromItemData, const int32 FromSlot, const FLFPInventoryItemData& ToItemData, const int32 ToSlot, const FString& EventInfo) const
{
	const auto EquipmentSlotIndexA = FindEquipmentSlotIndex(FromSlot);
	const auto EquipmentSlotIndexB = FindEquipmentSlotIndex(ToSlot);

	if (EquipmentSlotIndexA != INDEX_NONE)
	{
		if ((FromItemData.ItemName.IsNone() == false) && CanUnequipItem(FromItemData, EquipmentSlotIndexA.SlotIndex, FromSlot, EventInfo) == false) return false;
		if ((ToItemData.ItemName.IsNone() == false) && CanEquipItem(ToItemData, EquipmentSlotIndexA.SlotIndex, ToSlot, EventInfo) == false) return false;
	}

	if (EquipmentSlotIndexB != INDEX_NONE)
	{
		if ((ToItemData.ItemName.IsNone() == false) && CanUnequipItem(ToItemData, EquipmentSlotIndexB.SlotIndex, ToSlot, EventInfo) == false) return false;
		if ((FromItemData.ItemName.IsNone() == false) && CanEquipItem(FromItemData, EquipmentSlotIndexB.SlotIndex, FromSlot, EventInfo) == false) return false;
	}

	return true;
}

FLFPEquipmentSlotData ULFPEquipmentComponent::FindEquipmentSlotIndex(const int32 InventorySlotIndex) const
{
	if (IsValid(InventoryComponent) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : FindEquipmentSlotIndex InventoryComponent is not valid"));

		return INDEX_NONE;
	}

	for (int32 EquipmentSlotIndex = 0; EquipmentSlotIndex < EquipmentSlotList.Num(); EquipmentSlotIndex++)
	{
		if (InventorySlotIndex == EquipmentSlotList[EquipmentSlotIndex].SlotIndex)
		{
			return EquipmentSlotList[EquipmentSlotIndex];
		}
	}

	return INDEX_NONE;
}

void ULFPEquipmentComponent::OnInventoryComponentRep_Implementation(ULFPInventoryComponent* OldValue)
{
	if (IsValid(OldValue))
	{
		OldValue->OnUpdateItem.RemoveDynamic(this, &ULFPEquipmentComponent::OnInventoryUpdateItem);
	
		OldValue->CheckComponentList.Remove(this);
	}

	if (IsValid(InventoryComponent))
	{
		InventoryComponent->OnUpdateItem.AddDynamic(this, &ULFPEquipmentComponent::OnInventoryUpdateItem);

		InventoryComponent->CheckComponentList.Add(this);

		RunEquipOnAllSlot();
	}
}
