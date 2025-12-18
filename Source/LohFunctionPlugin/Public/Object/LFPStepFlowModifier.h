// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/LFPNoiseLibrary.h"
#include "UObject/Object.h"
#include "LFPStepFlowModifier.generated.h"

/**
 * 
 */
UCLASS ( Blueprintable )
class LOHFUNCTIONPLUGIN_API ULFPStepFlowModifier : public UObject
{
	GENERATED_BODY ( )

public:

	UFUNCTION ( BlueprintPure , Category=Default )
	virtual int32 GetResistantOffset ( const FIntVector& Position ) const { return 0; }

	UFUNCTION ( BlueprintPure , Category=Default )
	virtual int32 GetFlowOffset ( const FIntVector& Position , const int32 ComponentIndex ) const { return 0; }
};

UCLASS ( Blueprintable )
class LOHFUNCTIONPLUGIN_API ULFPStepFlowNoiseModifier : public ULFPStepFlowModifier
{
	GENERATED_BODY ( )

public:

	virtual int32 GetResistantOffset ( const FIntVector& Position ) const override;

	virtual int32 GetFlowOffset ( const FIntVector& Position , const int32 ComponentIndex ) const override;

public:

	UFUNCTION ( BlueprintCallable , Category=Default , meta=(AutoCreateRefTerm=NewOffset , NewScale) )
	void Initialize ( const FLFPNoiseTable& NewNoiseTable , const FVector& NewOffset , const FVector& NewScale , const int32 NewResistantScale , const int32 NewFlowScale );

	UFUNCTION ( BlueprintCallable , Category=Default , meta=(AutoCreateRefTerm=AdditionalOffset) )
	void AddOffset ( const FVector& AdditionalOffset );

protected:

	UPROPERTY ( )
	FLFPNoiseTable NoiseTable = FLFPNoiseTable ( );

	UPROPERTY ( )
	FVector NoiseOffset = FVector ( );

	UPROPERTY ( )
	FVector NoiseScale = FVector ( );

	UPROPERTY ( )
	int32 ResistantScale = 0;

	UPROPERTY ( )
	int32 FlowScale = 0;
};
