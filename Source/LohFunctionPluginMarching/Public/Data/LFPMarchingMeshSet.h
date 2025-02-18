// Copyright (c) 2023-2025 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LFPMarchingMeshSet.generated.h"

USTRUCT(BlueprintType)
struct FLFPMarchingMeshMappingData
{
	GENERATED_BODY()

	FLFPMarchingMeshMappingData( ) = default;

	FLFPMarchingMeshMappingData( const int32& MeshID , const FIntVector& Rotation ) :
		MeshID(MeshID), Rotation(Rotation)
	{
	}

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Default)
	int32 MeshID = INDEX_NONE;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Default)
	FIntVector Rotation = FIntVector(0);
};

USTRUCT()
struct FLFPMarchingSingleMeshData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Default)
	TSoftObjectPtr< UStaticMesh > Mesh = nullptr;

	UPROPERTY(EditAnywhere, Category = Default)
	uint8 DefaultID = 0;

	UPROPERTY(EditAnywhere, Category = Default)
	TMap< uint8 , FIntVector > MarchingRotationMap = TMap< uint8 , FIntVector >();

	FORCEINLINE bool operator==( const FLFPMarchingSingleMeshData& other ) const
	{
		return other.Mesh == Mesh;
	}

	FORCEINLINE bool operator==( const TSoftObjectPtr< UStaticMesh >& other ) const
	{
		return other == Mesh;
	}
};

UCLASS(Blueprintable)
class LOHFUNCTIONPLUGINMARCHING_API ULFPMarchingMeshSet : public UPrimaryDataAsset
{
	GENERATED_BODY()

protected:

	/* The static mesh use on this set, the index on this array follow MeshDataList */
	UPROPERTY(VisibleAnywhere, Category = Default)
	TArray< TSoftObjectPtr< UStaticMesh > > MappingMeshList = TArray< TSoftObjectPtr< UStaticMesh > >();

	/* What mesh and rotation base on Marching ID */
	UPROPERTY(VisibleAnywhere, Category = Default)
	TMap< uint8 , FLFPMarchingMeshMappingData > MappingDataList = TMap< uint8 , FLFPMarchingMeshMappingData >();

public:

	UFUNCTION(BlueprintCallable, Category = Default)
	TArray< UStaticMesh* > GetMeshList( ) const;

	UFUNCTION(BlueprintCallable, Category = Default)
	FLFPMarchingMeshMappingData GetMappingData( const uint8 MarchingID ) const;

#if WITH_EDITORONLY_DATA

protected:

	UPROPERTY(EditAnywhere, Category = Edit, Meta = ( NoElementDuplicate ))
	TArray< FLFPMarchingSingleMeshData > MeshDataList = TArray< FLFPMarchingSingleMeshData >();

	UPROPERTY(EditAnywhere, Category = Edit, Transient)
	TSoftObjectPtr< UStaticMesh > EditMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = Edit, Transient)
	uint8 EditID = 0;

	UPROPERTY(EditAnywhere, Category = Edit, Transient)
	FIntVector EditRotation = FIntVector(0);

#endif

#if WITH_EDITOR

	virtual void PreSave( FObjectPreSaveContext SaveContext ) override;

	UFUNCTION(CallInEditor, Category = "Rotation|Select")
	void RotateXPlus( );

	UFUNCTION(CallInEditor, Category = "Rotation|Select")
	void RotateXNeg( );

	UFUNCTION(CallInEditor, Category = "Rotation|Select")
	void RotateYPlus( );

	UFUNCTION(CallInEditor, Category = "Rotation|Select")
	void RotateYNeg( );

	UFUNCTION(CallInEditor, Category = "Rotation|Select")
	void RotateZPlus( );

	UFUNCTION(CallInEditor, Category = "Rotation|Select")
	void RotateZNeg( );

	UFUNCTION(CallInEditor, Category = "Rotation|Select")
	void RotateXFull( );

	UFUNCTION(CallInEditor, Category = "Rotation|Select")
	void RotateYFull( );

	UFUNCTION(CallInEditor, Category = "Rotation|Select")
	void RotateZFull( );

	UFUNCTION(CallInEditor, Category = "Rotation|Select")
	void RotateAll( );

	UFUNCTION(CallInEditor, Category = "Rotation")
	void RotateAllMesh( );

#endif
};
