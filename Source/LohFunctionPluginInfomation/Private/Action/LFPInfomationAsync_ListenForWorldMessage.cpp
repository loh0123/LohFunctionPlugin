#include "Action/LFPInfomationAsync_ListenForWorldMessage.h"
#include "System/LFPWorldMessageSubsystem.h"

void ULFPInfomationAsync_ListenForWorldMessage::Cancel()
{
	OwningWorldContext = nullptr;

	if ( EventSubsystem.IsValid() )
	{
		EventSubsystem->RemoveListener( TagChannel , this );

		EventSubsystem.Reset();
	}

	SetReadyToDestroy();
}

bool ULFPInfomationAsync_ListenForWorldMessage::ShouldBroadcastDelegates() const
{
	return OwningWorldContext.IsValid() && Super::ShouldBroadcastDelegates();
}

void ULFPInfomationAsync_ListenForWorldMessage::Activate()
{
	Super::Activate();

	if (
		OwningWorldContext.IsValid() == false ||
		IsValid( OwningWorldContext.Get()->GetWorld() ) == false ||
		OwningWorldContext.Get()->GetWorld()->HasSubsystem<ULFPWorldMessageSubsystem>() == false
		)
	{
		Cancel();

		return;
	}

	if ( TagChannel.IsValid() == false )
	{
		Cancel();

		return;
	}

	EventSubsystem = OwningWorldContext.Get()->GetWorld()->GetSubsystem<ULFPWorldMessageSubsystem>();

	EventSubsystem->AddListener( TagChannel , OwningWorldContext.Get() ).AddDynamic( this , &ULFPInfomationAsync_ListenForWorldMessage::BroadcastMessage );
}

ULFPInfomationAsync_ListenForWorldMessage* ULFPInfomationAsync_ListenForWorldMessage::ListenForWorldMessage( UObject* WorldContext , FGameplayTag TagChannel , bool bExactOnly , bool bOnlyTriggerOnce )
{
	ULFPInfomationAsync_ListenForWorldMessage* MyObj = NewObject<ULFPInfomationAsync_ListenForWorldMessage>();
	MyObj->OwningWorldContext = WorldContext;
	MyObj->TagChannel = TagChannel;
	MyObj->bExactOnly = bExactOnly;
	MyObj->bOnlyTriggerOnce = bOnlyTriggerOnce;

	MyObj->RegisterWithGameInstance( WorldContext );

	return MyObj;
}

void ULFPInfomationAsync_ListenForWorldMessage::BroadcastMessage( const FGameplayTag& Tag , UObject* Payload )
{
	if ( ShouldBroadcastDelegates() == false )
	{
		Cancel();

		return;
	}

	if ( bExactOnly && Tag != TagChannel )
	{
		return;
	}

	OnEvent.Broadcast( Payload );

	if ( bOnlyTriggerOnce )
	{
		Cancel();
	}
}
