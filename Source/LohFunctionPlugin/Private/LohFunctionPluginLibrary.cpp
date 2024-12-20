// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#include "LohFunctionPluginLibrary.h"
#include "LohFunctionPlugin.h"
#include "Misc/OutputDeviceNull.h"

DEFINE_LOG_CATEGORY( LFPCompactIntArray );
DEFINE_LOG_CATEGORY( LFPCompactIDArray );
DEFINE_LOG_CATEGORY( LFPCompactTagArray );
DEFINE_LOG_CATEGORY( LFPCompactMetaArray );

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

void ULohFunctionPluginLibrary::InitializeIDArray( UPARAM( ref )FLFPCompactIDArray& List , const int32 IndexSize )
{
	List = FLFPCompactIDArray( IndexSize );
}

int32 ULohFunctionPluginLibrary::AssignID( UPARAM( ref )FLFPCompactIDArray& List , const TArray<int32>& NewIndexList )
{
	return List.AssignID( NewIndexList );
}

bool ULohFunctionPluginLibrary::SetID( UPARAM( ref )FLFPCompactIDArray& List , const int32 Index , const int32 ID )
{
	return List.SetID( Index , ID );
}

bool ULohFunctionPluginLibrary::RemoveID( UPARAM( ref )FLFPCompactIDArray& List , const int32 Index )
{
	return List.RemoveID( Index );
}

int32 ULohFunctionPluginLibrary::GetID( UPARAM( ref )FLFPCompactIDArray& List , const int32 Index )
{
	return List.GetID( Index );
}

int32 ULohFunctionPluginLibrary::GetMetaDataAsInt( UPARAM( ref )FLFPCompactMetaData& MetaData )
{
	return MetaData.GetDataAsInt();
}

void ULohFunctionPluginLibrary::SetMetaDataAsInt( UPARAM( ref )FLFPCompactMetaData& MetaData , const int32 Value )
{
	MetaData.SetDataAsInt( Value );
}

float ULohFunctionPluginLibrary::GetMetaDataAsFloat( UPARAM( ref )FLFPCompactMetaData& MetaData )
{
	return MetaData.GetDataAsFloat();
}

void ULohFunctionPluginLibrary::SetMetaDataAsFloat( UPARAM( ref )FLFPCompactMetaData& MetaData , const float Value )
{
	MetaData.SetDataAsFloat( Value );
}

bool ULohFunctionPluginLibrary::GetMetaDataAsBool( UPARAM( ref )FLFPCompactMetaData& MetaData )
{
	return MetaData.GetDataAsBool();
}

void ULohFunctionPluginLibrary::SetMetaDataAsBool( UPARAM( ref )FLFPCompactMetaData& MetaData , const bool Value )
{
	MetaData.SetDataAsBool( Value );
}

FString ULohFunctionPluginLibrary::GetMetaDataAsString( UPARAM( ref )FLFPCompactMetaData& MetaData )
{
	return MetaData.GetDataAsString();
}

void ULohFunctionPluginLibrary::SetMetaDataAsString( UPARAM( ref )FLFPCompactMetaData& MetaData , const FString Value )
{
	MetaData.SetDataAsString( Value );
}

