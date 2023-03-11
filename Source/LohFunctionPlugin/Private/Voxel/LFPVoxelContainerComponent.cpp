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

	Setting.InitSetting();
}


// Called every frame
void ULFPVoxelContainerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*if (UpdateChuckData())
	{
		UpdateChuckState();
	}*/
}

FString ULFPVoxelContainerComponent::MemorySize(const int32 SaveFileAmount, const int32 ChuckAmount, const int32 VoxelAmount) const
{
	unsigned long long TotalSize = (5 * VoxelAmount) * ChuckAmount * SaveFileAmount;
	unsigned long long SaveSize = (5 * VoxelAmount) * ChuckAmount;
	unsigned long long ChuckSize = (5 * VoxelAmount);

	return FString::Printf(TEXT("Total : %llu : SaveData : %llu : ChuckData : %llu : FName : %llu"), 
		TotalSize,
		SaveSize,
		ChuckSize,
		sizeof(FName));
}

/** Checker */

bool ULFPVoxelContainerComponent::IsSaveInitialized(const int32 SaveIndex) const
{
	return SaveDataList.IsValidIndex(SaveIndex) && SaveDataList[SaveIndex].ChuckData.IsEmpty() == false;
}

bool ULFPVoxelContainerComponent::IsChuckInitialized(const int32 SaveIndex, const int32 ChuckIndex) const
{
	return IsSaveInitialized(SaveIndex) && Setting.GetChuckLength() > ChuckIndex && SaveDataList[SaveIndex].ChuckData[ChuckIndex].IsInitialized();
}

bool ULFPVoxelContainerComponent::IsVoxelGridPositionValid(const FLFPVoxelGridPosition& VoxelGridPosition) const
{
	return Setting.GetVoxelLength() > VoxelGridPosition.VoxelIndex && Setting.GetChuckLength() > VoxelGridPosition.ChuckIndex && Setting.GetSaveLength() > VoxelGridPosition.SaveIndex;
}

bool ULFPVoxelContainerComponent::IsVoxelVisible(const FLFPVoxelGridPosition& VoxelGridPosition) const
{
	return 
		IsVoxelGridPositionValid(VoxelGridPosition) && 
		IsChuckInitialized(VoxelGridPosition.SaveIndex, VoxelGridPosition.ChuckIndex) && 
		SaveDataList[VoxelGridPosition.SaveIndex].ChuckData[VoxelGridPosition.ChuckIndex].IsVoxelVisible(VoxelGridPosition.VoxelIndex);
}

/** Setter */

bool ULFPVoxelContainerComponent::SetVoxelColor(const FLFPVoxelGridPosition& VoxelGridPosition, const FColor VoxelColor)
{
	if (IsVoxelGridPositionValid(VoxelGridPosition) == false) return false;

	ChuckUpdateDataList.FindOrAdd(VoxelGridPosition.GetSaveAndChuck()).ChangeColor.Add(VoxelGridPosition.VoxelIndex, VoxelColor);

	return true;
}

bool ULFPVoxelContainerComponent::SetVoxelMaterial(const FLFPVoxelGridPosition& VoxelGridPosition, const uint8 VoxelMaterial)
{
	if (IsVoxelGridPositionValid(VoxelGridPosition) == false) return false;

	ChuckUpdateDataList.FindOrAdd(VoxelGridPosition.GetSaveAndChuck()).ChangeMaterial.Add(VoxelGridPosition.VoxelIndex, VoxelMaterial);

	return true;
}

/** Getter */

FColor ULFPVoxelContainerComponent::GetVoxelColor(const FLFPVoxelGridPosition& VoxelGridPosition) const
{
	if (IsVoxelGridPositionValid(VoxelGridPosition) == false || IsChuckInitialized(VoxelGridPosition.SaveIndex, VoxelGridPosition.ChuckIndex)) return FColor(0);

	return SaveDataList[VoxelGridPosition.SaveIndex].ChuckData[VoxelGridPosition.ChuckIndex].GetVoxelColor(VoxelGridPosition.VoxelIndex);
}

uint8 ULFPVoxelContainerComponent::GetVoxelMaterial(const FLFPVoxelGridPosition& VoxelGridPosition) const
{
	if (IsVoxelGridPositionValid(VoxelGridPosition) == false || IsChuckInitialized(VoxelGridPosition.SaveIndex, VoxelGridPosition.ChuckIndex)) return uint8(255);

	return SaveDataList[VoxelGridPosition.SaveIndex].ChuckData[VoxelGridPosition.ChuckIndex].GetVoxelMaterial(VoxelGridPosition.VoxelIndex);
}

void ULFPVoxelContainerComponent::InitializeSave_Implementation(const int32 SaveIndex)
{
	if (SaveDataList.IsValidIndex(SaveIndex) == false) return;

	auto& ChuckData = SaveDataList[SaveIndex];

	ChuckData.InitSaveData(Setting.GetChuckLength());

	return;
}

void ULFPVoxelContainerComponent::InitializeChuck_Implementation(const int32 SaveIndex, const int32 ChuckIndex)
{
	if (SaveDataList.IsValidIndex(SaveIndex) == false || SaveDataList[SaveIndex].ChuckData.IsValidIndex(ChuckIndex) == false) return;

	auto& ChuckData = SaveDataList[SaveIndex].ChuckData[ChuckIndex];

	ChuckData.InitChuckData(Setting.GetVoxelLength(), FColor(0), UINT8_MAX);

	return;
}

/** Chuck Request */

//void ULFPVoxelContainerComponent::RequestRenderChuck(const int32 SaveIndex, const int32 ChuckIndex, FLFPVoxelChuckDelegate& ChuckDelegate)
//{
//	if (ChuckDelegateList.Contains(ChuckVector)) return;
//
//	ChuckDelegate = ChuckDelegateList.Add(ChuckVector);
//}
//
//void ULFPVoxelContainerComponent::ReleaseRenderChuck(const int32 SaveIndex, const int32 ChuckIndex)
//{
//	if (ChuckDelegateList.Contains(ChuckVector) == false) return;
//
//	ChuckDelegateList.FindChecked(ChuckVector).VoxelChuckUpdateEvent.Unbind();
//
//	ChuckDelegateList.Remove(ChuckVector);
//}
//
//void ULFPVoxelContainerComponent::RequestRenderData(const int32 SaveIndex, const int32 ChuckIndex, FLFPVoxelContainerSetting& ChuckSetting, TArray<FLFPVoxelChuckData*>& RenderData)
//{
//	checkf(ChuckDelegateList.Contains(ChuckVector) == false, TEXT("Chuck is not connect"));
//
//	ContainerThreadLock.ReadLock();
//
//	ChuckSetting = Setting;
//
//	RenderData.Empty(27);
//
//	for (int32 Z = -1; Z <= 1; Z++)
//	{
//		for (int32 Y = -1; Y <= 1; Y++)
//		{
//			for (int32 X = -1; X <= 1; X++)
//			{
//				RenderData.Add(ChuckDataList.Find(ChuckVector + FIntVector(X, Y, Z)));
//			}
//		}
//	}
//}
//
//void ULFPVoxelContainerComponent::ReleaseRenderData(const int32 SaveIndex, const int32 ChuckIndex)
//{
//	checkf(ChuckDelegateList.Contains(ChuckVector) == false, TEXT("Chuck is not connect"));
//
//	ContainerThreadLock.ReadUnlock();
//}

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
		if (IsSaveInitialized(ChuckUpdate.Key.X) == false) InitializeSave(ChuckUpdate.Key.X);
		if (IsChuckInitialized(ChuckUpdate.Key.X, ChuckUpdate.Key.Y) == false) InitializeChuck(ChuckUpdate.Key.X, ChuckUpdate.Key.Y);

		FLFPVoxelChuckData& ChuckData = SaveDataList[ChuckUpdate.Key.X].ChuckData[ChuckUpdate.Key.Y];

		TSet<FIntVector> EdgeList = { FIntVector(0) };

		/** This change the outdate voxel material */
		for (const auto& ChangeVoxel : ChuckUpdate.Value.ChangeMaterial)
		{
			ChuckData.SetVoxel(ChangeVoxel.Key, ChuckData.GetVoxelColor(ChangeVoxel.Key), ChangeVoxel.Value);

			EdgeList.Append(ULFPGridLibrary::GetGridEdgeDirection(ULFPGridLibrary::ToGridLocation(ChangeVoxel.Key, Setting.VoxelGridSize), Setting.VoxelGridSize));
		}

		/** This change the outdate voxel color */
		for (const auto& ChangeVoxel : ChuckUpdate.Value.ChangeColor)
		{
			ChuckData.SetVoxel(ChangeVoxel.Key, ChangeVoxel.Value, ChuckData.GetVoxelMaterial(ChangeVoxel.Key));

			EdgeList.Append(ULFPGridLibrary::GetGridEdgeDirection(ULFPGridLibrary::ToGridLocation(ChangeVoxel.Key, Setting.VoxelGridSize), Setting.VoxelGridSize));
		}

		/** This add update state to list */
		for (const FIntVector& Edge : EdgeList)
		{
			FLFPVoxelChuckUpdateState& ChuckUpdateState = ChuckUpdateStateList.FindOrAdd(FIntPoint(ChuckUpdate.Key.X + Edge.X, ChuckUpdate.Key.Y + Edge.Y));

			if (ChuckUpdate.Value.ChangeColor.IsEmpty() == false) ChuckUpdateState.Color = true;
			if (ChuckUpdate.Value.ChangeMaterial.IsEmpty() == false) ChuckUpdateState.Material = true;
		}
	}

	ContainerThreadLock.WriteUnlock();

	return true;
}
