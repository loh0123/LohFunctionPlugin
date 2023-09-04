#include "Item/LFPItemMutatorComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
ULFPItemMutatorComponent::ULFPItemMutatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void ULFPItemMutatorComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ULFPItemMutatorComponent, MutatorQueue, COND_None, REPNOTIFY_Always);
}


// Called when the game starts
void ULFPItemMutatorComponent::BeginPlay()
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


// Called every frame
void ULFPItemMutatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bProcessQueueOnTick && MutatorQueue.Num() > 0)
	{
		ProcessItemQueue(DeltaTime);
	}
}

bool ULFPItemMutatorComponent::SetInventoryComponent(ULFPInventoryComponent* Component)
{
	InventoryComponent = Component;

	return IsValid(InventoryComponent);
}

bool ULFPItemMutatorComponent::AddItemToQueue(const FName RecipeName)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (IsValid(InventoryComponent) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPItemMutatorComponent : AddItemToQueue InventoryComponent is not valid"));

		return false;
	}

	if (MutatorQueue.Num() >= MaxQueueAmount)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPItemMutatorComponent : AddItemToQueue MutatorQueue num is over MaxQueueAmount"));

		return false;
	}

	FLFPItemMutatorQueueData NewQueueData = FLFPItemMutatorQueueData();

	if (GetItemRecipe(RecipeName, NewQueueData) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPItemMutatorComponent : AddItemToQueue GetItemRecipe return false"));

		return false;
	}

	NewQueueData.RecipeName = RecipeName;

	if (CanAddItemToQueue(NewQueueData) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPItemMutatorComponent : AddItemToQueue CanAddItemToQueue return false"));

		return false;
	}

	if (ConsumeItemFromInventory(NewQueueData) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPItemMutatorComponent : AddItemToQueue ConsumeItemFromInventory return false"));

		return false;
	}

	if (bInstanceProcess && NewQueueData.MaxDelay < 0.0f)
	{
		ProcessItem(NewQueueData);
	}
	else
	{
		NewQueueData.Delay = NewQueueData.MaxDelay;

		const int32 QueueIndex = MutatorQueue.Add(NewQueueData);

		OnAddItemToQueue.Broadcast(QueueIndex, NewQueueData);
	}

	return true;
}

bool ULFPItemMutatorComponent::RemoveItemFromQueue(const int32 QueueIndex)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (IsValid(InventoryComponent) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPItemMutatorComponent : RemoveItemFromQueue InventoryComponent is not valid"));

		return false;
	}

	if (IsQueueIndexValid(QueueIndex) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPItemMutatorComponent : RemoveItemFromQueue index not valid"));

		return false;
	}

	if (CanRemoveItemFromQueue(MutatorQueue[QueueIndex]) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPItemMutatorComponent : RemoveItemFromQueue CanRemoveItemFromQueue return false"));

		return false;
	}

	FLFPItemMutatorQueueData RemoveQueueData = MutatorQueue[QueueIndex];

	ProcessItem(RemoveQueueData, true, QueueIndex);

	OnRemoveItemFromQueue.Broadcast(QueueIndex, RemoveQueueData);

	return true;
}

bool ULFPItemMutatorComponent::PauseItemCountdown(const int32 QueueIndex)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (IsQueueIndexValid(QueueIndex) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPItemMutatorComponent : PauseItemCountdown index not valid"));

		return false;
	}

	if (CanPauseItemCountdown(MutatorQueue[QueueIndex]) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPItemMutatorComponent : PauseItemCountdown CanPauseItemCountdown return false"));

		return false;
	}

	MutatorQueue[QueueIndex].bIsPause = true;

	OnPauseItemCountdown.Broadcast(QueueIndex, MutatorQueue[QueueIndex]);

	return true;
}

bool ULFPItemMutatorComponent::ResumeItemCountdown(const int32 QueueIndex)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (IsQueueIndexValid(QueueIndex) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPItemMutatorComponent : ResumeItemCountdown index not valid"));

		return false;
	}

	if (CanResumeItemCountdown(MutatorQueue[QueueIndex]) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPItemMutatorComponent : ResumeItemCountdown CanResumeItemCountdown return false"));

		return false;
	}

	MutatorQueue[QueueIndex].bIsPause = false;

	OnResumeItemCountdown.Broadcast(QueueIndex, MutatorQueue[QueueIndex]);

	return true;
}

bool ULFPItemMutatorComponent::DeleteItemFromQueue(const int32 QueueIndex)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return false; // Prevent this function to run on client

	if (IsQueueIndexValid(QueueIndex) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPItemMutatorComponent : DeleteItemFromQueue index not valid"));

		return false;
	}

	if (CanDeleteItemFromQueue(MutatorQueue[QueueIndex]) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPItemMutatorComponent : DeleteItemFromQueue CanDeleteItemFromQueue return false"));

		return false;
	}

	const FLFPItemMutatorQueueData RemoveQueueData = MutatorQueue[QueueIndex];

	MutatorQueue.RemoveAt(QueueIndex);

	OnDeleteItemFromQueue.Broadcast(QueueIndex, RemoveQueueData);

	return false;
}

void ULFPItemMutatorComponent::ClearItemQueue(const bool bDeleteItem)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return; // Prevent this function to run on client

	for (int32 Index = MutatorQueue.Num() - 1; Index >= 0; Index--)
	{
		if (bDeleteItem) 
		{
			DeleteItemFromQueue(Index);
		}
		else
		{
			RemoveItemFromQueue(Index);
		}
	}

	OnClearItemQueue.Broadcast();
}

void ULFPItemMutatorComponent::ProcessItemQueue(const float ConsumeDelayAmount)
{
	if (GetOwner()->GetLocalRole() != ROLE_Authority) return; // Prevent this function to run on client

	for (int32 Index = QueueProcessAmount - 1; Index >= 0 && MutatorQueue.IsValidIndex(Index); Index--)
	{
		FLFPItemMutatorQueueData& MutatorData = MutatorQueue[Index];

		MutatorData.Delay -= ConsumeDelayAmount;

		if (MutatorData.Delay <= 0.0f)
		{
			ProcessItem(MutatorData, false, Index);
		}
	}
}

void ULFPItemMutatorComponent::ProcessItem(FLFPItemMutatorQueueData& ItemData, const bool bReturnConsume, const int32 QueueIndex)
{
	if (IsValid(InventoryComponent) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPItemMutatorComponent : ProcessItem InventoryComponent is not valid"));

		return;
	}

	if (bReturnConsume)
	{
		for (auto& ConsumeItem : ItemData.ItemConsumeList)
		{
			InventoryComponent->AddItem(ConsumeItem, INDEX_NONE, ItemData.ItemSearchSlotName, FString("ReturnConsume"));
		}
	}
	else
	{
		for (auto& ProduceItem : ItemData.ItemProduceList)
		{
			InventoryComponent->AddItem(ProduceItem, INDEX_NONE, ItemData.ItemSearchSlotName, FString("ReturnProduce"));
		}
	}

	OnProcessItem.Broadcast(ItemData, bReturnConsume);

	if (IsQueueIndexValid(QueueIndex)) MutatorQueue.RemoveAt(QueueIndex);
}

bool ULFPItemMutatorComponent::ConsumeItemFromInventory_Implementation(const FLFPItemMutatorQueueData& ItemMutatorQueueData)
{
	if (IsValid(InventoryComponent) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPItemMutatorComponent : ProcessItem InventoryComponent is not valid"));

		return false;
	}

	auto ConsumeList = ItemMutatorQueueData.ItemConsumeList;

	return InventoryComponent->RemoveItemList(ConsumeList, ItemMutatorQueueData.ItemSearchSlotName);
}
