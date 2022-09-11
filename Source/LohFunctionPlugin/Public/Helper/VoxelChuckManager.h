// Fill out your copyri// MIT License
// 
// Copyright(c) 2022 loh0123
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright noticeand this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
