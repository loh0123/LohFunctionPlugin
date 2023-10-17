#pragma once

#include "NativeGameplayTags.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_Identifiers)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_Categorizes)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_SlotNames)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_SlotNames_All)

struct LOHFUNCTIONPLUGINITEM_API FLFPItemGameplayTag
{
	FLFPItemGameplayTag() :
		Identifiers(FGameplayTag::RequestGameplayTag("Item.Identifiers")),
		Categorizes(FGameplayTag::RequestGameplayTag("Item.Categorizes")),
		SlotNames(FGameplayTag::RequestGameplayTag("Item.SlotNames")),
		SlotNames_All(FGameplayTag::RequestGameplayTag("Item.SlotNames.All"))
	{}

public:

	const FGameplayTag Identifiers;
	const FGameplayTag Categorizes;
	const FGameplayTag SlotNames;
	const FGameplayTag SlotNames_All;

public:

	static FLFPItemGameplayTag ItemGameplayTag;
};
