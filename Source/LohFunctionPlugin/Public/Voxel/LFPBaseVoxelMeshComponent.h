// Copyright (c) 2022 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#pragma once

#include "CoreMinimal.h"
#include "Components/MeshComponent.h"
#include "Voxel/LFPVoxelContainer.h"
#include "PhysicsEngine/BodySetup.h"
#include "LFPBaseVoxelMeshComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LFPVoxelMeshComponentLog, Log, All);

USTRUCT(BlueprintType)
struct FBaseVoxelMeshSetting
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseVoxelMeshSetting")
		TObjectPtr<UStaticMesh> DistanceFieldMesh = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseVoxelMeshSetting")
		float BoundExpand = 5.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseVoxelMeshSetting")
		int32 LumenCardBatch = 1;
};

USTRUCT(BlueprintType)
struct FBaseVoxelMeshStatus
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category = "BaseVoxelMeshStatus") uint8 bIsVoxelMeshDirty : 1;
	
	UPROPERTY(VisibleAnywhere, Category = "BaseVoxelMeshStatus") uint8 bIsGeneratingMesh : 1;
	
	UPROPERTY(VisibleAnywhere, Category = "BaseVoxelMeshStatus") uint8 bIsBodyInvalid : 1;
};

struct FBaseVoxelMeshConstantData
{
	const TArray<FRotator> VertexRotationList =
	{
		FRotator(  0.0f,   0.0f, 0.0f),
		FRotator( 90.0f,   0.0f, 0.0f),
		FRotator( 90.0f, 270.0f, 0.0f),
		FRotator( 90.0f, 180.0f, 0.0f),
		FRotator( 90.0f,  90.0f, 0.0f),
		FRotator(180.0f,   0.0f, 0.0f),
	};

	const TArray<FIntVector> FaceCheckDirection = {
		FIntVector( 0.0f, 0.0f, 1.0f),
		FIntVector(-1.0f, 0.0f, 0.0f),
		FIntVector( 0.0f, 1.0f, 0.0f),
		FIntVector( 1.0f, 0.0f, 0.0f),
		FIntVector( 0.0f,-1.0f, 0.0f),
		FIntVector( 0.0f, 0.0f,-1.0f),
	};

	const TArray<FVector2D> FaceUVStartOffset = {
		FVector2D(0.0f, 0.0f),
		FVector2D(1.0f, 0.0f),
		FVector2D(2.0f, 0.0f),
		FVector2D(2.0f, 1.0f),
		FVector2D(1.0f, 1.0f),
		FVector2D(0.0f, 1.0f),
	};

	const TArray<FVector> SurfaceScale = {
		FVector(1.0f, 1.0f, 0.0f),
		FVector(0.0f, 1.0f, 1.0f),
		FVector(1.0f, 0.0f, 1.0f),
		FVector(0.0f, 1.0f, 1.0f),
		FVector(1.0f, 0.0f, 1.0f),
		FVector(1.0f, 1.0f, 0.0f),
	};

	const TArray<int32> SurfaceDirectionID = {
		5,0,3,1,2,4
	};

	const float LumenUpOffset = 5.0f;
};

struct FBaseVoxelMeshSectionData
{
	/** Raw Vertex Generated For The Function */
	TArray<FVector3f> VertexList;

	/** Raw Triangle Index Generated For The Function */
	TArray<uint32> TriangleIndexList;

	/** Raw UV Generated For The Function */
	TArray<FVector2f> UVList;

	/** Color For The Vertex */
	TArray<FColor> VoxelColorList;

	/** How Many Triangle Has Been Generated */
	uint32 TriangleCount = 0;

	/** Index For The Voxel Trace */
	TArray<int32> VoxelIndexList;
};

/* This Contains Every Data Need To Render This Voxel Mesh */
struct FBaseVoxelMeshRenderData
{
	~FBaseVoxelMeshRenderData();

	TArray<FBaseVoxelMeshSectionData> Sections;

	TArray<FTransform> DistanceFieldInstanceData;

	class FDistanceFieldVolumeData* DistanceFieldMeshData = nullptr;

	class FCardRepresentationData* LumenCardData = nullptr;
};

//**
// * This Class Main Function Is To Render Out The Voxel
// *  - Render Voxel Mesh
// *  - Handle Collision
// * 
// * Secondary Function Is To Generate Out Ths Voxel Mesh Data From Voxel Coordination Data
// */

UCLASS(meta = (BlueprintSpawnableComponent), ClassGroup = Rendering)
class LOHFUNCTIONPLUGIN_API ULFPBaseVoxelMeshComponent : public UMeshComponent, public IInterface_CollisionDataProvider
{
	friend class FLFPBaseVoxelMeshSceneProxy;

	GENERATED_BODY()

public:

	ULFPBaseVoxelMeshComponent();

public: /* Functions For Setting Up Component */

	UFUNCTION(BlueprintCallable, Category = "LFPBaseVoxelMeshComponent | Function")
		FORCEINLINE void SetVoxelContainer(ULFPVoxelContainer* NewVoxelContainer, const int32 NewChuckIndex, const FName InitializeName);

	UFUNCTION(BlueprintCallable, Category = "LFPBaseVoxelMeshComponent | Function")
		FORCEINLINE void SetVoxelMaterial(const TArray<UMaterialInterface*>& Material);

	UFUNCTION(BlueprintCallable, Category = "LFPBaseVoxelMeshComponent | Function")
		FORCEINLINE void UpdateVoxelMesh();

protected:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private: // Helper Functions

	FORCEINLINE void AddVoxelFace(FBaseVoxelMeshSectionData& EditMesh, const int32 VoxelIndex, const FVector VoxelLocation, const FVector2D UVOffset, const int32 FaceIndex, const FColor VoxelColor, const FVector LocalVoxelHalfSize);

	FORCEINLINE void AddLumenBox(TMap<FIntPoint, FBox>& LumenBox, const FVector VoxelLocation, const int32 FaceIndex, const FVector VoxelHalfSize, const FIntVector VoxelGridLocation, const FBox VoxelBounds, const FIntVector LumenBatch);

protected: // Rendering Handler

	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;

	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;

public: // Material Handler

	virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override;

	virtual UMaterialInterface* GetMaterialFromCollisionFaceIndex(int32 FaceIndex, int32& SectionIndex) const override;

	virtual int32 GetNumMaterials() const override;

	virtual UMaterialInterface* GetMaterial(int32 ElementIndex) const override;

	virtual void SetMaterial(int32 ElementIndex, UMaterialInterface* Material) override;

public: // Collision Handler

	virtual bool GetPhysicsTriMeshData(struct FTriMeshCollisionData* CollisionData, bool InUseAllTriData) override;

	virtual bool ContainsPhysicsTriMeshData(bool InUseAllTriData) const override;

	virtual bool WantsNegXTriMesh() override;

	virtual UBodySetup* GetBodySetup() override;

	FORCEINLINE UBodySetup* CreateBodySetup();

	FORCEINLINE void RebuildPhysicsData();

	FORCEINLINE void FinishPhysicsAsyncCook(bool bSuccess, UBodySetup* FinishedBodySetup);

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPBaseVoxelMeshComponent | Cache")
		TObjectPtr<ULFPVoxelContainer> VoxelContainer = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPBaseVoxelMeshComponent | Cache")
		FLFPVoxelChuckInfo ChuckInfo;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPBaseVoxelMeshComponent | Cache")
		FBaseVoxelMeshStatus ChuckStatus;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPBaseVoxelMeshComponent | Cache")
		FBaseVoxelMeshSetting ChuckSetting;

private:

	UPROPERTY() TArray<TObjectPtr<UMaterialInterface>> VoxelMaterialList;

	UPROPERTY(Instanced) TObjectPtr<class UBodySetup> VoxelMeshBodySetup;

	FBaseVoxelMeshRenderData* VoxelMeshRenderData = nullptr;

	FBaseVoxelMeshConstantData VoxelMeshConstantData;

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPBaseVoxelMeshComponent | Setting")
		TObjectPtr<UStaticMesh> VoxelDistanceFieldMesh = nullptr;

};
