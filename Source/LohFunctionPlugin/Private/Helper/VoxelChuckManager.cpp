// Copyright (c) 2022 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)



#include "Helper/VoxelChuckManager.h"

// Sets default values for this component's properties
UVoxelChuckManager::UVoxelChuckManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UVoxelChuckManager::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UVoxelChuckManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UVoxelChuckManager::SetTrackingActor(AActor* Target)
{
	TrackingActor = Target;
}

