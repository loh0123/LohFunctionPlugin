// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LohFunctionPlugin/Public/Mesh/VoxelPoolBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeVoxelPoolBase() {}
// Cross Module References
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_UVoxelPoolBase_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_UVoxelPoolBase();
	GEOMETRYFRAMEWORK_API UClass* Z_Construct_UClass_UDynamicMeshPool();
	UPackage* Z_Construct_UPackage__Script_LohFunctionPlugin();
// End Cross Module References
	void UVoxelPoolBase::StaticRegisterNativesUVoxelPoolBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UVoxelPoolBase);
	UClass* Z_Construct_UClass_UVoxelPoolBase_NoRegister()
	{
		return UVoxelPoolBase::StaticClass();
	}
	struct Z_Construct_UClass_UVoxelPoolBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UVoxelPoolBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UDynamicMeshPool,
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVoxelPoolBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Mesh/VoxelPoolBase.h" },
		{ "ModuleRelativePath", "Public/Mesh/VoxelPoolBase.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UVoxelPoolBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UVoxelPoolBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UVoxelPoolBase_Statics::ClassParams = {
		&UVoxelPoolBase::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001000A8u,
		METADATA_PARAMS(Z_Construct_UClass_UVoxelPoolBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UVoxelPoolBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UVoxelPoolBase()
	{
		if (!Z_Registration_Info_UClass_UVoxelPoolBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UVoxelPoolBase.OuterSingleton, Z_Construct_UClass_UVoxelPoolBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UVoxelPoolBase.OuterSingleton;
	}
	template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<UVoxelPoolBase>()
	{
		return UVoxelPoolBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UVoxelPoolBase);
	struct Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_VoxelPoolBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_VoxelPoolBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UVoxelPoolBase, UVoxelPoolBase::StaticClass, TEXT("UVoxelPoolBase"), &Z_Registration_Info_UClass_UVoxelPoolBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UVoxelPoolBase), 2207721923U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_VoxelPoolBase_h_3027567220(TEXT("/Script/LohFunctionPlugin"),
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_VoxelPoolBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_VoxelPoolBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
