// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

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

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInventorySlotData")
		FJsonObjectWrapper MetaData = FJsonObjectWrapper();

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInventorySlotData")
		FName ItemName = FName("");

public:

	static const FLFPInventoryItemData EmptyInventoryItemData;

public:

	FORCEINLINE const FName& GetName() const
	{
		return ItemName;
	}

	FORCEINLINE	bool HasItem() const
	{
		return ItemName.IsNone() == false;
	}

	FORCEINLINE	bool IsEmpty() const
	{
		return ItemName.IsNone();
	}

	FORCEINLINE	bool IsItemEqual(const FLFPInventoryItemData& Other) const
	{
		return ItemName == Other.GetName();
	}

	FORCEINLINE	bool IsItemEqual(const FName& Other) const
	{
		return ItemName == Other;
	}

public:

	FORCEINLINE	FLFPInventoryItemData Copy() const
	{
		FLFPInventoryItemData CopyData;

		CopyData.ItemName = ItemName;

		CopyData.MetaData.JsonObjectFromString(MetaData.JsonString);

		return CopyData;
	}

	FORCEINLINE	bool operator==(const FLFPInventoryItemData& NewData) const
	{
		return ItemName == NewData.ItemName && MetaData.JsonString == NewData.MetaData.JsonString;
	}

	FORCEINLINE	bool operator!=(const FLFPInventoryItemData& NewData) const
	{
		return ItemName != NewData.ItemName || MetaData.JsonString != NewData.MetaData.JsonString;
	}


	friend FArchive& operator<<(FArchive& Ar, FLFPInventoryItemData& Data)
	{
		Ar << Data.MetaData.JsonString << Data.ItemName;

		Data.MetaData.PostSerialize(Ar);

		return Ar;
	}
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnItemEvent, const FLFPInventoryItemData&, ItemData, const int32, SlotIndex, const FString&, EventInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnUpdateItemEvent, const FLFPInventoryItemData&, OldItemData, const FLFPInventoryItemData&, NewItemData, const int32, SlotIndex, const FString&, EventInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnSwapItemEvent, const FLFPInventoryItemData&, FromItemData, const int32, FromSlot, const FLFPInventoryItemData&, ToItemData, const int32, ToSlot, const FString&, EventInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemFunctionEvent);


UCLASS(Blueprintable, ClassGroup = (LFPlugin), meta = (BlueprintSpawnableComponent))
class LOHFUNCTIONPLUGINITEM_API ULFPInventoryComponent : public UActorComponent
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

protected:

	UFUNCTION()
		FORCEINLINE void BroadcastItemEvent(const int32 SlotIndex, const FLFPInventoryItemData& OldItemData, const FLFPInventoryItemData& NewItemData, const FString& EventInfo) const;

public: // Function

	/**
	* Add item to inventory
	* @param ItemData Item Data to add to inventory or equipment
	* @param SlotIndex Index on where the item has been added or update and what is leave of the item added
	* @param SlotName What Slot Are Use On This Function
	* @param EventInfo Info to pass to trigger event
	* @return Some item has been added to inventory
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool AddItem(UPARAM(ref) FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FName Slotname = FName("All"), const FString EventInfo = FString("None"));

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool AddItemList(UPARAM(ref) TArray<FLFPInventoryItemData>& ItemDataList, const FName Slotname = FName("All"), const FString EventInfo = FString("None"));

	/**
	* Remove item From inventory
	* @param ItemData Item Data that got removed from inventory or equipment
	* @param SlotIndex Index on where the item has been added or update and what is leave of the item removed
	* @param SlotName What Slot Are Use On This Function
	* @param EventInfo Info to pass to trigger event
	* @return Some item has been Removed from inventory
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool RemoveItem(UPARAM(ref) FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FName Slotname = FName("All"), const FString EventInfo = FString("None"));

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool RemoveItemList(UPARAM(ref) TArray<FLFPInventoryItemData>& ItemData, const FName Slotname = FName("All"), const FString EventInfo = FString("None"));

	/**
	* Remove All item From inventory
	* @param SlotName What Slot Are Use On This Function
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		void ClearInventory(const FName SlotName = FName("All"), const FString EventInfo = FString("None"));

	/**
	* Swap Item In Inventory
	* @param FromSlot From other inventory slot
	* @param ToSlot To this inventory slot
	* @param EventInfo Info to pass to trigger event
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool SwapItem(const int32 FromSlotIndex, const FName FromSlotName = FName("All"), const int32 ToSlotIndex = -1, const FName ToSlotName = FName("All"), const FString EventInfo = FString("None"));

	/**
	* Transfer Item From To Inventory
	* @param ToInventory Take item on this inventory
	* @param FromSlot From other inventory slot
	* @param ToSlot To this inventory slot
	* @param EventInfo Info to pass to trigger event
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool TransferItem(ULFPInventoryComponent* ToInventory, const int32 FromSlotIndex, const FName FromSlotName = FName("All"), const int32 ToSlotIndex = -1, const FName ToSlotName = FName("All"), const FString EventInfo = FString("None"));

	/**
	* Sort inventory using sort function
	* @param EventInfo Info to pass to trigger event
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		void SortInventory(const FName Slotname = FName("All"), const FString EventInfo = FString("None"));

	/**
	* Trim inventory to make it more compact
	* @param FromSlot Trim from this index to lower index
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		void TrimInventorySlotList();


public: // Event

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPInventoryComponent | Event")
		bool CanAddItem(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const;
	virtual bool CanAddItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPInventoryComponent | Event")
		bool CanRemoveItem(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const;
	virtual bool CanRemoveItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPInventoryComponent | Event")
		bool CanSwapItem(const FLFPInventoryItemData& FromItemData, const int32 FromSlot, const FLFPInventoryItemData& ToItemData, const int32 ToSlot, const FString& EventInfo) const;
	virtual bool CanSwapItem_Implementation(const FLFPInventoryItemData& FromItemData, const int32 FromSlot, const FLFPInventoryItemData& ToItemData, const int32 ToSlot, const FString& EventInfo) const;


	/**
	* @param CurrentItemData The Item Currently On The Slot Under Process
	* @param AddItemData The Item That Need To Be Add
	* @param SlotIndex What Index This Slot In Inventory
	* @param EventInfo Info to pass to trigger event
	* @return Is The Process Completed And Stop Iteracte Next Slot
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Event")
		bool ProcessAddItem(UPARAM(ref) FLFPInventoryItemData& CurrentItemData, UPARAM(ref) FLFPInventoryItemData& AddItemData, const int32 SlotIndex, const FString& EventInfo) const;
	virtual bool ProcessAddItem_Implementation(UPARAM(ref) FLFPInventoryItemData& CurrentItemData, UPARAM(ref) FLFPInventoryItemData& AddItemData, const int32 SlotIndex, const FString& EventInfo) const { CurrentItemData = AddItemData; return true; }

	/**
	* @param CurrentItemData The Item Currently On The Slot Under Process
	* @param RemoveItemData The Item That Need To Be Remove
	* @param SlotIndex What Index This Slot In Inventory
	* @param EventInfo Info to pass to trigger event
	* @return Is The Process Completed And Stop Iteracte Next Slot
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Event")
		bool ProcessRemoveItem(UPARAM(ref) FLFPInventoryItemData& CurrentItemData, UPARAM(ref) FLFPInventoryItemData& RemoveItemData, const int32 SlotIndex, const FString& EventInfo) const;
	virtual bool ProcessRemoveItem_Implementation(UPARAM(ref) FLFPInventoryItemData& CurrentItemData, UPARAM(ref) FLFPInventoryItemData& RemoveItemData, const int32 SlotIndex, const FString& EventInfo) const { CurrentItemData = FLFPInventoryItemData::EmptyInventoryItemData; return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Event")
		bool ProcessSwapItem(UPARAM(ref) FLFPInventoryItemData& ItemDataA, const int32 SlotIndexA, UPARAM(ref) FLFPInventoryItemData& ItemDataB, const int32 SlotIndexB, const bool bMultipleSwap, const FString& EventInfo) const;
	virtual bool ProcessSwapItem_Implementation(UPARAM(ref) FLFPInventoryItemData& ItemDataA, const int32 SlotIndexA, UPARAM(ref) FLFPInventoryItemData& ItemDataB, const int32 SlotIndexB, const bool bMultipleSwap, const FString& EventInfo) const { const FLFPInventoryItemData AData = ItemDataA; const FLFPInventoryItemData BData = ItemDataB; ItemDataA = BData; ItemDataB = AData; return true; }


	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPInventoryComponent | Event")
		bool IsItemSortPriorityHigher(const FLFPInventoryItemData& ItemDataA, const FLFPInventoryItemData& ItemDataB, const FString& EventInfo) const;
	virtual bool IsItemSortPriorityHigher_Implementation(const FLFPInventoryItemData& ItemDataA, const FLFPInventoryItemData& ItemDataB, const FString& EventInfo) const { return false; }

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPInventoryComponent | Event")
		bool IsInventorySlotAvailable(const int32& SlotIndex, const FLFPInventoryItemData& SlotItem, const FLFPInventoryItemData& ForItem) const;
	virtual bool IsInventorySlotAvailable_Implementation(const int32& SlotIndex, const FLFPInventoryItemData& SlotItem, const FLFPInventoryItemData& ForItem) const { return SlotItem.IsEmpty(); }

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPInventoryComponent | Event")
		bool IsInventorySlotHasTag(const int32& SlotIndex, const FGameplayTag& SlotTag) const;
	virtual bool IsInventorySlotHasTag_Implementation(const int32& SlotIndex, const FGameplayTag& SlotTag) const { return false; }



	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Event")
		void OnInventorySlotItemListRep(const TArray<FLFPInventoryItemData>& OldValue);
	virtual void OnInventorySlotItemListRep_Implementation(const TArray<FLFPInventoryItemData>& OldValue);

public: // Delegate

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnUpdateItemEvent OnUpdateItem;

	UPROPERTY(BlueprintAssignable, BlueprintAuthorityOnly, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnItemEvent OnAddItem;

	UPROPERTY(BlueprintAssignable, BlueprintAuthorityOnly, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnItemEvent OnRemoveItem;

	UPROPERTY(BlueprintAssignable, BlueprintAuthorityOnly, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnSwapItemEvent OnSwapItem;

	UPROPERTY(BlueprintAssignable, BlueprintAuthorityOnly, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnItemFunctionEvent OnItemSortEvent;

public: // Checker Function

	UPROPERTY() TArray<TObjectPtr<UActorComponent>> CheckComponentList;

public: // Valid Checker

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Valid Checker")
		FORCEINLINE bool IsInventorySlotIndexValid(const int32 Index) const { return InventorySlotItemList.IsValidIndex(Index); };

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Valid Checker")
		FORCEINLINE bool IsInventorySlotItemValid(const int32 Index) const { return GetInventorySlot(Index).HasItem(); };

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Valid Checker")
		FORCEINLINE bool IsInventorySlotItemSame(const int32 IndexA, const int32 IndexB) const { return GetInventorySlot(IndexA).IsItemEqual(GetInventorySlot(IndexB)); };

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Valid Checker")
		FORCEINLINE bool HasInventorySlotName(const FName SlotName) const { return InventorySlotNameList.Contains(SlotName); }

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Valid Checker")
		FORCEINLINE bool IsInventorySlotHasName(const int32 Index, const FName SlotName) const;

public: // Getter

	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Getter")
		bool HaveItemsAtSlotName(const TArray<FLFPInventoryItemData>& ItemList, const FName SlotName) const;

	/** 
	* Find Empty Or Available Inventory Slot
	*/
	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Getter")
		bool FindAvailableInventorySlot(TArray<int32>& SlotList, const FLFPInventoryItemData& ForItem, const FName SlotName) const;

	/** 
	* Find Slot Index Within Slot Name Range
	*/
	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Getter")
		int32 FindInventorySlotOffsetWithName(const FName SlotName, const int32 SlotIndex) const;

	/** 
	* Find Inventory Slot Using Slot Name Defined On (InventorySlotNameList) variable
	* Suitable To Using For Getting Slot Based On Slot Type
	*/
	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Getter")
		bool FindInventorySlotWithName(TArray<int32>& SlotList, const FName SlotName) const;

	/** 
	* Find Items Using Gameplay Tag 
	* Suitable To Using For Getting Item Based On Categorize
	* Please Override (IsInventorySlotHasTag) To Use This Function 
	*/
	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Getter")
		bool FindItemListWithTag(TArray<int32>& SlotList, const FGameplayTag SlotTag, const FName SlotName) const;

	/** 
	* Find Items Using Item Name 
	* Suitable To Using For Getting Multiple Same Item
	*/
	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Getter")
		bool FindItemListWithItemName(TArray<int32>& ItemIndexList, const FName ItemName, const FName SlotName) const;

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		const FLFPInventoryItemData& GetInventorySlot(const int32 Index) const { return IsInventorySlotIndexValid(Index) ? InventorySlotItemList[Index] : FLFPInventoryItemData::EmptyInventoryItemData; };

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		const TArray<FLFPInventoryItemData>& GetInventorySlotList() const { return InventorySlotItemList; };

protected:

	/** How big is this inventory can get ( It can't change runtime ) */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "LFPInventoryComponent | Setting", meta = (ClampMin = "0"))
		int32 MaxInventorySlotAmount = 16;

protected:

	/** Can use this to mark equipment slot and hidden slot ( It can't change runtime ) */
	UPROPERTY(EditDefaultsOnly, Category = "LFPInventoryComponent | Setting")
		TMap<FName, FIntPoint> InventorySlotNameList = TMap<FName, FIntPoint>();

protected:

	UPROPERTY(VisibleAnywhere, Replicated, ReplicatedUsing = OnInventorySlotItemListRep, Category = "LFPInventoryComponent | Cache")
		TArray<FLFPInventoryItemData> InventorySlotItemList;
};
