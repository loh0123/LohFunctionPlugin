// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LohFunctionPluginLibrary.h"
#include "Engine/DataTable.h"
#include "LFPGridContainerComponentV2.generated.h"

/**
* This Component Is Use To Store Grid Data (IE : Tag, MetaData)
*/

USTRUCT( BlueprintType )
struct FLFPGridContainerSetting
{
	GENERATED_BODY()

	FLFPGridContainerSetting() {}

	FLFPGridContainerSetting(const FIntVector NewRegionGridSize, const FIntVector NewChuckGridSize, const FIntVector NewPaletteGridSize)
		: RegionGridSize(NewRegionGridSize), ChuckGridSize(NewChuckGridSize), PaletteGridSize(NewPaletteGridSize)
	{ InitSetting(); }

private:

	UPROPERTY() int32 RegionLength = 1;

	UPROPERTY() int32 ChuckLength = 1;

	UPROPERTY() int32 PaletteLength = 1;

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere,		Category = "GridContainerSetting | Setting")
		FIntVector RegionGridSize = FIntVector(1);

	UPROPERTY(BlueprintReadOnly, EditAnywhere,		Category = "GridContainerSetting | Setting")
		FIntVector ChuckGridSize = FIntVector(1);

	/* Size Of Grid Inside Of A Chuck */
	UPROPERTY(BlueprintReadOnly, EditAnywhere,		Category = "GridContainerSetting | Setting")
		FIntVector PaletteGridSize = FIntVector(1);

public:

	FORCEINLINE void InitSetting()
	{
		if (RegionGridSize.GetMin() <= 0) RegionGridSize = FIntVector(1);
		if (ChuckGridSize.GetMin() <= 0) ChuckGridSize = FIntVector(1);
		if (PaletteGridSize.GetMin() <= 0) PaletteGridSize = FIntVector(1);

		RegionLength = RegionGridSize.X * RegionGridSize.Y * RegionGridSize.Z;
		ChuckLength = ChuckGridSize.X * ChuckGridSize.Y * ChuckGridSize.Z;
		PaletteLength = PaletteGridSize.X * PaletteGridSize.Y * PaletteGridSize.Z;
	}

	FORCEINLINE int32 GetRegionLength() const
	{
		return RegionLength;
	}

	FORCEINLINE int32 GetChuckLength() const
	{
		return ChuckLength;
	}

	FORCEINLINE int32 GetGridLength() const
	{
		return PaletteLength;
	}

	FORCEINLINE FIntVector GetRegionGrid() const
	{
		return RegionGridSize;
	}

	FORCEINLINE FIntVector GetChuckGrid() const
	{
		return ChuckGridSize;
	}

	FORCEINLINE FIntVector GetPaletteGrid() const
	{
		return PaletteGridSize;
	}
};

USTRUCT(BlueprintType)
struct FLFPGridChuckDataV2
{
	GENERATED_BODY()

private:

	UPROPERTY(SaveGame)
		FLFPCompactTagArray TagList = FLFPCompactTagArray();

	UPROPERTY(SaveGame)
		FLFPCompactMetaArray MetaList = FLFPCompactMetaArray();

public:

	/** Check Function */

	FORCEINLINE bool IsInitialized() const
	{
		return TagList.IsInitialized() && MetaList.IsInitialized();
	}

	FORCEINLINE bool IsValidIndex(const int32 PaletteInde) const
	{
		return TagList.IsValidIndex(PaletteInde) && MetaList.IsValidIndex(PaletteInde);
	}

	/** Init Function */

	FORCEINLINE void InitChuckData(const uint32 NewIndexSize, const FGameplayTag& StartTag)
	{
		TagList = FLFPCompactTagArray(NewIndexSize, 4, StartTag);

		MetaList = FLFPCompactMetaArray(NewIndexSize, 4, false);
	}

	FORCEINLINE void SetIndexTag(const int32 PaletteIndex, const FGameplayTag& NewTag)
	{
		check(IsValidIndex(PaletteIndex));

		TagList.AddItem(PaletteIndex, NewTag);
	}

	FORCEINLINE void SetIndexMeta(const int32 PaletteIndex, const FLFPCompactMetaData& NewMeta)
	{
		check(IsValidIndex(PaletteIndex));

		MetaList.AddItem(PaletteIndex, NewMeta);
	}

	FORCEINLINE FGameplayTag GetIndexTag(const int32 PaletteIndex) const
	{
		check(IsValidIndex(PaletteIndex));

		return TagList.GetItem(PaletteIndex);
	}

	FORCEINLINE const FLFPCompactMetaData* GetIndexMeta(const int32 PaletteIndex) const
	{
		check(IsValidIndex(PaletteIndex));

		return MetaList.GetItem(PaletteIndex);
	}
};

USTRUCT(BlueprintType)
struct FLFPGridRegionDataV2
{
	GENERATED_BODY()

protected:

	UPROPERTY(SaveGame)
		TArray<FLFPGridChuckDataV2> ChuckData = {};

public:

	FORCEINLINE bool IsInitialized() const
	{
		return ChuckData.IsEmpty() == false;
	}

	FORCEINLINE void InitRegionData(const int32 ChuckLength)
	{
		ChuckData.Init(FLFPGridChuckDataV2(), ChuckLength);
	}

	FORCEINLINE FLFPGridChuckDataV2* GetChuck(const int32 ChuckIndex)
	{
		if (ChuckData.IsValidIndex(ChuckIndex))
		{
			return &ChuckData[ChuckIndex];
		}

		return nullptr;
	}

	FORCEINLINE bool IsChuckValidIndex(const int32 ChuckIndex) const
	{
		return ChuckData.IsValidIndex(ChuckIndex);
	}

	FORCEINLINE const FLFPGridChuckDataV2* GetChuck(const int32 ChuckIndex) const
	{
		if (ChuckData.IsValidIndex(ChuckIndex))
		{
			return &ChuckData[ChuckIndex];
		}

		return nullptr;
	}

	FORCEINLINE FLFPGridChuckDataV2& GetChuckChecked(const int32 ChuckIndex)
	{
		check(ChuckData.IsValidIndex(ChuckIndex));

		return ChuckData[ChuckIndex];
	}

	FORCEINLINE const FLFPGridChuckDataV2& GetChuckChecked(const int32 ChuckIndex) const
	{
		check(ChuckData.IsValidIndex(ChuckIndex));

		return ChuckData[ChuckIndex];
	}
};

USTRUCT(BlueprintType)
struct FLFPChuckUpdateActionV2
{
	GENERATED_BODY()
};


UCLASS( Blueprintable, meta = (BlueprintSpawnableComponent), ClassGroup = (LFPlugin) )
class LOHFUNCTIONPLUGIN_API ULFPGridContainerComponentV2 : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPGridContainerComponentV2();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public: /** Checker */

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Checker")
	FORCEINLINE bool IsRegionPositionValid(const int32 RegionIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Checker")
	FORCEINLINE bool IsRegionInitialized(const int32 RegionIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Checker")
	FORCEINLINE bool IsChuckPositionValid(const int32 RegionIndex, const int32 ChuckIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Checker")
	FORCEINLINE bool IsChuckInitialized(const int32 RegionIndex, const int32 ChuckIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Checker")
	FORCEINLINE bool IsPalettePositionValid(const int32 RegionIndex, const int32 ChuckIndex, const int32 PaletteIndex) const;

public:

	UFUNCTION(BlueprintCallable, Category = "LFPGridContainerComponent | Setter")
	FORCEINLINE bool SetPaletteTag(const int32 RegionIndex, const int32 ChuckIndex, const int32 PaletteIndex, const FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "LFPGridContainerComponent | Setter")
	FORCEINLINE bool SetPaletteData(const int32 RegionIndex, const int32 ChuckIndex, const int32 PaletteIndex, const FLFPCompactMetaData& Data);

public: /** Getter */

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Getter")
	FORCEINLINE FGameplayTag GetPaletteTag(const int32 RegionIndex, const int32 ChuckIndex, const int32 PaletteIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Getter")
	FORCEINLINE FLFPCompactMetaData GetPaletteData(const int32 RegionIndex, const int32 ChuckIndex, const int32 PaletteIndex) const;

protected: // Initialize Data

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPGridContainerComponent | Setting")
	FLFPGridContainerSetting Setting;

protected:  // Runtime Data

	/** This store the chuck */
	UPROPERTY(SaveGame)
	TArray<FLFPGridRegionDataV2> RegionDataList;
};
