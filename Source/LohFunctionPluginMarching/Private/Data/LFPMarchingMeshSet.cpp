#include "Data/LFPMarchingMeshSet.h"
#include "Math/LFPMarchingLibrary.h"
#include "UObject/ObjectSaveContext.h"

TArray<UStaticMesh*> ULFPMarchingMeshSet::GetMeshList() const
{
	TArray<UStaticMesh*> LoadedList;

	LoadedList.Reserve( MappingMeshList.Num() );

	for ( const auto& MeshSolfPtr : MappingMeshList )
	{
		LoadedList.Add( MeshSolfPtr.LoadSynchronous() );
	}

	return LoadedList;
}

FLFPMarchingMeshMappingData ULFPMarchingMeshSet::GetMappingData( const uint8 MarchingID ) const
{
	return MappingDataList.Contains( MarchingID ) ? MappingDataList.FindChecked( MarchingID ) : FLFPMarchingMeshMappingData();
}

void ULFPMarchingMeshSet::PreSave( FObjectPreSaveContext SaveContext )
{
	MappingMeshList.Empty( MeshDataList.Num() );
	MappingDataList.Empty( 255 );

	for ( const FLFPMarchingSingleMeshData& SingelMeshData : MeshDataList )
	{
		if ( SingelMeshData.Mesh.IsNull() )
		{
			continue;
		}

		const int32 MeshID = MappingMeshList.Add( SingelMeshData.Mesh );

		for ( const auto& RotationData : SingelMeshData.MarchingRotationMap )
		{
			MappingDataList.Add( RotationData.Key , FLFPMarchingMeshMappingData( MeshID , RotationData.Value ) );
		}
	}

	Super::PreSave( SaveContext );
}

void ULFPMarchingMeshSet::RotateXPlus()
{
	if ( const int32 MeshDataIndex = MeshDataList.IndexOfByKey( EditMesh ); MeshDataIndex != INDEX_NONE )
	{
		if ( EditRotation.X++; EditRotation.X > 3 )
		{
			EditRotation.X = 0;
		}

		EditID = ULFPMarchingLibrary::RotateMarchingIDByX( EditID , false );

		MeshDataList[ MeshDataIndex ].MarchingRotationMap.Add( EditID , EditRotation );
	}
}

void ULFPMarchingMeshSet::RotateXNeg()
{
	if ( const int32 MeshDataIndex = MeshDataList.IndexOfByKey( EditMesh ); MeshDataIndex != INDEX_NONE )
	{
		if ( EditRotation.X--; EditRotation.X < 0 )
		{
			EditRotation.X = 3;
		}

		EditID = ULFPMarchingLibrary::RotateMarchingIDByX( EditID , true );

		MeshDataList[ MeshDataIndex ].MarchingRotationMap.Add( EditID , EditRotation );
	}
}

void ULFPMarchingMeshSet::RotateYPlus()
{
	if ( const int32 MeshDataIndex = MeshDataList.IndexOfByKey( EditMesh ); MeshDataIndex != INDEX_NONE )
	{
		if ( EditRotation.Y++; EditRotation.Y > 3 )
		{
			EditRotation.Y = 0;
		}

		EditID = ULFPMarchingLibrary::RotateMarchingIDByY( EditID , false );

		MeshDataList[ MeshDataIndex ].MarchingRotationMap.Add( EditID , EditRotation );
	}
}

void ULFPMarchingMeshSet::RotateYNeg()
{
	if ( const int32 MeshDataIndex = MeshDataList.IndexOfByKey( EditMesh ); MeshDataIndex != INDEX_NONE )
	{
		if ( EditRotation.Y--; EditRotation.Y < 0 )
		{
			EditRotation.Y = 3;
		}

		EditID = ULFPMarchingLibrary::RotateMarchingIDByY( EditID , true );

		MeshDataList[ MeshDataIndex ].MarchingRotationMap.Add( EditID , EditRotation );
	}
}

void ULFPMarchingMeshSet::RotateZPlus()
{
	if ( const int32 MeshDataIndex = MeshDataList.IndexOfByKey( EditMesh ); MeshDataIndex != INDEX_NONE )
	{
		if ( EditRotation.Z++; EditRotation.Z > 3 )
		{
			EditRotation.Z = 0;
		}

		EditID = ULFPMarchingLibrary::RotateMarchingIDByZ( EditID , false );

		MeshDataList[ MeshDataIndex ].MarchingRotationMap.Add( EditID , EditRotation );
	}
}

void ULFPMarchingMeshSet::RotateZNeg()
{
	if ( const int32 MeshDataIndex = MeshDataList.IndexOfByKey( EditMesh ); MeshDataIndex != INDEX_NONE )
	{
		if ( EditRotation.Z--; EditRotation.Z < 0 )
		{
			EditRotation.Z = 3;
		}

		EditID = ULFPMarchingLibrary::RotateMarchingIDByZ( EditID , true );

		MeshDataList[ MeshDataIndex ].MarchingRotationMap.Add( EditID , EditRotation );
	}
}

void ULFPMarchingMeshSet::RotateXFull()
{
	for ( int32 Index = 0; Index <= 4; Index++ )
	{
		RotateXPlus();
	}
}

void ULFPMarchingMeshSet::RotateYFull()
{
	for ( int32 Index = 0; Index <= 4; Index++ )
	{
		RotateYPlus();
	}
}

void ULFPMarchingMeshSet::RotateZFull()
{
	for ( int32 Index = 0; Index <= 4; Index++ )
	{
		RotateZPlus();
	}
}

void ULFPMarchingMeshSet::RotateAll()
{
	if ( const int32 MeshDataIndex = MeshDataList.IndexOfByKey( EditMesh ); MeshDataIndex != INDEX_NONE )
	{
		for ( int32 Z = 0; Z < 4; Z++ )
		{
			for ( int32 Y = 0; Y < 4; Y++ )
			{
				for ( int32 X = 0; X < 4; X++ )
				{
					const uint8 NewID = ULFPMarchingLibrary::RotateMarchingID( EditID , FIntVector( X , Y , Z ) );

					if ( MeshDataList[ MeshDataIndex ].MarchingRotationMap.Contains( NewID ) == false )
					{
						MeshDataList[ MeshDataIndex ].MarchingRotationMap.Add( NewID , FIntVector( X , Y , Z ) );
					}
				}
			}
		}
	}
}
