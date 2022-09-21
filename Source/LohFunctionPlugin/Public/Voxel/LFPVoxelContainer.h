// Copyright (c) 2022 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Math/LFPGridLibrary.h"
#include "LFPVoxelContainer.generated.h"

USTRUCT(BlueprintType)
struct FLFPVoxelChuckInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelChuckInfo")
		int32 ChuckIndex = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelChuckInfo")
		FIntVector StartVoxelLocation = FIntVector::NoneValue;
};

USTRUCT(BlueprintType)
struct FLFPVoxelGridIndex
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelGridIndex")
		int32 ChuckIndex = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelGridIndex")
		int32 VoxelIndex = INDEX_NONE;
};

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

DECLARE_DELEGATE(FOnVoxelChuckColorUpdate);

USTRUCT()
struct FLFPVoxelChuckDataV2
{
	GENERATED_USTRUCT_BODY()

	FLFPVoxelChuckDataV2() {}

	FLFPVoxelChuckDataV2(const FLFPVoxelChuckDataV2& Data) : VoxelData(Data.VoxelData) {}

public:

	UPROPERTY() TArray<FName> VoxelData = {};

	UPROPERTY() TArray<FColor> VoxelColorData = {};

public:

	// Update Event For Notify Chuck On Voxel Update
	FOnVoxelChuckUpdate VoxelChuckUpdateEvent;

	// Update Event For Notify Chuck On Change Of Color
	FOnVoxelChuckColorUpdate VoxelChuckColorUpdateEvent;

public:

	FORCEINLINE bool IsInitialized() const
	{
		return VoxelData.IsEmpty() == false;
	}

	FORCEINLINE void InitChuckData(const int32 VoxelLength, const FName& VoxelName)
	{
		VoxelData.Init(VoxelName, VoxelLength);
		VoxelColorData.Init(FColor(0), VoxelLength);
	}

	FORCEINLINE void SetVoxel(const int32 VoxelIndex, const FName& VoxelName)
	{
		check(VoxelData.IsValidIndex(VoxelIndex));

		VoxelData[VoxelIndex] = VoxelName;
	}

	FORCEINLINE void SetVoxelColor(const int32 VoxelIndex, const FColor& VoxelColor)
	{
		check(VoxelData.IsValidIndex(VoxelIndex));

		VoxelColorData[VoxelIndex] = VoxelColor;
	}

	template <typename UserClass, typename Func01, typename Func02>
	FORCEINLINE void Connect(UserClass* InUserObject, Func01 InVoxelFunc, Func02 InColorFunc)
	{
		VoxelChuckUpdateEvent.BindUObject(InUserObject, InVoxelFunc);
		VoxelChuckColorUpdateEvent.BindUObject(InUserObject, InColorFunc);
	}

	FORCEINLINE void SendUpdateEvent()
	{
		VoxelChuckUpdateEvent.ExecuteIfBound();
	}

	FORCEINLINE void SendColorUpdateEvent()
	{
		VoxelChuckColorUpdateEvent.ExecuteIfBound();
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

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelContainerSetting | Cache")
		FVector HalfRenderBound = FVector(-1.0f);

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

	/* Half Of The Size Of The Voxel Should Be Render */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelContainerSetting | Setting")
		FVector VoxelHalfSize = FVector(100);

	/* Size Of The UV This Mesh Is Render On */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelContainerSetting | Setting")
		FIntPoint VoxelUVRound = FIntPoint(1);

public:

	FORCEINLINE void InitSetting()
	{
		if (VoxelGridSize.GetMin() <= 0) VoxelGridSize = FIntVector(1);
		if (ChuckGridSize.GetMin() <= 0) ChuckGridSize = FIntVector(1);
		if (VoxelHalfSize.GetMin() <= 0) VoxelHalfSize = FVector(50.0f);
		if (VoxelUVRound.GetMin() <= 0) VoxelUVRound = FIntPoint(1);

		VoxelLength = VoxelGridSize.X * VoxelGridSize.Y * VoxelGridSize.Z;
		ChuckLength = ChuckGridSize.X * ChuckGridSize.Y * ChuckGridSize.Z;
		HalfRenderBound = VoxelHalfSize * FVector(VoxelGridSize);
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

protected:

	FRWLock ContainerThreadLock;

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

	UPROPERTY() TSet<int32> BatchChuckColorUpdateList;


protected: // Empty Data

	const FLFPVoxelAttributeV2 DefaultVoxelAttribute = FLFPVoxelAttributeV2();


public: /* Function For Render Component To Multithread */

	FORCEINLINE FRWLock& GetContainerThreadLock() { return ContainerThreadLock; }


public: /* Function For Render Component To Getting Container Init Data */

	FORCEINLINE const FLFPVoxelContainerSettingV2& GetContainerSetting() const { return ContainerSetting; }


public:  /* Function For Render Component To Check Container Data Is Safe */

	FORCEINLINE bool IsChuckIndexValid(const int32 ChuckIndex) const { return ChuckData.IsValidIndex(ChuckIndex); }

	FORCEINLINE bool IsVoxelIndexValid(const FLFPVoxelGridIndex VoxelGridIndex) const { return IsChuckIndexValid(VoxelGridIndex.ChuckIndex) ? ChuckData[VoxelGridIndex.ChuckIndex].VoxelData.IsValidIndex(VoxelGridIndex.VoxelIndex) : false; }


public: /* Function For Render Component To Get Container Data */

	FORCEINLINE FLFPVoxelChuckInfo GetChuckInfo(const int32 ChuckIndex) const
	{
		check(IsChuckIndexValid(ChuckIndex));

		FLFPVoxelChuckInfo ChuckInfo;

		const FIntVector ChuckGridLocation = ULFPGridLibrary::IndexToGridLocation(ChuckIndex, ContainerSetting.ChuckGridSize);

		ChuckInfo.ChuckIndex = ChuckIndex;
		ChuckInfo.StartVoxelLocation = FIntVector(ChuckGridLocation.X * ContainerSetting.VoxelGridSize.X, ChuckGridLocation.Y * ContainerSetting.VoxelGridSize.Y, ChuckGridLocation.Z * ContainerSetting.VoxelGridSize.Z);

		return ChuckInfo;
	}

	/* This Is Use To Access Atttribute Outside Of The Local Chuck */
	FORCEINLINE const FLFPVoxelAttributeV2& GetVoxelAttribute(const FLFPVoxelGridIndex VoxelGridIndex) const
	{
		return IsVoxelIndexValid(VoxelGridIndex) && IsChuckInitialized(VoxelGridIndex.ChuckIndex) ? GetVoxelAttributeByName(GetVoxelName(VoxelGridIndex)) : DefaultVoxelAttribute;
	}

	/* This Is Use To Access Atttribute On Local Chuck */
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

	/* This Is Use To Access Voxel Name Outside Of The Local Chuck */
	FORCEINLINE const FName& GetVoxelName(const FLFPVoxelGridIndex VoxelGridIndex) const
	{
		return IsVoxelIndexValid(VoxelGridIndex) && IsChuckInitialized(VoxelGridIndex.ChuckIndex) ? ChuckData[VoxelGridIndex.ChuckIndex].VoxelData[VoxelGridIndex.VoxelIndex] : ContainerSetting.InvisibleName;
	}

	/* This Is Use To Access Voxel Name On Local Chuck */
	FORCEINLINE const TArray<FName>& GetVoxelNameList(const int32 ChuckIndex) const
	{
		check(IsChuckIndexValid(ChuckIndex));

		return ChuckData[ChuckIndex].VoxelData;
	}

	/* This Is Use To Access Voxel Name On Local Chuck */
	FORCEINLINE const TArray<FColor>& GetVoxelColorList(const int32 ChuckIndex) const
	{
		check(IsChuckIndexValid(ChuckIndex));

		return ChuckData[ChuckIndex].VoxelColorData;
	}

	/* This Is Use To Access Voxel Visible Outside Of The Local Chuck */
	FORCEINLINE bool IsVoxelVisible(const FLFPVoxelGridIndex VoxelGridIndex, const int32 CurrentMaterialID ) const
	{
		const FName& CheckName = GetVoxelName(VoxelGridIndex);

		return CheckName != ContainerSetting.InvisibleName && GetVoxelAttributeByName(CheckName).MaterialID == CurrentMaterialID;
	}

	/* This Is Use To Access Voxel Visible On Local Chuck */
	FORCEINLINE bool IsVoxelVisibleByName(const FName& VoxelName) const
	{
		return VoxelName != ContainerSetting.InvisibleName;
	}


public: /* Function For Prepare Render Component To Use Container Data */

	template <typename UserClass, typename Func01, typename Func02>
	FORCEINLINE void ConnectVoxelUpdateEvent(const int32 ChuckIndex, UserClass* InUserObject, Func01 InVoxelFunc, Func02 InColorFunc)
	{
		check(ChuckData.IsValidIndex(ChuckIndex));

		ChuckData[ChuckIndex].Connect(InUserObject, InVoxelFunc, InColorFunc);
	}

	FORCEINLINE void InitializeOrUpdateChuck(const int32 ChuckIndex, const FName& VoxelName)
	{
		check(IsChuckIndexValid(ChuckIndex));

		FRWScopeLock WriteLock(GetContainerThreadLock(), SLT_Write);

		if (ChuckData[ChuckIndex].IsInitialized() == false)
		{
			ChuckData[ChuckIndex].InitChuckData(ContainerSetting.VoxelLength, VoxelName);
		}

		ChuckData[ChuckIndex].SendUpdateEvent();
		ChuckData[ChuckIndex].SendColorUpdateEvent();
		
		VoxelChuckUpdateEvent.Broadcast(ChuckIndex);
	}


public: /* Function For External Blueprint Or C++ To Use */

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE int32 GetContainerSize();

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void UpdateChuck();

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void UpdateChuckColor();

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void MarkChuckForUpdate(const int32 ChuckIndex, const bool bUpdateNearbyChuck = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void MarkChuckForColorUpdate(const int32 ChuckIndex);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE bool SetupVoxelData(UDataTable* NewVoxelAttributeTable, const FLFPVoxelContainerSettingV2 NewSetting);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE bool IsChuckInitialized(const int32 ChuckIndex) const;

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE FLFPVoxelGridIndex VoxelGridLocationToVoxelGridIndex(const FIntVector VoxelGridLocation) const;

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE FIntVector VoxelGridIndexToVoxelGridLocation(const FLFPVoxelGridIndex VoxelGridIndex) const;

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetVoxelGridColor(const FLFPVoxelGridIndex VoxelGridIndex, const FColor VoxelColor, const bool bInitializeChuck = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetVoxelGridData(const FLFPVoxelGridIndex VoxelGridIndex, const FName VoxelAttributeName, const bool bInitializeChuck = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetVoxelGridDataList(const TArray<FLFPVoxelGridIndex>& VoxelGridIndexList, const FName VoxelAttributeName, const bool bInitializeChuck = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetVoxelGridDataWithArea(const FLFPVoxelGridIndex FromVoxelGridIndex, const FLFPVoxelGridIndex ToVoxelGridIndex, const FName VoxelAttributeName, const bool bInitializeChuck = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetChuckGridData(const int32 ChuckIndex, const FName VoxelAttributeName, const bool bInitializeChuck = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetChuckGridDataWithHeight(const int32 ChuckIndex, const FIntPoint VoxelGridPosition, const float Height, const FName VoxelAttributeName);
};

