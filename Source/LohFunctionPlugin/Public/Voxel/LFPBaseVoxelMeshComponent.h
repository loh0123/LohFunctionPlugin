// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/MeshComponent.h"
#include "Voxel/LFPVoxelContainer.h"
#include "LFPBaseVoxelMeshComponent.generated.h"

USTRUCT()
struct FVoxelMeshBufferData
{
	GENERATED_USTRUCT_BODY()

public:

	/** Raw Vertex Generated For The Function */
	UPROPERTY() TArray<FVector3f> VertexList;

	/** Raw Triangle Index Generated For The Function */
	UPROPERTY() TArray<int32> TriangleIndexList;

	/** Raw Vertex Generated For The Function */
	UPROPERTY() TArray<FVector2f> UVList;

	/** Voxel Index For The Generated Vertex To Get Attribute Data */
	UPROPERTY() TArray<uint32> VoxelIndexList;

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

	UFUNCTION(BlueprintCallable, Category = "LFPBaseVoxelMeshComponent | Function")
		FORCEINLINE void SetVoxelContainer(ULFPVoxelContainer* NewVoxelContainer, const int32 NewChuckIndex);

	UFUNCTION(BlueprintCallable, Category = "LFPBaseVoxelMeshComponent | Function")
		FORCEINLINE void SetVoxelMaterial(const TArray<UMaterialInterface*>& Material);
	
protected:

	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;

protected:

	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;

protected:

	UPROPERTY() TArray<FVoxelMeshBufferData> ProxyBufferData;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPBaseVoxelMeshComponent | Cache")
		TObjectPtr<ULFPVoxelContainer> VoxelContainer = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPBaseVoxelMeshComponent | Cache")
		FIntVector VoxelStartLocation = FIntVector(0);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPBaseVoxelMeshComponent | Cache")
		int32 ChuckIndex = INDEX_NONE;
};
