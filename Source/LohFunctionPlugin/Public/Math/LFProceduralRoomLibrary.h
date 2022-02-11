// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LFProceduralRoomLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LOHFUNCTIONPLUGIN_API ULFProceduralRoomLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	//UFUNCTION(BlueprintCallable, Category = "LFPVectorRoomLibrary")
	//	static bool BoxSeperate(UPARAM(ref)TArray<FBox>& BoxArray, TArray<FBox>& ReturnData, const int32 Index, const float MiddlePoint, const bool CutX, const bool CutY, const bool CutZ);
	//
	//UFUNCTION(BlueprintPure, Category = "LFPVectorRoomLibrary")
	//	static void GetBoxInfo(const FBox TargetBox, FVector& Origin, FVector& Scale);
};
