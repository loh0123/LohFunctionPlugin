// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "LFPGameplayTagComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FLFPGameplayTagEvent, const FGameplayTag, EventTag, UObject*, Caller, const FString&, Messages);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGINGAMEPLAYTAG_API ULFPGameplayTagComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPGameplayTagComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UFUNCTION()
		void BroadcastEvent(const FGameplayTag EventTag, UObject* Caller, const FString& Messages) const;

public:

	UPROPERTY(BlueprintAssignable, Category = Events)
		FLFPGameplayTagEvent OnGameplayTagEvent;

public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category=Tags, meta=(Categories="Component.Identifiers"))
		FGameplayTagContainer ComponentGameplayTags = FGameplayTagContainer();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category=Tags, meta=(Categories="Component.Events"))
		FGameplayTagContainer EventGameplayTags = FGameplayTagContainer();
};
