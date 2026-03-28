#include "Library/LFPDynamicTypeLibrary.h"

DEFINE_LOG_CATEGORY ( LFPDynamicIntStaticArray );

void ULFPDynamicTypeLibrary::InitializeTrackerArray ( UPARAM ( ref )
                                                      FLFPIndexTrackerStaticArray& List , const int32 IndexSize )
{
	List = FLFPIndexTrackerStaticArray ( IndexSize );
}

int32 ULFPDynamicTypeLibrary::GetNewID ( UPARAM ( ref )
	FLFPIndexTrackerStaticArray& List )
{
	return List.GetNewID ( );
}

bool ULFPDynamicTypeLibrary::SetID ( UPARAM ( ref )
                                     FLFPIndexTrackerStaticArray& List , const int32 Index , const int32 ID )
{
	if ( List.IsValidIndex ( Index ) == false || ID < INDEX_NONE )
	{
		return false;
	}

	List.SetID ( Index , ID );

	return true;
}

int32 ULFPDynamicTypeLibrary::GetID ( const FLFPIndexTrackerStaticArray& List , const int32 Index )
{
	if ( List.IsValidIndex ( Index ) == false )
	{
		return false;
	}

	return List.GetID ( Index );
}

void ULFPDynamicTypeLibrary::AddInstancedStructTag ( UPARAM ( ref ) FLFPInstancedStructTagArray& InData , const FInstancedStruct& NewData , const FGameplayTag& StructTag )
{
	InData.AddItem ( StructTag , NewData );
}

void ULFPDynamicTypeLibrary::RemoveInstancedStructTag ( FLFPInstancedStructTagArray& InData , const FGameplayTag& StructTag )
{
	InData.RemoveItem ( StructTag );
}

FInstancedStruct ULFPDynamicTypeLibrary::GetInstancedStructTag ( FLFPInstancedStructTagArray& InData , const FGameplayTag& StructTag )
{
	const FInstancedStruct* ItemPtr = InData.GetItemConst ( StructTag );
	
	return ItemPtr != nullptr ? *ItemPtr : FInstancedStruct ( );
}

//int32 ULFPDynamicTypeLibrary::GetDataAsInt ( UPARAM ( ref )
//	FLFPPrimitiveData& Data )
//{
//	return Data.AsInt ( );
//}
//
//void ULFPDynamicTypeLibrary::SetDataAsInt ( UPARAM ( ref )
//                                            FLFPPrimitiveData& Data , const int32 Value )
//{
//	Data = Value;
//}
//
//float ULFPDynamicTypeLibrary::GetDataAsFloat ( UPARAM ( ref )
//	FLFPPrimitiveData& Data )
//{
//	return Data.AsFloat ( );
//}
//
//void ULFPDynamicTypeLibrary::SetDataAsFloat ( UPARAM ( ref )
//                                              FLFPPrimitiveData& Data , const float Value )
//{
//	Data = Value;
//}
//
//bool ULFPDynamicTypeLibrary::GetDataAsBool ( UPARAM ( ref )
//	FLFPPrimitiveData& Data )
//{
//	return Data.AsBoolean ( );
//}
//
//void ULFPDynamicTypeLibrary::SetDataAsBool ( UPARAM ( ref )
//                                             FLFPPrimitiveData& Data , const bool Value )
//{
//	Data = Value;
//}
//
//FString ULFPDynamicTypeLibrary::GetDataAsString ( UPARAM ( ref )
//	FLFPPrimitiveData& Data )
//{
//	return Data.AsString ( );
//}
//
//void ULFPDynamicTypeLibrary::SeDataAsString ( UPARAM ( ref )
//                                              FLFPPrimitiveData& Data , const FString Value )
//{
//	Data = Value;
//}
//
//TArray < uint8 > ULFPDynamicTypeLibrary::GetDataAsList ( FLFPPrimitiveData& Data )
//{
//	return Data.AsList ( );
//}
//
//void ULFPDynamicTypeLibrary::ClearData ( UPARAM ( ref )
//	FLFPPrimitiveData& Data )
//{
//	Data.ClearData ( );
//}
//
//FString ULFPDynamicTypeLibrary::ToString ( UPARAM ( ref )
//	FLFPPrimitiveData& Data )
//{
//	return Data.ToString ( );
//}
