// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LFPMarchingMeshSet.h"
#include "LFPMarchingData.generated.h"

USTRUCT ( BlueprintType )
struct FLFPMarchingMeshMappingDataV2
{
	GENERATED_BODY ( )

public:

	FLFPMarchingMeshMappingDataV2 ( ) = default;

	FLFPMarchingMeshMappingDataV2 ( const int32& MeshID , const FIntVector& Rotation ) : MeshID ( MeshID ), Rotation ( Rotation )
	{
	}

public:

	UPROPERTY ( BlueprintReadOnly , EditAnywhere , Category = Default )
	int32 MeshID = INDEX_NONE;

	UPROPERTY ( BlueprintReadOnly , EditAnywhere , Category = Default )
	FIntVector Rotation = FIntVector ( 0 );

public:

	FORCEINLINE FRotator GetRotation ( ) const
	{
		return FRotator ( Rotation.Y * 90.0f , Rotation.Z * 90.0f , Rotation.X * 90.0f );
	}
};

USTRUCT ( )
struct FLFPMarchingSingleMeshDataV2
{
	GENERATED_BODY ( )

public:

	UPROPERTY ( EditAnywhere , Category = Default )
	TSoftObjectPtr < UStaticMesh > Mesh = nullptr;

	UPROPERTY ( EditAnywhere , Category = Default )
	uint8 MappingID = 0;

	UPROPERTY ( EditAnywhere , Category = Default )
	TMap < uint8 , FIntVector > SupportRotationList = TMap < uint8 , FIntVector > ( );

	UPROPERTY ( EditAnywhere , Category = Default )
	bool bLockRotationList = false;

public:

	FORCEINLINE bool operator== ( const FLFPMarchingSingleMeshData& other ) const
	{
		return other.Mesh == Mesh;
	}

	FORCEINLINE bool operator== ( const TSoftObjectPtr < UStaticMesh >& other ) const
	{
		return other == Mesh;
	}
};

/**
 * 
 */
UCLASS ( Blueprintable )
class LOHFUNCTIONPLUGINMARCHING_API ULFPMarchingData : public UDataAsset
{
	GENERATED_BODY ( )

protected:

	UPROPERTY ( EditAnywhere , BlueprintReadOnly , Category = "Setting" )
	FIntVector MarchingSize = FIntVector ( 100 );

	UPROPERTY ( EditAnywhere , BlueprintReadOnly , Category = "Setting" )
	bool bDisableChuckFaceCulling = false;

	UPROPERTY ( EditAnywhere , BlueprintReadOnly , Category = "Setting" )
	bool bDisableRegionFaceCulling = false;

protected:

	/* Mesh Data For Component */
	TArray < FDynamicMesh3 > DynamicMeshList = TArray < FDynamicMesh3 > ( );

	/* What mesh and rotation base on Marching ID */
	UPROPERTY ( VisibleAnywhere , Category = Default )
	TMap < uint8 , FLFPMarchingMeshMappingDataV2 > MappingDataList = TMap < uint8 , FLFPMarchingMeshMappingDataV2 > ( );

#if WITH_EDITORONLY_DATA

protected:

	UPROPERTY ( VisibleAnywhere , Category = Report )
	uint8 DynamicMeshAmount = 0;

	UPROPERTY ( VisibleAnywhere , Category = Report )
	TSet < FIntPoint > DuplicateList = TSet < FIntPoint > ( );

	UPROPERTY ( VisibleAnywhere , Category = Report )
	TSet < uint8 > InvalidIDList = TSet < uint8 > ( );

protected:

	UPROPERTY ( EditAnywhere , Category = Edit , Meta = ( NoElementDuplicate ) )
	TArray < FLFPMarchingSingleMeshDataV2 > MeshDataList = TArray < FLFPMarchingSingleMeshDataV2 > ( );

#endif

protected:

	virtual void PostLoad ( ) override;

public:

	FORCEINLINE FVector GetMarchingSize ( ) const { return FVector ( MarchingSize ); }

	FORCEINLINE bool IsChunkFaceCullingDisable ( ) const { return bDisableChuckFaceCulling; }

	FORCEINLINE bool IsRegionFaceCullingDisable ( ) const { return bDisableRegionFaceCulling; }

public:

	const FDynamicMesh3* GetDynamicMesh ( const int32 MeshIndex ) const;

	FLFPMarchingMeshMappingDataV2 GetMappingData ( const uint8 MarchingID ) const;

#if WITH_EDITOR

protected:

	/* Generate All-Possible Rotation For MeshDataList */
	UFUNCTION ( CallInEditor , Category = "Function" )
	void AutoFillRotationList ( );


	/* Fill Up DynamicMeshList And MappingDataList With Updated Data */
	UFUNCTION ( CallInEditor , Category = "Function" )
	void AutoFillMappingDataList ( );

protected:

	UFUNCTION ( )
	FORCEINLINE void GenerateDynamicMeshList ( );

#endif
};
