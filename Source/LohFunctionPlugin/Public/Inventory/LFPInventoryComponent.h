// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JsonObjectWrapper.h"
#include "LFPInventoryComponent.generated.h"


USTRUCT(BlueprintType)
struct FLFPInventoryItemData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInventorySlotData")
		FString AdditionalData = FString("");

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInventorySlotData")
		FName ItemID = NAME_None;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPInventorySlotData | Cache")
		int32 SyncSlotIndex = INDEX_NONE;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnItemEvent, const FLFPInventoryItemData&, ItemData, const int32, SlotIndex, const FString&, EventInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnSwapItemEvent, const FLFPInventoryItemData&, FromItemData, const int32, FromSlot, const FLFPInventoryItemData&, ToItemData, const int32, ToSlot, const FString&, EventInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemSortEvent);


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

public: // Function

	/** 
	* Add item to inventory 
	* @param ItemData Item Data to add to inventory or equipment
	* @param SlotIndex inventory or equipment slot index within max value
	* @param EventInfo Info to pass to trigger event
	*/
	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Function")
		bool AddItem(const FLFPInventoryItemData& ItemData, int32 SlotIndex = -1, const FString EventInfo = FString("None"));

	/** 
	* Remove item to inventory
	* @param ItemData Item Data that got removed from inventory or equipment
	* @param SlotIndex inventory or equipment slot index within max value
	* @param bEquipItem Remove from equipment slot
	* @param EventInfo Info to pass to trigger event
	*/
	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Function")
		bool RemoveItem(FLFPInventoryItemData& RemovedItemData, const int32 SlotIndex, const bool bIsEquipItem = false, const FString EventInfo = FString("None"));

	/**
	* Equip Item In Inventory
	* @param InventorySlotIndex Inventory slot index to equip
	* @param bSyncSlot Do not remove the item from inventory slot list
	* @param EventInfo Info to pass to trigger event
	*/
	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Function")
		bool EquipItem(const int32 InventorySlotIndex, const int32 EquipmentSlotIndex, const bool bSyncSlot = false, const FString EventInfo = FString("None"));

	/**
	* Unequip Item In Inventory
	* @param EquipmentSlotIndex Equipment slot index to remove
	* @param EventInfo Info to pass to trigger event
	*/
	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Function")
		bool UnequipItem(const int32 EquipmentSlotIndex, const int32 ToInventorySlotIndex = -1, const FString EventInfo = FString("None"));

	/**
	* Swap Item In Inventory
	* @param EventInfo Info to pass to trigger event
	*/
	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Function")
		bool SwapItem(const int32 FromSlot, const int32 ToSlot, const FString EventInfo = FString("None"));

	/**
	* Sort inventory using sort function
	* @param EventInfo Info to pass to trigger event
	*/
	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Function")
		void SortInventory(const FString EventInfo = FString("None"));

	/**
	* Trim inventory to make it more compact
	* @param FromSlot Trim from this index to lower index
	*/
	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Function")
		void TrimInventorySlotList(const int32 FromSlot);

public: // Event

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPInventoryComponent | Event")
		bool CanAddItem(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const;
		virtual bool CanAddItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const { return true; }

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPInventoryComponent | Event")
		bool CanRemoveItem(FLFPInventoryItemData& RemovedItemData, const int32 SlotIndex, const FString& EventInfo) const;
		virtual bool CanRemoveItem_Implementation(FLFPInventoryItemData& RemovedItemData, const int32 SlotIndex, const FString& EventInfo) const { return true; }

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPInventoryComponent | Event")
		bool CanEquipItem(const FLFPInventoryItemData& ItemData, const int32 InventorySlotIndex, const int32 EquipmentSlotIndex, const bool bSyncSlot, const FString& EventInfo) const;
		virtual bool CanEquipItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 InventorySlotIndex, const int32 EquipmentSlotIndex, const bool bSyncSlot, const FString& EventInfo) const { return true; }
	
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPInventoryComponent | Event")
		bool CanUnequipItem(const FLFPInventoryItemData& ItemData, const int32 EquipmentSlotIndex, const FString& EventInfo) const;
		virtual bool CanUnequipItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 EquipmentSlotIndex, const FString& EventInfo) const { return true; }

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPInventoryComponent | Event")
		bool CanSwapItem(const int32 FromSlot, const int32 ToSlot, const FString& EventInfo) const;
		virtual bool CanSwapItem_Implementation(const int32 FromSlot, const int32 ToSlot, const FString& EventInfo) const { return true; }



	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Event")
		bool InventorySortFunction(const FLFPInventoryItemData& ItemDataA, const FLFPInventoryItemData& ItemDataB, const FString& EventInfo) const;
		virtual bool InventorySortFunction_Implementation(const FLFPInventoryItemData& ItemDataA, const FLFPInventoryItemData& ItemDataB, const FString& EventInfo) const { return false; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Event")
		bool IsInventorySlotAvailable(const int32& SlotIndex, const FLFPInventoryItemData& ItemData) const;
		virtual bool IsInventorySlotAvailable_Implementation(const int32& SlotIndex, const FLFPInventoryItemData& ItemData) const { return InventorySlotList[SlotIndex].ItemID == NAME_None; }

public: // Delegate

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnItemEvent OnAddItem;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnItemEvent OnRemoveItem;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnItemEvent OnEquipItem;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnItemEvent OnUnequipItem;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnSwapItemEvent OnSwapItem;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnItemSortEvent OnItemSortEvent;

public: // Valid Checker

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		FORCEINLINE bool IsEquipmentSlotIndexValid(const int32 Index) const { return EquipmentSlotList.IsValidIndex(Index); };

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		FORCEINLINE bool IsInventorySlotIndexValid(const int32 Index) const { return InventorySlotList.IsValidIndex(Index); };

public: // Getter

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		bool GetAvailableInventorySlot(int32& SlotIndex, const FLFPInventoryItemData& ForItem) const;

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		bool GetItemListWithID(TArray<int32>& ItemIndexList, const FName ID, const bool bEquipment = false) const;

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		const FLFPInventoryItemData GetEquipmentSlot(const int32 Index) const { return IsEquipmentSlotIndexValid(Index) ? (EquipmentSlotList[Index].SyncSlotIndex == INDEX_NONE ? EquipmentSlotList[Index] : InventorySlotList[EquipmentSlotList[Index].SyncSlotIndex]) : FLFPInventoryItemData(); };

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		const FLFPInventoryItemData GetInventorySlot(const int32 Index) const { return IsInventorySlotIndexValid(Index) ? InventorySlotList[Index] : FLFPInventoryItemData(); };

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		const TArray<FLFPInventoryItemData>& GetEquipmentSlotList() const { return EquipmentSlotList; };

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		const TArray<FLFPInventoryItemData>& GetInventorySlotList() const { return InventorySlotList; };

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "LFPInventoryComponent | Setting", meta = (ClampMin = "0"))
		int32 MaxEquipmentSlotAmount = 4;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "LFPInventoryComponent | Setting", meta = (ClampMin = "0"))
		int32 MaxInventorySlotAmount = 16;

protected:

	UPROPERTY(VisibleAnywhere, Category = "LFPInventoryComponent | Cache")
		TArray<FLFPInventoryItemData> EquipmentSlotList;

	UPROPERTY(VisibleAnywhere, Category = "LFPInventoryComponent | Cache")
		TArray<FLFPInventoryItemData> InventorySlotList;
};
