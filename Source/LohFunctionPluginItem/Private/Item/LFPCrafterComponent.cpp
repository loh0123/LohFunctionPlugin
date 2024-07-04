#include "Item/LFPCrafterComponent.h"

// Sets default values for this component's properties
ULFPCrafterComponent::ULFPCrafterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void ULFPCrafterComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void ULFPCrafterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
