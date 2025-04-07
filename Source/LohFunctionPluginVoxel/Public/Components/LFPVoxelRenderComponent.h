// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Runtime/GeometryFramework/Public/Components/DynamicMeshComponent.h"
#include "LFPVoxelRenderComponent.generated.h"

struct FLFPVoxelRendererFaceDirection
{
	FLFPVoxelRendererFaceDirection( FIntVector F , FIntVector R , FIntVector U ) :
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

namespace LFPVoxelRenderConstantData
{
	static const TArray< FRotator > VertexRotationList =
		{
			FRotator(0.0f, 0.0f, 0.0f)
			, FRotator(90.0f, 0.0f, 0.0f)
			, FRotator(90.0f, 270.0f, 0.0f)
			, FRotator(90.0f, 180.0f, 0.0f)
			, FRotator(90.0f, 90.0f, 0.0f)
			, FRotator(180.0f, 0.0f, 0.0f)
			,
		};

	static const TArray< FLFPVoxelRendererFaceDirection > FaceDirection = {
			FLFPVoxelRendererFaceDirection(FIntVector(1, 0, 0), FIntVector(0, 1, 0), FIntVector(0, 0, 1))
			, FLFPVoxelRendererFaceDirection(FIntVector(0, 0, 1), FIntVector(0, 1, 0), FIntVector(-1, 0, 0))
			, FLFPVoxelRendererFaceDirection(FIntVector(0, 0, 1), FIntVector(1, 0, 0), FIntVector(0, 1, 0))
			, FLFPVoxelRendererFaceDirection(FIntVector(0, 0, 1), FIntVector(0, -1, 0), FIntVector(1, 0, 0))
			, FLFPVoxelRendererFaceDirection(FIntVector(0, 0, 1), FIntVector(-1, 0, 0), FIntVector(0, -1, 0))
			, FLFPVoxelRendererFaceDirection(FIntVector(-1, 0, 0), FIntVector(0, 1, 0), FIntVector(0, 0, -1))
			,
		};

	static const TArray< FIntVector > FaceLoopDirectionList = {
			FIntVector(0, 1, 2)
			, FIntVector(2, 1, 0)
			, FIntVector(2, 0, 1)
			, FIntVector(2, 1, 0)
			, FIntVector(2, 0, 1)
			, FIntVector(0, 1, 2)
			,
		};

	static const TArray< int32 > FacePositiveList = {
			1
			, -1
			, 1
			, 1
			, -1
			, -1
			,
		};

	static const TArray< int32 > SurfaceDirectionID = {
			5
			, 0
			, 3
			, 1
			, 2
			, 4
		};
};

class ULFPChunkedTagDataComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLFPOnVoxelMeshGeneratEvent);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LOHFUNCTIONPLUGINVOXEL_API ULFPVoxelRenderComponent : public UDynamicMeshComponent
{
	GENERATED_BODY()

public:

	// Sets default values for this component's properties
	ULFPVoxelRenderComponent( );

protected:

	// Called when the game starts
	virtual void BeginPlay( ) override;

public:

	// Called every frame
	virtual void TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;

public:

	UPROPERTY(BlueprintAssignable)
	FLFPOnVoxelMeshGeneratEvent OnVoxelMeshRebuild;

	UPROPERTY(BlueprintAssignable)
	FLFPOnVoxelMeshGeneratEvent OnVoxelMeshGenerated;

protected:

	UPROPERTY(EditAnywhere, Category="Setting")
	FGameplayTag HandleTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditAnywhere, Category="Setting")
	float DistanceFieldResolutionScale = 1.0f;

	UPROPERTY(EditAnywhere, Category="Setting")
	float BevelSize = 10.0f;

protected:

	UPROPERTY(Transient)
	TObjectPtr< class ULFPGridTagDataComponent > DataComponent = nullptr;

	UPROPERTY(Transient)
	int32 RegionIndex = INDEX_NONE;

	UPROPERTY(Transient)
	int32 ChunkIndex = INDEX_NONE;

public:

	UFUNCTION(BlueprintCallable, Category="LFPVoxelRender")
	void Initialize( class ULFPGridTagDataComponent* NewDataComponent , const int32 NewRegionIndex , const int32 NewChunkIndex );

	UFUNCTION(BlueprintCallable, Category="LFPVoxelRender")
	void Uninitialize( );

public:

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelRender")
	void UpdateVoxel( );

	virtual void RebuildPhysicsData( ) override;

protected:

	virtual void UpdateDistanceField( ) override;

private:

	TAsyncComponentDataComputeQueue< FDynamicMesh3 > VoxelMeshComputeQueue;

	void ComputeNewVoxelMesh_TaskFunction( FProgressCancel& Progress , FDynamicMesh3& Mesh , const float CurrentBevelSize ) const;

	void OnComputeNewVoxelMesh_Completed( TUniquePtr< FDynamicMesh3 > NewMeshData );

private:

	// Internal method to compute the distance field, run in a background thread.
	TUniquePtr< FDistanceFieldVolumeData > ComputeNewDistanceField_TaskFunctionV2( FProgressCancel& Progress , const FDynamicMesh3& Mesh , bool bMostlyTwoSided ) const;

	// Modify to use ParallelFor
	bool DynamicMesh_GenerateSignedDistanceFieldVolumeData(
		const FDynamicMesh3&      Mesh ,
		bool                      bGenerateAsIfTwoSided ,
		FDistanceFieldVolumeData& VolumeDataOut ,
		FProgressCancel&          Progress ) const;

	TUniquePtr< FDistanceFieldVolumeData > ComputeDistanceFieldForMesh(
		const FDynamicMesh3& Mesh ,
		FProgressCancel&     Progress ,
		bool                 bGenerateAsIfTwoSided ) const;

	static int32 ComputeLinearVoxelIndex( FIntVector VoxelCoordinate , FIntVector VolumeDimensions )
	{
		return (VoxelCoordinate.Z * VolumeDimensions.Y + VoxelCoordinate.Y) * VolumeDimensions.X + VoxelCoordinate.X;
	}

};
