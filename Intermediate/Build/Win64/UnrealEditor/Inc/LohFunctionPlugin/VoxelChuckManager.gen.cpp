// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LohFunctionPlugin/Public/Helper/VoxelChuckManager.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeVoxelChuckManager() {}
// Cross Module References
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_UVoxelChuckManager_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_UVoxelChuckManager();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	UPackage* Z_Construct_UPackage__Script_LohFunctionPlugin();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_AVoxelChuckActor_NoRegister();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntVector();
// End Cross Module References
	DEFINE_FUNCTION(UVoxelChuckManager::execSetTrackingActor)
	{
		P_GET_OBJECT(AActor,Z_Param_Target);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetTrackingActor(Z_Param_Target);
		P_NATIVE_END;
	}
	void UVoxelChuckManager::StaticRegisterNativesUVoxelChuckManager()
	{
		UClass* Class = UVoxelChuckManager::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "SetTrackingActor", &UVoxelChuckManager::execSetTrackingActor },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UVoxelChuckManager_SetTrackingActor_Statics
	{
		struct VoxelChuckManager_eventSetTrackingActor_Parms
		{
			AActor* Target;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Target;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UVoxelChuckManager_SetTrackingActor_Statics::NewProp_Target = { "Target", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(VoxelChuckManager_eventSetTrackingActor_Parms, Target), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UVoxelChuckManager_SetTrackingActor_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVoxelChuckManager_SetTrackingActor_Statics::NewProp_Target,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UVoxelChuckManager_SetTrackingActor_Statics::Function_MetaDataParams[] = {
		{ "Category", "VoxelChuckManager" },
		{ "ModuleRelativePath", "Public/Helper/VoxelChuckManager.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UVoxelChuckManager_SetTrackingActor_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UVoxelChuckManager, nullptr, "SetTrackingActor", nullptr, nullptr, sizeof(Z_Construct_UFunction_UVoxelChuckManager_SetTrackingActor_Statics::VoxelChuckManager_eventSetTrackingActor_Parms), Z_Construct_UFunction_UVoxelChuckManager_SetTrackingActor_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UVoxelChuckManager_SetTrackingActor_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UVoxelChuckManager_SetTrackingActor_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UVoxelChuckManager_SetTrackingActor_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UVoxelChuckManager_SetTrackingActor()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UVoxelChuckManager_SetTrackingActor_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UVoxelChuckManager);
	UClass* Z_Construct_UClass_UVoxelChuckManager_NoRegister()
	{
		return UVoxelChuckManager::StaticClass();
	}
	struct Z_Construct_UClass_UVoxelChuckManager_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ChuckType_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_ChuckType;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ChuckMeshSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_ChuckMeshSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ChuckGridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_ChuckGridSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PoolGridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_PoolGridSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VisibleSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_VisibleSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TrackingActor_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_TrackingActor;
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_ActiveChuckList_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ActiveChuckList_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ActiveChuckList;
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_AvailableChuckList_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AvailableChuckList_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_AvailableChuckList;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UVoxelChuckManager_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UVoxelChuckManager_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UVoxelChuckManager_SetTrackingActor, "SetTrackingActor" }, // 796518337
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVoxelChuckManager_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "Comment", "/*\n* This component use voxel pool and manage chuck spawning\n*/" },
		{ "IncludePath", "Helper/VoxelChuckManager.h" },
		{ "ModuleRelativePath", "Public/Helper/VoxelChuckManager.h" },
		{ "ToolTip", "* This component use voxel pool and manage chuck spawning" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_ChuckType_MetaData[] = {
		{ "Category", "VoxelChuckManager | Setting" },
		{ "ModuleRelativePath", "Public/Helper/VoxelChuckManager.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_ChuckType = { "ChuckType", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UVoxelChuckManager, ChuckType), Z_Construct_UClass_AVoxelChuckActor_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_ChuckType_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_ChuckType_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_ChuckMeshSize_MetaData[] = {
		{ "Category", "VoxelChuckManager | Setting" },
		{ "ModuleRelativePath", "Public/Helper/VoxelChuckManager.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_ChuckMeshSize = { "ChuckMeshSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UVoxelChuckManager, ChuckMeshSize), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_ChuckMeshSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_ChuckMeshSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_ChuckGridSize_MetaData[] = {
		{ "Category", "VoxelChuckManager | Setting" },
		{ "ModuleRelativePath", "Public/Helper/VoxelChuckManager.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_ChuckGridSize = { "ChuckGridSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UVoxelChuckManager, ChuckGridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_ChuckGridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_ChuckGridSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_PoolGridSize_MetaData[] = {
		{ "Category", "VoxelChuckManager | Setting" },
		{ "ModuleRelativePath", "Public/Helper/VoxelChuckManager.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_PoolGridSize = { "PoolGridSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UVoxelChuckManager, PoolGridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_PoolGridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_PoolGridSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_VisibleSize_MetaData[] = {
		{ "Category", "VoxelChuckManager | Setting" },
		{ "ModuleRelativePath", "Public/Helper/VoxelChuckManager.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_VisibleSize = { "VisibleSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UVoxelChuckManager, VisibleSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_VisibleSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_VisibleSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_TrackingActor_MetaData[] = {
		{ "ModuleRelativePath", "Public/Helper/VoxelChuckManager.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_TrackingActor = { "TrackingActor", nullptr, (EPropertyFlags)0x0044000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UVoxelChuckManager, TrackingActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_TrackingActor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_TrackingActor_MetaData)) };
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_ActiveChuckList_Inner = { "ActiveChuckList", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_AVoxelChuckActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_ActiveChuckList_MetaData[] = {
		{ "ModuleRelativePath", "Public/Helper/VoxelChuckManager.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_ActiveChuckList = { "ActiveChuckList", nullptr, (EPropertyFlags)0x0044000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UVoxelChuckManager, ActiveChuckList), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_ActiveChuckList_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_ActiveChuckList_MetaData)) };
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_AvailableChuckList_Inner = { "AvailableChuckList", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_AVoxelChuckActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_AvailableChuckList_MetaData[] = {
		{ "ModuleRelativePath", "Public/Helper/VoxelChuckManager.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_AvailableChuckList = { "AvailableChuckList", nullptr, (EPropertyFlags)0x0044000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UVoxelChuckManager, AvailableChuckList), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_AvailableChuckList_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_AvailableChuckList_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UVoxelChuckManager_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_ChuckType,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_ChuckMeshSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_ChuckGridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_PoolGridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_VisibleSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_TrackingActor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_ActiveChuckList_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_ActiveChuckList,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_AvailableChuckList_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVoxelChuckManager_Statics::NewProp_AvailableChuckList,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UVoxelChuckManager_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UVoxelChuckManager>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UVoxelChuckManager_Statics::ClassParams = {
		&UVoxelChuckManager::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UVoxelChuckManager_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UVoxelChuckManager_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UVoxelChuckManager_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UVoxelChuckManager_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UVoxelChuckManager()
	{
		if (!Z_Registration_Info_UClass_UVoxelChuckManager.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UVoxelChuckManager.OuterSingleton, Z_Construct_UClass_UVoxelChuckManager_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UVoxelChuckManager.OuterSingleton;
	}
	template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<UVoxelChuckManager>()
	{
		return UVoxelChuckManager::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UVoxelChuckManager);
	struct Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_VoxelChuckManager_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_VoxelChuckManager_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UVoxelChuckManager, UVoxelChuckManager::StaticClass, TEXT("UVoxelChuckManager"), &Z_Registration_Info_UClass_UVoxelChuckManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UVoxelChuckManager), 3338848309U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_VoxelChuckManager_h_3870585507(TEXT("/Script/LohFunctionPlugin"),
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_VoxelChuckManager_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_VoxelChuckManager_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
