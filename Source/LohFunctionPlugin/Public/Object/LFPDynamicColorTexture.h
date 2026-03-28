// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LFPDynamicColorTexture.generated.h"

/**
 * 
 */
UCLASS ( BlueprintType )
class LOHFUNCTIONPLUGIN_API ULFPDynamicColorTexture : public UObject
{
	GENERATED_BODY ( )

protected:

	UPROPERTY ( Transient , VisibleAnywhere , Category = "LFPDynamicColorTexture" )
	TObjectPtr < UTexture2D > ColorTexture = nullptr;

	UPROPERTY ( Transient , VisibleAnywhere , Category = "LFPDynamicColorTexture" )
	TArray < uint8 > ColorList;

protected:

	TUniquePtr < FUpdateTextureRegion2D > TextureRegion = nullptr;

public:

	UFUNCTION ( BlueprintPure , Category=Default )
	UTexture2D* GetTexture ( ) const;

public:

	UFUNCTION ( BlueprintCallable , Category=Default )
	void Init ( const FIntPoint Size , const TextureFilter Filter , const bool bSRGB = true );

	UFUNCTION ( BlueprintCallable , meta = ( AutoCreateRefTerm = "NewColor" ) , Category=Default )
	void SetPixelColor ( const int32 X , const int32 Y , const FColor& NewColor );

	UFUNCTION ( BlueprintCallable , Category=Default )
	void Upload ( );
};
