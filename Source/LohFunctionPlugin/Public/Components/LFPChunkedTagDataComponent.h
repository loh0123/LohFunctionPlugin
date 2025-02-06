// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Library/LFPDynamicTypeLibrary.h"
#include "LFPChunkedTagDataComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogChunkedTagDataComponent, Log, All);

USTRUCT()
struct FLFPTaggedMetaData
{
	GENERATED_BODY()

	FLFPTaggedMetaData( ) = default;

	explicit FLFPTaggedMetaData( int32 DataIndex ) :
		DataIndex(DataIndex)
	{
	}

private:

	UPROPERTY()
	int32 DataIndex = INDEX_NONE;

	UPROPERTY()
	FLFPPrimitiveDataTagArray MetaList = FLFPPrimitiveDataTagArray();

public:

	FORCEINLINE bool operator==( const int32 FindingIndex ) const
	{
		return DataIndex == FindingIndex;
	}

public:

	FORCEINLINE int32 GetDataIndex( ) const
	{
		return DataIndex;
	}

	FORCEINLINE void SetDataIndex( const int32 NewDataIndex )
	{
		DataIndex = NewDataIndex;
	}

public:

	FORCEINLINE const FLFPPrimitiveData* GetMetaData( const FGameplayTag& MetaTag ) const
	{
		return MetaList.GetItemConst(MetaTag);
	}

	FORCEINLINE FLFPPrimitiveData& GetOrAddMetaData( const FGameplayTag& MetaTag )
	{
		return MetaList.GetOrAddItem(MetaTag);
	}

	FORCEINLINE void RemoveMetaData( const FGameplayTag& MetaTag )
	{
		MetaList.RemoveItem(MetaTag);
	}

	FORCEINLINE void CleanEmptyMetaData( )
	{
		MetaList.CleanEmptyItem();
	}
};

USTRUCT()
struct FLFPTaggedChuckData
{
	GENERATED_BODY()

	FLFPTaggedChuckData( ) = default;

private:

	UPROPERTY()
	FGameplayTag ChuckTag = FGameplayTag::EmptyTag;

	UPROPERTY()
	FLFPPrimitiveDataTagArray ChuckMetaList = FLFPPrimitiveDataTagArray();

	UPROPERTY()
	FLFPTagTrackerStaticArray DataTagList = FLFPTagTrackerStaticArray();

	UPROPERTY()
	TArray< FLFPTaggedMetaData > DataMetaList = TArray< FLFPTaggedMetaData >();

public:

	FORCEINLINE void InitializeChuckData( const int32 NewDataIndexSize )
	{
		DataTagList = FLFPTagTrackerStaticArray(NewDataIndexSize);
	}

	FORCEINLINE void DeinitializeChuckData( )
	{
		DataTagList = FLFPTagTrackerStaticArray();
		DataMetaList.Empty();
	}

public:

	FORCEINLINE FGameplayTag GetChuckTag( ) const
	{
		return ChuckTag;
	}

	FORCEINLINE void SetChuckTag( const FGameplayTag& NewChuckTag )
	{
		ChuckTag = NewChuckTag;
	}

	FORCEINLINE void ResetChuckTag( )
	{
		ChuckTag = FGameplayTag::EmptyTag;
	}

public:

	FORCEINLINE const FLFPPrimitiveData* GetChuckMeta( const FGameplayTag& MetaTag ) const
	{
		return ChuckMetaList.GetItemConst(MetaTag);
	}

	FORCEINLINE FLFPPrimitiveData& GetOrAddChuckMeta( const FGameplayTag& MetaTag )
	{
		return ChuckMetaList.GetOrAddItem(MetaTag);
	}

	FORCEINLINE void RemoveChuckMeta( const FGameplayTag& MetaTag )
	{
		ChuckMetaList.RemoveItem(MetaTag);
	}

public:

	FORCEINLINE bool IsInitialized( ) const
	{
		return DataTagList.IsInitialized();
	}

	FORCEINLINE bool IsDataIndexValid( const int32 DataIndex ) const
	{
		return DataTagList.IsValidIndex(DataIndex);
	}

public:

	FORCEINLINE FGameplayTag GetDataTag( const int32 DataIndex ) const
	{
		check(DataTagList.IsValidIndex ( DataIndex ));

		return DataTagList.GetItem(DataIndex);
	}

	FORCEINLINE void SetDataTag( const int32 DataIndex , const FGameplayTag& NewDataTag )
	{
		check(DataTagList.IsValidIndex ( DataIndex ));

		DataTagList.SetItem(DataIndex, NewDataTag);
	}

public:

	FORCEINLINE TMap< int32 , int32 > GetDataMetaIndexMapping( ) const
	{
		TMap< int32 , int32 > ResultMapping;

		ResultMapping.Reserve(DataMetaList.Num());

		for ( int32 MetaIndex = 0 ; MetaIndex < DataMetaList.Num() ; MetaIndex++ )
		{
			ResultMapping.Add(DataMetaList[MetaIndex].GetDataIndex(), MetaIndex);
		}

		return ResultMapping;
	}

	FORCEINLINE int32 GetDataMetaIndex( const int32 DataIndex ) const
	{
		checkf(DataTagList.IsValidIndex ( DataIndex ),
		       TEXT(
			       "DataIndex invalid, call InitializeChuckData first. Resize chuck data after initialized not allow."
		       ));

		return DataMetaList.IndexOfByKey(DataIndex);
	}

	FORCEINLINE const FLFPPrimitiveData* GetDataMeta_Direct( const int32 DataMetaIndex , const FGameplayTag& MetaTag ) const
	{
		checkf(DataMetaList.IsValidIndex ( DataMetaIndex ),
		       TEXT(
			       "DataMetaIndex invalid"
		       ));

		return DataMetaList[DataMetaIndex].GetMetaData(MetaTag);
	}

	FORCEINLINE FLFPPrimitiveData& GetOrAddDataMeta_Direct( const int32 DataMetaIndex , const FGameplayTag& MetaTag )
	{
		checkf(DataMetaList.IsValidIndex ( DataMetaIndex ),
		       TEXT(
			       "DataMetaIndex invalid"
		       ));

		return DataMetaList[DataMetaIndex].GetOrAddMetaData(MetaTag);
	}

public:

	FORCEINLINE const FLFPPrimitiveData* GetDataMeta( const int32 DataIndex , const FGameplayTag& MetaTag ) const
	{
		checkf(DataTagList.IsValidIndex ( DataIndex ),
		       TEXT(
			       "DataIndex invalid, call InitializeChuckData first. Resize chuck data after initialized not allow."
		       ));

		if ( const int32 MetaDataIndex = DataMetaList.IndexOfByKey(DataIndex) ; MetaDataIndex != INDEX_NONE )
		{
			return DataMetaList[MetaDataIndex].GetMetaData(MetaTag);
		}

		return nullptr;
	}

	FORCEINLINE FLFPPrimitiveData& GetOrAddDataMeta( const int32 DataIndex , const FGameplayTag& MetaTag )
	{
		checkf(DataTagList.IsValidIndex ( DataIndex ),
		       TEXT(
			       "DataIndex invalid, call InitializeChuckData first. Resize chuck data after initialized not allow."
		       ));

		if ( const int32 MetaDataIndex = DataMetaList.IndexOfByKey(DataIndex) ; MetaDataIndex != INDEX_NONE )
		{
			return DataMetaList[MetaDataIndex].GetOrAddMetaData(MetaTag);
		}

		return DataMetaList.Add_GetRef(FLFPTaggedMetaData(DataIndex)).GetOrAddMetaData(MetaTag);
	}

	FORCEINLINE void RemoveDataMeta( const int32 DataIndex , const FGameplayTag& MetaTag )
	{
		checkf(DataTagList.IsValidIndex ( DataIndex ),
		       TEXT(
			       "DataIndex is invalid, call InitializeChuckData first. Resize chuck data after initialized is not allow"
		       ));

		if ( FLFPTaggedMetaData* MetaDataPtr = DataMetaList.FindByKey(DataIndex) ; MetaDataPtr != nullptr )
		{
			MetaDataPtr->RemoveMetaData(MetaTag);
		}
	}

public:

	FORCEINLINE void CleanEmptyMetaData( )
	{
		for ( FLFPTaggedMetaData& GridMeta : DataMetaList )
		{
			GridMeta.CleanEmptyMetaData();
		}

		ChuckMetaList.CleanEmptyItem();
	}
};

USTRUCT()
struct FLFPTaggedRegionData
{
	GENERATED_BODY()

private:

	UPROPERTY()
	FGameplayTag RegionTag = FGameplayTag::EmptyTag;

	UPROPERTY()
	FLFPPrimitiveDataTagArray RegionMetaList = FLFPPrimitiveDataTagArray();

	UPROPERTY()
	TArray< FLFPTaggedChuckData > ChuckList = TArray< FLFPTaggedChuckData >();

public:

	FORCEINLINE void InitializeRegionData( const int32 NewChuckIndexSize )
	{
		ChuckList.Reset(NewChuckIndexSize);
		ChuckList.SetNum(NewChuckIndexSize);
	}

	FORCEINLINE void DeinitializeRegionData( )
	{
		ChuckList.Empty();
	}

public:

	FORCEINLINE FGameplayTag GetRegionTag( ) const
	{
		return RegionTag;
	}

	FORCEINLINE void SetRegionTag( const FGameplayTag& NewChuckTag )
	{
		RegionTag = NewChuckTag;
	}

	FORCEINLINE void ResetRegionTag( )
	{
		RegionTag = FGameplayTag::EmptyTag;
	}

public:

	FORCEINLINE const FLFPPrimitiveData* GetRegionMeta( const FGameplayTag& MetaTag ) const
	{
		return RegionMetaList.GetItemConst(MetaTag);
	}

	FORCEINLINE FLFPPrimitiveData& GetOrAddRegionMeta( const FGameplayTag& MetaTag )
	{
		return RegionMetaList.GetOrAddItem(MetaTag);
	}

	FORCEINLINE void RemoveRegionMeta( const FGameplayTag& MetaTag )
	{
		RegionMetaList.RemoveItem(MetaTag);
	}

public:

	FORCEINLINE bool IsInitialized( ) const
	{
		return ChuckList.IsEmpty() == false;
	}

	FORCEINLINE bool IsChuckIndexValid( const int32 ChuckIndex ) const
	{
		return ChuckList.IsValidIndex(ChuckIndex);
	}

public:

	FORCEINLINE const FLFPTaggedChuckData& GetChuck( const int32 ChuckIndex ) const
	{
		checkf(ChuckList.IsValidIndex ( ChuckIndex ),
		       TEXT(
			       "ChuckIndex invalid, call InitializeRegionData first. Resize region data after initialized not allow."
		       ));

		return ChuckList[ChuckIndex];
	}

	FORCEINLINE FLFPTaggedChuckData& GetChuck( const int32 ChuckIndex )
	{
		checkf(ChuckList.IsValidIndex ( ChuckIndex ),
		       TEXT(
			       "ChuckIndex invalid, call InitializeRegionData first. Resize region data after initialized not allow."
		       ));

		return ChuckList[ChuckIndex];
	}

public:

	FORCEINLINE void CleanEmptyMetaData( )
	{
		for ( FLFPTaggedChuckData& ChuckData : ChuckList )
		{
			ChuckData.CleanEmptyMetaData();
		}

		RegionMetaList.CleanEmptyItem();
	}
};

USTRUCT(BlueprintType)
struct FLFPChunkedTagSerializeData
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TArray< uint8 > DataList = TArray< uint8 >();

	UPROPERTY()
	FName CompressionName = NAME_Oodle;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FLFPChuckedTagData_TagChanged, const int32, RegionIndex, const int32, ChuckIndex, const int32, DataIndex, const FGameplayTag&, OldTag, const FGameplayTag&, NewTag);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FLFPChuckedTagData_MetaChanged, const int32, RegionIndex, const int32, ChuckIndex, const int32, DataIndex, const FGameplayTag&, MetaTag, const FLFPPrimitiveData&, OldMetaData, const FLFPPrimitiveData&, NewMetaData);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LOHFUNCTIONPLUGIN_API ULFPChunkedTagDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// Sets default values for this component's properties
	ULFPChunkedTagDataComponent( );

protected:

	// Called when the game starts
	virtual void BeginPlay( ) override;

public:

	// Called every frame
	virtual void TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;

public:

	UFUNCTION(BlueprintCallable)
	void LoadRegion( const int32 RegionIndex , const FLFPChunkedTagSerializeData& LoadData );

	UFUNCTION(BlueprintCallable)
	void SaveRegion( const int32 RegionIndex , FLFPChunkedTagSerializeData& SaveData );

public:

	UFUNCTION(BlueprintCallable)
	void InitializeChuck( const int32 RegionIndex , const int32 ChuckIndex );

	UFUNCTION(BlueprintCallable)
	void DeinitializeChuck( const int32 RegionIndex , const int32 ChuckIndex );

	UFUNCTION(BlueprintCallable)
	void InitializeRegion( const int32 RegionIndex );

	UFUNCTION(BlueprintCallable)
	void DeinitializeRegion( const int32 RegionIndex );

public:

	// Faster version of get data tag without check
	FORCEINLINE FGameplayTag GetDataTag_Checked( const int32 RegionIndex , const int32 ChuckIndex , const int32 DataIndex ) const;

	// Get existing all data index to data meta index mapping
	FORCEINLINE TMap< int32 , int32 > GetDataMeta_Mapping( const int32 RegionIndex , const int32 ChuckIndex ) const;

	// Get meta by data meta index from mapping
	FORCEINLINE const FLFPPrimitiveData* GetDataMeta_Direct( const int32 RegionIndex , const int32 ChuckIndex , const int32 MappingIndex , const FGameplayTag& DataMetaTag ) const;

public:

	UFUNCTION(BlueprintCallable)
	FGameplayTag GetDataTag( const int32 RegionIndex , const int32 ChuckIndex , const int32 DataIndex ) const;

	UFUNCTION(BlueprintCallable)
	void SetDataTag( const int32 RegionIndex , const int32 ChuckIndex , const int32 DataIndex , const FGameplayTag& NewDataTag );

	UFUNCTION(BlueprintCallable)
	FLFPPrimitiveData GetDataMeta( const int32 RegionIndex , const int32 ChuckIndex , const int32 DataIndex , const FGameplayTag& DataMetaTag ) const;

	UFUNCTION(BlueprintCallable)
	void SetDataMeta( const int32 RegionIndex , const int32 ChuckIndex , const int32 DataIndex , const FGameplayTag& DataMetaTag , const FLFPPrimitiveData& NewDataMeta );

public:

	UFUNCTION(BlueprintCallable)
	FGameplayTag GetChuckTag( const int32 RegionIndex , const int32 ChuckIndex ) const;

	UFUNCTION(BlueprintCallable)
	void SetChuckTag( const int32 RegionIndex , const int32 ChuckIndex , const FGameplayTag& NewChuckTag );

	UFUNCTION(BlueprintCallable)
	FLFPPrimitiveData GetChuckMeta( const int32 RegionIndex , const int32 ChuckIndex , const FGameplayTag& ChuckMetaTag ) const;

	UFUNCTION(BlueprintCallable)
	void SetChuckMeta( const int32 RegionIndex , const int32 ChuckIndex , const FGameplayTag& ChuckMetaTag , const FLFPPrimitiveData& NewChuckMeta );

public:

	UFUNCTION(BlueprintCallable)
	FGameplayTag GetRegionTag( const int32 RegionIndex ) const;

	UFUNCTION(BlueprintCallable)
	void SetRegionTag( const int32 RegionIndex , const FGameplayTag& NewRegionTag );

	UFUNCTION(BlueprintCallable)
	FLFPPrimitiveData GetRegionMeta( const int32 RegionIndex , const FGameplayTag& RegionMetaTag ) const;

	UFUNCTION(BlueprintCallable)
	void SetRegionMeta( const int32 RegionIndex , const FGameplayTag& RegionMetaTag , const FLFPPrimitiveData& NewRegionMeta );

public:

	UFUNCTION(BlueprintCallable)
	bool IsGridValid( const int32 RegionIndex , const int32 ChuckIndex , const int32 DataIndex ) const;

	UFUNCTION(BlueprintCallable)
	bool IsChuckValid( const int32 RegionIndex , const int32 ChuckIndex ) const;

	UFUNCTION(BlueprintCallable)
	bool IsRegionValid( const int32 RegionIndex ) const;

public:

	UFUNCTION(BlueprintCallable)
	bool IsChuckInitialized( const int32 RegionIndex , const int32 ChuckIndex ) const;

	UFUNCTION(BlueprintCallable)
	bool IsRegionInitialized( const int32 RegionIndex ) const;

public:

	UPROPERTY(BlueprintAssignable)
	FLFPChuckedTagData_TagChanged OnTagChanged;

	UPROPERTY(BlueprintAssignable)
	FLFPChuckedTagData_MetaChanged OnMetaChanged;

private:

	UPROPERTY()
	TArray< FLFPTaggedRegionData > GridDataList = TArray< FLFPTaggedRegionData >();

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting")
	int32 DataIndexSize = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting")
	int32 ChuckIndexSize = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting")
	int32 RegionIndexSize = 1;
};
