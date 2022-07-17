// Copyright by Loh Zhi Kang


#include "Voxel/LFPVoxelContainer.h"

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

void ULFPVoxelContainer::MarkChuckForUpdate(const int32 ChuckIndex)
{
	BatchChuckUpdateList.Add(ChuckIndex);

	return;
}

void ULFPVoxelContainer::SetupVoxelData(UDataTable* NewVoxelAttributeTable, const FLFPVoxelContainerSettingV2 NewSetting)
{
	if (NewVoxelAttributeTable == nullptr || NewVoxelAttributeTable->GetRowStruct()->IsChildOf(FLFPVoxelAttributeV2::StaticStruct()) == false) return;

	ContainerSetting = NewSetting;

	ContainerSetting.InitSetting();

	VoxelAttributeTable = NewVoxelAttributeTable;

	return;
}

void ULFPVoxelContainer::GetChuckAttribute(const int32 ChuckIndex, FIntVector& StartVoxelLocation, FVector& ChuckMeshSize, FIntVector& ChuckVoxelGridSize)
{
	if (!ChuckData.IsValidIndex(ChuckIndex)) return;

	const FIntVector ChuckGridLocation = ULFPGridLibrary::IndexToGridLocation(ChuckIndex, ContainerSetting.PoolGridSize);
	StartVoxelLocation = FIntVector(ChuckGridLocation.X * ContainerSetting.ChuckGridSize.X, ChuckGridLocation.Y * ContainerSetting.ChuckGridSize.Y, ChuckGridLocation.Z * ContainerSetting.ChuckGridSize.Z);

	ChuckMeshSize = ContainerSetting.MeshSize;
	ChuckVoxelGridSize = ContainerSetting.ChuckGridSize;

	return;
}

bool ULFPVoxelContainer::IsChuckInitialized(const int32 ChuckIndex) const
{
	if (!ChuckData.IsValidIndex(ChuckIndex)) return false;

	return ChuckData[ChuckIndex].IsInitialized();
}

void ULFPVoxelContainer::SetVoxelGridData(const FIntVector VoxelGridLocation, const FName& VoxelAttributeName, const bool bUpdateMesh)
{
	int32 ChuckIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X / ContainerSetting.ChuckGridSize.X, VoxelGridLocation.Y / ContainerSetting.ChuckGridSize.Y, VoxelGridLocation.Z / ContainerSetting.ChuckGridSize.Z), ContainerSetting.PoolGridSize);
	int32 VoxelChuckIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X % ContainerSetting.ChuckGridSize.X, VoxelGridLocation.Y % ContainerSetting.ChuckGridSize.Y, VoxelGridLocation.Z % ContainerSetting.ChuckGridSize.Z), ContainerSetting.ChuckGridSize);

	if (ChuckData.IsValidIndex(ChuckIndex))
	{
		if (ChuckData[ChuckIndex].IsInitialized() == false)
		{
			ChuckData[ChuckIndex].InitChuckData(ContainerSetting.ChuckVoxelLength);
		}

		if (ChuckData[ChuckIndex].VoxelData.IsValidIndex(VoxelChuckIndex))
		{
			ChuckData[ChuckIndex].SetVoxel(VoxelChuckIndex, VoxelAttributeName);
		}

		if (bUpdateMesh)
		{
			UpdateChuck();
		}
	}

	return;
}

void ULFPVoxelContainer::SetVoxelGridDataList(const TArray<FIntVector>& VoxelGridLocationList, const FName& VoxelAttributeName, const bool bUpdateMesh)
{
	for (int32 ListIndex = 0; ListIndex < VoxelGridLocationList.Num(); ListIndex++)
	{
		SetVoxelGridData(VoxelGridLocationList[ListIndex], VoxelAttributeName, false);
	}

	if (bUpdateMesh)
	{
		UpdateChuck();
	}

	return;
}

void ULFPVoxelContainer::SetAllVoxelGridDataWithSingleData(const int32 ChuckIndex, const FName& VoxelAttributeName, const bool bUpdateMesh)
{
	const int32 ChuckGridMaxIndex = ContainerSetting.ChuckGridSize.X * ContainerSetting.ChuckGridSize.Y * ContainerSetting.ChuckGridSize.Z;

	if (ChuckData.IsValidIndex(ChuckIndex))
	{
		if (ChuckData[ChuckIndex].IsInitialized() == false)
		{
			ChuckData[ChuckIndex].InitChuckData(ContainerSetting.ChuckVoxelLength);
		}

		for (int32 VoxelChuckIndex = 0; VoxelChuckIndex < ChuckGridMaxIndex; VoxelChuckIndex++)
		{
			ChuckData[ChuckIndex].SetVoxel(VoxelChuckIndex, VoxelAttributeName);
		}

		if (bUpdateMesh)
		{
			UpdateChuck();
		}
	}

	return;
}
