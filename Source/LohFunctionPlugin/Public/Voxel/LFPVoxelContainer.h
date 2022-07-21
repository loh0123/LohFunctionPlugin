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

DECLARE_DELEGATE_OneParam(FOnVoxelChuckUpdate, const TSet<int32>&);

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

	FLFPVoxelContainerSettingV2() {}

	FLFPVoxelContainerSettingV2(FIntVector NewVoxelGridSize, FIntVector NewChuckGridSize, FName NewInvisibleName) : 
		VoxelGridSize(NewVoxelGridSize), ChuckGridSize(NewChuckGridSize), InvisibleName(NewInvisibleName) {}

public:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelContainerSetting | Cache")
		int32 ChuckLength = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelContainerSetting | Cache")
		int32 VoxelLength = 1;

public:

	/* Size Of Voxel Inside Of A Chuck */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelContainerSetting | Setting")
		FIntVector VoxelGridSize = FIntVector(1);

	/* Size Of Chuck Store In This Container */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelContainerSetting | Setting")
		FIntVector ChuckGridSize = FIntVector(1);

	/* The Name To Check For Voxel Visible */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelContainerSetting | Setting")
		FName InvisibleName = FName("None");

public:

	FORCEINLINE void InitSetting()
	{
		if (VoxelGridSize.GetMin() < 0) VoxelGridSize = FIntVector(1);
		if (ChuckGridSize.GetMin() < 0) ChuckGridSize = FIntVector(1);

		VoxelLength = VoxelGridSize.X * VoxelGridSize.Y * VoxelGridSize.Z;
		ChuckLength = ChuckGridSize.X * ChuckGridSize.Y * ChuckGridSize.Z;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChuckInitialize, const int32, ChuckIndex);

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

	FORCEINLINE const FLFPVoxelContainerSettingV2& GetContainerSetting() const { return ContainerSetting; }

public:

	FORCEINLINE bool IsChuckIndexValid(const int32 ChuckIndex) const { return ChuckData.IsValidIndex(ChuckIndex); }

	FORCEINLINE bool IsVoxelIndexValid(const int32 ChuckIndex, const int32 VoxelIndex) const { return ChuckData.IsValidIndex(ChuckIndex) ? ChuckData[ChuckIndex].VoxelData.IsValidIndex(VoxelIndex) : false; }

public:

	FORCEINLINE FOnVoxelChuckUpdate& GetVoxelUpdateEvent(const int32 ChuckIndex) { return ChuckData[ChuckIndex].VoxelChuckUpdateEvent; }

public:

	FORCEINLINE FIntVector GetChuckStartVoxelLocation(const int32 ChuckIndex) const
	{
		check(IsChuckIndexValid(ChuckIndex));

		const FIntVector ChuckGridLocation = ULFPGridLibrary::IndexToGridLocation(ChuckIndex, ContainerSetting.ChuckGridSize);

		return FIntVector(ChuckGridLocation.X * ContainerSetting.VoxelGridSize.X, ChuckGridLocation.Y * ContainerSetting.VoxelGridSize.Y, ChuckGridLocation.Z * ContainerSetting.VoxelGridSize.Z);
	}

	FORCEINLINE const FName& GetVoxelName(const FIntVector VoxelGridLocation) const
	{
		int32 ChuckIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X / ContainerSetting.VoxelGridSize.X, VoxelGridLocation.Y / ContainerSetting.VoxelGridSize.Y, VoxelGridLocation.Z / ContainerSetting.VoxelGridSize.Z), ContainerSetting.ChuckGridSize);
		int32 VoxelIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X % ContainerSetting.VoxelGridSize.X, VoxelGridLocation.Y % ContainerSetting.VoxelGridSize.Y, VoxelGridLocation.Z % ContainerSetting.VoxelGridSize.Z), ContainerSetting.VoxelGridSize);

		check(IsChuckIndexValid(ChuckIndex));
		check(VoxelIndex < ContainerSetting.VoxelLength && VoxelIndex >= 0);

		return ChuckData[ChuckIndex].VoxelData[VoxelIndex];
	}

	FORCEINLINE const TArray<FName>& GetVoxelNameList(const int32 ChuckIndex) const
	{
		check(IsChuckIndexValid(ChuckIndex));

		return ChuckData[ChuckIndex].VoxelData;
	}

	FORCEINLINE bool IsVoxelVisible(const FIntVector VoxelGridLocation) const
	{
		return GetVoxelName(VoxelGridLocation) != ContainerSetting.InvisibleName;
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
			ChuckData[ChuckIndex].InitChuckData(ContainerSetting.VoxelLength);

			VoxelChuckUpdateEvent.Broadcast(ChuckIndex);
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
		FORCEINLINE bool IsChuckInitialized(const int32 ChuckIndex) const;

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetVoxelGridData(const FIntVector VoxelGridLocation, const FName& VoxelAttributeName, const bool bUpdateMesh = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetVoxelGridDataList(const TArray<FIntVector>& VoxelGridLocationList, const FName& VoxelAttributeName, const bool bUpdateMesh = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetChuckGridData(const int32 ChuckIndex, const FName& VoxelAttributeName, const bool bUpdateMesh = true);

public:

	UPROPERTY(BlueprintAssignable, Category = "VoxelData | Event")
		FOnChuckInitialize VoxelChuckUpdateEvent;
};

