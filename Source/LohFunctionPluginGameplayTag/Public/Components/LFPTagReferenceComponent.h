// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "LFPTagReferenceComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FLFPGameplayTagEvent, const FGameplayTag, EventTag, UObject*, Caller, const FString&, Messages);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGINGAMEPLAYTAG_API ULFPTagReferenceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPTagReferenceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UFUNCTION(BlueprintCallable, Category = "LFPTagReferenceComponent|Getter")
		const FGameplayTagContainer& GetCategoryGameplayTags() const;

	UFUNCTION(BlueprintCallable, Category = "LFPTagReferenceComponent|Getter")
		const FGameplayTagContainer& GetComponentGameplayTags() const;

public:

	UFUNCTION()
		void BroadcastEvent(const FGameplayTag EventTag, UObject* Caller, const FString& Messages) const;

	UFUNCTION()
		bool MatchComponentGameplayTags(const FGameplayTagContainer& TagToMatch, const bool bMatchAll) const;

protected:

	UPROPERTY(BlueprintAssignable, Category = Events)
		FLFPGameplayTagEvent OnGameplayTagEvent;

protected:

	/* Group component together and can be find by parent tag */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Tags, meta = (Categories = "Component.Category"))
		FGameplayTagContainer CategoryGameplayTags = FGameplayTagContainer();

	/* Identify the component inside the category  */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category=Tags, meta=(Categories="Component.Identifiers"))
		FGameplayTagContainer ComponentGameplayTags = FGameplayTagContainer();

	/* Filter event send out by subsystem ( will not receive any event if left empty ) */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category=Tags, meta=(Categories="Component.Events"))
		FGameplayTagContainer EventGameplayTags = FGameplayTagContainer();
};
