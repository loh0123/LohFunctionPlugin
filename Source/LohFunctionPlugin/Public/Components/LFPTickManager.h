// Copyright (c) 2022 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include <Runtime/Core/Public/Misc/OutputDeviceNull.h>
#include "LFPTickManager.generated.h"


UCLASS( ClassGroup=(LFPlugin), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPTickManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPTickManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "LFPRandomTickHelper")
		FORCEINLINE int32 SendTick();

	UFUNCTION(BlueprintCallable, Category = "LFPRandomTickHelper")
		FORCEINLINE bool AddTickActor(AActor* Actor, const bool IsRandom, const bool CheckDuplication = false);

	UFUNCTION(BlueprintCallable, Category = "LFPRandomTickHelper")
		FORCEINLINE bool RemoveTickActor(AActor* Actor, const bool RemoveAll);

private:

	UFUNCTION() void SendTickInternal();

public:

	UPROPERTY(BlueprintReadWrite, Category = "LFPRandomTickHelper | Variable")
		FRandomStream Seed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPRandomTickHelper | Variable")
		FString CallFunctionName = "OnRandomTick";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPRandomTickHelper | Variable")
		int32 TickPerCall = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPRandomTickHelper | Variable")
		int32 TickCount = 1;

	UPROPERTY(BlueprintReadOnly, Category = "LFPRandomTickHelper | Variable")
		int32 CurrentArrayIndex = 0;

	UPROPERTY(BlueprintReadOnly, Category = "LFPRandomTickHelper | Variable")
		int32 CurrentCallCount = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPRandomTickHelper | Variable")
		float TickDelay = 0.0f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPRandomTickHelper | Variable")
		float CurrentTickDelay = 0.0f;

protected:

	UPROPERTY() TArray<AActor*> TickActorList;

	FOutputDeviceNull OutputDeviceNull;

};
