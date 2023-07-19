// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LFPGridContainerComponent.generated.h"

USTRUCT( BlueprintType )
struct FLFPGridPaletteContainerSetting
{
	GENERATED_BODY()

	FLFPGridPaletteContainerSetting() {}

	FLFPGridPaletteContainerSetting(const FIntVector NewRegionGridSize, const FIntVector NewChuckGridSize, const FIntVector NewPaletteGridSize)
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
struct FLFPGridPaletteData
{
	GENERATED_BODY()

	FLFPGridPaletteData() {}

	FLFPGridPaletteData(const FLFPGridPaletteData& Other) : Name(Other.Name), TagList(Other.TagList), DataList(Other.DataList), RefCounter(1) { check(DataList.Num() <= TagList.Num()) }

	FLFPGridPaletteData(const FName& NewName, const TArray<FName>& NewTag, const TArray<uint8>& NewData) : Name(NewName), TagList(NewTag), DataList(NewData), RefCounter(1) { check(DataList.Num() <= TagList.Num()) }

public:

	static FLFPGridPaletteData EmptyData;

public:

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category = "LFPGridPaletteData")
		FName Name = FName();

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category = "LFPGridPaletteData")
		TArray<FName> TagList = TArray<FName>();

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category = "LFPGridPaletteData")
		TArray<uint8> DataList = TArray<uint8>();

private:

	UPROPERTY(SaveGame)
		uint32 RefCounter = 0;

public:

	FORCEINLINE bool IsValid() const
	{
		return DataList.Num() <= TagList.Num();
	}

	FORCEINLINE void RemoveTag(const FName& TagName)
	{
		int32 Index = INDEX_NONE;

		if (TagList.Find(TagName, Index) == false) return;

		TagList.RemoveAt(Index);

		if (DataList.IsValidIndex(Index)) DataList.RemoveAt(Index);
	}

	FORCEINLINE void RemoveTagData(const FName& TagName)
	{
		int32 Index = INDEX_NONE;

		if (TagList.Find(TagName, Index) == false || DataList.IsValidIndex(Index) == false) return;

		TagList.Swap(Index, DataList.Num() - 1);
		DataList.Swap(Index, DataList.Num() - 1);

		Index = DataList.Num() - 1;

		TagList.RemoveAt(Index);
		DataList.RemoveAt(Index);
	}

	FORCEINLINE void AddTag(const FName& TagName)
	{
		TagList.AddUnique(TagName);
	}

	FORCEINLINE void AddTagData(const FName& TagName, const uint8 TagData)
	{
		int32 Index = INDEX_NONE;

		if (TagList.Find(TagName, Index))
		{
			if (DataList.IsValidIndex(Index))
			{
				DataList[Index] = TagData;
			}
			else
			{
				TagList.Swap(Index, DataList.Num());
				DataList.Add(TagData);
			}
		}
		else
		{
			TagList.Add(TagName);
			TagList.Swap(TagList.Num() - 1, DataList.Num());
			DataList.Add(TagData);
		}
	}

	FORCEINLINE bool IsNone() const
	{
		return Name.IsNone();
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

public:

	friend FArchive& operator<<(FArchive& Ar, FLFPGridPaletteData& Data)
	{
		return Ar << Data.Name << Data.TagList << Data.DataList << Data.RefCounter;
	}

	FORCEINLINE bool operator==(const FLFPGridPaletteData& Other) const
	{
		return Name == Other.Name && TagList == Other.TagList && DataList == Other.DataList;
	}

	FORCEINLINE bool operator!=(const FLFPGridPaletteData& Other) const
	{
		return Name != Other.Name || TagList != Other.TagList || DataList != Other.DataList;
	}
};

//FORCEINLINE uint32 GetTypeHash(const FLFPGridPaletteData& Other)
//{
//	return FCrc::MemCrc32(&Other, sizeof(FLFPGridPaletteData));
//}



USTRUCT(BlueprintType)
struct FLFPGridChuckData
{
	GENERATED_BODY()

private:

	UPROPERTY(SaveGame)
		TArray<FLFPGridPaletteData> PaletteList = {};

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

	FORCEINLINE FBitReference GetIndexRef(TArray<uint32>& GridIndexListRef, const int32 Index)
	{
		return FBitReference(
			GridIndexListRef.GetData()[Index / NumBitsPerDWORD],
			1 << (Index & (NumBitsPerDWORD - 1))
		);
	}

	FORCEINLINE FConstBitReference GetIndexConstRef(const TArray<uint32>& GridIndexListRef, const int32 Index) const
	{
		return FConstBitReference(
			GridIndexListRef.GetData()[Index / NumBitsPerDWORD],
			1 << (Index & (NumBitsPerDWORD - 1))
		);
	}

	/** Palette Function */

	FORCEINLINE int32 FindOrAddPalette(const FLFPGridPaletteData& NewGridPalette, const bool bIncreaseCounter, const bool bResizePalette)
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

		const TArray<uint32> OldGridIndexList = IndexList;

		const uint32 OldSize = EncodeBtye;

		EncodeBtye = NewSize;

		const int32 ChuckBitSize = FMath::DivideAndRoundUp(IndexSize, uint32(32));

		IndexList.Init(0, (NewSize * ChuckBitSize) + 1);

		if (OldSize == 0) return;

		for (uint32 GridIndex = 0; GridIndex < IndexSize; GridIndex++)
		{
			for (uint32 EncodeIndex = 0; EncodeIndex < OldSize; EncodeIndex++)
			{
				const int32 OldBitIndex = int32((GridIndex * OldSize) + EncodeIndex);
				const int32 NewBitIndex = int32((GridIndex * EncodeBtye) + EncodeIndex);

				GetIndexRef(IndexList, NewBitIndex) = GetIndexConstRef(OldGridIndexList, OldBitIndex);
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

	FORCEINLINE void InitChuckData(const FLFPGridPaletteData& GridPalette, const uint32 NewIndexSize)
	{
		OpenPaletteList.Empty();

		IndexSize = NewIndexSize;

		PaletteList.Init(GridPalette, 1);
		PaletteList[0].SetCounter(NewIndexSize);

		EncodeBtye = 0;

		ResizePalette();
	}

	/** Read / Write Function */

	FORCEINLINE void SetIndexData(const int32 GridIndex, const FLFPGridPaletteData& NewData)
	{
		check(GridIndex >= 0 && GridIndex < int32(IndexSize) && EncodeBtye > 0);

		RemovePalette(GetPaletteIndex(GridIndex), false);

		const int32 NewIndex = FindOrAddPalette(NewData, true, true);

		for (uint32 EncodeIndex = 0; EncodeIndex < EncodeBtye; EncodeIndex++)
		{
			const int32 BitIndex = (GridIndex * EncodeBtye) + EncodeIndex;

			GetIndexRef(IndexList, BitIndex) = FConstBitReference(NewIndex, 1 << EncodeIndex);
		}
	}

	FORCEINLINE const FLFPGridPaletteData& GetIndexData(const int32 GridIndex) const
	{
		return PaletteList[GetPaletteIndex(GridIndex)];
	}

	FORCEINLINE int32 GetPaletteIndex(const int32 GridIndex) const
	{
		check(GridIndex >= 0 && GridIndex < int32(IndexSize) && EncodeBtye > 0);

		uint32 OutIndex = 0;

		for (uint32 EncodeIndex = 0; EncodeIndex < EncodeBtye; EncodeIndex++)
		{
			const int32 BitIndex = (GridIndex * EncodeBtye) + EncodeIndex;

			FBitReference(OutIndex, 1 << EncodeIndex) = GetIndexConstRef(IndexList, BitIndex);
		}

		return OutIndex;
	}

	FORCEINLINE const TArray<FLFPGridPaletteData>& GetPaletteList() const
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

public:

	friend FArchive& operator<<(FArchive& Ar, FLFPGridChuckData& Data)
	{
		return Ar << Data.PaletteList << Data.OpenPaletteList << Data.IndexList << Data.EncodeBtye << Data.IndexSize;
	}

};

USTRUCT(BlueprintType)
struct FLFPGridRegionData
{
	GENERATED_BODY()

public:

	UPROPERTY(SaveGame)
		TArray<FLFPGridChuckData> ChuckData = {};

public:

	FORCEINLINE bool IsInitialized() const
	{
		return ChuckData.IsEmpty() == false;
	}

	FORCEINLINE void InitRegionData(const int32 ChuckLength)
	{
		ChuckData.Init(FLFPGridChuckData(), ChuckLength);
	}

public:

	friend FArchive& operator<<(FArchive& Ar, FLFPGridRegionData& Data)
	{
		return Ar << Data.ChuckData;
	}
};

USTRUCT(BlueprintType)
struct FLFPChuckUpdateAction
{
	GENERATED_BODY()

	FLFPChuckUpdateAction() : bIsGridNameDirty(false), bIsGridTagDirty(false) {}

public:

	UPROPERTY() uint8 bIsGridNameDirty : 1;

	UPROPERTY() uint8 bIsGridTagDirty : 1;

public: // Operator

	FLFPChuckUpdateAction& operator+=(const FLFPChuckUpdateAction& Other)
	{
		if (bIsGridNameDirty == false) bIsGridNameDirty = Other.bIsGridNameDirty;
		if (bIsGridTagDirty == false) bIsGridTagDirty = Other.bIsGridNameDirty;

		return *this;
	}
};


DECLARE_MULTICAST_DELEGATE_OneParam(FOnGridChuckUpdate, const FLFPChuckUpdateAction&);

USTRUCT()
struct FLFPGridChuckDelegate
{
	GENERATED_BODY()

private:

	// Update Event For Notify Chuck On Grid Update
	FOnGridChuckUpdate GridChuckUpdateEvent;


	UPROPERTY()
		int32 BindAmount = 0;
public:

	template <typename UserClass, typename... ParamTypes>
	FORCEINLINE void AddUObject(UserClass* InUserObject, typename TMemFunPtrType<false, UserClass, void(const FLFPChuckUpdateAction&)>::Type InFunc)
	{
		GridChuckUpdateEvent.AddUObject(InUserObject, InFunc);

		BindAmount++;
	}

	FORCEINLINE void RemoveUObject(const UObject* InUserObject)
	{
		GridChuckUpdateEvent.RemoveAll(InUserObject);

		BindAmount--;
	}

	FORCEINLINE void Broadcast(const FLFPChuckUpdateAction& UpdateData) const
	{
		GridChuckUpdateEvent.Broadcast(UpdateData);
	}

	FORCEINLINE bool CanRemove() const
	{
		return BindAmount <= 0;
	}

	FORCEINLINE int32 GetAmount() const
	{
		return BindAmount;
	}
};

USTRUCT(BlueprintType)
struct FLFPGridUpdateAction
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "LFPGridUpdateAction")
		TMap<int32, FLFPGridPaletteData> ChangePalette = TMap<int32, FLFPGridPaletteData>();

public: // Operator

	FLFPGridUpdateAction& operator+=(const FLFPGridUpdateAction& Other)
	{
		ChangePalette.Append(Other.ChangePalette);

		return *this;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnGridContainerChuckUpdate, const int32, RegionIndex, const int32, ChuckIndex, const FLFPGridUpdateAction&, GridUpdateAction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGridContainerChuckInitialized, const int32, RegionIndex, const int32, ChuckIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGridContainerRegionInitialized, const int32, RegionIndex);


UCLASS( Blueprintable, meta = (BlueprintSpawnableComponent), ClassGroup = (LFPlugin) )
class LOHFUNCTIONPLUGIN_API ULFPGridContainerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPGridContainerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public: /** Debugging */

	UFUNCTION(BlueprintCallable, Category = "LFPGridContainerComponent | Function")
		FORCEINLINE FString Test();

public: /** Checker */

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Checker")
		FORCEINLINE bool IsRegionInitialized(const int32 RegionIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Checker")
		FORCEINLINE bool IsChuckInitialized(const int32 RegionIndex, const int32 ChuckIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Checker")
		FORCEINLINE bool IsRegionPositionValid(const int32 RegionIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Checker")
		FORCEINLINE bool IsChuckPositionValid(const int32 RegionIndex, const int32 ChuckIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Checker")
		FORCEINLINE bool IsGridPositionValid(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex) const;

public: /** Setter */

	UFUNCTION(BlueprintCallable, Category = "LFPGridContainerComponent | Setter")
		FORCEINLINE bool AddPaletteTag(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex, const FName& Tag);

	UFUNCTION(BlueprintCallable, Category = "LFPGridContainerComponent | Setter")
		FORCEINLINE bool AddPaletteTagData(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex, const FName& Tag, const uint8 Data);

	UFUNCTION(BlueprintCallable, Category = "LFPGridContainerComponent | Setter")
		FORCEINLINE bool RemovePaletteTag(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex, const FName& Tag);

	UFUNCTION(BlueprintCallable, Category = "LFPGridContainerComponent | Setter")
		FORCEINLINE bool RemovePaletteTagData(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex, const FName& Tag);

	UFUNCTION(BlueprintCallable, Category = "LFPGridContainerComponent | Setter")
		FORCEINLINE bool SetGridPalette(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex, const FLFPGridPaletteData& Palette);

	UFUNCTION(BlueprintCallable, Category = "LFPGridContainerComponent | Setter")
		FORCEINLINE bool SetGridPalettes(const int32 RegionIndex, const int32 ChuckIndex, const TMap<int32, FLFPGridPaletteData>& PaletteMap);

	UFUNCTION(BlueprintCallable, Category = "LFPGridContainerComponent | Setter")
		FORCEINLINE bool SetGridChuckData(const int32 RegionIndex, const int32 ChuckIndex, const FLFPGridChuckData& ChuckData);

	UFUNCTION(BlueprintCallable, Category = "LFPGridContainerComponent | Setter")
		FORCEINLINE bool InitializeGridChuck(const int32 RegionIndex, const int32 ChuckIndex);

public: /** Getter */

	UFUNCTION(BlueprintCallable, Category = "LFPGridContainerComponent | Getter")
		FORCEINLINE int32 GetRenderChuckAmount(const int32 RegionIndex, const int32 ChuckIndex) const;

	UFUNCTION(BlueprintCallable, Category = "LFPGridContainerComponent | Getter")
		FORCEINLINE FLFPGridChuckData GetGridChuckData(const int32 RegionIndex, const int32 ChuckIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Getter")
		FORCEINLINE FLFPGridPaletteData GetGridPalette(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Getter")
		FORCEINLINE TArray<FLFPGridPaletteData> GetGridPaletteList(const int32 RegionIndex, const int32 ChuckIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Getter")
		FORCEINLINE int32 GetGridPaletteIndex(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex) const;


	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Getter")
		FORCEINLINE FIntVector ToGridGlobalPosition(const FIntVector GridGlobalIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Getter")
		FORCEINLINE FIntVector ToGridGlobalIndex(const FIntVector GridGlobalPosition) const;

public: /** C++ Getter */

	FORCEINLINE const FLFPGridPaletteContainerSetting& GetSetting() const { return Setting; }

	FORCEINLINE const FLFPGridPaletteData& GetGridPaletteRef(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex) const;

	FORCEINLINE bool GetGridChuckDataByArchive(const int32 RegionIndex, const int32 ChuckIndex, FArchive& Ar);

public:

	FORCEINLINE bool SetGridChuckDataByArchive(const int32 RegionIndex, const int32 ChuckIndex, FArchive& Ar);


protected: /** Can be override to provide custom behavir */

	UFUNCTION()
		virtual void InitializeRegion(const int32 RegionIndex);

	UFUNCTION()
		virtual void InitializeChuck(const int32 RegionIndex, const int32 ChuckIndex);

public: /** Chuck Request */

	/** Request chuck info on chuck spawn */
	UFUNCTION() 
		FORCEINLINE FLFPGridChuckDelegate& AddRenderChuck(const int32 RegionIndex, const int32 ChuckIndex);

	/** Release chuck info on chuck destroy */
	UFUNCTION() 
		FORCEINLINE void RemoveRenderChuck(const int32 RegionIndex, const int32 ChuckIndex, const UObject* RemoveObject);

protected: /** Function for updating chuck and data */

	FORCEINLINE bool UpdateChuckState();

	FORCEINLINE bool UpdateChuckData();

public: /** Delegate */

	UPROPERTY(BlueprintAssignable, Category = "LFPGridContainerComponent | Delegate")
		FOnGridContainerChuckUpdate OnGridContainerChuckUpdate;

	UPROPERTY(BlueprintAssignable, Category = "LFPGridContainerComponent | Delegate")
		FOnGridContainerChuckInitialized OnGridContainerChuckInitialized;

	UPROPERTY(BlueprintAssignable, Category = "LFPGridContainerComponent | Delegate")
		FOnGridContainerRegionInitialized OnGridContainerRegionInitialized;


public: /** Read and write lock */

	FRWLock ContainerThreadLock;

protected: // Initialize Data

	/** What setting this component use when saving the Grid */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPGridContainerComponent | Setting")
		FLFPGridPaletteContainerSetting Setting;

protected:  // Runtime Data

	/** This store the chuck */
	UPROPERTY(SaveGame)
		TArray<FLFPGridRegionData> RegionDataList;

	/** This store chuck delegate to call */
	UPROPERTY() 
		TMap<FIntPoint, FLFPGridChuckDelegate> ChuckDelegateList;

	/** This store future chuck update data to apply */
	UPROPERTY() 
		TMap<FIntPoint, FLFPGridUpdateAction> ChuckUpdateDataList;

	/** This store future chuck event data to send */
	UPROPERTY()
		TMap<FIntPoint, FLFPChuckUpdateAction> ChuckUpdateStateList;
};