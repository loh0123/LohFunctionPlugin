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
struct FLFPGridPaletteDataV2
{
	GENERATED_BODY()

	FLFPGridPaletteDataV2() {}

	FLFPGridPaletteDataV2(const FLFPGridPaletteDataV2& Other) : Name(Other.Name) {  }

	FLFPGridPaletteDataV2(const FName& NewName) : Name(NewName) {  }

public:

	static FLFPGridPaletteDataV2 EmptyData;

public:

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category = "LFPGridPaletteData")
		FName Name = FName();

public:

	FORCEINLINE bool IsNone() const
	{
		return Name.IsNone();
	}

public:

	FORCEINLINE bool operator==(const FLFPGridPaletteDataV2& Other) const
	{
		return Name == Other.Name;
	}

	FORCEINLINE bool operator!=(const FLFPGridPaletteDataV2& Other) const
	{
		return Name != Other.Name;
	}
};

USTRUCT(BlueprintType)
struct FLFPGridChuckDataV2
{
	GENERATED_BODY()

public:

	static FLFPGridChuckDataV2 EmptyData;

private:

	UPROPERTY(SaveGame)
		TArray<FLFPGridPaletteDataV2> PaletteList = {};

	UPROPERTY(SaveGame)
		FLFPCompactIDArray IDList = FLFPCompactIDArray();

private:

	/** Palette Function */

	FORCEINLINE int32 FindPaletteIndex(const FName& PaletteName) const
	{
		return PaletteList.Find(PaletteName);
	}

	FORCEINLINE int32 FindOrAddPaletteIndex(const FLFPGridPaletteDataV2& NewGridPalette)
	{
		int32 PaletteIndex = PaletteList.Find(NewGridPalette);

		if (PaletteIndex == INDEX_NONE)
		{
			const int32 AssignID = IDList.Assign();

			if (PaletteList.Num() < AssignID + 1)
			{
				PaletteList.SetNum(AssignID + 1);
			}

			PaletteList[AssignID] = NewGridPalette;
		}

		return PaletteIndex;
	}

	/** Resize Function */

	FORCEINLINE void ResizePalette()
	{
		check(IsInitialized());

		PaletteList.SetNum(IDList.Num());

		return;
	}

public:

	/** Check Function */

	FORCEINLINE bool IsInitialized() const
	{
		return PaletteList.IsEmpty() == false;
	}

	/** Init Function */

	FORCEINLINE void InitChuckData(const FLFPGridPaletteDataV2& GridPalette, const uint32 NewIndexSize)
	{
		PaletteList.Init(GridPalette, 1);

		IDList = FLFPCompactIDArray(NewIndexSize, 1);
	}

	/** Read / Write Function */

	FORCEINLINE const TArray<FLFPGridPaletteDataV2>& GetPaletteList() const
	{
		return PaletteList;
	}

	FORCEINLINE int32 GetPaletteIndex(const int32 GridIndex) const
	{
		return IDList.GetIndexNumber(GridIndex);
	}

	FORCEINLINE void SetIndexData(const int32 GridIndex, const FLFPGridPaletteDataV2& NewData)
	{
		check(GridIndex >= 0);

		const int32 NewIndex = FindOrAddPaletteIndex(NewData);

		IDList.Set(GridIndex, NewIndex);

		ResizePalette();
	}

	FORCEINLINE const FLFPGridPaletteDataV2& GetIndexData(const int32 GridIndex) const
	{
		return PaletteList[GetPaletteIndex(GridIndex)];
	}

	FORCEINLINE int32 GetIndexSize() const
	{
		return IDList.GetIndexSize();
	}

};

USTRUCT(BlueprintType)
struct FLFPGridRegionDataV2
{
	GENERATED_BODY()

public:

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
};
