// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LohFunctionPlugin/Public/Terrain/LFPTerrainSystem.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLFPTerrainSystem() {}
// Cross Module References
	LOHFUNCTIONPLUGIN_API UFunction* Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainRemoveEvent__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_LohFunctionPlugin();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntVector();
	LOHFUNCTIONPLUGIN_API UFunction* Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainAddEvent__DelegateSignature();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLGPTerrainData();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLGPTerrainSystemEvent();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPTerrainSystem_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPTerrainSystem();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainRemoveEvent__DelegateSignature_Statics
	{
		struct _Script_LohFunctionPlugin_eventLFPTerrainRemoveEvent_Parms
		{
			TArray<FIntVector> RemoveList;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_RemoveList_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RemoveList_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_RemoveList;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainRemoveEvent__DelegateSignature_Statics::NewProp_RemoveList_Inner = { "RemoveList", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainRemoveEvent__DelegateSignature_Statics::NewProp_RemoveList_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainRemoveEvent__DelegateSignature_Statics::NewProp_RemoveList = { "RemoveList", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_LohFunctionPlugin_eventLFPTerrainRemoveEvent_Parms, RemoveList), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainRemoveEvent__DelegateSignature_Statics::NewProp_RemoveList_MetaData, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainRemoveEvent__DelegateSignature_Statics::NewProp_RemoveList_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainRemoveEvent__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainRemoveEvent__DelegateSignature_Statics::NewProp_RemoveList_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainRemoveEvent__DelegateSignature_Statics::NewProp_RemoveList,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainRemoveEvent__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainRemoveEvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_LohFunctionPlugin, nullptr, "LFPTerrainRemoveEvent__DelegateSignature", nullptr, nullptr, sizeof(_Script_LohFunctionPlugin_eventLFPTerrainRemoveEvent_Parms), Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainRemoveEvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainRemoveEvent__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainRemoveEvent__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainRemoveEvent__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainRemoveEvent__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainRemoveEvent__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainAddEvent__DelegateSignature_Statics
	{
		struct _Script_LohFunctionPlugin_eventLFPTerrainAddEvent_Parms
		{
			TArray<FLGPTerrainData> AddList;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_AddList_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AddList_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_AddList;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainAddEvent__DelegateSignature_Statics::NewProp_AddList_Inner = { "AddList", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLGPTerrainData, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainAddEvent__DelegateSignature_Statics::NewProp_AddList_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainAddEvent__DelegateSignature_Statics::NewProp_AddList = { "AddList", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_LohFunctionPlugin_eventLFPTerrainAddEvent_Parms, AddList), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainAddEvent__DelegateSignature_Statics::NewProp_AddList_MetaData, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainAddEvent__DelegateSignature_Statics::NewProp_AddList_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainAddEvent__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainAddEvent__DelegateSignature_Statics::NewProp_AddList_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainAddEvent__DelegateSignature_Statics::NewProp_AddList,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainAddEvent__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainAddEvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_LohFunctionPlugin, nullptr, "LFPTerrainAddEvent__DelegateSignature", nullptr, nullptr, sizeof(_Script_LohFunctionPlugin_eventLFPTerrainAddEvent_Parms), Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainAddEvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainAddEvent__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainAddEvent__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainAddEvent__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainAddEvent__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainAddEvent__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
class UScriptStruct* FLGPTerrainSystemEvent::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOHFUNCTIONPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLGPTerrainSystemEvent, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("LGPTerrainSystemEvent"), sizeof(FLGPTerrainSystemEvent), Get_Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Hash());
	}
	return Singleton;
}
template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<FLGPTerrainSystemEvent>()
{
	return FLGPTerrainSystemEvent::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLGPTerrainSystemEvent(FLGPTerrainSystemEvent::StaticStruct, TEXT("/Script/LohFunctionPlugin"), TEXT("LGPTerrainSystemEvent"), false, nullptr, nullptr);
static struct FScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLGPTerrainSystemEvent
{
	FScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLGPTerrainSystemEvent()
	{
		UScriptStruct::DeferCppStructOps<FLGPTerrainSystemEvent>(FName(TEXT("LGPTerrainSystemEvent")));
	}
} ScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLGPTerrainSystemEvent;
	struct Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_AddList_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AddList_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_AddList;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_RemoveList_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RemoveList_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_RemoveList;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLGPTerrainSystemEvent>();
	}
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::NewProp_AddList_Inner = { "AddList", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLGPTerrainData, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::NewProp_AddList_MetaData[] = {
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::NewProp_AddList = { "AddList", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLGPTerrainSystemEvent, AddList), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::NewProp_AddList_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::NewProp_AddList_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::NewProp_RemoveList_Inner = { "RemoveList", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::NewProp_RemoveList_MetaData[] = {
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::NewProp_RemoveList = { "RemoveList", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLGPTerrainSystemEvent, RemoveList), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::NewProp_RemoveList_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::NewProp_RemoveList_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::NewProp_AddList_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::NewProp_AddList,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::NewProp_RemoveList_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::NewProp_RemoveList,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
		nullptr,
		&NewStructOps,
		"LGPTerrainSystemEvent",
		sizeof(FLGPTerrainSystemEvent),
		alignof(FLGPTerrainSystemEvent),
		Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLGPTerrainSystemEvent()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LohFunctionPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LGPTerrainSystemEvent"), sizeof(FLGPTerrainSystemEvent), Get_Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Hash() { return 450215125U; }
class UScriptStruct* FLGPTerrainData::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOHFUNCTIONPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FLGPTerrainData_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLGPTerrainData, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("LGPTerrainData"), sizeof(FLGPTerrainData), Get_Z_Construct_UScriptStruct_FLGPTerrainData_Hash());
	}
	return Singleton;
}
template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<FLGPTerrainData>()
{
	return FLGPTerrainData::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLGPTerrainData(FLGPTerrainData::StaticStruct, TEXT("/Script/LohFunctionPlugin"), TEXT("LGPTerrainData"), false, nullptr, nullptr);
static struct FScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLGPTerrainData
{
	FScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLGPTerrainData()
	{
		UScriptStruct::DeferCppStructOps<FLGPTerrainData>(FName(TEXT("LGPTerrainData")));
	}
} ScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLGPTerrainData;
	struct Z_Construct_UScriptStruct_FLGPTerrainData_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GridPosition_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_GridPosition;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Offset_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Offset;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TerrainID_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_TerrainID;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGPTerrainData_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLGPTerrainData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLGPTerrainData>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGPTerrainData_Statics::NewProp_GridPosition_MetaData[] = {
		{ "Category", "LGPTerrainData" },
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLGPTerrainData_Statics::NewProp_GridPosition = { "GridPosition", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLGPTerrainData, GridPosition), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FLGPTerrainData_Statics::NewProp_GridPosition_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGPTerrainData_Statics::NewProp_GridPosition_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGPTerrainData_Statics::NewProp_Offset_MetaData[] = {
		{ "Category", "LGPTerrainData" },
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLGPTerrainData_Statics::NewProp_Offset = { "Offset", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLGPTerrainData, Offset), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FLGPTerrainData_Statics::NewProp_Offset_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGPTerrainData_Statics::NewProp_Offset_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGPTerrainData_Statics::NewProp_TerrainID_MetaData[] = {
		{ "Category", "LGPTerrainData" },
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLGPTerrainData_Statics::NewProp_TerrainID = { "TerrainID", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLGPTerrainData, TerrainID), METADATA_PARAMS(Z_Construct_UScriptStruct_FLGPTerrainData_Statics::NewProp_TerrainID_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGPTerrainData_Statics::NewProp_TerrainID_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLGPTerrainData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGPTerrainData_Statics::NewProp_GridPosition,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGPTerrainData_Statics::NewProp_Offset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGPTerrainData_Statics::NewProp_TerrainID,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLGPTerrainData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
		nullptr,
		&NewStructOps,
		"LGPTerrainData",
		sizeof(FLGPTerrainData),
		alignof(FLGPTerrainData),
		Z_Construct_UScriptStruct_FLGPTerrainData_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGPTerrainData_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLGPTerrainData_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGPTerrainData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLGPTerrainData()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLGPTerrainData_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LohFunctionPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LGPTerrainData"), sizeof(FLGPTerrainData), Get_Z_Construct_UScriptStruct_FLGPTerrainData_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLGPTerrainData_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLGPTerrainData_Hash() { return 615771361U; }
	DEFINE_FUNCTION(ULFPTerrainSystem::execUpdateEvent)
	{
		P_GET_STRUCT(FLGPTerrainSystemEvent,Z_Param_Data);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->UpdateEvent_Implementation(Z_Param_Data);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPTerrainSystem::execGetTerrain)
	{
		P_GET_STRUCT(FIntVector,Z_Param_GridPosition);
		P_GET_STRUCT_REF(FLGPTerrainData,Z_Param_Out_ReturnData);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->GetTerrain(Z_Param_GridPosition,Z_Param_Out_ReturnData);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPTerrainSystem::execRemoveTerrain)
	{
		P_GET_STRUCT(FIntVector,Z_Param_GridPosition);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->RemoveTerrain(Z_Param_GridPosition);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPTerrainSystem::execAddTerrain)
	{
		P_GET_STRUCT(FLGPTerrainData,Z_Param_Data);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->AddTerrain(Z_Param_Data);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPTerrainSystem::execIsTerrainLocationValid)
	{
		P_GET_STRUCT(FIntVector,Z_Param_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->IsTerrainLocationValid(Z_Param_Location);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPTerrainSystem::execTerrainToWorldLocation)
	{
		P_GET_STRUCT(FIntVector,Z_Param_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FVector*)Z_Param__Result=P_THIS->TerrainToWorldLocation(Z_Param_Location);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPTerrainSystem::execWorldToTerrainLocation)
	{
		P_GET_STRUCT(FVector,Z_Param_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FIntVector*)Z_Param__Result=P_THIS->WorldToTerrainLocation(Z_Param_Location);
		P_NATIVE_END;
	}
	static FName NAME_ULFPTerrainSystem_UpdateEvent = FName(TEXT("UpdateEvent"));
	void ULFPTerrainSystem::UpdateEvent(FLGPTerrainSystemEvent const& Data)
	{
		LFPTerrainSystem_eventUpdateEvent_Parms Parms;
		Parms.Data=Data;
		ProcessEvent(FindFunctionChecked(NAME_ULFPTerrainSystem_UpdateEvent),&Parms);
	}
	void ULFPTerrainSystem::StaticRegisterNativesULFPTerrainSystem()
	{
		UClass* Class = ULFPTerrainSystem::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AddTerrain", &ULFPTerrainSystem::execAddTerrain },
			{ "GetTerrain", &ULFPTerrainSystem::execGetTerrain },
			{ "IsTerrainLocationValid", &ULFPTerrainSystem::execIsTerrainLocationValid },
			{ "RemoveTerrain", &ULFPTerrainSystem::execRemoveTerrain },
			{ "TerrainToWorldLocation", &ULFPTerrainSystem::execTerrainToWorldLocation },
			{ "UpdateEvent", &ULFPTerrainSystem::execUpdateEvent },
			{ "WorldToTerrainLocation", &ULFPTerrainSystem::execWorldToTerrainLocation },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULFPTerrainSystem_AddTerrain_Statics
	{
		struct LFPTerrainSystem_eventAddTerrain_Parms
		{
			FLGPTerrainData Data;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Data_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Data;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPTerrainSystem_AddTerrain_Statics::NewProp_Data_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPTerrainSystem_AddTerrain_Statics::NewProp_Data = { "Data", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPTerrainSystem_eventAddTerrain_Parms, Data), Z_Construct_UScriptStruct_FLGPTerrainData, METADATA_PARAMS(Z_Construct_UFunction_ULFPTerrainSystem_AddTerrain_Statics::NewProp_Data_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTerrainSystem_AddTerrain_Statics::NewProp_Data_MetaData)) };
	void Z_Construct_UFunction_ULFPTerrainSystem_AddTerrain_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPTerrainSystem_eventAddTerrain_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPTerrainSystem_AddTerrain_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPTerrainSystem_eventAddTerrain_Parms), &Z_Construct_UFunction_ULFPTerrainSystem_AddTerrain_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPTerrainSystem_AddTerrain_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPTerrainSystem_AddTerrain_Statics::NewProp_Data,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPTerrainSystem_AddTerrain_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPTerrainSystem_AddTerrain_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPTerrainSystem_AddTerrain_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPTerrainSystem, nullptr, "AddTerrain", nullptr, nullptr, sizeof(LFPTerrainSystem_eventAddTerrain_Parms), Z_Construct_UFunction_ULFPTerrainSystem_AddTerrain_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTerrainSystem_AddTerrain_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020405, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPTerrainSystem_AddTerrain_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTerrainSystem_AddTerrain_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPTerrainSystem_AddTerrain()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPTerrainSystem_AddTerrain_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPTerrainSystem_GetTerrain_Statics
	{
		struct LFPTerrainSystem_eventGetTerrain_Parms
		{
			FIntVector GridPosition;
			FLGPTerrainData ReturnData;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GridPosition_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_GridPosition;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnData;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPTerrainSystem_GetTerrain_Statics::NewProp_GridPosition_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPTerrainSystem_GetTerrain_Statics::NewProp_GridPosition = { "GridPosition", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPTerrainSystem_eventGetTerrain_Parms, GridPosition), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPTerrainSystem_GetTerrain_Statics::NewProp_GridPosition_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTerrainSystem_GetTerrain_Statics::NewProp_GridPosition_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPTerrainSystem_GetTerrain_Statics::NewProp_ReturnData = { "ReturnData", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPTerrainSystem_eventGetTerrain_Parms, ReturnData), Z_Construct_UScriptStruct_FLGPTerrainData, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_ULFPTerrainSystem_GetTerrain_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPTerrainSystem_eventGetTerrain_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPTerrainSystem_GetTerrain_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPTerrainSystem_eventGetTerrain_Parms), &Z_Construct_UFunction_ULFPTerrainSystem_GetTerrain_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPTerrainSystem_GetTerrain_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPTerrainSystem_GetTerrain_Statics::NewProp_GridPosition,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPTerrainSystem_GetTerrain_Statics::NewProp_ReturnData,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPTerrainSystem_GetTerrain_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPTerrainSystem_GetTerrain_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPTerrainSystem" },
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPTerrainSystem_GetTerrain_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPTerrainSystem, nullptr, "GetTerrain", nullptr, nullptr, sizeof(LFPTerrainSystem_eventGetTerrain_Parms), Z_Construct_UFunction_ULFPTerrainSystem_GetTerrain_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTerrainSystem_GetTerrain_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPTerrainSystem_GetTerrain_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTerrainSystem_GetTerrain_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPTerrainSystem_GetTerrain()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPTerrainSystem_GetTerrain_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPTerrainSystem_IsTerrainLocationValid_Statics
	{
		struct LFPTerrainSystem_eventIsTerrainLocationValid_Parms
		{
			FIntVector Location;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Location;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPTerrainSystem_IsTerrainLocationValid_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPTerrainSystem_eventIsTerrainLocationValid_Parms, Location), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_ULFPTerrainSystem_IsTerrainLocationValid_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPTerrainSystem_eventIsTerrainLocationValid_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPTerrainSystem_IsTerrainLocationValid_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPTerrainSystem_eventIsTerrainLocationValid_Parms), &Z_Construct_UFunction_ULFPTerrainSystem_IsTerrainLocationValid_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPTerrainSystem_IsTerrainLocationValid_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPTerrainSystem_IsTerrainLocationValid_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPTerrainSystem_IsTerrainLocationValid_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPTerrainSystem_IsTerrainLocationValid_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPTerrainSystem" },
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPTerrainSystem_IsTerrainLocationValid_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPTerrainSystem, nullptr, "IsTerrainLocationValid", nullptr, nullptr, sizeof(LFPTerrainSystem_eventIsTerrainLocationValid_Parms), Z_Construct_UFunction_ULFPTerrainSystem_IsTerrainLocationValid_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTerrainSystem_IsTerrainLocationValid_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPTerrainSystem_IsTerrainLocationValid_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTerrainSystem_IsTerrainLocationValid_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPTerrainSystem_IsTerrainLocationValid()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPTerrainSystem_IsTerrainLocationValid_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPTerrainSystem_RemoveTerrain_Statics
	{
		struct LFPTerrainSystem_eventRemoveTerrain_Parms
		{
			FIntVector GridPosition;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GridPosition_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_GridPosition;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPTerrainSystem_RemoveTerrain_Statics::NewProp_GridPosition_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPTerrainSystem_RemoveTerrain_Statics::NewProp_GridPosition = { "GridPosition", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPTerrainSystem_eventRemoveTerrain_Parms, GridPosition), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPTerrainSystem_RemoveTerrain_Statics::NewProp_GridPosition_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTerrainSystem_RemoveTerrain_Statics::NewProp_GridPosition_MetaData)) };
	void Z_Construct_UFunction_ULFPTerrainSystem_RemoveTerrain_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPTerrainSystem_eventRemoveTerrain_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPTerrainSystem_RemoveTerrain_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPTerrainSystem_eventRemoveTerrain_Parms), &Z_Construct_UFunction_ULFPTerrainSystem_RemoveTerrain_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPTerrainSystem_RemoveTerrain_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPTerrainSystem_RemoveTerrain_Statics::NewProp_GridPosition,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPTerrainSystem_RemoveTerrain_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPTerrainSystem_RemoveTerrain_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPTerrainSystem_RemoveTerrain_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPTerrainSystem, nullptr, "RemoveTerrain", nullptr, nullptr, sizeof(LFPTerrainSystem_eventRemoveTerrain_Parms), Z_Construct_UFunction_ULFPTerrainSystem_RemoveTerrain_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTerrainSystem_RemoveTerrain_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820405, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPTerrainSystem_RemoveTerrain_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTerrainSystem_RemoveTerrain_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPTerrainSystem_RemoveTerrain()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPTerrainSystem_RemoveTerrain_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPTerrainSystem_TerrainToWorldLocation_Statics
	{
		struct LFPTerrainSystem_eventTerrainToWorldLocation_Parms
		{
			FIntVector Location;
			FVector ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Location;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPTerrainSystem_TerrainToWorldLocation_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPTerrainSystem_eventTerrainToWorldLocation_Parms, Location), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPTerrainSystem_TerrainToWorldLocation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPTerrainSystem_eventTerrainToWorldLocation_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPTerrainSystem_TerrainToWorldLocation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPTerrainSystem_TerrainToWorldLocation_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPTerrainSystem_TerrainToWorldLocation_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPTerrainSystem_TerrainToWorldLocation_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPTerrainSystem" },
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPTerrainSystem_TerrainToWorldLocation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPTerrainSystem, nullptr, "TerrainToWorldLocation", nullptr, nullptr, sizeof(LFPTerrainSystem_eventTerrainToWorldLocation_Parms), Z_Construct_UFunction_ULFPTerrainSystem_TerrainToWorldLocation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTerrainSystem_TerrainToWorldLocation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPTerrainSystem_TerrainToWorldLocation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTerrainSystem_TerrainToWorldLocation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPTerrainSystem_TerrainToWorldLocation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPTerrainSystem_TerrainToWorldLocation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPTerrainSystem_UpdateEvent_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Data_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Data;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPTerrainSystem_UpdateEvent_Statics::NewProp_Data_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPTerrainSystem_UpdateEvent_Statics::NewProp_Data = { "Data", nullptr, (EPropertyFlags)0x0010000008000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPTerrainSystem_eventUpdateEvent_Parms, Data), Z_Construct_UScriptStruct_FLGPTerrainSystemEvent, METADATA_PARAMS(Z_Construct_UFunction_ULFPTerrainSystem_UpdateEvent_Statics::NewProp_Data_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTerrainSystem_UpdateEvent_Statics::NewProp_Data_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPTerrainSystem_UpdateEvent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPTerrainSystem_UpdateEvent_Statics::NewProp_Data,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPTerrainSystem_UpdateEvent_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPTerrainSystem_UpdateEvent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPTerrainSystem, nullptr, "UpdateEvent", nullptr, nullptr, sizeof(LFPTerrainSystem_eventUpdateEvent_Parms), Z_Construct_UFunction_ULFPTerrainSystem_UpdateEvent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTerrainSystem_UpdateEvent_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00224CC0, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPTerrainSystem_UpdateEvent_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTerrainSystem_UpdateEvent_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPTerrainSystem_UpdateEvent()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPTerrainSystem_UpdateEvent_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPTerrainSystem_WorldToTerrainLocation_Statics
	{
		struct LFPTerrainSystem_eventWorldToTerrainLocation_Parms
		{
			FVector Location;
			FIntVector ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Location;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPTerrainSystem_WorldToTerrainLocation_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPTerrainSystem_eventWorldToTerrainLocation_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPTerrainSystem_WorldToTerrainLocation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPTerrainSystem_eventWorldToTerrainLocation_Parms, ReturnValue), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPTerrainSystem_WorldToTerrainLocation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPTerrainSystem_WorldToTerrainLocation_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPTerrainSystem_WorldToTerrainLocation_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPTerrainSystem_WorldToTerrainLocation_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPTerrainSystem" },
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPTerrainSystem_WorldToTerrainLocation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPTerrainSystem, nullptr, "WorldToTerrainLocation", nullptr, nullptr, sizeof(LFPTerrainSystem_eventWorldToTerrainLocation_Parms), Z_Construct_UFunction_ULFPTerrainSystem_WorldToTerrainLocation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTerrainSystem_WorldToTerrainLocation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPTerrainSystem_WorldToTerrainLocation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTerrainSystem_WorldToTerrainLocation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPTerrainSystem_WorldToTerrainLocation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPTerrainSystem_WorldToTerrainLocation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ULFPTerrainSystem_NoRegister()
	{
		return ULFPTerrainSystem::StaticClass();
	}
	struct Z_Construct_UClass_ULFPTerrainSystem_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnAddTerrain_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnAddTerrain;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnRemoveTerrain_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnRemoveTerrain;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GridSize_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_GridSize;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GridGap_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_GridGap;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_TerrainData_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TerrainData_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_TerrainData;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TerrainEvent_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_TerrainEvent;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_IsEventDirty_MetaData[];
#endif
		static void NewProp_IsEventDirty_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_IsEventDirty;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULFPTerrainSystem_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USceneComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ULFPTerrainSystem_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULFPTerrainSystem_AddTerrain, "AddTerrain" }, // 3789006303
		{ &Z_Construct_UFunction_ULFPTerrainSystem_GetTerrain, "GetTerrain" }, // 104237891
		{ &Z_Construct_UFunction_ULFPTerrainSystem_IsTerrainLocationValid, "IsTerrainLocationValid" }, // 3924618406
		{ &Z_Construct_UFunction_ULFPTerrainSystem_RemoveTerrain, "RemoveTerrain" }, // 2207764258
		{ &Z_Construct_UFunction_ULFPTerrainSystem_TerrainToWorldLocation, "TerrainToWorldLocation" }, // 3107932343
		{ &Z_Construct_UFunction_ULFPTerrainSystem_UpdateEvent, "UpdateEvent" }, // 2253014979
		{ &Z_Construct_UFunction_ULFPTerrainSystem_WorldToTerrainLocation, "WorldToTerrainLocation" }, // 786042801
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPTerrainSystem_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "Terrain/LFPTerrainSystem.h" },
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_OnAddTerrain_MetaData[] = {
		{ "Category", "LFPTerrainSystem | Event" },
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_OnAddTerrain = { "OnAddTerrain", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPTerrainSystem, OnAddTerrain), Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainAddEvent__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_OnAddTerrain_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_OnAddTerrain_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_OnRemoveTerrain_MetaData[] = {
		{ "Category", "LFPTerrainSystem | Event" },
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_OnRemoveTerrain = { "OnRemoveTerrain", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPTerrainSystem, OnRemoveTerrain), Z_Construct_UDelegateFunction_LohFunctionPlugin_LFPTerrainRemoveEvent__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_OnRemoveTerrain_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_OnRemoveTerrain_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_GridSize_MetaData[] = {
		{ "Category", "LFPTerrainSystem | Variable" },
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_GridSize = { "GridSize", nullptr, (EPropertyFlags)0x0010000000000015, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPTerrainSystem, GridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_GridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_GridSize_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_GridGap_MetaData[] = {
		{ "Category", "LFPTerrainSystem | Variable" },
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_GridGap = { "GridGap", nullptr, (EPropertyFlags)0x0010000000000015, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPTerrainSystem, GridGap), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_GridGap_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_GridGap_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_TerrainData_Inner = { "TerrainData", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLGPTerrainData, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_TerrainData_MetaData[] = {
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_TerrainData = { "TerrainData", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPTerrainSystem, TerrainData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_TerrainData_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_TerrainData_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_TerrainEvent_MetaData[] = {
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_TerrainEvent = { "TerrainEvent", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPTerrainSystem, TerrainEvent), Z_Construct_UScriptStruct_FLGPTerrainSystemEvent, METADATA_PARAMS(Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_TerrainEvent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_TerrainEvent_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_IsEventDirty_MetaData[] = {
		{ "ModuleRelativePath", "Public/Terrain/LFPTerrainSystem.h" },
	};
#endif
	void Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_IsEventDirty_SetBit(void* Obj)
	{
		((ULFPTerrainSystem*)Obj)->IsEventDirty = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_IsEventDirty = { "IsEventDirty", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(uint8), sizeof(ULFPTerrainSystem), &Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_IsEventDirty_SetBit, METADATA_PARAMS(Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_IsEventDirty_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_IsEventDirty_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULFPTerrainSystem_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_OnAddTerrain,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_OnRemoveTerrain,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_GridSize,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_GridGap,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_TerrainData_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_TerrainData,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_TerrainEvent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPTerrainSystem_Statics::NewProp_IsEventDirty,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULFPTerrainSystem_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULFPTerrainSystem>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULFPTerrainSystem_Statics::ClassParams = {
		&ULFPTerrainSystem::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ULFPTerrainSystem_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ULFPTerrainSystem_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ULFPTerrainSystem_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPTerrainSystem_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULFPTerrainSystem()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULFPTerrainSystem_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULFPTerrainSystem, 3312738457);
	template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<ULFPTerrainSystem>()
	{
		return ULFPTerrainSystem::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULFPTerrainSystem(Z_Construct_UClass_ULFPTerrainSystem, &ULFPTerrainSystem::StaticClass, TEXT("/Script/LohFunctionPlugin"), TEXT("ULFPTerrainSystem"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULFPTerrainSystem);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
