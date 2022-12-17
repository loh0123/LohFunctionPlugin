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

bool ULFPInstanceGridComponent::IsMeshIndexValid(const int32 Index) const
{
	return MeshList.IsValidIndex(Index) && IsValid(MeshList[Index].ISMComponent);
}

void ULFPInstanceGridComponent::SetupGrid(const FIntVector NewGridSize, const FVector NewGridGap, const ELFPGridType NewGridType)
{
	GridSize = NewGridSize;
	GridGap = NewGridGap;
	GridType = NewGridType;

	GridInstanceIndexList.Init(INDEX_NONE, GridSize.X * GridSize.Y * GridSize.Z);
}

int32 ULFPInstanceGridComponent::RegisterInstanceStaticMeshComponent(UInstancedStaticMeshComponent* ISM)
{
	if (IsValid(ISM) == false)
	{
		return INDEX_NONE;
	}

	return MeshList.Add(FLFPInstanceGridMeshData(ISM));
}

bool ULFPInstanceGridComponent::SetInstance(const FLFPInstanceGridInstanceInfo& InstanceInfo)
{
	const int32 GridIndex = ULFPGridLibrary::ToIndex(InstanceInfo.Location, GridSize);

	if (GridInstanceIndexList.IsValidIndex(GridIndex) == false) return false;
	
	/* Calculate Instance Transform With Offset */
	FVector InstanceWorldLocation;
	FRotator InstanceWorldRotation;

	GridLocationToWorldLocation(InstanceInfo.Location, InstanceInfo.bIsWorld, InstanceWorldLocation, InstanceWorldRotation);

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
	const int32 GridIndex = ULFPGridLibrary::ToIndex(Location, GridSize);

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
	const int32 GridIndex = ULFPGridLibrary::ToIndex(Location, GridSize);

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

