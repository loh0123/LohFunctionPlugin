#pragma once

#include "CoreMinimal.h"
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

	FLFPDynamicIntStaticArray( const uint32 NewIndexSize , const uint32 NewMinSize ) : IndexSize( NewIndexSize ) , MinElementBitSize( NewMinSize ) {
	}

private:

	UPROPERTY()
	TArray<uint32> DataList = TArray<uint32>();

	UPROPERTY()
	uint32 IndexSize = 0;

	UPROPERTY()
	uint8 ElementBitSize = 0;

	UPROPERTY()
	uint8 MinElementBitSize = 0;

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
			NewSize = FMath::Max( NewSize , MinElementBitSize );
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

	/** Debug Function */

	FORCEINLINE uint8 GetEncodeLength() const
	{
		return ElementBitSize;
	}

	FORCEINLINE uint32 GetIndexSize() const
	{
		return IndexSize;
	}

};

UCLASS()
class LOHFUNCTIONPLUGIN_API ULFPDynamicTypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

};
