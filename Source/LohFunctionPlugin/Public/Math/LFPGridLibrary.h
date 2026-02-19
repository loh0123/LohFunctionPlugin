// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LFPGridLibrary.generated.h"

/**
 * 
 */
UCLASS ( meta = (BlueprintThreadSafe) )
class LOHFUNCTIONPLUGIN_API ULFPGridLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY ( )

public:

	UFUNCTION ( BlueprintPure , Category = "LFPGridSystem" )
	static FORCEINLINE bool IsGridLocationValid ( const FIntVector& Location , const FIntVector& GridSize )
	{
		return ( Location.GetMin ( ) >= 0 && Location.X < GridSize.X && Location.Y < GridSize.Y && Location.Z < GridSize.Z );
	}

	UFUNCTION ( BlueprintPure , Category = "LFPGridSystem" )
	static FORCEINLINE bool IsOnGridEdge ( const FIntVector& Location , const FIntVector& GridSize )
	{
		return Location.GetMin ( ) == 0 || Location.X == GridSize.X - 1 || Location.Y == GridSize.Y - 1 || Location.Z == GridSize.Z - 1;
	}

public:

	UFUNCTION ( BlueprintPure , Category = "LFPGridLibrary" )
	static FORCEINLINE int32 ToGridIndex ( const FIntVector& Location , const FIntVector& GridSize )
	{
		if ( IsGridLocationValid ( Location , GridSize ) == false )
		{
			return INDEX_NONE;
		}

		return Location.X + ( Location.Y * GridSize.X ) + ( Location.Z * ( GridSize.X * GridSize.Y ) );
	}

	UFUNCTION ( BlueprintPure , Category = "LFPGridLibrary" )
	static FORCEINLINE FIntVector ToGridLocation ( const int32 Index , const FIntVector& GridSize )
	{
		if ( Index < 0 || Index >= GridSize.X * GridSize.Y * GridSize.Z )
		{
			return FIntVector::NoneValue;
		}

		const int32 ZValue = Index / ( GridSize.X * GridSize.Y );

		return FIntVector ( Index % GridSize.X , ( Index / GridSize.X ) - ( ZValue * GridSize.Y ) , ZValue );
	}

public:

	UFUNCTION ( BlueprintPure , Category = "LFPGridSystem" )
	static TArray < FIntVector > GetGridEdgeDirection ( const FIntVector& Location , const FIntVector& GridSize );

	UFUNCTION ( BlueprintCallable , Category = "LFPGridLibrary" )
	static TArray < int32 > ToGridIndexList ( const TArray < FIntVector >& GridLocations , const FIntVector Offset , const FIntVector& GridSize );

	UFUNCTION ( BlueprintCallable , Category = "LFPGridLibrary" )
	static TArray < FIntVector > ToGridLocationList ( const TArray < int32 >& Indexs , const int32 Offset , const FIntVector& GridSize );

	UFUNCTION ( BlueprintCallable , Category = "LFPGridLibrary" )
	static TArray < int32 > SectionGridIndex ( const FIntVector SectionSize , const TSet < int32 >& IgnoreIndexs , const FIntVector& GridSize );

	UFUNCTION ( BlueprintCallable , Category = "LFPGridLibrary" )
	static TArray < int32 > RandomSectionGridIndex ( const int32 Amount , const FIntVector SectionSize , const TSet < int32 >& IgnoreIndexs , const FRandomStream& Seed , const FIntVector& GridSize );

	UFUNCTION ( BlueprintCallable , Category = "LFPGridLibrary" )
	static TArray < int32 > GetGridAreaIndex ( const int32 Index , const FIntVector Offset , const FIntVector AreaSize , const FIntVector& GridSize );

public:

	UFUNCTION ( BlueprintPure , Category = "LFPGridLibrary" )
	static FORCEINLINE int32 RoundGridIndex ( int32 Index , const FIntVector& GridSize )
	{
		const int32 TotalSize = ( GridSize.X * GridSize.Y * GridSize.Z );

		Index %= TotalSize;
		Index += Index < 0 ? TotalSize : 0;

		return Index;
	}

	UFUNCTION ( BlueprintPure , Category = "LFPGridLibrary" )
	static FORCEINLINE FIntVector RoundGridLocation ( FIntVector Location , const FIntVector& GridSize )
	{
		Location.X %= GridSize.X;
		Location.Y %= GridSize.Y;
		Location.Z %= GridSize.Z;

		Location.X += Location.X < 0 ? GridSize.X : 0;
		Location.Y += Location.Y < 0 ? GridSize.Y : 0;
		Location.Z += Location.Z < 0 ? GridSize.Z : 0;

		return Location;
	}
};
