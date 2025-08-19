// // Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "CoreMinimal.h"
#include "DynamicMesh/DynamicMesh3.h"
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

	UFUNCTION()
	static TArray< FVector > CreateVertexPosList( const FVector& Center , const FRotator& Rotation , const FVector& Scale );

	UFUNCTION()
	static void CreateFaceData( const TArray< FVector3f >& VertexPosList , TArray< FVector3f >& VertexList , TArray< FVector2f >& UVList , TArray< uint32 >& TriangleIndexList );
};
