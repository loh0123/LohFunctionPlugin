// Copyright (c) 2023-2025 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#include "Components/LFPChunkedTagDataComponent.h"

#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

struct FObjectAndNameAsStringProxyArchive;
DEFINE_LOG_CATEGORY ( LogChunkedTagDataComponent );

// Sets default values for this component's properties
ULFPChunkedTagDataComponent::ULFPChunkedTagDataComponent ( )
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void ULFPChunkedTagDataComponent::BeginPlay ( )
{
	Super::BeginPlay ( );

	RegionDataList.SetNum ( RegionIndexSize );
}

// Called every frame
void ULFPChunkedTagDataComponent::TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent ( DeltaTime , TickType , ThisTickFunction );

	// ...
}

void ULFPChunkedTagDataComponent::SetSize ( const FIntVector& NewSize )
{
	RegionIndexSize = NewSize.X;
	ChunkIndexSize  = NewSize.Y;
	CellIndexSize   = NewSize.Z;

	RegionDataList.Reset ( );
	RegionDataList.SetNum ( RegionIndexSize );
}

////////////////////////////

void ULFPChunkedTagDataComponent::LoadRegion ( const int32 RegionIndex , const FLFPChunkedTagSerializeData& LoadData )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	// Clear region
	RegionDataList [ RegionIndex ] = FLFPTaggedRegionData ( );

	TArray < uint8 > UncompressedData;
	{
		UncompressedData.SetNum ( LoadData.UncompressionSize );
		FMemoryReader Proxy ( LoadData.DataList );
		Proxy.SerializeCompressedNew ( UncompressedData.GetData ( ) , UncompressedData.Num ( ) );
	}

	FMemoryReader                      Proxy ( UncompressedData );
	FObjectAndNameAsStringProxyArchive Archive ( Proxy , true );

	FLFPTaggedRegionData& RegionData = RegionDataList [ RegionIndex ];

	RegionData.StaticStruct ( )->SerializeItem ( Archive , &RegionData , nullptr );

	AddMetaChangeEvent ( FLFPMetaChangeEvent (
	                                          RegionIndex ,
	                                          INDEX_NONE ,
	                                          INDEX_NONE ,
	                                          FGameplayTag::EmptyTag ,
	                                          FInstancedStruct ( )
	                                         )
	                   );
}

void ULFPChunkedTagDataComponent::SaveRegion ( const int32 RegionIndex ,UPARAM ( ref ) FLFPChunkedTagSerializeData& SaveData )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	TArray < uint8 > UncompressedData;
	{
		FMemoryWriter                      Proxy ( UncompressedData );
		FObjectAndNameAsStringProxyArchive Archive ( Proxy , true );
		Archive.bResolveRedirectors = true;

		FLFPTaggedRegionData& RegionData = RegionDataList [ RegionIndex ];

		RegionData.CleanEmptyMetaData ( );

		RegionData.StaticStruct ( )->SerializeItem ( Archive , &RegionData , nullptr );
	}

	SaveData.UncompressionSize = UncompressedData.Num ( );

	{
		FMemoryWriter DiskProxy ( SaveData.DataList );
		DiskProxy.SerializeCompressedNew ( UncompressedData.GetData ( ) , UncompressedData.Num ( ) );
	}

	AddMetaChangeEvent ( FLFPMetaChangeEvent (
	                                          RegionIndex ,
	                                          INDEX_NONE ,
	                                          INDEX_NONE ,
	                                          FGameplayTag::EmptyTag ,
	                                          FInstancedStruct ( )
	                                         )
	                   );
}

////////////////////////////

void ULFPChunkedTagDataComponent::InitializeChunk ( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& FillTag )
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	if ( IsChunkInitialized ( RegionIndex , ChunkIndex ) )
	{
		UE_LOG ( LogChunkedTagDataComponent , Log , TEXT("%hs : Chunk ( %i ) on Region ( %i ) already initialized") , __FUNCTION__ , ChunkIndex , RegionIndex );

		return;
	}

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).InitializeChunkData ( CellIndexSize , FillTag );

	OnInitialized.Broadcast ( RegionIndex , ChunkIndex );

	AddMetaChangeEvent ( FLFPMetaChangeEvent (
	                                          RegionIndex ,
	                                          ChunkIndex ,
	                                          INDEX_NONE ,
	                                          FGameplayTag::EmptyTag ,
	                                          FInstancedStruct ( )
	                                         )
	                   );
}

void ULFPChunkedTagDataComponent::DeinitializeChunk ( const int32 RegionIndex , const int32 ChunkIndex )
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).DeinitializeChunkData ( );

	OnUninitialized.Broadcast ( RegionIndex , ChunkIndex );

	AddMetaChangeEvent ( FLFPMetaChangeEvent (
	                                          RegionIndex ,
	                                          ChunkIndex ,
	                                          INDEX_NONE ,
	                                          FGameplayTag::EmptyTag ,
	                                          FInstancedStruct ( )
	                                         )
	                   );
}

void ULFPChunkedTagDataComponent::InitializeRegion ( const int32 RegionIndex )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	if ( IsRegionInitialized ( RegionIndex ) )
	{
		UE_LOG ( LogChunkedTagDataComponent , Log , TEXT("%hs : Region ( %i ) already initialized") , __FUNCTION__ , RegionIndex );

		return;
	}

	RegionDataList [ RegionIndex ].InitializeRegionData ( ChunkIndexSize );

	OnInitialized.Broadcast ( RegionIndex , INDEX_NONE );

	AddMetaChangeEvent ( FLFPMetaChangeEvent (
	                                          RegionIndex ,
	                                          INDEX_NONE ,
	                                          INDEX_NONE ,
	                                          FGameplayTag::EmptyTag ,
	                                          FInstancedStruct ( )
	                                         )
	                   );
}

void ULFPChunkedTagDataComponent::DeinitializeRegion ( const int32 RegionIndex )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Warning , TEXT("%hs : Invalid Index") , __FUNCTION__ );

		return;
	}

	RegionDataList [ RegionIndex ].DeinitializeRegionData ( );

	OnUninitialized.Broadcast ( RegionIndex , INDEX_NONE );

	AddMetaChangeEvent ( FLFPMetaChangeEvent (
	                                          RegionIndex ,
	                                          INDEX_NONE ,
	                                          INDEX_NONE ,
	                                          FGameplayTag::EmptyTag ,
	                                          FInstancedStruct ( )
	                                         )
	                   );
}

////////////////////////////

TArray < FGameplayTag > ULFPChunkedTagDataComponent::GetCellTagList ( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex );

		return TArray < FGameplayTag > ( );
	}

	return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetCellTagList ( );
}

////////////////////////////

FGameplayTag ULFPChunkedTagDataComponent::GetCellTag ( const int32 RegionIndex , const int32 ChunkIndex , const int32 CellIndex ) const
{
	if ( IsCellIndexValid ( RegionIndex , ChunkIndex , CellIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , CellIndex );

		return FGameplayTag ( );
	}

	return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetCellTag ( CellIndex );
}

void ULFPChunkedTagDataComponent::SetCellTag ( const int32 RegionIndex , const int32 ChunkIndex , const int32 CellIndex , const FGameplayTag& NewCellTag , const bool bSendEvent )
{
	if ( IsCellIndexValid ( RegionIndex , ChunkIndex , CellIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Warning , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , CellIndex );

		return;
	}

	if ( NewCellTag == RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetCellTag ( CellIndex ) )
	{
		return;
	}

	if ( bSendEvent )
	{
		AddTagChangeEvent ( FLFPTagChangeEvent (
		                                        RegionIndex ,
		                                        ChunkIndex ,
		                                        CellIndex ,
		                                        RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetCellTag ( CellIndex )
		                                       )
		                  );
	}

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).SetCellTag ( CellIndex , NewCellTag );
}

const FInstancedStruct& ULFPChunkedTagDataComponent::GetCellMeta ( const int32 RegionIndex , const int32 ChunkIndex , const int32 CellIndex , const FGameplayTag& CellMetaTag ) const
{
	if ( IsCellIndexValid ( RegionIndex , ChunkIndex , CellIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , CellIndex );

		return EmptyStruct;
	}

	if ( const FInstancedStruct* MetaData = RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetCellMeta ( CellIndex , CellMetaTag ) ; MetaData != nullptr )
	{
		return *MetaData;
	}

	return EmptyStruct;
}

void ULFPChunkedTagDataComponent::SetCellMeta ( const int32 RegionIndex , const int32 ChunkIndex , const int32 CellIndex , const FGameplayTag& CellMetaTag , const FInstancedStruct& NewCellMeta , const bool bSendEvent )
{
	if ( IsCellIndexValid ( RegionIndex , ChunkIndex , CellIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Warning , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , CellIndex );

		return;
	}

	if ( bSendEvent )
	{
		const FInstancedStruct* OldMetaPtr = RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetCellMeta ( CellIndex , CellMetaTag );

		AddMetaChangeEvent ( FLFPMetaChangeEvent (
		                                          RegionIndex ,
		                                          ChunkIndex ,
		                                          CellIndex ,
		                                          CellMetaTag ,
		                                          OldMetaPtr != nullptr
		                                          ? *OldMetaPtr
		                                          : FInstancedStruct ( )
		                                         )
		                   );
	}

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetOrAddCellMeta ( CellIndex , CellMetaTag ) = NewCellMeta;
}

void ULFPChunkedTagDataComponent::SetCellMeta ( const int32 RegionIndex , const int32 ChunkIndex , const int32 CellIndex , const FGameplayTag& CellMetaTag , const FConstStructView NewCellMeta , const bool bSendEvent )
{
	if ( IsCellIndexValid ( RegionIndex , ChunkIndex , CellIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Warning , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , CellIndex );

		return;
	}

	if ( bSendEvent )
	{
		const FInstancedStruct* OldMetaPtr = RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetCellMeta ( CellIndex , CellMetaTag );

		AddMetaChangeEvent ( FLFPMetaChangeEvent (
		                                          RegionIndex ,
		                                          ChunkIndex ,
		                                          CellIndex ,
		                                          CellMetaTag ,
		                                          OldMetaPtr != nullptr
		                                          ? *OldMetaPtr
		                                          : FInstancedStruct ( )
		                                         )
		                   );
	}

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetOrAddCellMeta ( CellIndex , CellMetaTag ) = NewCellMeta;
}

void ULFPChunkedTagDataComponent::RemoveCellMeta ( const int32 RegionIndex , const int32 ChunkIndex , const int32 CellIndex , const FGameplayTag& CellMetaTag )
{
	if ( IsCellIndexValid ( RegionIndex , ChunkIndex , CellIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Warning , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , CellIndex );

		return;
	}

	const FInstancedStruct* OldMetaPtr = RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetCellMeta ( CellIndex , CellMetaTag );

	if ( OldMetaPtr == nullptr )
	{
		return;
	}

	const FInstancedStruct OldMeta = OldMetaPtr != nullptr
	                                 ? *OldMetaPtr
	                                 : FInstancedStruct ( );

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).RemoveCellMeta ( CellIndex , CellMetaTag );

	AddMetaChangeEvent ( FLFPMetaChangeEvent ( RegionIndex , ChunkIndex , CellIndex , CellMetaTag , OldMeta ) );
}

////////////////////////////

FGameplayTag ULFPChunkedTagDataComponent::GetChunkTag ( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex );

		return FGameplayTag ( );
	}

	return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetChunkTag ( );
}

void ULFPChunkedTagDataComponent::SetChunkTag ( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& NewChunkTag , const bool bSendEvent )
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Warning , TEXT("%hs : Invalid Index ( R : %i , C : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex );

		return;
	}

	if ( NewChunkTag == RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetChunkTag ( ) )
	{
		return;
	}

	if ( bSendEvent )
	{
		AddTagChangeEvent ( FLFPTagChangeEvent (
		                                        RegionIndex ,
		                                        ChunkIndex ,
		                                        INDEX_NONE ,
		                                        RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetChunkTag ( )
		                                       )
		                  );
	}

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).SetChunkTag ( NewChunkTag );
}

const FInstancedStruct& ULFPChunkedTagDataComponent::GetChunkMeta ( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& ChunkMetaTag ) const
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex );

		return EmptyStruct;
	}

	if ( const FInstancedStruct* MetaData = RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetChunkMeta ( ChunkMetaTag ) ; MetaData != nullptr )
	{
		return *MetaData;
	}

	return EmptyStruct;
}

void ULFPChunkedTagDataComponent::SetChunkMeta ( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& ChunkMetaTag , const FInstancedStruct& NewChunkMeta , const bool bSendEvent )
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Warning , TEXT("%hs : Invalid Index ( R : %i , C : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex );

		return;
	}

	if ( bSendEvent )
	{
		const FInstancedStruct* OldMetaPtr = RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetChunkMeta ( ChunkMetaTag );

		AddMetaChangeEvent ( FLFPMetaChangeEvent (
		                                          RegionIndex ,
		                                          ChunkIndex ,
		                                          INDEX_NONE ,
		                                          ChunkMetaTag ,
		                                          OldMetaPtr != nullptr
		                                          ? *OldMetaPtr
		                                          : FInstancedStruct ( ) )
		                   );
	}

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetOrAddChunkMeta ( ChunkMetaTag ) = NewChunkMeta;
}

void ULFPChunkedTagDataComponent::RemoveChunkMeta ( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& ChunkMetaTag )
{
	if ( IsChunkIndexValid ( RegionIndex , ChunkIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Warning , TEXT("%hs : Invalid Index ( R : %i , C : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex );

		return;
	}

	const FInstancedStruct* OldMetaPtr = RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetChunkMeta ( ChunkMetaTag );

	if ( OldMetaPtr == nullptr )
	{
		return;
	}

	const FInstancedStruct OldMeta = OldMetaPtr != nullptr
	                                 ? *OldMetaPtr
	                                 : FInstancedStruct ( );

	RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).RemoveChunkMeta ( ChunkMetaTag );

	AddMetaChangeEvent ( FLFPMetaChangeEvent ( RegionIndex , ChunkIndex , INDEX_NONE , ChunkMetaTag , OldMeta ) );
}

////////////////////////////

FGameplayTag ULFPChunkedTagDataComponent::GetRegionTag ( const int32 RegionIndex ) const
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Verbose , TEXT("%hs : Invalid Index ( R : %i )") , __FUNCTION__ , RegionIndex );

		return FGameplayTag ( );
	}

	return RegionDataList [ RegionIndex ].GetRegionTag ( );
}

void ULFPChunkedTagDataComponent::SetRegionTag ( const int32 RegionIndex , const FGameplayTag& NewRegionTag , const bool bSendEvent )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Warning , TEXT("%hs : Invalid Index ( R : %i )") , __FUNCTION__ , RegionIndex );

		return;
	}

	if ( NewRegionTag == RegionDataList [ RegionIndex ].GetRegionTag ( ) )
	{
		return;
	}

	if ( bSendEvent )
	{
		AddTagChangeEvent ( FLFPTagChangeEvent (
		                                        RegionIndex ,
		                                        INDEX_NONE ,
		                                        INDEX_NONE ,
		                                        RegionDataList [ RegionIndex ].GetRegionTag ( )
		                                       )
		                  );
	}


	RegionDataList [ RegionIndex ].SetRegionTag ( NewRegionTag );
}

const FInstancedStruct& ULFPChunkedTagDataComponent::GetRegionMeta ( const int32 RegionIndex , const FGameplayTag& RegionMetaTag ) const
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Verbose , TEXT("%hs : Invalid Index ( R : %i )") , __FUNCTION__ , RegionIndex );

		return EmptyStruct;
	}

	if ( const FInstancedStruct* MetaData = RegionDataList [ RegionIndex ].GetRegionMeta ( RegionMetaTag ) ; MetaData != nullptr )
	{
		return *MetaData;
	}

	return EmptyStruct;
}

void ULFPChunkedTagDataComponent::SetRegionMeta ( const int32 RegionIndex , const FGameplayTag& RegionMetaTag , const FInstancedStruct& NewRegionMeta , const bool bSendEvent )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Warning , TEXT("%hs : Invalid Index ( R : %i )") , __FUNCTION__ , RegionIndex );

		return;
	}

	if ( bSendEvent )
	{
		const FInstancedStruct* OldMetaPtr = RegionDataList [ RegionIndex ].GetRegionMeta ( RegionMetaTag );

		AddMetaChangeEvent ( FLFPMetaChangeEvent (
		                                          RegionIndex ,
		                                          INDEX_NONE ,
		                                          INDEX_NONE ,
		                                          RegionMetaTag ,
		                                          OldMetaPtr != nullptr
		                                          ? *OldMetaPtr
		                                          : FInstancedStruct ( )
		                                         )
		                   );
	}

	RegionDataList [ RegionIndex ].GetOrAddRegionMeta ( RegionMetaTag ) = NewRegionMeta;
}

void ULFPChunkedTagDataComponent::RemoveRegionMeta ( const int32 RegionIndex , const FGameplayTag& RegionMetaTag )
{
	if ( IsRegionIndexValid ( RegionIndex ) == false )
	{
		UE_LOG ( LogChunkedTagDataComponent , Warning , TEXT("%hs : Invalid Index ( R : %i )") , __FUNCTION__ , RegionIndex );

		return;
	}

	const FInstancedStruct* OldMetaPtr = RegionDataList [ RegionIndex ].GetRegionMeta ( RegionMetaTag );

	if ( OldMetaPtr == nullptr )
	{
		return;
	}

	const FInstancedStruct OldMeta = OldMetaPtr != nullptr
	                                 ? *OldMetaPtr
	                                 : FInstancedStruct ( );

	RegionDataList [ RegionIndex ].RemoveRegionMeta ( RegionMetaTag );

	AddMetaChangeEvent ( FLFPMetaChangeEvent ( RegionIndex , INDEX_NONE , INDEX_NONE , RegionMetaTag , OldMeta ) );
}

////////////////////////////

bool ULFPChunkedTagDataComponent::IsCellIndexValid ( const int32 RegionIndex , const int32 ChunkIndex , const int32 CellIndex ) const
{
	return RegionDataList.IsValidIndex ( RegionIndex ) && RegionDataList [ RegionIndex ].IsChunkIndexValid ( ChunkIndex ) && RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).IsCellIndexValid ( CellIndex );
}

bool ULFPChunkedTagDataComponent::IsChunkIndexValid ( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return RegionDataList.IsValidIndex ( RegionIndex ) && RegionDataList [ RegionIndex ].IsChunkIndexValid ( ChunkIndex );
}

bool ULFPChunkedTagDataComponent::IsRegionIndexValid ( const int32 RegionIndex ) const
{
	return RegionDataList.IsValidIndex ( RegionIndex );
}

bool ULFPChunkedTagDataComponent::IsChunkInitialized ( const int32 RegionIndex , const int32 ChunkIndex ) const
{
	return IsChunkIndexValid ( RegionIndex , ChunkIndex ) && RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).IsInitialized ( );
}

bool ULFPChunkedTagDataComponent::IsRegionInitialized ( const int32 RegionIndex ) const
{
	return IsRegionIndexValid ( RegionIndex ) && RegionDataList [ RegionIndex ].IsInitialized ( );
}

int32 ULFPChunkedTagDataComponent::GetCellIndexSize ( ) const
{
	return CellIndexSize;
}

int32 ULFPChunkedTagDataComponent::GetChunkIndexSize ( ) const
{
	return ChunkIndexSize;
}

int32 ULFPChunkedTagDataComponent::GetRegionIndexSize ( ) const
{
	return RegionIndexSize;
}

void ULFPChunkedTagDataComponent::AddTagChangeEvent ( const FLFPTagChangeEvent& NewEvent )
{
	TagChangeEventList.Add ( NewEvent );

	if ( TagChangeEventHandle.IsValid ( ) == false )
	{
		TagChangeEventHandle = GetWorld ( )->GetTimerManager ( ).SetTimerForNextTick ( this , &ULFPChunkedTagDataComponent::BroadcastTagChangeEvent );
	}
}

void ULFPChunkedTagDataComponent::AddMetaChangeEvent ( const FLFPMetaChangeEvent& NewEvent )
{
	MetaChangeEventList.Add ( NewEvent );

	if ( MetaChangeEventHandle.IsValid ( ) == false )
	{
		MetaChangeEventHandle = GetWorld ( )->GetTimerManager ( ).SetTimerForNextTick ( this , &ULFPChunkedTagDataComponent::BroadcastTagChangeEvent );
	}
}

void ULFPChunkedTagDataComponent::BroadcastTagChangeEvent ( )
{
	OnTagChanged.Broadcast ( TagChangeEventList );

	TagChangeEventList.Reset ( );
	TagChangeEventHandle.Invalidate ( );
}

void ULFPChunkedTagDataComponent::BroadcastMetaChangeEvent ( )
{
	OnMetaChanged.Broadcast ( MetaChangeEventList );

	MetaChangeEventList.Reset ( );
	MetaChangeEventHandle.Invalidate ( );
}

const FInstancedStruct ULFPChunkedTagDataComponent::EmptyStruct = FInstancedStruct ( );
