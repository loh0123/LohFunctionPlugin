// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LFPChunkedByteListDataComponent.h"

#include "Serialization/ArchiveLoadCompressedProxy.h"
#include "Serialization/ArchiveSaveCompressedProxy.h"

DEFINE_LOG_CATEGORY ( LogChunkedByteListDataComponent );


// Sets default values for this component's properties
ULFPChunkedByteListDataComponent::ULFPChunkedByteListDataComponent ( )
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULFPChunkedByteListDataComponent::BeginPlay ( )
{
	Super::BeginPlay ( );

	RegionDataList.SetNum ( RegionIndexSize );
}


// Called every frame
void ULFPChunkedByteListDataComponent::TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent ( DeltaTime , TickType , ThisTickFunction );

	// ...
}

void ULFPChunkedByteListDataComponent::SetSize ( const FIntVector& NewSize , const int32 NewByteSize )
{
	RegionIndexSize = NewSize.X;
	ChunkIndexSize  = NewSize.Y;
	DataIndexSize   = NewSize.Z;

	DataByteSize = NewByteSize;

	RegionDataList.Reset ( );
	RegionDataList.SetNum ( RegionIndexSize );
}

void ULFPChunkedByteListDataComponent::LoadRegion ( const int32 RegionIndex , const FLFPChunkedByteListSerializeData& LoadData )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedByteListDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	// Clear region
	RegionDataList [ RegionIndex ] = FLFPByteListRegionData ( );

	FArchiveLoadCompressedProxy Proxy ( LoadData.DataList , LoadData.CompressionName , ECompressionFlags::COMPRESS_BiasMemory );

	FLFPByteListRegionData& RegionData = RegionDataList [ RegionIndex ];

	RegionData.StaticStruct ( )->SerializeItem ( Proxy , &RegionData , nullptr );
}

void ULFPChunkedByteListDataComponent::SaveRegion ( const int32 RegionIndex , FLFPChunkedByteListSerializeData& SaveData )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedByteListDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	FArchiveSaveCompressedProxy Proxy ( SaveData.DataList , SaveData.CompressionName , ECompressionFlags::COMPRESS_BiasMemory );

	FLFPByteListRegionData& RegionData = RegionDataList [ RegionIndex ];

	RegionData.StaticStruct ( )->SerializeItem ( Proxy , &RegionData , nullptr );
}

void ULFPChunkedByteListDataComponent::InitializeChunk ( const int32 RegionIndex , const int32 ChunkIndex )
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedByteListDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	if ( IsChunkInitialized ( RegionIndex , ChunkIndex ) )
	{
		UE_LOG ( LogChunkedByteListDataComponent , Log , TEXT("%hs : Chunk ( %i ) on Region ( %i ) already initialized") , __FUNCTION__ , ChunkIndex , RegionIndex );

		return;
	}

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).InitializeChunkData ( DataIndexSize , DataByteSize );
}

void ULFPChunkedByteListDataComponent::DeinitializeChunk ( const int32 RegionIndex , const int32 ChunkIndex )
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedByteListDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).DeinitializeChunkData ( );
}

void ULFPChunkedByteListDataComponent::InitializeRegion ( const int32 RegionIndex )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedByteListDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	if ( IsRegionInitialized ( RegionIndex ) )
	{
		UE_LOG ( LogChunkedByteListDataComponent , Log , TEXT("%hs : Region ( %i ) already initialized") , __FUNCTION__ , RegionIndex );

		return;
	}

	RegionDataList [ RegionIndex ].InitializeRegionData ( ChunkIndexSize );
}

void ULFPChunkedByteListDataComponent::DeinitializeRegion ( const int32 RegionIndex )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedByteListDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	RegionDataList [ RegionIndex ].DeinitializeRegionData ( );
}

TArray < uint8 > ULFPChunkedByteListDataComponent::GetData_Checked ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetData ( DataIndex , DataByteSize );
}

TArray < uint8 > ULFPChunkedByteListDataComponent::GetDataList ( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetDataList ( );
}

TArray < uint8 > ULFPChunkedByteListDataComponent::GetData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedByteListDataComponent , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return TArray < uint8 > ( );
	}

	return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetData ( DataIndex , DataByteSize );
}

void ULFPChunkedByteListDataComponent::SetData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const TArray < uint8 >& NewData )
{
	if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedByteListDataComponent , Warning , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return;
	}

	if ( NewData == RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetData ( DataIndex , DataByteSize ) )
	{
		return;
	}

	const TArray < uint8 > OldData = RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetData ( DataIndex , DataByteSize );

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).SetData ( DataIndex , DataByteSize , NewData );

	OnDataChanged.Broadcast ( RegionIndex , ChunkIndex , DataIndex , OldData , NewData );
}

bool ULFPChunkedByteListDataComponent::IsDataIndexValid ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	return RegionDataList.IsValidIndex ( RegionIndex ) && RegionDataList [ RegionIndex ].IsChunkIndexValid ( ChunkIndex ) && RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).IsDataIndexValid ( DataIndex , DataByteSize );
}

bool ULFPChunkedByteListDataComponent::IsChunkIndexValid ( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return RegionDataList.IsValidIndex ( RegionIndex ) && RegionDataList [ RegionIndex ].IsChunkIndexValid ( ChunkIndex );
}

bool ULFPChunkedByteListDataComponent::IsRegionIndexValid ( const int32 RegionIndex ) const
{
	return RegionDataList.IsValidIndex ( RegionIndex );
}

bool ULFPChunkedByteListDataComponent::IsChunkInitialized ( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return IsChunkIndexValid ( RegionIndex , ChunkIndex ) && RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).IsInitialized ( );
}

bool ULFPChunkedByteListDataComponent::IsRegionInitialized ( const int32 RegionIndex ) const
{
	return IsRegionIndexValid ( RegionIndex ) && RegionDataList [ RegionIndex ].IsInitialized ( );
}

int32 ULFPChunkedByteListDataComponent::GetDataIndexSize ( ) const
{
	return DataIndexSize;
}

int32 ULFPChunkedByteListDataComponent::GetChunkIndexSize ( ) const
{
	return ChunkIndexSize;
}

int32 ULFPChunkedByteListDataComponent::GetRegionIndexSize ( ) const
{
	return RegionIndexSize;
}
