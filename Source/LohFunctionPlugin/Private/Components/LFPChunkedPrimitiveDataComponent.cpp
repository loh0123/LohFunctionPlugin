// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LFPChunkedPrimitiveDataComponent.h"

#include "Serialization/ArchiveLoadCompressedProxy.h"
#include "Serialization/ArchiveSaveCompressedProxy.h"

DEFINE_LOG_CATEGORY ( LogChunkedByteListDataComponent );


// Sets default values for this component's properties
ULFPChunkedPrimitiveDataComponent::ULFPChunkedPrimitiveDataComponent ( )
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULFPChunkedPrimitiveDataComponent::BeginPlay ( )
{
	Super::BeginPlay ( );

	RegionDataList.SetNum ( RegionIndexSize );
}


// Called every frame
void ULFPChunkedPrimitiveDataComponent::TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent ( DeltaTime , TickType , ThisTickFunction );

	// ...
}

void ULFPChunkedPrimitiveDataComponent::SetSize ( const FIntVector& NewSize )
{
	RegionIndexSize = NewSize.X;
	ChunkIndexSize  = NewSize.Y;
	DataIndexSize   = NewSize.Z;

	RegionDataList.Reset ( );
	RegionDataList.SetNum ( RegionIndexSize );
}

void ULFPChunkedPrimitiveDataComponent::LoadRegion ( const int32 RegionIndex , const FLFPChunkedPrimitiveSerializeData& LoadData )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedByteListDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	// Clear region
	RegionDataList [ RegionIndex ] = FLFPPrimitiveRegionData ( );

	FArchiveLoadCompressedProxy Proxy ( LoadData.DataList , LoadData.CompressionName , ECompressionFlags::COMPRESS_BiasMemory );

	FLFPPrimitiveRegionData& RegionData = RegionDataList [ RegionIndex ];

	RegionData.StaticStruct ( )->SerializeItem ( Proxy , &RegionData , nullptr );
}

void ULFPChunkedPrimitiveDataComponent::SaveRegion ( const int32 RegionIndex , FLFPChunkedPrimitiveSerializeData& SaveData )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedByteListDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	FArchiveSaveCompressedProxy Proxy ( SaveData.DataList , SaveData.CompressionName , ECompressionFlags::COMPRESS_BiasMemory );

	FLFPPrimitiveRegionData& RegionData = RegionDataList [ RegionIndex ];

	RegionData.StaticStruct ( )->SerializeItem ( Proxy , &RegionData , nullptr );
}

void ULFPChunkedPrimitiveDataComponent::InitializeChunk ( const int32 RegionIndex , const int32 ChunkIndex )
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

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).InitializeChunkData ( DataIndexSize );
}

void ULFPChunkedPrimitiveDataComponent::DeinitializeChunk ( const int32 RegionIndex , const int32 ChunkIndex )
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedByteListDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).DeinitializeChunkData ( );
}

void ULFPChunkedPrimitiveDataComponent::InitializeRegion ( const int32 RegionIndex )
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

void ULFPChunkedPrimitiveDataComponent::DeinitializeRegion ( const int32 RegionIndex )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedByteListDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	RegionDataList [ RegionIndex ].DeinitializeRegionData ( );
}

const FLFPPrimitiveData& ULFPChunkedPrimitiveDataComponent::GetData_Checked ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetData ( DataIndex );
}

TArray < FLFPPrimitiveData > ULFPChunkedPrimitiveDataComponent::GetDataList ( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetDataList ( );
}

FLFPPrimitiveData ULFPChunkedPrimitiveDataComponent::GetData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedByteListDataComponent , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return TArray < uint8 > ( );
	}

	return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetData ( DataIndex );
}

void ULFPChunkedPrimitiveDataComponent::SetData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FLFPPrimitiveData& NewData )
{
	if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedByteListDataComponent , Warning , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return;
	}

	if ( NewData == RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetData ( DataIndex ) )
	{
		return;
	}

	const FLFPPrimitiveData OldData = RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetData ( DataIndex );

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).SetData ( DataIndex , NewData );

	OnDataChanged.Broadcast ( RegionIndex , ChunkIndex , DataIndex , OldData , NewData );
}

FLFPPrimitiveData ULFPChunkedPrimitiveDataComponent::GetChunkData ( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedByteListDataComponent , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex );

		return TArray < uint8 > ( );
	}

	return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetChunkData ( );
}

void ULFPChunkedPrimitiveDataComponent::SetChunkData ( const int32 RegionIndex , const int32 ChunkIndex , const FLFPPrimitiveData& NewData )
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedByteListDataComponent , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex );

		return;
	}

	if ( NewData == RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetChunkData ( ) )
	{
		return;
	}

	const FLFPPrimitiveData OldData = RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetChunkData ( );

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).SetChunkData ( NewData );

	OnDataChanged.Broadcast ( RegionIndex , ChunkIndex , INDEX_NONE , OldData , NewData );
}

FLFPPrimitiveData ULFPChunkedPrimitiveDataComponent::GetRegionData ( const int32 RegionIndex ) const
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedByteListDataComponent , Verbose , TEXT("%hs : Invalid Index ( R : %i )") , __FUNCTION__ , RegionIndex );

		return TArray < uint8 > ( );
	}

	return RegionDataList [ RegionIndex ].GetRegionData ( );
}

void ULFPChunkedPrimitiveDataComponent::SetRegionData ( const int32 RegionIndex , const FLFPPrimitiveData& NewData )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedByteListDataComponent , Verbose , TEXT("%hs : Invalid Index ( R : %i )") , __FUNCTION__ , RegionIndex );

		return;
	}

	if ( NewData == RegionDataList [ RegionIndex ].GetRegionData ( ) )
	{
		return;
	}

	const FLFPPrimitiveData OldData = RegionDataList [ RegionIndex ].GetRegionData ( );

	RegionDataList [ RegionIndex ].SetRegionData ( NewData );

	OnDataChanged.Broadcast ( RegionIndex , INDEX_NONE , INDEX_NONE , OldData , NewData );
}

bool ULFPChunkedPrimitiveDataComponent::IsDataIndexValid ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	return RegionDataList.IsValidIndex ( RegionIndex ) && RegionDataList [ RegionIndex ].IsChunkIndexValid ( ChunkIndex ) && RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).IsDataIndexValid ( DataIndex );
}

bool ULFPChunkedPrimitiveDataComponent::IsChunkIndexValid ( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return RegionDataList.IsValidIndex ( RegionIndex ) && RegionDataList [ RegionIndex ].IsChunkIndexValid ( ChunkIndex );
}

bool ULFPChunkedPrimitiveDataComponent::IsRegionIndexValid ( const int32 RegionIndex ) const
{
	return RegionDataList.IsValidIndex ( RegionIndex );
}

bool ULFPChunkedPrimitiveDataComponent::IsChunkInitialized ( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return IsChunkIndexValid ( RegionIndex , ChunkIndex ) && RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).IsInitialized ( );
}

bool ULFPChunkedPrimitiveDataComponent::IsRegionInitialized ( const int32 RegionIndex ) const
{
	return IsRegionIndexValid ( RegionIndex ) && RegionDataList [ RegionIndex ].IsInitialized ( );
}

int32 ULFPChunkedPrimitiveDataComponent::GetDataIndexSize ( ) const
{
	return DataIndexSize;
}

int32 ULFPChunkedPrimitiveDataComponent::GetChunkIndexSize ( ) const
{
	return ChunkIndexSize;
}

int32 ULFPChunkedPrimitiveDataComponent::GetRegionIndexSize ( ) const
{
	return RegionIndexSize;
}
