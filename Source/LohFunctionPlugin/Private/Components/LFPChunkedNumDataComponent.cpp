// Copyright (c) 2023-2025 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#include "Components/LFPChunkedNumDataComponent.h"

#include "Serialization/ArchiveLoadCompressedProxy.h"
#include "Serialization/ArchiveSaveCompressedProxy.h"

DEFINE_LOG_CATEGORY ( LogChunkedNumDataComponent );

// Sets default values for this component's properties
ULFPChunkedNumDataComponent::ULFPChunkedNumDataComponent ( )
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void ULFPChunkedNumDataComponent::BeginPlay ( )
{
	Super::BeginPlay ( );

	RegionDataList.SetNum ( RegionIndexSize );
}

// Called every frame
void ULFPChunkedNumDataComponent::TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent ( DeltaTime , TickType , ThisTickFunction );

	// ...
}

////////////////////////////

void ULFPChunkedNumDataComponent::LoadRegion ( const int32 RegionIndex , const FLFPChunkedNumSerializeData& LoadData )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedNumDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	// Clear region
	RegionDataList [ RegionIndex ] = FLFPNumRegionData ( );

	FArchiveLoadCompressedProxy Proxy ( LoadData.DataList , LoadData.CompressionName , ECompressionFlags::COMPRESS_BiasMemory );

	FLFPNumRegionData& RegionData = RegionDataList [ RegionIndex ];

	RegionData.StaticStruct ( )->SerializeItem ( Proxy , &RegionData , nullptr );
}

void ULFPChunkedNumDataComponent::SaveRegion ( const int32 RegionIndex , FLFPChunkedNumSerializeData& SaveData )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedNumDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	FArchiveSaveCompressedProxy Proxy ( SaveData.DataList , SaveData.CompressionName , ECompressionFlags::COMPRESS_BiasMemory );

	FLFPNumRegionData& RegionData = RegionDataList [ RegionIndex ];

	RegionData.StaticStruct ( )->SerializeItem ( Proxy , &RegionData , nullptr );
}

////////////////////////////

void ULFPChunkedNumDataComponent::InitializeChunk ( const int32 RegionIndex , const int32 ChunkIndex , const int32 FillID )
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedNumDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	if ( IsChunkInitialized ( RegionIndex , ChunkIndex ) )
	{
		UE_LOG ( LogChunkedNumDataComponent , Log , TEXT("%hs : Chunk ( %i ) on Region ( %i ) already initialized") , __FUNCTION__ , ChunkIndex , RegionIndex );

		return;
	}

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).InitializeChunkData ( DataIndexSize , FillID );
}

void ULFPChunkedNumDataComponent::DeinitializeChunk ( const int32 RegionIndex , const int32 ChunkIndex )
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedNumDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).DeinitializeChunkData ( );
}

void ULFPChunkedNumDataComponent::InitializeRegion ( const int32 RegionIndex )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedNumDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	if ( IsRegionInitialized ( RegionIndex ) )
	{
		UE_LOG ( LogChunkedNumDataComponent , Log , TEXT("%hs : Region ( %i ) already initialized") , __FUNCTION__ , RegionIndex );

		return;
	}

	RegionDataList [ RegionIndex ].InitializeRegionData ( ChunkIndexSize );
}

void ULFPChunkedNumDataComponent::DeinitializeRegion ( const int32 RegionIndex )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedNumDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	RegionDataList [ RegionIndex ].DeinitializeRegionData ( );
}

////////////////////////////

int32 ULFPChunkedNumDataComponent::GetDataID_Checked ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetDataID ( DataIndex );
}

int32 ULFPChunkedNumDataComponent::GetDataMeta_MappingNum ( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetDataMetaNum ( );
}

const FLFPNumMetaData* ULFPChunkedNumDataComponent::GetDataMetaList_Direct ( const int32 RegionIndex , const int32 ChunkIndex , const int32 MappingIndex ) const
{
	check ( IsChunkIndexValid(RegionIndex, ChunkIndex) );

	return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetDataMetaList_Direct ( MappingIndex );
}

void ULFPChunkedNumDataComponent::SetDataMeta_Direct ( const int32 RegionIndex , const int32 ChunkIndex , const int32 MappingIndex , const FGameplayTag& DataMetaTag , const FInstancedStruct& NewDataMeta )
{
	check ( IsChunkIndexValid(RegionIndex, ChunkIndex) );

	FLFPNumMetaData* DataMetaPtr = RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetDataMetaList_Direct_Mutable ( MappingIndex );

	check ( DataMetaPtr != nullptr );

	const FInstancedStruct* OldMetaPtr = DataMetaPtr->GetMetaData ( DataMetaTag );

	const FInstancedStruct OldMeta = OldMetaPtr != nullptr
	                                 ? *OldMetaPtr
	                                 : FInstancedStruct ( );

	DataMetaPtr->GetOrAddMetaData ( DataMetaTag ) = NewDataMeta;

	OnMetaChanged.Broadcast ( RegionIndex , ChunkIndex , DataMetaPtr->GetDataIndex ( ) , DataMetaTag , OldMeta , NewDataMeta );
}

TArray < int32 > ULFPChunkedNumDataComponent::GetDataIDList ( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedNumDataComponent , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex );

		return TArray < int32 > ( );
	}

	return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetDataIDList ( );
}

////////////////////////////

int32 ULFPChunkedNumDataComponent::GetDataID ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedNumDataComponent , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return INDEX_NONE;
	}

	return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetDataID ( DataIndex );
}

void ULFPChunkedNumDataComponent::SetDataID ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const int32 NewDataID )
{
	if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedNumDataComponent , Warning , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return;
	}

	if ( NewDataID == RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetDataID ( DataIndex ) )
	{
		return;
	}

	const int32 OldID = RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetDataID ( DataIndex );

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).SetDataID ( DataIndex , NewDataID );

	OnIDChanged.Broadcast ( RegionIndex , ChunkIndex , DataIndex , OldID , NewDataID );
}

FInstancedStruct ULFPChunkedNumDataComponent::GetDataMeta ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FGameplayTag& DataMetaTag ) const
{
	if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedNumDataComponent , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return FInstancedStruct ( );
	}

	if ( const FInstancedStruct* MetaData = RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetDataMeta ( DataIndex , DataMetaTag ) ; MetaData != nullptr )
	{
		return *MetaData;
	}

	return FInstancedStruct ( );
}

void ULFPChunkedNumDataComponent::SetDataMeta ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FGameplayTag& DataMetaTag , const FInstancedStruct& NewDataMeta )
{
	if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedNumDataComponent , Warning , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return;
	}

	const FInstancedStruct* OldMetaPtr = RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetDataMeta ( DataIndex , DataMetaTag );

	const FInstancedStruct OldMeta = OldMetaPtr != nullptr
	                                 ? *OldMetaPtr
	                                 : FInstancedStruct ( );

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetOrAddDataMeta ( DataIndex , DataMetaTag ) = NewDataMeta;

	OnMetaChanged.Broadcast ( RegionIndex , ChunkIndex , DataIndex , DataMetaTag , OldMeta , NewDataMeta );
}

////////////////////////////

int32 ULFPChunkedNumDataComponent::GetChunkID ( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedNumDataComponent , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex );

		return INDEX_NONE;
	}

	return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetChunkID ( );
}

void ULFPChunkedNumDataComponent::SetChunkID ( const int32 RegionIndex , const int32 ChunkIndex , const int32 NewChunkID )
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedNumDataComponent , Warning , TEXT("%hs : Invalid Index ( R : %i , C : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex );

		return;
	}

	if ( NewChunkID == RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetChunkID ( ) )
	{
		return;
	}

	const int32 OldID = RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetChunkID ( );

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).SetChunkID ( NewChunkID );

	OnIDChanged.Broadcast ( RegionIndex , ChunkIndex , INDEX_NONE , OldID , NewChunkID );
}

FInstancedStruct ULFPChunkedNumDataComponent::GetChunkMeta ( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& ChunkMetaTag ) const
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedNumDataComponent , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex );

		return FInstancedStruct ( );
	}

	if ( const FInstancedStruct* MetaData = RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetChunkMeta ( ChunkMetaTag ) ; MetaData != nullptr )
	{
		return *MetaData;
	}

	return FInstancedStruct ( );
}

void ULFPChunkedNumDataComponent::SetChunkMeta ( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& ChunkMetaTag , const FInstancedStruct& NewChunkMeta )
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedNumDataComponent , Warning , TEXT("%hs : Invalid Index ( R : %i , C : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex );

		return;
	}

	const FInstancedStruct* OldMetaPtr = RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetChunkMeta ( ChunkMetaTag );

	const FInstancedStruct OldMeta = OldMetaPtr != nullptr
	                                 ? *OldMetaPtr
	                                 : FInstancedStruct ( );

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetOrAddChunkMeta ( ChunkMetaTag ) = NewChunkMeta;

	OnMetaChanged.Broadcast ( RegionIndex , ChunkIndex , INDEX_NONE , ChunkMetaTag , OldMeta , NewChunkMeta );
}

////////////////////////////

int32 ULFPChunkedNumDataComponent::GetRegionID ( const int32 RegionIndex ) const
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedNumDataComponent , Verbose , TEXT("%hs : Invalid Index ( R : %i )") , __FUNCTION__ , RegionIndex );

		return INDEX_NONE;
	}

	return RegionDataList [ RegionIndex ].GetRegionID ( );
}

void ULFPChunkedNumDataComponent::SetRegionID ( const int32 RegionIndex , const int32 NewRegionID )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedNumDataComponent , Warning , TEXT("%hs : Invalid Index ( R : %i )") , __FUNCTION__ , RegionIndex );

		return;
	}

	if ( NewRegionID == RegionDataList [ RegionIndex ].GetRegionID ( ) )
	{
		return;
	}

	const int32 OldID = RegionDataList [ RegionIndex ].GetRegionID ( );

	RegionDataList [ RegionIndex ].SetRegionID ( NewRegionID );

	OnIDChanged.Broadcast ( RegionIndex , INDEX_NONE , INDEX_NONE , OldID , NewRegionID );
}

FInstancedStruct ULFPChunkedNumDataComponent::GetRegionMeta ( const int32 RegionIndex , const FGameplayTag& RegionMetaTag ) const
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedNumDataComponent , Verbose , TEXT("%hs : Invalid Index ( R : %i )") , __FUNCTION__ , RegionIndex );

		return FInstancedStruct ( );
	}

	if ( const FInstancedStruct* MetaData = RegionDataList [ RegionIndex ].GetRegionMeta ( RegionMetaTag ) ; MetaData != nullptr )
	{
		return *MetaData;
	}

	return FInstancedStruct ( );
}

void ULFPChunkedNumDataComponent::SetRegionMeta ( const int32 RegionIndex , const FGameplayTag& RegionMetaTag , const FInstancedStruct& NewRegionMeta )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedNumDataComponent , Warning , TEXT("%hs : Invalid Index ( R : %i )") , __FUNCTION__ , RegionIndex );

		return;
	}

	const FInstancedStruct* OldMetaPtr = RegionDataList [ RegionIndex ].GetRegionMeta ( RegionMetaTag );

	const FInstancedStruct OldMeta = OldMetaPtr != nullptr
	                                 ? *OldMetaPtr
	                                 : FInstancedStruct ( );

	RegionDataList [ RegionIndex ].GetOrAddRegionMeta ( RegionMetaTag ) = NewRegionMeta;

	OnMetaChanged.Broadcast ( RegionIndex , INDEX_NONE , INDEX_NONE , RegionMetaTag , OldMeta , NewRegionMeta );
}

////////////////////////////

bool ULFPChunkedNumDataComponent::IsDataIndexValid ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	return RegionDataList.IsValidIndex ( RegionIndex ) && RegionDataList [ RegionIndex ].IsChunkIndexValid ( ChunkIndex ) && RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).IsDataIndexValid ( DataIndex );
}

bool ULFPChunkedNumDataComponent::IsChunkIndexValid ( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return RegionDataList.IsValidIndex ( RegionIndex ) && RegionDataList [ RegionIndex ].IsChunkIndexValid ( ChunkIndex );
}

bool ULFPChunkedNumDataComponent::IsRegionIndexValid ( const int32 RegionIndex ) const
{
	return RegionDataList.IsValidIndex ( RegionIndex );
}

bool ULFPChunkedNumDataComponent::IsChunkInitialized ( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return IsChunkIndexValid ( RegionIndex , ChunkIndex ) && RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).IsInitialized ( );
}

bool ULFPChunkedNumDataComponent::IsRegionInitialized ( const int32 RegionIndex ) const
{
	return IsRegionIndexValid ( RegionIndex ) && RegionDataList [ RegionIndex ].IsInitialized ( );
}

int32 ULFPChunkedNumDataComponent::GetDataIndexSize ( ) const
{
	return DataIndexSize;
}

int32 ULFPChunkedNumDataComponent::GetChunkIndexSize ( ) const
{
	return ChunkIndexSize;
}

int32 ULFPChunkedNumDataComponent::GetRegionIndexSize ( ) const
{
	return RegionIndexSize;
}
