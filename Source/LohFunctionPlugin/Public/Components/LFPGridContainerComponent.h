// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LohFunctionPluginLibrary.h"
#include "Engine/DataTable.h"
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

	FLFPGridPaletteData(const FLFPGridPaletteData& Other) : Name(Other.Name), TagList(Other.TagList), RefCounter(1) {  }

	FLFPGridPaletteData(const FName& NewName, const TArray<FName>& NewTag) : Name(NewName), TagList(NewTag), RefCounter(1) {  }

	//FLFPGridPaletteData(const FLFPGridPaletteData& Other) : Name(Other.Name), TagList(Other.TagList), DataList(Other.DataList), RefCounter(1) { check(DataList.Num() <= TagList.Num()) }

	//FLFPGridPaletteData(const FName& NewName, const TArray<FName>& NewTag, const TArray<uint8>& NewData) : Name(NewName), TagList(NewTag), DataList(NewData), RefCounter(1) { check(DataList.Num() <= TagList.Num()) }

public:

	static FLFPGridPaletteData EmptyData;

public:

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category = "LFPGridPaletteData")
		FName Name = FName();

	UPROPERTY(SaveGame, BlueprintReadWrite, EditAnywhere, Category = "LFPGridPaletteData")
		TArray<FName> TagList = TArray<FName>();

private:

	UPROPERTY(SaveGame)
		uint32 RefCounter = 0;

public:

	FORCEINLINE void RemoveTag(const FName& TagName)
	{
		int32 Index = INDEX_NONE;

		if (TagList.Find(TagName, Index) == false) return;

		TagList.RemoveAt(Index);
	}

	FORCEINLINE void AddTag(const FName& TagName)
	{
		TagList.AddUnique(TagName);
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
		return Ar << Data.Name << Data.TagList/* << Data.DataList*/ << Data.RefCounter;
	}

	FORCEINLINE bool operator==(const FLFPGridPaletteData& Other) const
	{
		return Name == Other.Name && TagList == Other.TagList/* && DataList == Other.DataList*/;
	}

	FORCEINLINE bool operator!=(const FLFPGridPaletteData& Other) const
	{
		return Name != Other.Name || TagList != Other.TagList/* || DataList != Other.DataList*/;
	}
};

//FORCEINLINE uint32 GetTypeHash(const FLFPGridPaletteData& Other)
//{
//	return FCrc::MemCrc32(&Other, sizeof(FLFPGridPaletteData));
//}

USTRUCT(BlueprintType)
struct FLFPGridTagDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LFPGridTagDataTable") uint8 DataSize = uint8(255);
};

USTRUCT(BlueprintType)
struct FLFPGridChuckData
{
	GENERATED_BODY()

public:

	static FLFPGridChuckData EmptyData;

private:

	UPROPERTY(SaveGame)
		TArray<FLFPGridPaletteData> PaletteList = {};

	UPROPERTY(SaveGame)
		TArray<int32> OpenPaletteList = {};

	UPROPERTY(SaveGame)
		FLFPCompactIntArray IndexList = FLFPCompactIntArray();

	UPROPERTY(SaveGame)
		TArray<FLFPCompactIntNameArray> DataList = TArray<FLFPCompactIntNameArray>();

private:

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

	FORCEINLINE void InitChuckData(const FLFPGridPaletteData& GridPalette, const uint32 NewIndexSize)
	{
		OpenPaletteList.Empty();

		PaletteList.Init(GridPalette, 1);
		PaletteList[0].SetCounter(NewIndexSize);

		IndexList = FLFPCompactIntArray(NewIndexSize);

		ResizePalette();
	}

	/** Read / Write Function */

	FORCEINLINE void SetTagData(const int32 GridIndex, const FName& TagName, const uint8 NewData, const uint8 DataMaxSize)
	{
		check(GridIndex >= 0);

		auto TagDataList = DataList.FindByKey(TagName);

		if (TagDataList == nullptr)
		{
			const int32 NewIndex = DataList.Add(FLFPCompactIntNameArray(TagName, FLFPCompactIntArray(IndexList.GetIndexSize())));

			TagDataList = &DataList[NewIndex];

			TagDataList->Resize(DataMaxSize);
		}

		TagDataList->SetIndexNumber(GridIndex, uint32(FMath::Min(NewData, DataMaxSize)));
	}

	FORCEINLINE uint8 GetTagData(const int32 GridIndex, const FName TagName) const
	{
		check(GridIndex >= 0);

		auto TagDataList = DataList.FindByKey(TagName);

		if (TagDataList == nullptr)
		{
			return uint8(0);
		}
		else
		{
			return uint8(TagDataList->GetIndexNumber(GridIndex));
		}
	}

	FORCEINLINE void GetTagDataList(const int32 GridIndex, TMap<FName, uint8>& TagDataList) const
	{
		check(GridIndex >= 0);

		for (const auto& Data : DataList)
		{
			TagDataList.Add(Data.Name, Data.GetIndexNumber(GridIndex));
		}
	}

	FORCEINLINE void SetIndexData(const int32 GridIndex, const FLFPGridPaletteData& NewData)
	{
		check(GridIndex >= 0);

		RemovePalette(GetPaletteIndex(GridIndex), false);

		const int32 NewIndex = FindOrAddPalette(NewData, true, true);

		IndexList.SetIndexNumber(GridIndex, NewIndex);
	}

	FORCEINLINE const FLFPGridPaletteData& GetIndexData(const int32 GridIndex) const
	{
		return PaletteList[GetPaletteIndex(GridIndex)];
	}

	FORCEINLINE int32 GetPaletteIndex(const int32 GridIndex) const
	{
		return IndexList.GetIndexNumber(GridIndex);
	}

	FORCEINLINE const TArray<FLFPGridPaletteData>& GetPaletteList() const
	{
		return PaletteList;
	}

	FORCEINLINE int32 GetIndexSize() const
	{
		return IndexList.GetIndexSize();
	}

public:

	friend FArchive& operator<<(FArchive& Ar, FLFPGridChuckData& Data)
	{
		return Ar << Data.PaletteList << Data.OpenPaletteList << Data.IndexList;
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
struct FLFPGridNameUpdateData
{
	GENERATED_BODY()

	FLFPGridNameUpdateData() {}

	FLFPGridNameUpdateData(const FName& A, const FName& B) : FromName(A), ToName(B) {}

public:

	UPROPERTY()
		FName FromName = FName();

	UPROPERTY()
		FName ToName = FName();

public:

	bool operator==(const FLFPGridNameUpdateData& Other) const
	{
		return FromName == Other.FromName && ToName == Other.ToName;
	}

	bool operator!=(const FLFPGridNameUpdateData& Other) const
	{
		return FromName != Other.FromName || ToName != Other.ToName;
	}
};

#if UE_BUILD_DEBUG
uint32 GetTypeHash(const FLFPGridNameUpdateData& Thing);
#else
FORCEINLINE uint32 GetTypeHash(const FLFPGridNameUpdateData& Thing)
{
	uint32 Hash = FCrc::MemCrc32(&Thing, sizeof(FLFPGridNameUpdateData));
	return Hash;
}
#endif

USTRUCT(BlueprintType)
struct FLFPChuckUpdateAction
{
	GENERATED_BODY()

	FLFPChuckUpdateAction() : GridChangeNameList(TSet<FLFPGridNameUpdateData>()), GridDirtyIndexList(TSet<int32>()) {}

public:

	UPROPERTY() TSet<FLFPGridNameUpdateData> GridChangeNameList = TSet<FLFPGridNameUpdateData>();

	UPROPERTY() TSet<int32> GridDirtyIndexList = TSet<int32>();

public: // Operator

	FLFPChuckUpdateAction& operator+=(const FLFPChuckUpdateAction& Other)
	{
		GridChangeNameList.Append(Other.GridChangeNameList);
		GridDirtyIndexList.Append(Other.GridDirtyIndexList);

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
struct FLFPGridChangeTagData
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "LFPGridChangeTagData")
		TMap<FName, uint8> ChangeData = TMap<FName, uint8>();
};

USTRUCT(BlueprintType)
struct FLFPGridUpdateAction
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "LFPGridUpdateAction")
		TMap<int32, FLFPGridPaletteData> ChangePalette = TMap<int32, FLFPGridPaletteData>();

	UPROPERTY(BlueprintReadWrite, Category = "LFPGridUpdateAction")
		TMap<int32, FLFPGridChangeTagData> ChangeTagData = TMap<int32, FLFPGridChangeTagData>();

public: // Operator

	FLFPGridUpdateAction& operator+=(const FLFPGridUpdateAction& Other)
	{
		ChangePalette.Append(Other.ChangePalette);
		ChangeTagData.Append(Other.ChangeTagData);

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
		FORCEINLINE bool RemovePaletteTag(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex, const FName& Tag);

	UFUNCTION(BlueprintCallable, Category = "LFPGridContainerComponent | Setter")
		FORCEINLINE bool SetTagData(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex, const FName Tag, const uint8 Data);

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
		FORCEINLINE uint8 GetGridTagData(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex, const FName TagName) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Getter")
		FORCEINLINE FLFPGridPaletteData GetGridPalette(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Getter")
		FORCEINLINE TArray<FLFPGridPaletteData> GetGridPaletteList(const int32 RegionIndex, const int32 ChuckIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Getter")
		FORCEINLINE int32 GetGridPaletteIndex(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex) const;


	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Getter")
		FORCEINLINE FIntVector ToGridGlobalPosition(const FIntVector GridGlobalIndex, const bool bRound = false) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Getter")
		FORCEINLINE FIntVector ToGridGlobalIndex(FIntVector GridGlobalPosition, const bool bRound = false) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Getter")
		FORCEINLINE FIntVector AddGridGlobalPositionOffset(const FIntVector GridGlobalPosition, const FIntVector GridGlobalIndexOffset, const bool bRound = false) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Getter")
		FORCEINLINE FIntVector AddGridGlobalIndexOffset(const FIntVector GridGlobalIndex, const FIntVector GridGlobalPositionOffset, const bool bRound = false) const;

public: /** C++ Getter */

	FORCEINLINE const FLFPGridPaletteContainerSetting& GetSetting() const { return Setting; }

	FORCEINLINE const FLFPGridPaletteData& GetGridPaletteRef(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex) const;

	FORCEINLINE bool GetGridTagDataListRef(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex, TMap<FName, uint8>& TagDataList) const;

	FORCEINLINE const FLFPGridChuckData& GetGridChuckRef(const int32 RegionIndex, const int32 ChuckIndex) const;

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
		FORCEINLINE void RemoveRenderChuck(const int32 RegionIndex, const int32 ChuckIndex, const UActorComponent* RemoveObject);

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

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPGridContainerComponent | Setting ")
		TObjectPtr<UDataTable> TagDataTable = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPGridContainerComponent | Setting ")
		bool bSwitchRegionZWithX = false;

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
