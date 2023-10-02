// Copyright by Loh Zhi Kang


#include "Components/LFPGameplayTagComponent.h"
#include "System/LFPGameplayTagSubsystem.h"
#include "Subsystems/SubsystemBlueprintLibrary.h"

// Sets default values for this component's properties
ULFPGameplayTagComponent::ULFPGameplayTagComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULFPGameplayTagComponent::BeginPlay()
{
	Super::BeginPlay();

	ULFPGameplayTagSubsystem* SubSystem = Cast<ULFPGameplayTagSubsystem>(USubsystemBlueprintLibrary::GetGameInstanceSubsystem(this, ULFPGameplayTagSubsystem::StaticClass()));

	if (SubSystem != nullptr)
	{
		SubSystem->RegisterComponentByContainer(ComponentGameplayTags, this);
	}
}

void ULFPGameplayTagComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	ULFPGameplayTagSubsystem* SubSystem = Cast<ULFPGameplayTagSubsystem>(USubsystemBlueprintLibrary::GetGameInstanceSubsystem(this, ULFPGameplayTagSubsystem::StaticClass()));

	if (SubSystem != nullptr)
	{
		SubSystem->UnregisterComponentByContainer(ComponentGameplayTags, this);
	}
}


// Called every frame
void ULFPGameplayTagComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULFPGameplayTagComponent::BroadcastEvent(const FGameplayTag EventTag, UObject* Caller, const FString& Messages) const
{
	if (EventGameplayTags.HasTag(EventTag))
	{
		OnGameplayTagEvent.Broadcast(EventTag, Caller, Messages);
	}

	return;
}

