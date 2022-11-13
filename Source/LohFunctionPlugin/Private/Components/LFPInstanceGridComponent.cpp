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

	ISMList.SetNum(MeshList.Num());

	int32 Index = 0;

	for (TObjectPtr<UInstancedStaticMeshComponent>& ISM : ISMList)
	{
		ISM = Cast<UInstancedStaticMeshComponent>(GetOwner()->AddComponentByClass(UInstancedStaticMeshComponent::StaticClass(), true, FTransform(), true));

		ISM->SetStaticMesh(MeshList[Index].Mesh);
		ISM->NumCustomDataFloats = MeshList[Index].CustomDataAmount;

		for (int32 MaterialIndex = 0; MaterialIndex < MeshList[Index].Material.Num(); MaterialIndex++)
		{
			ISM->SetMaterial(MaterialIndex, MeshList[Index].Material[MaterialIndex]);
		}

		ISM->SetupAttachment(this);

		GetOwner()->FinishAddComponent(ISM, true, FTransform());

		GetOwner()->AddInstanceComponent(ISM);

		Index++;
	}
}

void ULFPInstanceGridComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for (TObjectPtr<UInstancedStaticMeshComponent>& ISM : ISMList)
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

