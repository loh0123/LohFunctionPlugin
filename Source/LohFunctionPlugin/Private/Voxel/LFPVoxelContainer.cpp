// Copyright (c) 2022 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)



#include "Voxel/LFPVoxelContainer.h"
#include "./Math/LFPGridLibrary.h"

int32 ULFPVoxelContainer::GetContainerSize()
{
	return GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
}

void ULFPVoxelContainer::UpdateChuck()
{
	if (BatchChuckUpdateList.Num() == 0) return;

	for (const int32 ChuckIndex : BatchChuckUpdateList)
	{
		ChuckData[ChuckIndex].SendUpdateEvent();
	}

	BatchChuckUpdateList.Empty();

	return;
}

void ULFPVoxelContainer::MarkChuckForUpdate(const int32 ChuckIndex, const bool bUpdateNearbyChuck)
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
				BatchChuckUpdateList.Add(ULFPGridLibrary::GridLocationToIndex(ChuckLocation + Direction, ContainerSetting.ChuckGridSize));
			}
		}
	}

	BatchChuckUpdateList.Add(ChuckIndex);

	return;
}

bool ULFPVoxelContainer::SetupVoxelData(UDataTable* NewVoxelAttributeTable, const FLFPVoxelContainerSettingV2 NewSetting)
{
	FRWScopeLock WriteLock(GetContainerThreadLock(), SLT_Write);

	if (NewVoxelAttributeTable == nullptr || NewVoxelAttributeTable->GetRowStruct()->IsChildOf(FLFPVoxelAttributeV2::StaticStruct()) == false) return false;

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

void ULFPVoxelContainer::SetVoxelGridData(const FLFPVoxelGridIndex VoxelGridIndex, const FName VoxelAttributeName, const bool bUpdateMesh, const bool bInitializeChuck)
{
	FRWScopeLock WriteLock(GetContainerThreadLock(), SLT_Write);

	if (IsVoxelIndexValid(VoxelGridIndex))
	{
		if (ChuckData[VoxelGridIndex.ChuckIndex].IsInitialized() == false)
		{
			if (bInitializeChuck == false) return;

			ChuckData[VoxelGridIndex.ChuckIndex].InitChuckData(ContainerSetting.VoxelLength, FName("None"));
		}

		if (ChuckData[VoxelGridIndex.ChuckIndex].VoxelData.IsValidIndex(VoxelGridIndex.VoxelIndex))
		{
			ChuckData[VoxelGridIndex.ChuckIndex].SetVoxel(VoxelGridIndex.VoxelIndex, VoxelAttributeName);
		}

		const FIntVector VoxelLocation = ULFPGridLibrary::IndexToGridLocation(VoxelGridIndex.VoxelIndex, ContainerSetting.VoxelGridSize);

		MarkChuckForUpdate(VoxelGridIndex.ChuckIndex, ULFPGridLibrary::IsOnGridEdge(VoxelLocation, ContainerSetting.VoxelGridSize));

		if (bUpdateMesh)
		{
			UpdateChuck();
		}
	}

	return;
}

void ULFPVoxelContainer::SetVoxelGridDataList(const TArray<FLFPVoxelGridIndex>& VoxelGridIndexList, const FName VoxelAttributeName, const bool bUpdateMesh, const bool bInitializeChuck)
{
	FRWScopeLock WriteLock(GetContainerThreadLock(), SLT_Write);

	for (int32 ListIndex = 0; ListIndex < VoxelGridIndexList.Num(); ListIndex++)
	{
		SetVoxelGridData(VoxelGridIndexList[ListIndex], VoxelAttributeName, false, bInitializeChuck);
	}

	if (bUpdateMesh)
	{
		UpdateChuck();
	}

	return;
}

void ULFPVoxelContainer::SetChuckGridData(const int32 ChuckIndex, const FName VoxelAttributeName, const bool bUpdateMesh, const bool bInitializeChuck)
{
	FRWScopeLock WriteLock(GetContainerThreadLock(), SLT_Write);

	const int32 ChuckGridMaxIndex = ContainerSetting.ChuckGridSize.X * ContainerSetting.ChuckGridSize.Y * ContainerSetting.ChuckGridSize.Z;

	if (ChuckData.IsValidIndex(ChuckIndex))
	{
		if (ChuckData[ChuckIndex].IsInitialized() == false)
		{
			if (bInitializeChuck == false) return;

			ChuckData[ChuckIndex].InitChuckData(ContainerSetting.VoxelLength, VoxelAttributeName);
		}
		else
		{
			for (int32 VoxelChuckIndex = 0; VoxelChuckIndex < ChuckGridMaxIndex; VoxelChuckIndex++)
			{
				ChuckData[ChuckIndex].SetVoxel(VoxelChuckIndex, VoxelAttributeName);
			}
		}

		MarkChuckForUpdate(ChuckIndex);

		if (bUpdateMesh)
		{
			UpdateChuck();
		}
	}

	return;
}
