// Copyright Epic Games, Inc. All Rights Reserved.

#include "LohFunctionPluginItem.h"

#define LOCTEXT_NAMESPACE "FLohFunctionPluginItemModule"

UE_DEFINE_GAMEPLAY_TAG(TAG_Item_Identifier, "Item.Identifier")
UE_DEFINE_GAMEPLAY_TAG(TAG_Item_Categorize, "Item.Categorize")
UE_DEFINE_GAMEPLAY_TAG(TAG_Item_SlotName, "Item.SlotName")
UE_DEFINE_GAMEPLAY_TAG(TAG_Item_Event, "Item.Event")
UE_DEFINE_GAMEPLAY_TAG(TAG_Item_Meta, "Item.Meta")
UE_DEFINE_GAMEPLAY_TAG(TAG_Item_Sort, "Item.Sort")

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