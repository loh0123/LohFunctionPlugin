// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)



#include "Render/LFPRenderLibrary.h"
#include "./Math/LFPGridLibrary.h"
#include "MeshCardRepresentation.h"
#include "DistanceFieldAtlas.h"

UTexture2D* ULFPRenderLibrary::CreateTexture2D(const FIntPoint Size, const TextureFilter Filter, const bool bSRGB)
{
	UTexture2D* VoxelColorMap = UTexture2D::CreateTransient(Size.X, Size.Y);

#if WITH_EDITORONLY_DATA
	VoxelColorMap->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
#endif
	VoxelColorMap->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
	VoxelColorMap->SRGB = bSRGB;
	VoxelColorMap->Filter = Filter;
	VoxelColorMap->UpdateResource();

	return VoxelColorMap;
}

bool ULFPRenderLibrary::UpdateTexture2D(UTexture2D* Texture, const TArray<FColor>& Data, const TArray<FIntVector4>& Regions)
{
	const int32 BufferSize = 4;
	const int32 ArraySize = Texture->GetSizeX() * Texture->GetSizeY() * BufferSize;

	if (Data.Num() != Texture->GetSizeX() * Texture->GetSizeY())
	{
		return false;
	}

	uint8* CPUColorData = new uint8[ArraySize];

#if WITH_EDITOR
	Texture->TemporarilyDisableStreaming();
#endif

	for (int32 Index = 0; Index < Data.Num(); Index++)
	{
		const FColor& Color = Data[Index];

		const int32 PixelPos = Index * BufferSize;

		*(CPUColorData + PixelPos) = Color.B;
		*(CPUColorData + PixelPos + 1) = Color.G;
		*(CPUColorData + PixelPos + 2) = Color.R;
		*(CPUColorData + PixelPos + 3) = Color.A;
	}

	FUpdateTextureRegion2D* RegionList;

	if (Regions.IsEmpty())
	{
		RegionList = new FUpdateTextureRegion2D[1];

		RegionList[0] = FUpdateTextureRegion2D(0, 0, 0, 0, Texture->GetSizeX(), Texture->GetSizeY());
	}
	else
	{
		RegionList = new FUpdateTextureRegion2D[Regions.Num()];

		for (int32 Index = 0; Index < Regions.Num(); Index++)
		{
			const FIntVector4& Region = Regions[Index];

			RegionList[Index] = FUpdateTextureRegion2D(Region.X, Region.Y, 0, 0, Region.Z, Region.W);
		}
	}

	Texture->UpdateTextureRegions(0, 1, RegionList, Texture->GetSizeX() * BufferSize, BufferSize, CPUColorData,
		[](uint8* SrcData, const FUpdateTextureRegion2D* Regions)
		{
			delete[] SrcData;
			delete[] Regions;
		}
	);

	return true;
}

TArray<FVector3f> ULFPRenderLibrary::CreateVertexPosList(const FVector3f& Center, const FRotator3f& Rotation, const FVector3f& Scale)
{
	return {
		(Scale * Rotation.RotateVector(FVector3f(-1.0f, -1.0f, 1.0f))) + Center,
		(Scale * Rotation.RotateVector(FVector3f( 1.0f, -1.0f, 1.0f))) + Center,
		(Scale * Rotation.RotateVector(FVector3f(-1.0f,  1.0f, 1.0f))) + Center,
		(Scale * Rotation.RotateVector(FVector3f( 1.0f,  1.0f, 1.0f))) + Center
	};
}

void ULFPRenderLibrary::CreateFaceData(const TArray<FVector3f>& VertexPosList, TArray<FVector3f>& VertexList, TArray<FVector2f>& UVList, TArray<uint32>& TriangleIndexList)
{
	check(VertexPosList.Num() == 4);

	/* Handle Index Data */
	{
		const uint32 StartIndex = VertexList.Num();

		TriangleIndexList.Append({ StartIndex, 1 + StartIndex, 2 + StartIndex, 3 + StartIndex, 4 + StartIndex, 5 + StartIndex });
	}

	/* Handle Vertex Data */
	{
		VertexList.Append({
			VertexPosList[1],
			VertexPosList[0],
			VertexPosList[3],
			VertexPosList[2],
			VertexPosList[3],
			VertexPosList[0],
			});
	}

	/* Handle UV Data */
	{
		const FVector2f MinUVOffset = FVector2f(0);
		const FVector2f MaxUVOffset = FVector2f(1);

		UVList.Append({
			FVector2f(MinUVOffset.X, MinUVOffset.Y),
			FVector2f(MinUVOffset.X, MaxUVOffset.Y),
			FVector2f(MaxUVOffset.X, MinUVOffset.Y),
			FVector2f(MaxUVOffset.X, MaxUVOffset.Y),
			FVector2f(MaxUVOffset.X, MinUVOffset.Y),
			FVector2f(MinUVOffset.X, MaxUVOffset.Y)
		});
	}
}
