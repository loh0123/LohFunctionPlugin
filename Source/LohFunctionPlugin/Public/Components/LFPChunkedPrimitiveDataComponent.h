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
	TArray < FInstancedStruct > PrimitiveList = TArray < FInstancedStruct > ( );

	UPROPERTY ( )
	FInstancedStruct ChunkPrimitiveData = FInstancedStruct ( );

public:

	FORCEINLINE void InitializeChunkData ( const int32 NewDataIndexSize )
	{
		PrimitiveList.SetNum ( NewDataIndexSize );
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

	FORCEINLINE FInstancedStruct& GetData_Ref ( const int32 DataIndex )
	{
		check ( IsDataIndexValid ( DataIndex ) );

		return PrimitiveList [ DataIndex ];
	}

	FORCEINLINE const FInstancedStruct& GetData ( const int32 DataIndex ) const
	{
		check ( IsDataIndexValid ( DataIndex ) );

		return PrimitiveList [ DataIndex ];
	}

	FORCEINLINE void SetData ( const int32 DataIndex , const FInstancedStruct& NewData )
	{
		check ( IsDataIndexValid ( DataIndex ) );

		PrimitiveList [ DataIndex ] = NewData;
	}

public:

	FORCEINLINE const FInstancedStruct& GetChunkData ( ) const
	{
		return ChunkPrimitiveData;
	}

	FORCEINLINE void SetChunkData ( const FInstancedStruct& NewData )
	{
		ChunkPrimitiveData = NewData;
	}

public:

	FORCEINLINE const TArray < FInstancedStruct >& GetDataList ( ) const
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
	FInstancedStruct RegionPrimitiveData = FInstancedStruct ( );

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

	FORCEINLINE const FInstancedStruct& GetRegionData ( ) const
	{
		return RegionPrimitiveData;
	}

	FORCEINLINE void SetRegionData ( const FInstancedStruct& NewData )
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

USTRUCT ( BlueprintType )
struct FLFPChunkedPrimitiveChangeEvent
{
	GENERATED_BODY ( )

	FLFPChunkedPrimitiveChangeEvent ( ) = default;

	FLFPChunkedPrimitiveChangeEvent
	(
		const int32             InRegionIndex ,
		const int32             InChunkIndex ,
		const int32             InDataIndex ,
		const FInstancedStruct& InOldData ,
		const FInstancedStruct& InNewData
		) : RegionIndex ( InRegionIndex )
		    , ChunkIndex ( InChunkIndex )
		    , DataIndex ( InDataIndex )
		    , OldData ( InOldData )
		    , NewData ( InNewData )
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
	FInstancedStruct OldData = FInstancedStruct ( );

	UPROPERTY ( VisibleAnywhere , BlueprintReadOnly , Category=Default )
	FInstancedStruct NewData = FInstancedStruct ( );
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam ( FLFPChunkedPrimitiveData_DataChanged , const TArray<FLFPChunkedPrimitiveChangeEvent>& , ChangeList );

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
	FORCEINLINE const FInstancedStruct& GetData_Checked ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
	{
		return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetData ( DataIndex );
	}

	template < typename FuncBody >
	FORCEINLINE void SetData_Template ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FuncBody& Body , const bool bSendEvent = true );

public:

	UFUNCTION ( BlueprintCallable )
	FORCEINLINE TArray < FInstancedStruct > GetDataList ( const int32 RegionIndex , const int32 ChunkIndex ) const
	{
		return RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetDataList ( );
	}

	UFUNCTION ( BlueprintCallable )
	const FInstancedStruct& GetData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

	UFUNCTION ( BlueprintCallable )
	void SetData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FInstancedStruct& NewData , const bool bSendEvent = true );

	UFUNCTION ( BlueprintCallable )
	const FInstancedStruct& GetChunkData ( const int32 RegionIndex , const int32 ChunkIndex ) const;

	UFUNCTION ( BlueprintCallable )
	void SetChunkData ( const int32 RegionIndex , const int32 ChunkIndex , const FInstancedStruct& NewData , const bool bSendEvent = true );

	UFUNCTION ( BlueprintCallable )
	const FInstancedStruct& GetRegionData ( const int32 RegionIndex ) const;

	UFUNCTION ( BlueprintCallable )
	void SetRegionData ( const int32 RegionIndex , const FInstancedStruct& NewData , const bool bSendEvent = true );

public:

	UFUNCTION ( BlueprintCallable )
	FORCEINLINE bool IsDataIndexValid ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
	{
		return RegionDataList.IsValidIndex ( RegionIndex ) && RegionDataList [ RegionIndex ].IsChunkIndexValid ( ChunkIndex ) && RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).IsDataIndexValid ( DataIndex );
	}

	UFUNCTION ( BlueprintCallable )
	FORCEINLINE bool IsChunkIndexValid ( const int32 RegionIndex , const int32 ChunkIndex ) const
	{
		return RegionDataList.IsValidIndex ( RegionIndex ) && RegionDataList [ RegionIndex ].IsChunkIndexValid ( ChunkIndex );
	}

	UFUNCTION ( BlueprintCallable )
	FORCEINLINE bool IsRegionIndexValid ( const int32 RegionIndex ) const
	{
		return RegionDataList.IsValidIndex ( RegionIndex );
	}

public:

	UFUNCTION ( BlueprintCallable )
	FORCEINLINE bool IsChunkInitialized ( const int32 RegionIndex , const int32 ChunkIndex ) const
	{
		return IsChunkIndexValid ( RegionIndex , ChunkIndex ) && RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).IsInitialized ( );
	}

	UFUNCTION ( BlueprintCallable )
	FORCEINLINE bool IsRegionInitialized ( const int32 RegionIndex ) const
	{
		return IsRegionIndexValid ( RegionIndex ) && RegionDataList [ RegionIndex ].IsInitialized ( );
	}

public:

	UFUNCTION ( BlueprintPure )
	FORCEINLINE int32 GetDataIndexSize ( ) const
	{
		return DataIndexSize;
	}

	UFUNCTION ( BlueprintPure )
	FORCEINLINE int32 GetChunkIndexSize ( ) const
	{
		return ChunkIndexSize;
	}

	UFUNCTION ( BlueprintPure )
	FORCEINLINE int32 GetRegionIndexSize ( ) const
	{
		return RegionIndexSize;
	}

private:

	UFUNCTION ( )
	void AddDataChangeEvent ( const FLFPChunkedPrimitiveChangeEvent& NewEvent );

	UFUNCTION ( )
	void BroadcastDataChangeEvent ( );

private:

	UPROPERTY ( Transient )
	TArray < FLFPChunkedPrimitiveChangeEvent > DataChangeEventList;

	UPROPERTY ( Transient )
	FTimerHandle DataChangeEventHandle;

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

private:

	static const FInstancedStruct EmptyStruct;
};

template < typename FuncBody >
void ULFPChunkedPrimitiveDataComponent::SetData_Template ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FuncBody& Body , const bool bSendEvent )
{
	check ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) )

	const FInstancedStruct OldData = RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetData ( DataIndex );

	FLFPChunkedPrimitiveChangeEvent BroadcastData = FLFPChunkedPrimitiveChangeEvent ( RegionIndex , ChunkIndex , DataIndex , FInstancedStruct ( ) , FInstancedStruct ( ) );

	FInstancedStruct& DataRef = RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetData_Ref ( DataIndex );

	if ( bSendEvent )
	{
		BroadcastData.OldData = RegionDataList [ RegionIndex ].GetChunk ( ChunkIndex ).GetData ( DataIndex );
	}

	Body ( DataRef );

	if ( bSendEvent )
	{
		BroadcastData.NewData = DataRef;

		AddDataChangeEvent ( BroadcastData );
	}
}
