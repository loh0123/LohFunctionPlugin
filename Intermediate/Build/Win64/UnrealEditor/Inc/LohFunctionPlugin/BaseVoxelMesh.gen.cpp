// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LohFunctionPlugin/Public/Mesh/BaseVoxelMesh.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBaseVoxelMesh() {}
// Cross Module References
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData();
	UPackage* Z_Construct_UPackage__Script_LohFunctionPlugin();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntVector();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2f();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelGridData();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2D();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelTriangleData();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelMeshData();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_UBaseVoxelMesh_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_UBaseVoxelMesh();
	GEOMETRYFRAMEWORK_API UClass* Z_Construct_UClass_UDynamicMesh();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_LFPVoxelTriangleUpdateData;
class UScriptStruct* FLFPVoxelTriangleUpdateData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_LFPVoxelTriangleUpdateData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_LFPVoxelTriangleUpdateData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("LFPVoxelTriangleUpdateData"));
	}
	return Z_Registration_Info_UScriptStruct_LFPVoxelTriangleUpdateData.OuterSingleton;
}
template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<FLFPVoxelTriangleUpdateData>()
{
	return FLFPVoxelTriangleUpdateData::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridIndex_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_GridIndex;
		static const UECodeGen_Private::FStructPropertyParams NewProp_NewTriangleList_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NewTriangleList_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_NewTriangleList;
		static const UECodeGen_Private::FIntPropertyParams NewProp_NewTriangleGroupList_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NewTriangleGroupList_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_NewTriangleGroupList;
		static const UECodeGen_Private::FStructPropertyParams NewProp_NewUVList_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NewUVList_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_NewUVList;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLFPVoxelTriangleUpdateData>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_GridIndex_MetaData[] = {
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_GridIndex = { "GridIndex", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelTriangleUpdateData, GridIndex), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_GridIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_GridIndex_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewTriangleList_Inner = { "NewTriangleList", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewTriangleList_MetaData[] = {
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewTriangleList = { "NewTriangleList", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelTriangleUpdateData, NewTriangleList), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewTriangleList_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewTriangleList_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewTriangleGroupList_Inner = { "NewTriangleGroupList", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewTriangleGroupList_MetaData[] = {
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewTriangleGroupList = { "NewTriangleGroupList", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelTriangleUpdateData, NewTriangleGroupList), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewTriangleGroupList_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewTriangleGroupList_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewUVList_Inner = { "NewUVList", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FVector2f, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewUVList_MetaData[] = {
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewUVList = { "NewUVList", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelTriangleUpdateData, NewUVList), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewUVList_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewUVList_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_GridIndex,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewTriangleList_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewTriangleList,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewTriangleGroupList_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewTriangleGroupList,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewUVList_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewUVList,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
		nullptr,
		&NewStructOps,
		"LFPVoxelTriangleUpdateData",
		sizeof(FLFPVoxelTriangleUpdateData),
		alignof(FLFPVoxelTriangleUpdateData),
		Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData()
	{
		if (!Z_Registration_Info_UScriptStruct_LFPVoxelTriangleUpdateData.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_LFPVoxelTriangleUpdateData.InnerSingleton, Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_LFPVoxelTriangleUpdateData.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_LFPVoxelGridData;
class UScriptStruct* FLFPVoxelGridData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_LFPVoxelGridData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_LFPVoxelGridData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLFPVoxelGridData, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("LFPVoxelGridData"));
	}
	return Z_Registration_Info_UScriptStruct_LFPVoxelGridData.OuterSingleton;
}
template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<FLFPVoxelGridData>()
{
	return FLFPVoxelGridData::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BlockName_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_BlockName;
		static const UECodeGen_Private::FStructPropertyParams NewProp_CustomData_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CustomData_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_CustomData;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaterialID_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_MaterialID;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLFPVoxelGridData>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::NewProp_BlockName_MetaData[] = {
		{ "Category", "LFPVoxelGridData" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::NewProp_BlockName = { "BlockName", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelGridData, BlockName), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::NewProp_BlockName_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::NewProp_BlockName_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::NewProp_CustomData_Inner = { "CustomData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::NewProp_CustomData_MetaData[] = {
		{ "Category", "LFPVoxelGridData" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::NewProp_CustomData = { "CustomData", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelGridData, CustomData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::NewProp_CustomData_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::NewProp_CustomData_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::NewProp_MaterialID_MetaData[] = {
		{ "Category", "LFPVoxelGridData" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::NewProp_MaterialID = { "MaterialID", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelGridData, MaterialID), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::NewProp_MaterialID_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::NewProp_MaterialID_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::NewProp_BlockName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::NewProp_CustomData_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::NewProp_CustomData,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::NewProp_MaterialID,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
		nullptr,
		&NewStructOps,
		"LFPVoxelGridData",
		sizeof(FLFPVoxelGridData),
		alignof(FLFPVoxelGridData),
		Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelGridData()
	{
		if (!Z_Registration_Info_UScriptStruct_LFPVoxelGridData.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_LFPVoxelGridData.InnerSingleton, Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_LFPVoxelGridData.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_LFPVoxelTriangleData;
class UScriptStruct* FLFPVoxelTriangleData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_LFPVoxelTriangleData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_LFPVoxelTriangleData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLFPVoxelTriangleData, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("LFPVoxelTriangleData"));
	}
	return Z_Registration_Info_UScriptStruct_LFPVoxelTriangleData.OuterSingleton;
}
template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<FLFPVoxelTriangleData>()
{
	return FLFPVoxelTriangleData::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FLFPVoxelTriangleData_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UECodeGen_Private::FIntPropertyParams NewProp_MeshTriangleIndex_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MeshTriangleIndex_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_MeshTriangleIndex;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelTriangleData_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLFPVoxelTriangleData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLFPVoxelTriangleData>();
	}
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPVoxelTriangleData_Statics::NewProp_MeshTriangleIndex_Inner = { "MeshTriangleIndex", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelTriangleData_Statics::NewProp_MeshTriangleIndex_MetaData[] = {
		{ "Category", "LFPVoxelTriangleData" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPVoxelTriangleData_Statics::NewProp_MeshTriangleIndex = { "MeshTriangleIndex", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelTriangleData, MeshTriangleIndex), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelTriangleData_Statics::NewProp_MeshTriangleIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelTriangleData_Statics::NewProp_MeshTriangleIndex_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPVoxelTriangleData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelTriangleData_Statics::NewProp_MeshTriangleIndex_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelTriangleData_Statics::NewProp_MeshTriangleIndex,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLFPVoxelTriangleData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
		nullptr,
		&NewStructOps,
		"LFPVoxelTriangleData",
		sizeof(FLFPVoxelTriangleData),
		alignof(FLFPVoxelTriangleData),
		Z_Construct_UScriptStruct_FLFPVoxelTriangleData_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelTriangleData_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelTriangleData_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelTriangleData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelTriangleData()
	{
		if (!Z_Registration_Info_UScriptStruct_LFPVoxelTriangleData.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_LFPVoxelTriangleData.InnerSingleton, Z_Construct_UScriptStruct_FLFPVoxelTriangleData_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_LFPVoxelTriangleData.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_LFPVoxelMeshData;
class UScriptStruct* FLFPVoxelMeshData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_LFPVoxelMeshData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_LFPVoxelMeshData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLFPVoxelMeshData, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("LFPVoxelMeshData"));
	}
	return Z_Registration_Info_UScriptStruct_LFPVoxelMeshData.OuterSingleton;
}
template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<FLFPVoxelMeshData>()
{
	return FLFPVoxelMeshData::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridData_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridData_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_GridData;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MeshSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_MeshSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridSize;
		static const UECodeGen_Private::FNamePropertyParams NewProp_RenderNameList_ElementProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RenderNameList_MetaData[];
#endif
		static const UECodeGen_Private::FSetPropertyParams NewProp_RenderNameList;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VertexSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_VertexSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaxIndex_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_MaxIndex;
		static const UECodeGen_Private::FStructPropertyParams NewProp_TriangleDataList_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TriangleDataList_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_TriangleDataList;
		static const UECodeGen_Private::FIntPropertyParams NewProp_TriangleUpdateList_ElementProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TriangleUpdateList_MetaData[];
#endif
		static const UECodeGen_Private::FSetPropertyParams NewProp_TriangleUpdateList;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLFPVoxelMeshData>();
	}
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_GridData_Inner = { "GridData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPVoxelGridData, METADATA_PARAMS(nullptr, 0) }; // 4094411625
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_GridData_MetaData[] = {
		{ "Category", "LFPVoxelData" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_GridData = { "GridData", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelMeshData, GridData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_GridData_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_GridData_MetaData)) }; // 4094411625
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_MeshSize_MetaData[] = {
		{ "Category", "LFPVoxelData | Setting" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_MeshSize = { "MeshSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelMeshData, MeshSize), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_MeshSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_MeshSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_GridSize_MetaData[] = {
		{ "Category", "LFPVoxelData | Setting" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_GridSize = { "GridSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelMeshData, GridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_GridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_GridSize_MetaData)) };
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_RenderNameList_ElementProp = { "RenderNameList", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_RenderNameList_MetaData[] = {
		{ "Category", "LFPVoxelData | Setting" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FSetPropertyParams Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_RenderNameList = { "RenderNameList", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelMeshData, RenderNameList), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_RenderNameList_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_RenderNameList_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_VertexSize_MetaData[] = {
		{ "Category", "LFPVoxelData | Cache" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_VertexSize = { "VertexSize", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelMeshData, VertexSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_VertexSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_VertexSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_MaxIndex_MetaData[] = {
		{ "Category", "LFPVoxelData | Cache" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_MaxIndex = { "MaxIndex", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelMeshData, MaxIndex), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_MaxIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_MaxIndex_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_TriangleDataList_Inner = { "TriangleDataList", nullptr, (EPropertyFlags)0x0000000000020000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPVoxelTriangleData, METADATA_PARAMS(nullptr, 0) }; // 2785686119
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_TriangleDataList_MetaData[] = {
		{ "Category", "LFPVoxelData | Cache" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_TriangleDataList = { "TriangleDataList", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelMeshData, TriangleDataList), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_TriangleDataList_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_TriangleDataList_MetaData)) }; // 2785686119
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_TriangleUpdateList_ElementProp = { "TriangleUpdateList", nullptr, (EPropertyFlags)0x0000000000020001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_TriangleUpdateList_MetaData[] = {
		{ "Category", "LFPVoxelData | Cache" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FSetPropertyParams Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_TriangleUpdateList = { "TriangleUpdateList", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelMeshData, TriangleUpdateList), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_TriangleUpdateList_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_TriangleUpdateList_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_GridData_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_GridData,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_MeshSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_GridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_RenderNameList_ElementProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_RenderNameList,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_VertexSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_MaxIndex,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_TriangleDataList_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_TriangleDataList,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_TriangleUpdateList_ElementProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewProp_TriangleUpdateList,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
		nullptr,
		&NewStructOps,
		"LFPVoxelMeshData",
		sizeof(FLFPVoxelMeshData),
		alignof(FLFPVoxelMeshData),
		Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelMeshData()
	{
		if (!Z_Registration_Info_UScriptStruct_LFPVoxelMeshData.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_LFPVoxelMeshData.InnerSingleton, Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_LFPVoxelMeshData.InnerSingleton;
	}
	DEFINE_FUNCTION(UBaseVoxelMesh::execIsBlockNeedRender)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_GridIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->IsBlockNeedRender(Z_Param_GridIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBaseVoxelMesh::execIsBlockFaceVisible)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_FromGridIndex);
		P_GET_PROPERTY(FIntProperty,Z_Param_ToGridIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->IsBlockFaceVisible(Z_Param_FromGridIndex,Z_Param_ToGridIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBaseVoxelMesh::execFindBlockVertices)
	{
		P_GET_STRUCT(FIntVector,Z_Param_GridLocation);
		P_GET_TARRAY_REF(int32,Z_Param_Out_VerticesIndexList);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->FindBlockVertices(Z_Param_GridLocation,Z_Param_Out_VerticesIndexList);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBaseVoxelMesh::execFindBlockNeighbour)
	{
		P_GET_STRUCT(FIntVector,Z_Param_GridLocation);
		P_GET_TARRAY_REF(int32,Z_Param_Out_NeighbourIndexList);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->FindBlockNeighbour(Z_Param_GridLocation,Z_Param_Out_NeighbourIndexList);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBaseVoxelMesh::execMarkTrianglesDataForUpdate)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_GridIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->MarkTrianglesDataForUpdate(Z_Param_GridIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBaseVoxelMesh::execUpdateTriangles)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->UpdateTriangles();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBaseVoxelMesh::execUpdateVertices)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->UpdateVertices();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBaseVoxelMesh::execUpdateMesh)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->UpdateMesh();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBaseVoxelMesh::execSetupMesh)
	{
		P_GET_STRUCT(FVector,Z_Param_MeshSize);
		P_GET_STRUCT(FIntVector,Z_Param_GridSize);
		P_GET_TSET_REF(FName,Z_Param_Out_RenderNameList);
		P_GET_TARRAY_REF(FLFPVoxelGridData,Z_Param_Out_GridData);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetupMesh(Z_Param_MeshSize,Z_Param_GridSize,Z_Param_Out_RenderNameList,Z_Param_Out_GridData);
		P_NATIVE_END;
	}
	void UBaseVoxelMesh::StaticRegisterNativesUBaseVoxelMesh()
	{
		UClass* Class = UBaseVoxelMesh::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "FindBlockNeighbour", &UBaseVoxelMesh::execFindBlockNeighbour },
			{ "FindBlockVertices", &UBaseVoxelMesh::execFindBlockVertices },
			{ "IsBlockFaceVisible", &UBaseVoxelMesh::execIsBlockFaceVisible },
			{ "IsBlockNeedRender", &UBaseVoxelMesh::execIsBlockNeedRender },
			{ "MarkTrianglesDataForUpdate", &UBaseVoxelMesh::execMarkTrianglesDataForUpdate },
			{ "SetupMesh", &UBaseVoxelMesh::execSetupMesh },
			{ "UpdateMesh", &UBaseVoxelMesh::execUpdateMesh },
			{ "UpdateTriangles", &UBaseVoxelMesh::execUpdateTriangles },
			{ "UpdateVertices", &UBaseVoxelMesh::execUpdateVertices },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UBaseVoxelMesh_FindBlockNeighbour_Statics
	{
		struct BaseVoxelMesh_eventFindBlockNeighbour_Parms
		{
			FIntVector GridLocation;
			TArray<int32> NeighbourIndexList;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridLocation_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridLocation;
		static const UECodeGen_Private::FIntPropertyParams NewProp_NeighbourIndexList_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_NeighbourIndexList;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelMesh_FindBlockNeighbour_Statics::NewProp_GridLocation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBaseVoxelMesh_FindBlockNeighbour_Statics::NewProp_GridLocation = { "GridLocation", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseVoxelMesh_eventFindBlockNeighbour_Parms, GridLocation), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelMesh_FindBlockNeighbour_Statics::NewProp_GridLocation_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_FindBlockNeighbour_Statics::NewProp_GridLocation_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UBaseVoxelMesh_FindBlockNeighbour_Statics::NewProp_NeighbourIndexList_Inner = { "NeighbourIndexList", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBaseVoxelMesh_FindBlockNeighbour_Statics::NewProp_NeighbourIndexList = { "NeighbourIndexList", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseVoxelMesh_eventFindBlockNeighbour_Parms, NeighbourIndexList), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBaseVoxelMesh_FindBlockNeighbour_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelMesh_FindBlockNeighbour_Statics::NewProp_GridLocation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelMesh_FindBlockNeighbour_Statics::NewProp_NeighbourIndexList_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelMesh_FindBlockNeighbour_Statics::NewProp_NeighbourIndexList,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelMesh_FindBlockNeighbour_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseVoxelMesh_FindBlockNeighbour_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseVoxelMesh, nullptr, "FindBlockNeighbour", nullptr, nullptr, sizeof(Z_Construct_UFunction_UBaseVoxelMesh_FindBlockNeighbour_Statics::BaseVoxelMesh_eventFindBlockNeighbour_Parms), Z_Construct_UFunction_UBaseVoxelMesh_FindBlockNeighbour_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_FindBlockNeighbour_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00C80401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelMesh_FindBlockNeighbour_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_FindBlockNeighbour_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBaseVoxelMesh_FindBlockNeighbour()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBaseVoxelMesh_FindBlockNeighbour_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBaseVoxelMesh_FindBlockVertices_Statics
	{
		struct BaseVoxelMesh_eventFindBlockVertices_Parms
		{
			FIntVector GridLocation;
			TArray<int32> VerticesIndexList;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridLocation_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridLocation;
		static const UECodeGen_Private::FIntPropertyParams NewProp_VerticesIndexList_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_VerticesIndexList;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelMesh_FindBlockVertices_Statics::NewProp_GridLocation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBaseVoxelMesh_FindBlockVertices_Statics::NewProp_GridLocation = { "GridLocation", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseVoxelMesh_eventFindBlockVertices_Parms, GridLocation), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelMesh_FindBlockVertices_Statics::NewProp_GridLocation_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_FindBlockVertices_Statics::NewProp_GridLocation_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UBaseVoxelMesh_FindBlockVertices_Statics::NewProp_VerticesIndexList_Inner = { "VerticesIndexList", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBaseVoxelMesh_FindBlockVertices_Statics::NewProp_VerticesIndexList = { "VerticesIndexList", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseVoxelMesh_eventFindBlockVertices_Parms, VerticesIndexList), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBaseVoxelMesh_FindBlockVertices_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelMesh_FindBlockVertices_Statics::NewProp_GridLocation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelMesh_FindBlockVertices_Statics::NewProp_VerticesIndexList_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelMesh_FindBlockVertices_Statics::NewProp_VerticesIndexList,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelMesh_FindBlockVertices_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// Override This\n" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
		{ "ToolTip", "Override This" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseVoxelMesh_FindBlockVertices_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseVoxelMesh, nullptr, "FindBlockVertices", nullptr, nullptr, sizeof(Z_Construct_UFunction_UBaseVoxelMesh_FindBlockVertices_Statics::BaseVoxelMesh_eventFindBlockVertices_Parms), Z_Construct_UFunction_UBaseVoxelMesh_FindBlockVertices_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_FindBlockVertices_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00C80401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelMesh_FindBlockVertices_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_FindBlockVertices_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBaseVoxelMesh_FindBlockVertices()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBaseVoxelMesh_FindBlockVertices_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics
	{
		struct BaseVoxelMesh_eventIsBlockFaceVisible_Parms
		{
			int32 FromGridIndex;
			int32 ToGridIndex;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FromGridIndex_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_FromGridIndex;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ToGridIndex_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_ToGridIndex;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::NewProp_FromGridIndex_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::NewProp_FromGridIndex = { "FromGridIndex", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseVoxelMesh_eventIsBlockFaceVisible_Parms, FromGridIndex), METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::NewProp_FromGridIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::NewProp_FromGridIndex_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::NewProp_ToGridIndex_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::NewProp_ToGridIndex = { "ToGridIndex", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseVoxelMesh_eventIsBlockFaceVisible_Parms, ToGridIndex), METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::NewProp_ToGridIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::NewProp_ToGridIndex_MetaData)) };
	void Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((BaseVoxelMesh_eventIsBlockFaceVisible_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(BaseVoxelMesh_eventIsBlockFaceVisible_Parms), &Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::NewProp_FromGridIndex,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::NewProp_ToGridIndex,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// Override This\n" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
		{ "ToolTip", "Override This" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseVoxelMesh, nullptr, "IsBlockFaceVisible", nullptr, nullptr, sizeof(Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::BaseVoxelMesh_eventIsBlockFaceVisible_Parms), Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x40080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBaseVoxelMesh_IsBlockNeedRender_Statics
	{
		struct BaseVoxelMesh_eventIsBlockNeedRender_Parms
		{
			int32 GridIndex;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridIndex_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_GridIndex;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelMesh_IsBlockNeedRender_Statics::NewProp_GridIndex_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UBaseVoxelMesh_IsBlockNeedRender_Statics::NewProp_GridIndex = { "GridIndex", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseVoxelMesh_eventIsBlockNeedRender_Parms, GridIndex), METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelMesh_IsBlockNeedRender_Statics::NewProp_GridIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_IsBlockNeedRender_Statics::NewProp_GridIndex_MetaData)) };
	void Z_Construct_UFunction_UBaseVoxelMesh_IsBlockNeedRender_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((BaseVoxelMesh_eventIsBlockNeedRender_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UBaseVoxelMesh_IsBlockNeedRender_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(BaseVoxelMesh_eventIsBlockNeedRender_Parms), &Z_Construct_UFunction_UBaseVoxelMesh_IsBlockNeedRender_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBaseVoxelMesh_IsBlockNeedRender_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelMesh_IsBlockNeedRender_Statics::NewProp_GridIndex,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelMesh_IsBlockNeedRender_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelMesh_IsBlockNeedRender_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// Override This\n" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
		{ "ToolTip", "Override This" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseVoxelMesh_IsBlockNeedRender_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseVoxelMesh, nullptr, "IsBlockNeedRender", nullptr, nullptr, sizeof(Z_Construct_UFunction_UBaseVoxelMesh_IsBlockNeedRender_Statics::BaseVoxelMesh_eventIsBlockNeedRender_Parms), Z_Construct_UFunction_UBaseVoxelMesh_IsBlockNeedRender_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_IsBlockNeedRender_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x40080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelMesh_IsBlockNeedRender_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_IsBlockNeedRender_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBaseVoxelMesh_IsBlockNeedRender()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBaseVoxelMesh_IsBlockNeedRender_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBaseVoxelMesh_MarkTrianglesDataForUpdate_Statics
	{
		struct BaseVoxelMesh_eventMarkTrianglesDataForUpdate_Parms
		{
			int32 GridIndex;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridIndex_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_GridIndex;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelMesh_MarkTrianglesDataForUpdate_Statics::NewProp_GridIndex_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UBaseVoxelMesh_MarkTrianglesDataForUpdate_Statics::NewProp_GridIndex = { "GridIndex", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseVoxelMesh_eventMarkTrianglesDataForUpdate_Parms, GridIndex), METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelMesh_MarkTrianglesDataForUpdate_Statics::NewProp_GridIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_MarkTrianglesDataForUpdate_Statics::NewProp_GridIndex_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBaseVoxelMesh_MarkTrianglesDataForUpdate_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelMesh_MarkTrianglesDataForUpdate_Statics::NewProp_GridIndex,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelMesh_MarkTrianglesDataForUpdate_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// Override This\n" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
		{ "ToolTip", "Override This" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseVoxelMesh_MarkTrianglesDataForUpdate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseVoxelMesh, nullptr, "MarkTrianglesDataForUpdate", nullptr, nullptr, sizeof(Z_Construct_UFunction_UBaseVoxelMesh_MarkTrianglesDataForUpdate_Statics::BaseVoxelMesh_eventMarkTrianglesDataForUpdate_Parms), Z_Construct_UFunction_UBaseVoxelMesh_MarkTrianglesDataForUpdate_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_MarkTrianglesDataForUpdate_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelMesh_MarkTrianglesDataForUpdate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_MarkTrianglesDataForUpdate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBaseVoxelMesh_MarkTrianglesDataForUpdate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBaseVoxelMesh_MarkTrianglesDataForUpdate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics
	{
		struct BaseVoxelMesh_eventSetupMesh_Parms
		{
			FVector MeshSize;
			FIntVector GridSize;
			TSet<FName> RenderNameList;
			TArray<FLFPVoxelGridData> GridData;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MeshSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_MeshSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridSize;
		static const UECodeGen_Private::FNamePropertyParams NewProp_RenderNameList_ElementProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RenderNameList_MetaData[];
#endif
		static const UECodeGen_Private::FSetPropertyParams NewProp_RenderNameList;
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridData_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridData_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_GridData;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_MeshSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_MeshSize = { "MeshSize", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseVoxelMesh_eventSetupMesh_Parms, MeshSize), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_MeshSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_MeshSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_GridSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_GridSize = { "GridSize", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseVoxelMesh_eventSetupMesh_Parms, GridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_GridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_GridSize_MetaData)) };
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_RenderNameList_ElementProp = { "RenderNameList", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_RenderNameList_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FSetPropertyParams Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_RenderNameList = { "RenderNameList", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseVoxelMesh_eventSetupMesh_Parms, RenderNameList), METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_RenderNameList_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_RenderNameList_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_GridData_Inner = { "GridData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPVoxelGridData, METADATA_PARAMS(nullptr, 0) }; // 4094411625
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_GridData_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_GridData = { "GridData", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseVoxelMesh_eventSetupMesh_Parms, GridData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_GridData_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_GridData_MetaData)) }; // 4094411625
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_MeshSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_GridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_RenderNameList_ElementProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_RenderNameList,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_GridData_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::NewProp_GridData,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::Function_MetaDataParams[] = {
		{ "Category", "BaseVoxelMesh | Function" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseVoxelMesh, nullptr, "SetupMesh", nullptr, nullptr, sizeof(Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::BaseVoxelMesh_eventSetupMesh_Parms), Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBaseVoxelMesh_UpdateMesh_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelMesh_UpdateMesh_Statics::Function_MetaDataParams[] = {
		{ "Category", "BaseVoxelMesh | Function" },
		{ "Comment", "// Override This\n// (Virtual Function Is Costly To Call) (This Is The Bridge To Other Class Function)\n" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
		{ "ToolTip", "Override This\n(Virtual Function Is Costly To Call) (This Is The Bridge To Other Class Function)" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseVoxelMesh_UpdateMesh_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseVoxelMesh, nullptr, "UpdateMesh", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelMesh_UpdateMesh_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_UpdateMesh_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBaseVoxelMesh_UpdateMesh()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBaseVoxelMesh_UpdateMesh_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBaseVoxelMesh_UpdateTriangles_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelMesh_UpdateTriangles_Statics::Function_MetaDataParams[] = {
		{ "Comment", "// Override This\n" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
		{ "ToolTip", "Override This" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseVoxelMesh_UpdateTriangles_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseVoxelMesh, nullptr, "UpdateTriangles", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelMesh_UpdateTriangles_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_UpdateTriangles_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBaseVoxelMesh_UpdateTriangles()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBaseVoxelMesh_UpdateTriangles_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBaseVoxelMesh_UpdateVertices_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelMesh_UpdateVertices_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseVoxelMesh_UpdateVertices_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseVoxelMesh, nullptr, "UpdateVertices", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelMesh_UpdateVertices_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelMesh_UpdateVertices_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBaseVoxelMesh_UpdateVertices()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBaseVoxelMesh_UpdateVertices_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UBaseVoxelMesh);
	UClass* Z_Construct_UClass_UBaseVoxelMesh_NoRegister()
	{
		return UBaseVoxelMesh::StaticClass();
	}
	struct Z_Construct_UClass_UBaseVoxelMesh_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MeshData_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_MeshData;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBaseVoxelMesh_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UDynamicMesh,
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UBaseVoxelMesh_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UBaseVoxelMesh_FindBlockNeighbour, "FindBlockNeighbour" }, // 3924809832
		{ &Z_Construct_UFunction_UBaseVoxelMesh_FindBlockVertices, "FindBlockVertices" }, // 2257578437
		{ &Z_Construct_UFunction_UBaseVoxelMesh_IsBlockFaceVisible, "IsBlockFaceVisible" }, // 2570512867
		{ &Z_Construct_UFunction_UBaseVoxelMesh_IsBlockNeedRender, "IsBlockNeedRender" }, // 4282840003
		{ &Z_Construct_UFunction_UBaseVoxelMesh_MarkTrianglesDataForUpdate, "MarkTrianglesDataForUpdate" }, // 2003530789
		{ &Z_Construct_UFunction_UBaseVoxelMesh_SetupMesh, "SetupMesh" }, // 2537417731
		{ &Z_Construct_UFunction_UBaseVoxelMesh_UpdateMesh, "UpdateMesh" }, // 1977918764
		{ &Z_Construct_UFunction_UBaseVoxelMesh_UpdateTriangles, "UpdateTriangles" }, // 2828525720
		{ &Z_Construct_UFunction_UBaseVoxelMesh_UpdateVertices, "UpdateVertices" }, // 4178450675
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelMesh_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n *  This class is the base of voxel and is design to be override\n */" },
		{ "IncludePath", "Mesh/BaseVoxelMesh.h" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
		{ "ToolTip", "This class is the base of voxel and is design to be override" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_MeshData_MetaData[] = {
		{ "Category", "BaseVoxelMesh | Varaible" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_MeshData = { "MeshData", nullptr, (EPropertyFlags)0x0020080000020015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseVoxelMesh, MeshData), Z_Construct_UScriptStruct_FLFPVoxelMeshData, METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_MeshData_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_MeshData_MetaData)) }; // 2558169204
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBaseVoxelMesh_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_MeshData,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBaseVoxelMesh_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBaseVoxelMesh>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UBaseVoxelMesh_Statics::ClassParams = {
		&UBaseVoxelMesh::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UBaseVoxelMesh_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelMesh_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelMesh_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelMesh_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UBaseVoxelMesh()
	{
		if (!Z_Registration_Info_UClass_UBaseVoxelMesh.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBaseVoxelMesh.OuterSingleton, Z_Construct_UClass_UBaseVoxelMesh_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UBaseVoxelMesh.OuterSingleton;
	}
	template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<UBaseVoxelMesh>()
	{
		return UBaseVoxelMesh::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBaseVoxelMesh);
	struct Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_Statics::ScriptStructInfo[] = {
		{ FLFPVoxelTriangleUpdateData::StaticStruct, Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewStructOps, TEXT("LFPVoxelTriangleUpdateData"), &Z_Registration_Info_UScriptStruct_LFPVoxelTriangleUpdateData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLFPVoxelTriangleUpdateData), 3094486123U) },
		{ FLFPVoxelGridData::StaticStruct, Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics::NewStructOps, TEXT("LFPVoxelGridData"), &Z_Registration_Info_UScriptStruct_LFPVoxelGridData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLFPVoxelGridData), 4094411625U) },
		{ FLFPVoxelTriangleData::StaticStruct, Z_Construct_UScriptStruct_FLFPVoxelTriangleData_Statics::NewStructOps, TEXT("LFPVoxelTriangleData"), &Z_Registration_Info_UScriptStruct_LFPVoxelTriangleData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLFPVoxelTriangleData), 2785686119U) },
		{ FLFPVoxelMeshData::StaticStruct, Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics::NewStructOps, TEXT("LFPVoxelMeshData"), &Z_Registration_Info_UScriptStruct_LFPVoxelMeshData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLFPVoxelMeshData), 2558169204U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UBaseVoxelMesh, UBaseVoxelMesh::StaticClass, TEXT("UBaseVoxelMesh"), &Z_Registration_Info_UClass_UBaseVoxelMesh, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBaseVoxelMesh), 3972167606U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_2640533044(TEXT("/Script/LohFunctionPlugin"),
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_Statics::ClassInfo),
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
