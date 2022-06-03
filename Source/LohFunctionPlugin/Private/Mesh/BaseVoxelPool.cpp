// Copyright by Loh Zhi Kang


#include "Mesh/BaseVoxelPool.h"
#include "./Math/LFPGridLibrary.h"
#include "Runtime/Core/Public/Async/ParallelFor.h"

void UBaseVoxelPool::SetupVoxelPool(const FIntVector NewPoolGridSize, const int32 NewAllowMeshSize, const FVector NewMainMeshSize, const FIntVector NewMainGridSize, TSubclassOf<UBaseVoxelMesh> VoxelType)
{
	FreeAllMeshes();

	PoolSize = NewPoolGridSize.X * NewPoolGridSize.Y * NewPoolGridSize.Z;

	PoolGridSize = NewPoolGridSize;
	MainMeshSize = NewMainMeshSize;
	MainGridSize = NewMainGridSize;

	FLFPVoxelMeshData VoxelDataToFill;

	VoxelDataToFill.GridSize = MainGridSize;
	VoxelDataToFill.MeshSize = MainMeshSize;
	VoxelDataToFill.MaxIndex = MainGridSize.X * MainGridSize.Y * MainGridSize.Z;

	PoolVoxelData.Init(VoxelDataToFill, PoolSize);

	AllowMeshSize = NewAllowMeshSize;

	CachedMeshes.Reserve(AllowMeshSize);

	for (int32 Index = 0; Index < AllowMeshSize; Index++)
	{
		CachedMeshes.Add(NewObject<UBaseVoxelMesh>(this, VoxelType));
	}

	AllCreatedMeshes = TSet(CachedMeshes);

	return;
}

void UBaseVoxelPool::ProcessVoxelUpdate(const int32 Count)
{
	if (UpdateList.Num() > 0)
	{
		for (int32 LoopIndex = 0; LoopIndex < FMath::Min(Count,UpdateList.Num()); LoopIndex++)
		{
			TObjectPtr<UBaseVoxelMesh> VoxelMesh = UpdateList.Pop();

			if (!VoxelMesh->IsInitialized())
			{
				VoxelMesh->SetInitialized(true);

				VoxelMesh->OnBeginGenerator.Broadcast(VoxelMesh);
			}

			VoxelMesh->UpdateMesh_Internal();
		}

		if (UpdateList.GetSlack() > 10)
		{
			UpdateList.Shrink();
		}
	}

	return;
}

FLFPVoxelMeshData& UBaseVoxelPool::GetPoolVoxelData(const int32 PoolIndex)
{
	checkf(PoolVoxelData.IsValidIndex(PoolIndex), TEXT("Pool Index Invalid"));

	return PoolVoxelData[PoolIndex];
}

int32 UBaseVoxelPool::PoolVoxelLocationToPoolIndex(const FIntVector PoolVoxelLocation) const
{
	if (PoolVoxelLocation.GetMin() < 0) return INDEX_NONE;

	const FIntVector PoolLocation = FIntVector(PoolVoxelLocation.X / MainGridSize.X, PoolVoxelLocation.Y / MainGridSize.Y, PoolVoxelLocation.Z / MainGridSize.Z);

	return ULFPGridLibrary::IsLocationValid(PoolLocation, PoolGridSize) ? ULFPGridLibrary::GridLocationToIndex(PoolLocation, PoolGridSize) : INDEX_NONE;
}

FIntVector UBaseVoxelPool::PoolVoxelLocationToVoxelLocation(const FIntVector PoolVoxelLocation) const
{
	return FIntVector(PoolVoxelLocation.X % MainGridSize.X, PoolVoxelLocation.Y % MainGridSize.Y, PoolVoxelLocation.Z % MainGridSize.Z);
}

void UBaseVoxelPool::MarkTrianglesDataForUpdate(const FIntVector& PoolVoxelLocation)
{
	const int32 PoolIndex = PoolVoxelLocationToPoolIndex(PoolVoxelLocation);

	if (!PoolVoxelData.IsValidIndex(PoolIndex) || !ActiveMeshes.Contains(PoolIndex)) return;

	const FIntVector VoxelLocation = PoolVoxelLocationToVoxelLocation(PoolVoxelLocation);

	TObjectPtr<UBaseVoxelMesh> VoxelMesh = ActiveMeshes.FindChecked(PoolIndex);

	VoxelMesh->MarkTrianglesDataForUpdate(VoxelLocation);

	VoxelMesh->UpdateMesh(); // Refactor later
}

void UBaseVoxelPool::MarkTrianglesDataListForUpdate(const TSet<FIntVector>& PoolVoxelLocationList)
{
	TSet<TObjectPtr<UBaseVoxelMesh>> UpdateMeshList;

	for (const FIntVector& PoolVoxelLocation : PoolVoxelLocationList)
	{
		const int32 PoolIndex = PoolVoxelLocationToPoolIndex(PoolVoxelLocation);

		if (!PoolVoxelData.IsValidIndex(PoolIndex) || !ActiveMeshes.Contains(PoolIndex)) continue;

		const FIntVector VoxelLocation = PoolVoxelLocationToVoxelLocation(PoolVoxelLocation);

		TObjectPtr<UBaseVoxelMesh> VoxelMesh = ActiveMeshes.FindChecked(PoolIndex);

		VoxelMesh->MarkTrianglesDataForUpdate(VoxelLocation);

		UpdateMeshList.Add(VoxelMesh);
	}

	for (TObjectPtr<UBaseVoxelMesh> VoxelMesh : UpdateMeshList)
	{
		VoxelMesh->UpdateMesh(); // Refactor later
	}
	
	return;
}

bool UBaseVoxelPool::IsBlockVisible(const FIntVector PoolVoxelLocation, const int32 SelfMaterialID) const
{
	const int32 PoolIndex = PoolVoxelLocationToPoolIndex(PoolVoxelLocation);

	// Check is PoolIndex valid
	if (!PoolVoxelData.IsValidIndex(PoolIndex)) return false;

	// Check is PoolIndex initialized
	if (!PoolVoxelData[PoolIndex].IsInitialized) return true;

	const int32 GridIndex = ULFPGridLibrary::GridLocationToIndex(PoolVoxelLocationToVoxelLocation(PoolVoxelLocation), MainGridSize);

	return PoolVoxelData[PoolIndex].GridData[GridIndex].IsVisible ? PoolVoxelData[PoolIndex].GridData[GridIndex].MaterialID == SelfMaterialID : false;
}

void UBaseVoxelPool::AddVoxelUpdate(TObjectPtr<UBaseVoxelMesh> VoxelMesh)
{
	if (UpdateList.Num() == 0 || UpdateList.Last() != VoxelMesh) UpdateList.AddUnique(VoxelMesh);

	return;
}



UBaseVoxelMesh* UBaseVoxelPool::RequestMesh(const FIntVector PoolLocation)
{
	if (CachedMeshes.Num() > 0 && ULFPGridLibrary::IsLocationValid(PoolLocation, PoolGridSize))
	{
		TObjectPtr<UBaseVoxelMesh> OutMesh = CachedMeshes.Pop(false);

		const int32 PoolIndex = ULFPGridLibrary::GridLocationToIndex(PoolLocation, PoolGridSize);

		ActiveMeshes.Add(PoolIndex, OutMesh);

		OutMesh->SetupPool(this, PoolLocation, PoolIndex);

		return OutMesh;
	}
	else
	{
		return nullptr;
	}
}



void UBaseVoxelPool::ReturnMesh(const FIntVector PoolLocation)
{
	TObjectPtr<UBaseVoxelMesh> Mesh = *(ActiveMeshes.Find(ULFPGridLibrary::GridLocationToIndex(PoolLocation, PoolGridSize)));

	if (ensure(Mesh) && ensure(AllCreatedMeshes.Contains(Mesh)))
	{
		ActiveMeshes.Remove(ULFPGridLibrary::GridLocationToIndex(PoolLocation, PoolGridSize));

		Mesh->ClearPool();
		Mesh->Reset();

		if (ensure(CachedMeshes.Contains(Mesh) == false))
		{
			CachedMeshes.Add(Mesh);
		}
	}
}


void UBaseVoxelPool::ReturnAllMeshes()
{
	CachedMeshes = AllCreatedMeshes.Array();

	AllCreatedMeshes.Empty();

	for (TObjectPtr<UBaseVoxelMesh> Mesh : CachedMeshes)
	{
		if (Mesh)
		{
			Mesh->ClearPool();
			Mesh->Reset();
		}
	}

	// TODO: this may be vestigial code, unclear how it could be hit
	int32 Removed = CachedMeshes.RemoveAll([](TObjectPtr<UBaseVoxelMesh> Mesh) { return Mesh == nullptr; });
	ensure(Removed == 0);
}

void UBaseVoxelPool::FreeAllMeshes()
{
	CachedMeshes.Reset();
	ActiveMeshes.Reset();
	AllCreatedMeshes.Reset();
}