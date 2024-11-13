// Copyright by Loh Zhi Kang

#include "System/LFPWorldMessageSubsystem.h" 	
#include "GameplayTagsManager.h"

DEFINE_LOG_CATEGORY( LFPWorldMessageSubsystem );

FLFPWorldMessageCallbackDelegate& ULFPWorldMessageSubsystem::AddListener( const FGameplayTag TagChannel , UObject* ListenerObject )
{
	check( IsValid( ListenerObject ) );

	FLFPWorldMessageCallbackDelegate& ReturnRef = BindList.FindOrAdd( TagChannel ).CallbackDelegate;

	if ( TArray<FGameplayTag> ParentTagList; UGameplayTagsManager::Get().ExtractParentTags( TagChannel , ParentTagList ) )
	{
		FGameplayTag ChildTag = TagChannel;

		/* Add All Parent And Link It Together */
		for ( const FGameplayTag& ParentTag : ParentTagList )
		{
			BindList.FindOrAdd( ParentTag ).ChildTagList.Add( ChildTag );

			ChildTag = ParentTag;
		}
	}

	UE_LOG( LFPWorldMessageSubsystem , Log , TEXT( "Added listener ( %s ) to world message sub system" ) , *ListenerObject->GetName() );

	return ReturnRef;
}

void ULFPWorldMessageSubsystem::RemoveListener( const FGameplayTag TagChannel , UObject* ListenerObject )
{
	check( IsValid( ListenerObject ) );

	FLFPWorldMessageBindData* BindData = BindList.Find( TagChannel );

	if ( BindData == nullptr )
	{
		return;
	}

	BindData->CallbackDelegate.RemoveAll( ListenerObject );

	if ( BindData->CanRemove() )
	{
		BindList.Remove( TagChannel );

		if ( TArray<FGameplayTag> ParentTagList; UGameplayTagsManager::Get().ExtractParentTags( TagChannel , ParentTagList ) )
		{
			FGameplayTag ChildTag = TagChannel;

			for ( const FGameplayTag& ParentTag : ParentTagList )
			{
				FLFPWorldMessageBindData* ParentBindData = BindList.Find( ParentTag );

				if ( ParentBindData == nullptr )
				{
					UE_LOG( LFPWorldMessageSubsystem , Error , TEXT( "RemoveListener ( %s ) Parent tag on BindList invalid (%s)" ) , *ListenerObject->GetName() , *ParentTag.ToString() );

					break;
				}

				ParentBindData->ChildTagList.Remove( ChildTag );

				if ( ParentBindData->CanRemove() )
				{
					BindList.Remove( ParentTag );

					ChildTag = ParentTag;
				}
				else
				{
					break;
				}
			}
		}
	}

	UE_LOG( LFPWorldMessageSubsystem , Log , TEXT( "Removed listener ( %s ) to world message sub system" ) , *ListenerObject->GetName() );
}

void ULFPWorldMessageSubsystem::BroadcastMessage( const FGameplayTag TagChannel , UObject* Payload ) const
{
	const FLFPWorldMessageBindData* BindData = BindList.Find( TagChannel );

	if ( BindData == nullptr )
	{
		UE_LOG( LFPWorldMessageSubsystem , Warning , TEXT( "Channel ( %s ) on world message sub system don't have any listener, message skipped" ) , *TagChannel.ToString() );

		return;
	}

	BindData->CallbackDelegate.Broadcast( TagChannel , Payload );

	if ( TArray<FGameplayTag> NewSearchTagList; UGameplayTagsManager::Get().ExtractParentTags( TagChannel , NewSearchTagList ) )
	{
		while ( NewSearchTagList.IsEmpty() == false )
		{
			const TArray<FGameplayTag> CurrentSearchlist = NewSearchTagList;

			NewSearchTagList.Empty();

			for ( const auto& SearchTag : CurrentSearchlist )
			{
				/* Loop Until There Are No Child To Check */
				if ( const auto ReferenceData = BindList.Find( SearchTag ); ReferenceData != nullptr )
				{
					ReferenceData->CallbackDelegate.Broadcast( TagChannel , Payload );

					NewSearchTagList.Append( ReferenceData->ChildTagList.Array() );
				}

			}
		}
	}


	UE_LOG( LFPWorldMessageSubsystem , Log , TEXT( "Broadcast to channel ( %s ) on world message sub system" ) , *TagChannel.ToString() );
}
