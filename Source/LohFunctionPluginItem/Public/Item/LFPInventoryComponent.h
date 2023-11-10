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

	FORCEINLINE	bool operator==(const FGameplayTag& Tag) const { return ItemTag.MatchesTag(Tag); }

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
struct FLFPInventoryIndex
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
		int32 SlotIndex = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default, meta = (Categories = "Item.SlotNames"))
		FGameplayTagContainer SlotNames;
};

USTRUCT(BlueprintType)
struct FLFPInventoryChange
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
		FLFPInventoryIndex InventoryIndex = FLFPInventoryIndex();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
		FLFPInventoryItem ItemData = FLFPInventoryItem();
};

USTRUCT(BlueprintType)
struct FLFPInventorySwap
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
		FLFPInventoryChange ItemA = FLFPInventoryChange();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
		FLFPInventoryChange ItemB = FLFPInventoryChange();
};

USTRUCT(BlueprintType)
struct FLFPInventorySlot
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
		FGameplayTag SlotName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
		TArray<FLFPInventoryItem> ItemList = TArray<FLFPInventoryItem>();
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChangeEvent, const FLFPInventoryChange&, OldData, const FGameplayTag&, EventTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSwapEvent, const FLFPInventorySwap&, OldData, const FGameplayTag&, EventTag);

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
		FOnSwapEvent OnSwapItem;

public:

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		void AddItem(const FLFPInventoryChange& ChangeData, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		void RemoveItem(const FLFPInventoryChange& ChangeData, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		void SwapItem(const FLFPInventorySwap& SwapData, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		void SortItem(const FGameplayTag SortTag, const FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPInventoryComponent | Function")
		void ClearInventory(const FGameplayTagContainer SlotNames, const FGameplayTag EventTag);

public:

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Function")
		bool ContainItem(const FLFPInventoryItem& ItemData, const FLFPInventoryIndex& InventoryIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Function")
		bool ContainItemList(const TArray<FLFPInventoryItem>& ItemDataList, const FLFPInventoryIndex& InventoryIndex, const bool bPartially = false) const;

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Function")
		bool IsSlotAvailable(const FLFPInventoryIndex& InventoryIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Function")
		bool IsItemSortPriorityHigherThan(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB) const;

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Function")
		bool IsSlotNameValid(const FGameplayTag SlotName) const;

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Function")
		bool IsSlotHasCatergorize(const FGameplayTagContainer Catergorizes, const int32 SlotIndex, const FGameplayTag SlotName) const;

public:

	//UFUNCTION()
	//	FLFPInventoryItem& GetSlotItemRef(const int32 SlotIndex, const FGameplayTag SlotName) const;

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Function")
		FLFPInventoryItem GetSlotItem(const int32 SlotIndex, const FGameplayTag SlotName) const;

public:

	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Function")
		bool FindItemIndexList(TArray<FLFPInventoryIndex>& ItemIndexList, const FLFPInventoryItem& ItemData, const FGameplayTagContainer SlotNames, const FGameplayTagContainer Catergorizes) const;
	
	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Function")
		bool FindItemDataList(TArray<FLFPInventoryItem>& ItemIndexList, const FLFPInventoryItem& ItemData, const FGameplayTagContainer SlotNames, const FGameplayTagContainer Catergorizes) const;

public:

	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Function")
		FJsonObjectWrapper ExportJson(const FGameplayTagContainer SlotNames) const;
	
	UFUNCTION(BlueprintCallable, Category = "LFPInventoryComponent | Function")
		bool ImportJson(const FJsonObjectWrapper& JsonData, const FGameplayTagContainer SlotNames);
};
