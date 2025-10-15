// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LFPChunkedByteListDataComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN ( LogChunkedByteListDataComponent , Log , All );

USTRUCT ( )
struct FLFPByteListChunkData
{
	GENERATED_BODY ( )

	FLFPByteListChunkData ( ) = default;

private:

	UPROPERTY ( )
	TArray < uint8 > DataByteList = TArray < uint8 > ( );

public:

	FORCEINLINE void InitializeChunkData ( const int32 NewDataIndexSize , const int32 ByteSize )
	{
		DataByteList.SetNumZeroed ( NewDataIndexSize * ByteSize );
	}

	FORCEINLINE void DeinitializeChunkData ( )
	{
		DataByteList.Empty ( );
	}

public:

	FORCEINLINE bool IsInitialized ( ) const
	{
		return DataByteList.IsEmpty ( ) == false;
	}

	FORCEINLINE bool IsDataIndexValid ( const int32 DataIndex , const int32 ByteSize ) const
	{
		return DataByteList.IsValidIndex ( ( DataIndex * ByteSize ) + ( ByteSize - 1 ) );
	}

public:

	FORCEINLINE TArray < uint8 > GetData ( const int32 DataIndex , const int32 ByteSize ) const
	{
		check ( IsDataIndexValid ( DataIndex,ByteSize ) );

		TArray < uint8 > ResultList = TArray < uint8 > ( );

		ResultList.SetNumUninitialized ( ByteSize );

		for ( int32 ByteIndex = 0 ; ByteIndex < ByteSize ; ByteIndex++ )
		{
			ResultList [ ByteIndex ] = DataByteList [ DataIndex + ByteIndex ];
		}

		return ResultList;
	}

	FORCEINLINE void SetData ( const int32 DataIndex , const int32 ByteSize , const TArray < uint8 >& NewData )
	{
		check ( IsDataIndexValid ( DataIndex,ByteSize ) );
		check ( NewData.Num ( ) == ByteSize );

		for ( int32 ByteIndex = 0 ; ByteIndex < ByteSize ; ByteIndex++ )
		{
			DataByteList [ DataIndex + ByteIndex ] = NewData [ ByteIndex ];
		}
	}

public:

	FORCEINLINE const TArray < uint8 >& GetDataList ( ) const
	{
		return DataByteList;
	}
};

USTRUCT ( )
struct FLFPByteListRegionData
{
	GENERATED_BODY ( )

private:

	UPROPERTY ( )
	TArray < FLFPByteListChunkData > ChunkList = TArray < FLFPByteListChunkData > ( );

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

	FORCEINLINE bool IsInitialized ( ) const
	{
		return ChunkList.IsEmpty ( ) == false;
	}

	FORCEINLINE bool IsChunkIndexValid ( const int32 ChunkIndex ) const
	{
		return ChunkList.IsValidIndex ( ChunkIndex );
	}

public:

	FORCEINLINE const FLFPByteListChunkData& GetChunk ( const int32 ChunkIndex ) const
	{
		checkf ( ChunkList.IsValidIndex ( ChunkIndex ) ,
		         TEXT(
			         "ChunkIndex invalid, call InitializeRegionData first. Resize region data after initialized not allow."
		         ) );

		return ChunkList [ ChunkIndex ];
	}

	FORCEINLINE FLFPByteListChunkData& GetChunk ( const int32 ChunkIndex )
	{
		checkf ( ChunkList.IsValidIndex ( ChunkIndex ) ,
		         TEXT(
			         "ChunkIndex invalid, call InitializeRegionData first. Resize region data after initialized not allow."
		         ) );

		return ChunkList [ ChunkIndex ];
	}
};

USTRUCT ( BlueprintType )
struct FLFPChunkedByteListSerializeData
{
	GENERATED_BODY ( )

public:

	UPROPERTY ( )
	TArray < uint8 > DataList = TArray < uint8 > ( );

	UPROPERTY ( )
	FName CompressionName = NAME_Oodle;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams ( FLFPChunkedByteListData_DataChanged , const int32 , RegionIndex , const int32 , ChunkIndex , const int32 , DataIndex , const TArray<uint8>& , OldData , const TArray<uint8>& , NewData );

UCLASS ( ClassGroup=(Custom) , meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPChunkedByteListDataComponent : public UActorComponent
{
	GENERATED_BODY ( )

public:

	// Sets default values for this component's properties
	ULFPChunkedByteListDataComponent ( );

protected:

	// Called when the game starts
	virtual void BeginPlay ( ) override;

public:

	// Called every frame
	virtual void TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;

public:

	UFUNCTION ( BlueprintCallable )
	void SetSize ( const FIntVector& NewSize , const int32 NewByteSize );

public:

	UFUNCTION ( BlueprintCallable )
	void LoadRegion ( const int32 RegionIndex , const FLFPChunkedByteListSerializeData& LoadData );

	UFUNCTION ( BlueprintCallable )
	void SaveRegion ( const int32 RegionIndex , FLFPChunkedByteListSerializeData& SaveData );

public:

	UFUNCTION ( BlueprintCallable )
	void InitializeChunk ( const int32 RegionIndex , const int32 ChunkIndex );

	UFUNCTION ( BlueprintCallable )
	void DeinitializeChunk ( const int32 RegionIndex , const int32 ChunkIndex );

	UFUNCTION ( BlueprintCallable )
	void InitializeRegion ( const int32 RegionIndex );

	UFUNCTION ( BlueprintCallable )
	void DeinitializeRegion ( const int32 RegionIndex );

public:

	// Faster version of get data ID without check
	FORCEINLINE TArray < uint8 > GetData_Checked ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

public:

	UFUNCTION ( BlueprintCallable )
	TArray < uint8 > GetDataList ( const int32 RegionIndex , const int32 ChunkIndex ) const;

	UFUNCTION ( BlueprintCallable )
	TArray < uint8 > GetData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

	UFUNCTION ( BlueprintCallable )
	void SetData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const TArray < uint8 >& NewData );

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
	FLFPChunkedByteListData_DataChanged OnDataChanged;

private:

	UPROPERTY ( )
	TArray < FLFPByteListRegionData > RegionDataList = TArray < FLFPByteListRegionData > ( );

protected:

	UPROPERTY ( EditAnywhere , Category = "Setting" )
	int32 DataByteSize = 1;

protected:

	UPROPERTY ( EditAnywhere , Category = "Setting|IndexSize" )
	int32 DataIndexSize = 1;

	UPROPERTY ( EditAnywhere , Category = "Setting|IndexSize" )
	int32 ChunkIndexSize = 1;

	UPROPERTY ( EditAnywhere , Category = "Setting|IndexSize" )
	int32 RegionIndexSize = 1;
};
