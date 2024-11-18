#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LFPMarchingMeshSet.generated.h"

USTRUCT()
struct FLFPMarchingMeshMappingData
{
	GENERATED_BODY()

public:

	FLFPMarchingMeshMappingData() = default;
	FLFPMarchingMeshMappingData( const int32& MeshID , const FIntVector& Rotation ) : MeshID( MeshID ) , Rotation( Rotation )
	{
	}

public:

	UPROPERTY( EditAnywhere , Category = Default )
	int32 MeshID = INDEX_NONE;

	UPROPERTY( EditAnywhere , Category = Default )
	FIntVector Rotation = FIntVector( 0 );
};

USTRUCT()
struct FLFPMarchingSingleMeshData
{
	GENERATED_BODY()

public:

	UPROPERTY( EditAnywhere , Category = Default )
	TSoftObjectPtr<UStaticMesh> Mesh = nullptr;

	UPROPERTY( EditAnywhere , Category = Default )
	TMap<uint8 , FIntVector> MarchingRotationMap = TMap<uint8 , FIntVector>();

public:

	FORCEINLINE bool operator==( const FLFPMarchingSingleMeshData& other ) const
	{
		return other.Mesh == Mesh;
	}

	FORCEINLINE bool operator==( const TSoftObjectPtr<UStaticMesh>& other ) const
	{
		return other == Mesh;
	}
};

UCLASS( Blueprintable )
class LOHFUNCTIONPLUGINMARCHING_API ULFPMarchingMeshSet : public UPrimaryDataAsset
{
	GENERATED_BODY()

protected:

	/* The static mesh use on this set, the index on this array follow MeshDataList */
	UPROPERTY( VisibleAnywhere , Category = Default )
	TArray<TSoftObjectPtr<UStaticMesh>> MappingMeshList = TArray<TSoftObjectPtr<UStaticMesh>>();

	/* Find what mesh and rotation base on Marching ID */
	UPROPERTY( VisibleAnywhere , Category = Default )
	TMap<uint8 , FLFPMarchingMeshMappingData> MappingDataList = TMap<uint8 , FLFPMarchingMeshMappingData>();

#if WITH_EDITORONLY_DATA  

	UPROPERTY( EditAnywhere , Category = Edit , Meta = ( NoElementDuplicate ) )
	TArray<FLFPMarchingSingleMeshData> MeshDataList = TArray<FLFPMarchingSingleMeshData>();

	UPROPERTY( EditAnywhere , Category = Edit , Transient )
	TSoftObjectPtr<UStaticMesh> EditMesh = nullptr;

	UPROPERTY( EditAnywhere , Category = Edit , Transient )
	uint8 EditID = 0;

	UPROPERTY( EditAnywhere , Category = Edit , Transient )
	FIntVector EditRotation = FIntVector( 0 );

#endif

#if WITH_EDITOR

	virtual void PreSave( FObjectPreSaveContext SaveContext ) override;

	UFUNCTION( CallInEditor , Category = Edit )
	void RotateXPlus();

	UFUNCTION( CallInEditor , Category = Edit )
	void RotateXNeg();

	UFUNCTION( CallInEditor , Category = Edit )
	void RotateYPlus();

	UFUNCTION( CallInEditor , Category = Edit )
	void RotateYNeg();

	UFUNCTION( CallInEditor , Category = Edit )
	void RotateZPlus();

	UFUNCTION( CallInEditor , Category = Edit )
	void RotateZNeg();

#endif
};
