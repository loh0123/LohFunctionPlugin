// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
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

	FORCEINLINE int32 GetItemNum() const { return ItemList.Num(); }

	FORCEINLINE int32 GetNextNum() const { return SlotMaxIndex > INDEX_NONE ? FMath::Max(GetItemNum(), SlotMaxIndex - 1) : GetItemNum(); }

	FORCEINLINE FLFPInventoryItem GetItemCopy(const int32 Index) const
	{
		check(Index > INDEX_NONE);

		if (ItemList.IsValidIndex(Index) == false)
		{
			return FLFPInventoryItem();
		}

		return ItemList[Index];
	}

	FORCEINLINE FLFPInventoryItem& GetItemRef(const int32 Index)
	{
		check(Index > INDEX_NONE);

		if (ItemList.IsValidIndex(Index) == false)
		{
			ItemList.SetNum(Index + 1);
		}

		return ItemList[Index];
	}

	FORCEINLINE const FLFPInventoryItem& GetItemConst(const int32 Index) const
	{
		check(ItemList.IsValidIndex(Index));

		return ItemList[Index];
	}

	FORCEINLINE void ClearEmptyItem()
	{
		while (ItemList.Num() > 0 && ItemList.Last().IsValid() == false)
		{
			ItemList.RemoveAt(ItemList.Num() - 1, 1, false);
		}

		ItemList.Shrink();
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnChangeEvent, const FLFPInventoryIndex&, InventoryIndex, const FLFPInventoryItem&, NewData, const FLFPInventoryItem&, OldData, const FGameplayTag&, EventTag);

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

protected: // Delegate

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnChangeEvent OnUpdateItem;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnChangeEvent OnAddItem;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnChangeEvent OnRemoveItem;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnChangeEvent OnSwapItem;

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

protected: // Internal Function

	FORCEINLINE bool ProcessInventoryIndex(
		const FLFPInventorySearchIndex& SearchIndex, 
		const TFunctionRef<bool(const FLFPInventoryChange& ChangeData, const FLFPInventoryKey& InventoryKey)> CheckerFunction,
		const TFunctionRef<bool(const FLFPInventoryChange& ChangeData, const FLFPInventoryKey& InventoryKey)> IndexFunction,
		const TFunction<void(const FLFPInventoryChange& OldData, const FLFPInventoryKey& InventoryKey)> EventFunction = nullptr,
		const TFunction<void(const FLFPInventoryKey& InventoryKey)> OnSlotNameEnd = nullptr
	) const;

	FORCEINLINE bool ProcessInventoryFunction(
		const TFunctionRef<bool(const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj)> RunFunction
	) const;

public:

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function", meta = (GameplayTagFilter = "Item.Event"))
		bool AddItem(const FLFPInventorySearchChange& SearchChangeData, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool RemoveItem(const FLFPInventorySearchChange& SearchChangeData, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool SwapItem(const FLFPInventorySearchSwap& SearchSwapData, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool SortItem(const FGameplayTag SortTag, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		void ClearInventory(const FGameplayTagContainer SlotNames, const FGameplayTag EventTag);

public:

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Function")
		ULFPItemInventoryFunction* GetFunctionObject(const TSubclassOf<ULFPItemInventoryFunction> FunctionClass) const;

public:

	UFUNCTION()
		bool CanAddItem(const FLFPInventoryChange& ChangeData) const;

	UFUNCTION()
		bool CanRemoveItem(const FLFPInventoryChange& ChangeData) const;

	UFUNCTION()
		bool CanSwapItem(const FLFPInventoryChange& ChangeDataA, const FLFPInventoryChange& ChangeDataB) const;

	// Process Modifier

	UFUNCTION()
		bool ProcessAddItem(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;

	UFUNCTION()
		bool ProcessRemoveItem(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;

	UFUNCTION()
		bool ProcessSwapItem(UPARAM(ref) FLFPInventoryItem& ItemDataA, const FLFPInventoryIndex& InventoryIndexA, UPARAM(ref) FLFPInventoryItem& ItemDataB, const FLFPInventoryIndex& InventoryIndexB) const;

	// Catergorize Modifier

	UFUNCTION()
		FGameplayTagContainer GetInventoryIndexCatergorize(const FLFPInventoryChange& ChangeData) const;

public:	// Check Modifier

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "LFPInventoryComponent | Modifier")
	bool CanItemSortHigherThan(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB, const FGameplayTag& SortTag) const;
	virtual bool CanItemSortHigherThan_Implementation(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB, const FGameplayTag& SortTag) const;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "LFPInventoryComponent | Modifier")
	bool CanItemUseInventoryIndex(const FLFPInventoryChange& ChangeData, const ELFPInventoryOperation Operation) const;
	virtual bool CanItemUseInventoryIndex_Implementation(const FLFPInventoryChange& ChangeData, const ELFPInventoryOperation Operation) const;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "LFPInventoryComponent | Modifier")
	bool DoInventoryIndexContainItem(const FLFPInventoryChange& ChangeData) const;
	virtual bool DoInventoryIndexContainItem_Implementation(const FLFPInventoryChange& ChangeData) const;

public:

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Function")
		bool ContainItem(const FLFPInventoryItem& ItemData, const FLFPInventorySearchIndex& SearchIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Function")
		bool ContainItemList(const TArray<FLFPInventoryItem>& ItemDataList, const FLFPInventorySearchIndex& SearchIndex, const bool bPartially = false) const;

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Function")
		bool ContainCatergorize(const FGameplayTagContainer Catergorizes, const FLFPInventorySearchIndex& SearchIndex, const bool bContainAll = false, const bool bCombineSearch = false) const;

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Function")
		bool IsSlotNameValid(const FGameplayTag SlotName) const;

public:

	//UFUNCTION()
	//	FLFPInventoryItem& GetSlotItemRef(const int32 SlotIndex, const FGameplayTag SlotName) const;

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Function")
		FLFPInventoryItem GetSlotItem(const FLFPInventoryIndex& InventoryIndex) const;

	UFUNCTION()
		const FLFPInventoryItem& GetSlotItemConst(const FLFPInventoryKey& InventoryKey) const;

	UFUNCTION()
		FLFPInventoryItem& GetSlotItemRef(const FLFPInventoryKey& InventoryKey);

	UFUNCTION()
		void ClearSlotEmptyItem(const int32 SlotNameKey);

public:

	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Function")
		bool FindInventoryIndexList(TArray<FLFPInventoryIndex>& InventoryIndexList, const FLFPInventoryItem& ItemData, const FGameplayTagContainer SlotNames, const FGameplayTagContainer Catergorizes, const bool bContainAllCatergorize = false, const int32 MaxListItem = -1) const;
	
	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Function")
		bool FindItemDataList(TArray<FLFPInventoryItem>& ItemIndexList, const FLFPInventoryItem& ItemData, const FGameplayTagContainer SlotNames, const FGameplayTagContainer Catergorizes, const bool bContainAllCatergorize = false, const int32 MaxListItem = -1) const;

public:

	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Function")
		FJsonObjectWrapper ExportJson(const FGameplayTagContainer SlotNames) const;
	
	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Function")
		bool ImportJson(const FJsonObjectWrapper& JsonData, const FGameplayTagContainer SlotNames);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "LFPInventoryComponent | Variable")
		TArray<FLFPInventorySlot> InventorySlot = TArray<FLFPInventorySlot>();

	UPROPERTY(EditDefaultsOnly, Instanced, Replicated, Category = "LFPInventoryComponent | Variable")
		TArray<TObjectPtr<ULFPItemInventoryFunction>> FunctionList = TArray<TObjectPtr<ULFPItemInventoryFunction>>();
};
