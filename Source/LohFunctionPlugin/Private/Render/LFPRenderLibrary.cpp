// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#include "Render/LFPRenderLibrary.h"


TArray < FVector > ULFPRenderLibrary::CreateVertexPosList ( const FVector& Center , const FRotator& Rotation , const FVector& Scale )
{
	return {
		( Scale * Rotation.RotateVector ( FVector ( -1.0f , -1.0f , 1.0f ) ) ) + Center , ( Scale * Rotation.RotateVector ( FVector ( 1.0f , -1.0f , 1.0f ) ) ) + Center , ( Scale * Rotation.RotateVector ( FVector ( -1.0f , 1.0f , 1.0f ) ) ) + Center , ( Scale * Rotation.RotateVector ( FVector ( 1.0f , 1.0f , 1.0f ) ) ) + Center
	};
}

void ULFPRenderLibrary::CreateFaceData ( const TArray < FVector3f >& VertexPosList , TArray < FVector3f >& VertexList , TArray < FVector2f >& UVList , TArray < uint32 >& TriangleIndexList )
{
	check ( VertexPosList.Num() == 4 );

	/* Handle Index Data */
	{
		const uint32 StartIndex = VertexList.Num ( );

		TriangleIndexList.Append ( {
			                          StartIndex , 1 + StartIndex , 2 + StartIndex , 3 + StartIndex , 4 + StartIndex , 5 + StartIndex
		                          } );
	}

	/* Handle Vertex Data */
	{
		VertexList.Append ( {
			                   VertexPosList [ 1 ] , VertexPosList [ 0 ] , VertexPosList [ 3 ] , VertexPosList [ 2 ] , VertexPosList [ 3 ] , VertexPosList [ 0 ] ,
		                   } );
	}

	/* Handle UV Data */
	{
		const FVector2f MinUVOffset = FVector2f ( 0 );
		const FVector2f MaxUVOffset = FVector2f ( 1 );

		UVList.Append ( {
			               FVector2f ( MinUVOffset.X , MinUVOffset.Y ) , FVector2f ( MinUVOffset.X , MaxUVOffset.Y ) , FVector2f ( MaxUVOffset.X , MinUVOffset.Y ) , FVector2f ( MaxUVOffset.X , MaxUVOffset.Y ) , FVector2f ( MaxUVOffset.X , MinUVOffset.Y ) , FVector2f ( MinUVOffset.X , MaxUVOffset.Y )
		               } );
	}
}
