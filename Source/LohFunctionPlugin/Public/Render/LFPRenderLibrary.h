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

	UFUNCTION(BlueprintCallable, Category = "LFPRenderLibrary")
		static bool UpdateTexture2D(UTexture2D* Texture, const TArray<FColor>& Data);
};

