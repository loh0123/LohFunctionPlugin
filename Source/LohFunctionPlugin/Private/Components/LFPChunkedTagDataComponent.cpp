// Fill out your copyright notice in the Description page of Project Settings.

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
	if ( IsRegionValid(RegionIndex) == false )
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
	if ( IsRegionValid(RegionIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

		return;
	}

	FArchiveSaveCompressedProxy Proxy(SaveData.DataList, SaveData.CompressionName, ECompressionFlags::COMPRESS_BiasMemory);

	FLFPTaggedRegionData& RegionData = GridDataList[RegionIndex];

	RegionData.StaticStruct()->SerializeItem(Proxy, &RegionData, nullptr);
}

////////////////////////////

void ULFPChunkedTagDataComponent::InitializeChuck( const int32 RegionIndex , const int32 ChuckIndex )
{
	if ( IsChuckValid(RegionIndex, ChuckIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

		return;
	}

	if ( IsChuckInitialized(RegionIndex, ChuckIndex) )
	{
		UE_LOG(LogChunkedTagDataComponent, Log, TEXT("%hs : Chuck ( %i ) on Region ( %i ) already initialized"), __FUNCTION__, ChuckIndex, RegionIndex);

		return;
	}

	GridDataList[RegionIndex].GetChuck(ChuckIndex).InitializeChuckData(DataIndexSize);
}

void ULFPChunkedTagDataComponent::DeinitializeChuck( const int32 RegionIndex , const int32 ChuckIndex )
{
	if ( IsChuckValid(RegionIndex, ChuckIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

		return;
	}

	GridDataList[RegionIndex].GetChuck(ChuckIndex).DeinitializeChuckData();
}

void ULFPChunkedTagDataComponent::InitializeRegion( const int32 RegionIndex )
{
	if ( IsRegionValid(RegionIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

		return;
	}

	if ( IsRegionInitialized(RegionIndex) )
	{
		UE_LOG(LogChunkedTagDataComponent, Log, TEXT("%hs : Region ( %i ) already initialized"), __FUNCTION__, RegionIndex);

		return;
	}

	GridDataList[RegionIndex].InitializeRegionData(ChuckIndexSize);
}

void ULFPChunkedTagDataComponent::DeinitializeRegion( const int32 RegionIndex )
{
	if ( IsRegionValid(RegionIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

		return;
	}

	GridDataList[RegionIndex].DeinitializeRegionData();
}

////////////////////////////

FGameplayTag ULFPChunkedTagDataComponent::GetDataTag_Checked( const int32 RegionIndex , const int32 ChuckIndex , const int32 DataIndex ) const
{
	return GridDataList[RegionIndex].GetChuck(ChuckIndex).GetDataTag(DataIndex);
}

TMap< int32 , int32 > ULFPChunkedTagDataComponent::GetDataMeta_Mapping( const int32 RegionIndex , const int32 ChuckIndex ) const
{
	return GridDataList[RegionIndex].GetChuck(ChuckIndex).GetDataMetaIndexMapping();
}

const FLFPPrimitiveData* ULFPChunkedTagDataComponent::GetDataMeta_Direct( const int32 RegionIndex , const int32 ChuckIndex , const int32 MappingIndex , const FGameplayTag& DataMetaTag ) const
{
	check(IsChuckValid(RegionIndex, ChuckIndex));

	return GridDataList[RegionIndex].GetChuck(ChuckIndex).GetDataMeta_Direct(MappingIndex, DataMetaTag);
}

////////////////////////////

FGameplayTag ULFPChunkedTagDataComponent::GetDataTag( const int32 RegionIndex , const int32 ChuckIndex , const int32 DataIndex ) const
{
	if ( IsGridValid(RegionIndex, ChuckIndex, DataIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

		return FGameplayTag();
	}

	return GridDataList[RegionIndex].GetChuck(ChuckIndex).GetDataTag(DataIndex);
}

void ULFPChunkedTagDataComponent::SetDataTag( const int32 RegionIndex , const int32 ChuckIndex , const int32 DataIndex , const FGameplayTag& NewDataTag )
{
	if ( IsGridValid(RegionIndex, ChuckIndex, DataIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

		return;
	}

	if ( NewDataTag == GridDataList[RegionIndex].GetChuck(ChuckIndex).GetDataTag(DataIndex) )
	{
		return;
	}

	const FGameplayTag OldTag = GridDataList[RegionIndex].GetChuck(ChuckIndex).GetDataTag(DataIndex);

	GridDataList[RegionIndex].GetChuck(ChuckIndex).SetDataTag(DataIndex, NewDataTag);

	OnTagChanged.Broadcast(RegionIndex, ChuckIndex, DataIndex, OldTag, NewDataTag);
}

FLFPPrimitiveData ULFPChunkedTagDataComponent::GetDataMeta( const int32 RegionIndex , const int32 ChuckIndex , const int32 DataIndex , const FGameplayTag& DataMetaTag ) const
{
	if ( IsGridValid(RegionIndex, ChuckIndex, DataIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

		return FLFPPrimitiveData();
	}

	if ( const FLFPPrimitiveData* MetaData = GridDataList[RegionIndex].GetChuck(ChuckIndex).GetDataMeta(DataIndex, DataMetaTag) ; MetaData != nullptr )
	{
		return *MetaData;
	}

	return FLFPPrimitiveData();
}

void ULFPChunkedTagDataComponent::SetDataMeta( const int32 RegionIndex , const int32 ChuckIndex , const int32 DataIndex , const FGameplayTag& DataMetaTag , const FLFPPrimitiveData& NewDataMeta )
{
	if ( IsGridValid(RegionIndex, ChuckIndex, DataIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

		return;
	}

	const FLFPPrimitiveData* OldMetaPtr = GridDataList[RegionIndex].GetChuck(ChuckIndex).GetDataMeta(DataIndex, DataMetaTag);

	const FLFPPrimitiveData OldMeta = OldMetaPtr != nullptr
		                                  ? *OldMetaPtr
		                                  : FLFPPrimitiveData();

	GridDataList[RegionIndex].GetChuck(ChuckIndex).GetOrAddDataMeta(DataIndex, DataMetaTag) = NewDataMeta;

	OnMetaChanged.Broadcast(RegionIndex, ChuckIndex, DataIndex, DataMetaTag, OldMeta, NewDataMeta);
}

////////////////////////////

FGameplayTag ULFPChunkedTagDataComponent::GetChuckTag( const int32 RegionIndex , const int32 ChuckIndex ) const
{
	if ( IsChuckValid(RegionIndex, ChuckIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

		return FGameplayTag();
	}

	return GridDataList[RegionIndex].GetChuck(ChuckIndex).GetChuckTag();
}

void ULFPChunkedTagDataComponent::SetChuckTag( const int32 RegionIndex , const int32 ChuckIndex , const FGameplayTag& NewChuckTag )
{
	if ( IsChuckValid(RegionIndex, ChuckIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

		return;
	}

	if ( NewChuckTag == GridDataList[RegionIndex].GetChuck(ChuckIndex).GetChuckTag() )
	{
		return;
	}

	const FGameplayTag OldTag = GridDataList[RegionIndex].GetChuck(ChuckIndex).GetChuckTag();

	GridDataList[RegionIndex].GetChuck(ChuckIndex).SetChuckTag(NewChuckTag);

	OnTagChanged.Broadcast(RegionIndex, ChuckIndex, INDEX_NONE, OldTag, NewChuckTag);
}

FLFPPrimitiveData ULFPChunkedTagDataComponent::GetChuckMeta( const int32 RegionIndex , const int32 ChuckIndex , const FGameplayTag& ChuckMetaTag ) const
{
	if ( IsChuckValid(RegionIndex, ChuckIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

		return FLFPPrimitiveData();
	}

	if ( const FLFPPrimitiveData* MetaData = GridDataList[RegionIndex].GetChuck(ChuckIndex).GetChuckMeta(ChuckMetaTag) ; MetaData != nullptr )
	{
		return *MetaData;
	}

	return FLFPPrimitiveData();
}

void ULFPChunkedTagDataComponent::SetChuckMeta( const int32 RegionIndex , const int32 ChuckIndex , const FGameplayTag& ChuckMetaTag , const FLFPPrimitiveData& NewChuckMeta )
{
	if ( IsChuckValid(RegionIndex, ChuckIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

		return;
	}

	const FLFPPrimitiveData* OldMetaPtr = GridDataList[RegionIndex].GetChuck(ChuckIndex).GetChuckMeta(ChuckMetaTag);

	const FLFPPrimitiveData OldMeta = OldMetaPtr != nullptr
		                                  ? *OldMetaPtr
		                                  : FLFPPrimitiveData();

	GridDataList[RegionIndex].GetChuck(ChuckIndex).GetOrAddChuckMeta(ChuckMetaTag) = NewChuckMeta;

	OnMetaChanged.Broadcast(RegionIndex, ChuckIndex, INDEX_NONE, ChuckMetaTag, OldMeta, NewChuckMeta);
}

////////////////////////////

FGameplayTag ULFPChunkedTagDataComponent::GetRegionTag( const int32 RegionIndex ) const
{
	if ( IsRegionValid(RegionIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

		return FGameplayTag();
	}

	return GridDataList[RegionIndex].GetRegionTag();
}

void ULFPChunkedTagDataComponent::SetRegionTag( const int32 RegionIndex , const FGameplayTag& NewRegionTag )
{
	if ( IsRegionValid(RegionIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

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
	if ( IsRegionValid(RegionIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

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
	if ( IsRegionValid(RegionIndex) == false )
	{
		UE_LOG(LogChunkedTagDataComponent, Warning, TEXT("%hs : Invalid Index"), __FUNCTION__);

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

bool ULFPChunkedTagDataComponent::IsGridValid( const int32 RegionIndex , const int32 ChuckIndex , const int32 DataIndex ) const
{
	return GridDataList.IsValidIndex(RegionIndex) && GridDataList[RegionIndex].IsChuckIndexValid(ChuckIndex) && GridDataList[RegionIndex].GetChuck(ChuckIndex).IsDataIndexValid(DataIndex);
}

bool ULFPChunkedTagDataComponent::IsChuckValid( const int32 RegionIndex , const int32 ChuckIndex ) const
{
	return GridDataList.IsValidIndex(RegionIndex) && GridDataList[RegionIndex].IsChuckIndexValid(ChuckIndex);
}

bool ULFPChunkedTagDataComponent::IsRegionValid( const int32 RegionIndex ) const
{
	return GridDataList.IsValidIndex(RegionIndex);
}

bool ULFPChunkedTagDataComponent::IsChuckInitialized( const int32 RegionIndex , const int32 ChuckIndex ) const
{
	return IsChuckValid(RegionIndex, ChuckIndex) && GridDataList[RegionIndex].GetChuck(ChuckIndex).IsInitialized();
}

bool ULFPChunkedTagDataComponent::IsRegionInitialized( const int32 RegionIndex ) const
{
	return IsRegionValid(RegionIndex) && GridDataList[RegionIndex].IsInitialized();
}
