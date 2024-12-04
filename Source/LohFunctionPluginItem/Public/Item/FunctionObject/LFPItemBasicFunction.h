// Copyright (c) 2023-2024 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "CoreMinimal.h"
#include "Item/FunctionObject/LFPItemInventoryFunction.h"
#include "LFPItemBasicFunction.generated.h"

USTRUCT( Blueprintable )
struct FLFPItemBasicData : public FTableRowBase
{
	GENERATED_BODY()

protected:

	/* Maximum Stack An Item Can Reach, Use -1 If Infinite */
	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Default|Stack" )
	uint8 MaxStack = 255;

	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Default|Attach" )
	FGameplayTag AttachSlotsTag = FGameplayTag();

	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Default|Attach" )
	int32 MaxAttachSlots = INDEX_NONE;

	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Default" )
	FGameplayTagContainer AllowedInventorySlotNameList = FGameplayTagContainer();

	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = "Default" )
	FGameplayTagContainer Categorize = FGameplayTagContainer();

public:

	FORCEINLINE bool DoItemAllowOnSlot( const FGameplayTag& SlotName ) const
	{
		return SlotName.MatchesAny( AllowedInventorySlotNameList );
	}

	FORCEINLINE bool DoItemReachMaxStack( const FLFPInventoryItem& CurrentData ) const
	{
		return CurrentData.IsValid() && MaxStack <= ( CurrentData.GetMetaData().IsValidIndex( 0 ) ? CurrentData.GetMetaData()[ 0 ] : 0 );
	}


	FORCEINLINE uint8 GetStackAmount( const FLFPInventoryItem& CurrentData ) const
	{
		return CurrentData.GetMetaData().IsValidIndex( 0 ) ? CurrentData.GetMetaData()[ 0 ] : 0;
	}

	FORCEINLINE void SetStackAmount( FLFPInventoryItem& CurrentData , const uint8 NewStack ) const
	{
		TArray<uint8> NewMetaData = CurrentData.GetMetaData();

		if ( NewMetaData.IsValidIndex( 0 ) == false )
		{
			NewMetaData.Add( NewStack );
		}
		else
		{
			NewMetaData[ 0 ] = NewStack;
		}

		ULFPItemFunctionLibrary::SetMetaData( CurrentData , NewMetaData );
	}

	FORCEINLINE uint8 ClampToMaxStack( const uint8 Stack ) const
	{
		return FMath::Min( MaxStack , Stack );
	}


	FORCEINLINE const FGameplayTagContainer& GetAllowInventorySlotNameList() const
	{
		return AllowedInventorySlotNameList;
	}

	FORCEINLINE const FGameplayTagContainer& GetCategorize() const
	{
		return Categorize;
	}
};

/**
 *
 */
UCLASS( BlueprintType )
class LOHFUNCTIONPLUGINITEM_API ULFPItemBasicFunction : public ULFPItemInventoryFunction
{
	GENERATED_BODY()

public:

	virtual bool CanAddItem_Implementation( const FLFPInventoryItem& ItemData ) const override;

	virtual bool CanRemoveItem_Implementation( const FLFPInventoryItem& ItemData ) const override;

	virtual bool CanUpdateItem_Implementation( const FLFPInventoryItem& ItemData ) const override;

	virtual bool CanFindItem_Implementation( const FLFPInventoryItem& ItemData ) const override;


	virtual bool CanAddItemOnSlot_Implementation( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryItem& CurrentData , const FLFPInventoryItem& ProcessData ) const override;

	virtual bool CanRemoveItemOnSlot_Implementation( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryItem& CurrentData , const FLFPInventoryItem& ProcessData ) const override;

	virtual bool CanSwapItemOnSlot_Implementation( const FLFPInventoryItem& FromItem , const FLFPInventoryIndex& FromIndex , const FLFPInventoryItem& ToItem , const FLFPInventoryIndex& ToIndex ) const override;

	virtual bool CanMergeItemOnSlot_Implementation( const FLFPInventoryItem& FromItem , const FLFPInventoryIndex& FromIndex , const FLFPInventoryItem& ToItem , const FLFPInventoryIndex& ToIndex ) const override;

	virtual bool CanUpdateItemOnSlot_Implementation( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryItem& CurrentData , const FLFPInventoryItem& ProcessData ) const override;

	virtual bool CanFindItemOnSlot_Implementation( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryItem& CurrentData , const FLFPInventoryItem& ProcessData ) const override;

	//// Process Modifier

	virtual bool ProcessAddItem_Implementation( UPARAM( ref ) FLFPInventoryItem& ItemData , UPARAM( ref ) FLFPInventoryItem& ProcessData , const FLFPInventoryIndex InventoryIndex ) const override;

	virtual bool ProcessRemoveItem_Implementation( UPARAM( ref ) FLFPInventoryItem& ItemData , UPARAM( ref ) FLFPInventoryItem& ProcessData , const FLFPInventoryIndex InventoryIndex ) const override;

	virtual bool ProcessSwapItem_Implementation( UPARAM( ref ) FLFPInventoryItem& FromItem , const FLFPInventoryIndex& FromIndex , UPARAM( ref ) FLFPInventoryItem& ToItem , const FLFPInventoryIndex& ToIndex ) const override;

	virtual bool ProcessMergeItem_Implementation( UPARAM( ref ) FLFPInventoryItem& FromItem , const FLFPInventoryIndex& FromIndex , UPARAM( ref ) FLFPInventoryItem& ToItem , const FLFPInventoryIndex& ToIndex ) const override;

	virtual bool ProcessUpdateItem_Implementation( UPARAM( ref ) FLFPInventoryItem& ItemData , UPARAM( ref ) FLFPInventoryItem& ProcessData , const FLFPInventoryIndex InventoryIndex ) const override;

	virtual bool ProcessFindItem_Implementation( const FLFPInventoryItem& ItemData , UPARAM( ref ) FLFPInventoryItem& ProcessData , const FLFPInventoryIndex InventoryIndex ) const override;

	//// Categorize Modifier

	virtual FGameplayTagContainer GetItemAllowSlotNameList_Implementation( const FLFPInventoryItem& ItemData ) const override;

	//// Check Modifier

	virtual bool CanItemSortHigherThan_Implementation( const FLFPInventoryItem& ItemDataA , const FLFPInventoryItem& ItemDataB , const FGameplayTag& SortTag ) const override;

protected:

	FORCEINLINE const FLFPItemBasicData* GetDataTableRow( const FGameplayTag& RowTag ) const;

protected:

	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , Category = "LFPItemBasicFunction | Setting" , meta = ( RequiredAssetDataTags = "RowStructure=/Script/LohFunctionPluginItem.LFPItemBasicData" ) )
	TObjectPtr<UDataTable> ItemDataTable = nullptr;

};
