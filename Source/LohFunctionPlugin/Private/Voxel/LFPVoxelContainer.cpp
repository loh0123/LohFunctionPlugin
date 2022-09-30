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

	UpdateChuck();
	UpdateChuckColor();
}

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

void ULFPVoxelContainer::UpdateChuckColor()
{
	if (BatchChuckColorUpdateList.Num() == 0) return;

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
	FRWScopeLock WriteLock(GetContainerThreadLock(), SLT_Write);

	if (IsVoxelIndexValid(VoxelGridIndex))
	{
		if (ChuckData[VoxelGridIndex.ChuckIndex].IsInitialized() == false)
		{
			if (bInitializeChuck == false) return;

			ChuckData[VoxelGridIndex.ChuckIndex].InitChuckData(ContainerSetting.VoxelLength, ContainerSetting.InvisibleName);
		}

		if (ChuckData[VoxelGridIndex.ChuckIndex].VoxelData.IsValidIndex(VoxelGridIndex.VoxelIndex))
		{
			ChuckData[VoxelGridIndex.ChuckIndex].SetVoxelColor(VoxelGridIndex.VoxelIndex, VoxelColor);
		}

		const FIntVector VoxelLocation = ULFPGridLibrary::IndexToGridLocation(VoxelGridIndex.VoxelIndex, ContainerSetting.VoxelGridSize);

		MarkChuckForColorUpdate(VoxelGridIndex.ChuckIndex, ULFPGridLibrary::IsOnGridEdge(VoxelLocation, ContainerSetting.VoxelGridSize));
	}

	return;
}

void ULFPVoxelContainer::SetVoxelGridData(const FLFPVoxelGridIndex VoxelGridIndex, const FName VoxelAttributeName, const bool bInitializeChuck)
{
	FRWScopeLock WriteLock(GetContainerThreadLock(), SLT_Write);

	if (IsVoxelIndexValid(VoxelGridIndex))
	{
		if (ChuckData[VoxelGridIndex.ChuckIndex].IsInitialized() == false)
		{
			if (bInitializeChuck == false) return;

			ChuckData[VoxelGridIndex.ChuckIndex].InitChuckData(ContainerSetting.VoxelLength, ContainerSetting.InvisibleName);
		}

		if (ChuckData[VoxelGridIndex.ChuckIndex].VoxelData.IsValidIndex(VoxelGridIndex.VoxelIndex))
		{
			ChuckData[VoxelGridIndex.ChuckIndex].SetVoxel(VoxelGridIndex.VoxelIndex, VoxelAttributeName);
		}

		const FIntVector VoxelLocation = ULFPGridLibrary::IndexToGridLocation(VoxelGridIndex.VoxelIndex, ContainerSetting.VoxelGridSize);

		MarkChuckForUpdate(VoxelGridIndex.ChuckIndex, ULFPGridLibrary::IsOnGridEdge(VoxelLocation, ContainerSetting.VoxelGridSize));
	}

	return;
}

void ULFPVoxelContainer::SetVoxelGridDataList(const TArray<FLFPVoxelGridIndex>& VoxelGridIndexList, const FName VoxelAttributeName, const bool bInitializeChuck)
{
	FRWScopeLock WriteLock(GetContainerThreadLock(), SLT_Write);

	for (int32 ListIndex = 0; ListIndex < VoxelGridIndexList.Num(); ListIndex++)
	{
		SetVoxelGridData(VoxelGridIndexList[ListIndex], VoxelAttributeName, bInitializeChuck);
	}

	return;
}

void ULFPVoxelContainer::SetVoxelGridDataWithArea(const FLFPVoxelGridIndex FromVoxelGridIndex, const FLFPVoxelGridIndex ToVoxelGridIndex, const FName VoxelAttributeName, const bool bInitializeChuck)
{
	FRWScopeLock WriteLock(GetContainerThreadLock(), SLT_Write);

	if (IsVoxelIndexValid(FromVoxelGridIndex) == false || IsVoxelIndexValid(ToVoxelGridIndex) == false) return;

	const FIntVector FromLocation = VoxelGridIndexToVoxelGridLocation(FromVoxelGridIndex);
	const FIntVector ToLocation = VoxelGridIndexToVoxelGridLocation(ToVoxelGridIndex);

	for (int32 Z = FromLocation.Z; Z <= ToLocation.Z; Z++)
	{
		for (int32 Y = FromLocation.Y; Y <= ToLocation.Y; Y++)
		{
			for (int32 X = FromLocation.X; X <= ToLocation.X; X++)
			{
				SetVoxelGridData(VoxelGridLocationToVoxelGridIndex(FIntVector(X, Y, Z)), VoxelAttributeName, bInitializeChuck);
			}
		}
	}

	return;
}

void ULFPVoxelContainer::SetChuckGridData(const int32 ChuckIndex, const FName VoxelAttributeName, const bool bInitializeChuck)
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
	}

	return;
}

void ULFPVoxelContainer::SetChuckGridDataWithHeight(const int32 ChuckIndex, const FIntPoint VoxelGridPosition, const float Height, const FName VoxelAttributeName, const bool bInitializeChuck)
{
	FRWScopeLock WriteLock(GetContainerThreadLock(), SLT_Write);

	if (ChuckData.IsValidIndex(ChuckIndex) && ULFPGridLibrary::IsLocationValid(FIntVector(VoxelGridPosition.X, VoxelGridPosition.Y, 0), ContainerSetting.VoxelGridSize))
	{
		if (ChuckData[ChuckIndex].IsInitialized() == false)
		{
			if (bInitializeChuck == false) return;

			ChuckData[ChuckIndex].InitChuckData(ContainerSetting.VoxelLength, ContainerSetting.InvisibleName);
		}
		
		const int32 HeightIndex = ContainerSetting.VoxelGridSize.Z * Height;

		for (int32 VoxelHeightIndex = 0; VoxelHeightIndex < HeightIndex; VoxelHeightIndex++)
		{
			const int32 VoxelIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridPosition.X, VoxelGridPosition.Y, VoxelHeightIndex), ContainerSetting.VoxelGridSize);

			ChuckData[ChuckIndex].SetVoxel(VoxelIndex, VoxelAttributeName);
		}

		MarkChuckForUpdate(ChuckIndex);
	}

	return;
}
