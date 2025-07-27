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
	TObjectPtr < class ULFPChunkedIndexTranslator > GridSetting = nullptr;

public:

	UFUNCTION ( BlueprintCallable , Category = "LFPGridTagDataComponent" )
	ULFPChunkedIndexTranslator* GetGridSetting ( ) const;
};
