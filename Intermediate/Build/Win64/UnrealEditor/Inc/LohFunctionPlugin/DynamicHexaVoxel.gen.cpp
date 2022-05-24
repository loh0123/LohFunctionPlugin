// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LohFunctionPlugin/Public/Mesh/DynamicHexaVoxel.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDynamicHexaVoxel() {}
// Cross Module References
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelBlockData();
	UPackage* Z_Construct_UPackage__Script_LohFunctionPlugin();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelTriData();
	GEOMETRYSCRIPTINGCORE_API UScriptStruct* Z_Construct_UScriptStruct_FGeometryScriptIndexList();
	GEOMETRYSCRIPTINGCORE_API UScriptStruct* Z_Construct_UScriptStruct_FGeometryScriptUVTriangle();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelData();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntVector();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_UDynamicHexaVoxel_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_UDynamicHexaVoxel();
	GEOMETRYFRAMEWORK_API UClass* Z_Construct_UClass_UDynamicMesh();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_LFPVoxelBlockData;
class UScriptStruct* FLFPVoxelBlockData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_LFPVoxelBlockData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_LFPVoxelBlockData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLFPVoxelBlockData, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("LFPVoxelBlockData"));
	}
	return Z_Registration_Info_UScriptStruct_LFPVoxelBlockData.OuterSingleton;
}
template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<FLFPVoxelBlockData>()
{
	return FLFPVoxelBlockData::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IsVisible_MetaData[];
#endif
		static void NewProp_IsVisible_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_IsVisible;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RenderLayer_MetaData[];
#endif
		static const UECodeGen_Private::FBytePropertyParams NewProp_RenderLayer;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLFPVoxelBlockData>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics::NewProp_IsVisible_MetaData[] = {
		{ "Category", "LFPVoxelData" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics::NewProp_IsVisible_SetBit(void* Obj)
	{
		((FLFPVoxelBlockData*)Obj)->IsVisible = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics::NewProp_IsVisible = { "IsVisible", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FLFPVoxelBlockData), &Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics::NewProp_IsVisible_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics::NewProp_IsVisible_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics::NewProp_IsVisible_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics::NewProp_RenderLayer_MetaData[] = {
		{ "Category", "LFPVoxelData" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics::NewProp_RenderLayer = { "RenderLayer", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelBlockData, RenderLayer), nullptr, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics::NewProp_RenderLayer_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics::NewProp_RenderLayer_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics::NewProp_IsVisible,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics::NewProp_RenderLayer,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
		nullptr,
		&NewStructOps,
		"LFPVoxelBlockData",
		sizeof(FLFPVoxelBlockData),
		alignof(FLFPVoxelBlockData),
		Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelBlockData()
	{
		if (!Z_Registration_Info_UScriptStruct_LFPVoxelBlockData.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_LFPVoxelBlockData.InnerSingleton, Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_LFPVoxelBlockData.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_LFPVoxelTriData;
class UScriptStruct* FLFPVoxelTriData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_LFPVoxelTriData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_LFPVoxelTriData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLFPVoxelTriData, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("LFPVoxelTriData"));
	}
	return Z_Registration_Info_UScriptStruct_LFPVoxelTriData.OuterSingleton;
}
template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<FLFPVoxelTriData>()
{
	return FLFPVoxelTriData::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MeshTriangleIndex_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_MeshTriangleIndex;
		static const UECodeGen_Private::FStructPropertyParams NewProp_MeshUVList_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MeshUVList_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_MeshUVList;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IsDirty_MetaData[];
#endif
		static void NewProp_IsDirty_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_IsDirty;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLFPVoxelTriData>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::NewProp_MeshTriangleIndex_MetaData[] = {
		{ "Category", "LFPVoxelTriData" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::NewProp_MeshTriangleIndex = { "MeshTriangleIndex", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelTriData, MeshTriangleIndex), Z_Construct_UScriptStruct_FGeometryScriptIndexList, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::NewProp_MeshTriangleIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::NewProp_MeshTriangleIndex_MetaData)) }; // 2628479871
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::NewProp_MeshUVList_Inner = { "MeshUVList", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FGeometryScriptUVTriangle, METADATA_PARAMS(nullptr, 0) }; // 3187439844
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::NewProp_MeshUVList_MetaData[] = {
		{ "Category", "LFPVoxelTriData" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::NewProp_MeshUVList = { "MeshUVList", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelTriData, MeshUVList), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::NewProp_MeshUVList_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::NewProp_MeshUVList_MetaData)) }; // 3187439844
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::NewProp_IsDirty_MetaData[] = {
		{ "Category", "LFPVoxelTriData" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::NewProp_IsDirty_SetBit(void* Obj)
	{
		((FLFPVoxelTriData*)Obj)->IsDirty = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::NewProp_IsDirty = { "IsDirty", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FLFPVoxelTriData), &Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::NewProp_IsDirty_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::NewProp_IsDirty_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::NewProp_IsDirty_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::NewProp_MeshTriangleIndex,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::NewProp_MeshUVList_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::NewProp_MeshUVList,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::NewProp_IsDirty,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
		nullptr,
		&NewStructOps,
		"LFPVoxelTriData",
		sizeof(FLFPVoxelTriData),
		alignof(FLFPVoxelTriData),
		Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelTriData()
	{
		if (!Z_Registration_Info_UScriptStruct_LFPVoxelTriData.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_LFPVoxelTriData.InnerSingleton, Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_LFPVoxelTriData.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_LFPVoxelData;
class UScriptStruct* FLFPVoxelData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_LFPVoxelData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_LFPVoxelData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLFPVoxelData, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("LFPVoxelData"));
	}
	return Z_Registration_Info_UScriptStruct_LFPVoxelData.OuterSingleton;
}
template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<FLFPVoxelData>()
{
	return FLFPVoxelData::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FLFPVoxelData_Statics
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
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VertexSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_VertexSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaxIndex_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_MaxIndex;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MeshVertexIndex_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_MeshVertexIndex;
		static const UECodeGen_Private::FStructPropertyParams NewProp_MeshTriangleData_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MeshTriangleData_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_MeshTriangleData;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelData_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLFPVoxelData>();
	}
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_GridData_Inner = { "GridData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPVoxelBlockData, METADATA_PARAMS(nullptr, 0) }; // 2407851110
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_GridData_MetaData[] = {
		{ "Category", "LFPVoxelData" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_GridData = { "GridData", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelData, GridData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_GridData_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_GridData_MetaData)) }; // 2407851110
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_MeshSize_MetaData[] = {
		{ "Category", "LFPVoxelData | Setting" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_MeshSize = { "MeshSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelData, MeshSize), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_MeshSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_MeshSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_GridSize_MetaData[] = {
		{ "Category", "LFPVoxelData | Setting" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_GridSize = { "GridSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelData, GridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_GridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_GridSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_VertexSize_MetaData[] = {
		{ "Category", "LFPVoxelData | Cache" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_VertexSize = { "VertexSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelData, VertexSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_VertexSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_VertexSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_MaxIndex_MetaData[] = {
		{ "Category", "LFPVoxelData | Cache" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_MaxIndex = { "MaxIndex", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelData, MaxIndex), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_MaxIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_MaxIndex_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_MeshVertexIndex_MetaData[] = {
		{ "Category", "LFPVoxelData | Cache" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_MeshVertexIndex = { "MeshVertexIndex", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelData, MeshVertexIndex), Z_Construct_UScriptStruct_FGeometryScriptIndexList, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_MeshVertexIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_MeshVertexIndex_MetaData)) }; // 2628479871
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_MeshTriangleData_Inner = { "MeshTriangleData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPVoxelTriData, METADATA_PARAMS(nullptr, 0) }; // 1056939622
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_MeshTriangleData_MetaData[] = {
		{ "Category", "LFPVoxelData | Cache" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_MeshTriangleData = { "MeshTriangleData", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelData, MeshTriangleData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_MeshTriangleData_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_MeshTriangleData_MetaData)) }; // 1056939622
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPVoxelData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_GridData_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_GridData,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_MeshSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_GridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_VertexSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_MaxIndex,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_MeshVertexIndex,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_MeshTriangleData_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewProp_MeshTriangleData,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLFPVoxelData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
		nullptr,
		&NewStructOps,
		"LFPVoxelData",
		sizeof(FLFPVoxelData),
		alignof(FLFPVoxelData),
		Z_Construct_UScriptStruct_FLFPVoxelData_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelData_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelData_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelData()
	{
		if (!Z_Registration_Info_UScriptStruct_LFPVoxelData.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_LFPVoxelData.InnerSingleton, Z_Construct_UScriptStruct_FLFPVoxelData_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_LFPVoxelData.InnerSingleton;
	}
	DEFINE_FUNCTION(UDynamicHexaVoxel::execGetHexagonVertexIndexBP)
	{
		P_GET_STRUCT(FIntVector,Z_Param_HexagonPos);
		P_GET_TARRAY_REF(int32,Z_Param_Out_VertexIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->GetHexagonVertexIndexBP(Z_Param_HexagonPos,Z_Param_Out_VertexIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UDynamicHexaVoxel::execUpdateTriangles)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->UpdateTriangles();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UDynamicHexaVoxel::execUpdateVertexs)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->UpdateVertexs();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UDynamicHexaVoxel::execSetVoxelData)
	{
		P_GET_STRUCT(FIntVector,Z_Param_Location);
		P_GET_UBOOL(Z_Param_IsVisible);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->SetVoxelData(Z_Param_Location,Z_Param_IsVisible);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UDynamicHexaVoxel::execSetupVoxel)
	{
		P_GET_STRUCT(FVector,Z_Param_MeshSize);
		P_GET_STRUCT(FIntVector,Z_Param_GridSize);
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_VertexSize);
		P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_MaxIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetupVoxel(Z_Param_MeshSize,Z_Param_GridSize,Z_Param_Out_VertexSize,Z_Param_Out_MaxIndex);
		P_NATIVE_END;
	}
	void UDynamicHexaVoxel::StaticRegisterNativesUDynamicHexaVoxel()
	{
		UClass* Class = UDynamicHexaVoxel::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetHexagonVertexIndexBP", &UDynamicHexaVoxel::execGetHexagonVertexIndexBP },
			{ "SetupVoxel", &UDynamicHexaVoxel::execSetupVoxel },
			{ "SetVoxelData", &UDynamicHexaVoxel::execSetVoxelData },
			{ "UpdateTriangles", &UDynamicHexaVoxel::execUpdateTriangles },
			{ "UpdateVertexs", &UDynamicHexaVoxel::execUpdateVertexs },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UDynamicHexaVoxel_GetHexagonVertexIndexBP_Statics
	{
		struct DynamicHexaVoxel_eventGetHexagonVertexIndexBP_Parms
		{
			FIntVector HexagonPos;
			TArray<int32> VertexIndex;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_HexagonPos_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_HexagonPos;
		static const UECodeGen_Private::FIntPropertyParams NewProp_VertexIndex_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_VertexIndex;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UDynamicHexaVoxel_GetHexagonVertexIndexBP_Statics::NewProp_HexagonPos_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UDynamicHexaVoxel_GetHexagonVertexIndexBP_Statics::NewProp_HexagonPos = { "HexagonPos", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DynamicHexaVoxel_eventGetHexagonVertexIndexBP_Parms, HexagonPos), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_UDynamicHexaVoxel_GetHexagonVertexIndexBP_Statics::NewProp_HexagonPos_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UDynamicHexaVoxel_GetHexagonVertexIndexBP_Statics::NewProp_HexagonPos_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UDynamicHexaVoxel_GetHexagonVertexIndexBP_Statics::NewProp_VertexIndex_Inner = { "VertexIndex", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UDynamicHexaVoxel_GetHexagonVertexIndexBP_Statics::NewProp_VertexIndex = { "VertexIndex", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DynamicHexaVoxel_eventGetHexagonVertexIndexBP_Parms, VertexIndex), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDynamicHexaVoxel_GetHexagonVertexIndexBP_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDynamicHexaVoxel_GetHexagonVertexIndexBP_Statics::NewProp_HexagonPos,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDynamicHexaVoxel_GetHexagonVertexIndexBP_Statics::NewProp_VertexIndex_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDynamicHexaVoxel_GetHexagonVertexIndexBP_Statics::NewProp_VertexIndex,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UDynamicHexaVoxel_GetHexagonVertexIndexBP_Statics::Function_MetaDataParams[] = {
		{ "Category", "DynamicHexaVoxel | Function" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDynamicHexaVoxel_GetHexagonVertexIndexBP_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDynamicHexaVoxel, nullptr, "GetHexagonVertexIndexBP", nullptr, nullptr, sizeof(Z_Construct_UFunction_UDynamicHexaVoxel_GetHexagonVertexIndexBP_Statics::DynamicHexaVoxel_eventGetHexagonVertexIndexBP_Parms), Z_Construct_UFunction_UDynamicHexaVoxel_GetHexagonVertexIndexBP_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UDynamicHexaVoxel_GetHexagonVertexIndexBP_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UDynamicHexaVoxel_GetHexagonVertexIndexBP_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UDynamicHexaVoxel_GetHexagonVertexIndexBP_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UDynamicHexaVoxel_GetHexagonVertexIndexBP()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDynamicHexaVoxel_GetHexagonVertexIndexBP_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics
	{
		struct DynamicHexaVoxel_eventSetupVoxel_Parms
		{
			FVector MeshSize;
			FIntVector GridSize;
			FIntVector VertexSize;
			int32 MaxIndex;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MeshSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_MeshSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridSize;
		static const UECodeGen_Private::FStructPropertyParams NewProp_VertexSize;
		static const UECodeGen_Private::FIntPropertyParams NewProp_MaxIndex;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::NewProp_MeshSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::NewProp_MeshSize = { "MeshSize", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DynamicHexaVoxel_eventSetupVoxel_Parms, MeshSize), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::NewProp_MeshSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::NewProp_MeshSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::NewProp_GridSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::NewProp_GridSize = { "GridSize", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DynamicHexaVoxel_eventSetupVoxel_Parms, GridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::NewProp_GridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::NewProp_GridSize_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::NewProp_VertexSize = { "VertexSize", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DynamicHexaVoxel_eventSetupVoxel_Parms, VertexSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::NewProp_MaxIndex = { "MaxIndex", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DynamicHexaVoxel_eventSetupVoxel_Parms, MaxIndex), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::NewProp_MeshSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::NewProp_GridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::NewProp_VertexSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::NewProp_MaxIndex,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::Function_MetaDataParams[] = {
		{ "Category", "DynamicHexaVoxel | Function" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDynamicHexaVoxel, nullptr, "SetupVoxel", nullptr, nullptr, sizeof(Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::DynamicHexaVoxel_eventSetupVoxel_Parms), Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics
	{
		struct DynamicHexaVoxel_eventSetVoxelData_Parms
		{
			FIntVector Location;
			bool IsVisible;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Location;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IsVisible_MetaData[];
#endif
		static void NewProp_IsVisible_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_IsVisible;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DynamicHexaVoxel_eventSetVoxelData_Parms, Location), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::NewProp_Location_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::NewProp_IsVisible_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::NewProp_IsVisible_SetBit(void* Obj)
	{
		((DynamicHexaVoxel_eventSetVoxelData_Parms*)Obj)->IsVisible = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::NewProp_IsVisible = { "IsVisible", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(DynamicHexaVoxel_eventSetVoxelData_Parms), &Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::NewProp_IsVisible_SetBit, METADATA_PARAMS(Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::NewProp_IsVisible_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::NewProp_IsVisible_MetaData)) };
	void Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DynamicHexaVoxel_eventSetVoxelData_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(DynamicHexaVoxel_eventSetVoxelData_Parms), &Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::NewProp_Location,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::NewProp_IsVisible,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::Function_MetaDataParams[] = {
		{ "Category", "DynamicHexaVoxel | Function" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDynamicHexaVoxel, nullptr, "SetVoxelData", nullptr, nullptr, sizeof(Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::DynamicHexaVoxel_eventSetVoxelData_Parms), Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UDynamicHexaVoxel_UpdateTriangles_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UDynamicHexaVoxel_UpdateTriangles_Statics::Function_MetaDataParams[] = {
		{ "Category", "DynamicHexaVoxel | Function" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDynamicHexaVoxel_UpdateTriangles_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDynamicHexaVoxel, nullptr, "UpdateTriangles", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UDynamicHexaVoxel_UpdateTriangles_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UDynamicHexaVoxel_UpdateTriangles_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UDynamicHexaVoxel_UpdateTriangles()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDynamicHexaVoxel_UpdateTriangles_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UDynamicHexaVoxel_UpdateVertexs_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UDynamicHexaVoxel_UpdateVertexs_Statics::Function_MetaDataParams[] = {
		{ "Category", "DynamicHexaVoxel | Function" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UDynamicHexaVoxel_UpdateVertexs_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UDynamicHexaVoxel, nullptr, "UpdateVertexs", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UDynamicHexaVoxel_UpdateVertexs_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UDynamicHexaVoxel_UpdateVertexs_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UDynamicHexaVoxel_UpdateVertexs()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UDynamicHexaVoxel_UpdateVertexs_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UDynamicHexaVoxel);
	UClass* Z_Construct_UClass_UDynamicHexaVoxel_NoRegister()
	{
		return UDynamicHexaVoxel::StaticClass();
	}
	struct Z_Construct_UClass_UDynamicHexaVoxel_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VoxelData_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_VoxelData;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_HasDirtyTriangles_MetaData[];
#endif
		static void NewProp_HasDirtyTriangles_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_HasDirtyTriangles;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UDynamicHexaVoxel_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UDynamicMesh,
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UDynamicHexaVoxel_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UDynamicHexaVoxel_GetHexagonVertexIndexBP, "GetHexagonVertexIndexBP" }, // 2782820580
		{ &Z_Construct_UFunction_UDynamicHexaVoxel_SetupVoxel, "SetupVoxel" }, // 200063711
		{ &Z_Construct_UFunction_UDynamicHexaVoxel_SetVoxelData, "SetVoxelData" }, // 2603663182
		{ &Z_Construct_UFunction_UDynamicHexaVoxel_UpdateTriangles, "UpdateTriangles" }, // 2543679353
		{ &Z_Construct_UFunction_UDynamicHexaVoxel_UpdateVertexs, "UpdateVertexs" }, // 1281341198
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDynamicHexaVoxel_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Mesh/DynamicHexaVoxel.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDynamicHexaVoxel_Statics::NewProp_VoxelData_MetaData[] = {
		{ "Category", "DynamicHexaVoxel | Varaible" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UDynamicHexaVoxel_Statics::NewProp_VoxelData = { "VoxelData", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UDynamicHexaVoxel, VoxelData), Z_Construct_UScriptStruct_FLFPVoxelData, METADATA_PARAMS(Z_Construct_UClass_UDynamicHexaVoxel_Statics::NewProp_VoxelData_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDynamicHexaVoxel_Statics::NewProp_VoxelData_MetaData)) }; // 2783516282
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UDynamicHexaVoxel_Statics::NewProp_HasDirtyTriangles_MetaData[] = {
		{ "Category", "DynamicHexaVoxel | Varaible" },
		{ "ModuleRelativePath", "Public/Mesh/DynamicHexaVoxel.h" },
	};
#endif
	void Z_Construct_UClass_UDynamicHexaVoxel_Statics::NewProp_HasDirtyTriangles_SetBit(void* Obj)
	{
		((UDynamicHexaVoxel*)Obj)->HasDirtyTriangles = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UDynamicHexaVoxel_Statics::NewProp_HasDirtyTriangles = { "HasDirtyTriangles", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UDynamicHexaVoxel), &Z_Construct_UClass_UDynamicHexaVoxel_Statics::NewProp_HasDirtyTriangles_SetBit, METADATA_PARAMS(Z_Construct_UClass_UDynamicHexaVoxel_Statics::NewProp_HasDirtyTriangles_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UDynamicHexaVoxel_Statics::NewProp_HasDirtyTriangles_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UDynamicHexaVoxel_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDynamicHexaVoxel_Statics::NewProp_VoxelData,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UDynamicHexaVoxel_Statics::NewProp_HasDirtyTriangles,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UDynamicHexaVoxel_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDynamicHexaVoxel>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UDynamicHexaVoxel_Statics::ClassParams = {
		&UDynamicHexaVoxel::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UDynamicHexaVoxel_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UDynamicHexaVoxel_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UDynamicHexaVoxel_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UDynamicHexaVoxel_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UDynamicHexaVoxel()
	{
		if (!Z_Registration_Info_UClass_UDynamicHexaVoxel.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDynamicHexaVoxel.OuterSingleton, Z_Construct_UClass_UDynamicHexaVoxel_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UDynamicHexaVoxel.OuterSingleton;
	}
	template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<UDynamicHexaVoxel>()
	{
		return UDynamicHexaVoxel::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UDynamicHexaVoxel);
	struct Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_DynamicHexaVoxel_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_DynamicHexaVoxel_h_Statics::ScriptStructInfo[] = {
		{ FLFPVoxelBlockData::StaticStruct, Z_Construct_UScriptStruct_FLFPVoxelBlockData_Statics::NewStructOps, TEXT("LFPVoxelBlockData"), &Z_Registration_Info_UScriptStruct_LFPVoxelBlockData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLFPVoxelBlockData), 2407851110U) },
		{ FLFPVoxelTriData::StaticStruct, Z_Construct_UScriptStruct_FLFPVoxelTriData_Statics::NewStructOps, TEXT("LFPVoxelTriData"), &Z_Registration_Info_UScriptStruct_LFPVoxelTriData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLFPVoxelTriData), 1056939622U) },
		{ FLFPVoxelData::StaticStruct, Z_Construct_UScriptStruct_FLFPVoxelData_Statics::NewStructOps, TEXT("LFPVoxelData"), &Z_Registration_Info_UScriptStruct_LFPVoxelData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLFPVoxelData), 2783516282U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_DynamicHexaVoxel_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UDynamicHexaVoxel, UDynamicHexaVoxel::StaticClass, TEXT("UDynamicHexaVoxel"), &Z_Registration_Info_UClass_UDynamicHexaVoxel, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDynamicHexaVoxel), 979348546U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_DynamicHexaVoxel_h_1674411427(TEXT("/Script/LohFunctionPlugin"),
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_DynamicHexaVoxel_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_DynamicHexaVoxel_h_Statics::ClassInfo),
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_DynamicHexaVoxel_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_DynamicHexaVoxel_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
