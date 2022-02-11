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
	LOHFUNCTIONPLUGIN_API UEnum* Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType();
	UPackage* Z_Construct_UPackage__Script_LohFunctionPlugin();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPMazeTable();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntVector();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPMazeStartData();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPMazeData();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPMazeLibrary_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPMazeLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntPoint();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRandomStream();
// End Cross Module References
	static UEnum* EMazeCellType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("EMazeCellType"));
		}
		return Singleton;
	}
	template<> LOHFUNCTIONPLUGIN_API UEnum* StaticEnum<EMazeCellType>()
	{
		return EMazeCellType_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EMazeCellType(EMazeCellType_StaticEnum, TEXT("/Script/LohFunctionPlugin"), TEXT("EMazeCellType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType_Hash() { return 754166857U; }
	UEnum* Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_LohFunctionPlugin();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EMazeCellType"), 0, Get_Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EMazeCellType::Maze_Open", (int64)EMazeCellType::Maze_Open },
				{ "EMazeCellType::Maze_Close", (int64)EMazeCellType::Maze_Close },
				{ "EMazeCellType::Maze_Room", (int64)EMazeCellType::Maze_Room },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "Maze_Close.DisplayName", "Close" },
				{ "Maze_Close.Name", "EMazeCellType::Maze_Close" },
				{ "Maze_Open.DisplayName", "Open" },
				{ "Maze_Open.Name", "EMazeCellType::Maze_Open" },
				{ "Maze_Room.DisplayName", "Room" },
				{ "Maze_Room.Name", "EMazeCellType::Maze_Room" },
				{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
				nullptr,
				"EMazeCellType",
				"EMazeCellType",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
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
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MazeSize_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MazeSize;
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
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_RoomSize_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RoomSize_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_RoomSize;
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
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeSize_MetaData[] = {
		{ "Category", "LFPMazeTable" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeSize = { "MazeSize", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeTable, MazeSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeSize_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_StartData_Inner = { "StartData", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPMazeStartData, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_StartData_MetaData[] = {
		{ "Category", "LFPMazeTable" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_StartData = { "StartData", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeTable, StartData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_StartData_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_StartData_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeData_Inner = { "MazeData", nullptr, (EPropertyFlags)0x0000000000020000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPMazeData, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeData_MetaData[] = {
		{ "Category", "LFPMazeTable" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeData = { "MazeData", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeTable, MazeData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeData_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeData_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_DeadEnd_Inner = { "DeadEnd", nullptr, (EPropertyFlags)0x0000000000020000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_DeadEnd_MetaData[] = {
		{ "Category", "LFPMazeTable" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_DeadEnd = { "DeadEnd", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeTable, DeadEnd), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_DeadEnd_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_DeadEnd_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_RoomSize_Inner = { "RoomSize", nullptr, (EPropertyFlags)0x0000000000020000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_RoomSize_MetaData[] = {
		{ "Category", "LFPMazeTable" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_RoomSize = { "RoomSize", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeTable, RoomSize), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_RoomSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_RoomSize_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPMazeTable_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeSize,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_StartData_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_StartData,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeData_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeData,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_DeadEnd_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_DeadEnd,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_RoomSize_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_RoomSize,
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
	uint32 Get_Z_Construct_UScriptStruct_FLFPMazeTable_Hash() { return 4010512229U; }
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
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_CellType_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CellType_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_CellType;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CellID_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_CellID;
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
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellType_MetaData[] = {
		{ "Category", "LFPMazeStartData" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellType = { "CellType", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeStartData, CellType), Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellType_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellType_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellID_MetaData[] = {
		{ "Category", "LFPMazeStartData" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellID = { "CellID", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeStartData, CellID), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellID_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellID_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_GraphLocation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_OpenConnection_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_OpenConnection,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellType_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellID,
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
	uint32 Get_Z_Construct_UScriptStruct_FLFPMazeStartData_Hash() { return 3353761067U; }
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
	uint32 Get_Z_Construct_UScriptStruct_FLFPMazeData_Hash() { return 3977096029U; }
	DEFINE_FUNCTION(ULFPMazeLibrary::execGetMazeCellNeighbourByType)
	{
		P_GET_STRUCT_REF(FLFPMazeTable,Z_Param_Out_MazeTable);
		P_GET_PROPERTY(FIntProperty,Z_Param_Index);
		P_GET_ENUM(EMazeCellType,Z_Param_Type);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<int32>*)Z_Param__Result=ULFPMazeLibrary::GetMazeCellNeighbourByType(Z_Param_Out_MazeTable,Z_Param_Index,EMazeCellType(Z_Param_Type));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPMazeLibrary::execSetMazeCellID)
	{
		P_GET_STRUCT_REF(FLFPMazeTable,Z_Param_Out_MazeTable);
		P_GET_TARRAY(int32,Z_Param_Indexs);
		P_GET_PROPERTY(FIntProperty,Z_Param_ID);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=ULFPMazeLibrary::SetMazeCellID(Z_Param_Out_MazeTable,Z_Param_Indexs,Z_Param_ID);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPMazeLibrary::execSetMazeCellType)
	{
		P_GET_STRUCT_REF(FLFPMazeTable,Z_Param_Out_MazeTable);
		P_GET_TARRAY(int32,Z_Param_Indexs);
		P_GET_ENUM(EMazeCellType,Z_Param_Type);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=ULFPMazeLibrary::SetMazeCellType(Z_Param_Out_MazeTable,Z_Param_Indexs,EMazeCellType(Z_Param_Type));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPMazeLibrary::execGenerateMazeArea)
	{
		P_GET_STRUCT_REF(FLFPMazeTable,Z_Param_Out_MazeTable);
		P_GET_STRUCT(FIntPoint,Z_Param_AreaSize);
		P_GET_STRUCT_REF(FRandomStream,Z_Param_Out_Seed);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=ULFPMazeLibrary::GenerateMazeArea(Z_Param_Out_MazeTable,Z_Param_AreaSize,Z_Param_Out_Seed);
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
		P_GET_TSET_REF(int32,Z_Param_Out_PreConnection);
		P_GET_STRUCT(FIntPoint,Z_Param_RoomExit);
		P_GET_STRUCT_REF(FRandomStream,Z_Param_Out_Seed);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=ULFPMazeLibrary::GenerateMazeData(Z_Param_Out_MazeTable,Z_Param_Out_PreConnection,Z_Param_RoomExit,Z_Param_Out_Seed);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPMazeLibrary::execCreateMazeStartData)
	{
		P_GET_STRUCT(FIntVector,Z_Param_MazeSize);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FLFPMazeTable*)Z_Param__Result=ULFPMazeLibrary::CreateMazeStartData(Z_Param_MazeSize);
		P_NATIVE_END;
	}
	void ULFPMazeLibrary::StaticRegisterNativesULFPMazeLibrary()
	{
		UClass* Class = ULFPMazeLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CreateMazeStartData", &ULFPMazeLibrary::execCreateMazeStartData },
			{ "GenerateMazeArea", &ULFPMazeLibrary::execGenerateMazeArea },
			{ "GenerateMazeData", &ULFPMazeLibrary::execGenerateMazeData },
			{ "GetMazeCellNeighbourByType", &ULFPMazeLibrary::execGetMazeCellNeighbourByType },
			{ "RemoveMazeDeadEnd", &ULFPMazeLibrary::execRemoveMazeDeadEnd },
			{ "SetMazeCellID", &ULFPMazeLibrary::execSetMazeCellID },
			{ "SetMazeCellType", &ULFPMazeLibrary::execSetMazeCellType },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics
	{
		struct LFPMazeLibrary_eventCreateMazeStartData_Parms
		{
			FIntVector MazeSize;
			FLFPMazeTable ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MazeSize_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MazeSize;
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
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventCreateMazeStartData_Parms, ReturnValue), Z_Construct_UScriptStruct_FLFPMazeTable, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_MazeSize,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Maze" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPMazeLibrary, nullptr, "CreateMazeStartData", nullptr, nullptr, sizeof(LFPMazeLibrary_eventCreateMazeStartData_Parms), Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04842401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::Function_MetaDataParams)) };
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
			FIntPoint AreaSize;
			FRandomStream Seed;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MazeTable;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AreaSize_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_AreaSize;
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
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_MazeTable = { "MazeTable", nullptr, (EPropertyFlags)0x0010000008000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGenerateMazeArea_Parms, MazeTable), Z_Construct_UScriptStruct_FLFPMazeTable, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_AreaSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_AreaSize = { "AreaSize", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGenerateMazeArea_Parms, AreaSize), Z_Construct_UScriptStruct_FIntPoint, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_AreaSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_AreaSize_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_Seed_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_Seed = { "Seed", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGenerateMazeArea_Parms, Seed), Z_Construct_UScriptStruct_FRandomStream, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_Seed_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_Seed_MetaData)) };
	void Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPMazeLibrary_eventGenerateMazeArea_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPMazeLibrary_eventGenerateMazeArea_Parms), &Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_MazeTable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_AreaSize,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_Seed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Maze" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPMazeLibrary, nullptr, "GenerateMazeArea", nullptr, nullptr, sizeof(LFPMazeLibrary_eventGenerateMazeArea_Parms), Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C42401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::Function_MetaDataParams)) };
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
			TSet<int32> PreConnection;
			FIntPoint RoomExit;
			FRandomStream Seed;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MazeTable;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_PreConnection_ElementProp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PreConnection_MetaData[];
#endif
		static const UE4CodeGen_Private::FSetPropertyParams NewProp_PreConnection;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RoomExit_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_RoomExit;
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
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_PreConnection_ElementProp = { "PreConnection", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_PreConnection_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FSetPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_PreConnection = { "PreConnection", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGenerateMazeData_Parms, PreConnection), METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_PreConnection_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_PreConnection_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_RoomExit_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_RoomExit = { "RoomExit", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGenerateMazeData_Parms, RoomExit), Z_Construct_UScriptStruct_FIntPoint, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_RoomExit_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_RoomExit_MetaData)) };
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
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_PreConnection_ElementProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_PreConnection,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_RoomExit,
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
	struct Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics
	{
		struct LFPMazeLibrary_eventGetMazeCellNeighbourByType_Parms
		{
			FLFPMazeTable MazeTable;
			int32 Index;
			EMazeCellType Type;
			TArray<int32> ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MazeTable_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MazeTable;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Index_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Index;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Type_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Type_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_Type;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ReturnValue_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_MazeTable_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_MazeTable = { "MazeTable", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGetMazeCellNeighbourByType_Parms, MazeTable), Z_Construct_UScriptStruct_FLFPMazeTable, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_MazeTable_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_MazeTable_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Index_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGetMazeCellNeighbourByType_Parms, Index), METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Index_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Index_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Type_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Type_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGetMazeCellNeighbourByType_Parms, Type), Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Type_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Type_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGetMazeCellNeighbourByType_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_MazeTable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Type_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Type,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Maze" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPMazeLibrary, nullptr, "GetMazeCellNeighbourByType", nullptr, nullptr, sizeof(LFPMazeLibrary_eventGetMazeCellNeighbourByType_Parms), Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14442401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::FuncParams);
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
	struct Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics
	{
		struct LFPMazeLibrary_eventSetMazeCellID_Parms
		{
			FLFPMazeTable MazeTable;
			TArray<int32> Indexs;
			int32 ID;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MazeTable;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Indexs_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Indexs_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Indexs;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ID_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ID;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_MazeTable = { "MazeTable", nullptr, (EPropertyFlags)0x0010000008000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventSetMazeCellID_Parms, MazeTable), Z_Construct_UScriptStruct_FLFPMazeTable, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_Indexs_Inner = { "Indexs", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_Indexs_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_Indexs = { "Indexs", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventSetMazeCellID_Parms, Indexs), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_Indexs_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_Indexs_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_ID_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_ID = { "ID", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventSetMazeCellID_Parms, ID), METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_ID_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_ID_MetaData)) };
	void Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPMazeLibrary_eventSetMazeCellID_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPMazeLibrary_eventSetMazeCellID_Parms), &Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_MazeTable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_Indexs_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_Indexs,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_ID,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Maze" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPMazeLibrary, nullptr, "SetMazeCellID", nullptr, nullptr, sizeof(LFPMazeLibrary_eventSetMazeCellID_Parms), Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04442401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics
	{
		struct LFPMazeLibrary_eventSetMazeCellType_Parms
		{
			FLFPMazeTable MazeTable;
			TArray<int32> Indexs;
			EMazeCellType Type;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MazeTable;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Indexs_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Indexs_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Indexs;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Type_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Type_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_Type;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_MazeTable = { "MazeTable", nullptr, (EPropertyFlags)0x0010000008000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventSetMazeCellType_Parms, MazeTable), Z_Construct_UScriptStruct_FLFPMazeTable, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Indexs_Inner = { "Indexs", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Indexs_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Indexs = { "Indexs", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventSetMazeCellType_Parms, Indexs), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Indexs_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Indexs_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Type_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Type_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventSetMazeCellType_Parms, Type), Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Type_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Type_MetaData)) };
	void Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPMazeLibrary_eventSetMazeCellType_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPMazeLibrary_eventSetMazeCellType_Parms), &Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_MazeTable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Indexs_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Indexs,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Type_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Type,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Maze" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPMazeLibrary, nullptr, "SetMazeCellType", nullptr, nullptr, sizeof(LFPMazeLibrary_eventSetMazeCellType_Parms), Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04442401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::FuncParams);
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
		{ &Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData, "CreateMazeStartData" }, // 2833974586
		{ &Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea, "GenerateMazeArea" }, // 1133400670
		{ &Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData, "GenerateMazeData" }, // 3429440127
		{ &Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType, "GetMazeCellNeighbourByType" }, // 4084929738
		{ &Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd, "RemoveMazeDeadEnd" }, // 676199115
		{ &Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID, "SetMazeCellID" }, // 2245063142
		{ &Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType, "SetMazeCellType" }, // 1741323170
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
	IMPLEMENT_CLASS(ULFPMazeLibrary, 3935836447);
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
