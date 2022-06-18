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
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelTriangleData();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_UBaseVoxelMesh_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_UBaseVoxelMesh();
	GEOMETRYFRAMEWORK_API UClass* Z_Construct_UClass_UDynamicMesh();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPVoxelData_NoRegister();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
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
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaterialID_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_MaterialID;
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
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_MaterialID_MetaData[] = {
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_MaterialID = { "MaterialID", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelTriangleUpdateData, MaterialID), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_MaterialID_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_MaterialID_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_GridIndex,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewTriangleList_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewTriangleList,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewTriangleGroupList_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewTriangleGroupList,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewUVList_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_NewUVList,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewProp_MaterialID,
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
	void UBaseVoxelMesh::StaticRegisterNativesUBaseVoxelMesh()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UBaseVoxelMesh);
	UClass* Z_Construct_UClass_UBaseVoxelMesh_NoRegister()
	{
		return UBaseVoxelMesh::StaticClass();
	}
	struct Z_Construct_UClass_UBaseVoxelMesh_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VoxelData_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_VoxelData;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ChuckGridLocation_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_ChuckGridLocation;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_StartVoxelLocation_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_StartVoxelLocation;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ChuckIndex_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_ChuckIndex;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MeshSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_MeshSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VoxelGridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_VoxelGridSize;
		static const UECodeGen_Private::FStructPropertyParams NewProp_VerticesList_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VerticesList_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_VerticesList;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VertexSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_VertexSize;
		static const UECodeGen_Private::FStructPropertyParams NewProp_TriangleDataList_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TriangleDataList_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_TriangleDataList;
		static const UECodeGen_Private::FIntPropertyParams NewProp_DataUpdateList_ElementProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DataUpdateList_MetaData[];
#endif
		static const UECodeGen_Private::FSetPropertyParams NewProp_DataUpdateList;
		static const UECodeGen_Private::FIntPropertyParams NewProp_BufferUpdateList_ElementProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BufferUpdateList_MetaData[];
#endif
		static const UECodeGen_Private::FSetPropertyParams NewProp_BufferUpdateList;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBaseVoxelMesh_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UDynamicMesh,
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
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
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_VoxelData_MetaData[] = {
		{ "Comment", "// Initialize Data\n" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
		{ "ToolTip", "Initialize Data" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_VoxelData = { "VoxelData", nullptr, (EPropertyFlags)0x0024080000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseVoxelMesh, VoxelData), Z_Construct_UClass_ULFPVoxelData_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_VoxelData_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_VoxelData_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_ChuckGridLocation_MetaData[] = {
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_ChuckGridLocation = { "ChuckGridLocation", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseVoxelMesh, ChuckGridLocation), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_ChuckGridLocation_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_ChuckGridLocation_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_StartVoxelLocation_MetaData[] = {
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_StartVoxelLocation = { "StartVoxelLocation", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseVoxelMesh, StartVoxelLocation), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_StartVoxelLocation_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_StartVoxelLocation_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_ChuckIndex_MetaData[] = {
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_ChuckIndex = { "ChuckIndex", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseVoxelMesh, ChuckIndex), METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_ChuckIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_ChuckIndex_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_MeshSize_MetaData[] = {
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_MeshSize = { "MeshSize", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseVoxelMesh, MeshSize), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_MeshSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_MeshSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_VoxelGridSize_MetaData[] = {
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_VoxelGridSize = { "VoxelGridSize", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseVoxelMesh, VoxelGridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_VoxelGridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_VoxelGridSize_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_VerticesList_Inner = { "VerticesList", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_VerticesList_MetaData[] = {
		{ "Comment", "// Runtime Data\n" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
		{ "ToolTip", "Runtime Data" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_VerticesList = { "VerticesList", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseVoxelMesh, VerticesList), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_VerticesList_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_VerticesList_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_VertexSize_MetaData[] = {
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_VertexSize = { "VertexSize", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseVoxelMesh, VertexSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_VertexSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_VertexSize_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_TriangleDataList_Inner = { "TriangleDataList", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPVoxelTriangleData, METADATA_PARAMS(nullptr, 0) }; // 2785686119
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_TriangleDataList_MetaData[] = {
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_TriangleDataList = { "TriangleDataList", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseVoxelMesh, TriangleDataList), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_TriangleDataList_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_TriangleDataList_MetaData)) }; // 2785686119
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_DataUpdateList_ElementProp = { "DataUpdateList", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_DataUpdateList_MetaData[] = {
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FSetPropertyParams Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_DataUpdateList = { "DataUpdateList", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseVoxelMesh, DataUpdateList), METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_DataUpdateList_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_DataUpdateList_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_BufferUpdateList_ElementProp = { "BufferUpdateList", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_BufferUpdateList_MetaData[] = {
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelMesh.h" },
	};
#endif
	const UECodeGen_Private::FSetPropertyParams Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_BufferUpdateList = { "BufferUpdateList", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseVoxelMesh, BufferUpdateList), METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_BufferUpdateList_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_BufferUpdateList_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBaseVoxelMesh_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_VoxelData,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_ChuckGridLocation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_StartVoxelLocation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_ChuckIndex,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_MeshSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_VoxelGridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_VerticesList_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_VerticesList,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_VertexSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_TriangleDataList_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_TriangleDataList,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_DataUpdateList_ElementProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_DataUpdateList,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_BufferUpdateList_ElementProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelMesh_Statics::NewProp_BufferUpdateList,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBaseVoxelMesh_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBaseVoxelMesh>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UBaseVoxelMesh_Statics::ClassParams = {
		&UBaseVoxelMesh::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UBaseVoxelMesh_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
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
		{ FLFPVoxelTriangleUpdateData::StaticStruct, Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics::NewStructOps, TEXT("LFPVoxelTriangleUpdateData"), &Z_Registration_Info_UScriptStruct_LFPVoxelTriangleUpdateData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLFPVoxelTriangleUpdateData), 1497137956U) },
		{ FLFPVoxelTriangleData::StaticStruct, Z_Construct_UScriptStruct_FLFPVoxelTriangleData_Statics::NewStructOps, TEXT("LFPVoxelTriangleData"), &Z_Registration_Info_UScriptStruct_LFPVoxelTriangleData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLFPVoxelTriangleData), 2785686119U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UBaseVoxelMesh, UBaseVoxelMesh::StaticClass, TEXT("UBaseVoxelMesh"), &Z_Registration_Info_UClass_UBaseVoxelMesh, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBaseVoxelMesh), 1587572903U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_17296615(TEXT("/Script/LohFunctionPlugin"),
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_Statics::ClassInfo),
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
