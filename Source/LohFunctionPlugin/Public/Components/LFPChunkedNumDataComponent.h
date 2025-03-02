// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Library/LFPDynamicTypeLibrary.h"
#include "LFPChunkedNumDataComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogChunkedNumDataComponent, Log, All);

USTRUCT()
struct FLFPNumMetaData
{
	GENERATED_BODY()

	FLFPNumMetaData( ) = default;

	explicit FLFPNumMetaData( int32 DataIndex ) :
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
struct FLFPNumChunkData
{
	GENERATED_BODY()

	FLFPNumChunkData( ) = default;

private:

	UPROPERTY()
	int32 ChunkID = INDEX_NONE;

	UPROPERTY()
	FLFPPrimitiveDataTagArray ChunkMetaList = FLFPPrimitiveDataTagArray();

	UPROPERTY()
	FLFPIDTrackerStaticArray DataTagList = FLFPIDTrackerStaticArray();

	UPROPERTY()
	TArray< FLFPNumMetaData > DataMetaList = TArray< FLFPNumMetaData >();

public:

	FORCEINLINE void InitializeChunkData( const int32 NewDataIndexSize , const int32 FillID )
	{
		DataTagList = FLFPIDTrackerStaticArray(NewDataIndexSize);

		if ( FillID >= 0 )
		{
			for ( int32 Index = 0 ; Index < NewDataIndexSize ; ++Index )
			{
				SetDataID(Index, FillID);
			}
		}
	}

	FORCEINLINE void DeinitializeChunkData( )
	{
		DataTagList = FLFPIDTrackerStaticArray();
		DataMetaList.Empty();
	}

public:

	FORCEINLINE int32 GetChunkID( ) const
	{
		return ChunkID;
	}

	FORCEINLINE void SetChunkID( const int32 NewChunkID )
	{
		ChunkID = NewChunkID;
	}

	FORCEINLINE void ResetChunkID( )
	{
		ChunkID = INDEX_NONE;
	}

public:

	FORCEINLINE const FLFPPrimitiveData* GetChunkMeta( const FGameplayTag& MetaTag ) const
	{
		return ChunkMetaList.GetItemConst(MetaTag);
	}

	FORCEINLINE FLFPPrimitiveData& GetOrAddChunkMeta( const FGameplayTag& MetaTag )
	{
		return ChunkMetaList.GetOrAddItem(MetaTag);
	}

	FORCEINLINE void RemoveChunkMeta( const FGameplayTag& MetaTag )
	{
		ChunkMetaList.RemoveItem(MetaTag);
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

	FORCEINLINE int32 GetDataID( const int32 DataIndex ) const
	{
		check(DataTagList.IsValidIndex ( DataIndex ));

		return DataTagList.GetItem(DataIndex);
	}

	FORCEINLINE void SetDataID( const int32 DataIndex , const int32 NewDataID )
	{
		check(DataTagList.IsValidIndex ( DataIndex ));

		DataTagList.SetItem(DataIndex, NewDataID);
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
			       "DataIndex invalid, call InitializeChunkData first. Resize Chunk data after initialized not allow."
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
			       "DataIndex invalid, call InitializeChunkData first. Resize Chunk data after initialized not allow."
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
			       "DataIndex invalid, call InitializeChunkData first. Resize Chunk data after initialized not allow."
		       ));

		if ( const int32 MetaDataIndex = DataMetaList.IndexOfByKey(DataIndex) ; MetaDataIndex != INDEX_NONE )
		{
			return DataMetaList[MetaDataIndex].GetOrAddMetaData(MetaTag);
		}

		return DataMetaList.Add_GetRef(FLFPNumMetaData(DataIndex)).GetOrAddMetaData(MetaTag);
	}

	FORCEINLINE void RemoveDataMeta( const int32 DataIndex , const FGameplayTag& MetaTag )
	{
		checkf(DataTagList.IsValidIndex ( DataIndex ),
		       TEXT(
			       "DataIndex is invalid, call InitializeChunkData first. Resize Chunk data after initialized is not allow"
		       ));

		if ( FLFPNumMetaData* MetaDataPtr = DataMetaList.FindByKey(DataIndex) ; MetaDataPtr != nullptr )
		{
			MetaDataPtr->RemoveMetaData(MetaTag);
		}
	}

public:

	FORCEINLINE void CleanEmptyMetaData( )
	{
		for ( FLFPNumMetaData& GridMeta : DataMetaList )
		{
			GridMeta.CleanEmptyMetaData();
		}

		ChunkMetaList.CleanEmptyItem();
	}
};

USTRUCT()
struct FLFPNumRegionData
{
	GENERATED_BODY()

private:

	UPROPERTY()
	int32 RegionID = INDEX_NONE;

	UPROPERTY()
	FLFPPrimitiveDataTagArray RegionMetaList = FLFPPrimitiveDataTagArray();

	UPROPERTY()
	TArray< FLFPNumChunkData > ChunkList = TArray< FLFPNumChunkData >();

public:

	FORCEINLINE void InitializeRegionData( const int32 NewChunkIndexSize )
	{
		ChunkList.Reset(NewChunkIndexSize);
		ChunkList.SetNum(NewChunkIndexSize);
	}

	FORCEINLINE void DeinitializeRegionData( )
	{
		ChunkList.Empty();
	}

public:

	FORCEINLINE int32 GetRegionID( ) const
	{
		return RegionID;
	}

	FORCEINLINE void SetRegionID( const int32 NewChunkID )
	{
		RegionID = NewChunkID;
	}

	FORCEINLINE void ResetRegionID( )
	{
		RegionID = INDEX_NONE;
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
		return ChunkList.IsEmpty() == false;
	}

	FORCEINLINE bool IsChunkIndexValid( const int32 ChunkIndex ) const
	{
		return ChunkList.IsValidIndex(ChunkIndex);
	}

public:

	FORCEINLINE const FLFPNumChunkData& GetChunk( const int32 ChunkIndex ) const
	{
		checkf(ChunkList.IsValidIndex ( ChunkIndex ),
		       TEXT(
			       "ChunkIndex invalid, call InitializeRegionData first. Resize region data after initialized not allow."
		       ));

		return ChunkList[ChunkIndex];
	}

	FORCEINLINE FLFPNumChunkData& GetChunk( const int32 ChunkIndex )
	{
		checkf(ChunkList.IsValidIndex ( ChunkIndex ),
		       TEXT(
			       "ChunkIndex invalid, call InitializeRegionData first. Resize region data after initialized not allow."
		       ));

		return ChunkList[ChunkIndex];
	}

public:

	FORCEINLINE void CleanEmptyMetaData( )
	{
		for ( FLFPNumChunkData& ChunkData : ChunkList )
		{
			ChunkData.CleanEmptyMetaData();
		}

		RegionMetaList.CleanEmptyItem();
	}
};

USTRUCT(BlueprintType)
struct FLFPChunkedNumSerializeData
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TArray< uint8 > DataList = TArray< uint8 >();

	UPROPERTY()
	FName CompressionName = NAME_Oodle;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FLFPChunkedNumData_TagChanged, const int32, RegionIndex, const int32, ChunkIndex, const int32, DataIndex, const int32, OldID, const int32, NewID);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FLFPChunkedNumData_MetaChanged, const int32, RegionIndex, const int32, ChunkIndex, const int32, DataIndex, const FGameplayTag&, MetaTag, const FLFPPrimitiveData&, OldMetaData, const FLFPPrimitiveData&, NewMetaData);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LOHFUNCTIONPLUGIN_API ULFPChunkedNumDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// Sets default values for this component's properties
	ULFPChunkedNumDataComponent( );

protected:

	// Called when the game starts
	virtual void BeginPlay( ) override;

public:

	// Called every frame
	virtual void TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;

public:

	UFUNCTION(BlueprintCallable)
	void LoadRegion( const int32 RegionIndex , const FLFPChunkedNumSerializeData& LoadData );

	UFUNCTION(BlueprintCallable)
	void SaveRegion( const int32 RegionIndex , FLFPChunkedNumSerializeData& SaveData );

public:

	UFUNCTION(BlueprintCallable)
	void InitializeChunk( const int32 RegionIndex , const int32 ChunkIndex , const int32 FillID );

	UFUNCTION(BlueprintCallable)
	void DeinitializeChunk( const int32 RegionIndex , const int32 ChunkIndex );

	UFUNCTION(BlueprintCallable)
	void InitializeRegion( const int32 RegionIndex );

	UFUNCTION(BlueprintCallable)
	void DeinitializeRegion( const int32 RegionIndex );

public:

	// Faster version of get data ID without check
	FORCEINLINE int32 GetDataID_Checked( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

	// Get existing all data index to data meta index mapping
	FORCEINLINE TMap< int32 , int32 > GetDataMeta_Mapping( const int32 RegionIndex , const int32 ChunkIndex ) const;

	// Get meta by data meta index from mapping
	FORCEINLINE const FLFPPrimitiveData* GetDataMeta_Direct( const int32 RegionIndex , const int32 ChunkIndex , const int32 MappingIndex , const FGameplayTag& DataMetaTag ) const;

public:

	UFUNCTION(BlueprintCallable)
	int32 GetDataID( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

	UFUNCTION(BlueprintCallable)
	void SetDataID( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const int32 NewDataID );

	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="DataMetaTag"))
	FLFPPrimitiveData GetDataMeta( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FGameplayTag& DataMetaTag ) const;

	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="DataMetaTag"))
	void SetDataMeta( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FGameplayTag& DataMetaTag , const FLFPPrimitiveData& NewDataMeta );

public:

	UFUNCTION(BlueprintCallable)
	int32 GetChunkID( const int32 RegionIndex , const int32 ChunkIndex ) const;

	UFUNCTION(BlueprintCallable)
	void SetChunkID( const int32 RegionIndex , const int32 ChunkIndex , const int32 NewChunkID );

	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="ChunkMetaTag"))
	FLFPPrimitiveData GetChunkMeta( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& ChunkMetaTag ) const;

	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="ChunkMetaTag"))
	void SetChunkMeta( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& ChunkMetaTag , const FLFPPrimitiveData& NewChunkMeta );

public:

	UFUNCTION(BlueprintCallable)
	int32 GetRegionID( const int32 RegionIndex ) const;

	UFUNCTION(BlueprintCallable)
	void SetRegionID( const int32 RegionIndex , const int32 NewRegionID );

	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="RegionMetaTag"))
	FLFPPrimitiveData GetRegionMeta( const int32 RegionIndex , const FGameplayTag& RegionMetaTag ) const;

	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="RegionMetaTag"))
	void SetRegionMeta( const int32 RegionIndex , const FGameplayTag& RegionMetaTag , const FLFPPrimitiveData& NewRegionMeta );

public:

	UFUNCTION(BlueprintCallable)
	bool IsDataIndexValid( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

	UFUNCTION(BlueprintCallable)
	bool IsChunkIndexValid( const int32 RegionIndex , const int32 ChunkIndex ) const;

	UFUNCTION(BlueprintCallable)
	bool IsRegionIndexValid( const int32 RegionIndex ) const;

public:

	UFUNCTION(BlueprintCallable)
	bool IsChunkInitialized( const int32 RegionIndex , const int32 ChunkIndex ) const;

	UFUNCTION(BlueprintCallable)
	bool IsRegionInitialized( const int32 RegionIndex ) const;

public:

	UFUNCTION(BlueprintPure)
	int32 GetDataIndexSize( ) const;

	UFUNCTION(BlueprintPure)
	int32 GetChunkIndexSize( ) const;

	UFUNCTION(BlueprintPure)
	int32 GetRegionIndexSize( ) const;

public:

	UPROPERTY(BlueprintAssignable)
	FLFPChunkedNumData_TagChanged OnIDChanged;

	UPROPERTY(BlueprintAssignable)
	FLFPChunkedNumData_MetaChanged OnMetaChanged;

private:

	UPROPERTY()
	TArray< FLFPNumRegionData > RegionDataList = TArray< FLFPNumRegionData >();

protected:

	UPROPERTY(EditAnywhere, Category = "Setting|IndexSize")
	int32 DataIndexSize = 1;

	UPROPERTY(EditAnywhere, Category = "Setting|IndexSize")
	int32 ChunkIndexSize = 1;

	UPROPERTY(EditAnywhere, Category = "Setting|IndexSize")
	int32 RegionIndexSize = 1;
};
