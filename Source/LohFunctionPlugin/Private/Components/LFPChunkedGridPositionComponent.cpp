// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LFPChunkedGridPositionComponent.h"

#include "Math/LFPGridLibrary.h"


// Sets default values for this component's properties
ULFPChunkedGridPositionComponent::ULFPChunkedGridPositionComponent ( )
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULFPChunkedGridPositionComponent::BeginPlay ( )
{
	Super::BeginPlay ( );

	// ...
}


// Called every frame
void ULFPChunkedGridPositionComponent::TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent ( DeltaTime , TickType , ThisTickFunction );

	// ...
}

void ULFPChunkedGridPositionComponent::SetSize ( const FIntVector& NewRegionSize , const FIntVector& NewChunkSize , const FIntVector& NewDataSize )
{
	RegionGridSize = NewRegionSize;
	ChunkGridSize  = NewChunkSize;
	DataGridSize   = NewDataSize;
}

void ULFPChunkedGridPositionComponent::SetIsolation ( const bool bRegion , const bool bChunk )
{
	bIsolateRegion = bRegion;
	bIsolateChunk  = bChunk;
}

FIntVector ULFPChunkedGridPositionComponent::GetChunkedGridSize ( ) const
{
	return FIntVector (
	                   RegionGridSize.X * RegionGridSize.Y * RegionGridSize.Z ,
	                   ChunkGridSize.X * ChunkGridSize.Y * ChunkGridSize.Z ,
	                   DataGridSize.X * DataGridSize.Y * DataGridSize.Z
	                  );
}

const FIntVector& ULFPChunkedGridPositionComponent::GetDataGridSize ( ) const
{
	return DataGridSize;
}

const FIntVector& ULFPChunkedGridPositionComponent::GetChunkGridSize ( ) const
{
	return ChunkGridSize;
}

const FIntVector& ULFPChunkedGridPositionComponent::GetRegionGridSize ( ) const
{
	return RegionGridSize;
}

bool ULFPChunkedGridPositionComponent::IsIsolateRegion ( ) const
{
	return bIsolateRegion;
}

bool ULFPChunkedGridPositionComponent::IsIsolateChunk ( ) const
{
	return bIsolateChunk;
}

FIntVector ULFPChunkedGridPositionComponent::ToChunkGridPosition ( const FIntPoint& ChunkGridIndex ) const
{
	const FIntVector& RegionPos ( ULFPGridLibrary::ToGridLocation ( ChunkGridIndex.X , GetRegionGridSize ( ) ) );
	const FIntVector& ChuckPos ( ULFPGridLibrary::ToGridLocation ( ChunkGridIndex.Y , GetChunkGridSize ( ) ) );

	return ( RegionPos * GetChunkGridSize ( ) ) + ChuckPos;
}

FIntPoint ULFPChunkedGridPositionComponent::ToChunkGridIndex ( FIntVector ChunkGridPosition ) const
{
	auto DivideVector = [&] ( const FIntVector& A , const FIntVector& B )
	{
		return FIntVector ( A.X / B.X , A.Y / B.Y , A.Z / B.Z );
	};

	if ( ULFPGridLibrary::IsGridLocationValid ( ChunkGridPosition , GetRegionGridSize ( ) * GetChunkGridSize ( ) ) == false )
	{
		return FIntPoint::NoneValue;
	}

	const FIntVector& RegionPos ( DivideVector ( ChunkGridPosition , GetChunkGridSize ( ) ) );

	return FIntPoint ( ULFPGridLibrary::ToGridIndex ( RegionPos , GetRegionGridSize ( ) ) , ULFPGridLibrary::ToGridIndex ( ULFPGridLibrary::RoundGridLocation ( ChunkGridPosition , GetChunkGridSize ( ) ) , GetChunkGridSize ( ) ) );
}

FIntVector ULFPChunkedGridPositionComponent::ToDataGridPosition ( const FIntVector& DataGridIndex ) const
{
	const FIntVector& RegionPos ( ULFPGridLibrary::ToGridLocation ( DataGridIndex.X , GetRegionGridSize ( ) ) );
	const FIntVector& ChuckPos ( ULFPGridLibrary::ToGridLocation ( DataGridIndex.Y , GetChunkGridSize ( ) ) );
	const FIntVector& GridPos ( ULFPGridLibrary::ToGridLocation ( DataGridIndex.Z , GetDataGridSize ( ) ) );

	return ( RegionPos * GetChunkGridSize ( ) * GetDataGridSize ( ) ) + ( ChuckPos * GetDataGridSize ( ) ) + GridPos;
}

FIntVector ULFPChunkedGridPositionComponent::ToDataGridIndex ( FIntVector DataGridPosition ) const
{
	auto DivideVector = [&] ( const FIntVector& A , const FIntVector& B )
	{
		return FIntVector ( A.X / B.X , A.Y / B.Y , A.Z / B.Z );
	};

	if ( ULFPGridLibrary::IsGridLocationValid ( DataGridPosition , GetRegionGridSize ( ) * GetChunkGridSize ( ) * GetDataGridSize ( ) ) == false )
	{
		return FIntVector::NoneValue;
	}

	const FIntVector& RegionPos ( DivideVector ( DataGridPosition , GetChunkGridSize ( ) * GetDataGridSize ( ) ) );
	const FIntVector& ChuckPos ( DivideVector ( DataGridPosition , GetDataGridSize ( ) ) );

	return FIntVector ( ULFPGridLibrary::ToGridIndex ( RegionPos , GetRegionGridSize ( ) ) , ULFPGridLibrary::ToGridIndex ( ChuckPos , GetChunkGridSize ( ) ) , ULFPGridLibrary::ToGridIndex ( ULFPGridLibrary::RoundGridLocation ( DataGridPosition , GetDataGridSize ( ) ) , GetDataGridSize ( ) ) );
}

FIntVector ULFPChunkedGridPositionComponent::GetDistanceToChunkGridIndex ( const FIntPoint& ChunkGridIndexA , const FIntPoint& ChunkGridIndexB , const bool bAbsResult ) const
{
	if ( IsIsolateRegion ( ) && ChunkGridIndexA.X != ChunkGridIndexB.X )
	{
		return FIntVector::ZeroValue;
	}

	if ( IsIsolateChunk ( ) && ChunkGridIndexA.Y != ChunkGridIndexB.Y )
	{
		return FIntVector::ZeroValue;
	}

	const FIntVector& Total = ToChunkGridPosition ( ChunkGridIndexA ) - ToChunkGridPosition ( ChunkGridIndexB );

	return bAbsResult ? FIntVector ( FMath::Abs ( Total.X ) , FMath::Abs ( Total.Y ) , FMath::Abs ( Total.Z ) ) : Total;
}

FIntVector ULFPChunkedGridPositionComponent::GetDistanceToDataGridIndex ( const FIntVector& DataGridIndexA , const FIntVector& DataGridIndexB , const bool bAbsResult ) const
{
	if ( IsIsolateRegion ( ) && DataGridIndexA.X != DataGridIndexB.X )
	{
		return FIntVector::ZeroValue;
	}

	if ( IsIsolateChunk ( ) && DataGridIndexA.Y != DataGridIndexB.Y )
	{
		return FIntVector::ZeroValue;
	}

	const FIntVector& Total = ToDataGridPosition ( DataGridIndexA ) - ToDataGridPosition ( DataGridIndexB );

	return bAbsResult ? FIntVector ( FMath::Abs ( Total.X ) , FMath::Abs ( Total.Y ) , FMath::Abs ( Total.Z ) ) : Total;
}

FIntPoint ULFPChunkedGridPositionComponent::AddOffsetToChunkGridIndex ( const FIntPoint& ChunkGridIndex , const FIntVector& Offset ) const
{
	const FIntPoint& Result = ToChunkGridIndex ( ToChunkGridPosition ( ChunkGridIndex ) + Offset );

	if ( IsIsolateRegion ( ) && ChunkGridIndex.X != Result.X )
	{
		return FIntPoint::NoneValue;
	}

	if ( IsIsolateChunk ( ) && ChunkGridIndex.Y != Result.Y )
	{
		return FIntPoint::NoneValue;
	}

	return Result;
}

FIntVector ULFPChunkedGridPositionComponent::AddOffsetToDataGridIndex ( const FIntVector& DataGridIndex , const FIntVector& Offset ) const
{
	const FIntVector& Result = ToDataGridIndex ( ToDataGridPosition ( DataGridIndex ) + Offset );

	if ( IsIsolateRegion ( ) && DataGridIndex.X != Result.X )
	{
		return FIntVector::NoneValue;
	}

	if ( IsIsolateChunk ( ) && DataGridIndex.Y != Result.Y )
	{
		return FIntVector::NoneValue;
	}

	return Result;
}
