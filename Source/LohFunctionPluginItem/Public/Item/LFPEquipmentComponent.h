#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/LFPInventoryComponent.h"
#include "Item/LFPInventoryInterface.h"
#include "LFPItemGameplayTag.h"
#include "LFPEquipmentComponent.generated.h"


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGINITEM_API ULFPEquipmentComponent : public UActorComponent, public ILFPInventoryInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPEquipmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
