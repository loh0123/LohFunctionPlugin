// Copyright by Loh Zhi Kang


#include "Voxel/LFPBaseVoxelMeshComponent.h"
#include "./Math/LFPGridLibrary.h"
#include "Voxel/LFPBaseVoxelMeshSceneProxy.h"

DEFINE_LOG_CATEGORY(LFPVoxelMeshComponentLog);

ULFPBaseVoxelMeshComponent::ULFPBaseVoxelMeshComponent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;
	//PrimaryComponentTick.bRunOnAnyThread = true;

}

void ULFPBaseVoxelMeshComponent::SetVoxelContainer(ULFPVoxelContainer* NewVoxelContainer, const int32 NewChuckIndex, const FVector NewVoxelHalfSize)
{
	VoxelContainer = NewVoxelContainer;

	if (VoxelContainer != nullptr && VoxelContainer->IsChuckIndexValid(NewChuckIndex))
	{
		ChuckIndex = NewChuckIndex;

		VoxelStartLocation = VoxelContainer->GetChuckStartVoxelLocation(ChuckIndex);

		VoxelHalfSize = NewVoxelHalfSize.GetMin() >= 10.0f ? NewVoxelHalfSize : FVector(100);

		VoxelContainer->ConnectVoxelUpdateEvent(ChuckIndex, this, &ULFPBaseVoxelMeshComponent::UpdateVoxelMesh);

		VoxelContainer->InitializeOrUpdateChuck(ChuckIndex);
	}
	else
	{
		UE_LOG(LFPVoxelMeshComponentLog, Warning, TEXT("Can't Setup Voxel Container Because Is Null Or Invalid Chuck"));
	}
}

void ULFPBaseVoxelMeshComponent::SetVoxelMaterial(const TArray<UMaterialInterface*>& Material)
{
	if (Material.IsEmpty() == false)
	{
		for (int k = 0; k < Material.Num(); ++k)
		{
			SetMaterial(k, Material[k]);
		}

		UpdateVoxelMesh();
	}
	else
	{
		UE_LOG(LFPVoxelMeshComponentLog, Warning, TEXT("Can't Set Material Because Array Is Empty"));
	}
}

void ULFPBaseVoxelMeshComponent::UpdateVoxelMesh()
{
	if (VoxelContainer == nullptr)
	{
		UE_LOG(LFPVoxelMeshComponentLog, Warning, TEXT("Voxel Mesh Can't Be Update Because Voxel Container Is Null"));

		return;
	}

	IsVoxelMeshDirty = true;
}

void ULFPBaseVoxelMeshComponent::AddVoxelFace(FVoxelMeshBufferData& EditMesh, const FVector3f VoxelLocation, const int32 FaceIndex, const FColor VoxelColor)
{
	const uint32 StartIndex = EditMesh.VertexList.Num();

	bool FlipTriangleIndex = true;

	switch (FaceIndex)
	{
	case 0 : EditMesh.VertexList.Append({ 
		FVector3f(-VoxelHalfSize.X,-VoxelHalfSize.Y,VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X,VoxelHalfSize.Y,VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(VoxelHalfSize.X,-VoxelHalfSize.Y,VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(VoxelHalfSize.X,VoxelHalfSize.Y,VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(VoxelHalfSize.X,-VoxelHalfSize.Y,VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X,VoxelHalfSize.Y,VoxelHalfSize.Z) + VoxelLocation,
		});
		FlipTriangleIndex = false;
		break;
	case 1 : EditMesh.VertexList.Append({
		FVector3f(-VoxelHalfSize.X,-VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X,-VoxelHalfSize.Y,VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X,VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X,VoxelHalfSize.Y,VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X,VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X,-VoxelHalfSize.Y,VoxelHalfSize.Z) + VoxelLocation,
		});
		break;
	case 2 : EditMesh.VertexList.Append({
		FVector3f(-VoxelHalfSize.X,VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X,VoxelHalfSize.Y,VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(VoxelHalfSize.X,VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(VoxelHalfSize.X,VoxelHalfSize.Y,VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(VoxelHalfSize.X,VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X,VoxelHalfSize.Y,VoxelHalfSize.Z) + VoxelLocation,
		});
		break;
	case 3 : EditMesh.VertexList.Append({
		FVector3f(VoxelHalfSize.X,VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(VoxelHalfSize.X,VoxelHalfSize.Y,VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(VoxelHalfSize.X,-VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(VoxelHalfSize.X,-VoxelHalfSize.Y,VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(VoxelHalfSize.X,-VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(VoxelHalfSize.X,VoxelHalfSize.Y,VoxelHalfSize.Z) + VoxelLocation,
		});
		break;
	case 4 : EditMesh.VertexList.Append({
		FVector3f(VoxelHalfSize.X,-VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(VoxelHalfSize.X,-VoxelHalfSize.Y,VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X,-VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X,-VoxelHalfSize.Y,VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X,-VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(VoxelHalfSize.X,-VoxelHalfSize.Y,VoxelHalfSize.Z) + VoxelLocation,
		});
		break;
	case 5 : EditMesh.VertexList.Append({
		FVector3f(VoxelHalfSize.X,-VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X,-VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(VoxelHalfSize.X,VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X,VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(VoxelHalfSize.X,VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		FVector3f(-VoxelHalfSize.X,-VoxelHalfSize.Y,-VoxelHalfSize.Z) + VoxelLocation,
		});
		break;
	}

	if (FlipTriangleIndex)
	{
		EditMesh.TriangleIndexList.Append({ 5 + StartIndex,4 + StartIndex,3 + StartIndex,2 + StartIndex,1 + StartIndex, StartIndex });
	}
	else
	{
		EditMesh.TriangleIndexList.Append({ StartIndex,1 + StartIndex,2 + StartIndex,3 + StartIndex,4 + StartIndex,5 + StartIndex });
	}

	EditMesh.UVList.Append({ FVector2f(0.0f,0.0f),FVector2f(0.0f,1.0f),FVector2f(1.0f,0.0f),FVector2f(1.0f,1.0f),FVector2f(1.0f,0.0f),FVector2f(0.0f,1.0f) });

	EditMesh.VoxelColorList.Append({ VoxelColor ,VoxelColor ,VoxelColor ,VoxelColor ,VoxelColor ,VoxelColor });

	EditMesh.TriangleCount += 2;
}

int32 ULFPBaseVoxelMeshComponent::GetVoxelLength() const
{
	return VoxelContainer != nullptr ? VoxelContainer->GetContainerSetting().VoxelLength : INDEX_NONE;
}

void ULFPBaseVoxelMeshComponent::GetVoxelAttributeList(TArray<FLFPVoxelAttributeV2>& VoxelAttributeList, TBitArray<>& VisibleList)
{
	check(VoxelContainer != nullptr);
	check(VoxelContainer->IsChuckInitialized(ChuckIndex));

	VoxelAttributeList.Empty(VoxelContainer->GetContainerSetting().VoxelLength);
	VisibleList.Init(false, VoxelContainer->GetContainerSetting().VoxelLength);

	int32 Index = 0;

	for (const FName& VoxelName : VoxelContainer->GetVoxelNameList(ChuckIndex))
	{
		VoxelAttributeList.Add(VoxelContainer->GetVoxelAttributeByName(VoxelName));

		VisibleList[Index++] = VoxelContainer->IsVoxelVisibleByName(VoxelName);
	}
}

const TArray<FVoxelMeshBufferData>& ULFPBaseVoxelMeshComponent::GetVoxelMesh()
{
	return VoxelMesh;
}

void ULFPBaseVoxelMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (IsVoxelMeshDirty)
	{
		IsVoxelMeshDirty = false;

		VoxelMesh.Init(FVoxelMeshBufferData(), FMath::Max(GetNumOverrideMaterials(), 1));

		TArray<FName> VoxelNameList = VoxelContainer->GetVoxelNameList(ChuckIndex);

		TArray<FIntVector> FaceCheckDirection = {
			FIntVector(0,0,1),
			FIntVector(-1,0,0),
			FIntVector(0,1,0),
			FIntVector(1,0,0),
			FIntVector(0,-1,0),
			FIntVector(0,0,-1),
		};

		for (int32 VoxelIndex = 0; VoxelIndex < VoxelContainer->GetContainerSetting().VoxelLength; VoxelIndex++)
		{
			const FIntVector VoxelGridLocation = ULFPGridLibrary::IndexToGridLocation(VoxelIndex, VoxelContainer->GetContainerSetting().VoxelGridSize);

			const FVector3f VoxelLocation = ((FVector3f)VoxelGridLocation) * ((FVector3f)VoxelHalfSize * 2);

			const FLFPVoxelAttributeV2& VoxelAttribute = VoxelContainer->GetVoxelAttributeByName(VoxelNameList[VoxelIndex]);

			if (VoxelContainer->IsVoxelVisibleByName(VoxelNameList[VoxelIndex]))
			{
				for (int32 FaceIndex = 0; FaceIndex < 6; FaceIndex++)
				{
					if (VoxelContainer->IsVoxelVisible(VoxelGridLocation + FaceCheckDirection[FaceIndex] + VoxelStartLocation) == false)
					{
						AddVoxelFace(VoxelMesh[VoxelAttribute.MaterialID < GetNumOverrideMaterials() ? VoxelAttribute.MaterialID : 0], VoxelLocation, FaceIndex, VoxelAttribute.VertexColor);
					}
				}
			}
		}

		MarkRenderStateDirty();
	}
}

FPrimitiveSceneProxy* ULFPBaseVoxelMeshComponent::CreateSceneProxy()
{
	if (VoxelContainer != nullptr && VoxelContainer->IsChuckInitialized(ChuckIndex) && VoxelMesh.Num() != 0 && GetNumMaterials() != 0)
	{
		return new FLFPBaseVoxelMeshSceneProxy(this);
	}
	else
	{
		return nullptr;
	}
}

FBoxSphereBounds ULFPBaseVoxelMeshComponent::CalcBounds(const FTransform& LocalToWorld) const
{
	FBox LocalBoundingBox = FBox(FVector3d(-VoxelHalfSize), VoxelContainer != nullptr ? ((FVector3d)VoxelHalfSize * 2) * ((FVector3d)VoxelContainer->GetContainerSetting().VoxelGridSize) : FVector3d(VoxelHalfSize));
	FBoxSphereBounds Ret(LocalBoundingBox.TransformBy(LocalToWorld));
	Ret.BoxExtent *= BoundsScale;
	Ret.SphereRadius *= BoundsScale;

	return Ret;
}

int32 ULFPBaseVoxelMeshComponent::GetNumMaterials() const
{
	return BaseMaterials.Num();
}

UMaterialInterface* ULFPBaseVoxelMeshComponent::GetMaterial(int32 ElementIndex) const
{
	return (ElementIndex >= 0 && ElementIndex < BaseMaterials.Num()) ? BaseMaterials[ElementIndex] : nullptr;
}

void ULFPBaseVoxelMeshComponent::SetMaterial(int32 ElementIndex, UMaterialInterface* Material)
{
	check(ElementIndex >= 0);
	if (ElementIndex >= BaseMaterials.Num())
	{
		BaseMaterials.SetNum(ElementIndex + 1, false);
	}
	BaseMaterials[ElementIndex] = Material;
}
