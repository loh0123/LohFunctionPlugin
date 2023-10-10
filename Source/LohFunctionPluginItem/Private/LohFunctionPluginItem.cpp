// Copyright Epic Games, Inc. All Rights Reserved.

#include "LohFunctionPluginItem.h"

#define LOCTEXT_NAMESPACE "FLohFunctionPluginItemModule"

UE_DEFINE_GAMEPLAY_TAG(TAG_Item					, "Item")
UE_DEFINE_GAMEPLAY_TAG(TAG_Item_Identifiers		, "Item.Identifiers")
UE_DEFINE_GAMEPLAY_TAG(TAG_Item_Categorizes		, "Item.Categorizes")
UE_DEFINE_GAMEPLAY_TAG(TAG_Item_SlotNames		, "Item.SlotNames")
UE_DEFINE_GAMEPLAY_TAG(TAG_Item_SlotNames_All	, "Item.SlotNames.All")

void FLohFunctionPluginItemModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void FLohFunctionPluginItemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLohFunctionPluginItemModule, LohFunctionPluginItem)