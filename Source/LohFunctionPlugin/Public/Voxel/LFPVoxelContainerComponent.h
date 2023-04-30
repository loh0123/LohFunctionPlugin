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

	FLFPVoxelContainerSetting() {}

	FLFPVoxelContainerSetting(const FIntVector NewRegionGridSize, const FIntVector NewChuckGridSize, const FIntVector NewVoxelGridSize, const FVector NewVoxelHalfSize)
		: RegionGridSize(NewRegionGridSize), ChuckGridSize(NewChuckGridSize), VoxelGridSize(NewVoxelGridSize), VoxelHalfSize(NewVoxelHalfSize)
	{ InitSetting(); }

private:

	UPROPERTY() int32 RegionLength = 1;

	UPROPERTY() int32 ChuckLength = 1;

	UPROPERTY() int32 VoxelLength = 1;

	UPROPERTY() FVector VoxelHalfBounds = FVector::ZeroVector;

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere,		Category = "VoxelContainerSetting | Setting")
		FIntVector RegionGridSize = FIntVector(1);

	UPROPERTY(BlueprintReadOnly, EditAnywhere,		Category = "VoxelContainerSetting | Setting")
		FIntVector ChuckGridSize = FIntVector(1);

	/* Size Of Voxel Inside Of A Chuck */
	UPROPERTY(BlueprintReadOnly, EditAnywhere,		Category = "VoxelContainerSetting | Setting")
		FIntVector VoxelGridSize = FIntVector(1);

	UPROPERTY(BlueprintReadOnly, EditAnywhere,		Category = "VoxelContainerSetting | Setting")
		FVector VoxelHalfSize = FVector(50.0f);

public:

	FORCEINLINE void InitSetting()
	{
		if (RegionGridSize.GetMin() <= 0) RegionGridSize = FIntVector(1);
		if (ChuckGridSize.GetMin() <= 0) ChuckGridSize = FIntVector(1);
		if (VoxelGridSize.GetMin() <= 0) VoxelGridSize = FIntVector(1);
		if (VoxelHalfSize.GetMin() <= 0) VoxelHalfSize = FVector(50.0f);

		RegionLength = RegionGridSize.X * RegionGridSize.Y * RegionGridSize.Z;
		ChuckLength = ChuckGridSize.X * ChuckGridSize.Y * ChuckGridSize.Z;
		VoxelLength = VoxelGridSize.X * VoxelGridSize.Y * VoxelGridSize.Z;
		VoxelHalfBounds = VoxelHalfSize * FVector(VoxelGridSize);
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

	FORCEINLINE FVector GetVoxelHalfBounds() const
	{
		return VoxelHalfBounds;
	}

	FORCEINLINE FIntVector GetRegionGrid() const
	{
		return RegionGridSize;
	}

	FORCEINLINE FIntVector GetChuckGrid() const
	{
		return ChuckGridSize;
	}

	FORCEINLINE FIntVector GetVoxelGrid() const
	{
		return VoxelGridSize;
	}

	FORCEINLINE FVector GetVoxelHalfSize() const
	{
		return VoxelHalfSize;
	}
};

USTRUCT(BlueprintType)
struct FLFPVoxelPaletteData
{
	GENERATED_BODY()

	FLFPVoxelPaletteData() {}

	FLFPVoxelPaletteData(const FName& NewVoxelName, const TArray<FName>& NewVoxelTag) : VoxelName(NewVoxelName), VoxelTag(NewVoxelTag), RefCounter(1) {}

public:

	static FLFPVoxelPaletteData EmptyData;

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

	FORCEINLINE bool operator!=(const FLFPVoxelPaletteData& Other) const
	{
		return VoxelName != Other.VoxelName || VoxelTag != Other.VoxelTag;
	}
};

//FORCEINLINE uint32 GetTypeHash(const FLFPVoxelPaletteData& Other)
//{
//	return FCrc::MemCrc32(&Other, sizeof(FLFPVoxelPaletteData));
//}



USTRUCT(BlueprintType)
struct FLFPVoxelChuckData
{
	GENERATED_BODY()

private:

	UPROPERTY(SaveGame)
		TArray<FLFPVoxelPaletteData> PaletteList = {};

	UPROPERTY(SaveGame)
		TArray<int32> OpenPaletteList = {};

	UPROPERTY(SaveGame)
		TArray<uint32> IndexList = TArray<uint32>();

	UPROPERTY(SaveGame)
		uint32 EncodeBtye = 0;

	UPROPERTY(SaveGame)
		uint32 IndexSize = 0;

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
		int32 PaletteIndex = PaletteList.Find(NewVoxelPalette);

		if (PaletteIndex == INDEX_NONE)
		{
			if (OpenPaletteList.IsEmpty() == false) 
			{
				PaletteIndex = OpenPaletteList.Pop();

				PaletteList[PaletteIndex] = NewVoxelPalette;
			}
			else
			{
				PaletteIndex = PaletteList.Add(NewVoxelPalette);
			}
		}

		PaletteList[PaletteIndex].IncreaseCounter();

		if (bResizePalette) ResizePalette();

		return PaletteIndex;
	}

	FORCEINLINE void RemovePalette(const int32 PaletteIndex, const bool bResizePalette)
	{
		check(PaletteList[PaletteIndex].CanRemove() == false);

		if (PaletteList[PaletteIndex].DecreaseCounter() == false) return;

		/** Sort And Push Into Open Index List */
		if (OpenPaletteList.Num() > 0)
		{
			for (int32 Index = OpenPaletteList.Num() - 1; Index >= 0; Index--)
			{
				if (OpenPaletteList[Index] < PaletteIndex) continue;

				OpenPaletteList.EmplaceAt(Index, PaletteIndex);

				break;
			}
		}
		else
		{
			OpenPaletteList.Emplace(PaletteIndex);
		}

		for (int32 Index = PaletteList.Num() - 1; Index >= 0; --Index)
		{
			if (PaletteList[Index].CanRemove())
			{
				PaletteList.RemoveAt(Index);

				OpenPaletteList.Remove(Index);

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
		if (NewSize == EncodeBtye) return;

		const TArray<uint32> OldVoxelIndexList = IndexList;

		const uint32 OldSize = EncodeBtye;

		EncodeBtye = NewSize;

		const int32 ChuckBitSize = FMath::DivideAndRoundUp(IndexSize, uint32(32));

		IndexList.Init(0, (NewSize * ChuckBitSize) + 1);

		if (OldSize == 0) return;

		for (uint32 VoxelIndex = 0; VoxelIndex < IndexSize; VoxelIndex++)
		{
			for (uint32 EncodeIndex = 0; EncodeIndex < OldSize; EncodeIndex++)
			{
				const int32 OldBitIndex = int32((VoxelIndex * OldSize) + EncodeIndex);
				const int32 NewBitIndex = int32((VoxelIndex * EncodeBtye) + EncodeIndex);

				GetIndexRef(IndexList, NewBitIndex) = GetIndexConstRef(OldVoxelIndexList, OldBitIndex);
			}
		}
	}

	FORCEINLINE void ResizePalette()
	{
		check(IsInitialized());

		const int32 PaletteSize = PaletteList.Num();

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
		return PaletteList.IsEmpty() == false;
	}

	/** Init Function */

	FORCEINLINE void InitChuckData(const FLFPVoxelPaletteData& VoxelPalette, const uint32 NewIndexSize)
	{
		OpenPaletteList.Empty();

		IndexSize = NewIndexSize;

		PaletteList.Init(VoxelPalette, 1);
		PaletteList[0].SetCounter(NewIndexSize);

		EncodeBtye = 0;

		ResizePalette();
	}

	/** Read / Write Function */

	FORCEINLINE void SetIndexData(const int32 VoxelIndex, const FLFPVoxelPaletteData& NewData)
	{
		check(VoxelIndex >= 0 && VoxelIndex < int32(IndexSize) && EncodeBtye > 0);

		RemovePalette(GetPaletteIndex(VoxelIndex), false);

		const int32 NewIndex = FindOrAddPalette(NewData, true, true);

		for (uint32 EncodeIndex = 0; EncodeIndex < EncodeBtye; EncodeIndex++)
		{
			const int32 BitIndex = (VoxelIndex * EncodeBtye) + EncodeIndex;

			GetIndexRef(IndexList, BitIndex) = FConstBitReference(NewIndex, 1 << EncodeIndex);
		}
	}

	FORCEINLINE const FLFPVoxelPaletteData& GetIndexData(const int32 VoxelIndex) const
	{
		return PaletteList[GetPaletteIndex(VoxelIndex)];
	}

	FORCEINLINE int32 GetPaletteIndex(const int32 VoxelIndex) const
	{
		check(VoxelIndex >= 0 && VoxelIndex < int32(IndexSize) && EncodeBtye > 0);

		uint32 OutIndex = 0;

		for (uint32 EncodeIndex = 0; EncodeIndex < EncodeBtye; EncodeIndex++)
		{
			const int32 BitIndex = (VoxelIndex * EncodeBtye) + EncodeIndex;

			FBitReference(OutIndex, 1 << EncodeIndex) = GetIndexConstRef(IndexList, BitIndex);
		}

		return OutIndex;
	}

	FORCEINLINE const TArray<FLFPVoxelPaletteData>& GetPaletteList() const
	{
		return PaletteList;
	}

	/** Debug Function */

	FORCEINLINE uint8 GetEncodeLength() const
	{
		return EncodeBtye;
	}

	FORCEINLINE int32 GetPaletteLength() const
	{
		return PaletteList.Num();
	}

	FORCEINLINE int32 GetIndexSize() const
	{
		return IndexSize;
	}

};

USTRUCT(BlueprintType)
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

USTRUCT(BlueprintType)
struct FLFPChuckUpdateAction
{
	GENERATED_BODY()

	FLFPChuckUpdateAction() : bIsVoxelNameDirty(false), bIsVoxelTagDirty(false) {}

public:

	UPROPERTY() uint8 bIsVoxelNameDirty : 1;

	UPROPERTY() uint8 bIsVoxelTagDirty : 1;

public: // Operator

	FLFPChuckUpdateAction& operator+=(const FLFPChuckUpdateAction& Other)
	{
		if (bIsVoxelNameDirty == false) bIsVoxelNameDirty = Other.bIsVoxelNameDirty;
		if (bIsVoxelTagDirty == false) bIsVoxelTagDirty = Other.bIsVoxelNameDirty;

		return *this;
	}
};


DECLARE_DELEGATE_OneParam(FOnVoxelChuckUpdate, const FLFPChuckUpdateAction&);

USTRUCT()
struct FLFPVoxelChuckDelegate
{
	GENERATED_BODY()

public:

	// Update Event For Notify Chuck On Voxel Update
	FOnVoxelChuckUpdate VoxelChuckUpdateEvent;

};

USTRUCT(BlueprintType)
struct FLFPVoxelUpdateAction
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "LFPVoxelUpdateAction")
		TMap<int32, FLFPVoxelPaletteData> ChangePalette = TMap<int32, FLFPVoxelPaletteData>();

public: // Operator

	FLFPVoxelUpdateAction& operator+=(const FLFPVoxelUpdateAction& Other)
	{
		ChangePalette.Append(Other.ChangePalette);

		return *this;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnVoxelContainerChuckUpdate, const int32, RegionIndex, const int32, ChuckIndex, const FLFPVoxelUpdateAction&, VoxelUpdateAction);


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
		FORCEINLINE FString Test();

public: /** Checker */

	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Checker")
		FORCEINLINE bool IsRegionInitialized(const int32 RegionIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Checker")
		FORCEINLINE bool IsChuckInitialized(const int32 RegionIndex, const int32 ChuckIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Checker")
		FORCEINLINE bool IsRegionPositionValid(const int32 RegionIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Checker")
		FORCEINLINE bool IsChuckPositionValid(const int32 RegionIndex, const int32 ChuckIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Checker")
		FORCEINLINE bool IsVoxelPositionValid(const int32 RegionIndex, const int32 ChuckIndex, const int32 VoxelIndex) const;

public: /** Setter */

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelContainerComponent | Setter")
		FORCEINLINE bool SetVoxelPalette(const int32 RegionIndex, const int32 ChuckIndex, const int32 VoxelIndex, const FLFPVoxelPaletteData& VoxelPalette);

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelContainerComponent | Setter")
		FORCEINLINE bool SetVoxelChuckData(const int32 RegionIndex, const int32 ChuckIndex, const FLFPVoxelChuckData& ChuckData);

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelContainerComponent | Setter")
		FORCEINLINE bool InitializeVoxelChuck(const int32 RegionIndex, const int32 ChuckIndex);

public: /** Getter */

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelContainerComponent | Getter")
		FORCEINLINE FLFPVoxelChuckData GetVoxelChuckData(const int32 RegionIndex, const int32 ChuckIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Getter")
		FORCEINLINE FLFPVoxelPaletteData GetVoxelPalette(const int32 RegionIndex, const int32 ChuckIndex, const int32 VoxelIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Getter")
		FORCEINLINE TArray<FLFPVoxelPaletteData> GetVoxelPaletteList(const int32 RegionIndex, const int32 ChuckIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Getter")
		FORCEINLINE int32 GetVoxelPaletteIndex(const int32 RegionIndex, const int32 ChuckIndex, const int32 VoxelIndex) const;


	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Getter")
		FORCEINLINE FIntVector ToVoxelGlobalPosition(const FIntVector VoxelGlobalIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Getter")
		FORCEINLINE FIntVector ToVoxelGlobalIndex(const FIntVector VoxelGlobalPosition) const;

public: /** C++ Getter */

	FORCEINLINE const FLFPVoxelContainerSetting& GetSetting() const { return Setting; }

	FORCEINLINE const FLFPVoxelPaletteData& GetVoxelPaletteRef(const int32 RegionIndex, const int32 ChuckIndex, const int32 VoxelIndex) const;


protected: /** Can be override to provide custom behavir */

	UFUNCTION()
		virtual void InitializeRegion(const int32 RegionIndex);

	UFUNCTION()
		virtual void InitializeChuck(const int32 RegionIndex, const int32 ChuckIndex);

public: /** Chuck Request */

	/** Request chuck info on chuck spawn */
	UFUNCTION() 
		FORCEINLINE bool AddRenderChuck(const int32 RegionIndex, const int32 ChuckIndex, FLFPVoxelChuckDelegate& Delegate);

	/** Release chuck info on chuck destroy */
	UFUNCTION() 
		FORCEINLINE void RemoveRenderChuck(const int32 RegionIndex, const int32 ChuckIndex);

protected: /** Function for updating chuck and data */

	FORCEINLINE bool UpdateChuckState();

	FORCEINLINE bool UpdateChuckData();

public: /** Delegate */

	UPROPERTY(BlueprintAssignable, Category = "LFPVoxelContainerComponent | Delegate")
		FOnVoxelContainerChuckUpdate OnVoxelContainerChuckUpdate;

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
