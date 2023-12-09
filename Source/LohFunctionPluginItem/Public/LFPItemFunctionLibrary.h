// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LFPItemFunctionLibrary.generated.h"

UENUM(BlueprintType)
enum ELFPInventoryOperation : uint8
{
	OnAdd		UMETA(DisplayName = "OnAdd"),
	OnRemove	UMETA(DisplayName = "OnRemove"),
	OnSwap      UMETA(DisplayName = "OnSwap")
};

USTRUCT(BlueprintType)
struct FLFPInventoryMeta
{
	GENERATED_BODY()

	FLFPInventoryMeta() {}

	FLFPInventoryMeta(const FGameplayTag& Tag) : MetaTag(Tag), MetaData(FString("")) {}

	FLFPInventoryMeta(const FGameplayTag& Tag, const FString& Data) : MetaTag(Tag), MetaData(Data) {}

	FLFPInventoryMeta(const FLFPInventoryMeta& Other) : MetaTag(Other.MetaTag), MetaData(Other.MetaData) {}

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default, meta = (Categories = "Item.Meta"))
	FGameplayTag MetaTag = FGameplayTag();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	FString MetaData = FString("");

public:

	FORCEINLINE bool operator==(const FGameplayTag& Tag) const { return MetaTag == Tag; }

	FORCEINLINE bool operator==(const FLFPInventoryMeta& Other) const { return MetaTag == Other.MetaTag && MetaData == Other.MetaData; }
};

USTRUCT(BlueprintType)
struct FLFPInventoryItem
{
	GENERATED_BODY()

	FLFPInventoryItem() {}

	FLFPInventoryItem(const FGameplayTag& Tag) : ItemTag(Tag), MetaData(TArray<FLFPInventoryMeta>()) {}

	FLFPInventoryItem(const FLFPInventoryItem& Other) : ItemTag(Other.ItemTag), MetaData(Other.MetaData) {}

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default, meta = (Categories = "Item.Identifier"))
	FGameplayTag ItemTag = FGameplayTag();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	TArray<FLFPInventoryMeta> MetaData = TArray<FLFPInventoryMeta>();

public:

	FORCEINLINE bool IsValid() const { return ItemTag.IsValid(); }

	FORCEINLINE	bool MatchesTag(const FGameplayTag& Tag) const { return ItemTag.MatchesTag(Tag); }


	FORCEINLINE	bool HasMetaData(const FGameplayTag& Tag) const { return MetaData.IndexOfByKey(Tag) != INDEX_NONE; }

	FORCEINLINE	FString GetMetaData(const FGameplayTag& Tag) const { int32 ReturnIndex(MetaData.IndexOfByKey(Tag)); return ReturnIndex != INDEX_NONE ? MetaData[ReturnIndex].MetaData : FString(""); }

	FORCEINLINE	void SetMetaData(const FLFPInventoryMeta& Data)
	{
		int32 ReturnIndex(MetaData.IndexOfByKey(Data.MetaTag));

		if (ReturnIndex != INDEX_NONE)
		{
			MetaData[ReturnIndex].MetaData = Data.MetaData;
		}
		else
		{
			MetaData.Add(Data);
		}
	}


	FORCEINLINE	bool operator==(const FGameplayTag& Tag) const { return ItemTag == Tag; }

	FORCEINLINE	bool operator!=(const FGameplayTag& Tag) const { return ItemTag != Tag; }

	FORCEINLINE	bool operator==(const FLFPInventoryItem& Other) const { return ItemTag == Other.ItemTag && MetaData == Other.MetaData; }

	FORCEINLINE	bool operator!=(const FLFPInventoryItem& Other) const { return ItemTag != Other.ItemTag || MetaData != Other.MetaData; }

	FORCEINLINE	FLFPInventoryItem& operator=(const FLFPInventoryItem& Other)
	{
		ItemTag = Other.ItemTag;
		MetaData = Other.MetaData;

		return *this;
	}
};

USTRUCT()
struct FLFPInventoryKey
{
	GENERATED_BODY()

	FLFPInventoryKey() {}

	FLFPInventoryKey(const int32 NewSlotIndex, const int32 NewSlotNameIndex) : SlotIndex(NewSlotIndex), SlotNameIndex(NewSlotNameIndex) {}

public:

	UPROPERTY()
	int32 SlotIndex = INDEX_NONE;

	UPROPERTY()
	int32 SlotNameIndex = INDEX_NONE;

public:

	FORCEINLINE bool IsValid() const { return SlotIndex != INDEX_NONE && SlotNameIndex != INDEX_NONE; }
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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default, meta = (Categories = "Item.SlotName"))
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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default, meta = (Categories = "Item.SlotName"))
	FGameplayTag SlotName = FGameplayTag::EmptyTag;

public:

	//FORCEINLINE bool IsIndexMatch(const int32 Index) const { return SlotIndex == INDEX_NONE ? true : SlotIndex == Index; }

	//FORCEINLINE bool IsTagMatch(const FGameplayTag Tag) const { return SlotName.IsValid() == false ? true : Tag.MatchesTag(SlotName); }

	FORCEINLINE	bool operator==(const FLFPInventoryIndex& Other) const { return SlotIndex == Other.SlotIndex && SlotName == Other.SlotName; }

	FORCEINLINE	bool operator!=(const FLFPInventoryIndex& Other) const { return SlotIndex != Other.SlotIndex || SlotName != Other.SlotName; }

	FORCEINLINE FString ToString() const { return FString::Printf(TEXT("%s | Index = %d"), *SlotName.ToString(), SlotIndex); }
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
	FLFPInventorySearchIndex FromIndex = FLFPInventorySearchIndex();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	FLFPInventorySearchIndex ToIndex = FLFPInventorySearchIndex();
};

USTRUCT(BlueprintType)
struct FLFPInventorySearchTransfer
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	FLFPInventorySearchIndex FromIndex = FLFPInventorySearchIndex();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	FLFPInventorySearchIndex ToIndex = FLFPInventorySearchIndex();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	FLFPInventoryItem ItemData = FLFPInventoryItem();

public:

	FORCEINLINE bool IsValid() const { return ItemData.IsValid(); }
};

USTRUCT(BlueprintType)
struct FLFPInventorySearchChange
{
	GENERATED_BODY()

	FLFPInventorySearchChange() {};

	FLFPInventorySearchChange(const FLFPInventorySearchIndex& NewSearchIndex, const FLFPInventoryItem& NewItemData) : SearchIndex(NewSearchIndex), ItemData(NewItemData) {};

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	FLFPInventorySearchIndex SearchIndex = FLFPInventorySearchIndex();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	FLFPInventoryItem ItemData = FLFPInventoryItem();

public:

	FORCEINLINE bool IsValid() const { return ItemData.IsValid(); }
};

/**
 * 
 */
UCLASS()
class LOHFUNCTIONPLUGINITEM_API ULFPItemFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, Category = "LohFunctionPluginLibrary")
	static bool HasMetaData(const FLFPInventoryItem& Item, const FGameplayTag MetaTag);

	UFUNCTION(BlueprintPure, Category = "LohFunctionPluginLibrary")
	static FString GetMetaData(const FLFPInventoryItem& Item, const FGameplayTag MetaTag);

	UFUNCTION(BlueprintPure, Category = "LohFunctionPluginLibrary")
	static void SetMetaData(UPARAM(ref) FLFPInventoryItem& Item, const FLFPInventoryMeta& Data);
	
};
