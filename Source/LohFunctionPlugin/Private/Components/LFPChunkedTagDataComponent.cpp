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

	return GridDataList[RegionIndex].GetChuck(ChuckIndex).SetDataTag(DataIndex, NewDataTag);
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

	GridDataList[RegionIndex].GetChuck(ChuckIndex).GetOrAddDataMeta(DataIndex, DataMetaTag) = NewDataMeta;
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

	return GridDataList[RegionIndex].GetChuck(ChuckIndex).SetChuckTag(NewChuckTag);
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

	GridDataList[RegionIndex].GetChuck(ChuckIndex).GetOrAddChuckMeta(ChuckMetaTag) = NewChuckMeta;
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

	return GridDataList[RegionIndex].SetRegionTag(NewRegionTag);
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

	GridDataList[RegionIndex].GetOrAddRegionMeta(RegionMetaTag) = NewRegionMeta;
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
