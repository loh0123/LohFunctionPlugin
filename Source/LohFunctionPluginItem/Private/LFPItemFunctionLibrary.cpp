// Copyright (c) 2023-2024 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#include "LFPItemFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"

FLFPInventoryItem FLFPInventoryItem::EmptyItem = FLFPInventoryItem();

const TArray<uint8>& ULFPItemFunctionLibrary::GetMetaData( const FLFPInventoryItem& Item )
{
	return Item.GetMetaData();
}

void ULFPItemFunctionLibrary::SetMetaData( UPARAM( ref ) FLFPInventoryItem& Item , const TArray<uint8>& Data )
{
	Item.SetMetaData( Data );
}

void ULFPItemFunctionLibrary::SetItemTag( UPARAM( ref )FLFPInventoryItem& Item , const FGameplayTag ItemTag )
{
	Item.SetItemTag( ItemTag );
}
