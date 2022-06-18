// Copyright by Loh Zhi Kang


#include "Mesh/VoxelDynamicMeshComponent.h"
#include "DynamicMesh/MeshTransforms.h"
#include "Mesh/BaseVoxelMesh.h"

#include "Mesh/VoxelDynamicMeshSceneProxy.h"

using namespace UE::Geometry;

UVoxelDynamicMeshComponent::UVoxelDynamicMeshComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;

	SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

	VoxelMeshObject = CreateDefaultSubobject<UBaseVoxelMesh>(TEXT("BaseVoxelMesh"));

	ResetProxy();
}

void UVoxelDynamicMeshComponent::ApplyTransform(const FTransform3d& Transform, bool bInvert)
{
	VoxelMeshObject->EditMesh([&](FDynamicMesh3& EditMesh)
		{
			if (bInvert)
			{
				MeshTransforms::ApplyTransformInverse(EditMesh, Transform);
			}
			else
			{
				MeshTransforms::ApplyTransform(EditMesh, Transform);
			}
		}, EDynamicMeshChangeType::DeformationEdit);
}

void UVoxelDynamicMeshComponent::OnMeshObjectChanged(UDynamicMesh* ChangedMeshObject, FDynamicMeshChangeInfo ChangeInfo)
{
	if (ChangeInfo.Type == EDynamicMeshChangeType::AttributeEdit)
	{
		// ToDo : Update Vertex Info
	}
	else
	{
		NotifyMeshUpdated();
	}

	// Rebuild body setup.
	//InvalidatePhysicsData();
}

void UVoxelDynamicMeshComponent::ConfigureMaterialSet(const TArray<UMaterialInterface*>& NewMaterialSet)
{
	if (NewMaterialSet.IsEmpty()) return;

	if (VoxelMeshObject->isVoxelDataValid())
	{
		SetNumMaterials(GetVoxelSectionCount());

		for (int k = 0; k < GetVoxelSectionCount(); ++k)
		{
			SetMaterial(k, NewMaterialSet[k % NewMaterialSet.Num()]);
		}
	}
	else
	{
		for (int k = 0; k < NewMaterialSet.Num(); ++k)
		{
			SetMaterial(k, NewMaterialSet[k]);
		}
	}
}

void UVoxelDynamicMeshComponent::SetVoxelMesh(UBaseVoxelMesh* NewVoxelMesh)
{
	if (ensure(NewVoxelMesh) == false)
	{
		return;
	}

	if (ensure(VoxelMeshObject))
	{
		VoxelMeshObject->OnMeshChanged().Remove(MeshObjectChangedHandle);
	}

	VoxelMeshObject = NewVoxelMesh;
	MeshObjectChangedHandle = VoxelMeshObject->OnMeshChanged().AddUObject(this, &UVoxelDynamicMeshComponent::OnMeshObjectChanged);

	ConfigureMaterialSet(GetMaterials());

	NotifyMeshUpdated();

	// Rebuild physics data
	//InvalidatePhysicsData();
}

void UVoxelDynamicMeshComponent::InvalidateAutoCalculatedTangents()
{
	bAutoCalculatedTangentsValid = false;
}

const UE::Geometry::FMeshTangentsf* UVoxelDynamicMeshComponent::GetAutoCalculatedTangents()
{
	if (GetDynamicMesh()->GetMeshRef().HasAttributes())
	{
		UpdateAutoCalculatedTangents();
		return (bAutoCalculatedTangentsValid) ? &AutoCalculatedTangents : nullptr;
	}
	return nullptr;
}

void UVoxelDynamicMeshComponent::UpdateAutoCalculatedTangents()
{
	if (bAutoCalculatedTangentsValid == false)
	{
		GetDynamicMesh()->ProcessMesh([&](const FDynamicMesh3& Mesh)
			{
				if (Mesh.HasAttributes())
				{
					const FDynamicMeshUVOverlay* UVOverlay = Mesh.Attributes()->PrimaryUV();
					const FDynamicMeshNormalOverlay* NormalOverlay = Mesh.Attributes()->PrimaryNormals();
					if (UVOverlay && NormalOverlay)
					{
						AutoCalculatedTangents.SetMesh(&Mesh);
						AutoCalculatedTangents.ComputeTriVertexTangents(NormalOverlay, UVOverlay, FComputeTangentsOptions());
						AutoCalculatedTangents.SetMesh(nullptr);
					}
				}
			});

		bAutoCalculatedTangentsValid = true;
	}
}

FPrimitiveSceneProxy* UVoxelDynamicMeshComponent::CreateSceneProxy()
{
	ensure(GetCurrentSceneProxy() == nullptr);

	FVoxelDynamicMeshSceneProxy* NewProxy = nullptr;
	if (GetMesh()->TriangleCount() > 0)
	{
		NewProxy = new FVoxelDynamicMeshSceneProxy(this);

		NewProxy->Initialize();

		NewProxy->SetVerifyUsedMaterials(true);
	}

	bProxyValid = true;
	return NewProxy;
}

void UVoxelDynamicMeshComponent::ResetProxy()
{
	bProxyValid = false;
	InvalidateAutoCalculatedTangents();

	// Need to recreate scene proxy to send it over
	MarkRenderStateDirty();
	UpdateLocalBounds();
	UpdateBounds();

	GetDynamicMesh()->PostRealtimeUpdate();
}

void UVoxelDynamicMeshComponent::UpdateLocalBounds()
{
	LocalBounds = GetMesh()->GetBounds(true);
	if (LocalBounds.MaxDim() <= 0)
	{
		// If bbox is empty, set a very small bbox to avoid log spam/etc in other engine systems.
		// The check used is generally IsNearlyZero(), which defaults to KINDA_SMALL_NUMBER, so set 
		// a slightly larger box here to be above that threshold
		LocalBounds = FAxisAlignedBox3d(FVector3d::Zero(), (double)(KINDA_SMALL_NUMBER + SMALL_NUMBER));
	}
}

FBoxSphereBounds UVoxelDynamicMeshComponent::CalcBounds(const FTransform& LocalToWorld) const
{
	// can get a tighter box by calculating in world space, but we care more about performance
	FBox LocalBoundingBox = (FBox)LocalBounds;
	FBoxSphereBounds Ret(LocalBoundingBox.TransformBy(LocalToWorld));
	Ret.BoxExtent *= BoundsScale;
	Ret.SphereRadius *= BoundsScale;
	return Ret;
}

void UVoxelDynamicMeshComponent::PostLoad()
{
	Super::PostLoad();

	check(VoxelMeshObject != nullptr);

	ResetProxy();

	if (MeshBodySetup && IsTemplate())
	{
		MeshBodySetup->SetFlags(RF_Public | RF_ArchetypeObject);
	}

	// make sure BodySetup is created
	GetBodySetup();
}

#if WITH_EDITOR
void UVoxelDynamicMeshComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropName = PropertyChangedEvent.GetPropertyName();
	//if ((PropName == GET_MEMBER_NAME_CHECKED(UVoxelDynamicMeshComponent, bEnableComplexCollision)) ||
	//	(PropName == GET_MEMBER_NAME_CHECKED(UVoxelDynamicMeshComponent, CollisionType)) ||
	//	(PropName == GET_MEMBER_NAME_CHECKED(UVoxelDynamicMeshComponent, bDeferCollisionUpdates)))
	//{
	//	// ToDo : Invalid Physic Data
	//}
}
#endif
