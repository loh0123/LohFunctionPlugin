// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/LFPDynamicColorTexture.h"

UTexture2D* ULFPDynamicColorTexture::GetTexture ( ) const
{
	return ColorTexture;
}

void ULFPDynamicColorTexture::Init ( const FIntPoint Size , const TextureFilter Filter , const bool bSRGB )
{
	if ( IsValid ( ColorTexture ) )
	{
		ColorTexture->MarkAsGarbage ( );
		ColorTexture = nullptr;
	}

	ColorTexture = UTexture2D::CreateTransient ( Size.X , Size.Y );
	ColorList.SetNum ( Size.X * Size.Y * 4 );

#if WITH_EDITORONLY_DATA
	ColorTexture->MipGenSettings = TMGS_NoMipmaps;
#endif
	ColorTexture->CompressionSettings = TC_VectorDisplacementmap;
	ColorTexture->SRGB                = bSRGB;
	ColorTexture->Filter              = Filter;
	ColorTexture->UpdateResourceWithParams ( UTexture::EUpdateResourceFlags::None );

	TextureRegion = MakeUnique < FUpdateTextureRegion2D > ( 0 , 0 , 0 , 0 , Size.X , Size.Y );
	Upload ( );
}

void ULFPDynamicColorTexture::SetPixelColor ( const int32 X , const int32 Y , const FColor& NewColor )
{
	if ( IsValid ( ColorTexture ) == false )
	{
		return;
	}

	const int32 ListIndex = ( X + Y * ColorTexture->GetSizeX ( ) ) * 4;

	if ( ColorList.IsValidIndex ( ListIndex ) && ColorList.IsValidIndex ( ListIndex + 3 ) )
	{
		ColorList [ ListIndex ]     = NewColor.B;
		ColorList [ ListIndex + 1 ] = NewColor.G;
		ColorList [ ListIndex + 2 ] = NewColor.R;
		ColorList [ ListIndex + 3 ] = NewColor.A;
	}
}

void ULFPDynamicColorTexture::Upload ( )
{
	if ( IsValid ( ColorTexture ) == false )
	{
		return;
	}

	constexpr int32 BufferSize = 4;

#if WITH_EDITOR
	ColorTexture->TemporarilyDisableStreaming ( );
#endif

	ColorTexture->UpdateTextureRegions (
	                                    0 ,
	                                    1 ,
	                                    TextureRegion.Get ( ) ,
	                                    ColorTexture->GetSizeX ( ) * BufferSize ,
	                                    BufferSize ,
	                                    ColorList.GetData ( )
	                                   );
}
