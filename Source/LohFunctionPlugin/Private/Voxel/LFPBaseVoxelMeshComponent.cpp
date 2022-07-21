// Copyright by Loh Zhi Kang


#include "Voxel/LFPBaseVoxelMeshComponent.h"

#include "Voxel/LFPBaseVoxelMeshSceneProxy.h"

void ULFPBaseVoxelMeshComponent::SetVoxelContainer(ULFPVoxelContainer* NewVoxelContainer, const int32 NewChuckIndex)
{
	VoxelContainer = NewVoxelContainer;

	if (VoxelContainer != nullptr && VoxelContainer->IsChuckIndexValid(NewChuckIndex))
	{
		ChuckIndex = NewChuckIndex;

		VoxelStartLocation = VoxelContainer->GetChuckStartVoxelLocation(ChuckIndex);
	}

	MarkRenderStateDirty();
}

void ULFPBaseVoxelMeshComponent::SetVoxelMaterial(const TArray<UMaterialInterface*>& Material)
{
	if (Material.IsEmpty() == false)
	{
		for (int k = 0; k < Material.Num(); ++k)
		{
			SetMaterial(k, Material[k]);
		}

		ProxyBufferData.Init(FVoxelMeshBufferData(), Material.Num());
	}

	MarkRenderStateDirty();
}

FPrimitiveSceneProxy* ULFPBaseVoxelMeshComponent::CreateSceneProxy()
{
	return new FLFPBaseVoxelMeshSceneProxy(this);
}

FBoxSphereBounds ULFPBaseVoxelMeshComponent::CalcBounds(const FTransform& LocalToWorld) const
{
	FBox LocalBoundingBox = FBox(FVector3d(-100), FVector3d(100));
	FBoxSphereBounds Ret(LocalBoundingBox.TransformBy(LocalToWorld));
	Ret.BoxExtent *= BoundsScale;
	Ret.SphereRadius *= BoundsScale;

	return Ret;
}
