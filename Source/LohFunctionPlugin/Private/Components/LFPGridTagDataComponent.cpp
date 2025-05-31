// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/LFPGridTagDataComponent.h"

#include "Data/LFPGridSetting.h"
#include "Math/LFPGridLibrary.h"

// Sets default values for this component's properties
ULFPGridTagDataComponent::ULFPGridTagDataComponent ( )
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void ULFPGridTagDataComponent::BeginPlay ( )
{
	if ( IsValid ( GridSetting ) )
	{
		DataIndexSize   = GridSetting->GetDataIndexSize ( );
		ChunkIndexSize  = GridSetting->GetChunkIndexSize ( );
		RegionIndexSize = GridSetting->GetRegionIndexSize ( );
	}

	Super::BeginPlay ( );
}

// Called every frame
void ULFPGridTagDataComponent::TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent ( DeltaTime , TickType , ThisTickFunction );

	// ...
}

ULFPGridSetting* ULFPGridTagDataComponent::GetGridSetting ( ) const
{
	return GridSetting;
}

FIntVector ULFPGridTagDataComponent::ToChunkGridPosition ( const FIntPoint ChunkGridIndex , const bool bRound ) const
{
	if ( IsValid ( GridSetting ) == false )
	{
		return FIntVector ( );
	}

	const FIntVector RegionPos ( ULFPGridLibrary::ToGridLocation ( ChunkGridIndex.X , GridSetting->GetRegionGridSize ( ) , bRound ) );
	const FIntVector ChuckPos ( ULFPGridLibrary::ToGridLocation ( ChunkGridIndex.Y , GridSetting->GetChunkGridSize ( ) , bRound ) );

	return ( RegionPos * GridSetting->GetChunkGridSize ( ) ) + ChuckPos;
}

FIntPoint ULFPGridTagDataComponent::ToChunkGridIndex ( FIntVector ChunkGridPosition , const bool bRound ) const
{
	auto DivideVector = [&] ( const FIntVector& A , const FIntVector& B )
	{
		return FIntVector ( A.X / B.X , A.Y / B.Y , A.Z / B.Z );
	};

	const FIntVector TotalSize ( GridSetting->GetRegionGridSize ( ) * GridSetting->GetChunkGridSize ( ) );

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

	const FIntVector RegionPos ( DivideVector ( ChunkGridPosition , GridSetting->GetChunkGridSize ( ) ) );

	return FIntPoint ( ULFPGridLibrary::ToGridIndex ( RegionPos , GridSetting->GetRegionGridSize ( ) ) , ULFPGridLibrary::ToGridIndex ( ChunkGridPosition , GridSetting->GetChunkGridSize ( ) , true ) );
}

FIntVector ULFPGridTagDataComponent::ToDataGridPosition ( const FIntVector DataGridIndex , const bool bRound ) const
{
	if ( IsValid ( GridSetting ) == false )
	{
		return FIntVector ( );
	}

	const FIntVector RegionPos ( ULFPGridLibrary::ToGridLocation ( DataGridIndex.X , GridSetting->GetRegionGridSize ( ) , bRound ) );
	const FIntVector ChuckPos ( ULFPGridLibrary::ToGridLocation ( DataGridIndex.Y , GridSetting->GetChunkGridSize ( ) , bRound ) );
	const FIntVector GridPos ( ULFPGridLibrary::ToGridLocation ( DataGridIndex.Z , GridSetting->GetDataGridSize ( ) , bRound ) );

	return ( RegionPos * GridSetting->GetChunkGridSize ( ) * GridSetting->GetDataGridSize ( ) ) + ( ChuckPos * GridSetting->GetDataGridSize ( ) ) + GridPos;
}

FIntVector ULFPGridTagDataComponent::ToDataGridIndex ( FIntVector DataGridPosition , const bool bRound ) const
{
	auto DivideVector = [&] ( const FIntVector& A , const FIntVector& B )
	{
		return FIntVector ( A.X / B.X , A.Y / B.Y , A.Z / B.Z );
	};

	const FIntVector TotalSize ( GridSetting->GetRegionGridSize ( ) * GridSetting->GetChunkGridSize ( ) * GridSetting->GetDataGridSize ( ) );

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

	const FIntVector RegionPos ( DivideVector ( DataGridPosition , GridSetting->GetChunkGridSize ( ) * GridSetting->GetDataGridSize ( ) ) );
	const FIntVector ChuckPos ( DivideVector ( DataGridPosition , GridSetting->GetDataGridSize ( ) ) );

	return FIntVector ( ULFPGridLibrary::ToGridIndex ( RegionPos , GridSetting->GetRegionGridSize ( ) ) , ULFPGridLibrary::ToGridIndex ( ChuckPos , GridSetting->GetChunkGridSize ( ) ) , ULFPGridLibrary::ToGridIndex ( DataGridPosition , GridSetting->GetDataGridSize ( ) , true ) );
}

FIntVector ULFPGridTagDataComponent::AddOffsetToGridIndex ( FIntVector GridIndex , const FIntVector Offset , const bool bRound ) const
{
	GridIndex = ToDataGridPosition ( GridIndex , bRound );
	GridIndex += Offset;
	return ToDataGridIndex ( GridIndex , bRound );
}
