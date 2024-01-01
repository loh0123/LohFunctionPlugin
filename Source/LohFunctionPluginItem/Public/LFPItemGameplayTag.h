// Copyright (c) 2023-2024 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "NativeGameplayTags.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_Identifier)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_Categorize)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_SlotName)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_Event)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_Meta)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_Sort)

struct LOHFUNCTIONPLUGINITEM_API FLFPItemGameplayTag
{
	FLFPItemGameplayTag() :
		Identifier(FGameplayTag::RequestGameplayTag("Item.Identifier")),
		Categorize(FGameplayTag::RequestGameplayTag("Item.Categorize")),
		SlotName(FGameplayTag::RequestGameplayTag("Item.SlotName")),
		Event(FGameplayTag::RequestGameplayTag("Item.Event")),
		Meta(FGameplayTag::RequestGameplayTag("Item.Meta")),
		Sort(FGameplayTag::RequestGameplayTag("Item.Sort"))
	{}

public:

	const FGameplayTag Identifier;
	const FGameplayTag Categorize;
	const FGameplayTag SlotName;
	const FGameplayTag Event;
	const FGameplayTag Meta;
	const FGameplayTag Sort;

public:

	static FLFPItemGameplayTag ItemGameplayTag;
};
