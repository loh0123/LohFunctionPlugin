// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Library/LFPDynamicTypeLibrary.h"
#include "LFPChunkedPrimitiveDataComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN ( LogChunkedByteListDataComponent , Log , All );

USTRUCT ( )
struct FLFPPrimitiveChunkData
{
	GENERATED_BODY ( )

	FLFPPrimitiveChunkData ( ) = default;

private:

	UPROPERTY ( )
	TArray < FLFPPrimitiveData > PrimitiveList = TArray < FLFPPrimitiveData > ( );

	UPROPERTY ( )
	FLFPPrimitiveData ChunkPrimitiveData = FLFPPrimitiveData ( );

public:

	FORCEINLINE void InitializeChunkData ( const int32 NewDataIndexSize )
	{
		PrimitiveList.SetNumZeroed ( NewDataIndexSize );
	}

	FORCEINLINE void DeinitializeChunkData ( )
	{
		PrimitiveList.Empty ( );
	}

public:

	FORCEINLINE bool IsInitialized ( ) const
	{
		return PrimitiveList.IsEmpty ( ) == false;
	}

	FORCEINLINE bool IsDataIndexValid ( const int32 DataIndex ) const
	{
		return PrimitiveList.IsValidIndex ( DataIndex );
	}

public:

	FORCEINLINE const FLFPPrimitiveData& GetData ( const int32 DataIndex ) const
	{
		check ( IsDataIndexValid ( DataIndex ) );

		return PrimitiveList [ DataIndex ];
	}

	FORCEINLINE void SetData ( const int32 DataIndex , const FLFPPrimitiveData& NewData )
	{
		check ( IsDataIndexValid ( DataIndex ) );

		PrimitiveList [ DataIndex ] = NewData;
	}

public:

	FORCEINLINE const FLFPPrimitiveData& GetChunkData ( ) const
	{
		return ChunkPrimitiveData;
	}

	FORCEINLINE void SetChunkData ( const FLFPPrimitiveData& NewData )
	{
		ChunkPrimitiveData = NewData;
	}

public:

	FORCEINLINE const TArray < FLFPPrimitiveData >& GetDataList ( ) const
	{
		return PrimitiveList;
	}
};

USTRUCT ( )
struct FLFPPrimitiveRegionData
{
	GENERATED_BODY ( )

private:

	UPROPERTY ( )
	TArray < FLFPPrimitiveChunkData > ChunkList = TArray < FLFPPrimitiveChunkData > ( );

	UPROPERTY ( )
	FLFPPrimitiveData RegionPrimitiveData = FLFPPrimitiveData ( );

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

	FORCEINLINE const FLFPPrimitiveChunkData& GetChunk ( const int32 ChunkIndex ) const
	{
		checkf ( ChunkList.IsValidIndex ( ChunkIndex ) ,
		         TEXT(
			         "ChunkIndex invalid, call InitializeRegionData first. Resize region data after initialized not allow."
		         ) );

		return ChunkList [ ChunkIndex ];
	}

	FORCEINLINE FLFPPrimitiveChunkData& GetChunk ( const int32 ChunkIndex )
	{
		checkf ( ChunkList.IsValidIndex ( ChunkIndex ) ,
		         TEXT(
			         "ChunkIndex invalid, call InitializeRegionData first. Resize region data after initialized not allow."
		         ) );

		return ChunkList [ ChunkIndex ];
	}

public:

	FORCEINLINE const FLFPPrimitiveData& GetRegionData ( ) const
	{
		return RegionPrimitiveData;
	}

	FORCEINLINE void SetRegionData ( const FLFPPrimitiveData& NewData )
	{
		RegionPrimitiveData = NewData;
	}
};

USTRUCT ( BlueprintType )
struct FLFPChunkedPrimitiveSerializeData
{
	GENERATED_BODY ( )

public:

	UPROPERTY ( )
	TArray < uint8 > DataList = TArray < uint8 > ( );

	UPROPERTY ( )
	FName CompressionName = NAME_Oodle;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams ( FLFPChunkedPrimitiveData_DataChanged , const int32 , RegionIndex , const int32 , ChunkIndex , const int32 , DataIndex , const FLFPPrimitiveData& , OldData , const FLFPPrimitiveData& , NewData );

UCLASS ( ClassGroup=(Custom) , meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPChunkedPrimitiveDataComponent : public UActorComponent
{
	GENERATED_BODY ( )

public:

	// Sets default values for this component's properties
	ULFPChunkedPrimitiveDataComponent ( );

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
	void LoadRegion ( const int32 RegionIndex , const FLFPChunkedPrimitiveSerializeData& LoadData );

	UFUNCTION ( BlueprintCallable )
	void SaveRegion ( const int32 RegionIndex , FLFPChunkedPrimitiveSerializeData& SaveData );

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
	FORCEINLINE const FLFPPrimitiveData& GetData_Checked ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

public:

	UFUNCTION ( BlueprintCallable )
	TArray < FLFPPrimitiveData > GetDataList ( const int32 RegionIndex , const int32 ChunkIndex ) const;

	UFUNCTION ( BlueprintCallable )
	FLFPPrimitiveData GetData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

	UFUNCTION ( BlueprintCallable )
	void SetData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FLFPPrimitiveData& NewData );

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
	FLFPChunkedPrimitiveData_DataChanged OnDataChanged;

private:

	UPROPERTY ( )
	TArray < FLFPPrimitiveRegionData > RegionDataList = TArray < FLFPPrimitiveRegionData > ( );

protected:

	UPROPERTY ( EditAnywhere , Category = "Setting|IndexSize" )
	int32 DataIndexSize = 1;

	UPROPERTY ( EditAnywhere , Category = "Setting|IndexSize" )
	int32 ChunkIndexSize = 1;

	UPROPERTY ( EditAnywhere , Category = "Setting|IndexSize" )
	int32 RegionIndexSize = 1;
};
