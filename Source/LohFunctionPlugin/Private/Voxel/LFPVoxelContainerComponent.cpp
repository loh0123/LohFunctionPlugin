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

FString ULFPVoxelContainerComponent::MemorySize() const
{
	return FString::Printf(TEXT("%llu : ChuckDataList Size : %llu : Struct Size"), ChuckDataList.GetAllocatedSize(), sizeof(FColor));
}

/** Checker */

bool ULFPVoxelContainerComponent::IsChuckInitialized(const FIntVector& ChuckVector) const
{
	return ChuckDataList.Contains(ChuckVector);
}

bool ULFPVoxelContainerComponent::IsVoxelGridPositionValid(const FLFPVoxelGridPosition& VoxelGridPosition) const
{
	return IsChuckInitialized(VoxelGridPosition.ChuckVector) && Setting.GetVoxelLength() < VoxelGridPosition.VoxelIndex;
}

bool ULFPVoxelContainerComponent::IsVoxelVisible(const FLFPVoxelGridPosition& VoxelGridPosition) const
{
	return IsVoxelGridPositionValid(VoxelGridPosition) && ChuckDataList.FindRef(VoxelGridPosition.ChuckVector).GetChuckMaterial(VoxelGridPosition.VoxelIndex) != 255;
}

/** Setter */

bool ULFPVoxelContainerComponent::SetVoxelColor(const FLFPVoxelGridPosition& VoxelGridPosition, const FColor VoxelColor)
{
	if (IsVoxelGridPositionValid(VoxelGridPosition) == false) return false;

	ChuckUpdateDataList.FindOrAdd(VoxelGridPosition.ChuckVector).ChangeColor.Add(VoxelGridPosition.VoxelIndex, VoxelColor);

	return true;
}

bool ULFPVoxelContainerComponent::SetVoxelMaterial(const FLFPVoxelGridPosition& VoxelGridPosition, const uint8 VoxelMaterial)
{
	if (IsVoxelGridPositionValid(VoxelGridPosition) == false) return false;

	ChuckUpdateDataList.FindOrAdd(VoxelGridPosition.ChuckVector).ChangeMaterial.Add(VoxelGridPosition.VoxelIndex, VoxelMaterial);

	return true;
}

/** Getter */

FColor ULFPVoxelContainerComponent::GetVoxelColor(const FLFPVoxelGridPosition& VoxelGridPosition) const
{
	if (IsVoxelGridPositionValid(VoxelGridPosition) == false) return FColor(0);

	return ChuckDataList.FindChecked(VoxelGridPosition.ChuckVector).GetChuckColor(VoxelGridPosition.VoxelIndex);
}

uint8 ULFPVoxelContainerComponent::GetVoxelMaterial(const FLFPVoxelGridPosition& VoxelGridPosition) const
{
	if (IsVoxelGridPositionValid(VoxelGridPosition) == false) return uint8(255);

	return ChuckDataList.FindChecked(VoxelGridPosition.ChuckVector).GetChuckMaterial(VoxelGridPosition.VoxelIndex);
}

void ULFPVoxelContainerComponent::InitializeChuck_Implementation(const FIntVector& ChuckVector, const uint8 VoxelMaterial, const FColor VoxelColor)
{
	FLFPVoxelChuckData& ChuckData = ChuckDataList.FindOrAdd(ChuckVector);

	ChuckData.InitChuckData(Setting.GetVoxelLength(), VoxelMaterial, VoxelColor);

	return;
}

/** Chuck Request */

void ULFPVoxelContainerComponent::RequestRenderChuck(const FIntVector ChuckVector, FLFPVoxelChuckDelegate& ChuckDelegate)
{
	if (ChuckDelegateList.Contains(ChuckVector)) return;

	ChuckDelegate = ChuckDelegateList.Add(ChuckVector);
}

void ULFPVoxelContainerComponent::ReleaseRenderChuck(const FIntVector ChuckVector)
{
	if (ChuckDelegateList.Contains(ChuckVector) == false) return;

	ChuckDelegateList.FindChecked(ChuckVector).VoxelChuckUpdateEvent.Unbind();

	ChuckDelegateList.Remove(ChuckVector);
}

void ULFPVoxelContainerComponent::RequestRenderData(const FIntVector ChuckVector, FLFPVoxelContainerSetting& ChuckSetting, TArray<FLFPVoxelChuckData*>& RenderData)
{
	checkf(ChuckDelegateList.Contains(ChuckVector) == false, TEXT("Chuck is not connect"));

	ContainerThreadLock.ReadLock();

	ChuckSetting = Setting;

	RenderData.Empty(27);

	for (int32 Z = -1; Z <= 1; Z++)
	{
		for (int32 Y = -1; Y <= 1; Y++)
		{
			for (int32 X = -1; X <= 1; X++)
			{
				RenderData.Add(ChuckDataList.Find(ChuckVector + FIntVector(X, Y, Z)));
			}
		}
	}
}

void ULFPVoxelContainerComponent::ReleaseRenderData(const FIntVector ChuckVector)
{
	checkf(ChuckDelegateList.Contains(ChuckVector) == false, TEXT("Chuck is not connect"));

	ContainerThreadLock.ReadUnlock();
}

void ULFPVoxelContainerComponent::UpdateChuckState()
{
	if (ChuckUpdateStateList.IsEmpty()) return;

	auto ChuckUpdateState = ChuckUpdateStateList.CreateIterator();

	const FLFPVoxelChuckDelegate* ChuckDelegate = ChuckDelegateList.Find(ChuckUpdateState.Key());

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
	if (ChuckUpdateDataList.IsEmpty()) return true;

	if (ContainerThreadLock.TryWriteLock() == false) return false;

	for (const auto& ChuckUpdate : ChuckUpdateDataList)
	{
		FLFPVoxelChuckData* ChuckData = ChuckDataList.Find(ChuckUpdate.Key);

		if (ChuckData == nullptr) continue;

		TSet<FIntVector> EdgeList = { FIntVector(0) };

		/** This change the outdate voxel material */
		for (const auto& ChangeVoxel : ChuckUpdate.Value.ChangeMaterial)
		{
			ChuckData->SetChuckMaterial(ChangeVoxel.Key, ChangeVoxel.Value);

			EdgeList.Append(ULFPGridLibrary::GetGridEdgeDirection(ULFPGridLibrary::ToGridLocation(ChangeVoxel.Key, Setting.VoxelGridSize), Setting.VoxelGridSize));
		}

		/** This change the outdate voxel color */
		for (const auto& ChangeVoxel : ChuckUpdate.Value.ChangeColor)
		{
			ChuckData->SetChuckColor(ChangeVoxel.Key, ChangeVoxel.Value);

			EdgeList.Append(ULFPGridLibrary::GetGridEdgeDirection(ULFPGridLibrary::ToGridLocation(ChangeVoxel.Key, Setting.VoxelGridSize), Setting.VoxelGridSize));
		}

		/** This add update state to list */
		for (const FIntVector& Edge : EdgeList)
		{
			FLFPVoxelChuckUpdateState& ChuckUpdateState = ChuckUpdateStateList.FindOrAdd(ChuckUpdate.Key + Edge);

			if (ChuckUpdate.Value.ChangeColor.IsEmpty() == false) ChuckUpdateState.Color = true;
			if (ChuckUpdate.Value.ChangeMaterial.IsEmpty() == false) ChuckUpdateState.Material = true;
		}
	}

	ContainerThreadLock.WriteUnlock();

	return true;
}
