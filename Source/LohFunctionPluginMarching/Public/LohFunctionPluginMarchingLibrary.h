// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "LohFunctionPluginMarchingLibrary.generated.h"

USTRUCT(BlueprintType)
struct FLFPMarchingPartKey
{
	GENERATED_BODY()

public:

	FLFPMarchingPartKey() {}

	FLFPMarchingPartKey(const uint8 NewConnectID, const FGameplayTag& NewObjectTag) : ConnectID(NewConnectID), ObjectTag(NewObjectTag) {}

public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default, meta = (Bitmask))
	uint8 ConnectID = uint8(255);

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default)
	FGameplayTag ObjectTag = FGameplayTag::EmptyTag;

public:

	bool operator==(const FLFPMarchingPartKey& Other) const
	{
		return ConnectID == Other.ConnectID && ObjectTag == Other.ObjectTag;
	}
};

FORCEINLINE uint32 GetTypeHash(const FLFPMarchingPartKey& Thing)
{
	uint32 Hash = FCrc::MemCrc32(&Thing, sizeof(FLFPMarchingPartKey));
	return Hash;
};

/**
 * 
 */
UCLASS()
class LOHFUNCTIONPLUGINMARCHING_API ULohFunctionPluginMarchingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginMarchingLibrary | Function")
		static TMap<FLFPMarchingPartKey, class ULFPMarchingPartAsset*> GenerateMarchingMap();

	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary | Bit")
		static TArray<uint8> GenerateBitMatrixNumberTop(const uint8 BitList);

	UFUNCTION(BlueprintPure, Category = "LohFunctionPluginMarchingLibrary | Function")
		static FLFPMarchingPartKey MakeMarchingPartKey(const TArray<bool>& ConnectPointList, const FGameplayTag ObjectTag);
};
