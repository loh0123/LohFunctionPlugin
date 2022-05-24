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
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntVector();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelGridData();
// End Cross Module References
	DEFINE_FUNCTION(UHexagonVoxelMesh::execSetVoxelGridDataList)
	{
		P_GET_TARRAY_REF(FIntVector,Z_Param_Out_GridLocation);
		P_GET_TARRAY_REF(FLFPVoxelGridData,Z_Param_Out_GridData);
		P_GET_UBOOL(Z_Param_bUpdateMesh);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetVoxelGridDataList(Z_Param_Out_GridLocation,Z_Param_Out_GridData,Z_Param_bUpdateMesh);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UHexagonVoxelMesh::execSetVoxelGridData)
	{
		P_GET_STRUCT(FIntVector,Z_Param_GridLocation);
		P_GET_STRUCT(FLFPVoxelGridData,Z_Param_GridData);
		P_GET_UBOOL(Z_Param_bUpdateMesh);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetVoxelGridData(Z_Param_GridLocation,Z_Param_GridData,Z_Param_bUpdateMesh);
		P_NATIVE_END;
	}
	void UHexagonVoxelMesh::StaticRegisterNativesUHexagonVoxelMesh()
	{
		UClass* Class = UHexagonVoxelMesh::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "SetVoxelGridData", &UHexagonVoxelMesh::execSetVoxelGridData },
			{ "SetVoxelGridDataList", &UHexagonVoxelMesh::execSetVoxelGridDataList },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics
	{
		struct HexagonVoxelMesh_eventSetVoxelGridData_Parms
		{
			FIntVector GridLocation;
			FLFPVoxelGridData GridData;
			bool bUpdateMesh;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridLocation_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridLocation;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridData_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridData;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bUpdateMesh_MetaData[];
#endif
		static void NewProp_bUpdateMesh_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bUpdateMesh;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::NewProp_GridLocation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::NewProp_GridLocation = { "GridLocation", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HexagonVoxelMesh_eventSetVoxelGridData_Parms, GridLocation), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::NewProp_GridLocation_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::NewProp_GridLocation_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::NewProp_GridData_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::NewProp_GridData = { "GridData", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HexagonVoxelMesh_eventSetVoxelGridData_Parms, GridData), Z_Construct_UScriptStruct_FLFPVoxelGridData, METADATA_PARAMS(Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::NewProp_GridData_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::NewProp_GridData_MetaData)) }; // 4094411625
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::NewProp_bUpdateMesh_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::NewProp_bUpdateMesh_SetBit(void* Obj)
	{
		((HexagonVoxelMesh_eventSetVoxelGridData_Parms*)Obj)->bUpdateMesh = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::NewProp_bUpdateMesh = { "bUpdateMesh", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(HexagonVoxelMesh_eventSetVoxelGridData_Parms), &Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::NewProp_bUpdateMesh_SetBit, METADATA_PARAMS(Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::NewProp_bUpdateMesh_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::NewProp_bUpdateMesh_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::NewProp_GridLocation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::NewProp_GridData,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::NewProp_bUpdateMesh,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::Function_MetaDataParams[] = {
		{ "Category", "HexagonVoxelMesh | Function" },
		{ "CPP_Default_bUpdateMesh", "true" },
		{ "ModuleRelativePath", "Public/Mesh/HexagonVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHexagonVoxelMesh, nullptr, "SetVoxelGridData", nullptr, nullptr, sizeof(Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::HexagonVoxelMesh_eventSetVoxelGridData_Parms), Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics
	{
		struct HexagonVoxelMesh_eventSetVoxelGridDataList_Parms
		{
			TArray<FIntVector> GridLocation;
			TArray<FLFPVoxelGridData> GridData;
			bool bUpdateMesh;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridLocation_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridLocation_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_GridLocation;
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridData_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridData_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_GridData;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bUpdateMesh_MetaData[];
#endif
		static void NewProp_bUpdateMesh_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bUpdateMesh;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::NewProp_GridLocation_Inner = { "GridLocation", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::NewProp_GridLocation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::NewProp_GridLocation = { "GridLocation", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HexagonVoxelMesh_eventSetVoxelGridDataList_Parms, GridLocation), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::NewProp_GridLocation_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::NewProp_GridLocation_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::NewProp_GridData_Inner = { "GridData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPVoxelGridData, METADATA_PARAMS(nullptr, 0) }; // 4094411625
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::NewProp_GridData_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::NewProp_GridData = { "GridData", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HexagonVoxelMesh_eventSetVoxelGridDataList_Parms, GridData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::NewProp_GridData_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::NewProp_GridData_MetaData)) }; // 4094411625
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::NewProp_bUpdateMesh_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::NewProp_bUpdateMesh_SetBit(void* Obj)
	{
		((HexagonVoxelMesh_eventSetVoxelGridDataList_Parms*)Obj)->bUpdateMesh = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::NewProp_bUpdateMesh = { "bUpdateMesh", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(HexagonVoxelMesh_eventSetVoxelGridDataList_Parms), &Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::NewProp_bUpdateMesh_SetBit, METADATA_PARAMS(Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::NewProp_bUpdateMesh_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::NewProp_bUpdateMesh_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::NewProp_GridLocation_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::NewProp_GridLocation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::NewProp_GridData_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::NewProp_GridData,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::NewProp_bUpdateMesh,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::Function_MetaDataParams[] = {
		{ "Category", "HexagonVoxelMesh | Function" },
		{ "CPP_Default_bUpdateMesh", "true" },
		{ "ModuleRelativePath", "Public/Mesh/HexagonVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHexagonVoxelMesh, nullptr, "SetVoxelGridDataList", nullptr, nullptr, sizeof(Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::HexagonVoxelMesh_eventSetVoxelGridDataList_Parms), Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList_Statics::FuncParams);
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
		{ &Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridData, "SetVoxelGridData" }, // 2099557468
		{ &Z_Construct_UFunction_UHexagonVoxelMesh_SetVoxelGridDataList, "SetVoxelGridDataList" }, // 4098314853
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
		{ Z_Construct_UClass_UHexagonVoxelMesh, UHexagonVoxelMesh::StaticClass, TEXT("UHexagonVoxelMesh"), &Z_Registration_Info_UClass_UHexagonVoxelMesh, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UHexagonVoxelMesh), 2894907072U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_HexagonVoxelMesh_h_2643078655(TEXT("/Script/LohFunctionPlugin"),
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_HexagonVoxelMesh_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_HexagonVoxelMesh_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
