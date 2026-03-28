// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/LFPStepFlowModifier.h"

int32 ULFPStepFlowNoiseModifier::GetResistantOffset ( const FIntVector& Position ) const
{
	const FVector CurrentPosition = ( FVector ( Position ) * NoiseScale ) + NoiseOffset;

	return FMath::RoundToInt32 ( ULFPNoiseLibrary::GetLerpNoise ( NoiseTable , CurrentPosition ) * ResistantScale );
}

int32 ULFPStepFlowNoiseModifier::GetFlowOffset ( const FIntVector& Position , const int32 ComponentIndex ) const
{
	if ( ComponentIndex < 0 || ComponentIndex >= 3 )
	{
		return 0;
	}

	const FVector CurrentPosition = ( FVector ( Position ) * NoiseScale ) + NoiseOffset;

	return FMath::RoundToInt32 ( ULFPNoiseLibrary::GetLerpDirectionNoise ( NoiseTable , CurrentPosition ) [ ComponentIndex ] * FlowScale );
}

void ULFPStepFlowNoiseModifier::Initialize ( const FLFPNoiseTable& NewNoiseTable , const FVector& NewOffset , const FVector& NewScale , const int32 NewResistantScale , const int32 NewFlowScale )
{
	NoiseTable     = NewNoiseTable;
	NoiseOffset    = NewOffset;
	NoiseScale     = NewScale;
	ResistantScale = NewResistantScale;
	FlowScale      = NewFlowScale;
}

void ULFPStepFlowNoiseModifier::AddOffset ( const FVector& AdditionalOffset )
{
	NoiseOffset += AdditionalOffset;
}
