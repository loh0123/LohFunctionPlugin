// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/MeshComponent.h"
#include "Voxel/LFPVoxelContainer.h"
#include "PhysicsEngine/BodySetup.h"
#include "DistanceFieldAtlas.h"
#include "LFPBaseVoxelMeshComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LFPVoxelMeshComponentLog, Log, All);

USTRUCT()
struct FVoxelMeshBufferData
{
	GENERATED_USTRUCT_BODY()

public:

	/** Raw Vertex Generated For The Function */
	TArray<FVector3f> VertexList;

	/** Raw Triangle Index Generated For The Function */
	TArray<uint32> TriangleIndexList;

	/** Raw UV Generated For The Function */
	TArray<FVector2d> UVList;

	/** Color For The Vertex */
	TArray<FColor> VoxelColorList;

	/** How Many Triangle Has Been Generated */
	int32 TriangleCount = 0;

	/** Index For The Voxel Trace */
	TArray<int32> VoxelIndexList;
};

/**
 * This Class Main Function Is To Render Out The Voxel
 *  - Render Voxel Mesh
 *  - Handle Collision
 * 
 * Secondary Function Is To Generate Out Ths Voxel Mesh Data From Voxel Coordination Data
 */
UCLASS(meta = (BlueprintSpawnableComponent), ClassGroup = Rendering)
class LOHFUNCTIONPLUGIN_API ULFPBaseVoxelMeshComponent : public UMeshComponent, public IInterface_CollisionDataProvider
{
	friend class FLFPBaseVoxelMeshSceneProxy;

	GENERATED_BODY()

public:

	ULFPBaseVoxelMeshComponent();

public:

	UFUNCTION(BlueprintCallable, Category = "LFPBaseVoxelMeshComponent | Function")
		FORCEINLINE void SetVoxelContainer(ULFPVoxelContainer* NewVoxelContainer, const int32 NewChuckIndex, const FVector NewVoxelHalfSize, const FName InitializeName);

	UFUNCTION(BlueprintCallable, Category = "LFPBaseVoxelMeshComponent | Function")
		FORCEINLINE void SetVoxelMaterial(const TArray<UMaterialInterface*>& Material);

	UFUNCTION(BlueprintCallable, Category = "LFPBaseVoxelMeshComponent | Function")
		FORCEINLINE void UpdateVoxelMesh();

	UFUNCTION(BlueprintPure, Category = "LFPBaseVoxelMeshComponent | Function")
		FORCEINLINE FLFPVoxelAttributeV2 GetVoxelDataFromFaceIndex(const int32 FaceIndex, FLFPVoxelGridIndex& OutVoxelGridIndex, FVector& OutVoxelWorldLocation) const;

protected:

	FORCEINLINE void AddVoxelFace(FVoxelMeshBufferData& EditMesh, const int32 VoxelIndex, const FVector3f VoxelLocation, const FVector2d UVOffset, const int32 FaceIndex, const FColor VoxelColor);

public:

	FORCEINLINE int32 GetVoxelLength() const;

	FORCEINLINE void GetVoxelAttributeList(TArray<FLFPVoxelAttributeV2>& VoxelAttributeList, TBitArray<>& VisibleList);

protected:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
public:

	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;

public:

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

	virtual void RebuildPhysicsData();

	FORCEINLINE void FinishPhysicsAsyncCook(bool bSuccess, UBodySetup* FinishedBodySetup);

protected:

	UPROPERTY(transient) TArray<FVoxelMeshBufferData> VoxelMesh;

	UPROPERTY() bool IsVoxelMeshValid = false;

	UPROPERTY() bool IsVoxelMeshDirty = false;

	UPROPERTY() bool IsGeneratingMesh = false;

	UPROPERTY() TArray<TObjectPtr<UMaterialInterface>> BaseMaterials;

	UPROPERTY(transient) bool bIsBodyInvalid = false;

	UPROPERTY(Instanced) TObjectPtr<class UBodySetup> MeshBodySetup;

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPBaseVoxelMeshComponent | Setting")
		TObjectPtr<UStaticMesh> DistanceFieldMesh = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPBaseVoxelMeshComponent | Cache")
		TArray<FTransform> VoxelDistanceField;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPBaseVoxelMeshComponent | Cache")
		TObjectPtr<ULFPVoxelContainer> VoxelContainer = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPBaseVoxelMeshComponent | Cache")
		FIntVector VoxelStartLocation = FIntVector(0);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPBaseVoxelMeshComponent | Cache")
		int32 ChuckIndex = INDEX_NONE;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPBaseVoxelMeshComponent | Cache")
		FVector VoxelHalfSize = FVector(100);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPBaseVoxelMeshComponent | Cache")
		FVector2D VoxelUVSize = FVector2D(1.0f);
};
