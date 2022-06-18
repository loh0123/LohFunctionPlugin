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

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelAttribute")
		bool IsVisible = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelAttribute")
		TArray<FVector2D> CustomData = {};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelAttribute")
		FVector VertexColor = FVector(1);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelAttribute")
		int32 MaterialID = 0;

	void CorrectMaterialID(const int32 MaxID = 1)
	{
		MaterialID = MaterialID >= 0 && MaterialID < MaxID ? MaterialID : 0;
	}
};

DECLARE_DELEGATE_TwoParams(FOnVoxelDataUpdate, int32, bool);
DECLARE_DELEGATE(FOnVoxelUpdate);

USTRUCT(BlueprintType)
struct FLFPVoxelChuckData
{
	GENERATED_USTRUCT_BODY()

	FLFPVoxelChuckData() {}

	FLFPVoxelChuckData(const FLFPVoxelChuckData& Data) : VoxelData(Data.VoxelData) {}

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelChuckData")
		TArray<FLFPVoxelAttribute> VoxelData = {};

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

/**
 * 
 */
UCLASS(BlueprintType)
class LOHFUNCTIONPLUGIN_API ULFPVoxelData : public UObject
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnChuckGeneration, int32, ChuckIndex, FIntVector, StartVoxelGridLocation, FIntVector, EndVoxelGridLocation);

protected: // Initialize Data

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelData | Cache")
		int32 MaxMaterialID = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelData | Cache")
		int32 SectionCount = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelData | Cache")
		int32 SectionSize = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelData | Cache")
		int32 PoolLength = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelData | Cache")
		int32 ChuckVoxelLength = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelData | Setting")
		FVector MeshSize = FVector(10.0);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelData | Setting")
		FIntVector PoolGridSize = FIntVector(1);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelData | Setting")
		FIntVector ChuckGridSize = FIntVector(1);

protected:  // Runtime Data

	UPROPERTY() TArray<FLFPVoxelChuckData> ChuckData;

	UPROPERTY() TSet<int32> UpdateChuckList;

	TBitArray<> InitializedList;

protected: // Empty Data

	const FLFPVoxelAttribute DefaultVoxelAttribute = FLFPVoxelAttribute();

public:

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "ChuckBegin"))
		FOnChuckGeneration OnChuckGeneration;

public:

	FORCEINLINE bool IsChuckIndexValid(const int32 ChuckIndex) const { return ChuckData.IsValidIndex(ChuckIndex); }

	FORCEINLINE int32 GetPoolLength() const { return PoolLength; }

	FORCEINLINE int32 GetMaxMaterialID() const { return MaxMaterialID; }

	FORCEINLINE int32 GetSectionCount() const { return SectionCount; }

	FORCEINLINE int32 GetSectionSize() const { return SectionSize; }

	FORCEINLINE int32 GetChuckVoxelLength() const { return ChuckVoxelLength; }

	FORCEINLINE FIntVector GetPoolGridSize() const { return PoolGridSize; }

public:

	FORCEINLINE FOnVoxelDataUpdate& GetVoxelDataUpdateEvent(const int32 ChuckIndex) { return ChuckData[ChuckIndex].VoxelDataUpdateEvent; }

	FORCEINLINE FOnVoxelUpdate& GetVoxelUpdateEvent(const int32 ChuckIndex) { return ChuckData[ChuckIndex].VoxelUpdateEvent; }

	FORCEINLINE void DisconnectEvent(const int32 ChuckIndex) { return ChuckData[ChuckIndex].Disconnect(); }

public:

	FORCEINLINE const FLFPVoxelAttribute& GetVoxelData(const FIntVector VoxelGridLocation) const;

	FORCEINLINE const FLFPVoxelAttribute& GetVoxelData(const int32 ChuckIndex, const int32 VoxelIndex) const;

	FORCEINLINE void InitializeChuck(const int32 ChuckIndex);

public:

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
		FORCEINLINE void SetVoxelGridData(const FIntVector VoxelGridLocation, const FLFPVoxelAttribute& VoxelAttribute, const bool bUpdateMesh = true);
	
	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetVoxelGridDataList(const TArray<FIntVector>& VoxelGridLocationList, const TArray<FLFPVoxelAttribute>& VoxelAttributeList, const bool bUpdateMesh = true);
	
	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetVoxelGridDataListWithSingleData(const TArray<FIntVector>& VoxelGridLocationList, const FLFPVoxelAttribute& VoxelAttribute, const bool bUpdateMesh = true);
	
	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetAllVoxelGridDataWithSingleData(const int32 ChuckIndex, const FLFPVoxelAttribute& VoxelAttribute, const bool bUpdateMesh = true);
};
