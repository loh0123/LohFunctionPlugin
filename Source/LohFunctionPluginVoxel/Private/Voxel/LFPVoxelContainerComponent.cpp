// Copyright by Loh Zhi Kang

#include "Voxel/LFPVoxelContainerComponent.h"
#include "./Math/LFPGridLibrary.h"
#include "Serialization/ArchiveProxy.h"
#include "Serialization/NameAsStringProxyArchive.h"
#include "Serialization/ArchiveSaveCompressedProxy.h"
#include "Serialization/ArchiveLoadCompressedProxy.h"
#include "UObject/ReflectedTypeAccessors.h"


// Sets default values for this component's properties
ULFPVoxelContainerComponent::ULFPVoxelContainerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
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

	if (UpdateChuckData() == false) return;

	if (UpdateChuckState() == false) return;

	SetComponentTickEnabled(false);
}

//FString ULFPVoxelContainerComponent::MemorySize(const int32 SaveFileAmount, const int32 ChuckAmount, const int32 VoxelAmount) const
//{
//	unsigned long long TotalSize = (5 * VoxelAmount) * ChuckAmount * SaveFileAmount;
//	unsigned long long SaveSize = (5 * VoxelAmount) * ChuckAmount;
//	unsigned long long ChuckSize = (5 * VoxelAmount);
//
//	return FString::Printf(TEXT("Total : %llu : SaveData : %llu : ChuckData : %llu : FName : %llu"), 
//		TotalSize,
//		SaveSize,
//		ChuckSize,
//		sizeof(FName));
//}

FString ULFPVoxelContainerComponent::Test()
{
	TArray<uint8> SrData;

	FMemoryWriter MemoryWriter(SrData, true);
	FArchiveProxy Ar(MemoryWriter);
	Ar.SetIsSaving(true);

	Ar << RegionDataList;

	FIntVector Pos(0, 0, 0);

	Pos.Serialize(Ar);

	return "";
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

bool ULFPVoxelContainerComponent::IsRegionPositionValid(const int32 RegionIndex) const
{
	return Setting.GetRegionLength() > RegionIndex && RegionIndex >= 0;
}

bool ULFPVoxelContainerComponent::IsChuckPositionValid(const int32 RegionIndex, const int32 ChuckIndex) const
{
	return IsRegionPositionValid(RegionIndex) && Setting.GetChuckLength() > ChuckIndex && ChuckIndex >= 0;
}

bool ULFPVoxelContainerComponent::IsVoxelPositionValid(const int32 RegionIndex, const int32 ChuckIndex, const int32 VoxelIndex) const
{
	return IsChuckPositionValid(RegionIndex, ChuckIndex) && Setting.GetVoxelLength() > VoxelIndex && VoxelIndex >= 0;
}

bool ULFPVoxelContainerComponent::AddVoxelTag(const int32 RegionIndex, const int32 ChuckIndex, const int32 VoxelIndex, const FName& VoxelTag)
{
	if (IsVoxelPositionValid(RegionIndex, ChuckIndex, VoxelIndex) == false) return false;

	FLFPVoxelPaletteData NewPalette(GetVoxelPalette(RegionIndex, ChuckIndex, VoxelIndex));

	NewPalette.AddTag(VoxelTag);

	return SetVoxelPalette(RegionIndex, ChuckIndex, VoxelIndex, NewPalette);
}

bool ULFPVoxelContainerComponent::AddVoxelTagData(const int32 RegionIndex, const int32 ChuckIndex, const int32 VoxelIndex, const FName& VoxelTag, const uint8 VoxelData)
{
	if (IsVoxelPositionValid(RegionIndex, ChuckIndex, VoxelIndex) == false) return false;

	FLFPVoxelPaletteData NewPalette(GetVoxelPalette(RegionIndex, ChuckIndex, VoxelIndex));

	NewPalette.AddTagData(VoxelTag, VoxelData);

	return SetVoxelPalette(RegionIndex, ChuckIndex, VoxelIndex, NewPalette);
}

bool ULFPVoxelContainerComponent::RemoveVoxelTag(const int32 RegionIndex, const int32 ChuckIndex, const int32 VoxelIndex, const FName& VoxelTag)
{
	if (IsVoxelPositionValid(RegionIndex, ChuckIndex, VoxelIndex) == false) return false;

	FLFPVoxelPaletteData NewPalette(GetVoxelPalette(RegionIndex, ChuckIndex, VoxelIndex));

	NewPalette.RemoveTag(VoxelTag);

	return SetVoxelPalette(RegionIndex, ChuckIndex, VoxelIndex, NewPalette);
}

bool ULFPVoxelContainerComponent::RemoveVoxelTagData(const int32 RegionIndex, const int32 ChuckIndex, const int32 VoxelIndex, const FName& VoxelTag)
{
	if (IsVoxelPositionValid(RegionIndex, ChuckIndex, VoxelIndex) == false) return false;

	FLFPVoxelPaletteData NewPalette(GetVoxelPalette(RegionIndex, ChuckIndex, VoxelIndex));

	NewPalette.RemoveTagData(VoxelTag);

	return SetVoxelPalette(RegionIndex, ChuckIndex, VoxelIndex, NewPalette);
}

/** Setter */

bool ULFPVoxelContainerComponent::SetVoxelPalette(const int32 RegionIndex, const int32 ChuckIndex, const int32 VoxelIndex, const FLFPVoxelPaletteData& VoxelPalette)
{
	if (IsVoxelPositionValid(RegionIndex, ChuckIndex, VoxelIndex) == false || VoxelPalette.IsValid() == false) return false;

	ChuckUpdateDataList.FindOrAdd(FIntPoint(RegionIndex, ChuckIndex)).ChangePalette.Add(VoxelIndex, VoxelPalette);

	SetComponentTickEnabled(true);

	return true;
}

bool ULFPVoxelContainerComponent::SetVoxelPalettes(const int32 RegionIndex, const int32 ChuckIndex, const TMap<int32, FLFPVoxelPaletteData>& VoxelPaletteMap)
{
	if (IsChuckPositionValid(RegionIndex, ChuckIndex) == false) return false;

	for (const auto& VoxelPalette : VoxelPaletteMap)
	{
		if (Setting.GetVoxelLength() <= VoxelPalette.Key || VoxelPalette.Key < 0) continue;

		ChuckUpdateDataList.FindOrAdd(FIntPoint(RegionIndex, ChuckIndex)).ChangePalette.Add(VoxelPalette);
	}

	SetComponentTickEnabled(true);

	return true;
}

bool ULFPVoxelContainerComponent::SetVoxelChuckData(const int32 RegionIndex, const int32 ChuckIndex, const FLFPVoxelChuckData& ChuckData)
{
	if (IsChuckPositionValid(RegionIndex, ChuckIndex) == false || ChuckData.IsInitialized() == false || ChuckData.GetIndexSize() != Setting.GetVoxelLength()) return false;

	for (int32 VoxelIndex = 0; VoxelIndex < Setting.GetVoxelLength(); VoxelIndex++)
	{
		if (ChuckData.GetIndexData(VoxelIndex) != GetVoxelPaletteRef(RegionIndex, ChuckIndex, VoxelIndex)) SetVoxelPalette(RegionIndex, ChuckIndex, VoxelIndex, ChuckData.GetIndexData(VoxelIndex));
	}

	return true;
}

bool ULFPVoxelContainerComponent::InitializeVoxelChuck(const int32 RegionIndex, const int32 ChuckIndex)
{
	if (IsChuckPositionValid(RegionIndex, ChuckIndex) == false) return false;

	ChuckUpdateDataList.FindOrAdd(FIntPoint(RegionIndex, ChuckIndex));

	SetComponentTickEnabled(true);

	return true;
}

/** Getter */

int32 ULFPVoxelContainerComponent::GetRenderChuckAmount(const int32 RegionIndex, const int32 ChuckIndex) const
{
	return ChuckDelegateList.Contains(FIntPoint(RegionIndex, ChuckIndex)) ? ChuckDelegateList.FindChecked(FIntPoint(RegionIndex, ChuckIndex)).GetAmount() : INDEX_NONE;
}

FLFPVoxelChuckData ULFPVoxelContainerComponent::GetVoxelChuckData(const int32 RegionIndex, const int32 ChuckIndex) const
{
	if (IsRegionInitialized(RegionIndex) == false || RegionDataList[RegionIndex].ChuckData.IsValidIndex(ChuckIndex) == false) return FLFPVoxelChuckData();

	return RegionDataList[RegionIndex].ChuckData[ChuckIndex];
}

FLFPVoxelPaletteData ULFPVoxelContainerComponent::GetVoxelPalette(const int32 RegionIndex, const int32 ChuckIndex, const int32 VoxelIndex) const
{
	if (IsVoxelPositionValid(RegionIndex, ChuckIndex, VoxelIndex) == false || IsChuckInitialized(RegionIndex, ChuckIndex) == false) return FLFPVoxelPaletteData();

	return RegionDataList[RegionIndex].ChuckData[ChuckIndex].GetIndexData(VoxelIndex);
}

TArray<FLFPVoxelPaletteData> ULFPVoxelContainerComponent::GetVoxelPaletteList(const int32 RegionIndex, const int32 ChuckIndex) const
{
	if (IsChuckInitialized(RegionIndex, ChuckIndex) == false) return TArray<FLFPVoxelPaletteData>();

	return RegionDataList[RegionIndex].ChuckData[ChuckIndex].GetPaletteList();
}

int32 ULFPVoxelContainerComponent::GetVoxelPaletteIndex(const int32 RegionIndex, const int32 ChuckIndex, const int32 VoxelIndex) const
{
	if (IsVoxelPositionValid(RegionIndex, ChuckIndex, VoxelIndex) == false || IsChuckInitialized(RegionIndex, ChuckIndex) == false) return INDEX_NONE;

	return RegionDataList[RegionIndex].ChuckData[ChuckIndex].GetPaletteIndex(VoxelIndex);
}

FIntVector ULFPVoxelContainerComponent::ToVoxelGlobalPosition(const FIntVector VoxelGlobalIndex) const
{
	const FIntVector RegionPos(ULFPGridLibrary::ToGridLocation(VoxelGlobalIndex.X, Setting.GetRegionGrid()));
	const FIntVector ChuckPos(ULFPGridLibrary::ToGridLocation(VoxelGlobalIndex.Y, Setting.GetChuckGrid()));
	const FIntVector VoxelPos(ULFPGridLibrary::ToGridLocation(VoxelGlobalIndex.Z, Setting.GetVoxelGrid()));

	return (RegionPos * Setting.GetChuckGrid() * Setting.GetVoxelGrid()) + (ChuckPos * Setting.GetVoxelGrid()) + VoxelPos;
}

FIntVector ULFPVoxelContainerComponent::ToVoxelGlobalIndex(const FIntVector VoxelGlobalPosition) const
{
	auto DivideVector = [&](const FIntVector& A, const FIntVector& B) {
		return FIntVector(A.X / B.X, A.Y / B.Y, A.Z / B.Z);
	};

	auto PercentageVector = [&](const FIntVector& A, const FIntVector& B) {
		return FIntVector(A.X % B.X, A.Y % B.Y, A.Z % B.Z);
	};

	const FIntVector RegionVoxelSize(Setting.GetChuckGrid() * Setting.GetVoxelGrid());

	const FIntVector RegionPos	(DivideVector(VoxelGlobalPosition, RegionVoxelSize));
	const FIntVector ChuckPos	(PercentageVector(DivideVector(VoxelGlobalPosition, Setting.GetVoxelGrid()), Setting.GetChuckGrid()));
	const FIntVector VoxelPos	(PercentageVector(VoxelGlobalPosition, Setting.GetVoxelGrid()));

	return FIntVector(ULFPGridLibrary::ToGridIndex(RegionPos, Setting.GetRegionGrid()), ULFPGridLibrary::ToGridIndex(ChuckPos, Setting.GetChuckGrid()), ULFPGridLibrary::ToGridIndex(VoxelPos, Setting.GetVoxelGrid()));
}

/** C++ Getter */

const FLFPVoxelPaletteData& ULFPVoxelContainerComponent::GetVoxelPaletteRef(const int32 RegionIndex, const int32 ChuckIndex, const int32 VoxelIndex) const
{
	if (IsVoxelPositionValid(RegionIndex, ChuckIndex, VoxelIndex) == false || IsChuckInitialized(RegionIndex, ChuckIndex) == false) return FLFPVoxelPaletteData::EmptyData;

	return RegionDataList[RegionIndex].ChuckData[ChuckIndex].GetIndexData(VoxelIndex);
}

bool ULFPVoxelContainerComponent::GetVoxelChuckDataByArchive(const int32 RegionIndex, const int32 ChuckIndex, FArchive& Ar)
{
	if (IsChuckInitialized(RegionIndex, ChuckIndex) == false) return false;

	uint8 DataID = 0;

	Ar << DataID;

	Ar << RegionDataList[RegionIndex].ChuckData[ChuckIndex];

	return true;
}

/** C++ Setter */

bool ULFPVoxelContainerComponent::SetVoxelChuckDataByArchive(const int32 RegionIndex, const int32 ChuckIndex, FArchive& Ar)
{
	if (IsChuckPositionValid(RegionIndex, ChuckIndex) == false) return false;

	uint8 DataID = 0;

	Ar << DataID;

	switch (DataID)
	{
	case 0:
	{
		FLFPVoxelChuckData DecompressedChuckData = FLFPVoxelChuckData();
		Ar << DecompressedChuckData;
		SetVoxelChuckData(RegionIndex, ChuckIndex, DecompressedChuckData);
	}
	break;

	case 1:
	{
		TMap<int32, FLFPVoxelPaletteData> DecompressedChuckVoxelPalettes;
		Ar << DecompressedChuckVoxelPalettes;
		SetVoxelPalettes(RegionIndex, ChuckIndex, DecompressedChuckVoxelPalettes);
	}
	break;

	}

	return true;
}

void ULFPVoxelContainerComponent::InitializeRegion(const int32 RegionIndex)
{
	check(IsRegionPositionValid(RegionIndex));

	if (RegionDataList.IsValidIndex(RegionIndex) == false) RegionDataList.SetNum(RegionIndex + 1);

	auto& ChuckData = RegionDataList[RegionIndex];

	ChuckData.InitRegionData(Setting.GetChuckLength());

	OnVoxelContainerRegionInitialized.Broadcast(RegionIndex);

	return;
}

void ULFPVoxelContainerComponent::InitializeChuck(const int32 RegionIndex, const int32 ChuckIndex)
{
	check(RegionDataList.IsValidIndex(RegionIndex) && RegionDataList[RegionIndex].ChuckData.IsValidIndex(ChuckIndex));

	auto& ChuckData = RegionDataList[RegionIndex].ChuckData[ChuckIndex];

	ChuckData.InitChuckData(FLFPVoxelPaletteData(), Setting.GetVoxelLength());

	OnVoxelContainerChuckInitialized.Broadcast(RegionIndex, ChuckIndex);

	return;
}

FLFPVoxelChuckDelegate& ULFPVoxelContainerComponent::AddRenderChuck(const int32 RegionIndex, const int32 ChuckIndex)
{
	FIntPoint ChuckPos(RegionIndex, ChuckIndex);

	if (ChuckDelegateList.Contains(ChuckPos))
	{
		return ChuckDelegateList.FindChecked(ChuckPos);
	}

	return ChuckDelegateList.Add(ChuckPos, FLFPVoxelChuckDelegate());
}

void ULFPVoxelContainerComponent::RemoveRenderChuck(const int32 RegionIndex, const int32 ChuckIndex, const UObject* RemoveObject)
{
	FIntPoint ChuckPos(RegionIndex, ChuckIndex);

	if (ChuckDelegateList.Contains(ChuckPos) == false) return;

	auto& Delegate = ChuckDelegateList.FindChecked(ChuckPos);

	Delegate.RemoveUObject(RemoveObject);

	if (Delegate.CanRemove()) ChuckDelegateList.Remove(ChuckPos);
}

bool ULFPVoxelContainerComponent::UpdateChuckState()
{
	if (ChuckUpdateStateList.IsEmpty()) return false;

	auto ChuckUpdateState = ChuckUpdateStateList.CreateIterator();

	const FLFPVoxelChuckDelegate* ChuckDelegate = ChuckDelegateList.Find(ChuckUpdateState.Key());

	if (ChuckDelegate != nullptr) ChuckDelegate->Broadcast(ChuckUpdateState.Value());

	ChuckUpdateStateList.Remove(ChuckUpdateState.Key());

	if (ChuckUpdateStateList.Num() == 0)
	{
		ChuckUpdateStateList.Shrink();
	}

	return ChuckUpdateStateList.Num() == 0;
}

bool ULFPVoxelContainerComponent::UpdateChuckData()
{
	if (ChuckUpdateDataList.IsEmpty()) return true;

	if (ContainerThreadLock.TryWriteLock() == false) return false;

	for (const auto& ChuckUpdate : ChuckUpdateDataList)
	{
		/** Check Is Valid */
		if (IsChuckPositionValid(ChuckUpdate.Key.X, ChuckUpdate.Key.Y) == false) continue;

		/** Region Initialization */
		if (IsRegionInitialized(ChuckUpdate.Key.X) == false) InitializeRegion(ChuckUpdate.Key.X);

		/** Chuck Initialization */
		if (IsChuckInitialized(ChuckUpdate.Key.X, ChuckUpdate.Key.Y) == false) InitializeChuck(ChuckUpdate.Key.X, ChuckUpdate.Key.Y);

		FLFPVoxelChuckData& ChuckData = RegionDataList[ChuckUpdate.Key.X].ChuckData[ChuckUpdate.Key.Y];

		TSet<FIntVector> EdgeList = { FIntVector(0) };
		FLFPChuckUpdateAction ChuckUpdateAction;

		/** This change the outdate voxel name */
		for (const auto& ChangeVoxel : ChuckUpdate.Value.ChangePalette)
		{
			bool IsDirty = false;

			if (ChuckData.GetIndexData(ChangeVoxel.Key).VoxelName != ChangeVoxel.Value.VoxelName)
			{
				ChuckUpdateAction.bIsVoxelNameDirty = true;

				IsDirty = true;
			}

			if (ChuckData.GetIndexData(ChangeVoxel.Key).VoxelTag != ChangeVoxel.Value.VoxelTag)
			{
				ChuckUpdateAction.bIsVoxelTagDirty = true;

				IsDirty = true;
			}

			if (IsDirty == false) continue;

			ChuckData.SetIndexData(ChangeVoxel.Key, ChangeVoxel.Value);

			EdgeList.Append(ULFPGridLibrary::GetGridEdgeDirection(ULFPGridLibrary::ToGridLocation(ChangeVoxel.Key, Setting.GetVoxelGrid()), Setting.GetVoxelGrid()));
		}

		const FIntVector CurrentGlobalPos = ToVoxelGlobalPosition(FIntVector(ChuckUpdate.Key.X, ChuckUpdate.Key.Y, 0));

		/** This add update state to list */
		for (const FIntVector& Edge : EdgeList)
		{
			const FIntVector TargetGlobalIndex = ToVoxelGlobalIndex(CurrentGlobalPos + (Edge * Setting.GetVoxelGrid()));

			FLFPChuckUpdateAction& ChuckUpdateData = ChuckUpdateStateList.FindOrAdd(FIntPoint(TargetGlobalIndex.X, TargetGlobalIndex.Y));

			ChuckUpdateData += ChuckUpdateAction;
		}

		OnVoxelContainerChuckUpdate.Broadcast(ChuckUpdate.Key.X, ChuckUpdate.Key.Y, ChuckUpdate.Value);
	}

	ChuckUpdateDataList.Empty();

	ContainerThreadLock.WriteUnlock();

	return true;
}
