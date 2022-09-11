// MIT License
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
#include "GameFramework/Actor.h"
#include <Runtime/Core/Public/Misc/OutputDeviceNull.h>
#include "LFPTickManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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
