// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LFPChunkedEntityListDataComponent.h"

#include "Serialization/ArchiveLoadCompressedProxy.h"
#include "Serialization/ArchiveSaveCompressedProxy.h"

DEFINE_LOG_CATEGORY ( LogChunkedEntityListDataComponent );


// Sets default values for this component's properties
ULFPChunkedEntityListDataComponent::ULFPChunkedEntityListDataComponent ( )
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULFPChunkedEntityListDataComponent::BeginPlay ( )
{
	Super::BeginPlay ( );

	// ...
}


// Called every frame
void ULFPChunkedEntityListDataComponent::TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent ( DeltaTime , TickType , ThisTickFunction );

	// ...
}

void ULFPChunkedEntityListDataComponent::SetSize ( const int32& NewRegionSize )
{
	RegionIndexSize = NewRegionSize;

	RegionDataList.Reset ( );
	RegionDataList.SetNum ( RegionIndexSize );
}

void ULFPChunkedEntityListDataComponent::LoadRegion ( const int32 RegionIndex , const FLFPChunkedEntityListSerializeData& LoadData )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedEntityListDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	// Clear region
	RegionDataList [ RegionIndex ] = FLFPEntityListRegionData ( );

	FArchiveLoadCompressedProxy Proxy ( LoadData.DataList , LoadData.CompressionName , ECompressionFlags::COMPRESS_BiasMemory );

	FLFPEntityListRegionData& RegionData = RegionDataList [ RegionIndex ];

	RegionData.StaticStruct ( )->SerializeItem ( Proxy , &RegionData , nullptr );
}

void ULFPChunkedEntityListDataComponent::SaveRegion ( const int32 RegionIndex , FLFPChunkedEntityListSerializeData& SaveData )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedEntityListDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	FArchiveSaveCompressedProxy Proxy ( SaveData.DataList , SaveData.CompressionName , ECompressionFlags::COMPRESS_BiasMemory );

	FLFPEntityListRegionData& RegionData = RegionDataList [ RegionIndex ];

	RegionData.StaticStruct ( )->SerializeItem ( Proxy , &RegionData , nullptr );
}

const TArray < FLFPEntityData >& ULFPChunkedEntityListDataComponent::GetDataList_Checked ( const int32 RegionIndex ) const
{
	return RegionDataList [ RegionIndex ].GetDataList ( );
}

const FLFPEntityData& ULFPChunkedEntityListDataComponent::GetData_Checked ( const int32 RegionIndex , const int32 EntityIndex ) const
{
	return RegionDataList [ RegionIndex ].GetData ( EntityIndex );
}

TArray < uint8 > ULFPChunkedEntityListDataComponent::GetData ( const int32 RegionIndex , const int32 EntityIndex ) const
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		return TArray < uint8 > ( );
	}

	return RegionDataList [ RegionIndex ].GetData ( EntityIndex ).GetData ( );
}

void ULFPChunkedEntityListDataComponent::SetData ( const int32 RegionIndex , const int32 EntityIndex , const TArray < uint8 >& NewData )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		return;
	}

	if ( RegionDataList [ RegionIndex ].IsEntityIndexValid ( EntityIndex ) == false )
	{
		RegionDataList [ RegionIndex ].AllocateEntity ( ).SetData ( NewData );
	}
	else
	{
		RegionDataList [ RegionIndex ].GetData ( EntityIndex ).SetData ( NewData );
	}
}

bool ULFPChunkedEntityListDataComponent::IsDataIndexValid ( const int32 RegionIndex , const int32 EntityIndex ) const
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		return false;
	}

	return RegionDataList [ RegionIndex ].IsEntityIndexValid ( EntityIndex );
}

bool ULFPChunkedEntityListDataComponent::IsRegionIndexValid ( const int32 RegionIndex ) const
{
	return RegionDataList.IsValidIndex ( RegionIndex );
}

int32 ULFPChunkedEntityListDataComponent::GetRegionIndexSize ( ) const
{
	return RegionIndexSize;
}
