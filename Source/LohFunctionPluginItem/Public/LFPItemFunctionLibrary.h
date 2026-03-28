// Copyright (c) 2023-2024 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "Library/LFPDynamicTypeLibrary.h"
#include "LFPItemFunctionLibrary.generated.h"

USTRUCT ( BlueprintType )
struct LOHFUNCTIONPLUGINITEM_API FLFPInventoryItem
{
	GENERATED_BODY ( )

	FLFPInventoryItem ( )
	{
	}

	FLFPInventoryItem ( const FGameplayTag& Tag ) : ItemTag ( Tag ), MetaDataList ( FLFPInstancedStructTagArray ( ) )
	{
	}

	FLFPInventoryItem ( const FLFPInventoryItem& Other ) : ItemTag ( Other.ItemTag ), MetaDataList ( Other.MetaDataList )
	{
	}

	static FLFPInventoryItem EmptyItem;

protected:

	UPROPERTY ( BlueprintReadWrite , EditAnywhere , Category = Default , meta = ( Categories = "Item.Identifier" ) )
	FGameplayTag ItemTag = FGameplayTag ( );

	UPROPERTY ( BlueprintReadWrite , EditAnywhere , Category = Default )
	FLFPInstancedStructTagArray MetaDataList = FLFPInstancedStructTagArray ( );

public:

	FORCEINLINE bool IsValid ( ) const
	{
		return ItemTag.IsValid ( ) && UGameplayTagsManager::Get ( ).RequestGameplayTag ( ItemTag.GetTagName ( ) ).IsValid ( );
	}

	FORCEINLINE bool MatchesTag ( const FGameplayTag& Tag ) const
	{
		return ItemTag.MatchesTag ( Tag );
	}

	FORCEINLINE bool MatchesAnyTag ( const FGameplayTagContainer& TagList ) const
	{
		return ItemTag.MatchesAny ( TagList );
	}

	// Item Tag

	FORCEINLINE const FGameplayTag& GetItemTag ( ) const
	{
		return ItemTag;
	}

	FORCEINLINE void SetItemTag ( const FGameplayTag& Tag )
	{
		ItemTag = Tag;

		if ( ItemTag.IsValid ( ) == false )
		{
			MetaDataList.Empty ( );
		}
	}

	// Meta Data

	FORCEINLINE bool ContainMetaData ( const FGameplayTag& Tag ) const
	{
		return MetaDataList.Contain ( Tag );
	}

	FORCEINLINE const FInstancedStruct* GetMetaData ( const FGameplayTag& Tag ) const
	{
		return MetaDataList.GetItemConst ( Tag );
	}

	FORCEINLINE const TArray < FGameplayTag >& GetMetaDataTagList ( ) const
	{
		return MetaDataList.GetMappingList ( );
	}

	FORCEINLINE void AddMetaData ( const FGameplayTag& MetaTag , const FInstancedStruct& MetaData , const bool bUniqueOnly = false )
	{
		if ( bUniqueOnly && MetaDataList.Contain ( MetaTag ) )
		{
			return;
		}

		MetaDataList.AddItem ( MetaTag , MetaData );
	}

	FORCEINLINE bool RemoveMetaData ( const FGameplayTag& MetaTag )
	{
		const bool bIsContain = MetaDataList.Contain ( MetaTag );

		MetaDataList.RemoveItem ( MetaTag );

		return bIsContain;
	}

	// Append Meta Data

	//FORCEINLINE void AppendMetaDataInt ( const TMap <FGameplayTag , int32>& DataMap , const bool bUniqueOnly = false );
	//
	//FORCEINLINE void AppendMetaDataFloat ( const TMap <FGameplayTag , float>& DataMap , const bool bUniqueOnly = false );
	//
	//FORCEINLINE void AppendMetaDataString ( const TMap <FGameplayTag , FString>& DataMap , const bool bUniqueOnly = false );
	//
	//FORCEINLINE void AppendMetaDataBoolean ( const TMap <FGameplayTag , bool>& DataMap , const bool bUniqueOnly = false );

	// String

	FORCEINLINE FString ToString ( ) const
	{
		return ItemTag.ToString ( );
	}

	FORCEINLINE bool operator== ( const FGameplayTag& Tag ) const
	{
		return ItemTag == Tag;
	}

	FORCEINLINE bool operator== ( const FLFPInventoryItem& Other ) const
	{
		return ItemTag == Other.ItemTag && MetaDataList == Other.MetaDataList;
	}
};

/**
 *
 */
UCLASS ( )
class LOHFUNCTIONPLUGINITEM_API ULFPItemFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY ( )

public: // Checker

	UFUNCTION ( BlueprintPure , Category = "LohFunctionPluginLibrary" )
	static bool IsMetaDataSame ( const FLFPInventoryItem& ItemA , const FLFPInventoryItem& ItemB , const FGameplayTag MetaTag );

	UFUNCTION ( BlueprintPure , Category = "LohFunctionPluginLibrary" )
	static bool ContainMetaData ( const FLFPInventoryItem& Item , const FGameplayTag MetaTag );

	/* Check Is Item Contain All Metadata And Equal Or Bigger Than The Cost  */
	//UFUNCTION ( BlueprintCallable , Category = "LohFunctionPluginLibrary" )
	//static bool CheckMetaDataCost ( const FLFPInventoryItem& Item , const TMap < FGameplayTag , int32 >& IntCostDataMap , const TMap < FGameplayTag , float >& FloatCostDataMap );

	// Getter

	UFUNCTION ( BlueprintPure , Category = "LohFunctionPluginLibrary" )
	static const FInstancedStruct& GetMetaData ( const FLFPInventoryItem& Item , const FGameplayTag MetaTag );

	UFUNCTION ( BlueprintPure , Category = "LohFunctionPluginLibrary" )
	static FGameplayTag GetItemTag ( const FLFPInventoryItem& Item );

	// Setter

	UFUNCTION ( BlueprintCallable , Category = "LohFunctionPluginLibrary" )
	static void SetMetaData ( UPARAM ( ref ) FLFPInventoryItem& Item , const FGameplayTag MetaTag , const FInstancedStruct& MetaData );

	UFUNCTION ( BlueprintCallable , Category = "LohFunctionPluginLibrary" )
	static void SetItemTag ( UPARAM ( ref ) FLFPInventoryItem& Item , const FGameplayTag ItemTag );

	/* Subtract The Cost From Item Metadata */
	//UFUNCTION ( BlueprintCallable , Category = "LohFunctionPluginLibrary" )
	//static void ConsumeMetaDataCost ( UPARAM ( ref ) FLFPInventoryItem& Item , const TMap <FGameplayTag , int32>& IntCostDataMap , const TMap <FGameplayTag , float>& FloatCostDataMap );

private:

	static FInstancedStruct EmptyStruct;
};
