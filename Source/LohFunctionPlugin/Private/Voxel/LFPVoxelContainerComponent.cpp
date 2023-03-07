// Copyright by Loh Zhi Kang

#include "Voxel/LFPVoxelContainerComponent.h"
#include "./Math/LFPGridLibrary.h"

// Sets default values for this component's properties
ULFPVoxelContainerComponent::ULFPVoxelContainerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULFPVoxelContainerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (VoxelIDTable.IsNull() == false)
	{
		VoxelIDNameList = VoxelIDTable->GetRowNames();
	}
}


// Called every frame
void ULFPVoxelContainerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (UpdateChuckData())
	{
		UpdateChuckState();
	}
}

FString ULFPVoxelContainerComponent::MemorySize()
{
	return FString::Printf(TEXT("%llu : ChuckDataList Size : %llu : Struct Size"), ChuckDataList.GetAllocatedSize(), sizeof(FLFPVoxelIdentifyData));
}

void ULFPVoxelContainerComponent::UpdateChuckState()
{
	if (ChuckUpdateStateList.IsEmpty()) return;

	auto ChuckUpdateState = ChuckUpdateStateList.CreateIterator();

	auto ChuckDelegate = ChuckDelegateList.Find(ChuckUpdateState.Key());

	if (ChuckDelegate != nullptr) ChuckDelegate->VoxelChuckUpdateEvent.ExecuteIfBound(ChuckUpdateState.Value());

	ChuckUpdateStateList.Remove(ChuckUpdateState.Key());

	if (ChuckUpdateStateList.Num() == 0)
	{
		ChuckUpdateStateList.Shrink();
	}

	return;
}

bool ULFPVoxelContainerComponent::UpdateChuckData()
{
	if (ContainerThreadLock.TryWriteLock() == false) return false;

	for (const auto& ChuckUpdate : ChuckUpdateDataList)
	{
		FLFPVoxelChuckData* ChuckData = ChuckDataList.Find(ChuckUpdate.Key);

		if (ChuckData == nullptr) continue;

		/** This change the outdate voxel */
		for (const auto& ChangeVoxel : ChuckUpdate.Value.ChangeData)
		{
			ChuckData->SetChuckData(ChangeVoxel.Key, ChangeVoxel.Value);
		}

		/** This add update state to list */
		{
			ELFPVoxelChuckUpdateState& ChuckUpdateState = ChuckUpdateStateList.FindOrAdd(ChuckUpdate.Key);

			if (ChuckUpdateState < ChuckUpdate.Value.UpdateState) ChuckUpdateState = ChuckUpdate.Value.UpdateState;
		}
	}

	ContainerThreadLock.WriteUnlock();

	return true;
}

void ULFPVoxelContainerComponent::MarkChuckForUpdate(const FIntVector ChuckVector, const FLFPVoxelUpdateAction& UpdateData)
{
	if (ChuckDataList.Contains(ChuckVector) == false) return;

	FLFPVoxelUpdateAction& UpdateAction = ChuckUpdateDataList.FindOrAdd(ChuckVector);

	TSet<FIntVector> EdgeList;

	for (const auto& ChangeVoxel : UpdateData.ChangeData)
	{
		EdgeList.Append(ULFPGridLibrary::GetGridEdgeDirection(ULFPGridLibrary::ToGridLocation(ChangeVoxel.Key, Setting.VoxelGridSize), Setting.VoxelGridSize));
	}

	UpdateAction += UpdateData;

	if (UpdateData.UpdateState == ELFPVoxelChuckUpdateState::LFP_Full)
	{
		for (const FIntVector& Edge : EdgeList)
		{
			if (ChuckDataList.Contains(ChuckVector + Edge) == false) continue;

			ChuckUpdateDataList.FindOrAdd(ChuckVector + Edge).UpdateState = ELFPVoxelChuckUpdateState::LFP_Full;
		}
	}
}
