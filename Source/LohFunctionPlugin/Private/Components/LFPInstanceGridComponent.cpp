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
		GridInstanceIndexList = FLFPCompactIntArray(WorldGrid->GetGridSize().X * WorldGrid->GetGridSize().Y * WorldGrid->GetGridSize().Z);

		GridInstanceIndexList.Resize(MeshList.Num());
	}
	else
	{
		GridInstanceIndexList = FLFPCompactIntArray();
	}

	return;
}

int32 ULFPInstanceGridComponent::RegisterInstanceStaticMeshComponent(UInstancedStaticMeshComponent* ISM)
{
	if (IsValid(ISM) == false)
	{
		return INDEX_NONE;
	}

	if (GridInstanceIndexList.GetIndexSize() > 0) GridInstanceIndexList.Resize(MeshList.Num() + 1);

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

	if (GridInstanceIndexList.GetIndexSize() > 0) GridInstanceIndexList.Resize(MeshList.Num());

	return Count;
}

bool ULFPInstanceGridComponent::SetInstance(const FLFPInstanceGridInstanceInfo& InstanceInfo)
{
	if (IsValid(WorldGrid) == false) return false;

	const int32 GridIndex = ULFPGridLibrary::ToGridIndex(InstanceInfo.Location, WorldGrid->GetGridSize());

	if (GridInstanceIndexList.IsValidIndex(GridIndex) == false) return false;
	
	/* Calculate Instance Transform With Offset */
	FVector InstanceWorldLocation;
	FRotator InstanceWorldRotation;

	WorldGrid->GridLocationToWorldLocation(InstanceInfo.Location, InstanceInfo.bAddHalfGap, InstanceWorldLocation, InstanceWorldRotation);

	FTransform TargetTransform(InstanceWorldRotation + InstanceInfo.RotationOffset, InstanceWorldLocation + InstanceInfo.LocationOffset, InstanceInfo.Scale);

	///////////////////////////////////////////////

	/* Find The Prev Data Is Valid And Remove Or Update It */
	if (GridInstanceIndexList.GetIndexNumber(GridIndex) - 1 != INDEX_NONE && IsMeshIndexValid(GridInstanceIndexList.GetIndexNumber(GridIndex) - 1))
	{
		FLFPInstanceGridMeshData& ISMData = MeshList[GridInstanceIndexList.GetIndexNumber(GridIndex) - 1];

		const int32 TargetIndex = ISMData.InstanceGridIndexList.Find(GridIndex);

		check(TargetIndex != INDEX_NONE);

		/* Same Instance So Just Update Transform */
		if (GridInstanceIndexList.GetIndexNumber(GridIndex) - 1 == InstanceInfo.InstanceIndex)
		{
			ISMData.ISMComponent->UpdateInstanceTransform(TargetIndex, TargetTransform, true, true);

			return true;
		}

		/* Remove Operation */
		else
		{
			ISMData.InstanceGridIndexList.RemoveAt(TargetIndex);
			ISMData.ISMComponent->RemoveInstance(TargetIndex);

			GridInstanceIndexList.SetIndexNumber(GridIndex, 0);
		}
	}

	/* Add Operation */
	if (IsMeshIndexValid(InstanceInfo.InstanceIndex))
	{
		GridInstanceIndexList.SetIndexNumber(GridIndex, InstanceInfo.InstanceIndex + 1);

		FLFPInstanceGridMeshData& ISMData = MeshList[InstanceInfo.InstanceIndex];

		const int32 ISMIndex = ISMData.ISMComponent->AddInstance(TargetTransform, true);

		ISMData.ISMComponent->GetInstanceTransform(ISMIndex, TargetTransform);

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

	const int32 GridIndex = ULFPGridLibrary::ToGridIndex(Location, WorldGrid->GetGridSize());

	if (GridInstanceIndexList.IsValidIndex(GridIndex))
	{
		if (IsMeshIndexValid(GridInstanceIndexList.GetIndexNumber(GridIndex) - 1))
		{
			FLFPInstanceGridMeshData& ISMData = MeshList[GridInstanceIndexList.GetIndexNumber(GridIndex) - 1];

			const int32 TargetIndex = ISMData.InstanceGridIndexList.Find(GridIndex);

			return ISMData.ISMComponent->SetCustomDataValue(TargetIndex, DataIndex, DataValue, bMarkRenderStateDirty);
		}
	}

	return false;
}

bool ULFPInstanceGridComponent::SetCustomDatas(const FIntVector Location, const TArray<float>& DataList, const bool bMarkRenderStateDirty)
{
	if (IsValid(WorldGrid) == false) return false;

	const int32 GridIndex = ULFPGridLibrary::ToGridIndex(Location, WorldGrid->GetGridSize());

	if (GridInstanceIndexList.IsValidIndex(GridIndex))
	{
		if (IsMeshIndexValid(GridInstanceIndexList.GetIndexNumber(GridIndex) - 1))
		{
			FLFPInstanceGridMeshData& ISMData = MeshList[GridInstanceIndexList.GetIndexNumber(GridIndex) - 1];

			const int32 TargetIndex = ISMData.InstanceGridIndexList.Find(GridIndex);

			return ISMData.ISMComponent->SetCustomData(TargetIndex, DataList, bMarkRenderStateDirty);
		}
	}

	return false;
}

