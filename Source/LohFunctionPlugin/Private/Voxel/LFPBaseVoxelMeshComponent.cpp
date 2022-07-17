// Copyright by Loh Zhi Kang


#include "Voxel/LFPBaseVoxelMeshComponent.h"

#include "Voxel/LFPBaseVoxelMeshSceneProxy.h"

FPrimitiveSceneProxy* ULFPBaseVoxelMeshComponent::CreateSceneProxy()
{
	return new FLFPBaseVoxelMeshSceneProxy(this, 1);
}

FBoxSphereBounds ULFPBaseVoxelMeshComponent::CalcBounds(const FTransform& LocalToWorld) const
{
	FBox LocalBoundingBox = FBox(FVector3d(-100), FVector3d(100));
	FBoxSphereBounds Ret(LocalBoundingBox.TransformBy(LocalToWorld));
	Ret.BoxExtent *= BoundsScale;
	Ret.SphereRadius *= BoundsScale;

	return Ret;
}
