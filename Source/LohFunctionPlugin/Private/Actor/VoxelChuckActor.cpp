// Fill out your copyright notice in the Description page of Project Settings.


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

