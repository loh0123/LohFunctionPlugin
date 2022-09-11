// MIT License
// 
// Copyright(c) 2022 loh0123
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright noticeand this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Math/LFPGridLibrary.h"
#include "LFPVoxelContainer.generated.h"

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

	FORCEINLINE void InitChuckData(const int32 VoxelLength, const FName& VoxelName)
	{
		VoxelData.Init(VoxelName, VoxelLength);
	}

	FORCEINLINE void SetVoxel(const int32 VoxelIndex, const FName& VoxelName)
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

	FORCEINLINE FIntVector GetChuckStartVoxelLocation(const int32 ChuckIndex) const
	{
		check(IsChuckIndexValid(ChuckIndex));

		const FIntVector ChuckGridLocation = ULFPGridLibrary::IndexToGridLocation(ChuckIndex, ContainerSetting.ChuckGridSize);

		return FIntVector(ChuckGridLocation.X * ContainerSetting.VoxelGridSize.X, ChuckGridLocation.Y * ContainerSetting.VoxelGridSize.Y, ChuckGridLocation.Z * ContainerSetting.VoxelGridSize.Z);
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

	/* This Is Use To Access Voxel Visible Outside Of The Local Chuck */
	FORCEINLINE bool IsVoxelVisible(const FLFPVoxelGridIndex VoxelGridIndex) const
	{
		return GetVoxelName(VoxelGridIndex) != ContainerSetting.InvisibleName;
	}

	/* This Is Use To Access Voxel Visible On Local Chuck */
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

	FORCEINLINE void InitializeOrUpdateChuck(const int32 ChuckIndex, const FName& VoxelName)
	{
		check(IsChuckIndexValid(ChuckIndex));

		FRWScopeLock WriteLock(GetContainerThreadLock(), SLT_Write);

		if (ChuckData[ChuckIndex].IsInitialized() == false)
		{
			ChuckData[ChuckIndex].InitChuckData(ContainerSetting.VoxelLength, VoxelName);
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
		FORCEINLINE FLFPVoxelGridIndex VoxelGridLocationToVoxelGridIndex(const FIntVector VoxelGridLocation) const;

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetVoxelGridData(const FLFPVoxelGridIndex VoxelGridIndex, const FName VoxelAttributeName, const bool bUpdateMesh = true, const bool bInitializeChuck = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetVoxelGridDataList(const TArray<FLFPVoxelGridIndex>& VoxelGridIndexList, const FName VoxelAttributeName, const bool bUpdateMesh = true, const bool bInitializeChuck = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetChuckGridData(const int32 ChuckIndex, const FName VoxelAttributeName, const bool bUpdateMesh = true, const bool bInitializeChuck = true);
};

