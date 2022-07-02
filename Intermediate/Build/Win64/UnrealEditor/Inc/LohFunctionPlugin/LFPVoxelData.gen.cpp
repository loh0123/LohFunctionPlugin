// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LohFunctionPlugin/Public/Container/LFPVoxelData.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLFPVoxelData() {}
// Cross Module References
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelAttribute();
	UPackage* Z_Construct_UPackage__Script_LohFunctionPlugin();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FColor();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelChuckData();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelContainerSetting();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntVector();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPVoxelData_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPVoxelData();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_LFPVoxelAttribute;
class UScriptStruct* FLFPVoxelAttribute::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_LFPVoxelAttribute.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_LFPVoxelAttribute.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLFPVoxelAttribute, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("LFPVoxelAttribute"));
	}
	return Z_Registration_Info_UScriptStruct_LFPVoxelAttribute.OuterSingleton;
}
template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<FLFPVoxelAttribute>()
{
	return FLFPVoxelAttribute::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VertexColor_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_VertexColor;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaterialID_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_MaterialID;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLFPVoxelAttribute>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_VertexColor_MetaData[] = {
		{ "Category", "LFPVoxelAttribute" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_VertexColor = { "VertexColor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelAttribute, VertexColor), Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_VertexColor_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_VertexColor_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_MaterialID_MetaData[] = {
		{ "Category", "LFPVoxelAttribute" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_MaterialID = { "MaterialID", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelAttribute, MaterialID), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_MaterialID_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_MaterialID_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_VertexColor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_MaterialID,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
		nullptr,
		&NewStructOps,
		"LFPVoxelAttribute",
		sizeof(FLFPVoxelAttribute),
		alignof(FLFPVoxelAttribute),
		Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelAttribute()
	{
		if (!Z_Registration_Info_UScriptStruct_LFPVoxelAttribute.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_LFPVoxelAttribute.InnerSingleton, Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_LFPVoxelAttribute.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_LFPVoxelChuckData;
class UScriptStruct* FLFPVoxelChuckData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_LFPVoxelChuckData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_LFPVoxelChuckData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLFPVoxelChuckData, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("LFPVoxelChuckData"));
	}
	return Z_Registration_Info_UScriptStruct_LFPVoxelChuckData.OuterSingleton;
}
template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<FLFPVoxelChuckData>()
{
	return FLFPVoxelChuckData::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UECodeGen_Private::FStructPropertyParams NewProp_VoxelData_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VoxelData_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_VoxelData;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLFPVoxelChuckData>();
	}
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::NewProp_VoxelData_Inner = { "VoxelData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPVoxelAttribute, METADATA_PARAMS(nullptr, 0) }; // 409723961
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::NewProp_VoxelData_MetaData[] = {
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::NewProp_VoxelData = { "VoxelData", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelChuckData, VoxelData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::NewProp_VoxelData_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::NewProp_VoxelData_MetaData)) }; // 409723961
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::NewProp_VoxelData_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::NewProp_VoxelData,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
		nullptr,
		&NewStructOps,
		"LFPVoxelChuckData",
		sizeof(FLFPVoxelChuckData),
		alignof(FLFPVoxelChuckData),
		Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelChuckData()
	{
		if (!Z_Registration_Info_UScriptStruct_LFPVoxelChuckData.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_LFPVoxelChuckData.InnerSingleton, Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_LFPVoxelChuckData.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_LFPVoxelContainerSetting;
class UScriptStruct* FLFPVoxelContainerSetting::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_LFPVoxelContainerSetting.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_LFPVoxelContainerSetting.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLFPVoxelContainerSetting, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("LFPVoxelContainerSetting"));
	}
	return Z_Registration_Info_UScriptStruct_LFPVoxelContainerSetting.OuterSingleton;
}
template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<FLFPVoxelContainerSetting>()
{
	return FLFPVoxelContainerSetting::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaxMaterialID_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_MaxMaterialID;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SectionCount_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_SectionCount;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SectionSize_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_SectionSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PoolLength_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_PoolLength;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ChuckVoxelLength_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_ChuckVoxelLength;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MeshSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_MeshSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PoolGridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_PoolGridSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ChuckGridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_ChuckGridSize;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLFPVoxelContainerSetting>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_MaxMaterialID_MetaData[] = {
		{ "Category", "VoxelContainerSetting | Cache" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_MaxMaterialID = { "MaxMaterialID", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelContainerSetting, MaxMaterialID), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_MaxMaterialID_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_MaxMaterialID_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_SectionCount_MetaData[] = {
		{ "Category", "VoxelContainerSetting | Cache" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_SectionCount = { "SectionCount", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelContainerSetting, SectionCount), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_SectionCount_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_SectionCount_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_SectionSize_MetaData[] = {
		{ "Category", "VoxelContainerSetting | Cache" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_SectionSize = { "SectionSize", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelContainerSetting, SectionSize), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_SectionSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_SectionSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_PoolLength_MetaData[] = {
		{ "Category", "VoxelContainerSetting | Cache" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_PoolLength = { "PoolLength", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelContainerSetting, PoolLength), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_PoolLength_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_PoolLength_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_ChuckVoxelLength_MetaData[] = {
		{ "Category", "VoxelContainerSetting | Cache" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_ChuckVoxelLength = { "ChuckVoxelLength", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelContainerSetting, ChuckVoxelLength), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_ChuckVoxelLength_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_ChuckVoxelLength_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_MeshSize_MetaData[] = {
		{ "Category", "VoxelContainerSetting | Setting" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_MeshSize = { "MeshSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelContainerSetting, MeshSize), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_MeshSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_MeshSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_PoolGridSize_MetaData[] = {
		{ "Category", "VoxelContainerSetting | Setting" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_PoolGridSize = { "PoolGridSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelContainerSetting, PoolGridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_PoolGridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_PoolGridSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_ChuckGridSize_MetaData[] = {
		{ "Category", "VoxelContainerSetting | Setting" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_ChuckGridSize = { "ChuckGridSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelContainerSetting, ChuckGridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_ChuckGridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_ChuckGridSize_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_MaxMaterialID,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_SectionCount,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_SectionSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_PoolLength,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_ChuckVoxelLength,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_MeshSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_PoolGridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewProp_ChuckGridSize,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
		nullptr,
		&NewStructOps,
		"LFPVoxelContainerSetting",
		sizeof(FLFPVoxelContainerSetting),
		alignof(FLFPVoxelContainerSetting),
		Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelContainerSetting()
	{
		if (!Z_Registration_Info_UScriptStruct_LFPVoxelContainerSetting.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_LFPVoxelContainerSetting.InnerSingleton, Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_LFPVoxelContainerSetting.InnerSingleton;
	}
	DEFINE_FUNCTION(ULFPVoxelData::execSetAllVoxelGridDataWithSingleData)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_ChuckIndex);
		P_GET_STRUCT_REF(FLFPVoxelAttribute,Z_Param_Out_VoxelAttribute);
		P_GET_UBOOL(Z_Param_IsVisible);
		P_GET_UBOOL(Z_Param_bUpdateMesh);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetAllVoxelGridDataWithSingleData(Z_Param_ChuckIndex,Z_Param_Out_VoxelAttribute,Z_Param_IsVisible,Z_Param_bUpdateMesh);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPVoxelData::execSetVoxelGridDataList)
	{
		P_GET_TARRAY_REF(FIntVector,Z_Param_Out_VoxelGridLocationList);
		P_GET_STRUCT_REF(FLFPVoxelAttribute,Z_Param_Out_VoxelAttribute);
		P_GET_UBOOL(Z_Param_IsVisible);
		P_GET_UBOOL(Z_Param_bUpdateMesh);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetVoxelGridDataList(Z_Param_Out_VoxelGridLocationList,Z_Param_Out_VoxelAttribute,Z_Param_IsVisible,Z_Param_bUpdateMesh);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPVoxelData::execSetVoxelGridData)
	{
		P_GET_STRUCT(FIntVector,Z_Param_VoxelGridLocation);
		P_GET_STRUCT_REF(FLFPVoxelAttribute,Z_Param_Out_VoxelAttribute);
		P_GET_UBOOL(Z_Param_IsVisible);
		P_GET_UBOOL(Z_Param_bUpdateMesh);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetVoxelGridData(Z_Param_VoxelGridLocation,Z_Param_Out_VoxelAttribute,Z_Param_IsVisible,Z_Param_bUpdateMesh);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPVoxelData::execIsChuckInitialized)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_ChuckIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->IsChuckInitialized(Z_Param_ChuckIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPVoxelData::execGetPoolAttribute)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_ChuckIndex);
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_StartVoxelLocation);
		P_GET_STRUCT_REF(FVector,Z_Param_Out_ChuckMeshSize);
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_ChuckVoxelGridSize);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->GetPoolAttribute(Z_Param_ChuckIndex,Z_Param_Out_StartVoxelLocation,Z_Param_Out_ChuckMeshSize,Z_Param_Out_ChuckVoxelGridSize);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPVoxelData::execSetupVoxelData)
	{
		P_GET_STRUCT(FVector,Z_Param_NewMeshSize);
		P_GET_STRUCT(FIntVector,Z_Param_NewPoolGridSize);
		P_GET_STRUCT(FIntVector,Z_Param_NewChuckGridSize);
		P_GET_PROPERTY(FIntProperty,Z_Param_NewMaxMaterialID);
		P_GET_PROPERTY(FIntProperty,Z_Param_NewSectionSize);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetupVoxelData(Z_Param_NewMeshSize,Z_Param_NewPoolGridSize,Z_Param_NewChuckGridSize,Z_Param_NewMaxMaterialID,Z_Param_NewSectionSize);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPVoxelData::execMarkChuckForUpdate)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_ChuckIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->MarkChuckForUpdate(Z_Param_ChuckIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPVoxelData::execUpdateChuck)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_UpdateCount);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->UpdateChuck(Z_Param_UpdateCount);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPVoxelData::execGetContainerSize)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetContainerSize();
		P_NATIVE_END;
	}
	void ULFPVoxelData::StaticRegisterNativesULFPVoxelData()
	{
		UClass* Class = ULFPVoxelData::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetContainerSize", &ULFPVoxelData::execGetContainerSize },
			{ "GetPoolAttribute", &ULFPVoxelData::execGetPoolAttribute },
			{ "IsChuckInitialized", &ULFPVoxelData::execIsChuckInitialized },
			{ "MarkChuckForUpdate", &ULFPVoxelData::execMarkChuckForUpdate },
			{ "SetAllVoxelGridDataWithSingleData", &ULFPVoxelData::execSetAllVoxelGridDataWithSingleData },
			{ "SetupVoxelData", &ULFPVoxelData::execSetupVoxelData },
			{ "SetVoxelGridData", &ULFPVoxelData::execSetVoxelGridData },
			{ "SetVoxelGridDataList", &ULFPVoxelData::execSetVoxelGridDataList },
			{ "UpdateChuck", &ULFPVoxelData::execUpdateChuck },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULFPVoxelData_GetContainerSize_Statics
	{
		struct LFPVoxelData_eventGetContainerSize_Parms
		{
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPVoxelData_GetContainerSize_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventGetContainerSize_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPVoxelData_GetContainerSize_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_GetContainerSize_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_GetContainerSize_Statics::Function_MetaDataParams[] = {
		{ "Category", "VoxelData | Function" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPVoxelData_GetContainerSize_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPVoxelData, nullptr, "GetContainerSize", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPVoxelData_GetContainerSize_Statics::LFPVoxelData_eventGetContainerSize_Parms), Z_Construct_UFunction_ULFPVoxelData_GetContainerSize_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_GetContainerSize_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_GetContainerSize_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_GetContainerSize_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPVoxelData_GetContainerSize()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPVoxelData_GetContainerSize_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics
	{
		struct LFPVoxelData_eventGetPoolAttribute_Parms
		{
			int32 ChuckIndex;
			FIntVector StartVoxelLocation;
			FVector ChuckMeshSize;
			FIntVector ChuckVoxelGridSize;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ChuckIndex_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_ChuckIndex;
		static const UECodeGen_Private::FStructPropertyParams NewProp_StartVoxelLocation;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ChuckMeshSize;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ChuckVoxelGridSize;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::NewProp_ChuckIndex_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::NewProp_ChuckIndex = { "ChuckIndex", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventGetPoolAttribute_Parms, ChuckIndex), METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::NewProp_ChuckIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::NewProp_ChuckIndex_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::NewProp_StartVoxelLocation = { "StartVoxelLocation", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventGetPoolAttribute_Parms, StartVoxelLocation), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::NewProp_ChuckMeshSize = { "ChuckMeshSize", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventGetPoolAttribute_Parms, ChuckMeshSize), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::NewProp_ChuckVoxelGridSize = { "ChuckVoxelGridSize", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventGetPoolAttribute_Parms, ChuckVoxelGridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::NewProp_ChuckIndex,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::NewProp_StartVoxelLocation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::NewProp_ChuckMeshSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::NewProp_ChuckVoxelGridSize,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::Function_MetaDataParams[] = {
		{ "Category", "VoxelData | Function" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPVoxelData, nullptr, "GetPoolAttribute", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::LFPVoxelData_eventGetPoolAttribute_Parms), Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPVoxelData_IsChuckInitialized_Statics
	{
		struct LFPVoxelData_eventIsChuckInitialized_Parms
		{
			int32 ChuckIndex;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ChuckIndex_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_ChuckIndex;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_IsChuckInitialized_Statics::NewProp_ChuckIndex_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPVoxelData_IsChuckInitialized_Statics::NewProp_ChuckIndex = { "ChuckIndex", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventIsChuckInitialized_Parms, ChuckIndex), METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_IsChuckInitialized_Statics::NewProp_ChuckIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_IsChuckInitialized_Statics::NewProp_ChuckIndex_MetaData)) };
	void Z_Construct_UFunction_ULFPVoxelData_IsChuckInitialized_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPVoxelData_eventIsChuckInitialized_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPVoxelData_IsChuckInitialized_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPVoxelData_eventIsChuckInitialized_Parms), &Z_Construct_UFunction_ULFPVoxelData_IsChuckInitialized_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPVoxelData_IsChuckInitialized_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_IsChuckInitialized_Statics::NewProp_ChuckIndex,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_IsChuckInitialized_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_IsChuckInitialized_Statics::Function_MetaDataParams[] = {
		{ "Category", "VoxelData | Function" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPVoxelData_IsChuckInitialized_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPVoxelData, nullptr, "IsChuckInitialized", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPVoxelData_IsChuckInitialized_Statics::LFPVoxelData_eventIsChuckInitialized_Parms), Z_Construct_UFunction_ULFPVoxelData_IsChuckInitialized_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_IsChuckInitialized_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_IsChuckInitialized_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_IsChuckInitialized_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPVoxelData_IsChuckInitialized()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPVoxelData_IsChuckInitialized_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPVoxelData_MarkChuckForUpdate_Statics
	{
		struct LFPVoxelData_eventMarkChuckForUpdate_Parms
		{
			int32 ChuckIndex;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ChuckIndex_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_ChuckIndex;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_MarkChuckForUpdate_Statics::NewProp_ChuckIndex_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPVoxelData_MarkChuckForUpdate_Statics::NewProp_ChuckIndex = { "ChuckIndex", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventMarkChuckForUpdate_Parms, ChuckIndex), METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_MarkChuckForUpdate_Statics::NewProp_ChuckIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_MarkChuckForUpdate_Statics::NewProp_ChuckIndex_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPVoxelData_MarkChuckForUpdate_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_MarkChuckForUpdate_Statics::NewProp_ChuckIndex,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_MarkChuckForUpdate_Statics::Function_MetaDataParams[] = {
		{ "Category", "VoxelData | Function" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPVoxelData_MarkChuckForUpdate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPVoxelData, nullptr, "MarkChuckForUpdate", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPVoxelData_MarkChuckForUpdate_Statics::LFPVoxelData_eventMarkChuckForUpdate_Parms), Z_Construct_UFunction_ULFPVoxelData_MarkChuckForUpdate_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_MarkChuckForUpdate_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_MarkChuckForUpdate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_MarkChuckForUpdate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPVoxelData_MarkChuckForUpdate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPVoxelData_MarkChuckForUpdate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics
	{
		struct LFPVoxelData_eventSetAllVoxelGridDataWithSingleData_Parms
		{
			int32 ChuckIndex;
			FLFPVoxelAttribute VoxelAttribute;
			bool IsVisible;
			bool bUpdateMesh;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ChuckIndex_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_ChuckIndex;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VoxelAttribute_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_VoxelAttribute;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IsVisible_MetaData[];
#endif
		static void NewProp_IsVisible_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_IsVisible;
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
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_ChuckIndex_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_ChuckIndex = { "ChuckIndex", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventSetAllVoxelGridDataWithSingleData_Parms, ChuckIndex), METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_ChuckIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_ChuckIndex_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_VoxelAttribute_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_VoxelAttribute = { "VoxelAttribute", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventSetAllVoxelGridDataWithSingleData_Parms, VoxelAttribute), Z_Construct_UScriptStruct_FLFPVoxelAttribute, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_VoxelAttribute_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_VoxelAttribute_MetaData)) }; // 409723961
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_IsVisible_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_IsVisible_SetBit(void* Obj)
	{
		((LFPVoxelData_eventSetAllVoxelGridDataWithSingleData_Parms*)Obj)->IsVisible = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_IsVisible = { "IsVisible", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPVoxelData_eventSetAllVoxelGridDataWithSingleData_Parms), &Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_IsVisible_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_IsVisible_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_IsVisible_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_bUpdateMesh_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_bUpdateMesh_SetBit(void* Obj)
	{
		((LFPVoxelData_eventSetAllVoxelGridDataWithSingleData_Parms*)Obj)->bUpdateMesh = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_bUpdateMesh = { "bUpdateMesh", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPVoxelData_eventSetAllVoxelGridDataWithSingleData_Parms), &Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_bUpdateMesh_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_bUpdateMesh_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_bUpdateMesh_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_ChuckIndex,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_VoxelAttribute,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_IsVisible,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_bUpdateMesh,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::Function_MetaDataParams[] = {
		{ "Category", "VoxelData | Function" },
		{ "CPP_Default_bUpdateMesh", "true" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPVoxelData, nullptr, "SetAllVoxelGridDataWithSingleData", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::LFPVoxelData_eventSetAllVoxelGridDataWithSingleData_Parms), Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics
	{
		struct LFPVoxelData_eventSetupVoxelData_Parms
		{
			FVector NewMeshSize;
			FIntVector NewPoolGridSize;
			FIntVector NewChuckGridSize;
			int32 NewMaxMaterialID;
			int32 NewSectionSize;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NewMeshSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_NewMeshSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NewPoolGridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_NewPoolGridSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NewChuckGridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_NewChuckGridSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NewMaxMaterialID_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_NewMaxMaterialID;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NewSectionSize_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_NewSectionSize;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewMeshSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewMeshSize = { "NewMeshSize", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventSetupVoxelData_Parms, NewMeshSize), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewMeshSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewMeshSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewPoolGridSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewPoolGridSize = { "NewPoolGridSize", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventSetupVoxelData_Parms, NewPoolGridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewPoolGridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewPoolGridSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewChuckGridSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewChuckGridSize = { "NewChuckGridSize", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventSetupVoxelData_Parms, NewChuckGridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewChuckGridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewChuckGridSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewMaxMaterialID_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewMaxMaterialID = { "NewMaxMaterialID", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventSetupVoxelData_Parms, NewMaxMaterialID), METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewMaxMaterialID_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewMaxMaterialID_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewSectionSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewSectionSize = { "NewSectionSize", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventSetupVoxelData_Parms, NewSectionSize), METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewSectionSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewSectionSize_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewMeshSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewPoolGridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewChuckGridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewMaxMaterialID,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewSectionSize,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::Function_MetaDataParams[] = {
		{ "Category", "VoxelData | Function" },
		{ "CPP_Default_NewMaxMaterialID", "1" },
		{ "CPP_Default_NewSectionSize", "16" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPVoxelData, nullptr, "SetupVoxelData", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::LFPVoxelData_eventSetupVoxelData_Parms), Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics
	{
		struct LFPVoxelData_eventSetVoxelGridData_Parms
		{
			FIntVector VoxelGridLocation;
			FLFPVoxelAttribute VoxelAttribute;
			bool IsVisible;
			bool bUpdateMesh;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VoxelGridLocation_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_VoxelGridLocation;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VoxelAttribute_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_VoxelAttribute;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IsVisible_MetaData[];
#endif
		static void NewProp_IsVisible_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_IsVisible;
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
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_VoxelGridLocation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_VoxelGridLocation = { "VoxelGridLocation", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventSetVoxelGridData_Parms, VoxelGridLocation), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_VoxelGridLocation_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_VoxelGridLocation_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_VoxelAttribute_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_VoxelAttribute = { "VoxelAttribute", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventSetVoxelGridData_Parms, VoxelAttribute), Z_Construct_UScriptStruct_FLFPVoxelAttribute, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_VoxelAttribute_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_VoxelAttribute_MetaData)) }; // 409723961
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_IsVisible_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_IsVisible_SetBit(void* Obj)
	{
		((LFPVoxelData_eventSetVoxelGridData_Parms*)Obj)->IsVisible = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_IsVisible = { "IsVisible", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPVoxelData_eventSetVoxelGridData_Parms), &Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_IsVisible_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_IsVisible_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_IsVisible_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_bUpdateMesh_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_bUpdateMesh_SetBit(void* Obj)
	{
		((LFPVoxelData_eventSetVoxelGridData_Parms*)Obj)->bUpdateMesh = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_bUpdateMesh = { "bUpdateMesh", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPVoxelData_eventSetVoxelGridData_Parms), &Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_bUpdateMesh_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_bUpdateMesh_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_bUpdateMesh_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_VoxelGridLocation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_VoxelAttribute,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_IsVisible,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_bUpdateMesh,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::Function_MetaDataParams[] = {
		{ "Category", "VoxelData | Function" },
		{ "CPP_Default_bUpdateMesh", "true" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPVoxelData, nullptr, "SetVoxelGridData", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::LFPVoxelData_eventSetVoxelGridData_Parms), Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics
	{
		struct LFPVoxelData_eventSetVoxelGridDataList_Parms
		{
			TArray<FIntVector> VoxelGridLocationList;
			FLFPVoxelAttribute VoxelAttribute;
			bool IsVisible;
			bool bUpdateMesh;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_VoxelGridLocationList_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VoxelGridLocationList_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_VoxelGridLocationList;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VoxelAttribute_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_VoxelAttribute;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IsVisible_MetaData[];
#endif
		static void NewProp_IsVisible_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_IsVisible;
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
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_VoxelGridLocationList_Inner = { "VoxelGridLocationList", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_VoxelGridLocationList_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_VoxelGridLocationList = { "VoxelGridLocationList", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventSetVoxelGridDataList_Parms, VoxelGridLocationList), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_VoxelGridLocationList_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_VoxelGridLocationList_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_VoxelAttribute_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_VoxelAttribute = { "VoxelAttribute", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventSetVoxelGridDataList_Parms, VoxelAttribute), Z_Construct_UScriptStruct_FLFPVoxelAttribute, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_VoxelAttribute_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_VoxelAttribute_MetaData)) }; // 409723961
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_IsVisible_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_IsVisible_SetBit(void* Obj)
	{
		((LFPVoxelData_eventSetVoxelGridDataList_Parms*)Obj)->IsVisible = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_IsVisible = { "IsVisible", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPVoxelData_eventSetVoxelGridDataList_Parms), &Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_IsVisible_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_IsVisible_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_IsVisible_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_bUpdateMesh_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_bUpdateMesh_SetBit(void* Obj)
	{
		((LFPVoxelData_eventSetVoxelGridDataList_Parms*)Obj)->bUpdateMesh = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_bUpdateMesh = { "bUpdateMesh", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPVoxelData_eventSetVoxelGridDataList_Parms), &Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_bUpdateMesh_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_bUpdateMesh_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_bUpdateMesh_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_VoxelGridLocationList_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_VoxelGridLocationList,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_VoxelAttribute,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_IsVisible,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_bUpdateMesh,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::Function_MetaDataParams[] = {
		{ "Category", "VoxelData | Function" },
		{ "CPP_Default_bUpdateMesh", "true" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPVoxelData, nullptr, "SetVoxelGridDataList", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::LFPVoxelData_eventSetVoxelGridDataList_Parms), Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPVoxelData_UpdateChuck_Statics
	{
		struct LFPVoxelData_eventUpdateChuck_Parms
		{
			int32 UpdateCount;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_UpdateCount_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_UpdateCount;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_UpdateChuck_Statics::NewProp_UpdateCount_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPVoxelData_UpdateChuck_Statics::NewProp_UpdateCount = { "UpdateCount", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventUpdateChuck_Parms, UpdateCount), METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_UpdateChuck_Statics::NewProp_UpdateCount_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_UpdateChuck_Statics::NewProp_UpdateCount_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPVoxelData_UpdateChuck_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_UpdateChuck_Statics::NewProp_UpdateCount,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_UpdateChuck_Statics::Function_MetaDataParams[] = {
		{ "Category", "VoxelData | Function" },
		{ "CPP_Default_UpdateCount", "9999999" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPVoxelData_UpdateChuck_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPVoxelData, nullptr, "UpdateChuck", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPVoxelData_UpdateChuck_Statics::LFPVoxelData_eventUpdateChuck_Parms), Z_Construct_UFunction_ULFPVoxelData_UpdateChuck_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_UpdateChuck_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_UpdateChuck_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_UpdateChuck_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPVoxelData_UpdateChuck()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPVoxelData_UpdateChuck_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ULFPVoxelData);
	UClass* Z_Construct_UClass_ULFPVoxelData_NoRegister()
	{
		return ULFPVoxelData::StaticClass();
	}
	struct Z_Construct_UClass_ULFPVoxelData_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ContainerSetting_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_ContainerSetting;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ChuckData_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ChuckData_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ChuckData;
		static const UECodeGen_Private::FIntPropertyParams NewProp_UpdateChuckList_ElementProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_UpdateChuckList_MetaData[];
#endif
		static const UECodeGen_Private::FSetPropertyParams NewProp_UpdateChuckList;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULFPVoxelData_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ULFPVoxelData_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULFPVoxelData_GetContainerSize, "GetContainerSize" }, // 1222470925
		{ &Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute, "GetPoolAttribute" }, // 4236831372
		{ &Z_Construct_UFunction_ULFPVoxelData_IsChuckInitialized, "IsChuckInitialized" }, // 3678710791
		{ &Z_Construct_UFunction_ULFPVoxelData_MarkChuckForUpdate, "MarkChuckForUpdate" }, // 1990761464
		{ &Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData, "SetAllVoxelGridDataWithSingleData" }, // 1327241388
		{ &Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData, "SetupVoxelData" }, // 683281325
		{ &Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData, "SetVoxelGridData" }, // 2607414450
		{ &Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList, "SetVoxelGridDataList" }, // 3617240275
		{ &Z_Construct_UFunction_ULFPVoxelData_UpdateChuck, "UpdateChuck" }, // 1599670573
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPVoxelData_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Container/LFPVoxelData.h" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ContainerSetting_MetaData[] = {
		{ "Category", "VoxelData | Setting" },
		{ "Comment", "// Initialize Data\n" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
		{ "ToolTip", "Initialize Data" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ContainerSetting = { "ContainerSetting", nullptr, (EPropertyFlags)0x0020080000020015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPVoxelData, ContainerSetting), Z_Construct_UScriptStruct_FLFPVoxelContainerSetting, METADATA_PARAMS(Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ContainerSetting_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ContainerSetting_MetaData)) }; // 1390228499
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckData_Inner = { "ChuckData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPVoxelChuckData, METADATA_PARAMS(nullptr, 0) }; // 3322816980
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckData_MetaData[] = {
		{ "Comment", "// Runtime Data\n" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
		{ "ToolTip", "Runtime Data" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckData = { "ChuckData", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPVoxelData, ChuckData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckData_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckData_MetaData)) }; // 3322816980
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_UpdateChuckList_ElementProp = { "UpdateChuckList", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_UpdateChuckList_MetaData[] = {
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FSetPropertyParams Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_UpdateChuckList = { "UpdateChuckList", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPVoxelData, UpdateChuckList), METADATA_PARAMS(Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_UpdateChuckList_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_UpdateChuckList_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULFPVoxelData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ContainerSetting,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckData_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckData,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_UpdateChuckList_ElementProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_UpdateChuckList,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULFPVoxelData_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULFPVoxelData>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ULFPVoxelData_Statics::ClassParams = {
		&ULFPVoxelData::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ULFPVoxelData_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ULFPVoxelData_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_ULFPVoxelData_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPVoxelData_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULFPVoxelData()
	{
		if (!Z_Registration_Info_UClass_ULFPVoxelData.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULFPVoxelData.OuterSingleton, Z_Construct_UClass_ULFPVoxelData_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ULFPVoxelData.OuterSingleton;
	}
	template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<ULFPVoxelData>()
	{
		return ULFPVoxelData::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULFPVoxelData);
	struct Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_Statics::ScriptStructInfo[] = {
		{ FLFPVoxelAttribute::StaticStruct, Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewStructOps, TEXT("LFPVoxelAttribute"), &Z_Registration_Info_UScriptStruct_LFPVoxelAttribute, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLFPVoxelAttribute), 409723961U) },
		{ FLFPVoxelChuckData::StaticStruct, Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::NewStructOps, TEXT("LFPVoxelChuckData"), &Z_Registration_Info_UScriptStruct_LFPVoxelChuckData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLFPVoxelChuckData), 3322816980U) },
		{ FLFPVoxelContainerSetting::StaticStruct, Z_Construct_UScriptStruct_FLFPVoxelContainerSetting_Statics::NewStructOps, TEXT("LFPVoxelContainerSetting"), &Z_Registration_Info_UScriptStruct_LFPVoxelContainerSetting, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLFPVoxelContainerSetting), 1390228499U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ULFPVoxelData, ULFPVoxelData::StaticClass, TEXT("ULFPVoxelData"), &Z_Registration_Info_UClass_ULFPVoxelData, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULFPVoxelData), 684980865U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_4009344582(TEXT("/Script/LohFunctionPlugin"),
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_Statics::ClassInfo),
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
