#include "Data/LFPMarchingMeshSet.h"
#include "Math/LFPMarchingLibrary.h"
#include "UObject/ObjectSaveContext.h"

void ULFPMarchingMeshSet::PreSave( FObjectPreSaveContext SaveContext )
{
	MappingMeshList.Empty( MeshDataList.Num() );
	MappingDataList.Empty( 255 );

	for ( const FLFPMarchingSingleMeshData& SingelMeshData : MeshDataList )
	{
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
