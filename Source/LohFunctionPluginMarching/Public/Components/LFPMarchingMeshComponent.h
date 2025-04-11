// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MeshCardBuild.h"
#include "Components/DynamicMeshComponent.h"
#include "LFPMarchingMeshComponent.generated.h"

class ULFPMarchingData;

struct FLFPMarchingRendererFaceDirection
{
	FLFPMarchingRendererFaceDirection( FIntVector F , FIntVector R , FIntVector U ) :
		Forward(F), Right(R), Up(U)
	{
	}

	FIntVector Forward , Right , Up = FIntVector::NoneValue;

public:

	FORCEINLINE void SetAxis( FVector3f& X , FVector3f& Y , FVector3f& Z ) const
	{
		X = FVector3f(Forward);
		Y = FVector3f(Right);
		Z = FVector3f(Up);
	}
};

namespace LFPMarchingRenderConstantData
{
	static const TArray< FRotator > VertexRotationList =
		{
			FRotator(0.0f, 0.0f, 0.0f)
			, FRotator(90.0f, 0.0f, 0.0f)
			, FRotator(90.0f, 270.0f, 0.0f)
			, FRotator(180.0f, 0.0f, 0.0f)
			, FRotator(90.0f, 180.0f, 0.0f)
			, FRotator(90.0f, 90.0f, 0.0f)
		};

	static const TArray< FLFPMarchingRendererFaceDirection > FaceDirection = {
			FLFPMarchingRendererFaceDirection(FIntVector(1, 0, 0), FIntVector(0, 1, 0), FIntVector(0, 0, 1))
			, FLFPMarchingRendererFaceDirection(FIntVector(0, 0, 1), FIntVector(0, 1, 0), FIntVector(-1, 0, 0))
			, FLFPMarchingRendererFaceDirection(FIntVector(0, 0, 1), FIntVector(1, 0, 0), FIntVector(0, 1, 0))
			, FLFPMarchingRendererFaceDirection(FIntVector(-1, 0, 0), FIntVector(0, 1, 0), FIntVector(0, 0, -1))
			, FLFPMarchingRendererFaceDirection(FIntVector(0, 0, 1), FIntVector(0, -1, 0), FIntVector(1, 0, 0))
			, FLFPMarchingRendererFaceDirection(FIntVector(0, 0, 1), FIntVector(-1, 0, 0), FIntVector(0, -1, 0))
		};

	static const TArray< FIntVector > FaceLoopDirectionList = {
			FIntVector(0, 1, 2)
			, FIntVector(2, 1, 0)
			, FIntVector(2, 0, 1)
			, FIntVector(0, 1, 2)
			, FIntVector(2, 1, 0)
			, FIntVector(2, 0, 1)
		};

	static const TArray< int32 > SurfaceDirectionID = {
			5
			, 0
			, 3
			, 4
			, 1
			, 2
		};
};

struct FLFPMarchingPassData
{
public:

	bool       bNeedCollision              = false;
	bool       bIsChunkFaceCullingDisable  = false;
	bool       bIsRegionFaceCullingDisable = false;
	FVector    MarchingMeshFullSize        = FVector();
	FIntVector RealGridSize                = FIntVector();
	int32      RealIndexSize               = INDEX_NONE;
	float      BoundExpand                 = 0.0f;
	FDateTime  StartTime                   = FDateTime();

	ULFPMarchingData* RenderSetting = nullptr;
};

struct FLFPMarchingThreadData
{
public:

	FDynamicMesh3 MeshData = FDynamicMesh3();

	TArray< FLumenCardBuildData > LumenCardData = TArray< FLumenCardBuildData >();
	FBox                          LumenBound    = FBox();

	TArray< FKBoxElem > CollisionBoxElems;

	FDateTime StartTime = FDateTime();
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLFPOnMarchingMeshGenerateEvent);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LOHFUNCTIONPLUGINMARCHING_API ULFPMarchingMeshComponent : public UDynamicMeshComponent
{
	GENERATED_BODY()

public:

	// Sets default values for this component's properties
	ULFPMarchingMeshComponent( );

protected:

	// Called when the game starts
	virtual void BeginPlay( ) override;

public:

	// Called every frame
	virtual void TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;

public:

	UPROPERTY(BlueprintAssignable)
	FLFPOnMarchingMeshGenerateEvent OnMarchingMeshRebuild;

	UPROPERTY(BlueprintAssignable)
	FLFPOnMarchingMeshGenerateEvent OnMarchingMeshGenerated;

protected:

	UPROPERTY(EditAnywhere, Category="Setting")
	TObjectPtr< ULFPMarchingData > RenderSetting = nullptr;

	UPROPERTY(EditAnywhere, Category="Setting")
	FGameplayTag HandleTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditAnywhere, Category="Setting")
	float DistanceFieldResolutionScale = 1.0f;

	UPROPERTY(EditAnywhere, Category="Setting")
	float BoundExpand = 25.0f;

	UPROPERTY(EditAnywhere, Category="Setting")
	bool bForceTwoSide = true;

protected:

	UPROPERTY(Transient)
	FGameplayTagContainer HandleTagContainer = FGameplayTagContainer();

	UPROPERTY(Transient)
	TObjectPtr< class ULFPGridTagDataComponent > DataComponent = nullptr;

	UPROPERTY(Transient)
	int32 RegionIndex = INDEX_NONE;

	UPROPERTY(Transient)
	int32 ChunkIndex = INDEX_NONE;

protected:

	UFUNCTION()
	FORCEINLINE FIntVector GetChunkDataSize( ) const;

	UFUNCTION()
	FORCEINLINE int32 GetChunkDataNum( ) const;

	UFUNCTION()
	FORCEINLINE FVector GetMarchingMeshSize( ) const;

	UFUNCTION()
	FORCEINLINE bool IsDataComponentValid( ) const;

	UFUNCTION()
	FORCEINLINE void GetFaceCullingSetting( bool& bIsChunkFaceCullingDisable , bool& bIsRegionFaceCullingDisable ) const;

protected:

	UFUNCTION()
	FORCEINLINE uint8 GetMarchingID( const FIntVector& Offset ) const;

public:

	UFUNCTION(BlueprintCallable, Category="LFPVoxelRender")
	void Initialize( class ULFPGridTagDataComponent* NewDataComponent , const int32 NewRegionIndex , const int32 NewChunkIndex );

	UFUNCTION(BlueprintCallable, Category="LFPVoxelRender")
	void Uninitialize( );

public:

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelRender")
	void ClearMarching( );

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelRender")
	void UpdateMarching( );

	virtual void RebuildPhysicsData( ) override;

protected:

	virtual void UpdateDistanceField( ) override;

protected:

	virtual FPrimitiveSceneProxy* CreateSceneProxy( ) override;

private:

	FLFPMarchingThreadData LocalThreadData = FLFPMarchingThreadData();

	TAsyncComponentDataComputeQueue< FLFPMarchingThreadData > MeshComputeQueue;

	static TUniquePtr< FLFPMarchingThreadData > ComputeNewMarchingMesh_TaskFunction( FProgressCancel& Progress , const TBitArray< >& SolidList , const FLFPMarchingPassData& PassData );

	void ComputeNewMarchingMesh_Completed( TUniquePtr< FLFPMarchingThreadData > ThreadData );

	// Add Safety
	virtual void OnNewDistanceFieldData_Async( TUniquePtr< FDistanceFieldVolumeData > NewData ) override;

	// Internal method to compute the distance field, run in a background thread.
	static TUniquePtr< FDistanceFieldVolumeData > ComputeNewDistanceField_TaskFunctionV2( FProgressCancel& Progress , const FDynamicMesh3& Mesh , bool bGenerateAsIfTwoSided , const float CurrentDistanceFieldResolutionScale );

	// Modify to use ParallelFor
	static bool DynamicMesh_GenerateSignedDistanceFieldVolumeData(
		const FDynamicMesh3&      Mesh ,
		const bool                bGenerateAsIfTwoSided ,
		const float               CurrentDistanceFieldResolutionScale ,
		FDistanceFieldVolumeData& VolumeDataOut ,
		FProgressCancel&          Progress );
};
