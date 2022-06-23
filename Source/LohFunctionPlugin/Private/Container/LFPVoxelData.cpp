// Copyright by Loh Zhi Kang


#include "Container/LFPVoxelData.h"
#include "Math/LFPGridLibrary.h"

ULFPVoxelData::ULFPVoxelData(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

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

//const FLFPVoxelAttribute& ULFPVoxelData::GetVoxelData(const int32 ChuckIndex, const int32 VoxelIndex) const
//{
//	if (ChuckData.IsValidIndex(ChuckIndex) && ChuckData[ChuckIndex].VoxelData.IsValidIndex(VoxelIndex))
//	{
//		return ChuckData[ChuckIndex].VoxelData[VoxelIndex];
//	}
//
//	return DefaultVoxelAttribute;
//}

const TArray<FLFPVoxelAttribute>& ULFPVoxelData::GetVoxelData(const int32 ChuckIndex)
{
	checkf(ChuckData.IsValidIndex(ChuckIndex), TEXT("Error : Out Of Chuck List Range"));
	
	if (InitializedList[ChuckIndex] == false)
	{
		InitializeChuck(ChuckIndex);
	}

	return ChuckData[ChuckIndex].VoxelData;
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

	return;
}

void ULFPVoxelData::UpdateChuck(const int32 UpdateCount)
{
	const TArray<int32> UpdateArray = UpdateChuckList.Array();

	for (int32 CountIndex = 0; CountIndex < FMath::Min(UpdateCount, UpdateArray.Num()); CountIndex++)
	{
		UpdateChuckList.Remove(UpdateArray[CountIndex]);

		if (ChuckData.IsValidIndex(UpdateArray[CountIndex]))
		{
			ChuckData[UpdateArray[CountIndex]].VoxelUpdateEvent.ExecuteIfBound();
		}
	}

	return;
}

void ULFPVoxelData::MarkChuckForUpdate(const int32 ChuckIndex)
{
	UpdateChuckList.Add(ChuckIndex);

	return;
}

void ULFPVoxelData::SetupVoxelData(const FVector NewMeshSize, const FIntVector NewPoolGridSize, const FIntVector NewChuckGridSize, const int32 NewMaxMaterialID, const int32 NewSectionSize)
{
	MeshSize = NewMeshSize.GetMin() > 10.0 ? NewMeshSize : FVector(10.0);
	PoolGridSize = NewPoolGridSize.GetMin() > 0 ? NewPoolGridSize : FIntVector(1);
	ChuckGridSize = NewChuckGridSize.GetMin() > 0 ? NewChuckGridSize : FIntVector(1);
	MaxMaterialID = NewMaxMaterialID > 0 ? NewMaxMaterialID : 1;

	SectionSize = NewSectionSize > 16 ? NewSectionSize : 16;

	SectionCount = ChuckGridSize.Z / SectionSize;
	if (ChuckGridSize.Z % SectionSize > 0) SectionCount++;

	SectionCount *= MaxMaterialID;

	PoolLength = PoolGridSize.X * PoolGridSize.Y * PoolGridSize.Z;
	ChuckVoxelLength = ChuckGridSize.X * ChuckGridSize.Y * ChuckGridSize.Z;

	ChuckData.Empty(PoolLength);
	ChuckData.SetNum(PoolLength);

	InitializedList.Empty(PoolLength);
	InitializedList.AddUninitialized(PoolLength);
	InitializedList.SetRange(0, PoolLength, false);

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

	if (ChuckData.IsValidIndex(ChuckIndex))
	{
		if (InitializedList[ChuckIndex] == false)
		{
			InitializeChuck(ChuckIndex);
		}

		if (ChuckData[ChuckIndex].VoxelData.IsValidIndex(VoxelChuckIndex))
		{
			ChuckData[ChuckIndex].VoxelData[VoxelChuckIndex] = VoxelAttribute;

			ChuckData[ChuckIndex].VoxelData[VoxelChuckIndex].CorrectMaterialID(MaxMaterialID);

			ChuckData[ChuckIndex].VoxelDataUpdateEvent.ExecuteIfBound(VoxelChuckIndex, true);
		}

		if (bUpdateMesh)
		{
			UpdateChuck();
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
		UpdateChuck();
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
		UpdateChuck();
	}

	return;
}

void ULFPVoxelData::SetAllVoxelGridDataWithSingleData(const int32 ChuckIndex, const FLFPVoxelAttribute& VoxelAttribute, const bool bUpdateMesh)
{
	const int32 ChuckGridMaxIndex = ChuckGridSize.X * ChuckGridSize.Y * ChuckGridSize.Z;

	if (ChuckData.IsValidIndex(ChuckIndex))
	{
		if (InitializedList[ChuckIndex] == false)
		{
			InitializeChuck(ChuckIndex);
		}

		for (int32 VoxelChuckIndex = 0; VoxelChuckIndex < ChuckGridMaxIndex; VoxelChuckIndex++)
		{
			ChuckData[ChuckIndex].VoxelData[VoxelChuckIndex] = VoxelAttribute;

			ChuckData[ChuckIndex].VoxelData[VoxelChuckIndex].CorrectMaterialID(MaxMaterialID);

			ChuckData[ChuckIndex].VoxelDataUpdateEvent.ExecuteIfBound(VoxelChuckIndex, ULFPGridLibrary::IsOnGridEdge(ULFPGridLibrary::IndexToGridLocation(VoxelChuckIndex, ChuckGridSize), ChuckGridSize));

		}

		if (bUpdateMesh)
		{
			UpdateChuck();
		}
	}

	return;
}
