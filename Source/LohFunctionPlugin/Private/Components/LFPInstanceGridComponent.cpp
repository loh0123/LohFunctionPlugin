// Copyright by Loh Zhi Kang


#include "Components/LFPInstanceGridComponent.h"
#include "Components/LFPWorldGrid.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Math/LFPGridLibrary.h"

// Sets default values for this component's properties
ULFPInstanceGridComponent::ULFPInstanceGridComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void ULFPInstanceGridComponent::BeginPlay()
{
	Super::BeginPlay();

	SetupGrid(Cast<ULFPWorldGrid>(GetAttachParent()));

	for (int32 Index = 0; Index < GetNumChildrenComponents(); Index++)
	{
		RegisterInstanceStaticMeshComponent(Cast<UInstancedStaticMeshComponent>(GetChildComponent(Index)));
	}
}

void ULFPInstanceGridComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}


// Called every frame
void ULFPInstanceGridComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool ULFPInstanceGridComponent::IsMeshIndexValid(const int32 Index) const
{
	return MeshList.IsValidIndex(Index) && IsValid(MeshList[Index].ISMComponent);
}

void ULFPInstanceGridComponent::SetupGrid(ULFPWorldGrid* NewWorldGrid)
{
	WorldGrid = NewWorldGrid;

	if (IsValid(WorldGrid))
	{
		GridInstanceIndexList.Init(INDEX_NONE, WorldGrid->GetGridSize().X * WorldGrid->GetGridSize().Y * WorldGrid->GetGridSize().Z);
	}
	else
	{
		GridInstanceIndexList.Empty();
	}

	return;
}

int32 ULFPInstanceGridComponent::RegisterInstanceStaticMeshComponent(UInstancedStaticMeshComponent* ISM)
{
	if (IsValid(ISM) == false)
	{
		return INDEX_NONE;
	}

	return MeshList.Add(FLFPInstanceGridMeshData(ISM));
}

int32 ULFPInstanceGridComponent::RegisterInstanceStaticMeshComponentList(TArray<UInstancedStaticMeshComponent*> ISMList)
{
	int32 Count = 0;

	for (UInstancedStaticMeshComponent* ISM : ISMList)
	{
		if (IsValid(ISM))
		{
			MeshList.Add(FLFPInstanceGridMeshData(ISM));

			Count++;
		}
	}

	return Count;
}

bool ULFPInstanceGridComponent::SetInstance(const FLFPInstanceGridInstanceInfo& InstanceInfo)
{
	if (IsValid(WorldGrid) == false) return false;

	const int32 GridIndex = ULFPGridLibrary::ToIndex(InstanceInfo.Location, WorldGrid->GetGridSize());

	if (GridInstanceIndexList.IsValidIndex(GridIndex) == false) return false;
	
	/* Calculate Instance Transform With Offset */
	FVector InstanceWorldLocation;
	FRotator InstanceWorldRotation;

	WorldGrid->GridLocationToWorldLocation(InstanceInfo.Location, InstanceInfo.bIsWorld, InstanceWorldLocation, InstanceWorldRotation);

	FTransform TargetTransform(InstanceWorldRotation + InstanceInfo.RotationOffset, InstanceWorldLocation + InstanceInfo.LocationOffset, InstanceInfo.Scale);

	///////////////////////////////////////////////

	/* Find The Prev Data Is Valid And Remove Or Update It */
	if (GridInstanceIndexList[GridIndex] != INDEX_NONE && IsMeshIndexValid(GridInstanceIndexList[GridIndex]))
	{
		FLFPInstanceGridMeshData& ISMData = MeshList[GridInstanceIndexList[GridIndex]];

		const int32 TargetIndex = ISMData.InstanceGridIndexList.Find(GridIndex);

		check(TargetIndex != INDEX_NONE);

		/* Same Instance So Just Update Transform */
		if (GridInstanceIndexList[GridIndex] == InstanceInfo.InstanceIndex)
		{
			ISMData.ISMComponent->UpdateInstanceTransform(TargetIndex, TargetTransform, InstanceInfo.bIsWorld, true);

			return true;
		}

		/* Remove Operation */
		else
		{
			ISMData.InstanceGridIndexList.RemoveAt(TargetIndex);
			ISMData.ISMComponent->RemoveInstance(TargetIndex);

			GridInstanceIndexList[GridIndex] = INDEX_NONE;
		}
	}

	/* Add Operation */
	if (IsMeshIndexValid(InstanceInfo.InstanceIndex))
	{
		GridInstanceIndexList[GridIndex] = InstanceInfo.InstanceIndex;

		FLFPInstanceGridMeshData& ISMData = MeshList[InstanceInfo.InstanceIndex];

		ISMData.ISMComponent->AddInstance(TargetTransform, InstanceInfo.bIsWorld);

		ISMData.InstanceGridIndexList.Add(GridIndex);
	}

	return true;
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

bool ULFPInstanceGridComponent::SetCustomData(const FIntVector Location, const int32 DataIndex, const float DataValue, const bool bMarkRenderStateDirty)
{
	if (IsValid(WorldGrid) == false) return false;

	const int32 GridIndex = ULFPGridLibrary::ToIndex(Location, WorldGrid->GetGridSize());

	if (GridInstanceIndexList.IsValidIndex(GridIndex))
	{
		if (IsMeshIndexValid(GridInstanceIndexList[GridIndex]))
		{
			FLFPInstanceGridMeshData& ISMData = MeshList[GridInstanceIndexList[GridIndex]];

			const int32 TargetIndex = ISMData.InstanceGridIndexList.Find(GridIndex);

			return ISMData.ISMComponent->SetCustomDataValue(TargetIndex, DataIndex, DataValue, bMarkRenderStateDirty);
		}
	}

	return false;
}

bool ULFPInstanceGridComponent::SetCustomDatas(const FIntVector Location, const TArray<float>& DataList, const bool bMarkRenderStateDirty)
{
	if (IsValid(WorldGrid) == false) return false;

	const int32 GridIndex = ULFPGridLibrary::ToIndex(Location, WorldGrid->GetGridSize());

	if (GridInstanceIndexList.IsValidIndex(GridIndex))
	{
		if (IsMeshIndexValid(GridInstanceIndexList[GridIndex]))
		{
			FLFPInstanceGridMeshData& ISMData = MeshList[GridInstanceIndexList[GridIndex]];

			const int32 TargetIndex = ISMData.InstanceGridIndexList.Find(GridIndex);

			return ISMData.ISMComponent->SetCustomData(TargetIndex, DataList, bMarkRenderStateDirty);
		}
	}

	return false;
}

