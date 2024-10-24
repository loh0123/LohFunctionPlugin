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
	const int32 SwapList[ 6 ][ 2 ] =
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
	const int32 SwapList[ 6 ][ 2 ] =
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
	const int32 SwapList[ 6 ][ 2 ] =
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
