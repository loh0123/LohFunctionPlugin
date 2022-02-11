// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LFPRandomTickHelper.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPRandomTickHelper : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPRandomTickHelper();



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "LFPRandomTickHelper")
		FORCEINLINE AActor* SendTick();

	UFUNCTION(BlueprintCallable, Category = "LFPRandomTickHelper")
		FORCEINLINE bool AddTickActor(AActor* Actor, const bool CheckDuplication);

	UFUNCTION(BlueprintCallable, Category = "LFPRandomTickHelper")
		FORCEINLINE bool RemoveTickActor(AActor* Actor, const bool RemoveAll);

public:

	UPROPERTY(BlueprintReadWrite, Category = "LFPRandomTickHelper | Variable")
		FRandomStream Seed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPRandomTickHelper | Variable")
		FString CallFunctionName = "OnRandomTick";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPRandomTickHelper | Variable")
		int32 TickCount = 1;

	UPROPERTY(BlueprintReadOnly, Category = "LFPRandomTickHelper | Variable")
		int32 CurrentArrayIndex = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPRandomTickHelper | Variable")
		float TickDelay = 0.0f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPRandomTickHelper | Variable")
		float CurrentTickDelay = 0.0f;

protected:

	UPROPERTY() TArray<AActor*> TickActorList;

};
