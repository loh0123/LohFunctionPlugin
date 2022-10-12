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

void ULFPVoxelContainer::BeginPlay()
{
	SetupVoxelData(VoxelAttributeTable, ContainerSetting);

	Super::BeginPlay();
}

void ULFPVoxelContainer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ChuckWriteActionList.IsEmpty())
	{
		UpdateChuckName();
		UpdateChuckColor();
	}
	else if (bIsThreadReading == false)
	{
		UpdateChuckWriteAction(1);
	}
}

int32 ULFPVoxelContainer::GetContainerSize()
{
	return GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
}

void ULFPVoxelContainer::UpdateChuckWriteAction(const int32 Amount)
{
	if (ChuckWriteActionList.IsEmpty()) return;

	FRWScopeLock WriteLock(GetContainerThreadLock(), SLT_Write);

	int32 Index = 0;

	TArray<int32> RemoveAction;

	RemoveAction.Reserve(Amount);

	for (const auto& ChuckWriteAction : ChuckWriteActionList)
	{
		if (Index >= Amount) break;

		RemoveAction.Add(ChuckWriteAction.Key);

		check(ChuckData.IsValidIndex(ChuckWriteAction.Key));

		if (ChuckData[ChuckWriteAction.Key].IsInitialized() == false)
		{
			ChuckData[ChuckWriteAction.Key].InitChuckData(ContainerSetting.VoxelLength, ContainerSetting.InvisibleName);
		}

		for (const auto& VoxelName : ChuckWriteAction.Value.NameData)
		{
			ChuckData[ChuckWriteAction.Key].SetVoxelName(VoxelName.Key, VoxelName.Value);

			const FIntVector VoxelLocation = ULFPGridLibrary::IndexToGridLocation(VoxelName.Key, ContainerSetting.VoxelGridSize);

			MarkChuckForUpdate(ChuckWriteAction.Key, ULFPGridLibrary::IsOnGridEdge(VoxelLocation, ContainerSetting.VoxelGridSize));
		}

		for (const auto& VoxelColor : ChuckWriteAction.Value.ColorData)
		{
			ChuckData[ChuckWriteAction.Key].SetVoxelColor(VoxelColor.Key, VoxelColor.Value);

			const FIntVector VoxelLocation = ULFPGridLibrary::IndexToGridLocation(VoxelColor.Key, ContainerSetting.VoxelGridSize);

			MarkChuckForColorUpdate(ChuckWriteAction.Key, ULFPGridLibrary::IsOnGridEdge(VoxelLocation, ContainerSetting.VoxelGridSize));
		}
	}

	for (const int32 IndexToRemove : RemoveAction)
	{
		ChuckWriteActionList.Remove(IndexToRemove);
	}

	ChuckWriteActionList.Shrink();

	return;
}

void ULFPVoxelContainer::UpdateChuckName()
{
	if (BatchChuckUpdateList.IsEmpty()) return;

	for (const int32 ChuckIndex : BatchChuckUpdateList)
	{
		ChuckData[ChuckIndex].SendNameUpdateEvent();
	}

	BatchChuckUpdateList.Empty();

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

void ULFPVoxelContainer::MarkChuckForUpdate(const int32 ChuckIndex, const bool bUpdateNearbyChuck)
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

		const FIntVector ChuckLocation = ULFPGridLibrary::IndexToGridLocation(ChuckIndex, ContainerSetting.ChuckGridSize);

		for (const FIntVector& Direction : UpdateDirection)
		{
			if (ULFPGridLibrary::IsLocationValid(ChuckLocation + Direction, ContainerSetting.ChuckGridSize))
			{
				BatchChuckUpdateList.Add(ULFPGridLibrary::GridLocationToIndex(ChuckLocation + Direction, ContainerSetting.ChuckGridSize));
			}
		}
	}

	BatchChuckUpdateList.Add(ChuckIndex);

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

		const FIntVector ChuckLocation = ULFPGridLibrary::IndexToGridLocation(ChuckIndex, ContainerSetting.ChuckGridSize);

		for (const FIntVector& Direction : UpdateDirection)
		{
			if (ULFPGridLibrary::IsLocationValid(ChuckLocation + Direction, ContainerSetting.ChuckGridSize))
			{
				BatchChuckColorUpdateList.Add(ULFPGridLibrary::GridLocationToIndex(ChuckLocation + Direction, ContainerSetting.ChuckGridSize));
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

FLFPVoxelGridIndex ULFPVoxelContainer::VoxelGridLocationToVoxelGridIndex(const FIntVector VoxelGridLocation) const
{
	FLFPVoxelGridIndex ReturnData;

	if (VoxelGridLocation.GetMin() < 0) return ReturnData;

	ReturnData.ChuckIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X / ContainerSetting.VoxelGridSize.X, VoxelGridLocation.Y / ContainerSetting.VoxelGridSize.Y, VoxelGridLocation.Z / ContainerSetting.VoxelGridSize.Z), ContainerSetting.ChuckGridSize);
	ReturnData.VoxelIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X % ContainerSetting.VoxelGridSize.X, VoxelGridLocation.Y % ContainerSetting.VoxelGridSize.Y, VoxelGridLocation.Z % ContainerSetting.VoxelGridSize.Z), ContainerSetting.VoxelGridSize);

	return ReturnData;
}

FIntVector ULFPVoxelContainer::VoxelGridIndexToVoxelGridLocation(const FLFPVoxelGridIndex VoxelGridIndex) const
{
	if (IsVoxelIndexValid(VoxelGridIndex) == false) return FIntVector(-1);

	const FIntVector ChuckLocation = ULFPGridLibrary::IndexToGridLocation(VoxelGridIndex.ChuckIndex, ContainerSetting.ChuckGridSize);
	const FIntVector VoxelLocation = ULFPGridLibrary::IndexToGridLocation(VoxelGridIndex.VoxelIndex, ContainerSetting.VoxelGridSize);

	return VoxelLocation + FIntVector(ChuckLocation.X * ContainerSetting.VoxelGridSize.X, ChuckLocation.Y * ContainerSetting.VoxelGridSize.Y, ChuckLocation.Z * ContainerSetting.VoxelGridSize.Z);
}

void ULFPVoxelContainer::SetVoxelGridColor(const FLFPVoxelGridIndex VoxelGridIndex, const FColor VoxelColor, const bool bInitializeChuck)
{
	FLFPVoxelWriteAction* Action = ChuckWriteActionList.Find(VoxelGridIndex.ChuckIndex);

	if (Action == nullptr)
	{
		FLFPVoxelWriteAction NewAction;

		NewAction.bWantUpdateColor = bInitializeChuck;

		NewAction.ColorData.Add(VoxelGridIndex.VoxelIndex, VoxelColor);

		ChuckWriteActionList.Add(VoxelGridIndex.ChuckIndex, NewAction);
	}
	else
	{
		Action->bWantUpdateColor = Action->bWantUpdateName || bInitializeChuck;

		Action->ColorData.Add(VoxelGridIndex.VoxelIndex, VoxelColor);
	}

	return;
}

void ULFPVoxelContainer::SetVoxelGridName(const FLFPVoxelGridIndex VoxelGridIndex, const FName VoxelAttributeName, const bool bInitializeChuck)
{
	FLFPVoxelWriteAction* Action = ChuckWriteActionList.Find(VoxelGridIndex.ChuckIndex);

	if (Action == nullptr)
	{
		FLFPVoxelWriteAction NewAction;

		NewAction.bWantUpdateName = bInitializeChuck;

		NewAction.NameData.Add(VoxelGridIndex.VoxelIndex, VoxelAttributeName);

		ChuckWriteActionList.Add(VoxelGridIndex.ChuckIndex, NewAction);
	}
	else
	{
		Action->bWantUpdateName = Action->bWantUpdateName || bInitializeChuck;

		Action->NameData.Add(VoxelGridIndex.VoxelIndex, VoxelAttributeName);
	}

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

void ULFPVoxelContainer::SetVoxelGridNameWithArea(const FLFPVoxelGridIndex FromVoxelGridIndex, const FLFPVoxelGridIndex ToVoxelGridIndex, const FName VoxelAttributeName, const bool bInitializeChuck)
{
	if (IsVoxelIndexValid(FromVoxelGridIndex) == false || IsVoxelIndexValid(ToVoxelGridIndex) == false) return;

	const FIntVector FromLocation = VoxelGridIndexToVoxelGridLocation(FromVoxelGridIndex);
	const FIntVector ToLocation = VoxelGridIndexToVoxelGridLocation(ToVoxelGridIndex);

	for (int32 Z = FromLocation.Z; Z <= ToLocation.Z; Z++)
	{
		for (int32 Y = FromLocation.Y; Y <= ToLocation.Y; Y++)
		{
			for (int32 X = FromLocation.X; X <= ToLocation.X; X++)
			{
				SetVoxelGridName(VoxelGridLocationToVoxelGridIndex(FIntVector(X, Y, Z)), VoxelAttributeName, bInitializeChuck);
			}
		}
	}

	return;
}

void ULFPVoxelContainer::SetChuckGridName(const int32 ChuckIndex, const FName VoxelAttributeName, const bool bInitializeChuck)
{
	const int32 ChuckGridMaxIndex = ContainerSetting.ChuckGridSize.X * ContainerSetting.ChuckGridSize.Y * ContainerSetting.ChuckGridSize.Z;

	FLFPVoxelWriteAction* Action = ChuckWriteActionList.Find(ChuckIndex);

	if (Action == nullptr) Action = &ChuckWriteActionList.Add(ChuckIndex, FLFPVoxelWriteAction());

	for (int32 VoxelIndex = 0; VoxelIndex < ChuckGridMaxIndex; VoxelIndex++)
	{
		Action->NameData.Add(VoxelIndex, VoxelAttributeName);
	}

	Action->bWantUpdateName = Action->bWantUpdateName || bInitializeChuck;

	return;
}

void ULFPVoxelContainer::SetChuckGridNameWithHeight(const int32 ChuckIndex, const FIntPoint VoxelGridPosition, const float Height, const FName VoxelAttributeName, const bool bInitializeChuck)
{
	const int32 HeightIndex = ContainerSetting.VoxelGridSize.Z * Height;

	FLFPVoxelWriteAction* Action = ChuckWriteActionList.Find(ChuckIndex);

	if (Action == nullptr) Action = &ChuckWriteActionList.Add(ChuckIndex, FLFPVoxelWriteAction());

	for (int32 VoxelHeightIndex = 0; VoxelHeightIndex < HeightIndex; VoxelHeightIndex++)
	{
		const int32 VoxelIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridPosition.X, VoxelGridPosition.Y, VoxelHeightIndex), ContainerSetting.VoxelGridSize);

		Action->NameData.Add(VoxelIndex, VoxelAttributeName);
	}

	Action->bWantUpdateName = Action->bWantUpdateName || bInitializeChuck;

	return;
}
