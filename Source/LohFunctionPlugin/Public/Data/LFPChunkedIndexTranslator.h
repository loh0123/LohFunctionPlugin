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

	virtual const FIntVector& GetDataGridSize ( ) const { return FIntVector::ZeroValue; }

	virtual const FIntVector& GetChunkGridSize ( ) const { return FIntVector::ZeroValue; }

	virtual const FIntVector& GetRegionGridSize ( ) const { return FIntVector::ZeroValue; }

public:

	FORCEINLINE int32 GetDataIndexSize ( ) const
	{
		const FIntVector DataGridSize = GetDataGridSize ( );
		return DataGridSize.X * DataGridSize.Y * DataGridSize.Z;
	}

	FORCEINLINE int32 GetChunkIndexSize ( ) const
	{
		const FIntVector ChunkGridSize = GetChunkGridSize ( );
		return ChunkGridSize.X * ChunkGridSize.Y * ChunkGridSize.Z;
	}

	FORCEINLINE int32 GetRegionIndexSize ( ) const
	{
		const FIntVector RegionGridSize = GetRegionGridSize ( );
		return RegionGridSize.X * RegionGridSize.Y * RegionGridSize.Z;
	}

public:

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	virtual FIntVector ToChunkGridPosition ( const FIntPoint ChunkGridIndex , const bool bRound = false ) const { return FIntVector ( ); }

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	virtual FIntPoint ToChunkGridIndex ( FIntVector ChunkGridPosition , const bool bRound = false ) const { return FIntPoint ( ); }

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	virtual FIntVector ToDataGridPosition ( const FIntVector DataGridIndex , const bool bRound = false ) const { return FIntVector ( ); }

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	virtual FIntVector ToDataGridIndex ( FIntVector DataGridPosition , const bool bRound = false ) const { return FIntVector ( ); }

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	virtual FIntVector AddOffsetToGridIndex ( FIntVector GridIndex , const FIntVector Offset , const bool bRound = false ) const { return FIntVector ( ); }
};
