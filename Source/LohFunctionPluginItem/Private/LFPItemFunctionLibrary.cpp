// Copyright (c) 2023-2024 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#include "LFPItemFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"

FLFPInventoryItem FLFPInventoryItem::EmptyItem = FLFPInventoryItem ( );

bool ULFPItemFunctionLibrary::IsMetaDataSame ( const FLFPInventoryItem& ItemA , const FLFPInventoryItem& ItemB , const FGameplayTag MetaTag )
{
	auto MetaDataA = ItemA.GetMetaData ( MetaTag );
	auto MetaDataB = ItemB.GetMetaData ( MetaTag );

	return ( MetaDataA == nullptr
		         ? FLFPPrimitiveData ( )
		         : *MetaDataA ) == ( MetaDataB == nullptr
			                             ? FLFPPrimitiveData ( )
			                             : *MetaDataB );
}

bool ULFPItemFunctionLibrary::ContainMetaData ( const FLFPInventoryItem& Item , const FGameplayTag MetaTag )
{
	return Item.ContainMetaData ( MetaTag );
}

bool ULFPItemFunctionLibrary::CheckMetaDataCost ( const FLFPInventoryItem& Item , const TMap <FGameplayTag , int32>& IntCostDataMap , const TMap <FGameplayTag , float>& FloatCostDataMap )
{
	for ( const auto& CostData : IntCostDataMap )
	{
		const auto MetaData = Item.GetMetaData ( CostData.Key );

		if ( MetaData == nullptr )
		{
			return false;
		}

		if ( MetaData->GetDataType ( ) != ELFPPrimitiveDataType::LFP_Int )
		{
			return false;
		}

		if ( MetaData->AsInt ( ) < CostData.Value )
		{
			return false;
		}
	}

	for ( const auto& CostData : FloatCostDataMap )
	{
		const auto MetaData = Item.GetMetaData ( CostData.Key );

		if ( MetaData == nullptr )
		{
			return false;
		}

		if ( MetaData->GetDataType ( ) != ELFPPrimitiveDataType::LFP_Int )
		{
			return false;
		}

		if ( MetaData->AsFloat ( ) < CostData.Value )
		{
			return false;
		}
	}

	return true;
}

FLFPPrimitiveData ULFPItemFunctionLibrary::GetMetaData ( const FLFPInventoryItem& Item , const FGameplayTag MetaTag )
{
	auto MetaData = Item.GetMetaData ( MetaTag );

	return MetaData != nullptr
		       ? *MetaData
		       : FLFPPrimitiveData ( );
}

FGameplayTag ULFPItemFunctionLibrary::GetItemTag ( const FLFPInventoryItem& Item )
{
	return Item.GetItemTag ( );
}

void ULFPItemFunctionLibrary::SetMetaData ( UPARAM ( ref ) FLFPInventoryItem& Item , const FGameplayTag MetaTag , const FLFPPrimitiveData& MetaData )
{
	Item.SetMetaData ( MetaTag , MetaData );
}

void ULFPItemFunctionLibrary::SetItemTag ( UPARAM ( ref )FLFPInventoryItem& Item , const FGameplayTag ItemTag )
{
	Item.SetItemTag ( ItemTag );
}

void ULFPItemFunctionLibrary::ConsumeMetaDataCost ( UPARAM ( ref )FLFPInventoryItem& Item , const TMap <FGameplayTag , int32>& IntCostDataMap , const TMap <FGameplayTag , float>& FloatCostDataMap )
{
	for ( const auto& CostData : IntCostDataMap )
	{
		const auto MetaData = Item.GetMetaData ( CostData.Key );

		if ( MetaData == nullptr )
		{
			continue;
		}

		if ( MetaData->GetDataType ( ) != ELFPPrimitiveDataType::LFP_Int )
		{
			continue;
		}

		FLFPPrimitiveData NewMetaData = FLFPPrimitiveData ( );

		NewMetaData = MetaData->AsInt ( ) - CostData.Value;

		Item.SetMetaData ( CostData.Key , NewMetaData );
	}

	for ( const auto& CostData : FloatCostDataMap )
	{
		const auto MetaData = Item.GetMetaData ( CostData.Key );

		if ( MetaData == nullptr )
		{
			continue;
		}

		if ( MetaData->GetDataType ( ) != ELFPPrimitiveDataType::LFP_Float )
		{
			continue;
		}

		FLFPPrimitiveData NewMetaData = FLFPPrimitiveData ( );

		NewMetaData = MetaData->AsFloat ( ) - CostData.Value;

		Item.SetMetaData ( CostData.Key , NewMetaData );
	}
}

void FLFPInventoryItem::AppendMetaDataInt ( const TMap <FGameplayTag , int32>& DataMap , const bool bUniqueOnly )
{
	for ( const auto& RawMetaData : DataMap )
	{
		FLFPPrimitiveData NewMetaData = FLFPPrimitiveData ( );

		NewMetaData = RawMetaData.Value;

		SetMetaData ( RawMetaData.Key , NewMetaData , bUniqueOnly );
	}
}

void FLFPInventoryItem::AppendMetaDataFloat ( const TMap <FGameplayTag , float>& DataMap , const bool bUniqueOnly )
{
	for ( const auto& RawMetaData : DataMap )
	{
		FLFPPrimitiveData NewMetaData = FLFPPrimitiveData ( );

		NewMetaData = RawMetaData.Value;

		SetMetaData ( RawMetaData.Key , NewMetaData , bUniqueOnly );
	}
}

void FLFPInventoryItem::AppendMetaDataString ( const TMap <FGameplayTag , FString>& DataMap , const bool bUniqueOnly )
{
	for ( const auto& RawMetaData : DataMap )
	{
		FLFPPrimitiveData NewMetaData = FLFPPrimitiveData ( );

		NewMetaData = RawMetaData.Value;

		SetMetaData ( RawMetaData.Key , NewMetaData , bUniqueOnly );
	}
}

void FLFPInventoryItem::AppendMetaDataBoolean ( const TMap <FGameplayTag , bool>& DataMap , const bool bUniqueOnly )
{
	for ( const auto& RawMetaData : DataMap )
	{
		FLFPPrimitiveData NewMetaData = FLFPPrimitiveData ( );

		NewMetaData = RawMetaData.Value;

		SetMetaData ( RawMetaData.Key , NewMetaData , bUniqueOnly );
	}
}
