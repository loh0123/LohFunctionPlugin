// Copyright (c) 2022 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)



#include "Voxel/LFPVoxelContainer.h"
#include "./Math/LFPGridLibrary.h"
#include "Net/UnrealNetwork.h"

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

FLFPVoxelWriteAction* ULFPVoxelContainer::FindOrAddChuckWriteAction(const int32& ChuckIndex, const bool bResetDelay)
{
	if (IsChuckIndexValid(ChuckIndex) == false) return nullptr;

	FLFPVoxelWriteAction* Action = ChuckWriteActionList.Find(ChuckIndex);

	if (Action == nullptr) Action = &ChuckWriteActionList.Add(ChuckIndex, FLFPVoxelWriteAction());

	if (bResetDelay) Action->TickDelayCount = ContainerSetting.WriteActionTickDelay;

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
		UpdateChuckWriteAction();
	}

	UpdateChuckName();
	UpdateChuckColor();
}

int32 ULFPVoxelContainer::GetContainerSize()
{
	return GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
}

void ULFPVoxelContainer::UpdateChuckWriteAction()
{
	if (ChuckWriteActionList.IsEmpty()) return;

	FRWScopeLock WriteLock(GetContainerThreadLock(), SLT_Write);

	auto ChuckWriteAction = ChuckWriteActionList.CreateIterator();

	if (ChuckWriteAction)
	{
		if (ChuckWriteAction.Value().TickDelayCount > 0)
		{
			ChuckWriteAction.Value().TickDelayCount -= 1;
		}
		else
		{
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

				if (OldName == ContainerSetting.InvisibleName || VoxelName.Value == ContainerSetting.InvisibleName)
				{
					MarkChuckForNameUpdate(ChuckWriteAction.Key(), ULFPGridLibrary::IsOnGridEdge(VoxelLocation, ContainerSetting.VoxelGridSize));
				}
				else
				{
					MarkChuckForColorUpdate(ChuckWriteAction.Key(), ULFPGridLibrary::IsOnGridEdge(VoxelLocation, ContainerSetting.VoxelGridSize));
				}
			}

			for (const auto& VoxelColor : ChuckWriteAction.Value().ColorData)
			{
				ChuckData[ChuckWriteAction.Key()].SetVoxelColor(VoxelColor.Key, VoxelColor.Value);

				const FIntVector VoxelLocation = ULFPGridLibrary::ToGridLocation(VoxelColor.Key, ContainerSetting.VoxelGridSize);

				MarkChuckForColorUpdate(ChuckWriteAction.Key(), ULFPGridLibrary::IsOnGridEdge(VoxelLocation, ContainerSetting.VoxelGridSize));
			}

			ChuckWriteActionList.Remove(ChuckWriteAction.Key());
		}
	}

	ChuckWriteActionList.Shrink();

	return;
}

void ULFPVoxelContainer::UpdateChuckName()
{
	if (BatchChuckNameUpdateList.IsEmpty()) return;

	for (const int32 ChuckIndex : BatchChuckNameUpdateList)
	{
		ChuckData[ChuckIndex].SendNameUpdateEvent();
	}

	BatchChuckNameUpdateList.Empty();

	return;
}

void ULFPVoxelContainer::UpdateChuckColor()
{
	if (BatchChuckColorUpdateList.IsEmpty()) return;

	for (const int32 ChuckIndex : BatchChuckColorUpdateList)
	{
		ChuckData[ChuckIndex].SendColorUpdateEvent();
	}

	BatchChuckColorUpdateList.Empty();

	return;
}

void ULFPVoxelContainer::MarkChuckForNameUpdate(const int32 ChuckIndex, const bool bUpdateNearbyChuck)
{
	MarkChuckForColorUpdate(ChuckIndex, bUpdateNearbyChuck);

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
			if (ULFPGridLibrary::IsLocationValid(ChuckLocation + Direction, ContainerSetting.ChuckGridSize))
			{
				BatchChuckNameUpdateList.Add(ULFPGridLibrary::ToIndex(ChuckLocation + Direction, ContainerSetting.ChuckGridSize));
			}
		}
	}

	BatchChuckNameUpdateList.Add(ChuckIndex);

	return;
}

void ULFPVoxelContainer::MarkChuckForColorUpdate(const int32 ChuckIndex, const bool bUpdateNearbyChuck)
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
			if (ULFPGridLibrary::IsLocationValid(ChuckLocation + Direction, ContainerSetting.ChuckGridSize))
			{
				BatchChuckColorUpdateList.Add(ULFPGridLibrary::ToIndex(ChuckLocation + Direction, ContainerSetting.ChuckGridSize));
			}
		}
	}

	BatchChuckColorUpdateList.Add(ChuckIndex);

	return;
}

bool ULFPVoxelContainer::SetupVoxelData(UDataTable* NewVoxelAttributeTable, const FLFPVoxelContainerSettingV2 NewSetting)
{
	FRWScopeLock WriteLock(GetContainerThreadLock(), SLT_Write);

	if (NewVoxelAttributeTable == nullptr || NewVoxelAttributeTable->GetRowStruct()->IsChildOf(FLFPVoxelAttributeV2::StaticStruct()) == false)
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

void ULFPVoxelContainer::SetVoxelGridColor(const FLFPVoxelGridIndex VoxelGridIndex, const FColor VoxelColor, const bool bInitializeChuck)
{
	FLFPVoxelWriteAction* Action = FindOrAddChuckWriteAction(VoxelGridIndex.ChuckIndex);

	if (Action == nullptr) return;

	Action->bWantUpdateColor = Action->bWantUpdateName || bInitializeChuck;

	Action->ColorData.Add(VoxelGridIndex.VoxelIndex, VoxelColor);

	return;
}

void ULFPVoxelContainer::SetVoxelGridName(const FLFPVoxelGridIndex VoxelGridIndex, const FName VoxelAttributeName, const bool bInitializeChuck)
{
	FLFPVoxelWriteAction* Action = FindOrAddChuckWriteAction(VoxelGridIndex.ChuckIndex);

	if (Action == nullptr) return;

	Action->bWantUpdateName = Action->bWantUpdateName || bInitializeChuck;

	Action->NameData.Add(VoxelGridIndex.VoxelIndex, VoxelAttributeName);

	return;
}

void ULFPVoxelContainer::SetVoxelGridNameList(const TArray<FLFPVoxelGridIndex>& VoxelGridIndexList, const FName VoxelAttributeName, const bool bInitializeChuck)
{
	for (int32 ListIndex = 0; ListIndex < VoxelGridIndexList.Num(); ListIndex++)
	{
		SetVoxelGridName(VoxelGridIndexList[ListIndex], VoxelAttributeName, bInitializeChuck);
	}

	return;
}

void ULFPVoxelContainer::SetChuckGridName(const int32 ChuckIndex, const FName VoxelAttributeName, const bool bInitializeChuck)
{
	FLFPVoxelWriteAction* Action = FindOrAddChuckWriteAction(ChuckIndex);

	if (Action == nullptr) return;

	Action->NameData.Reserve(ContainerSetting.VoxelLength);

	for (int32 VoxelIndex = 0; VoxelIndex < ContainerSetting.VoxelLength; VoxelIndex++)
	{
		Action->NameData.Add(VoxelIndex, VoxelAttributeName);
	}

	Action->bWantUpdateName = Action->bWantUpdateName || bInitializeChuck;

	return;
}

void ULFPVoxelContainer::SetChuckGridNameWithHeight(const int32 ChuckIndex, const FIntPoint VoxelGridPosition, const float Height, const FName VoxelAttributeName, const bool bInitializeChuck)
{
	FLFPVoxelWriteAction* Action = FindOrAddChuckWriteAction(ChuckIndex);

	if (Action == nullptr) return;

	const int32 HeightIndex = ContainerSetting.VoxelGridSize.Z * Height;

	for (int32 VoxelHeightIndex = 0; VoxelHeightIndex < HeightIndex; VoxelHeightIndex++)
	{
		const int32 VoxelIndex = ULFPGridLibrary::ToIndex(FIntVector(VoxelGridPosition.X, VoxelGridPosition.Y, VoxelHeightIndex), ContainerSetting.VoxelGridSize);

		Action->NameData.Add(VoxelIndex, VoxelAttributeName);
	}

	Action->bWantUpdateName = Action->bWantUpdateName || bInitializeChuck;

	return;
}
