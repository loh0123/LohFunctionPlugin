// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LFPChunkedTagDataComponent.h"
#include "LFPGridTagDataComponent.generated.h"

UCLASS ( ClassGroup=(Custom) , meta=(BlueprintSpawnableComponent) , HideCategories=("Setting|IndexSize") )
class LOHFUNCTIONPLUGIN_API ULFPGridTagDataComponent : public ULFPChunkedTagDataComponent
{
	GENERATED_BODY ( )

public:

	// Sets default values for this component's properties
	ULFPGridTagDataComponent ( );

protected:

	// Called when the game starts
	virtual void BeginPlay ( ) override;

public:

	// Called every frame
	virtual void TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;

protected:

	UPROPERTY ( EditAnywhere , BlueprintReadOnly , Category="Setting" )
	TObjectPtr < class ULFPGridSetting > GridSetting = nullptr;

public:

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	class ULFPGridSetting* GetGridSetting ( ) const;

public:

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FIntVector ToChunkGridPosition ( const FIntPoint ChunkGridIndex , const bool bRound = false ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FIntPoint ToChunkGridIndex ( FIntVector ChunkGridPosition , const bool bRound = false ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FIntVector ToDataGridPosition ( const FIntVector DataGridIndex , const bool bRound = false ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FIntVector ToDataGridIndex ( FIntVector DataGridPosition , const bool bRound = false ) const;

	UFUNCTION ( BlueprintPure , Category = "LFPGridTagDataComponent | Getter" )
	FIntVector AddOffsetToGridIndex ( FIntVector GridIndex , const FIntVector Offset , const bool bRound = false ) const;
};
