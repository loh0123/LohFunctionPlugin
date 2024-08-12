// Copyright by Loh Zhi Kang


#include "System/LFPWorldReferenceSubsystem.h"
#include "GameplayTagsManager.h"
#include "Components/LFPTagReferenceComponent.h"

void ULFPWorldReferenceSubsystem::ProcessActorComponent(
	const FGameplayTagContainer& CategoryGameplayTags, 
	const FGameplayTagQuery& ComponentGameplayTagsQuery,
	const TFunctionRef<bool(ULFPTagReferenceComponent* FoundedComponent)> OnMatchComponentFounded
) const
{
	/* Find Component On ReferenceMap And Cache It */
	for (TArray<FGameplayTag> NewSearchTagList = CategoryGameplayTags.GetGameplayTagArray(); NewSearchTagList.IsEmpty() == false;)
	{
		const TArray<FGameplayTag> CurrentSearchlist = NewSearchTagList;

		NewSearchTagList.Empty();

		for (const auto& SearchTag : CurrentSearchlist)
		{
			/* Loop Until There Are No Child To Check */
			if (auto ReferenceData = ReferenceMap.Find(SearchTag); ReferenceData != nullptr)
			{
				/* Loop All Found Component And Check Tag Name Match */
				for (const auto& FoundComponent : ReferenceData->GetBindedObjectList())
				{
					if (ComponentGameplayTagsQuery.IsEmpty() == false)
					{
						if (FoundComponent->GetComponentGameplayTags().MatchesQuery(ComponentGameplayTagsQuery) == false)
						{
							continue;
						}
					}

					if (OnMatchComponentFounded(FoundComponent))
					{
						return;
					}
				}

				NewSearchTagList.Append(ReferenceData->ChildTagList.Array());
			}
		}
	}

	return;
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

bool ULFPWorldReferenceSubsystem::FindComponentListByTagList(
	TArray<ULFPTagReferenceComponent*>& ComponentList, 
	UPARAM(meta = (Categories = "Component.Category")) const FGameplayTagContainer CategoryGameplayTags,
	const FGameplayTagQuery ComponentGameplayTagsQuery
) const
{
	const int32 OldAmount = ComponentList.Num();

	ProcessActorComponent(CategoryGameplayTags, ComponentGameplayTagsQuery,
		[&](ULFPTagReferenceComponent* FoundedComponent)
		{ 
			ComponentList.Add(FoundedComponent); 

			return false; /* Continues To Loop */
		}
	);

	return ComponentList.Num() > OldAmount;
}

bool ULFPWorldReferenceSubsystem::FindComponentListByName(
	TArray<ULFPTagReferenceComponent*>& ComponentList, 
	const FName NameTag,
	UPARAM(meta = (Categories = "Component.Category")) const FGameplayTagContainer CategoryGameplayTags,
	const FGameplayTagQuery ComponentGameplayTagsQuery
) const
{
	const int32 OldAmount = ComponentList.Num();

	ProcessActorComponent(CategoryGameplayTags, ComponentGameplayTagsQuery,
		[&](ULFPTagReferenceComponent* FoundedComponent)
		{
			if (FoundedComponent->ComponentHasTag(NameTag))
			{
				ComponentList.Add(FoundedComponent);
			}

			return false; /* Continues To Loop */
		}
	);

	return ComponentList.Num() > OldAmount;
}

bool ULFPWorldReferenceSubsystem::FindActorListByTagList(
	TArray<AActor*>& ActorList, 
	UPARAM(meta = (Categories = "Component.Category")) const FGameplayTagContainer CategoryGameplayTags,
	const FGameplayTagQuery ComponentGameplayTagsQuery
) const
{
	const int32 OldAmount = ActorList.Num();

	ProcessActorComponent(CategoryGameplayTags, ComponentGameplayTagsQuery,
		[&](UActorComponent* FoundedComponent)
		{
			if (IsValid(FoundedComponent->GetOwner()))
			{
				ActorList.Add(FoundedComponent->GetOwner());
			}

			return false; /* Continues To Loop */
		}
	);

	return ActorList.Num() > OldAmount;
}

bool ULFPWorldReferenceSubsystem::FindActorListByName(
	TArray<AActor*>& ActorList, 
	const FName NameTag, 
	UPARAM(meta = (Categories = "Component.Category")) const FGameplayTagContainer CategoryGameplayTags,
	const FGameplayTagQuery ComponentGameplayTagsQuery
) const
{
	const int32 OldAmount = ActorList.Num();

	ProcessActorComponent(CategoryGameplayTags, ComponentGameplayTagsQuery,
		[&](UActorComponent* FoundedComponent)
		{
			if (IsValid(FoundedComponent->GetOwner()) && FoundedComponent->GetOwner()->ActorHasTag(NameTag))
			{
				ActorList.Add(FoundedComponent->GetOwner());
			}

			return false; /* Continues To Loop */
		}
	);

	return ActorList.Num() > OldAmount;
}

bool ULFPWorldReferenceSubsystem::FindActorListByInterface(
	TArray<AActor*>& ActorList, 
	const TSubclassOf<UInterface> Interface, 
	UPARAM(meta = (Categories = "Component.Category")) const FGameplayTagContainer CategoryGameplayTags,
	const FGameplayTagQuery ComponentGameplayTagsQuery
) const
{
	const int32 OldAmount = ActorList.Num();

	ProcessActorComponent(CategoryGameplayTags, ComponentGameplayTagsQuery,
		[&](UActorComponent* FoundedComponent)
		{
			if (IsValid(FoundedComponent->GetOwner()) && FoundedComponent->GetOwner()->GetClass()->ImplementsInterface(Interface))
			{
				ActorList.Add(FoundedComponent->GetOwner());
			}

			return false; /* Continues To Loop */
		}
	);

	return ActorList.Num() > OldAmount;
}

bool ULFPWorldReferenceSubsystem::HasComponentWithTags(
	UPARAM(meta = (Categories = "Component.Category")) const FGameplayTagContainer CategoryGameplayTags,
	const FGameplayTagQuery ComponentGameplayTagsQuery
) const
{
	bool bHasFound = false;

	ProcessActorComponent(CategoryGameplayTags, ComponentGameplayTagsQuery, 
		[&](UActorComponent* FoundedComponent) 
		{ 
			bHasFound = true; 
			
			return true; 
		}
	);

	return bHasFound;
}

bool ULFPWorldReferenceSubsystem::HasActorWithTags(
	const FName NameTag,
	UPARAM(meta = (Categories = "Component.Category")) const FGameplayTagContainer CategoryGameplayTags,
	const FGameplayTagQuery ComponentGameplayTagsQuery
) const
{
	bool bHasFound = false;

	ProcessActorComponent(CategoryGameplayTags, ComponentGameplayTagsQuery,
		[&](UActorComponent* FoundedComponent)
		{
			if (IsValid(FoundedComponent->GetOwner()) && FoundedComponent->GetOwner()->ActorHasTag(NameTag))
			{
				bHasFound = true;

				return true;
			}

			return false; /* Continues To Loop */
		}
	);

	return bHasFound;
}

bool ULFPWorldReferenceSubsystem::BroadcastGameplayTagEvent(
	UPARAM(meta = (Categories = "Component.Category")) const FGameplayTagContainer CategoryGameplayTags,
	const FGameplayTagQuery ComponentGameplayTagsQuery,
	const FGameplayTag EventTag,
	UObject* Caller,
	const UObject* Messages
) const
{
	bool bHasFound = false;

	ProcessActorComponent(CategoryGameplayTags, ComponentGameplayTagsQuery,
		[&](UActorComponent* FoundedComponent)
		{
			const ULFPTagReferenceComponent* TagComponent = Cast<ULFPTagReferenceComponent>(FoundedComponent);

			if (IsValid(TagComponent))
			{
				TagComponent->BroadcastEvent(EventTag, Caller, Messages);

				bHasFound = true;
			}

			return false; /* Continues To Loop */
		}
	);

	return bHasFound;
}
