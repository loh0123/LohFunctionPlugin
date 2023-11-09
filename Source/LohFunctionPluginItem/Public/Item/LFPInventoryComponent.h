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

	FLFPInventoryItem() { MetaData.JsonObjectFromString("{}"); }

	FLFPInventoryItem(const FGameplayTag Tag) : ItemTag(Tag) { MetaData.JsonObjectFromString("{}"); }

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	FJsonObjectWrapper MetaData = FJsonObjectWrapper();

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default, meta = (Categories = "Item.Identifiers"))
	FGameplayTag ItemTag = FGameplayTag();

public:

	FORCEINLINE const FGameplayTag& GetItemTag() const
	{
		return ItemTag;
	}

public:

	FORCEINLINE	bool operator==(const FGameplayTag& Tag) const
	{
		return ItemTag.MatchesTag(Tag);
	}

	FORCEINLINE	FLFPInventoryItem& operator=(const FLFPInventoryItem& Other)
	{
		if (MetaData.JsonObjectFromString(Other.MetaData.JsonString) == false) MetaData.JsonObjectFromString("{}");

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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
		int32 Index = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default, meta = (Categories = "Item.SlotNames"))
		FGameplayTag SlotName = FGameplayTag::EmptyTag;
};

USTRUCT(BlueprintType)
struct FLFPInventoryChange
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
		FLFPInventoryIndex InventoryIndex = FLFPInventoryIndex();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
		FLFPInventoryItem ItemData = FLFPInventoryItem();
};

USTRUCT(BlueprintType)
struct FLFPInventorySwap
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
		FLFPInventoryChange ItemA = FLFPInventoryChange();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
		FLFPInventoryChange ItemB = FLFPInventoryChange();
};

USTRUCT(BlueprintType)
struct FLFPInventorySlot
{
	GENERATED_BODY()

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
};
