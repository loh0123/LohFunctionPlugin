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

	TestChuckData.InitChuckData(TestPalette);

	TestPalette.VoxelName = FName("Dirt");

	TestChuckData.SetIndexData(0, TestPalette);
	TestChuckData.SetIndexData(10, TestPalette);

	TestPalette.VoxelName = FName("Stone");

	TestChuckData.SetIndexData(20, TestPalette);
	TestChuckData.SetIndexData(30, TestPalette);

	TestPalette.VoxelName = FName("Grass");
	
	TestChuckData.SetIndexData(20, TestPalette);
	TestChuckData.SetIndexData(30, TestPalette);

	TestPalette.VoxelName = FName("Hello");

	TestChuckData.SetIndexData(40, TestPalette);
	TestChuckData.SetIndexData(50, TestPalette);

	return FString::Printf(TEXT("Total : %d, Encode : %d, Palette : %d, Default : %llu"),
		TestChuckData.GetPaletteIndex(10),
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

bool ULFPVoxelContainerComponent::IsVoxelPositionValid(const int32 RegionIndex, const int32 ChuckIndex, const int32 VoxelIndex) const
{
	return Setting.GetRegionLength() > RegionIndex && Setting.GetChuckLength() > ChuckIndex && Setting.GetVoxelLength() > VoxelIndex;
}

/** Setter */

bool ULFPVoxelContainerComponent::SetVoxelPalette(const int32 RegionIndex, const int32 ChuckIndex, const int32 VoxelIndex, const FLFPVoxelPaletteData& VoxelPalette)
{
	if (IsVoxelPositionValid(RegionIndex, ChuckIndex, VoxelIndex) == false) return false;

	ChuckUpdateDataList.FindOrAdd(FIntPoint(RegionIndex, ChuckIndex)).ChangePalette.Add(VoxelIndex, VoxelPalette);

	return true;
}

/** Getter */

FLFPVoxelPaletteData ULFPVoxelContainerComponent::GetVoxelPalette(const int32 RegionIndex, const int32 ChuckIndex, const int32 VoxelIndex) const
{
	if (IsVoxelPositionValid(RegionIndex, ChuckIndex, VoxelIndex) == false || IsChuckInitialized(RegionIndex, ChuckIndex) == false) return FLFPVoxelPaletteData();

	return RegionDataList[RegionIndex].ChuckData[ChuckIndex].GetIndexData(VoxelIndex);
}

TArray<FLFPVoxelPaletteData> ULFPVoxelContainerComponent::GetVoxelPaletteList(const int32 RegionIndex, const int32 ChuckIndex) const
{
	if (IsChuckInitialized(RegionIndex, ChuckIndex) == false) return TArray<FLFPVoxelPaletteData>();

	return RegionDataList[RegionIndex].ChuckData[ChuckIndex].GetVoxelPaletteList();
}

int32 ULFPVoxelContainerComponent::GetVoxelPaletteIndex(const int32 RegionIndex, const int32 ChuckIndex, const int32 VoxelIndex) const
{
	if (IsVoxelPositionValid(RegionIndex, ChuckIndex, VoxelIndex) == false || IsChuckInitialized(RegionIndex, ChuckIndex) == false) return INDEX_NONE;

	return RegionDataList[RegionIndex].ChuckData[ChuckIndex].GetPaletteIndex(VoxelIndex);
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
	if (RegionDataList.IsValidIndex(RegionIndex) == false || RegionDataList[RegionIndex].ChuckData.IsValidIndex(ChuckIndex) == false) return;

	auto& ChuckData = RegionDataList[RegionIndex].ChuckData[ChuckIndex];

	ChuckData.InitChuckData(FLFPVoxelPaletteData());

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
			if (ChuckData.GetIndexData(ChangeVoxel.Key) == ChangeVoxel.Value) continue;

			ChuckUpdateAction.ChangePalette.Add(ChuckData.GetIndexData(ChangeVoxel.Key), ChangeVoxel.Value);

			ChuckData.SetIndexData(ChangeVoxel.Key, ChangeVoxel.Value);

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
