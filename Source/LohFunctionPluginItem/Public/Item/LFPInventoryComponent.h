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
#include "LFPInventoryComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LFPInventoryComponent, Log, All);


UENUM(BlueprintType)
enum ELFPInventoryOperation : uint8
{
	OnAdd		UMETA(DisplayName = "OnAdd"),
	OnRemove	UMETA(DisplayName = "OnRemove"),
	OnSwap      UMETA(DisplayName = "OnSwap")
};

USTRUCT(BlueprintType)
struct FLFPInventoryItem
{
	GENERATED_BODY()

	FLFPInventoryItem() {}

	FLFPInventoryItem(const FGameplayTag Tag) : ItemTag(Tag), MetaData(FJsonObjectWrapper()) {}

	FLFPInventoryItem(const FLFPInventoryItem& Other) : ItemTag(Other.ItemTag), MetaData(Other.MetaData) 
	{ 
		MetaData.JsonObject = MakeShared<FJsonObject>();

		if (MetaData.JsonObjectFromString(MetaData.JsonString) == false)
		{
			MetaData.JsonString.Empty();
		}
	}

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default, meta = (Categories = "Item.Identifiers"))
		FGameplayTag ItemTag = FGameplayTag();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
		FJsonObjectWrapper MetaData = FJsonObjectWrapper();

public:

	FORCEINLINE bool IsValid() const { return ItemTag.IsValid() && MetaData.JsonObject.IsValid(); }

	FORCEINLINE	bool MatchesTag(const FGameplayTag& Tag) const { return ItemTag.MatchesTag(Tag); }

	FORCEINLINE	bool operator==(const FGameplayTag& Tag) const { return ItemTag == Tag; }

	FORCEINLINE	bool operator!=(const FGameplayTag& Tag) const { return ItemTag != Tag; }

	FORCEINLINE	bool operator==(const FLFPInventoryItem& Other) const { return ItemTag == Other.ItemTag && MetaData.JsonString == Other.MetaData.JsonString; }

	FORCEINLINE	bool operator!=(const FLFPInventoryItem& Other) const { return ItemTag != Other.ItemTag || MetaData.JsonString != Other.MetaData.JsonString; }

	FORCEINLINE	FLFPInventoryItem& operator=(const FLFPInventoryItem& Other)
	{
		MetaData.JsonObject = MakeShared<FJsonObject>();

		if (MetaData.JsonObjectFromString(MetaData.JsonString) == false)
		{
			MetaData.JsonString.Empty();
		}

		ItemTag = Other.ItemTag;

		return *this;
	}

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
	{
		Ar << MetaData.JsonString << ItemTag;

		MetaData.PostSerialize(Ar);

		if (MetaData.JsonObject.IsValid() == false) MetaData.JsonObjectFromString("{}");

		bOutSuccess = true;

		return true;
	}
};

template<>
struct TStructOpsTypeTraits<FLFPInventoryItem> : public TStructOpsTypeTraitsBase2<FLFPInventoryItem>
{
	enum
	{
		WithNetSerializer = true
	};
};

USTRUCT(BlueprintType)
struct FLFPInventorySearchIndex
{
	GENERATED_BODY()

	FLFPInventorySearchIndex() {}

	FLFPInventorySearchIndex(const int32 NewSlotIndex, const FGameplayTagContainer& NewSlotNames) : SlotIndex(NewSlotIndex), SlotNames(NewSlotNames) {}

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
		int32 SlotIndex = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default, meta = (Categories = "Item.SlotNames"))
		FGameplayTagContainer SlotNames = FGameplayTagContainer::EmptyContainer;

public:

	//FORCEINLINE bool IsIndexMatch(const int32 Index) const { return SlotIndex == INDEX_NONE ? true : SlotIndex == Index; }

	FORCEINLINE bool IsTagMatch(const FGameplayTag Tag) const { return SlotNames.IsEmpty() ? true : Tag.MatchesAny(SlotNames); }

	FORCEINLINE FString ToString() const { return FString::Printf(TEXT("%s | Index = %d"), *SlotNames.ToString(), SlotIndex); }
};

USTRUCT(BlueprintType)
struct FLFPInventoryIndex
{
	GENERATED_BODY()

	FLFPInventoryIndex() {}

	FLFPInventoryIndex(const int32 NewSlotIndex, const FGameplayTag& NewSlotName) : SlotIndex(NewSlotIndex), SlotName(NewSlotName) {}

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
		int32 SlotIndex = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default, meta = (Categories = "Item.SlotNames"))
		FGameplayTag SlotName = FGameplayTag::EmptyTag;

public:

	//FORCEINLINE bool IsIndexMatch(const int32 Index) const { return SlotIndex == INDEX_NONE ? true : SlotIndex == Index; }

	//FORCEINLINE bool IsTagMatch(const FGameplayTag Tag) const { return SlotName.IsValid() == false ? true : Tag.MatchesTag(SlotName); }

	FORCEINLINE	bool operator==(const FLFPInventoryIndex& Other) const { return SlotIndex == Other.SlotIndex && SlotName == Other.SlotName; }
	
	FORCEINLINE	bool operator!=(const FLFPInventoryIndex& Other) const { return SlotIndex != Other.SlotIndex || SlotName != Other.SlotName; }
};

USTRUCT(BlueprintType)
struct FLFPInventorySearchChange
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
		FLFPInventorySearchIndex SearchIndex = FLFPInventorySearchIndex();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
		FLFPInventoryItem ItemData = FLFPInventoryItem();

public:

	FORCEINLINE bool IsValid() const { return ItemData.IsValid(); }
};

USTRUCT(BlueprintType)
struct FLFPInventoryChange
{
	GENERATED_BODY()

	FLFPInventoryChange() {};

	FLFPInventoryChange(const FLFPInventoryIndex& NewInventoryIndex, const FLFPInventoryItem& NewItemData) : InventoryIndex(NewInventoryIndex), ItemData(NewItemData) {};

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
		FLFPInventoryIndex InventoryIndex = FLFPInventoryIndex();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
		FLFPInventoryItem ItemData = FLFPInventoryItem();

public:

	FORCEINLINE	bool operator==(const FLFPInventoryChange& Other) const { return InventoryIndex == Other.InventoryIndex && ItemData == Other.ItemData; }

	FORCEINLINE	bool operator!=(const FLFPInventoryChange& Other) const { return InventoryIndex != Other.InventoryIndex || ItemData != Other.ItemData; }
};

USTRUCT(BlueprintType)
struct FLFPInventorySearchSwap
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
		FLFPInventorySearchIndex TargetIndex = FLFPInventorySearchIndex();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
		FLFPInventorySearchIndex ToIndex = FLFPInventorySearchIndex();
};

USTRUCT(BlueprintType)
struct FLFPInventorySlot
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default, meta = (Categories = "Item.SlotNames"))
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
		if (ItemList.IsValidIndex(Index) == false)
		{
			return FLFPInventoryItem();
		}

		return ItemList[Index];
	}

	FORCEINLINE FLFPInventoryItem& GetItemRef(const int32 Index)
	{
		if (ItemList.IsValidIndex(Index) == false)
		{
			ItemList.SetNum(Index + 1);
		}

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

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public: // Delegate

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnChangeEvent OnUpdateItem;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnChangeEvent OnAddItem;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnChangeEvent OnRemoveItem;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPInventoryComponent | Delegate")
		FOnChangeEvent OnSwapItem;

public: // Delegate Function

	UFUNCTION(NetMulticast, Reliable)
	void SendAddDelegateEvent(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const;
	void SendAddDelegateEvent_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const;

	UFUNCTION(NetMulticast, Reliable)
	void SendRemoveDelegateEvent(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const;
	void SendRemoveDelegateEvent_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const;

	UFUNCTION(NetMulticast, Reliable)
	void SendSwapDelegateEvent(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const;
	void SendSwapDelegateEvent_Implementation(const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData, const FGameplayTag& EventTag) const;

public: // Internal Function

	FORCEINLINE bool ProcessInventoryIndex(
		const FLFPInventorySearchIndex& SearchIndex, 
		const TFunctionRef<bool(const FLFPInventoryChange& ChangeData)> CheckerFunction, 
		const TFunctionRef<bool(FLFPInventoryItem& ItemData, const FLFPInventoryIndex InventoryIndex)> IndexFunction,
		const TFunctionRef<void(const FLFPInventoryIndex InventoryIndex, const FLFPInventoryItem& NewData, const FLFPInventoryItem& OldData)> EventFunction
	);

	FORCEINLINE bool ProcessInventoryIndexConst(
		const FLFPInventorySearchIndex& SearchIndex,
		const TFunctionRef<bool(const FLFPInventoryChange& ChangeData)> CheckerFunction,
		const TFunctionRef<bool(const FLFPInventoryChange& ChangeData)> IndexFunction
	) const;

public:

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool AddItem(const FLFPInventorySearchChange& SearchChangeData, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool RemoveItem(const FLFPInventorySearchChange& SearchChangeData, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool SwapItem(const FLFPInventorySearchSwap& SearchSwapData, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		bool SortItem(const FGameplayTag SortTag, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		void ClearInventory(const FGameplayTagContainer SlotNames, const FGameplayTag EventTag);

protected: // Modifier

	// Confirm Modifier

	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Modifier")
	bool CanAddItem(const FLFPInventoryChange& ChangeData) const;
	virtual bool CanAddItem_Implementation(const FLFPInventoryChange& ChangeData) const;

	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Modifier")
	bool CanRemoveItem(const FLFPInventoryChange& ChangeData) const;
	virtual bool CanRemoveItem_Implementation(const FLFPInventoryChange& ChangeData) const;

	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Modifier")
	bool CanSwapItem(const FLFPInventoryChange& ChangeDataA, const FLFPInventoryChange& ChangeDataB) const;
	virtual bool CanSwapItem_Implementation(const FLFPInventoryChange& ChangeDataA, const FLFPInventoryChange& ChangeDataB) const;

	// Process Modifier

	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Modifier")
	bool ProcessAddItem(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;
	virtual bool ProcessAddItem_Implementation(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;

	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Modifier")
	bool ProcessRemoveItem(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;
	virtual bool ProcessRemoveItem_Implementation(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;

	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Modifier")
	bool ProcessSwapItem(UPARAM(ref) FLFPInventoryItem& ItemDataA, const FLFPInventoryIndex InventoryIndexA, UPARAM(ref) FLFPInventoryItem& ItemDataB, const FLFPInventoryIndex InventoryIndexB) const;
	virtual bool ProcessSwapItem_Implementation(UPARAM(ref) FLFPInventoryItem& ItemDataA, const FLFPInventoryIndex InventoryIndexA, UPARAM(ref) FLFPInventoryItem& ItemDataB, const FLFPInventoryIndex InventoryIndexB) const;

	// Catergorize Modifier

	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Modifier")
	FGameplayTagContainer GetInventoryIndexCatergorize(const FLFPInventoryChange& ChangeData) const;
	virtual FGameplayTagContainer GetInventoryIndexCatergorize_Implementation(const FLFPInventoryChange& ChangeData) const;

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
};
