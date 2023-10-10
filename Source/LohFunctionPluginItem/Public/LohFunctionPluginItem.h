// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "NativeGameplayTags.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_Identifiers)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_Categorizes)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_SlotNames)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_SlotNames_All)

class FLohFunctionPluginItemModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
