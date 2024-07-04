// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "NativeGameplayTags.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Component)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Component_Category)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Component_Identifiers)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Component_Events)

class FLohFunctionPluginGameplayTagModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
