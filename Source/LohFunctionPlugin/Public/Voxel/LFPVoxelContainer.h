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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelAttribute")
		FVector2D UVOffset = FVector2D(0);
};

DECLARE_DELEGATE(FOnVoxelChuckUpdate);

USTRUCT()
struct FLFPVoxelChuckDataV2
{
	GENERATED_USTRUCT_BODY()

	FLFPVoxelChuckDataV2() {}

	FLFPVoxelChuckDataV2(const FLFPVoxelChuckDataV2& Data) : VoxelData(Data.VoxelData) {}

public:

	UPROPERTY() TArray<FName> VoxelData = {};

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
		VoxelData.Init(FName("Empty"), VoxelLength);
	}

	FORCEINLINE void SetVoxel(const int32 VoxelIndex, FName VoxelName)
	{
		check(VoxelData.IsValidIndex(VoxelIndex));

		VoxelData[VoxelIndex] = VoxelName;
	}

	template <typename UserClass, typename Func>
	FORCEINLINE void Connect(UserClass* InUserObject, Func InFunc)
	{
		VoxelChuckUpdateEvent.BindUObject(InUserObject, InFunc);
	}

	FORCEINLINE void SendUpdateEvent()
	{
		VoxelChuckUpdateEvent.ExecuteIfBound();
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

public:

	UPROPERTY(BlueprintAssignable, Category = "VoxelData | Event")
		FOnChuckInitialize VoxelChuckUpdateEvent;

protected: // Initialize Data

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelData | Setting")
		FLFPVoxelContainerSettingV2 ContainerSetting;

protected:  // Runtime Data

	UPROPERTY() TObjectPtr<UDataTable> VoxelAttributeTable;

	UPROPERTY() TArray<FLFPVoxelChuckDataV2> ChuckData;

	UPROPERTY() TSet<int32> BatchChuckUpdateList;

protected: // Empty Data

	const FLFPVoxelAttributeV2 DefaultVoxelAttribute = FLFPVoxelAttributeV2();

public: /* Function For Render Component To Getting Container Init Data */

	FORCEINLINE const FLFPVoxelContainerSettingV2& GetContainerSetting() const { return ContainerSetting; }

public:  /* Function For Render Component To Check Container Data Is Safe */

	FORCEINLINE bool IsChuckIndexValid(const int32 ChuckIndex) const { return ChuckData.IsValidIndex(ChuckIndex); }

	FORCEINLINE bool IsVoxelIndexValid(const int32 ChuckIndex, const int32 VoxelIndex) const { return ChuckData.IsValidIndex(ChuckIndex) ? ChuckData[ChuckIndex].VoxelData.IsValidIndex(VoxelIndex) : false; }

public: /* Function For Render Component To Get Container Data */

	FORCEINLINE FIntVector GetChuckStartVoxelLocation(const int32 ChuckIndex) const
	{
		check(IsChuckIndexValid(ChuckIndex));

		const FIntVector ChuckGridLocation = ULFPGridLibrary::IndexToGridLocation(ChuckIndex, ContainerSetting.ChuckGridSize);

		return FIntVector(ChuckGridLocation.X * ContainerSetting.VoxelGridSize.X, ChuckGridLocation.Y * ContainerSetting.VoxelGridSize.Y, ChuckGridLocation.Z * ContainerSetting.VoxelGridSize.Z);
	}

	FORCEINLINE const FLFPVoxelAttributeV2& GetVoxelAttribute(const FIntVector VoxelGridLocation) const
	{
		if (VoxelGridLocation.GetMin() < 0) return DefaultVoxelAttribute;

		int32 ChuckIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X / ContainerSetting.VoxelGridSize.X, VoxelGridLocation.Y / ContainerSetting.VoxelGridSize.Y, VoxelGridLocation.Z / ContainerSetting.VoxelGridSize.Z), ContainerSetting.ChuckGridSize);
		int32 VoxelIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X % ContainerSetting.VoxelGridSize.X, VoxelGridLocation.Y % ContainerSetting.VoxelGridSize.Y, VoxelGridLocation.Z % ContainerSetting.VoxelGridSize.Z), ContainerSetting.VoxelGridSize);

		return IsChuckIndexValid(ChuckIndex) ? GetVoxelAttributeByName(ChuckData[ChuckIndex].VoxelData[VoxelIndex]) : DefaultVoxelAttribute;
	}

	FORCEINLINE const FLFPVoxelAttributeV2& GetVoxelAttributeByName(const FName VoxelName) const
	{
		uint8* Data = VoxelAttributeTable != nullptr ? VoxelAttributeTable->FindRowUnchecked(VoxelName) : nullptr;

		if (Data != nullptr)
		{
			return *(reinterpret_cast<FLFPVoxelAttributeV2*>(Data));
		}
		else
		{
			return DefaultVoxelAttribute;
		}
	}

	FORCEINLINE const FName& GetVoxelName(const FIntVector VoxelGridLocation) const
	{
		if (VoxelGridLocation.GetMin() < 0) return ContainerSetting.InvisibleName;

		int32 ChuckIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X / ContainerSetting.VoxelGridSize.X, VoxelGridLocation.Y / ContainerSetting.VoxelGridSize.Y, VoxelGridLocation.Z / ContainerSetting.VoxelGridSize.Z), ContainerSetting.ChuckGridSize);
		int32 VoxelIndex = ULFPGridLibrary::GridLocationToIndex(FIntVector(VoxelGridLocation.X % ContainerSetting.VoxelGridSize.X, VoxelGridLocation.Y % ContainerSetting.VoxelGridSize.Y, VoxelGridLocation.Z % ContainerSetting.VoxelGridSize.Z), ContainerSetting.VoxelGridSize);

		return IsChuckIndexValid(ChuckIndex) ? ChuckData[ChuckIndex].VoxelData[VoxelIndex] : ContainerSetting.InvisibleName;
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

	FORCEINLINE bool IsVoxelVisibleByName(const FName VoxelName) const
	{
		return VoxelName != ContainerSetting.InvisibleName;
	}

public: /* Function For Prepare Render Component To Use Container Data */

	template <typename UserClass, typename Func>
	FORCEINLINE void ConnectVoxelUpdateEvent(const int32 ChuckIndex, UserClass* InUserObject, Func InFunc)
	{
		check(ChuckData.IsValidIndex(ChuckIndex));

		ChuckData[ChuckIndex].Connect(InUserObject, InFunc);
	}

	FORCEINLINE void InitializeOrUpdateChuck(const int32 ChuckIndex)
	{
		check(IsChuckIndexValid(ChuckIndex));

		if (ChuckData[ChuckIndex].IsInitialized() == false)
		{
			ChuckData[ChuckIndex].InitChuckData(ContainerSetting.VoxelLength);
		}

		ChuckData[ChuckIndex].SendUpdateEvent();
		
		VoxelChuckUpdateEvent.Broadcast(ChuckIndex);
	}

public: /* Function For External Blueprint Or C++ To Use */

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE int32 GetContainerSize();

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void UpdateChuck();

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void MarkChuckForUpdate(const int32 ChuckIndex);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE bool SetupVoxelData(UDataTable* NewVoxelAttributeTable, const FLFPVoxelContainerSettingV2 NewSetting);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE bool IsChuckInitialized(const int32 ChuckIndex) const;

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetVoxelGridData(const FIntVector VoxelGridLocation, const FName& VoxelAttributeName, const bool bUpdateMesh = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetVoxelGridDataList(const TArray<FIntVector>& VoxelGridLocationList, const FName& VoxelAttributeName, const bool bUpdateMesh = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetChuckGridData(const int32 ChuckIndex, const FName& VoxelAttributeName, const bool bUpdateMesh = true);
};

