#pragma once

#include "NativeGameplayTags.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_Identifiers)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_Categorizes)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_SlotNames)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_Events)

struct LOHFUNCTIONPLUGINITEM_API FLFPItemGameplayTag
{
	FLFPItemGameplayTag() :
		Identifiers(FGameplayTag::RequestGameplayTag("Item.Identifiers")),
		Categorizes(FGameplayTag::RequestGameplayTag("Item.Categorizes")),
		SlotNames(FGameplayTag::RequestGameplayTag("Item.SlotNames")),
		Events(FGameplayTag::RequestGameplayTag("Item.Events"))
	{}

public:

	const FGameplayTag Identifiers;
	const FGameplayTag Categorizes;
	const FGameplayTag SlotNames;
	const FGameplayTag Events;

public:

	static FLFPItemGameplayTag ItemGameplayTag;
};
