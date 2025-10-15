// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LFPChunkedFlowDataComponent.h"

#include "Serialization/ArchiveLoadCompressedProxy.h"
#include "Serialization/ArchiveSaveCompressedProxy.h"


DEFINE_LOG_CATEGORY ( LogChunkedFlowDataComponent );

FLFPFlowCellData ULFPChunkedFlowDataLibrary::MakeFlowCellData ( const ELFPFlowSetting FlowSetting , const FVector FlowVector , const float FlowPressure )
{
	FLFPFlowCellData ResultData;

	ResultData.FlowSetting  = FlowSetting;
	ResultData.FlowVectorX  = FlowVector.X;
	ResultData.FlowVectorY  = FlowVector.Y;
	ResultData.FlowVectorZ  = FlowVector.Z;
	ResultData.FlowPressure = FlowPressure;

	return ResultData;
}

ELFPFlowSetting ULFPChunkedFlowDataLibrary::GetFlowCellSetting ( const FLFPFlowCellData& CellData )
{
	return CellData.FlowSetting;
}

FVector ULFPChunkedFlowDataLibrary::GetFlowCellVelocity ( const FLFPFlowCellData& CellData )
{
	return FVector ( CellData.FlowVectorX , CellData.FlowVectorY , CellData.FlowVectorZ );
}

float ULFPChunkedFlowDataLibrary::GetFlowCellPressure ( const FLFPFlowCellData& CellData )
{
	return CellData.FlowPressure;
}

// Sets default values for this component's properties
ULFPChunkedFlowDataComponent::ULFPChunkedFlowDataComponent ( )
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULFPChunkedFlowDataComponent::BeginPlay ( )
{
	Super::BeginPlay ( );

	// ...
}


// Called every frame
void ULFPChunkedFlowDataComponent::TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent ( DeltaTime , TickType , ThisTickFunction );

	// ...
}

void ULFPChunkedFlowDataComponent::SetSize ( const FIntVector& NewSize )
{
	RegionIndexSize = NewSize.X;
	ChunkIndexSize  = NewSize.Y;
	DataIndexSize   = NewSize.Z;

	RegionDataList.Reset ( );
	RegionDataList.SetNum ( RegionIndexSize );
}

void ULFPChunkedFlowDataComponent::LoadRegion ( const int32 RegionIndex , const FLFPChunkedFlowSerializeData& LoadData )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedFlowDataComponent
		         , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	// Clear region
	RegionDataList [ RegionIndex ] = FLFPFlowRegionData ( );

	FArchiveLoadCompressedProxy Proxy ( LoadData.DataList , LoadData.CompressionName , ECompressionFlags::COMPRESS_BiasMemory );

	FLFPFlowRegionData& RegionData = RegionDataList [ RegionIndex ];

	RegionData.StaticStruct ( )->SerializeItem ( Proxy , &RegionData , nullptr );
}

void ULFPChunkedFlowDataComponent::SaveRegion ( const int32 RegionIndex , FLFPChunkedFlowSerializeData& SaveData )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedFlowDataComponent
		         , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	FArchiveSaveCompressedProxy Proxy ( SaveData.DataList , SaveData.CompressionName , ECompressionFlags::COMPRESS_BiasMemory );

	FLFPFlowRegionData& RegionData = RegionDataList [ RegionIndex ];

	RegionData.StaticStruct ( )->SerializeItem ( Proxy , &RegionData , nullptr );
}

void ULFPChunkedFlowDataComponent::InitializeChunk ( const int32 RegionIndex , const int32 ChunkIndex )
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedFlowDataComponent
		         , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	if ( IsChunkInitialized ( RegionIndex , ChunkIndex ) )
	{
		UE_LOG ( LogChunkedFlowDataComponent
		         , Log , TEXT("%hs : Chunk ( %i ) on Region ( %i ) already initialized") , __FUNCTION__ , ChunkIndex , RegionIndex );

		return;
	}

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).InitializeChunkData ( DataIndexSize );
}

void ULFPChunkedFlowDataComponent::DeinitializeChunk ( const int32 RegionIndex , const int32 ChunkIndex )
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedFlowDataComponent
		         , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).DeinitializeChunkData ( );
}

void ULFPChunkedFlowDataComponent::InitializeRegion ( const int32 RegionIndex )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedFlowDataComponent
		         , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	if ( IsRegionInitialized ( RegionIndex ) )
	{
		UE_LOG ( LogChunkedFlowDataComponent
		         , Log , TEXT("%hs : Region ( %i ) already initialized") , __FUNCTION__ , RegionIndex );

		return;
	}

	RegionDataList [ RegionIndex ].InitializeRegionData ( ChunkIndexSize );
}

void ULFPChunkedFlowDataComponent::DeinitializeRegion ( const int32 RegionIndex )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedFlowDataComponent
		         , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	RegionDataList [ RegionIndex ].DeinitializeRegionData ( );
}

const FLFPFlowCellData& ULFPChunkedFlowDataComponent::GetData_Checked ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetData ( DataIndex );
}

TArray < FLFPFlowCellData > ULFPChunkedFlowDataComponent::GetDataList ( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetDataList ( );
}

FLFPFlowCellData ULFPChunkedFlowDataComponent::GetData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedFlowDataComponent
		         , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return FLFPFlowCellData ( );
	}

	return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetData ( DataIndex );
}

void ULFPChunkedFlowDataComponent::SetData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FLFPFlowCellData& NewData )
{
	if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedFlowDataComponent
		         , Warning , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return;
	}

	if ( NewData == RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetData ( DataIndex ) )
	{
		return;
	}

	const FLFPFlowCellData OldData = RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetData ( DataIndex );

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).SetData ( DataIndex , NewData );

	AddFLowChangeEvent ( FLFPFlowChangeEvent ( RegionIndex , ChunkIndex , DataIndex , OldData , NewData ) );
}

bool ULFPChunkedFlowDataComponent::IsDataIndexValid ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	return RegionDataList.IsValidIndex ( RegionIndex ) && RegionDataList [ RegionIndex ].IsChunkIndexValid ( ChunkIndex ) && RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).IsDataIndexValid ( DataIndex );
}

bool ULFPChunkedFlowDataComponent::IsChunkIndexValid ( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return RegionDataList.IsValidIndex ( RegionIndex ) && RegionDataList [ RegionIndex ].IsChunkIndexValid ( ChunkIndex );
}

bool ULFPChunkedFlowDataComponent::IsRegionIndexValid ( const int32 RegionIndex ) const
{
	return RegionDataList.IsValidIndex ( RegionIndex );
}

bool ULFPChunkedFlowDataComponent::IsChunkInitialized ( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return IsChunkIndexValid ( RegionIndex , ChunkIndex ) && RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).IsInitialized ( );
}

bool ULFPChunkedFlowDataComponent::IsRegionInitialized ( const int32 RegionIndex ) const
{
	return IsRegionIndexValid ( RegionIndex ) && RegionDataList [ RegionIndex ].IsInitialized ( );
}

int32 ULFPChunkedFlowDataComponent::GetDataIndexSize ( ) const
{
	return DataIndexSize;
}

int32 ULFPChunkedFlowDataComponent::GetChunkIndexSize ( ) const
{
	return ChunkIndexSize;
}

int32 ULFPChunkedFlowDataComponent::GetRegionIndexSize ( ) const
{
	return RegionIndexSize;
}

void ULFPChunkedFlowDataComponent::AddFLowChangeEvent ( const FLFPFlowChangeEvent& NewEvent )
{
	FlowChangeEventList.Add ( NewEvent );

	if ( FlowChangeEventHandle.IsValid ( ) )
	{
		return;
	}

	FlowChangeEventHandle = GetWorld ( )->GetTimerManager ( ).SetTimerForNextTick ( this , &ULFPChunkedFlowDataComponent::BroadcastFlowChangeEvent );
}

void ULFPChunkedFlowDataComponent::BroadcastFlowChangeEvent ( )
{
	OnFlowChanged.Broadcast ( FlowChangeEventList );

	FlowChangeEventList.Reset ( );
	FlowChangeEventHandle.Invalidate ( );
}
