// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/LFPChunkedIndexTranslator.h"

#include "Math/LFPGridLibrary.h"

FIntVector ULFPChunkedIndexTranslator::ToChunkGridPosition ( const FIntPoint ChunkGridIndex , const bool bRound ) const
{
	const FIntVector RegionPos ( ULFPGridLibrary::ToGridLocation ( ChunkGridIndex.X , GetRegionGridSize ( ) , bRound ) );
	const FIntVector ChuckPos ( ULFPGridLibrary::ToGridLocation ( ChunkGridIndex.Y , GetChunkGridSize ( ) , bRound ) );

	return ( RegionPos * GetChunkGridSize ( ) ) + ChuckPos;
}

FIntPoint ULFPChunkedIndexTranslator::ToChunkGridIndex ( FIntVector ChunkGridPosition , const bool bRound ) const
{
	auto DivideVector = [&] ( const FIntVector& A , const FIntVector& B )
	{
		return FIntVector ( A.X / B.X , A.Y / B.Y , A.Z / B.Z );
	};

	const FIntVector TotalSize ( GetRegionGridSize ( ) * GetChunkGridSize ( ) );

	if ( bRound )
	{
		ChunkGridPosition.X %= TotalSize.X;
		ChunkGridPosition.Y %= TotalSize.Y;
		ChunkGridPosition.Z %= TotalSize.Z;

		if ( ChunkGridPosition.X < 0 )
		{
			ChunkGridPosition.X += TotalSize.X;
		}
		if ( ChunkGridPosition.Y < 0 )
		{
			ChunkGridPosition.Y += TotalSize.Y;
		}
		if ( ChunkGridPosition.Z < 0 )
		{
			ChunkGridPosition.Z += TotalSize.Z;
		}
	}
	else if ( ULFPGridLibrary::IsGridLocationValid ( ChunkGridPosition , TotalSize ) == false )
	{
		return FIntPoint::NoneValue;
	}

	const FIntVector RegionPos ( DivideVector ( ChunkGridPosition , GetChunkGridSize ( ) ) );

	return FIntPoint ( ULFPGridLibrary::ToGridIndex ( RegionPos , GetRegionGridSize ( ) ) , ULFPGridLibrary::ToGridIndex ( ChunkGridPosition , GetChunkGridSize ( ) , true ) );
}

FIntVector ULFPChunkedIndexTranslator::ToDataGridPosition ( const FIntVector DataGridIndex , const bool bRound ) const
{
	const FIntVector RegionPos ( ULFPGridLibrary::ToGridLocation ( DataGridIndex.X , GetRegionGridSize ( ) , bRound ) );
	const FIntVector ChuckPos ( ULFPGridLibrary::ToGridLocation ( DataGridIndex.Y , GetChunkGridSize ( ) , bRound ) );
	const FIntVector GridPos ( ULFPGridLibrary::ToGridLocation ( DataGridIndex.Z , GetDataGridSize ( ) , bRound ) );

	return ( RegionPos * GetChunkGridSize ( ) * GetDataGridSize ( ) ) + ( ChuckPos * GetDataGridSize ( ) ) + GridPos;
}

FIntVector ULFPChunkedIndexTranslator::ToDataGridIndex ( FIntVector DataGridPosition , const bool bRound ) const
{
	auto DivideVector = [&] ( const FIntVector& A , const FIntVector& B )
	{
		return FIntVector ( A.X / B.X , A.Y / B.Y , A.Z / B.Z );
	};

	const FIntVector TotalSize ( GetRegionGridSize ( ) * GetChunkGridSize ( ) * GetDataGridSize ( ) );

	if ( bRound )
	{
		DataGridPosition.X %= TotalSize.X;
		DataGridPosition.Y %= TotalSize.Y;
		DataGridPosition.Z %= TotalSize.Z;

		if ( DataGridPosition.X < 0 )
		{
			DataGridPosition.X += TotalSize.X;
		}
		if ( DataGridPosition.Y < 0 )
		{
			DataGridPosition.Y += TotalSize.Y;
		}
		if ( DataGridPosition.Z < 0 )
		{
			DataGridPosition.Z += TotalSize.Z;
		}
	}
	else if ( ULFPGridLibrary::IsGridLocationValid ( DataGridPosition , TotalSize ) == false )
	{
		return FIntVector::NoneValue;
	}

	const FIntVector RegionPos ( DivideVector ( DataGridPosition , GetChunkGridSize ( ) * GetDataGridSize ( ) ) );
	const FIntVector ChuckPos ( DivideVector ( DataGridPosition , GetDataGridSize ( ) ) );

	return FIntVector ( ULFPGridLibrary::ToGridIndex ( RegionPos , GetRegionGridSize ( ) ) , ULFPGridLibrary::ToGridIndex ( ChuckPos , GetChunkGridSize ( ) ) , ULFPGridLibrary::ToGridIndex ( DataGridPosition , GetDataGridSize ( ) , true ) );
}
