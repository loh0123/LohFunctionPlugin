// Copyright (c) 2025 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LFPGraphLibrary.generated.h"

USTRUCT ( BlueprintType )
struct LOHFUNCTIONPLUGIN_API FLFPGraphAreaSize
{
	GENERATED_BODY ( )

public:

	UPROPERTY ( BlueprintReadWrite , EditAnywhere , Category = "LFPGraphAreaSize" )
	FIntVector Min = FIntVector ( );

	UPROPERTY ( BlueprintReadWrite , EditAnywhere , Category = "LFPGraphAreaSize" )
	FIntVector Max = FIntVector ( );

public:

	FORCEINLINE FIntVector GetSize ( ) const
	{
		return Max - Min;
	}
};

USTRUCT ( BlueprintType )
struct LOHFUNCTIONPLUGIN_API FLFPGraphPointData
{
	GENERATED_BODY ( )

public:

	UPROPERTY ( BlueprintReadWrite , EditAnywhere , Category = "LFPGraphPointData" )
	FBox PointData = FBox ( );

	UPROPERTY ( BlueprintReadWrite , EditAnywhere , Category = "LFPGraphPointData" )
	TArray < int32 > ReferenceGraphIndexList = TArray < int32 > ( );

	UPROPERTY ( BlueprintReadWrite , EditAnywhere , Category = "LFPGraphPointData" )
	TArray < int32 > ConnectedGraphIndexList = TArray < int32 > ( );

	UPROPERTY ( BlueprintReadWrite , EditAnywhere , Category = "LFPGraphPointData" )
	TArray < int32 > ClosedGraphIndexList = TArray < int32 > ( );

public:

	FORCEINLINE void CloseAllConnection ( )
	{
		ClosedGraphIndexList = ConnectedGraphIndexList;
	}

	FORCEINLINE bool IsConnectToIndex ( const int32 Index ) const
	{
		return ConnectedGraphIndexList.Contains ( Index ) && ClosedGraphIndexList.Contains ( Index ) == false;
	}

	FORCEINLINE bool IsSingleConnect ( ) const
	{
		return ConnectedGraphIndexList.Num ( ) - ClosedGraphIndexList.Num ( ) == 1;
	}
};

USTRUCT ( BlueprintType )
struct LOHFUNCTIONPLUGIN_API FLFPGraphPointListData
{
	GENERATED_BODY ( )

public:

	UPROPERTY ( BlueprintReadWrite , EditAnywhere , Category = "LFPGraphPointListData" )
	TArray < FLFPGraphPointData > PointList = TArray < FLFPGraphPointData > ( );

	UPROPERTY ( BlueprintReadWrite , EditAnywhere , Category = "LFPGraphPointListData" )
	TArray < int32 > InvalidIndexList = TArray < int32 > ( );

public:

	FORCEINLINE void Clear ( )
	{
		PointList.Empty ( );
		InvalidIndexList.Empty ( );
	}

public:

	FORCEINLINE bool IsIndexValid ( const int32 Index ) const
	{
		return InvalidIndexList.Contains ( Index ) == false;
	}
};

USTRUCT ( BlueprintType )
struct LOHFUNCTIONPLUGIN_API FLFPGraphMazeData
{
	GENERATED_BODY ( )

public:

	UPROPERTY ( BlueprintReadWrite , EditAnywhere , Category = "LFPGraphMazeData" )
	int32 FlowFromIndex = INDEX_NONE;

	UPROPERTY ( BlueprintReadWrite , EditAnywhere , Category = "LFPGraphMazeData" )
	int32 WalkStep = 0;
};

USTRUCT ( BlueprintType )
struct LOHFUNCTIONPLUGIN_API FLFPGraphMazeListData
{
	GENERATED_BODY ( )

public:

	FLFPGraphMazeListData ( ) : GraphPoint ( ), GraphMaze ( )
	{
	}

	FLFPGraphMazeListData ( const FLFPGraphPointListData& GraphPoint ) : GraphPoint ( GraphPoint ), GraphMaze ( )
	{
		GraphMaze.SetNum ( GraphPoint.PointList.Num ( ) );
	}

public:

	UPROPERTY ( BlueprintReadWrite , EditAnywhere , Category = "LFPGraphMazeListData" )
	FLFPGraphPointListData GraphPoint = FLFPGraphPointListData ( );

	UPROPERTY ( BlueprintReadWrite , EditAnywhere , Category = "LFPGraphMazeListData" )
	TArray < FLFPGraphMazeData > GraphMaze = TArray < FLFPGraphMazeData > ( );

	UPROPERTY ( BlueprintReadWrite , EditAnywhere , Category = "LFPGraphMazeListData" )
	TArray < int32 > MazeDeadEndList = TArray < int32 > ( );
};

/**
 * 
 */
UCLASS ( )
class LOHFUNCTIONPLUGIN_API ULFPGraphLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY ( )

public: // Graph Creation

	UFUNCTION ( BlueprintCallable , Category = "LFPGraphLibrary" )
	static void CreateSeparateGraphSection (
		FLFPGraphPointListData& OutResult ,
		UPARAM ( ref )
		FRandomStream&   RandomSeed ,
		const FIntVector GridSize ,
		const int32      SeparateAmount ,
		const int32      MinSize ,
		const float      SeparateXChance ,
		const float      SeparateYChance ,
		const float      SeparateZChance
		);

	UFUNCTION ( BlueprintCallable , Category = "LFPGraphLibrary" )
	static void CreateGridGraph (
		FLFPGraphPointListData& OutResult ,
		const FIntVector        GridSize
		);

public: // Maze Generation

	UFUNCTION ( BlueprintCallable , Category = "LFPMathLibrary | Maze" )
	static FLFPGraphMazeListData GenerateMazeData (
		UPARAM ( Ref )
		FLFPGraphPointListData& GraphData ,
		const int32             RoomStartIndex ,
		const FRandomStream&    Seed
		);

	UFUNCTION ( BlueprintCallable , Category = "LFPMathLibrary | Maze" )
	static void RemoveMazeDeadEnd (
		UPARAM ( Ref )
		FLFPGraphMazeListData& MazeData ,
		const float            Percentage ,
		const FRandomStream&   Seed
		);
};
