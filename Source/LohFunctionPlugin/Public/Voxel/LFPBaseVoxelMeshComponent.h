// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#pragma once

#include "CoreMinimal.h"
#include "Components/MeshComponent.h"
#include "Voxel/LFPVoxelContainer.h"
#include "PhysicsEngine/BodySetup.h"
#include "DistanceFieldAtlas.h"
#include "LFPBaseVoxelMeshComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LFPVoxelMeshComponentLog, Log, All);

USTRUCT(BlueprintType)
struct FLFPBaseVoxelMeshSetting
{
	GENERATED_USTRUCT_BODY()

public:

	/* Generate Distance Field And Lumen */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseVoxelMeshSetting | DistanceFieldAndLumen")
		bool bGenerateLumenData = false;

	/* Increase Cover Range But Decrease Quality */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseVoxelMeshSetting | DistanceFieldAndLumen")
		float BoundExpand = 5.0f;

	/* How Much Data Can Be In The Distance Field (High Value Will Slow Down Computation Time) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseVoxelMeshSetting | DistanceFieldAndLumen", Meta = (ClampMin = "3", ClampMax = "32.0"))
		uint8 VoxelPerDistanceField = 3;

	/* Decrease Accuracy To Improve Build Time */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseVoxelMeshSetting | DistanceFieldAndLumen", Meta = (ClampMin = "1.0", ClampMax = "8.0"))
		float VoxelDistanceFieldJump = 1.0f;
};

struct FLFPBaseVoxelFaceDirection
{
	FLFPBaseVoxelFaceDirection(FIntVector F, FIntVector R, FIntVector U) : Forward(F), Right(R), Up(U) {}

	FIntVector Forward, Right, Up = FIntVector::NoneValue;

public:

	FORCEINLINE void SetAxis(FVector3f& X, FVector3f& Y, FVector3f& Z) const
	{
		X = FVector3f(Forward);
		Y = FVector3f(Right);
		Z = FVector3f(Up);
	}
};

const struct FLFPBaseVoxelMeshConstantData
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

	const TArray<FLFPBaseVoxelFaceDirection> FaceDirection = {
		FLFPBaseVoxelFaceDirection(FIntVector( 1, 0, 0), FIntVector( 0, 1, 0), FIntVector( 0, 0, 1)),
		FLFPBaseVoxelFaceDirection(FIntVector( 0, 0, 1), FIntVector( 0, 1, 0), FIntVector(-1, 0, 0)),
		FLFPBaseVoxelFaceDirection(FIntVector( 0, 0, 1), FIntVector( 1, 0, 0), FIntVector( 0, 1, 0)),
		FLFPBaseVoxelFaceDirection(FIntVector( 0, 0, 1), FIntVector( 0,-1, 0), FIntVector( 1, 0, 0)),
		FLFPBaseVoxelFaceDirection(FIntVector( 0, 0, 1), FIntVector(-1, 0, 0), FIntVector( 0,-1, 0)),
		FLFPBaseVoxelFaceDirection(FIntVector(-1, 0, 0), FIntVector( 0, 1, 0), FIntVector( 0, 0,-1)),
	};

	const TArray<FIntPoint> FaceUVPositionMapping = {
		FIntPoint(0, 1),
		FIntPoint(2, 1),
		FIntPoint(2, 0),
		FIntPoint(2, 1),
		FIntPoint(2, 0),
		FIntPoint(0, 1),
	};

	const TArray<FVector2D> FaceUVStartOffset = {
		FVector2D(0.0f, 0.0f),
		FVector2D(1.0f, 0.0f),
		FVector2D(2.0f, 0.0f),
		FVector2D(2.0f, 1.0f),
		FVector2D(1.0f, 1.0f),
		FVector2D(0.0f, 1.0f),
	};

	const TArray<int32> SurfaceDirectionID = {
		5,0,3,1,2,4
	};
};

struct FLFPBaseVoxelMeshSectionData
{
	/** Raw Vertex Generated For The Function */
	TArray<FVector3f> VertexList;

	/** Raw Triangle Index Generated For The Function */
	TArray<uint32> TriangleIndexList;

	/** Raw UV Generated For The Function */
	TArray<FVector2f> UVList;

	/** Edge UV Generated For Material To Use Edge Texture */
	TArray<FVector2f> EdgeUVList;

	/** Point UV Generated For Material To Use Point Texture */
	TArray<FVector2f> PointUVList;

	/** Point UV Generated For Material To Use Point Texture */
	TArray<FVector2f> PositionUVList;

	/** Color For The Vertex */
	TArray<FColor> VoxelColorList;

	/** How Many Triangle Has Been Generated */
	uint32 TriangleCount = 0;

	/** Index For The Voxel Trace */
	//TArray<int32> VoxelIndexList;
};

/* This Contains Every Data Need To Render This Voxel Mesh */
struct FLFPBaseVoxelMeshRenderData
{
	TArray<FLFPBaseVoxelMeshSectionData> Sections;

	TArray<uint8> VoxelMaterialList; // This Is Use For Distance Field And Lumen Acceleration

	FBox LocalBounds = FBox(EForceInit::ForceInitToZero);

	int32 RefCount = 0;

	FORCEINLINE void AddRef()
	{
		RefCount += 1;
	}

	FORCEINLINE void Release()
	{
		RefCount -= 1;

		if (RefCount == 0)
		{
			delete this;
		}
	}

	FORCEINLINE int32 GetRefCount()
	{
		return RefCount;
	}
};

/* This Contains Every Data Need For Lumen Support */
struct FLFPBaseVoxelMeshLumenData
{
	~FLFPBaseVoxelMeshLumenData();

	class FDistanceFieldVolumeData* DistanceFieldMeshData = nullptr;

	class FCardRepresentationData* LumenCardData = nullptr;

	int32 RefCount = 0;

	FORCEINLINE void AddRef()
	{
		RefCount += 1;
	}

	FORCEINLINE void Release()
	{
		RefCount -= 1;

		if (RefCount == 0)
		{
			delete this;
		}
	}

	FORCEINLINE int32 GetRefCount()
	{
		return RefCount;
	}
};

USTRUCT(BlueprintType)
struct FLFPBaseVoxelMeshStatus
{
	GENERATED_USTRUCT_BODY()

public:

	FLFPBaseVoxelMeshStatus()
	{
		bIsVoxelAttributeDirty = false;
		bIsVoxelMeshDirty = false;
		bIsGeneratingMesh = false;
		bIsLumenDataDirty = false;
		bIsGeneratingLumen = false;
		bIsBodyInvalid = false;
	}

	UPROPERTY(VisibleAnywhere, Category = "BaseVoxelMeshStatus") uint8 bIsVoxelAttributeDirty : 1;

	UPROPERTY(VisibleAnywhere, Category = "BaseVoxelMeshStatus") uint8 bIsVoxelMeshDirty : 1;

	UPROPERTY(VisibleAnywhere, Category = "BaseVoxelMeshStatus") uint8 bIsGeneratingMesh : 1;

	UPROPERTY(VisibleAnywhere, Category = "BaseVoxelMeshStatus") uint8 bIsLumenDataDirty : 1;

	UPROPERTY(VisibleAnywhere, Category = "BaseVoxelMeshStatus") uint8 bIsGeneratingLumen : 1;

	UPROPERTY(VisibleAnywhere, Category = "BaseVoxelMeshStatus") uint8 bIsBodyInvalid : 1;
};

class FLFPBaseBoxelRenderTask;
class FLFPBaseBoxelLumenTask;

//**
// * This Class Main Function Is To Render Out The Voxel
// *  - Render Voxel Mesh
// *  - Handle Collision
// * 
// * Secondary Function Is To Generate Out Ths Voxel Mesh Data From Voxel Coordination Data
// */
UCLASS(meta = (BlueprintSpawnableComponent), ClassGroup = (LFPlugin))
class LOHFUNCTIONPLUGIN_API ULFPBaseVoxelMeshComponent : public UMeshComponent, public IInterface_CollisionDataProvider
{
	friend class FLFPBaseVoxelMeshSceneProxy;
	friend class FLFPBaseBoxelRenderTask;
	friend class FLFPBaseBoxelLumenTask;

	GENERATED_BODY()

public:

	ULFPBaseVoxelMeshComponent();

	virtual void BeginDestroy() override;

public: /* Functions For Setting Up Component */

	/* Setup This Component And Reset VoxelDataTexture And VoxelColorTexture : Please Rebind VoxelDataTexture And VoxelColorTexture After This */
	UFUNCTION(BlueprintCallable, Category = "LFPBaseVoxelMeshComponent | Function")
		FORCEINLINE void SetVoxelContainer(const TArray<UMaterialInterface*>& Material, ULFPVoxelContainer* NewVoxelContainer, const int32 NewChuckIndex, const FName InitializeName, const bool bAutoCreateMaterialInstance, TArray<UMaterialInstanceDynamic*>& MaterialInstanceDynamicList, UTexture2D*& OutVoxelDataTexture, UTexture2D*& OutVoxelColorTexture);

	UFUNCTION(BlueprintCallable, Category = "LFPBaseVoxelMeshComponent | Function")
		FORCEINLINE void SetVoxelMaterial(const TArray<UMaterialInterface*>& Material);

	UFUNCTION(BlueprintCallable, Category = "LFPBaseVoxelMeshComponent | Function")
		FORCEINLINE void UpdateVoxelMesh();

	UFUNCTION(BlueprintCallable, Category = "LFPBaseVoxelMeshComponent | Function")
		FORCEINLINE void UpdateVoxelAttribute();

protected:

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private: // Helper Functions

	FORCEINLINE void AddVoxelFace(FLFPBaseVoxelMeshRenderData& RenderParam, const int32 VoxelIndex, const FIntVector VoxelGridLocation, const FVector VoxelLocation, const FIntVector VoxelGlobalGridLocation, const int32 FaceIndex, const ULFPVoxelContainer* LocalVoxelContainer, const FLFPVoxelStaticAttributeData& VoxelAttribute, const FVector& LocalVoxelHalfSize);

	FORCEINLINE uint8 CheckVoxelDirectionVisible(const ULFPVoxelContainer* LocalVoxelContainer, const int32 MateriaID, const FIntVector From, const FIntVector Direction, const FIntVector Up) const;

protected: // Rendering Handler

	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;

	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;

public: // Material Handler

	virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override;

	virtual UMaterialInterface* GetMaterialFromCollisionFaceIndex(int32 FaceIndex, int32& SectionIndex) const override;

	virtual int32 GetNumMaterials() const override;

	virtual UMaterialInterface* GetMaterial(int32 ElementIndex) const override;

	virtual void SetMaterial(int32 ElementIndex, UMaterialInterface* Material) override;

	/* This Create Dynamic Material Instance And Apply VoxelDataTexture And VoxelColorTexture To It (Use Name On Texture Parameter : VoxelDataTexture or VoxelColorTexture) */
	virtual UMaterialInstanceDynamic* CreateDynamicMaterialInstance(int32 ElementIndex, class UMaterialInterface* SourceMaterial, FName OptionalName) override;

public: // Collision Handler

	virtual bool GetPhysicsTriMeshData(struct FTriMeshCollisionData* CollisionData, bool InUseAllTriData) override;

	virtual bool ContainsPhysicsTriMeshData(bool InUseAllTriData) const override;

	virtual bool WantsNegXTriMesh() override;

	virtual UBodySetup* GetBodySetup() override;

	FORCEINLINE UBodySetup* CreateBodySetup();

	FORCEINLINE void RebuildPhysicsData();

	FORCEINLINE void FinishPhysicsAsyncCook(bool bSuccess, UBodySetup* FinishedBodySetup);

public:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPBaseVoxelMeshComponent | Cache")
		TObjectPtr<UTexture2D> VoxelDataTexture = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPBaseVoxelMeshComponent | Cache")
		TObjectPtr<UTexture2D> VoxelColorTexture = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPBaseVoxelMeshComponent | Cache")
		TObjectPtr<ULFPVoxelContainer> VoxelContainer = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere,	Category = "LFPBaseVoxelMeshComponent")
		FLFPVoxelChuckInfo ChuckInfo;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere,	Category = "LFPBaseVoxelMeshComponent")
		FLFPBaseVoxelMeshStatus ChuckStatus;

	UPROPERTY(BlueprintReadOnly, EditAnywhere,		Category = "LFPBaseVoxelMeshComponent")
		FLFPBaseVoxelMeshSetting ChuckSetting;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, AdvancedDisplay, Category = Lighting)
		uint8 bOverrideDistanceFieldSelfShadowBias : 1;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, AdvancedDisplay, Category = Lighting)
		float DistanceFieldSelfShadowBias;

private:

	UPROPERTY() TArray<TObjectPtr<UMaterialInterface>> MaterialList;

	UPROPERTY(Instanced) TObjectPtr<UBodySetup> BodySetup;

	const FLFPBaseVoxelMeshConstantData ConstantData;

	TRefCountPtr<FLFPBaseVoxelMeshRenderData> RenderData = nullptr;

	TRefCountPtr<FLFPBaseVoxelMeshLumenData> LumenData = nullptr;

	FAsyncTask<FLFPBaseBoxelRenderTask>* RenderTask = nullptr;

	FAsyncTask<FLFPBaseBoxelLumenTask>* LumenTask = nullptr;
};

struct FLFPBaseBoxelRenderParam
{
	ULFPBaseVoxelMeshComponent* SharePtr = nullptr;
	ULFPVoxelContainer* LocalVoxelContainer = nullptr;
	FLFPVoxelChuckInfo	LocalChuckInfo;
	FLFPBaseVoxelMeshSetting LocalChuckSetting;
	//FBoxSphereBounds LocalBounds;
	int32 SectionSize = 0;
	int32 MaterialNum = 0;

	void Reset()
	{
		SharePtr = nullptr;
		LocalVoxelContainer = nullptr;
		SectionSize = 0;
		MaterialNum = 0;
	}
};

class FLFPBaseBoxelRenderTask : public FNonAbandonableTask {
	friend class FAsyncTask<FLFPBaseBoxelRenderTask>;

public:

	FLFPBaseBoxelRenderParam RenderParam;

	FLFPBaseBoxelRenderTask(const FLFPBaseBoxelRenderParam& Param) : RenderParam(Param) { }

	void DoWork();

	FORCEINLINE TStatId GetStatId() const { RETURN_QUICK_DECLARE_CYCLE_STAT(FLFPBaseBoxelRenderTask, STATGROUP_ThreadPoolAsyncTasks); }
};

struct FLFPBaseBoxelLumenParam
{
	ULFPBaseVoxelMeshComponent* SharePtr = nullptr;
	FLFPBaseVoxelMeshSetting LocalChuckSetting;
	FBoxSphereBounds LocalBounds;
	TArray<uint8> VoxelMaterialList;
	FLFPVoxelContainerSettingV2 VoxelSetting = FLFPVoxelContainerSettingV2();

	void Reset()
	{
		SharePtr = nullptr;
		VoxelMaterialList.Empty();
		VoxelSetting = FLFPVoxelContainerSettingV2();
	}
};

class FLFPBaseBoxelLumenTask : public FNonAbandonableTask {
	friend class FAsyncTask<FLFPBaseBoxelLumenTask>;

public:

	FLFPBaseBoxelLumenParam LumenParam;

	FLFPBaseBoxelLumenTask(const FLFPBaseBoxelLumenParam& Param) : LumenParam(Param) { }

	void DoWork();

	FORCEINLINE class FDistanceFieldVolumeData* GenerateDistanceField();

	FORCEINLINE class FCardRepresentationData* GenerateLumenCard();

	FORCEINLINE TStatId GetStatId() const { RETURN_QUICK_DECLARE_CYCLE_STAT(FLFPBaseBoxelLumenTask, STATGROUP_ThreadPoolAsyncTasks); }
};
