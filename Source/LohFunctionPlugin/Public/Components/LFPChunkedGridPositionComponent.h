// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LFPChunkedGridPositionComponent.generated.h"


UCLASS ( ClassGroup=(Custom) , meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPChunkedGridPositionComponent : public UActorComponent
{
	GENERATED_BODY ( )

public:

	// Sets default values for this component's properties
	ULFPChunkedGridPositionComponent ( );

protected:

	// Called when the game starts
	virtual void BeginPlay ( ) override;

public:

	// Called every frame
	virtual void TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;

public:

	UFUNCTION ( BlueprintCallable , Category = "LFPGridTagDataComponent | Setter" )
	FORCEINLINE void SetSize ( const FIntVector& NewRegionSize , const FIntVector& NewChunkSize , const FIntVector& NewDataSize )
	{
		RegionGridSize = NewRegionSize;
		ChunkGridSize  = NewChunkSize;
		DataGridSize   = NewDataSize;
	}

	UFUNCTION ( BlueprintCallable , Category = "LFPGridTagDataComponent | Setter" )
	FORCEINLINE void SetIsolation ( const bool bRegion , const bool bChunk )
	{
		bIsolateRegion = bRegion;
		bIsolateChunk  = bChunk;
	}

public:

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FIntVector GetChunkedGridSize ( ) const
	{
		return FIntVector (
		                   RegionGridSize.X * RegionGridSize.Y * RegionGridSize.Z ,
		                   ChunkGridSize.X * ChunkGridSize.Y * ChunkGridSize.Z ,
		                   DataGridSize.X * DataGridSize.Y * DataGridSize.Z
		                  );
	}

public:

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	const FORCEINLINE FIntVector& GetDataGridSize ( ) const
	{
		return DataGridSize;
	}

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	const FORCEINLINE FIntVector& GetChunkGridSize ( ) const
	{
		return ChunkGridSize;
	}

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	const FORCEINLINE FIntVector& GetRegionGridSize ( ) const
	{
		return RegionGridSize;
	}

public:

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FORCEINLINE bool IsIsolateRegion ( ) const
	{
		return bIsolateRegion;
	}

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FORCEINLINE bool IsIsolateChunk ( ) const
	{
		return bIsolateChunk;
	}

public:

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FIntVector ToChunkGridPosition ( const FIntPoint& ChunkGridIndex ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FIntPoint ToChunkGridIndex ( FIntVector ChunkGridPosition ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FIntVector ToDataGridPosition ( const FIntVector& DataGridIndex ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FIntVector ToDataGridIndex ( FIntVector DataGridPosition ) const;

public:

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedIndexTranslator | Getter" )
	FIntVector GetDistanceToChunkGridIndex ( const FIntPoint& ChunkGridIndexA , const FIntPoint& ChunkGridIndexB , const bool bAbsResult = true ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedIndexTranslator | Getter" )
	FIntVector GetDistanceToDataGridIndex ( const FIntVector& DataGridIndexA , const FIntVector& DataGridIndexB , const bool bAbsResult = true ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedIndexTranslator | Getter" )
	FIntPoint AddOffsetToChunkGridIndex ( const FIntPoint& ChunkGridIndex , const FIntVector& Offset ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedIndexTranslator | Getter" )
	FIntVector AddOffsetToDataGridIndex ( const FIntVector& DataGridIndex , const FIntVector& Offset ) const;

protected:

	UPROPERTY ( EditAnywhere , BlueprintReadOnly , Category = "Setting|GridSize" )
	FIntVector DataGridSize = FIntVector ( 1 );

	UPROPERTY ( EditAnywhere , BlueprintReadOnly , Category = "Setting|GridSize" )
	FIntVector ChunkGridSize = FIntVector ( 1 );

	UPROPERTY ( EditAnywhere , BlueprintReadOnly , Category = "Setting|GridSize" )
	FIntVector RegionGridSize = FIntVector ( 1 );

protected:

	UPROPERTY ( EditAnywhere , BlueprintReadOnly , Category = "Setting" )
	bool bIsolateRegion = false;

	UPROPERTY ( EditAnywhere , BlueprintReadOnly , Category = "Setting" )
	bool bIsolateChunk = false;
};
