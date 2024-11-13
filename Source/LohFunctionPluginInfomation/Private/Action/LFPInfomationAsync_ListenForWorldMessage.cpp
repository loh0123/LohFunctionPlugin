#include "Action/LFPInfomationAsync_ListenForWorldMessage.h"
#include "System/LFPWorldMessageSubsystem.h"

void ULFPInfomationAsync_ListenForWorldMessage::Cancel()
{
	if ( EventSubsystem.IsValid() )
	{
		EventSubsystem->RemoveListener( TagChannel , this );

		EventSubsystem.Reset();
	}

	SetReadyToDestroy();
}

void ULFPInfomationAsync_ListenForWorldMessage::Activate()
{
	Super::Activate();

	if (
		IsValid( this ) == false ||
		IsValid( GetWorld() ) == false ||
		GetWorld()->HasSubsystem<ULFPWorldMessageSubsystem>() == false
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

	EventSubsystem = GetWorld()->GetSubsystem<ULFPWorldMessageSubsystem>();

	EventSubsystem->AddListener( TagChannel , GetOuter() ).AddDynamic( this , &ULFPInfomationAsync_ListenForWorldMessage::BroadcastMessage );
}

ULFPInfomationAsync_ListenForWorldMessage* ULFPInfomationAsync_ListenForWorldMessage::ListenForWorldMessage( UObject* WorldContext , FGameplayTag TagChannel , const bool bExactOnly , const bool bOnlyTriggerOnce )
{
	ULFPInfomationAsync_ListenForWorldMessage* MyObj = NewObject<ULFPInfomationAsync_ListenForWorldMessage>( WorldContext );
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

	if ( bExactOnly && Tag.MatchesTagExact( TagChannel ) == false )
	{
		return;
	}

	OnEvent.Broadcast( Payload );

	if ( bOnlyTriggerOnce )
	{
		Cancel();
	}
}
