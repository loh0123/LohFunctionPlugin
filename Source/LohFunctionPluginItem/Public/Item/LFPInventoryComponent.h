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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInventorySlotData")
		FJsonObjectWrapper MetaData = FJsonObjectWrapper();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInventorySlotData")
		FName ItemName = FName("");


	static const FLFPInventoryItemData EmptyInventoryItemData;

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

USTRUCT(BlueprintType)
struct FLFPInventoryItemIndexData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInventoryItemIndexList")
		FName ItemName = FName("");

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInventoryItemIndexList")
		int32 ItemIndex = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInventoryItemIndexList")
		TMap<int32, FLFPInventoryItemData> InventoryChangeMap = TMap<int32, FLFPInventoryItemData>();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInventoryItemIndexList")
		FLFPInventoryItemData LeaveItemData = FLFPInventoryItemData();
};

USTRUCT(BlueprintType)
struct FLFPInventorySlotName
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInventorySlotName")
		TArray<FIntPoint> SlotRangeList = TArray<FIntPoint>();
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
	* Add / Set item to inventory
	* @param ItemData Item Data to add to inventory or equipment
	* @param ItemIndexData Index on where the item has been added or update and what is leave of the item added
	* @param StartSlot Start location to place item (Use -1 to auto)
	* @param EndSlot End location to place item (Use -1 to auto)
	* @param EventInfo Info to pass to trigger event
	* @return Some item has been added to inventory
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool AddItem(FLFPInventoryItemData ItemData, FLFPInventoryItemIndexData& ItemIndexData, const int32 StartSlot = -1, const int32 EndSlot = -1, const FString EventInfo = FString("None"));

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool AddItemList(const TArray<FLFPInventoryItemData>& ItemDataList, TArray<FLFPInventoryItemIndexData>& ItemIndexList, const TArray<FIntPoint>& SearchSlotRangeList, const FString EventInfo = FString("None"));

	/**
	* Remove item From inventory
	* @param ItemData Item Data that got removed from inventory or equipment
	* @param ItemIndexData Index on where the item has been added or update and what is leave of the item removed
	* @param StartSlot Start location to place item (Use -1 to auto)
	* @param EndSlot End location to place item (Use -1 to auto)
	* @param bForce Ignore lock item rule and can remove item
	* @param bCheckAllRemove return true only if all item is remove
	* @param EventInfo Info to pass to trigger event
	* @return Some item has been Removed from inventory
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool RemoveItem(FLFPInventoryItemData ItemData, FLFPInventoryItemIndexData& ItemIndexData, const int32 StartSlot = -1, const int32 EndSlot = -1, const bool bForce = false, const bool bCheckAllRemove = false, const FString EventInfo = FString("None"));

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool RemoveItemList(const TArray<FLFPInventoryItemData>& ItemData, TArray<FLFPInventoryItemIndexData>& ItemIndexList, const TArray<FIntPoint>& SearchSlotRangeList, const bool bForce = false, const bool bCheckAllRemove = false, const FString EventInfo = FString("None"));

	/**
	* Remove All item From inventory
	* @param bForce Ignore lock item rule and can remove item
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		void ClearInventory(const bool bForce = false, const FString EventInfo = FString("None"));

	/**
	* Swap Item In Inventory
	* @param FromSlot From other inventory slot
	* @param ToSlot To this inventory slot
	* @param EventInfo Info to pass to trigger event
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool SwapItem(const int32 FromSlot, const int32 ToSlot, const FString EventInfo = FString("None"));

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool SwapItemToAvailable(const int32 FromSlot, const FString EventInfo = FString("None"));

	/**
	* Transfer Item From To Inventory
	* @param ToInventory Take item on this inventory
	* @param FromSlot From other inventory slot
	* @param ToSlot To this inventory slot
	* @param EventInfo Info to pass to trigger event
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool TransferItem(ULFPInventoryComponent* ToInventory, const int32 FromSlot, const int32 ToSlot, const FString EventInfo = FString("None"));

	/**
	* Sort inventory using sort function
	* @param EventInfo Info to pass to trigger event
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		void SortInventory(const FIntPoint SortRange, const FString EventInfo = FString("None"));

	/**
	* Trim inventory to make it more compact
	* @param FromSlot Trim from this index to lower index
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		void TrimInventorySlotList(const int32 FromSlot);


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


	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Event")
		bool ProcessAddItem(UPARAM(ref) FLFPInventoryItemData& CurrentItemData, UPARAM(ref) FLFPInventoryItemData& AddItemData, const int32 SlotIndex, const FString& EventInfo) const;
		virtual bool ProcessAddItem_Implementation(UPARAM(ref) FLFPInventoryItemData& CurrentItemData, UPARAM(ref) FLFPInventoryItemData& AddItemData, const int32 SlotIndex, const FString& EventInfo) const { CurrentItemData = AddItemData; return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Event")
		bool ProcessRemoveItem(UPARAM(ref) FLFPInventoryItemData& CurrentItemData, UPARAM(ref) FLFPInventoryItemData& RemoveItemData, const int32 SlotIndex, const FString& EventInfo) const;
		virtual bool ProcessRemoveItem_Implementation(UPARAM(ref) FLFPInventoryItemData& CurrentItemData, UPARAM(ref) FLFPInventoryItemData& RemoveItemData, const int32 SlotIndex, const FString& EventInfo) const { CurrentItemData = FLFPInventoryItemData::EmptyInventoryItemData; return true; }

	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Event")
		void ProcessSwapItem(UPARAM(ref) FLFPInventoryItemData& ItemDataA, const int32 SlotIndexA, UPARAM(ref) FLFPInventoryItemData& ItemDataB, const int32 SlotIndexB, const FString& EventInfo) const;
	virtual void ProcessSwapItem_Implementation(UPARAM(ref) FLFPInventoryItemData& ItemDataA, const int32 SlotIndexA, UPARAM(ref) FLFPInventoryItemData& ItemDataB, const int32 SlotIndexB, const FString& EventInfo) const { FLFPInventoryItemData AData = ItemDataA; FLFPInventoryItemData BData = ItemDataB; ItemDataA = BData; ItemDataB = AData; }



	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPInventoryComponent | Event")
		bool IsItemSortPriorityHigher(const FLFPInventoryItemData& ItemDataA, const FLFPInventoryItemData& ItemDataB, const FString& EventInfo) const;
	virtual bool IsItemSortPriorityHigher_Implementation(const FLFPInventoryItemData& ItemDataA, const FLFPInventoryItemData& ItemDataB, const FString& EventInfo) const { return false; }

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPInventoryComponent | Event")
		bool IsInventorySlotAvailable(const int32& SlotIndex, const FLFPInventoryItemData& SlotItem, const FLFPInventoryItemData& ForItem) const;
	virtual bool IsInventorySlotAvailable_Implementation(const int32& SlotIndex, const FLFPInventoryItemData& SlotItem, const FLFPInventoryItemData& ForItem) const { return true; }



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
		FORCEINLINE bool IsInventorySlotItemValid(const int32 Index) const { return GetInventorySlot(Index).ItemName.IsNone() == false; };

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Valid Checker")
		FORCEINLINE bool IsInventorySlotItemSame(const int32 IndexA, const int32 IndexB) const { return GetInventorySlot(IndexA).ItemName == GetInventorySlot(IndexB).ItemName; };

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Valid Checker")
		FORCEINLINE bool HasInventorySlotName(const FName SlotName) const { return InventorySlotNameList.Contains(SlotName); }

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Valid Checker")
		FORCEINLINE bool IsInventorySlotHasName(const int32 Index, const FName SlotName) const;

public: // Getter

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		bool FindAvailableInventorySlot(TArray<int32>& AvailableSlotList, const FLFPInventoryItemData& ForItem, int32 StartSlot = -1, int32 EndSlot = -1, const FString EventInfo = FString("None")) const;

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		bool FindInventorySlotWithName(TArray<int32>& AvailableSlotList, const FName SlotName, int32 StartSlot = -1, int32 EndSlot = -1, const FString EventInfo = FString("None")) const;

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		bool FindItemListWithItemName(TArray<int32>& ItemIndexList, const FName ItemName, int32 StartSlot = -1, int32 EndSlot = -1) const;

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		const FLFPInventoryItemData& GetInventorySlot(const int32 Index) const { return IsInventorySlotIndexValid(Index) ? InventorySlotItemList[Index] : FLFPInventoryItemData::EmptyInventoryItemData; };

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		const TArray<FLFPInventoryItemData>& GetInventorySlotList() const { return InventorySlotItemList; };

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "LFPInventoryComponent | Setting", meta = (ClampMin = "0"))
		int32 MaxInventorySlotAmount = 16;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "LFPInventoryComponent | Setting")
		TMap<FName, FLFPInventorySlotName> InventorySlotNameList = TMap<FName, FLFPInventorySlotName>();

protected:

	UPROPERTY(VisibleAnywhere, Replicated, ReplicatedUsing = OnInventorySlotItemListRep, Category = "LFPInventoryComponent | Cache")
		TArray<FLFPInventoryItemData> InventorySlotItemList;
};
