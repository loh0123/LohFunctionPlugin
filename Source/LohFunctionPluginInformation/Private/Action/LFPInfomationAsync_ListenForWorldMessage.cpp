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
		UE_LOG( LFPWorldMessageSubsystem , Error , TEXT( "Activate failed ULFPWorldMessageSubsystem or World invalid" ) );

		Cancel();

		return;
	}

	if ( TagChannel.IsValid() == false )
	{
		UE_LOG( LFPWorldMessageSubsystem , Error , TEXT( "Activate failed Tag ( %s ) invalid" ) , *TagChannel.ToString() );

		Cancel();

		return;
	}

	EventSubsystem = GetWorld()->GetSubsystem<ULFPWorldMessageSubsystem>();

	FLFPWorldMessageCallbackDelegate& Delegate = EventSubsystem->AddListener( TagChannel , GetOuter() );

	Delegate.AddDynamic( this , &ULFPInfomationAsync_ListenForWorldMessage::BroadcastMessage );

	check( Delegate.IsBound() );
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
