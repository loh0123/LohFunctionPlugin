// Copyright (c) 2022 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "LohFunctionPluginLibrary.generated.h"

USTRUCT(BlueprintType)
struct FLFPFunctionData
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPFunctionData")
		TObjectPtr<UObject> Caller = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPFunctionData")
		FString NameAndParam = FString("");
};

UCLASS()
class LOHFUNCTIONPLUGIN_API ULohFunctionPluginLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginTesting")
		static bool CallFunctionByFunctionData(const FLFPFunctionData& FunctionData, const bool bForce = true);
};
