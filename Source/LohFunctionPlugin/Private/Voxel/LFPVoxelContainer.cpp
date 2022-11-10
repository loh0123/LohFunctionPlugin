// Copyright (c) 2022 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)



#include "Voxel/LFPVoxelContainer.h"
#include "./Math/LFPGridLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Voxel/LFPVoxelContainerInterface.h"

ULFPVoxelContainer::ULFPVoxelContainer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void ULFPVoxelContainer::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ULFPVoxelContainer, ChuckData);
}

void ULFPVoxelContainer::InitializeChuck(const int32 ChuckIndex, const FName& VoxelName, const bool bSkipLock)
{
	check(IsChuckIndexValid(ChuckIndex));

	if (bSkipLock == false) FRWScopeLock WriteLock(GetContainerThreadLock(), SLT_Write);

	if (ChuckData[ChuckIndex].IsInitialized() == false)
	{
		if (GetOwner()->Implements<ULFPVoxelContainerInterface>())
		{
			const FIntVector ChuckGridLocation = ULFPGridLibrary::ToGridLocation(ChuckIndex, ContainerSetting.ChuckGridSize);

			const FIntVector VoxelStartLocation = FIntVector(ChuckGridLocation.X * ContainerSetting.VoxelGridSize.X, ChuckGridLocation.Y * ContainerSetting.VoxelGridSize.Y, ChuckGridLocation.Z * ContainerSetting.VoxelGridSize.Z);

			TArray<FName> NameDataList;
			TArray<FLFPVoxelDynamicAttributeData> AttributeDataList;

			NameDataList.AddZeroed(ContainerSetting.VoxelLength);
			AttributeDataList.AddZeroed(ContainerSetting.VoxelLength);

			ParallelFor(ContainerSetting.VoxelLength, [&](const int32 VoxelIndex) {
				ILFPVoxelContainerInterface::Execute_InitializeVoxelData(GetOwner(), VoxelStartLocation + ULFPGridLibrary::ToGridLocation(VoxelIndex, ContainerSetting.VoxelGridSize), NameDataList[VoxelIndex], AttributeDataList[VoxelIndex]);
				});

			ChuckData[ChuckIndex].InitChuckData(ContainerSetting.VoxelLength, NameDataList, AttributeDataList);
		}
		else
		{
			ChuckData[ChuckIndex].InitChuckData(ContainerSetting.VoxelLength, VoxelName);
		}
	}
}

FLFPVoxelWriteAction* ULFPVoxelContainer::FindOrAddChuckWriteAction(const int32& ChuckIndex)
{
	if (IsChuckIndexValid(ChuckIndex) == false) return nullptr;

	FLFPVoxelWriteAction* Action = ChuckWriteActionList.Find(ChuckIndex);

	if (Action == nullptr) Action = &ChuckWriteActionList.Add(ChuckIndex, FLFPVoxelWriteAction());

	return Action;
}

void ULFPVoxelContainer::BeginPlay()
{
	SetupVoxelData(VoxelAttributeTable, ContainerSetting);

	Super::BeginPlay();
}

void ULFPVoxelContainer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsThreadReading == false)
	{
		if (ChuckWriteActionList.Num() > 0)
		{
			UpdateChuckWriteAction();
		}
		else
		{
			UpdateChuckAttribute();
			UpdateChuckName();
		}
	}
}

int32 ULFPVoxelContainer::GetContainerSize()
{
	return GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
}

void ULFPVoxelContainer::UpdateChuckWriteAction()
{
	if (ChuckWriteActionList.IsEmpty()) return;

	FRWScopeLock WriteLock(GetContainerThreadLock(), SLT_Write);
	
	TArray<int32> RemoveList;

	RemoveList.Reserve(ContainerSetting.WriteActionBatchAmount);

	int32 Index = 0;

	for (auto ChuckWriteAction = ChuckWriteActionList.CreateIterator(); ChuckWriteAction && Index < ContainerSetting.WriteActionBatchAmount; ++ChuckWriteAction)
	{
		Index++;

		if (ChuckData[ChuckWriteAction.Key()].IsInitialized() == false)
		{
			InitializeChuck(ChuckWriteAction.Key(), ContainerSetting.InvisibleName, true);

			MarkChuckForNameUpdate(ChuckWriteAction.Key(), true);
		}

		for (const auto& VoxelName : ChuckWriteAction.Value().NameData)
		{
			const FName OldName = ChuckData[ChuckWriteAction.Key()].VoxelNameData[VoxelName.Key];

			if (OldName == VoxelName.Value) continue;

			ChuckData[ChuckWriteAction.Key()].SetVoxelName(VoxelName.Key, VoxelName.Value);

			const FIntVector VoxelLocation = ULFPGridLibrary::ToGridLocation(VoxelName.Key, ContainerSetting.VoxelGridSize);

			MarkChuckForNameUpdate(ChuckWriteAction.Key(), ULFPGridLibrary::IsOnGridEdge(VoxelLocation, ContainerSetting.VoxelGridSize));
		}

		for (const auto& VoxelColor : ChuckWriteAction.Value().AttributeData)
		{
			ChuckData[ChuckWriteAction.Key()].SetVoxelAttribute(VoxelColor.Key, VoxelColor.Value);

			const FIntVector VoxelLocation = ULFPGridLibrary::ToGridLocation(VoxelColor.Key, ContainerSetting.VoxelGridSize);

			MarkChuckForAttributeUpdate(ChuckWriteAction.Key(), ULFPGridLibrary::IsOnGridEdge(VoxelLocation, ContainerSetting.VoxelGridSize));
		}

		RemoveList.Add(ChuckWriteAction.Key());
	}

	for (const int32 RemoveKey : RemoveList)
	{
		ChuckWriteActionList.Remove(RemoveKey);
	}

	if (ChuckWriteActionList.Num() == 0)
	{
		ChuckWriteActionList.Shrink();

		VoxelWriteActionListCompleteEvent.Broadcast();
	}

	return;
}

void ULFPVoxelContainer::UpdateChuckName()
{
	if (BatchChuckNameUpdateList.IsEmpty()) return;

	auto ChuckNameUpdate = BatchChuckNameUpdateList.CreateIterator();

	ChuckData[*ChuckNameUpdate].SendNameUpdateEvent();

	VoxelChuckNameUpdateEvent.Broadcast(*ChuckNameUpdate);

	BatchChuckNameUpdateList.Remove(*ChuckNameUpdate);

	if (BatchChuckNameUpdateList.Num() == 0)
	{
		BatchChuckNameUpdateList.Shrink();

		VoxelChuckNameListCompleteEvent.Broadcast();
	}

	return;
}

void ULFPVoxelContainer::UpdateChuckAttribute()
{
	if (BatchChuckAttributeUpdateList.IsEmpty()) return;

	auto ChuckAttributeUpdate = BatchChuckAttributeUpdateList.CreateIterator();
	
	ChuckData[*ChuckAttributeUpdate].SendAttributeUpdateEvent();

	VoxelChuckAttributeUpdateEvent.Broadcast(*ChuckAttributeUpdate);
	
	BatchChuckAttributeUpdateList.Remove(*ChuckAttributeUpdate);

	if (BatchChuckAttributeUpdateList.Num() == 0)
	{
		BatchChuckAttributeUpdateList.Shrink();

		VoxelChuckAttributeListCompleteEvent.Broadcast();
	}

	return;
}

void ULFPVoxelContainer::MarkChuckForNameUpdate(const int32 ChuckIndex, const bool bUpdateNearbyChuck)
{
	MarkChuckForAttributeUpdate(ChuckIndex, bUpdateNearbyChuck);

	if (bUpdateNearbyChuck)
	{
		const TArray<FIntVector> UpdateDirection =
		{
			FIntVector(0, 0, 1),
			FIntVector(0, 0,-1),
			FIntVector(0, 1, 0),
			FIntVector(0,-1, 0),
			FIntVector(1, 0, 0),
			FIntVector(-1, 0, 0)
		};

		const FIntVector ChuckLocation = ULFPGridLibrary::ToGridLocation(ChuckIndex, ContainerSetting.ChuckGridSize);

		for (const FIntVector& Direction : UpdateDirection)
		{
			const int32 CurChuckIndex = ULFPGridLibrary::ToIndex(ChuckLocation + Direction, ContainerSetting.ChuckGridSize);

			if (CurChuckIndex != INDEX_NONE && IsChuckInitialized(CurChuckIndex))
			{
				BatchChuckNameUpdateList.Add(CurChuckIndex);
			}
		}
	}

	BatchChuckNameUpdateList.Add(ChuckIndex);

	return;
}

void ULFPVoxelContainer::MarkChuckForAttributeUpdate(const int32 ChuckIndex, const bool bUpdateNearbyChuck)
{
	if (bUpdateNearbyChuck)
	{
		const TArray<FIntVector> UpdateDirection =
		{
			FIntVector(0, 0, 1),
			FIntVector(0, 0,-1),
			FIntVector(0, 1, 0),
			FIntVector(0,-1, 0),
			FIntVector(1, 0, 0),
			FIntVector(-1, 0, 0)
		};

		const FIntVector ChuckLocation = ULFPGridLibrary::ToGridLocation(ChuckIndex, ContainerSetting.ChuckGridSize);

		for (const FIntVector& Direction : UpdateDirection)
		{
			const int32 CurChuckIndex = ULFPGridLibrary::ToIndex(ChuckLocation + Direction, ContainerSetting.ChuckGridSize);

			if (CurChuckIndex != INDEX_NONE && IsChuckInitialized(CurChuckIndex))
			{
				BatchChuckAttributeUpdateList.Add(CurChuckIndex);
			}
		}
	}

	BatchChuckAttributeUpdateList.Add(ChuckIndex);

	return;
}

bool ULFPVoxelContainer::SetupVoxelData(UDataTable* NewVoxelAttributeTable, const FLFPVoxelContainerSettingV2 NewSetting)
{
	FRWScopeLock WriteLock(GetContainerThreadLock(), SLT_Write);

	if (NewVoxelAttributeTable == nullptr || NewVoxelAttributeTable->GetRowStruct()->IsChildOf(FLFPVoxelStaticAttributeData::StaticStruct()) == false)
	{
		VoxelAttributeTable = nullptr;
		ContainerSetting = FLFPVoxelContainerSettingV2();

		return false;
	}

	ContainerSetting = NewSetting;

	ContainerSetting.InitSetting();

	ChuckData.Init(FLFPVoxelChuckDataV2(), ContainerSetting.ChuckLength);

	VoxelAttributeTable = NewVoxelAttributeTable;

	return true;
}

bool ULFPVoxelContainer::IsChuckInitialized(const int32 ChuckIndex) const
{
	if (!ChuckData.IsValidIndex(ChuckIndex)) return false;

	return ChuckData[ChuckIndex].IsInitialized();
}

FLFPVoxelGridIndex ULFPVoxelContainer::ToVoxelGridIndex(const FIntVector VoxelGridLocation) const
{
	FLFPVoxelGridIndex ReturnData;

	if (VoxelGridLocation.GetMin() < 0) return ReturnData;

	ReturnData.ChuckIndex = ULFPGridLibrary::ToIndex(FIntVector(VoxelGridLocation.X / ContainerSetting.VoxelGridSize.X, VoxelGridLocation.Y / ContainerSetting.VoxelGridSize.Y, VoxelGridLocation.Z / ContainerSetting.VoxelGridSize.Z), ContainerSetting.ChuckGridSize);
	ReturnData.VoxelIndex = ULFPGridLibrary::ToIndex(FIntVector(VoxelGridLocation.X % ContainerSetting.VoxelGridSize.X, VoxelGridLocation.Y % ContainerSetting.VoxelGridSize.Y, VoxelGridLocation.Z % ContainerSetting.VoxelGridSize.Z), ContainerSetting.VoxelGridSize);

	return ReturnData;
}

FIntVector ULFPVoxelContainer::ToVoxelGridLocation(const FLFPVoxelGridIndex VoxelGridIndex) const
{
	if (IsVoxelIndexValid(VoxelGridIndex) == false) return FIntVector(-1);

	const FIntVector ChuckLocation = ULFPGridLibrary::ToGridLocation(VoxelGridIndex.ChuckIndex, ContainerSetting.ChuckGridSize);
	const FIntVector VoxelLocation = ULFPGridLibrary::ToGridLocation(VoxelGridIndex.VoxelIndex, ContainerSetting.VoxelGridSize);

	return VoxelLocation + FIntVector(ChuckLocation.X * ContainerSetting.VoxelGridSize.X, ChuckLocation.Y * ContainerSetting.VoxelGridSize.Y, ChuckLocation.Z * ContainerSetting.VoxelGridSize.Z);
}

bool ULFPVoxelContainer::GetVoxelGridAttribute(const FLFPVoxelGridIndex VoxelGridIndex, FLFPVoxelDynamicAttributeData& VoxelAttribute) const
{
	VoxelAttribute = GetVoxelDynamicAttribute(VoxelGridIndex);

	return (IsVoxelIndexValid(VoxelGridIndex) == false || IsChuckInitialized(VoxelGridIndex.ChuckIndex) == false);
}

bool ULFPVoxelContainer::GetVoxelGridName(const FLFPVoxelGridIndex VoxelGridIndex, FName& VoxelName) const
{
	VoxelName = GetVoxelName(VoxelGridIndex);

	return (IsVoxelIndexValid(VoxelGridIndex) == false || IsChuckInitialized(VoxelGridIndex.ChuckIndex) == false);
}

void ULFPVoxelContainer::SetVoxelGridAttribute(const FLFPVoxelGridIndex VoxelGridIndex, const FLFPVoxelDynamicAttributeData VoxelAttribute, const bool bInitializeChuck)
{
	FLFPVoxelWriteAction* Action = FindOrAddChuckWriteAction(VoxelGridIndex.ChuckIndex);

	if (Action == nullptr) return;

	Action->bWantUpdateAttribute = Action->bWantUpdateName || bInitializeChuck;

	Action->AttributeData.Add(VoxelGridIndex.VoxelIndex, VoxelAttribute);

	return;
}

void ULFPVoxelContainer::SetVoxelGridName(const FLFPVoxelGridIndex VoxelGridIndex, const FName VoxelName, const bool bInitializeChuck)
{
	FLFPVoxelWriteAction* Action = FindOrAddChuckWriteAction(VoxelGridIndex.ChuckIndex);

	if (Action == nullptr) return;

	Action->bWantUpdateName = Action->bWantUpdateName || bInitializeChuck;

	Action->NameData.Add(VoxelGridIndex.VoxelIndex, VoxelName);

	return;
}

void ULFPVoxelContainer::SetVoxelGridNameList(const TArray<FLFPVoxelGridIndex>& VoxelGridIndexList, const FName VoxelName, const bool bInitializeChuck)
{
	for (int32 ListIndex = 0; ListIndex < VoxelGridIndexList.Num(); ListIndex++)
	{
		SetVoxelGridName(VoxelGridIndexList[ListIndex], VoxelName, bInitializeChuck);
	}

	return;
}

void ULFPVoxelContainer::SetChuckGridName(const int32 ChuckIndex, const FName VoxelName, const bool bInitializeChuck)
{
	FLFPVoxelWriteAction* Action = FindOrAddChuckWriteAction(ChuckIndex);

	if (Action == nullptr) return;

	Action->NameData.Reserve(ContainerSetting.VoxelLength);

	for (int32 VoxelIndex = 0; VoxelIndex < ContainerSetting.VoxelLength; VoxelIndex++)
	{
		Action->NameData.Add(VoxelIndex, VoxelName);
	}

	Action->bWantUpdateName = Action->bWantUpdateName || bInitializeChuck;

	return;
}

void ULFPVoxelContainer::SetChuckGridNameWithHeight(const int32 ChuckIndex, const FIntPoint VoxelGridPosition, const float Height, const FName VoxelName, const bool bInitializeChuck)
{
	FLFPVoxelWriteAction* Action = FindOrAddChuckWriteAction(ChuckIndex);

	if (Action == nullptr) return;

	const int32 HeightIndex = ContainerSetting.VoxelGridSize.Z * Height;

	for (int32 VoxelHeightIndex = 0; VoxelHeightIndex < HeightIndex; VoxelHeightIndex++)
	{
		const int32 VoxelIndex = ULFPGridLibrary::ToIndex(FIntVector(VoxelGridPosition.X, VoxelGridPosition.Y, VoxelHeightIndex), ContainerSetting.VoxelGridSize);

		Action->NameData.Add(VoxelIndex, VoxelName);
	}

	Action->bWantUpdateName = Action->bWantUpdateName || bInitializeChuck;

	return;
}
