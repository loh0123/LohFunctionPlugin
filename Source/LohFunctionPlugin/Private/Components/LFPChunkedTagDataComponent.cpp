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

	RegionDataList.SetNum(RegionIndexSize);
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
	RegionDataList[RegionIndex] = FLFPTaggedRegionData();

	FArchiveLoadCompressedProxy Proxy(LoadData.DataList, LoadData.CompressionName, ECompressionFlags::COMPRESS_BiasMemory);

	FLFPTaggedRegionData& RegionData = RegionDataList[RegionIndex];

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

	FLFPTaggedRegionData& RegionData = RegionDataList[RegionIndex];

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

	RegionDataList[RegionIndex].GetChunk(ChunkIndex).InitializeChunkData(DataIndexSize, FillTag);

	OnInitialized.Broadcast(RegionIndex, ChunkIndex);
}

void ULFPChunkedTagDataComponent::DeinitializeChunk( const int32 RegionIndex , const int32 ChunkIndex )
{
	if ( IsChunkIndexValid(RegionIndex, ChunkIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

		return;
	}

	RegionDataList[RegionIndex].GetChunk(ChunkIndex).DeinitializeChunkData();

	OnUninitialized.Broadcast(RegionIndex, ChunkIndex);
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

	RegionDataList[RegionIndex].InitializeRegionData(ChunkIndexSize);

	OnInitialized.Broadcast(RegionIndex, INDEX_NONE);
}

void ULFPChunkedTagDataComponent::DeinitializeRegion( const int32 RegionIndex )
{
	if ( IsRegionIndexValid(RegionIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

		return;
	}

	RegionDataList[RegionIndex].DeinitializeRegionData();

	OnUninitialized.Broadcast(RegionIndex, INDEX_NONE);
}

////////////////////////////

FGameplayTag ULFPChunkedTagDataComponent::GetDataTag_Checked( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	return RegionDataList[RegionIndex].GetChunk(ChunkIndex).GetDataTag(DataIndex);
}

TMap< int32 , int32 > ULFPChunkedTagDataComponent::GetDataMeta_Mapping( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return RegionDataList[RegionIndex].GetChunk(ChunkIndex).GetDataMetaIndexMapping();
}

const FLFPPrimitiveData* ULFPChunkedTagDataComponent::GetDataMeta_Direct( const int32 RegionIndex , const int32 ChunkIndex , const int32 MappingIndex , const FGameplayTag& DataMetaTag ) const
{
	check(IsChunkIndexValid(RegionIndex, ChunkIndex));

	return RegionDataList[RegionIndex].GetChunk(ChunkIndex).GetDataMeta_Direct(MappingIndex, DataMetaTag);
}

////////////////////////////

FGameplayTag ULFPChunkedTagDataComponent::GetDataTag( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	if ( IsDataIndexValid(RegionIndex, ChunkIndex, DataIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Verbose, TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )"), __FUNCTION__, RegionIndex, ChunkIndex, DataIndex);

		return FGameplayTag();
	}

	return RegionDataList[RegionIndex].GetChunk(ChunkIndex).GetDataTag(DataIndex);
}

void ULFPChunkedTagDataComponent::SetDataTag( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FGameplayTag& NewDataTag )
{
	if ( IsDataIndexValid(RegionIndex, ChunkIndex, DataIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )"), __FUNCTION__, RegionIndex, ChunkIndex, DataIndex);

		return;
	}

	if ( NewDataTag == RegionDataList[RegionIndex].GetChunk(ChunkIndex).GetDataTag(DataIndex) )
	{
		return;
	}

	const FGameplayTag OldTag = RegionDataList[RegionIndex].GetChunk(ChunkIndex).GetDataTag(DataIndex);

	RegionDataList[RegionIndex].GetChunk(ChunkIndex).SetDataTag(DataIndex, NewDataTag);

	OnTagChanged.Broadcast(RegionIndex, ChunkIndex, DataIndex, OldTag, NewDataTag);
}

FLFPPrimitiveData ULFPChunkedTagDataComponent::GetDataMeta( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FGameplayTag& DataMetaTag ) const
{
	if ( IsDataIndexValid(RegionIndex, ChunkIndex, DataIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Verbose, TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )"), __FUNCTION__, RegionIndex, ChunkIndex, DataIndex);

		return FLFPPrimitiveData();
	}

	if ( const FLFPPrimitiveData* MetaData = RegionDataList[RegionIndex].GetChunk(ChunkIndex).GetDataMeta(DataIndex, DataMetaTag) ; MetaData != nullptr )
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

	const FLFPPrimitiveData* OldMetaPtr = RegionDataList[RegionIndex].GetChunk(ChunkIndex).GetDataMeta(DataIndex, DataMetaTag);

	const FLFPPrimitiveData OldMeta = OldMetaPtr != nullptr
		                                  ? *OldMetaPtr
		                                  : FLFPPrimitiveData();

	RegionDataList[RegionIndex].GetChunk(ChunkIndex).GetOrAddDataMeta(DataIndex, DataMetaTag) = NewDataMeta;

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

	return RegionDataList[RegionIndex].GetChunk(ChunkIndex).GetChunkTag();
}

void ULFPChunkedTagDataComponent::SetChunkTag( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& NewChunkTag )
{
	if ( IsChunkIndexValid(RegionIndex, ChunkIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index ( R : %i , C : %i )"), __FUNCTION__, RegionIndex, ChunkIndex);

		return;
	}

	if ( NewChunkTag == RegionDataList[RegionIndex].GetChunk(ChunkIndex).GetChunkTag() )
	{
		return;
	}

	const FGameplayTag OldTag = RegionDataList[RegionIndex].GetChunk(ChunkIndex).GetChunkTag();

	RegionDataList[RegionIndex].GetChunk(ChunkIndex).SetChunkTag(NewChunkTag);

	OnTagChanged.Broadcast(RegionIndex, ChunkIndex, INDEX_NONE, OldTag, NewChunkTag);
}

FLFPPrimitiveData ULFPChunkedTagDataComponent::GetChunkMeta( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& ChunkMetaTag ) const
{
	if ( IsChunkIndexValid(RegionIndex, ChunkIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Verbose, TEXT("%hs : Invalid Index ( R : %i , C : %i )"), __FUNCTION__, RegionIndex, ChunkIndex);

		return FLFPPrimitiveData();
	}

	if ( const FLFPPrimitiveData* MetaData = RegionDataList[RegionIndex].GetChunk(ChunkIndex).GetChunkMeta(ChunkMetaTag) ; MetaData != nullptr )
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

	const FLFPPrimitiveData* OldMetaPtr = RegionDataList[RegionIndex].GetChunk(ChunkIndex).GetChunkMeta(ChunkMetaTag);

	const FLFPPrimitiveData OldMeta = OldMetaPtr != nullptr
		                                  ? *OldMetaPtr
		                                  : FLFPPrimitiveData();

	RegionDataList[RegionIndex].GetChunk(ChunkIndex).GetOrAddChunkMeta(ChunkMetaTag) = NewChunkMeta;

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

	return RegionDataList[RegionIndex].GetRegionTag();
}

void ULFPChunkedTagDataComponent::SetRegionTag( const int32 RegionIndex , const FGameplayTag& NewRegionTag )
{
	if ( IsRegionIndexValid(RegionIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index ( R : %i )"), __FUNCTION__, RegionIndex);

		return;
	}

	if ( NewRegionTag == RegionDataList[RegionIndex].GetRegionTag() )
	{
		return;
	}

	const FGameplayTag OldTag = RegionDataList[RegionIndex].GetRegionTag();

	RegionDataList[RegionIndex].SetRegionTag(NewRegionTag);

	OnTagChanged.Broadcast(RegionIndex, INDEX_NONE, INDEX_NONE, OldTag, NewRegionTag);
}

FLFPPrimitiveData ULFPChunkedTagDataComponent::GetRegionMeta( const int32 RegionIndex , const FGameplayTag& RegionMetaTag ) const
{
	if ( IsRegionIndexValid(RegionIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Verbose, TEXT("%hs : Invalid Index ( R : %i )"), __FUNCTION__, RegionIndex);

		return FLFPPrimitiveData();
	}

	if ( const FLFPPrimitiveData* MetaData = RegionDataList[RegionIndex].GetRegionMeta(RegionMetaTag) ; MetaData != nullptr )
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

	const FLFPPrimitiveData* OldMetaPtr = RegionDataList[RegionIndex].GetRegionMeta(RegionMetaTag);

	const FLFPPrimitiveData OldMeta = OldMetaPtr != nullptr
		                                  ? *OldMetaPtr
		                                  : FLFPPrimitiveData();

	RegionDataList[RegionIndex].GetOrAddRegionMeta(RegionMetaTag) = NewRegionMeta;

	OnMetaChanged.Broadcast(RegionIndex, INDEX_NONE, INDEX_NONE, RegionMetaTag, OldMeta, NewRegionMeta);
}

////////////////////////////

bool ULFPChunkedTagDataComponent::IsDataIndexValid( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	return RegionDataList.IsValidIndex(RegionIndex) && RegionDataList[RegionIndex].IsChunkIndexValid(ChunkIndex) && RegionDataList[RegionIndex].GetChunk(ChunkIndex).IsDataIndexValid(DataIndex);
}

bool ULFPChunkedTagDataComponent::IsChunkIndexValid( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return RegionDataList.IsValidIndex(RegionIndex) && RegionDataList[RegionIndex].IsChunkIndexValid(ChunkIndex);
}

bool ULFPChunkedTagDataComponent::IsRegionIndexValid( const int32 RegionIndex ) const
{
	return RegionDataList.IsValidIndex(RegionIndex);
}

bool ULFPChunkedTagDataComponent::IsChunkInitialized( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return IsChunkIndexValid(RegionIndex, ChunkIndex) && RegionDataList[RegionIndex].GetChunk(ChunkIndex).IsInitialized();
}

bool ULFPChunkedTagDataComponent::IsRegionInitialized( const int32 RegionIndex ) const
{
	return IsRegionIndexValid(RegionIndex) && RegionDataList[RegionIndex].IsInitialized();
}

int32 ULFPChunkedTagDataComponent::GetDataIndexSize( ) const
{
	return DataIndexSize;
}

int32 ULFPChunkedTagDataComponent::GetChunkIndexSize( ) const
{
	return ChunkIndexSize;
}

int32 ULFPChunkedTagDataComponent::GetRegionIndexSize( ) const
{
	return RegionIndexSize;
}
