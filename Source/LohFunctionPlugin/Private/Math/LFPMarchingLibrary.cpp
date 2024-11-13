#include "Math/LFPMarchingLibrary.h"
#include "GenericPlatform/GenericPlatformMath.h"

bool ULFPMarchingLibrary::GetMarchingIDBit( const uint8 MarchingID , const int32 BitIndex )
{
	check( BitIndex >= 0 || BitIndex <= 7 );

	return ( MarchingID & ( 1 << ( BitIndex & ( 8 - 1 ) ) ) ) != 0;
}

void ULFPMarchingLibrary::SetMarchingIDBit( uint8& MarchingID , const int32 BitIndex , const bool bNewValue )
{
	check( BitIndex >= 0 || BitIndex <= 7 );

	if ( bNewValue )
	{
		MarchingID |= 1 << ( BitIndex & 7 );
	}
	else
	{
		MarchingID &= ~( 1 << ( BitIndex & 7 ) );
	}
}

uint8 ULFPMarchingLibrary::RotateMarchingIDByX( const uint8 MarchingID , const bool bReverse )
{
	constexpr int32 SwapList[ 6 ][ 2 ] =
	{
		{ 0,2 },
		{ 2,6 },
		{ 6,4 },
		{ 1,3 },
		{ 3,7 },
		{ 7,5 }
	};

	uint8 ReturnValue = MarchingID;

	for ( int32 Index = bReverse ? 5 : 0; Index < 6 && Index >= 0; bReverse ? Index-- : Index++ )
	{
		const bool TempBool = GetMarchingIDBit( ReturnValue , SwapList[ Index ][ 0 ] );

		SetMarchingIDBit( ReturnValue , SwapList[ Index ][ 0 ] , GetMarchingIDBit( ReturnValue , SwapList[ Index ][ 1 ] ) );
		SetMarchingIDBit( ReturnValue , SwapList[ Index ][ 1 ] , TempBool );
	}

	return ReturnValue;
}

uint8 ULFPMarchingLibrary::RotateMarchingIDByY( const uint8 MarchingID , const bool bReverse )
{
	constexpr int32 SwapList[ 6 ][ 2 ] =
	{
		{ 0,4 } ,
		{ 4,5 } ,
		{ 5,1 } ,
		{ 2,6 } ,
		{ 6,7 } ,
		{ 7,3 }
	};

	uint8 ReturnValue = MarchingID;

	for ( int32 Index = bReverse ? 5 : 0; Index < 6 && Index >= 0; bReverse ? Index-- : Index++ )
	{
		const bool TempBool = GetMarchingIDBit( ReturnValue , SwapList[ Index ][ 0 ] );

		SetMarchingIDBit( ReturnValue , SwapList[ Index ][ 0 ] , GetMarchingIDBit( ReturnValue , SwapList[ Index ][ 1 ] ) );
		SetMarchingIDBit( ReturnValue , SwapList[ Index ][ 1 ] , TempBool );
	}

	return ReturnValue;
}

uint8 ULFPMarchingLibrary::RotateMarchingIDByZ( const uint8 MarchingID , const bool bReverse )
{
	constexpr int32 SwapList[ 6 ][ 2 ] =
	{
		{ 0,2 },
		{ 2,3 },
		{ 3,1 },
		{ 4,6 },
		{ 6,7 },
		{ 7,5 }
	};

	uint8 ReturnValue = MarchingID;

	for ( int32 Index = bReverse ? 5 : 0; Index < 6 && Index >= 0; bReverse ? Index-- : Index++ )
	{
		const bool TempBool = GetMarchingIDBit( ReturnValue , SwapList[ Index ][ 0 ] );

		SetMarchingIDBit( ReturnValue , SwapList[ Index ][ 0 ] , GetMarchingIDBit( ReturnValue , SwapList[ Index ][ 1 ] ) );
		SetMarchingIDBit( ReturnValue , SwapList[ Index ][ 1 ] , TempBool );
	}

	return ReturnValue;
}

uint8 ULFPMarchingLibrary::RotateMarchingID( const uint8 MarchingID , const FIntVector& Rotation )
{
	uint8 ReturnValue = MarchingID;

	const bool bReverseX = Rotation.X < 0;
	const bool bReverseY = Rotation.Y < 0;
	const bool bReverseZ = Rotation.Z < 0;

	FIntVector ABSRotation = FIntVector( FMath::Abs( Rotation.X ) , FMath::Abs( Rotation.Y ) , FMath::Abs( Rotation.Z ) );

	for ( int32 Count = 0; Count < ABSRotation.X; Count++ )
	{
		ReturnValue = RotateMarchingIDByX( ReturnValue , bReverseX );
	}

	for ( int32 Count = 0; Count < ABSRotation.Y; Count++ )
	{
		ReturnValue = RotateMarchingIDByY( ReturnValue , bReverseY );
	}

	for ( int32 Count = 0; Count < ABSRotation.Z; Count++ )
	{
		ReturnValue = RotateMarchingIDByZ( ReturnValue , bReverseZ );
	}

	return ReturnValue;
}

uint8 ULFPMarchingLibrary::CalculateDualGridMarchingID( const uint8 FullMarchingID , const int32 CalculateIndex )
{
	if ( FullMarchingID == 255 || FullMarchingID == 0 )
	{
		return 0; /* Fill so skip */
	}

	constexpr uint8 CheckList[ ] =
	{
		23 , 6 , 8 , 18 , 32 , 20 , 64,
		43 , 10 , 4 , 33 , 16 , 40 , 128,
		77 , 10 , 2 , 65 , 16 , 72 , 128,
		142 , 6 , 1 , 130 , 32 , 132 , 64,
		113 , 96 , 128 , 33 , 2 , 65 , 4,
		178 , 144 , 64 , 18 , 1 , 130 , 8,
		212 , 144 , 32 , 20 , 1 , 132 , 8,
		232 , 96 , 16 , 40 , 2 , 72 , 4
	};

	const int32 CurrentListIndex = CalculateIndex * 7;

	uint8 CurrentFilter = CheckList[ CurrentListIndex ];

	for ( int32 Step = 0; Step < 3; Step++ )
	{
		const uint8 CheckByte = CheckList[ CurrentListIndex + ( Step * 2 ) + 1 ];
		const uint8 ApplyByte = CheckList[ CurrentListIndex + ( Step * 2 ) + 2 ];

		if ( ( FullMarchingID & CheckByte ) == CheckByte )
		{
			CurrentFilter |= ApplyByte;
		}
	}

	return FullMarchingID & CurrentFilter;
}
