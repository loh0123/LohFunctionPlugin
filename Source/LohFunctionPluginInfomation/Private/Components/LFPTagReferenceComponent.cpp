// Copyright by Loh Zhi Kang


#include "Components/LFPTagReferenceComponent.h"
#include "System/LFPWorldReferenceSubsystem.h"
#include "Subsystems/SubsystemBlueprintLibrary.h"

// Sets default values for this component's properties
ULFPTagReferenceComponent::ULFPTagReferenceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	// ...
}


void ULFPTagReferenceComponent::InitializeComponent()
{
	Super::InitializeComponent();

	ULFPWorldReferenceSubsystem* SubSystem = Cast<ULFPWorldReferenceSubsystem>( USubsystemBlueprintLibrary::GetWorldSubsystem( this , ULFPWorldReferenceSubsystem::StaticClass() ) );

	if ( SubSystem != nullptr )
	{
		SubSystem->RegisterComponent( this );
	}
}

// Called when the game starts
void ULFPTagReferenceComponent::BeginPlay()
{
	Super::BeginPlay();
}

void ULFPTagReferenceComponent::EndPlay( const EEndPlayReason::Type EndPlayReason )
{
	Super::EndPlay( EndPlayReason );

	ULFPWorldReferenceSubsystem* SubSystem = Cast<ULFPWorldReferenceSubsystem>( USubsystemBlueprintLibrary::GetWorldSubsystem( this , ULFPWorldReferenceSubsystem::StaticClass() ) );

	if ( SubSystem != nullptr )
	{
		SubSystem->UnregisterComponent( this );
	}
}


// Called every frame
void ULFPTagReferenceComponent::TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime , TickType , ThisTickFunction );

	// ...
}

void ULFPTagReferenceComponent::SetComponentGameplayTags( UPARAM( meta = ( Categories = "Component.Identifiers" ) ) const FGameplayTagContainer NewContainer )
{
	ComponentGameplayTags = NewContainer;
}

void ULFPTagReferenceComponent::SetEventGameplayTags( UPARAM( meta = ( Categories = "Component.Events" ) ) const FGameplayTagContainer NewContainer )
{
	EventGameplayTags = NewContainer;
}

void ULFPTagReferenceComponent::BroadcastEvent( const FGameplayTag EventTag , UObject* Caller , const UObject* Messages ) const
{
	if ( EventTag.MatchesAny( EventGameplayTags ) )
	{
		OnGameplayTagEvent.Broadcast( EventTag , Caller , Messages );
	}

	return;
}

const FGameplayTagContainer& ULFPTagReferenceComponent::GetCategoryGameplayTags() const
{
	return CategoryGameplayTags;
}

const FGameplayTagContainer& ULFPTagReferenceComponent::GetComponentGameplayTags() const
{
	return ComponentGameplayTags;
}

