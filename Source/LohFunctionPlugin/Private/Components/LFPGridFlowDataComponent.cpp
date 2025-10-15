// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LFPGridFlowDataComponent.h"

#include "Math/LFPGridLibrary.h"


int32 ULFPGridFlowDataLibrary::GetOpenEdge ( const FLFPFlowEdgeCellData& Data )
{
	return Data.OpenEdgeCount;
}

// Sets default values for this component's properties
ULFPGridFlowDataComponent::ULFPGridFlowDataComponent ( )
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULFPGridFlowDataComponent::BeginPlay ( )
{
	Super::BeginPlay ( );

	SetSize ( FIntVector (
	                      RegionGridSize.X * RegionGridSize.Y * RegionGridSize.Z ,
	                      ChunkGridSize.X * ChunkGridSize.Y * ChunkGridSize.Z ,
	                      DataGridSize.X * DataGridSize.Y * DataGridSize.Z
	                     ) );
}


// Called every frame
void ULFPGridFlowDataComponent::TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent ( DeltaTime , TickType , ThisTickFunction );

	// ...
}

FLFPFlowEdgeCellData ULFPGridFlowDataComponent::GetEdgeFlowData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedFlowDataComponent
		         , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return FLFPFlowEdgeCellData ( );
	}

	const FIntVector        CurrentIndex = FIntVector ( RegionIndex , ChunkIndex , DataIndex );
	const FLFPFlowCellData& CurrentData  = GetData_Checked ( RegionIndex , ChunkIndex , DataIndex );

	FLFPFlowEdgeCellData ResultData;

	ResultData.CenterPressure = CurrentData.FlowPressure;

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
	for ( int32 i = 3 ; i < 6 ; ++i )
	{
		const FIntVector CheckIndex = AddOffsetToDataGridIndex ( CurrentIndex , CheckPos [ i ] , false );

		if ( CheckIndex.X == INDEX_NONE )
		{
			continue;
		}

		const FLFPFlowCellData& CheckData = GetData_Checked ( CheckIndex.X , CheckIndex.Y , CheckIndex.Z );

		if ( CheckData.IsFlowable ( ) == false )
		{
			continue;
		}

		ResultData.GetFlowVector ( i ) = CurrentData.GetFlowVectorComponent ( i - 3 );
	}

	// Get Flow Velocity
	for ( int32 i = 0 ; i < 3 ; ++i )
	{
		const FIntVector CheckIndex = AddOffsetToDataGridIndex ( CurrentIndex , CheckPos [ i ] , false );

		if ( CheckIndex.X == INDEX_NONE )
		{
			continue;
		}

		const FLFPFlowCellData& CheckData = GetData_Checked ( CheckIndex.X , CheckIndex.Y , CheckIndex.Z );

		if ( CheckData.IsFlowable ( ) == false )
		{
			continue;
		}

		ResultData.GetFlowVector ( i ) = CheckData.GetFlowVectorComponent ( i );
	}

	// Get Flow Pressure
	for ( int32 i = 0 ; i < 6 ; ++i )
	{
		const FIntVector CheckIndex = AddOffsetToDataGridIndex ( CurrentIndex , CheckPos [ i ] , false );

		if ( CheckIndex.X == INDEX_NONE )
		{
			continue;
		}

		const FLFPFlowCellData& CheckData = GetData_Checked ( CheckIndex.X , CheckIndex.Y , CheckIndex.Z );

		if ( CheckData.IsFlowable ( ) )
		{
			ResultData.GetFlowPressure ( i ) = CheckData.FlowPressure;
			ResultData.OpenEdgeCount += 1;
		}
	}

	return ResultData;
}

float ULFPGridFlowDataComponent::GetFlowPressure ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedFlowDataComponent
		         , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return 0;
	}

	return GetData_Checked ( RegionIndex , ChunkIndex , DataIndex ).FlowPressure;
}

float ULFPGridFlowDataComponent::GetFlowDivergence ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex ) const
{
	return GetEdgeFlowData ( RegionIndex , ChunkIndex , DataIndex ).GetFlowDivergence ( );
}

FVector ULFPGridFlowDataComponent::GetPointVelocity ( const FVector& Point ) const
{
	const FIntVector DataPos       = FIntVector ( FMath::FloorToInt ( Point.X ) , FMath::FloorToInt ( Point.Y ) , FMath::FloorToInt ( Point.Z ) );
	const FIntVector DataGridIndex = ToDataGridIndex ( DataPos );

	if ( IsDataIndexValid ( DataGridIndex.X , DataGridIndex.Y , DataGridIndex.Z ) == false )
	{
		UE_LOG ( LogChunkedFlowDataComponent
		         , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , DataGridIndex.X , DataGridIndex.Y , DataGridIndex.Z );

		return FVector ( 0.0f );
	}

	const FVector LocalPos = Point - FVector ( DataPos );
	const int32   XOffset  = LocalPos.X >= 0.5f ? 0 : -1;
	const int32   YOffset  = LocalPos.Y >= 0.5f ? 0 : -1;
	const int32   ZOffset  = LocalPos.Z >= 0.5f ? 0 : -1;

	const auto SampleInterp = [this, &DataPos] ( const FIntVector& OffsetPos , const FVector& Alpha , const int32 ComponentIndex )
	{
		const auto SampleFlow = [this, &DataPos] ( const FIntVector& SampleOffset , float& ChangeValue , const int32 ComponentIndex )
		{
			const FIntVector SamplePos           = DataPos + SampleOffset;
			const FIntVector SampleDataGridIndex = ToDataGridIndex ( SamplePos );

			if ( IsDataIndexValid ( SampleDataGridIndex.X , SampleDataGridIndex.Y , SampleDataGridIndex.Z ) )
			{
				const FLFPFlowCellData& SampleData = GetData_Checked ( SampleDataGridIndex.X , SampleDataGridIndex.Y , SampleDataGridIndex.Z );

				if ( SampleData.IsFlowable ( ) == false )
				{
					ChangeValue = 0.0f;

					return;
				}

				ChangeValue = SampleData.GetFlowVectorComponent ( ComponentIndex );
			}
			else
			{
				ChangeValue = 0.0f;
			}
		};

		TArray < float > ValueList;
		ValueList.Reserve ( 8 );

		TArray < float > InterList;
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

	return FVector (
	                SampleInterp ( FIntVector ( 0 , YOffset , ZOffset ) , FVector ( LocalPos.X , InterpPos.Y , InterpPos.Z ) , 0 ) ,
	                SampleInterp ( FIntVector ( XOffset , 0 , ZOffset ) , FVector ( InterpPos.X , LocalPos.Y , InterpPos.Z ) , 1 ) ,
	                SampleInterp ( FIntVector ( XOffset , YOffset , 0 ) , FVector ( InterpPos.X , InterpPos.Y , LocalPos.Z ) , 2 )
	               );
}

//void ULFPGridFlowDataComponent::SolveDivergenceOnData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex )
//{
//	if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
//	{
//		UE_LOG ( LogChunkedFlowDataComponent
//		         , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );
//
//		return;
//	}
//
//	const FLFPFlowEdgeCellData EdgeData     = GetEdgeFlowData ( RegionIndex , ChunkIndex , DataIndex );
//	const float                Divergence   = EdgeData.GetFlowDivergence ( CellSize ) / EdgeData.OpenEdgeCount;
//	const FIntVector           CurrentIndex = FIntVector ( RegionIndex , ChunkIndex , DataIndex );
//
//	//Update Self
//	{
//		FLFPFlowCellData UpdateData = GetData_Checked ( RegionIndex , ChunkIndex , DataIndex );
//
//		const FIntVector CheckPos [ ] =
//		{
//			FIntVector ( -1 , 0 , 0 ) ,
//			FIntVector ( 0 , -1 , 0 ) ,
//			FIntVector ( 0 , 0 , -1 )
//		};
//
//		// Get Flow Velocity
//		for ( int32 i = 0 ; i < 3 ; ++i )
//		{
//			const FIntVector CheckIndex = AddOffsetToDataGridIndex ( CurrentIndex , CheckPos [ i ] , false );
//
//			if ( CheckIndex.X == INDEX_NONE )
//			{
//				continue;
//			}
//
//			const FLFPFlowCellData& CheckData = GetData_Checked ( CheckIndex.X , CheckIndex.Y , CheckIndex.Z );
//
//			UpdateData.GetFlowVectorComponent ( i ) += Divergence;
//		}
//
//		SetData ( RegionIndex , ChunkIndex , DataIndex , UpdateData );
//	}
//
//	// Update Neighbor
//	{
//		const FIntVector CheckPos [ ] =
//		{
//			FIntVector ( 1 , 0 , 0 ) ,
//			FIntVector ( 0 , 1 , 0 ) ,
//			FIntVector ( 0 , 0 , 1 )
//		};
//
//		// Get Flow Velocity
//		for ( int32 i = 0 ; i < 3 ; ++i )
//		{
//			const FIntVector CheckIndex = AddOffsetToDataGridIndex ( CurrentIndex , CheckPos [ i ] , false );
//
//			if ( CheckIndex.X == INDEX_NONE )
//			{
//				continue;
//			}
//
//			FLFPFlowCellData CheckData = GetData_Checked ( CheckIndex.X , CheckIndex.Y , CheckIndex.Z );
//
//			CheckData.GetFlowVectorComponent ( i ) -= Divergence;
//
//			SetData ( RegionIndex , ChunkIndex , DataIndex , CheckData );
//		}
//	}
//}
//
FLFPFlowCellData ULFPGridFlowDataComponent::CalculatePressureOnData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const float TimeStep , const float WeightSOR )
{
	if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedFlowDataComponent
		         , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return FLFPFlowCellData ( );
	}

	FLFPFlowCellData UpdateData = GetData_Checked ( RegionIndex , ChunkIndex , DataIndex );

	if ( UpdateData.IsFlowable ( ) == false )
	{
		return UpdateData;
	}

	const FLFPFlowEdgeCellData EdgeData = GetEdgeFlowData ( RegionIndex , ChunkIndex , DataIndex );

	if ( EdgeData.OpenEdgeCount <= 0 )
	{
		return FLFPFlowCellData ( );
	}

	const float OldValue    = UpdateData.FlowPressure;
	const float NewValue    = ( EdgeData.GetTotalPressure ( ) - EdgeData.GetFlowDivergence ( ) / TimeStep ) / static_cast < float > ( EdgeData.OpenEdgeCount );
	UpdateData.FlowPressure = OldValue + ( ( NewValue - OldValue ) * WeightSOR );

	return UpdateData;
}

FLFPFlowCellData ULFPGridFlowDataComponent::CalculateVelocityOnData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const float TimeStep )
{
	if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedFlowDataComponent
		         , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return FLFPFlowCellData ( );
	}

	FLFPFlowCellData UpdateData = GetData_Checked ( RegionIndex , ChunkIndex , DataIndex );

	if ( UpdateData.IsFlowable ( ) == false )
	{
		return UpdateData;
	}

	const float FlowSpeed = TimeStep;

	const FIntVector CurrentIndex = FIntVector ( RegionIndex , ChunkIndex , DataIndex );

	const FIntVector CheckPos [ ] =
	{
		FIntVector ( -1 , 0 , 0 ) ,
		FIntVector ( 0 , -1 , 0 ) ,
		FIntVector ( 0 , 0 , -1 )
	};

	const FVector FlowAdvectPos [ ] =
	{
		FVector ( -0.5f , 0 , 0 ) ,
		FVector ( 0 , -0.5f , 0 ) ,
		FVector ( 0 , 0 , -0.5f )
	};

	// Get Flow Velocity
	for ( int32 i = 0 ; i < 3 ; ++i )
	{
		const FIntVector CheckIndex = AddOffsetToDataGridIndex ( CurrentIndex , CheckPos [ i ] , false );

		if ( CheckIndex.X == INDEX_NONE )
		{
			continue;
		}

		const FLFPFlowCellData& CheckData = GetData_Checked ( CheckIndex.X , CheckIndex.Y , CheckIndex.Z );

		if ( CheckData.IsFlowable ( ) == false )
		{
			UpdateData.GetFlowVectorComponent ( i ) = 0;
		}
		else
		{
			UpdateData.GetFlowVectorComponent ( i ) -= FlowSpeed * ( UpdateData.FlowPressure - CheckData.FlowPressure );
		}
	}

	return UpdateData;
}

FLFPFlowCellData ULFPGridFlowDataComponent::CalculateAdventOnData ( const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex , const float TimeStep )
{
	if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedFlowDataComponent
		         , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return FLFPFlowCellData ( );
	}

	FLFPFlowCellData UpdateData = GetData_Checked ( RegionIndex , ChunkIndex , DataIndex );

	if ( UpdateData.IsFlowable ( ) == false )
	{
		return UpdateData;
	}

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
	for ( int32 i = 0 ; i < 3 ; ++i )
	{
		const FIntVector CheckIndex = AddOffsetToDataGridIndex ( CurrentIndex , CheckPos [ i ] , false );

		if ( CheckIndex.X == INDEX_NONE )
		{
			continue;
		}

		const FLFPFlowCellData& CheckData = GetData_Checked ( CheckIndex.X , CheckIndex.Y , CheckIndex.Z );

		if ( CheckData.IsFlowable ( ) == false )
		{
			UpdateData.GetFlowVectorComponent ( i ) = 0;
		}
		else
		{
			const FVector& CurrentAdvectPos         = FlowAdvectPos [ i ] + FVector ( CurrentPos );
			const FVector& CurrentAdvectVelocity    = GetPointVelocity ( CurrentAdvectPos );
			const FVector& PrevAdvectPos            = CurrentAdvectPos - ( CurrentAdvectVelocity * TimeStep );
			UpdateData.GetFlowVectorComponent ( i ) = GetPointVelocity ( PrevAdvectPos ) [ i ];
		}
	}

	return UpdateData;
}

void ULFPGridFlowDataComponent::SolvePressureOnRegion ( const int32 RegionIndex , const float TimeStep , const float WeightSOR )
{
	TArray < FLFPFlowCellData > NewDataList;
	NewDataList.SetNumUninitialized ( GetChunkIndexSize ( ) * GetDataIndexSize ( ) );

	for ( int32 ListIndex = 0 ; ListIndex < NewDataList.Num ( ) ; ++ListIndex )
	{
		const int32 ChunkIndex = ListIndex / GetDataIndexSize ( );
		const int32 DataIndex  = ListIndex % GetDataIndexSize ( );

		if ( IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
		{
			continue;
		}

		NewDataList [ ListIndex ] = ( CalculatePressureOnData ( RegionIndex , ChunkIndex , DataIndex , TimeStep , WeightSOR ) );
		//SetData ( RegionIndex , ChunkIndex , DataIndex , NewDataList [ ListIndex ] );
	}

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

void ULFPGridFlowDataComponent::SolveVelocityOnRegion ( const int32 RegionIndex , const float TimeStep )
{
	TArray < FLFPFlowCellData > NewDataList;
	NewDataList.Reserve ( GetChunkIndexSize ( ) * GetDataIndexSize ( ) );

	for ( int32 ChunkIndex = 0 ; ChunkIndex < GetChunkIndexSize ( ) ; ++ChunkIndex )
	{
		for ( int32 DataIndex = 0 ; DataIndex < GetDataIndexSize ( ) ; ++DataIndex )
		{
			NewDataList.Add ( CalculateVelocityOnData ( RegionIndex , ChunkIndex , DataIndex , TimeStep ) );
		}
	}

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

void ULFPGridFlowDataComponent::SolveAdventOnRegion ( const int32 RegionIndex , const float TimeStep )
{
	TArray < FLFPFlowCellData > NewDataList;
	NewDataList.Reserve ( GetChunkIndexSize ( ) * GetDataIndexSize ( ) );

	for ( int32 ChunkIndex = 0 ; ChunkIndex < GetChunkIndexSize ( ) ; ++ChunkIndex )
	{
		for ( int32 DataIndex = 0 ; DataIndex < GetDataIndexSize ( ) ; ++DataIndex )
		{
			NewDataList.Add ( CalculateAdventOnData ( RegionIndex , ChunkIndex , DataIndex , TimeStep ) );
		}
	}

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

void ULFPGridFlowDataComponent::SolvePressureOnLoop ( const int32 RegionIndex , const float TimeStep , const int32 LoopCount , const float WeightSOR )
{
	for ( int32 LoopIndex = 0 ; LoopIndex < LoopCount ; ++LoopIndex )
	{
		SolvePressureOnRegion ( RegionIndex , TimeStep , WeightSOR );
	}
}

void ULFPGridFlowDataComponent::SolveVelocityOnLoop ( const int32 RegionIndex , const float TimeStep , const int32 LoopCount )
{
	for ( int32 LoopIndex = 0 ; LoopIndex < LoopCount ; ++LoopIndex )
	{
		SolveVelocityOnRegion ( RegionIndex , TimeStep );
	}
}


const FIntVector& ULFPGridFlowDataComponent::GetDataGridSize ( ) const
{
	return DataGridSize;
}

const FIntVector& ULFPGridFlowDataComponent::GetChunkGridSize ( ) const
{
	return ChunkGridSize;
}

const FIntVector& ULFPGridFlowDataComponent::GetRegionGridSize ( ) const
{
	return RegionGridSize;
}

FIntVector ULFPGridFlowDataComponent::ToChunkGridPosition ( const FIntPoint ChunkGridIndex , const bool bRound ) const
{
	const FIntVector RegionPos ( ULFPGridLibrary::ToGridLocation ( ChunkGridIndex.X , GetRegionGridSize ( ) , bRound ) );
	const FIntVector ChuckPos ( ULFPGridLibrary::ToGridLocation ( ChunkGridIndex.Y , GetChunkGridSize ( ) , bRound ) );

	return ( RegionPos * GetChunkGridSize ( ) ) + ChuckPos;
}

FIntPoint ULFPGridFlowDataComponent::ToChunkGridIndex ( FIntVector ChunkGridPosition , const bool bRound ) const
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

FIntVector ULFPGridFlowDataComponent::ToDataGridPosition ( const FIntVector DataGridIndex , const bool bRound ) const
{
	const FIntVector RegionPos ( ULFPGridLibrary::ToGridLocation ( DataGridIndex.X , GetRegionGridSize ( ) , bRound ) );
	const FIntVector ChuckPos ( ULFPGridLibrary::ToGridLocation ( DataGridIndex.Y , GetChunkGridSize ( ) , bRound ) );
	const FIntVector GridPos ( ULFPGridLibrary::ToGridLocation ( DataGridIndex.Z , GetDataGridSize ( ) , bRound ) );

	return ( RegionPos * GetChunkGridSize ( ) * GetDataGridSize ( ) ) + ( ChuckPos * GetDataGridSize ( ) ) + GridPos;
}

FIntVector ULFPGridFlowDataComponent::ToDataGridIndex ( FIntVector DataGridPosition , const bool bRound ) const
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

FIntVector ULFPGridFlowDataComponent::GetDistanceToChunkGridIndex ( const FIntPoint ChunkGridIndexA , const FIntPoint ChunkGridIndexB , const bool bAbsResult ) const
{
	const FIntVector Total = ToChunkGridPosition ( ChunkGridIndexA ) - ToChunkGridPosition ( ChunkGridIndexB );

	return bAbsResult ? FIntVector ( FMath::Abs ( Total.X ) , FMath::Abs ( Total.Y ) , FMath::Abs ( Total.Z ) ) : Total;
}

FIntVector ULFPGridFlowDataComponent::GetDistanceToDataGridIndex ( const FIntVector DataGridIndexA , const FIntVector DataGridIndexB , const bool bAbsResult ) const
{
	const FIntVector Total = ToDataGridPosition ( DataGridIndexA ) - ToDataGridPosition ( DataGridIndexB );

	return bAbsResult ? FIntVector ( FMath::Abs ( Total.X ) , FMath::Abs ( Total.Y ) , FMath::Abs ( Total.Z ) ) : Total;
}

FIntPoint ULFPGridFlowDataComponent::AddOffsetToChunkGridIndex ( const FIntPoint ChunkGridIndex , const FIntVector Offset , const bool bRound ) const
{
	return ToChunkGridIndex ( ToChunkGridPosition ( ChunkGridIndex , bRound ) + Offset , bRound );
}

FIntVector ULFPGridFlowDataComponent::AddOffsetToDataGridIndex ( const FIntVector DataGridIndex , const FIntVector Offset , const bool bRound ) const
{
	return ToDataGridIndex ( ToDataGridPosition ( DataGridIndex , bRound ) + Offset , bRound );
}
