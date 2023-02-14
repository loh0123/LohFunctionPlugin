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
		FGameplayTag ItemTag = FGameplayTag::EmptyTag;


	static const FLFPInventoryItemData EmptyInventoryItemData;
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
		int32 AddItem(FLFPInventoryItemData ItemData, int32 SlotIndex = -1, const FString EventInfo = FString("None"));

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		TArray<int32> AddItemList(const TArray<FLFPInventoryItemData>& ItemDataList, int32 SlotIndex = -1, const FString EventInfo = FString("None"));

	/** 
	* Remove item From inventory
	* @param RemovedItemData Item Data that got removed from inventory or equipment
	* @param SlotIndex inventory or equipment slot index within max value
	* @param bForce Ignore lock item rule and can remove item
	* @param EventInfo Info to pass to trigger event
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool RemoveItem(FLFPInventoryItemData& RemovedItemData, const int32 SlotIndex, const bool bForce = false, const FString EventInfo = FString("None"));

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		void RemoveItemList(TArray<FLFPInventoryItemData>& RemovedItemDataList, const TArray<int32> SlotIndexList, const bool bForce = false, const FString EventInfo = FString("None"));

	/** 
	* Remove All item From inventory
	* @param bForce Ignore lock item rule and can remove item
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		void ClearInventory(const int32 StartSlotIndex = -1, const bool bForce = false, const FString EventInfo = FString("None"));

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
			void ProcessAddItem(UPARAM(ref) FLFPInventoryItemData& CurrentItemData, UPARAM(ref) FLFPInventoryItemData& NewItemData, const int32 SlotIndex, const FString& EventInfo) const;
		virtual void ProcessAddItem_Implementation(UPARAM(ref) FLFPInventoryItemData& CurrentItemData, UPARAM(ref) FLFPInventoryItemData& NewItemData, const int32 SlotIndex, const FString& EventInfo) const { CurrentItemData = NewItemData; NewItemData = FLFPInventoryItemData::EmptyInventoryItemData; }

		UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Event")
			void ProcessRemoveItem(UPARAM(ref) FLFPInventoryItemData& CurrentItemData, const int32 SlotIndex, const FString& EventInfo) const;
		virtual void ProcessRemoveItem_Implementation(UPARAM(ref) FLFPInventoryItemData& CurrentItemData, const int32 SlotIndex, const FString& EventInfo) const { CurrentItemData = FLFPInventoryItemData::EmptyInventoryItemData; }

		UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Event")
			void ProcessSwapItem(UPARAM(ref) FLFPInventoryItemData& ItemDataA, const int32 SlotIndexA, UPARAM(ref) FLFPInventoryItemData& ItemDataB, const int32 SlotIndexB, const FString& EventInfo) const;
		virtual void ProcessSwapItem_Implementation(UPARAM(ref) FLFPInventoryItemData& ItemDataA, const int32 SlotIndexA, UPARAM(ref) FLFPInventoryItemData& ItemDataB, const int32 SlotIndexB, const FString& EventInfo) const { FLFPInventoryItemData AData = ItemDataA; FLFPInventoryItemData BData = ItemDataB; ItemDataA = BData; ItemDataB = AData; }



	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPInventoryComponent | Event")
		bool IsItemSortPriorityHigher(const FLFPInventoryItemData& ItemDataA, const FLFPInventoryItemData& ItemDataB, const FString& EventInfo) const;
		virtual bool IsItemSortPriorityHigher_Implementation(const FLFPInventoryItemData& ItemDataA, const FLFPInventoryItemData& ItemDataB, const FString& EventInfo) const { return false; }

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPInventoryComponent | Event")
		bool IsInventorySlotAvailable(const int32& SlotIndex, const FLFPInventoryItemData& SlotItem, const FLFPInventoryItemData& ForItem) const;
		virtual bool IsInventorySlotAvailable_Implementation(const int32& SlotIndex, const FLFPInventoryItemData& SlotItem, const FLFPInventoryItemData& ForItem) const { return GetInventorySlot(SlotIndex).ItemTag == FGameplayTag::EmptyTag; }



	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Event")
		void OnInventorySlotRep(const TArray<FLFPInventoryItemData>& OldValue);
		virtual void OnInventorySlotRep_Implementation(const TArray<FLFPInventoryItemData>& OldValue) { }

public: // Delegate

	UPROPERTY(BlueprintAssignable, BlueprintAuthorityOnly, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnItemEvent OnUpdateItem;

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
		FORCEINLINE bool IsInventorySlotIndexValid(const int32 Index) const { return InventorySlotList.IsValidIndex(Index); };

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Valid Checker")
		FORCEINLINE bool IsInventorySlotItemValid(const int32 Index) const { return GetInventorySlot(Index).ItemTag.IsValid(); };

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Valid Checker")
		FORCEINLINE bool IsInventorySlotItemSame(const int32 IndexA, const int32 IndexB) const { return GetInventorySlot(IndexA).ItemTag == GetInventorySlot(IndexB).ItemTag; };

public: // Getter

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		int32 FindAddableInventorySlot(int32 SlotIndex, const FLFPInventoryItemData& ForItem, int32 EndIndex = -1, const FString EventInfo = FString("None")) const;

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		bool FindItemListWithItemTag(TArray<int32>& ItemIndexList, const FGameplayTag ItemTag, const int32 StartIndex = 0, int32 EndIndex = -1) const;

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		const FLFPInventoryItemData& GetInventorySlot(const int32 Index) const { return IsInventorySlotIndexValid(Index) ? InventorySlotList[Index] : FLFPInventoryItemData::EmptyInventoryItemData; };

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		const TArray<FLFPInventoryItemData>& GetInventorySlotList() const { return InventorySlotList; };

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "LFPInventoryComponent | Setting", meta = (ClampMin = "0"))
		int32 MaxInventorySlotAmount = 16;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "LFPInventoryComponent | Setting", meta = (ClampMin = "0"))
		int32 StartInventorySlotIndex = 0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "LFPInventoryComponent | Setting")
		TArray<FIntPoint> IgnoreInventorySlotList = TArray<FIntPoint>();

protected:

	UPROPERTY(VisibleAnywhere, Replicated, Savegame, ReplicatedUsing = OnInventorySlotRep, Category = "LFPInventoryComponent | Cache")
		TArray<FLFPInventoryItemData> InventorySlotList;
};
