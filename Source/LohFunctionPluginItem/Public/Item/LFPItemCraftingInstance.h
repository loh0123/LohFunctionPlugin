#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Item/LFPInventoryComponent.h"
#include "LohFunctionPluginItem.h"
#include "LFPItemCraftingInstance.generated.h"


UCLASS( Blueprintable, ClassGroup = (LFPlugin), meta = (BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGINITEM_API ULFPItemCraftingInstance : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPItemCraftingInstance();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
