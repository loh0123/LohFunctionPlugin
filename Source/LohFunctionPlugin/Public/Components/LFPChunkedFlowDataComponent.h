// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LFPChunkedFlowDataComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN ( LogChunkedFlowDataComponent , Log , All );

UENUM ( BlueprintType , meta=( Bitflags , UseEnumValuesAsMaskValuesInEditor=true ) )
enum class ELFPFlowSetting : uint8
{
	LFP_None         = 0 UMETA ( DisplayName = "None" , Hidden ) ,
	LFP_Inaccessible = 1 << 0 UMETA ( DisplayName = "Inaccessible" ) ,
};

ENUM_CLASS_FLAGS ( ELFPFlowSetting );

USTRUCT ( BlueprintType )
struct FLFPFlowCellData
{
	GENERATED_BODY ( )

	FLFPFlowCellData ( ) = default;

public:

	UPROPERTY ( )
	ELFPFlowSetting FlowSetting = ELFPFlowSetting::LFP_None;

	UPROPERTY ( )
	float FlowVectorX = 0;

	UPROPERTY ( )
	float FlowVectorY = 0;

	UPROPERTY ( )
	float FlowVectorZ = 0;

	UPROPERTY ( )
	float FlowPressure = 0;

public:

	FORCEINLINE const float& GetFlowVectorComponent ( const int32 ComponentIndex ) const
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

		// This is an error and is not supposed to hit
		return FlowVectorX;
	}

	FORCEINLINE float& GetFlowVectorComponent ( const int32 ComponentIndex )
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

		// This is an error and is not supposed to hit
		return FlowVectorX;
	}

public:

	FORCEINLINE bool IsFlowable ( ) const
	{
		return ( FlowSetting & ELFPFlowSetting::LFP_Inaccessible ) == ELFPFlowSetting::LFP_None;
	}

public:

	FORCEINLINE bool operator== ( const FLFPFlowCellData& Other ) const
	{
		return
			FlowSetting == Other.FlowSetting
			&& FlowVectorX == Other.FlowVectorX
			&& FlowVectorY == Other.FlowVectorY
			&& FlowVectorZ == Other.FlowVectorZ
			&& FlowPressure == Other.FlowPressure;
	}
};

USTRUCT ( )
struct FLFPFlowChunkData
{
	GENERATED_BODY ( )

	FLFPFlowChunkData ( ) = default;

private:

	UPROPERTY ( )
	TArray < FLFPFlowCellData > DataList = TArray < FLFPFlowCellData > ( );

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

	FORCEINLINE const FLFPFlowCellData& GetData ( const int32 DataIndex ) const
	{
		check ( IsDataIndexValid ( DataIndex ) );

		return DataList [ DataIndex ];
	}

	FORCEINLINE void SetData ( const int32 DataIndex , const FLFPFlowCellData& NewData )
	{
		check ( IsDataIndexValid ( DataIndex ) );

		DataList [ DataIndex ] = NewData;
	}

public:

	FORCEINLINE const TArray < FLFPFlowCellData >& GetDataList ( ) const
	{
		return DataList;
	}
};

USTRUCT ( )
struct FLFPFlowRegionData
{
	GENERATED_BODY ( )

private:

	UPROPERTY ( )
	TArray < FLFPFlowChunkData > ChunkList = TArray < FLFPFlowChunkData > ( );

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

	FORCEINLINE const FLFPFlowChunkData& GetChunk ( const int32 ChunkIndex ) const
	{
		checkf ( ChunkList.IsValidIndex ( ChunkIndex ) ,
		         TEXT(
			         "ChunkIndex invalid, call InitializeRegionData first. Resize region data after initialized not allow."
		         ) );

		return ChunkList [ ChunkIndex ];
	}

	FORCEINLINE FLFPFlowChunkData& GetChunk ( const int32 ChunkIndex )
	{
		checkf ( ChunkList.IsValidIndex ( ChunkIndex ) ,
		         TEXT(
			         "ChunkIndex invalid, call InitializeRegionData first. Resize region data after initialized not allow."
		         ) );

		return ChunkList [ ChunkIndex ];
	}
};

USTRUCT ( BlueprintType )
struct FLFPChunkedFlowSerializeData
{
	GENERATED_BODY ( )

public:

	UPROPERTY ( )
	TArray < uint8 > DataList = TArray < uint8 > ( );

	UPROPERTY ( )
	FName CompressionName = NAME_Oodle;
};

USTRUCT ( BlueprintType )
struct FLFPFlowChangeEvent
{
	GENERATED_BODY ( )

	FLFPFlowChangeEvent ( ) = default;

	FLFPFlowChangeEvent
	(
		const int32             InRegionIndex ,
		const int32             InChunkIndex ,
		const int32             InDataIndex ,
		const FLFPFlowCellData& InOldFlow ,
		const FLFPFlowCellData& InNewFlow
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
	FLFPFlowCellData OldFlow = FLFPFlowCellData ( );

	UPROPERTY ( VisibleAnywhere , BlueprintReadOnly , Category=Default )
	FLFPFlowCellData NewFlow = FLFPFlowCellData ( );
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam ( FLFPChunkedFlowData_DataChanged , const TArray<FLFPFlowChangeEvent>& , ChangeList );


UCLASS ( )
class ULFPChunkedFlowDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY ( )

public:

	UFUNCTION ( BlueprintCallable , Category = "LFPChunkedFlowDataLibrary" )
	static FLFPFlowCellData MakeFlowCellData ( const ELFPFlowSetting FlowSetting , const FVector FlowVector , const float FlowPressure );

	UFUNCTION ( BlueprintCallable , Category = "LFPChunkedFlowDataLibrary" )
	static ELFPFlowSetting GetFlowCellSetting ( const FLFPFlowCellData& CellData );

	UFUNCTION ( BlueprintCallable , Category = "LFPChunkedFlowDataLibrary" )
	static FVector GetFlowCellVelocity ( const FLFPFlowCellData& CellData );

	UFUNCTION ( BlueprintCallable , Category = "LFPChunkedFlowDataLibrary" )
	static float GetFlowCellPressure ( const FLFPFlowCellData& CellData );
};

UCLASS ( ClassGroup=(Custom) , meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPChunkedFlowDataComponent : public UActorComponent
{
	GENERATED_BODY ( )

public:

	// Sets default values for this component's properties
	ULFPChunkedFlowDataComponent ( );

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
	void LoadRegion ( const int32 RegionIndex , const FLFPChunkedFlowSerializeData& LoadData );

	UFUNCTION ( BlueprintCallable )
	void SaveRegion ( const int32 RegionIndex , FLFPChunkedFlowSerializeData& SaveData );

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
	FORCEINLINE const FLFPFlowCellData& GetData_Checked ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

public:

	UFUNCTION ( BlueprintCallable )
	TArray < FLFPFlowCellData > GetDataList ( const int32 RegionIndex , const int32 ChunkIndex ) const;

	UFUNCTION ( BlueprintCallable )
	FLFPFlowCellData GetData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

	UFUNCTION ( BlueprintCallable )
	void SetData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const FLFPFlowCellData& NewData );

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
	void AddFLowChangeEvent ( const FLFPFlowChangeEvent& NewEvent );

	UFUNCTION ( )
	void BroadcastFlowChangeEvent ( );

private:

	UPROPERTY ( Transient )
	TArray < FLFPFlowChangeEvent > FlowChangeEventList;

	UPROPERTY ( Transient )
	FTimerHandle FlowChangeEventHandle;

public:

	UPROPERTY ( BlueprintAssignable )
	FLFPChunkedFlowData_DataChanged OnFlowChanged;

private:

	UPROPERTY ( Transient )
	TArray < FLFPFlowRegionData > RegionDataList = TArray < FLFPFlowRegionData > ( );

protected:

	UPROPERTY ( EditAnywhere , Category = "Setting|IndexSize" )
	int32 DataIndexSize = 1;

	UPROPERTY ( EditAnywhere , Category = "Setting|IndexSize" )
	int32 ChunkIndexSize = 1;

	UPROPERTY ( EditAnywhere , Category = "Setting|IndexSize" )
	int32 RegionIndexSize = 1;
};
