// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LFPChunkedFlowDataComponent.h"
#include "LFPGridFlowDataComponent.generated.h"


USTRUCT ( BlueprintType )
struct FLFPFlowEdgeCellData
{
	GENERATED_BODY ( )

	FLFPFlowEdgeCellData ( ) = default;

public:

	UPROPERTY ( )
	float FlowVectorPosX = 0;

	UPROPERTY ( )
	float FlowVectorPosY = 0;

	UPROPERTY ( )
	float FlowVectorPosZ = 0;

	UPROPERTY ( )
	float FlowVectorNegX = 0;

	UPROPERTY ( )
	float FlowVectorNegY = 0;

	UPROPERTY ( )
	float FlowVectorNegZ = 0;

	UPROPERTY ( )
	float FlowPressurePosX = 0;

	UPROPERTY ( )
	float FlowPressurePosY = 0;

	UPROPERTY ( )
	float FlowPressurePosZ = 0;

	UPROPERTY ( )
	float FlowPressureNegX = 0;

	UPROPERTY ( )
	float FlowPressureNegY = 0;

	UPROPERTY ( )
	float FlowPressureNegZ = 0;

	UPROPERTY ( )
	float CenterPressure = 0;

	UPROPERTY ( )
	uint8 OpenEdgeCount = 0;

public:

	FORCEINLINE float GetFlowDivergence ( ) const
	{
		//constexpr float ClampSize = INT8_MAX;

		const float GradientX = FlowVectorPosX - FlowVectorNegX; // / ClampSize;
		const float GradientY = FlowVectorPosY - FlowVectorNegY; // / ClampSize;
		const float GradientZ = FlowVectorPosZ - FlowVectorNegZ; // / ClampSize;

		return GradientX + GradientY + GradientZ;
	}

	FORCEINLINE float GetTotalPressure ( ) const
	{
		return
			FlowPressureNegX +
			FlowPressureNegY +
			FlowPressureNegZ +
			FlowPressurePosX +
			FlowPressurePosY +
			FlowPressurePosZ;
	}

public:

	[[nodiscard]] const float& GetFlowVector ( const int32 ComponentIndex ) const
	{
		switch ( ComponentIndex )
		{
			case 0 : return FlowVectorPosX;
				break;
			case 1 : return FlowVectorPosY;
				break;
			case 2 : return FlowVectorPosZ;
				break;
			case 3 : return FlowVectorNegX;
				break;
			case 4 : return FlowVectorNegY;
				break;
			case 5 : return FlowVectorNegZ;
				break;
			default : checkf ( false , TEXT ( "Invalid ComponentIndex" ) );
				break;
		}

		// This is an error and is not supposed to hit
		return FlowVectorPosX;
	}

	[[nodiscard]] float& GetFlowVector ( const int32 ComponentIndex )
	{
		switch ( ComponentIndex )
		{
			case 0 : return FlowVectorPosX;
				break;
			case 1 : return FlowVectorPosY;
				break;
			case 2 : return FlowVectorPosZ;
				break;
			case 3 : return FlowVectorNegX;
				break;
			case 4 : return FlowVectorNegY;
				break;
			case 5 : return FlowVectorNegZ;
				break;
			default : checkf ( false , TEXT ( "Invalid ComponentIndex" ) );
				break;
		}

		// This is an error and is not supposed to hit
		return FlowVectorPosX;
	}

	[[nodiscard]] const float& GetFlowPressure ( const int32 ComponentIndex ) const
	{
		switch ( ComponentIndex )
		{
			case 0 : return FlowPressurePosX;
				break;
			case 1 : return FlowPressurePosY;
				break;
			case 2 : return FlowPressurePosZ;
				break;
			case 3 : return FlowPressureNegX;
				break;
			case 4 : return FlowPressureNegY;
				break;
			case 5 : return FlowPressureNegZ;
				break;
			default : checkf ( false , TEXT ( "Invalid ComponentIndex" ) );
				break;
		}

		// This is an error and is not supposed to hit
		return FlowPressurePosX;
	}

	[[nodiscard]] float& GetFlowPressure ( const int32 ComponentIndex )
	{
		switch ( ComponentIndex )
		{
			case 0 : return FlowPressurePosX;
				break;
			case 1 : return FlowPressurePosY;
				break;
			case 2 : return FlowPressurePosZ;
				break;
			case 3 : return FlowPressureNegX;
				break;
			case 4 : return FlowPressureNegY;
				break;
			case 5 : return FlowPressureNegZ;
				break;
			default : checkf ( false , TEXT ( "Invalid ComponentIndex" ) );
				break;
		}

		// This is an error and is not supposed to hit
		return FlowPressurePosX;
	}
};

UCLASS ( )
class ULFPGridFlowDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY ( )

public:

	UFUNCTION ( BlueprintCallable , Category = "LFPChunkedFlowDataLibrary" )
	static int32 GetOpenEdge ( const FLFPFlowEdgeCellData& Data );
};

UCLASS ( ClassGroup=(Custom) , meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPGridFlowDataComponent : public ULFPChunkedFlowDataComponent
{
	GENERATED_BODY ( )

public:

	// Sets default values for this component's properties
	ULFPGridFlowDataComponent ( );

protected:

	// Called when the game starts
	virtual void BeginPlay ( ) override;

public:

	// Called every frame
	virtual void TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;

public:

	UFUNCTION ( BlueprintCallable )
	FLFPFlowEdgeCellData GetEdgeFlowData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

	UFUNCTION ( BlueprintCallable )
	float GetFlowPressure ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

	UFUNCTION ( BlueprintCallable )
	float GetFlowDivergence ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const;

	UFUNCTION ( BlueprintCallable )
	FVector GetPointVelocity ( const FVector& Point ) const;

public:

	//UFUNCTION ( BlueprintCallable )
	//void SolveDiffusionOnData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const float TimeStep );
	//
	//UFUNCTION ( BlueprintCallable )
	//void SolveAdvectionOnData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const float TimeStep );
	//
	//UFUNCTION ( BlueprintCallable )
	//void SolveProjectionOnData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const float TimeStep );

public:

	UFUNCTION ( BlueprintCallable )
	FLFPFlowCellData CalculatePressureOnData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const float TimeStep , const float WeightSOR );

	UFUNCTION ( BlueprintCallable )
	FLFPFlowCellData CalculateVelocityOnData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const float TimeStep );

	UFUNCTION ( BlueprintCallable )
	FLFPFlowCellData CalculateAdventOnData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const float TimeStep );

public:

	UFUNCTION ( BlueprintCallable )
	void SolvePressureOnRegion ( const int32 RegionIndex , const float TimeStep , const float WeightSOR );

	UFUNCTION ( BlueprintCallable )
	void SolveVelocityOnRegion ( const int32 RegionIndex , const float TimeStep );

	UFUNCTION ( BlueprintCallable )
	void SolveAdventOnRegion ( const int32 RegionIndex , const float TimeStep );

	UFUNCTION ( BlueprintCallable )
	void SolvePressureOnLoop ( const int32 RegionIndex , const float TimeStep , const int32 LoopCount , const float WeightSOR );

	UFUNCTION ( BlueprintCallable )
	void SolveVelocityOnLoop ( const int32 RegionIndex , const float TimeStep , const int32 LoopCount );

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

protected:

	//const float CellSize    = INT8_MAX;
	//const float CellDensity = 1.0f;
};
