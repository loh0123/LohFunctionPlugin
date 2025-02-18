// Copyright (c) 2023-2025 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

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
struct FLFPTaggedChunkData
{
	GENERATED_BODY()

	FLFPTaggedChunkData( ) = default;

private:

	UPROPERTY()
	FGameplayTag ChunkTag = FGameplayTag::EmptyTag;

	UPROPERTY()
	FLFPPrimitiveDataTagArray ChunkMetaList = FLFPPrimitiveDataTagArray();

	UPROPERTY()
	FLFPTagTrackerStaticArray DataTagList = FLFPTagTrackerStaticArray();

	UPROPERTY()
	TArray< FLFPTaggedMetaData > DataMetaList = TArray< FLFPTaggedMetaData >();

public:

	FORCEINLINE void InitializeChunkData( const int32 NewDataIndexSize , const FGameplayTag& FillTag )
	{
		DataTagList = FLFPTagTrackerStaticArray(NewDataIndexSize);

		if ( FillTag.IsValid() )
		{
			for ( int32 Index = 0 ; Index < NewDataIndexSize ; ++Index )
			{
				SetDataTag(Index, FillTag);
			}
		}
	}

	FORCEINLINE void DeinitializeChunkData( )
	{
		DataTagList = FLFPTagTrackerStaticArray();
		DataMetaList.Empty();
	}

public:

	FORCEINLINE FGameplayTag GetChunkTag( ) const
	{
		return ChunkTag;
	}

	FORCEINLINE void SetChunkTag( const FGameplayTag& NewChunkTag )
	{
		ChunkTag = NewChunkTag;
	}

	FORCEINLINE void ResetChunkTag( )
	{
		ChunkTag = FGameplayTag::EmptyTag;
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

		return DataMetaList.Add_GetRef(FLFPTaggedMetaData(DataIndex)).GetOrAddMetaData(MetaTag);
	}

	FORCEINLINE void RemoveDataMeta( const int32 DataIndex , const FGameplayTag& MetaTag )
	{
		checkf(DataTagList.IsValidIndex ( DataIndex ),
		       TEXT(
			       "DataIndex is invalid, call InitializeChunkData first. Resize Chunk data after initialized is not allow"
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

		ChunkMetaList.CleanEmptyItem();
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
	TArray< FLFPTaggedChunkData > ChunkList = TArray< FLFPTaggedChunkData >();

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

	FORCEINLINE FGameplayTag GetRegionTag( ) const
	{
		return RegionTag;
	}

	FORCEINLINE void SetRegionTag( const FGameplayTag& NewChunkTag )
	{
		RegionTag = NewChunkTag;
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
		return ChunkList.IsEmpty() == false;
	}

	FORCEINLINE bool IsChunkIndexValid( const int32 ChunkIndex ) const
	{
		return ChunkList.IsValidIndex(ChunkIndex);
	}

public:

	FORCEINLINE const FLFPTaggedChunkData& GetChunk( const int32 ChunkIndex ) const
	{
		checkf(ChunkList.IsValidIndex ( ChunkIndex ),
		       TEXT(
			       "ChunkIndex invalid, call InitializeRegionData first. Resize region data after initialized not allow."
		       ));

		return ChunkList[ChunkIndex];
	}

	FORCEINLINE FLFPTaggedChunkData& GetChunk( const int32 ChunkIndex )
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
		for ( FLFPTaggedChunkData& ChunkData : ChunkList )
		{
			ChunkData.CleanEmptyMetaData();
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FLFPChunkedTagData_TagChanged, const int32, RegionIndex, const int32, ChunkIndex, const int32, DataIndex, const FGameplayTag&, OldTag, const FGameplayTag&, NewTag);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FLFPChunkedTagData_MetaChanged, const int32, RegionIndex, const int32, ChunkIndex, const int32, DataIndex, const FGameplayTag&, MetaTag, const FLFPPrimitiveData&, OldMetaData, const FLFPPrimitiveData&, NewMetaData);

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

	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="FillTag"))
	void InitializeChunk( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& FillTag );

	UFUNCTION(BlueprintCallable)
	void DeinitializeChunk( const int32 RegionIndex , const int32 ChunkIndex );

	UFUNCTION(BlueprintCallable)
	void InitializeRegion( const int32 RegionIndex );

	UFUNCTION(BlueprintCallable)
	void DeinitializeRegion( const int32 RegionIndex );

public:

	// Faster version of get data tag without check
	FORCEINLINE FGameplayTag GetDataTag_Checked( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

	// Get existing all data index to data meta index mapping
	FORCEINLINE TMap< int32 , int32 > GetDataMeta_Mapping( const int32 RegionIndex , const int32 ChunkIndex ) const;

	// Get meta by data meta index from mapping
	FORCEINLINE const FLFPPrimitiveData* GetDataMeta_Direct( const int32 RegionIndex , const int32 ChunkIndex , const int32 MappingIndex , const FGameplayTag& DataMetaTag ) const;

public:

	UFUNCTION(BlueprintCallable)
	FGameplayTag GetDataTag( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="NewDataTag"))
	void SetDataTag( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FGameplayTag& NewDataTag );

	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="DataMetaTag"))
	FLFPPrimitiveData GetDataMeta( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FGameplayTag& DataMetaTag ) const;

	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="DataMetaTag"))
	void SetDataMeta( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FGameplayTag& DataMetaTag , const FLFPPrimitiveData& NewDataMeta );

public:

	UFUNCTION(BlueprintCallable)
	FGameplayTag GetChunkTag( const int32 RegionIndex , const int32 ChunkIndex ) const;

	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="NewChunkTag"))
	void SetChunkTag( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& NewChunkTag );

	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="ChunkMetaTag"))
	FLFPPrimitiveData GetChucnMeta( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& ChunkMetaTag ) const;

	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="ChunkMetaTag"))
	void SetChunkMeta( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& ChunkMetaTag , const FLFPPrimitiveData& NewChunkMeta );

public:

	UFUNCTION(BlueprintCallable)
	FGameplayTag GetRegionTag( const int32 RegionIndex ) const;

	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="NewRegionTag"))
	void SetRegionTag( const int32 RegionIndex , const FGameplayTag& NewRegionTag );

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

	UPROPERTY(BlueprintAssignable)
	FLFPChunkedTagData_TagChanged OnTagChanged;

	UPROPERTY(BlueprintAssignable)
	FLFPChunkedTagData_MetaChanged OnMetaChanged;

private:

	UPROPERTY()
	TArray< FLFPTaggedRegionData > GridDataList = TArray< FLFPTaggedRegionData >();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting|IndexSize")
	int32 DataIndexSize = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting|IndexSize")
	int32 ChunkIndexSize = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting|IndexSize")
	int32 RegionIndexSize = 1;
};
