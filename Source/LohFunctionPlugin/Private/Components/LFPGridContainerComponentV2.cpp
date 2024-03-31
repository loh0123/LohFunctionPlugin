// Copyright by Loh Zhi Kang

#include "Components/LFPGridContainerComponentV2.h"
#include "./Math/LFPGridLibrary.h"
#include "Serialization/ArchiveProxy.h"
#include "Serialization/NameAsStringProxyArchive.h"
#include "Serialization/ArchiveSaveCompressedProxy.h"
#include "Serialization/ArchiveLoadCompressedProxy.h"
#include "UObject/ReflectedTypeAccessors.h"


// Sets default values for this component's properties
ULFPGridContainerComponentV2::ULFPGridContainerComponentV2()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	// ...
}


// Called when the game starts
void ULFPGridContainerComponentV2::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ULFPGridContainerComponentV2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}