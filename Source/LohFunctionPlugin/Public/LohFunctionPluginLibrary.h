// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "LohFunctionPluginLibrary.generated.h"

USTRUCT ( BlueprintType )
struct LOHFUNCTIONPLUGIN_API FLFPIntPointList
{
	GENERATED_BODY ( )

protected:

	UPROPERTY ( VisibleAnywhere , SaveGame )
	TArray <FIntPoint> PointList = TArray <FIntPoint> ( );

public:

	FORCEINLINE bool ContainIndex ( const int32 Index ) const
	{
		for ( const FIntPoint Point : PointList )
		{
			if ( Point.X <= Index && Point.Y >= Index )
			{
				return true;
			}
		}

		return false;
	}

	FORCEINLINE FIntPoint GetOverlapIndex ( const FIntPoint Point ) const
	{
		FIntPoint Result ( INDEX_NONE );

		for ( int32 Index = 0 ; Index < PointList.Num ( ) ; Index++ )
		{
			if ( PointList[ Index ].Y < Point.X )
			{
				continue;
			}

			if ( PointList[ Index ].X > Point.Y )
			{
				/* Search Too Far */

				Result.Y = Index;

				break;
			}

			Result.X = Index;

			break;
		}

		if ( Result.X == INDEX_NONE )
		{
			return Result;
		}

		for ( int32 Index = PointList.Num ( ) - 1 ; Index >= Result.X ; Index-- )
		{
			if ( PointList[ Index ].X > Point.Y )
			{
				continue;
			}

			Result.Y = Index;

			break;
		}

		return Result;
	}

	FORCEINLINE void Merge ( const int32 Index , const FIntPoint Point )
	{
		check ( PointList.IsValidIndex( Index ) );

		if ( PointList[ Index ].X > Point.X )
		{
			PointList[ Index ].X = Point.X;
		}
		if ( PointList[ Index ].Y < Point.Y )
		{
			PointList[ Index ].Y = Point.Y;
		}
	}

	FORCEINLINE void Cut ( const int32 Index , const FIntPoint Point )
	{
		if ( PointList[ Index ].X > Point.Y || PointList[ Index ].Y < Point.X )
		{
			return;
		}

		check ( PointList.IsValidIndex( Index ) );

		if ( PointList[ Index ].Y <= Point.Y && PointList[ Index ].X >= Point.X )
		{
			PointList.RemoveAt ( Index );
		}
		else if ( PointList[ Index ].Y > Point.Y && PointList[ Index ].X < Point.X )
		{
			PointList.Insert ( FIntPoint ( Point.Y + 1 , PointList[ Index ].Y ) , Index + 1 );

			PointList[ Index ].Y = Point.X - 1;
		}
		else if ( PointList[ Index ].Y > Point.Y )
		{
			PointList[ Index ].X = Point.Y + 1;
		}
		else if ( PointList[ Index ].X < Point.X )
		{
			PointList[ Index ].Y = Point.X - 1;
		}
	}

	FORCEINLINE void Add ( const FIntPoint Point )
	{
		const FIntPoint OverlapIndexPoint ( GetOverlapIndex ( Point + FIntPoint ( -1 , 1 ) ) );

		if ( OverlapIndexPoint.X == INDEX_NONE )
		{
			if ( OverlapIndexPoint.Y == INDEX_NONE )
			{
				PointList.Add ( Point );
			}
			else
			{
				PointList.Insert ( Point , OverlapIndexPoint.Y );
			}

			return;
		}

		check ( OverlapIndexPoint.Y != INDEX_NONE );

		Merge ( OverlapIndexPoint.X , FIntPoint ( Point.X , FMath::Max ( Point.Y , PointList[ OverlapIndexPoint.Y ].Y ) ) );

		for ( int32 Index = OverlapIndexPoint.Y ; Index > OverlapIndexPoint.X ; Index-- )
		{
			PointList.RemoveAt ( Index );
		}
	}

	FORCEINLINE void Remove ( const FIntPoint Point )
	{
		const FIntPoint OverlapIndexPoint ( GetOverlapIndex ( Point ) );

		for ( int32 Index = OverlapIndexPoint.Y ; Index >= OverlapIndexPoint.X ; Index-- )
		{
			Cut ( Index , Point );
		}
	}
};

UCLASS ( )
class LOHFUNCTIONPLUGIN_API ULohFunctionPluginLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY ( )

public:

	UFUNCTION ( BlueprintPure , Category = "LohFunctionPluginLibrary | String" )
	static FString BufferToString ( const TArray <uint8>& Buffer );

	UFUNCTION ( BlueprintPure , Category = "LohFunctionPluginLibrary | String" )
	static TArray <uint8> StringToBuffer ( FString FromString );

	UFUNCTION ( BlueprintPure , Category = "LohFunctionPluginLibrary | LFPIntPointList" )
	static bool ContainPoint ( const FLFPIntPointList& List , const int32 Index );

	UFUNCTION ( BlueprintCallable , Category = "LohFunctionPluginLibrary | LFPIntPointList" )
	static void AddPoint ( UPARAM ( ref ) FLFPIntPointList& List , const FIntPoint Range );

	UFUNCTION ( BlueprintCallable , Category = "LohFunctionPluginLibrary | LFPIntPointList" )
	static void RemovePoint ( UPARAM ( ref ) FLFPIntPointList& List , const FIntPoint Range );

	UFUNCTION ( BlueprintCallable , Category = "LohFunctionPluginLibrary | Other" )
	static FGameplayTag GetGameplayTagFromName ( const FName TagName );
};
