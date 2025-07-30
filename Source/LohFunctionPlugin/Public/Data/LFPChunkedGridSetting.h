// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LFPChunkedIndexTranslator.h"
#include "LFPChunkedGridSetting.generated.h"

/**
 * 
 */
UCLASS ( Blueprintable )
class LOHFUNCTIONPLUGIN_API ULFPChunkedGridSetting : public ULFPChunkedIndexTranslator
{
	GENERATED_BODY ( )

protected:

	UPROPERTY ( EditAnywhere , BlueprintReadOnly , Category = "Setting|GridSize" )
	FIntVector DataGridSize = FIntVector ( 1 );

	UPROPERTY ( EditAnywhere , BlueprintReadOnly , Category = "Setting|GridSize" )
	FIntVector ChunkGridSize = FIntVector ( 1 );

	UPROPERTY ( EditAnywhere , BlueprintReadOnly , Category = "Setting|GridSize" )
	FIntVector RegionGridSize = FIntVector ( 1 );

public:

	virtual const FIntVector& GetDataGridSize ( ) const override { return DataGridSize; }

	virtual const FIntVector& GetChunkGridSize ( ) const override { return ChunkGridSize; }

	virtual const FIntVector& GetRegionGridSize ( ) const override { return RegionGridSize; }

public:

	virtual FIntVector GetDistanceToChunkGridIndex ( const FIntPoint ChunkGridIndexA , const FIntPoint ChunkGridIndexB , const bool bAbsResult ) const override;
	virtual FIntVector GetDistanceToDataGridIndex ( const FIntVector DataGridIndexA , const FIntVector DataGridIndexB , const bool bAbsResult ) const override;
	virtual FIntPoint  AddOffsetToChunkGridIndex ( const FIntPoint ChunkGridIndex , const FIntVector Offset , const bool bRound = false ) const override;
	virtual FIntVector AddOffsetToDataGridIndex ( const FIntVector DataGridIndex , const FIntVector Offset , const bool bRound = false ) const override;
};
