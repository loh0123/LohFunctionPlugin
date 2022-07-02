// Copyright by Loh Zhi Kang


#include "Container/LFPVoxelData.h"
#include "Math/LFPGridLibrary.h"

const FLFPVoxelAttribute& ULFPVoxelData::GetVoxelData(const FIntVector VoxelGridLocation) const
{
	int32 ChuckIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X / ContainerSetting.ChuckGridSize.X, VoxelGridLocation.Y / ContainerSetting.ChuckGridSize.Y, VoxelGridLocation.Z / ContainerSetting.ChuckGridSize.Z), ContainerSetting.PoolGridSize);
	int32 VoxelIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X % ContainerSetting.ChuckGridSize.X, VoxelGridLocation.Y % ContainerSetting.ChuckGridSize.Y, VoxelGridLocation.Z % ContainerSetting.ChuckGridSize.Z), ContainerSetting.ChuckGridSize);

	if (ChuckData.IsValidIndex(ChuckIndex) && ChuckData[ChuckIndex].VoxelData.IsValidIndex(VoxelIndex))
	{
		return ChuckData[ChuckIndex].VoxelData[VoxelIndex];
	}

	return DefaultVoxelAttribute;
}

const TArray<FLFPVoxelAttribute>& ULFPVoxelData::GetVoxelData(const int32 ChuckIndex)
{
	checkf(ChuckData.IsValidIndex(ChuckIndex), TEXT("Error : Out Of Chuck List Range"));
	
	if (InitializedList[ChuckIndex] == false)
	{
		InitializeChuck(ChuckIndex);
	}

	return ChuckData[ChuckIndex].VoxelData;
}


bool ULFPVoxelData::GetVoxelVisible(const FIntVector VoxelGridLocation) const
{
	int32 ChuckIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X / ContainerSetting.ChuckGridSize.X, VoxelGridLocation.Y / ContainerSetting.ChuckGridSize.Y, VoxelGridLocation.Z / ContainerSetting.ChuckGridSize.Z), ContainerSetting.PoolGridSize);
	int32 VoxelIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X % ContainerSetting.ChuckGridSize.X, VoxelGridLocation.Y % ContainerSetting.ChuckGridSize.Y, VoxelGridLocation.Z % ContainerSetting.ChuckGridSize.Z), ContainerSetting.ChuckGridSize);

	if (ChuckData.IsValidIndex(ChuckIndex) && ChuckData[ChuckIndex].VoxelVisibleMap.IsValidIndex(VoxelIndex))
	{
		return ChuckData[ChuckIndex].VoxelVisibleMap[VoxelIndex];
	}

	return false;
}

const TBitArray<>& ULFPVoxelData::GetVoxelVisible(const int32 ChuckIndex)
{
	if (InitializedList[ChuckIndex] == false)
	{
		InitializeChuck(ChuckIndex);
	}

	return ChuckData[ChuckIndex].VoxelVisibleMap;
}

void ULFPVoxelData::InitializeChuck(const int32 ChuckIndex)
{
	checkf(ChuckData.IsValidIndex(ChuckIndex), TEXT("Error : Out Of Chuck List Range"));

	ChuckData[ChuckIndex].VoxelData.Init(FLFPVoxelAttribute(), ContainerSetting.ChuckVoxelLength);

	ChuckData[ChuckIndex].VoxelVisibleMap = TBitArray(false, ContainerSetting.ChuckVoxelLength);

	InitializedList[ChuckIndex] = true;

	return;
}

int32 ULFPVoxelData::GetContainerSize()
{
	return GetResourceSizeBytes(EResourceSizeMode::EstimatedTotal);
}

void ULFPVoxelData::UpdateChuck(const int32 UpdateCount)
{
	//const TArray<int32> UpdateArray = UpdateChuckList.Array();

	if (UpdateCount <= 0)
	{
		return;
	}

	int32 Count = 0;

	TArray<int32> RemoveArray;

	RemoveArray.Reserve(UpdateCount);

	for (auto ChuckIndex = UpdateChuckList.CreateIterator(); ChuckIndex && Count < UpdateCount; ++ChuckIndex)
	{
		RemoveArray.Add(*ChuckIndex);

		if (ChuckData.IsValidIndex(*ChuckIndex))
		{
			ChuckData[*ChuckIndex].VoxelUpdateEvent.ExecuteIfBound();
		}

		Count++;
	}

	for (const int32 ChuckIndex : RemoveArray)
	{
		UpdateChuckList.Remove(ChuckIndex);
	}

	//for (int32 CountIndex = 0; CountIndex < FMath::Min(UpdateCount, UpdateArray.Num()); CountIndex++)
	//{
	//	UpdateChuckList.Remove(UpdateArray[CountIndex]);
	//
	//	if (ChuckData.IsValidIndex(UpdateArray[CountIndex]))
	//	{
	//		ChuckData[UpdateArray[CountIndex]].VoxelUpdateEvent.ExecuteIfBound();
	//	}
	//}

	return;
}

void ULFPVoxelData::MarkChuckForUpdate(const int32 ChuckIndex)
{
	UpdateChuckList.Add(ChuckIndex);

	return;
}

void ULFPVoxelData::SetupVoxelData(const FVector NewMeshSize, const FIntVector NewPoolGridSize, const FIntVector NewChuckGridSize, const int32 NewMaxMaterialID, const int32 NewSectionSize)
{
	ContainerSetting.SetValue(NewMeshSize, NewPoolGridSize, NewChuckGridSize);

	ContainerSetting.UpdateCache(NewMaxMaterialID, NewSectionSize);

	ChuckData.Init(FLFPVoxelChuckData(), ContainerSetting.PoolLength);

	InitializedList = TBitArray(false, ContainerSetting.PoolLength);

	return;
}

void ULFPVoxelData::GetPoolAttribute(const int32 ChuckIndex, FIntVector& StartVoxelLocation, FVector& ChuckMeshSize, FIntVector& ChuckVoxelGridSize)
{
	if (!ChuckData.IsValidIndex(ChuckIndex)) return;

	const FIntVector ChuckGridLocation = ULFPGridLibrary::IndexToGridLocation(ChuckIndex, ContainerSetting.PoolGridSize);
	StartVoxelLocation = FIntVector(ChuckGridLocation.X * ContainerSetting.ChuckGridSize.X, ChuckGridLocation.Y * ContainerSetting.ChuckGridSize.Y, ChuckGridLocation.Z * ContainerSetting.ChuckGridSize.Z);

	ChuckMeshSize = ContainerSetting.MeshSize;
	ChuckVoxelGridSize = ContainerSetting.ChuckGridSize;

	return;
}

bool ULFPVoxelData::IsChuckInitialized(const int32 ChuckIndex) const
{
	if (!ChuckData.IsValidIndex(ChuckIndex)) return false;

	return InitializedList[ChuckIndex];
}

void ULFPVoxelData::SetVoxelGridData(const FIntVector VoxelGridLocation, const FLFPVoxelAttribute& VoxelAttribute, const bool IsVisible, const bool bUpdateMesh)
{
	int32 ChuckIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X / ContainerSetting.ChuckGridSize.X, VoxelGridLocation.Y / ContainerSetting.ChuckGridSize.Y, VoxelGridLocation.Z / ContainerSetting.ChuckGridSize.Z), ContainerSetting.PoolGridSize);
	int32 VoxelChuckIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X % ContainerSetting.ChuckGridSize.X, VoxelGridLocation.Y % ContainerSetting.ChuckGridSize.Y, VoxelGridLocation.Z % ContainerSetting.ChuckGridSize.Z), ContainerSetting.ChuckGridSize);

	if (ChuckData.IsValidIndex(ChuckIndex))
	{
		if (InitializedList[ChuckIndex] == false)
		{
			InitializeChuck(ChuckIndex);
		}

		if (ChuckData[ChuckIndex].VoxelData.IsValidIndex(VoxelChuckIndex))
		{
			ChuckData[ChuckIndex].VoxelData[VoxelChuckIndex] = VoxelAttribute;

			ChuckData[ChuckIndex].VoxelVisibleMap[VoxelChuckIndex] = IsVisible;

			ChuckData[ChuckIndex].VoxelData[VoxelChuckIndex].CorrectMaterialID(ContainerSetting.MaxMaterialID);

			ChuckData[ChuckIndex].VoxelDataUpdateEvent.ExecuteIfBound(VoxelChuckIndex, true);
		}

		if (bUpdateMesh)
		{
			UpdateChuck();
		}
	}

	return;
}

void ULFPVoxelData::SetVoxelGridDataList(const TArray<FIntVector>& VoxelGridLocationList, const FLFPVoxelAttribute& VoxelAttribute, const bool IsVisible, const bool bUpdateMesh)
{
	for (int32 ListIndex = 0; ListIndex < VoxelGridLocationList.Num(); ListIndex++)
	{
		SetVoxelGridData(VoxelGridLocationList[ListIndex], VoxelAttribute, IsVisible, false);
	}

	if (bUpdateMesh)
	{
		UpdateChuck();
	}

	return;
}

void ULFPVoxelData::SetAllVoxelGridDataWithSingleData(const int32 ChuckIndex, const FLFPVoxelAttribute& VoxelAttribute, const bool IsVisible, const bool bUpdateMesh)
{
	const int32 ChuckGridMaxIndex = ContainerSetting.ChuckGridSize.X * ContainerSetting.ChuckGridSize.Y * ContainerSetting.ChuckGridSize.Z;

	if (ChuckData.IsValidIndex(ChuckIndex))
	{
		if (InitializedList[ChuckIndex] == false)
		{
			InitializeChuck(ChuckIndex);
		}

		for (int32 VoxelChuckIndex = 0; VoxelChuckIndex < ChuckGridMaxIndex; VoxelChuckIndex++)
		{
			ChuckData[ChuckIndex].VoxelData[VoxelChuckIndex] = VoxelAttribute;

			ChuckData[ChuckIndex].VoxelVisibleMap[VoxelChuckIndex] = IsVisible;

			ChuckData[ChuckIndex].VoxelData[VoxelChuckIndex].CorrectMaterialID(ContainerSetting.MaxMaterialID);

			ChuckData[ChuckIndex].VoxelDataUpdateEvent.ExecuteIfBound(VoxelChuckIndex, ULFPGridLibrary::IsOnGridEdge(ULFPGridLibrary::IndexToGridLocation(VoxelChuckIndex, ContainerSetting.ChuckGridSize), ContainerSetting.ChuckGridSize));

		}

		if (bUpdateMesh)
		{
			UpdateChuck();
		}
	}

	return;
}
