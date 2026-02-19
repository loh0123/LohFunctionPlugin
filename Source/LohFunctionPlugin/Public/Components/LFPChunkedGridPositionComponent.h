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
	void SetSize ( const FIntVector& NewRegionSize , const FIntVector& NewChunkSize , const FIntVector& NewDataSize );

	UFUNCTION ( BlueprintCallable , Category = "LFPGridTagDataComponent | Setter" )
	void SetIsolation ( const bool bRegion , const bool bChunk );

public:

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FORCEINLINE FIntVector GetChunkedGridSize ( ) const;

public:

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	const FORCEINLINE FIntVector& GetDataGridSize ( ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	const FORCEINLINE FIntVector& GetChunkGridSize ( ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	const FORCEINLINE FIntVector& GetRegionGridSize ( ) const;

public:

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FORCEINLINE bool IsIsolateRegion ( ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FORCEINLINE bool IsIsolateChunk ( ) const;

public:

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FORCEINLINE FIntVector ToChunkGridPosition ( const FIntPoint& ChunkGridIndex ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FORCEINLINE FIntPoint ToChunkGridIndex ( FIntVector ChunkGridPosition ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FORCEINLINE FIntVector ToDataGridPosition ( const FIntVector& DataGridIndex ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FORCEINLINE FIntVector ToDataGridIndex ( FIntVector DataGridPosition ) const;

public:

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedIndexTranslator | Getter" )
	FORCEINLINE FIntVector GetDistanceToChunkGridIndex ( const FIntPoint& ChunkGridIndexA , const FIntPoint& ChunkGridIndexB , const bool bAbsResult = true ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedIndexTranslator | Getter" )
	FORCEINLINE FIntVector GetDistanceToDataGridIndex ( const FIntVector& DataGridIndexA , const FIntVector& DataGridIndexB , const bool bAbsResult = true ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedIndexTranslator | Getter" )
	FORCEINLINE FIntPoint AddOffsetToChunkGridIndex ( const FIntPoint& ChunkGridIndex , const FIntVector& Offset ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedIndexTranslator | Getter" )
	FORCEINLINE FIntVector AddOffsetToDataGridIndex ( const FIntVector& DataGridIndex , const FIntVector& Offset ) const;

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
