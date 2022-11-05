// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LFPInstanceGridComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPInstanceGridComponent : public USceneComponent
{
	GENERATED_BODY()

	UPROPERTY() TArray<TObjectPtr<class UInstancedStaticMeshComponent>> ISMList;


public:	
	// Sets default values for this component's properties
	ULFPInstanceGridComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called when the game end
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
