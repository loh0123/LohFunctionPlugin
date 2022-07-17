// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/MeshComponent.h"
#include "LFPBaseVoxelMeshComponent.generated.h"

class FLFPBaseVoxelMeshSceneProxy;

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), ClassGroup = Rendering)
class LOHFUNCTIONPLUGIN_API ULFPBaseVoxelMeshComponent : public UMeshComponent
{
	GENERATED_BODY()
	
protected:

	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;

protected:

	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
};
