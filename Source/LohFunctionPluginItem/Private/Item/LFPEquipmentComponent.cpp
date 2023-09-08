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
	DOREPLIFETIME_CONDITION_NOTIFY(ULFPEquipmentComponent, EquipmentSlotList, COND_None, REPNOTIFY_Always);
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
}

void ULFPEquipmentComponent::SetInventoryComponent(ULFPInventoryComponent* Component)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return; // Prevent this function to run on client

	SetInventoryComponent_Internal(InventoryComponent, Component);

	return;
}

void ULFPEquipmentComponent::SetInventoryComponent_Internal(ULFPInventoryComponent* OldComponent, ULFPInventoryComponent* NewComponent)
{
	if (IsValid(OldComponent))
	{
		OldComponent->OnUpdateItem.RemoveDynamic(this, &ULFPEquipmentComponent::OnInventoryUpdateItem);

		OldComponent->CheckComponentList.Remove(this);

		ClearEquipmentSlot("SetInventoryComponent");
	}

	InventoryComponent = NewComponent;

	if (IsValid(NewComponent))
	{
		NewComponent->OnUpdateItem.AddDynamic(this, &ULFPEquipmentComponent::OnInventoryUpdateItem);

		NewComponent->CheckComponentList.Add(this);

		for (const auto& Config : EquipmentSlotConfigList)
		{
			AddEquipmentSlotName(Config.SlotName, Config.bIsActive, Config.bIsLock, "SetInventoryComponent");
		}
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

	if (InventoryComponent->FindInventorySlotWithName(SlotIndexList, InventorySlotName) == false)
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

	if (EquipmentSlotList.Contains(InventorySlotIndex))
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPEquipmentComponent : AddEquipmentSlot InventorySlotIndex is already exist"));

		return false;
	}

	const auto& CurrentItemData = InventoryComponent->GetInventorySlot(InventorySlotIndex);

	if (CurrentItemData.HasItem() && CanEquipItem(CurrentItemData, EquipmentSlotList.Num(), InventorySlotIndex, EventInfo) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPEquipmentComponent : AddEquipmentSlot InventorySlotIndex Item Cant Equip"));

		return false;
	}

	EquipmentSlotList.Add(FLFPEquipmentSlotData(InventorySlotIndex, bIsSlotActive, bIsSlotLock));

	OnInventoryUpdateItem(FLFPInventoryItemData(), CurrentItemData, InventorySlotIndex, EventInfo);

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

	const int32 EquipmentIndex = EquipmentSlotList.Find(InventorySlotIndex);

	if (EquipmentIndex == INDEX_NONE)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPEquipmentComponent : RemoveEquipmentSlot InventorySlotIndex is not exist"));

		return false;
	}

	const auto& CurrentItemData = InventoryComponent->GetInventorySlot(InventorySlotIndex);

	if (CurrentItemData.HasItem() && CanUnequipItem(CurrentItemData, EquipmentIndex, InventorySlotIndex, EventInfo) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPEquipmentComponent : RemoveEquipmentSlot InventorySlotIndex Item Cant Unequip"));

		return false;
	}

	OnInventoryUpdateItem(CurrentItemData, FLFPInventoryItemData(), InventorySlotIndex, EventInfo);

	EquipmentSlotList.RemoveAt(EquipmentIndex);

	return true;
}

void ULFPEquipmentComponent::ClearEquipmentSlot(const FString EventInfo)
{
	if (IsValid(InventoryComponent) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : ClearEquipmentSlot InventoryComponent is not valid"));

		return;
	}

	bool bIsComplete = true;

	while (EquipmentSlotList.IsEmpty() == false)
	{
		const int32 InvSlotIndex = EquipmentSlotList.Last().SlotIndex;
		const auto& CurrentItemData = InventoryComponent->GetInventorySlot(InvSlotIndex);

		if (CurrentItemData.HasItem() && CanUnequipItem(CurrentItemData, EquipmentSlotList.Num() - 1, InvSlotIndex, EventInfo) == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("ULFPEquipmentComponent : ClearEquipmentSlot InventorySlotIndex Item Cant Unequip But Forced"));
		}

		OnInventoryUpdateItem(CurrentItemData, FLFPInventoryItemData(), InvSlotIndex, EventInfo);

		EquipmentSlotList.RemoveAt(EquipmentSlotList.Num() - 1, 1, false);
	}

	EquipmentSlotList.Shrink();

	return;
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

		if (InventoryComponent->SwapItem(InventorySlotIndex, "All", EquipmentSlot.SlotIndex, "All", EventInfo)) return true;
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

	return InventoryComponent->SwapItem(EquipmentSlotList[EquipmentSlotIndex].SlotIndex, "All", INDEX_NONE, Slotname, EventInfo);
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

void ULFPEquipmentComponent::OnInventoryUpdateItem(const FLFPInventoryItemData& OldItemData, const FLFPInventoryItemData& NewItemData, const int32 SlotIndex, const FString& EventInfo)
{
	int32 EquipmentSlotIndex = INDEX_NONE;

	FindEquipmentSlotIndex(SlotIndex, EquipmentSlotIndex);

	if (EquipmentSlotIndex == INDEX_NONE) return;

	if (OldItemData.IsItemEqual(NewItemData) == false)
	{
		if (OldItemData.HasItem())
		{
			OnUnequipItem.Broadcast(OldItemData, EquipmentSlotIndex, SlotIndex, EventInfo);
		}

		if (NewItemData.HasItem())
		{
			OnEquipItem.Broadcast(NewItemData, EquipmentSlotIndex, SlotIndex, EventInfo);
		}
	}
}

bool ULFPEquipmentComponent::CanInventoryAddItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const
{
	int32 EquipmentSlotIndex = INDEX_NONE;

	FindEquipmentSlotIndex(SlotIndex, EquipmentSlotIndex);

	/* Slot is not an equipment slot */
	if (EquipmentSlotIndex == INDEX_NONE) return true;

	return CanEquipItem(ItemData, EquipmentSlotIndex, SlotIndex, EventInfo);
}

bool ULFPEquipmentComponent::CanInventoryRemoveItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const
{
	int32 EquipmentSlotIndex = INDEX_NONE;

	FindEquipmentSlotIndex(SlotIndex, EquipmentSlotIndex);

	/* Slot is not an equipment slot */
	if (EquipmentSlotIndex == INDEX_NONE) return true;

	return CanUnequipItem(ItemData, EquipmentSlotIndex, SlotIndex, EventInfo);
}

bool ULFPEquipmentComponent::CanInventorySwapItem_Implementation(const FLFPInventoryItemData& FromItemData, const int32 FromSlot, const FLFPInventoryItemData& ToItemData, const int32 ToSlot, const FString& EventInfo) const
{
	int32 EquipmentSlotIndexA = INDEX_NONE;
	int32 EquipmentSlotIndexB = INDEX_NONE;

	FindEquipmentSlotIndex(FromSlot, EquipmentSlotIndexA);
	FindEquipmentSlotIndex(ToSlot, EquipmentSlotIndexB);

	if (EquipmentSlotIndexA != INDEX_NONE)
	{
		if (FromItemData.HasItem() && CanUnequipItem(FromItemData, EquipmentSlotIndexA, FromSlot, EventInfo) == false) return false;
		if (ToItemData.HasItem() && CanEquipItem(ToItemData, EquipmentSlotIndexA, ToSlot, EventInfo) == false) return false;
	}

	if (EquipmentSlotIndexB != INDEX_NONE)
	{
		if (ToItemData.HasItem() && CanUnequipItem(ToItemData, EquipmentSlotIndexB, ToSlot, EventInfo) == false) return false;
		if (FromItemData.HasItem() && CanEquipItem(FromItemData, EquipmentSlotIndexB, FromSlot, EventInfo) == false) return false;
	}

	return true;
}

FLFPEquipmentSlotData ULFPEquipmentComponent::FindEquipmentSlotIndex(const int32 InventorySlotIndex, int32& EquipmentIndex) const
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
			EquipmentIndex = EquipmentSlotIndex;
			
			return EquipmentSlotList[EquipmentSlotIndex];
		}
	}

	return INDEX_NONE;
}

void ULFPEquipmentComponent::OnInventoryComponentRep_Implementation(ULFPInventoryComponent* OldValue)
{
	SetInventoryComponent_Internal(OldValue, InventoryComponent);
}

void ULFPEquipmentComponent::OnEquipmentSlotListRep_Implementation(TArray<FLFPEquipmentSlotData>& OldValue)
{
	if (IsValid(InventoryComponent) == false)
	{
		return;
	}

	for (const FLFPEquipmentSlotData& SlotData : OldValue)
	{
		if (EquipmentSlotList.Contains(SlotData))
		{
			continue;
		}

		const auto& CurrentItemData = InventoryComponent->GetInventorySlot(SlotData.SlotIndex);

		OnInventoryUpdateItem(CurrentItemData, FLFPInventoryItemData(), SlotData.SlotIndex, "OnEquipmentSlotListRep");
	}

	for (const FLFPEquipmentSlotData& SlotData : EquipmentSlotList)
	{
		if (OldValue.Contains(SlotData))
		{
			continue;
		}

		const auto& CurrentItemData = InventoryComponent->GetInventorySlot(SlotData.SlotIndex);

		OnInventoryUpdateItem(FLFPInventoryItemData(), CurrentItemData, SlotData.SlotIndex, "OnEquipmentSlotListRep");
	}
}
