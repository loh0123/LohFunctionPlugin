// Copyright by Loh Zhi Kang

#include "Voxel/LFPVoxelContainerComponent.h"
#include "./Math/LFPGridLibrary.h"
#include "UObject/ReflectedTypeAccessors.h"

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

bool ULFPVoxelContainerComponent::IsChuckInitialized(const FIntVector& ChuckVector) const
{
	return ChuckDataList.Contains(ChuckVector);
}

bool ULFPVoxelContainerComponent::IsVoxelGridPositionValid(const FLFPVoxelGridPosition& VoxelGridPosition) const
{
	return ChuckDataList.Contains(VoxelGridPosition.ChuckVector) && Setting.GetVoxelLength() < VoxelGridPosition.VoxelIndex;
}

FString ULFPVoxelContainerComponent::MemorySize() const
{
	return FString::Printf(TEXT("%llu : ChuckDataList Size : %llu : Struct Size"), ChuckDataList.GetAllocatedSize(), sizeof(FColor));
}

void ULFPVoxelContainerComponent::InitializeChuck_Implementation(const FIntVector& ChuckVector, const uint8 VoxelMaterial, const FColor VoxelColor)
{
	FLFPVoxelChuckData& ChuckData = ChuckDataList.FindOrAdd(ChuckVector);

	ChuckData.InitChuckData(Setting.GetVoxelLength(), VoxelMaterial, VoxelColor);

	return;
}

bool ULFPVoxelContainerComponent::SetVoxelColor(const FLFPVoxelGridPosition& VoxelGridPosition, const FColor VoxelColor)
{
	if (IsVoxelGridPositionValid(VoxelGridPosition) == false) return false;

	FLFPVoxelUpdateAction UpdateAction;

	UpdateAction.ChangeColor.Add(VoxelGridPosition.VoxelIndex, VoxelColor);

	UpdateAction.UpdateState = ELFPVoxelChuckUpdateState::LFP_Color;

	MarkChuckForUpdate(VoxelGridPosition.ChuckVector, UpdateAction);

	return true;
}

bool ULFPVoxelContainerComponent::SetVoxelMaterial(const FLFPVoxelGridPosition& VoxelGridPosition, const uint8 VoxelMaterial)
{
	if (IsVoxelGridPositionValid(VoxelGridPosition) == false) return false;

	FLFPVoxelUpdateAction UpdateAction;

	UpdateAction.ChangeMaterial.Add(VoxelGridPosition.VoxelIndex, VoxelMaterial);

	UpdateAction.UpdateState = ELFPVoxelChuckUpdateState::LFP_Material;

	MarkChuckForUpdate(VoxelGridPosition.ChuckVector, UpdateAction);

	return true;
}

FColor ULFPVoxelContainerComponent::GetVoxelColor(const FLFPVoxelGridPosition& VoxelGridPosition) const
{
	if (IsVoxelGridPositionValid(VoxelGridPosition) == false) return FColor(0);

	return ChuckDataList.FindRef(VoxelGridPosition.ChuckVector).GetChuckColor(VoxelGridPosition.VoxelIndex);
}

uint8 ULFPVoxelContainerComponent::GetVoxelMaterial(const FLFPVoxelGridPosition& VoxelGridPosition) const
{
	if (IsVoxelGridPositionValid(VoxelGridPosition) == false) return uint8(255);

	return ChuckDataList.FindRef(VoxelGridPosition.ChuckVector).GetChuckMaterial(VoxelGridPosition.VoxelIndex);
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

		/** This change the outdate voxel material */
		for (const auto& ChangeVoxel : ChuckUpdate.Value.ChangeMaterial)
		{
			ChuckData->SetChuckMaterial(ChangeVoxel.Key, ChangeVoxel.Value);
		}

		/** This change the outdate voxel color */
		for (const auto& ChangeVoxel : ChuckUpdate.Value.ChangeColor)
		{
			ChuckData->SetChuckColor(ChangeVoxel.Key, ChangeVoxel.Value);
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

	for (const auto& ChangeVoxel : UpdateData.ChangeMaterial)
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
