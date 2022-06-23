// Copyright by Loh Zhi Kang


#include "Mesh/VoxelDynamicMeshComponent.h"
#include "DynamicMesh/MeshTransforms.h"
#include "Mesh/BaseVoxelMesh.h"
#include "Engine/CollisionProfile.h"

#include "Mesh/VoxelDynamicMeshSceneProxy.h"

using namespace UE::Geometry;

UVoxelDynamicMeshComponent::UVoxelDynamicMeshComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;

	SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

	VoxelMeshObject = CreateDefaultSubobject<UBaseVoxelMesh>(TEXT("BaseVoxelMesh"));
	MeshObjectChangedHandle = VoxelMeshObject->OnMeshChanged().AddUObject(this, &UVoxelDynamicMeshComponent::OnMeshObjectChanged);
	MeshObjectSectionHandle = VoxelMeshObject->OnSectionUpdate().AddUObject(this, &UVoxelDynamicMeshComponent::MarkSectionListDirty);

	ResetProxy();
}

UVoxelDynamicMeshComponent::~UVoxelDynamicMeshComponent()
{
	VoxelMeshObject = nullptr;
	MeshObjectChangedHandle.Reset();
	MeshObjectSectionHandle.Reset();
}

void UVoxelDynamicMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (TickCounter >= 5)
	{
		TickCounter = 0;

		if (UpdateMode != EVoxelDynamicMeshComponentUpdateMode::NoUpdate)
		{
			NotifyMeshUpdated();
		}
	}

	TickCounter++;
}

void UVoxelDynamicMeshComponent::ProcessMesh(
	TFunctionRef<void(const UE::Geometry::FDynamicMesh3&)> ProcessFunc) const
{
	VoxelMeshObject->ProcessMesh(ProcessFunc);
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
		SetUpdateMode(EVoxelDynamicMeshComponentUpdateMode::FastUpdate);
	}
	else
	{
		SetUpdateMode(EVoxelDynamicMeshComponentUpdateMode::SectionUpdate);
	}

	// Rebuild body setup.
	//InvalidatePhysicsData();
}

bool UVoxelDynamicMeshComponent::GetPhysicsTriMeshData(struct FTriMeshCollisionData* CollisionData, bool InUseAllTriData)
{
	ProcessMesh([&](const FDynamicMesh3& Mesh)
		{
			TArray<int32> VertexMap;
			bool bIsSparseV = !Mesh.IsCompactV();
			if (bIsSparseV)
			{
				VertexMap.SetNum(Mesh.MaxVertexID());
			}

			// copy vertices
			CollisionData->Vertices.Reserve(Mesh.VertexCount());
			for (int32 vid : Mesh.VertexIndicesItr())
			{
				int32 Index = CollisionData->Vertices.Add((FVector3f)Mesh.GetVertex(vid));
				if (bIsSparseV)
				{
					VertexMap[vid] = Index;
				}
				else
				{
					check(vid == Index);
				}
			}

			// copy triangles
			CollisionData->Indices.Reserve(Mesh.TriangleCount());
			CollisionData->MaterialIndices.Reserve(Mesh.TriangleCount());
			for (int tid : Mesh.TriangleIndicesItr())
			{
				FIndex3i Tri = Mesh.GetTriangle(tid);
				FTriIndices Triangle;
				Triangle.v0 = (bIsSparseV) ? VertexMap[Tri.A] : Tri.A;
				Triangle.v1 = (bIsSparseV) ? VertexMap[Tri.B] : Tri.B;
				Triangle.v2 = (bIsSparseV) ? VertexMap[Tri.C] : Tri.C;
				CollisionData->Indices.Add(Triangle);

				CollisionData->MaterialIndices.Add(0);		// not supporting physical materials yet
			}

			CollisionData->bFlipNormals = true;
			//CollisionData->bDeformableMesh = true;
			CollisionData->bFastCook = true;
		});

	return true;
}

bool UVoxelDynamicMeshComponent::ContainsPhysicsTriMeshData(bool InUseAllTriData) const
{
	return (VoxelMeshObject != nullptr) && (VoxelMeshObject->GetTriangleCount() > 0);
}

bool UVoxelDynamicMeshComponent::WantsNegXTriMesh()
{
	return true;
}

UBodySetup* UVoxelDynamicMeshComponent::GetBodySetup()
{
	if (MeshBodySetup == nullptr)
	{
		MeshBodySetup = GetBodySetupHelper();
	}

	return MeshBodySetup;
}

UBodySetup* UVoxelDynamicMeshComponent::GetBodySetupHelper()
{
	UBodySetup* NewBodySetup = NewObject<UBodySetup>(this, NAME_None, (IsTemplate() ? RF_Public | RF_ArchetypeObject : RF_NoFlags));
	NewBodySetup->BodySetupGuid = FGuid::NewGuid();

	NewBodySetup->bGenerateMirroredCollision = false;
	NewBodySetup->CollisionTraceFlag = ECollisionTraceFlag::CTF_UseComplexAsSimple;

	NewBodySetup->DefaultInstance.SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	NewBodySetup->bSupportUVsAndFaceRemap = false; /* bSupportPhysicalMaterialMasks; */

	return NewBodySetup;
}

void UVoxelDynamicMeshComponent::RebuildPhysicsData()
{
	AsyncBodySetupQueue.Add(GetBodySetupHelper());

	UBodySetup* UseBodySetup = AsyncBodySetupQueue.Last();

	if (UseBodySetup)
	{
		UseBodySetup->CreatePhysicsMeshesAsync(FOnAsyncPhysicsCookFinished::CreateUObject(this, &UVoxelDynamicMeshComponent::FinishPhysicsAsyncCook, UseBodySetup));
		
		//MeshBodySetup->InvalidatePhysicsData();
		//// Also we want cooked data for this
		//MeshBodySetup->bHasCookedCollisionData = true;
		//
		//MeshBodySetup->CreatePhysicsMeshes();
		//RecreatePhysicsState();
	}
}

void UVoxelDynamicMeshComponent::FinishPhysicsAsyncCook(bool bSuccess, UBodySetup* FinishedBodySetup)
{
	TArray<UBodySetup*> NewQueue;
	NewQueue.Reserve(AsyncBodySetupQueue.Num());


	int32 FoundIdx;
	if (AsyncBodySetupQueue.Find(FinishedBodySetup, FoundIdx))
	{
		if (bSuccess)
		{
			//The new body was found in the array meaning it's newer so use it
			MeshBodySetup = FinishedBodySetup;
			RecreatePhysicsState();

			//remove any async body setups that were requested before this one
			for (int32 AsyncIdx = FoundIdx + 1; AsyncIdx < AsyncBodySetupQueue.Num(); ++AsyncIdx)
			{
				NewQueue.Add(AsyncBodySetupQueue[AsyncIdx]);
			}

			AsyncBodySetupQueue = NewQueue;
		}
		else
		{
			AsyncBodySetupQueue.RemoveAt(FoundIdx);
		}
	}
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

	SetUpdateMode(EVoxelDynamicMeshComponentUpdateMode::FullUpdate);
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
		VoxelMeshObject->OnSectionUpdate().Remove(MeshObjectSectionHandle);
	}

	VoxelMeshObject = NewVoxelMesh;
	MeshObjectChangedHandle = VoxelMeshObject->OnMeshChanged().AddUObject(this, &UVoxelDynamicMeshComponent::OnMeshObjectChanged);
	MeshObjectSectionHandle = VoxelMeshObject->OnSectionUpdate().AddUObject(this, &UVoxelDynamicMeshComponent::MarkSectionListDirty);

	ConfigureMaterialSet(GetMaterials());

	SetUpdateMode(EVoxelDynamicMeshComponentUpdateMode::FullUpdate);

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

void UVoxelDynamicMeshComponent::UpdateProxySection()
{
	if (bProxyValid && GetCurrentSceneProxy())
	{
		InvalidateAutoCalculatedTangents();
		GetCurrentSceneProxy()->UpdateSectionList(DirtySectionIndexList.Array(), VoxelMeshObject->GetSectionTriangleList());
		DirtySectionIndexList.Empty();
		UpdateLocalBounds();
		UpdateBounds();

		GetDynamicMesh()->PostRealtimeUpdate();
	}
	else
	{
		ResetProxy();
	}
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
