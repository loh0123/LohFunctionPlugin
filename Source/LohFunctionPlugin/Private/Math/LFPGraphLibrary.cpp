// Copyright (c) 2025 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#include "Math/LFPGraphLibrary.h"

#include "Math/LFPGridLibrary.h"

void ULFPGraphLibrary::CreateSeparateGraphSection (
	FLFPGraphPointListData& OutResult ,
	FRandomStream&          RandomSeed ,
	const FIntVector        GridSize ,
	const int32             SeparateAmount ,
	const int32             MinSize ,
	const float             SeparateXChance ,
	const float             SeparateYChance ,
	const float             SeparateZChance )
{
	const float AxesChanceList [ 3 ] = { SeparateXChance , SeparateYChance , SeparateZChance };

	const int32 MinAllowedSize = FMath::Max ( MinSize , 0 );
	const int32 MinAreaSize    = MinAllowedSize + MinAllowedSize;

	TArray < FLFPGraphAreaSize > NextSeparateAreaList;
	{
		FLFPGraphAreaSize& NewArea = NextSeparateAreaList.Add_GetRef ( FLFPGraphAreaSize ( ) );
		NewArea.Min                = FIntVector ( 0 , 0 , 0 );
		NewArea.Max                = GridSize - FIntVector ( 1 );
	}

	for (
		int32 SeparateIndex = 0 ;
		SeparateIndex < SeparateAmount && NextSeparateAreaList.IsEmpty ( ) == false ;
		++SeparateIndex
	)
	{
		// Random Swap
		for ( int32 ArrayIndex = 0 ; ArrayIndex < NextSeparateAreaList.Num ( ) ; ++ArrayIndex )
		{
			NextSeparateAreaList.Swap ( ArrayIndex , RandomSeed.RandHelper ( NextSeparateAreaList.Num ( ) - 1 ) );
		}

		for ( int32 AxesIndex = 0 ; AxesIndex < 3 ; ++AxesIndex )
		{
			TArray < FLFPGraphAreaSize > CurrentSeparateAreaList = NextSeparateAreaList;
			NextSeparateAreaList.Reset ( );

			int32 SeparateCount = FMath::CeilToInt ( AxesChanceList [ AxesIndex ] * static_cast < float > ( CurrentSeparateAreaList.Num ( ) ) );

			for ( const FLFPGraphAreaSize& IterationData : CurrentSeparateAreaList )
			{
				if ( SeparateCount <= 0 )
				{
					NextSeparateAreaList.Add ( IterationData );
				}
				else
				{
					SeparateCount -= 1;

					const int32 AreaSize = IterationData.GetSize ( ) [ AxesIndex ];
					const int32 CutRange = AreaSize - MinAreaSize - 1;

					const int32 CutIndex =
						RandomSeed.RandHelper ( CutRange ) +
						MinAllowedSize + // Min area size
						1 +              // Offset to prevent 0
						IterationData.Min [ AxesIndex ];

					if ( CutIndex > 0 && CutRange > 0 )
					{
						{
							FLFPGraphAreaSize& NewArea_A = NextSeparateAreaList.Add_GetRef ( IterationData );
							NewArea_A.Max [ AxesIndex ]  = CutIndex - 1;
						}

						{
							FLFPGraphAreaSize& NewArea_B = NextSeparateAreaList.Add_GetRef ( IterationData );
							NewArea_B.Min [ AxesIndex ]  = CutIndex;
						}
					}
					else
					{
						NextSeparateAreaList.Add ( IterationData );
					}
				}
			}
		}
	}

	{
		OutResult.Clear ( );

		for ( const FLFPGraphAreaSize& AreaData : NextSeparateAreaList )
		{
			FLFPGraphPointData& CurrentPointData = OutResult.PointList.Add_GetRef ( FLFPGraphPointData ( ) );

			CurrentPointData.PointData = FBox ( FVector ( AreaData.Min ) , FVector ( AreaData.Max ) );
		}

		for ( int32 CurrentIndex = 0 ; CurrentIndex < OutResult.PointList.Num ( ) ; ++CurrentIndex )
		{
			auto& CurrentData = OutResult.PointList [ CurrentIndex ];

			for ( int32 CompareIndex = 0 ; CompareIndex < OutResult.PointList.Num ( ) ; ++CompareIndex )
			{
				if ( CurrentIndex == CompareIndex )
				{
					continue;
				}

				auto& CompareData = OutResult.PointList [ CompareIndex ];
				{
					if (
						CurrentData.PointData.Intersect ( CompareData.PointData.ExpandBy ( FVector ( 1.0 , 0.0 , 0.0 ) ) ) ||
						CurrentData.PointData.Intersect ( CompareData.PointData.ExpandBy ( FVector ( 0.0 , 1.0 , 0.0 ) ) ) ||
						CurrentData.PointData.Intersect ( CompareData.PointData.ExpandBy ( FVector ( 0.0 , 0.0 , 1.0 ) ) )
					)
					{
						CurrentData.ConnectedGraphIndexList.Add ( CompareIndex );
						CompareData.ReferenceGraphIndexList.Add ( CurrentIndex );
					}
				}
			}
		}
	}
}

void ULFPGraphLibrary::CreateGridGraph ( FLFPGraphPointListData& OutResult , const FIntVector GridSize )
{
	OutResult.Clear ( );

	const int32 TotalIndex = GridSize.X * GridSize.Y * GridSize.Z;
	const int32 JumpZ      = GridSize.X * GridSize.Y;

	for ( int32 ArrayIndex = 0 ; ArrayIndex < TotalIndex ; ++ArrayIndex )
	{
		FLFPGraphPointData& CurrentPointData = OutResult.PointList.Add_GetRef ( FLFPGraphPointData ( ) );

		const FIntVector Location = ULFPGridLibrary::ToGridLocation ( ArrayIndex , GridSize );

		CurrentPointData.PointData = FBox ( FVector ( Location ) , FVector ( Location ) );
	}

	for ( int32 ArrayIndex = 0 ; ArrayIndex < TotalIndex ; ++ArrayIndex )
	{
		auto& CurrentData = OutResult.PointList [ ArrayIndex ];

		const FIntVector Location = ULFPGridLibrary::ToGridLocation ( ArrayIndex , GridSize );

		if ( Location.X - 1 >= 0 )
		{
			CurrentData.ConnectedGraphIndexList.Add ( ArrayIndex - 1 );
			OutResult.PointList [ ArrayIndex - 1 ].ReferenceGraphIndexList.Add ( ArrayIndex );
		}
		if ( Location.Y - 1 >= 0 )
		{
			CurrentData.ConnectedGraphIndexList.Add ( ArrayIndex - GridSize.X );
			OutResult.PointList [ ArrayIndex - GridSize.X ].ReferenceGraphIndexList.Add ( ArrayIndex );
		}
		if ( Location.Z - 1 >= 0 )
		{
			CurrentData.ConnectedGraphIndexList.Add ( ArrayIndex - JumpZ );
			OutResult.PointList [ ArrayIndex - JumpZ ].ReferenceGraphIndexList.Add ( ArrayIndex );
		}
		if ( Location.X + 1 < GridSize.X )
		{
			CurrentData.ConnectedGraphIndexList.Add ( ArrayIndex + 1 );
			OutResult.PointList [ ArrayIndex + 1 ].ReferenceGraphIndexList.Add ( ArrayIndex );
		}
		if ( Location.Y + 1 < GridSize.Y )
		{
			CurrentData.ConnectedGraphIndexList.Add ( ArrayIndex + GridSize.X );
			OutResult.PointList [ ArrayIndex + GridSize.X ].ReferenceGraphIndexList.Add ( ArrayIndex );
		}
		if ( Location.Z + 1 < GridSize.Z )
		{
			CurrentData.ConnectedGraphIndexList.Add ( ArrayIndex + JumpZ );
			OutResult.PointList [ ArrayIndex + JumpZ ].ReferenceGraphIndexList.Add ( ArrayIndex );
		}
	}
}

FLFPGraphMazeListData ULFPGraphLibrary::GenerateMazeData ( FLFPGraphPointListData& GraphData , const int32 RoomStartIndex , const FRandomStream& Seed )
{
	FLFPGraphMazeListData ResultData = GraphData;

	auto& GraphMazeData  = ResultData.GraphMaze;
	auto& GraphPointData = ResultData.GraphPoint;

	TSet < int32 > NextVisitList = { RoomStartIndex };

	// Setup Unvisited List For Visit Check
	TSet < int32 > UnVisit;
	{
		for ( int32 ArrayIndex = 0 ; ArrayIndex < GraphPointData.PointList.Num ( ) ; ++ArrayIndex )
		{
			if ( GraphPointData.IsIndexValid ( ArrayIndex ) )
			{
				UnVisit.Add ( ArrayIndex );

				GraphPointData.PointList [ ArrayIndex ].CloseAllConnection ( );
			}
		}
	}

	// Select Index For VisitList If Available
	int32 CurrentIndex = RoomStartIndex;

	while ( UnVisit.Num ( ) != 0 )
	{
		// Get First Item In List
		if ( CurrentIndex == -1 )
		{
			CurrentIndex = *UnVisit.begin ( );
		}

		//Mark As Visit
		UnVisit.Remove ( CurrentIndex );
		NextVisitList.Remove ( CurrentIndex );

		// Connect To Parent If Valid
		if ( GraphMazeData [ CurrentIndex ].FlowFromIndex != INDEX_NONE )
		{
			GraphPointData.PointList [ CurrentIndex ].ClosedGraphIndexList.RemoveSingleSwap ( GraphMazeData [ CurrentIndex ].FlowFromIndex );
			GraphPointData.PointList [ GraphMazeData [ CurrentIndex ].FlowFromIndex ].ClosedGraphIndexList.RemoveSingleSwap ( CurrentIndex );
		}

		// Fill Open List
		TArray < int32 > OpenIndex = GraphPointData.PointList [ CurrentIndex ].ConnectedGraphIndexList;

		// Swap Array
		for ( int32 i = 0 ; i < OpenIndex.Num ( ) ; i++ )
		{
			OpenIndex.Swap ( i , Seed.RandHelper ( OpenIndex.Num ( ) - 1 ) );
		}

		// Add To Next Visit
		for ( const int32 Item : OpenIndex )
		{
			if ( UnVisit.Contains ( Item ) )
			{
				NextVisitList.Add ( Item );
				GraphMazeData [ Item ].FlowFromIndex = CurrentIndex;
				GraphMazeData [ Item ].WalkStep      = GraphMazeData [ CurrentIndex ].WalkStep + 1;
			}
		}

		// Next Index
		CurrentIndex = NextVisitList.IsEmpty ( ) == false
		               ? *NextVisitList.begin ( )
		               : INDEX_NONE;
	}

	for ( int32 ArrayIndex = 0 ; ArrayIndex < GraphPointData.PointList.Num ( ) ; ++ArrayIndex )
	{
		if ( GraphPointData.PointList [ ArrayIndex ].IsSingleConnect ( ) && GraphPointData.PointList [ ArrayIndex ].ConnectedGraphIndexList.Num ( ) > 1 )
		{
			ResultData.MazeDeadEndList.Add ( ArrayIndex );
		}
	}

	return ResultData;
}

void ULFPGraphLibrary::RemoveMazeDeadEnd ( FLFPGraphMazeListData& MazeData , const float Percentage , const FRandomStream& Seed )
{
	const int32 Amount = FMath::CeilToInt ( static_cast < float > ( MazeData.MazeDeadEndList.Num ( ) ) * Percentage );

	if ( Amount <= 0 )
	{
		return;
	}

	for ( int32 Count = 0 ; Count < Amount && MazeData.MazeDeadEndList.IsEmpty ( ) == false ; Count++ )
	{
		const int32 CurrentIndex = MazeData.MazeDeadEndList.Pop ( );
		auto&       PointList    = MazeData.GraphPoint.PointList;
		const int32 ChooseIndex  = PointList [ CurrentIndex ].ClosedGraphIndexList.IsEmpty ( ) ? INDEX_NONE : Seed.RandHelper ( PointList [ CurrentIndex ].ClosedGraphIndexList.Num ( ) - 1 );

		if ( ChooseIndex == INDEX_NONE )
		{
			continue;
		}

		const int32 CloseIndex = PointList [ CurrentIndex ].ClosedGraphIndexList [ ChooseIndex ];

		PointList [ CurrentIndex ].ClosedGraphIndexList.RemoveAtSwap ( ChooseIndex );
		PointList [ CloseIndex ].ClosedGraphIndexList.RemoveSingleSwap ( CurrentIndex );
	}
}
