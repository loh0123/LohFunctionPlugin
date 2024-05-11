// Copyright by Loh Zhi Kang


#include "System/LFPWorldReferenceSubsystem.h"
#include "Components/LFPTagReferenceComponent.h"

bool ULFPWorldReferenceSubsystem::ProcessActorComponent(const FGameplayTagContainer& ComponentGameplayTags, const TArray<FName>& ComponentTagList, const bool bHasAllTags, const TFunctionRef<bool(UActorComponent* FoundedComponent)> OnMatchComponentFounded, const TFunctionRef<bool()> OnEnd) const
{
	if (TagContainer.HasAny(ComponentGameplayTags) == false) return false;

	for (const FGameplayTag& TagCheck : TagContainer)
	{
		if (TagCheck.MatchesAny(ComponentGameplayTags) == false) continue;

		if (ReferenceMap.Contains(TagCheck) == false)
		{
			UE_LOG(LogTemp, Error, TEXT("ULFPWorldReferenceSubsystem : Function ( HasComponentWithTags ) : ReferenceMap And TagContainer Not Match"));

			continue;
		}

		const auto& Reference = ReferenceMap.FindChecked(TagCheck);

		for (const auto& BindedObject : Reference.GetBindedObjectList())
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
	const bool bHasTag = ReferenceMap.Contains(Tag);

	FLFPGameplayTagBindData& RefVar = ReferenceMap.FindOrAdd(Tag);

	RefVar.BindObject(Component);

	if (bHasTag) TagContainer.AddTag(Tag);

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
		TagContainer.RemoveTag(Tag);

		ReferenceMap.Remove(Tag);
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

bool ULFPWorldReferenceSubsystem::FindComponentListByTag(TArray<UActorComponent*>& ComponentList, const FGameplayTag ComponentGameplayTag, const TArray<FName>& ComponentTagList, const bool bHasAllTags) const
{
	return FindComponentListByTags(ComponentList, ComponentGameplayTag.GetSingleTagContainer(), ComponentTagList, bHasAllTags);
}

bool ULFPWorldReferenceSubsystem::FindComponentListByTags(TArray<UActorComponent*>& ComponentList, const FGameplayTagContainer ComponentGameplayTags, const TArray<FName>& ComponentTagList, const bool bHasAllTags) const
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
