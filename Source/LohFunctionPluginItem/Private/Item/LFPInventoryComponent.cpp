// Copyright (c) 2023-2024 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#include "Item/LFPInventoryComponent.h"
#include "Item/FunctionObject/LFPItemInventoryFunction.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY( LFPInventoryComponent );


// Sets default values for this component's properties
ULFPInventoryComponent::ULFPInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}


// Called when the game starts
void ULFPInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	/* For Supporting Function List Object Replication */
	if ( GetIsReplicated() )
	{
		ProcessInventoryFunction(
			[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
			{
				check( FunctionObj.Get()->GetOuter() );

				AddReplicatedSubObject( FunctionObj.Get() );

				FunctionObj.Get()->InitializeComponent();

				return true;
			}
		);
	}
	////////////////////////////////////////////////////
}

void ULFPInventoryComponent::EndPlay( const EEndPlayReason::Type EndPlayReason )
{
	Super::EndPlay( EndPlayReason );

	/* For Supporting Function List Object Replication */
	if ( GetIsReplicated() )
	{
		ProcessInventoryFunction(
			[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
			{
				RemoveReplicatedSubObject( FunctionObj.Get() );

				FunctionObj.Get()->UninitializeComponent();

				return true;
			}
		);
	}
	////////////////////////////////////////////////////
}

void ULFPInventoryComponent::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( ULFPInventoryComponent , InventorySlot );

	DOREPLIFETIME( ULFPInventoryComponent , FunctionList );
}

// Called every frame
void ULFPInventoryComponent::TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime , TickType , ThisTickFunction );

	// ...
}

bool ULFPInventoryComponent::ReplicateSubobjects( UActorChannel* Channel , FOutBunch* Bunch , FReplicationFlags* RepFlags )
{
#if SUBOBJECT_TRANSITION_VALIDATION
	if ( UActorChannel::CanIgnoreDeprecatedReplicateSubObjects() )
	{
		return false;
	}
#endif

	Super::ReplicateSubobjects( Channel , Bunch , RepFlags );

	/* For Supporting Function List Object Replication */
	return ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			Channel->ReplicateSubobject( FunctionObj.Get() , *Bunch , *RepFlags );

			return true;
		}
	);
	////////////////////////////////////////////////////
}

void ULFPInventoryComponent::Activate( bool bReset )
{
	Super::Activate( bReset );

	if ( bReset )
	{
		FGameplayTagContainer SlotNameList;

		for ( const auto& InventorySlotData : InventorySlot.GetSlotListConst() )
		{
			SlotNameList.AddTag( InventorySlotData.SlotName );
		}

		ClearInventory( SlotNameList , FGameplayTag() );

		ProcessInventoryFunction(
			[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
			{
				FunctionObj->Reset();

				return true;
			}
		);
	}
}

void ULFPInventoryComponent::SendItemDelegateEvent( const FLFPInventoryItemOperationData& ItemOperationData ) const
{
	if ( GetOwner()->HasAuthority() == false ) return;

	OnItemChange.Broadcast( ItemOperationData );

	CLIENT_SendItemDelegateEvent( ItemOperationData );
}

void ULFPInventoryComponent::CLIENT_SendItemDelegateEvent_Implementation( const FLFPInventoryItemOperationData& ItemOperationData ) const
{
	/* Prevent This To Run Again On Singel Player */
	if ( GetOwner()->GetLocalRole() == ROLE_SimulatedProxy )
	{
		OnItemChange.Broadcast( ItemOperationData );
	}
}

const FLFPInventorySlotList& ULFPInventoryComponent::GetInventorySlotList() const
{
	return InventorySlot;
}

bool ULFPInventoryComponent::ProcessInventoryIndex(
	const FGameplayTagContainer& InventorySlotNameList ,
	const TFunctionRef<bool( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryInternalIndex& InventoryInternalIndex )>& IndexFunction ,
	const bool bUseMaxIndex ,
	const TFunction<void( const int32 SlotListIndex )> OnSlotNameEnd
) const
{
	UE_LOG( LFPInventoryComponent , VeryVerbose , TEXT( "ProcessInventoryIndex Start" ) );

	for ( int32 SlotDataIndex = 0; SlotDataIndex < InventorySlot.GetSlotListConst().Num(); SlotDataIndex++ )
	{
		const FLFPInventorySlot& SlotData = InventorySlot.GetSlotListConst()[ SlotDataIndex ];

		if ( SlotData.SlotName.MatchesAny( InventorySlotNameList ) == false )
		{
			UE_LOG( LFPInventoryComponent , Verbose , TEXT( "ProcessInventoryIndex Skip Slot Bacause Name Not Match : %s" ) , *InventorySlotNameList.ToString() );

			continue; // Tag Not Match Any One On Search
		}

		//
		const int32 MaxIndex = bUseMaxIndex ?
			SlotData.GetMaxNum( ExtraLoopSlot )
			:
			SlotData.GetItemNum( ExtraLoopSlot )
			;
		//

		UE_LOG( LFPInventoryComponent , Verbose , TEXT( "ProcessInventoryIndex SlotData Start : Name = %s | EndIndex = %d" ) , *SlotData.SlotName.ToString() , MaxIndex );

		for ( int32 Index = 0; Index < MaxIndex; Index++ )
		{
			const FLFPInventoryIndex InventoryIndex( Index , SlotData.SlotName );
			const FLFPInventoryInternalIndex InventoryInternalIndex( ( InventorySlot.ToInventoryIndexInternal( FLFPInventoryIndex( Index , SlotData.SlotName ) ) ) );

			if ( InventoryInternalIndex.IsValid() == false ) continue;

			if ( IndexFunction( InventoryIndex , InventoryInternalIndex ) )
			{
				UE_LOG( LFPInventoryComponent , Verbose , TEXT( "ProcessInventoryIndex Success : %s" ) , *InventoryIndex.ToString() );

				if ( OnSlotNameEnd ) OnSlotNameEnd( SlotDataIndex );

				return true;
			}
		}

		UE_LOG( LFPInventoryComponent , Verbose , TEXT( "ProcessInventoryIndex SlotData End : %s" ) , *SlotData.SlotName.ToString() );

		if ( OnSlotNameEnd ) OnSlotNameEnd( SlotDataIndex );
	}

	UE_LOG( LFPInventoryComponent , VeryVerbose , TEXT( "ProcessInventoryIndex Fail" ) );

	return false;
}

bool ULFPInventoryComponent::ProcessItemOperation(
	const FGameplayTagContainer& InventorySlotNameList ,
	TArray<FLFPInventoryItem>& ItemDataList ,
	const TFunctionRef<bool( const FLFPInventoryItem& ItemData )>& CheckerFunction ,
	const TFunctionRef<bool( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryInternalIndex& InternalIndex , FLFPInventoryItem& ItemData )>& IndexFunction ,
	const bool bStopOnFail ,
	const bool bUseMaxIndex
) const
{
	bool bIsSuccess = true;

	for ( FLFPInventoryItem& ItemData : ItemDataList )
	{
		if ( ItemData.IsValid() == false )
		{
			UE_LOG( LFPInventoryComponent , Warning , TEXT( "ProcessItemOperation Skip Invalid Item" ) );

			continue;
		}

		if ( CheckerFunction( ItemData ) == false )
		{
			bIsSuccess = false;

			if ( bStopOnFail )
			{
				return bIsSuccess;
			}

			continue;
		}

		/* Filter Out Disallow Slot Name List */
		const FGameplayTagContainer ItemAllowSlotNameList = GetItemAllowSlotNameList( ItemData , InventorySlotNameList );

		bIsSuccess = bIsSuccess && ProcessInventoryIndex(
			ItemAllowSlotNameList ,
			[&] ( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryInternalIndex& InventoryInternalIndex )
			{
				return IndexFunction( InventoryIndex , InventoryInternalIndex , ItemData );
			} ,
			bUseMaxIndex
		);

		if ( bStopOnFail && bIsSuccess == false )
		{
			return bIsSuccess;
		}
	}

	return bIsSuccess;
}

bool ULFPInventoryComponent::ProcessSingleItemOperation(
	const FGameplayTagContainer& InventorySlotNameList ,
	FLFPInventoryItem& ItemData ,
	const TFunctionRef<bool( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryInternalIndex& InternalIndex , FLFPInventoryItem& ItemData )>& IndexFunction ,
	const bool bUseMaxIndex
) const
{
	bool bIsSuccess = true;

	if ( ItemData.IsValid() == false )
	{
		UE_LOG( LFPInventoryComponent , Warning , TEXT( "ProcessSingleItemOperation Skip Invalid Item" ) );

		return false;
	}

	/* Filter Out Disallow Slot Name List */
	const FGameplayTagContainer ItemAllowSlotNameList = GetItemAllowSlotNameList( ItemData , InventorySlotNameList );

	return ProcessInventoryIndex(
		ItemAllowSlotNameList ,
		[&] ( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryInternalIndex& InventoryInternalIndex )
		{
			return IndexFunction( InventoryIndex , InventoryInternalIndex , ItemData );
		} ,
		bUseMaxIndex
	);
}

bool ULFPInventoryComponent::ProcessInventoryFunction( const TFunctionRef<bool( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )> RunFunction ) const
{
	for ( const auto& FunctionObj : FunctionList )
	{
		if ( IsValid( FunctionObj ) == false )
		{
			UE_LOG( LFPInventoryComponent , Warning , TEXT( "InitializeComponent : FunctionObj Invalids" ) );

			continue;
		}

		if ( RunFunction( FunctionObj ) == false ) return false;
	}

	if ( FunctionList.IsEmpty() )
	{
		UE_LOG( LFPInventoryComponent , Warning , TEXT( "ProcessInventoryFunction FunctionList Is Empty" ) );

		return false;
	}

	return true;
}


bool ULFPInventoryComponent::AddItem_Index_Uncheck_Internal( const FLFPInventoryIndex& InventoryIndex , FLFPInventoryItem& ProcessItemData , const FGameplayTag& EventTag )
{
	const FLFPInventoryInternalIndex InventoryInternalIndex( ( InventorySlot.ToInventoryIndexInternal( InventoryIndex ) ) );

	if ( InventoryInternalIndex.IsValid() == false ) return false;

	FLFPInventoryItem OldItemData = InventorySlot.GetSlotItemConst( InventoryInternalIndex );

	if ( CanAddItemOnSlot( InventoryIndex , OldItemData , ProcessItemData ) == false ) return false;

	FLFPInventoryItem& NewItemData = InventorySlot.GetSlotItemRef( InventoryInternalIndex , true );

	const bool bSuccess = ProcessAddItem( NewItemData , ProcessItemData , InventoryIndex );

	InventorySlot.AddPendingEvent( FLFPInventoryItemOperationData( ELFPInventoryItemEventType::Inventory_Add , InventoryIndex , NewItemData , OldItemData , EventTag ) );

	return bSuccess;
}

bool ULFPInventoryComponent::AddItem_SlotName_Internal( const FGameplayTagContainer& InventorySlotNameList , FLFPInventoryItem& ProcessItemData , const FGameplayTag& EventTag )
{
	if ( CanAddItem( ProcessItemData ) == false )
	{
		return false;
	}

	return ProcessSingleItemOperation(
		InventorySlotNameList ,
		ProcessItemData ,
		[&] ( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryInternalIndex& InventoryInternalIndex , FLFPInventoryItem& ItemData )
		{
			return AddItem_Index_Uncheck_Internal( InventoryIndex , ItemData , EventTag );
		} ,
		true
	);
}

bool ULFPInventoryComponent::AddItemList_SlotName_Internal( const FGameplayTagContainer& InventorySlotNameList , TArray<FLFPInventoryItem>& ItemDataList , const bool bStopOnFail , const FGameplayTag& EventTag )
{
	return ProcessItemOperation(
		InventorySlotNameList ,
		ItemDataList ,
		[&] ( const FLFPInventoryItem& ItemData )
		{
			return CanAddItem( ItemData );
		} ,
		[&] ( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryInternalIndex& InventoryInternalIndex , FLFPInventoryItem& ItemData )
		{
			return AddItem_Index_Uncheck_Internal( InventoryIndex , ItemData , EventTag );
		} ,
		bStopOnFail ,
		true
	);
}

bool ULFPInventoryComponent::RemoveItem_Index_Uncheck_Internal( const FLFPInventoryIndex& InventoryIndex , FLFPInventoryItem& ProcessItemData , const FGameplayTag& EventTag )
{
	if ( CanRemoveItem( ProcessItemData ) == false )
	{
		return false;
	}

	const FLFPInventoryInternalIndex InventoryInternalIndex( ( InventorySlot.ToInventoryIndexInternal( InventoryIndex ) ) );

	if ( InventoryInternalIndex.IsValid() == false ) return false;

	FLFPInventoryItem OldItemData = InventorySlot.GetSlotItemConst( InventoryInternalIndex );

	if ( CanRemoveItemOnSlot( InventoryIndex , OldItemData , ProcessItemData ) == false ) return false;

	FLFPInventoryItem& NewItemData = InventorySlot.GetSlotItemRef( InventoryInternalIndex , true );

	const bool bSuccess = ProcessRemoveItem( NewItemData , ProcessItemData , InventoryIndex );

	InventorySlot.AddPendingEvent( FLFPInventoryItemOperationData( ELFPInventoryItemEventType::Inventory_Remove , InventoryIndex , NewItemData , OldItemData , EventTag ) );

	return bSuccess;
}

bool ULFPInventoryComponent::RemoveItem_SlotName_Internal( const FGameplayTagContainer& InventorySlotNameList , FLFPInventoryItem& ProcessItemData , const FGameplayTag& EventTag )
{
	if ( CanRemoveItem( ProcessItemData ) == false )
	{
		return false;
	}

	return ProcessSingleItemOperation(
		InventorySlotNameList ,
		ProcessItemData ,
		[&] ( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryInternalIndex& InventoryInternalIndex , FLFPInventoryItem& ItemData )
		{
			return RemoveItem_Index_Uncheck_Internal( InventoryIndex , ItemData , EventTag );
		} ,
		true
	);
}

bool ULFPInventoryComponent::RemoveItemList_SlotName_Internal( const FGameplayTagContainer& InventorySlotNameList , TArray<FLFPInventoryItem>& ItemDataList , const bool bStopOnFail , const FGameplayTag& EventTag )
{
	return ProcessItemOperation(
		InventorySlotNameList ,
		ItemDataList ,
		[&] ( const FLFPInventoryItem& ItemData )
		{
			return CanRemoveItem( ItemData );
		} ,
		[&] ( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryInternalIndex& InventoryInternalIndex , FLFPInventoryItem& ItemData )
		{
			return RemoveItem_Index_Uncheck_Internal( InventoryIndex , ItemData , EventTag );
		} ,
		bStopOnFail ,
		true
	);
}

bool ULFPInventoryComponent::SwapItem_Index_Internal( const FLFPInventoryInternalIndex& FromIndex , const FLFPInventoryInternalIndex& ToIndex , const FGameplayTag& EventTag )
{
	if ( FromIndex == ToIndex ) return false;

	if ( FromIndex.IsValid() == false ) return false;
	if ( ToIndex.IsValid() == false ) return false;

	const FLFPInventoryItem& CopyFromItem = InventorySlot.GetSlotItemConst( FromIndex );
	const FLFPInventoryItem& CopyToItem = InventorySlot.GetSlotItemConst( ToIndex );

	if ( CanSwapItemOnSlot( CopyFromItem , FromIndex.ToInventoryIndex() , CopyToItem , ToIndex.ToInventoryIndex() ) == false ) return false;

	FLFPInventoryItem& FromData = InventorySlot.GetSlotItemRef( FromIndex , true );
	FLFPInventoryItem& ToData = InventorySlot.GetSlotItemRef( ToIndex , true );

	const bool bSuccess = ProcessSwapItem( FromData , FromIndex.ToInventoryIndex() , ToData , ToIndex.ToInventoryIndex() );

	InventorySlot.AddPendingEvent( FLFPInventoryItemOperationData( ELFPInventoryItemEventType::Inventory_Swap , FromIndex.ToInventoryIndex() , FromData , CopyFromItem , EventTag ) );
	InventorySlot.AddPendingEvent( FLFPInventoryItemOperationData( ELFPInventoryItemEventType::Inventory_Swap , ToIndex.ToInventoryIndex() , ToData , CopyToItem , EventTag ) );

	return bSuccess;
}

bool ULFPInventoryComponent::MergeItem_Index_Internal( const FLFPInventoryInternalIndex& FromIndex , const FLFPInventoryInternalIndex& ToIndex , const FGameplayTag& EventTag )
{
	if ( FromIndex == ToIndex ) return false;

	if ( FromIndex.IsValid() == false ) return false;
	if ( ToIndex.IsValid() == false ) return false;

	const FLFPInventoryItem& CopyFromItem = InventorySlot.GetSlotItemConst( FromIndex );
	const FLFPInventoryItem& CopyToItem = InventorySlot.GetSlotItemConst( ToIndex );

	if ( CanMergeItemOnSlot( CopyFromItem , FromIndex.ToInventoryIndex() , CopyToItem , ToIndex.ToInventoryIndex() ) == false ) return false;

	FLFPInventoryItem& FromData = InventorySlot.GetSlotItemRef( FromIndex , true );
	FLFPInventoryItem& ToData = InventorySlot.GetSlotItemRef( ToIndex , true );

	const bool bSuccess = ProcessMergeItem( FromData , FromIndex.ToInventoryIndex() , ToData , ToIndex.ToInventoryIndex() );

	InventorySlot.AddPendingEvent( FLFPInventoryItemOperationData( ELFPInventoryItemEventType::Inventory_Merge , FromIndex.ToInventoryIndex() , FromData , CopyFromItem , EventTag ) );
	InventorySlot.AddPendingEvent( FLFPInventoryItemOperationData( ELFPInventoryItemEventType::Inventory_Merge , ToIndex.ToInventoryIndex() , ToData , CopyToItem , EventTag ) );

	return bSuccess;
}

bool ULFPInventoryComponent::MergeItem_SlotName_Internal( const FLFPInventoryIndex& FromIndex , const FGameplayTagContainer& ToSlotNameList , const FGameplayTag& EventTag )
{
	const FLFPInventoryInternalIndex FromIndexInternal = InventorySlot.ToInventoryIndexInternal( FromIndex );

	return ProcessSingleItemOperation(
		ToSlotNameList ,
		InventorySlot.GetSlotItemRef( FromIndexInternal , true ) ,
		[&] ( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryInternalIndex& InventoryInternalIndex , FLFPInventoryItem& ItemData )
		{
			return MergeItem_Index_Internal( FromIndexInternal , InventoryInternalIndex , EventTag );
		} ,
		true
	);;
}

bool ULFPInventoryComponent::Transfer_Index_Internal( const FLFPInventoryIndex& FromIndex , const FLFPInventoryIndex& ToIndex , ULFPInventoryComponent* TargetInventoryComponent , const bool bMustFullyTransfer , const FGameplayTag& EventTag )
{
	const FLFPInventoryInternalIndex FromInventoryInternalIndex( ( InventorySlot.ToInventoryIndexInternal( FromIndex ) ) );

	if ( FromInventoryInternalIndex.IsValid() == false ) return false;

	if ( InventorySlot.IsSlotItemValid( FromInventoryInternalIndex ) == false ) return false;

	FLFPInventoryItem& RefOfFrom = InventorySlot.GetSlotItemRef( FromInventoryInternalIndex , true );
	FLFPInventoryItem CopyOfFrom = RefOfFrom;

	if ( CanTransferItemOnSlot( FromIndex , RefOfFrom ) == false ) return false;

	const bool bSuccess = TargetInventoryComponent->AddItemByIndex( ToIndex , RefOfFrom , bMustFullyTransfer , EventTag );

	InventorySlot.AddPendingEvent( FLFPInventoryItemOperationData( ELFPInventoryItemEventType::Inventory_Transfer , FromIndex , RefOfFrom , CopyOfFrom , EventTag ) );

	return bSuccess;
}

bool ULFPInventoryComponent::Transfer_SlotName_Internal( const FLFPInventoryIndex& FromIndex , const FGameplayTagContainer& ToSlotNameList , ULFPInventoryComponent* TargetInventoryComponent , const bool bMustFullyTransfer , const FGameplayTag& EventTag )
{
	const FLFPInventoryInternalIndex FromInventoryInternalIndex( ( InventorySlot.ToInventoryIndexInternal( FromIndex ) ) );

	if ( FromInventoryInternalIndex.IsValid() == false ) return false;

	if ( InventorySlot.IsSlotItemValid( FromInventoryInternalIndex ) == false ) return false;

	FLFPInventoryItem& RefOfFrom = InventorySlot.GetSlotItemRef( FromInventoryInternalIndex , true );
	FLFPInventoryItem CopyOfFrom = RefOfFrom;

	if ( CanTransferItemOnSlot( FromIndex , RefOfFrom ) == false ) return false;

	const bool bSuccess = TargetInventoryComponent->AddItemBySlotName( ToSlotNameList , RefOfFrom , bMustFullyTransfer , EventTag );

	InventorySlot.AddPendingEvent( FLFPInventoryItemOperationData( ELFPInventoryItemEventType::Inventory_Transfer , FromIndex , RefOfFrom , CopyOfFrom , EventTag ) );

	return bSuccess;
}

bool ULFPInventoryComponent::UpdateItem_Index_Uncheck_Internal( const FLFPInventoryIndex& InventoryIndex , FLFPInventoryItem& ProcessItemData , const FGameplayTag& EventTag )
{
	const FLFPInventoryInternalIndex InventoryInternalIndex( ( InventorySlot.ToInventoryIndexInternal( InventoryIndex ) ) );

	if ( InventoryInternalIndex.IsValid() == false ) return false;

	if ( CanUpdateItemOnSlot( InventoryIndex , InventorySlot.GetSlotItemConst( InventoryInternalIndex ) , ProcessItemData ) == false ) return false;

	FLFPInventoryItem OldItemData = InventorySlot.GetSlotItemConst( InventoryInternalIndex );
	FLFPInventoryItem& NewItemData = InventorySlot.GetSlotItemRef( InventoryInternalIndex , true );

	const bool bSuccess = ProcessUpdateItem( NewItemData , ProcessItemData , InventoryIndex );

	InventorySlot.AddPendingEvent( FLFPInventoryItemOperationData( ELFPInventoryItemEventType::Inventory_Update , InventoryIndex , NewItemData , OldItemData , EventTag ) );

	return bSuccess;
}

bool ULFPInventoryComponent::UpdateItem_SlotName_Internal( const FGameplayTagContainer& InventorySlotNameList , FLFPInventoryItem& ProcessItemData , const FGameplayTag& EventTag )
{
	if ( CanUpdateItem( ProcessItemData ) == false )
	{
		return false;
	}

	return ProcessSingleItemOperation(
		InventorySlotNameList ,
		ProcessItemData ,
		[&] ( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryInternalIndex& InventoryInternalIndex , FLFPInventoryItem& ItemData )
		{
			return UpdateItem_Index_Uncheck_Internal( InventoryIndex , ItemData , EventTag );
		} ,
		true
	);
}

bool ULFPInventoryComponent::ContainItem_Index_Internal( const FLFPInventoryInternalIndex& InventoryInternalIndex , FLFPInventoryItem& ProcessItemData ) const
{
	if ( CanFindItemOnSlot( InventoryInternalIndex.ToInventoryIndex() , InventorySlot.GetSlotItemConst( InventoryInternalIndex ) , ProcessItemData ) == false )
	{
		return false;
	}

	return ProcessFindItem( InventorySlot.GetSlotItemConst( InventoryInternalIndex ) , ProcessItemData , InventoryInternalIndex.ToInventoryIndex() );
}

bool ULFPInventoryComponent::FindItem_Index_Internal( const FLFPInventoryInternalIndex& InventoryInternalIndex , FLFPInventoryItem& ProcessItemData ) const
{
	if ( CanFindItemOnSlot( InventoryInternalIndex.ToInventoryIndex() , InventorySlot.GetSlotItemConst( InventoryInternalIndex ) , ProcessItemData ) == false )
	{
		return false;
	}

	ProcessFindItem( InventorySlot.GetSlotItemConst( InventoryInternalIndex ) , ProcessItemData , InventoryInternalIndex.ToInventoryIndex() );

	return true;
}

void ULFPInventoryComponent::ApplyInventoryPendingChange()
{
	InventorySlot.ApplyPendingChange( [&] ( const FLFPInventoryItemOperationData& OperationData ) { SendItemDelegateEvent( OperationData ); } );
}

void ULFPInventoryComponent::ClearInventoryPendingChange()
{
	InventorySlot.ClearPendingChange();
}


bool ULFPInventoryComponent::AddItem( UPARAM( ref ) FLFPInventoryItem& ItemData , const bool bMustFullyAdd , const FGameplayTag EventTag )
{
	return AddItemBySlotName( GetItemAllowSlotNameList( ItemData ) , ItemData , bMustFullyAdd , EventTag );
}

bool ULFPInventoryComponent::AddItemList( UPARAM( ref ) TArray<FLFPInventoryItem>& ItemDataList , const bool bMustFullyAdd , const FGameplayTag EventTag )
{
	FGameplayTagContainer SearchSlotNameList = FGameplayTagContainer();

	bool bIsSuccess = true;

	for ( FLFPInventoryItem& ItemData : ItemDataList )
	{
		SearchSlotNameList.AppendTags( GetItemAllowSlotNameList( ItemData ) );
	}

	return AddItemListBySlotName( SearchSlotNameList , ItemDataList , bMustFullyAdd , EventTag );
}

bool ULFPInventoryComponent::AddItemBySlotName( UPARAM( meta = ( Categories = "Item.SlotName" ) )const FGameplayTagContainer InventorySlotNameList , UPARAM( ref ) FLFPInventoryItem& ItemData , const bool bMustFullyAdd , const FGameplayTag EventTag )
{
	if ( GetOwner()->GetLocalRole() != ROLE_Authority ) return false; // Prevent this function to run on client

	const bool bIsSuccess = AddItem_SlotName_Internal(
		InventorySlotNameList ,
		ItemData ,
		EventTag
	);

	/* Apply Inventory Item Change */
	if ( bIsSuccess || bMustFullyAdd == false )
	{
		ApplyInventoryPendingChange();
	}
	else
	{
		ClearInventoryPendingChange();
	}

	return bIsSuccess;
}

bool ULFPInventoryComponent::AddItemListBySlotName( UPARAM( meta = ( Categories = "Item.SlotName" ) )const FGameplayTagContainer InventorySlotNameList , UPARAM( ref )TArray<FLFPInventoryItem>& ItemDataList , const bool bMustFullyAdd , const FGameplayTag EventTag )
{
	if ( GetOwner()->GetLocalRole() != ROLE_Authority ) return false; // Prevent this function to run on client

	const bool bIsSuccess = AddItemList_SlotName_Internal(
		InventorySlotNameList ,
		ItemDataList ,
		bMustFullyAdd ,
		EventTag
	);

	/* Apply Inventory Item Change */
	if ( bIsSuccess || bMustFullyAdd == false )
	{
		ApplyInventoryPendingChange();
	}
	else
	{
		ClearInventoryPendingChange();
	}

	return bIsSuccess;
}

bool ULFPInventoryComponent::AddItemByIndex( const FLFPInventoryIndex& InventoryIndex , UPARAM( ref ) FLFPInventoryItem& ItemData , const bool bMustFullyAdd , const FGameplayTag EventTag )
{
	if ( GetOwner()->GetLocalRole() != ROLE_Authority ) return false; // Prevent this function to run on client

	if ( CanAddItem( ItemData ) == false ) return false;

	const bool bIsSuccess = AddItem_Index_Uncheck_Internal( InventoryIndex , ItemData , EventTag );

	if ( bIsSuccess || bMustFullyAdd == false )
	{
		ApplyInventoryPendingChange();
	}
	else
	{
		ClearInventoryPendingChange();
	}

	return bIsSuccess;
}


bool ULFPInventoryComponent::RemoveItem( UPARAM( ref ) FLFPInventoryItem& ItemData , const bool bMustFullyRemove , const FGameplayTag EventTag )
{
	return RemoveItemBySlotName( GetItemAllowSlotNameList( ItemData ) , ItemData , bMustFullyRemove , EventTag );
}

bool ULFPInventoryComponent::RemoveItemList( UPARAM( ref )TArray<FLFPInventoryItem>& ItemDataList , const bool bMustFullyRemove , const FGameplayTag EventTag )
{
	FGameplayTagContainer SearchSlotNameList = FGameplayTagContainer();

	bool bIsSuccess = true;

	for ( FLFPInventoryItem& ItemData : ItemDataList )
	{
		SearchSlotNameList.AppendTags( GetItemAllowSlotNameList( ItemData ) );
	}

	return RemoveItemListBySlotName( SearchSlotNameList , ItemDataList , bMustFullyRemove , EventTag );
}

bool ULFPInventoryComponent::RemoveItemBySlotName( UPARAM( meta = ( Categories = "Item.SlotName" ) )const FGameplayTagContainer InventorySlotNameList , UPARAM( ref ) FLFPInventoryItem& ItemData , const bool bMustFullyRemove , const FGameplayTag EventTag )
{
	if ( GetOwner()->GetLocalRole() != ROLE_Authority ) return false; // Prevent this function to run on client

	const bool bIsSuccess = RemoveItem_SlotName_Internal(
		InventorySlotNameList ,
		ItemData ,
		EventTag
	);

	/* Apply Inventory Item Change */
	if ( bIsSuccess || bMustFullyRemove == false )
	{
		ApplyInventoryPendingChange();
	}
	else
	{
		ClearInventoryPendingChange();
	}

	return bIsSuccess;
}

bool ULFPInventoryComponent::RemoveItemListBySlotName( UPARAM( meta = ( Categories = "Item.SlotName" ) )const FGameplayTagContainer InventorySlotNameList , UPARAM( ref )TArray<FLFPInventoryItem>& ItemDataList , const bool bMustFullyRemove , const FGameplayTag EventTag )
{
	if ( GetOwner()->GetLocalRole() != ROLE_Authority ) return false; // Prevent this function to run on client

	const bool bIsSuccess = RemoveItemList_SlotName_Internal(
		InventorySlotNameList ,
		ItemDataList ,
		bMustFullyRemove ,
		EventTag
	);

	/* Apply Inventory Item Change */
	if ( bIsSuccess || bMustFullyRemove == false )
	{
		ApplyInventoryPendingChange();
	}
	else
	{
		ClearInventoryPendingChange();
	}

	return bIsSuccess;
}

bool ULFPInventoryComponent::RemoveItemByIndex( const FLFPInventoryIndex& InventoryIndex , UPARAM( ref ) FLFPInventoryItem& ItemData , const bool bMustFullyRemove , const FGameplayTag EventTag )
{
	if ( GetOwner()->GetLocalRole() != ROLE_Authority ) return false; // Prevent this function to run on client

	if ( CanRemoveItem( ItemData ) == false ) return false;

	const bool bIsSuccess = RemoveItem_Index_Uncheck_Internal( InventoryIndex , ItemData , EventTag );

	if ( bIsSuccess || bMustFullyRemove == false )
	{
		ApplyInventoryPendingChange();
	}
	else
	{
		ClearInventoryPendingChange();
	}

	return bIsSuccess;
}


bool ULFPInventoryComponent::SwapItemByIndex( const FLFPInventoryIndex& FromIndex , const FLFPInventoryIndex& ToIndex , const FGameplayTag EventTag )
{
	if ( GetOwner()->GetLocalRole() != ROLE_Authority ) return false; // Prevent this function to run on client

	const FLFPInventoryInternalIndex FromIndexInternal = InventorySlot.ToInventoryIndexInternal( FromIndex );
	const FLFPInventoryInternalIndex ToIndexInternal = InventorySlot.ToInventoryIndexInternal( ToIndex );

	const bool bIsSuccess = SwapItem_Index_Internal( FromIndexInternal , ToIndexInternal , EventTag );

	/* Apply Inventory Item Change */
	ApplyInventoryPendingChange();

	return bIsSuccess;
}


bool ULFPInventoryComponent::MergeItemByIndex( const FLFPInventoryIndex& FromIndex , const FLFPInventoryIndex& ToIndex , const FGameplayTag EventTag )
{
	if ( GetOwner()->GetLocalRole() != ROLE_Authority ) return false; // Prevent this function to run on client

	const FLFPInventoryInternalIndex FromIndexInternal = InventorySlot.ToInventoryIndexInternal( FromIndex );
	const FLFPInventoryInternalIndex ToIndexInternal = InventorySlot.ToInventoryIndexInternal( ToIndex );

	const bool bIsSuccess = MergeItem_Index_Internal( FromIndexInternal , ToIndexInternal , EventTag );

	/* Apply Inventory Item Change */
	ApplyInventoryPendingChange();

	return bIsSuccess;
}

bool ULFPInventoryComponent::MergeItemBySlotName( const FLFPInventoryIndex& FromIndex , const FGameplayTagContainer ToSlotNameList , const FGameplayTag EventTag )
{
	if ( GetOwner()->GetLocalRole() != ROLE_Authority ) return false; // Prevent this function to run on client

	const bool bIsSuccess = MergeItem_SlotName_Internal(
		FromIndex ,
		ToSlotNameList ,
		EventTag
	);

	/* Apply Inventory Item Change */
	ApplyInventoryPendingChange();

	return bIsSuccess;
}


bool ULFPInventoryComponent::TransferItemByIndex( const FLFPInventoryIndex& FromIndex , const FLFPInventoryIndex& ToIndex , ULFPInventoryComponent* TargetInventoryComponent , const bool bMustFullyTransfer , const FGameplayTag EventTag )
{
	if ( GetOwner()->GetLocalRole() != ROLE_Authority ) return false; // Prevent this function to run on client

	const bool bIsSuccess = Transfer_Index_Internal( FromIndex , ToIndex , TargetInventoryComponent , bMustFullyTransfer , EventTag );

	/* Apply Inventory Item Change */
	if ( bIsSuccess || bMustFullyTransfer == false )
	{
		ApplyInventoryPendingChange();
	}
	else
	{
		ClearInventoryPendingChange();
	}

	return bIsSuccess;
}

bool ULFPInventoryComponent::TransferItemBySlotName( const FLFPInventoryIndex& FromIndex , const FGameplayTagContainer ToSlotNameList , ULFPInventoryComponent* TargetInventoryComponent , const bool bMustFullyTransfer , const FGameplayTag EventTag )
{
	if ( GetOwner()->GetLocalRole() != ROLE_Authority ) return false; // Prevent this function to run on client

	const bool bIsSuccess = Transfer_SlotName_Internal( FromIndex , ToSlotNameList , TargetInventoryComponent , bMustFullyTransfer , EventTag );

	/* Apply Inventory Item Change */
	if ( bIsSuccess || bMustFullyTransfer == false )
	{
		ApplyInventoryPendingChange();
	}
	else
	{
		ClearInventoryPendingChange();
	}

	return bIsSuccess;
}


bool ULFPInventoryComponent::ExchangeItemBySlotName( const FGameplayTagContainer TakeSlotNameList , UPARAM( ref )FLFPInventoryItem& TakeItemData , const FGameplayTagContainer GiveSlotNameList , UPARAM( ref )TArray<FLFPInventoryItem>& GiveItemDataList , const FGameplayTag EventTag )
{
	if ( GetOwner()->GetLocalRole() != ROLE_Authority ) return false; // Prevent this function to run on client

	const bool bIsSuccess =
		RemoveItem_SlotName_Internal(
		TakeSlotNameList ,
		TakeItemData ,
		EventTag
		)
		&&
		AddItemList_SlotName_Internal(
		GiveSlotNameList ,
		GiveItemDataList ,
		true ,
		EventTag
		);

	/* Apply Inventory Item Change */
	if ( bIsSuccess )
	{
		ApplyInventoryPendingChange();
	}
	else
	{
		ClearInventoryPendingChange();
	}

	return bIsSuccess;
}

bool ULFPInventoryComponent::ExchangeItemListBySlotName( const FGameplayTagContainer TakeSlotNameList , UPARAM( ref )TArray<FLFPInventoryItem>& TakeItemDataList , const FGameplayTagContainer GiveSlotNameList , UPARAM( ref )TArray<FLFPInventoryItem>& GiveItemDataList , const FGameplayTag EventTag )
{
	if ( GetOwner()->GetLocalRole() != ROLE_Authority ) return false; // Prevent this function to run on client

	const bool bIsSuccess =
		RemoveItemList_SlotName_Internal(
		TakeSlotNameList ,
		TakeItemDataList ,
		true ,
		EventTag
		)
		&&
		AddItemList_SlotName_Internal(
		GiveSlotNameList ,
		GiveItemDataList ,
		true ,
		EventTag
		);

	/* Apply Inventory Item Change */
	if ( bIsSuccess )
	{
		ApplyInventoryPendingChange();
	}
	else
	{
		ClearInventoryPendingChange();
	}

	return bIsSuccess;
}

bool ULFPInventoryComponent::TradeItemBySlotName( const FGameplayTagContainer TakeSlotNameList , UPARAM( ref )FLFPInventoryItem& TakeItemData , const FGameplayTagContainer GiveSlotNameList , UPARAM( ref )TArray<FLFPInventoryItem>& GiveItemDataList , ULFPInventoryComponent* GiveInventoryComponent , const FGameplayTag EventTag )
{
	if ( GetOwner()->GetLocalRole() != ROLE_Authority ) return false; // Prevent this function to run on client

	if ( IsValid( GiveInventoryComponent ) == false ) return false;

	const bool bIsSuccess =
		RemoveItem_SlotName_Internal(
		TakeSlotNameList ,
		TakeItemData ,
		EventTag
		)
		&&
		GiveInventoryComponent->AddItemList_SlotName_Internal(
		GiveSlotNameList ,
		GiveItemDataList ,
		true ,
		EventTag
		);

	/* Apply Inventory Item Change */
	if ( bIsSuccess )
	{
		ApplyInventoryPendingChange();

		GiveInventoryComponent->ApplyInventoryPendingChange();
	}
	else
	{
		ClearInventoryPendingChange();

		GiveInventoryComponent->ClearInventoryPendingChange();
	}

	return bIsSuccess;
}

bool ULFPInventoryComponent::TradeItemListBySlotName( const FGameplayTagContainer TakeSlotNameList , UPARAM( ref )TArray<FLFPInventoryItem>& TakeItemDataList , const FGameplayTagContainer GiveSlotNameList , UPARAM( ref )TArray<FLFPInventoryItem>& GiveItemDataList , ULFPInventoryComponent* GiveInventoryComponent , const FGameplayTag EventTag )
{
	if ( GetOwner()->GetLocalRole() != ROLE_Authority ) return false; // Prevent this function to run on client

	if ( IsValid( GiveInventoryComponent ) == false ) return false;

	const bool bIsSuccess =
		RemoveItemList_SlotName_Internal(
		TakeSlotNameList ,
		TakeItemDataList ,
		true ,
		EventTag
		)
		&&
		GiveInventoryComponent->AddItemList_SlotName_Internal(
		GiveSlotNameList ,
		GiveItemDataList ,
		true ,
		EventTag
		);

	/* Apply Inventory Item Change */
	if ( bIsSuccess )
	{
		ApplyInventoryPendingChange();

		GiveInventoryComponent->ApplyInventoryPendingChange();
	}
	else
	{
		ClearInventoryPendingChange();

		GiveInventoryComponent->ClearInventoryPendingChange();
	}

	return bIsSuccess;
}


bool ULFPInventoryComponent::UpdateItem( UPARAM( ref )FLFPInventoryItem& ItemData , const FGameplayTag EventTag )
{
	return UpdateItemBySlotName( GetItemAllowSlotNameList( ItemData ) , ItemData , EventTag );
}

bool ULFPInventoryComponent::UpdateItemBySlotName( UPARAM( meta = ( Categories = "Item.SlotName" ) )const FGameplayTagContainer InventorySlotNameList , UPARAM( ref )FLFPInventoryItem& ItemData , const FGameplayTag EventTag )
{
	if ( GetOwner()->GetLocalRole() != ROLE_Authority ) return false; // Prevent this function to run on client

	UpdateItem_SlotName_Internal( InventorySlotNameList , ItemData , EventTag );

	ApplyInventoryPendingChange();

	return true;
}

bool ULFPInventoryComponent::UpdateItemByIndex( const FLFPInventoryIndex& InventoryIndex , UPARAM( ref )FLFPInventoryItem& ItemData , const FGameplayTag EventTag )
{
	if ( GetOwner()->GetLocalRole() != ROLE_Authority ) return false; // Prevent this function to run on client

	if ( CanUpdateItem( ItemData ) == false ) return false;

	UpdateItem_Index_Uncheck_Internal( InventoryIndex , ItemData , EventTag );

	ApplyInventoryPendingChange();

	return true;
}


bool ULFPInventoryComponent::SortItem( UPARAM( meta = ( Categories = "Item.SlotName" ) )const FGameplayTagContainer InventorySlotNameList , UPARAM( meta = ( Categories = "Item.Sort" ) ) const FGameplayTag SortTag , const FGameplayTag EventTag )
{
	if ( GetOwner()->GetLocalRole() != ROLE_Authority ) return false; // Prevent this function to run on client

	InventorySlot.SortSlot(
		InventorySlotNameList ,
		[&] ( const FGameplayTag& SlotName )
		{
			return CanSlotNameBeSort( SlotName );
		} ,
		[&] ( const FLFPInventoryItem& ItemDataA , const FLFPInventoryItem& ItemDataB )
		{
			return CanItemSortHigherThan( ItemDataA , ItemDataB , SortTag );
		} ,
		EventTag
	);

	ApplyInventoryPendingChange();

	return true;
}

void ULFPInventoryComponent::ClearInventory( UPARAM( meta = ( Categories = "Item.SlotName" ) ) const FGameplayTagContainer SlotNames , const FGameplayTag EventTag )
{
	if ( GetOwner()->GetLocalRole() != ROLE_Authority ) return; // Prevent this function to run on client

	const bool bProcessSuccess = ProcessInventoryIndex(
		SlotNames ,
		[&] ( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryInternalIndex& InventoryInternalIndex )
		{
			if ( InventorySlot.IsSlotItemValid( InventoryInternalIndex ) == false )
			{
				return false;
			}

			InventorySlot.AddPendingEvent( FLFPInventoryItemOperationData(
				ELFPInventoryItemEventType::Inventory_Clear ,
				InventoryIndex ,
				FLFPInventoryItem() ,
				InventorySlot.GetSlotItemConst( InventoryInternalIndex ) ,
				EventTag
			) );

			InventorySlot.GetSlotItemRef( InventoryInternalIndex , true ) = FLFPInventoryItem();

			return false;
		} ,
		false
	);

	ApplyInventoryPendingChange();

	return;
}


ULFPItemInventoryFunction* ULFPInventoryComponent::GetFunctionObject( const TSubclassOf<ULFPItemInventoryFunction> FunctionClass ) const
{
	if ( FunctionClass == nullptr ) return nullptr;

	ULFPItemInventoryFunction* ReturnPtr = nullptr;

	ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			if ( FunctionObj.GetClass() == FunctionClass.Get() )
			{
				ReturnPtr = FunctionObj;

				/* Stop The Loop Using False */
				return false;
			}

			return true;
		}
	);

	return ReturnPtr;
}

TArray<ULFPItemInventoryFunction*> ULFPInventoryComponent::GetFunctionObjectListByClass( const TSubclassOf<ULFPItemInventoryFunction> FunctionClass ) const
{
	if ( FunctionClass == nullptr ) return TArray<ULFPItemInventoryFunction*>();

	TArray<ULFPItemInventoryFunction*> ReturnPtrList = TArray<ULFPItemInventoryFunction*>();

	ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			if ( FunctionObj.GetClass() == FunctionClass.Get() )
			{
				ReturnPtrList.Add( FunctionObj );

				/* Stop The Loop Using False */
				return false;
			}

			return true;
		}
	);

	return ReturnPtrList;
}


bool ULFPInventoryComponent::CanAddItem( const FLFPInventoryItem& ItemData ) const
{
	return ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			const bool bSuccess = FunctionObj->CanAddItem( ItemData );

			if ( bSuccess == false )
			{
				UE_LOG( LFPInventoryComponent , Verbose , TEXT( "CanAddItem Fail : FunctionObj = %s | ItemData = %s" ) , *FunctionObj->GetName() , *ItemData.ToString() );
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::CanRemoveItem( const FLFPInventoryItem& ItemData ) const
{
	return ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			const bool bSuccess = FunctionObj->CanRemoveItem( ItemData );

			if ( bSuccess == false )
			{
				UE_LOG( LFPInventoryComponent , Verbose , TEXT( "CanRemoveItem Fail : FunctionObj = %s | ItemData = %s" ) , *FunctionObj->GetName() , *ItemData.ToString() );
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::CanUpdateItem( const FLFPInventoryItem& ItemData ) const
{
	return ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			const bool bSuccess = FunctionObj->CanUpdateItem( ItemData );

			if ( bSuccess == false )
			{
				UE_LOG( LFPInventoryComponent , Verbose , TEXT( "CanUpdateItem Fail : FunctionObj = %s | ItemData = %s" ) , *FunctionObj->GetName() , *ItemData.ToString() );
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::CanFindItem( const FLFPInventoryItem& ItemData ) const
{
	return ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			const bool bSuccess = FunctionObj->CanFindItem( ItemData );

			if ( bSuccess == false )
			{
				UE_LOG( LFPInventoryComponent , Verbose , TEXT( "CanContainItem Fail : FunctionObj = %s | ItemData = %s" ) , *FunctionObj->GetName() , *ItemData.ToString() );
			}

			return bSuccess;
		}
	);
}


bool ULFPInventoryComponent::CanAddItemOnSlot( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryItem& CurrentData , const FLFPInventoryItem& ProcessData ) const
{
	return ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			const bool bSuccess = FunctionObj->CanAddItemOnSlot( InventoryIndex , CurrentData , ProcessData );

			if ( bSuccess == false )
			{
				UE_LOG( LFPInventoryComponent , Verbose , TEXT( "CanAddItemOnSlot Fail : FunctionObj = %s | InventoryIndex = %s" ) , *FunctionObj->GetName() , *InventoryIndex.ToString() );
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::CanRemoveItemOnSlot( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryItem& CurrentData , const FLFPInventoryItem& ProcessData ) const
{
	return ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			const bool bSuccess = FunctionObj->CanRemoveItemOnSlot( InventoryIndex , CurrentData , ProcessData );

			if ( bSuccess == false )
			{
				UE_LOG( LFPInventoryComponent , Verbose , TEXT( "CanRemoveItemOnSlot Fail : FunctionObj = %s | InventoryIndex = %s" ) , *FunctionObj->GetName() , *InventoryIndex.ToString() );
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::CanSwapItemOnSlot( const FLFPInventoryItem& FromItem , const FLFPInventoryIndex& FromIndex , const FLFPInventoryItem& ToItem , const FLFPInventoryIndex& ToIndex ) const
{
	return ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			const bool bSuccess = FunctionObj->CanSwapItemOnSlot( FromItem , FromIndex , ToItem , ToIndex );

			if ( bSuccess == false )
			{
				UE_LOG( LFPInventoryComponent , Verbose , TEXT( "CanSwapItemOnSlot Fail : FunctionObj = %s | FromIndex = %s | ToIndex = %s" ) , *FunctionObj->GetName() , *FromIndex.ToString() , *ToIndex.ToString() );
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::CanMergeItemOnSlot( const FLFPInventoryItem& FromItem , const FLFPInventoryIndex& FromIndex , const FLFPInventoryItem& ToItem , const FLFPInventoryIndex& ToIndex ) const
{
	return ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			const bool bSuccess = FunctionObj->CanMergeItemOnSlot( FromItem , FromIndex , ToItem , ToIndex );

			if ( bSuccess == false )
			{
				UE_LOG( LFPInventoryComponent , Verbose , TEXT( "CanMergeItemOnSlot Fail : FunctionObj = %s | FromIndex = %s | ToIndex = %s" ) , *FunctionObj->GetName() , *FromIndex.ToString() , *ToIndex.ToString() );
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::CanTransferItemOnSlot( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryItem& ItemData ) const
{
	return ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			const bool bSuccess = FunctionObj->CanTransferItemOnSlot( InventoryIndex , ItemData );

			if ( bSuccess == false )
			{
				UE_LOG( LFPInventoryComponent , Verbose , TEXT( "CanTransferItemOnSlot Fail : FunctionObj = %s | InventoryIndex = %s" ) , *FunctionObj->GetName() , *InventoryIndex.ToString() );
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::CanUpdateItemOnSlot( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryItem& CurrentData , const FLFPInventoryItem& ProcessData ) const
{
	return ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			const bool bSuccess = FunctionObj->CanUpdateItemOnSlot( InventoryIndex , CurrentData , ProcessData );

			if ( bSuccess == false )
			{
				UE_LOG( LFPInventoryComponent , Verbose , TEXT( "CanUpdateItemOnSlot Fail : FunctionObj = %s | InventoryIndex = %s" ) , *FunctionObj->GetName() , *InventoryIndex.ToString() );
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::CanFindItemOnSlot( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryItem& CurrentData , const FLFPInventoryItem& ProcessData ) const
{
	return ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			const bool bSuccess = FunctionObj->CanFindItemOnSlot( InventoryIndex , CurrentData , ProcessData );

			if ( bSuccess == false )
			{
				UE_LOG( LFPInventoryComponent , Verbose , TEXT( "CanContainItemOnSlot Fail : FunctionObj = %s | InventoryIndex = %s" ) , *FunctionObj->GetName() , *InventoryIndex.ToString() );
			}

			return bSuccess;
		}
	);
}


bool ULFPInventoryComponent::ProcessAddItem( UPARAM( ref )FLFPInventoryItem& ItemData , UPARAM( ref )FLFPInventoryItem& ProcessData , const FLFPInventoryIndex InventoryIndex ) const
{
	return ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			const bool bSuccess = FunctionObj->ProcessAddItem( ItemData , ProcessData , InventoryIndex );

			if ( bSuccess == false )
			{
				UE_LOG( LFPInventoryComponent , VeryVerbose , TEXT( "ProcessAddItem Fail : FunctionObj = %s | InventoryIndex = %s" ) , *FunctionObj->GetName() , *InventoryIndex.ToString() );
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::ProcessRemoveItem( UPARAM( ref )FLFPInventoryItem& ItemData , UPARAM( ref )FLFPInventoryItem& ProcessData , const FLFPInventoryIndex InventoryIndex ) const
{
	return ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			const bool bSuccess = FunctionObj->ProcessRemoveItem( ItemData , ProcessData , InventoryIndex );

			if ( bSuccess == false )
			{
				UE_LOG( LFPInventoryComponent , VeryVerbose , TEXT( "ProcessRemoveItem Fail : FunctionObj = %s | InventoryIndex = %s" ) , *FunctionObj->GetName() , *InventoryIndex.ToString() );
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::ProcessSwapItem( UPARAM( ref )FLFPInventoryItem& FromItem , const FLFPInventoryIndex& FromIndex , UPARAM( ref )FLFPInventoryItem& ToItem , const FLFPInventoryIndex& ToIndex ) const
{
	return ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			const bool bSuccess = FunctionObj->ProcessSwapItem( FromItem , FromIndex , ToItem , ToIndex );

			if ( bSuccess == false )
			{
				UE_LOG( LFPInventoryComponent , VeryVerbose , TEXT( "ProcessSwapItem Fail : FunctionObj = %s | FromIndex = %s | ToIndex = %s" ) , *FunctionObj->GetName() , *FromIndex.ToString() , *ToIndex.ToString() );
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::ProcessMergeItem( UPARAM( ref )FLFPInventoryItem& FromItem , const FLFPInventoryIndex& FromIndex , UPARAM( ref )FLFPInventoryItem& ToItem , const FLFPInventoryIndex& ToIndex ) const
{
	return ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			const bool bSuccess = FunctionObj->ProcessMergeItem( FromItem , FromIndex , ToItem , ToIndex );

			if ( bSuccess == false )
			{
				UE_LOG( LFPInventoryComponent , VeryVerbose , TEXT( "ProcessMergeItem Fail : FunctionObj = %s | FromIndex = %s | ToIndex = %s" ) , *FunctionObj->GetName() , *FromIndex.ToString() , *ToIndex.ToString() );
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::ProcessUpdateItem( UPARAM( ref )FLFPInventoryItem& ItemData , UPARAM( ref )FLFPInventoryItem& ProcessData , const FLFPInventoryIndex InventoryIndex ) const
{
	return ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			const bool bSuccess = FunctionObj->ProcessUpdateItem( ItemData , ProcessData , InventoryIndex );

			if ( bSuccess == false )
			{
				UE_LOG( LFPInventoryComponent , VeryVerbose , TEXT( "ProcessUpdateItem Fail : FunctionObj = %s | InventoryIndex = %s" ) , *FunctionObj->GetName() , *InventoryIndex.ToString() );
			}

			return bSuccess;
		}
	);
}

bool ULFPInventoryComponent::ProcessFindItem( const FLFPInventoryItem& ItemData , UPARAM( ref )FLFPInventoryItem& ProcessData , const FLFPInventoryIndex InventoryIndex ) const
{
	return ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			const bool bSuccess = FunctionObj->ProcessFindItem( ItemData , ProcessData , InventoryIndex );

			if ( bSuccess == false )
			{
				UE_LOG( LFPInventoryComponent , VeryVerbose , TEXT( "ProcessContainItem Fail : FunctionObj = %s | InventoryIndex = %s" ) , *FunctionObj->GetName() , *InventoryIndex.ToString() );
			}

			return bSuccess;
		}
	);
}


FGameplayTagContainer ULFPInventoryComponent::GetItemAllowSlotNameList( const FLFPInventoryItem& ItemData , const FGameplayTagContainer& FilterList ) const
{
	FGameplayTagContainer Result = FGameplayTagContainer();

	ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			Result.AppendTags( FunctionObj->GetItemAllowSlotNameList( ItemData ) );

			return true;
		}
	);

	return FilterList.IsEmpty() ? Result : Result.Filter( FilterList );
}

bool ULFPInventoryComponent::CanSlotNameBeSort( const FGameplayTag& SlotName ) const
{
	return ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			return FunctionObj->CanSlotNameBeSort( SlotName );
		}
	);
}

bool ULFPInventoryComponent::CanItemSortHigherThan( const FLFPInventoryItem& ItemDataA , const FLFPInventoryItem& ItemDataB , const FGameplayTag& SortTag ) const
{
	return ProcessInventoryFunction(
		[&] ( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )
		{
			return FunctionObj->CanItemSortHigherThan( ItemDataA , ItemDataB , SortTag );
		}
	);
}

//bool ULFPInventoryComponent::CanAddItemBySlotName(UPARAM(meta=(Categories="Item.SlotName"))const FGameplayTagContainer InventorySlotNameList, UPARAM(ref)FLFPInventoryItem& ItemData) const
//{
//	if (CanAddItem(ItemData) == false) return false;
//
//	return ProcessInventoryIndex(
//		InventorySearch,
//		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex)
//		{
//			return AddItem_Internal_Check(InventoryIndex, ItemData);
//		},
//		true);
//}
//
//bool ULFPInventoryComponent::CanAddItemListBySlotName(UPARAM(meta=(Categories="Item.SlotName"))const FGameplayTagContainer InventorySlotNameList, UPARAM(ref)TArray<FLFPInventoryItem>& ItemDataList) const
//{
//	bool bIsSuccess = true;
//
//	for (FLFPInventoryItem& ItemData : ItemDataList)
//	{
//		if (CanAddItemBySearch(InventorySearch, ItemData) == false)
//		{
//			bIsSuccess = false;
//		}
//	}
//
//	return bIsSuccess;
//}
//
//bool ULFPInventoryComponent::CanAddItemByIndex(const FLFPInventoryIndex& InventoryIndex, UPARAM(ref) FLFPInventoryItem& ItemData) const
//{
//	if (CanAddItem(ItemData) == false) return false;
//
//	return AddItem_Internal_Check(InventoryIndex, ItemData);
//}
//
//bool ULFPInventoryComponent::CanRemoveItemBySlotName(UPARAM(meta=(Categories="Item.SlotName"))const FGameplayTagContainer InventorySlotNameList, UPARAM(ref)FLFPInventoryItem& ItemData) const
//{
//	if (CanRemoveItem(ItemData) == false) return false;
//
//	return ProcessInventoryIndex(
//		InventorySearch,
//		[&](const FLFPInventoryIndex& InventoryIndex, const FLFPInventoryInternalIndex& InventoryInternalIndex)
//		{
//			return RemoveItem_Internal_Check(InventoryIndex, ItemData);
//		},
//		true);
//}
//
//bool ULFPInventoryComponent::CanRemoveItemListBySlotName(UPARAM(meta=(Categories="Item.SlotName"))const FGameplayTagContainer InventorySlotNameList, UPARAM(ref)TArray<FLFPInventoryItem>& ItemDataList) const
//{
//	bool bIsSuccess = true;
//
//	for (FLFPInventoryItem& ItemData : ItemDataList)
//	{
//		if (CanRemoveItemBySearch(InventorySearch, ItemData) == false)
//		{
//			bIsSuccess = false;
//		}
//	}
//
//	return bIsSuccess;
//}
//
//bool ULFPInventoryComponent::CanRemoveItemByIndex(const FLFPInventoryIndex& InventoryIndex, UPARAM(ref) FLFPInventoryItem& ItemData) const
//{
//	if (CanRemoveItem(ItemData) == false) return false;
//
//	return RemoveItem_Internal_Check(InventoryIndex, ItemData);
//}


bool ULFPInventoryComponent::ContainItem( FLFPInventoryItem ItemData , UPARAM( meta = ( Categories = "Item.SlotName" ) )const FGameplayTagContainer InventorySlotNameList ) const
{
	if ( CanFindItem( ItemData ) == false ) return false;

	return ProcessSingleItemOperation(
		InventorySlotNameList ,
		ItemData ,
		[&] ( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryInternalIndex& InventoryInternalIndex , FLFPInventoryItem& TargetItemData )
		{
			return ContainItem_Index_Internal( InventoryInternalIndex , ItemData );
		} ,
		false
	);
}

bool ULFPInventoryComponent::ContainItemList( const TArray<FLFPInventoryItem>& ItemDataList , UPARAM( meta = ( Categories = "Item.SlotName" ) )const FGameplayTagContainer InventorySlotNameList , const bool bPartially ) const
{
	for ( const auto& ItemData : ItemDataList )
	{
		const bool bIsSearchComplete = ContainItem( ItemData , InventorySlotNameList );

		if ( bPartially )
		{
			if ( bIsSearchComplete ) return true;
		}
		else if ( bIsSearchComplete == false )
		{
			return false;
		}
	}

	return true;
}


bool ULFPInventoryComponent::IsSlotNameValid( const FGameplayTag SlotName ) const
{
	for ( const auto& Slot : InventorySlot.GetSlotListConst() )
	{
		if ( Slot.SlotName.MatchesTag( SlotName ) ) return true;
	}

	return false;
}

bool ULFPInventoryComponent::IsInventoryIndexValid( const FLFPInventoryIndex& InventoryIndex ) const
{
	const FLFPInventoryInternalIndex InventoryInternalIndex( ( InventorySlot.ToInventoryIndexInternal( InventoryIndex ) ) );

	if ( InventoryInternalIndex.IsValid() == false ) return false;

	return InventorySlot.IsSlotIndexValid( InventoryInternalIndex );
}



const FLFPInventoryItem& ULFPInventoryComponent::GetSlotItem( const FLFPInventoryIndex& InventoryIndex ) const
{
	const FLFPInventoryInternalIndex InventoryInternalIndex( ( InventorySlot.ToInventoryIndexInternal( InventoryIndex ) ) );

	if ( InventoryInternalIndex.IsValid() == false ) return FLFPInventoryItem::EmptyItem;

	return InventorySlot.GetSlotItemConst( InventoryInternalIndex );
}

int32 ULFPInventoryComponent::GetSlotListItemNum( const FGameplayTagContainer& SlotTagList ) const
{
	return InventorySlot.GetSlotListItemNum( SlotTagList );
}

int32 ULFPInventoryComponent::GetSlotItemNum( const FGameplayTag& SlotTag ) const
{
	return InventorySlot.GetSlotItemNum( SlotTag );
}



bool ULFPInventoryComponent::FindInventoryIndexList( TArray<FLFPInventoryIndex>& InventoryIndexList , FLFPInventoryItem ItemData , UPARAM( meta = ( Categories = "Item.SlotName" ) )const FGameplayTagContainer InventorySlotNameList , const int32 MaxListItem ) const
{
	if ( CanFindItem( ItemData ) == false ) return false;

	const int32 CurrentAmount = InventoryIndexList.Num();

	const bool bIsSuccess = ProcessSingleItemOperation(
		InventorySlotNameList ,
		ItemData ,
		[&] ( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryInternalIndex& InventoryInternalIndex , FLFPInventoryItem& TargetItemData )
		{
			if ( FindItem_Index_Internal( InventoryInternalIndex , TargetItemData ) )
			{
				InventoryIndexList.Add( InventoryIndex );
			}

			return ItemData.IsValid() == false || ( MaxListItem > 0 ? MaxListItem <= CurrentAmount : false );
		} ,
		false
	);

	return InventoryIndexList.Num() > CurrentAmount;
}

bool ULFPInventoryComponent::FindItemDataList( TArray<FLFPInventoryItem>& ItemDataList , FLFPInventoryItem ItemData , UPARAM( meta = ( Categories = "Item.SlotName" ) )const FGameplayTagContainer InventorySlotNameList , const int32 MaxListItem ) const
{
	if ( CanFindItem( ItemData ) == false ) return false;

	const int32 CurrentAmount = ItemDataList.Num();

	const bool bIsSuccess = ProcessSingleItemOperation(
		InventorySlotNameList ,
		ItemData ,
		[&] ( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryInternalIndex& InventoryInternalIndex , FLFPInventoryItem& TargetItemData )
		{
			if ( FindItem_Index_Internal( InventoryInternalIndex , TargetItemData ) )
			{
				ItemDataList.Add( InventorySlot.GetSlotItemConst( InventoryInternalIndex ) );
			}

			return ItemData.IsValid() == false || ( MaxListItem > 0 ? MaxListItem <= CurrentAmount : false );
		} ,
		false
	);

	return ItemDataList.Num() > CurrentAmount;
}

bool ULFPInventoryComponent::FindInventoryIndexListByItemTag( TArray<FLFPInventoryIndex>& InventoryIndexList , UPARAM( meta = ( Categories = "Item.SlotName" ) ) const FGameplayTagContainer InventorySlotNameList , UPARAM( meta = ( Categories = "Item.Categorize" ) )const FGameplayTagContainer ItemTagList , const int32 MaxListItem ) const
{
	const int32 CurrentAmount = InventoryIndexList.Num();

	const bool bIsSuccess = ProcessInventoryIndex(
		InventorySlotNameList ,
		[&] ( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryInternalIndex& InventoryInternalIndex )
		{
			if ( InventorySlot.GetSlotItemConst( InventoryInternalIndex ).MatchesAnyTag( ItemTagList ) )
			{
				InventoryIndexList.Add( InventoryIndex );
			}

			return MaxListItem > 0 && InventoryIndexList.Num() - CurrentAmount >= MaxListItem;
		}
	);

	return InventoryIndexList.Num() > CurrentAmount;
}

bool ULFPInventoryComponent::FindItemDataListByItemTag( TArray<FLFPInventoryItem>& ItemDataList , UPARAM( meta = ( Categories = "Item.SlotName" ) ) const FGameplayTagContainer InventorySlotNameList , UPARAM( meta = ( Categories = "Item.Categorize" ) )const FGameplayTagContainer ItemTagList , const int32 MaxListItem ) const
{
	const int32 CurrentAmount = ItemDataList.Num();

	const bool bIsSuccess = ProcessInventoryIndex(
		InventorySlotNameList ,
		[&] ( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryInternalIndex& InventoryInternalIndex )
		{
			if ( InventorySlot.GetSlotItemConst( InventoryInternalIndex ).MatchesAnyTag( ItemTagList ) )
			{
				ItemDataList.Add( InventorySlot.GetSlotItemConst( InventoryInternalIndex ) );
			}

			return MaxListItem > 0 && ItemDataList.Num() - CurrentAmount >= MaxListItem;
		}
	);

	return ItemDataList.Num() > CurrentAmount;
}