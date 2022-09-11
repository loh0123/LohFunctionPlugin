// MIT License
// 
// Copyright(c) 2022 loh0123
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright noticeand this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


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

		MarkChuckForUpdate(VoxelGridIndex.ChuckIndex);

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
