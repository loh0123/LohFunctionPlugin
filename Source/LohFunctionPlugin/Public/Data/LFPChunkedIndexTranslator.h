// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LFPChunkedIndexTranslator.generated.h"

/**
 * 
 */
UCLASS ( )
class LOHFUNCTIONPLUGIN_API ULFPChunkedIndexTranslator : public UDataAsset
{
	GENERATED_BODY ( )

public:

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedIndexTranslator | Getter" )
	virtual const FIntVector& GetDataGridSize ( ) const { return FIntVector::ZeroValue; }

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedIndexTranslator | Getter" )
	virtual const FIntVector& GetChunkGridSize ( ) const { return FIntVector::ZeroValue; }

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedIndexTranslator | Getter" )
	virtual const FIntVector& GetRegionGridSize ( ) const { return FIntVector::ZeroValue; }

public:

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedIndexTranslator | Getter" )
	virtual int32 GetDataIndexSize ( ) const
	{
		const FIntVector DataGridSize = GetDataGridSize ( );
		return DataGridSize.X * DataGridSize.Y * DataGridSize.Z;
	}

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedIndexTranslator | Getter" )
	virtual int32 GetChunkIndexSize ( ) const
	{
		const FIntVector ChunkGridSize = GetChunkGridSize ( );
		return ChunkGridSize.X * ChunkGridSize.Y * ChunkGridSize.Z;
	}

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedIndexTranslator | Getter" )
	virtual int32 GetRegionIndexSize ( ) const
	{
		const FIntVector RegionGridSize = GetRegionGridSize ( );
		return RegionGridSize.X * RegionGridSize.Y * RegionGridSize.Z;
	}

public:

	FORCEINLINE FIntVector ToChunkGridPosition ( const FIntPoint ChunkGridIndex , const bool bRound = false ) const;
	FORCEINLINE FIntPoint  ToChunkGridIndex ( FIntVector ChunkGridPosition , const bool bRound = false ) const;
	FORCEINLINE FIntVector ToDataGridPosition ( const FIntVector DataGridIndex , const bool bRound = false ) const;
	FORCEINLINE FIntVector ToDataGridIndex ( FIntVector DataGridPosition , const bool bRound = false ) const;

public:

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedIndexTranslator | Getter" )
	virtual FIntVector GetDistanceToChunkGridIndex ( const FIntPoint ChunkGridIndexA , const FIntPoint ChunkGridIndexB , const bool bAbsResult = true ) const { return FIntVector ( ); }

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedIndexTranslator | Getter" )
	virtual FIntVector GetDistanceToDataGridIndex ( const FIntVector DataGridIndexA , const FIntVector DataGridIndexB , const bool bAbsResult = true ) const { return FIntVector ( ); }

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedIndexTranslator | Getter" )
	virtual FIntPoint AddOffsetToChunkGridIndex ( const FIntPoint ChunkGridIndex , const FIntVector Offset , const bool bRound = false ) const { return FIntPoint ( ); }

	UFUNCTION ( BlueprintPure , Category = "LFPChunkedIndexTranslator | Getter" )
	virtual FIntVector AddOffsetToDataGridIndex ( const FIntVector DataGridIndex , const FIntVector Offset , const bool bRound = false ) const { return FIntVector ( ); }
};
