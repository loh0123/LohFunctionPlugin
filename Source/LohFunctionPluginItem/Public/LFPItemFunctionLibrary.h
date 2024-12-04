// Copyright (c) 2023-2024 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetStringLibrary.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "LohFunctionPluginLibrary.h"
#include "LFPItemFunctionLibrary.generated.h"

USTRUCT( BlueprintType )
struct LOHFUNCTIONPLUGINITEM_API FLFPInventoryItem
{
	GENERATED_BODY()

	FLFPInventoryItem() {
	}

	FLFPInventoryItem( const FGameplayTag& Tag ) : ItemTag( Tag ) , MetaData( TArray<uint8>() ) {
	}

	FLFPInventoryItem( const FLFPInventoryItem& Other ) : ItemTag( Other.ItemTag ) , MetaData( Other.MetaData ) {
	}

public:

	static FLFPInventoryItem EmptyItem;

protected:

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = Default , meta = ( Categories = "Item.Identifier" ) )
	FGameplayTag ItemTag = FGameplayTag();

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = Default )
	TArray<uint8> MetaData = TArray<uint8>();

public:

	FORCEINLINE bool IsValid() const {
		return ItemTag.IsValid() && UGameplayTagsManager::Get().RequestGameplayTag( ItemTag.GetTagName() ).IsValid();
	}

	FORCEINLINE	bool MatchesTag( const FGameplayTag& Tag ) const {
		return ItemTag.MatchesTag( Tag );
	}

	FORCEINLINE	bool MatchesAnyTag( const FGameplayTagContainer& TagList ) const {
		return ItemTag.MatchesAny( TagList );
	}

	// Item Tag

	FORCEINLINE const FGameplayTag& GetItemTag() const
	{
		return ItemTag;
	}

	FORCEINLINE	void SetItemTag( const FGameplayTag& Tag )
	{
		ItemTag = Tag;

		if ( ItemTag.IsValid() == false )
		{
			MetaData.Empty();
		}

		return;
	}

	// Meta Data

	FORCEINLINE	const TArray<uint8>& GetMetaData() const
	{
		return MetaData;
	}

	FORCEINLINE	void SetMetaData( const TArray<uint8>& NewData )
	{
		MetaData = NewData;
	}

	// String

	FORCEINLINE	FString ToString() const
	{
		return  ItemTag.ToString() + FString( " : " ) + FString::FromInt( MetaData.Num() );
	}


	FORCEINLINE	bool operator==( const FGameplayTag& Tag ) const {
		return ItemTag == Tag;
	}

	FORCEINLINE	bool operator!=( const FGameplayTag& Tag ) const {
		return ItemTag != Tag;
	}

	FORCEINLINE	bool operator==( const FLFPInventoryItem& Other ) const {
		return ItemTag == Other.ItemTag && MetaData == Other.MetaData;
	}

	FORCEINLINE	bool operator!=( const FLFPInventoryItem& Other ) const {
		return ItemTag != Other.ItemTag || MetaData != Other.MetaData;
	}

	FORCEINLINE	FLFPInventoryItem& operator=( const FLFPInventoryItem& Other )
	{
		ItemTag = Other.ItemTag;
		MetaData = Other.MetaData;

		return *this;
	}
};

/**
 *
 */
UCLASS()
class LOHFUNCTIONPLUGINITEM_API ULFPItemFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public: // Getter

	UFUNCTION( BlueprintPure , Category = "LohFunctionPluginLibrary" )
	static const TArray<uint8>& GetMetaData( const FLFPInventoryItem& Item );

public: // Setter

	UFUNCTION( BlueprintCallable , Category = "LohFunctionPluginLibrary" )
	static void SetMetaData( UPARAM( ref ) FLFPInventoryItem& Item , const TArray<uint8>& Data );

	UFUNCTION( BlueprintCallable , Category = "LohFunctionPluginLibrary" )
	static void SetItemTag( UPARAM( ref ) FLFPInventoryItem& Item , const FGameplayTag ItemTag );
};
