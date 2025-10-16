// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LFPChunkedStepFlowDataComponent.h"
#include "LFPGridStepFlowDataComponent.generated.h"

USTRUCT ( BlueprintType )
struct FLFPStepFlowNeighbourCellData
{
	GENERATED_BODY ( )

	FLFPStepFlowNeighbourCellData ( ) = default;

public:

	UPROPERTY ( )
	FIntVector FlowVectorPos = FIntVector ( );

	UPROPERTY ( )
	FIntVector FlowVectorNeg = FIntVector ( );

public:

	UPROPERTY ( )
	FIntVector FlowResistantPos = FIntVector ( INT32_MAX );

	UPROPERTY ( )
	FIntVector FlowResistantNeg = FIntVector ( INT32_MAX );

	UPROPERTY ( )
	int32 CenterResistant = INT32_MAX;

public:

	FORCEINLINE int32 GetFlowDivergence ( ) const
	{
		//constexpr float ClampSize = INT8_MAX;

		const int32 GradientX = FlowVectorPos.X - FlowVectorNeg.X; // / ClampSize;
		const int32 GradientY = FlowVectorPos.Y - FlowVectorNeg.Y; // / ClampSize;
		const int32 GradientZ = FlowVectorPos.Z - FlowVectorNeg.Z; // / ClampSize;

		return GradientX + GradientY + GradientZ;
	}

	FORCEINLINE int32 GetFlowPressure ( ) const
	{
		return -GetFlowDivergence ( ) / 6; // Constant Edge Count
	}

	FORCEINLINE int32 GetTotalFlow ( ) const
	{
		return
			FMath::Abs ( FlowVectorNeg.X ) +
			FMath::Abs ( FlowVectorNeg.Y ) +
			FMath::Abs ( FlowVectorNeg.Z ) +
			FMath::Abs ( FlowVectorPos.X ) +
			FMath::Abs ( FlowVectorPos.Y ) +
			FMath::Abs ( FlowVectorPos.Z );
	}

public:

	FORCEINLINE int32 GetTotalResistant ( ) const
	{
		return
			FlowResistantNeg.X +
			FlowResistantNeg.Y +
			FlowResistantNeg.Z +
			FlowResistantPos.X +
			FlowResistantPos.Y +
			FlowResistantPos.Z;
	}

public:

	FORCEINLINE int32 GetFlowVector ( const int32 ComponentIndex ) const
	{
		if ( ComponentIndex < 0 || ComponentIndex >= 6 )
		{
			checkf ( false , TEXT ( "Invalid ComponentIndex" ) );

			return 0;
		}

		if ( ComponentIndex < 3 )
		{
			return FlowVectorPos [ ComponentIndex ];
		}
		else
		{
			return FlowVectorNeg [ ComponentIndex - 3 ];
		}
	}

	FORCEINLINE void SetFlowVector ( const int32 ComponentIndex , const int32 NewValue )
	{
		if ( ComponentIndex < 0 || ComponentIndex >= 6 )
		{
			checkf ( false , TEXT ( "Invalid ComponentIndex" ) );

			return;
		}

		if ( ComponentIndex < 3 )
		{
			FlowVectorPos [ ComponentIndex ] = NewValue;
		}
		else
		{
			FlowVectorNeg [ ComponentIndex - 3 ] = NewValue;
		}
	}

public:

	FORCEINLINE int32 GetFlowResistant ( const int32 ComponentIndex , const int32 FlowValue ) const
	{
		return
			FlowValue >= 0
			? FMath::Max ( 0 , FlowValue - GetFlowResistantWithoutApply ( ComponentIndex ) )
			: FMath::Min ( 0 , FlowValue + GetFlowResistantWithoutApply ( ComponentIndex ) );
	}

	FORCEINLINE int32 GetFlowResistantWithoutApply ( const int32 ComponentIndex ) const
	{
		if ( ComponentIndex < 0 || ComponentIndex >= 6 )
		{
			checkf ( false , TEXT ( "Invalid ComponentIndex" ) );

			return 0;
		}

		if ( ComponentIndex < 3 )
		{
			return CenterResistant + FlowResistantPos [ ComponentIndex ];
		}
		else
		{
			return CenterResistant + FlowResistantNeg [ ComponentIndex - 3 ];
		}
	}

	FORCEINLINE void SetFlowResistant ( const int32 ComponentIndex , const int32 NewValue )
	{
		if ( ComponentIndex < 0 || ComponentIndex >= 6 )
		{
			checkf ( false , TEXT ( "Invalid ComponentIndex" ) );

			return;
		}

		if ( ComponentIndex < 3 )
		{
			FlowResistantPos [ ComponentIndex ] = NewValue;
		}
		else
		{
			FlowResistantNeg [ ComponentIndex - 3 ] = NewValue;
		}
	}
};

UCLASS ( )
class ULFPGridStepFlowDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY ( )

public:

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedStepFlowDataLibrary" )
	static int32 GetFlowPressure ( const FLFPStepFlowNeighbourCellData& Data );

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedStepFlowDataLibrary" )
	static int32 GetTotalFlow ( const FLFPStepFlowNeighbourCellData& Data );

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedStepFlowDataLibrary" )
	static int32 GetFlowResistant ( const FLFPStepFlowNeighbourCellData& Data , const int32 ComponentIndex );

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedStepFlowDataLibrary" )
	static int32 GetSelfFlowResistant ( const FLFPStepFlowNeighbourCellData& Data );

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedStepFlowDataLibrary" )
	static int32 GetFlowDivergence ( const FLFPStepFlowNeighbourCellData& Data );
};

UCLASS ( ClassGroup=(Custom) , meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPGridStepFlowDataComponent : public ULFPChunkedStepFlowDataComponent
{
	GENERATED_BODY ( )

public:

	// Sets default values for this component's properties
	ULFPGridStepFlowDataComponent ( );

protected:

	// Called when the game starts
	virtual void BeginPlay ( ) override;

public:

	// Called every frame
	virtual void TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;

public:

	UFUNCTION ( BlueprintCallable )
	FLFPStepFlowNeighbourCellData GetNeighbourFlowData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

	UFUNCTION ( BlueprintCallable )
	FIntVector GetPointVelocity ( const FVector& Point ) const;

public:

	UFUNCTION ( BlueprintCallable )
	FLFPStepFlowCellData CalculateVelocityOnData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex );

	UFUNCTION ( BlueprintCallable )
	FLFPStepFlowCellData CalculateAdventOnData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const float Step );

public:

	UFUNCTION ( BlueprintCallable )
	void SolveVelocityOnRegion ( const int32 RegionIndex );

	UFUNCTION ( BlueprintCallable )
	void SolveAdventOnRegion ( const int32 RegionIndex , const float Step );

public:

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	const FIntVector& GetDataGridSize ( ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	const FIntVector& GetChunkGridSize ( ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	const FIntVector& GetRegionGridSize ( ) const;

public:

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FIntVector ToChunkGridPosition ( const FIntPoint ChunkGridIndex , const bool bRound = false ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FIntPoint ToChunkGridIndex ( FIntVector ChunkGridPosition , const bool bRound = false ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FIntVector ToDataGridPosition ( const FIntVector DataGridIndex , const bool bRound = false ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FIntVector ToDataGridIndex ( FIntVector DataGridPosition , const bool bRound = false ) const;

public:

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedIndexTranslator | Getter" )
	FIntVector GetDistanceToChunkGridIndex ( const FIntPoint ChunkGridIndexA , const FIntPoint ChunkGridIndexB , const bool bAbsResult = true ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedIndexTranslator | Getter" )
	FIntVector GetDistanceToDataGridIndex ( const FIntVector DataGridIndexA , const FIntVector DataGridIndexB , const bool bAbsResult = true ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedIndexTranslator | Getter" )
	FIntPoint AddOffsetToChunkGridIndex ( const FIntPoint ChunkGridIndex , const FIntVector Offset , const bool bRound = false ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedIndexTranslator | Getter" )
	FIntVector AddOffsetToDataGridIndex ( const FIntVector DataGridIndex , const FIntVector Offset , const bool bRound = false ) const;

protected:

	UPROPERTY ( EditAnywhere , BlueprintReadOnly , Category = "Setting|GridSize" )
	FIntVector DataGridSize = FIntVector ( 1 );

	UPROPERTY ( EditAnywhere , BlueprintReadOnly , Category = "Setting|GridSize" )
	FIntVector ChunkGridSize = FIntVector ( 1 );

	UPROPERTY ( EditAnywhere , BlueprintReadOnly , Category = "Setting|GridSize" )
	FIntVector RegionGridSize = FIntVector ( 1 );
};
