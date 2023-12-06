#pragma once

#include "NativeGameplayTags.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_Identifier)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_Categorize)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_SlotName)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_Event)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_Meta)

struct LOHFUNCTIONPLUGINITEM_API FLFPItemGameplayTag
{
	FLFPItemGameplayTag() :
		Identifier(FGameplayTag::RequestGameplayTag("Item.Identifier")),
		Categorize(FGameplayTag::RequestGameplayTag("Item.Categorize")),
		SlotName(FGameplayTag::RequestGameplayTag("Item.SlotName")),
		Event(FGameplayTag::RequestGameplayTag("Item.Event")),
		Meta(FGameplayTag::RequestGameplayTag("Item.Meta"))
	{}

public:

	const FGameplayTag Identifier;
	const FGameplayTag Categorize;
	const FGameplayTag SlotName;
	const FGameplayTag Event;
	const FGameplayTag Meta;

public:

	static FLFPItemGameplayTag ItemGameplayTag;
};
