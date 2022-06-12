// Fill out your copyright notice in the Description page of Project Settings.


#include "Container/LFPVoxelData.h"
#include "Math/LFPGridLibrary.h"

const FLFPVoxelAttribute& ULFPVoxelData::GetVoxelData(const FIntVector VoxelGridLocation) const
{
	int32 ChuckIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X / ChuckGridSize.X, VoxelGridLocation.Y / ChuckGridSize.Y, VoxelGridLocation.Z / ChuckGridSize.Z), PoolGridSize);
	int32 VoxelIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X % ChuckGridSize.X, VoxelGridLocation.Y % ChuckGridSize.Y, VoxelGridLocation.Z % ChuckGridSize.Z), ChuckGridSize);

	if (ChuckData.IsValidIndex(ChuckIndex) && ChuckData[ChuckIndex].VoxelData.IsValidIndex(VoxelIndex))
	{
		return ChuckData[ChuckIndex].VoxelData[VoxelIndex];
	}

	return DefaultVoxelAttribute;
}

const FLFPVoxelAttribute& ULFPVoxelData::GetVoxelData(const int32 ChuckIndex, const int32 VoxelIndex) const
{
	if (ChuckData.IsValidIndex(ChuckIndex) && ChuckData[ChuckIndex].VoxelData.IsValidIndex(VoxelIndex))
	{
		return ChuckData[ChuckIndex].VoxelData[VoxelIndex];
	}

	return DefaultVoxelAttribute;
}

void ULFPVoxelData::InitializeChuck(const int32 ChuckIndex)
{
	checkf(ChuckData.IsValidIndex(ChuckIndex), TEXT("Error : Out Of Chuck List Range"));

	ChuckData[ChuckIndex].VoxelData.Empty(ChuckVoxelLength);
	ChuckData[ChuckIndex].VoxelData.SetNum(ChuckVoxelLength);

	InitializedList[ChuckIndex] = true;

	FIntVector ChuckGridLocation = ULFPGridLibrary::IndexToGridLocation(ChuckIndex, PoolGridSize);
	FIntVector StartVoxelLocation = FIntVector(ChuckGridLocation.X * ChuckGridSize.X, ChuckGridLocation.Y * ChuckGridSize.Y, ChuckGridLocation.Z * ChuckGridSize.Z);
	FIntVector EndVoxelLocation = FIntVector(ChuckGridLocation.X * (ChuckGridSize.X + 1), ChuckGridLocation.Y * (ChuckGridSize.Y + 1), ChuckGridLocation.Z * (ChuckGridSize.Z + 1)) - FIntVector(1);

	OnChuckGeneration.Broadcast(ChuckIndex, StartVoxelLocation, EndVoxelLocation);

	return;
}

void ULFPVoxelData::SetupVoxelData(const FVector NewMeshSize, const FIntVector NewPoolGridSize, const FIntVector NewChuckGridSize)
{
	PoolLength = NewPoolGridSize.X * NewPoolGridSize.Y * NewPoolGridSize.Z;
	ChuckVoxelLength = NewChuckGridSize.X * NewChuckGridSize.Y * NewChuckGridSize.Z;

	ChuckData.Empty(PoolLength);
	ChuckData.SetNum(PoolLength);

	InitializedList.Empty(PoolLength);
	InitializedList.AddUninitialized(PoolLength);
	InitializedList.SetRange(0, PoolLength, false);

	MeshSize = NewMeshSize;
	PoolGridSize = NewPoolGridSize;
	ChuckGridSize = NewChuckGridSize;

	return;
}

void ULFPVoxelData::GetPoolAttribute(const int32 ChuckIndex, FIntVector& ChuckGridLocation, FIntVector& StartVoxelLocation, FVector& ChuckMeshSize, FIntVector& ChuckVoxelGridSize)
{
	if (!ChuckData.IsValidIndex(ChuckIndex)) return;

	ChuckGridLocation = ULFPGridLibrary::IndexToGridLocation(ChuckIndex, PoolGridSize);
	StartVoxelLocation = FIntVector(ChuckGridLocation.X * ChuckGridSize.X, ChuckGridLocation.Y * ChuckGridSize.Y, ChuckGridLocation.Z * ChuckGridSize.Z);

	ChuckMeshSize = MeshSize;
	ChuckVoxelGridSize = ChuckGridSize;

	return;
}

bool ULFPVoxelData::IsChuckInitialized(const int32 ChuckIndex) const
{
	if (!ChuckData.IsValidIndex(ChuckIndex)) return false;

	return InitializedList[ChuckIndex];
}

void ULFPVoxelData::SetVoxelGridData(const FIntVector VoxelGridLocation, const FLFPVoxelAttribute& VoxelAttribute, const bool bUpdateMesh)
{
	int32 ChuckIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X / ChuckGridSize.X, VoxelGridLocation.Y / ChuckGridSize.Y, VoxelGridLocation.Z / ChuckGridSize.Z), PoolGridSize);
	int32 VoxelChuckIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X % ChuckGridSize.X, VoxelGridLocation.Y % ChuckGridSize.Y, VoxelGridLocation.Z % ChuckGridSize.Z), ChuckGridSize);

	if (ChuckData.IsValidIndex(ChuckIndex) && 
		InitializedList[ChuckIndex] && 
		ChuckData[ChuckIndex].VoxelData.IsValidIndex(VoxelChuckIndex))
	{
		ChuckData[ChuckIndex].VoxelData[VoxelChuckIndex] = VoxelAttribute;

		ChuckData[ChuckIndex].VoxelDataUpdateEvent.ExecuteIfBound(VoxelChuckIndex);

		if (bUpdateMesh)
		{
			OnChuckUpdate.Broadcast();
		}
	}

	return;
}

void ULFPVoxelData::SetVoxelGridDataList(const TArray<FIntVector>& VoxelGridLocationList, const TArray<FLFPVoxelAttribute>& VoxelAttributeList, const bool bUpdateMesh)
{
	for (int32 ListIndex = 0; ListIndex < VoxelGridLocationList.Num(); ListIndex++)
	{
		SetVoxelGridData(VoxelGridLocationList[ListIndex], VoxelAttributeList[ListIndex], false);
	}

	if (bUpdateMesh)
	{
		OnChuckUpdate.Broadcast();
	}

	return;
}

void ULFPVoxelData::SetVoxelGridDataListWithSingleData(const TArray<FIntVector>& VoxelGridLocationList, const FLFPVoxelAttribute& VoxelAttribute, const bool bUpdateMesh)
{
	for (int32 ListIndex = 0; ListIndex < VoxelGridLocationList.Num(); ListIndex++)
	{
		SetVoxelGridData(VoxelGridLocationList[ListIndex], VoxelAttribute, false);
	}

	if (bUpdateMesh)
	{
		OnChuckUpdate.Broadcast();
	}

	return;
}

void ULFPVoxelData::SetAllVoxelGridDataWithSingleData(const int32 ChuckIndex, const FLFPVoxelAttribute& VoxelAttribute, const bool bUpdateMesh)
{
	if (!ChuckData.IsValidIndex(ChuckIndex)) return;

	const int32 ChuckGridMaxIndex = ChuckGridSize.X * ChuckGridSize.Y * ChuckGridSize.Z;

	for (int32 VoxelChuckIndex = 0; VoxelChuckIndex < ChuckGridMaxIndex; VoxelChuckIndex++)
	{
		ChuckData[ChuckIndex].VoxelData[VoxelChuckIndex] = VoxelAttribute;

		ChuckData[ChuckIndex].VoxelDataUpdateEvent.ExecuteIfBound(VoxelChuckIndex);
	}

	if (bUpdateMesh)
	{
		OnChuckUpdate.Broadcast();
	}

	return;
}
