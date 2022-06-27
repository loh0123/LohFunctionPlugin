// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LFPVoxelData.generated.h"

class UBaseVoxelMesh;

USTRUCT(BlueprintType)
struct FLFPVoxelAttribute
{
	GENERATED_USTRUCT_BODY()

	FLFPVoxelAttribute() {}

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelAttribute")
		FColor VertexColor = FColor(255);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelAttribute")
		int32 MaterialID = 0;

public:

	void CorrectMaterialID(const int32 MaxID = 1)
	{
		MaterialID = MaterialID >= 0 && MaterialID < MaxID ? MaterialID : 0;
	}
};

DECLARE_DELEGATE_TwoParams(FOnVoxelDataUpdate, int32, bool);
DECLARE_DELEGATE(FOnVoxelUpdate);

USTRUCT()
struct FLFPVoxelChuckData
{
	GENERATED_USTRUCT_BODY()

	FLFPVoxelChuckData() {}

	FLFPVoxelChuckData(const FLFPVoxelChuckData& Data) : VoxelData(Data.VoxelData) {}

public:

	UPROPERTY() TArray<FLFPVoxelAttribute> VoxelData = {};

	TBitArray<> VoxelVisibleMap = {};

public:

	// Update Event For Notify Chuck On Voxel Data Change
	FOnVoxelDataUpdate VoxelDataUpdateEvent;

	// Update Event For Notify Chuck On Voxel Update
	FOnVoxelUpdate VoxelUpdateEvent;

	void Disconnect()
	{
		VoxelDataUpdateEvent.Unbind();
		VoxelUpdateEvent.Unbind();
	}
};

USTRUCT(BlueprintType)
struct FLFPVoxelContainerSetting
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelContainerSetting | Cache")
		int32 MaxMaterialID = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelContainerSetting | Cache")
		int32 SectionCount = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelContainerSetting | Cache")
		int32 SectionSize = 1;

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

public:

	FORCEINLINE void SetValue(const FVector& NewMeshSize, const FIntVector& NewPoolGridSize, const FIntVector& NewChuckGridSize)
	{
		MeshSize = NewMeshSize.GetMin() > 10.0 ? NewMeshSize : FVector(10.0);
		PoolGridSize = NewPoolGridSize.GetMin() > 0 ? NewPoolGridSize : FIntVector(1);
		ChuckGridSize = NewChuckGridSize.GetMin() > 0 ? NewChuckGridSize : FIntVector(1);
	}

	FORCEINLINE void UpdateCache(const int32 NewMaxMaterialID, const int32 NewSectionSize)
	{
		MaxMaterialID = NewMaxMaterialID;
		SectionSize = NewSectionSize > 16 ? NewSectionSize : 16;

		SectionCount = ChuckGridSize.Z / SectionSize;
		if (ChuckGridSize.Z % SectionSize > 0) SectionCount++;

		SectionCount *= MaxMaterialID;

		PoolLength = PoolGridSize.X * PoolGridSize.Y * PoolGridSize.Z;
		ChuckVoxelLength = ChuckGridSize.X * ChuckGridSize.Y * ChuckGridSize.Z;
	}
};

/**
 * 
 */
UCLASS(BlueprintType)
class LOHFUNCTIONPLUGIN_API ULFPVoxelData : public UObject
{
	GENERATED_BODY()

protected: // Initialize Data

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelData | Setting")
		FLFPVoxelContainerSetting ContainerSetting;

protected:  // Runtime Data

	UPROPERTY() TArray<FLFPVoxelChuckData> ChuckData;

	UPROPERTY() TSet<int32> UpdateChuckList;

	TBitArray<> InitializedList;

protected: // Empty Data

	const FLFPVoxelAttribute DefaultVoxelAttribute = FLFPVoxelAttribute();

public:

	FORCEINLINE bool IsChuckIndexValid(const int32 ChuckIndex) const { return ChuckData.IsValidIndex(ChuckIndex); }

	FORCEINLINE const FLFPVoxelContainerSetting& GetContainerSetting() const { return ContainerSetting; }

public:

	FORCEINLINE FOnVoxelDataUpdate& GetVoxelDataUpdateEvent(const int32 ChuckIndex) { return ChuckData[ChuckIndex].VoxelDataUpdateEvent; }

	FORCEINLINE FOnVoxelUpdate& GetVoxelUpdateEvent(const int32 ChuckIndex) { return ChuckData[ChuckIndex].VoxelUpdateEvent; }

	FORCEINLINE void DisconnectEvent(const int32 ChuckIndex) { return ChuckData[ChuckIndex].Disconnect(); }

public:

	FORCEINLINE const FLFPVoxelAttribute& GetVoxelData(const FIntVector VoxelGridLocation) const;

	FORCEINLINE const TArray<FLFPVoxelAttribute>& GetVoxelData(const int32 ChuckIndex);

	FORCEINLINE bool GetVoxelVisible(const FIntVector VoxelGridLocation) const;

	FORCEINLINE const TBitArray<>& GetVoxelVisible(const int32 ChuckIndex);

	FORCEINLINE void InitializeChuck(const int32 ChuckIndex);

public:

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE int32 GetContainerSize();

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void UpdateChuck(const int32 UpdateCount = 9999999);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void MarkChuckForUpdate(const int32 ChuckIndex);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetupVoxelData(const FVector NewMeshSize, const FIntVector NewPoolGridSize, const FIntVector NewChuckGridSize, const int32 NewMaxMaterialID = 1, const int32 NewSectionSize = 16);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void GetPoolAttribute(const int32 ChuckIndex, FIntVector& ChuckGridLocation, FIntVector& StartVoxelLocation, FVector& ChuckMeshSize, FIntVector& ChuckVoxelGridSize);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE bool IsChuckInitialized(const int32 ChuckIndex) const;

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetVoxelGridData(const FIntVector VoxelGridLocation, const FLFPVoxelAttribute& VoxelAttribute, const bool IsVisible, const bool bUpdateMesh = true);
	
	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetVoxelGridDataList(const TArray<FIntVector>& VoxelGridLocationList, const FLFPVoxelAttribute& VoxelAttribute, const bool IsVisible, const bool bUpdateMesh = true);
	
	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetAllVoxelGridDataWithSingleData(const int32 ChuckIndex, const FLFPVoxelAttribute& VoxelAttribute, const bool IsVisible, const bool bUpdateMesh = true);
};
