// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "NativeGameplayTags.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_Identifier)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_Categorize)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_SlotName)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_Meta)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_Sort)

class FLohFunctionPluginItemModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
