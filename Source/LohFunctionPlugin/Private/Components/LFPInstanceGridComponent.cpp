// Copyright by Loh Zhi Kang


#include "Components/LFPInstanceGridComponent.h"
#include "Components/InstancedStaticMeshComponent.h"

// Sets default values for this component's properties
ULFPInstanceGridComponent::ULFPInstanceGridComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULFPInstanceGridComponent::BeginPlay()
{
	Super::BeginPlay();

	UInstancedStaticMeshComponent* ISM = Cast<UInstancedStaticMeshComponent>(GetOwner()->AddComponentByClass(UInstancedStaticMeshComponent::StaticClass(), true, FTransform(), true));

	ISM->SetupAttachment(this);

	ISMList.Add(ISM);

	GetOwner()->FinishAddComponent(ISM, true, FTransform());

	GetOwner()->AddInstanceComponent(ISM);
}

void ULFPInstanceGridComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for (UInstancedStaticMeshComponent* ISM : ISMList)
	{
		ISM->DestroyComponent();
	}
}


// Called every frame
void ULFPInstanceGridComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

