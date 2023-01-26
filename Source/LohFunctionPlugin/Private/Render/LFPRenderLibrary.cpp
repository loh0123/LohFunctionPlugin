// Copyright (c) 2022 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)



#include "Render/LFPRenderLibrary.h"
#include "./Math/LFPGridLibrary.h"
#include "MeshCardRepresentation.h"
#include "DistanceFieldAtlas.h"

UTexture2D* ULFPRenderLibrary::CreateTexture2D(const FIntPoint Size, const TextureFilter Filter)
{
	UTexture2D* VoxelColorMap = UTexture2D::CreateTransient(Size.X, Size.Y);

#if WITH_EDITORONLY_DATA
	VoxelColorMap->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
#endif
	VoxelColorMap->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
	VoxelColorMap->SRGB = 1;
	VoxelColorMap->Filter = Filter;
	VoxelColorMap->UpdateResource();

	return VoxelColorMap;
}

bool ULFPRenderLibrary::UpdateTexture2D(UTexture2D* Texture, const TArray<FColor>& Data)
{
	const int32 BufferSize = 4;
	const int32 ArraySize = Texture->GetSizeX() * Texture->GetSizeY() * BufferSize;

	if (Data.Num() != Texture->GetSizeX() * Texture->GetSizeY())
	{
		return false;
	}

	uint8* CPUColorData = new uint8[ArraySize];

	Texture->TemporarilyDisableStreaming();

	for (int32 Index = 0; Index < Data.Num(); Index++)
	{
		const FColor& Color = Data[Index];

		const int32 PixelPos = Index * BufferSize;

		*(CPUColorData + PixelPos) = Color.B;
		*(CPUColorData + PixelPos + 1) = Color.G;
		*(CPUColorData + PixelPos + 2) = Color.R;
		*(CPUColorData + PixelPos + 3) = Color.A;
	}

	FUpdateTextureRegion2D* Region = new FUpdateTextureRegion2D(0, 0, 0, 0, Texture->GetSizeX(), Texture->GetSizeY());

	Texture->UpdateTextureRegions(0, 1, Region, Texture->GetSizeX() * BufferSize, BufferSize, CPUColorData,
		[Region](uint8* SrcData, const FUpdateTextureRegion2D* Regions)
		{
			delete[] SrcData;
			delete Region;
		}
	);

	return true;
}
