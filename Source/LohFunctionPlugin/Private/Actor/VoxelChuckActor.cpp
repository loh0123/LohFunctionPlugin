// Copyright (c) 2022 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#include "Actor/VoxelChuckActor.h"

// Sets default values
AVoxelChuckActor::AVoxelChuckActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVoxelChuckActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVoxelChuckActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

