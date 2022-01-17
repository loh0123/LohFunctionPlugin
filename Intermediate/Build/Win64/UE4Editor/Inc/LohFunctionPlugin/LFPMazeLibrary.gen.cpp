// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LohFunctionPlugin/Public/Math/LFPMazeLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLFPMazeLibrary() {}
// Cross Module References
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPMazeTable();
	UPackage* Z_Construct_UPackage__Script_LohFunctionPlugin();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPMazeStartData();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPMazeData();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPMazeArea();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntVector();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPMazeLibrary_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPMazeLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRandomStream();
// End Cross Module References
class UScriptStruct* FLFPMazeTable::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOHFUNCTIONPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FLFPMazeTable_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLFPMazeTable, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("LFPMazeTable"), sizeof(FLFPMazeTable), Get_Z_Construct_UScriptStruct_FLFPMazeTable_Hash());
	}
	return Singleton;
}
template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<FLFPMazeTable>()
{
	return FLFPMazeTable::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLFPMazeTable(FLFPMazeTable::StaticStruct, TEXT("/Script/LohFunctionPlugin"), TEXT("LFPMazeTable"), false, nullptr, nullptr);
static struct FScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLFPMazeTable
{
	FScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLFPMazeTable()
	{
		UScriptStruct::DeferCppStructOps<FLFPMazeTable>(FName(TEXT("LFPMazeTable")));
	}
} ScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLFPMazeTable;
	struct Z_Construct_UScriptStruct_FLFPMazeTable_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_StartData_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_StartData_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_StartData;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MazeData_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MazeData_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_MazeData;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_DeadEnd_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DeadEnd_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_DeadEnd;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MazeArea_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MazeArea_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_MazeArea;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeTable_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLFPMazeTable>();
	}
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_StartData_Inner = { "StartData", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPMazeStartData, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_StartData_MetaData[] = {
		{ "Category", "LFPMazeTable" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_StartData = { "StartData", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeTable, StartData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_StartData_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_StartData_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeData_Inner = { "MazeData", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPMazeData, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeData_MetaData[] = {
		{ "Category", "LFPMazeTable" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeData = { "MazeData", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeTable, MazeData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeData_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeData_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_DeadEnd_Inner = { "DeadEnd", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_DeadEnd_MetaData[] = {
		{ "Category", "LFPMazeTable" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_DeadEnd = { "DeadEnd", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeTable, DeadEnd), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_DeadEnd_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_DeadEnd_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeArea_Inner = { "MazeArea", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPMazeArea, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeArea_MetaData[] = {
		{ "Category", "LFPMazeTable" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeArea = { "MazeArea", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeTable, MazeArea), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeArea_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeArea_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPMazeTable_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_StartData_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_StartData,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeData_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeData,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_DeadEnd_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_DeadEnd,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeArea_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeArea,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
		nullptr,
		&NewStructOps,
		"LFPMazeTable",
		sizeof(FLFPMazeTable),
		alignof(FLFPMazeTable),
		Z_Construct_UScriptStruct_FLFPMazeTable_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLFPMazeTable()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLFPMazeTable_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LohFunctionPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LFPMazeTable"), sizeof(FLFPMazeTable), Get_Z_Construct_UScriptStruct_FLFPMazeTable_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLFPMazeTable_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLFPMazeTable_Hash() { return 141946911U; }
class UScriptStruct* FLFPMazeArea::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOHFUNCTIONPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FLFPMazeArea_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLFPMazeArea, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("LFPMazeArea"), sizeof(FLFPMazeArea), Get_Z_Construct_UScriptStruct_FLFPMazeArea_Hash());
	}
	return Singleton;
}
template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<FLFPMazeArea>()
{
	return FLFPMazeArea::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLFPMazeArea(FLFPMazeArea::StaticStruct, TEXT("/Script/LohFunctionPlugin"), TEXT("LFPMazeArea"), false, nullptr, nullptr);
static struct FScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLFPMazeArea
{
	FScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLFPMazeArea()
	{
		UScriptStruct::DeferCppStructOps<FLFPMazeArea>(FName(TEXT("LFPMazeArea")));
	}
} ScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLFPMazeArea;
	struct Z_Construct_UScriptStruct_FLFPMazeArea_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Cell_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Cell_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Cell;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeArea_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLFPMazeArea_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLFPMazeArea>();
	}
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPMazeArea_Statics::NewProp_Cell_Inner = { "Cell", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeArea_Statics::NewProp_Cell_MetaData[] = {
		{ "Category", "LFPMazeArea" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPMazeArea_Statics::NewProp_Cell = { "Cell", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeArea, Cell), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeArea_Statics::NewProp_Cell_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeArea_Statics::NewProp_Cell_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPMazeArea_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeArea_Statics::NewProp_Cell_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeArea_Statics::NewProp_Cell,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLFPMazeArea_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
		nullptr,
		&NewStructOps,
		"LFPMazeArea",
		sizeof(FLFPMazeArea),
		alignof(FLFPMazeArea),
		Z_Construct_UScriptStruct_FLFPMazeArea_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeArea_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeArea_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeArea_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLFPMazeArea()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLFPMazeArea_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LohFunctionPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LFPMazeArea"), sizeof(FLFPMazeArea), Get_Z_Construct_UScriptStruct_FLFPMazeArea_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLFPMazeArea_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLFPMazeArea_Hash() { return 713902846U; }
class UScriptStruct* FLFPMazeStartData::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOHFUNCTIONPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FLFPMazeStartData_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLFPMazeStartData, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("LFPMazeStartData"), sizeof(FLFPMazeStartData), Get_Z_Construct_UScriptStruct_FLFPMazeStartData_Hash());
	}
	return Singleton;
}
template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<FLFPMazeStartData>()
{
	return FLFPMazeStartData::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLFPMazeStartData(FLFPMazeStartData::StaticStruct, TEXT("/Script/LohFunctionPlugin"), TEXT("LFPMazeStartData"), false, nullptr, nullptr);
static struct FScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLFPMazeStartData
{
	FScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLFPMazeStartData()
	{
		UScriptStruct::DeferCppStructOps<FLFPMazeStartData>(FName(TEXT("LFPMazeStartData")));
	}
} ScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLFPMazeStartData;
	struct Z_Construct_UScriptStruct_FLFPMazeStartData_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GraphLocation_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_GraphLocation;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_OpenConnection_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OpenConnection_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_OpenConnection;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_IsBlock_MetaData[];
#endif
		static void NewProp_IsBlock_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_IsBlock;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLFPMazeStartData>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_GraphLocation_MetaData[] = {
		{ "Category", "LFPMazeStartData" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_GraphLocation = { "GraphLocation", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeStartData, GraphLocation), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_GraphLocation_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_GraphLocation_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_OpenConnection_Inner = { "OpenConnection", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_OpenConnection_MetaData[] = {
		{ "Category", "LFPMazeStartData" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_OpenConnection = { "OpenConnection", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeStartData, OpenConnection), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_OpenConnection_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_OpenConnection_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_IsBlock_MetaData[] = {
		{ "Category", "LFPMazeStartData" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_IsBlock_SetBit(void* Obj)
	{
		((FLFPMazeStartData*)Obj)->IsBlock = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_IsBlock = { "IsBlock", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FLFPMazeStartData), &Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_IsBlock_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_IsBlock_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_IsBlock_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_GraphLocation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_OpenConnection_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_OpenConnection,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_IsBlock,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
		nullptr,
		&NewStructOps,
		"LFPMazeStartData",
		sizeof(FLFPMazeStartData),
		alignof(FLFPMazeStartData),
		Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLFPMazeStartData()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLFPMazeStartData_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LohFunctionPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LFPMazeStartData"), sizeof(FLFPMazeStartData), Get_Z_Construct_UScriptStruct_FLFPMazeStartData_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLFPMazeStartData_Hash() { return 3031122482U; }
class UScriptStruct* FLFPMazeData::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOHFUNCTIONPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FLFPMazeData_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLFPMazeData, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("LFPMazeData"), sizeof(FLFPMazeData), Get_Z_Construct_UScriptStruct_FLFPMazeData_Hash());
	}
	return Singleton;
}
template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<FLFPMazeData>()
{
	return FLFPMazeData::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLFPMazeData(FLFPMazeData::StaticStruct, TEXT("/Script/LohFunctionPlugin"), TEXT("LFPMazeData"), false, nullptr, nullptr);
static struct FScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLFPMazeData
{
	FScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLFPMazeData()
	{
		UScriptStruct::DeferCppStructOps<FLFPMazeData>(FName(TEXT("LFPMazeData")));
	}
} ScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLFPMazeData;
	struct Z_Construct_UScriptStruct_FLFPMazeData_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_WalkCount_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_WalkCount;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ParentIndex_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ParentIndex;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AreaID_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_AreaID;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_OpenList_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OpenList_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_OpenList;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeData_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLFPMazeData>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_WalkCount_MetaData[] = {
		{ "Category", "LFPMazeData" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_WalkCount = { "WalkCount", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeData, WalkCount), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_WalkCount_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_WalkCount_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_ParentIndex_MetaData[] = {
		{ "Category", "LFPMazeData" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_ParentIndex = { "ParentIndex", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeData, ParentIndex), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_ParentIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_ParentIndex_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_AreaID_MetaData[] = {
		{ "Category", "LFPMazeData" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_AreaID = { "AreaID", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeData, AreaID), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_AreaID_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_AreaID_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_OpenList_Inner = { "OpenList", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_OpenList_MetaData[] = {
		{ "Category", "LFPMazeData" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_OpenList = { "OpenList", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeData, OpenList), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_OpenList_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_OpenList_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPMazeData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_WalkCount,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_ParentIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_AreaID,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_OpenList_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_OpenList,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLFPMazeData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
		nullptr,
		&NewStructOps,
		"LFPMazeData",
		sizeof(FLFPMazeData),
		alignof(FLFPMazeData),
		Z_Construct_UScriptStruct_FLFPMazeData_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeData_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeData_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLFPMazeData()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLFPMazeData_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LohFunctionPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LFPMazeData"), sizeof(FLFPMazeData), Get_Z_Construct_UScriptStruct_FLFPMazeData_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLFPMazeData_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLFPMazeData_Hash() { return 4165723562U; }
	DEFINE_FUNCTION(ULFPMazeLibrary::execGenerateMazeArea)
	{
		P_GET_STRUCT_REF(FLFPMazeTable,Z_Param_Out_MazeTable);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=ULFPMazeLibrary::GenerateMazeArea(Z_Param_Out_MazeTable);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPMazeLibrary::execRemoveMazeDeadEnd)
	{
		P_GET_STRUCT_REF(FLFPMazeTable,Z_Param_Out_MazeTable);
		P_GET_PROPERTY(FIntProperty,Z_Param_Amount);
		P_GET_STRUCT_REF(FRandomStream,Z_Param_Out_Seed);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=ULFPMazeLibrary::RemoveMazeDeadEnd(Z_Param_Out_MazeTable,Z_Param_Amount,Z_Param_Out_Seed);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPMazeLibrary::execGenerateMazeData)
	{
		P_GET_STRUCT_REF(FLFPMazeTable,Z_Param_Out_MazeTable);
		P_GET_STRUCT_REF(FRandomStream,Z_Param_Out_Seed);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=ULFPMazeLibrary::GenerateMazeData(Z_Param_Out_MazeTable,Z_Param_Out_Seed);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPMazeLibrary::execCreateMazeStartData)
	{
		P_GET_STRUCT(FIntVector,Z_Param_MazeSize);
		P_GET_TSET_REF(int32,Z_Param_Out_BlockID);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FLFPMazeTable*)Z_Param__Result=ULFPMazeLibrary::CreateMazeStartData(Z_Param_MazeSize,Z_Param_Out_BlockID);
		P_NATIVE_END;
	}
	void ULFPMazeLibrary::StaticRegisterNativesULFPMazeLibrary()
	{
		UClass* Class = ULFPMazeLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CreateMazeStartData", &ULFPMazeLibrary::execCreateMazeStartData },
			{ "GenerateMazeArea", &ULFPMazeLibrary::execGenerateMazeArea },
			{ "GenerateMazeData", &ULFPMazeLibrary::execGenerateMazeData },
			{ "RemoveMazeDeadEnd", &ULFPMazeLibrary::execRemoveMazeDeadEnd },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics
	{
		struct LFPMazeLibrary_eventCreateMazeStartData_Parms
		{
			FIntVector MazeSize;
			TSet<int32> BlockID;
			FLFPMazeTable ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MazeSize_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MazeSize;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_BlockID_ElementProp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BlockID_MetaData[];
#endif
		static const UE4CodeGen_Private::FSetPropertyParams NewProp_BlockID;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_MazeSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_MazeSize = { "MazeSize", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventCreateMazeStartData_Parms, MazeSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_MazeSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_MazeSize_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_BlockID_ElementProp = { "BlockID", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_BlockID_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FSetPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_BlockID = { "BlockID", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventCreateMazeStartData_Parms, BlockID), METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_BlockID_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_BlockID_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventCreateMazeStartData_Parms, ReturnValue), Z_Construct_UScriptStruct_FLFPMazeTable, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_MazeSize,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_BlockID_ElementProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_BlockID,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Maze" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPMazeLibrary, nullptr, "CreateMazeStartData", nullptr, nullptr, sizeof(LFPMazeLibrary_eventCreateMazeStartData_Parms), Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C42401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics
	{
		struct LFPMazeLibrary_eventGenerateMazeArea_Parms
		{
			FLFPMazeTable MazeTable;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MazeTable;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_MazeTable = { "MazeTable", nullptr, (EPropertyFlags)0x0010000008000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGenerateMazeArea_Parms, MazeTable), Z_Construct_UScriptStruct_FLFPMazeTable, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPMazeLibrary_eventGenerateMazeArea_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPMazeLibrary_eventGenerateMazeArea_Parms), &Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_MazeTable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Maze" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPMazeLibrary, nullptr, "GenerateMazeArea", nullptr, nullptr, sizeof(LFPMazeLibrary_eventGenerateMazeArea_Parms), Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04442401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics
	{
		struct LFPMazeLibrary_eventGenerateMazeData_Parms
		{
			FLFPMazeTable MazeTable;
			FRandomStream Seed;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MazeTable;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Seed_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Seed;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_MazeTable = { "MazeTable", nullptr, (EPropertyFlags)0x0010000008000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGenerateMazeData_Parms, MazeTable), Z_Construct_UScriptStruct_FLFPMazeTable, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_Seed_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_Seed = { "Seed", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGenerateMazeData_Parms, Seed), Z_Construct_UScriptStruct_FRandomStream, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_Seed_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_Seed_MetaData)) };
	void Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPMazeLibrary_eventGenerateMazeData_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPMazeLibrary_eventGenerateMazeData_Parms), &Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_MazeTable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_Seed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Maze" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPMazeLibrary, nullptr, "GenerateMazeData", nullptr, nullptr, sizeof(LFPMazeLibrary_eventGenerateMazeData_Parms), Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C42401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics
	{
		struct LFPMazeLibrary_eventRemoveMazeDeadEnd_Parms
		{
			FLFPMazeTable MazeTable;
			int32 Amount;
			FRandomStream Seed;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MazeTable;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Amount_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Amount;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Seed_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Seed;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_MazeTable = { "MazeTable", nullptr, (EPropertyFlags)0x0010000008000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventRemoveMazeDeadEnd_Parms, MazeTable), Z_Construct_UScriptStruct_FLFPMazeTable, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_Amount_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_Amount = { "Amount", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventRemoveMazeDeadEnd_Parms, Amount), METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_Amount_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_Amount_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_Seed_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_Seed = { "Seed", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventRemoveMazeDeadEnd_Parms, Seed), Z_Construct_UScriptStruct_FRandomStream, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_Seed_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_Seed_MetaData)) };
	void Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPMazeLibrary_eventRemoveMazeDeadEnd_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPMazeLibrary_eventRemoveMazeDeadEnd_Parms), &Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_MazeTable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_Amount,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_Seed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Maze" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPMazeLibrary, nullptr, "RemoveMazeDeadEnd", nullptr, nullptr, sizeof(LFPMazeLibrary_eventRemoveMazeDeadEnd_Parms), Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C42401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ULFPMazeLibrary_NoRegister()
	{
		return ULFPMazeLibrary::StaticClass();
	}
	struct Z_Construct_UClass_ULFPMazeLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULFPMazeLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ULFPMazeLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData, "CreateMazeStartData" }, // 2944273491
		{ &Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea, "GenerateMazeArea" }, // 1913663866
		{ &Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData, "GenerateMazeData" }, // 1197283529
		{ &Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd, "RemoveMazeDeadEnd" }, // 676199115
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPMazeLibrary_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Math/LFPMazeLibrary.h" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULFPMazeLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULFPMazeLibrary>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULFPMazeLibrary_Statics::ClassParams = {
		&ULFPMazeLibrary::StaticClass,
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
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_ULFPMazeLibrary_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPMazeLibrary_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULFPMazeLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULFPMazeLibrary_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULFPMazeLibrary, 776852041);
	template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<ULFPMazeLibrary>()
	{
		return ULFPMazeLibrary::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULFPMazeLibrary(Z_Construct_UClass_ULFPMazeLibrary, &ULFPMazeLibrary::StaticClass, TEXT("/Script/LohFunctionPlugin"), TEXT("ULFPMazeLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULFPMazeLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
