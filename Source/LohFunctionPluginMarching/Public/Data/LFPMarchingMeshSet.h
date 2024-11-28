#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LFPMarchingMeshSet.generated.h"

USTRUCT( BlueprintType )
struct FLFPMarchingMeshMappingData
{
	GENERATED_BODY()

public:

	FLFPMarchingMeshMappingData() = default;
	FLFPMarchingMeshMappingData( const int32& MeshID , const FIntVector& Rotation ) : MeshID( MeshID ) , Rotation( Rotation )
	{
	}

public:

	UPROPERTY( BlueprintReadOnly , EditAnywhere , Category = Default )
	int32 MeshID = INDEX_NONE;

	UPROPERTY( BlueprintReadOnly , EditAnywhere , Category = Default )
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

	/* What mesh and rotation base on Marching ID */
	UPROPERTY( VisibleAnywhere , Category = Default )
	TMap<uint8 , FLFPMarchingMeshMappingData> MappingDataList = TMap<uint8 , FLFPMarchingMeshMappingData>();

public:

	UFUNCTION( BlueprintCallable , Category = Default )
	TArray<UStaticMesh*> GetMeshList() const;

	UFUNCTION( BlueprintCallable , Category = Default )
	FLFPMarchingMeshMappingData GetMappingData( const uint8 MarchingID ) const;

#if WITH_EDITORONLY_DATA  

protected:

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

protected:

	virtual void PreSave( FObjectPreSaveContext SaveContext ) override;

	UFUNCTION( CallInEditor , Category = "Rotation|X" )
	void RotateXPlus();

	UFUNCTION( CallInEditor , Category = "Rotation|X" )
	void RotateXNeg();

	UFUNCTION( CallInEditor , Category = "Rotation|Y" )
	void RotateYPlus();

	UFUNCTION( CallInEditor , Category = "Rotation|Y" )
	void RotateYNeg();

	UFUNCTION( CallInEditor , Category = "Rotation|Z" )
	void RotateZPlus();

	UFUNCTION( CallInEditor , Category = "Rotation|Z" )
	void RotateZNeg();

	UFUNCTION( CallInEditor , Category = "Rotation|Full" )
	void RotateXFull();

	UFUNCTION( CallInEditor , Category = "Rotation|Full" )
	void RotateYFull();

	UFUNCTION( CallInEditor , Category = "Rotation|Full" )
	void RotateZFull();

	UFUNCTION( CallInEditor , Category = "Rotation|Full" )
	void RotateAll();

#endif
};
