#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LFPDynamicTypeLibrary.generated.h"

DECLARE_LOG_CATEGORY_EXTERN ( LFPDynamicIntStaticArray , Log , All );

USTRUCT ( BlueprintType )
struct LOHFUNCTIONPLUGIN_API FLFPDynamicIntStaticArray
{
	GENERATED_BODY ( )

	FLFPDynamicIntStaticArray ( )
	{
	}

	FLFPDynamicIntStaticArray ( const uint32 NewIndexSize ) : IndexSize ( NewIndexSize )
	{
	}

	FLFPDynamicIntStaticArray ( const uint32 NewIndexSize , const uint8 NewDataAlignment ) : IndexSize ( NewIndexSize ), ElementAlignment ( NewDataAlignment )
	{
	}

private:

	UPROPERTY ( )
	TArray < uint32 > DataList = TArray < uint32 > ( );

	UPROPERTY ( )
	uint32 IndexSize = 0;

	UPROPERTY ( )
	uint8 ElementBitSize = 0;

	UPROPERTY ( )
	uint8 ElementAlignment = 4;

	/** Read / Write Function */

	FORCEINLINE FBitReference GetIndexRef ( const int32 Index )
	{
		return FBitReference (
		                      DataList.GetData ( ) [ Index / NumBitsPerDWORD ] ,
		                      1 << ( Index & ( NumBitsPerDWORD - 1 ) )
		                     );
	}

	FORCEINLINE FConstBitReference GetIndexConstRef ( const int32 Index ) const
	{
		return FConstBitReference (
		                           DataList.GetData ( ) [ Index / NumBitsPerDWORD ] ,
		                           1 << ( Index & ( NumBitsPerDWORD - 1 ) )
		                          );
	}

	FORCEINLINE void ResizeBitArray ( uint8 NewSize )
	{
		check ( NewSize >= static_cast<uint8>(0) );

		if ( NewSize > 0 )
		{
			NewSize = FMath::DivideAndRoundUp ( NewSize , ElementAlignment ) * ElementAlignment;
		}

		if ( NewSize == 0 )
		{
			DataList.Empty ( );

			UE_LOG ( LFPDynamicIntStaticArray , Verbose , TEXT( "FLFPCompactIntArray : Resize Bit From %d To %d" ) , ElementBitSize , NewSize );

			ElementBitSize = NewSize;

			return;
		}

		if ( NewSize == ElementBitSize )
		{
			return;
		}

		const TArray < uint32 > OldDataList = MoveTemp ( DataList );

		const uint8 OldElementBitSize = ElementBitSize;

		ElementBitSize = NewSize;

		UE_LOG ( LFPDynamicIntStaticArray , Verbose , TEXT( "FLFPCompactIntArray : Resize Bit From %d To %d" ) , OldElementBitSize , ElementBitSize );

		const int32 ChuckBitSize = FMath::DivideAndRoundUp ( IndexSize , static_cast < uint32 > ( 32 ) );

		DataList.Init ( 0 , ( NewSize * ChuckBitSize ) );

		if ( OldElementBitSize == 0 )
		{
			return;
		}

		for ( uint32 GridIndex = 0 ; GridIndex < IndexSize ; GridIndex++ )
		{
			for ( uint8 EncodeIndex = 0 ; EncodeIndex < OldElementBitSize ; EncodeIndex++ )
			{
				const int32 OldBitIndex = static_cast < int32 > ( ( GridIndex * OldElementBitSize ) + EncodeIndex );
				const int32 NewBitIndex = static_cast < int32 > ( ( GridIndex * ElementBitSize ) + EncodeIndex );

				GetIndexRef ( NewBitIndex ) =
					FConstBitReference (
					                    OldDataList.GetData ( ) [ OldBitIndex / NumBitsPerDWORD ] ,
					                    1 << ( OldBitIndex & ( NumBitsPerDWORD - 1 ) )
					                   );
			}
		}
	}

public:

	FORCEINLINE bool HasData ( ) const
	{
		return ElementBitSize > 0 && IsInitialized ( );
	}

	FORCEINLINE bool IsInitialized ( ) const
	{
		return IndexSize > 0;
	}

	FORCEINLINE bool IsValidIndex ( const int32 Index ) const
	{
		return Index >= 0 && Index < static_cast < int32 > ( IndexSize );
	}

	/** Resize Function */

	FORCEINLINE void ResizeElement ( const int32 NewMaxNumber )
	{
		for ( uint8 NewEncodeSize = 1 ; NewEncodeSize < NumBitsPerDWORD ; NewEncodeSize++ )
		{
			if ( NewMaxNumber <= ( 1 << NewEncodeSize ) - 1 )
			{
				ResizeBitArray ( NewEncodeSize );

				break;
			}
		}
	}

	/** Read / Write Function */

	FORCEINLINE void SetIndexNumber ( const int32 Index , const uint32 Number )
	{
		checkf ( IsValidIndex( Index ) && HasData() , TEXT( "Index : %d, EncodeByte : %u" ) , Index , ElementBitSize );

		for ( uint8 EncodeIndex = 0 ; EncodeIndex < ElementBitSize ; EncodeIndex++ )
		{
			const int32 BitIndex = ( Index * ElementBitSize ) + EncodeIndex;

			GetIndexRef ( BitIndex ) = FConstBitReference ( Number , 1 << EncodeIndex );
		}
	}

	FORCEINLINE uint32 GetIndexNumber ( const int32 Index ) const
	{
		checkf ( IsValidIndex( Index ) , TEXT( "Index : %d, EncodeByte : %u" ) , Index , ElementBitSize );

		uint32 OutIndex = 0;

		for ( uint8 EncodeIndex = 0 ; EncodeIndex < ElementBitSize ; EncodeIndex++ )
		{
			const int32 BitIndex = ( Index * ElementBitSize ) + EncodeIndex;

			FBitReference ( OutIndex , 1 << EncodeIndex ) = GetIndexConstRef ( BitIndex );
		}

		return OutIndex;
	}

	FORCEINLINE uint8 GetEncodeLength ( ) const
	{
		return ElementBitSize;
	}

	FORCEINLINE uint32 GetIndexSize ( ) const
	{
		return IndexSize;
	}
};

USTRUCT ( BlueprintType )
struct LOHFUNCTIONPLUGIN_API FLFPIndexTrackerStaticArray : public FLFPDynamicIntStaticArray
{
	GENERATED_BODY ( )

	FLFPIndexTrackerStaticArray ( )
	{
	}

	FLFPIndexTrackerStaticArray ( const uint32 NewIndexSize ) : Super ( NewIndexSize )
	{
	}

	FLFPIndexTrackerStaticArray ( const uint32 NewIndexSize , const uint8 NewDataAlignment ) : Super ( NewIndexSize , NewDataAlignment )
	{
	}

private:

	UPROPERTY ( )
	TArray < int32 > OpenIDList = { };

	UPROPERTY ( )
	TArray < int32 > IDCountList = { };

protected:

	/** Resize Function */

	FORCEINLINE void ResizeID ( )
	{
		for ( int32 IDIndex = IDCountList.Num ( ) - 1 ; IDIndex >= 0 ; --IDIndex )
		{
			if ( IDCountList [ IDIndex ] == 0 )
			{
				IDCountList.RemoveAt ( IDIndex , EAllowShrinking::No );

				OpenIDList.HeapRemoveAt ( OpenIDList.IndexOfByKey ( IDIndex ) , EAllowShrinking::No );
			}
			else
			{
				break;
			}
		}

		OpenIDList.Shrink ( );
		IDCountList.Shrink ( );

		ResizeElement ( IDCountList.Num ( ) );
	}

public:

	FORCEINLINE int32 GetNewID ( ) const
	{
		if ( OpenIDList.IsEmpty ( ) == false )
		{
			return OpenIDList [ 0 ];
		}
		return IDCountList.Num ( );
	}

	FORCEINLINE void RemoveRef ( const int32 IDIndex )
	{
		check ( IDCountList.IsValidIndex( IDIndex ) );

		check ( IDCountList[ IDIndex ] > 0 );

		IDCountList [ IDIndex ]--;

		if ( IDCountList [ IDIndex ] == 0 )
		{
			if ( IDCountList.Num ( ) - 1 == IDIndex )
			{
				IDCountList.RemoveAt ( IDIndex );

				ResizeID ( );
			}
			else
			{
				OpenIDList.HeapPush ( IDIndex );
			}
		}
	}

	FORCEINLINE void RemoveRefOnArrayIndex ( const int32 ArrayIndex )
	{
		check ( IsValidIndex( ArrayIndex ) );

		RemoveRef ( GetID ( ArrayIndex ) );
	}

	FORCEINLINE void AddRef ( const int32 IDIndex )
	{
		bool bNeedResize = false;

		if ( IDCountList.IsValidIndex ( IDIndex ) == false )
		{
			const int32 OldNum = IDCountList.Num ( );

			IDCountList.SetNum ( IDIndex + 1 );

			for ( int32 Index = OldNum ; Index < IDCountList.Num ( ) - 1 ; Index++ )
			{
				OpenIDList.HeapPush ( Index );
			}

			bNeedResize = true;
		}
		else if ( IDCountList [ IDIndex ] == 0 )
		{
			// In case this ID come from OpenIDList
			if ( const int32 OpenID = OpenIDList.IndexOfByKey ( IDIndex ) ; OpenID != INDEX_NONE )
			{
				OpenIDList.HeapRemoveAt ( OpenID );
			}
		}

		check ( IDCountList[ IDIndex ] >= 0 );

		IDCountList [ IDIndex ]++;

		if ( bNeedResize )
		{
			ResizeID ( );
		}
	}

	FORCEINLINE int32 GetID ( const int32 ArrayIndex ) const
	{
		check ( IsValidIndex( ArrayIndex ) );

		return GetIndexNumber ( ArrayIndex ) - 1;
	}

	FORCEINLINE void SetID ( const int32 ArrayIndex , const int32 IDIndex )
	{
		check ( IsValidIndex( ArrayIndex ) );
		check ( IDIndex + 1 >= 0 );

		const int32 IndexCurrentID = GetID ( ArrayIndex );

		if ( IndexCurrentID == IDIndex )
		{
			return;
		}

		if ( IndexCurrentID > 0 )
		{
			RemoveRefOnArrayIndex ( ArrayIndex );
		}

		if ( IDIndex >= 0 )
		{
			AddRef ( IDIndex );
		}

		SetIndexNumber ( ArrayIndex , IDIndex + 1 );
	}

	FORCEINLINE int32 IDLength ( ) const
	{
		if ( HasData ( ) == false )
		{
			return 0;
		}

		return IDCountList.Num ( );
	}

	FORCEINLINE int32 GetIDCount ( const int32 ID ) const
	{
		check ( IDCountList.IsValidIndex( ID ) );

		return IDCountList [ ID ];
	}
};

USTRUCT ( BlueprintType )
struct LOHFUNCTIONPLUGIN_API FLFPIDTrackerStaticArray : public FLFPIndexTrackerStaticArray
{
	GENERATED_BODY ( )

	FLFPIDTrackerStaticArray ( )
	{
	}

	FLFPIDTrackerStaticArray ( const uint32 NewIndexSize ) : Super ( NewIndexSize )
	{
	}

	FLFPIDTrackerStaticArray ( const uint32 NewIndexSize , const uint8 NewDataAlignment , const int32 StartID ) : Super ( NewIndexSize , NewDataAlignment )
	{
		if ( StartID == INDEX_NONE )
		{
			return;
		}

		ItemList.Add ( StartID );

		for ( uint32 ArrayIndex = 0 ; ArrayIndex < NewIndexSize ; ArrayIndex++ )
		{
			SetID ( ArrayIndex , 0 );
		}
	}

private:

	UPROPERTY ( )
	TArray < int32 > ItemList = { };

public:

	FORCEINLINE void SetItem ( const int32 ArrayIndex , const int32 Item )
	{
		check ( IsValidIndex( ArrayIndex ) );

		int32 NewItemIndex = INDEX_NONE;

		if ( Item != INDEX_NONE )
		{
			if ( NewItemIndex = ItemList.IndexOfByKey ( Item ) ; NewItemIndex == INDEX_NONE )
			{
				NewItemIndex = GetNewID ( );

				if ( ItemList.IsValidIndex ( NewItemIndex ) == false )
				{
					ItemList.SetNum ( NewItemIndex + 1 );
				}

				ItemList [ NewItemIndex ] = Item;
			}
		}

		SetID ( ArrayIndex , NewItemIndex );

		ItemList.SetNum ( IDLength ( ) );
	}

	FORCEINLINE const TArray < int32 >& GetItemList ( ) const
	{
		return ItemList;
	}

	FORCEINLINE int32 GetItem ( const int32 ArrayIndex ) const
	{
		const int32 ID = GetID ( ArrayIndex );

		return ID != INDEX_NONE
		       ? ItemList [ ID ]
		       : INDEX_NONE;
	}

	FORCEINLINE int32 GetItemCount ( const int32 Item ) const
	{
		if ( const int32 ID = ItemList.IndexOfByKey ( Item ) ; ID >= 0 )
		{
			return GetIDCount ( ID );
		}

		return INDEX_NONE;
	}

	FORCEINLINE bool ContainItem ( const int32 Item ) const
	{
		return ItemList.Contains ( Item );
	}
};

USTRUCT ( BlueprintType )
struct LOHFUNCTIONPLUGIN_API FLFPTagTrackerStaticArray : public FLFPIndexTrackerStaticArray
{
	GENERATED_BODY ( )

	FLFPTagTrackerStaticArray ( )
	{
	}

	FLFPTagTrackerStaticArray ( const uint32 NewIndexSize ) : Super ( NewIndexSize )
	{
	}

	FLFPTagTrackerStaticArray ( const uint32 NewIndexSize , const uint8 NewDataAlignment , const FGameplayTag& StartTag ) : Super ( NewIndexSize , NewDataAlignment )
	{
		if ( StartTag.IsValid ( ) == false )
		{
			return;
		}

		ItemList.Add ( StartTag );

		for ( uint32 ArrayIndex = 0 ; ArrayIndex < NewIndexSize ; ArrayIndex++ )
		{
			SetID ( ArrayIndex , 0 );
		}
	}

private:

	UPROPERTY ( )
	TArray < FGameplayTag > ItemList = { };

public:

	FORCEINLINE void SetItem ( const int32 ArrayIndex , const FGameplayTag& Item )
	{
		check ( IsValidIndex( ArrayIndex ) );

		int32 NewItemIndex = INDEX_NONE;

		if ( Item.IsValid ( ) )
		{
			if ( NewItemIndex = ItemList.IndexOfByKey ( Item ) ; NewItemIndex == INDEX_NONE )
			{
				NewItemIndex = GetNewID ( );

				if ( ItemList.IsValidIndex ( NewItemIndex ) == false )
				{
					ItemList.SetNum ( NewItemIndex + 1 );
				}

				ItemList [ NewItemIndex ] = Item;
			}
		}

		SetID ( ArrayIndex , NewItemIndex );

		ItemList.SetNum ( IDLength ( ) );
	}

	FORCEINLINE const TArray < FGameplayTag >& GetItemList ( ) const
	{
		return ItemList;
	}

	FORCEINLINE FGameplayTag GetItem ( const int32 ArrayIndex ) const
	{
		const int32 ID = GetID ( ArrayIndex );

		return ID != INDEX_NONE
		       ? ItemList [ ID ]
		       : FGameplayTag::EmptyTag;
	}

	FORCEINLINE int32 GetItemCount ( const FGameplayTag& Item ) const
	{
		if ( const int32 ID = ItemList.IndexOfByKey ( Item ) ; ID >= 0 )
		{
			return GetIDCount ( ID );
		}

		return INDEX_NONE;
	}

	FORCEINLINE bool ContainItem ( const FGameplayTag& Item ) const
	{
		return ItemList.Contains ( Item );
	}
};

UENUM ( BlueprintType )
enum class ELFPPrimitiveDataType : uint8
{
	LFP_None UMETA ( DisplayName = "None" ) ,
	LFP_Int UMETA ( DisplayName = "Int" ) ,
	LFP_Float UMETA ( DisplayName = "Float" ) ,
	LFP_Double UMETA ( DisplayName = "Double" ) ,
	LFP_Boolean UMETA ( DisplayName = "Boolean" ) ,
	LFP_String UMETA ( DisplayName = "String" ) ,
	LFP_List UMETA ( DisplayName = "List" ) ,
	LFP_Struct UMETA ( DisplayName = "Struct" ) ,
};

USTRUCT ( BlueprintType )
struct LOHFUNCTIONPLUGIN_API FLFPPrimitiveData
{
	GENERATED_BODY ( )

public:

	FLFPPrimitiveData ( ) = default;

	FLFPPrimitiveData ( const int32 NewData )
	{
		Type = ELFPPrimitiveDataType::LFP_Int;

		DataList.SetNum ( 4 );

		*( reinterpret_cast < int32* > ( DataList.GetData ( ) ) ) = NewData;
	}

	FLFPPrimitiveData ( const float NewData )
	{
		Type = ELFPPrimitiveDataType::LFP_Float;

		DataList.SetNum ( 4 );

		*( reinterpret_cast < float* > ( DataList.GetData ( ) ) ) = NewData;
	}

	FLFPPrimitiveData ( const double NewData )
	{
		Type = ELFPPrimitiveDataType::LFP_Double;

		DataList.SetNum ( 8 );

		*( reinterpret_cast < double* > ( DataList.GetData ( ) ) ) = NewData;
	}

	FLFPPrimitiveData ( const bool NewData )
	{
		Type = ELFPPrimitiveDataType::LFP_Boolean;

		DataList.SetNum ( 1 );

		*( reinterpret_cast < bool* > ( DataList.GetData ( ) ) ) = NewData;
	}

	FLFPPrimitiveData ( const FString& NewData )
	{
		Type = ELFPPrimitiveDataType::LFP_String;

		DataList.SetNum ( NewData.Len ( ) );

		StringToBytes ( NewData , DataList.GetData ( ) , DataList.Num ( ) );
	}

	FLFPPrimitiveData ( const TArray < uint8 >& NewData )
	{
		Type = ELFPPrimitiveDataType::LFP_List;

		DataList = NewData;
	}

	template < typename T >
	FLFPPrimitiveData ( T NewData )
	{
		Type = ELFPPrimitiveDataType::LFP_Struct;

		FMemoryWriter Writer ( DataList , true );
		Writer << NewData;
	}

private:

	UPROPERTY ( )
	ELFPPrimitiveDataType Type = ELFPPrimitiveDataType::LFP_None;

	UPROPERTY ( )
	TArray < uint8 > DataList = TArray < uint8 > ( );

public:

	FORCEINLINE FString ToString ( ) const
	{
		if ( Type == ELFPPrimitiveDataType::LFP_None )
		{
			return FString ( );
		}

		switch ( Type )
		{
			case ELFPPrimitiveDataType::LFP_Int : return FString::FromInt ( AsInt ( ) );
			case ELFPPrimitiveDataType::LFP_Float : return FString::SanitizeFloat ( AsFloat ( ) );
			case ELFPPrimitiveDataType::LFP_Double : return FString::SanitizeFloat ( AsDouble ( ) );
			case ELFPPrimitiveDataType::LFP_Boolean : return AsBoolean ( )
			                                                 ? "True"
			                                                 : "False";
			case ELFPPrimitiveDataType::LFP_String : return AsString ( );
			default : ;
		}

		return FString ( );
	}

	FORCEINLINE void ClearData ( )
	{
		Type = ELFPPrimitiveDataType::LFP_None;

		DataList.Empty ( );
	}

	FORCEINLINE bool ContainData ( ) const
	{
		return Type != ELFPPrimitiveDataType::LFP_None;
	}

	FORCEINLINE ELFPPrimitiveDataType GetDataType ( ) const
	{
		return Type;
	}

	FORCEINLINE const TArray < uint8 >& GetData ( ) const
	{
		return DataList;
	}

	FORCEINLINE int32 AsInt ( ) const
	{
		if ( Type != ELFPPrimitiveDataType::LFP_Int )
		{
			return INDEX_NONE;
		}

		return *( reinterpret_cast < const int32* > ( DataList.GetData ( ) ) );
	}

	FORCEINLINE float AsFloat ( ) const
	{
		if ( Type != ELFPPrimitiveDataType::LFP_Float )
		{
			return 0.0f;
		}

		return *( reinterpret_cast < const float* > ( DataList.GetData ( ) ) );
	}

	FORCEINLINE double AsDouble ( ) const
	{
		if ( Type != ELFPPrimitiveDataType::LFP_Double )
		{
			return 0.0;
		}

		return *( reinterpret_cast < const double* > ( DataList.GetData ( ) ) );
	}

	FORCEINLINE double AsNum ( ) const
	{
		switch ( Type )
		{
			case ELFPPrimitiveDataType::LFP_Int : return AsInt ( );
			case ELFPPrimitiveDataType::LFP_Float : return AsFloat ( );
			case ELFPPrimitiveDataType::LFP_Double : return AsDouble ( );
			default : return 0.0;
		}
	}

	FORCEINLINE bool AsBoolean ( ) const
	{
		if ( Type != ELFPPrimitiveDataType::LFP_Boolean )
		{
			return false;
		}

		return *( reinterpret_cast < const bool* > ( DataList.GetData ( ) ) );
	}

	FORCEINLINE FString AsString ( ) const
	{
		if ( Type != ELFPPrimitiveDataType::LFP_String )
		{
			return "";
		}

		return BytesToString ( DataList.GetData ( ) , DataList.Num ( ) );
	}

	FORCEINLINE const TArray < uint8 >& AsList ( ) const
	{
		return DataList;
	}

	template < typename T >
	FORCEINLINE T AsStruct ( ) const
	{
		if ( Type != ELFPPrimitiveDataType::LFP_Struct )
		{
			return T ( );
		}

		T             ResultStruct;
		FMemoryReader Reader ( DataList , true );
		Reader << ResultStruct;
		return ResultStruct;
	}

	FORCEINLINE bool operator== ( const FLFPPrimitiveData& other ) const
	{
		return Type == other.Type && DataList == other.DataList;
	}
};

USTRUCT ( BlueprintType )
struct LOHFUNCTIONPLUGIN_API FLFPPrimitiveDataTagArray
{
	GENERATED_BODY ( )

private:

	UPROPERTY ( )
	TArray < FLFPPrimitiveData > ItemList = { };

	UPROPERTY ( )
	TArray < FGameplayTag > MappingList = { };

public:

	FORCEINLINE FString ToString ( ) const
	{
		FString ReturnString = "";

		for ( int32 Index = 0 ; Index < MappingList.Num ( ) ; Index++ )
		{
			const FLFPPrimitiveData& ItemData = ItemList [ Index ];
			const FGameplayTag&      ItemTag  = MappingList [ Index ];

			ReturnString += "[ " + ItemTag.ToString ( ) + " : ";
			ReturnString += ItemData.ToString ( ) + " ]";
		}

		return ReturnString;
	}

	/** Read / Write Function */

	FORCEINLINE void AddItem ( const FGameplayTag& ItemTag , const FLFPPrimitiveData& NewItem )
	{
		const int32 ItemIndex = MappingList.IndexOfByKey ( ItemTag );

		if ( ItemIndex != INDEX_NONE )
		{
			ItemList [ ItemIndex ] = NewItem;
		}
		else if ( NewItem.ContainData ( ) )
		{
			ItemList.Add ( NewItem );
			MappingList.Add ( ItemTag );
		}
	}

	FORCEINLINE void RemoveItem ( const FGameplayTag& ItemTag )
	{
		if ( const int32 ItemIndex = MappingList.IndexOfByKey ( ItemTag ) ; ItemIndex != INDEX_NONE )
		{
			ItemList.RemoveAtSwap ( ItemIndex );
			MappingList.RemoveAtSwap ( ItemIndex );
		}
	}

	FORCEINLINE const TArray < FLFPPrimitiveData >& GetItemList ( ) const
	{
		return ItemList;
	}

	FORCEINLINE const TArray < FGameplayTag >& GetMappingList ( ) const
	{
		return MappingList;
	}

	FORCEINLINE const FLFPPrimitiveData* GetItemConst ( const FGameplayTag& ItemTag ) const
	{
		const int32 ItemIndex = MappingList.IndexOfByKey ( ItemTag );

		if ( ItemIndex != INDEX_NONE )
		{
			return &ItemList [ ItemIndex ];
		}

		return nullptr;
	}

	FORCEINLINE FLFPPrimitiveData* GetItem ( const FGameplayTag& ItemTag )
	{
		const int32 ItemIndex = MappingList.IndexOfByKey ( ItemTag );

		if ( ItemIndex != INDEX_NONE )
		{
			return &ItemList [ ItemIndex ];
		}

		return nullptr;
	}

	FORCEINLINE FLFPPrimitiveData& GetOrAddItem ( const FGameplayTag& ItemTag )
	{
		const int32 ItemIndex = MappingList.IndexOfByKey ( ItemTag );

		if ( ItemIndex != INDEX_NONE )
		{
			return ItemList [ ItemIndex ];
		}

		MappingList.Add ( ItemTag );

		return ItemList.AddDefaulted_GetRef ( );
	}

	FORCEINLINE void CleanEmptyItem ( )
	{
		for ( int32 Index = MappingList.Num ( ) - 1 ; Index >= 0 ; Index-- )
		{
			if ( const FLFPPrimitiveData& ItemData = ItemList [ Index ] ; ItemData.ContainData ( ) == false )
			{
				ItemList.RemoveAtSwap ( Index , EAllowShrinking::No );
				MappingList.RemoveAtSwap ( Index , EAllowShrinking::No );
			}
		}

		ItemList.Shrink ( );
		MappingList.Shrink ( );
	}

	FORCEINLINE void Empty ( )
	{
		ItemList.Empty ( );
		MappingList.Empty ( );
	}

	FORCEINLINE bool Contain ( const FGameplayTag& ItemTag ) const
	{
		return MappingList.Contains ( ItemTag );
	}

public:

	FORCEINLINE bool operator== ( const FLFPPrimitiveDataTagArray& other ) const
	{
		return ItemList == other.ItemList && MappingList == other.MappingList;
	}
};

UCLASS ( )
class LOHFUNCTIONPLUGIN_API ULFPDynamicTypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY ( )

public:

	UFUNCTION ( BlueprintCallable , Category = "LohFunctionPluginLibrary | LFPIDTrackerStaticArray" )
	static void InitializeTrackerArray ( UPARAM ( ref )
	                                     FLFPIndexTrackerStaticArray& List , const int32 IndexSize );

	UFUNCTION ( BlueprintCallable , Category = "LohFunctionPluginLibrary | LFPIDTrackerStaticArray" )
	static int32 GetNewID ( UPARAM ( ref )
		FLFPIndexTrackerStaticArray& List );

	UFUNCTION ( BlueprintCallable , Category = "LohFunctionPluginLibrary | LFPIDTrackerStaticArray" )
	static bool SetID ( UPARAM ( ref )
	                    FLFPIndexTrackerStaticArray& List , const int32 Index , const int32 ID );

	UFUNCTION ( BlueprintPure , Category = "LohFunctionPluginLibrary | LFPIDTrackerStaticArray" )
	static int32 GetID ( const FLFPIndexTrackerStaticArray& List , const int32 Index );

	UFUNCTION ( BlueprintCallable , Category = "LohFunctionPluginLibrary | LFPPrimitiveData" )
	static int32 GetDataAsInt ( UPARAM ( ref )
		FLFPPrimitiveData& Data );

	UFUNCTION ( BlueprintCallable , Category = "LohFunctionPluginLibrary | LFPPrimitiveData" )
	static void SetDataAsInt ( UPARAM ( ref )
	                           FLFPPrimitiveData& Data , const int32 Value );

	UFUNCTION ( BlueprintCallable , Category = "LohFunctionPluginLibrary | LFPPrimitiveData" )
	static float GetDataAsFloat ( UPARAM ( ref )
		FLFPPrimitiveData& Data );

	UFUNCTION ( BlueprintCallable , Category = "LohFunctionPluginLibrary | LFPPrimitiveData" )
	static void SetDataAsFloat ( UPARAM ( ref )
	                             FLFPPrimitiveData& Data , const float Value );

	UFUNCTION ( BlueprintCallable , Category = "LohFunctionPluginLibrary | LFPPrimitiveData" )
	static bool GetDataAsBool ( UPARAM ( ref )
		FLFPPrimitiveData& Data );

	UFUNCTION ( BlueprintCallable , Category = "LohFunctionPluginLibrary | LFPPrimitiveData" )
	static void SetDataAsBool ( UPARAM ( ref )
	                            FLFPPrimitiveData& Data , const bool Value );

	UFUNCTION ( BlueprintCallable , Category = "LohFunctionPluginLibrary | LFPPrimitiveData" )
	static FString GetDataAsString ( UPARAM ( ref )
		FLFPPrimitiveData& Data );

	UFUNCTION ( BlueprintCallable , Category = "LohFunctionPluginLibrary | LFPPrimitiveData" )
	static void SeDataAsString ( UPARAM ( ref )
	                             FLFPPrimitiveData& Data , const FString Value );

	UFUNCTION ( BlueprintCallable , Category = "LohFunctionPluginLibrary | LFPPrimitiveData" )
	static TArray < uint8 > GetDataAsList ( UPARAM ( ref )
		FLFPPrimitiveData& Data );

	UFUNCTION ( BlueprintCallable , Category = "LohFunctionPluginLibrary | LFPPrimitiveData" )
	static void ClearData ( UPARAM ( ref )
		FLFPPrimitiveData& Data );

	UFUNCTION ( BlueprintCallable , Category = "LohFunctionPluginLibrary | LFPPrimitiveData" )
	static FString ToString ( UPARAM ( ref )
		FLFPPrimitiveData& Data );
};
