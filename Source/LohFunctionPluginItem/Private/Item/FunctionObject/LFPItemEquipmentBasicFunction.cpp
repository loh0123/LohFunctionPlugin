// Copyright by LOH ZHI KANG


#include "Item/FunctionObject/LFPItemEquipmentBasicFunction.h"

#include "Net/UnrealNetwork.h"

void ULFPItemEquipmentBasicFunction::GetLifetimeReplicatedProps ( TArray < FLifetimeProperty >& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps ( OutLifetimeProps );

	DOREPLIFETIME_CONDITION_NOTIFY ( ULFPItemEquipmentBasicFunction , SelectedIndex , COND_None , REPNOTIFY_Always );
}

void ULFPItemEquipmentBasicFunction::InitializeComponent ( )
{
	Super::InitializeComponent ( );

	GetOwner ( )->OnItemChange.AddDynamic ( this , &ULFPItemEquipmentBasicFunction::OnInventoryUpdateItem );
}

void ULFPItemEquipmentBasicFunction::UninitializeComponent ( )
{
	Super::UninitializeComponent ( );

	GetOwner ( )->OnItemChange.RemoveDynamic ( this , &ULFPItemEquipmentBasicFunction::OnInventoryUpdateItem );
}

void ULFPItemEquipmentBasicFunction::SelectIndex ( const int32 Index )
{
	SelectedIndex = Index;
}

int32 ULFPItemEquipmentBasicFunction::GetSelectedIndex ( ) const
{
	return SelectedIndex;
}

void ULFPItemEquipmentBasicFunction::OnInventoryUpdateItem ( const TArray < FLFPInventoryItemOperationData >& ItemOperationDataList )
{
	for ( const FLFPInventoryItemOperationData& ItemOperationData : ItemOperationDataList )
	{
		/* Not Currently Selected */
		if ( HandleSlotTag != ItemOperationData.InventoryIndex.SlotName || ( SelectedIndex != ItemOperationData.InventoryIndex.SlotItemIndex && SelectedIndex > INDEX_NONE ) )
		{
			return;
		}

		if ( ItemOperationData.OldData.IsValid ( ) )
		{
			OnUnequipItem.Broadcast ( ItemOperationData );
		}

		if ( GetOwner ( )->GetSlotItem ( ItemOperationData.InventoryIndex ).IsValid ( ) )
		{
			OnEquipItem.Broadcast ( ItemOperationData.InventoryIndex );
		}
	}
}

void ULFPItemEquipmentBasicFunction::OnRep_SelectedIndex ( const int32& OldValue ) const
{
	if ( OldValue == SelectedIndex || ( SelectedIndex <= INDEX_NONE && OldValue <= INDEX_NONE ) )
	{
		return;
	}

	if ( OldValue <= INDEX_NONE )
	{
		for ( int32 Index = 0 ; Index < GetOwner ( )->GetSlotItemNum ( HandleSlotTag ) ; ++Index )
		{
			const FLFPInventoryIndex InventoryIndex ( Index , HandleSlotTag );

			if ( const FLFPInventoryItem& CurrentItem = GetOwner ( )->GetSlotItem ( InventoryIndex ) ; CurrentItem.IsValid ( ) )
			{
				FLFPInventoryItemOperationData UnequipEventData ( ELFPInventoryItemEventType::Inventory_None , InventoryIndex , CurrentItem , FGameplayTag::EmptyTag );

				OnUnequipItem.Broadcast ( UnequipEventData );
			}
		}
	}
	else if ( const FLFPInventoryItem& CurrentItem = GetOwner ( )->GetSlotItem ( FLFPInventoryIndex ( OldValue , HandleSlotTag ) ) ; CurrentItem.IsValid ( ) )
	{
		FLFPInventoryItemOperationData UnequipEventData ( ELFPInventoryItemEventType::Inventory_None , FLFPInventoryIndex ( OldValue , HandleSlotTag ) , CurrentItem , FGameplayTag::EmptyTag );

		OnUnequipItem.Broadcast ( UnequipEventData );
	}

	if ( SelectedIndex <= INDEX_NONE )
	{
		for ( int32 Index = 0 ; Index < GetOwner ( )->GetSlotItemNum ( HandleSlotTag ) ; ++Index )
		{
			if ( const FLFPInventoryIndex InventoryIndex ( Index , HandleSlotTag ) ; GetOwner ( )->GetSlotItem ( InventoryIndex ).IsValid ( ) )
			{
				OnEquipItem.Broadcast ( InventoryIndex );
			}
		}
	}
	else if ( GetOwner ( )->GetSlotItem ( FLFPInventoryIndex ( SelectedIndex , HandleSlotTag ) ).IsValid ( ) )
	{
		OnEquipItem.Broadcast ( FLFPInventoryIndex ( SelectedIndex , HandleSlotTag ) );
	}
}
