// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JsonObjectWrapper.h"
#include "GameplayTagContainer.h"
#include "LFPInventoryComponent.generated.h"


USTRUCT(BlueprintType)
struct FLFPInventoryItemData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInventorySlotData")
		FString AdditionalData = FString("");

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInventorySlotData")
		FGameplayTag ItemTag = FGameplayTag::EmptyTag;

	UPROPERTY()
		TArray<FName> LockList;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnItemEvent, const FLFPInventoryItemData&, ItemData, const int32, SlotIndex, const FString&, EventInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnSwapItemEvent, const FLFPInventoryItemData&, FromItemData, const int32, FromSlot, const FLFPInventoryItemData&, ToItemData, const int32, ToSlot, const FString&, EventInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemFunctionEvent);


UCLASS( Blueprintable, ClassGroup=(LFPlugin), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Serialize(FArchive& Ar) override;

public: // Function

	/** 
	* Add / Set item to inventory 
	* @param ItemData Item Data to add to inventory or equipment
	* @param SlotIndex inventory or equipment slot index within max value
	* @param EventInfo Info to pass to trigger event
	* @return Index of the item in the Inventory
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		int32 AddItem(const FLFPInventoryItemData& ItemData, int32 SlotIndex = -1, const FString EventInfo = FString("None"));

	/** 
	* Remove item to inventory
	* @param RemovedItemData Item Data that got removed from inventory or equipment
	* @param SlotIndex inventory or equipment slot index within max value
	* @param EventInfo Info to pass to trigger event
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool RemoveItem(FLFPInventoryItemData& RemovedItemData, const int32 SlotIndex, const FString EventInfo = FString("None"));

	/**
	* Swap Item In Inventory
	* @param FromSlot From other inventory slot
	* @param ToSlot To this inventory slot
	* @param EventInfo Info to pass to trigger event
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool SwapItem(const int32 FromSlot, const int32 ToSlot, const FString EventInfo = FString("None"));

	/**
	* Swap Item From Other Inventory
	* @param Other Take item on this inventory
	* @param FromSlot From other inventory slot
	* @param ToSlot To this inventory slot
	* @param EventInfo Info to pass to trigger event
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool SwapItemFromOther(ULFPInventoryComponent* Other, const int32 FromSlot, const int32 ToSlot, const FString EventInfo = FString("None"));

	/**
	* Sort inventory using sort function
	* @param EventInfo Info to pass to trigger event
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		void SortInventory(const FString EventInfo = FString("None"));

	/**
	* Trim inventory to make it more compact
	* @param FromSlot Trim from this index to lower index
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		void TrimInventorySlotList(const int32 FromSlot);

	/**
	* Prevent item operation like remove, swap and sort
	* @param SlotIndex Item index to lock
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool AddItemLock(const int32 SlotIndex, const FName LockName);

	/**
	* Recover item operation like remove, swap and sort
	* @param SlotIndex Item index to lock
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool RemoveItemLock(const int32 SlotIndex, const FName LockName);

public: // Event

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPInventoryComponent | Event")
		bool CanAddItem(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const;
		virtual bool CanAddItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const { return GetInventorySlot(SlotIndex).ItemTag == FGameplayTag::EmptyTag; }

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPInventoryComponent | Event")
		bool CanRemoveItem(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const;
		virtual bool CanRemoveItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const { return true; }

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPInventoryComponent | Event")
		bool CanSwapItem(const int32 FromSlot, const int32 ToSlot, const FString& EventInfo) const;
		virtual bool CanSwapItem_Implementation(const int32 FromSlot, const int32 ToSlot, const FString& EventInfo) const { return true; }



	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPInventoryComponent | Event")
		bool IsItemSortPriorityHigher(const FLFPInventoryItemData& ItemDataA, const FLFPInventoryItemData& ItemDataB, const FString& EventInfo) const;
		virtual bool IsItemSortPriorityHigher_Implementation(const FLFPInventoryItemData& ItemDataA, const FLFPInventoryItemData& ItemDataB, const FString& EventInfo) const { return false; }

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPInventoryComponent | Event")
		bool IsInventorySlotAvailable(const int32& SlotIndex, const FLFPInventoryItemData& SlotItem, const FLFPInventoryItemData& ForItem) const;
		virtual bool IsInventorySlotAvailable_Implementation(const int32& SlotIndex, const FLFPInventoryItemData& SlotItem, const FLFPInventoryItemData& ForItem) const { return InventorySlotList[SlotIndex].ItemTag == FGameplayTag::EmptyTag; }



	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Event")
		void OnInventorySlotRep(const TArray<FLFPInventoryItemData>& OldValue);
		virtual void OnInventorySlotRep_Implementation(const TArray<FLFPInventoryItemData>& OldValue) { }

public: // Delegate

	UPROPERTY(BlueprintAssignable, BlueprintAuthorityOnly, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnItemEvent OnAddItem;

	UPROPERTY(BlueprintAssignable, BlueprintAuthorityOnly, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnItemEvent OnRemoveItem;

	UPROPERTY(BlueprintAssignable, BlueprintAuthorityOnly, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnSwapItemEvent OnSwapItem;

	UPROPERTY(BlueprintAssignable, BlueprintAuthorityOnly, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnItemFunctionEvent OnItemSortEvent;

public: // Valid Checker

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		FORCEINLINE bool IsInventorySlotIndexValid(const int32 Index) const { return InventorySlotList.IsValidIndex(Index); };

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		FORCEINLINE bool IsInventorySlotIndexLock(const int32 Index) const { return IsInventorySlotIndexValid(Index) && InventorySlotList[Index].LockList.IsEmpty() == false; };

public: // Getter

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		int32 FindAvailableInventorySlot(int32 SlotIndex, const FLFPInventoryItemData& ForItem, int32 EndIndex = -1) const;

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		bool FindItemListWithItemTag(TArray<int32>& ItemIndexList, const FGameplayTag ItemTag, const int32 StartIndex = 0, int32 EndIndex = -1) const;

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		FLFPInventoryItemData GetInventorySlot(const int32 Index) const { return IsInventorySlotIndexValid(Index) ? InventorySlotList[Index] : FLFPInventoryItemData(); };

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		const TArray<FLFPInventoryItemData>& GetInventorySlotList() const { return InventorySlotList; };

public: // Setter

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Setter")
		bool SetAdditionalData(const int32 Index, const FString NewAdditionalData);

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "LFPInventoryComponent | Setting", meta = (ClampMin = "0"))
		int32 MaxInventorySlotAmount = 16;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "LFPInventoryComponent | Setting", meta = (ClampMin = "0"))
		int32 StartInventorySlotIndex = 0;

protected:

	UPROPERTY(VisibleAnywhere, Replicated, Savegame, ReplicatedUsing = OnInventorySlotRep, Category = "LFPInventoryComponent | Cache")
		TArray<FLFPInventoryItemData> InventorySlotList;
};
