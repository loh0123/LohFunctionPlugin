// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MeshCardBuild.h"
#include "Components/DynamicMeshComponent.h"
#include "Subsystem/LFPMarchingWorldSubsystem.h"
#include "LFPMarchingMeshComponent.generated.h"

class ULFPMarchingData;

struct FLFPMarchingRendererFaceDirection
{
	FLFPMarchingRendererFaceDirection ( FIntVector F , FIntVector R , FIntVector U ) : Forward ( F ), Right ( R ), Up ( U )
	{
	}

	FIntVector Forward , Right , Up = FIntVector::NoneValue;

public:

	FORCEINLINE void SetAxis ( FVector3f& X , FVector3f& Y , FVector3f& Z ) const
	{
		X = FVector3f ( Forward );
		Y = FVector3f ( Right );
		Z = FVector3f ( Up );
	}
};

namespace LFPMarchingRenderConstantData
{
	static const TArray < FRotator > VertexRotationList =
	{
		FRotator ( 0.0f , 0.0f , 0.0f ) , FRotator ( 90.0f , 0.0f , 0.0f ) , FRotator ( 90.0f , 270.0f , 0.0f ) , FRotator ( 180.0f , 0.0f , 0.0f ) , FRotator ( 90.0f , 180.0f , 0.0f ) , FRotator ( 90.0f , 90.0f , 0.0f )
	};

	static const TArray < FLFPMarchingRendererFaceDirection > FaceDirection = {
		FLFPMarchingRendererFaceDirection ( FIntVector ( 1 , 0 , 0 ) , FIntVector ( 0 , 1 , 0 ) , FIntVector ( 0 , 0 , 1 ) ) , FLFPMarchingRendererFaceDirection ( FIntVector ( 0 , 0 , 1 ) , FIntVector ( 0 , 1 , 0 ) , FIntVector ( -1 , 0 , 0 ) ) , FLFPMarchingRendererFaceDirection ( FIntVector ( 0 , 0 , 1 ) , FIntVector ( 1 , 0 , 0 ) , FIntVector ( 0 , 1 , 0 ) ) , FLFPMarchingRendererFaceDirection ( FIntVector ( -1 , 0 , 0 ) , FIntVector ( 0 , 1 , 0 ) , FIntVector ( 0 , 0 , -1 ) ) , FLFPMarchingRendererFaceDirection ( FIntVector ( 0 , 0 , 1 ) , FIntVector ( 0 , -1 , 0 ) , FIntVector ( 1 , 0 , 0 ) ) , FLFPMarchingRendererFaceDirection ( FIntVector ( 0 , 0 , 1 ) , FIntVector ( -1 , 0 , 0 ) , FIntVector ( 0 , -1 , 0 ) )
	};

	static const TArray < FIntVector > FaceLoopDirectionList = {
		FIntVector ( 0 , 1 , 2 ) , FIntVector ( 2 , 1 , 0 ) , FIntVector ( 2 , 0 , 1 ) , FIntVector ( 0 , 1 , 2 ) , FIntVector ( 2 , 1 , 0 ) , FIntVector ( 2 , 0 , 1 )
	};

	static const TArray < int32 > SurfaceDirectionID = {
		5 , 0 , 3 , 4 , 1 , 2
	};
};

USTRUCT ( )
struct FLFPMarchingPassData
{
	GENERATED_BODY ( )

public:

	bool       bNeedCollision              = false;
	bool       bIsChunkFaceCullingDisable  = false;
	bool       bIsRegionFaceCullingDisable = false;
	bool       bSimplify                   = false;
	int32      LODIndex                    = 0;
	FVector    MeshFullSize                = FVector ( );
	FIntVector DataSize                    = FIntVector ( );
	float      BoundExpand                 = 0.0f;
	FDateTime  StartTime                   = FDateTime ( );

	UPROPERTY ( )
	TObjectPtr < ULFPMarchingData > RenderSetting = nullptr;
};

USTRUCT ( )
struct FLFPMarchingThreadData
{
	GENERATED_BODY ( )

public:

	FDynamicMesh3 MeshData = FDynamicMesh3 ( );

	TArray < FLumenCardBuildData > LumenCardData = TArray < FLumenCardBuildData > ( );
	FBox                           LumenBound    = FBox ( );

	TArray < FKBoxElem > CollisionBoxElems;

	FDateTime StartTime = FDateTime ( );
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam ( FLFPOnMarchingMeshGenerateEvent , UDynamicMeshComponent* , Component );

UCLASS ( ClassGroup=(Custom) , EditInlineNew , meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGINMARCHING_API ULFPMarchingMeshComponent : public UDynamicMeshComponent
{
	GENERATED_BODY ( )

public:

	// Sets default values for this component's properties
	ULFPMarchingMeshComponent ( );

protected:

	// Called when the game starts
	virtual void BeginPlay ( ) override;

	virtual void EndPlay ( const EEndPlayReason::Type EndPlayReason ) override;

public:

	// Called every frame
	virtual void TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;

public:

	UPROPERTY ( BlueprintAssignable )
	FLFPOnMarchingMeshGenerateEvent OnMeshRebuilding;

	UPROPERTY ( BlueprintAssignable )
	FLFPOnMarchingMeshGenerateEvent OnMeshGenerated;

	UPROPERTY ( BlueprintAssignable )
	FLFPOnMarchingMeshGenerateEvent OnDistanceFieldRebuilding;

	UPROPERTY ( BlueprintAssignable )
	FLFPOnMarchingMeshGenerateEvent OnDistanceFieldGenerated;

protected:

	UPROPERTY ( EditAnywhere , Category="Setting" )
	TObjectPtr < ULFPMarchingData > RenderSetting = nullptr;

	UPROPERTY ( EditAnywhere , Category="Setting" )
	FGameplayTag HandleTag = FGameplayTag::EmptyTag;

	UPROPERTY ( EditAnywhere , Category="Setting" )
	float DistanceFieldResolutionScale = 1.0f;

	UPROPERTY ( EditAnywhere , Category="Setting" )
	float BoundExpand = 25.0f;

	UPROPERTY ( EditAnywhere , Category="Setting" )
	bool bForceTwoSide = true;

	UPROPERTY ( EditAnywhere , Category="Setting" )
	bool bOverrideBoxCollision = true;

protected:

	UPROPERTY ( Transient )
	TObjectPtr < class ULFPGridTagDataComponent > DataComponent = nullptr;

	UPROPERTY ( Transient )
	int32 RegionIndex = INDEX_NONE;

	UPROPERTY ( Transient )
	int32 ChunkIndex = INDEX_NONE;

public:

	UFUNCTION ( BlueprintCallable , Category="LFPMarchingMeshComponent" )
	FORCEINLINE FIntVector GetDataSize ( ) const;

	UFUNCTION ( BlueprintCallable , Category="LFPMarchingMeshComponent" )
	FORCEINLINE int32 GetDataNum ( ) const;

	UFUNCTION ( BlueprintCallable , Category="LFPMarchingMeshComponent" )
	FORCEINLINE FVector GetMeshSize ( ) const;

	UFUNCTION ( BlueprintCallable , Category="LFPMarchingMeshComponent" )
	FORCEINLINE bool IsDataComponentValid ( ) const;

	UFUNCTION ( BlueprintCallable , Category="LFPMarchingMeshComponent" )
	FORCEINLINE void GetFaceCullingSetting ( bool& bIsChunkFaceCullingDisable , bool& bIsRegionFaceCullingDisable ) const;

protected:

	UFUNCTION ( )
	FORCEINLINE uint8 GetMarchingID ( const FIntVector& Offset ) const;

public:

	UFUNCTION ( BlueprintCallable , Category="LFPVoxelRender" )
	void Initialize ( class ULFPGridTagDataComponent* NewDataComponent , const int32 NewRegionIndex , const int32 NewChunkIndex , const bool bClearMesh );

	UFUNCTION ( BlueprintCallable , Category="LFPVoxelRender" )
	void Uninitialize ( );

public:

	UFUNCTION ( BlueprintCallable , Category = "LFPVoxelRender" )
	void ClearRender ( );

	UFUNCTION ( BlueprintCallable , Category = "LFPVoxelRender" )
	bool UpdateRender ( const bool bSimplify = false , const int32 LODIndex = 0 );

public:

	UFUNCTION ( BlueprintCallable , Category = "LFPVoxelRender" )
	void SetDistanceFieldResolution ( const float NewResolutionScale , const bool bDeferUpdate = false );

protected:

	virtual void RebuildPhysicsData ( ) override;

protected:

	// Add Mesh Fill
	virtual void UpdateDistanceField ( ) override;

protected:

	virtual FPrimitiveSceneProxy* CreateSceneProxy ( ) override;

private:

	std::atomic < bool > bUpdatingThreadData = false;

	FCriticalSection ThreadDataLock;

	TSharedPtr < FLFPMarchingThreadData > LocalThreadData = nullptr;

	TAsyncMarchingData MeshComputeData = TAsyncMarchingData ( this );

	static TUniquePtr < FLFPMarchingThreadData > ComputeNewMarchingMesh_TaskFunction ( FProgressCancel& Progress , const TBitArray < >& SolidList , const FLFPMarchingPassData& PassData );

	void ComputeNewMarchingMesh_Completed ( TUniquePtr < FLFPMarchingThreadData > ThreadData , TQueue < TFunction < void  ( ) > , EQueueMode::Mpsc >& GameThreadJob );

private:

	std::atomic < bool > bUpdatingDistanceFieldData = false;

	TAsyncMarchingData DistanceFieldComputeData = TAsyncMarchingData ( this );

	// Modify to use ParallelFor
	static TUniquePtr < FDistanceFieldVolumeData > ComputeNewDistanceField_TaskFunctionV2 ( FProgressCancel& Progress , const FDynamicMesh3& Mesh , const bool bGenerateAsIfTwoSided , const float CurrentDistanceFieldResolutionScale );

	// Add Safety
	void ComputeNewDistanceFieldData_Completed ( TUniquePtr < FDistanceFieldVolumeData > NewData , TQueue < TFunction < void  ( ) > , EQueueMode::Mpsc >& GameThreadJob );
};
