// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Library/LFPDynamicTypeLibrary.h"
#include "LFPChunkedNumDataComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN ( LogChunkedNumDataComponent , Log , All );

USTRUCT ( )
struct FLFPNumMetaData
{
	GENERATED_BODY ( )

	FLFPNumMetaData ( ) = default;

	explicit FLFPNumMetaData ( int32 DataIndex ) : DataIndex ( DataIndex )
	{
	}

private:

	UPROPERTY ( )
	int32 DataIndex = INDEX_NONE;

	UPROPERTY ( )
	FLFPInstancedStructTagArray MetaList = FLFPInstancedStructTagArray ( );

public:

	FORCEINLINE bool operator== ( const int32 FindingIndex ) const
	{
		return DataIndex == FindingIndex;
	}

public:

	FORCEINLINE int32 GetDataIndex ( ) const
	{
		return DataIndex;
	}

	FORCEINLINE void SetDataIndex ( const int32 NewDataIndex )
	{
		DataIndex = NewDataIndex;
	}

public:

	FORCEINLINE const TArray < FGameplayTag >& GetMetaDataTagList ( ) const
	{
		return MetaList.GetMappingList ( );
	}

	FORCEINLINE const FInstancedStruct* GetMetaData ( const FGameplayTag& MetaTag ) const
	{
		return MetaList.GetItemConst ( MetaTag );
	}

	FORCEINLINE FInstancedStruct& GetOrAddMetaData ( const FGameplayTag& MetaTag )
	{
		return MetaList.GetOrAddItem ( MetaTag );
	}

	FORCEINLINE void RemoveMetaData ( const FGameplayTag& MetaTag )
	{
		MetaList.RemoveItem ( MetaTag );
	}

	FORCEINLINE void CleanEmptyMetaData ( )
	{
		MetaList.CleanEmptyItem ( );
	}
};

USTRUCT ( )
struct FLFPNumChunkData
{
	GENERATED_BODY ( )

	FLFPNumChunkData ( ) = default;

private:

	UPROPERTY ( )
	int32 ChunkID = INDEX_NONE;

	UPROPERTY ( )
	FLFPInstancedStructTagArray ChunkMetaList = FLFPInstancedStructTagArray ( );

	UPROPERTY ( )
	FLFPIDTrackerStaticArray DataTagList = FLFPIDTrackerStaticArray ( );

	UPROPERTY ( )
	TArray < FLFPNumMetaData > DataMetaList = TArray < FLFPNumMetaData > ( );

public:

	FORCEINLINE void InitializeChunkData ( const int32 NewDataIndexSize , const int32 FillID )
	{
		DataTagList = FLFPIDTrackerStaticArray ( NewDataIndexSize );

		if ( FillID >= 0 )
		{
			for ( int32 Index = 0 ; Index < NewDataIndexSize ; ++Index )
			{
				SetDataID ( Index , FillID );
			}
		}
	}

	FORCEINLINE void DeinitializeChunkData ( )
	{
		DataTagList = FLFPIDTrackerStaticArray ( );
		DataMetaList.Empty ( );
	}

public:

	FORCEINLINE int32 GetChunkID ( ) const
	{
		return ChunkID;
	}

	FORCEINLINE void SetChunkID ( const int32 NewChunkID )
	{
		ChunkID = NewChunkID;
	}

	FORCEINLINE void ResetChunkID ( )
	{
		ChunkID = INDEX_NONE;
	}

public:

	FORCEINLINE const FInstancedStruct* GetChunkMeta ( const FGameplayTag& MetaTag ) const
	{
		return ChunkMetaList.GetItemConst ( MetaTag );
	}

	FORCEINLINE FInstancedStruct& GetOrAddChunkMeta ( const FGameplayTag& MetaTag )
	{
		return ChunkMetaList.GetOrAddItem ( MetaTag );
	}

	FORCEINLINE void RemoveChunkMeta ( const FGameplayTag& MetaTag )
	{
		ChunkMetaList.RemoveItem ( MetaTag );
	}

public:

	FORCEINLINE bool IsInitialized ( ) const
	{
		return DataTagList.IsInitialized ( );
	}

	FORCEINLINE bool IsDataIndexValid ( const int32 DataIndex ) const
	{
		return DataTagList.IsValidIndex ( DataIndex );
	}

public:

	FORCEINLINE int32 GetDataID ( const int32 DataIndex ) const
	{
		check ( DataTagList.IsValidIndex ( DataIndex ) );

		return DataTagList.GetItem ( DataIndex );
	}

	FORCEINLINE void SetDataID ( const int32 DataIndex , const int32 NewDataID )
	{
		check ( DataTagList.IsValidIndex ( DataIndex ) );

		DataTagList.SetItem ( DataIndex , NewDataID );
	}

public:

	FORCEINLINE const TArray < int32 >& GetDataIDList ( ) const
	{
		return DataTagList.GetItemList ( );
	}

	FORCEINLINE const FLFPNumMetaData* GetDataMetaList ( const int32 DataIndex ) const
	{
		return DataMetaList.FindByKey ( DataIndex );
	}

	FORCEINLINE FLFPNumMetaData* GetDataMetaList_Mutable ( const int32 DataIndex )
	{
		return DataMetaList.FindByKey ( DataIndex );
	}

	FORCEINLINE const FLFPNumMetaData* GetDataMetaList_Direct ( const int32 DataMetaIndex ) const
	{
		return DataMetaList.IsValidIndex ( DataMetaIndex )
		       ? &DataMetaList [ DataMetaIndex ]
		       : nullptr;
	}

	FORCEINLINE FLFPNumMetaData* GetDataMetaList_Direct_Mutable ( const int32 DataMetaIndex )
	{
		return DataMetaList.IsValidIndex ( DataMetaIndex )
		       ? &DataMetaList [ DataMetaIndex ]
		       : nullptr;
	}

public:

	FORCEINLINE int32 GetDataMetaNum ( ) const
	{
		return DataMetaList.Num ( );
	}

public:

	FORCEINLINE const FInstancedStruct* GetDataMeta ( const int32 DataIndex , const FGameplayTag& MetaTag ) const
	{
		checkf ( DataTagList.IsValidIndex ( DataIndex ) ,
		         TEXT(
			         "DataIndex invalid, call InitializeChunkData first. Resize Chunk data after initialized not allow."
		         ) );

		if ( const int32 MetaDataIndex = DataMetaList.IndexOfByKey ( DataIndex ) ; MetaDataIndex != INDEX_NONE )
		{
			return DataMetaList [ MetaDataIndex ].GetMetaData ( MetaTag );
		}

		return nullptr;
	}

	FORCEINLINE FInstancedStruct& GetOrAddDataMeta ( const int32 DataIndex , const FGameplayTag& MetaTag )
	{
		checkf ( DataTagList.IsValidIndex ( DataIndex ) ,
		         TEXT(
			         "DataIndex invalid, call InitializeChunkData first. Resize Chunk data after initialized not allow."
		         ) );

		if ( const int32 MetaDataIndex = DataMetaList.IndexOfByKey ( DataIndex ) ; MetaDataIndex != INDEX_NONE )
		{
			return DataMetaList [ MetaDataIndex ].GetOrAddMetaData ( MetaTag );
		}

		return DataMetaList.Add_GetRef ( FLFPNumMetaData ( DataIndex ) ).GetOrAddMetaData ( MetaTag );
	}

	FORCEINLINE void RemoveDataMeta ( const int32 DataIndex , const FGameplayTag& MetaTag )
	{
		checkf ( DataTagList.IsValidIndex ( DataIndex ) ,
		         TEXT(
			         "DataIndex is invalid, call InitializeChunkData first. Resize Chunk data after initialized is not allow"
		         ) );

		if ( FLFPNumMetaData* MetaDataPtr = DataMetaList.FindByKey ( DataIndex ) ; MetaDataPtr != nullptr )
		{
			MetaDataPtr->RemoveMetaData ( MetaTag );
		}
	}

public:

	FORCEINLINE void CleanEmptyMetaData ( )
	{
		for ( FLFPNumMetaData& GridMeta : DataMetaList )
		{
			GridMeta.CleanEmptyMetaData ( );
		}

		ChunkMetaList.CleanEmptyItem ( );
	}
};

USTRUCT ( )
struct FLFPNumRegionData
{
	GENERATED_BODY ( )

private:

	UPROPERTY ( )
	int32 RegionID = INDEX_NONE;

	UPROPERTY ( )
	FLFPInstancedStructTagArray RegionMetaList = FLFPInstancedStructTagArray ( );

	UPROPERTY ( )
	TArray < FLFPNumChunkData > ChunkList = TArray < FLFPNumChunkData > ( );

public:

	FORCEINLINE void InitializeRegionData ( const int32 NewChunkIndexSize )
	{
		ChunkList.Reset ( NewChunkIndexSize );
		ChunkList.SetNum ( NewChunkIndexSize );
	}

	FORCEINLINE void DeinitializeRegionData ( )
	{
		ChunkList.Empty ( );
	}

public:

	FORCEINLINE int32 GetRegionID ( ) const
	{
		return RegionID;
	}

	FORCEINLINE void SetRegionID ( const int32 NewChunkID )
	{
		RegionID = NewChunkID;
	}

	FORCEINLINE void ResetRegionID ( )
	{
		RegionID = INDEX_NONE;
	}

public:

	FORCEINLINE const FInstancedStruct* GetRegionMeta ( const FGameplayTag& MetaTag ) const
	{
		return RegionMetaList.GetItemConst ( MetaTag );
	}

	FORCEINLINE FInstancedStruct& GetOrAddRegionMeta ( const FGameplayTag& MetaTag )
	{
		return RegionMetaList.GetOrAddItem ( MetaTag );
	}

	FORCEINLINE void RemoveRegionMeta ( const FGameplayTag& MetaTag )
	{
		RegionMetaList.RemoveItem ( MetaTag );
	}

public:

	FORCEINLINE bool IsInitialized ( ) const
	{
		return ChunkList.IsEmpty ( ) == false;
	}

	FORCEINLINE bool IsChunkIndexValid ( const int32 ChunkIndex ) const
	{
		return ChunkList.IsValidIndex ( ChunkIndex );
	}

public:

	FORCEINLINE const FLFPNumChunkData& GetChunk ( const int32 ChunkIndex ) const
	{
		checkf ( ChunkList.IsValidIndex ( ChunkIndex ) ,
		         TEXT(
			         "ChunkIndex invalid, call InitializeRegionData first. Resize region data after initialized not allow."
		         ) );

		return ChunkList [ ChunkIndex ];
	}

	FORCEINLINE FLFPNumChunkData& GetChunk ( const int32 ChunkIndex )
	{
		checkf ( ChunkList.IsValidIndex ( ChunkIndex ) ,
		         TEXT(
			         "ChunkIndex invalid, call InitializeRegionData first. Resize region data after initialized not allow."
		         ) );

		return ChunkList [ ChunkIndex ];
	}

public:

	FORCEINLINE void CleanEmptyMetaData ( )
	{
		for ( FLFPNumChunkData& ChunkData : ChunkList )
		{
			ChunkData.CleanEmptyMetaData ( );
		}

		RegionMetaList.CleanEmptyItem ( );
	}
};

USTRUCT ( BlueprintType )
struct FLFPChunkedNumSerializeData
{
	GENERATED_BODY ( )

public:

	UPROPERTY ( )
	TArray < uint8 > DataList = TArray < uint8 > ( );

	UPROPERTY ( )
	FName CompressionName = NAME_Oodle;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams ( FLFPChunkedNumData_TagChanged , const int32 , RegionIndex , const int32 , ChunkIndex , const int32 , DataIndex , const int32 , OldID , const int32 , NewID );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams ( FLFPChunkedNumData_MetaChanged , const int32 , RegionIndex , const int32 , ChunkIndex , const int32 , DataIndex , const FGameplayTag& , MetaTag , const FInstancedStruct& , OldMetaData , const FInstancedStruct& , NewMetaData );

UCLASS ( ClassGroup=(Custom) , meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPChunkedNumDataComponent : public UActorComponent
{
	GENERATED_BODY ( )

public:

	// Sets default values for this component's properties
	ULFPChunkedNumDataComponent ( );

protected:

	// Called when the game starts
	virtual void BeginPlay ( ) override;

public:

	// Called every frame
	virtual void TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;

public:

	UFUNCTION ( BlueprintCallable )
	void LoadRegion ( const int32 RegionIndex , const FLFPChunkedNumSerializeData& LoadData );

	UFUNCTION ( BlueprintCallable )
	void SaveRegion ( const int32 RegionIndex , FLFPChunkedNumSerializeData& SaveData );

public:

	UFUNCTION ( BlueprintCallable )
	void InitializeChunk ( const int32 RegionIndex , const int32 ChunkIndex , const int32 FillID );

	UFUNCTION ( BlueprintCallable )
	void DeinitializeChunk ( const int32 RegionIndex , const int32 ChunkIndex );

	UFUNCTION ( BlueprintCallable )
	void InitializeRegion ( const int32 RegionIndex );

	UFUNCTION ( BlueprintCallable )
	void DeinitializeRegion ( const int32 RegionIndex );

public:

	// Faster version of get data ID without check
	FORCEINLINE int32 GetDataID_Checked ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

	// Get data index to data meta count
	FORCEINLINE int32 GetDataMeta_MappingNum ( const int32 RegionIndex , const int32 ChunkIndex ) const;

	// Get existing All Meta Tag in data 
	FORCEINLINE const FLFPNumMetaData* GetDataMetaList_Direct ( const int32 RegionIndex , const int32 ChunkIndex , const int32 MappingIndex ) const;

	// Set meta by data meta index from mapping
	FORCEINLINE void SetDataMeta_Direct ( const int32 RegionIndex , const int32 ChunkIndex , const int32 MappingIndex , const FGameplayTag& DataMetaTag , const FInstancedStruct& NewDataMeta );

public:

	UFUNCTION ( BlueprintCallable )
	TArray < int32 > GetDataIDList ( const int32 RegionIndex , const int32 ChunkIndex ) const;

	UFUNCTION ( BlueprintCallable )
	int32 GetDataID ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

	UFUNCTION ( BlueprintCallable )
	void SetDataID ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const int32 NewDataID );

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="DataMetaTag") )
	FInstancedStruct GetDataMeta ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FGameplayTag& DataMetaTag ) const;

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="DataMetaTag") )
	void SetDataMeta ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FGameplayTag& DataMetaTag , const FInstancedStruct& NewDataMeta );

public:

	UFUNCTION ( BlueprintCallable )
	int32 GetChunkID ( const int32 RegionIndex , const int32 ChunkIndex ) const;

	UFUNCTION ( BlueprintCallable )
	void SetChunkID ( const int32 RegionIndex , const int32 ChunkIndex , const int32 NewChunkID );

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="ChunkMetaTag") )
	FInstancedStruct GetChunkMeta ( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& ChunkMetaTag ) const;

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="ChunkMetaTag") )
	void SetChunkMeta ( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& ChunkMetaTag , const FInstancedStruct& NewChunkMeta );

public:

	UFUNCTION ( BlueprintCallable )
	int32 GetRegionID ( const int32 RegionIndex ) const;

	UFUNCTION ( BlueprintCallable )
	void SetRegionID ( const int32 RegionIndex , const int32 NewRegionID );

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="RegionMetaTag") )
	FInstancedStruct GetRegionMeta ( const int32 RegionIndex , const FGameplayTag& RegionMetaTag ) const;

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="RegionMetaTag") )
	void SetRegionMeta ( const int32 RegionIndex , const FGameplayTag& RegionMetaTag , const FInstancedStruct& NewRegionMeta );

public:

	UFUNCTION ( BlueprintCallable )
	bool IsDataIndexValid ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

	UFUNCTION ( BlueprintCallable )
	bool IsChunkIndexValid ( const int32 RegionIndex , const int32 ChunkIndex ) const;

	UFUNCTION ( BlueprintCallable )
	bool IsRegionIndexValid ( const int32 RegionIndex ) const;

public:

	UFUNCTION ( BlueprintCallable )
	bool IsChunkInitialized ( const int32 RegionIndex , const int32 ChunkIndex ) const;

	UFUNCTION ( BlueprintCallable )
	bool IsRegionInitialized ( const int32 RegionIndex ) const;

public:

	UFUNCTION ( BlueprintPure )
	int32 GetDataIndexSize ( ) const;

	UFUNCTION ( BlueprintPure )
	int32 GetChunkIndexSize ( ) const;

	UFUNCTION ( BlueprintPure )
	int32 GetRegionIndexSize ( ) const;

public:

	UPROPERTY ( BlueprintAssignable )
	FLFPChunkedNumData_TagChanged OnIDChanged;

	UPROPERTY ( BlueprintAssignable )
	FLFPChunkedNumData_MetaChanged OnMetaChanged;

private:

	UPROPERTY ( )
	TArray < FLFPNumRegionData > RegionDataList = TArray < FLFPNumRegionData > ( );

protected:

	UPROPERTY ( EditAnywhere , Category = "Setting|IndexSize" )
	int32 DataIndexSize = 1;

	UPROPERTY ( EditAnywhere , Category = "Setting|IndexSize" )
	int32 ChunkIndexSize = 1;

	UPROPERTY ( EditAnywhere , Category = "Setting|IndexSize" )
	int32 RegionIndexSize = 1;
};
