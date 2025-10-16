// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LFPGridStepFlowDataComponent.h"

#include "Math/LFPGridLibrary.h"


int32 ULFPGridStepFlowDataLibrary::GetFlowPressure ( const FLFPStepFlowNeighbourCellData& Data )
{
	return Data.GetFlowPressure ( );
}

int32 ULFPGridStepFlowDataLibrary::GetTotalFlow ( const FLFPStepFlowNeighbourCellData& Data )
{
	return Data.GetTotalFlow ( );
}

int32 ULFPGridStepFlowDataLibrary::GetFlowResistant ( const FLFPStepFlowNeighbourCellData& Data , const int32 ComponentIndex )
{
	return Data.GetFlowResistantWithoutApply ( ComponentIndex );
}

int32 ULFPGridStepFlowDataLibrary::GetSelfFlowResistant ( const FLFPStepFlowNeighbourCellData& Data )
{
	return Data.CenterResistant;
}

int32 ULFPGridStepFlowDataLibrary::GetFlowDivergence ( const FLFPStepFlowNeighbourCellData& Data )
{
	return Data.GetFlowDivergence ( );
}

// Sets default values for this component's properties
ULFPGridStepFlowDataComponent::ULFPGridStepFlowDataComponent ( )
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULFPGridStepFlowDataComponent::BeginPlay ( )
{
	Super::BeginPlay ( );

	SetSize ( FIntVector (
	                      RegionGridSize.X * RegionGridSize.Y * RegionGridSize.Z ,
	                      ChunkGridSize.X * ChunkGridSize.Y * ChunkGridSize.Z ,
	                      DataGridSize.X * DataGridSize.Y * DataGridSize.Z
	                     ) );
}


// Called every frame
void ULFPGridStepFlowDataComponent::TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent ( DeltaTime , TickType , ThisTickFunction );

	// ...
}

FLFPStepFlowNeighbourCellData ULFPGridStepFlowDataComponent::GetNeighbourFlowData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedStepFlowDataComponent
		         , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return FLFPStepFlowNeighbourCellData ( );
	}

	const FIntVector            CurrentIndex = FIntVector ( RegionIndex , ChunkIndex , DataIndex );
	const FLFPStepFlowCellData& CurrentData  = GetData_Checked ( RegionIndex , ChunkIndex , DataIndex );

	FLFPStepFlowNeighbourCellData ResultData;

	ResultData.CenterResistant = CurrentData.GetFlowResistant ( );

	const FIntVector CheckPos [ ] =
	{
		FIntVector ( 1 , 0 , 0 ) ,
		FIntVector ( 0 , 1 , 0 ) ,
		FIntVector ( 0 , 0 , 1 ) ,
		FIntVector ( -1 , 0 , 0 ) ,
		FIntVector ( 0 , -1 , 0 ) ,
		FIntVector ( 0 , 0 , -1 )
	};

	// Get Self-Flow Velocity
	for ( int32 ComponentIndex = 3 ; ComponentIndex < 6 ; ++ComponentIndex )
	{
		const FIntVector CheckIndex = AddOffsetToDataGridIndex ( CurrentIndex , CheckPos [ ComponentIndex ] , false );

		if ( CheckIndex.X == INDEX_NONE )
		{
			continue;
		}

		ResultData.SetFlowVector ( ComponentIndex , CurrentData.GetFlowVectorComponent ( ComponentIndex - 3 ) );
	}

	// Get Flow Velocity
	for ( int32 ComponentIndex = 0 ; ComponentIndex < 3 ; ++ComponentIndex )
	{
		const FIntVector CheckIndex = AddOffsetToDataGridIndex ( CurrentIndex , CheckPos [ ComponentIndex ] , false );

		if ( CheckIndex.X == INDEX_NONE )
		{
			continue;
		}

		const FLFPStepFlowCellData& CheckData = GetData_Checked ( CheckIndex.X , CheckIndex.Y , CheckIndex.Z );

		ResultData.SetFlowVector ( ComponentIndex , CheckData.GetFlowVectorComponent ( ComponentIndex ) );
	}

	// Get Flow Resistant
	for ( int32 ComponentIndex = 0 ; ComponentIndex < 6 ; ++ComponentIndex )
	{
		const FIntVector CheckIndex = AddOffsetToDataGridIndex ( CurrentIndex , CheckPos [ ComponentIndex ] , false );

		if ( CheckIndex.X == INDEX_NONE )
		{
			continue;
		}

		const FLFPStepFlowCellData& CheckData = GetData_Checked ( CheckIndex.X , CheckIndex.Y , CheckIndex.Z );

		ResultData.SetFlowResistant ( ComponentIndex , CheckData.GetFlowResistant ( ) );
	}

	return ResultData;
}

FIntVector ULFPGridStepFlowDataComponent::GetPointVelocity ( const FVector& Point ) const
{
	const FIntVector DataPos       = FIntVector ( FMath::FloorToInt ( Point.X ) , FMath::FloorToInt ( Point.Y ) , FMath::FloorToInt ( Point.Z ) );
	const FIntVector DataGridIndex = ToDataGridIndex ( DataPos );

	if ( IsDataIndexValid ( DataGridIndex.X , DataGridIndex.Y , DataGridIndex.Z ) == false )
	{
		UE_LOG ( LogChunkedStepFlowDataComponent
		         , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , DataGridIndex.X , DataGridIndex.Y , DataGridIndex.Z );

		return FIntVector ( 0 );
	}

	const FVector LocalPos = Point - FVector ( DataPos );
	const int32   XOffset  = LocalPos.X >= 0.5f ? 0 : -1;
	const int32   YOffset  = LocalPos.Y >= 0.5f ? 0 : -1;
	const int32   ZOffset  = LocalPos.Z >= 0.5f ? 0 : -1;

	const auto SampleInterp = [this, &DataPos] ( const FIntVector& OffsetPos , const FVector& Alpha , const int32 ComponentIndex )
	{
		const auto SampleFlow = [this, &DataPos] ( const FIntVector& SampleOffset , int32& ChangeValue , const int32 SampleComponentIndex )
		{
			const FIntVector SamplePos           = DataPos + SampleOffset;
			const FIntVector SampleDataGridIndex = ToDataGridIndex ( SamplePos );

			if ( IsDataIndexValid ( SampleDataGridIndex.X , SampleDataGridIndex.Y , SampleDataGridIndex.Z ) )
			{
				const FLFPStepFlowCellData& SampleData = GetData_Checked ( SampleDataGridIndex.X , SampleDataGridIndex.Y , SampleDataGridIndex.Z );

				ChangeValue = SampleData.GetFlowVectorComponent ( SampleComponentIndex );
			}
			else
			{
				ChangeValue = 0.0f;
			}
		};

		TArray < int32 > ValueList;
		ValueList.Reserve ( 8 );

		TArray < int32 > InterList;
		InterList.SetNum ( 6 );

		SampleFlow ( OffsetPos + FIntVector ( 0 , 0 , 0 ) , ValueList.Add_GetRef ( 0.0f ) , ComponentIndex );
		SampleFlow ( OffsetPos + FIntVector ( 1 , 0 , 0 ) , ValueList.Add_GetRef ( 0.0f ) , ComponentIndex );
		SampleFlow ( OffsetPos + FIntVector ( 0 , 1 , 0 ) , ValueList.Add_GetRef ( 0.0f ) , ComponentIndex );
		SampleFlow ( OffsetPos + FIntVector ( 1 , 1 , 0 ) , ValueList.Add_GetRef ( 0.0f ) , ComponentIndex );

		SampleFlow ( OffsetPos + FIntVector ( 0 , 0 , 1 ) , ValueList.Add_GetRef ( 0.0f ) , ComponentIndex );
		SampleFlow ( OffsetPos + FIntVector ( 1 , 0 , 1 ) , ValueList.Add_GetRef ( 0.0f ) , ComponentIndex );
		SampleFlow ( OffsetPos + FIntVector ( 0 , 1 , 1 ) , ValueList.Add_GetRef ( 0.0f ) , ComponentIndex );
		SampleFlow ( OffsetPos + FIntVector ( 1 , 1 , 1 ) , ValueList.Add_GetRef ( 0.0f ) , ComponentIndex );

		// Interpolate On Z Value
		for ( int32 ZInterpIndex = 0 ; ZInterpIndex < 4 ; ++ZInterpIndex )
		{
			InterList [ ZInterpIndex ] =
				FMath::Lerp (
				             ValueList [ ZInterpIndex + 0 ] ,
				             ValueList [ ZInterpIndex + 4 ] ,
				             Alpha.Z
				            );
		}

		// Interpolate On Y Value
		for ( int32 YInterpIndex = 0 ; YInterpIndex < 2 ; ++YInterpIndex )
		{
			InterList [ YInterpIndex + 4 ] =
				FMath::Lerp (
				             InterList [ YInterpIndex + 0 ] ,
				             InterList [ YInterpIndex + 2 ] ,
				             Alpha.Y
				            );
		}

		// Interpolate On X Value
		return
			FMath::Lerp (
			             InterList [ 4 ] ,
			             InterList [ 5 ] ,
			             Alpha.X
			            );
	};

	// We do this because we sample the point on centers of edge
	const FVector InterpPos = LocalPos +
	                          FVector (
	                                   LocalPos.X >= 0.5f ? -0.5f : 0.5f ,
	                                   LocalPos.Y >= 0.5f ? -0.5f : 0.5f ,
	                                   LocalPos.Z >= 0.5f ? -0.5f : 0.5f
	                                  );

	return FIntVector (
	                   SampleInterp ( FIntVector ( 0 , YOffset , ZOffset ) , FVector ( LocalPos.X , InterpPos.Y , InterpPos.Z ) , 0 ) ,
	                   SampleInterp ( FIntVector ( XOffset , 0 , ZOffset ) , FVector ( InterpPos.X , LocalPos.Y , InterpPos.Z ) , 1 ) ,
	                   SampleInterp ( FIntVector ( XOffset , YOffset , 0 ) , FVector ( InterpPos.X , InterpPos.Y , LocalPos.Z ) , 2 )
	                  );
}

FLFPStepFlowCellData ULFPGridStepFlowDataComponent::CalculateVelocityOnData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex )
{
	if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedStepFlowDataComponent
		         , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return FLFPStepFlowCellData ( );
	}

	FLFPStepFlowCellData UpdateData = GetData_Checked ( RegionIndex , ChunkIndex , DataIndex );

	const FLFPStepFlowNeighbourCellData NeighbourData = GetNeighbourFlowData ( RegionIndex , ChunkIndex , DataIndex );

	const FIntVector CurrentIndex = FIntVector ( RegionIndex , ChunkIndex , DataIndex );

	const FIntVector CheckPos [ ] =
	{
		FIntVector ( -1 , 0 , 0 ) ,
		FIntVector ( 0 , -1 , 0 ) ,
		FIntVector ( 0 , 0 , -1 )
	};

	// Get Flow Velocity
	for ( int32 ComponentIndex = 0 ; ComponentIndex < 3 ; ++ComponentIndex )
	{
		const FIntVector CheckIndex = AddOffsetToDataGridIndex ( CurrentIndex , CheckPos [ ComponentIndex ] , false );

		if ( CheckIndex.X == INDEX_NONE )
		{
			UpdateData.SetFlowVectorComponent ( ComponentIndex , 0 );
			continue;
		}

		const FLFPStepFlowNeighbourCellData CheckNeighbourData = GetNeighbourFlowData ( CheckIndex.X , CheckIndex.Y , CheckIndex.Z );

		// Pos = Income
		// Neg = Outcome
		const int32 FlowChange = NeighbourData.GetFlowPressure ( ) - CheckNeighbourData.GetFlowPressure ( );

		UpdateData.AddFlowVectorComponent ( ComponentIndex , -( NeighbourData.GetFlowResistant ( ComponentIndex + 3 , FlowChange ) ) );
	}

	return UpdateData;
}

FLFPStepFlowCellData ULFPGridStepFlowDataComponent::CalculateAdventOnData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const float Step )
{
	if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedStepFlowDataComponent
		         , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return FLFPStepFlowCellData ( );
	}

	FLFPStepFlowCellData UpdateData = GetData_Checked ( RegionIndex , ChunkIndex , DataIndex );

	const FLFPStepFlowNeighbourCellData NeighbourData = GetNeighbourFlowData ( RegionIndex , ChunkIndex , DataIndex );

	const FIntVector CurrentIndex = FIntVector ( RegionIndex , ChunkIndex , DataIndex );
	const FIntVector CurrentPos   = ToDataGridPosition ( CurrentIndex );

	const FIntVector CheckPos [ ] =
	{
		FIntVector ( -1 , 0 , 0 ) ,
		FIntVector ( 0 , -1 , 0 ) ,
		FIntVector ( 0 , 0 , -1 )
	};

	const FVector FlowAdvectPos [ ] =
	{
		FVector ( 0.0f , 0.5f , 0.5f ) ,
		FVector ( 0.5f , 0.0f , 0.5f ) ,
		FVector ( 0.5f , 0.5f , 0.0f )
	};

	// Get Flow Velocity
	for ( int32 ComponentIndex = 0 ; ComponentIndex < 3 ; ++ComponentIndex )
	{
		const FIntVector CheckIndex = AddOffsetToDataGridIndex ( CurrentIndex , CheckPos [ ComponentIndex ] , false );

		if ( CheckIndex.X == INDEX_NONE )
		{
			continue;
		}

		{
			const FVector CurrentAdvectPos      = FlowAdvectPos [ ComponentIndex ] + FVector ( CurrentPos );
			FVector       CurrentAdvectVelocity = FVector ( GetPointVelocity ( CurrentAdvectPos ) );

			CurrentAdvectVelocity.Normalize ( 1.0f );

			const FVector PrevAdvectPos = CurrentAdvectPos - ( CurrentAdvectVelocity * Step );
			const int32   NextVelocity  = GetPointVelocity ( PrevAdvectPos ) [ ComponentIndex ];

			UpdateData.SetFlowVectorComponent ( ComponentIndex , NeighbourData.GetFlowResistant ( ComponentIndex + 3 , NextVelocity ) );
		}
	}

	return UpdateData;
}

void ULFPGridStepFlowDataComponent::SolveVelocityOnRegion ( const int32 RegionIndex )
{
	TArray < FLFPStepFlowCellData > NewDataList;
	NewDataList.SetNumUninitialized ( GetChunkIndexSize ( ) * GetDataIndexSize ( ) );

	ParallelFor ( GetChunkIndexSize ( ) * GetDataIndexSize ( ) , [&] ( const int32 LoopIndex )
	{
		const int32 ChunkIndex = LoopIndex / GetDataIndexSize ( );
		const int32 DataIndex  = LoopIndex % GetDataIndexSize ( );

		if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
		{
			return;
		}

		NewDataList [ LoopIndex ] = CalculateVelocityOnData ( RegionIndex , ChunkIndex , DataIndex );
	} );

	for ( int32 ListIndex = 0 ; ListIndex < NewDataList.Num ( ) ; ++ListIndex )
	{
		const int32 ChunkIndex = ListIndex / GetDataIndexSize ( );
		const int32 DataIndex  = ListIndex % GetDataIndexSize ( );

		if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
		{
			continue;
		}

		SetData ( RegionIndex , ChunkIndex , DataIndex , NewDataList [ ListIndex ] );
	}
}

void ULFPGridStepFlowDataComponent::SolveAdventOnRegion ( const int32 RegionIndex , const float Step )
{
	TArray < FLFPStepFlowCellData > NewDataList;
	NewDataList.SetNumUninitialized ( GetChunkIndexSize ( ) * GetDataIndexSize ( ) );

	ParallelFor ( GetChunkIndexSize ( ) * GetDataIndexSize ( ) , [&] ( const int32 LoopIndex )
	{
		const int32 ChunkIndex = LoopIndex / GetDataIndexSize ( );
		const int32 DataIndex  = LoopIndex % GetDataIndexSize ( );

		if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
		{
			return;
		}

		NewDataList [ LoopIndex ] = ( CalculateAdventOnData ( RegionIndex , ChunkIndex , DataIndex , Step ) );
	} );

	for ( int32 ListIndex = 0 ; ListIndex < NewDataList.Num ( ) ; ++ListIndex )
	{
		const int32 ChunkIndex = ListIndex / GetDataIndexSize ( );
		const int32 DataIndex  = ListIndex % GetDataIndexSize ( );

		if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
		{
			continue;
		}

		SetData ( RegionIndex , ChunkIndex , DataIndex , NewDataList [ ListIndex ] );
	}
}

const FIntVector& ULFPGridStepFlowDataComponent::GetDataGridSize ( ) const
{
	return DataGridSize;
}

const FIntVector& ULFPGridStepFlowDataComponent::GetChunkGridSize ( ) const
{
	return ChunkGridSize;
}

const FIntVector& ULFPGridStepFlowDataComponent::GetRegionGridSize ( ) const
{
	return RegionGridSize;
}

FIntVector ULFPGridStepFlowDataComponent::ToChunkGridPosition ( const FIntPoint ChunkGridIndex , const bool bRound ) const
{
	const FIntVector RegionPos ( ULFPGridLibrary::ToGridLocation ( ChunkGridIndex.X , GetRegionGridSize ( ) , bRound ) );
	const FIntVector ChuckPos ( ULFPGridLibrary::ToGridLocation ( ChunkGridIndex.Y , GetChunkGridSize ( ) , bRound ) );

	return ( RegionPos * GetChunkGridSize ( ) ) + ChuckPos;
}

FIntPoint ULFPGridStepFlowDataComponent::ToChunkGridIndex ( FIntVector ChunkGridPosition , const bool bRound ) const
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

FIntVector ULFPGridStepFlowDataComponent::ToDataGridPosition ( const FIntVector DataGridIndex , const bool bRound ) const
{
	const FIntVector RegionPos ( ULFPGridLibrary::ToGridLocation ( DataGridIndex.X , GetRegionGridSize ( ) , bRound ) );
	const FIntVector ChuckPos ( ULFPGridLibrary::ToGridLocation ( DataGridIndex.Y , GetChunkGridSize ( ) , bRound ) );
	const FIntVector GridPos ( ULFPGridLibrary::ToGridLocation ( DataGridIndex.Z , GetDataGridSize ( ) , bRound ) );

	return ( RegionPos * GetChunkGridSize ( ) * GetDataGridSize ( ) ) + ( ChuckPos * GetDataGridSize ( ) ) + GridPos;
}

FIntVector ULFPGridStepFlowDataComponent::ToDataGridIndex ( FIntVector DataGridPosition , const bool bRound ) const
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

FIntVector ULFPGridStepFlowDataComponent::GetDistanceToChunkGridIndex ( const FIntPoint ChunkGridIndexA , const FIntPoint ChunkGridIndexB , const bool bAbsResult ) const
{
	const FIntVector Total = ToChunkGridPosition ( ChunkGridIndexA ) - ToChunkGridPosition ( ChunkGridIndexB );

	return bAbsResult ? FIntVector ( FMath::Abs ( Total.X ) , FMath::Abs ( Total.Y ) , FMath::Abs ( Total.Z ) ) : Total;
}

FIntVector ULFPGridStepFlowDataComponent::GetDistanceToDataGridIndex ( const FIntVector DataGridIndexA , const FIntVector DataGridIndexB , const bool bAbsResult ) const
{
	const FIntVector Total = ToDataGridPosition ( DataGridIndexA ) - ToDataGridPosition ( DataGridIndexB );

	return bAbsResult ? FIntVector ( FMath::Abs ( Total.X ) , FMath::Abs ( Total.Y ) , FMath::Abs ( Total.Z ) ) : Total;
}

FIntPoint ULFPGridStepFlowDataComponent::AddOffsetToChunkGridIndex ( const FIntPoint ChunkGridIndex , const FIntVector Offset , const bool bRound ) const
{
	return ToChunkGridIndex ( ToChunkGridPosition ( ChunkGridIndex , bRound ) + Offset , bRound );
}

FIntVector ULFPGridStepFlowDataComponent::AddOffsetToDataGridIndex ( const FIntVector DataGridIndex , const FIntVector Offset , const bool bRound ) const
{
	return ToDataGridIndex ( ToDataGridPosition ( DataGridIndex , bRound ) + Offset , bRound );
}
