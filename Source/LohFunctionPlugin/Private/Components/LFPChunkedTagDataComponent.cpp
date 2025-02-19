// Copyright (c) 2023-2025 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#include "Components/LFPChunkedTagDataComponent.h"

#include "Serialization/ArchiveLoadCompressedProxy.h"
#include "Serialization/ArchiveSaveCompressedProxy.h"

DEFINE_LOG_CATEGORY(LogChunkedTagDataComponent);

// Sets default values for this component's properties
ULFPChunkedTagDataComponent::ULFPChunkedTagDataComponent( )
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void ULFPChunkedTagDataComponent::BeginPlay( )
{
	Super::BeginPlay();

	GridDataList.SetNum(RegionIndexSize);
}

// Called every frame
void ULFPChunkedTagDataComponent::TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

////////////////////////////

void ULFPChunkedTagDataComponent::LoadRegion( const int32 RegionIndex , const FLFPChunkedTagSerializeData& LoadData )
{
	if ( IsRegionIndexValid(RegionIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

		return;
	}

	// Clear region
	GridDataList[RegionIndex] = FLFPTaggedRegionData();

	FArchiveLoadCompressedProxy Proxy(LoadData.DataList, LoadData.CompressionName, ECompressionFlags::COMPRESS_BiasMemory);

	FLFPTaggedRegionData& RegionData = GridDataList[RegionIndex];

	RegionData.StaticStruct()->SerializeItem(Proxy, &RegionData, nullptr);
}

void ULFPChunkedTagDataComponent::SaveRegion( const int32 RegionIndex , FLFPChunkedTagSerializeData& SaveData )
{
	if ( IsRegionIndexValid(RegionIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

		return;
	}

	FArchiveSaveCompressedProxy Proxy(SaveData.DataList, SaveData.CompressionName, ECompressionFlags::COMPRESS_BiasMemory);

	FLFPTaggedRegionData& RegionData = GridDataList[RegionIndex];

	RegionData.StaticStruct()->SerializeItem(Proxy, &RegionData, nullptr);
}

////////////////////////////

void ULFPChunkedTagDataComponent::InitializeChunk( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& FillTag )
{
	if ( IsChunkIndexValid(RegionIndex, ChunkIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

		return;
	}

	if ( IsChunkInitialized(RegionIndex, ChunkIndex) )
	{
		UE_LOG(LogChunkedTagDataComponent, Log, TEXT("%hs : Chunk ( %i ) on Region ( %i ) already initialized"), __FUNCTION__, ChunkIndex, RegionIndex);

		return;
	}

	GridDataList[RegionIndex].GetChunk(ChunkIndex).InitializeChunkData(DataIndexSize, FillTag);
}

void ULFPChunkedTagDataComponent::DeinitializeChunk( const int32 RegionIndex , const int32 ChunkIndex )
{
	if ( IsChunkIndexValid(RegionIndex, ChunkIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

		return;
	}

	GridDataList[RegionIndex].GetChunk(ChunkIndex).DeinitializeChunkData();
}

void ULFPChunkedTagDataComponent::InitializeRegion( const int32 RegionIndex )
{
	if ( IsRegionIndexValid(RegionIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

		return;
	}

	if ( IsRegionInitialized(RegionIndex) )
	{
		UE_LOG(LogChunkedTagDataComponent, Log, TEXT("%hs : Region ( %i ) already initialized"), __FUNCTION__, RegionIndex);

		return;
	}

	GridDataList[RegionIndex].InitializeRegionData(ChunkIndexSize);
}

void ULFPChunkedTagDataComponent::DeinitializeRegion( const int32 RegionIndex )
{
	if ( IsRegionIndexValid(RegionIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

		return;
	}

	GridDataList[RegionIndex].DeinitializeRegionData();
}

////////////////////////////

FGameplayTag ULFPChunkedTagDataComponent::GetDataTag_Checked( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	return GridDataList[RegionIndex].GetChunk(ChunkIndex).GetDataTag(DataIndex);
}

TMap< int32 , int32 > ULFPChunkedTagDataComponent::GetDataMeta_Mapping( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return GridDataList[RegionIndex].GetChunk(ChunkIndex).GetDataMetaIndexMapping();
}

const FLFPPrimitiveData* ULFPChunkedTagDataComponent::GetDataMeta_Direct( const int32 RegionIndex , const int32 ChunkIndex , const int32 MappingIndex , const FGameplayTag& DataMetaTag ) const
{
	check(IsChunkIndexValid(RegionIndex, ChunkIndex));

	return GridDataList[RegionIndex].GetChunk(ChunkIndex).GetDataMeta_Direct(MappingIndex, DataMetaTag);
}

////////////////////////////

FGameplayTag ULFPChunkedTagDataComponent::GetDataTag( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	if ( IsDataIndexValid(RegionIndex, ChunkIndex, DataIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Verbose, TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )"), __FUNCTION__, RegionIndex, ChunkIndex, DataIndex);

		return FGameplayTag();
	}

	return GridDataList[RegionIndex].GetChunk(ChunkIndex).GetDataTag(DataIndex);
}

void ULFPChunkedTagDataComponent::SetDataTag( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FGameplayTag& NewDataTag )
{
	if ( IsDataIndexValid(RegionIndex, ChunkIndex, DataIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )"), __FUNCTION__, RegionIndex, ChunkIndex, DataIndex);

		return;
	}

	if ( NewDataTag == GridDataList[RegionIndex].GetChunk(ChunkIndex).GetDataTag(DataIndex) )
	{
		return;
	}

	const FGameplayTag OldTag = GridDataList[RegionIndex].GetChunk(ChunkIndex).GetDataTag(DataIndex);

	GridDataList[RegionIndex].GetChunk(ChunkIndex).SetDataTag(DataIndex, NewDataTag);

	OnTagChanged.Broadcast(RegionIndex, ChunkIndex, DataIndex, OldTag, NewDataTag);
}

FLFPPrimitiveData ULFPChunkedTagDataComponent::GetDataMeta( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FGameplayTag& DataMetaTag ) const
{
	if ( IsDataIndexValid(RegionIndex, ChunkIndex, DataIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Verbose, TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )"), __FUNCTION__, RegionIndex, ChunkIndex, DataIndex);

		return FLFPPrimitiveData();
	}

	if ( const FLFPPrimitiveData* MetaData = GridDataList[RegionIndex].GetChunk(ChunkIndex).GetDataMeta(DataIndex, DataMetaTag) ; MetaData != nullptr )
	{
		return *MetaData;
	}

	return FLFPPrimitiveData();
}

void ULFPChunkedTagDataComponent::SetDataMeta( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FGameplayTag& DataMetaTag , const FLFPPrimitiveData& NewDataMeta )
{
	if ( IsDataIndexValid(RegionIndex, ChunkIndex, DataIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )"), __FUNCTION__, RegionIndex, ChunkIndex, DataIndex);

		return;
	}

	const FLFPPrimitiveData* OldMetaPtr = GridDataList[RegionIndex].GetChunk(ChunkIndex).GetDataMeta(DataIndex, DataMetaTag);

	const FLFPPrimitiveData OldMeta = OldMetaPtr != nullptr
		                                  ? *OldMetaPtr
		                                  : FLFPPrimitiveData();

	GridDataList[RegionIndex].GetChunk(ChunkIndex).GetOrAddDataMeta(DataIndex, DataMetaTag) = NewDataMeta;

	OnMetaChanged.Broadcast(RegionIndex, ChunkIndex, DataIndex, DataMetaTag, OldMeta, NewDataMeta);
}

////////////////////////////

FGameplayTag ULFPChunkedTagDataComponent::GetChunkTag( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	if ( IsChunkIndexValid(RegionIndex, ChunkIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Verbose, TEXT("%hs : Invalid Index ( R : %i , C : %i )"), __FUNCTION__, RegionIndex, ChunkIndex);

		return FGameplayTag();
	}

	return GridDataList[RegionIndex].GetChunk(ChunkIndex).GetChunkTag();
}

void ULFPChunkedTagDataComponent::SetChunkTag( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& NewChunkTag )
{
	if ( IsChunkIndexValid(RegionIndex, ChunkIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index ( R : %i , C : %i )"), __FUNCTION__, RegionIndex, ChunkIndex);

		return;
	}

	if ( NewChunkTag == GridDataList[RegionIndex].GetChunk(ChunkIndex).GetChunkTag() )
	{
		return;
	}

	const FGameplayTag OldTag = GridDataList[RegionIndex].GetChunk(ChunkIndex).GetChunkTag();

	GridDataList[RegionIndex].GetChunk(ChunkIndex).SetChunkTag(NewChunkTag);

	OnTagChanged.Broadcast(RegionIndex, ChunkIndex, INDEX_NONE, OldTag, NewChunkTag);
}

FLFPPrimitiveData ULFPChunkedTagDataComponent::GetChunkMeta( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& ChunkMetaTag ) const
{
	if ( IsChunkIndexValid(RegionIndex, ChunkIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Verbose, TEXT("%hs : Invalid Index ( R : %i , C : %i )"), __FUNCTION__, RegionIndex, ChunkIndex);

		return FLFPPrimitiveData();
	}

	if ( const FLFPPrimitiveData* MetaData = GridDataList[RegionIndex].GetChunk(ChunkIndex).GetChunkMeta(ChunkMetaTag) ; MetaData != nullptr )
	{
		return *MetaData;
	}

	return FLFPPrimitiveData();
}

void ULFPChunkedTagDataComponent::SetChunkMeta( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& ChunkMetaTag , const FLFPPrimitiveData& NewChunkMeta )
{
	if ( IsChunkIndexValid(RegionIndex, ChunkIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index ( R : %i , C : %i )"), __FUNCTION__, RegionIndex, ChunkIndex);

		return;
	}

	const FLFPPrimitiveData* OldMetaPtr = GridDataList[RegionIndex].GetChunk(ChunkIndex).GetChunkMeta(ChunkMetaTag);

	const FLFPPrimitiveData OldMeta = OldMetaPtr != nullptr
		                                  ? *OldMetaPtr
		                                  : FLFPPrimitiveData();

	GridDataList[RegionIndex].GetChunk(ChunkIndex).GetOrAddChunkMeta(ChunkMetaTag) = NewChunkMeta;

	OnMetaChanged.Broadcast(RegionIndex, ChunkIndex, INDEX_NONE, ChunkMetaTag, OldMeta, NewChunkMeta);
}

////////////////////////////

FGameplayTag ULFPChunkedTagDataComponent::GetRegionTag( const int32 RegionIndex ) const
{
	if ( IsRegionIndexValid(RegionIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Verbose, TEXT("%hs : Invalid Index ( R : %i )"), __FUNCTION__, RegionIndex);

		return FGameplayTag();
	}

	return GridDataList[RegionIndex].GetRegionTag();
}

void ULFPChunkedTagDataComponent::SetRegionTag( const int32 RegionIndex , const FGameplayTag& NewRegionTag )
{
	if ( IsRegionIndexValid(RegionIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index ( R : %i )"), __FUNCTION__, RegionIndex);

		return;
	}

	if ( NewRegionTag == GridDataList[RegionIndex].GetRegionTag() )
	{
		return;
	}

	const FGameplayTag OldTag = GridDataList[RegionIndex].GetRegionTag();

	GridDataList[RegionIndex].SetRegionTag(NewRegionTag);

	OnTagChanged.Broadcast(RegionIndex, INDEX_NONE, INDEX_NONE, OldTag, NewRegionTag);
}

FLFPPrimitiveData ULFPChunkedTagDataComponent::GetRegionMeta( const int32 RegionIndex , const FGameplayTag& RegionMetaTag ) const
{
	if ( IsRegionIndexValid(RegionIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Verbose, TEXT("%hs : Invalid Index ( R : %i )"), __FUNCTION__, RegionIndex);

		return FLFPPrimitiveData();
	}

	if ( const FLFPPrimitiveData* MetaData = GridDataList[RegionIndex].GetRegionMeta(RegionMetaTag) ; MetaData != nullptr )
	{
		return *MetaData;
	}

	return FLFPPrimitiveData();
}

void ULFPChunkedTagDataComponent::SetRegionMeta( const int32 RegionIndex , const FGameplayTag& RegionMetaTag , const FLFPPrimitiveData& NewRegionMeta )
{
	if ( IsRegionIndexValid(RegionIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index ( R : %i )"), __FUNCTION__, RegionIndex);

		return;
	}

	const FLFPPrimitiveData* OldMetaPtr = GridDataList[RegionIndex].GetRegionMeta(RegionMetaTag);

	const FLFPPrimitiveData OldMeta = OldMetaPtr != nullptr
		                                  ? *OldMetaPtr
		                                  : FLFPPrimitiveData();

	GridDataList[RegionIndex].GetOrAddRegionMeta(RegionMetaTag) = NewRegionMeta;

	OnMetaChanged.Broadcast(RegionIndex, INDEX_NONE, INDEX_NONE, RegionMetaTag, OldMeta, NewRegionMeta);
}

////////////////////////////

bool ULFPChunkedTagDataComponent::IsDataIndexValid( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	return GridDataList.IsValidIndex(RegionIndex) && GridDataList[RegionIndex].IsChunkIndexValid(ChunkIndex) && GridDataList[RegionIndex].GetChunk(ChunkIndex).IsDataIndexValid(DataIndex);
}

bool ULFPChunkedTagDataComponent::IsChunkIndexValid( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return GridDataList.IsValidIndex(RegionIndex) && GridDataList[RegionIndex].IsChunkIndexValid(ChunkIndex);
}

bool ULFPChunkedTagDataComponent::IsRegionIndexValid( const int32 RegionIndex ) const
{
	return GridDataList.IsValidIndex(RegionIndex);
}

bool ULFPChunkedTagDataComponent::IsChunkInitialized( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return IsChunkIndexValid(RegionIndex, ChunkIndex) && GridDataList[RegionIndex].GetChunk(ChunkIndex).IsInitialized();
}

bool ULFPChunkedTagDataComponent::IsRegionInitialized( const int32 RegionIndex ) const
{
	return IsRegionIndexValid(RegionIndex) && GridDataList[RegionIndex].IsInitialized();
}
