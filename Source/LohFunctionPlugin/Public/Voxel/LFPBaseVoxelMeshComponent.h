// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/MeshComponent.h"
#include "Voxel/LFPVoxelContainer.h"
#include "LFPBaseVoxelMeshComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LFPVoxelMeshComponentLog, Log, All);

USTRUCT()
struct FVoxelMeshBufferData
{
	GENERATED_USTRUCT_BODY()

public:

	/** Raw Vertex Generated For The Function */
	UPROPERTY() TArray<FVector3f> VertexList;

	/** Raw Triangle Index Generated For The Function */
	UPROPERTY() TArray<uint32> TriangleIndexList;

	/** Raw Vertex Generated For The Function */
	UPROPERTY() TArray<FVector2f> UVList;

	/** Color For The Vertex */
	UPROPERTY() TArray<FColor> VoxelColorList;

	/** How Many Triangle Has Been Generated */
	UPROPERTY() int32 TriangleCount = 0;
};

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), ClassGroup = Rendering)
class LOHFUNCTIONPLUGIN_API ULFPBaseVoxelMeshComponent : public UMeshComponent
{
	GENERATED_BODY()

public:

	ULFPBaseVoxelMeshComponent();

public:

	UFUNCTION(BlueprintCallable, Category = "LFPBaseVoxelMeshComponent | Function")
		FORCEINLINE void SetVoxelContainer(ULFPVoxelContainer* NewVoxelContainer, const int32 NewChuckIndex, const FVector NewVoxelHalfSize);

	UFUNCTION(BlueprintCallable, Category = "LFPBaseVoxelMeshComponent | Function")
		FORCEINLINE void SetVoxelMaterial(const TArray<UMaterialInterface*>& Material);

	UFUNCTION(BlueprintCallable, Category = "LFPBaseVoxelMeshComponent | Function")
		FORCEINLINE void UpdateVoxelMesh();

protected:

	FORCEINLINE void AddVoxelFace(FVoxelMeshBufferData& EditMesh, const FVector3f VoxelLocation, const int32 FaceIndex, const FColor VoxelColor);

public:

	FORCEINLINE int32 GetVoxelLength() const;

	FORCEINLINE void GetVoxelAttributeList(TArray<FLFPVoxelAttributeV2>& VoxelAttributeList, TBitArray<>& VisibleList);

	FORCEINLINE const TArray<FVoxelMeshBufferData>& GetVoxelMesh();

protected:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:

	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;

protected:

	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;

public:

	virtual int32 GetNumMaterials() const override;

	virtual UMaterialInterface* GetMaterial(int32 ElementIndex) const override;

	virtual void SetMaterial(int32 ElementIndex, UMaterialInterface* Material) override;

protected:

	UPROPERTY() TArray<FVoxelMeshBufferData> VoxelMesh;

	UPROPERTY() bool IsVoxelMeshDirty = false;

	UPROPERTY() TArray<TObjectPtr<UMaterialInterface>> BaseMaterials;

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPBaseVoxelMeshComponent | Cache")
		TObjectPtr<ULFPVoxelContainer> VoxelContainer = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPBaseVoxelMeshComponent | Cache")
		FIntVector VoxelStartLocation = FIntVector(0);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPBaseVoxelMeshComponent | Cache")
		int32 ChuckIndex = INDEX_NONE;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPBaseVoxelMeshComponent | Cache")
		FVector VoxelHalfSize = FVector(100);
};
