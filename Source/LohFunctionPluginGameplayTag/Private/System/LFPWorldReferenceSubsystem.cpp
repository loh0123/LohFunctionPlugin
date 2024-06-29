// Copyright by Loh Zhi Kang


#include "System/LFPWorldReferenceSubsystem.h"
#include "Components/LFPTagReferenceComponent.h"

bool ULFPWorldReferenceSubsystem::ProcessActorComponent(const FGameplayTagContainer& ComponentGameplayTags, const TArray<FName>& ComponentTagList, const bool bHasAllTags, const TFunctionRef<bool(UActorComponent* FoundedComponent)> OnMatchComponentFounded, const TFunctionRef<bool()> OnEnd) const
{
	TArray<TObjectPtr<UActorComponent>> FoundComponentList;

	/* Find Component On ReferenceMap And Cache It */
	for (TArray<FGameplayTag> SearchTagList = ComponentGameplayTags.GetGameplayTagArray(); SearchTagList.IsEmpty() == false;)
	{
		const TArray<FGameplayTag> OldSearchlist = SearchTagList;

		SearchTagList.Empty();

		for (const auto& SearchTag : OldSearchlist)
		{
			if (auto ReferenceData = ReferenceMap.Find(SearchTag); ReferenceData != nullptr)
			{
				FoundComponentList.Append(ReferenceData->GetBindedObjectList());

				SearchTagList.Append(ReferenceData->ChildTagList.Array());
			}
		}
	}

	/* Loop All Found Component And Check Tag Name Match */
	for (const auto& FoundComponent : FoundComponentList)
	{
		if (ComponentTagList.IsEmpty() == false)
		{
			bool bIsPass = bHasAllTags;

			for (const FName& ComponentCheckTag : ComponentTagList)
			{
				if (FoundComponent->ComponentHasTag(ComponentCheckTag) == !bIsPass)
				{
					bIsPass = !bIsPass;

					break;
				}
			}

			if (bIsPass == false) continue;
		}

		if (OnMatchComponentFounded(FoundComponent))
		{
			return OnEnd();
		}
	}

	return OnEnd();
}

void ULFPWorldReferenceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	
}

void ULFPWorldReferenceSubsystem::Deinitialize()
{
	
}

void ULFPWorldReferenceSubsystem::RegisterComponent(const FGameplayTag Tag, UActorComponent* Component)
{
	if (IsValid(Component) == false)
	{
		return;
	}

	if (auto ReferenceData = ReferenceMap.Find(Tag); ReferenceData != nullptr)
	{
		ReferenceData->BindObject(Component);
	}
	else
	{
		/* Add Child First And Bind Object */
		ReferenceMap.Add(Tag).BindObject(Component);

		/* Try Extract Parent Tag If Any */
		if (TArray<FGameplayTag> ParentTagList; UGameplayTagsManager::Get().ExtractParentTags(Tag, ParentTagList))
		{
			FGameplayTag ChildTag = Tag;

			/* Add All Parent And Link It Together */
			for (const FGameplayTag& ParentTag : ParentTagList)
			{
				ReferenceMap.FindOrAdd(ParentTag).ChildTagList.Add(ChildTag);
			}
		}
	}

	OnRegisterComponent.Broadcast(Tag, Component);

	return;
}

void ULFPWorldReferenceSubsystem::RegisterComponentByContainer(const FGameplayTagContainer Tags, UActorComponent* Component)
{
	for (const auto& Tag : Tags)
	{
		RegisterComponent(Tag, Component);
	}

	return;
}

void ULFPWorldReferenceSubsystem::UnregisterComponent(const FGameplayTag Tag, UActorComponent* Component)
{
	if (IsValid(Component) == false)
	{
		return;
	}

	if (ReferenceMap.Contains(Tag) == false)
	{
		return;
	}

	/* First Unbind Object On The Tag */
	ReferenceMap.FindChecked(Tag).UnbindObject(Component);

	/* Remove The Tag And It Parent Until It Can't Be Remove Or No Parent Left */
	if (TArray<FGameplayTag> RemoveTagList = { Tag }; UGameplayTagsManager::Get().ExtractParentTags(Tag, RemoveTagList))
	{
		for (const FGameplayTag& RemoveTag : RemoveTagList)
		{
			if (ReferenceMap.FindChecked(RemoveTag).CanRemove() == false)
			{
				break;
			}

			ReferenceMap.Remove(RemoveTag);
		}
	}

	OnUnregisterComponent.Broadcast(Tag, Component);

	return;
}

void ULFPWorldReferenceSubsystem::UnregisterComponentByContainer(const FGameplayTagContainer Tags, UActorComponent* Component)
{
	for (const auto& Tag : Tags)
	{
		UnregisterComponent(Tag, Component);
	}

	return;
}

bool ULFPWorldReferenceSubsystem::FindComponentListByTagList(TArray<UActorComponent*>& ComponentList, const FGameplayTagContainer ComponentGameplayTags, const TArray<FName>& ComponentTagList, const bool bHasAllTags) const
{
	bool bHasFound = false;

	return ProcessActorComponent(ComponentGameplayTags, ComponentTagList, bHasAllTags,
		[&](UActorComponent* FoundedComponent) 
		{ 
			ComponentList.Add(FoundedComponent); 
			bHasFound = true; 
			return false; 
		}, 
		[&]() 
		{ 
			return bHasFound; 
		}
	);
}

bool ULFPWorldReferenceSubsystem::FindActorListByTagList(TArray<AActor*>& ActorList, const FGameplayTagContainer ComponentGameplayTags, const TArray<FName>& ComponentTagList, const bool bHasAllTags) const
{
	bool bHasFound = false;

	return ProcessActorComponent(ComponentGameplayTags, ComponentTagList, bHasAllTags,
		[&](UActorComponent* FoundedComponent)
		{
			if (IsValid(FoundedComponent->GetOwner()))
			{
				ActorList.Add(FoundedComponent->GetOwner());
				bHasFound = true;
			}

			return false;
		},
		[&]()
		{
			return bHasFound;
		}
	);
}

bool ULFPWorldReferenceSubsystem::FindActorListByInterface(TArray<AActor*>& ActorList, const TSubclassOf<UInterface> Interface, const FGameplayTagContainer ComponentGameplayTags, const TArray<FName>& ComponentTagList, const bool bHasAllTags) const
{
	bool bHasFound = false;

	return ProcessActorComponent(ComponentGameplayTags, ComponentTagList, bHasAllTags,
		[&](UActorComponent* FoundedComponent)
		{
			if (IsValid(FoundedComponent->GetOwner()) && FoundedComponent->GetOwner()->GetClass()->ImplementsInterface(Interface))
			{
				ActorList.Add(FoundedComponent->GetOwner());
				bHasFound = true;
			}

			return false;
		},
		[&]()
		{
			return bHasFound;
		}
	);
}

bool ULFPWorldReferenceSubsystem::BroadcastGameplayTagEvent(const FGameplayTagContainer ComponentGameplayTags, const TArray<FName>& ComponentTagList, const bool bHasAllTags, const FGameplayTag EventTag, UObject* Caller, const FString Messages) const
{
	bool bHasFound = false;

	return ProcessActorComponent(ComponentGameplayTags, ComponentTagList, bHasAllTags,
		[&](UActorComponent* FoundedComponent)
		{
			const ULFPTagReferenceComponent* TagComponent = Cast<ULFPTagReferenceComponent>(FoundedComponent);

			if (IsValid(TagComponent)) TagComponent->BroadcastEvent(EventTag, Caller, Messages);

			bHasFound = true;

			// Stop Loop (false)
			return false;
		},
		[&]()
		{
			return bHasFound;
		}
	);
}

bool ULFPWorldReferenceSubsystem::HasComponentWithTag(const FGameplayTag ComponentGameplayTag, const TArray<FName>& ComponentTagList, const bool bHasAllTags) const
{
	return HasComponentWithTags(ComponentGameplayTag.GetSingleTagContainer(), ComponentTagList, bHasAllTags);
}

bool ULFPWorldReferenceSubsystem::HasComponentWithTags(const FGameplayTagContainer ComponentGameplayTags, const TArray<FName>& ComponentTagList, const bool bHasAllTags) const
{
	return ProcessActorComponent(ComponentGameplayTags, ComponentTagList, bHasAllTags, [&](UActorComponent* FoundedComponent) { return true; }, [&]() { return true; });
}


