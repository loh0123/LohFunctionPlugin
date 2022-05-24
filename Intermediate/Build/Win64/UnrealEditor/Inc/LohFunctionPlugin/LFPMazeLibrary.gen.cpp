// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LohFunctionPlugin/Public/Math/LFPMazeLibrary.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLFPMazeLibrary() {}
// Cross Module References
	LOHFUNCTIONPLUGIN_API UEnum* Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType();
	UPackage* Z_Construct_UPackage__Script_LohFunctionPlugin();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPMazeData();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPMazeStartData();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntVector();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPMazeTable();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPMazeLibrary_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPMazeLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntPoint();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRandomStream();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EMazeCellType;
	static UEnum* EMazeCellType_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EMazeCellType.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EMazeCellType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("EMazeCellType"));
		}
		return Z_Registration_Info_UEnum_EMazeCellType.OuterSingleton;
	}
	template<> LOHFUNCTIONPLUGIN_API UEnum* StaticEnum<EMazeCellType>()
	{
		return EMazeCellType_StaticEnum();
	}
	struct Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType_Statics::Enumerators[] = {
		{ "EMazeCellType::Maze_Open", (int64)EMazeCellType::Maze_Open },
		{ "EMazeCellType::Maze_Close", (int64)EMazeCellType::Maze_Close },
		{ "EMazeCellType::Maze_Room", (int64)EMazeCellType::Maze_Room },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType_Statics::Enum_MetaDataParams[] = {
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
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
		nullptr,
		"EMazeCellType",
		"EMazeCellType",
		Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType()
	{
		if (!Z_Registration_Info_UEnum_EMazeCellType.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EMazeCellType.InnerSingleton, Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EMazeCellType.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_LFPMazeData;
class UScriptStruct* FLFPMazeData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_LFPMazeData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_LFPMazeData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLFPMazeData, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("LFPMazeData"));
	}
	return Z_Registration_Info_UScriptStruct_LFPMazeData.OuterSingleton;
}
template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<FLFPMazeData>()
{
	return FLFPMazeData::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FLFPMazeData_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_WalkCount_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_WalkCount;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ParentIndex_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_ParentIndex;
		static const UECodeGen_Private::FIntPropertyParams NewProp_OpenList_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OpenList_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_OpenList;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeData_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLFPMazeData>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_WalkCount_MetaData[] = {
		{ "Category", "LFPMazeData" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_WalkCount = { "WalkCount", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeData, WalkCount), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_WalkCount_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_WalkCount_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_ParentIndex_MetaData[] = {
		{ "Category", "LFPMazeData" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_ParentIndex = { "ParentIndex", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeData, ParentIndex), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_ParentIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_ParentIndex_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_OpenList_Inner = { "OpenList", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_OpenList_MetaData[] = {
		{ "Category", "LFPMazeData" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_OpenList = { "OpenList", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeData, OpenList), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_OpenList_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_OpenList_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPMazeData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_WalkCount,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_ParentIndex,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_OpenList_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewProp_OpenList,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLFPMazeData_Statics::ReturnStructParams = {
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
		if (!Z_Registration_Info_UScriptStruct_LFPMazeData.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_LFPMazeData.InnerSingleton, Z_Construct_UScriptStruct_FLFPMazeData_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_LFPMazeData.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_LFPMazeStartData;
class UScriptStruct* FLFPMazeStartData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_LFPMazeStartData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_LFPMazeStartData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLFPMazeStartData, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("LFPMazeStartData"));
	}
	return Z_Registration_Info_UScriptStruct_LFPMazeStartData.OuterSingleton;
}
template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<FLFPMazeStartData>()
{
	return FLFPMazeStartData::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FLFPMazeStartData_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GraphLocation_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_GraphLocation;
		static const UECodeGen_Private::FIntPropertyParams NewProp_OpenConnection_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OpenConnection_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_OpenConnection;
		static const UECodeGen_Private::FBytePropertyParams NewProp_CellType_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CellType_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_CellType;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CellID_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_CellID;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLFPMazeStartData>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_GraphLocation_MetaData[] = {
		{ "Category", "LFPMazeStartData" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_GraphLocation = { "GraphLocation", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeStartData, GraphLocation), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_GraphLocation_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_GraphLocation_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_OpenConnection_Inner = { "OpenConnection", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_OpenConnection_MetaData[] = {
		{ "Category", "LFPMazeStartData" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_OpenConnection = { "OpenConnection", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeStartData, OpenConnection), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_OpenConnection_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_OpenConnection_MetaData)) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellType_MetaData[] = {
		{ "Category", "LFPMazeStartData" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellType = { "CellType", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeStartData, CellType), Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellType_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellType_MetaData)) }; // 552270702
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellID_MetaData[] = {
		{ "Category", "LFPMazeStartData" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellID = { "CellID", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeStartData, CellID), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellID_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellID_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_GraphLocation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_OpenConnection_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_OpenConnection,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellType_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellType,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewProp_CellID,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::ReturnStructParams = {
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
		if (!Z_Registration_Info_UScriptStruct_LFPMazeStartData.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_LFPMazeStartData.InnerSingleton, Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_LFPMazeStartData.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_LFPMazeTable;
class UScriptStruct* FLFPMazeTable::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_LFPMazeTable.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_LFPMazeTable.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLFPMazeTable, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("LFPMazeTable"));
	}
	return Z_Registration_Info_UScriptStruct_LFPMazeTable.OuterSingleton;
}
template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<FLFPMazeTable>()
{
	return FLFPMazeTable::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FLFPMazeTable_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MazeSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_MazeSize;
		static const UECodeGen_Private::FStructPropertyParams NewProp_StartData_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_StartData_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_StartData;
		static const UECodeGen_Private::FStructPropertyParams NewProp_MazeData_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MazeData_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_MazeData;
		static const UECodeGen_Private::FIntPropertyParams NewProp_DeadEnd_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DeadEnd_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_DeadEnd;
		static const UECodeGen_Private::FStructPropertyParams NewProp_RoomSize_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RoomSize_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_RoomSize;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeTable_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLFPMazeTable>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeSize_MetaData[] = {
		{ "Category", "LFPMazeTable" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeSize = { "MazeSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeTable, MazeSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeSize_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_StartData_Inner = { "StartData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPMazeStartData, METADATA_PARAMS(nullptr, 0) }; // 3946774763
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_StartData_MetaData[] = {
		{ "Category", "LFPMazeTable" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_StartData = { "StartData", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeTable, StartData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_StartData_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_StartData_MetaData)) }; // 3946774763
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeData_Inner = { "MazeData", nullptr, (EPropertyFlags)0x0000000000020000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPMazeData, METADATA_PARAMS(nullptr, 0) }; // 2787218936
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeData_MetaData[] = {
		{ "Category", "LFPMazeTable" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeData = { "MazeData", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeTable, MazeData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeData_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeData_MetaData)) }; // 2787218936
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_DeadEnd_Inner = { "DeadEnd", nullptr, (EPropertyFlags)0x0000000000020000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_DeadEnd_MetaData[] = {
		{ "Category", "LFPMazeTable" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_DeadEnd = { "DeadEnd", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeTable, DeadEnd), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_DeadEnd_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_DeadEnd_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_RoomSize_Inner = { "RoomSize", nullptr, (EPropertyFlags)0x0000000000020000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_RoomSize_MetaData[] = {
		{ "Category", "LFPMazeTable" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_RoomSize = { "RoomSize", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPMazeTable, RoomSize), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_RoomSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_RoomSize_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPMazeTable_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_StartData_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_StartData,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeData_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_MazeData,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_DeadEnd_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_DeadEnd,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_RoomSize_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewProp_RoomSize,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLFPMazeTable_Statics::ReturnStructParams = {
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
		if (!Z_Registration_Info_UScriptStruct_LFPMazeTable.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_LFPMazeTable.InnerSingleton, Z_Construct_UScriptStruct_FLFPMazeTable_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_LFPMazeTable.InnerSingleton;
	}
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
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MazeSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_MazeSize;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_MazeSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_MazeSize = { "MazeSize", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventCreateMazeStartData_Parms, MazeSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_MazeSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_MazeSize_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventCreateMazeStartData_Parms, ReturnValue), Z_Construct_UScriptStruct_FLFPMazeTable, METADATA_PARAMS(nullptr, 0) }; // 1567876007
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_MazeSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Maze" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPMazeLibrary, nullptr, "CreateMazeStartData", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::LFPMazeLibrary_eventCreateMazeStartData_Parms), Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04842401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData_Statics::FuncParams);
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
		static const UECodeGen_Private::FStructPropertyParams NewProp_MazeTable;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AreaSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_AreaSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Seed_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Seed;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_MazeTable = { "MazeTable", nullptr, (EPropertyFlags)0x0010000008000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGenerateMazeArea_Parms, MazeTable), Z_Construct_UScriptStruct_FLFPMazeTable, METADATA_PARAMS(nullptr, 0) }; // 1567876007
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_AreaSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_AreaSize = { "AreaSize", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGenerateMazeArea_Parms, AreaSize), Z_Construct_UScriptStruct_FIntPoint, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_AreaSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_AreaSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_Seed_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_Seed = { "Seed", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGenerateMazeArea_Parms, Seed), Z_Construct_UScriptStruct_FRandomStream, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_Seed_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_Seed_MetaData)) };
	void Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPMazeLibrary_eventGenerateMazeArea_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPMazeLibrary_eventGenerateMazeArea_Parms), &Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_MazeTable,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_AreaSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_Seed,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Maze" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPMazeLibrary, nullptr, "GenerateMazeArea", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::LFPMazeLibrary_eventGenerateMazeArea_Parms), Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C42401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea_Statics::FuncParams);
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
		static const UECodeGen_Private::FStructPropertyParams NewProp_MazeTable;
		static const UECodeGen_Private::FIntPropertyParams NewProp_PreConnection_ElementProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PreConnection_MetaData[];
#endif
		static const UECodeGen_Private::FSetPropertyParams NewProp_PreConnection;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RoomExit_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_RoomExit;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Seed_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Seed;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_MazeTable = { "MazeTable", nullptr, (EPropertyFlags)0x0010000008000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGenerateMazeData_Parms, MazeTable), Z_Construct_UScriptStruct_FLFPMazeTable, METADATA_PARAMS(nullptr, 0) }; // 1567876007
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_PreConnection_ElementProp = { "PreConnection", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_PreConnection_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FSetPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_PreConnection = { "PreConnection", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGenerateMazeData_Parms, PreConnection), METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_PreConnection_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_PreConnection_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_RoomExit_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_RoomExit = { "RoomExit", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGenerateMazeData_Parms, RoomExit), Z_Construct_UScriptStruct_FIntPoint, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_RoomExit_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_RoomExit_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_Seed_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_Seed = { "Seed", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGenerateMazeData_Parms, Seed), Z_Construct_UScriptStruct_FRandomStream, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_Seed_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_Seed_MetaData)) };
	void Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPMazeLibrary_eventGenerateMazeData_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPMazeLibrary_eventGenerateMazeData_Parms), &Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_MazeTable,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_PreConnection_ElementProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_PreConnection,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_RoomExit,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_Seed,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Maze" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPMazeLibrary, nullptr, "GenerateMazeData", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::LFPMazeLibrary_eventGenerateMazeData_Parms), Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C42401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData_Statics::FuncParams);
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
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MazeTable_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_MazeTable;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Index_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Index;
		static const UECodeGen_Private::FBytePropertyParams NewProp_Type_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Type_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_Type;
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_MazeTable_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_MazeTable = { "MazeTable", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGetMazeCellNeighbourByType_Parms, MazeTable), Z_Construct_UScriptStruct_FLFPMazeTable, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_MazeTable_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_MazeTable_MetaData)) }; // 1567876007
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Index_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGetMazeCellNeighbourByType_Parms, Index), METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Index_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Index_MetaData)) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Type_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Type_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGetMazeCellNeighbourByType_Parms, Type), Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Type_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Type_MetaData)) }; // 552270702
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventGetMazeCellNeighbourByType_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_MazeTable,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Index,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Type_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_Type,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Maze" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPMazeLibrary, nullptr, "GetMazeCellNeighbourByType", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::LFPMazeLibrary_eventGetMazeCellNeighbourByType_Parms), Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14442401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType_Statics::FuncParams);
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
		static const UECodeGen_Private::FStructPropertyParams NewProp_MazeTable;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Amount_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Amount;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Seed_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Seed;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_MazeTable = { "MazeTable", nullptr, (EPropertyFlags)0x0010000008000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventRemoveMazeDeadEnd_Parms, MazeTable), Z_Construct_UScriptStruct_FLFPMazeTable, METADATA_PARAMS(nullptr, 0) }; // 1567876007
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_Amount_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_Amount = { "Amount", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventRemoveMazeDeadEnd_Parms, Amount), METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_Amount_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_Amount_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_Seed_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_Seed = { "Seed", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventRemoveMazeDeadEnd_Parms, Seed), Z_Construct_UScriptStruct_FRandomStream, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_Seed_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_Seed_MetaData)) };
	void Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPMazeLibrary_eventRemoveMazeDeadEnd_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPMazeLibrary_eventRemoveMazeDeadEnd_Parms), &Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_MazeTable,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_Amount,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_Seed,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Maze" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPMazeLibrary, nullptr, "RemoveMazeDeadEnd", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::LFPMazeLibrary_eventRemoveMazeDeadEnd_Parms), Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C42401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd_Statics::FuncParams);
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
		static const UECodeGen_Private::FStructPropertyParams NewProp_MazeTable;
		static const UECodeGen_Private::FIntPropertyParams NewProp_Indexs_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Indexs_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Indexs;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ID_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_ID;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_MazeTable = { "MazeTable", nullptr, (EPropertyFlags)0x0010000008000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventSetMazeCellID_Parms, MazeTable), Z_Construct_UScriptStruct_FLFPMazeTable, METADATA_PARAMS(nullptr, 0) }; // 1567876007
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_Indexs_Inner = { "Indexs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_Indexs_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_Indexs = { "Indexs", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventSetMazeCellID_Parms, Indexs), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_Indexs_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_Indexs_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_ID_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_ID = { "ID", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventSetMazeCellID_Parms, ID), METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_ID_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_ID_MetaData)) };
	void Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPMazeLibrary_eventSetMazeCellID_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPMazeLibrary_eventSetMazeCellID_Parms), &Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_MazeTable,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_Indexs_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_Indexs,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_ID,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Maze" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPMazeLibrary, nullptr, "SetMazeCellID", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::LFPMazeLibrary_eventSetMazeCellID_Parms), Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04442401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID_Statics::FuncParams);
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
		static const UECodeGen_Private::FStructPropertyParams NewProp_MazeTable;
		static const UECodeGen_Private::FIntPropertyParams NewProp_Indexs_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Indexs_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Indexs;
		static const UECodeGen_Private::FBytePropertyParams NewProp_Type_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Type_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_Type;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_MazeTable = { "MazeTable", nullptr, (EPropertyFlags)0x0010000008000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventSetMazeCellType_Parms, MazeTable), Z_Construct_UScriptStruct_FLFPMazeTable, METADATA_PARAMS(nullptr, 0) }; // 1567876007
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Indexs_Inner = { "Indexs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Indexs_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Indexs = { "Indexs", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventSetMazeCellType_Parms, Indexs), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Indexs_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Indexs_MetaData)) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Type_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Type_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPMazeLibrary_eventSetMazeCellType_Parms, Type), Z_Construct_UEnum_LohFunctionPlugin_EMazeCellType, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Type_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Type_MetaData)) }; // 552270702
	void Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPMazeLibrary_eventSetMazeCellType_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPMazeLibrary_eventSetMazeCellType_Parms), &Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_MazeTable,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Indexs_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Indexs,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Type_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_Type,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Maze" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPMazeLibrary, nullptr, "SetMazeCellType", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::LFPMazeLibrary_eventSetMazeCellType_Parms), Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04442401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ULFPMazeLibrary);
	UClass* Z_Construct_UClass_ULFPMazeLibrary_NoRegister()
	{
		return ULFPMazeLibrary::StaticClass();
	}
	struct Z_Construct_UClass_ULFPMazeLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULFPMazeLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ULFPMazeLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULFPMazeLibrary_CreateMazeStartData, "CreateMazeStartData" }, // 1532781740
		{ &Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeArea, "GenerateMazeArea" }, // 891124736
		{ &Z_Construct_UFunction_ULFPMazeLibrary_GenerateMazeData, "GenerateMazeData" }, // 52331679
		{ &Z_Construct_UFunction_ULFPMazeLibrary_GetMazeCellNeighbourByType, "GetMazeCellNeighbourByType" }, // 2672038666
		{ &Z_Construct_UFunction_ULFPMazeLibrary_RemoveMazeDeadEnd, "RemoveMazeDeadEnd" }, // 1128761888
		{ &Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellID, "SetMazeCellID" }, // 2538619433
		{ &Z_Construct_UFunction_ULFPMazeLibrary_SetMazeCellType, "SetMazeCellType" }, // 3481412191
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPMazeLibrary_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Math/LFPMazeLibrary.h" },
		{ "ModuleRelativePath", "Public/Math/LFPMazeLibrary.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULFPMazeLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULFPMazeLibrary>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ULFPMazeLibrary_Statics::ClassParams = {
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
		if (!Z_Registration_Info_UClass_ULFPMazeLibrary.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULFPMazeLibrary.OuterSingleton, Z_Construct_UClass_ULFPMazeLibrary_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ULFPMazeLibrary.OuterSingleton;
	}
	template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<ULFPMazeLibrary>()
	{
		return ULFPMazeLibrary::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULFPMazeLibrary);
	struct Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_Statics::EnumInfo[] = {
		{ EMazeCellType_StaticEnum, TEXT("EMazeCellType"), &Z_Registration_Info_UEnum_EMazeCellType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 552270702U) },
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_Statics::ScriptStructInfo[] = {
		{ FLFPMazeData::StaticStruct, Z_Construct_UScriptStruct_FLFPMazeData_Statics::NewStructOps, TEXT("LFPMazeData"), &Z_Registration_Info_UScriptStruct_LFPMazeData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLFPMazeData), 2787218936U) },
		{ FLFPMazeStartData::StaticStruct, Z_Construct_UScriptStruct_FLFPMazeStartData_Statics::NewStructOps, TEXT("LFPMazeStartData"), &Z_Registration_Info_UScriptStruct_LFPMazeStartData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLFPMazeStartData), 3946774763U) },
		{ FLFPMazeTable::StaticStruct, Z_Construct_UScriptStruct_FLFPMazeTable_Statics::NewStructOps, TEXT("LFPMazeTable"), &Z_Registration_Info_UScriptStruct_LFPMazeTable, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLFPMazeTable), 1567876007U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ULFPMazeLibrary, ULFPMazeLibrary::StaticClass, TEXT("ULFPMazeLibrary"), &Z_Registration_Info_UClass_ULFPMazeLibrary, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULFPMazeLibrary), 2823400573U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_4248356023(TEXT("/Script/LohFunctionPlugin"),
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_Statics::ClassInfo),
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_Statics::ScriptStructInfo),
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
