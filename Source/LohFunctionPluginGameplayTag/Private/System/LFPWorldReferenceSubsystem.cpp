// Copyright by Loh Zhi Kang


#include "System/LFPWorldReferenceSubsystem.h"
#include "GameplayTagsManager.h"
#include "Components/LFPTagReferenceComponent.h"

bool ULFPWorldReferenceSubsystem::ProcessActorComponent(const FGameplayTagContainer& CategoryGameplayTags, const FGameplayTagContainer& ComponentGameplayTags, const bool bHasAllTags, const TFunctionRef<bool(ULFPTagReferenceComponent* FoundedComponent)> OnMatchComponentFounded, const TFunctionRef<bool()> OnEnd) const
{
	TArray<TObjectPtr<ULFPTagReferenceComponent>> FoundComponentList;

	/* Find Component On ReferenceMap And Cache It */
	for (TArray<FGameplayTag> SearchTagList = CategoryGameplayTags.GetGameplayTagArray(); SearchTagList.IsEmpty() == false;)
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
		if (ComponentGameplayTags.IsEmpty() == false)
		{
			if (FoundComponent->MatchComponentGameplayTags(ComponentGameplayTags, bHasAllTags) == false) 
			{
				continue;
			}
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

void ULFPWorldReferenceSubsystem::RegisterComponent(ULFPTagReferenceComponent* Component)
{
	if (IsValid(Component) == false)
	{
		return;
	}

	for (const auto& CategoryTag : Component->GetCategoryGameplayTags())
	{
		if (auto ReferenceData = ReferenceMap.Find(CategoryTag); ReferenceData != nullptr)
		{
			ReferenceData->BindObject(Component);
		}
		else
		{
			/* Add Child First And Bind Object */
			ReferenceMap.Add(CategoryTag).BindObject(Component);

			/* Try Extract Parent Tag If Any */
			if (TArray<FGameplayTag> ParentTagList; UGameplayTagsManager::Get().ExtractParentTags(CategoryTag, ParentTagList))
			{
				FGameplayTag ChildTag = CategoryTag;

				/* Add All Parent And Link It Together */
				for (const FGameplayTag& ParentTag : ParentTagList)
				{
					ReferenceMap.FindOrAdd(ParentTag).ChildTagList.Add(ChildTag);
				}
			}
		}
	}

	OnRegisterComponent.Broadcast(Component);

	return;
}

void ULFPWorldReferenceSubsystem::UnregisterComponent(ULFPTagReferenceComponent* Component)
{
	if (IsValid(Component) == false)
	{
		return;
	}

	for (const auto& CategoryTag : Component->GetCategoryGameplayTags())
	{
		if (ReferenceMap.Contains(CategoryTag) == false)
		{
			continue;
		}

		/* First Unbind Object On The Tag */
		ReferenceMap.FindChecked(CategoryTag).UnbindObject(Component);

		/* Remove The Tag And It Parent Until It Can't Be Remove Or No Parent Left */
		if (TArray<FGameplayTag> RemoveTagList = { CategoryTag }; UGameplayTagsManager::Get().ExtractParentTags(CategoryTag, RemoveTagList))
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
	}

	OnUnregisterComponent.Broadcast(Component);

	return;
}
bool ULFPWorldReferenceSubsystem::FindComponentListByTagList(TArray<ULFPTagReferenceComponent*>& ComponentList, const FGameplayTagContainer CategoryGameplayTags, const FGameplayTagContainer ComponentGameplayTags, const bool bHasAllTags) const
{
	bool bHasFound = false;

	return ProcessActorComponent(CategoryGameplayTags, ComponentGameplayTags, bHasAllTags,
		[&](ULFPTagReferenceComponent* FoundedComponent)
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

bool ULFPWorldReferenceSubsystem::FindActorListByTagList(TArray<AActor*>& ActorList, const FGameplayTagContainer CategoryGameplayTags, const FGameplayTagContainer ComponentGameplayTags, const bool bHasAllTags) const
{
	bool bHasFound = false;

	return ProcessActorComponent(CategoryGameplayTags, ComponentGameplayTags, bHasAllTags,
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

bool ULFPWorldReferenceSubsystem::FindActorListByInterface(TArray<AActor*>& ActorList, const TSubclassOf<UInterface> Interface, const FGameplayTagContainer CategoryGameplayTags, const FGameplayTagContainer ComponentGameplayTags, const bool bHasAllTags) const
{
	bool bHasFound = false;

	return ProcessActorComponent(CategoryGameplayTags, ComponentGameplayTags, bHasAllTags,
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

bool ULFPWorldReferenceSubsystem::BroadcastGameplayTagEvent(const FGameplayTagContainer CategoryGameplayTags, const FGameplayTagContainer ComponentGameplayTags, const bool bHasAllTags, const FGameplayTag EventTag, UObject* Caller, const FString Messages) const
{
	bool bHasFound = false;

	return ProcessActorComponent(CategoryGameplayTags, ComponentGameplayTags, bHasAllTags,
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

bool ULFPWorldReferenceSubsystem::HasComponentWithTags(const FGameplayTagContainer CategoryGameplayTags, const FGameplayTagContainer ComponentGameplayTags, const bool bHasAllTags) const
{
	bool bHasFound = false;

	return ProcessActorComponent(CategoryGameplayTags, ComponentGameplayTags, bHasAllTags, [&](UActorComponent* FoundedComponent) { bHasFound = true; return true; }, [&]() { return bHasFound; });
}


