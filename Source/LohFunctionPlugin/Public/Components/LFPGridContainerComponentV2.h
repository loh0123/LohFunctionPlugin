// Copyright by Loh Zhi Kang

#pragma once

#include "Components/ActorComponent.h"
#include "LohFunctionPluginLibrary.h"
#include "LFPGridContainerComponentV2.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LFPGridContainerComponentV2, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LFPGridChuckDataV2, Log, All);

/**
* This Component Is Use To Store Grid Data (IE : Tag, MetaData)
*/

USTRUCT( BlueprintType )
struct LOHFUNCTIONPLUGIN_API FLFPGridContainerSetting
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

	FORCEINLINE bool IsValid() const
	{
		return GetRegionLength() > 0 && GetChuckLength() > 0 && GetPaletteLength() > 0;
	}

	FORCEINLINE int32 GetRegionLength() const
	{
		return RegionLength;
	}

	FORCEINLINE int32 GetChuckLength() const
	{
		return ChuckLength;
	}

	FORCEINLINE int32 GetPaletteLength() const
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
struct LOHFUNCTIONPLUGIN_API FLFPGridChuckDataV2
{
	GENERATED_BODY()

private:

	UPROPERTY()
		FLFPCompactTagArray TagList = FLFPCompactTagArray();

	UPROPERTY()
		FLFPCompactUniqueMetaArray MetaList = FLFPCompactUniqueMetaArray();

	UPROPERTY()
		FLFPMetaArray ChuckMetaList = FLFPMetaArray();

	UPROPERTY()
		uint64 WriteCount = 0;

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

		MetaList = FLFPCompactUniqueMetaArray(NewIndexSize, 4);

		WriteCount++;

		UE_LOG(LFPGridChuckDataV2, Log, TEXT("FLFPGridChuckDataV2 : InitChuckData Allocated IndexSize = %d With StartTag = %s"), TagList.GetIndexSize(), *StartTag.ToString());
	}

	FORCEINLINE void SetIndexTag(const int32 PaletteIndex, const FGameplayTag& NewTag)
	{
		check(IsValidIndex(PaletteIndex));

		TagList.AddItem(PaletteIndex, NewTag);

		WriteCount++;
	}

	FORCEINLINE bool SetIndexTagList(const TArray<int32>& PaletteIndexList, const FGameplayTag& NewTag)
	{
		WriteCount++;

		return TagList.AddItemList(PaletteIndexList, NewTag);
	}

	FORCEINLINE void SetIndexMeta(const int32 PaletteIndex, const FLFPCompactMetaData& NewMeta)
	{
		check(IsValidIndex(PaletteIndex));

		MetaList.AddItem(PaletteIndex, NewMeta);

		WriteCount++;
	}

	FORCEINLINE void SetChuckMeta(const FLFPCompactMetaData& NewMeta)
	{
		ChuckMetaList.SetItem(NewMeta);
	}

	FORCEINLINE FGameplayTag GetIndexTag(const int32 PaletteIndex) const
	{
		check(IsValidIndex(PaletteIndex));

		return TagList.GetItem(PaletteIndex);
	}

	FORCEINLINE uint64 GetWriteCount() const
	{
		return WriteCount;
	}

	FORCEINLINE const FLFPCompactMetaData* GetIndexMeta(const int32 PaletteIndex) const
	{
		check(IsValidIndex(PaletteIndex));

		return MetaList.GetItem(PaletteIndex);
	}

	FORCEINLINE const FLFPCompactMetaData* GetChuckMeta(const FGameplayTag& MetaTag) const
	{
		return ChuckMetaList.GetItemConst(MetaTag);
	}

};

USTRUCT(BlueprintType)
struct LOHFUNCTIONPLUGIN_API FLFPGridRegionDataV2
{
	GENERATED_BODY()

protected:

	UPROPERTY()
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
struct LOHFUNCTIONPLUGIN_API FLFPChuckUpdateActionV2
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FGameplayTag InitializeTag = FGameplayTag();

	UPROPERTY() 
	TMap<int32, FGameplayTag> TagChangeList = TMap<int32, FGameplayTag>();

	UPROPERTY() 
	TMap<int32, FLFPMetaArray> DataChangeList = TMap<int32, FLFPMetaArray>();

public:

	FORCEINLINE void SetInitializeTag(const FGameplayTag& Tag)
	{
		InitializeTag = Tag;
	}

	FORCEINLINE void AddTagChange(const int32 Index, const FGameplayTag& Tag)
	{
		TagChangeList.Add(Index, Tag);
	}

	FORCEINLINE void AddDataChange(const int32 Index, const FLFPCompactMetaData& Data)
	{
		FLFPMetaArray& MetaArray = DataChangeList.FindOrAdd(Index);

		MetaArray.SetItem(Data);
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnGridContainerPalleteDataUpdated, const int32, RegionIndex, const int32, ChuckIndex, const TSet<int32>&, PaletteIndexList);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGridContainerV2ChuckInitialized, const int32, RegionIndex, const int32, ChuckIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGridContainerV2RegionInitialized, const int32, RegionIndex);


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

protected:

	FORCEINLINE bool UpdateChuckData();

public: /** Checker */

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Checker")
	bool IsRegionPositionValid(const int32 RegionIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Checker")
	bool IsRegionInitialized(const int32 RegionIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Checker")
	bool IsChuckPositionValid(const int32 RegionIndex, const int32 ChuckIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Checker")
	bool IsChuckInitialized(const int32 RegionIndex, const int32 ChuckIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Checker")
	bool IsPalettePositionValid(const int32 RegionIndex, const int32 ChuckIndex, const int32 PaletteIndex) const;

public: /** Setter */

	UFUNCTION(BlueprintCallable, Category = "LFPGridContainerComponent | Setter")
	void ReinitializeRegion();

	UFUNCTION(BlueprintCallable, Category = "LFPGridContainerComponent | Setter")
	bool InitializeData(const int32 RegionIndex, const int32 ChuckIndex, const FGameplayTag StartTag, const bool bOverride = true);

	UFUNCTION(BlueprintCallable, Category = "LFPGridContainerComponent | Setter")
	bool SetPaletteTag(const int32 RegionIndex, const int32 ChuckIndex, const int32 PaletteIndex, const FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "LFPGridContainerComponent | Setter")
	bool SetPaletteTagList(const int32 RegionIndex, const int32 ChuckIndex, const TArray<int32>& PaletteIndexList, const FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "LFPGridContainerComponent | Setter")
	bool SetPaletteData(const int32 RegionIndex, const int32 ChuckIndex, const int32 PaletteIndex, const FLFPCompactMetaData& Data);

public: /** Getter */

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Getter")
	FGameplayTag GetPaletteTag(const int32 RegionIndex, const int32 ChuckIndex, const int32 PaletteIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Getter")
	FLFPCompactMetaData GetPaletteData(const int32 RegionIndex, const int32 ChuckIndex, const int32 PaletteIndex) const;

public: /** Positon */

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Positon")
	FIntVector ToGridGlobalPosition(const FIntVector GridGlobalIndex, const bool bRound = false) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridContainerComponent | Positon")
	FIntVector ToGridGlobalIndex(FIntVector GridGlobalPosition, const bool bRound = false) const;

public: /** Read and write Thread lock */

	FRWLock ContainerThreadLock;

public: /** Delegate */

	UPROPERTY(BlueprintAssignable, Category = "LFPGridContainerComponent | Delegate")
	FOnGridContainerPalleteDataUpdated OnGridContainerPalleteUpdated;

	UPROPERTY(BlueprintAssignable, Category = "LFPGridContainerComponent | Delegate")
	FOnGridContainerV2ChuckInitialized OnGridContainerChuckUpdated;

	UPROPERTY(BlueprintAssignable, Category = "LFPGridContainerComponent | Delegate")
	FOnGridContainerV2ChuckInitialized OnGridContainerChuckInitialized;

	UPROPERTY(BlueprintAssignable, Category = "LFPGridContainerComponent | Delegate")
	FOnGridContainerV2RegionInitialized OnGridContainerRegionInitialized;

protected: // Initialize Data

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPGridContainerComponent | Setting")
	FLFPGridContainerSetting Setting;

protected:  // Runtime Data

	/** This store the chuck */
	UPROPERTY()
	TArray<FLFPGridRegionDataV2> RegionDataList;

	/** This store future chuck event data to send */
	UPROPERTY()
	TMap<FIntPoint, FLFPChuckUpdateActionV2> ChuckUpdateStateList;
};
