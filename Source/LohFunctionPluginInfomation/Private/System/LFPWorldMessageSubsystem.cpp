// Copyright by Loh Zhi Kang

#include "System/LFPWorldMessageSubsystem.h"

DEFINE_LOG_CATEGORY( LFPWorldMessageSubsystem );

FLFPWorldMessageCallbackDelegate& ULFPWorldMessageSubsystem::AddListener( const FGameplayTag TagChannel , UObject* ListenerObject )
{
	check( IsValid( ListenerObject ) );

	FLFPWorldMessageBindData* FindedData = nullptr;

	if ( FindedData = BindList.FindByKey( TagChannel ); FindedData == nullptr )
	{
		FindedData = &BindList.Add_GetRef( FLFPWorldMessageBindData( TagChannel ) );
	}

	UE_LOG( LFPWorldMessageSubsystem , Log , TEXT( "Added listener ( %s ) to world message sub system" ) , *ListenerObject->GetName() );

	return FindedData->CallbackDelegate;
}

void ULFPWorldMessageSubsystem::RemoveListener( const FGameplayTag TagChannel , UObject* ListenerObject )
{
	check( IsValid( ListenerObject ) );

	if ( FLFPWorldMessageBindData* FindedData = BindList.FindByKey( TagChannel ); FindedData != nullptr )
	{
		FindedData->CallbackDelegate.RemoveAll( ListenerObject );

		if ( FindedData->CallbackDelegate.IsBound() == false )
		{
			BindList.RemoveAtSwap( BindList.IndexOfByKey( TagChannel ) );
		}

		UE_LOG( LFPWorldMessageSubsystem , Log , TEXT( "Removed listener ( %s ) to world message sub system" ) , *ListenerObject->GetName() );
	}
}

void ULFPWorldMessageSubsystem::BroadcastMessage( const FGameplayTag TagChannel , UObject* Payload ) const
{
	bool bBroadcasted = false;

	for ( const FLFPWorldMessageBindData& BindData : BindList )
	{
		if ( BindData.GetTagChannel().MatchesTag( TagChannel ) )
		{
			BindData.CallbackDelegate.Broadcast( TagChannel , Payload );

			bBroadcasted = true;
		}
	}

	if ( bBroadcasted )
	{
		UE_LOG( LFPWorldMessageSubsystem , Log , TEXT( "Broadcast to channel ( %s ) on world message sub system" ) , *TagChannel.ToString() );
	}
	else
	{
		UE_LOG( LFPWorldMessageSubsystem , Warning , TEXT( "Channel ( %s ) on world message sub system don't have any listener, message skipped" ) , *TagChannel.ToString() );
	}
}
