// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LFPStepFlowLibrary.generated.h"


class ULFPStepFlowModifier;
class ULFPChunkedStepFlowDataComponent;
class ULFPChunkedGridPositionComponent;

USTRUCT ( BlueprintType )
struct FLFPStepFlowNeighbourCellData
{
	GENERATED_BODY ( )

	FLFPStepFlowNeighbourCellData ( ) = default;

public:

	UPROPERTY ( )
	FIntVector FlowVectorPos = FIntVector ( 0 );

	UPROPERTY ( )
	FIntVector FlowVectorNeg = FIntVector ( 0 );

public:

	UPROPERTY ( )
	FIntVector FlowResistantPos = FIntVector ( INT32_MAX );

	UPROPERTY ( )
	FIntVector FlowResistantNeg = FIntVector ( INT32_MAX );

	UPROPERTY ( )
	int32 CenterResistant = INT32_MAX;

	UPROPERTY ( )
	int32 EdgeCount = 0;

public:

	FORCEINLINE int32 GetFlowDivergence ( ) const
	{
		const int32 GradientX = FlowVectorPos.X - FlowVectorNeg.X;
		const int32 GradientY = FlowVectorPos.Y - FlowVectorNeg.Y;
		const int32 GradientZ = FlowVectorPos.Z - FlowVectorNeg.Z;

		return GradientX + GradientY + GradientZ;
	}

	FORCEINLINE int32 GetFlowPressure ( ) const
	{
		return -GetFlowDivergence ( ) / EdgeCount;
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

/**
 * 
 */
UCLASS ( )
class LOHFUNCTIONPLUGIN_API ULFPStepFlowLibrary : public UBlueprintFunctionLibrary
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

public:

	UFUNCTION ( BlueprintCallable )
	static FLFPStepFlowNeighbourCellData GetNeighbourFlowData (
		const ULFPChunkedStepFlowDataComponent* DataComponent ,
		const ULFPChunkedGridPositionComponent* PositionComponent ,
		const ULFPStepFlowModifier*             Modifier ,
		const int32                             RegionIndex ,
		const int32                             ChunkIndex ,
		const int32                             DataIndex
		);

	UFUNCTION ( BlueprintCallable )
	static FIntVector GetPointVelocity (
		const ULFPChunkedStepFlowDataComponent* DataComponent ,
		const ULFPChunkedGridPositionComponent* PositionComponent ,
		const ULFPStepFlowModifier*             Modifier ,
		const FVector&                          Point
		);

public:

	UFUNCTION ( BlueprintCallable )
	static FLFPStepFlowCellData CalculateVelocityOnData (
		const ULFPChunkedStepFlowDataComponent* DataComponent ,
		const ULFPChunkedGridPositionComponent* PositionComponent ,
		const ULFPStepFlowModifier*             Modifier ,
		const int32                             RegionIndex ,
		const int32                             ChunkIndex ,
		const int32                             DataIndex
		);

	UFUNCTION ( BlueprintCallable )
	static FLFPStepFlowCellData CalculateAdventOnData (
		const ULFPChunkedStepFlowDataComponent* DataComponent ,
		const ULFPChunkedGridPositionComponent* PositionComponent ,
		const ULFPStepFlowModifier*             Modifier ,
		const int32                             RegionIndex ,
		const int32                             ChunkIndex ,
		const int32                             DataIndex ,
		const float                             Step
		);

public:

	UFUNCTION ( BlueprintCallable )
	static void SolveVelocityOnRegion (
		ULFPChunkedStepFlowDataComponent*       DataComponent ,
		const ULFPChunkedGridPositionComponent* PositionComponent ,
		const ULFPStepFlowModifier*             Modifier ,
		const int32                             RegionIndex
		);

	UFUNCTION ( BlueprintCallable )
	static void SolveAdventOnRegion (
		ULFPChunkedStepFlowDataComponent*       DataComponent ,
		const ULFPChunkedGridPositionComponent* PositionComponent ,
		const ULFPStepFlowModifier*             Modifier ,
		const int32                             RegionIndex ,
		const float                             Step
		);

public:

	UFUNCTION ( BlueprintCallable )
	static void SolveVelocity (
		ULFPChunkedStepFlowDataComponent*       DataComponent ,
		const ULFPChunkedGridPositionComponent* PositionComponent ,
		const ULFPStepFlowModifier*             Modifier
		);

	UFUNCTION ( BlueprintCallable )
	static void SolveAdvent (
		ULFPChunkedStepFlowDataComponent*       DataComponent ,
		const ULFPChunkedGridPositionComponent* PositionComponent ,
		const ULFPStepFlowModifier*             Modifier ,
		const float                             Step
		);
};
