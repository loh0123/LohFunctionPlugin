// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "ScalableFloat.h"
#include "LFPExperienceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGINEXPERIENCE_API ULFPExperienceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPExperienceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public: // Getter

	//UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
	//	int32 GetCurrentLevel() const;
	//
	//UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
	//	float GetNextLevelExperience() const;
	//
	//UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
	//	float GetCurrentLevelExperience() const;


	//UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
	//	float GetExperienceAmount() const { return ExperienceAmount; }

protected:

	//UPROPERTY(EditAnywhere, Savegame, Category = "LFPExperienceComponent | Data")
	//	FScalableFloat ExperienceAmount = 0.0f;
};
