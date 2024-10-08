// Copyright (c) 2023-2024 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JsonObjectWrapper.h"
#include "GameplayTagContainer.h"
#include "LFPItemFunctionLibrary.h"
#include "LFPInventoryComponent.generated.h"

class ULFPItemInventoryFunction;

DECLARE_LOG_CATEGORY_EXTERN( LFPInventoryComponent , Log , All );

USTRUCT( BlueprintType )
struct LOHFUNCTIONPLUGINITEM_API FLFPInventorySearch
{
	GENERATED_BODY()

	FLFPInventorySearch() {}

	FLFPInventorySearch( const FGameplayTag& NewSlotName ) : SlotNames( NewSlotName.GetSingleTagContainer() ) {}

	FLFPInventorySearch( const FGameplayTagContainer& NewSlotNames ) : SlotNames( NewSlotNames ) {}

	FLFPInventorySearch(
		const FGameplayTagContainer& NewSlotNames ,
		const FGameplayTagContainer& NewCategorizes ,
		const bool NewAnyCategorizes ,
		const bool NewPassOnEmptyIndexCategorizes
	)
		:
		SlotNames( NewSlotNames ) ,
		Categorizes( NewCategorizes ) ,
		bAnyCategorizes( NewAnyCategorizes ) ,
		bPassOnEmptyIndexCategorizes( NewPassOnEmptyIndexCategorizes )
	{}

protected:

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = Default , meta = ( Categories = "Item.SlotName" ) )
	FGameplayTagContainer SlotNames = FGameplayTagContainer::EmptyContainer;

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = Default )
	FGameplayTagContainer Categorizes = FGameplayTagContainer::EmptyContainer;

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = Default )
	bool bAnyCategorizes = false;

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = Default )
	bool bPassOnEmptyIndexCategorizes = false;

public:

	FORCEINLINE bool IsValid() const {
		return SlotNames.IsEmpty() == false;
	}

	FORCEINLINE bool IsTagMatch( const FGameplayTag& Tag ) const {
		return SlotNames.IsEmpty() ? true : Tag.MatchesAny( SlotNames );
	}

	FORCEINLINE bool IsCategorizesMatch( const FGameplayTagContainer& Container ) const
	{
		if ( bPassOnEmptyIndexCategorizes && Container.IsEmpty() ) return true;
		if ( Categorizes.IsEmpty() ) return true;

		return bAnyCategorizes ? Container.HasAny( Categorizes ) : Container.HasAll( Categorizes );
	}

	FORCEINLINE FString ToString() const {
		return FString::Printf( TEXT( "SlotNames = %s : Categorizes = %s : AnyCategorizes = %s" ) , *SlotNames.ToString() , *Categorizes.ToString() , bAnyCategorizes ? TEXT( "True" ) : TEXT( "False" ) );
	}

	FORCEINLINE	FLFPInventorySearch& operator+=( const FLFPInventorySearch& Other ) {
		SlotNames.AppendTags( Other.SlotNames ); Categorizes.AppendTags( Other.Categorizes ); return *this;
	}
};

USTRUCT( BlueprintType )
struct LOHFUNCTIONPLUGINITEM_API FLFPInventoryIndex
{
	GENERATED_BODY()

	FLFPInventoryIndex() {}

	FLFPInventoryIndex( const int32 NewSlotIndex , const FGameplayTag& NewSlotName ) : SlotItemIndex( NewSlotIndex ) , SlotName( NewSlotName ) {}

public:

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = Default )
	int32 SlotItemIndex = INDEX_NONE;

	/* Use For Getting SlotListIndex */
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = Default , meta = ( Categories = "Item.SlotName" ) )
	FGameplayTag SlotName = FGameplayTag::EmptyTag;

public:

	FORCEINLINE bool IsValid() const {
		return SlotName.IsValid() && SlotItemIndex > INDEX_NONE;
	}

	FORCEINLINE	bool operator==( const FLFPInventoryIndex& Other ) const {
		return SlotItemIndex == Other.SlotItemIndex && SlotName == Other.SlotName;
	}

	FORCEINLINE	bool operator!=( const FLFPInventoryIndex& Other ) const {
		return SlotItemIndex != Other.SlotItemIndex || SlotName != Other.SlotName;
	}

	FORCEINLINE FString ToString() const {
		return FString::Printf( TEXT( "%s | ItemIndex = %d" ) , *SlotName.ToString() , SlotItemIndex );
	}
};

USTRUCT()
struct LOHFUNCTIONPLUGINITEM_API FLFPInventoryInternalIndex
{
	GENERATED_BODY()

	FLFPInventoryInternalIndex() {}

	FLFPInventoryInternalIndex( const int32 NewSlotIndex , const int32 NewSlotListIndex , const FGameplayTag NewSlotListName ) : SlotItemIndex( NewSlotIndex ) , SlotListIndex( NewSlotListIndex ) , SlotListName( NewSlotListName ) {}

public:

	UPROPERTY()
	int32 SlotItemIndex = INDEX_NONE;

	UPROPERTY()
	int32 SlotListIndex = INDEX_NONE;

	UPROPERTY()
	FGameplayTag SlotListName = FGameplayTag::EmptyTag;

public:

	FORCEINLINE bool IsValid() const {
		return SlotListIndex > INDEX_NONE && SlotItemIndex > INDEX_NONE;
	}

	FORCEINLINE	bool operator==( const FLFPInventoryInternalIndex& Other ) const {
		return SlotItemIndex == Other.SlotItemIndex && SlotListIndex == Other.SlotListIndex;
	}

	FORCEINLINE	bool operator!=( const FLFPInventoryInternalIndex& Other ) const {
		return SlotItemIndex != Other.SlotItemIndex || SlotListIndex != Other.SlotListIndex;
	}

	FORCEINLINE	FLFPInventoryIndex ToInventoryIndex() const {
		return FLFPInventoryIndex( SlotItemIndex , SlotListName );
	}
};

#if UE_BUILD_DEBUG
uint32 GetTypeHash( const FLFPInventoryInternalIndex& Thing );
#else // optimize by inlining in shipping and development builds
FORCEINLINE uint32 GetTypeHash( const FLFPInventoryInternalIndex& Thing )
{
	uint32 Hash = FCrc::MemCrc32( &Thing , sizeof( FLFPInventoryInternalIndex ) );
	return Hash;
}
#endif


USTRUCT( BlueprintType )
struct LOHFUNCTIONPLUGINITEM_API FLFPInventorySlot
{
	GENERATED_BODY()

public:

	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = Default , meta = ( Categories = "Item.SlotName" ) )
	FGameplayTag SlotName = FGameplayTag::EmptyTag;

	UPROPERTY( BlueprintReadWrite , EditDefaultsOnly , Category = Default )
	int32 SlotMaxIndex = INDEX_NONE;

protected:

	UPROPERTY( VisibleAnywhere , Category = Default )
	TArray<FLFPInventoryItem> ItemList = TArray<FLFPInventoryItem>();

public:

	FORCEINLINE bool IsItemDataValid( const int32 Index ) const {
		return ItemList.IsValidIndex( Index ) && ItemList[ Index ].IsValid();
	}

	FORCEINLINE bool IsItemIndexValid( const int32 Index ) const {
		return SlotMaxIndex > 0 ? Index >= 0 && Index < SlotMaxIndex : Index >= 0;
	}

	FORCEINLINE void ReserveItemIndex( const int32 Index )
	{
		check( Index > INDEX_NONE );

		if ( ItemList.IsValidIndex( Index ) == false )
		{
			ItemList.SetNum( Index + 1 );
		}

		return;
	}

	/* Get Loopable Item Index Clamp By SlotMaxIndex If Bigger Than INDEX_NONE */
	FORCEINLINE int32 GetItemNum( const int32 ExtraSlot = 0 ) const {
		return FMath::Min( ItemList.Num() + ExtraSlot , SlotMaxIndex > INDEX_NONE ? SlotMaxIndex : INT_MAX );
	}

	/* Get Maximum Loopable Index */
	FORCEINLINE int32 GetMaxNum( const int32 ExtraSlot = 0 ) const {
		return SlotMaxIndex > INDEX_NONE ? SlotMaxIndex : GetItemNum() + ExtraSlot;
	}

public: // Get Item

	FORCEINLINE FLFPInventoryItem& GetItemRef( const int32 Index )
	{
		check( Index > INDEX_NONE );

		ReserveItemIndex( Index );

		return ItemList[ Index ];
	}

	FORCEINLINE const FLFPInventoryItem& GetItemConst( const int32 Index ) const
	{
		if ( ItemList.IsValidIndex( Index ) == false )
		{
			return FLFPInventoryItem::EmptyItem;
		}

		return ItemList[ Index ];
	}

	FORCEINLINE const TArray<FLFPInventoryItem>& GetItemListConst() const
	{
		return ItemList;
	}

public: // List Operation

	FORCEINLINE void ClearEmptyItem()
	{
		while ( ItemList.Num() > 0 && ItemList.Last().IsValid() == false )
		{
			ItemList.RemoveAt( ItemList.Num() - 1 , 1 , false );
		}

		ItemList.Shrink();
	}
};

UENUM( BlueprintType )
enum class ELFPInventoryItemEventType : uint8
{
	Inventory_None		UMETA( DisplayName = "None" ) ,
	Inventory_Add		UMETA( DisplayName = "Add" ) ,
	Inventory_Remove	UMETA( DisplayName = "Remove" ) ,
	Inventory_Swap		UMETA( DisplayName = "Swap" ) ,
	Inventory_Merge		UMETA( DisplayName = "Merge" ) ,
	Inventory_Transfer	UMETA( DisplayName = "Transfer" ) ,
	Inventory_Exchange	UMETA( DisplayName = "Exchange" ) ,
	Inventory_Trade		UMETA( DisplayName = "Trade" ) ,
	Inventory_Update	UMETA( DisplayName = "Update" ) ,
	Inventory_Clear		UMETA( DisplayName = "Clear" ) ,
};

USTRUCT()
struct LOHFUNCTIONPLUGINITEM_API FLFPInventoryItemOperationData
{
	GENERATED_BODY()

	FLFPInventoryItemOperationData() {}

	FLFPInventoryItemOperationData(
		const ELFPInventoryItemEventType& IN_EventType ,
		const FLFPInventoryIndex& IN_InventoryIndex ,
		const FLFPInventoryItem& IN_NewData ,
		const FLFPInventoryItem& IN_OldData ,
		const FGameplayTag& IN_EventTag )
		:
		EventType( IN_EventType ) ,
		InventoryIndex( IN_InventoryIndex ) ,
		NewData( IN_NewData ) ,
		OldData( IN_OldData ) ,
		EventTag( IN_EventTag )
	{

	}

public:

	UPROPERTY()
	ELFPInventoryItemEventType EventType = ELFPInventoryItemEventType::Inventory_Add;

	UPROPERTY()
	FLFPInventoryIndex InventoryIndex = FLFPInventoryIndex();

	UPROPERTY()
	FLFPInventoryItem NewData = FLFPInventoryItem();

	UPROPERTY()
	FLFPInventoryItem OldData = FLFPInventoryItem();

	UPROPERTY()
	FGameplayTag EventTag = FGameplayTag();
};

USTRUCT()
struct LOHFUNCTIONPLUGINITEM_API FLFPInventorySlotList
{
	GENERATED_BODY()

protected:

	UPROPERTY( EditDefaultsOnly , Category = Default )
	TArray<FLFPInventorySlot> SlotList = TArray<FLFPInventorySlot>();

private:

	UPROPERTY( NotReplicated )
	TMap<FLFPInventoryInternalIndex , FLFPInventoryItem> PendingChangeMap = TMap<FLFPInventoryInternalIndex , FLFPInventoryItem>();

	UPROPERTY( NotReplicated )
	TArray<FLFPInventoryItemOperationData> PendingEventList = TArray<FLFPInventoryItemOperationData>();

public: // InventoryIndex

	FORCEINLINE FLFPInventoryInternalIndex ToInventoryIndexInternal( const FLFPInventoryIndex& InventoryIndex ) const
	{
		for ( int32 Index = 0; Index < SlotList.Num(); Index++ )
		{
			if ( SlotList[ Index ].SlotName != InventoryIndex.SlotName )
			{
				continue;
			}

			if ( SlotList[ Index ].IsItemIndexValid( InventoryIndex.SlotItemIndex ) == false )
			{
				continue;
			}

			return FLFPInventoryInternalIndex( InventoryIndex.SlotItemIndex , Index , InventoryIndex.SlotName );
		}

		return FLFPInventoryInternalIndex();
	}

	FORCEINLINE	bool IsSlotItemValid( const FLFPInventoryInternalIndex& InventoryIndex ) const
	{
		return SlotList.IsValidIndex( InventoryIndex.SlotListIndex ) && SlotList[ InventoryIndex.SlotListIndex ].IsItemDataValid( InventoryIndex.SlotItemIndex );
	}

	FORCEINLINE	bool IsSlotIndexValid( const FLFPInventoryInternalIndex& InventoryIndex ) const
	{
		return SlotList.IsValidIndex( InventoryIndex.SlotListIndex ) && SlotList[ InventoryIndex.SlotListIndex ].IsItemIndexValid( InventoryIndex.SlotItemIndex );
	}

public: // Get Slot

	FORCEINLINE const	FLFPInventoryItem& GetSlotItemConst( const FLFPInventoryInternalIndex& InventoryIndex ) const
	{
		check( SlotList.IsValidIndex( InventoryIndex.SlotListIndex ) );

		if ( auto PendingChangePtr = PendingChangeMap.Find( InventoryIndex ); PendingChangePtr != nullptr )
		{
			return *PendingChangePtr;
		}
		else
		{
			return SlotList[ InventoryIndex.SlotListIndex ].GetItemConst( InventoryIndex.SlotItemIndex );
		}
	}

	FORCEINLINE			FLFPInventoryItem& GetSlotItemRef( const FLFPInventoryInternalIndex& InventoryIndex , const bool bIsPendingChange )
	{
		check( SlotList.IsValidIndex( InventoryIndex.SlotListIndex ) );

		if ( bIsPendingChange )
		{
			if ( auto PendingChangePtr = PendingChangeMap.Find( InventoryIndex ); PendingChangePtr != nullptr )
			{
				return *PendingChangePtr;
			}
			else
			{
				return PendingChangeMap.Add( InventoryIndex , GetSlotItemConst( InventoryIndex ) );
			}
		}

		return SlotList[ InventoryIndex.SlotListIndex ].GetItemRef( InventoryIndex.SlotItemIndex );
	}

public: // Getter

	FORCEINLINE int32 GetSlotListItemNum( const FGameplayTagContainer& SlotTagList ) const
	{
		int32 TotalCount = INDEX_NONE;

		for ( int32 Index = 0; Index < SlotList.Num(); Index++ )
		{
			if ( SlotList[ Index ].SlotName.MatchesAnyExact( SlotTagList ) == false )
			{
				continue;
			}

			if ( TotalCount == INDEX_NONE )
			{
				TotalCount = 0;
			}

			TotalCount += SlotList[ Index ].GetItemNum();
		}

		return TotalCount;
	}

	FORCEINLINE int32 GetSlotItemNum( const FGameplayTag& SlotTag ) const
	{
		for ( int32 Index = 0; Index < SlotList.Num(); Index++ )
		{
			if ( SlotList[ Index ].SlotName != SlotTag )
			{
				continue;
			}

			return SlotList[ Index ].GetItemNum();
		}

		return INDEX_NONE;
	}

public: // Slot Operation

	FORCEINLINE void ReserveItemIndex( const FLFPInventoryInternalIndex& InventoryIndex )
	{
		check( SlotList.IsValidIndex( InventoryIndex.SlotListIndex ) );
		check( InventoryIndex.SlotItemIndex > INDEX_NONE );

		SlotList[ InventoryIndex.SlotListIndex ].ReserveItemIndex( InventoryIndex.SlotItemIndex );
	}

	FORCEINLINE void ClearSlotEmptyItem( const int32 SlotListIndex )
	{
		check( SlotList.IsValidIndex( SlotListIndex ) );

		SlotList[ SlotListIndex ].ClearEmptyItem();
	}

	FORCEINLINE void SortSlot( const FGameplayTagContainer& InventorySlotNameList , const TFunctionRef<bool( const FGameplayTag& SlotName )> SlotFunction , const TFunctionRef<bool( const FLFPInventoryItem& ItemDataA , const FLFPInventoryItem& ItemDataB )> Predicate , const FGameplayTag& EventTag )
	{
		for ( int32 SlotListIndex = 0; SlotListIndex < SlotList.Num(); SlotListIndex++ )
		{
			FLFPInventorySlot& SlotData = SlotList[ SlotListIndex ];

			if ( SlotData.SlotName.MatchesAny( InventorySlotNameList ) == false || SlotFunction( SlotData.SlotName ) == false )
			{
				UE_LOG( LFPInventoryComponent , Verbose , TEXT( "SortSlot Skip Slot Bacause Name Not Match : %s" ) , *InventorySlotNameList.ToString() );

				continue; // Tag Not Match Any One On Search
			}

			TArray<FLFPInventoryItem> CopyArray = SlotData.GetItemListConst();

			CopyArray.RemoveAll(
				[&] ( const FLFPInventoryItem& ItemData )
				{
					return ItemData.IsValid() == false;
				}
			);

			CopyArray.StableSort( Predicate );

			for ( int32 SlotIndex = 0; SlotIndex < SlotData.GetItemNum(); SlotIndex++ )
			{
				GetSlotItemRef( FLFPInventoryInternalIndex( SlotIndex , SlotListIndex , SlotData.SlotName ) , true ) = CopyArray.IsValidIndex( SlotIndex ) ? CopyArray[ SlotIndex ] : FLFPInventoryItem();
			}
		}
	}

public:

	FORCEINLINE void ClearPendingChange()
	{
		PendingChangeMap.Empty();
		PendingEventList.Empty();
	}

	FORCEINLINE void ApplyPendingChange( const TFunctionRef<void( const FLFPInventoryItemOperationData& OperationData )>& ItemEvent )
	{
		TSet<int32> SlotIndexList;

		for ( const auto& PendingData : PendingChangeMap )
		{
			GetSlotItemRef( PendingData.Key , false ) = PendingData.Value;

			SlotIndexList.Add( PendingData.Key.SlotListIndex );
		}

		for ( const int32 SlotIndex : SlotIndexList )
		{
			ClearSlotEmptyItem( SlotIndex );
		}

		for ( const auto& PendingEvent : PendingEventList )
		{
			ItemEvent( PendingEvent );
		}

		ClearPendingChange();
	}

	FORCEINLINE void AddPendingEvent( const FLFPInventoryItemOperationData& OperationData )
	{
		if ( OperationData.OldData != OperationData.NewData ) // Don't Send Event If No Change (Prevent Network Overload)
		{
			PendingEventList.Add( OperationData );
		}
	}

public:

	FORCEINLINE const TArray<FLFPInventorySlot>& GetSlotListConst() const
	{
		return SlotList;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FLFPInventoryItemDelegate , const FLFPInventoryItemOperationData& , ItemOperationData );

UCLASS( Blueprintable , ClassGroup = ( LFPlugin ) , meta = ( BlueprintSpawnableComponent ) )
class LOHFUNCTIONPLUGINITEM_API ULFPInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULFPInventoryComponent();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

public:
	// Called every frame
	virtual void TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;

	// Legacy Replication Support
	virtual bool ReplicateSubobjects( class UActorChannel* Channel , class FOutBunch* Bunch , FReplicationFlags* RepFlags ) override;

	virtual void Activate( bool bReset ) override;

public: // Delegate

	UPROPERTY( BlueprintAssignable , BlueprintReadWrite , Category = "LFPInventoryComponent | Events" )
	FLFPInventoryItemDelegate OnItemChange;

private: // Delegate Function

	UFUNCTION()
	void SendItemDelegateEvent( const FLFPInventoryItemOperationData& ItemOperationData ) const;

private: // Delegate Network Function

	UFUNCTION( Client , Reliable )
	void CLIENT_SendItemDelegateEvent( const FLFPInventoryItemOperationData& ItemOperationData ) const;
	void CLIENT_SendItemDelegateEvent_Implementation( const FLFPInventoryItemOperationData& ItemOperationData ) const;

public:

	/* Not Recommend, Try To Use (Find / Contain / GetSlotItem) First */
	const FLFPInventorySlotList& GetInventorySlotList() const;

	bool ProcessInventoryIndex(
		const FGameplayTagContainer& InventorySlotNameList ,
		const TFunctionRef<bool( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryInternalIndex& InternalIndex )>& IndexFunction ,
		const bool bUseMaxIndex = false ,
		const TFunction<void( const int32 SlotListIndex )> OnSlotNameEnd = nullptr
	) const;

	bool ProcessItemOperation(
		const FGameplayTagContainer& InventorySlotNameList ,
		TArray<FLFPInventoryItem>& ItemDataList ,
		const TFunctionRef<bool( const FLFPInventoryItem& ItemData )>& CheckerFunction ,
		const TFunctionRef<bool( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryInternalIndex& InternalIndex , FLFPInventoryItem& ItemData )>& IndexFunction ,
		const bool bStopOnFail = false ,
		const bool bUseMaxIndex = false
	) const;

	bool ProcessSingleItemOperation(
		const FGameplayTagContainer& InventorySlotNameList ,
		FLFPInventoryItem& ItemData ,
		const TFunctionRef<bool( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryInternalIndex& InternalIndex , FLFPInventoryItem& ItemData )>& IndexFunction ,
		const bool bUseMaxIndex = false
	) const;

protected: // Internal Function

	FORCEINLINE bool ProcessInventoryFunction(
		const TFunctionRef<bool( const TObjectPtr<ULFPItemInventoryFunction>& FunctionObj )> RunFunction
	) const;

	UFUNCTION()
	bool AddItem_Index_Uncheck_Internal( const FLFPInventoryIndex& InventoryIndex , FLFPInventoryItem& ProcessItemData , const FGameplayTag& EventTag );

	UFUNCTION()
	bool AddItem_SlotName_Internal( const FGameplayTagContainer& InventorySlotNameList , FLFPInventoryItem& ProcessItemData , const FGameplayTag& EventTag );

	UFUNCTION()
	bool AddItemList_SlotName_Internal( const FGameplayTagContainer& InventorySlotNameList , TArray<FLFPInventoryItem>& ItemDataList , const bool bStopOnFail , const FGameplayTag& EventTag );

	UFUNCTION()
	bool RemoveItem_Index_Uncheck_Internal( const FLFPInventoryIndex& InventoryIndex , FLFPInventoryItem& ProcessItemData , const FGameplayTag& EventTag );

	UFUNCTION()
	bool RemoveItem_SlotName_Internal( const FGameplayTagContainer& InventorySlotNameList , FLFPInventoryItem& ProcessItemData , const FGameplayTag& EventTag );

	UFUNCTION()
	bool RemoveItemList_SlotName_Internal( const FGameplayTagContainer& InventorySlotNameList , TArray<FLFPInventoryItem>& ItemDataList , const bool bStopOnFail , const FGameplayTag& EventTag );

	UFUNCTION()
	bool SwapItem_Index_Internal( const FLFPInventoryInternalIndex& FromIndex , const FLFPInventoryInternalIndex& ToIndex , const FGameplayTag& EventTag );

	UFUNCTION()
	bool MergeItem_Index_Internal( const FLFPInventoryInternalIndex& FromIndex , const FLFPInventoryInternalIndex& ToIndex , const FGameplayTag& EventTag );

	UFUNCTION()
	bool MergeItem_SlotName_Internal( const FLFPInventoryIndex& FromIndex , const FGameplayTagContainer& ToSlotNameList , const FGameplayTag& EventTag );

	UFUNCTION()
	bool Transfer_Index_Internal( const FLFPInventoryIndex& FromIndex , const FLFPInventoryIndex& ToIndex , ULFPInventoryComponent* TargetInventoryComponent , const bool bMustFullyTransfer , const FGameplayTag& EventTag );

	UFUNCTION()
	bool Transfer_SlotName_Internal( const FLFPInventoryIndex& FromIndex , const FGameplayTagContainer& ToSlotNameList , ULFPInventoryComponent* TargetInventoryComponent , const bool bMustFullyTransfer , const FGameplayTag& EventTag );

	UFUNCTION()
	bool UpdateItem_Index_Uncheck_Internal( const FLFPInventoryIndex& InventoryIndex , FLFPInventoryItem& ProcessItemData , const FGameplayTag& EventTag );

	UFUNCTION()
	bool UpdateItem_SlotName_Internal( const FGameplayTagContainer& InventorySlotNameList , FLFPInventoryItem& ProcessItemData , const FGameplayTag& EventTag );

	UFUNCTION()
	bool ContainItem_Index_Internal( const FLFPInventoryInternalIndex& InventoryInternalIndex , FLFPInventoryItem& ProcessItemData ) const;

	UFUNCTION()
	bool FindItem_Index_Internal( const FLFPInventoryInternalIndex& InventoryInternalIndex , FLFPInventoryItem& ProcessItemData ) const;


	UFUNCTION()
	void ApplyInventoryPendingChange();

	UFUNCTION()
	void ClearInventoryPendingChange();

public:

	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool AddItem( UPARAM( ref ) FLFPInventoryItem& ItemData , const bool bMustFullyAdd , const FGameplayTag EventTag );

	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool AddItemList( UPARAM( ref ) TArray<FLFPInventoryItem>& ItemDataList , const bool bMustFullyAdd , const FGameplayTag EventTag );

	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool AddItemBySlotName( UPARAM( meta = ( Categories = "Item.SlotName" ) )const FGameplayTagContainer InventorySlotNameList , UPARAM( ref ) FLFPInventoryItem& ItemData , const bool bMustFullyAdd , const FGameplayTag EventTag );

	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool AddItemListBySlotName( UPARAM( meta = ( Categories = "Item.SlotName" ) )const FGameplayTagContainer InventorySlotNameList , UPARAM( ref ) TArray<FLFPInventoryItem>& ItemDataList , const bool bMustFullyAdd , const FGameplayTag EventTag );

	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool AddItemByIndex( const FLFPInventoryIndex& InventoryIndex , UPARAM( ref ) FLFPInventoryItem& ItemData , const bool bMustFullyAdd , const FGameplayTag EventTag );


	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool RemoveItem( UPARAM( ref ) FLFPInventoryItem& ItemData , const bool bMustFullyRemove , const FGameplayTag EventTag );

	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool RemoveItemList( UPARAM( ref ) TArray<FLFPInventoryItem>& ItemDataList , const bool bMustFullyRemove , const FGameplayTag EventTag );

	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool RemoveItemBySlotName( UPARAM( meta = ( Categories = "Item.SlotName" ) )const FGameplayTagContainer InventorySlotNameList , UPARAM( ref ) FLFPInventoryItem& ItemData , const bool bMustFullyRemove , const FGameplayTag EventTag );

	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool RemoveItemListBySlotName( UPARAM( meta = ( Categories = "Item.SlotName" ) )const FGameplayTagContainer InventorySlotNameList , UPARAM( ref ) TArray<FLFPInventoryItem>& ItemDataList , const bool bMustFullyRemove , const FGameplayTag EventTag );

	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool RemoveItemByIndex( const FLFPInventoryIndex& InventoryIndex , UPARAM( ref ) FLFPInventoryItem& ItemData , const bool bMustFullyRemove , const FGameplayTag EventTag );


	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool SwapItemByIndex( const FLFPInventoryIndex& FromIndex , const FLFPInventoryIndex& ToIndex , const FGameplayTag EventTag );


	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool MergeItemByIndex( const FLFPInventoryIndex& FromIndex , const FLFPInventoryIndex& ToIndex , const FGameplayTag EventTag );

	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool MergeItemBySlotName( const FLFPInventoryIndex& FromIndex , const FGameplayTagContainer ToSlotNameList , const FGameplayTag EventTag );


	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool TransferItemByIndex( const FLFPInventoryIndex& FromIndex , const FLFPInventoryIndex& ToIndex , ULFPInventoryComponent* GiveInventoryComponent , const bool bMustFullyTransfer , const FGameplayTag EventTag );

	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool TransferItemBySlotName( const FLFPInventoryIndex& FromIndex , const FGameplayTagContainer ToSlotNameList , ULFPInventoryComponent* GiveInventoryComponent , const bool bMustFullyTransfer , const FGameplayTag EventTag );


	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool ExchangeItemBySlotName( const FGameplayTagContainer TakeSlotNameList , UPARAM( ref ) FLFPInventoryItem& TakeItemData , const FGameplayTagContainer GiveSlotNameList , UPARAM( ref )TArray<FLFPInventoryItem>& GiveItemDataList , const FGameplayTag EventTag );

	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool ExchangeItemListBySlotName( const FGameplayTagContainer TakeSlotNameList , UPARAM( ref ) TArray<FLFPInventoryItem>& TakeItemDataList , const FGameplayTagContainer GiveSlotNameList , UPARAM( ref ) TArray<FLFPInventoryItem>& GiveItemDataList , const FGameplayTag EventTag );


	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool TradeItemBySlotName( const FGameplayTagContainer TakeSlotNameList , UPARAM( ref ) FLFPInventoryItem& TakeItemData , const FGameplayTagContainer GiveSlotNameList , UPARAM( ref )TArray<FLFPInventoryItem>& GiveItemDataList , ULFPInventoryComponent* GiveInventoryComponent , const FGameplayTag EventTag );

	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool TradeItemListBySlotName( const FGameplayTagContainer TakeSlotNameList , UPARAM( ref )TArray<FLFPInventoryItem>& TakeItemDataList , const FGameplayTagContainer GiveSlotNameList , UPARAM( ref )TArray<FLFPInventoryItem>& GiveItemDataList , ULFPInventoryComponent* GiveInventoryComponent , const FGameplayTag EventTag );


	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool UpdateItem( UPARAM( ref ) FLFPInventoryItem& ItemData , const FGameplayTag EventTag );

	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool UpdateItemBySlotName( UPARAM( meta = ( Categories = "Item.SlotName" ) )const FGameplayTagContainer InventorySlotNameList , UPARAM( ref ) FLFPInventoryItem& ItemData , const FGameplayTag EventTag );

	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool UpdateItemByIndex( const FLFPInventoryIndex& InventoryIndex , UPARAM( ref ) FLFPInventoryItem& ItemData , const FGameplayTag EventTag );


	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	bool SortItem( UPARAM( meta = ( Categories = "Item.SlotName" ) )const FGameplayTagContainer InventorySlotNameList , UPARAM( meta = ( Categories = "Item.Sort" ) ) const FGameplayTag SortTag , const FGameplayTag EventTag );


	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	void ClearInventoryByIndex( const FLFPInventoryIndex& InventoryIndex , const FGameplayTag EventTag );

	UFUNCTION( BlueprintCallable , BlueprintAuthorityOnly , Category = "LFPInventoryComponent | Function" )
	void ClearInventoryBySlotName( UPARAM( meta = ( Categories = "Item.SlotName" ) ) const FGameplayTagContainer SlotNames , const FGameplayTag EventTag );

public:

	UFUNCTION( BlueprintPure , Category = "LFPInventoryComponent | Function" )
	ULFPItemInventoryFunction* GetFunctionObject( const TSubclassOf<ULFPItemInventoryFunction> FunctionClass ) const;

	UFUNCTION( BlueprintPure , Category = "LFPInventoryComponent | Function" )
	TArray<ULFPItemInventoryFunction*> GetFunctionObjectListByClass( const TSubclassOf<ULFPItemInventoryFunction> FunctionClass ) const;

public:

	// Start Modifier

	UFUNCTION()
	bool CanAddItem( const FLFPInventoryItem& ItemData ) const;

	UFUNCTION()
	bool CanRemoveItem( const FLFPInventoryItem& ItemData ) const;

	UFUNCTION()
	bool CanUpdateItem( const FLFPInventoryItem& ItemData ) const;

	UFUNCTION()
	bool CanFindItem( const FLFPInventoryItem& ItemData ) const;

	// Slot Check Modifier

	UFUNCTION()
	bool CanAddItemOnSlot( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryItem& CurrentData , const FLFPInventoryItem& ProcessData ) const;

	UFUNCTION()
	bool CanRemoveItemOnSlot( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryItem& CurrentData , const FLFPInventoryItem& ProcessData ) const;

	UFUNCTION()
	bool CanSwapItemOnSlot( const FLFPInventoryItem& FromItem , const FLFPInventoryIndex& FromIndex , const FLFPInventoryItem& ToItem , const FLFPInventoryIndex& ToIndex ) const;

	UFUNCTION()
	bool CanMergeItemOnSlot( const FLFPInventoryItem& FromItem , const FLFPInventoryIndex& FromIndex , const FLFPInventoryItem& ToItem , const FLFPInventoryIndex& ToIndex ) const;

	UFUNCTION()
	bool CanTransferItemOnSlot( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryItem& ItemData ) const;

	UFUNCTION()
	bool CanUpdateItemOnSlot( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryItem& CurrentData , const FLFPInventoryItem& ProcessData ) const;

	UFUNCTION()
	bool CanFindItemOnSlot( const FLFPInventoryIndex& InventoryIndex , const FLFPInventoryItem& CurrentData , const FLFPInventoryItem& ProcessData ) const;

	// Process Modifier

	UFUNCTION()
	bool ProcessAddItem( UPARAM( ref ) FLFPInventoryItem& ItemData , UPARAM( ref ) FLFPInventoryItem& ProcessData , const FLFPInventoryIndex InventoryIndex ) const;

	UFUNCTION()
	bool ProcessRemoveItem( UPARAM( ref ) FLFPInventoryItem& ItemData , UPARAM( ref ) FLFPInventoryItem& ProcessData , const FLFPInventoryIndex InventoryIndex ) const;

	UFUNCTION()
	bool ProcessSwapItem( UPARAM( ref ) FLFPInventoryItem& FromItem , const FLFPInventoryIndex& FromIndex , UPARAM( ref ) FLFPInventoryItem& ToItem , const FLFPInventoryIndex& ToIndex ) const;

	UFUNCTION()
	bool ProcessMergeItem( UPARAM( ref ) FLFPInventoryItem& FromItem , const FLFPInventoryIndex& FromIndex , UPARAM( ref ) FLFPInventoryItem& ToItem , const FLFPInventoryIndex& ToIndex ) const;

	UFUNCTION()
	bool ProcessUpdateItem( UPARAM( ref ) FLFPInventoryItem& ItemData , UPARAM( ref ) FLFPInventoryItem& ProcessData , const FLFPInventoryIndex InventoryIndex ) const;

	UFUNCTION()
	bool ProcessFindItem( const FLFPInventoryItem& ItemData , UPARAM( ref ) FLFPInventoryItem& ProcessData , const FLFPInventoryIndex InventoryIndex ) const;

	// Categorize Modifier

	UFUNCTION()
	FGameplayTagContainer GetItemAllowSlotNameList( const FLFPInventoryItem& ItemData , const FGameplayTagContainer& FilterList = FGameplayTagContainer() ) const;

	// Check Modifier

	UFUNCTION()
	bool CanSlotNameBeSort( const FGameplayTag& SlotName ) const;

	UFUNCTION()
	bool CanItemSortHigherThan( const FLFPInventoryItem& ItemDataA , const FLFPInventoryItem& ItemDataB , const FGameplayTag& SortTag ) const;

public:

	UFUNCTION( BlueprintPure , Category = "LFPInventoryComponent | Function" )
	bool ContainItem( FLFPInventoryItem ItemData , UPARAM( meta = ( Categories = "Item.SlotName" ) )const FGameplayTagContainer InventorySlotNameList ) const;

	UFUNCTION( BlueprintPure , Category = "LFPInventoryComponent | Function" )
	bool ContainItemList( const TArray<FLFPInventoryItem>& ItemDataList , UPARAM( meta = ( Categories = "Item.SlotName" ) )const FGameplayTagContainer InventorySlotNameList , const bool bPartially = false ) const;

public:

	UFUNCTION( BlueprintPure , Category = "LFPInventoryComponent | Function" )
	bool IsSlotNameValid( const FGameplayTag SlotName ) const;

	UFUNCTION( BlueprintPure , Category = "LFPInventoryComponent | Function" )
	bool IsInventoryIndexValid( const FLFPInventoryIndex& InventoryIndex ) const;

public:

	UFUNCTION( BlueprintPure , Category = "LFPInventoryComponent | Function" )
	const FLFPInventoryItem& GetSlotItem( const FLFPInventoryIndex& InventoryIndex ) const;

	UFUNCTION( BlueprintPure , Category = "LFPInventoryComponent | Function" )
	int32 GetSlotListItemNum( const FGameplayTagContainer& SlotTagList ) const;

	UFUNCTION( BlueprintPure , Category = "LFPInventoryComponent | Function" )
	int32 GetSlotItemNum( const FGameplayTag& SlotTag ) const;

public:

	UFUNCTION( BlueprintCallable , Category = "LFPInventoryComponent | Function" )
	bool FindInventoryIndexList( TArray<FLFPInventoryIndex>& InventoryIndexList , FLFPInventoryItem ItemData , UPARAM( meta = ( Categories = "Item.SlotName" ) )const FGameplayTagContainer InventorySlotNameList , const int32 MaxListItem = -1 ) const;

	UFUNCTION( BlueprintCallable , Category = "LFPInventoryComponent | Function" )
	bool FindItemDataList( TArray<FLFPInventoryItem>& ItemDataList , FLFPInventoryItem ItemData , UPARAM( meta = ( Categories = "Item.SlotName" ) )const FGameplayTagContainer InventorySlotNameList , const int32 MaxListItem = -1 ) const;

	UFUNCTION( BlueprintCallable , Category = "LFPInventoryComponent | Function" )
	bool FindInventoryIndexListByItemTag( TArray<FLFPInventoryIndex>& InventoryIndexList , UPARAM( meta = ( Categories = "Item.SlotName" ) ) const FGameplayTagContainer InventorySlotNameList , UPARAM( meta = ( Categories = "Item.Identifier" ) )const FGameplayTagContainer ItemTagList , const int32 MaxListItem = -1 ) const;

	UFUNCTION( BlueprintCallable , Category = "LFPInventoryComponent | Function" )
	bool FindItemDataListByItemTag( TArray<FLFPInventoryItem>& ItemDataList , UPARAM( meta = ( Categories = "Item.SlotName" ) ) const FGameplayTagContainer InventorySlotNameList , UPARAM( meta = ( Categories = "Item.Identifier" ) )const FGameplayTagContainer ItemTagList , const int32 MaxListItem = -1 ) const;

protected:

	UPROPERTY( EditDefaultsOnly , Replicated , Category = "LFPInventoryComponent | Variable" )
	FLFPInventorySlotList InventorySlot = FLFPInventorySlotList();

	UPROPERTY( EditDefaultsOnly , Instanced , Replicated , Category = "LFPInventoryComponent | Variable" )
	TArray<TObjectPtr<ULFPItemInventoryFunction>> FunctionList = TArray<TObjectPtr<ULFPItemInventoryFunction>>();

	/* Limit Loop Num On New Add / Swap Index */
	UPROPERTY( EditDefaultsOnly , Category = "LFPInventoryComponent | Setting" )
	int32 ExtraLoopSlot = 32;
};
