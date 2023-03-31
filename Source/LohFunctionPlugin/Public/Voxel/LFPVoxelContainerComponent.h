// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "LFPVoxelContainerComponent.generated.h"

USTRUCT( BlueprintType )
struct FLFPVoxelContainerSetting
{
	GENERATED_BODY()

public:

	FLFPVoxelContainerSetting() {}

	FLFPVoxelContainerSetting(FIntVector NewChuckGridSize, FIntVector NewSaveGridSize) :
		RegionGridSize(NewSaveGridSize), ChuckGridSize(NewChuckGridSize), VoxelGridSize(16) {}

private:

	UPROPERTY() int32 RegionLength = 1;

	UPROPERTY() int32 ChuckLength = 1;

	UPROPERTY() int32 VoxelLength = 1;

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelContainerSetting | Setting")
		FIntVector RegionGridSize = FIntVector(1);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelContainerSetting | Setting")
		FIntVector ChuckGridSize = FIntVector(1);

	/* Size Of Voxel Inside Of A Chuck */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelContainerSetting | Setting")
		FIntVector VoxelGridSize = FIntVector(16);

public:

	FORCEINLINE void InitSetting()
	{
		if (RegionGridSize.GetMin() <= 0) RegionGridSize = FIntVector(1);
		if (ChuckGridSize.GetMin() <= 0) ChuckGridSize = FIntVector(1);
		if (VoxelGridSize.GetMin() <= 0) VoxelGridSize = FIntVector(1);

		RegionLength = RegionGridSize.X * RegionGridSize.Y * RegionGridSize.Z;
		ChuckLength = ChuckGridSize.X * ChuckGridSize.Y * ChuckGridSize.Z;
		VoxelLength = VoxelGridSize.X * VoxelGridSize.Y * VoxelGridSize.Z;
	}

	FORCEINLINE int32 GetRegionLength() const
	{
		return RegionLength;
	}

	FORCEINLINE int32 GetChuckLength() const
	{
		return ChuckLength;
	}

	FORCEINLINE int32 GetVoxelLength() const
	{
		return VoxelLength;
	}

};

USTRUCT(BlueprintType)
struct FLFPVoxelPaletteData
{
	GENERATED_BODY()

	FLFPVoxelPaletteData() {}

	FLFPVoxelPaletteData(const FName& NewVoxelName, const TArray<FName>& NewVoxelTag) : VoxelName(NewVoxelName), VoxelTag(NewVoxelTag), RefCounter(1) {}

public:

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelPaletteData")
		FName VoxelName = FName();

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelPaletteData")
		TArray<FName> VoxelTag = TArray<FName>();

private:

	UPROPERTY(SaveGame)
		uint32 RefCounter = 0;

public:

	FORCEINLINE bool IsNone() const
	{
		return VoxelName.IsNone();
	}

	FORCEINLINE bool CanRemove() const
	{
		return RefCounter == 0;
	}

	FORCEINLINE void SetCounter(const uint32 NewRef)
	{
		RefCounter = NewRef;
	}

	FORCEINLINE void IncreaseCounter()
	{
		RefCounter++;
	}

	FORCEINLINE bool DecreaseCounter()
	{
		if (RefCounter > 0) RefCounter--;

		return RefCounter == 0;
	}

	FORCEINLINE bool operator==(const FLFPVoxelPaletteData& Other) const
	{
		return VoxelName == Other.VoxelName && VoxelTag == Other.VoxelTag;
	}
};

FORCEINLINE uint32 GetTypeHash(const FLFPVoxelPaletteData& Other)
{
	return FCrc::MemCrc32(&Other, sizeof(FLFPVoxelPaletteData));
}



USTRUCT()
struct FLFPVoxelChuckData
{
	GENERATED_BODY()

private:

	UPROPERTY(SaveGame)
		TArray<FLFPVoxelPaletteData> VoxelPaletteList = {};

	UPROPERTY(SaveGame)
		TArray<int32> OpenPaletteIndexList = {};

	UPROPERTY(SaveGame)
		TArray<uint32> VoxelIndexList = TArray<uint32>();

	UPROPERTY(SaveGame)
		uint32 VoxelEncodeBtye = 0;

private:

	/** Read / Write Bit Function */

	FORCEINLINE FBitReference GetIndexRef(TArray<uint32>& VoxelIndexListRef, const int32 Index)
	{
		return FBitReference(
			VoxelIndexListRef.GetData()[Index / NumBitsPerDWORD],
			1 << (Index & (NumBitsPerDWORD - 1))
		);
	}

	FORCEINLINE FConstBitReference GetIndexConstRef(const TArray<uint32>& VoxelIndexListRef, const int32 Index) const
	{
		return FConstBitReference(
			VoxelIndexListRef.GetData()[Index / NumBitsPerDWORD],
			1 << (Index & (NumBitsPerDWORD - 1))
		);
	}

	/** Palette Function */

	FORCEINLINE int32 FindOrAddPalette(const FLFPVoxelPaletteData& NewVoxelPalette, const bool bIncreaseCounter, const bool bResizePalette)
	{
		int32 PaletteIndex = VoxelPaletteList.Find(NewVoxelPalette);

		if (PaletteIndex == INDEX_NONE)
		{
			if (OpenPaletteIndexList.IsEmpty() == false) 
			{
				PaletteIndex = OpenPaletteIndexList.Pop();

				VoxelPaletteList[PaletteIndex] = NewVoxelPalette;
			}
			else
			{
				PaletteIndex = VoxelPaletteList.Add(NewVoxelPalette);
			}
		}

		VoxelPaletteList[PaletteIndex].IncreaseCounter();

		if (bResizePalette) ResizePalette();

		return PaletteIndex;
	}

	FORCEINLINE void RemovePalette(const int32 PaletteIndex, const bool bResizePalette)
	{
		check(VoxelPaletteList[PaletteIndex].CanRemove() == false);

		if (VoxelPaletteList[PaletteIndex].DecreaseCounter() == false) return;

		OpenPaletteIndexList.Add(PaletteIndex);

		for (int32 Index = VoxelPaletteList.Num() - 1; Index >= 0; --Index)
		{
			if (VoxelPaletteList[Index].CanRemove())
			{
				VoxelPaletteList.RemoveAt(Index);

				OpenPaletteIndexList.Remove(Index);

				continue;
			}

			break;
		}

		if (bResizePalette) ResizePalette();

		return;
	}

	/** Resize Function */

	FORCEINLINE void ResizeBitArray(const uint32 NewSize)
	{
		if (NewSize == VoxelEncodeBtye) return;

		const TArray<uint32> OldVoxelIndexList = VoxelIndexList;

		const uint32 OldSize = VoxelEncodeBtye;

		VoxelEncodeBtye = NewSize;

		const int32 VoxelLength = 4096;
		const int32 ChuckBitSize = VoxelLength / 32;

		VoxelIndexList.Init(0, (NewSize * ChuckBitSize) + 1);

		if (OldSize == 0) return;

		for (int32 VoxelIndex = 0; VoxelIndex < VoxelLength; VoxelIndex++)
		{
			for (uint32 EncodeIndex = 0; EncodeIndex < OldSize; EncodeIndex++)
			{
				const int32 OldBitIndex = (VoxelIndex * OldSize) + EncodeIndex;
				const int32 NewBitIndex = (VoxelIndex * VoxelEncodeBtye) + EncodeIndex;

				GetIndexRef(VoxelIndexList, NewBitIndex) = GetIndexConstRef(OldVoxelIndexList, OldBitIndex);
			}
		}
	}

	FORCEINLINE void ResizePalette()
	{
		check(IsInitialized());

		const int32 PaletteSize = VoxelPaletteList.Num();

		for (uint8 NewEncodeSize = 0; NewEncodeSize < NumBitsPerDWORD; NewEncodeSize++)
		{
			if (PaletteSize < 1 << NewEncodeSize)
			{
				ResizeBitArray(NewEncodeSize);

				break;
			}
		}

		return;
	}

public:

	/** Check Function */

	FORCEINLINE bool IsInitialized() const
	{
		return VoxelPaletteList.IsEmpty() == false;
	}

	/** Init Function */

	FORCEINLINE void InitChuckData(const FLFPVoxelPaletteData& VoxelPalette)
	{
		VoxelPaletteList.Init(VoxelPalette, 1);

		VoxelPaletteList[0].SetCounter(4096);

		VoxelEncodeBtye = 0;

		ResizePalette();
	}

	/** Read / Write Function */

	FORCEINLINE void SetIndexData(const int32 VoxelIndex, const FLFPVoxelPaletteData& NewData)
	{
		check(VoxelIndex >= 0 && VoxelIndex < 4096 && VoxelEncodeBtye > 0);

		RemovePalette(GetPaletteIndex(VoxelIndex), false);

		const int32 NewIndex = FindOrAddPalette(NewData, true, true);

		for (uint32 EncodeIndex = 0; EncodeIndex < VoxelEncodeBtye; EncodeIndex++)
		{
			const int32 BitIndex = (VoxelIndex * VoxelEncodeBtye) + EncodeIndex;

			GetIndexRef(VoxelIndexList, BitIndex) = FConstBitReference(NewIndex, 1 << EncodeIndex);
		}
	}

	FORCEINLINE const FLFPVoxelPaletteData& GetIndexData(const int32 VoxelIndex) const
	{
		return VoxelPaletteList[GetPaletteIndex(VoxelIndex)];
	}

	FORCEINLINE int32 GetPaletteIndex(const int32 VoxelIndex) const
	{
		check(VoxelIndex >= 0 && VoxelIndex < 4096 && VoxelEncodeBtye > 0);

		uint32 OutIndex = 0;

		for (uint32 EncodeIndex = 0; EncodeIndex < VoxelEncodeBtye; EncodeIndex++)
		{
			const int32 BitIndex = (VoxelIndex * VoxelEncodeBtye) + EncodeIndex;

			FBitReference(OutIndex, 1 << EncodeIndex) = GetIndexConstRef(VoxelIndexList, BitIndex);
		}

		return OutIndex;
	}

	FORCEINLINE const TArray<FLFPVoxelPaletteData>& GetVoxelPaletteList() const
	{
		return VoxelPaletteList;
	}

	/** Debug Function */

	FORCEINLINE uint8 GetEncodeLength() const
	{
		return VoxelEncodeBtye;
	}

	FORCEINLINE int32 GetPaletteLength() const
	{
		return VoxelPaletteList.Num();
	}

};

USTRUCT()
struct FLFPVoxelRegionData
{
	GENERATED_BODY()

public:

	UPROPERTY(SaveGame)
		TArray<FLFPVoxelChuckData> ChuckData = {};

public:

	FORCEINLINE bool IsInitialized() const
	{
		return ChuckData.IsEmpty() == false;
	}

	FORCEINLINE void InitRegionData(const int32 ChuckLength)
	{
		ChuckData.Init(FLFPVoxelChuckData(), ChuckLength);
	}

};

USTRUCT()
struct FLFPChuckUpdateAction
{
	GENERATED_BODY()

public:

	UPROPERTY()
		TMap<FLFPVoxelPaletteData, FLFPVoxelPaletteData> ChangePalette = TMap<FLFPVoxelPaletteData, FLFPVoxelPaletteData>();

public: // Operator

	FLFPChuckUpdateAction& operator+=(const FLFPChuckUpdateAction& Other)
	{
		ChangePalette.Append(Other.ChangePalette);
	
		return *this;
	}
};


DECLARE_DELEGATE_OneParam(FOnVoxelChuckUpdate, const FLFPChuckUpdateAction& ChuckUpdateAction);

USTRUCT()
struct FLFPVoxelChuckDelegate
{
	GENERATED_BODY()

public:

	// Update Event For Notify Chuck On Voxel Update
	FOnVoxelChuckUpdate VoxelChuckUpdateEvent;

};

USTRUCT()
struct FLFPVoxelUpdateAction
{
	GENERATED_BODY()

public:

	UPROPERTY()
		TMap<int32, FLFPVoxelPaletteData> ChangePalette = TMap<int32, FLFPVoxelPaletteData>();

public: // Operator

	FLFPVoxelUpdateAction& operator+=(const FLFPVoxelUpdateAction& Other)
	{
		ChangePalette.Append(Other.ChangePalette);

		return *this;
	}
};


UCLASS( Blueprintable, meta = (BlueprintSpawnableComponent), ClassGroup = (LFPlugin) )
class LOHFUNCTIONPLUGIN_API ULFPVoxelContainerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPVoxelContainerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public: /** Debugging */

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelContainerComponent | Function")
		FORCEINLINE FString MemorySize(const int32 SaveFileAmount, const int32 ChuckAmount, const int32 VoxelAmount) const;

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelContainerComponent | Function")
		FORCEINLINE FString Test() const;

public: /** Checker */

	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Checker")
		FORCEINLINE bool IsRegionInitialized(const int32 RegionIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Checker")
		FORCEINLINE bool IsChuckInitialized(const int32 RegionIndex, const int32 ChuckIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Checker")
		FORCEINLINE bool IsVoxelPositionValid(const int32 RegionIndex, const int32 ChuckIndex, const int32 VoxelIndex) const;

public: /** Setter */

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelContainerComponent | Setter")
		FORCEINLINE bool SetVoxelPalette(const int32 RegionIndex, const int32 ChuckIndex, const int32 VoxelIndex, const FLFPVoxelPaletteData& VoxelPalette);

public: /** Getter */

	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Getter")
		FORCEINLINE FLFPVoxelPaletteData GetVoxelPalette(const int32 RegionIndex, const int32 ChuckIndex, const int32 VoxelIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Getter")
		FORCEINLINE TArray<FLFPVoxelPaletteData> GetVoxelPaletteList(const int32 RegionIndex, const int32 ChuckIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Getter")
		FORCEINLINE int32 GetVoxelPaletteIndex(const int32 RegionIndex, const int32 ChuckIndex, const int32 VoxelIndex) const;

public: /** Can be override to provide custom behavir */

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelContainerComponent | Chuck")
		virtual void InitializeRegion(const int32 RegionIndex);

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelContainerComponent | Chuck")
		virtual void InitializeChuck(const int32 RegionIndex, const int32 ChuckIndex);

//public: /** Chuck Request */
//
//	/** Request chuck info on chuck spawn */
//	FORCEINLINE void RequestRenderChuck(const int32 RegionIndex, const int32 ChuckIndex, FLFPVoxelChuckDelegate& ChuckDelegate);
//
//	/** Release chuck info on chuck destroy */
//	FORCEINLINE void ReleaseRenderChuck(const int32 RegionIndex, const int32 ChuckIndex);
//
//	/** Request Render Data and lock write access */
//	FORCEINLINE void RequestRenderData(const int32 RegionIndex, const int32 ChuckIndex, FLFPVoxelContainerSetting& ChuckSetting);
//
//	/** Release write access */
//	FORCEINLINE void ReleaseRenderData(const int32 RegionIndex, const int32 ChuckIndex);

protected: /** Function for updating chuck and data */

	FORCEINLINE void UpdateChuckState();

	FORCEINLINE bool UpdateChuckData();

public: /** Read and write lock */

	FRWLock ContainerThreadLock;

protected: // Initialize Data

	/** What setting this component use when saving the voxel */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPVoxelContainerComponent | Setting")
		FLFPVoxelContainerSetting Setting;

protected:  // Runtime Data

	/** This store the chuck */
	UPROPERTY(SaveGame) 
		TArray<FLFPVoxelRegionData> RegionDataList;

	/** This store chuck delegate to call */
	UPROPERTY() 
		TMap<FIntPoint, FLFPVoxelChuckDelegate> ChuckDelegateList;

	/** This store future chuck update data to apply */
	UPROPERTY() 
		TMap<FIntPoint, FLFPVoxelUpdateAction> ChuckUpdateDataList;

	/** This store future chuck event data to send */
	UPROPERTY()
		TMap<FIntPoint, FLFPChuckUpdateAction> ChuckUpdateStateList;
};
