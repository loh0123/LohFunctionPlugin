// Copyright by Loh Zhi Kang


#include "System/LFPGameplayTagSubsystem.h"
#include "Components/LFPGameplayTagComponent.h"

void ULFPGameplayTagSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	
}

void ULFPGameplayTagSubsystem::Deinitialize()
{
	
}

void ULFPGameplayTagSubsystem::RegisterComponent(const FGameplayTag Tag, UActorComponent* Component)
{
	FLFPGameplayTagBindData& RefVar = ReferenceMap.FindOrAdd(Tag);

	RefVar.BindObject(Component);

	TagContainer.AddTag(Tag);

	OnRegisterComponent.Broadcast(Tag, Component);

	return;
}

void ULFPGameplayTagSubsystem::RegisterComponentByContainer(const FGameplayTagContainer Tags, UActorComponent* Component)
{
	for (const auto& Tag : Tags)
	{
		RegisterComponent(Tag, Component);
	}

	return;
}

void ULFPGameplayTagSubsystem::UnregisterComponent(const FGameplayTag Tag, UActorComponent* Component)
{
	if (ReferenceMap.Contains(Tag) == false) return;
	
	FLFPGameplayTagBindData& RefVar = ReferenceMap.FindChecked(Tag);

	RefVar.UnbindObject(Component);

	TagContainer.RemoveTag(Tag);

	OnUnregisterComponent.Broadcast(Tag, Component);

	return;
}

void ULFPGameplayTagSubsystem::UnregisterComponentByContainer(const FGameplayTagContainer Tags, UActorComponent* Component)
{
	for (const auto& Tag : Tags)
	{
		UnregisterComponent(Tag, Component);
	}

	return;
}

void ULFPGameplayTagSubsystem::FindComponentListByTag(TArray<UActorComponent*>& ComponentList, const FGameplayTag ComponentGameplayTag, const TArray<FName>& ComponentTagList, const bool bHasAllTags) const
{
	FindComponentListByTags(ComponentList, ComponentGameplayTag.GetSingleTagContainer(), ComponentTagList, bHasAllTags);

	return;
}

void ULFPGameplayTagSubsystem::FindComponentListByTags(TArray<UActorComponent*>& ComponentList, const FGameplayTagContainer ComponentGameplayTags, const TArray<FName>& ComponentTagList, const bool bHasAllTags) const
{
	if (TagContainer.HasAny(ComponentGameplayTags) == false) return;

	TSet<UActorComponent*> UniqueList;

	for (const auto& Reference : ReferenceMap)
	{
		if (Reference.Key.MatchesAny(ComponentGameplayTags) == false) continue;

		UniqueList.Reserve(UniqueList.Num() + Reference.Value.BindedObjectNum());

		for (const auto& BindedObject : Reference.Value.GetBindedObjectList())
		{
			if (ComponentTagList.IsEmpty() == false)
			{
				bool bIsPass = bHasAllTags;

				for (const FName& ComponentCheckTag : ComponentTagList)
				{
					if (BindedObject->ComponentHasTag(ComponentCheckTag) == (bIsPass == false))
					{
						bIsPass = !bIsPass;

						break;
					}
				}

				if (bIsPass == false) continue;
			}

			UniqueList.Add(BindedObject);
		}
	}

	ComponentList.Append(UniqueList.Array());

	return;
}

void ULFPGameplayTagSubsystem::BroadcastGameplayTagEvent(const FGameplayTagContainer ComponentTags, const FGameplayTag EventTag, UObject* Caller, const FString Messages) const
{
	if (TagContainer.HasAny(ComponentTags) == false) return;

	TSet<UActorComponent*> UniqueList;

	for (const auto& Reference : ReferenceMap)
	{
		if (Reference.Key.MatchesAny(ComponentTags) == false) continue;

		UniqueList.Reserve(UniqueList.Num() + Reference.Value.BindedObjectNum());

		for (const auto& BindedObject : Reference.Value.GetBindedObjectList())
		{
			if (UniqueList.Contains(BindedObject)) continue;

			UniqueList.Add(BindedObject);

			const ULFPGameplayTagComponent* TagComponent = Cast<ULFPGameplayTagComponent>(BindedObject);

			if (TagComponent != nullptr) TagComponent->BroadcastEvent(EventTag, Caller, Messages);
		}
	}

	return;
}

bool ULFPGameplayTagSubsystem::HasComponentWithTag(const FGameplayTag ComponentGameplayTag, const TArray<FName>& ComponentTagList, const bool bHasAllTags) const
{
	return HasComponentWithTags(ComponentGameplayTag.GetSingleTagContainer(), ComponentTagList, bHasAllTags);
}

bool ULFPGameplayTagSubsystem::HasComponentWithTags(const FGameplayTagContainer ComponentGameplayTags, const TArray<FName>& ComponentTagList, const bool bHasAllTags) const
{
	if (TagContainer.HasAny(ComponentGameplayTags) == false) return false;

	for (const auto& Reference : ReferenceMap)
	{
		if (Reference.Key.MatchesAny(ComponentGameplayTags) == false) continue;

		for (const auto& BindedObject : Reference.Value.GetBindedObjectList())
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

			return true;
		}
	}

	return false;
}
