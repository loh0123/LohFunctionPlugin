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

void ULFPGameplayTagSubsystem::FindComponentListByTag(TArray<UActorComponent*> ComponentList, const FGameplayTag ComponentTag) const
{
	if (TagContainer.HasTag(ComponentTag) == false) return;

	TSet<UActorComponent*> UniqueList;
	
	for (const auto& Reference : ReferenceMap)
	{
		if (Reference.Key.MatchesTag(ComponentTag) == false) continue;

		UniqueList.Reserve(UniqueList.Num() + Reference.Value.BindedObjectNum());

		for (const auto& BindedObject : Reference.Value.GetBindedObjectList())
		{
			UniqueList.Add(BindedObject);
		}
	}

	ComponentList.Append(UniqueList.Array());

	return;
}

void ULFPGameplayTagSubsystem::FindComponentListByTags(TArray<UActorComponent*> ComponentList, const FGameplayTagContainer ComponentTags) const
{
	if (TagContainer.HasAny(ComponentTags) == false) return;

	TSet<UActorComponent*> UniqueList;

	for (const auto& Reference : ReferenceMap)
	{
		if (Reference.Key.MatchesAny(ComponentTags) == false) continue;

		UniqueList.Reserve(UniqueList.Num() + Reference.Value.BindedObjectNum());

		for (const auto& BindedObject : Reference.Value.GetBindedObjectList())
		{
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
