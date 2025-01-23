// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#include "LohFunctionPluginLibrary.h"

FString ULohFunctionPluginLibrary::BufferToString( const TArray<uint8>& Buffer )
{
	FMemoryReader StringRead( Buffer );

	FString OutString;

	StringRead << OutString;

	return OutString;
}

TArray<uint8> ULohFunctionPluginLibrary::StringToBuffer( FString FromString )
{
	TArray<uint8> OutArray;

	FMemoryWriter StringWriter( OutArray , false );

	StringWriter << FromString;

	return OutArray;
}

bool ULohFunctionPluginLibrary::ContainPoint( const FLFPIntPointList& List , const int32 Index )
{
	return List.ContainIndex( Index );
}

void ULohFunctionPluginLibrary::AddPoint( UPARAM( ref )FLFPIntPointList& List , const FIntPoint Range )
{
	List.Add( Range );
}

void ULohFunctionPluginLibrary::RemovePoint( UPARAM( ref )FLFPIntPointList& List , const FIntPoint Range )
{
	List.Remove( Range );
}

FGameplayTag ULohFunctionPluginLibrary::GetGameplayTagFromName( const FName TagName )
{
	return FGameplayTag::RequestGameplayTag( TagName , false );
}

