// Copyright by Loh Zhi Kang

#include "Components/LFPGridContainerComponent.h"
#include "./Math/LFPGridLibrary.h"
#include "Serialization/ArchiveProxy.h"
#include "Serialization/NameAsStringProxyArchive.h"
#include "Serialization/ArchiveSaveCompressedProxy.h"
#include "Serialization/ArchiveLoadCompressedProxy.h"
#include "UObject/ReflectedTypeAccessors.h"


FLFPGridPaletteData FLFPGridPaletteData::EmptyData = FLFPGridPaletteData();


// Sets default values for this component's properties
ULFPGridContainerComponent::ULFPGridContainerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	// ...
}


// Called when the game starts
void ULFPGridContainerComponent::BeginPlay()
{
	Super::BeginPlay();

	Setting.InitSetting();
}


// Called every frame
void ULFPGridContainerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (UpdateChuckData() == false) return;

	if (UpdateChuckState() == false) return;

	SetComponentTickEnabled(false);
}

//FString ULFPGridContainerComponent::MemorySize(const int32 SaveFileAmount, const int32 ChuckAmount, const int32 GridAmount) const
//{
//	unsigned long long TotalSize = (5 * GridAmount) * ChuckAmount * SaveFileAmount;
//	unsigned long long SaveSize = (5 * GridAmount) * ChuckAmount;
//	unsigned long long ChuckSize = (5 * GridAmount);
//
//	return FString::Printf(TEXT("Total : %llu : SaveData : %llu : ChuckData : %llu : FName : %llu"), 
//		TotalSize,
//		SaveSize,
//		ChuckSize,
//		sizeof(FName));
//}

FString ULFPGridContainerComponent::Test()
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

bool ULFPGridContainerComponent::IsRegionInitialized(const int32 RegionIndex) const
{
	return RegionDataList.IsValidIndex(RegionIndex) && RegionDataList[RegionIndex].IsInitialized();
}

bool ULFPGridContainerComponent::IsChuckInitialized(const int32 RegionIndex, const int32 ChuckIndex) const
{
	return IsRegionInitialized(RegionIndex) && RegionDataList[RegionIndex].ChuckData.IsValidIndex(ChuckIndex) && RegionDataList[RegionIndex].ChuckData[ChuckIndex].IsInitialized();
}

bool ULFPGridContainerComponent::IsRegionPositionValid(const int32 RegionIndex) const
{
	return Setting.GetRegionLength() > RegionIndex && RegionIndex >= 0;
}

bool ULFPGridContainerComponent::IsChuckPositionValid(const int32 RegionIndex, const int32 ChuckIndex) const
{
	return IsRegionPositionValid(RegionIndex) && Setting.GetChuckLength() > ChuckIndex && ChuckIndex >= 0;
}

bool ULFPGridContainerComponent::IsGridPositionValid(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex) const
{
	return IsChuckPositionValid(RegionIndex, ChuckIndex) && Setting.GetGridLength() > GridIndex && GridIndex >= 0;
}

bool ULFPGridContainerComponent::AddPaletteTag(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex, const FName& GridTag)
{
	if (IsGridPositionValid(RegionIndex, ChuckIndex, GridIndex) == false) return false;

	FLFPGridPaletteData NewPalette(GetGridPalette(RegionIndex, ChuckIndex, GridIndex));

	NewPalette.AddTag(GridTag);

	return SetGridPalette(RegionIndex, ChuckIndex, GridIndex, NewPalette);
}

bool ULFPGridContainerComponent::AddPaletteTagData(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex, const FName& GridTag, const uint8 GridData)
{
	if (IsGridPositionValid(RegionIndex, ChuckIndex, GridIndex) == false) return false;

	FLFPGridPaletteData NewPalette(GetGridPalette(RegionIndex, ChuckIndex, GridIndex));

	NewPalette.AddTagData(GridTag, GridData);

	return SetGridPalette(RegionIndex, ChuckIndex, GridIndex, NewPalette);
}

bool ULFPGridContainerComponent::RemovePaletteTag(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex, const FName& GridTag)
{
	if (IsGridPositionValid(RegionIndex, ChuckIndex, GridIndex) == false) return false;

	FLFPGridPaletteData NewPalette(GetGridPalette(RegionIndex, ChuckIndex, GridIndex));

	NewPalette.RemoveTag(GridTag);

	return SetGridPalette(RegionIndex, ChuckIndex, GridIndex, NewPalette);
}

bool ULFPGridContainerComponent::RemovePaletteTagData(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex, const FName& GridTag)
{
	if (IsGridPositionValid(RegionIndex, ChuckIndex, GridIndex) == false) return false;

	FLFPGridPaletteData NewPalette(GetGridPalette(RegionIndex, ChuckIndex, GridIndex));

	NewPalette.RemoveTagData(GridTag);

	return SetGridPalette(RegionIndex, ChuckIndex, GridIndex, NewPalette);
}

/** Setter */

bool ULFPGridContainerComponent::SetGridPalette(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex, const FLFPGridPaletteData& GridPalette)
{
	if (IsGridPositionValid(RegionIndex, ChuckIndex, GridIndex) == false || GridPalette.IsValid() == false) return false;

	ChuckUpdateDataList.FindOrAdd(FIntPoint(RegionIndex, ChuckIndex)).ChangePalette.Add(GridIndex, GridPalette);

	SetComponentTickEnabled(true);

	return true;
}

bool ULFPGridContainerComponent::SetGridPalettes(const int32 RegionIndex, const int32 ChuckIndex, const TMap<int32, FLFPGridPaletteData>& GridPaletteMap)
{
	if (IsChuckPositionValid(RegionIndex, ChuckIndex) == false) return false;

	for (const auto& GridPalette : GridPaletteMap)
	{
		if (Setting.GetGridLength() <= GridPalette.Key || GridPalette.Key < 0) continue;

		ChuckUpdateDataList.FindOrAdd(FIntPoint(RegionIndex, ChuckIndex)).ChangePalette.Add(GridPalette);
	}

	SetComponentTickEnabled(true);

	return true;
}

bool ULFPGridContainerComponent::SetGridChuckData(const int32 RegionIndex, const int32 ChuckIndex, const FLFPGridChuckData& ChuckData)
{
	if (IsChuckPositionValid(RegionIndex, ChuckIndex) == false || ChuckData.GetIndexSize() != Setting.GetGridLength()) return false;

	bool bIsAllSuccess = true;
	bool bHasPassed = false;

	for (int32 GridIndex = 0; GridIndex < Setting.GetGridLength(); GridIndex++)
	{
		if (ChuckData.GetIndexData(GridIndex) != GetGridPaletteRef(RegionIndex, ChuckIndex, GridIndex)) 
		{
			bHasPassed = true;

			if (SetGridPalette(RegionIndex, ChuckIndex, GridIndex, ChuckData.GetIndexData(GridIndex)) == false)
			{
				bIsAllSuccess = false;
			}
		}
	}

	return bIsAllSuccess && bHasPassed;
}

bool ULFPGridContainerComponent::InitializeGridChuck(const int32 RegionIndex, const int32 ChuckIndex)
{
	if (IsChuckPositionValid(RegionIndex, ChuckIndex) == false) return false;

	ChuckUpdateDataList.FindOrAdd(FIntPoint(RegionIndex, ChuckIndex));

	SetComponentTickEnabled(true);

	return true;
}

/** Getter */

int32 ULFPGridContainerComponent::GetRenderChuckAmount(const int32 RegionIndex, const int32 ChuckIndex) const
{
	return ChuckDelegateList.Contains(FIntPoint(RegionIndex, ChuckIndex)) ? ChuckDelegateList.FindChecked(FIntPoint(RegionIndex, ChuckIndex)).GetAmount() : INDEX_NONE;
}

FLFPGridChuckData ULFPGridContainerComponent::GetGridChuckData(const int32 RegionIndex, const int32 ChuckIndex) const
{
	if (IsRegionInitialized(RegionIndex) == false || RegionDataList[RegionIndex].ChuckData.IsValidIndex(ChuckIndex) == false) return FLFPGridChuckData();

	return RegionDataList[RegionIndex].ChuckData[ChuckIndex];
}

FLFPGridPaletteData ULFPGridContainerComponent::GetGridPalette(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex) const
{
	if (IsGridPositionValid(RegionIndex, ChuckIndex, GridIndex) == false || IsChuckInitialized(RegionIndex, ChuckIndex) == false) return FLFPGridPaletteData();

	return RegionDataList[RegionIndex].ChuckData[ChuckIndex].GetIndexData(GridIndex);
}

TArray<FLFPGridPaletteData> ULFPGridContainerComponent::GetGridPaletteList(const int32 RegionIndex, const int32 ChuckIndex) const
{
	if (IsChuckInitialized(RegionIndex, ChuckIndex) == false) return TArray<FLFPGridPaletteData>();

	return RegionDataList[RegionIndex].ChuckData[ChuckIndex].GetPaletteList();
}

int32 ULFPGridContainerComponent::GetGridPaletteIndex(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex) const
{
	if (IsGridPositionValid(RegionIndex, ChuckIndex, GridIndex) == false || IsChuckInitialized(RegionIndex, ChuckIndex) == false) return INDEX_NONE;

	return RegionDataList[RegionIndex].ChuckData[ChuckIndex].GetPaletteIndex(GridIndex);
}

FIntVector ULFPGridContainerComponent::ToGridGlobalPosition(const FIntVector GridGlobalIndex) const
{
	const FIntVector RegionPos(ULFPGridLibrary::ToGridLocation(GridGlobalIndex.X, Setting.GetRegionGrid()));
	const FIntVector ChuckPos(ULFPGridLibrary::ToGridLocation(GridGlobalIndex.Y, Setting.GetChuckGrid()));
	const FIntVector GridPos(ULFPGridLibrary::ToGridLocation(GridGlobalIndex.Z, Setting.GetPaletteGrid()));

	return (RegionPos * Setting.GetChuckGrid() * Setting.GetPaletteGrid()) + (ChuckPos * Setting.GetPaletteGrid()) + GridPos;
}

FIntVector ULFPGridContainerComponent::ToGridGlobalIndex(const FIntVector GridGlobalPosition) const
{
	auto DivideVector = [&](const FIntVector& A, const FIntVector& B) {
		return FIntVector(A.X / B.X, A.Y / B.Y, A.Z / B.Z);
	};

	auto PercentageVector = [&](const FIntVector& A, const FIntVector& B) {
		return FIntVector(A.X % B.X, A.Y % B.Y, A.Z % B.Z);
	};

	const FIntVector RegionGridSize(Setting.GetChuckGrid() * Setting.GetPaletteGrid());

	const FIntVector RegionPos	(DivideVector(GridGlobalPosition, RegionGridSize));
	const FIntVector ChuckPos	(PercentageVector(DivideVector(GridGlobalPosition, Setting.GetPaletteGrid()), Setting.GetChuckGrid()));
	const FIntVector GridPos	(PercentageVector(GridGlobalPosition, Setting.GetPaletteGrid()));

	return FIntVector(ULFPGridLibrary::ToGridIndex(RegionPos, Setting.GetRegionGrid()), ULFPGridLibrary::ToGridIndex(ChuckPos, Setting.GetChuckGrid()), ULFPGridLibrary::ToGridIndex(GridPos, Setting.GetPaletteGrid()));
}

/** C++ Getter */

const FLFPGridPaletteData& ULFPGridContainerComponent::GetGridPaletteRef(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex) const
{
	if (IsGridPositionValid(RegionIndex, ChuckIndex, GridIndex) == false || IsChuckInitialized(RegionIndex, ChuckIndex) == false) return FLFPGridPaletteData::EmptyData;

	return RegionDataList[RegionIndex].ChuckData[ChuckIndex].GetIndexData(GridIndex);
}

bool ULFPGridContainerComponent::GetGridChuckDataByArchive(const int32 RegionIndex, const int32 ChuckIndex, FArchive& Ar)
{
	if (IsChuckInitialized(RegionIndex, ChuckIndex) == false) return false;

	uint8 DataID = 0;

	Ar << DataID;

	Ar << RegionDataList[RegionIndex].ChuckData[ChuckIndex];

	return true;
}

/** C++ Setter */

bool ULFPGridContainerComponent::SetGridChuckDataByArchive(const int32 RegionIndex, const int32 ChuckIndex, FArchive& Ar)
{
	if (IsChuckPositionValid(RegionIndex, ChuckIndex) == false) return false;

	uint8 DataID = 0;

	Ar << DataID;

	switch (DataID)
	{
	case 0:
	{
		FLFPGridChuckData DecompressedChuckData = FLFPGridChuckData();
		Ar << DecompressedChuckData;
		return SetGridChuckData(RegionIndex, ChuckIndex, DecompressedChuckData);
	}
	break;

	case 1:
	{
		TMap<int32, FLFPGridPaletteData> DecompressedChuckGridPalettes;
		Ar << DecompressedChuckGridPalettes;
		return SetGridPalettes(RegionIndex, ChuckIndex, DecompressedChuckGridPalettes);
	}
	break;

	}

	UE_LOG(LogTemp, Error, TEXT("LFPGridContainerComponent : SetGridChuckDataByArchive DataID Invalid : %d"), DataID);

	return false;
}

void ULFPGridContainerComponent::InitializeRegion(const int32 RegionIndex)
{
	check(IsRegionPositionValid(RegionIndex));

	if (RegionDataList.IsValidIndex(RegionIndex) == false) RegionDataList.SetNum(RegionIndex + 1);

	auto& ChuckData = RegionDataList[RegionIndex];

	ChuckData.InitRegionData(Setting.GetChuckLength());

	OnGridContainerRegionInitialized.Broadcast(RegionIndex);

	return;
}

void ULFPGridContainerComponent::InitializeChuck(const int32 RegionIndex, const int32 ChuckIndex)
{
	check(RegionDataList.IsValidIndex(RegionIndex) && RegionDataList[RegionIndex].ChuckData.IsValidIndex(ChuckIndex));

	auto& ChuckData = RegionDataList[RegionIndex].ChuckData[ChuckIndex];

	ChuckData.InitChuckData(FLFPGridPaletteData(), Setting.GetGridLength());

	OnGridContainerChuckInitialized.Broadcast(RegionIndex, ChuckIndex);

	return;
}

FLFPGridChuckDelegate& ULFPGridContainerComponent::AddRenderChuck(const int32 RegionIndex, const int32 ChuckIndex)
{
	FIntPoint ChuckPos(RegionIndex, ChuckIndex);

	if (ChuckDelegateList.Contains(ChuckPos))
	{
		return ChuckDelegateList.FindChecked(ChuckPos);
	}

	return ChuckDelegateList.Add(ChuckPos, FLFPGridChuckDelegate());
}

void ULFPGridContainerComponent::RemoveRenderChuck(const int32 RegionIndex, const int32 ChuckIndex, const UObject* RemoveObject)
{
	FIntPoint ChuckPos(RegionIndex, ChuckIndex);

	if (ChuckDelegateList.Contains(ChuckPos) == false) return;

	auto& Delegate = ChuckDelegateList.FindChecked(ChuckPos);

	Delegate.RemoveUObject(RemoveObject);

	if (Delegate.CanRemove()) ChuckDelegateList.Remove(ChuckPos);
}

bool ULFPGridContainerComponent::UpdateChuckState()
{
	if (ChuckUpdateStateList.IsEmpty()) return false;

	auto ChuckUpdateState = ChuckUpdateStateList.CreateIterator();

	const FLFPGridChuckDelegate* ChuckDelegate = ChuckDelegateList.Find(ChuckUpdateState.Key());

	if (ChuckDelegate != nullptr) ChuckDelegate->Broadcast(ChuckUpdateState.Value());

	ChuckUpdateStateList.Remove(ChuckUpdateState.Key());

	if (ChuckUpdateStateList.Num() == 0)
	{
		ChuckUpdateStateList.Shrink();
	}

	return ChuckUpdateStateList.Num() == 0;
}

bool ULFPGridContainerComponent::UpdateChuckData()
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

		FLFPGridChuckData& ChuckData = RegionDataList[ChuckUpdate.Key.X].ChuckData[ChuckUpdate.Key.Y];

		TSet<FIntVector> EdgeList = { FIntVector(0) };
		FLFPChuckUpdateAction ChuckUpdateAction;

		/** This change the outdate Grid name */
		for (const auto& ChangeGrid : ChuckUpdate.Value.ChangePalette)
		{
			bool IsDirty = false;

			if (ChuckData.GetIndexData(ChangeGrid.Key).Name != ChangeGrid.Value.Name)
			{
				ChuckUpdateAction.bIsGridNameDirty = true;

				IsDirty = true;
			}

			if (ChuckData.GetIndexData(ChangeGrid.Key).TagList != ChangeGrid.Value.TagList)
			{
				ChuckUpdateAction.bIsGridTagDirty = true;

				IsDirty = true;
			}

			if (IsDirty == false) continue;

			ChuckData.SetIndexData(ChangeGrid.Key, ChangeGrid.Value);

			EdgeList.Append(ULFPGridLibrary::GetGridEdgeDirection(ULFPGridLibrary::ToGridLocation(ChangeGrid.Key, Setting.GetPaletteGrid()), Setting.GetPaletteGrid()));
		}

		const FIntVector CurrentGlobalPos = ToGridGlobalPosition(FIntVector(ChuckUpdate.Key.X, ChuckUpdate.Key.Y, 0));

		/** This add update state to list */
		for (const FIntVector& Edge : EdgeList)
		{
			const FIntVector TargetGlobalIndex = ToGridGlobalIndex(CurrentGlobalPos + (Edge * Setting.GetPaletteGrid()));

			FLFPChuckUpdateAction& ChuckUpdateData = ChuckUpdateStateList.FindOrAdd(FIntPoint(TargetGlobalIndex.X, TargetGlobalIndex.Y));

			ChuckUpdateData += ChuckUpdateAction;
		}

		OnGridContainerChuckUpdate.Broadcast(ChuckUpdate.Key.X, ChuckUpdate.Key.Y, ChuckUpdate.Value);
	}

	ChuckUpdateDataList.Empty();

	ContainerThreadLock.WriteUnlock();

	return true;
}