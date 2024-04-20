// Copyright (c) 2023-2024 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JsonObjectWrapper.h"
#include "GameplayTagContainer.h"
#include "LFPItemGameplayTag.h"
#include "LFPItemFunctionLibrary.h"
#include "LFPInventoryComponent.generated.h"

class ULFPItemInventoryFunction;

DECLARE_LOG_CATEGORY_EXTERN(LFPInventoryComponent, Log, All);

//UENUM(BlueprintType)
//enum ELFPInventoryOperation : uint8
//{
//	OnAdd		UMETA(DisplayName = "OnAdd"),
//	OnRemove	UMETA(DisplayName = "OnRemove"),
//	OnSwap      UMETA(DisplayName = "OnSwap")
//};

//USTRUCT()
//struct FLFPInventoryKey
//{
//	GENERATED_BODY()
//
//	FLFPInventoryKey() {}
//
//	FLFPInventoryKey(const int32 NewSlotIndex, const int32 NewSlotNameIndex) : SlotIndex(NewSlotIndex), SlotNameIndex(NewSlotNameIndex) {}
//
//public:
//
//	UPROPERTY()
//	int32 SlotIndex = INDEX_NONE;
//
//	UPROPERTY()
//	int32 SlotNameIndex = INDEX_NONE;
//
//public:
//
//	FORCEINLINE bool IsValid() const { return SlotIndex > INDEX_NONE && SlotNameIndex > INDEX_NONE; }
//};

USTRUCT(BlueprintType)
struct FLFPInventorySearch
{
	GENERATED_BODY()

	FLFPInventorySearch() {}

	FLFPInventorySearch(const FGameplayTag& NewSlotName) : SlotNames(NewSlotName.GetSingleTagContainer()) {}

	FLFPInventorySearch(const FGameplayTagContainer& NewSlotNames) : SlotNames(NewSlotNames) {}

	FLFPInventorySearch(
		const FGameplayTagContainer& NewSlotNames,
		const FGameplayTagContainer& NewCatergorizes,
		const bool NewAnyCatergorizes,
		const bool NewPassOnEmptyIndexCatergorizes
	) 
		: 
		SlotNames(NewSlotNames),
		Catergorizes(NewCatergorizes),
		bAnyCatergorizes(NewAnyCatergorizes),
		bPassOnEmptyIndexCatergorizes(NewPassOnEmptyIndexCatergorizes)
	{}

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default, meta = (Categories = "Item.SlotName"))
	FGameplayTagContainer SlotNames = FGameplayTagContainer::EmptyContainer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	FGameplayTagContainer Catergorizes = FGameplayTagContainer::EmptyContainer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	bool bAnyCatergorizes = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	bool bPassOnEmptyIndexCatergorizes = false;

public:

	FORCEINLINE bool IsValid() const { return SlotNames.IsEmpty() == false; }

	FORCEINLINE bool IsTagMatch(const FGameplayTag& Tag) const { return SlotNames.IsEmpty() ? true : Tag.MatchesAny(SlotNames); }

	FORCEINLINE bool IsCatergorizesMatch(const FGameplayTagContainer& Container) const 
	{ 
		if (bPassOnEmptyIndexCatergorizes && Container.IsEmpty()) return true;
		if (Catergorizes.IsEmpty()) return true; 

		return bAnyCatergorizes ? Container.HasAny(Catergorizes) : Container.HasAll(Catergorizes); 
	}

	FORCEINLINE FString ToString() const { return FString::Printf(TEXT("SlotNames = %s : Catergorizes = %s : AnyCatergorizes = %s"), *SlotNames.ToString(), *Catergorizes.ToString(), bAnyCatergorizes ? TEXT("True") : TEXT("False")); }

	FORCEINLINE	FLFPInventorySearch& operator+=(const FLFPInventorySearch& Other) { SlotNames.AppendTags(Other.SlotNames); return *this; }
};

USTRUCT()
struct FLFPInventoryInternalIndex
{
	GENERATED_BODY()

	FLFPInventoryInternalIndex() {}

	FLFPInventoryInternalIndex(const int32 NewSlotIndex, const int32 NewSlotListIndex) : SlotItemIndex(NewSlotIndex), SlotListIndex(NewSlotListIndex) {}

public:

	UPROPERTY()
	int32 SlotItemIndex = INDEX_NONE;

	UPROPERTY()
	int32 SlotListIndex = INDEX_NONE;

public:

	FORCEINLINE bool IsValid() const { return SlotListIndex > INDEX_NONE && SlotItemIndex > INDEX_NONE; }

	FORCEINLINE	bool operator==(const FLFPInventoryInternalIndex& Other) const { return SlotItemIndex == Other.SlotItemIndex && SlotListIndex == Other.SlotListIndex; }

	FORCEINLINE	bool operator!=(const FLFPInventoryInternalIndex& Other) const { return SlotItemIndex != Other.SlotItemIndex || SlotListIndex != Other.SlotListIndex; }
};

USTRUCT(BlueprintType)
struct FLFPInventoryIndex
{
	GENERATED_BODY()

	FLFPInventoryIndex() {}

	FLFPInventoryIndex(const int32 NewSlotIndex, const FGameplayTag& NewSlotName) : SlotItemIndex(NewSlotIndex), SlotName(NewSlotName) {}

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	int32 SlotItemIndex = INDEX_NONE;

	/* Use For Getting SlotListIndex */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default, meta = (Categories = "Item.SlotName"))
	FGameplayTag SlotName = FGameplayTag::EmptyTag;

public:

	FORCEINLINE bool IsValid() const { return SlotName.IsValid() && SlotItemIndex > INDEX_NONE; }

	FORCEINLINE	bool operator==(const FLFPInventoryIndex& Other) const { return SlotItemIndex == Other.SlotItemIndex && SlotName == Other.SlotName; }

	FORCEINLINE	bool operator!=(const FLFPInventoryIndex& Other) const { return SlotItemIndex != Other.SlotItemIndex || SlotName != Other.SlotName; }

	FORCEINLINE FString ToString() const { return FString::Printf(TEXT("%s | ItemIndex = %d"), *SlotName.ToString(), SlotItemIndex); }
};


USTRUCT(BlueprintType)
struct FLFPInventorySlot
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default, meta = (Categories = "Item.SlotName"))
		FGameplayTag SlotName = FGameplayTag::EmptyTag;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default)
		int32 SlotMaxIndex = INDEX_NONE;

protected:

	UPROPERTY(VisibleAnywhere, Category = Default)
		TArray<FLFPInventoryItem> ItemList = TArray<FLFPInventoryItem>();

public:

	FORCEINLINE bool IsItemDataValid(const int32 Index) const { return ItemList.IsValidIndex(Index) && ItemList[Index].IsValid(); }

	FORCEINLINE bool IsItemIndexValid(const int32 Index) const { return ItemList.IsValidIndex(Index); }

	FORCEINLINE void ReserveItemIndex(const int32 Index)
	{
		check(Index > INDEX_NONE);

		if (ItemList.IsValidIndex(Index) == false)
		{
			ItemList.SetNum(Index + 1);
		}

		return;
	}

	FORCEINLINE int32 GetItemNum() const { return ItemList.Num(); }

	FORCEINLINE int32 GetMaxNum(const int32 ExtraSlot) const { return SlotMaxIndex > INDEX_NONE ? SlotMaxIndex - 1 : GetItemNum() + ExtraSlot; }

public: // Get Item

	FORCEINLINE FLFPInventoryItem& GetItemRef(const int32 Index)
	{
		check(Index > INDEX_NONE);

		ReserveItemIndex(Index);

		return ItemList[Index];
	}

	FORCEINLINE const FLFPInventoryItem& GetItemConst(const int32 Index) const
	{
		if (ItemList.IsValidIndex(Index) == false)
		{
			return FLFPInventoryItem::EmptyItem;
		}

		return ItemList[Index];
	}

public: // List Operation

	FORCEINLINE void ClearEmptyItem()
	{
		while (ItemList.Num() > 0 && ItemList.Last().IsValid() == false)
		{
			ItemList.RemoveAt(ItemList.Num() - 1, 1, false);
		}

		ItemList.Shrink();
	}

	FORCEINLINE void SortItem(const TFunctionRef<bool(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB)> Predicate)
	{
		ItemList.Sort(Predicate);
	}
};

USTRUCT()
struct FLFPInventorySlotList
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = Default)
	TArray<FLFPInventorySlot> SlotList = TArray<FLFPInventorySlot>();

public: // InventoryIndex

	FORCEINLINE FLFPInventoryInternalIndex ToInventoryIndexInternal(const FLFPInventoryIndex& InventoryIndex) const
	{
		for (int32 Index = 0; Index < SlotList.Num(); Index++)
		{
			if (SlotList[Index].SlotName == InventoryIndex.SlotName)
			{
				return FLFPInventoryInternalIndex(InventoryIndex.SlotItemIndex, Index);
			}
		}

		return FLFPInventoryInternalIndex();
	}

	FORCEINLINE	bool IsSlotItemValid(const FLFPInventoryInternalIndex& InventoryIndex) const
	{
		return SlotList.IsValidIndex(InventoryIndex.SlotListIndex) && SlotList[InventoryIndex.SlotListIndex].IsItemDataValid(InventoryIndex.SlotItemIndex);
	}

	FORCEINLINE	bool IsSlotIndexValid(const FLFPInventoryInternalIndex& InventoryIndex) const
	{
		return SlotList.IsValidIndex(InventoryIndex.SlotListIndex) && SlotList[InventoryIndex.SlotListIndex].IsItemIndexValid(InventoryIndex.SlotItemIndex);
	}

public: // Get Slot

	FORCEINLINE const	FLFPInventoryItem& GetSlotItemConst(const FLFPInventoryInternalIndex& InventoryIndex) const
	{
		check(SlotList.IsValidIndex(InventoryIndex.SlotListIndex));

		return SlotList[InventoryIndex.SlotListIndex].GetItemConst(InventoryIndex.SlotItemIndex);
	}

	FORCEINLINE			FLFPInventoryItem& GetSlotItemRef(const FLFPInventoryInternalIndex& InventoryIndex)
	{
		check(SlotList.IsValidIndex(InventoryIndex.SlotListIndex));

		return SlotList[InventoryIndex.SlotListIndex].GetItemRef(InventoryIndex.SlotItemIndex);
	}

public: // Slot Operation

	FORCEINLINE void ReserveItemIndex(const FLFPInventoryInternalIndex& InventoryIndex)
	{
		check(SlotList.IsValidIndex(InventoryIndex.SlotListIndex));
		check(InventoryIndex.SlotItemIndex > INDEX_NONE);

		SlotList[InventoryIndex.SlotListIndex].ReserveItemIndex(InventoryIndex.SlotItemIndex);
	}

	FORCEINLINE void ClearSlotEmptyItem(const int32 SlotListIndex)
	{
		check(SlotList.IsValidIndex(SlotListIndex));

		SlotList[SlotListIndex].ClearEmptyItem();
	}

	FORCEINLINE void SortSlot(const FLFPInventorySearch& InventorySearch, const TFunctionRef<bool(const FGameplayTag& SlotName)> SlotFunction, const TFunctionRef<bool(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB)> Predicate)
	{
		for (auto& SlotData : SlotList)
		{
			if (InventorySearch.IsTagMatch(SlotData.SlotName) == false || SlotFunction(SlotData.SlotName) == false)
			{
				continue; // Tag Not Match Any One On Search
			}

			SlotData.SortItem(Predicate);
			SlotData.ClearEmptyItem();
		}
	}

public:

	FORCEINLINE const TArray<FLFPInventorySlot>& GetSlotListConst() const
	{
		return SlotList;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FLFPInventoryItemEvent, const FLFPInventoryIndex&, InventoryIndex, const FLFPInventoryItem&, NewData, const FLFPInventoryItem&, OldData, const FGameplayTag&, EventTag);

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

	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	virtual void InitializeComponent() override;

	virtual void UninitializeComponent() override;


	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

public: // Delegate

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FLFPInventoryItemEvent OnUpdateItem;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FLFPInventoryItemEvent OnAddItem;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FLFPInventoryItemEvent OnRemoveItem;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FLFPInventoryItemEvent OnSwapItem;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FLFPInventoryItemEvent OnTransferItem;

protected: // Delegate Function

	UFUNCTION(NetMulticast, Reliable)
	void SendAddDelegateEvent(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const;
	void SendAddDelegateEvent_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const;

	UFUNCTION(NetMulticast, Reliable)
	void SendRemoveDelegateEvent(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const;
	void SendRemoveDelegateEvent_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const;

	UFUNCTION(NetMulticast, Reliable)
	void SendSwapDelegateEvent(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const;
	void SendSwapDelegateEvent_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const;

	UFUNCTION(NetMulticast, Reliable)
	void SendTransferDelegateEvent(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const;
	void SendTransferDelegateEvent_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const;

	UFUNCTION(NetMulticast, Reliable)
	void SendUpdateDelegateEvent(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const;
	void SendUpdateDelegateEvent_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const;

public:

	/* Not Recommend, Try To Use (Find / Contain / GetSlotItem) First */
	FORCEINLINE const FLFPInventorySlotList& GetInventorySlotList() const;

	FORCEINLINE bool ProcessInventoryIndex(
		const FLFPInventorySearch& InventoryCategorize,
		const TFunctionRef<bool(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InternalIndex)> IndexFunction,
		const bool bUseMaxIndex = false,
		const TFunction<void(const int32 SlotListIndex)> OnSlotNameEnd = nullptr
	) const;

protected: // Internal Function

	FORCEINLINE bool ProcessInventoryFunction(
		const TFunctionRef<bool(const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)> RunFunction
	) const;

	UFUNCTION() FORCEINLINE bool AddItem_Internal			(const FLFPInventoryIndex& InventoryIndex, FLFPInventoryItem& ProcessItemData, const FGameplayTag& EventTag);

	UFUNCTION() FORCEINLINE bool AddItem_Internal_Check		(const FLFPInventoryIndex& InventoryIndex, FLFPInventoryItem& ProcessItemData) const;

	UFUNCTION() FORCEINLINE bool RemoveItem_Internal		(const FLFPInventoryIndex& InventoryIndex, FLFPInventoryItem& ProcessItemData, const FGameplayTag& EventTag);

	UFUNCTION() FORCEINLINE bool RemoveItem_Internal_Check	(const FLFPInventoryIndex& InventoryIndex, FLFPInventoryItem& ProcessItemData) const;

	UFUNCTION() FORCEINLINE bool SwapItem_Internal			(const FLFPInventoryIndex& FromIndex, const FLFPInventoryIndex& ToIndex, const FGameplayTag& EventTag);

	UFUNCTION() FORCEINLINE bool Transfer_Index_Internal	(const FLFPInventoryIndex& FromIndex, const FLFPInventoryIndex& ToIndex, ULFPInventoryComponent* TargetInventoryComponent, const FGameplayTag EventTag);

	UFUNCTION() FORCEINLINE bool Transfer_Search_Internal	(const FLFPInventoryIndex& FromIndex, const FLFPInventorySearch& ToSearch, ULFPInventoryComponent* TargetInventoryComponent, const FGameplayTag EventTag);

	UFUNCTION() FORCEINLINE bool UpdateItem_Internal		(const FLFPInventoryIndex& InventoryIndex, FLFPInventoryItem& ProcessItemData, const FGameplayTag& EventTag);

	UFUNCTION() FORCEINLINE bool ContainItem_Internal		(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex, FLFPInventoryItem& ProcessItemData) const;

	UFUNCTION() FORCEINLINE bool FindItem_Internal			(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex, FLFPInventoryItem& ProcessItemData) const;

public:

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function", meta = (GameplayTagFilter = "Item.Event"))
		bool AddItem(UPARAM(ref) FLFPInventoryItem& ItemData, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function", meta = (GameplayTagFilter = "Item.Event"))
		bool AddItemList(UPARAM(ref) TArray<FLFPInventoryItem>& ItemDataList, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function", meta = (GameplayTagFilter = "Item.Event"))
		bool AddItemBySearch(const FLFPInventorySearch& InventorySearch, UPARAM(ref) FLFPInventoryItem& ItemData, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function", meta = (GameplayTagFilter = "Item.Event"))
		bool AddItemListBySearch(const FLFPInventorySearch& InventorySearch, UPARAM(ref) TArray<FLFPInventoryItem>& ItemDataList, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function", meta = (GameplayTagFilter = "Item.Event"))
		bool AddItemByIndex(const FLFPInventoryIndex& InventoryIndex, UPARAM(ref) FLFPInventoryItem& ItemData, const FGameplayTag EventTag);


	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function", meta = (GameplayTagFilter = "Item.Event"))
		bool RemoveItem(UPARAM(ref) FLFPInventoryItem& ItemData, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function", meta = (GameplayTagFilter = "Item.Event"))
		bool RemoveItemList(UPARAM(ref) TArray<FLFPInventoryItem>& ItemDataList, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function", meta = (GameplayTagFilter = "Item.Event"))
		bool RemoveItemBySearch(const FLFPInventorySearch& InventorySearch, UPARAM(ref) FLFPInventoryItem& ItemData, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function", meta = (GameplayTagFilter = "Item.Event"))
		bool RemoveItemListBySearch(const FLFPInventorySearch& InventorySearch, UPARAM(ref) TArray<FLFPInventoryItem>& ItemDataList, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function", meta = (GameplayTagFilter = "Item.Event"))
		bool RemoveItemByIndex(const FLFPInventoryIndex& InventoryIndex, UPARAM(ref) FLFPInventoryItem& ItemData, const FGameplayTag EventTag);


	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function", meta = (GameplayTagFilter = "Item.Event"))
		bool SwapItemToIndex(const FLFPInventoryIndex& FromIndex, const FLFPInventoryIndex& ToIndex, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function", meta = (GameplayTagFilter = "Item.Event"))
		bool SwapItemToSearch(const FLFPInventoryIndex& FromIndex, const FLFPInventorySearch& ToSearch, const FGameplayTag EventTag);


	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function", meta = (GameplayTagFilter = "Item.Event"))
		bool TransferItemToIndex(const FLFPInventoryIndex& FromIndex, const FLFPInventoryIndex& ToIndex, ULFPInventoryComponent* TargetInventoryComponent, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function", meta = (GameplayTagFilter = "Item.Event"))
		bool TransferItemToSearch(const FLFPInventoryIndex& FromIndex, const FLFPInventorySearch& ToSearch, ULFPInventoryComponent* TargetInventoryComponent, const FGameplayTag EventTag);


	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function", meta = (GameplayTagFilter = "Item.Event"))
		bool UpdateItem(UPARAM(ref) FLFPInventoryItem& ItemData, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function", meta = (GameplayTagFilter = "Item.Event"))
		bool UpdateItemBySearch(const FLFPInventorySearch& InventorySearch, UPARAM(ref) FLFPInventoryItem& ItemData, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function", meta = (GameplayTagFilter = "Item.Event"))
		bool UpdateItemByIndex(const FLFPInventoryIndex& InventoryIndex, UPARAM(ref) FLFPInventoryItem& ItemData, const FGameplayTag EventTag);


	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool SortItem(const FLFPInventorySearch& InventorySearch, UPARAM(meta = (Categories = "Item.Sort")) const FGameplayTag SortTag, UPARAM(meta = (Categories = "Item.Event")) const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		void ClearInventory(UPARAM(meta = (Categories = "Item.SlotName")) const FGameplayTagContainer SlotNames, UPARAM(meta = (Categories = "Item.Event")) const FGameplayTag EventTag);

public:

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Function")
		ULFPItemInventoryFunction* GetFunctionObject(const TSubclassOf<ULFPItemInventoryFunction> FunctionClass) const;

public:

	// Start Modifier

	UFUNCTION()
	FORCEINLINE bool CanAddItem(const FLFPInventoryItem& ItemData) const;

	UFUNCTION()
	FORCEINLINE bool CanRemoveItem(const FLFPInventoryItem& ItemData) const;

	UFUNCTION()
	FORCEINLINE bool CanSwapItem(const FLFPInventoryItem& FromItem, const FLFPInventoryItem& ToItem) const;

	UFUNCTION()
	FORCEINLINE bool CanUpdateItem(const FLFPInventoryItem& ItemData) const;

	UFUNCTION()
	FORCEINLINE bool CanContainItem(const FLFPInventoryItem& ItemData) const;

	// Slot Check Modifier

	UFUNCTION()
	FORCEINLINE bool CanAddItemOnSlot(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const;

	UFUNCTION()
	FORCEINLINE bool CanRemoveItemOnSlot(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const;

	UFUNCTION()
	FORCEINLINE bool CanSwapItemOnSlot(const FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, const FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const;

	UFUNCTION()
	FORCEINLINE bool CanUpdateItemOnSlot(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const;

	UFUNCTION()
	FORCEINLINE bool CanContainItemOnSlot(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& CurrentData, const FLFPInventoryItem& ProcessData) const;

	// Process Modifier

	UFUNCTION()
	FORCEINLINE bool ProcessAddItem(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;

	UFUNCTION()
	FORCEINLINE bool ProcessRemoveItem(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;

	UFUNCTION()
	FORCEINLINE bool ProcessSwapItem(UPARAM(ref) FLFPInventoryItem& FromItem, const FLFPInventoryIndex& FromIndex, UPARAM(ref) FLFPInventoryItem& ToItem, const FLFPInventoryIndex& ToIndex) const;

	UFUNCTION()
	FORCEINLINE bool ProcessUpdateItem(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;

	UFUNCTION()
	FORCEINLINE bool ProcessContainItem(const FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;

	// Catergorize Modifier

	UFUNCTION()
	FORCEINLINE FGameplayTagContainer GetIndexCatergorize(const FLFPInventoryInternalIndex& InventoryIndex) const;

	UFUNCTION()
	FORCEINLINE FGameplayTagContainer GetItemCatergorize(const FLFPInventoryItem& ItemData) const;

	UFUNCTION()
	FORCEINLINE FLFPInventorySearch GetItemInventorySearch(const FLFPInventoryItem& ItemData) const;

	// Check Modifier

	UFUNCTION()
	FORCEINLINE bool CanSlotNameBeSort(const FGameplayTag& SlotName) const;

	UFUNCTION()
	FORCEINLINE bool CanItemSortHigherThan(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB, const FGameplayTag& SortTag) const;

public:

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Function")
		bool ContainItem(FLFPInventoryItem ItemData, const FLFPInventorySearch& InventorySearch) const;

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Function")
		bool ContainItemList(const TArray<FLFPInventoryItem>& ItemDataList, const FLFPInventorySearch& InventorySearch, const bool bPartially = false) const;

public:

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Function")
		bool IsSlotNameValid(const FGameplayTag SlotName) const;

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Function")
		bool IsInventoryIndexReserved(const FLFPInventoryIndex& InventoryIndex) const;

public:

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Function")
	FORCEINLINE FLFPInventoryItem GetSlotItem(const FLFPInventoryIndex& InventoryIndex) const;

public:

	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Function")
		bool FindInventoryIndexList(TArray<FLFPInventoryIndex>& InventoryIndexList, FLFPInventoryItem ItemData, const FLFPInventorySearch& InventorySearch, const int32 MaxListItem = -1) const;
	
	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Function")
		bool FindItemDataList(TArray<FLFPInventoryItem>& ItemIndexList, FLFPInventoryItem ItemData, const FLFPInventorySearch& InventorySearch, const int32 MaxListItem = -1) const;

protected:

	UPROPERTY(EditDefaultsOnly, Replicated, Category = "LFPInventoryComponent | Variable")
		FLFPInventorySlotList InventorySlot = FLFPInventorySlotList();

	UPROPERTY(EditDefaultsOnly, Instanced, Replicated, Category = "LFPInventoryComponent | Variable")
		TArray<TObjectPtr<ULFPItemInventoryFunction>> FunctionList = TArray<TObjectPtr<ULFPItemInventoryFunction>>();

	/* Use On Slot With -1 SlotMaxIndex To Limit Loop Num On Add / Swap */
	UPROPERTY(EditDefaultsOnly, Category = "LFPInventoryComponent | Setting")
		int32 ExtraLoopSlot = 32;
};
