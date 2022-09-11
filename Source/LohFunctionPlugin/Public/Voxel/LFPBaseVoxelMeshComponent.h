// MIT License
// 
// Copyright(c) 2022 loh0123
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright noticeand this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include "CoreMinimal.h"
#include "Components/MeshComponent.h"
#include "Voxel/LFPVoxelContainer.h"
#include "PhysicsEngine/BodySetup.h"
#include "LFPBaseVoxelMeshComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LFPVoxelMeshComponentLog, Log, All);

USTRUCT()
struct FVoxelMeshSectionData
{
	GENERATED_USTRUCT_BODY()

public:

	/** Raw Vertex Generated For The Function */
	UPROPERTY() TArray<FVector3f> VertexList;

	/** Raw Triangle Index Generated For The Function */
	UPROPERTY() TArray<uint32> TriangleIndexList;

	/** Raw UV Generated For The Function */
	UPROPERTY() TArray<FVector2f> UVList;

	/** Color For The Vertex */
	UPROPERTY() TArray<FColor> VoxelColorList;

	/** How Many Triangle Has Been Generated */
	UPROPERTY() uint32 TriangleCount = 0;

	/** Index For The Voxel Trace */
	UPROPERTY() TArray<int32> VoxelIndexList;
};

/* This Contains Every Data Need To Render This Voxel Mesh */
USTRUCT()
struct FVoxelMeshRenderData
{
	GENERATED_USTRUCT_BODY()

	~FVoxelMeshRenderData();

public:

	UPROPERTY() TArray<FVoxelMeshSectionData> Sections;

	UPROPERTY() TArray<FTransform> DistanceFieldInstanceData;

	/** Lumen Box To Calculate Lumen Card : X-, X+, Y-, Y+, Z-, Z+ */
	UPROPERTY() TMap<FIntPoint, FBox> LumenBox;

	class FDistanceFieldVolumeData* DistanceFieldMeshData = nullptr;

	class FCardRepresentationData* LumenCardData = nullptr;
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

protected:

	FORCEINLINE void AddVoxelFace(FVoxelMeshSectionData& EditMesh, const int32 VoxelIndex, const FVector3f VoxelLocation, const FVector2f UVOffset, const int32 FaceIndex, const FColor VoxelColor);

	FORCEINLINE int32 GetVoxelLength() const;

	FORCEINLINE void GetVoxelAttributeList(TArray<FLFPVoxelAttributeV2>& VoxelAttributeList, TBitArray<>& VisibleList);

	FORCEINLINE FBox GetVoxelMeshBound() const
	{ 
		return FBox(FVector3d(-VoxelHalfSize), VoxelContainer != nullptr ? 
			((FVector3d)VoxelHalfSize * 2) * ((FVector3d)VoxelContainer->GetContainerSetting().VoxelGridSize) + FVector3d(VoxelHalfSize) 
			: 
			FVector3d(VoxelHalfSize)).ExpandBy(BoundExpand);
	}

protected:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


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

	FVoxelMeshRenderData* VoxelMeshRenderData = nullptr;

	UPROPERTY() bool bIsVoxelMeshDirty = false;

	UPROPERTY() bool bIsGeneratingMesh = false;

	UPROPERTY() bool bIsBodyInvalid = false;

	UPROPERTY() TArray<TObjectPtr<UMaterialInterface>> BaseMaterials;

	UPROPERTY(Instanced) TObjectPtr<class UBodySetup> MeshBodySetup;

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPBaseVoxelMeshComponent | Setting")
		TObjectPtr<UStaticMesh> DistanceFieldMesh = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPBaseVoxelMeshComponent | Setting")
		float BoundExpand = 5.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPBaseVoxelMeshComponent | Setting")
		int32 LumenCardBatch = 1;

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
