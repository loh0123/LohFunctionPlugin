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

bool ULFPRenderLibrary::UpdateTexture2D(UTexture2D* Texture, uint8* Data, const FUpdateTextureRegion2D* RegionList, const int32 RegionAmount)
{
	if (IsValid(Texture) == false) return false;

	const int32 BufferSize = 4;

#if WITH_EDITOR
	Texture->TemporarilyDisableStreaming();
#endif

	Texture->UpdateTextureRegions(0, RegionAmount, RegionList, Texture->GetSizeX() * BufferSize, BufferSize, Data,
		[](uint8* SrcData, const FUpdateTextureRegion2D* Regions)
		{
			delete[] SrcData;
			delete[] Regions;
		}
	);

	return true;
}
