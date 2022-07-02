// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LohFunctionPlugin/Public/Mesh/HexagonVoxelMesh.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHexagonVoxelMesh() {}
// Cross Module References
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_UHexagonVoxelMesh_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_UHexagonVoxelMesh();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_UBaseVoxelMesh();
	UPackage* Z_Construct_UPackage__Script_LohFunctionPlugin();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPVoxelData_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(UHexagonVoxelMesh::execSetupMesh)
	{
		P_GET_OBJECT(ULFPVoxelData,Z_Param_NewVoxelData);
		P_GET_PROPERTY(FIntProperty,Z_Param_NewChuckIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetupMesh(Z_Param_NewVoxelData,Z_Param_NewChuckIndex);
		P_NATIVE_END;
	}
	void UHexagonVoxelMesh::StaticRegisterNativesUHexagonVoxelMesh()
	{
		UClass* Class = UHexagonVoxelMesh::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "SetupMesh", &UHexagonVoxelMesh::execSetupMesh },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UHexagonVoxelMesh_SetupMesh_Statics
	{
		struct HexagonVoxelMesh_eventSetupMesh_Parms
		{
			ULFPVoxelData* NewVoxelData;
			int32 NewChuckIndex;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_NewVoxelData;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NewChuckIndex_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_NewChuckIndex;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UHexagonVoxelMesh_SetupMesh_Statics::NewProp_NewVoxelData = { "NewVoxelData", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HexagonVoxelMesh_eventSetupMesh_Parms, NewVoxelData), Z_Construct_UClass_ULFPVoxelData_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHexagonVoxelMesh_SetupMesh_Statics::NewProp_NewChuckIndex_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UHexagonVoxelMesh_SetupMesh_Statics::NewProp_NewChuckIndex = { "NewChuckIndex", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HexagonVoxelMesh_eventSetupMesh_Parms, NewChuckIndex), METADATA_PARAMS(Z_Construct_UFunction_UHexagonVoxelMesh_SetupMesh_Statics::NewProp_NewChuckIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UHexagonVoxelMesh_SetupMesh_Statics::NewProp_NewChuckIndex_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHexagonVoxelMesh_SetupMesh_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHexagonVoxelMesh_SetupMesh_Statics::NewProp_NewVoxelData,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHexagonVoxelMesh_SetupMesh_Statics::NewProp_NewChuckIndex,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHexagonVoxelMesh_SetupMesh_Statics::Function_MetaDataParams[] = {
		{ "Category", "HexagonVoxelMesh | Function" },
		{ "ModuleRelativePath", "Public/Mesh/HexagonVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHexagonVoxelMesh_SetupMesh_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHexagonVoxelMesh, nullptr, "SetupMesh", nullptr, nullptr, sizeof(Z_Construct_UFunction_UHexagonVoxelMesh_SetupMesh_Statics::HexagonVoxelMesh_eventSetupMesh_Parms), Z_Construct_UFunction_UHexagonVoxelMesh_SetupMesh_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHexagonVoxelMesh_SetupMesh_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHexagonVoxelMesh_SetupMesh_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHexagonVoxelMesh_SetupMesh_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHexagonVoxelMesh_SetupMesh()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHexagonVoxelMesh_SetupMesh_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UHexagonVoxelMesh);
	UClass* Z_Construct_UClass_UHexagonVoxelMesh_NoRegister()
	{
		return UHexagonVoxelMesh::StaticClass();
	}
	struct Z_Construct_UClass_UHexagonVoxelMesh_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UHexagonVoxelMesh_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBaseVoxelMesh,
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UHexagonVoxelMesh_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UHexagonVoxelMesh_SetupMesh, "SetupMesh" }, // 1472532446
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHexagonVoxelMesh_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Mesh/HexagonVoxelMesh.h" },
		{ "ModuleRelativePath", "Public/Mesh/HexagonVoxelMesh.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UHexagonVoxelMesh_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHexagonVoxelMesh>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UHexagonVoxelMesh_Statics::ClassParams = {
		&UHexagonVoxelMesh::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UHexagonVoxelMesh_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UHexagonVoxelMesh_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UHexagonVoxelMesh()
	{
		if (!Z_Registration_Info_UClass_UHexagonVoxelMesh.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UHexagonVoxelMesh.OuterSingleton, Z_Construct_UClass_UHexagonVoxelMesh_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UHexagonVoxelMesh.OuterSingleton;
	}
	template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<UHexagonVoxelMesh>()
	{
		return UHexagonVoxelMesh::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UHexagonVoxelMesh);
	struct Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_HexagonVoxelMesh_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_HexagonVoxelMesh_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UHexagonVoxelMesh, UHexagonVoxelMesh::StaticClass, TEXT("UHexagonVoxelMesh"), &Z_Registration_Info_UClass_UHexagonVoxelMesh, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UHexagonVoxelMesh), 1332365247U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_HexagonVoxelMesh_h_273839452(TEXT("/Script/LohFunctionPlugin"),
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_HexagonVoxelMesh_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_HexagonVoxelMesh_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
