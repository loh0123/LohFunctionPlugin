// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Math/LFPGridLibrary.h"
#include "LFPVoxelContainer.generated.h"

USTRUCT(BlueprintType)
struct FLFPVoxelAttributeV2 : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelAttribute")
		FColor VertexColor = FColor(255);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelAttribute")
		int32 MaterialID = 0;
};

DECLARE_DELEGATE_OneParam(FOnVoxelChuckUpdate, TSet<int32>);

USTRUCT()
struct FLFPVoxelChuckDataV2
{
	GENERATED_USTRUCT_BODY()

	FLFPVoxelChuckDataV2() {}

	FLFPVoxelChuckDataV2(const FLFPVoxelChuckDataV2& Data) : VoxelData(Data.VoxelData) {}

public:

	UPROPERTY() TArray<FName> VoxelData = {};

protected:

	UPROPERTY() TSet<int32> VoxelChangeIndexList = {};

public:

	// Update Event For Notify Chuck On Voxel Update
	FOnVoxelChuckUpdate VoxelChuckUpdateEvent;

public:

	FORCEINLINE bool IsInitialized() const
	{
		return VoxelData.IsEmpty() == false;
	}

	FORCEINLINE void InitChuckData(const int32 VoxelLength)
	{
		VoxelData.Init(FName("None"), VoxelLength);

		VoxelChangeIndexList.Empty(VoxelLength);

		UpdateAllChuckData();
	}

	FORCEINLINE void UpdateAllChuckData()
	{
		for (int32 Index = 0; Index < VoxelData.Num(); Index++)
		{
			VoxelChangeIndexList.Add(Index);
		}
	}

	FORCEINLINE void SetVoxel(const int32 VoxelIndex, FName VoxelName)
	{
		VoxelChangeIndexList.Add(VoxelIndex);

		VoxelData[VoxelIndex] = VoxelName;
	}

	FORCEINLINE void SendUpdateEvent()
	{
		VoxelChuckUpdateEvent.ExecuteIfBound(VoxelChangeIndexList);

		VoxelChangeIndexList.Empty();
	}

	FORCEINLINE void Disconnect()
	{
		VoxelChuckUpdateEvent.Unbind();
	}
};

USTRUCT(BlueprintType)
struct FLFPVoxelContainerSettingV2
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelContainerSetting | Cache")
		int32 PoolLength = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelContainerSetting | Cache")
		int32 ChuckVoxelLength = 1;

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelContainerSetting | Setting")
		FVector MeshSize = FVector(10.0);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelContainerSetting | Setting")
		FIntVector PoolGridSize = FIntVector(1);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelContainerSetting | Setting")
		FIntVector ChuckGridSize = FIntVector(1);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelContainerSetting | Setting")
		FName InvisibleName = FName("None");

public:

	FORCEINLINE void InitSetting()
	{
		if (MeshSize.GetMin() < 10.0) MeshSize = FVector(10.0);
		if (PoolGridSize.GetMin() < 0) PoolGridSize = FIntVector(1);
		if (ChuckGridSize.GetMin() < 0) ChuckGridSize = FIntVector(1);

		PoolLength = PoolGridSize.X * PoolGridSize.Y * PoolGridSize.Z;
		ChuckVoxelLength = ChuckGridSize.X * ChuckGridSize.Y * ChuckGridSize.Z;
	}
};

/**
 *
 */
UCLASS(BlueprintType)
class LOHFUNCTIONPLUGIN_API ULFPVoxelContainer : public UObject
{
	GENERATED_BODY()

protected: // Initialize Data

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelData | Setting")
		FLFPVoxelContainerSettingV2 ContainerSetting;

protected:  // Runtime Data

	UPROPERTY() TObjectPtr<UDataTable> VoxelAttributeTable;

	UPROPERTY() TArray<FLFPVoxelChuckDataV2> ChuckData;

	UPROPERTY() TSet<int32> BatchChuckUpdateList;

protected: // Empty Data

	const FLFPVoxelAttributeV2 DefaultVoxelAttribute = FLFPVoxelAttributeV2();

public:

	FORCEINLINE bool IsChuckIndexValid(const int32 ChuckIndex) const { return ChuckData.IsValidIndex(ChuckIndex); }

	FORCEINLINE const FLFPVoxelContainerSettingV2& GetContainerSetting() const { return ContainerSetting; }

public:

	FORCEINLINE FOnVoxelChuckUpdate& GetVoxelUpdateEvent(const int32 ChuckIndex) { return ChuckData[ChuckIndex].VoxelChuckUpdateEvent; }

	FORCEINLINE void DisconnectEvent(const int32 ChuckIndex) { return ChuckData[ChuckIndex].Disconnect(); }

public:

	FORCEINLINE const FName& GetVoxelName(const FIntVector VoxelGridLocation) const
	{
		int32 ChuckIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X / ContainerSetting.ChuckGridSize.X, VoxelGridLocation.Y / ContainerSetting.ChuckGridSize.Y, VoxelGridLocation.Z / ContainerSetting.ChuckGridSize.Z), ContainerSetting.PoolGridSize);
		int32 VoxelIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X % ContainerSetting.ChuckGridSize.X, VoxelGridLocation.Y % ContainerSetting.ChuckGridSize.Y, VoxelGridLocation.Z % ContainerSetting.ChuckGridSize.Z), ContainerSetting.ChuckGridSize);

		check(IsChuckIndexValid(ChuckIndex));
		check(VoxelIndex < ContainerSetting.ChuckVoxelLength && VoxelIndex >= 0);

		return ChuckData[ChuckIndex].VoxelData[VoxelIndex];
	}

	FORCEINLINE const TArray<FName>& GetVoxelNameList(const int32 ChuckIndex) const
	{
		check(IsChuckIndexValid(ChuckIndex));

		return ChuckData[ChuckIndex].VoxelData;
	}

	FORCEINLINE bool IsVoxelVisible(const FIntVector VoxelGridLocation) const
	{
		int32 ChuckIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X / ContainerSetting.ChuckGridSize.X, VoxelGridLocation.Y / ContainerSetting.ChuckGridSize.Y, VoxelGridLocation.Z / ContainerSetting.ChuckGridSize.Z), ContainerSetting.PoolGridSize);
		int32 VoxelIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X % ContainerSetting.ChuckGridSize.X, VoxelGridLocation.Y % ContainerSetting.ChuckGridSize.Y, VoxelGridLocation.Z % ContainerSetting.ChuckGridSize.Z), ContainerSetting.ChuckGridSize);

		check(IsChuckIndexValid(ChuckIndex));
		check(VoxelIndex < ContainerSetting.ChuckVoxelLength&& VoxelIndex >= 0);

		return ChuckData[ChuckIndex].VoxelData[VoxelIndex] != ContainerSetting.InvisibleName;
	}

	FORCEINLINE void InitializeOrUpdateChuck(const int32 ChuckIndex)
	{
		check(IsChuckIndexValid(ChuckIndex));

		if (ChuckData[ChuckIndex].IsInitialized())
		{
			ChuckData[ChuckIndex].UpdateAllChuckData();
		}
		else
		{
			ChuckData[ChuckIndex].InitChuckData(ContainerSetting.ChuckVoxelLength);
		}
	}

public:

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE int32 GetContainerSize();

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void UpdateChuck();

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void MarkChuckForUpdate(const int32 ChuckIndex);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetupVoxelData(UDataTable* NewVoxelAttributeTable, const FLFPVoxelContainerSettingV2 NewSetting);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void GetChuckAttribute(const int32 ChuckIndex, FIntVector& StartVoxelLocation, FVector& ChuckMeshSize, FIntVector& ChuckVoxelGridSize);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE bool IsChuckInitialized(const int32 ChuckIndex) const;

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetVoxelGridData(const FIntVector VoxelGridLocation, const FName& VoxelAttributeName, const bool bUpdateMesh = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetVoxelGridDataList(const TArray<FIntVector>& VoxelGridLocationList, const FName& VoxelAttributeName, const bool bUpdateMesh = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetAllVoxelGridDataWithSingleData(const int32 ChuckIndex, const FName& VoxelAttributeName, const bool bUpdateMesh = true);
};

