// Copyright Epic Games, Inc. All Rights Reserved.

#include "LohFunctionPluginGameplayTag.h"

#define LOCTEXT_NAMESPACE "FLohFunctionPluginGameplayTagModule"

UE_DEFINE_GAMEPLAY_TAG(TAG_Component, "Component");
UE_DEFINE_GAMEPLAY_TAG(TAG_Component_Category, "Component.Category");
UE_DEFINE_GAMEPLAY_TAG(TAG_Component_Identifiers, "Component.Identifiers");
UE_DEFINE_GAMEPLAY_TAG(TAG_Component_Events, "Component.Events");

void FLohFunctionPluginGameplayTagModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void FLohFunctionPluginGameplayTagModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLohFunctionPluginGameplayTagModule, LohFunctionPluginGameplayTag)