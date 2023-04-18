// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/MeshComponent.h"
#include "Voxel/LFPVoxelContainerComponent.h"
#include "Rendering/StaticMeshVertexBuffer.h"
#include "Rendering/PositionVertexBuffer.h"
#include "DynamicMeshBuilder.h"
#include "LFPVoxelRendererComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LFPVoxelRendererComponent, Log, All);

struct FLFPVoxelRendererFaceDirection
{
	FLFPVoxelRendererFaceDirection(FIntVector F, FIntVector R, FIntVector U) : Forward(F), Right(R), Up(U) {}

	FIntVector Forward, Right, Up = FIntVector::NoneValue;

public:

	FORCEINLINE void SetAxis(FVector3f& X, FVector3f& Y, FVector3f& Z) const
	{
		X = FVector3f(Forward);
		Y = FVector3f(Right);
		Z = FVector3f(Up);
	}
};

namespace LFPVoxelRendererConstantData
{
	const TArray<FRotator> VertexRotationList =
	{
		FRotator(0.0f	,   0.0f, 0.0f),
		FRotator(90.0f	,   0.0f, 0.0f),
		FRotator(90.0f	, 270.0f, 0.0f),
		FRotator(90.0f	, 180.0f, 0.0f),
		FRotator(90.0f	,  90.0f, 0.0f),
		FRotator(180.0f	,   0.0f, 0.0f),
	};

	const TArray<FLFPVoxelRendererFaceDirection> FaceDirection = {
		FLFPVoxelRendererFaceDirection(FIntVector(1, 0, 0), FIntVector(0, 1, 0), FIntVector(0, 0, 1)),
		FLFPVoxelRendererFaceDirection(FIntVector(0, 0, 1), FIntVector(0, 1, 0), FIntVector(-1, 0, 0)),
		FLFPVoxelRendererFaceDirection(FIntVector(0, 0, 1), FIntVector(1, 0, 0), FIntVector(0, 1, 0)),
		FLFPVoxelRendererFaceDirection(FIntVector(0, 0, 1), FIntVector(0,-1, 0), FIntVector(1, 0, 0)),
		FLFPVoxelRendererFaceDirection(FIntVector(0, 0, 1), FIntVector(-1, 0, 0), FIntVector(0,-1, 0)),
		FLFPVoxelRendererFaceDirection(FIntVector(-1, 0, 0), FIntVector(0, 1, 0), FIntVector(0, 0,-1)),
	};

	const TArray<FIntVector> FaceLoopDirectionList = {
		FIntVector(0, 1, 2),
		FIntVector(2, 1, 0),
		FIntVector(2, 0, 1),
		FIntVector(2, 1, 0),
		FIntVector(2, 0, 1),
		FIntVector(0, 1, 2),
	};

	const TArray<int32> SurfaceDirectionID = {
		5,0,3,1,2,4
	};
};

struct FLFPVoxelRendererFaceData
{
	/** Raw Vertex Generated For The Function */
	TArray<FVector3f> VertexList;

	/** Raw Triangle Index Generated For The Function */
	TArray<uint32> TriangleIndexList;

	/** Raw UV Generated For The Function */
	TArray<FVector2f> UVList;
};

struct FLFPVoxelRendererSectionData
{
	FLFPVoxelRendererSectionData() {}
	FLFPVoxelRendererSectionData(const FIntVector NewFaceDirectionAmount)
	{
		SetFaceDirectionAmount(NewFaceDirectionAmount);
	}

	TArray<FLFPVoxelRendererFaceData> FaceDataList = TArray<FLFPVoxelRendererFaceData>();

	FIntVector FaceDirectionAmount = FIntVector(0);

	uint32 TriangleCount = 0;

public:

	FORCEINLINE void SetFaceDirectionAmount(const FIntVector NewFaceDirectionAmount)
	{
		FaceDirectionAmount = NewFaceDirectionAmount;

		const int32 FaceAmount = (FaceDirectionAmount.X * 2) + (FaceDirectionAmount.Y * 2) * (FaceDirectionAmount.Z * 2);

		FaceDataList.Init(FLFPVoxelRendererFaceData(), FaceAmount);
	}

	FORCEINLINE FLFPVoxelRendererFaceData& GetVoxelFaceData(const int32 DirectionIndex, const int32 FaceIndex)
	{
		int32 FaceDataIndex = 0;

		for (int32 CurrentLoopIndex = 0; CurrentLoopIndex < DirectionIndex; CurrentLoopIndex++)
		{
			FaceDataIndex += FaceDirectionAmount[LFPVoxelRendererConstantData::FaceLoopDirectionList[CurrentLoopIndex].Z];
		}

		check(FaceDataList.IsValidIndex(FaceDataIndex + FaceIndex));

		return FaceDataList[FaceDataIndex + FaceIndex];
	}

	FORCEINLINE void GenerateFaceData(FStaticMeshVertexBuffer& VertexDataBuffer, FPositionVertexBuffer& PositionVertexBuffer, FDynamicMeshIndexBuffer32& IndexBuffer, FColorVertexBuffer& ColorVertexBuffer) const
	{
		TArray<FVector3f> VertexPosList;

		const int32 VertexAmount = TriangleCount * 3;

		VertexPosList.Reserve(VertexAmount);
		IndexBuffer.Indices.Reserve(VertexAmount);

		VertexDataBuffer.Init(VertexAmount, 1);

		ColorVertexBuffer.InitFromSingleColor(FColor(255), VertexAmount);

		int32 CurrentFaceIndex = 0;

		for (const auto& FaceData : FaceDataList)
		{
			int32 CurrentRotationIndex = 0;
			{
				int32 CheckFaceAmount = FaceDirectionAmount[LFPVoxelRendererConstantData::FaceLoopDirectionList[0].Z];

				for (CurrentRotationIndex = 0; CurrentRotationIndex < 5; CurrentRotationIndex++)
				{
					if (CheckFaceAmount > CurrentFaceIndex)
					{
						break;
					}

					CheckFaceAmount += FaceDirectionAmount[LFPVoxelRendererConstantData::FaceLoopDirectionList[CurrentRotationIndex + 1].Z];
				}
			}

			const auto& FaceDirectionData = LFPVoxelRendererConstantData::FaceDirection[CurrentRotationIndex];

			const uint32 StartIndex = VertexPosList.Num();

			for (const uint32 Index : FaceData.TriangleIndexList)
			{
				const uint32 CurrentIndex = Index + StartIndex;

				IndexBuffer.Indices.Emplace(CurrentIndex);

				VertexDataBuffer.SetVertexUV(CurrentIndex, 0, FaceData.UVList[Index]);

				VertexDataBuffer.SetVertexTangents(CurrentIndex, FVector3f(FaceDirectionData.Forward), FVector3f(FaceDirectionData.Right), FVector3f(FaceDirectionData.Up));
			}

			VertexPosList.Append(FaceData.VertexList);

			CurrentFaceIndex++;
		}

		PositionVertexBuffer.Init(VertexPosList, true);
	}
};

struct FLFPVoxelRendererThreadResult
{
	TArray<FLFPVoxelRendererSectionData> SectionData = TArray<FLFPVoxelRendererSectionData>();

	FBox RenderBounds = FBox(EForceInit::ForceInitToZero);

	class FDistanceFieldVolumeData* DistanceFieldMeshData = nullptr;

	class FCardRepresentationData* LumenCardData = nullptr;

public:

	FORCEINLINE void Init(const int32 SectionAmount)
	{
		SectionData.Init(FLFPVoxelRendererSectionData(), SectionAmount);
	}

	FORCEINLINE FLFPVoxelRendererSectionData& AddOrFindSectionData(const int32 SectionIndex)
	{
		if (SectionData.Num() <= SectionIndex)
		{
			SectionData.SetNum(SectionIndex + 1);
		}

		return SectionData[SectionIndex];
	}
};

USTRUCT(BlueprintType)
struct FLFPVoxelRendererSetting
{
	GENERATED_BODY()

public:

	/* Generate Distance Field And Lumen */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelRendererSetting")
		bool bGenerateLumenData = false;
};

USTRUCT(BlueprintType)
struct FLFPVoxelRendererStatus
{
	GENERATED_BODY()

public:

	FLFPVoxelRendererStatus() : 
		bIsVoxelAttributeDirty(false), 
		bIsVoxelMeshDirty(false), 
		bIsGeneratingMesh(false), 
		bIsLumenDataDirty(false), 
		bIsGeneratingLumen(false), 
		bIsBodyInvalid(false) 
	{}

	UPROPERTY(VisibleAnywhere, Category = "VoxelRendererStatus") uint8 bIsVoxelAttributeDirty : 1;

	UPROPERTY(VisibleAnywhere, Category = "VoxelRendererStatus") uint8 bIsVoxelMeshDirty : 1;

	UPROPERTY(VisibleAnywhere, Category = "VoxelRendererStatus") uint8 bIsGeneratingMesh : 1;

	UPROPERTY(VisibleAnywhere, Category = "VoxelRendererStatus") uint8 bIsLumenDataDirty : 1;

	UPROPERTY(VisibleAnywhere, Category = "VoxelRendererStatus") uint8 bIsGeneratingLumen : 1;

	UPROPERTY(VisibleAnywhere, Category = "VoxelRendererStatus") uint8 bIsBodyInvalid : 1;
};

class ULFPVoxelContainerComponent;

/**
 * 
 */
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent), ClassGroup = (LFPlugin))
class LOHFUNCTIONPLUGIN_API ULFPVoxelRendererComponent : public UMeshComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULFPVoxelRendererComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public: /** Debugging */

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelRendererComponent | Function")
		FORCEINLINE FString Test();

public:

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelRendererComponent | Setter")
		FORCEINLINE bool InitializeRenderer(const int32 RegionIndex, const int32 ChuckIndex, ULFPVoxelContainerComponent* NewVoxelContainer);

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelRendererComponent | Setter")
		FORCEINLINE bool ReleaseRenderer();

public:

	UFUNCTION(BlueprintPure, Category = "LFPVoxelRendererComponent | Checker")
		FORCEINLINE bool IsFaceVisible(const FLFPVoxelPaletteData& FromPaletteData, const FLFPVoxelPaletteData& ToPaletteData) const;

public:

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelRendererComponent | Function")
		FORCEINLINE void SetMaterialList(const TArray<UMaterialInterface*>& Material);

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelRendererComponent | Function")
		FORCEINLINE void UpdateMesh();

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelRendererComponent | Function")
		FORCEINLINE void UpdateAttribute();

public:

	UFUNCTION()
		FORCEINLINE void CreateFace();

public:

	UFUNCTION()
		FORCEINLINE void OnChuckUpdate(const FLFPChuckUpdateAction& Data);

protected: /** Can be override to provide custom behavir */

	UFUNCTION()
		virtual FColor GetVoxelAttribute(const FLFPVoxelPaletteData& VoxelPalette) const;

	UFUNCTION()
		virtual int32 GetVoxelMaterialIndex(const FLFPVoxelPaletteData& VoxelPalette) const;

public:

	FORCEINLINE const TSharedPtr<FLFPVoxelRendererThreadResult>& GetThreadResult() const;

protected: // Rendering Handler

	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;

	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;

public: // Material Handler

	virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override;

	/*virtual UMaterialInterface* GetMaterialFromCollisionFaceIndex(int32 FaceIndex, int32& SectionIndex) const override;*/

	virtual int32 GetNumMaterials() const override;

	virtual UMaterialInterface* GetMaterial(int32 ElementIndex) const override;

	virtual void SetMaterial(int32 ElementIndex, UMaterialInterface* Material) override;

	/* This Create Dynamic Material Instance And Apply VoxelDataTexture And VoxelColorTexture To It (Use Name On Texture Parameter : VoxelDataTexture or VoxelColorTexture) */
	virtual UMaterialInstanceDynamic* CreateDynamicMaterialInstance(int32 ElementIndex, class UMaterialInterface* SourceMaterial, FName OptionalName) override;
//
//public: // Collision Handler
//
//	virtual bool GetPhysicsTriMeshData(struct FTriMeshCollisionData* CollisionData, bool InUseAllTriData) override;
//
//	virtual bool ContainsPhysicsTriMeshData(bool InUseAllTriData) const override;
//
//	virtual bool WantsNegXTriMesh() override;
//
//	virtual UBodySetup* GetBodySetup() override;
//
//	FORCEINLINE UBodySetup* CreateBodySetup();
//
//	FORCEINLINE void RebuildPhysicsData();
//
//	FORCEINLINE void FinishPhysicsAsyncCook(bool bSuccess, UBodySetup* FinishedBodySetup);

protected:

	UPROPERTY(VisibleAnywhere, Category = "LFPVoxelRendererComponent")
		FLFPVoxelRendererStatus Status;

public:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPVoxelRendererComponent | Cache")
		TObjectPtr<UTexture2D> AttributesTexture = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "LFPVoxelRendererComponent | Cache")
		TObjectPtr<ULFPVoxelContainerComponent> VoxelContainer = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "LFPVoxelRendererComponent | Cache")
		int32 RegionIndex = INDEX_NONE;
		
	UPROPERTY(BlueprintReadOnly, Category = "LFPVoxelRendererComponent | Cache")
		int32 ChuckIndex = INDEX_NONE;

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPVoxelRendererComponent | Setting")
		FLFPVoxelRendererSetting Setting = FLFPVoxelRendererSetting();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, AdvancedDisplay, Category = Lighting)
		float DistanceFieldSelfShadowBias = 1.0f;

private:

	UPROPERTY() TArray<TObjectPtr<UMaterialInterface>> MaterialList;

	UPROPERTY(Instanced) TObjectPtr<UBodySetup> BodySetup;
	

	TSharedPtr<FLFPVoxelRendererThreadResult> ThreadResult;
	UE::Tasks::FTask WorkThread;
};
