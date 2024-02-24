#include "LohFunctionPluginMarching.h"

DEFINE_LOG_CATEGORY(LohFunctionPluginMarching);

#define LOCTEXT_NAMESPACE "FLohFunctionPluginMarching"

void FLohFunctionPluginMarching::StartupModule()
{
	UE_LOG(LohFunctionPluginMarching, Warning, TEXT("LohFunctionPluginMarching module has been loaded"));
}

void FLohFunctionPluginMarching::ShutdownModule()
{
	UE_LOG(LohFunctionPluginMarching, Warning, TEXT("LohFunctionPluginMarching module has been unloaded"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FLohFunctionPluginMarching, LohFunctionPluginMarching)