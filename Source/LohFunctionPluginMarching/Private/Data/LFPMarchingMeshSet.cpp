#include "Data/LFPMarchingMeshSet.h"
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
