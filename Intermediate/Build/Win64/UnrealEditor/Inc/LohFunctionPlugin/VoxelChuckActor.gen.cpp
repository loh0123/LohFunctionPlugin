// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LohFunctionPlugin/Public/Actor/VoxelChuckActor.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeVoxelChuckActor() {}
// Cross Module References
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_AVoxelChuckActor_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_AVoxelChuckActor();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_LohFunctionPlugin();
// End Cross Module References
	void AVoxelChuckActor::StaticRegisterNativesAVoxelChuckActor()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AVoxelChuckActor);
	UClass* Z_Construct_UClass_AVoxelChuckActor_NoRegister()
	{
		return AVoxelChuckActor::StaticClass();
	}
	struct Z_Construct_UClass_AVoxelChuckActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AVoxelChuckActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AVoxelChuckActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Actor/VoxelChuckActor.h" },
		{ "ModuleRelativePath", "Public/Actor/VoxelChuckActor.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AVoxelChuckActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AVoxelChuckActor>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AVoxelChuckActor_Statics::ClassParams = {
		&AVoxelChuckActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AVoxelChuckActor_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AVoxelChuckActor_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AVoxelChuckActor()
	{
		if (!Z_Registration_Info_UClass_AVoxelChuckActor.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AVoxelChuckActor.OuterSingleton, Z_Construct_UClass_AVoxelChuckActor_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AVoxelChuckActor.OuterSingleton;
	}
	template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<AVoxelChuckActor>()
	{
		return AVoxelChuckActor::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AVoxelChuckActor);
	struct Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Actor_VoxelChuckActor_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Actor_VoxelChuckActor_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AVoxelChuckActor, AVoxelChuckActor::StaticClass, TEXT("AVoxelChuckActor"), &Z_Registration_Info_UClass_AVoxelChuckActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AVoxelChuckActor), 1336349406U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Actor_VoxelChuckActor_h_1658765622(TEXT("/Script/LohFunctionPlugin"),
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Actor_VoxelChuckActor_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Actor_VoxelChuckActor_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
