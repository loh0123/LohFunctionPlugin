// Copyright by Loh Zhi Kang


#include "Components/LFPInstanceGridComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Math/LFPGridLibrary.h"

// Sets default values for this component's properties
ULFPInstanceGridComponent::ULFPInstanceGridComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULFPInstanceGridComponent::BeginPlay()
{
	Super::BeginPlay();

	SetupGrid(GridSize, GridGap, GridType);
}

void ULFPInstanceGridComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for (FLFPInstanceGridMeshData& ISMData : MeshList)
	{
		ISMData.ISMComponent->DestroyComponent();
	}
}


// Called every frame
void ULFPInstanceGridComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULFPInstanceGridComponent::SetupGrid(const FIntVector NewGridSize, const FVector NewGridGap, const ELFPGridType NewGridType)
{
	GridSize = NewGridSize;
	GridGap = NewGridGap;
	GridType = NewGridType;

	GridInstanceIndexList.Init(0, GridSize.X * GridSize.Y * GridSize.Z);

	for (FLFPInstanceGridMeshData& ISMData : MeshList)
	{
		if (IsValid(ISMData.ISMComponent))
		{
			ISMData.ISMComponent->DestroyComponent(false);
		}

		ISMData.ISMComponent = Cast<UInstancedStaticMeshComponent>(GetOwner()->AddComponentByClass(UInstancedStaticMeshComponent::StaticClass(), true, FTransform(), true));

		ISMData.ISMComponent->SetStaticMesh(ISMData.Mesh);
		ISMData.ISMComponent->NumCustomDataFloats = ISMData.CustomDataAmount;

		for (int32 MaterialIndex = 0; MaterialIndex < ISMData.Material.Num(); MaterialIndex++)
		{
			ISMData.ISMComponent->SetMaterial(MaterialIndex, ISMData.Material[MaterialIndex]);
		}

		ISMData.ISMComponent->SetupAttachment(this);

		GetOwner()->FinishAddComponent(ISMData.ISMComponent, true, FTransform());

		GetOwner()->AddInstanceComponent(ISMData.ISMComponent);
	}
}

bool ULFPInstanceGridComponent::SetInstance(const FLFPInstanceGridInstanceInfo& InstanceInfo)
{
	const int32 GridIndex = ULFPGridLibrary::ToIndex(InstanceInfo.Location, GridSize);

	if (MeshList.IsValidIndex(InstanceInfo.InstanceIndex - 1) && GridInstanceIndexList.IsValidIndex(GridIndex))
	{
		if (GridInstanceIndexList[GridIndex] == InstanceInfo.InstanceIndex)
		{
			return true;
		}
		/* Remove Operation */
		else if (GridInstanceIndexList[GridIndex] != 0)
		{
			FLFPInstanceGridMeshData& ISMData = MeshList[GridInstanceIndexList[GridIndex] - 1];

			const int32 RemoveIndex = ISMData.InstanceGridIndexList.Find(GridIndex);

			check(RemoveIndex != INDEX_NONE);

			ISMData.InstanceGridIndexList.RemoveAt(RemoveIndex);
			ISMData.ISMComponent->RemoveInstance(RemoveIndex);
		}

		GridInstanceIndexList[GridIndex] = InstanceInfo.InstanceIndex;

		/* Add Operation */
		if (GridInstanceIndexList[GridIndex] != 0)
		{
			FVector InstanceWorldLocation;
			FRotator InstanceWorldRotation;

			GridLocationToWorldLocation(InstanceInfo.Location, false, InstanceWorldLocation, InstanceWorldRotation);

			InstanceWorldRotation += InstanceInfo.Rotation;

			FTransform InstanceTransform(InstanceWorldRotation, InstanceWorldLocation);

			FLFPInstanceGridMeshData& ISMData = MeshList[InstanceInfo.InstanceIndex - 1];

			ISMData.ISMComponent->AddInstance(InstanceTransform, true);

			ISMData.InstanceGridIndexList.Add(GridIndex);
		}

		return true;
	}

	return false;
}

bool ULFPInstanceGridComponent::SetInstances(const TArray<FLFPInstanceGridInstanceInfo>& InstanceInfoList)
{
	bool bResult = true;

	for (const FLFPInstanceGridInstanceInfo& Info : InstanceInfoList)
	{
		if (SetInstance(Info) == false)
		{
			bResult = false;
		}
	}

	return bResult;
}

