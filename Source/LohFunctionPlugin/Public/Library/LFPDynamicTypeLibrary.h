#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LFPDynamicTypeLibrary.generated.h"

DECLARE_LOG_CATEGORY_EXTERN( LFPDynamicIntStaticArray , Log , All );

USTRUCT( BlueprintType )
struct LOHFUNCTIONPLUGIN_API FLFPDynamicIntStaticArray
{
	GENERATED_BODY()

	FLFPDynamicIntStaticArray() {
	}

	FLFPDynamicIntStaticArray( const uint32 NewIndexSize ) : IndexSize( NewIndexSize ) {
	}

	FLFPDynamicIntStaticArray( const uint32 NewIndexSize , const uint8 NewDataAlignment ) : IndexSize( NewIndexSize ) , ElementAlignment( NewDataAlignment ) {
	}

private:

	UPROPERTY()
	TArray<uint32> DataList = TArray<uint32>();

	UPROPERTY()
	uint32 IndexSize = 0;

	UPROPERTY()
	uint8 ElementBitSize = 0;

	UPROPERTY()
	uint8 ElementAlignment = 4;

private:

	/** Read / Write Bit Function */

	FORCEINLINE FBitReference GetIndexRef( TArray<uint32>& GridIndexListRef , const int32 Index )
	{
		return FBitReference(
			GridIndexListRef.GetData()[ Index / NumBitsPerDWORD ] ,
			1 << ( Index & ( NumBitsPerDWORD - 1 ) )
		);
	}

	FORCEINLINE FConstBitReference GetIndexConstRef( const TArray<uint32>& GridIndexListRef , const int32 Index ) const
	{
		return FConstBitReference(
			GridIndexListRef.GetData()[ Index / NumBitsPerDWORD ] ,
			1 << ( Index & ( NumBitsPerDWORD - 1 ) )
		);
	}

	FORCEINLINE void ResizeBitArray( uint8 NewSize )
	{
		check( NewSize >= 0 );

		UE_LOG( LFPDynamicIntStaticArray , Log , TEXT( "FLFPCompactIntArray : Resize Bit To %d" ) , NewSize );

		if ( NewSize > 0 )
		{
			NewSize = FMath::DivideAndRoundUp( NewSize , ElementAlignment ) * ElementAlignment;
		}

		if ( NewSize == ElementBitSize ) return;

		if ( NewSize == 0 )
		{
			DataList.Empty();

			ElementBitSize = NewSize;

			return;
		}

		const TArray<uint32> OldDataList = MoveTemp( DataList );

		const uint8 OldElementBitSize = ElementBitSize;

		ElementBitSize = NewSize;

		const int32 ChuckBitSize = FMath::DivideAndRoundUp( IndexSize , uint32( 32 ) );

		DataList.Init( 0 , ( NewSize * ChuckBitSize ) );

		if ( OldElementBitSize == 0 ) return;

		for ( uint32 GridIndex = 0; GridIndex < IndexSize; GridIndex++ )
		{
			for ( uint8 EncodeIndex = 0; EncodeIndex < OldElementBitSize; EncodeIndex++ )
			{
				const int32 OldBitIndex = int32( ( GridIndex * OldElementBitSize ) + EncodeIndex );
				const int32 NewBitIndex = int32( ( GridIndex * ElementBitSize ) + EncodeIndex );

				GetIndexRef( DataList , NewBitIndex ) = GetIndexConstRef( OldDataList , OldBitIndex );
			}
		}
	}

public:

	FORCEINLINE bool HasData() const
	{
		return ElementBitSize > 0 && IsInitialized();
	}

	FORCEINLINE bool IsInitialized() const
	{
		return IndexSize > 0;
	}

	FORCEINLINE bool IsValidIndex( const int32 Index ) const
	{
		return Index >= 0 && Index < int32( IndexSize );
	}

	/** Resize Function */

	FORCEINLINE void ResizeElement( const int32 NewMaxNumber )
	{
		for ( uint8 NewEncodeSize = 1; NewEncodeSize < NumBitsPerDWORD; NewEncodeSize++ )
		{
			if ( NewMaxNumber <= ( 1 << NewEncodeSize ) - 1 )
			{
				ResizeBitArray( NewEncodeSize );

				break;
			}
		}

		return;
	}

	/** Read / Write Function */

	FORCEINLINE void SetIndexNumber( const int32 Index , const uint32 Number )
	{
		checkf( IsValidIndex( Index ) && HasData() , TEXT( "Index : %d, EncodeBtye : %u" ) , Index , ElementBitSize );

		for ( uint8 EncodeIndex = 0; EncodeIndex < ElementBitSize; EncodeIndex++ )
		{
			const int32 BitIndex = ( Index * ElementBitSize ) + EncodeIndex;

			GetIndexRef( DataList , BitIndex ) = FConstBitReference( Number , 1 << EncodeIndex );
		}
	}

	FORCEINLINE uint32 GetIndexNumber( const int32 Index ) const
	{
		checkf( IsValidIndex( Index ) , TEXT( "Index : %d, EncodeBtye : %u" ) , Index , ElementBitSize );

		uint32 OutIndex = 0;

		for ( uint8 EncodeIndex = 0; EncodeIndex < ElementBitSize; EncodeIndex++ )
		{
			const int32 BitIndex = ( Index * ElementBitSize ) + EncodeIndex;

			FBitReference( OutIndex , 1 << EncodeIndex ) = GetIndexConstRef( DataList , BitIndex );
		}

		return OutIndex;
	}

public:

	FORCEINLINE uint8 GetEncodeLength() const
	{
		return ElementBitSize;
	}

	FORCEINLINE uint32 GetIndexSize() const
	{
		return IndexSize;
	}

};

USTRUCT( BlueprintType )
struct LOHFUNCTIONPLUGIN_API FLFPIDTrackerStaticArray : public FLFPDynamicIntStaticArray
{
	GENERATED_BODY()

	FLFPIDTrackerStaticArray() {
	}

	FLFPIDTrackerStaticArray( const uint32 NewIndexSize ) : Super( NewIndexSize ) {
	}

	FLFPIDTrackerStaticArray( const uint32 NewIndexSize , const uint8 NewDataAlignment ) : Super( NewIndexSize , NewDataAlignment ) {
	}

private:

	UPROPERTY()
	TArray<int32> OpenIDList = {};

	UPROPERTY()
	TArray<int32> IDRefList = {};

protected:

	/** Resize Function */

	FORCEINLINE void ResizeID()
	{
		for ( int32 IDIndex = IDRefList.Num() - 1; IDIndex >= 0; --IDIndex )
		{
			if ( IDRefList[ IDIndex ] == 0 )
			{
				IDRefList.RemoveAt( IDIndex , EAllowShrinking::No );

				OpenIDList.HeapRemoveAt( OpenIDList.IndexOfByKey( IDIndex ) , EAllowShrinking::No );
			}
			else
			{
				break;
			}
		}

		OpenIDList.Shrink();
		IDRefList.Shrink();

		ResizeElement( IDRefList.Num() );

		return;
	}

public:

	FORCEINLINE int32 GetNewID() const
	{
		if ( OpenIDList.IsEmpty() == false )
		{
			return OpenIDList[ 0 ];
		}
		else
		{
			return IDRefList.Num();
		};
	}

	FORCEINLINE void RemoveRef( const int32 IDIndex )
	{
		check( IDRefList.IsValidIndex( IDIndex ) );

		check( IDRefList[ IDIndex ] > 0 );

		IDRefList[ IDIndex ]--;

		if ( IDRefList[ IDIndex ] == 0 )
		{
			if ( IDRefList.Num() - 1 == IDIndex )
			{
				IDRefList.RemoveAt( IDIndex );

				ResizeID();
			}
			else
			{
				OpenIDList.HeapPush( IDIndex );
			}
		}
	}

	FORCEINLINE void RemoveRefOnArrayIndex( const int32 ArrayIndex )
	{
		check( IsValidIndex( ArrayIndex ) );

		RemoveRef( GetID( ArrayIndex ) );
	}

	FORCEINLINE void AddRef( const int32 IDIndex )
	{
		bool bNeedResize = false;

		if ( IDRefList.IsValidIndex( IDIndex ) == false )
		{
			const int32 OldNum = IDRefList.Num();

			IDRefList.SetNum( IDIndex + 1 );

			for ( int32 Index = OldNum; Index < IDRefList.Num() - 1; Index++ )
			{
				OpenIDList.HeapPush( Index );
			}

			bNeedResize = true;
		}
		else if ( IDRefList[ IDIndex ] == 0 )
		{
			// In case this ID come from OpenIDList
			if ( const int32 OpenID = OpenIDList.IndexOfByKey( IDIndex ); OpenID != INDEX_NONE )
			{
				OpenIDList.HeapRemoveAt( OpenID );
			}
		}

		check( IDRefList[ IDIndex ] >= 0 );

		IDRefList[ IDIndex ]++;

		if ( bNeedResize )
		{
			ResizeID();
		}
	}

	FORCEINLINE int32 GetID( const int32 ArrayIndex ) const
	{
		check( IsValidIndex( ArrayIndex ) );

		return GetIndexNumber( ArrayIndex ) - 1;
	}

	FORCEINLINE void SetID( const int32 ArrayIndex , const int32 IDIndex )
	{
		check( IsValidIndex( ArrayIndex ) );
		check( IDIndex + 1 >= 0 );

		const int32 IndexCurrentID = GetID( ArrayIndex );

		if ( IndexCurrentID == IDIndex )
		{
			return;
		}

		if ( IndexCurrentID > 0 )
		{
			RemoveRefOnArrayIndex( ArrayIndex );
		}

		if ( IDIndex >= 0 )
		{
			AddRef( IDIndex );
		}

		SetIndexNumber( ArrayIndex , IDIndex + 1 );

		return;
	}

	FORCEINLINE int32 IDLength() const
	{
		if ( HasData() == false )
		{
			return 0;
		}

		return IDRefList.Num();
	}
};

USTRUCT( BlueprintType )
struct LOHFUNCTIONPLUGIN_API FLFPRefTagStaticArray : public FLFPIDTrackerStaticArray
{
	GENERATED_BODY()

	FLFPRefTagStaticArray() {
	}

	FLFPRefTagStaticArray( const uint32 NewIndexSize ) : Super( NewIndexSize ) {
	}

	FLFPRefTagStaticArray( const uint32 NewIndexSize , const uint8 NewDataAlignment , const FGameplayTag& StartTag ) : Super( NewIndexSize , NewDataAlignment )
	{
		if ( StartTag.IsValid() == false )
		{
			return;
		}

		ItemList.Add( StartTag );

		for ( uint32 ArrayIndex = 0; ArrayIndex < NewIndexSize; ArrayIndex++ )
		{
			SetID( ArrayIndex , 0 );
		}
	}

private:

	UPROPERTY()
	TArray<FGameplayTag> ItemList = {};

public:

	FORCEINLINE void SetItem( const int32 ArrayIndex , const FGameplayTag& Item )
	{
		check( IsValidIndex( ArrayIndex ) );

		int32 NewItemIndex = INDEX_NONE;

		if ( Item.IsValid() )
		{
			if ( NewItemIndex = ItemList.IndexOfByKey( Item ); NewItemIndex != INDEX_NONE )
			{
				NewItemIndex = GetNewID();

				if ( ItemList.IsValidIndex( NewItemIndex ) == false )
				{
					ItemList.SetNum( NewItemIndex + 1 );
				}

				ItemList[ NewItemIndex ] = Item;
			}
		}

		SetID( ArrayIndex , NewItemIndex );

		ItemList.SetNum( IDLength() );
	}

	FORCEINLINE const TArray<FGameplayTag>& GetItemList() const
	{
		return ItemList;
	}

	FORCEINLINE FGameplayTag GetItem( const int32 ArrayIndex ) const
	{
		const int32 ID = GetID( ArrayIndex );

		return ID != INDEX_NONE ? ItemList[ ID ] : FGameplayTag::EmptyTag;
	}
};

UCLASS()
class LOHFUNCTIONPLUGIN_API ULFPDynamicTypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

};
