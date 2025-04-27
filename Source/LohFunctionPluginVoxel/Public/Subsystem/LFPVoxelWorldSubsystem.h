// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "LFPVoxelWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS ( )
class LOHFUNCTIONPLUGINVOXEL_API ULFPVoxelWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY ( )

public:

	virtual void Initialize ( FSubsystemCollectionBase& Collection ) override;

	virtual void Deinitialize ( ) override;
};
