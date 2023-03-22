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

	if (UpdateChuckData())
	{
		UpdateChuckState();
	}
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

FString ULFPVoxelContainerComponent::Test() const
{
	FLFPVoxelChuckData TestChuckData;

	FLFPVoxelPaletteData TestPalette;

	TestChuckData.InitChuckData(16 * 16 * 16, TestPalette);

	TestPalette.VoxelName = FName("Dirt");

	TestChuckData.SetVoxel(0, TestPalette);
	TestChuckData.SetVoxel(10, TestPalette);

	TestPalette.VoxelName = FName("Stone");

	TestChuckData.SetVoxel(20, TestPalette);
	TestChuckData.SetVoxel(30, TestPalette);

	TestPalette.VoxelName = FName("Grass");
	
	TestChuckData.SetVoxel(20, TestPalette);
	TestChuckData.SetVoxel(30, TestPalette);

	TestPalette.VoxelName = FName("Hello");

	TestChuckData.SetVoxel(40, TestPalette);
	TestChuckData.SetVoxel(50, TestPalette);

	return FString::Printf(TEXT("Total : %d, Encode : %d, Palette : %d, Default : %llu"),
		TestChuckData.GetVoxelIndex(10),
		TestChuckData.GetEncodeLength(), 
		TestChuckData.GetPaletteLength(),
		sizeof(FLFPVoxelChuckData));
}

/** Checker */

bool ULFPVoxelContainerComponent::IsRegionInitialized(const int32 RegionIndex) const
{
	return RegionDataList.IsValidIndex(RegionIndex) && RegionDataList[RegionIndex].IsInitialized();
}

bool ULFPVoxelContainerComponent::IsChuckInitialized(const int32 RegionIndex, const int32 ChuckIndex) const
{
	return IsRegionInitialized(RegionIndex) && RegionDataList[RegionIndex].ChuckData.IsValidIndex(ChuckIndex) && RegionDataList[RegionIndex].ChuckData[ChuckIndex].IsInitialized();
}

bool ULFPVoxelContainerComponent::IsVoxelGridPositionValid(const FLFPVoxelGridPosition& VoxelGridPosition) const
{
	return Setting.GetVoxelLength() > VoxelGridPosition.VoxelIndex && Setting.GetChuckLength() > VoxelGridPosition.ChuckIndex && Setting.GetRegionLength() > VoxelGridPosition.RegionIndex;
}

bool ULFPVoxelContainerComponent::IsVoxelVisible(const FLFPVoxelGridPosition& VoxelGridPosition) const
{
	return 
		IsVoxelGridPositionValid(VoxelGridPosition) && 
		IsChuckInitialized(VoxelGridPosition.RegionIndex, VoxelGridPosition.ChuckIndex) && 
		RegionDataList[VoxelGridPosition.RegionIndex].ChuckData[VoxelGridPosition.ChuckIndex].IsVoxelVisible(VoxelGridPosition.VoxelIndex);
}

/** Setter */

bool ULFPVoxelContainerComponent::SetVoxelPalette(const FLFPVoxelGridPosition& VoxelGridPosition, const FLFPVoxelPaletteData& VoxelPalette)
{
	if (IsVoxelGridPositionValid(VoxelGridPosition) == false) return false;

	ChuckUpdateDataList.FindOrAdd(VoxelGridPosition.GetSaveAndChuck()).ChangePalette.Add(VoxelGridPosition.VoxelIndex, VoxelPalette);

	return true;
}

/** Getter */

FLFPVoxelPaletteData ULFPVoxelContainerComponent::GetVoxelPalette(const FLFPVoxelGridPosition& VoxelGridPosition) const
{
	if (IsVoxelGridPositionValid(VoxelGridPosition) == false || IsChuckInitialized(VoxelGridPosition.RegionIndex, VoxelGridPosition.ChuckIndex) == false) return FLFPVoxelPaletteData();

	return RegionDataList[VoxelGridPosition.RegionIndex].ChuckData[VoxelGridPosition.ChuckIndex].GetVoxelPalette(VoxelGridPosition.VoxelIndex);
}

int32 ULFPVoxelContainerComponent::GetVoxelPaletteIndex(const FLFPVoxelGridPosition& VoxelGridPosition) const
{
	if (IsVoxelGridPositionValid(VoxelGridPosition) == false || IsChuckInitialized(VoxelGridPosition.RegionIndex, VoxelGridPosition.ChuckIndex) == false) return INDEX_NONE;

	return RegionDataList[VoxelGridPosition.RegionIndex].ChuckData[VoxelGridPosition.ChuckIndex].GetVoxelIndex(VoxelGridPosition.VoxelIndex);
}

void ULFPVoxelContainerComponent::InitializeRegion(const int32 RegionIndex)
{
	if (Setting.GetRegionLength() <= RegionIndex || RegionIndex < 0) return;

	if (RegionDataList.IsValidIndex(RegionIndex) == false) RegionDataList.SetNum(RegionIndex + 1);

	auto& ChuckData = RegionDataList[RegionIndex];

	ChuckData.InitRegionData(Setting.GetChuckLength());

	return;
}

void ULFPVoxelContainerComponent::InitializeChuck(const int32 RegionIndex, const int32 ChuckIndex)
{
	if (RegionDataList.IsValidIndex(RegionIndex) == false || Setting.GetChuckLength() <= ChuckIndex || ChuckIndex < 0) return;

	if (RegionDataList[RegionIndex].ChuckData.IsValidIndex(ChuckIndex) == false) RegionDataList[RegionIndex].ChuckData.SetNum(RegionIndex + 1);

	auto& ChuckData = RegionDataList[RegionIndex].ChuckData[ChuckIndex];

	ChuckData.InitChuckData(Setting.GetVoxelLength(), FLFPVoxelPaletteData());

	return;
}

/** Chuck Request */

//void ULFPVoxelContainerComponent::RequestRenderChuck(const int32 RegionIndex, const int32 ChuckIndex, FLFPVoxelChuckDelegate& ChuckDelegate)
//{
//	if (ChuckDelegateList.Contains(ChuckVector)) return;
//
//	ChuckDelegate = ChuckDelegateList.Add(ChuckVector);
//}
//
//void ULFPVoxelContainerComponent::ReleaseRenderChuck(const int32 RegionIndex, const int32 ChuckIndex)
//{
//	if (ChuckDelegateList.Contains(ChuckVector) == false) return;
//
//	ChuckDelegateList.FindChecked(ChuckVector).VoxelChuckUpdateEvent.Unbind();
//
//	ChuckDelegateList.Remove(ChuckVector);
//}
//
//void ULFPVoxelContainerComponent::RequestRenderData(const int32 RegionIndex, const int32 ChuckIndex, FLFPVoxelContainerSetting& ChuckSetting, TArray<FLFPVoxelChuckData*>& RenderData)
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
//void ULFPVoxelContainerComponent::ReleaseRenderData(const int32 RegionIndex, const int32 ChuckIndex)
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
		if (IsRegionInitialized(ChuckUpdate.Key.X) == false) InitializeRegion(ChuckUpdate.Key.X);

		if (IsChuckInitialized(ChuckUpdate.Key.X, ChuckUpdate.Key.Y) == false) InitializeChuck(ChuckUpdate.Key.X, ChuckUpdate.Key.Y);

		FLFPVoxelChuckData& ChuckData = RegionDataList[ChuckUpdate.Key.X].ChuckData[ChuckUpdate.Key.Y];

		TSet<FIntVector> EdgeList = { FIntVector(0) };
		FLFPChuckUpdateAction ChuckUpdateAction;

		/** This change the outdate voxel name */
		for (const auto& ChangeVoxel : ChuckUpdate.Value.ChangePalette)
		{
			if (ChuckData.GetVoxelPalette(ChangeVoxel.Key) == ChangeVoxel.Value) continue;

			ChuckUpdateAction.ChangePalette.Add(ChuckData.GetVoxelPalette(ChangeVoxel.Key), ChangeVoxel.Value);

			ChuckData.SetVoxel(ChangeVoxel.Key, ChangeVoxel.Value);

			EdgeList.Append(ULFPGridLibrary::GetGridEdgeDirection(ULFPGridLibrary::ToGridLocation(ChangeVoxel.Key, Setting.VoxelGridSize), Setting.VoxelGridSize));
		}

		/** This add update state to list */
		for (const FIntVector& Edge : EdgeList)
		{
			auto& ChuckUpdateData = ChuckUpdateStateList.FindOrAdd(FIntPoint(ChuckUpdate.Key.X + Edge.X, ChuckUpdate.Key.Y + Edge.Y));

			ChuckUpdateData += ChuckUpdateAction;
		}
	}

	ContainerThreadLock.WriteUnlock();

	return true;
}
