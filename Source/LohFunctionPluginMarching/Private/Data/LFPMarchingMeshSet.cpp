// Copyright (c) 2023-2025 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#include "Data/LFPMarchingMeshSet.h"

#include "StaticMeshLODResourcesToDynamicMesh.h"
#include "DynamicMesh/Operations/MergeCoincidentMeshEdges.h"
#include "Library/LFPMarchingFunctionLibrary.h"
#include "UObject/ObjectSaveContext.h"

const FDynamicMesh3* ULFPMarchingMeshSet::GetDynamicMesh ( const int32 MeshIndex , const int32 LODIndex ) const
{
	if ( DynamicMeshLODCount <= 0 )
	{
		return nullptr;
	}

	const int32 DynamicIndex = ( MeshIndex * DynamicMeshLODCount ) + FMath::Clamp ( LODIndex , 0 , DynamicMeshLODCount - 1 );

	return MappingDynamicMeshList.IsValidIndex ( DynamicIndex ) ? &MappingDynamicMeshList [ DynamicIndex ] : nullptr;
}

const TArray < FDynamicMesh3 >& ULFPMarchingMeshSet::GetDynamicMeshList ( ) const
{
	return MappingDynamicMeshList;
}

void ULFPMarchingMeshSet::GenerateDynamicMeshList ( )
{
	MappingDynamicMeshList.SetNum ( MappingMeshList.Num ( ) * DynamicMeshLODCount );\

	TotalDynamicMeshLODAmount = 0;

	for ( int32 LODIndex = 0 ; LODIndex < DynamicMeshLODCount ; ++LODIndex )
	{
		for ( int32 MeshIndex = 0 ; MeshIndex < MappingMeshList.Num ( ) ; ++MeshIndex )
		{
			TotalDynamicMeshLODAmount += 1;

			const UStaticMesh* MeshData = MappingMeshList [ MeshIndex ].LoadSynchronous ( );

			if ( IsValid ( MeshData ) == false )
			{
				continue;
			}

			if ( MeshData->bAllowCPUAccess == false )
			{
				continue;
			}

			if ( const FStaticMeshRenderData* RenderData = MeshData->GetRenderData ( ) ; RenderData != nullptr )
			{
				if ( const FStaticMeshLODResources* LODData = RenderData->GetCurrentFirstLOD ( LODIndex ) ; LODData != nullptr )
				{
					FDynamicMesh3& NewMeshData = MappingDynamicMeshList [ ( MeshIndex * DynamicMeshLODCount ) + LODIndex ];

					UE::Geometry::FStaticMeshLODResourcesToDynamicMesh::ConversionOptions ConvertOptions;

					UE::Geometry::FStaticMeshLODResourcesToDynamicMesh Converter;
					Converter.Convert ( LODData , ConvertOptions , NewMeshData );

					UE::Geometry::FMergeCoincidentMeshEdges Welder ( &NewMeshData );
					Welder.MergeVertexTolerance = 1.0f;
					Welder.OnlyUniquePairs      = false;
					Welder.Apply ( );

					NewMeshData.CompactInPlace ( nullptr );
				}
			}
		}
	}
}

bool ULFPMarchingMeshSet::IsDynamicMeshListValid ( ) const
{
	return MappingDynamicMeshList.Num ( ) == ( MappingMeshList.Num ( ) * DynamicMeshLODCount );
}

TArray < UStaticMesh* > ULFPMarchingMeshSet::GetMeshList ( ) const
{
	TArray < UStaticMesh* > LoadedList;

	LoadedList.Reserve ( MappingMeshList.Num ( ) );

	for ( const auto& MeshSoftPtr : MappingMeshList )
	{
		LoadedList.Add ( MeshSoftPtr.LoadSynchronous ( ) );
	}

	return LoadedList;
}

FLFPMarchingMeshMappingData ULFPMarchingMeshSet::GetMappingData ( const uint8 MarchingID ) const
{
	return MappingDataList.Contains ( MarchingID )
	       ? MappingDataList.FindChecked ( MarchingID )
	       : FLFPMarchingMeshMappingData ( );
}

void ULFPMarchingMeshSet::PostLoad ( )
{
	GenerateDynamicMeshList ( );

	Super::PostLoad ( );
}

void ULFPMarchingMeshSet::PreSave ( FObjectPreSaveContext SaveContext )
{
	MappingMeshList.Empty ( MeshDataList.Num ( ) );
	MappingDataList.Empty ( 255 );
	MappingDynamicMeshList.Empty ( MeshDataList.Num ( ) );

	for ( const FLFPMarchingSingleMeshData& SingelMeshData : MeshDataList )
	{
		if ( SingelMeshData.Mesh.IsNull ( ) )
		{
			continue;
		}

		const int32 MeshID = MappingMeshList.Add ( SingelMeshData.Mesh );

		for ( const auto& RotationData : SingelMeshData.MarchingRotationMap )
		{
			MappingDataList.Add ( RotationData.Key , FLFPMarchingMeshMappingData ( MeshID , RotationData.Value ) );
		}
	}

	GenerateDynamicMeshList ( );

	Super::PreSave ( SaveContext );
}

void ULFPMarchingMeshSet::RotateXPlus ( )
{
	if ( const int32 MeshDataIndex = MeshDataList.IndexOfByKey ( EditMesh ) ; MeshDataIndex != INDEX_NONE )
	{
		if ( EditRotation.X++ ; EditRotation.X > 3 )
		{
			EditRotation.X = 0;
		}

		EditID = ULFPMarchingFunctionLibrary::RotateMarchingIDByX ( EditID , false );

		MeshDataList [ MeshDataIndex ].MarchingRotationMap.Add ( EditID , EditRotation );
	}
}

void ULFPMarchingMeshSet::RotateXNeg ( )
{
	if ( const int32 MeshDataIndex = MeshDataList.IndexOfByKey ( EditMesh ) ; MeshDataIndex != INDEX_NONE )
	{
		if ( EditRotation.X-- ; EditRotation.X < 0 )
		{
			EditRotation.X = 3;
		}

		EditID = ULFPMarchingFunctionLibrary::RotateMarchingIDByX ( EditID , true );

		MeshDataList [ MeshDataIndex ].MarchingRotationMap.Add ( EditID , EditRotation );
	}
}

void ULFPMarchingMeshSet::RotateYPlus ( )
{
	if ( const int32 MeshDataIndex = MeshDataList.IndexOfByKey ( EditMesh ) ; MeshDataIndex != INDEX_NONE )
	{
		if ( EditRotation.Y++ ; EditRotation.Y > 3 )
		{
			EditRotation.Y = 0;
		}

		EditID = ULFPMarchingFunctionLibrary::RotateMarchingIDByY ( EditID , false );

		MeshDataList [ MeshDataIndex ].MarchingRotationMap.Add ( EditID , EditRotation );
	}
}

void ULFPMarchingMeshSet::RotateYNeg ( )
{
	if ( const int32 MeshDataIndex = MeshDataList.IndexOfByKey ( EditMesh ) ; MeshDataIndex != INDEX_NONE )
	{
		if ( EditRotation.Y-- ; EditRotation.Y < 0 )
		{
			EditRotation.Y = 3;
		}

		EditID = ULFPMarchingFunctionLibrary::RotateMarchingIDByY ( EditID , true );

		MeshDataList [ MeshDataIndex ].MarchingRotationMap.Add ( EditID , EditRotation );
	}
}

void ULFPMarchingMeshSet::RotateZPlus ( )
{
	if ( const int32 MeshDataIndex = MeshDataList.IndexOfByKey ( EditMesh ) ; MeshDataIndex != INDEX_NONE )
	{
		if ( EditRotation.Z++ ; EditRotation.Z > 3 )
		{
			EditRotation.Z = 0;
		}

		EditID = ULFPMarchingFunctionLibrary::RotateMarchingIDByZ ( EditID , false );

		MeshDataList [ MeshDataIndex ].MarchingRotationMap.Add ( EditID , EditRotation );
	}
}

void ULFPMarchingMeshSet::RotateZNeg ( )
{
	if ( const int32 MeshDataIndex = MeshDataList.IndexOfByKey ( EditMesh ) ; MeshDataIndex != INDEX_NONE )
	{
		if ( EditRotation.Z-- ; EditRotation.Z < 0 )
		{
			EditRotation.Z = 3;
		}

		EditID = ULFPMarchingFunctionLibrary::RotateMarchingIDByZ ( EditID , true );

		MeshDataList [ MeshDataIndex ].MarchingRotationMap.Add ( EditID , EditRotation );
	}
}

void ULFPMarchingMeshSet::RotateXFull ( )
{
	for ( int32 Index = 0 ; Index <= 4 ; Index++ )
	{
		RotateXPlus ( );
	}
}

void ULFPMarchingMeshSet::RotateYFull ( )
{
	for ( int32 Index = 0 ; Index <= 4 ; Index++ )
	{
		RotateYPlus ( );
	}
}

void ULFPMarchingMeshSet::RotateZFull ( )
{
	for ( int32 Index = 0 ; Index <= 4 ; Index++ )
	{
		RotateZPlus ( );
	}
}

void ULFPMarchingMeshSet::RotateAll ( )
{
	if ( const int32 MeshDataIndex = MeshDataList.IndexOfByKey ( EditMesh ) ; MeshDataIndex != INDEX_NONE )
	{
		for ( int32 Z = 0 ; Z < 4 ; Z++ )
		{
			for ( int32 Y = 0 ; Y < 4 ; Y++ )
			{
				for ( int32 X = 0 ; X < 4 ; X++ )
				{
					const uint8 NewID = ULFPMarchingFunctionLibrary::RotateMarchingID ( EditID , FIntVector ( X , Y , Z ) );

					if ( MeshDataList [ MeshDataIndex ].MarchingRotationMap.Contains ( NewID ) == false )
					{
						MeshDataList [ MeshDataIndex ].MarchingRotationMap.Add ( NewID , FIntVector ( X , Y , Z ) );
					}
				}
			}
		}
	}
}

void ULFPMarchingMeshSet::RotateAllMesh ( )
{
	for ( FLFPMarchingSingleMeshData& MeshData : MeshDataList )
	{
		MeshData.MarchingRotationMap.Reset ( );

		for ( int32 Z = 0 ; Z < 4 ; Z++ )
		{
			for ( int32 Y = 0 ; Y < 4 ; Y++ )
			{
				for ( int32 X = 0 ; X < 4 ; X++ )
				{
					const uint8 NewID = ULFPMarchingFunctionLibrary::RotateMarchingID ( MeshData.DefaultID , FIntVector ( X , Y , Z ) );

					if ( MeshData.MarchingRotationMap.Contains ( NewID ) == false )
					{
						MeshData.MarchingRotationMap.Add ( NewID , FIntVector ( X , Y , Z ) );
					}
				}
			}
		}
	}
}
