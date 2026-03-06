// Copyright (c) 2023-2025 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Library/LFPDynamicTypeLibrary.h"
#include "StructUtils/InstancedStruct.h"
#include "LFPChunkedTagDataComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN ( LogChunkedTagDataComponent , Log , All );

USTRUCT ( )
struct FLFPTaggedChunkData
{
	GENERATED_BODY ( )

	FLFPTaggedChunkData ( ) = default;

private:

	UPROPERTY ( )
	FGameplayTag ChunkTag = FGameplayTag::EmptyTag;

	UPROPERTY ( )
	FLFPInstancedStructTagArray ChunkMetaList = FLFPInstancedStructTagArray ( );

	UPROPERTY ( )
	FLFPTagTrackerStaticArray DataTagList = FLFPTagTrackerStaticArray ( );

	UPROPERTY ( )
	TArray < FLFPInstancedStructTagArray > DataMetaList = TArray < FLFPInstancedStructTagArray > ( );

public:

	FORCEINLINE void InitializeChunkData ( const int32 NewDataIndexSize , const FGameplayTag& FillTag )
	{
		DataTagList = FLFPTagTrackerStaticArray ( NewDataIndexSize );
		DataMetaList.SetNum ( NewDataIndexSize );

		if ( FillTag.IsValid ( ) )
		{
			for ( int32 Index = 0 ; Index < NewDataIndexSize ; ++Index )
			{
				SetDataTag ( Index , FillTag );
			}
		}
	}

	FORCEINLINE void DeinitializeChunkData ( )
	{
		DataTagList = FLFPTagTrackerStaticArray ( );
		DataMetaList.Empty ( );
	}

public:

	FORCEINLINE FGameplayTag GetChunkTag ( ) const
	{
		return ChunkTag;
	}

	FORCEINLINE void SetChunkTag ( const FGameplayTag& NewChunkTag )
	{
		ChunkTag = NewChunkTag;
	}

	FORCEINLINE void ResetChunkTag ( )
	{
		ChunkTag = FGameplayTag::EmptyTag;
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

	FORCEINLINE FGameplayTag GetDataTag ( const int32 DataIndex ) const
	{
		check ( DataTagList.IsValidIndex ( DataIndex ) );

		return DataTagList.GetItem ( DataIndex );
	}

	FORCEINLINE void SetDataTag ( const int32 DataIndex , const FGameplayTag& NewDataTag )
	{
		check ( DataTagList.IsValidIndex ( DataIndex ) );

		DataTagList.SetItem ( DataIndex , NewDataTag );
	}

public:

	FORCEINLINE const TArray < FGameplayTag >& GetDataTagList ( ) const
	{
		return DataTagList.GetItemList ( );
	}

	FORCEINLINE const FLFPInstancedStructTagArray* GetDataMetaList ( const int32 DataIndex ) const
	{
		return DataMetaList.IsValidIndex ( DataIndex ) ? &DataMetaList [ DataIndex ] : nullptr;
	}

	FORCEINLINE FLFPInstancedStructTagArray* GetDataMetaList ( const int32 DataIndex )
	{
		return DataMetaList.IsValidIndex ( DataIndex ) ? &DataMetaList [ DataIndex ] : nullptr;
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

		return DataMetaList [ DataIndex ].GetItemConst ( MetaTag );
	}

	FORCEINLINE FInstancedStruct& GetOrAddDataMeta ( const int32 DataIndex , const FGameplayTag& MetaTag )
	{
		checkf ( DataTagList.IsValidIndex ( DataIndex ) ,
		         TEXT(
			         "DataIndex invalid, call InitializeChunkData first. Resize Chunk data after initialized not allow."
		         ) );

		return DataMetaList [ DataIndex ].GetOrAddItem ( MetaTag );
	}

	FORCEINLINE void RemoveDataMeta ( const int32 DataIndex , const FGameplayTag& MetaTag )
	{
		checkf ( DataTagList.IsValidIndex ( DataIndex ) ,
		         TEXT(
			         "DataIndex is invalid, call InitializeChunkData first. Resize Chunk data after initialized is not allowed"
		         ) );

		DataMetaList [ DataIndex ].RemoveItem ( MetaTag );
	}

public:

	FORCEINLINE void CleanEmptyMetaData ( )
	{
		DataMetaList.RemoveAllSwap ( [] ( FLFPInstancedStructTagArray& MetaData )
		{
			MetaData.CleanEmptyItem ( );
			return MetaData.IsEmpty ( );
		} );

		ChunkMetaList.CleanEmptyItem ( );
	}
};

USTRUCT ( )
struct FLFPTaggedRegionData
{
	GENERATED_BODY ( )

private:

	UPROPERTY ( )
	FGameplayTag RegionTag = FGameplayTag::EmptyTag;

	UPROPERTY ( )
	FLFPInstancedStructTagArray RegionMetaList = FLFPInstancedStructTagArray ( );

	UPROPERTY ( )
	TArray < FLFPTaggedChunkData > ChunkList = TArray < FLFPTaggedChunkData > ( );

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

	FORCEINLINE FGameplayTag GetRegionTag ( ) const
	{
		return RegionTag;
	}

	FORCEINLINE void SetRegionTag ( const FGameplayTag& NewChunkTag )
	{
		RegionTag = NewChunkTag;
	}

	FORCEINLINE void ResetRegionTag ( )
	{
		RegionTag = FGameplayTag::EmptyTag;
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

	FORCEINLINE const FLFPTaggedChunkData& GetChunk ( const int32 ChunkIndex ) const
	{
		checkf ( ChunkList.IsValidIndex ( ChunkIndex ) ,
		         TEXT(
			         "ChunkIndex invalid, call InitializeRegionData first. Resize region data after initialized not allow."
		         ) );

		return ChunkList [ ChunkIndex ];
	}

	FORCEINLINE FLFPTaggedChunkData& GetChunk ( const int32 ChunkIndex )
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
		for ( FLFPTaggedChunkData& ChunkData : ChunkList )
		{
			ChunkData.CleanEmptyMetaData ( );
		}

		RegionMetaList.CleanEmptyItem ( );
	}
};

USTRUCT ( BlueprintType )
struct FLFPChunkedTagSerializeData
{
	GENERATED_BODY ( )

public:

	UPROPERTY ( )
	TArray < uint8 > DataList = TArray < uint8 > ( );

	UPROPERTY ( )
	FName CompressionName = NAME_Oodle;
};

USTRUCT ( BlueprintType )
struct FLFPTagChangeEvent
{
	GENERATED_BODY ( )

	FLFPTagChangeEvent ( ) = default;

	FLFPTagChangeEvent
	(
		const int32         InRegionIndex ,
		const int32         InChunkIndex ,
		const int32         InDataIndex ,
		const FGameplayTag& InOldTag
		) : RegionIndex ( InRegionIndex )
		    , ChunkIndex ( InChunkIndex )
		    , DataIndex ( InDataIndex )
		    , OldTag ( InOldTag )
	{
	}

public:

	UPROPERTY ( VisibleAnywhere , BlueprintReadOnly , Category=Default )
	int32 RegionIndex = INDEX_NONE;

	UPROPERTY ( VisibleAnywhere , BlueprintReadOnly , Category=Default )
	int32 ChunkIndex = INDEX_NONE;

	UPROPERTY ( VisibleAnywhere , BlueprintReadOnly , Category=Default )
	int32 DataIndex = INDEX_NONE;

	UPROPERTY ( VisibleAnywhere , BlueprintReadOnly , Category=Default )
	FGameplayTag OldTag = FGameplayTag::EmptyTag;
};

USTRUCT ( BlueprintType )
struct FLFPMetaChangeEvent
{
	GENERATED_BODY ( )

	FLFPMetaChangeEvent ( ) = default;

	FLFPMetaChangeEvent
	(
		const int32             InRegionIndex ,
		const int32             InChunkIndex ,
		const int32             InDataIndex ,
		const FGameplayTag&     InMetaTag ,
		const FInstancedStruct& InOldMetaData
		) : RegionIndex ( InRegionIndex )
		    , ChunkIndex ( InChunkIndex )
		    , DataIndex ( InDataIndex )
		    , MetaTag ( InMetaTag )
		    , OldMetaData ( InOldMetaData )
	{
	}

public:

	UPROPERTY ( VisibleAnywhere , BlueprintReadOnly , Category=Default )
	int32 RegionIndex = INDEX_NONE;

	UPROPERTY ( VisibleAnywhere , BlueprintReadOnly , Category=Default )
	int32 ChunkIndex = INDEX_NONE;

	UPROPERTY ( VisibleAnywhere , BlueprintReadOnly , Category=Default )
	int32 DataIndex = INDEX_NONE;

	UPROPERTY ( VisibleAnywhere , BlueprintReadOnly , Category=Default )
	FGameplayTag MetaTag = FGameplayTag::EmptyTag;

	UPROPERTY ( VisibleAnywhere , BlueprintReadOnly , Category=Default , Transient )
	FInstancedStruct OldMetaData = FInstancedStruct ( );
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam ( FLFPChunkedTagData_TagChanged , const TArray<FLFPTagChangeEvent>& , ChangeList );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam ( FLFPChunkedTagData_MetaChanged , const TArray<FLFPMetaChangeEvent>& , ChangeList );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams ( FLFPChunkedTagData_Initialization , const int32 , RegionIndex , const int32 , ChunkIndex );

UCLASS ( ClassGroup=(Custom) , meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPChunkedTagDataComponent : public UActorComponent
{
	GENERATED_BODY ( )

public:

	// Sets default values for this component's properties
	ULFPChunkedTagDataComponent ( );

protected:

	// Called when the game starts
	virtual void BeginPlay ( ) override;

public:

	// Called every frame
	virtual void TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;

public:

	UFUNCTION ( BlueprintCallable )
	void SetSize ( const FIntVector& NewSize );

public:

	UFUNCTION ( BlueprintCallable )
	void LoadRegion ( const int32 RegionIndex , const FLFPChunkedTagSerializeData& LoadData );

	UFUNCTION ( BlueprintCallable )
	void SaveRegion ( const int32 RegionIndex , FLFPChunkedTagSerializeData& SaveData );

public:

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="FillTag") )
	void InitializeChunk ( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& FillTag );

	UFUNCTION ( BlueprintCallable )
	void DeinitializeChunk ( const int32 RegionIndex , const int32 ChunkIndex );

	UFUNCTION ( BlueprintCallable )
	void InitializeRegion ( const int32 RegionIndex );

	UFUNCTION ( BlueprintCallable )
	void DeinitializeRegion ( const int32 RegionIndex );

public:

	// Faster version of get data tag without check
	FORCEINLINE FGameplayTag GetDataTag_Checked ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

	// Get data index to data meta count
	FORCEINLINE int32 GetDataMeta_MappingNum ( const int32 RegionIndex , const int32 ChunkIndex ) const;

	// Get existing All Meta Tag in data 
	FORCEINLINE const FLFPInstancedStructTagArray* GetDataMetaList_Direct ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

public:

	UFUNCTION ( BlueprintCallable )
	TArray < FGameplayTag > GetDataTagList ( const int32 RegionIndex , const int32 ChunkIndex ) const;

	UFUNCTION ( BlueprintCallable )
	FGameplayTag GetDataTag ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="NewDataTag") )
	void SetDataTag ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FGameplayTag& NewDataTag , const bool bSendEvent = true );

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="DataMetaTag") )
	const FInstancedStruct& GetDataMeta ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FGameplayTag& DataMetaTag ) const;

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="DataMetaTag") )
	void SetDataMeta ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FGameplayTag& DataMetaTag , const FInstancedStruct& NewDataMeta , const bool bSendEvent = true );
	void SetDataMeta ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FGameplayTag& DataMetaTag , const FConstStructView NewDataMeta , const bool bSendEvent = true );

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="DataMetaTag") )
	void RemoveDataMeta ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FGameplayTag& DataMetaTag );

public:

	UFUNCTION ( BlueprintCallable )
	FGameplayTag GetChunkTag ( const int32 RegionIndex , const int32 ChunkIndex ) const;

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="NewChunkTag") )
	void SetChunkTag ( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& NewChunkTag , const bool bSendEvent = true );

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="ChunkMetaTag") )
	const FInstancedStruct& GetChunkMeta ( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& ChunkMetaTag ) const;

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="ChunkMetaTag") )
	void SetChunkMeta ( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& ChunkMetaTag , const FInstancedStruct& NewChunkMeta , const bool bSendEvent = true );

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="ChunkMetaTag") )
	void RemoveChunkMeta ( const int32 RegionIndex , const int32 ChunkIndex , const FGameplayTag& ChunkMetaTag );

public:

	UFUNCTION ( BlueprintCallable )
	FGameplayTag GetRegionTag ( const int32 RegionIndex ) const;

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="NewRegionTag") )
	void SetRegionTag ( const int32 RegionIndex , const FGameplayTag& NewRegionTag , const bool bSendEvent = true );

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="RegionMetaTag") )
	const FInstancedStruct& GetRegionMeta ( const int32 RegionIndex , const FGameplayTag& RegionMetaTag ) const;

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="RegionMetaTag") )
	void SetRegionMeta ( const int32 RegionIndex , const FGameplayTag& RegionMetaTag , const FInstancedStruct& NewRegionMeta , const bool bSendEvent = true );

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="RegionMetaTag") )
	void RemoveRegionMeta ( const int32 RegionIndex , const FGameplayTag& RegionMetaTag );

public:

	UFUNCTION ( BlueprintPure )
	bool IsDataIndexValid ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

	UFUNCTION ( BlueprintPure )
	bool IsChunkIndexValid ( const int32 RegionIndex , const int32 ChunkIndex ) const;

	UFUNCTION ( BlueprintPure )
	bool IsRegionIndexValid ( const int32 RegionIndex ) const;

public:

	UFUNCTION ( BlueprintPure )
	bool IsChunkInitialized ( const int32 RegionIndex , const int32 ChunkIndex ) const;

	UFUNCTION ( BlueprintPure )
	bool IsRegionInitialized ( const int32 RegionIndex ) const;

public:

	UFUNCTION ( BlueprintPure )
	int32 GetDataIndexSize ( ) const;

	UFUNCTION ( BlueprintPure )
	int32 GetChunkIndexSize ( ) const;

	UFUNCTION ( BlueprintPure )
	int32 GetRegionIndexSize ( ) const;

private:

	UFUNCTION ( )
	void AddTagChangeEvent ( const FLFPTagChangeEvent& NewEvent );

	UFUNCTION ( )
	void AddMetaChangeEvent ( const FLFPMetaChangeEvent& NewEvent );

	UFUNCTION ( )
	void BroadcastTagChangeEvent ( );

	UFUNCTION ( )
	void BroadcastMetaChangeEvent ( );

private:

	UPROPERTY ( Transient )
	TArray < FLFPTagChangeEvent > TagChangeEventList;

	UPROPERTY ( Transient )
	TArray < FLFPMetaChangeEvent > MetaChangeEventList;

	UPROPERTY ( Transient )
	FTimerHandle TagChangeEventHandle;

	UPROPERTY ( Transient )
	FTimerHandle MetaChangeEventHandle;

public:

	UPROPERTY ( BlueprintAssignable )
	FLFPChunkedTagData_TagChanged OnTagChanged;

	UPROPERTY ( BlueprintAssignable )
	FLFPChunkedTagData_MetaChanged OnMetaChanged;

	UPROPERTY ( BlueprintAssignable )
	FLFPChunkedTagData_Initialization OnInitialized;

	UPROPERTY ( BlueprintAssignable )
	FLFPChunkedTagData_Initialization OnUninitialized;

private:

	UPROPERTY ( Transient )
	TArray < FLFPTaggedRegionData > RegionDataList = TArray < FLFPTaggedRegionData > ( );

protected:

	UPROPERTY ( EditAnywhere , Category = "Setting|IndexSize" )
	int32 DataIndexSize = 1;

	UPROPERTY ( EditAnywhere , Category = "Setting|IndexSize" )
	int32 ChunkIndexSize = 1;

	UPROPERTY ( EditAnywhere , Category = "Setting|IndexSize" )
	int32 RegionIndexSize = 1;

private:

	static const FInstancedStruct EmptyStruct;
};
