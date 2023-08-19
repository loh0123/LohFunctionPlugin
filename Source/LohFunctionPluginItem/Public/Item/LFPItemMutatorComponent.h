#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Item/LFPInventoryComponent.h"
#include "LFPItemMutatorComponent.generated.h"


USTRUCT(BlueprintType)
struct FLFPItemMutatorQueueData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "LFPItemMutatorQueueData")
		FName RecipeName = FName("");

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPItemMutatorQueueData")
		TArray<FLFPInventoryItemData> ItemConsumeList = TArray<FLFPInventoryItemData>();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPItemMutatorQueueData")
		FName ItemSearchSlotName = FName("All");

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPItemMutatorQueueData")
		TArray<FLFPInventoryItemData> ItemProduceList = TArray<FLFPInventoryItemData>();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPItemMutatorQueueData")
		float MaxDelay = -1.0f;

	UPROPERTY(BlueprintReadOnly, Category = "LFPItemMutatorQueueData")
		float Delay = -1.0f;

	UPROPERTY(BlueprintReadOnly, Category = "LFPItemMutatorQueueData")
		bool bIsPause = false;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMutatorItemEvent, const int32, QueueIndex, const FLFPItemMutatorQueueData, QueueData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMutatorFunctionEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnProcessMutatorItemEvent, const FLFPItemMutatorQueueData&, ItemData, const bool, bReturnConsume);


/**
* Crafting System
* Has a crafting queue
* Can connect inventory
*/

UCLASS( Blueprintable, ClassGroup = (LFPlugin), meta = (BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGINITEM_API ULFPItemMutatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPItemMutatorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public: // Function

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPItemMutatorComponent | Function")
		bool SetInventoryComponent(ULFPInventoryComponent* Component);
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPItemMutatorComponent | Function")
		bool AddItemToQueue(const FName RecipeName);
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPItemMutatorComponent | Function")
		bool RemoveItemFromQueue(const int32 QueueIndex);
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPItemMutatorComponent | Function")
		bool PauseItemCountdown(const int32 QueueIndex);
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPItemMutatorComponent | Function")
		bool ResumeItemCountdown(const int32 QueueIndex);
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPItemMutatorComponent | Function")
		bool DeleteItemFromQueue(const int32 QueueIndex);
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPItemMutatorComponent | Function")
		void ClearItemQueue(const bool bDeleteItem = false);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPItemMutatorComponent | Function")
		void ProcessItemQueue(const float ConsumeDelayAmount);


	UFUNCTION()
		void ProcessItem(FLFPItemMutatorQueueData& ItemData, const bool bReturnConsume = false, const int32 QueueIndex = -1);
	
public: // Event

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPItemMutatorComponent | Event")
		bool CanAddItemToQueue(const FLFPItemMutatorQueueData& ItemMutatorQueueData) const;
		virtual bool CanAddItemToQueue_Implementation(const FLFPItemMutatorQueueData& ItemMutatorQueueData) const { return true; }
	 
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPItemMutatorComponent | Event")
		bool CanRemoveItemFromQueue(const FLFPItemMutatorQueueData& ItemMutatorQueueData) const;
		virtual bool CanRemoveItemFromQueue_Implementation(const FLFPItemMutatorQueueData& ItemMutatorQueueData) const { return true; }
	
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPItemMutatorComponent | Event")
		bool CanPauseItemCountdown(const FLFPItemMutatorQueueData& ItemMutatorQueueData) const;
		virtual bool CanPauseItemCountdown_Implementation(const FLFPItemMutatorQueueData& ItemMutatorQueueData) const { return true; }
	
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPItemMutatorComponent | Event")
		bool CanResumeItemCountdown(const FLFPItemMutatorQueueData& ItemMutatorQueueData) const;
		virtual bool CanResumeItemCountdown_Implementation(const FLFPItemMutatorQueueData& ItemMutatorQueueData) const { return true; }
	
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPItemMutatorComponent | Event")
		bool CanDeleteItemFromQueue(const FLFPItemMutatorQueueData& ItemMutatorQueueData) const;
		virtual bool CanDeleteItemFromQueue_Implementation(const FLFPItemMutatorQueueData& ItemMutatorQueueData) const { return true; }


	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPItemMutatorComponent | Event")
		bool ConsumeItemFromInventory(const FLFPItemMutatorQueueData& ItemMutatorQueueData);
		virtual bool ConsumeItemFromInventory_Implementation(const FLFPItemMutatorQueueData& ItemMutatorQueueData);


	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemMutatorComponent | Event")
		void OnMutatorQueueRep(const TArray<FLFPItemMutatorQueueData>& OldValue);
		virtual void OnMutatorQueueRep_Implementation(const TArray<FLFPItemMutatorQueueData>& OldValue) { }

public: // Valid Checker

	UFUNCTION(BlueprintPure, Category = "LFPItemMutatorComponent | Getter")
		FORCEINLINE bool IsQueueIndexValid(const int32 Index) const { return MutatorQueue.IsValidIndex(Index); };

public: // Getter

	UFUNCTION(BlueprintPure, Category = "LFPItemMutatorComponent | Function")
		FLFPItemMutatorQueueData GetQueueItem(const int32 QueueIndex) const { return IsQueueIndexValid(QueueIndex) ? MutatorQueue[QueueIndex] : FLFPItemMutatorQueueData(); }
	
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPItemMutatorComponent | Function")
		bool GetItemRecipe(const FName RecipeName, FLFPItemMutatorQueueData& RecipeData) const;
		virtual bool GetItemRecipe_Implementation(const FName RecipeName, FLFPItemMutatorQueueData& RecipeData) const { return false; }

public: // Delegate

	UPROPERTY(BlueprintAssignable, BlueprintAuthorityOnly, BlueprintReadWrite, Category = "LFPItemMutatorComponent | Delegate")
		FOnMutatorItemEvent OnAddItemToQueue;

	UPROPERTY(BlueprintAssignable, BlueprintAuthorityOnly, BlueprintReadWrite, Category = "LFPItemMutatorComponent | Delegate")
		FOnMutatorItemEvent OnRemoveItemFromQueue;

	UPROPERTY(BlueprintAssignable, BlueprintAuthorityOnly, BlueprintReadWrite, Category = "LFPItemMutatorComponent | Delegate")
		FOnMutatorItemEvent OnPauseItemCountdown;

	UPROPERTY(BlueprintAssignable, BlueprintAuthorityOnly, BlueprintReadWrite, Category = "LFPItemMutatorComponent | Delegate")
		FOnMutatorItemEvent OnResumeItemCountdown;

	UPROPERTY(BlueprintAssignable, BlueprintAuthorityOnly, BlueprintReadWrite, Category = "LFPItemMutatorComponent | Delegate")
		FOnMutatorItemEvent OnDeleteItemFromQueue;

	UPROPERTY(BlueprintAssignable, BlueprintAuthorityOnly, BlueprintReadWrite, Category = "LFPItemMutatorComponent | Delegate")
		FOnMutatorFunctionEvent OnClearItemQueue;

	UPROPERTY(BlueprintAssignable, BlueprintAuthorityOnly, BlueprintReadWrite, Category = "LFPItemMutatorComponent | Delegate")
		FOnProcessMutatorItemEvent OnProcessItem;

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "LFPItemMutatorComponent | Setting")
		bool bAutoSetup = true;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "LFPItemMutatorComponent | Setting", meta = (ClampMin = "0"))
		int32 MaxQueueAmount = 5;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "LFPItemMutatorComponent | Setting", meta = (ClampMin = "0"))
		int32 QueueProcessAmount = 1;

	/* Process non delay item without adding to queue */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "LFPItemMutatorComponent | Setting")
		bool bInstanceProcess = false;

	/* Process queue item on tick automatic */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "LFPItemMutatorComponent | Setting")
		bool bProcessQueueOnTick = true;

protected:

	UPROPERTY(VisibleAnywhere, Replicated, Savegame, ReplicatedUsing = OnMutatorQueueRep, Category = "LFPItemMutatorComponent | Cache")
		TArray<FLFPItemMutatorQueueData> MutatorQueue;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Savegame, Category = "LFPItemMutatorComponent | Cache")
		ULFPInventoryComponent* InventoryComponent = nullptr;

};
