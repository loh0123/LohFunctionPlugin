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

	FLFPVoxelContainerSetting(FIntVector NewVoxelGridSize, FIntVector NewChuckGridSize, FIntVector NewSaveGridSize) :
		SaveGridSize(NewSaveGridSize), ChuckGridSize(NewChuckGridSize), VoxelGridSize(NewVoxelGridSize) {}

private:

	UPROPERTY() int32 SaveLength = 1;

	UPROPERTY() int32 ChuckLength = 1;

	UPROPERTY() int32 VoxelLength = 1;

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelContainerSetting | Setting")
		FIntVector SaveGridSize = FIntVector(1);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelContainerSetting | Setting")
		FIntVector ChuckGridSize = FIntVector(1);

	/* Size Of Voxel Inside Of A Chuck */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelContainerSetting | Setting")
		FIntVector VoxelGridSize = FIntVector(1);

public:

	FORCEINLINE void InitSetting()
	{
		if (SaveGridSize.GetMin() <= 0) SaveGridSize = FIntVector(1);
		if (ChuckGridSize.GetMin() <= 0) ChuckGridSize = FIntVector(1);
		if (VoxelGridSize.GetMin() <= 0) VoxelGridSize = FIntVector(1);

		SaveLength = SaveGridSize.X * SaveGridSize.Y * SaveGridSize.Z;
		ChuckLength = ChuckGridSize.X * ChuckGridSize.Y * ChuckGridSize.Z;
		VoxelLength = VoxelGridSize.X * VoxelGridSize.Y * VoxelGridSize.Z;
	}

	FORCEINLINE int32 GetSaveLength() const
	{
		return SaveLength;
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

USTRUCT( BlueprintType )
struct FLFPVoxelGridPosition
{
	GENERATED_BODY()

	FLFPVoxelGridPosition() {}

	FLFPVoxelGridPosition(const int32 NewSaveIndex, const int32 NewChuckIndex, const int32 NewVoxelIndex) : SaveIndex(NewSaveIndex), ChuckIndex(NewChuckIndex), VoxelIndex(NewVoxelIndex) {}

public:

	/** Save Index In Array */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelGridPosition")
		int32 SaveIndex = INDEX_NONE;

	/** Chuck Index In Array */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelGridPosition")
		int32 ChuckIndex = INDEX_NONE;

	/** Voxel Index In Array */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelGridPosition")
		int32 VoxelIndex = INDEX_NONE;

public:

	FORCEINLINE FIntPoint GetSaveAndChuck() const
	{
		return FIntPoint(SaveIndex, ChuckIndex);
	}

	FORCEINLINE bool operator==(const FLFPVoxelGridPosition& Other) const
	{
		return SaveIndex == Other.SaveIndex && ChuckIndex == Other.ChuckIndex && VoxelIndex == Other.VoxelIndex;
	}
};


USTRUCT()
struct FLFPVoxelChuckData
{
	GENERATED_BODY()

private:

	UPROPERTY(SaveGame)
		TArray<uint8> VoxelPaletteList = {};

	UPROPERTY(SaveGame)
		TArray<uint16> VoxelIndexList = {};

public:

	FORCEINLINE bool IsInitialized() const
	{
		return VoxelPaletteList.IsEmpty() == false;
	}

	FORCEINLINE void InitChuckData(const int32 VoxelLength, const FColor& VoxelColor, const uint8 VoxelMaterial)
	{
		if (VoxelMaterial == UINT16_MAX)
		{
			VoxelIndexList.Init(UINT16_MAX, VoxelLength);

			return;
		}

		VoxelPaletteList.Empty(1);

		VoxelPaletteList.Append({ VoxelColor.R, VoxelColor.G, VoxelColor.B, VoxelColor.A, VoxelMaterial});

		VoxelIndexList.SetNum(VoxelLength);

		return;
	}

	FORCEINLINE void SetVoxel(const int32 VoxelIndex, const FColor& NewVoxelColor, const uint8 NewVoxelMaterial)
	{
		check(VoxelIndexList.IsValidIndex(VoxelIndex));

		/** Is Air */
		if (NewVoxelMaterial == UINT8_MAX)
		{
			VoxelIndexList[VoxelIndex] = UINT16_MAX;

			return;
		}

		int32 PaletteIndex = INDEX_NONE;

		TArray<uint8> CheckData = { NewVoxelColor.R, NewVoxelColor.G, NewVoxelColor.B, NewVoxelColor.A, NewVoxelMaterial };

		/** Find Palette Index */
		for (int32 Index = 0; Index < VoxelPaletteList.Num(); Index += 5)
		{
			bool bSuccess = true;

			for (int32 CheckIndex = 0; CheckIndex < 5; CheckIndex++)
			{
				if (VoxelPaletteList[Index + CheckIndex] != CheckData[CheckIndex])
				{
					bSuccess = false;

					break;
				}
			}

			if (bSuccess)
			{
				PaletteIndex = Index / 5;

				break;
			}
		}

		/** Palette Not Found */
		if (PaletteIndex == INDEX_NONE)
		{
			PaletteIndex = VoxelPaletteList.Num() / 5;

			VoxelPaletteList.Append(CheckData);
		}

		VoxelIndexList[VoxelIndex] = PaletteIndex;

		return;
	}

	FORCEINLINE bool IsVoxelVisible(const int32 VoxelIndex) const
	{
		check(VoxelIndexList.IsValidIndex(VoxelIndex));

		return VoxelIndexList[VoxelIndex] != UINT16_MAX;
	}

	FORCEINLINE uint16 GetVoxelIndex(const int32 VoxelIndex) const
	{
		check(VoxelIndexList.IsValidIndex(VoxelIndex));

		return VoxelIndexList[VoxelIndex];
	}

	FORCEINLINE uint8 GetVoxelMaterial(const int32 VoxelIndex) const
	{
		check(VoxelIndexList.IsValidIndex(VoxelIndex));

		/** Is Air */
		if (VoxelIndexList[VoxelIndex] == UINT16_MAX) return UINT8_MAX;

		const int32 PaletteIndex = VoxelIndexList[VoxelIndex] * 5;

		return VoxelPaletteList[PaletteIndex + 4];
	}

	FORCEINLINE FColor GetVoxelColor(const int32 VoxelIndex) const
	{
		check(VoxelIndexList.IsValidIndex(VoxelIndex));

		/** Is Air */
		if (VoxelIndexList[VoxelIndex] == UINT16_MAX) return FColor(0);

		const int32 PaletteIndex = VoxelIndexList[VoxelIndex] * 5;

		return FColor(VoxelPaletteList[PaletteIndex], VoxelPaletteList[PaletteIndex + 1], VoxelPaletteList[PaletteIndex + 2], VoxelPaletteList[PaletteIndex + 3]);
	}

};

USTRUCT()
struct FLFPVoxelSaveData
{
	GENERATED_BODY()

public:

	UPROPERTY(SaveGame)
		TArray<FLFPVoxelChuckData> ChuckData = {};

public:

	FORCEINLINE void InitSaveData(const int32 ChuckLength)
	{
		ChuckData.Init(FLFPVoxelChuckData(), ChuckLength);
	}

};

USTRUCT()
struct FLFPVoxelChuckUpdateState
{
	GENERATED_BODY()

	FLFPVoxelChuckUpdateState() : Color(false), Material(false) {}

	UPROPERTY() 
		uint8 Color : 1;

	UPROPERTY() 
		uint8 Material : 1;

public: // Operator

	FORCEINLINE FLFPVoxelChuckUpdateState& operator+=(const FLFPVoxelChuckUpdateState& Other)
	{
		if (Other.Color) Color = true;
		if (Other.Material) Material = true;

		return *this;
	}
};


DECLARE_DELEGATE_OneParam(FOnVoxelChuckUpdate, const FLFPVoxelChuckUpdateState);

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
		TMap<int32, FColor> ChangeColor = TMap<int32, FColor>();

	UPROPERTY()
		TMap<int32, uint8> ChangeMaterial = TMap<int32, uint8>();

public: // Operator

	FLFPVoxelUpdateAction& operator+=(const FLFPVoxelUpdateAction& Other)
	{
		ChangeColor.Append(Other.ChangeColor);
		ChangeMaterial.Append(Other.ChangeMaterial);

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

public: /** Checker */

	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Checker")
		FORCEINLINE bool IsSaveInitialized(const int32 SaveIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Checker")
		FORCEINLINE bool IsChuckInitialized(const int32 SaveIndex, const int32 ChuckIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Checker")
		FORCEINLINE bool IsVoxelGridPositionValid(const FLFPVoxelGridPosition& VoxelGridPosition) const;

	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Checker")
		FORCEINLINE bool IsVoxelVisible(const FLFPVoxelGridPosition& VoxelGridPosition) const;

public: /** Setter */

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelContainerComponent | Setter")
		FORCEINLINE bool SetVoxelColor(const FLFPVoxelGridPosition& VoxelGridPosition, const FColor VoxelColor);

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelContainerComponent | Setter")
		FORCEINLINE bool SetVoxelMaterial(const FLFPVoxelGridPosition& VoxelGridPosition, const uint8 VoxelMaterial);

public: /** Getter */

	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Getter")
		FORCEINLINE FColor GetVoxelColor(const FLFPVoxelGridPosition& VoxelGridPosition) const;

	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Getter")
		FORCEINLINE uint8 GetVoxelMaterial(const FLFPVoxelGridPosition& VoxelGridPosition) const;

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LFPVoxelContainerComponent | Chuck")
		FORCEINLINE void InitializeSave(const int32 SaveIndex);
		virtual void InitializeSave_Implementation(const int32 SaveIndex);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LFPVoxelContainerComponent | Chuck")
		FORCEINLINE void InitializeChuck(const int32 SaveIndex, const int32 ChuckIndex);
		virtual void InitializeChuck_Implementation(const int32 SaveIndex, const int32 ChuckIndex);

//public: /** Chuck Request */
//
//	/** Request chuck info on chuck spawn */
//	FORCEINLINE void RequestRenderChuck(const int32 SaveIndex, const int32 ChuckIndex, FLFPVoxelChuckDelegate& ChuckDelegate);
//
//	/** Release chuck info on chuck destroy */
//	FORCEINLINE void ReleaseRenderChuck(const int32 SaveIndex, const int32 ChuckIndex);
//
//	/** Request Render Data and lock write access */
//	FORCEINLINE void RequestRenderData(const int32 SaveIndex, const int32 ChuckIndex, FLFPVoxelContainerSetting& ChuckSetting);
//
//	/** Release write access */
//	FORCEINLINE void ReleaseRenderData(const int32 SaveIndex, const int32 ChuckIndex);

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
		TArray<FLFPVoxelSaveData> SaveDataList;

	/** This store chuck delegate to call */
	UPROPERTY() 
		TMap<FIntPoint, FLFPVoxelChuckDelegate> ChuckDelegateList;

	/** This store future chuck update data to apply */
	UPROPERTY() 
		TMap<FIntPoint, FLFPVoxelUpdateAction> ChuckUpdateDataList;

	/** This store future chuck event data to send */
	UPROPERTY()
		TMap<FIntPoint, FLFPVoxelChuckUpdateState> ChuckUpdateStateList;
};
