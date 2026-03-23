// Copyright (c) 2023-2024 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#include "Item/FunctionObject/LFPItemBasicFunction.h"

#include "DataRegistrySubsystem.h"
#include "LFPItemFunctionLibrary.h"

bool ULFPItemBasicFunction::CanAddItem_Implementation ( const FLFPInventoryItem& ItemData ) const
{
	return GetDataTableRow ( ItemData.GetItemTag ( ) ) != nullptr;
}

bool ULFPItemBasicFunction::CanRemoveItem_Implementation ( const FLFPInventoryItem& ItemData ) const
{
	return GetDataTableRow ( ItemData.GetItemTag ( ) ) != nullptr;
}

bool ULFPItemBasicFunction::CanUpdateItem_Implementation ( const FLFPInventoryItem& ItemData ) const
{
	return GetDataTableRow ( ItemData.GetItemTag ( ) ) != nullptr;
}

bool ULFPItemBasicFunction::CanFindItem_Implementation ( const FLFPInventoryItem& ItemData ) const
{
	return GetDataTableRow ( ItemData.GetItemTag ( ) ) != nullptr;
}

bool ULFPItemBasicFunction::CanAddItemOnSlot_Implementation ( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryItem& CurrentData , const FLFPInventoryItem& ProcessData ) const
{
	// Ensure CurrentData Is Empty Or Match ProcessData Type
	if ( CurrentData.GetItemTag ( ).IsValid ( ) && CurrentData.GetItemTag ( ) != ProcessData.GetItemTag ( ) )
	{
		return false;
	}

	// Get Table Data ///////////////////////////////
	const FLFPItemBasicTableData* TableData = GetDataTableRow ( ProcessData.GetItemTag ( ) );

	if ( TableData == nullptr )
	{
		return false;
	}
	//////////////////////////////////////////////////

	if ( TableData->DoItemAllowOnSlot ( InventoryIndex.SlotName ) == false )
	{
		return false; // Check AllowOnSlot Because The CurrentData Migth Be Empty
	}

	if ( TableData->DoItemMetaMatch ( CurrentData , ProcessData ) == false )
	{
		return false;
	}

	if ( TableData->DoItemReachMaxStack ( CurrentData , BasicMetaTag , BasicStackTag ) )
	{
		return false;
	}

	return true;
}

bool ULFPItemBasicFunction::CanRemoveItemOnSlot_Implementation ( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryItem& CurrentData , const FLFPInventoryItem& ProcessData ) const
{
	// Ensure CurrentData Is Valid And Match ProcessData Type
	if ( CurrentData.GetItemTag ( ).IsValid ( ) == false || CurrentData.GetItemTag ( ) != ProcessData.GetItemTag ( ) )
	{
		return false;
	}

	// Get Table Data ///////////////////////////////
	const FLFPItemBasicTableData* TableData = GetDataTableRow ( ProcessData.GetItemTag ( ) );

	if ( TableData == nullptr )
	{
		return false;
	}
	//////////////////////////////////////////////////

	if ( TableData->DoItemMetaMatch ( CurrentData , ProcessData ) == false )
	{
		return false;
	}

	return true;
}

bool ULFPItemBasicFunction::CanSwapItemOnSlot_Implementation ( const FLFPInventoryItem& FromItem , const FLFPInventoryIndex& FromIndex , const FLFPInventoryItem& ToItem , const FLFPInventoryIndex& ToIndex ) const
{
	const FLFPItemBasicTableData* FromTableData = GetDataTableRow ( FromItem.GetItemTag ( ) );
	const FLFPItemBasicTableData* ToTableData   = GetDataTableRow ( ToItem.GetItemTag ( ) );

	if ( FromTableData != nullptr && FromTableData->DoItemAllowOnSlot ( ToIndex.SlotName ) == false )
	{
		return false;
	}

	if ( ToTableData != nullptr && ToTableData->DoItemAllowOnSlot ( FromIndex.SlotName ) == false )
	{
		return false;
	}

	return true;
}

bool ULFPItemBasicFunction::CanMergeItemOnSlot_Implementation ( const FLFPInventoryItem& FromItem , const FLFPInventoryIndex& FromIndex , const FLFPInventoryItem& ToItem , const FLFPInventoryIndex& ToIndex ) const
{
	/* Same As Add Function */
	return CanAddItemOnSlot ( ToIndex , ToItem , FromItem );
}

bool ULFPItemBasicFunction::CanUpdateItemOnSlot_Implementation ( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryItem& CurrentData , const FLFPInventoryItem& ProcessData ) const
{
	// Ensure CurrentData Is Valid And Match ProcessData Type
	if ( CurrentData.GetItemTag ( ).IsValid ( ) == false || CurrentData.GetItemTag ( ) != ProcessData.GetItemTag ( ) )
	{
		return false;
	}

	// Get Table Data ///////////////////////////////
	const FLFPItemBasicTableData* TableData = GetDataTableRow ( ProcessData.GetItemTag ( ) );

	if ( TableData == nullptr )
	{
		return false;
	}
	//////////////////////////////////////////////////

	return true;
}

bool ULFPItemBasicFunction::CanFindItemOnSlot_Implementation ( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryItem& CurrentData , const FLFPInventoryItem& ProcessData ) const
{
	// Ensure CurrentData Is Valid And Match ProcessData Type
	if ( CurrentData.GetItemTag ( ).IsValid ( ) == false || CurrentData.GetItemTag ( ) != ProcessData.GetItemTag ( ) )
	{
		return false;
	}

	// Get Table Data ///////////////////////////////
	const FLFPItemBasicTableData* TableData = GetDataTableRow ( ProcessData.GetItemTag ( ) );

	if ( TableData == nullptr )
	{
		return false;
	}
	//////////////////////////////////////////////////

	if ( TableData->DoItemMetaMatch ( CurrentData , ProcessData ) == false )
	{
		return false;
	}

	return true;
}

bool ULFPItemBasicFunction::ProcessAddItem_Implementation ( UPARAM ( ref )FLFPInventoryItem& ItemData , UPARAM ( ref )FLFPInventoryItem& ProcessData , const FLFPInventoryIndex& InventoryIndex )
{
	// Get Table Data ///////////////////////////////
	const FLFPItemBasicTableData* TableData = GetDataTableRow ( ProcessData.GetItemTag ( ) );

	if ( TableData == nullptr )
	{
		return false;
	}
	//////////////////////////////////////////////////

	// Process Stack Function ///////////////////////
	const int32 CurrentStack = ItemData.IsValid ( )
	                           ? TableData->GetStackAmount ( ItemData , BasicMetaTag )
	                           : 0;
	const int32 ProcessStack = ProcessData.IsValid ( )
	                           ? TableData->GetStackAmount ( ProcessData , BasicMetaTag )
	                           : 0;

	const int32 NextStack        = TableData->ClampToMaxStack ( CurrentStack + ProcessStack , BasicStackTag );
	const int32 NextProcessStack = ( CurrentStack + ProcessStack ) - NextStack;

	// Check Current Slot Is Empty
	if ( ItemData.IsValid ( ) == false )
	{
		ItemData = ProcessData; // Override ItemData With ProcessData ( Meta Data Include ) This Give All Meta Data That Is Not Stack Into Inventory ( Only Doing This If The Slot Is Empty )
	}

	TableData->SetStackAmount ( ItemData , BasicMetaTag , NextStack );           // Set Item Stack To Correct Number
	TableData->SetStackAmount ( ProcessData , BasicMetaTag , NextProcessStack ); // Decrease Stack On Process Data
	////////////////////////////////////////////////

	/* Clear ProcessData Tag If Stack Is Empty To Prevent It Been Treated As 1 Stack */
	if ( NextProcessStack <= 0 )
	{
		ProcessData = FLFPInventoryItem ( );
	}

	return NextProcessStack <= 0;
}

bool ULFPItemBasicFunction::ProcessRemoveItem_Implementation ( UPARAM ( ref )FLFPInventoryItem& ItemData , UPARAM ( ref )FLFPInventoryItem& ProcessData , const FLFPInventoryIndex& InventoryIndex )
{
	// Get Table Data ///////////////////////////////
	const FLFPItemBasicTableData* TableData = GetDataTableRow ( ProcessData.GetItemTag ( ) );

	if ( TableData == nullptr )
	{
		return false;
	}

	//////////////////////////////////////////////////

	// Process Stack Function ///////////////////////
	const int32 CurrentStack = ItemData.IsValid ( )
	                           ? TableData->GetStackAmount ( ItemData , BasicMetaTag )
	                           : 0;
	const int32 ProcessStack = ProcessData.IsValid ( )
	                           ? TableData->GetStackAmount ( ProcessData , BasicMetaTag )
	                           : 0;

	const int32 NextStack        = CurrentStack - ProcessStack;
	const int32 NextProcessStack = NextStack < 0
	                               ? FMath::Abs ( NextStack )
	                               : 0;

	TableData->SetStackAmount ( ItemData , BasicMetaTag , NextStack );
	TableData->SetStackAmount ( ProcessData , BasicMetaTag , NextProcessStack );
	////////////////////////////////////////////////

	/* If Stack Is Going To Be Empty Than Clear Item */
	if ( NextStack <= 0 )
	{
		ItemData = FLFPInventoryItem ( );
	}

	/* Clear ProcessData Tag If Stack Is Empty To Prevent It Been Treated As 1 Stack */
	if ( NextProcessStack <= 0 )
	{
		ProcessData = FLFPInventoryItem ( );
	}

	return NextProcessStack <= 0;
}

bool ULFPItemBasicFunction::ProcessSwapItem_Implementation ( UPARAM ( ref )FLFPInventoryItem& FromItem , const FLFPInventoryIndex& FromIndex , UPARAM ( ref )FLFPInventoryItem& ToItem , const FLFPInventoryIndex& ToIndex )
{
	FLFPInventoryItem TempItem = FromItem;

	FromItem = ToItem;
	ToItem   = TempItem;

	return true;
}

bool ULFPItemBasicFunction::ProcessMergeItem_Implementation ( UPARAM ( ref )FLFPInventoryItem& FromItem , const FLFPInventoryIndex& FromIndex , UPARAM ( ref )FLFPInventoryItem& ToItem , const FLFPInventoryIndex& ToIndex )
{
	return ProcessAddItem ( ToItem , FromItem , ToIndex );
}

bool ULFPItemBasicFunction::ProcessUpdateItem_Implementation ( UPARAM ( ref )FLFPInventoryItem& ItemData , UPARAM ( ref )FLFPInventoryItem& ProcessData , const FLFPInventoryIndex& InventoryIndex )
{
	// Get Table Data ///////////////////////////////
	const FLFPItemBasicTableData* TableData = GetDataTableRow ( ProcessData.GetItemTag ( ) );

	if ( TableData == nullptr )
	{
		return false;
	}

	//////////////////////////////////////////////////

	const int32 CurrentStack = ItemData.IsValid ( )
	                           ? TableData->GetStackAmount ( ItemData , BasicMetaTag )
	                           : 0;
	const int32 ProcessStack = ProcessData.IsValid ( )
	                           ? TableData->GetStackAmount ( ProcessData , BasicMetaTag )
	                           : 0;

	ItemData = ProcessData; // Override

	TableData->SetStackAmount ( ItemData , BasicMetaTag , CurrentStack );
	TableData->SetStackAmount ( ProcessData , BasicMetaTag , ProcessStack - 1 );

	/* Clear ProcessData Tag If Stack Is Empty To Prevent It Been Treated As 1 Stack */
	if ( ProcessStack - 1 <= 0 )
	{
		ProcessData = FLFPInventoryItem ( );
	}

	return ProcessStack - 1 <= 0;
}

bool ULFPItemBasicFunction::ProcessFindItem_Implementation ( const FLFPInventoryItem& ItemData , UPARAM ( ref )FLFPInventoryItem& ProcessData , const FLFPInventoryIndex& InventoryIndex )
{
	// Get Table Data ///////////////////////////////
	const FLFPItemBasicTableData* TableData = GetDataTableRow ( ProcessData.GetItemTag ( ) );

	if ( TableData == nullptr )
	{
		return false;
	}

	//////////////////////////////////////////////////

	// Process Stack Function ///////////////////////
	const int32 CurrentStack = ItemData.IsValid ( )
	                           ? TableData->GetStackAmount ( ItemData , BasicMetaTag )
	                           : 0;
	const int32 ProcessStack = ProcessData.IsValid ( )
	                           ? TableData->GetStackAmount ( ProcessData , BasicMetaTag )
	                           : 0;

	const int32 NextStack        = CurrentStack - ProcessStack;
	const int32 NextProcessStack = NextStack < 0
	                               ? FMath::Abs ( NextStack )
	                               : 0;

	TableData->SetStackAmount ( ProcessData , BasicMetaTag , NextProcessStack );
	////////////////////////////////////////////////

	/* Clear ProcessData Tag If Stack Is Empty To Prevent It Been Treated As 1 Stack */
	if ( NextProcessStack <= 0 )
	{
		ProcessData = FLFPInventoryItem ( );
	}

	return NextProcessStack <= 0;
}

FGameplayTagContainer ULFPItemBasicFunction::GetItemAllowSlotNameList_Implementation ( const FLFPInventoryItem& ItemData ) const
{
	const FLFPItemBasicTableData* TableData = GetDataTableRow ( ItemData.GetItemTag ( ) );

	if ( TableData == nullptr )
	{
		return FGameplayTagContainer ( );
	}

	return TableData->GetAllowInventorySlotNameList ( );
}

bool ULFPItemBasicFunction::CanItemSortHigherThan_Implementation ( const FLFPInventoryItem& ItemDataA , const FLFPInventoryItem& ItemDataB , const FGameplayTag& SortTag ) const
{
	const FLFPItemBasicTableData* AData = GetDataTableRow ( ItemDataA.GetItemTag ( ) );
	const FLFPItemBasicTableData* BData = GetDataTableRow ( ItemDataB.GetItemTag ( ) );

	if ( AData == nullptr || BData == nullptr )
	{
		return false;
	}

	const int32 CurrentStack = AData->GetStackAmount ( ItemDataA , BasicMetaTag );
	const int32 ProcessStack = BData->GetStackAmount ( ItemDataB , BasicMetaTag );

	return CurrentStack > ProcessStack;
}

const FLFPItemBasicTableData* ULFPItemBasicFunction::GetDataTableRow ( const FGameplayTag& RowTag ) const
{
	if ( IsValid ( ItemDataRegister ) == false )
	{
		return nullptr;
	}

	FDataRegistryId ItemID;
	ItemID.ItemName     = RowTag.GetTagName ( );
	ItemID.RegistryType = ItemDataRegister->GetRegistryType ( );

	const FLFPItemBasicTableData* TableData = ItemDataRegister->GetCachedItem < FLFPItemBasicTableData > ( ItemID );

	if ( TableData == nullptr )
	{
		return nullptr; // Item Is Different Type
	}

	return TableData;
}
