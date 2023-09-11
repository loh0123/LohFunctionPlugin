// // Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LFPRenderLibrary.generated.h"

/**
 *
 */
UCLASS()
class LOHFUNCTIONPLUGIN_API ULFPRenderLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "LFPRenderLibrary")
		static UTexture2D* CreateTexture2D(const FIntPoint Size, const TextureFilter Filter, const bool bSRGB = true);

	UFUNCTION()
		static TArray<FVector3f> CreateVertexPosList(const FVector3f& Center, const FRotator3f& Rotation, const FVector3f& Scale);

	UFUNCTION()
		static void CreateFaceData(const TArray<FVector3f>& VertexPosList, TArray<FVector3f>& VertexList, TArray<FVector2f>& UVList, TArray<uint32>& TriangleIndexList);

public:

	static bool UpdateTexture2D(UTexture2D* Texture, uint8* Data, const FUpdateTextureRegion2D* RegionList, const int32 RegionAmount);
};

