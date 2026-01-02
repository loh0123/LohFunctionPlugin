// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LFPChunkedStepFlowDataComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN ( LogChunkedStepFlowDataComponent , Log , All );

USTRUCT ( BlueprintType )
struct LOHFUNCTIONPLUGIN_API FLFPStepFlowCellData
{
	GENERATED_BODY ( )

	FLFPStepFlowCellData ( ) = default;

private:

	UPROPERTY ( )
	int16 FlowVectorX = 0;

	UPROPERTY ( )
	int16 FlowVectorY = 0;

	UPROPERTY ( )
	int16 FlowVectorZ = 0;

	UPROPERTY ( )
	int16 FlowResistant = 0;

public:

	FORCEINLINE int32 GetFlowX ( ) const
	{
		return FlowVectorX;
	}

	FORCEINLINE int32 GetFlowY ( ) const
	{
		return FlowVectorY;
	}

	FORCEINLINE int32 GetFlowZ ( ) const
	{
		return FlowVectorZ;
	}

	FORCEINLINE int32 GetFlowResistant ( ) const
	{
		return FlowResistant;
	}

	FORCEINLINE FIntVector GetFlowVector ( ) const
	{
		return FIntVector ( FlowVectorX , FlowVectorY , FlowVectorZ );
	}

public:

	FORCEINLINE int32 GetFlowVectorComponent ( const int32 ComponentIndex ) const
	{
		switch ( ComponentIndex )
		{
			case 0 : return FlowVectorX;
				break;
			case 1 : return FlowVectorY;
				break;
			case 2 : return FlowVectorZ;
				break;
			default : checkf ( false , TEXT ( "Invalid ComponentIndex" ) );
		}

		return 0;
	}

	FORCEINLINE void SetFlowVectorComponent ( const int32 ComponentIndex , const int32 NewValue )
	{
		switch ( ComponentIndex )
		{
			case 0 : FlowVectorX = FMath::Clamp ( NewValue , INT16_MIN , INT16_MAX );
				break;
			case 1 : FlowVectorY = FMath::Clamp ( NewValue , INT16_MIN , INT16_MAX );
				break;
			case 2 : FlowVectorZ = FMath::Clamp ( NewValue , INT16_MIN , INT16_MAX );
				break;
			default : checkf ( false , TEXT ( "Invalid ComponentIndex" ) );
		}
	}

	FORCEINLINE void AddFlowVectorComponent ( const int32 ComponentIndex , const int32 AddValue )
	{
		SetFlowVectorComponent ( ComponentIndex , GetFlowVectorComponent ( ComponentIndex ) + AddValue );
	}

public:

	FORCEINLINE void SetFlowResistant ( const int32 NewValue )
	{
		FlowResistant = FMath::Clamp ( NewValue , INT16_MIN , INT16_MAX );
	}

public:

	FORCEINLINE bool operator== ( const FLFPStepFlowCellData& Other ) const
	{
		return
			FlowVectorX == Other.FlowVectorX
			&& FlowVectorY == Other.FlowVectorY
			&& FlowVectorZ == Other.FlowVectorZ
			&& FlowResistant == Other.FlowResistant;
	}
};

USTRUCT ( )
struct FLFPStepFlowChunkData
{
	GENERATED_BODY ( )

	FLFPStepFlowChunkData ( ) = default;

private:

	UPROPERTY ( )
	TArray < FLFPStepFlowCellData > DataList = TArray < FLFPStepFlowCellData > ( );

public:

	FORCEINLINE void InitializeChunkData ( const int32 NewDataIndexSize )
	{
		DataList.SetNumZeroed ( NewDataIndexSize );
	}

	FORCEINLINE void DeinitializeChunkData ( )
	{
		DataList.Empty ( );
	}

public:

	FORCEINLINE bool IsInitialized ( ) const
	{
		return DataList.IsEmpty ( ) == false;
	}

	FORCEINLINE bool IsDataIndexValid ( const int32 DataIndex ) const
	{
		return DataList.IsValidIndex ( DataIndex );
	}

public:

	FORCEINLINE const FLFPStepFlowCellData& GetData ( const int32 DataIndex ) const
	{
		check ( IsDataIndexValid ( DataIndex ) );

		return DataList [ DataIndex ];
	}

	FORCEINLINE void SetData ( const int32 DataIndex , const FLFPStepFlowCellData& NewData )
	{
		check ( IsDataIndexValid ( DataIndex ) );

		DataList [ DataIndex ] = NewData;
	}

public:

	FORCEINLINE const TArray < FLFPStepFlowCellData >& GetDataList ( ) const
	{
		return DataList;
	}
};

USTRUCT ( )
struct FLFPStepFlowRegionData
{
	GENERATED_BODY ( )

private:

	UPROPERTY ( )
	TArray < FLFPStepFlowChunkData > ChunkList = TArray < FLFPStepFlowChunkData > ( );

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

	FORCEINLINE const FLFPStepFlowChunkData& GetChunk ( const int32 ChunkIndex ) const
	{
		checkf ( ChunkList.IsValidIndex ( ChunkIndex ) ,
		         TEXT(
			         "ChunkIndex invalid, call InitializeRegionData first. Resize region data after initialized not allow."
		         ) );

		return ChunkList [ ChunkIndex ];
	}

	FORCEINLINE FLFPStepFlowChunkData& GetChunk ( const int32 ChunkIndex )
	{
		checkf ( ChunkList.IsValidIndex ( ChunkIndex ) ,
		         TEXT(
			         "ChunkIndex invalid, call InitializeRegionData first. Resize region data after initialized not allow."
		         ) );

		return ChunkList [ ChunkIndex ];
	}

public:

	FORCEINLINE bool IsFlowable ( ) const { return IsInitialized ( ); }
};

USTRUCT ( BlueprintType )
struct FLFPChunkedStepFlowSerializeData
{
	GENERATED_BODY ( )

public:

	UPROPERTY ( )
	TArray < uint8 > DataList = TArray < uint8 > ( );

	UPROPERTY ( )
	FName CompressionName = NAME_Oodle;
};

USTRUCT ( BlueprintType )
struct FLFPStepFlowChangeEvent
{
	GENERATED_BODY ( )

	FLFPStepFlowChangeEvent ( ) = default;

	FLFPStepFlowChangeEvent
	(
		const int32                 InRegionIndex ,
		const int32                 InChunkIndex ,
		const int32                 InDataIndex ,
		const FLFPStepFlowCellData& InOldFlow ,
		const FLFPStepFlowCellData& InNewFlow
		) : RegionIndex ( InRegionIndex )
		    , ChunkIndex ( InChunkIndex )
		    , DataIndex ( InDataIndex )
		    , OldFlow ( InOldFlow )
		    , NewFlow ( InNewFlow )
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
	FLFPStepFlowCellData OldFlow = FLFPStepFlowCellData ( );

	UPROPERTY ( VisibleAnywhere , BlueprintReadOnly , Category=Default )
	FLFPStepFlowCellData NewFlow = FLFPStepFlowCellData ( );
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam ( FLFPChunkedStepFlowData_DataChanged , const TArray<FLFPStepFlowChangeEvent>& , ChangeList );


UCLASS ( )
class ULFPChunkedStepFlowDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY ( )

public:

	UFUNCTION ( BlueprintCallable , Category = "LFPChunkedFlowDataLibrary" )
	static FLFPStepFlowCellData MakeFlowCellData ( const FIntVector FlowVector , const int32 FlowResistant );

	UFUNCTION ( BlueprintCallable , Category = "LFPChunkedFlowDataLibrary" )
	static FIntVector GetFlowCellVelocity ( const FLFPStepFlowCellData& CellData );

	UFUNCTION ( BlueprintCallable , Category = "LFPChunkedFlowDataLibrary" )
	static int32 GetFlowCellResistant ( const FLFPStepFlowCellData& CellData );
};

UCLASS ( ClassGroup=(Custom) , meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPChunkedStepFlowDataComponent : public UActorComponent
{
	GENERATED_BODY ( )

public:

	// Sets default values for this component's properties
	ULFPChunkedStepFlowDataComponent ( );

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
	void LoadRegion ( const int32 RegionIndex , const FLFPChunkedStepFlowSerializeData& LoadData );

	UFUNCTION ( BlueprintCallable )
	void SaveRegion ( const int32 RegionIndex , FLFPChunkedStepFlowSerializeData& SaveData );

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
	const FLFPStepFlowCellData& GetData_Checked ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

public:

	UFUNCTION ( BlueprintCallable )
	TArray < FLFPStepFlowCellData > GetDataList ( const int32 RegionIndex , const int32 ChunkIndex ) const;

	UFUNCTION ( BlueprintCallable )
	FLFPStepFlowCellData GetData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

	UFUNCTION ( BlueprintCallable )
	void SetData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FLFPStepFlowCellData& NewData );

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

private:

	UFUNCTION ( )
	void AddFlowChangeEvent ( const FLFPStepFlowChangeEvent& NewEvent );

	UFUNCTION ( )
	void BroadcastFlowChangeEvent ( );

private:

	UPROPERTY ( Transient )
	TArray < FLFPStepFlowChangeEvent > FlowChangeEventList;

	UPROPERTY ( Transient )
	FTimerHandle FlowChangeEventHandle;

public:

	UPROPERTY ( BlueprintAssignable )
	FLFPChunkedStepFlowData_DataChanged OnFlowChanged;

private:

	UPROPERTY ( Transient )
	TArray < FLFPStepFlowRegionData > RegionDataList = TArray < FLFPStepFlowRegionData > ( );

protected:

	UPROPERTY ( EditAnywhere , Category = "Setting|IndexSize" )
	int32 DataIndexSize = 1;

	UPROPERTY ( EditAnywhere , Category = "Setting|IndexSize" )
	int32 ChunkIndexSize = 1;

	UPROPERTY ( EditAnywhere , Category = "Setting|IndexSize" )
	int32 RegionIndexSize = 1;
};
