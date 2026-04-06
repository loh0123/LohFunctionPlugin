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
	FLFPTagTrackerStaticArray CellTagList = FLFPTagTrackerStaticArray ( );

	UPROPERTY ( )
	TArray < FLFPInstancedStructTagArray > CellMetaList = TArray < FLFPInstancedStructTagArray > ( );

public:

	FORCEINLINE void InitializeChunkData ( const int32 NewCellIndexSize , const FGameplayTag& FillTag )
	{
		CellTagList = FLFPTagTrackerStaticArray ( NewCellIndexSize );
		CellMetaList.SetNum ( NewCellIndexSize );

		if ( FillTag.IsValid ( ) )
		{
			for ( int32 Index = 0 ; Index < NewCellIndexSize ; ++Index )
			{
				SetCellTag ( Index , FillTag );
			}
		}
	}

	FORCEINLINE void DeinitializeChunkData ( )
	{
		CellTagList = FLFPTagTrackerStaticArray ( );
		CellMetaList.Empty ( );
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
		return CellTagList.IsInitialized ( );
	}

	FORCEINLINE bool IsCellIndexValid ( const int32 CellIndex ) const
	{
		return CellTagList.IsValidIndex ( CellIndex );
	}

public:

	FORCEINLINE FGameplayTag GetCellTag ( const int32 CellIndex ) const
	{
		check ( CellTagList.IsValidIndex ( CellIndex ) );

		return CellTagList.GetItem ( CellIndex );
	}

	FORCEINLINE void SetCellTag ( const int32 CellIndex , const FGameplayTag& NewCellTag )
	{
		check ( CellTagList.IsValidIndex ( CellIndex ) );

		CellTagList.SetItem ( CellIndex , NewCellTag );
	}

public:

	FORCEINLINE const TArray < FGameplayTag >& GetCellTagList ( ) const
	{
		return CellTagList.GetItemList ( );
	}

	FORCEINLINE const FLFPInstancedStructTagArray* GetCellMetaList ( const int32 CellIndex ) const
	{
		return CellMetaList.IsValidIndex ( CellIndex ) ? &CellMetaList [ CellIndex ] : nullptr;
	}

	FORCEINLINE FLFPInstancedStructTagArray* GetCellMetaList ( const int32 CellIndex )
	{
		return CellMetaList.IsValidIndex ( CellIndex ) ? &CellMetaList [ CellIndex ] : nullptr;
	}

public:

	FORCEINLINE int32 GetCellMetaNum ( ) const
	{
		return CellMetaList.Num ( );
	}

public:

	FORCEINLINE const FInstancedStruct* GetCellMeta ( const int32 CellIndex , const FGameplayTag& MetaTag ) const
	{
		checkf ( CellTagList.IsValidIndex ( CellIndex ) ,
		         TEXT(
			         "CellIndex invalid, call InitializeChunkData first. Resize Chunk data after initialized not allow."
		         ) );

		return CellMetaList [ CellIndex ].GetItemConst ( MetaTag );
	}

	FORCEINLINE FInstancedStruct& GetOrAddCellMeta ( const int32 CellIndex , const FGameplayTag& MetaTag )
	{
		checkf ( CellTagList.IsValidIndex ( CellIndex ) ,
		         TEXT(
			         "CellIndex invalid, call InitializeChunkData first. Resize Chunk data after initialized not allow."
		         ) );

		return CellMetaList [ CellIndex ].GetOrAddItem ( MetaTag );
	}

	FORCEINLINE void RemoveCellMeta ( const int32 CellIndex , const FGameplayTag& MetaTag )
	{
		checkf ( CellTagList.IsValidIndex ( CellIndex ) ,
		         TEXT(
			         "CellIndex is invalid, call InitializeChunkData first. Resize Chunk data after initialized is not allowed"
		         ) );

		CellMetaList [ CellIndex ].RemoveItem ( MetaTag );
	}

public:

	FORCEINLINE void CleanEmptyMetaData ( )
	{
		for ( FLFPInstancedStructTagArray& CellMeta : CellMetaList )
		{
			CellMeta.CleanEmptyItem ( );
		}

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

	UPROPERTY ( BlueprintReadWrite , Category=Default )
	TArray < uint8 > DataList = TArray < uint8 > ( );

	UPROPERTY ( BlueprintReadWrite , Category=Default )
	int32 UncompressionSize = INDEX_NONE;
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
		const int32         InCellIndex ,
		const FGameplayTag& InOldTag
		) : RegionIndex ( InRegionIndex )
		    , ChunkIndex ( InChunkIndex )
		    , CellIndex ( InCellIndex )
		    , OldTag ( InOldTag )
	{
	}

public:

	UPROPERTY ( BlueprintReadWrite , Category=Default )
	int32 RegionIndex = INDEX_NONE;

	UPROPERTY ( BlueprintReadWrite , Category=Default )
	int32 ChunkIndex = INDEX_NONE;

	UPROPERTY ( BlueprintReadWrite , Category=Default )
	int32 CellIndex = INDEX_NONE;

	UPROPERTY ( BlueprintReadWrite , Category=Default )
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
		const int32             InCellIndex ,
		const FGameplayTag&     InMetaTag ,
		const FInstancedStruct& InOldMetaData
		) : RegionIndex ( InRegionIndex )
		    , ChunkIndex ( InChunkIndex )
		    , CellIndex ( InCellIndex )
		    , MetaTag ( InMetaTag )
		    , OldMetaData ( InOldMetaData )
	{
	}

public:

	UPROPERTY ( BlueprintReadWrite , Category=Default )
	int32 RegionIndex = INDEX_NONE;

	UPROPERTY ( BlueprintReadWrite , Category=Default )
	int32 ChunkIndex = INDEX_NONE;

	UPROPERTY ( BlueprintReadWrite , Category=Default )
	int32 CellIndex = INDEX_NONE;

	UPROPERTY ( BlueprintReadWrite , Category=Default )
	FGameplayTag MetaTag = FGameplayTag::EmptyTag;

	UPROPERTY ( BlueprintReadWrite , Category=Default )
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
	void LoadRegion ( const int32 RegionIndex , const FLFPChunkedTagSerializeData& LoadData , const APlayerController* PlayerController , const bool bIsNetData );

	UFUNCTION ( BlueprintCallable )
	void SaveRegion ( const int32 RegionIndex , UPARAM ( ref ) FLFPChunkedTagSerializeData& SaveData , const APlayerController* PlayerController , const bool bIsNetData );

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
	FORCEINLINE FGameplayTag GetCellTag_Checked ( const int32 RegionIndex , const int32 ChunkIndex , const int32 CellIndex ) const
	{
		return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetCellTag ( CellIndex );
	}

	// Get data index to data meta count
	FORCEINLINE int32 GetCellMeta_MappingNum ( const int32 RegionIndex , const int32 ChunkIndex ) const
	{
		return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetCellMetaNum ( );
	}

	// Get existing All Meta Tag in data 
	FORCEINLINE const FLFPInstancedStructTagArray* GetCellMetaList_Direct ( const int32 RegionIndex , const int32 ChunkIndex , const int32 CellIndex ) const
	{
		check ( IsChunkIndexValid(RegionIndex, ChunkIndex) );

		return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetCellMetaList ( CellIndex );
	}

public:

	UFUNCTION ( BlueprintCallable )
	TArray < FGameplayTag > GetCellTagList ( const int32 RegionIndex , const int32 ChunkIndex ) const;

	UFUNCTION ( BlueprintCallable )
	FGameplayTag GetCellTag ( const int32 RegionIndex , const int32 ChunkIndex , const int32 CellIndex ) const;

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="NewCellTag") )
	void SetCellTag ( const int32 RegionIndex , const int32 ChunkIndex , const int32 CellIndex , const FGameplayTag& NewCellTag , const bool bSendEvent = true );

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="CellMetaTag") )
	const FInstancedStruct& GetCellMeta ( const int32 RegionIndex , const int32 ChunkIndex , const int32 CellIndex , const FGameplayTag& CellMetaTag ) const;

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="CellMetaTag") )
	void SetCellMeta ( const int32 RegionIndex , const int32 ChunkIndex , const int32 CellIndex , const FGameplayTag& CellMetaTag , const FInstancedStruct& NewCellMeta , const bool bSendEvent = true );
	void SetCellMeta ( const int32 RegionIndex , const int32 ChunkIndex , const int32 CellIndex , const FGameplayTag& CellMetaTag , const FConstStructView NewCellMeta , const bool bSendEvent = true );
	void SetCellMeta_Move ( const int32 RegionIndex , const int32 ChunkIndex , const int32 CellIndex , const FGameplayTag& CellMetaTag , FInstancedStruct&& NewCellMeta , const bool bSendEvent = true );

	UFUNCTION ( BlueprintCallable , meta=(AutoCreateRefTerm="CellMetaTag") )
	void RemoveCellMeta ( const int32 RegionIndex , const int32 ChunkIndex , const int32 CellIndex , const FGameplayTag& CellMetaTag );

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
	bool IsCellIndexValid ( const int32 RegionIndex , const int32 ChunkIndex , const int32 CellIndex ) const;

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
	int32 GetCellIndexSize ( ) const;

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

	//UPROPERTY ( Transient )
	TArray < FLFPTagChangeEvent > TagChangeEventList;

	//UPROPERTY ( Transient )
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
	int32 CellIndexSize = 1;

	UPROPERTY ( EditAnywhere , Category = "Setting|IndexSize" )
	int32 ChunkIndexSize = 1;

	UPROPERTY ( EditAnywhere , Category = "Setting|IndexSize" )
	int32 RegionIndexSize = 1;

private:

	static const FInstancedStruct EmptyStruct;
};
