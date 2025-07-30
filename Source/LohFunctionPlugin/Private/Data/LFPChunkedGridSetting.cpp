// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/LFPChunkedGridSetting.h"

#include "Math/LFPGridLibrary.h"

FIntVector ULFPChunkedGridSetting::GetDistanceToChunkGridIndex ( const FIntPoint ChunkGridIndexA , const FIntPoint ChunkGridIndexB , const bool bAbsResult ) const
{
	const FIntVector Total = ToChunkGridPosition ( ChunkGridIndexA ) - ToChunkGridPosition ( ChunkGridIndexB );

	return bAbsResult ? FIntVector ( FMath::Abs ( Total.X ) , FMath::Abs ( Total.Y ) , FMath::Abs ( Total.Z ) ) : Total;
}

FIntVector ULFPChunkedGridSetting::GetDistanceToDataGridIndex ( const FIntVector DataGridIndexA , const FIntVector DataGridIndexB , const bool bAbsResult ) const
{
	const FIntVector Total = ToDataGridPosition ( DataGridIndexA ) - ToDataGridPosition ( DataGridIndexB );

	return bAbsResult ? FIntVector ( FMath::Abs ( Total.X ) , FMath::Abs ( Total.Y ) , FMath::Abs ( Total.Z ) ) : Total;
}

FIntPoint ULFPChunkedGridSetting::AddOffsetToChunkGridIndex ( const FIntPoint ChunkGridIndex , const FIntVector Offset , const bool bRound ) const
{
	return ToChunkGridIndex ( ToChunkGridPosition ( ChunkGridIndex , bRound ) + Offset , bRound );
}

FIntVector ULFPChunkedGridSetting::AddOffsetToDataGridIndex ( const FIntVector DataGridIndex , const FIntVector Offset , const bool bRound ) const
{
	return ToDataGridIndex ( ToDataGridPosition ( DataGridIndex , bRound ) + Offset , bRound );
}
