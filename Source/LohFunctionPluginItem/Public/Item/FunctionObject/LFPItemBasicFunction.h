// Copyright (c) 2023-2024 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "CoreMinimal.h"
#include "Item/FunctionObject/LFPItemInventoryFunction.h"
#include "LFPItemBasicFunction.generated.h"

class UDataRegistry;

USTRUCT ( BlueprintType )
struct FLFPItemBasicData
{
	GENERATED_BODY ( )

public:

	UPROPERTY ( BlueprintReadWrite , EditDefaultsOnly , Category = "Default|Stack" )
	int32 StackCount = 1;
};

USTRUCT ( Blueprintable )
struct FLFPItemBasicTableData : public FTableRowBase
{
	GENERATED_BODY ( )

protected:

	/* Maximum Stack An Item Can Reach, Infinite If Not Found */
	UPROPERTY ( BlueprintReadWrite , EditDefaultsOnly , Category = "Default|Stack" )
	TMap < FGameplayTag , int32 > MaxStackMap = TMap < FGameplayTag , int32 > ( );

	UPROPERTY ( BlueprintReadWrite , EditDefaultsOnly , Category = "Default|Attach" )
	FGameplayTag AttachSlotsTag = FGameplayTag ( );

	UPROPERTY ( BlueprintReadWrite , EditDefaultsOnly , Category = "Default|Attach" )
	int32 MaxAttachSlots = INDEX_NONE;

	/* Check All The Meta Match Other Item ( Can't Use Parent Tag ) */
	UPROPERTY ( BlueprintReadWrite , EditDefaultsOnly , Category = "Default" )
	FGameplayTagContainer MatchMetaTagList = FGameplayTagContainer ( );

	UPROPERTY ( BlueprintReadWrite , EditDefaultsOnly , Category = "Default" )
	FGameplayTagContainer AllowedInventorySlotNameList = FGameplayTagContainer ( );

	UPROPERTY ( BlueprintReadWrite , EditDefaultsOnly , Category = "Default" )
	FGameplayTagContainer Categorize = FGameplayTagContainer ( );

public:

	FORCEINLINE bool DoItemAllowOnSlot ( const FGameplayTag& SlotName ) const
	{
		return SlotName.MatchesAny ( AllowedInventorySlotNameList );
	}

	FORCEINLINE bool DoItemMetaMatch ( const FLFPInventoryItem& CurrentData , const FLFPInventoryItem& ProcessData ) const
	{
		if ( CurrentData.IsValid ( ) == false || ProcessData.IsValid ( ) == false )
		{
			return true;
		}

		for ( const FGameplayTag& MathIntTag : MatchMetaTagList )
		{
			if ( ULFPItemFunctionLibrary::IsMetaDataSame ( CurrentData , ProcessData , MathIntTag ) == false )
			{
				return false;
			}
		}

		return true;
	}

	FORCEINLINE bool DoItemReachMaxStack ( const FLFPInventoryItem& CurrentData , const FGameplayTag& MetaTag , const FGameplayTag& StackTag ) const
	{
		if ( MaxStackMap.Contains ( StackTag ) == false )
		{
			return false;
		}

		const int32 MaxStack = FMath::Max ( MaxStackMap.FindChecked ( StackTag ) , 1 );

		return CurrentData.IsValid ( ) && MaxStack <= GetStackAmount ( CurrentData , MetaTag );
	}

	FORCEINLINE int32 GetStackAmount ( const FLFPInventoryItem& CurrentData , const FGameplayTag& MetaTag ) const
	{
		const auto RawBasicMetaData = CurrentData.GetMetaData ( MetaTag );

		if ( RawBasicMetaData != nullptr && RawBasicMetaData->GetScriptStruct ( ) != FLFPItemBasicData::StaticStruct ( ) )
		{
			return 1;
		}

		const FLFPItemBasicData& BasicMetaData = RawBasicMetaData == nullptr ? FLFPItemBasicData ( ) : RawBasicMetaData->Get < FLFPItemBasicData > ( );

		return FMath::Max ( BasicMetaData.StackCount , 1 );
	}

	FORCEINLINE void SetStackAmount ( FLFPInventoryItem& CurrentData , const FGameplayTag& MetaTag , const int32 NewStack ) const
	{
		const auto RawBasicMetaData = CurrentData.GetMetaData ( MetaTag );

		FLFPItemBasicData BasicMetaData = RawBasicMetaData == nullptr ? FLFPItemBasicData ( ) : RawBasicMetaData->Get < FLFPItemBasicData > ( );

		BasicMetaData.StackCount = NewStack;

		CurrentData.AddMetaData ( MetaTag , FInstancedStruct::Make ( BasicMetaData ) );
	}

	FORCEINLINE int32 ClampToMaxStack ( const int32 Stack , const FGameplayTag& StackTag ) const
	{
		if ( MaxStackMap.Contains ( StackTag ) == false )
		{
			return FMath::Max ( Stack , 0 );
		}

		const int32 MaxStack = FMath::Max ( MaxStackMap.FindChecked ( StackTag ) , 1 );

		return FMath::Clamp ( Stack , 0 , MaxStack );
	}

	FORCEINLINE const FGameplayTagContainer& GetAllowInventorySlotNameList ( ) const
	{
		return AllowedInventorySlotNameList;
	}

	FORCEINLINE const FGameplayTagContainer& GetCategorize ( ) const
	{
		return Categorize;
	}
};

/**
 *
 */
UCLASS ( BlueprintType )
class LOHFUNCTIONPLUGINITEM_API ULFPItemBasicFunction : public ULFPItemInventoryFunction
{
	GENERATED_BODY ( )

public:

	virtual bool CanAddItem_Implementation ( const FLFPInventoryItem& ItemData ) const override;

	virtual bool CanRemoveItem_Implementation ( const FLFPInventoryItem& ItemData ) const override;

	virtual bool CanUpdateItem_Implementation ( const FLFPInventoryItem& ItemData ) const override;

	virtual bool CanFindItem_Implementation ( const FLFPInventoryItem& ItemData ) const override;

	virtual bool CanAddItemOnSlot_Implementation ( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryItem& CurrentData , const FLFPInventoryItem& ProcessData ) const override;

	virtual bool CanRemoveItemOnSlot_Implementation ( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryItem& CurrentData , const FLFPInventoryItem& ProcessData ) const override;

	virtual bool CanSwapItemOnSlot_Implementation ( const FLFPInventoryItem& FromItem , const FLFPInventoryIndex& FromIndex , const FLFPInventoryItem& ToItem , const FLFPInventoryIndex& ToIndex ) const override;

	virtual bool CanMergeItemOnSlot_Implementation ( const FLFPInventoryItem& FromItem , const FLFPInventoryIndex& FromIndex , const FLFPInventoryItem& ToItem , const FLFPInventoryIndex& ToIndex ) const override;

	virtual bool CanUpdateItemOnSlot_Implementation ( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryItem& CurrentData , const FLFPInventoryItem& ProcessData ) const override;

	virtual bool CanFindItemOnSlot_Implementation ( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryItem& CurrentData , const FLFPInventoryItem& ProcessData ) const override;

	//// Process Modifier

	virtual bool ProcessAddItem_Implementation ( UPARAM ( ref ) FLFPInventoryItem& ItemData , UPARAM ( ref ) FLFPInventoryItem& ProcessData , const FLFPInventoryIndex& InventoryIndex ) override;

	virtual bool ProcessRemoveItem_Implementation ( UPARAM ( ref ) FLFPInventoryItem& ItemData , UPARAM ( ref ) FLFPInventoryItem& ProcessData , const FLFPInventoryIndex& InventoryIndex ) override;

	virtual bool ProcessSwapItem_Implementation ( UPARAM ( ref ) FLFPInventoryItem& FromItem , const FLFPInventoryIndex& FromIndex , UPARAM ( ref ) FLFPInventoryItem& ToItem , const FLFPInventoryIndex& ToIndex ) override;

	virtual bool ProcessMergeItem_Implementation ( UPARAM ( ref ) FLFPInventoryItem& FromItem , const FLFPInventoryIndex& FromIndex , UPARAM ( ref ) FLFPInventoryItem& ToItem , const FLFPInventoryIndex& ToIndex ) override;

	virtual bool ProcessUpdateItem_Implementation ( UPARAM ( ref ) FLFPInventoryItem& ItemData , UPARAM ( ref ) FLFPInventoryItem& ProcessData , const FLFPInventoryIndex& InventoryIndex ) override;

	virtual bool ProcessFindItem_Implementation ( const FLFPInventoryItem& ItemData , UPARAM ( ref ) FLFPInventoryItem& ProcessData , const FLFPInventoryIndex& InventoryIndex ) override;

	//// Categorize Modifier

	virtual FGameplayTagContainer GetItemAllowSlotNameList_Implementation ( const FLFPInventoryItem& ItemData ) const override;

	//// Check Modifier

	virtual bool CanItemSortHigherThan_Implementation ( const FLFPInventoryItem& ItemDataA , const FLFPInventoryItem& ItemDataB , const FGameplayTag& SortTag ) const override;

protected:

	FORCEINLINE const FLFPItemBasicTableData* GetDataTableRow ( const FGameplayTag& RowTag ) const;

	UPROPERTY ( EditDefaultsOnly , BlueprintReadOnly )
	TObjectPtr < UDataRegistry > ItemDataRegister = nullptr;

	UPROPERTY ( EditDefaultsOnly , BlueprintReadOnly , Category = "Setting" )
	FGameplayTag BasicMetaTag = FGameplayTag ( );

	UPROPERTY ( EditDefaultsOnly , BlueprintReadOnly , Category = "Setting" )
	FGameplayTag BasicStackTag = FGameplayTag ( );
};
