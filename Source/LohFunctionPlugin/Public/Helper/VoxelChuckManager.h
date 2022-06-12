// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Actor/VoxelChuckActor.h"
#include "VoxelChuckManager.generated.h"

/*
* This component use voxel pool and manage chuck spawning
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API UVoxelChuckManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVoxelChuckManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable, Category = "VoxelChuckManager")
		FORCEINLINE void SetTrackingActor(AActor* Target);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelChuckManager | Setting")
		TSubclassOf<AVoxelChuckActor> ChuckType = AVoxelChuckActor::StaticClass();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelChuckManager | Setting")
		FVector ChuckMeshSize = FVector(400, 346.4, 300);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelChuckManager | Setting")
		FIntVector ChuckGridSize = FIntVector(1);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelChuckManager | Setting")
		FIntVector PoolGridSize = FIntVector(1);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelChuckManager | Setting")
		FIntVector VisibleSize = FIntVector(1);
	
private:

	UPROPERTY() TObjectPtr<AActor> TrackingActor;

	UPROPERTY() TArray<TObjectPtr<AVoxelChuckActor>> ActiveChuckList;

	UPROPERTY() TArray<TObjectPtr<AVoxelChuckActor>> AvailableChuckList;

};
