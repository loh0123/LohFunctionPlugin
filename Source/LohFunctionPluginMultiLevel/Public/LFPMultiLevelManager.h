// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "LFPMultiLevelManager.generated.h"

UCLASS ( BlueprintType )
class ULFPMultiLevelHandler : public UObject
{
	GENERATED_BODY ( )

public:

	UFUNCTION ( BlueprintCallable , Category = Default )
	TArray < AActor* > GetCaptureActorList ( ) const;

public:

	UPROPERTY ( )
	TSoftObjectPtr < UWorld > LevelPath = nullptr;

	UPROPERTY ( )
	TObjectPtr < UWorld > LoadedWorld = nullptr;

	UPROPERTY ( )
	TArray < TObjectPtr < AActor > > CaptureActorList = TArray < TObjectPtr < AActor > > ( );
};

/**
 * 
 */
UCLASS ( )
class LOHFUNCTIONPLUGINMULTILEVEL_API ULFPMultiLevelManager : public UWorldSubsystem
{
	GENERATED_BODY ( )

public:

	virtual void Deinitialize ( ) override;
	virtual void Initialize ( FSubsystemCollectionBase& Collection ) override;

public:

	UFUNCTION ( BlueprintCallable , Category = Default )
	ULFPMultiLevelHandler* LoadMultiLevel ( const TSoftObjectPtr < UWorld > Level );

	UFUNCTION ( BlueprintCallable , Category = Default )
	void UnloadMultiLevel ( ULFPMultiLevelHandler* LevelHandler );

private:

	UPROPERTY ( )
	TArray < TObjectPtr < ULFPMultiLevelHandler > > MultiLevelHandlerList;
};
