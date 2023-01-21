// Copyright by Loh Zhi Kang


#include "Inventory/LFPItemMutatorComponent.h"
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

	// ...
	
}


// Called every frame
void ULFPItemMutatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (MutatorQueue.IsEmpty() == false)
	{
		FLFPItemMutatorQueueData& MutatorData = MutatorQueue.Last();

		MutatorData.Delay -= DeltaTime;

		if (MutatorData.Delay <= 0.0f)
		{
			ProcessItem(MutatorData, false, MutatorQueue.Num() - 1);
		}
	}
}

bool ULFPItemMutatorComponent::SetInventoryComponent(ULFPInventoryComponent* Component)
{
	InventoryComponent = Component;

	return IsValid(InventoryComponent);
}

bool ULFPItemMutatorComponent::AddItemToQueue(const FGameplayTag RecipeTag)
{
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

	if (GetItemRecipe(RecipeTag, NewQueueData) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPItemMutatorComponent : AddItemToQueue GetItemRecipe return false"));

		return false;
	}

	if (CanAddItemToQueue(NewQueueData.ItemConsumeList) == false)
	{
		UE_LOG(LogTemp, Display, TEXT("ULFPItemMutatorComponent : AddItemToQueue CanAddItemToQueue return false"));

		return false;
	}

	if (ConsumeItemFromInventory(NewQueueData.ItemConsumeList) == false)
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

		MutatorQueue.Insert(NewQueueData, 0);

		OnAddItemToQueue.Broadcast(RecipeTag);
	}

	return true;
}

bool ULFPItemMutatorComponent::RemoveItemFromQueue(const int32 QueueIndex)
{
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

	ProcessItem(MutatorQueue[QueueIndex], true, QueueIndex);

	OnRemoveItemFromQueue.Broadcast(QueueIndex);

	return true;
}

bool ULFPItemMutatorComponent::PauseItemCountdown(const int32 QueueIndex)
{
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

	OnPauseItemCountdown.Broadcast(QueueIndex);

	return true;
}

bool ULFPItemMutatorComponent::ResumeItemCountdown(const int32 QueueIndex)
{
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

	OnResumeItemCountdown.Broadcast(QueueIndex);

	return true;
}

bool ULFPItemMutatorComponent::DeleteItemFromQueue(const int32 QueueIndex)
{
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

	MutatorQueue.RemoveAt(QueueIndex);

	OnDeleteItemFromQueue.Broadcast(QueueIndex);

	return false;
}

void ULFPItemMutatorComponent::ClearItemQueue(const bool bDeleteItem)
{
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

void ULFPItemMutatorComponent::ProcessItem(const FLFPItemMutatorQueueData& ItemData, const bool bReturnConsume, const int32 QueueIndex)
{
	if (IsValid(InventoryComponent) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("ULFPItemMutatorComponent : ProcessItem InventoryComponent is not valid"));

		return;
	}

	if (bReturnConsume)
	{
		for (const auto& ConsumeItem : ItemData.ItemConsumeList)
		{
			InventoryComponent->AddItem(ConsumeItem, -1, FString("ReturnConsume"));
		}
	}
	else
	{
		for (const auto& ProduceItem : ItemData.ItemProduceList)
		{
			InventoryComponent->AddItem(ProduceItem, -1, FString("ReturnProduce"));
		}
	}

	OnProcessItem.Broadcast(ItemData, bReturnConsume);

	if (IsQueueIndexValid(QueueIndex)) MutatorQueue.RemoveAt(QueueIndex);
}

