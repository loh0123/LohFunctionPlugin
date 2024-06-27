// Copyright by Loh Zhi Kang


#include "System/LFPWorldReferenceSubsystem.h"
#include "Components/LFPTagReferenceComponent.h"
#include "GameplayTagsManager.h"

bool ULFPWorldReferenceSubsystem::ProcessActorComponent(const FGameplayTagContainer& ComponentGameplayTags, const TArray<FName>& ComponentTagList, const bool bHasAllTags, const TFunctionRef<bool(UActorComponent* FoundedComponent)> OnMatchComponentFounded, const TFunctionRef<bool()> OnEnd) const
{
	TArray<FGameplayTag> FoundComponentTagList;

	for (TArray<FGameplayTag> SearchTagList = ComponentGameplayTags.GetGameplayTagArray(); SearchTagList.IsEmpty() == false;)
	{
		const TArray<FGameplayTag> OldSearchlist = SearchTagList;

		SearchTagList.Empty();

		for (const auto& SearchTag : OldSearchlist)
		{
			if (ReferenceMap.Contains(SearchTag))
			{
				FoundComponentTagList.Add(SearchTag);
			}

			if (TagParentMap.Contains(SearchTag))
			{
				SearchTagList.Append(TagParentMap.FindChecked(SearchTag).ChildList.Array());
			}
		}
	}

	for (const auto& FoundComponentTag : FoundComponentTagList)
	{
		for (const auto& BindedObject : ReferenceMap.FindChecked(FoundComponentTag).GetBindedObjectList())
		{
			if (ComponentTagList.IsEmpty() == false)
			{
				bool bIsPass = bHasAllTags;

				for (const FName& ComponentCheckTag : ComponentTagList)
				{
					if (BindedObject->ComponentHasTag(ComponentCheckTag) == !bIsPass)
					{
						bIsPass = !bIsPass;

						break;
					}
				}

				if (bIsPass == false) continue;
			}

			if (OnMatchComponentFounded(BindedObject))
			{
				return OnEnd();
			}
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
	if (ReferenceMap.Contains(Tag) == false)
	{
		for (FGameplayTag ChildTag = Tag; ChildTag.IsValid();)
		{
			const FGameplayTag ParentTag = UGameplayTagsManager::Get().RequestGameplayTagDirectParent(ChildTag);

			if (ParentTag.IsValid())
			{
				TagParentMap.FindOrAdd(ParentTag).ChildList.Add(ChildTag);
			}

			ChildTag = ParentTag;
		}
	}

	ReferenceMap.FindOrAdd(Tag).BindObject(Component);

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
	if (ReferenceMap.Contains(Tag) == false) return;
	
	FLFPGameplayTagBindData& RefVar = ReferenceMap.FindChecked(Tag);

	RefVar.UnbindObject(Component);

	if (RefVar.CanRemove())
	{
		ReferenceMap.Remove(Tag);

		for (FGameplayTag ChildTag = Tag; ChildTag.IsValid();)
		{
			const FGameplayTag ParentTag = UGameplayTagsManager::Get().RequestGameplayTagDirectParent(ChildTag);

			if (ParentTag.IsValid() && TagParentMap.Contains(ParentTag))
			{
				auto& ParentTagData = TagParentMap.FindChecked(ParentTag);

				ParentTagData.ChildList.Remove(ChildTag);

				if (ParentTagData.ChildList.IsEmpty())
				{
					TagParentMap.Remove(ParentTag);
				}
				else
				{
					break;
				}
			}

			ChildTag = ParentTag;
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
