#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LFPCompressDataLibrary.generated.h"

DECLARE_LOG_CATEGORY_EXTERN( LFPCompressNumberStaticArray , Log , All );

USTRUCT()
struct FLFPCompressNumberStaticArray
{
	GENERATED_BODY()

public:

	FLFPCompressNumberStaticArray() {
	}

	FLFPCompressNumberStaticArray( const uint32 NewSize ) : IndexSize( NewSize ) {
	}

	FLFPCompressNumberStaticArray( const uint32 NewIndexSize , const uint32 NewMinSize ) : IndexSize( NewIndexSize ) , MinBitSize( NewMinSize ) {
	}

private:

	UPROPERTY()
	TArray<uint32> IndexList = TArray<uint32>();

	UPROPERTY()
	uint32 IndexSize = 0;

	UPROPERTY()
	uint8 EncodeBit = 0;

	UPROPERTY()
	uint8 MinBitSize = 0;

	UPROPERTY()
	bool bIsBitSizeDirty = false;

private:

	/** Read / Write Bit Function */

	FORCEINLINE FBitReference GetIndexRef( const int32 Index )
	{
		return FBitReference(
			IndexList.GetData()[ Index / NumBitsPerDWORD ] ,
			1 << ( Index & ( NumBitsPerDWORD - 1 ) )
		);
	}

	FORCEINLINE FConstBitReference GetIndexConstRef( const int32 Index ) const
	{
		return FConstBitReference(
			IndexList.GetData()[ Index / NumBitsPerDWORD ] ,
			1 << ( Index & ( NumBitsPerDWORD - 1 ) )
		);
	}

private:

	FORCEINLINE void UpdateBitSize()
	{
		if ( bIsBitSizeDirty == false )
		{
			return;
		}

		bIsBitSizeDirty = false;

		const uint8 NewSize = FMath::Max( NewSize , GetNewBitSize() );

		UE_LOG( LFPCompressNumberStaticArray , Log , TEXT( "FLFPCompressNumberStaticArray : Resize Bit To %d" ) , NewSize );

		// No need to change
		if ( NewSize == EncodeBit )
		{
			return;
		}

		// Clear data
		if ( NewSize == 0 )
		{
			IndexList.Empty();

			EncodeBit = NewSize;

			return;
		}

		const TArray<uint32> OldIndexList = MoveTemp( IndexList );

		const uint8 OldSize = EncodeBit;

		EncodeBit = NewSize;

		const int32 ChuckBitSize = FMath::DivideAndRoundUp( IndexSize , ( uint32 ) sizeof( uint32 ) * 4 );

		IndexList.Init( 0 , ( EncodeBit * ChuckBitSize ) );

		if ( OldSize == 0 ) return; // No data to copy

		for ( uint32 DataIndex = 0; DataIndex < IndexSize; DataIndex++ )
		{
			for ( uint8 EncodeIndex = 0; EncodeIndex < OldSize; EncodeIndex++ )
			{
				const int32 OldBitIndex = int32( ( DataIndex * OldSize ) + EncodeIndex );
				const int32 NewBitIndex = int32( ( DataIndex * EncodeBit ) + EncodeIndex );

				GetIndexRef( NewBitIndex ) = FConstBitReference(
					OldIndexList.GetData()[ OldBitIndex / NumBitsPerDWORD ] ,
					1 << ( OldBitIndex & ( NumBitsPerDWORD - 1 ) )
				);
			}
		}
	}

protected:

	virtual uint8 GetNewBitSize() const
	{
		return 0;
	}

public:

	FORCEINLINE bool HasData() const
	{
		return EncodeBit > 0 && IndexSize > 0;
	}

	FORCEINLINE bool IsInitialized() const
	{
		return IndexSize > 0;
	}

	FORCEINLINE bool IsValidIndex( const int32 Index ) const
	{
		return Index >= 0 && Index < int32( IndexSize );
	}

	/** Read / Write Function */

	FORCEINLINE void SetIndexNumber( const int32 Index , const uint32 Number )
	{
		checkf( IsValidIndex( Index ) && HasData() , TEXT( "Index : %d, EncodeBtye : %u" ) , Index , EncodeBit );

		for ( uint8 EncodeIndex = 0; EncodeIndex < EncodeBit; EncodeIndex++ )
		{
			const int32 BitIndex = ( Index * EncodeBit ) + EncodeIndex;

			GetIndexRef( BitIndex ) = FConstBitReference( Number , 1 << EncodeIndex );
		}
	}

	FORCEINLINE uint32 GetIndexNumber( const int32 Index ) const
	{
		checkf( IsValidIndex( Index ) , TEXT( "Index : %d, EncodeBtye : %u" ) , Index , EncodeBit );

		uint32 OutIndex = 0;

		for ( uint8 EncodeIndex = 0; EncodeIndex < EncodeBit; EncodeIndex++ )
		{
			const int32 BitIndex = ( Index * EncodeBit ) + EncodeIndex;

			FBitReference( OutIndex , 1 << EncodeIndex ) = GetIndexConstRef( BitIndex );
		}

		return OutIndex;
	}

	/** Debug Function */

	FORCEINLINE uint8 GetEncodeLength() const
	{
		return EncodeBit;
	}

	FORCEINLINE uint32 GetIndexSize() const
	{
		return IndexSize;
	}
};

UCLASS()
class LOHFUNCTIONPLUGIN_API ULFPCompressDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

};
