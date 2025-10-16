// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LFPChunkedStepFlowDataComponent.h"

#include "Serialization/ArchiveLoadCompressedProxy.h"
#include "Serialization/ArchiveSaveCompressedProxy.h"

DEFINE_LOG_CATEGORY ( LogChunkedStepFlowDataComponent );

FLFPStepFlowCellData ULFPChunkedStepFlowDataLibrary::MakeFlowCellData ( const FIntVector FlowVector , const int32 FlowResistant )
{
	FLFPStepFlowCellData ResultData;

	ResultData.SetFlowVectorComponent ( 0 , FlowVector.X );
	ResultData.SetFlowVectorComponent ( 1 , FlowVector.Y );
	ResultData.SetFlowVectorComponent ( 2 , FlowVector.Z );
	ResultData.SetFlowResistant ( FlowResistant );

	return ResultData;
}

FIntVector ULFPChunkedStepFlowDataLibrary::GetFlowCellVelocity ( const FLFPStepFlowCellData& CellData )
{
	return CellData.GetFlowVector ( );
}

int32 ULFPChunkedStepFlowDataLibrary::GetFlowCellResistant ( const FLFPStepFlowCellData& CellData )
{
	return CellData.GetFlowResistant ( );
}


// Sets default values for this component's properties
ULFPChunkedStepFlowDataComponent::ULFPChunkedStepFlowDataComponent ( )
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULFPChunkedStepFlowDataComponent::BeginPlay ( )
{
	Super::BeginPlay ( );

	// ...
}


// Called every frame
void ULFPChunkedStepFlowDataComponent::TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent ( DeltaTime , TickType , ThisTickFunction );

	// ...
}

void ULFPChunkedStepFlowDataComponent::SetSize ( const FIntVector& NewSize )
{
	RegionIndexSize = NewSize.X;
	ChunkIndexSize  = NewSize.Y;
	DataIndexSize   = NewSize.Z;

	RegionDataList.Reset ( );
	RegionDataList.SetNum ( RegionIndexSize );
}

void ULFPChunkedStepFlowDataComponent::LoadRegion ( const int32 RegionIndex , const FLFPChunkedStepFlowSerializeData& LoadData )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedStepFlowDataComponent
		         , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	// Clear region
	RegionDataList [ RegionIndex ] = FLFPStepFlowRegionData ( );

	FArchiveLoadCompressedProxy Proxy ( LoadData.DataList , LoadData.CompressionName , ECompressionFlags::COMPRESS_BiasMemory );

	FLFPStepFlowRegionData& RegionData = RegionDataList [ RegionIndex ];

	RegionData.StaticStruct ( )->SerializeItem ( Proxy , &RegionData , nullptr );
}

void ULFPChunkedStepFlowDataComponent::SaveRegion ( const int32 RegionIndex , FLFPChunkedStepFlowSerializeData& SaveData )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedStepFlowDataComponent
		         , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	FArchiveSaveCompressedProxy Proxy ( SaveData.DataList , SaveData.CompressionName , ECompressionFlags::COMPRESS_BiasMemory );

	FLFPStepFlowRegionData& RegionData = RegionDataList [ RegionIndex ];

	RegionData.StaticStruct ( )->SerializeItem ( Proxy , &RegionData , nullptr );
}

void ULFPChunkedStepFlowDataComponent::InitializeChunk ( const int32 RegionIndex , const int32 ChunkIndex )
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedStepFlowDataComponent
		         , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	if ( IsChunkInitialized ( RegionIndex , ChunkIndex ) )
	{
		UE_LOG ( LogChunkedStepFlowDataComponent
		         , Log , TEXT("%hs : Chunk ( %i ) on Region ( %i ) already initialized") , __FUNCTION__ , ChunkIndex , RegionIndex );

		return;
	}

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).InitializeChunkData ( DataIndexSize );
}

void ULFPChunkedStepFlowDataComponent::DeinitializeChunk ( const int32 RegionIndex , const int32 ChunkIndex )
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedStepFlowDataComponent
		         , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).DeinitializeChunkData ( );
}

void ULFPChunkedStepFlowDataComponent::InitializeRegion ( const int32 RegionIndex )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedStepFlowDataComponent
		         , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	if ( IsRegionInitialized ( RegionIndex ) )
	{
		UE_LOG ( LogChunkedStepFlowDataComponent
		         , Log , TEXT("%hs : Region ( %i ) already initialized") , __FUNCTION__ , RegionIndex );

		return;
	}

	RegionDataList [ RegionIndex ].InitializeRegionData ( ChunkIndexSize );
}

void ULFPChunkedStepFlowDataComponent::DeinitializeRegion ( const int32 RegionIndex )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedStepFlowDataComponent
		         , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	RegionDataList [ RegionIndex ].DeinitializeRegionData ( );
}

const FLFPStepFlowCellData& ULFPChunkedStepFlowDataComponent::GetData_Checked ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetData ( DataIndex );
}

TArray < FLFPStepFlowCellData > ULFPChunkedStepFlowDataComponent::GetDataList ( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetDataList ( );
}

FLFPStepFlowCellData ULFPChunkedStepFlowDataComponent::GetData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedStepFlowDataComponent
		         , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return FLFPStepFlowCellData ( );
	}

	return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetData ( DataIndex );
}

void ULFPChunkedStepFlowDataComponent::SetData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FLFPStepFlowCellData& NewData )
{
	if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedStepFlowDataComponent
		         , Warning , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return;
	}

	if ( NewData == RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetData ( DataIndex ) )
	{
		return;
	}

	const FLFPStepFlowCellData OldData = RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetData ( DataIndex );

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).SetData ( DataIndex , NewData );

	AddFlowChangeEvent ( FLFPStepFlowChangeEvent ( RegionIndex , ChunkIndex , DataIndex , OldData , NewData ) );
}

bool ULFPChunkedStepFlowDataComponent::IsDataIndexValid ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	return RegionDataList.IsValidIndex ( RegionIndex ) && RegionDataList [ RegionIndex ].IsChunkIndexValid ( ChunkIndex ) && RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).IsDataIndexValid ( DataIndex );
}

bool ULFPChunkedStepFlowDataComponent::IsChunkIndexValid ( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return RegionDataList.IsValidIndex ( RegionIndex ) && RegionDataList [ RegionIndex ].IsChunkIndexValid ( ChunkIndex );
}

bool ULFPChunkedStepFlowDataComponent::IsRegionIndexValid ( const int32 RegionIndex ) const
{
	return RegionDataList.IsValidIndex ( RegionIndex );
}

bool ULFPChunkedStepFlowDataComponent::IsChunkInitialized ( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return IsChunkIndexValid ( RegionIndex , ChunkIndex ) && RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).IsInitialized ( );
}

bool ULFPChunkedStepFlowDataComponent::IsRegionInitialized ( const int32 RegionIndex ) const
{
	return IsRegionIndexValid ( RegionIndex ) && RegionDataList [ RegionIndex ].IsInitialized ( );
}

int32 ULFPChunkedStepFlowDataComponent::GetDataIndexSize ( ) const
{
	return DataIndexSize;
}

int32 ULFPChunkedStepFlowDataComponent::GetChunkIndexSize ( ) const
{
	return ChunkIndexSize;
}

int32 ULFPChunkedStepFlowDataComponent::GetRegionIndexSize ( ) const
{
	return RegionIndexSize;
}

void ULFPChunkedStepFlowDataComponent::AddFlowChangeEvent ( const FLFPStepFlowChangeEvent& NewEvent )
{
	FlowChangeEventList.Add ( NewEvent );

	if ( FlowChangeEventHandle.IsValid ( ) )
	{
		return;
	}

	FlowChangeEventHandle = GetWorld ( )->GetTimerManager ( ).SetTimerForNextTick ( this , &ULFPChunkedStepFlowDataComponent::BroadcastFlowChangeEvent );
}

void ULFPChunkedStepFlowDataComponent::BroadcastFlowChangeEvent ( )
{
	OnFlowChanged.Broadcast ( FlowChangeEventList );

	FlowChangeEventList.Reset ( );
	FlowChangeEventHandle.Invalidate ( );
}
