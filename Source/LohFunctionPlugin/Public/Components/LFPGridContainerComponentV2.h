// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LohFunctionPluginLibrary.h"
#include "Engine/DataTable.h"
#include "LFPGridContainerComponentV2.generated.h"

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

	FLFPGridPaletteDataV2(const FLFPGridPaletteDataV2& Other) : Name(Other.Name), RefCounter(1) {  }

	FLFPGridPaletteDataV2(const FName& NewName) : Name(NewName), RefCounter(1) {  }

public:

	static FLFPGridPaletteDataV2 EmptyData;

public:

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category = "LFPGridPaletteData")
		FName Name = FName();

private:

	UPROPERTY(SaveGame)
		uint32 RefCounter = 0;

public:

	FORCEINLINE bool IsNone() const
	{
		return Name.IsNone();
	}

	FORCEINLINE bool CanRemove() const
	{
		return RefCounter == 0;
	}

	FORCEINLINE void AddRef(const int32 NewRef = 1)
	{
		check(NewRef > 0);

		RefCounter += NewRef;
	}

	FORCEINLINE void RemoveRef(const int32 OldRef = 1)
	{
		check(OldRef > 0);

		if (RefCounter > 0)
		{
			RefCounter -= OldRef;

			if (RefCounter < 0) RefCounter = 0;
		}
	}

public:

	friend FArchive& operator<<(FArchive& Ar, FLFPGridPaletteDataV2& Data)
	{
		return Ar << Data.Name << Data.RefCounter;
	}

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
		TArray<int32> OpenPaletteList = {};

	UPROPERTY(SaveGame)
		FLFPCompactIntArray IndexList = FLFPCompactIntArray();

private:

	/** Palette Function */

	FORCEINLINE int32 FindPaletteIndex(const FName& PaletteName) const
	{
		return PaletteList.Find(PaletteName);
	}

	FORCEINLINE int32 FindOrAddPaletteIndex(const FLFPGridPaletteDataV2& NewGridPalette, const bool bIncreaseCounter, const bool bResizePalette)
	{
		int32 PaletteIndex = PaletteList.Find(NewGridPalette);

		if (PaletteIndex == INDEX_NONE)
		{
			if (OpenPaletteList.IsEmpty() == false) 
			{
				PaletteIndex = OpenPaletteList.Pop();

				PaletteList[PaletteIndex] = NewGridPalette;
			}
			else
			{
				PaletteIndex = PaletteList.Add(NewGridPalette);
			}

			if (bResizePalette) ResizePalette();
		}
		else if (bIncreaseCounter)
		{
			PaletteList[PaletteIndex].AddRef();
		}

		return PaletteIndex;
	}

	FORCEINLINE void RemovePalette(const int32 PaletteIndex, const bool bResizePalette)
	{
		check(PaletteList[PaletteIndex].CanRemove() == false);

		PaletteList[PaletteIndex].RemoveRef();

		if (PaletteList[PaletteIndex].CanRemove() == false) return;

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

	FORCEINLINE void ResizePalette()
	{
		check(IsInitialized());

		IndexList.Resize(PaletteList.Num());

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
		OpenPaletteList.Empty();

		PaletteList.Init(GridPalette, 1);
		PaletteList[0].AddRef(NewIndexSize - 1);

		IndexList = FLFPCompactIntArray(NewIndexSize);

		ResizePalette();
	}

	/** Read / Write Function */

	FORCEINLINE const TArray<FLFPGridPaletteDataV2>& GetPaletteList() const
	{
		return PaletteList;
	}

	FORCEINLINE int32 GetPaletteIndex(const int32 GridIndex) const
	{
		return IndexList.GetIndexNumber(GridIndex);
	}

	FORCEINLINE void SetIndexData(const int32 GridIndex, const FLFPGridPaletteDataV2& NewData)
	{
		check(GridIndex >= 0);

		RemovePalette(GetPaletteIndex(GridIndex), false);

		const int32 NewIndex = FindOrAddPaletteIndex(NewData, true, true);

		IndexList.SetIndexNumber(GridIndex, NewIndex);
	}

	FORCEINLINE const FLFPGridPaletteDataV2& GetIndexData(const int32 GridIndex) const
	{
		return PaletteList[GetPaletteIndex(GridIndex)];
	}

	FORCEINLINE int32 GetIndexSize() const
	{
		return IndexList.GetIndexSize();
	}

public:

	friend FArchive& operator<<(FArchive& Ar, FLFPGridChuckDataV2& Data)
	{
		return Ar << Data.PaletteList << Data.OpenPaletteList << Data.IndexList;
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

public:

	friend FArchive& operator<<(FArchive& Ar, FLFPGridRegionDataV2& Data)
	{
		return Ar << Data.ChuckData;
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
