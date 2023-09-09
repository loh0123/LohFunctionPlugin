// Copyright by Loh Zhi Kang

#include "Components/LFPGridContainerComponent.h"
#include "./Math/LFPGridLibrary.h"
#include "Serialization/ArchiveProxy.h"
#include "Serialization/NameAsStringProxyArchive.h"
#include "Serialization/ArchiveSaveCompressedProxy.h"
#include "Serialization/ArchiveLoadCompressedProxy.h"
#include "UObject/ReflectedTypeAccessors.h"


FLFPGridPaletteData FLFPGridPaletteData::EmptyData = FLFPGridPaletteData();
FLFPGridChuckData FLFPGridChuckData::EmptyData = FLFPGridChuckData();


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

	if (IsValid(TagDataTable))
	{
		if (TagDataTable->GetRowStruct()->IsChildOf(FLFPGridTagDataTable::StaticStruct()) == false)
		{
			TagDataTable = nullptr;

			UE_LOG(LogTemp, Warning, TEXT("TagDataTable Is Not Using Struct ( FLFPGridTagDataTable )"));
		}
	}
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

	auto& NewPalette = ChuckUpdateDataList.FindOrAdd(FIntPoint(RegionIndex, ChuckIndex)).ChangePalette.FindOrAdd(GridIndex);

	if (NewPalette.IsNone()) NewPalette = (GetGridPalette(RegionIndex, ChuckIndex, GridIndex));

	NewPalette.AddTag(GridTag);

	SetComponentTickEnabled(true);

	return true;
}

bool ULFPGridContainerComponent::RemovePaletteTag(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex, const FName& GridTag)
{
	if (IsGridPositionValid(RegionIndex, ChuckIndex, GridIndex) == false) return false;

	auto& NewPalette = ChuckUpdateDataList.FindOrAdd(FIntPoint(RegionIndex, ChuckIndex)).ChangePalette.FindOrAdd(GridIndex);

	if (NewPalette.IsNone()) NewPalette = (GetGridPalette(RegionIndex, ChuckIndex, GridIndex));

	NewPalette.RemoveTag(GridTag);

	SetComponentTickEnabled(true);

	return true;
}

/** Setter */

bool ULFPGridContainerComponent::SetTagData(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex, const FName GridTag, const uint8 GridData)
{
	if (IsGridPositionValid(RegionIndex, ChuckIndex, GridIndex) == false) return false;

	ChuckUpdateDataList.FindOrAdd(FIntPoint(RegionIndex, ChuckIndex)).ChangeTagData.FindOrAdd(GridIndex).ChangeData.Add(GridTag, GridData);

	SetComponentTickEnabled(true);

	return true;
}

bool ULFPGridContainerComponent::SetGridPalette(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex, const FLFPGridPaletteData& GridPalette)
{
	if (IsGridPositionValid(RegionIndex, ChuckIndex, GridIndex) == false/* || GridPalette.IsValid() == false*/) return false;

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

uint8 ULFPGridContainerComponent::GetGridTagData(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex, const FName TagName) const
{
	if (IsGridPositionValid(RegionIndex, ChuckIndex, GridIndex) == false || IsChuckInitialized(RegionIndex, ChuckIndex) == false) return uint8(0);

	return RegionDataList[RegionIndex].ChuckData[ChuckIndex].GetTagData(GridIndex, TagName);
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

FIntVector ULFPGridContainerComponent::ToGridGlobalPosition(const FIntVector GridGlobalIndex, const bool bRound) const
{
	FIntVector RegionPos(ULFPGridLibrary::ToGridLocation(GridGlobalIndex.X, Setting.GetRegionGrid(), bRound));
	const FIntVector ChuckPos(ULFPGridLibrary::ToGridLocation(GridGlobalIndex.Y, Setting.GetChuckGrid(), bRound));
	const FIntVector GridPos(ULFPGridLibrary::ToGridLocation(GridGlobalIndex.Z, Setting.GetPaletteGrid(), bRound));

	if (bSwitchRegionZWithX) RegionPos = FIntVector(RegionPos.Z, RegionPos.Y, RegionPos.X);

	return (RegionPos * Setting.GetChuckGrid() * Setting.GetPaletteGrid()) + (ChuckPos * Setting.GetPaletteGrid()) + GridPos;
}

FIntVector ULFPGridContainerComponent::ToGridGlobalIndex(FIntVector GridGlobalPosition, const bool bRound) const
{
	auto DivideVector = [&](const FIntVector& A, const FIntVector& B) {
		return FIntVector(A.X / B.X, A.Y / B.Y, A.Z / B.Z);
	};

	const FIntVector TotalSize(Setting.GetRegionGrid() * Setting.GetChuckGrid() * Setting.GetPaletteGrid());

	if (bRound)
	{
		GridGlobalPosition.X %= TotalSize.X;
		GridGlobalPosition.Y %= TotalSize.Y;
		GridGlobalPosition.Z %= TotalSize.Z;

		if (GridGlobalPosition.X < 0) GridGlobalPosition.X += TotalSize.X;
		if (GridGlobalPosition.Y < 0) GridGlobalPosition.Y += TotalSize.Y;
		if (GridGlobalPosition.Z < 0) GridGlobalPosition.Z += TotalSize.Z;
	}
	else if (ULFPGridLibrary::IsGridLocationValid(GridGlobalPosition, TotalSize) == false)
	{
		return FIntVector(INDEX_NONE);
	}

	FIntVector RegionPos	(DivideVector(GridGlobalPosition, Setting.GetChuckGrid() * Setting.GetPaletteGrid()));
	const FIntVector ChuckPos	(DivideVector(GridGlobalPosition, Setting.GetPaletteGrid()));

	if (bSwitchRegionZWithX) RegionPos = FIntVector(RegionPos.Z, RegionPos.Y, RegionPos.X);

	return FIntVector(ULFPGridLibrary::ToGridIndex(RegionPos, Setting.GetRegionGrid()), ULFPGridLibrary::ToGridIndex(ChuckPos, Setting.GetChuckGrid()), ULFPGridLibrary::ToGridIndex(GridGlobalPosition, Setting.GetPaletteGrid(), true));
}

FIntVector ULFPGridContainerComponent::AddGridGlobalPositionOffset(const FIntVector GridGlobalPosition, const FIntVector GridGlobalIndexOffset, const bool bRound) const
{
	return ToGridGlobalPosition(ToGridGlobalIndex(GridGlobalPosition, bRound) + GridGlobalIndexOffset, bRound);
}

FIntVector ULFPGridContainerComponent::AddGridGlobalIndexOffset(const FIntVector GridGlobalIndex, const FIntVector GridGlobalPositionOffset, const bool bRound) const
{
	return ToGridGlobalIndex(ToGridGlobalPosition(GridGlobalIndex, bRound) + GridGlobalPositionOffset, bRound);
}

/** C++ Getter */

const FLFPGridPaletteData& ULFPGridContainerComponent::GetGridPaletteRef(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex) const
{
	if (IsGridPositionValid(RegionIndex, ChuckIndex, GridIndex) == false || IsChuckInitialized(RegionIndex, ChuckIndex) == false) return FLFPGridPaletteData::EmptyData;

	return RegionDataList[RegionIndex].ChuckData[ChuckIndex].GetIndexData(GridIndex);
}

bool ULFPGridContainerComponent::GetGridTagDataListRef(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex, TMap<FName, uint8>& TagDataList) const
{
	if (IsGridPositionValid(RegionIndex, ChuckIndex, GridIndex) == false || IsChuckInitialized(RegionIndex, ChuckIndex) == false) return false;

	RegionDataList[RegionIndex].ChuckData[ChuckIndex].GetTagDataList(GridIndex, TagDataList);

	return true;
}

const FLFPGridChuckData& ULFPGridContainerComponent::GetGridChuckRef(const int32 RegionIndex, const int32 ChuckIndex) const
{
	if (IsChuckPositionValid(RegionIndex, ChuckIndex) == false || IsRegionInitialized(RegionIndex) == false) return FLFPGridChuckData::EmptyData;

	return RegionDataList[RegionIndex].ChuckData[ChuckIndex];
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

void ULFPGridContainerComponent::RemoveRenderChuck(const int32 RegionIndex, const int32 ChuckIndex, const UActorComponent* RemoveObject)
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

	for (const auto& ChuckUpdateState : ChuckUpdateStateList)
	{
		const FLFPGridChuckDelegate* ChuckDelegate = ChuckDelegateList.Find(ChuckUpdateState.Key);

		if (ChuckDelegate != nullptr) ChuckDelegate->Broadcast(ChuckUpdateState.Value);
	}

	ChuckUpdateStateList.Empty();

	return false;
}

bool ULFPGridContainerComponent::UpdateChuckData()
{
	if (ChuckUpdateDataList.IsEmpty()) return true;

	if (ContainerThreadLock.TryWriteLock() == false) return false;

	const auto CacheChuckUpdateDataList = ChuckUpdateDataList;

	ChuckUpdateDataList.Empty();

	for (const auto& ChuckUpdate : CacheChuckUpdateDataList)
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
				ChuckUpdateAction.GridChangeNameList.Add(FLFPGridNameUpdateData(ChuckData.GetIndexData(ChangeGrid.Key).Name, ChangeGrid.Value.Name));

				ChuckUpdateAction.GridDirtyIndexList.Add(ChangeGrid.Key);

				IsDirty = true;
			}

			if (ChuckData.GetIndexData(ChangeGrid.Key).TagList != ChangeGrid.Value.TagList)
			{
				ChuckUpdateAction.GridDirtyIndexList.Add(ChangeGrid.Key);

				IsDirty = true;
			}

			if (IsDirty == false) continue;

			ChuckData.SetIndexData(ChangeGrid.Key, ChangeGrid.Value);

			EdgeList.Append(ULFPGridLibrary::GetGridEdgeDirection(ULFPGridLibrary::ToGridLocation(ChangeGrid.Key, Setting.GetPaletteGrid()), Setting.GetPaletteGrid()));
		}

		/** This change the outdate Attribute texture */
		{
			for (const auto& ChangeTag : ChuckUpdate.Value.ChangeTagData)
			{
				ChuckUpdateAction.GridDirtyIndexList.Add(ChangeTag.Key);

				for (const auto& ChangeData : ChangeTag.Value.ChangeData)
				{
					const FLFPGridTagDataTable* TagDataRef = IsValid(TagDataTable) ? reinterpret_cast<FLFPGridTagDataTable*>(TagDataTable->FindRowUnchecked(ChangeData.Key)) : nullptr;

					ChuckData.SetTagData(ChangeTag.Key, ChangeData.Key, ChangeData.Value, TagDataRef != nullptr ? TagDataRef->DataSize : uint8(255));
				}
			}
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

	ContainerThreadLock.WriteUnlock();

	/** ChuckUpdateDataList Maybe Updated After Event Broadcast */
	return ChuckUpdateDataList.IsEmpty();
}
