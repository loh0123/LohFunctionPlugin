// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/LFPStepFlowLibrary.h"

#include "Components/LFPChunkedGridPositionComponent.h"
#include "Components/LFPChunkedStepFlowDataComponent.h"
#include "Object/LFPStepFlowModifier.h"

int32 ULFPStepFlowLibrary::GetFlowPressure ( const FLFPStepFlowNeighbourCellData& Data )
{
	return Data.GetFlowPressure ( );
}

int32 ULFPStepFlowLibrary::GetTotalFlow ( const FLFPStepFlowNeighbourCellData& Data )
{
	return Data.GetTotalFlow ( );
}

int32 ULFPStepFlowLibrary::GetFlowResistant ( const FLFPStepFlowNeighbourCellData& Data , const int32 ComponentIndex )
{
	return Data.GetFlowResistantWithoutApply ( ComponentIndex );
}

int32 ULFPStepFlowLibrary::GetSelfFlowResistant ( const FLFPStepFlowNeighbourCellData& Data )
{
	return Data.CenterResistant;
}

int32 ULFPStepFlowLibrary::GetFlowDivergence ( const FLFPStepFlowNeighbourCellData& Data )
{
	return Data.GetFlowDivergence ( );
}

FLFPStepFlowNeighbourCellData ULFPStepFlowLibrary::GetNeighbourFlowData ( const ULFPChunkedStepFlowDataComponent* DataComponent , const ULFPChunkedGridPositionComponent* PositionComponent , const ULFPStepFlowModifier* Modifier , const int32 RegionIndex , const int32 ChunkIndex , const int32 DataIndex )
{
	if ( IsValid ( DataComponent ) == false || IsValid ( PositionComponent ) == false )
	{
		return FLFPStepFlowNeighbourCellData ( );
	}

	if ( DataComponent->IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedStepFlowDataComponent
		         , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return FLFPStepFlowNeighbourCellData ( );
	}

	const FIntVector            CurrentIndex = FIntVector ( RegionIndex , ChunkIndex , DataIndex );
	const FIntVector            CurrentPos   = PositionComponent->ToDataGridPosition ( CurrentIndex );
	const FLFPStepFlowCellData& CurrentData  = DataComponent->GetData_Checked ( RegionIndex , ChunkIndex , DataIndex );

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

	const auto GetFlowModifier = [&] ( const FIntVector Pos , const int32 ComponentIndex )
	{
		if ( IsValid ( Modifier ) == false )
		{
			return 0;
		}

		return Modifier->GetFlowOffset ( Pos , ComponentIndex );
	};

	const auto GetResistantModifier = [&] ( const FIntVector Pos )
	{
		if ( IsValid ( Modifier ) == false )
		{
			return 0;
		}

		return Modifier->GetResistantOffset ( Pos );
	};

	// Get Self-Flow Velocity
	for ( int32 ComponentIndex = 3 ; ComponentIndex < 6 ; ++ComponentIndex )
	{
		const FIntVector CheckIndex = PositionComponent->AddOffsetToDataGridIndex ( CurrentIndex , CheckPos [ ComponentIndex ] );

		if ( DataComponent->IsDataIndexValid ( CheckIndex.X , CheckIndex.Y , CheckIndex.Z ) == false )
		{
			ResultData.SetFlowVector ( ComponentIndex , 0 );
			continue;
		}

		ResultData.SetFlowVector ( ComponentIndex , CurrentData.GetFlowVectorComponent ( ComponentIndex - 3 ) + GetFlowModifier ( CurrentPos , ComponentIndex - 3 ) );
	}

	// Get Flow Velocity
	for ( int32 ComponentIndex = 0 ; ComponentIndex < 3 ; ++ComponentIndex )
	{
		const FIntVector CheckIndex = PositionComponent->AddOffsetToDataGridIndex ( CurrentIndex , CheckPos [ ComponentIndex ] );

		if ( DataComponent->IsDataIndexValid ( CheckIndex.X , CheckIndex.Y , CheckIndex.Z ) == false )
		{
			ResultData.SetFlowVector ( ComponentIndex , 0 );
			continue;
		}

		const FLFPStepFlowCellData& CheckData = DataComponent->GetData_Checked ( CheckIndex.X , CheckIndex.Y , CheckIndex.Z );

		ResultData.SetFlowVector ( ComponentIndex , CheckData.GetFlowVectorComponent ( ComponentIndex ) + GetFlowModifier ( CheckIndex , ComponentIndex ) );
	}

	// Get Flow Resistant
	for ( int32 ComponentIndex = 0 ; ComponentIndex < 6 ; ++ComponentIndex )
	{
		const FIntVector CheckIndex = PositionComponent->AddOffsetToDataGridIndex ( CurrentIndex , CheckPos [ ComponentIndex ] );

		if ( DataComponent->IsDataIndexValid ( CheckIndex.X , CheckIndex.Y , CheckIndex.Z ) == false )
		{
			ResultData.SetFlowResistant ( ComponentIndex , INT16_MAX ); // Max Resistant On Edge

			continue;
		}

		const FLFPStepFlowCellData& CheckData = DataComponent->GetData_Checked ( CheckIndex.X , CheckIndex.Y , CheckIndex.Z );

		const int32 OffsetModifier = ComponentIndex >= 3 ? GetResistantModifier ( CurrentPos ) : GetResistantModifier ( CheckIndex );

		ResultData.EdgeCount++;
		ResultData.SetFlowResistant ( ComponentIndex , CheckData.GetFlowResistant ( ) + OffsetModifier );
	}

	return ResultData;
}

FIntVector ULFPStepFlowLibrary::GetPointVelocity (
	const ULFPChunkedStepFlowDataComponent* DataComponent ,
	const ULFPChunkedGridPositionComponent* PositionComponent ,
	const ULFPStepFlowModifier*             Modifier ,
	const FVector&                          Point
	)
{
	if ( IsValid ( DataComponent ) == false || IsValid ( PositionComponent ) == false )
	{
		return FIntVector ( 0 );
	}

	const FIntVector DataPos       = FIntVector ( FMath::FloorToInt ( Point.X ) , FMath::FloorToInt ( Point.Y ) , FMath::FloorToInt ( Point.Z ) );
	const FIntVector DataGridIndex = PositionComponent->ToDataGridIndex ( DataPos );

	if ( DataComponent->IsDataIndexValid ( DataGridIndex.X , DataGridIndex.Y , DataGridIndex.Z ) == false )
	{
		UE_LOG ( LogChunkedStepFlowDataComponent
		         , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , DataGridIndex.X , DataGridIndex.Y , DataGridIndex.Z );

		return FIntVector ( 0 );
	}

	const FVector LocalPos = Point - FVector ( DataPos );
	const int32   XOffset  = LocalPos.X >= 0.5f ? 0 : -1;
	const int32   YOffset  = LocalPos.Y >= 0.5f ? 0 : -1;
	const int32   ZOffset  = LocalPos.Z >= 0.5f ? 0 : -1;

	const auto SampleInterp = [&DataPos,&PositionComponent, &DataComponent, &Modifier] ( const FIntVector& OffsetPos , const FVector& Alpha , const int32 ComponentIndex )
	{
		const auto SampleFlow = [&DataPos, &PositionComponent, &DataComponent, &Modifier] ( const FIntVector& SampleOffset , int32& ChangeValue , const int32 SampleComponentIndex )
		{
			const auto GetFlowModifier = [&] ( const FIntVector Pos , const int32 ComponentIndex )
			{
				if ( IsValid ( Modifier ) == false )
				{
					return 0;
				}

				return Modifier->GetFlowOffset ( Pos , ComponentIndex );
			};

			const FIntVector SamplePos           = DataPos + SampleOffset;
			const FIntVector SampleDataGridIndex = PositionComponent->ToDataGridIndex ( SamplePos );

			if ( DataComponent->IsDataIndexValid ( SampleDataGridIndex.X , SampleDataGridIndex.Y , SampleDataGridIndex.Z ) )
			{
				const FLFPStepFlowCellData& SampleData = DataComponent->GetData_Checked ( SampleDataGridIndex.X , SampleDataGridIndex.Y , SampleDataGridIndex.Z );

				const int32 OffsetModifier = GetFlowModifier ( SamplePos , SampleComponentIndex );

				ChangeValue = SampleData.GetFlowVectorComponent ( SampleComponentIndex + OffsetModifier );
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

FLFPStepFlowCellData ULFPStepFlowLibrary::CalculateVelocityOnData (
	const ULFPChunkedStepFlowDataComponent* DataComponent ,
	const ULFPChunkedGridPositionComponent* PositionComponent ,
	const ULFPStepFlowModifier*             Modifier ,
	const int32                             RegionIndex ,
	const int32                             ChunkIndex ,
	const int32                             DataIndex )
{
	if ( IsValid ( DataComponent ) == false || IsValid ( PositionComponent ) == false )
	{
		return FLFPStepFlowCellData ( );
	}

	if ( DataComponent->IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedStepFlowDataComponent
		         , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return FLFPStepFlowCellData ( );
	}

	FLFPStepFlowCellData UpdateData = DataComponent->GetData_Checked ( RegionIndex , ChunkIndex , DataIndex );

	const FLFPStepFlowNeighbourCellData NeighbourData = GetNeighbourFlowData ( DataComponent , PositionComponent , Modifier , RegionIndex , ChunkIndex , DataIndex );

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
		const FIntVector CheckIndex = PositionComponent->AddOffsetToDataGridIndex ( CurrentIndex , CheckPos [ ComponentIndex ] );

		if ( DataComponent->IsDataIndexValid ( CheckIndex.X , CheckIndex.Y , CheckIndex.Z ) == false )
		{
			UpdateData.SetFlowVectorComponent ( ComponentIndex , 0 );
			continue;
		}

		const FLFPStepFlowNeighbourCellData CheckNeighbourData = GetNeighbourFlowData ( DataComponent , PositionComponent , Modifier , CheckIndex.X , CheckIndex.Y , CheckIndex.Z );

		// Pos = Income
		// Neg = Outcome
		const int32 FlowChange = NeighbourData.GetFlowPressure ( ) - CheckNeighbourData.GetFlowPressure ( );

		UpdateData.AddFlowVectorComponent ( ComponentIndex , -( NeighbourData.GetFlowResistant ( ComponentIndex + 3 , FlowChange ) ) );
	}

	return UpdateData;
}

FLFPStepFlowCellData ULFPStepFlowLibrary::CalculateAdventOnData (
	const ULFPChunkedStepFlowDataComponent* DataComponent ,
	const ULFPChunkedGridPositionComponent* PositionComponent ,
	const ULFPStepFlowModifier*             Modifier ,
	const int32                             RegionIndex ,
	const int32                             ChunkIndex ,
	const int32                             DataIndex ,
	const float                             Step )
{
	if ( IsValid ( DataComponent ) == false || IsValid ( PositionComponent ) == false )
	{
		return FLFPStepFlowCellData ( );
	}

	if ( DataComponent->IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
	{
		UE_LOG ( LogChunkedStepFlowDataComponent
		         , Verbose , TEXT("%hs : Invalid Index ( R : %i , C : %i , D : %i )") , __FUNCTION__ , RegionIndex , ChunkIndex , DataIndex );

		return FLFPStepFlowCellData ( );
	}

	FLFPStepFlowCellData UpdateData = DataComponent->GetData_Checked ( RegionIndex , ChunkIndex , DataIndex );

	const FLFPStepFlowNeighbourCellData NeighbourData = GetNeighbourFlowData ( DataComponent , PositionComponent , Modifier , RegionIndex , ChunkIndex , DataIndex );

	const FIntVector CurrentIndex = FIntVector ( RegionIndex , ChunkIndex , DataIndex );
	const FIntVector CurrentPos   = PositionComponent->ToDataGridPosition ( CurrentIndex );

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
		const FIntVector CheckIndex = PositionComponent->AddOffsetToDataGridIndex ( CurrentIndex , CheckPos [ ComponentIndex ] );

		if ( DataComponent->IsDataIndexValid ( CheckIndex.X , CheckIndex.Y , CheckIndex.Z ) == false )
		{
			continue;
		}

		{
			const FVector CurrentAdvectPos      = FlowAdvectPos [ ComponentIndex ] + FVector ( CurrentPos );
			const FVector CurrentAdvectVelocity = FVector ( GetPointVelocity ( DataComponent , PositionComponent , Modifier , CurrentAdvectPos ) );

			float   VelLenght;
			FVector VelNor;
			CurrentAdvectVelocity.ToDirectionAndLength ( VelNor , VelLenght );

			constexpr float CellSize = INT8_MAX; // How far to travel one cell

			VelNor    *= Step;
			VelLenght /= CellSize;
			VelLenght = FMath::Clamp ( VelLenght , -1 , 1 );

			const FVector PrevAdvectPos = CurrentAdvectPos - VelNor * VelLenght;
			const int32   NextVelocity  = GetPointVelocity ( DataComponent , PositionComponent , Modifier , PrevAdvectPos ) [ ComponentIndex ];

			UpdateData.SetFlowVectorComponent ( ComponentIndex , NeighbourData.GetFlowResistant ( ComponentIndex + 3 , NextVelocity ) );
		}
	}

	return UpdateData;
}

void ULFPStepFlowLibrary::SolveVelocityOnRegion (
	ULFPChunkedStepFlowDataComponent*       DataComponent ,
	const ULFPChunkedGridPositionComponent* PositionComponent ,
	const ULFPStepFlowModifier*             Modifier ,
	const int32                             RegionIndex )
{
	if ( IsValid ( DataComponent ) == false || IsValid ( PositionComponent ) == false )
	{
		return;
	}

	const auto ChunkIndexSize = DataComponent->GetChunkIndexSize ( );
	const auto DataIndexSize  = DataComponent->GetDataIndexSize ( );

	TArray < FLFPStepFlowCellData > NewDataList;
	NewDataList.SetNumUninitialized ( ChunkIndexSize * DataIndexSize );

	ParallelFor ( NewDataList.Num ( ) , [&] ( const int32 LoopIndex )
	{
		const int32 ChunkIndex = LoopIndex / DataIndexSize;
		const int32 DataIndex  = LoopIndex % DataIndexSize;

		if ( DataComponent->IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
		{
			return;
		}

		NewDataList [ LoopIndex ] = CalculateVelocityOnData ( DataComponent , PositionComponent , Modifier , RegionIndex , ChunkIndex , DataIndex );
	} );

	for ( int32 ListIndex = 0 ; ListIndex < NewDataList.Num ( ) ; ++ListIndex )
	{
		const int32 ChunkIndex = ListIndex / DataIndexSize;
		const int32 DataIndex  = ListIndex % DataIndexSize;

		if ( DataComponent->IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
		{
			continue;
		}

		DataComponent->SetData ( RegionIndex , ChunkIndex , DataIndex , NewDataList [ ListIndex ] );
	}
}

void ULFPStepFlowLibrary::SolveAdventOnRegion (
	ULFPChunkedStepFlowDataComponent*       DataComponent ,
	const ULFPChunkedGridPositionComponent* PositionComponent ,
	const ULFPStepFlowModifier*             Modifier ,
	const int32                             RegionIndex ,
	const float                             Step )
{
	if ( IsValid ( DataComponent ) == false || IsValid ( PositionComponent ) == false )
	{
		return;
	}

	const auto ChunkIndexSize = DataComponent->GetChunkIndexSize ( );
	const auto DataIndexSize  = DataComponent->GetDataIndexSize ( );

	TArray < FLFPStepFlowCellData > NewDataList;
	NewDataList.SetNumUninitialized ( ChunkIndexSize * DataIndexSize );

	ParallelFor ( NewDataList.Num ( ) , [&] ( const int32 LoopIndex )
	{
		const int32 ChunkIndex = LoopIndex / DataIndexSize;
		const int32 DataIndex  = LoopIndex % DataIndexSize;

		if ( DataComponent->IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
		{
			return;
		}

		NewDataList [ LoopIndex ] = ( CalculateAdventOnData ( DataComponent , PositionComponent , Modifier , RegionIndex , ChunkIndex , DataIndex , Step ) );
	} );

	for ( int32 ListIndex = 0 ; ListIndex < NewDataList.Num ( ) ; ++ListIndex )
	{
		const int32 ChunkIndex = ListIndex / DataIndexSize;
		const int32 DataIndex  = ListIndex % DataIndexSize;

		if ( DataComponent->IsDataIndexValid ( RegionIndex , ChunkIndex , DataIndex ) == false )
		{
			continue;
		}

		DataComponent->SetData ( RegionIndex , ChunkIndex , DataIndex , NewDataList [ ListIndex ] );
	}
}

void ULFPStepFlowLibrary::SolveVelocity (
	ULFPChunkedStepFlowDataComponent*       DataComponent ,
	const ULFPChunkedGridPositionComponent* PositionComponent ,
	const ULFPStepFlowModifier*             Modifier
	)
{
	if ( IsValid ( DataComponent ) == false || IsValid ( PositionComponent ) == false )
	{
		return;
	}

	for ( int32 RegionIndex = 0 ; RegionIndex < DataComponent->GetRegionIndexSize ( ) ; ++RegionIndex )
	{
		SolveVelocityOnRegion ( DataComponent , PositionComponent , Modifier , RegionIndex );
	}
}

void ULFPStepFlowLibrary::SolveAdvent (
	ULFPChunkedStepFlowDataComponent*       DataComponent ,
	const ULFPChunkedGridPositionComponent* PositionComponent ,
	const ULFPStepFlowModifier*             Modifier ,
	const float                             Step )
{
	if ( IsValid ( DataComponent ) == false || IsValid ( PositionComponent ) == false )
	{
		return;
	}

	for ( int32 RegionIndex = 0 ; RegionIndex < DataComponent->GetRegionIndexSize ( ) ; ++RegionIndex )
	{
		SolveAdventOnRegion ( DataComponent , PositionComponent , Modifier , RegionIndex , Step );
	}
}
