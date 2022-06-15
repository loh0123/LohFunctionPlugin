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
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2D();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelChuckData();
	LOHFUNCTIONPLUGIN_API UFunction* Z_Construct_UDelegateFunction_ULFPVoxelData_OnChuckGeneration__DelegateSignature();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPVoxelData();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntVector();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPVoxelData_NoRegister();
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
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IsVisible_MetaData[];
#endif
		static void NewProp_IsVisible_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_IsVisible;
		static const UECodeGen_Private::FStructPropertyParams NewProp_CustomData_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CustomData_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_CustomData;
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
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_IsVisible_MetaData[] = {
		{ "Category", "LFPVoxelAttribute" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_IsVisible_SetBit(void* Obj)
	{
		((FLFPVoxelAttribute*)Obj)->IsVisible = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_IsVisible = { "IsVisible", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FLFPVoxelAttribute), &Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_IsVisible_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_IsVisible_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_IsVisible_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_CustomData_Inner = { "CustomData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_CustomData_MetaData[] = {
		{ "Category", "LFPVoxelAttribute" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_CustomData = { "CustomData", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelAttribute, CustomData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_CustomData_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_CustomData_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_VertexColor_MetaData[] = {
		{ "Category", "LFPVoxelAttribute" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_VertexColor = { "VertexColor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelAttribute, VertexColor), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_VertexColor_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_VertexColor_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_MaterialID_MetaData[] = {
		{ "Category", "LFPVoxelAttribute" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_MaterialID = { "MaterialID", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelAttribute, MaterialID), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_MaterialID_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_MaterialID_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_IsVisible,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_CustomData_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewProp_CustomData,
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
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLFPVoxelChuckData>();
	}
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::NewProp_VoxelData_Inner = { "VoxelData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPVoxelAttribute, METADATA_PARAMS(nullptr, 0) }; // 1933575918
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::NewProp_VoxelData_MetaData[] = {
		{ "Category", "LFPVoxelChuckData" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::NewProp_VoxelData = { "VoxelData", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPVoxelChuckData, VoxelData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::NewProp_VoxelData_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::NewProp_VoxelData_MetaData)) }; // 1933575918
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
	struct Z_Construct_UDelegateFunction_ULFPVoxelData_OnChuckGeneration__DelegateSignature_Statics
	{
		struct LFPVoxelData_eventOnChuckGeneration_Parms
		{
			int32 ChuckIndex;
			FIntVector StartVoxelGridLocation;
			FIntVector EndVoxelGridLocation;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_ChuckIndex;
		static const UECodeGen_Private::FStructPropertyParams NewProp_StartVoxelGridLocation;
		static const UECodeGen_Private::FStructPropertyParams NewProp_EndVoxelGridLocation;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_ULFPVoxelData_OnChuckGeneration__DelegateSignature_Statics::NewProp_ChuckIndex = { "ChuckIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventOnChuckGeneration_Parms, ChuckIndex), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_ULFPVoxelData_OnChuckGeneration__DelegateSignature_Statics::NewProp_StartVoxelGridLocation = { "StartVoxelGridLocation", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventOnChuckGeneration_Parms, StartVoxelGridLocation), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_ULFPVoxelData_OnChuckGeneration__DelegateSignature_Statics::NewProp_EndVoxelGridLocation = { "EndVoxelGridLocation", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventOnChuckGeneration_Parms, EndVoxelGridLocation), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_ULFPVoxelData_OnChuckGeneration__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_ULFPVoxelData_OnChuckGeneration__DelegateSignature_Statics::NewProp_ChuckIndex,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_ULFPVoxelData_OnChuckGeneration__DelegateSignature_Statics::NewProp_StartVoxelGridLocation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_ULFPVoxelData_OnChuckGeneration__DelegateSignature_Statics::NewProp_EndVoxelGridLocation,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_ULFPVoxelData_OnChuckGeneration__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_ULFPVoxelData_OnChuckGeneration__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPVoxelData, nullptr, "OnChuckGeneration__DelegateSignature", nullptr, nullptr, sizeof(Z_Construct_UDelegateFunction_ULFPVoxelData_OnChuckGeneration__DelegateSignature_Statics::LFPVoxelData_eventOnChuckGeneration_Parms), Z_Construct_UDelegateFunction_ULFPVoxelData_OnChuckGeneration__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ULFPVoxelData_OnChuckGeneration__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00930000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_ULFPVoxelData_OnChuckGeneration__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ULFPVoxelData_OnChuckGeneration__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_ULFPVoxelData_OnChuckGeneration__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_ULFPVoxelData_OnChuckGeneration__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	DEFINE_FUNCTION(ULFPVoxelData::execSetAllVoxelGridDataWithSingleData)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_ChuckIndex);
		P_GET_STRUCT_REF(FLFPVoxelAttribute,Z_Param_Out_VoxelAttribute);
		P_GET_UBOOL(Z_Param_bUpdateMesh);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetAllVoxelGridDataWithSingleData(Z_Param_ChuckIndex,Z_Param_Out_VoxelAttribute,Z_Param_bUpdateMesh);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPVoxelData::execSetVoxelGridDataListWithSingleData)
	{
		P_GET_TARRAY_REF(FIntVector,Z_Param_Out_VoxelGridLocationList);
		P_GET_STRUCT_REF(FLFPVoxelAttribute,Z_Param_Out_VoxelAttribute);
		P_GET_UBOOL(Z_Param_bUpdateMesh);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetVoxelGridDataListWithSingleData(Z_Param_Out_VoxelGridLocationList,Z_Param_Out_VoxelAttribute,Z_Param_bUpdateMesh);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPVoxelData::execSetVoxelGridDataList)
	{
		P_GET_TARRAY_REF(FIntVector,Z_Param_Out_VoxelGridLocationList);
		P_GET_TARRAY_REF(FLFPVoxelAttribute,Z_Param_Out_VoxelAttributeList);
		P_GET_UBOOL(Z_Param_bUpdateMesh);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetVoxelGridDataList(Z_Param_Out_VoxelGridLocationList,Z_Param_Out_VoxelAttributeList,Z_Param_bUpdateMesh);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPVoxelData::execSetVoxelGridData)
	{
		P_GET_STRUCT(FIntVector,Z_Param_VoxelGridLocation);
		P_GET_STRUCT_REF(FLFPVoxelAttribute,Z_Param_Out_VoxelAttribute);
		P_GET_UBOOL(Z_Param_bUpdateMesh);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetVoxelGridData(Z_Param_VoxelGridLocation,Z_Param_Out_VoxelAttribute,Z_Param_bUpdateMesh);
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
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_ChuckGridLocation);
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_StartVoxelLocation);
		P_GET_STRUCT_REF(FVector,Z_Param_Out_ChuckMeshSize);
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_ChuckVoxelGridSize);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->GetPoolAttribute(Z_Param_ChuckIndex,Z_Param_Out_ChuckGridLocation,Z_Param_Out_StartVoxelLocation,Z_Param_Out_ChuckMeshSize,Z_Param_Out_ChuckVoxelGridSize);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPVoxelData::execSetupVoxelData)
	{
		P_GET_STRUCT(FVector,Z_Param_NewMeshSize);
		P_GET_STRUCT(FIntVector,Z_Param_NewPoolGridSize);
		P_GET_STRUCT(FIntVector,Z_Param_NewChuckGridSize);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetupVoxelData(Z_Param_NewMeshSize,Z_Param_NewPoolGridSize,Z_Param_NewChuckGridSize);
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
	void ULFPVoxelData::StaticRegisterNativesULFPVoxelData()
	{
		UClass* Class = ULFPVoxelData::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetPoolAttribute", &ULFPVoxelData::execGetPoolAttribute },
			{ "IsChuckInitialized", &ULFPVoxelData::execIsChuckInitialized },
			{ "MarkChuckForUpdate", &ULFPVoxelData::execMarkChuckForUpdate },
			{ "SetAllVoxelGridDataWithSingleData", &ULFPVoxelData::execSetAllVoxelGridDataWithSingleData },
			{ "SetupVoxelData", &ULFPVoxelData::execSetupVoxelData },
			{ "SetVoxelGridData", &ULFPVoxelData::execSetVoxelGridData },
			{ "SetVoxelGridDataList", &ULFPVoxelData::execSetVoxelGridDataList },
			{ "SetVoxelGridDataListWithSingleData", &ULFPVoxelData::execSetVoxelGridDataListWithSingleData },
			{ "UpdateChuck", &ULFPVoxelData::execUpdateChuck },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics
	{
		struct LFPVoxelData_eventGetPoolAttribute_Parms
		{
			int32 ChuckIndex;
			FIntVector ChuckGridLocation;
			FIntVector StartVoxelLocation;
			FVector ChuckMeshSize;
			FIntVector ChuckVoxelGridSize;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ChuckIndex_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_ChuckIndex;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ChuckGridLocation;
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
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::NewProp_ChuckGridLocation = { "ChuckGridLocation", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventGetPoolAttribute_Parms, ChuckGridLocation), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::NewProp_StartVoxelLocation = { "StartVoxelLocation", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventGetPoolAttribute_Parms, StartVoxelLocation), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::NewProp_ChuckMeshSize = { "ChuckMeshSize", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventGetPoolAttribute_Parms, ChuckMeshSize), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::NewProp_ChuckVoxelGridSize = { "ChuckVoxelGridSize", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventGetPoolAttribute_Parms, ChuckVoxelGridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::NewProp_ChuckIndex,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute_Statics::NewProp_ChuckGridLocation,
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
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_VoxelAttribute = { "VoxelAttribute", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventSetAllVoxelGridDataWithSingleData_Parms, VoxelAttribute), Z_Construct_UScriptStruct_FLFPVoxelAttribute, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_VoxelAttribute_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData_Statics::NewProp_VoxelAttribute_MetaData)) }; // 1933575918
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
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewMeshSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewPoolGridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::NewProp_NewChuckGridSize,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData_Statics::Function_MetaDataParams[] = {
		{ "Category", "VoxelData | Function" },
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
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_VoxelAttribute = { "VoxelAttribute", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventSetVoxelGridData_Parms, VoxelAttribute), Z_Construct_UScriptStruct_FLFPVoxelAttribute, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_VoxelAttribute_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData_Statics::NewProp_VoxelAttribute_MetaData)) }; // 1933575918
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
			TArray<FLFPVoxelAttribute> VoxelAttributeList;
			bool bUpdateMesh;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_VoxelGridLocationList_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VoxelGridLocationList_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_VoxelGridLocationList;
		static const UECodeGen_Private::FStructPropertyParams NewProp_VoxelAttributeList_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VoxelAttributeList_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_VoxelAttributeList;
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
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_VoxelAttributeList_Inner = { "VoxelAttributeList", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPVoxelAttribute, METADATA_PARAMS(nullptr, 0) }; // 1933575918
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_VoxelAttributeList_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_VoxelAttributeList = { "VoxelAttributeList", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventSetVoxelGridDataList_Parms, VoxelAttributeList), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_VoxelAttributeList_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_VoxelAttributeList_MetaData)) }; // 1933575918
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
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_VoxelAttributeList_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList_Statics::NewProp_VoxelAttributeList,
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
	struct Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics
	{
		struct LFPVoxelData_eventSetVoxelGridDataListWithSingleData_Parms
		{
			TArray<FIntVector> VoxelGridLocationList;
			FLFPVoxelAttribute VoxelAttribute;
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
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::NewProp_VoxelGridLocationList_Inner = { "VoxelGridLocationList", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::NewProp_VoxelGridLocationList_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::NewProp_VoxelGridLocationList = { "VoxelGridLocationList", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventSetVoxelGridDataListWithSingleData_Parms, VoxelGridLocationList), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::NewProp_VoxelGridLocationList_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::NewProp_VoxelGridLocationList_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::NewProp_VoxelAttribute_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::NewProp_VoxelAttribute = { "VoxelAttribute", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPVoxelData_eventSetVoxelGridDataListWithSingleData_Parms, VoxelAttribute), Z_Construct_UScriptStruct_FLFPVoxelAttribute, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::NewProp_VoxelAttribute_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::NewProp_VoxelAttribute_MetaData)) }; // 1933575918
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::NewProp_bUpdateMesh_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::NewProp_bUpdateMesh_SetBit(void* Obj)
	{
		((LFPVoxelData_eventSetVoxelGridDataListWithSingleData_Parms*)Obj)->bUpdateMesh = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::NewProp_bUpdateMesh = { "bUpdateMesh", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPVoxelData_eventSetVoxelGridDataListWithSingleData_Parms), &Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::NewProp_bUpdateMesh_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::NewProp_bUpdateMesh_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::NewProp_bUpdateMesh_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::NewProp_VoxelGridLocationList_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::NewProp_VoxelGridLocationList,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::NewProp_VoxelAttribute,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::NewProp_bUpdateMesh,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::Function_MetaDataParams[] = {
		{ "Category", "VoxelData | Function" },
		{ "CPP_Default_bUpdateMesh", "true" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPVoxelData, nullptr, "SetVoxelGridDataListWithSingleData", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::LFPVoxelData_eventSetVoxelGridDataListWithSingleData_Parms), Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData_Statics::FuncParams);
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
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OnChuckGeneration_MetaData[];
#endif
		static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnChuckGeneration;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULFPVoxelData_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ULFPVoxelData_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULFPVoxelData_GetPoolAttribute, "GetPoolAttribute" }, // 4127497440
		{ &Z_Construct_UFunction_ULFPVoxelData_IsChuckInitialized, "IsChuckInitialized" }, // 3678710791
		{ &Z_Construct_UFunction_ULFPVoxelData_MarkChuckForUpdate, "MarkChuckForUpdate" }, // 1990761464
		{ &Z_Construct_UDelegateFunction_ULFPVoxelData_OnChuckGeneration__DelegateSignature, "OnChuckGeneration__DelegateSignature" }, // 1924044401
		{ &Z_Construct_UFunction_ULFPVoxelData_SetAllVoxelGridDataWithSingleData, "SetAllVoxelGridDataWithSingleData" }, // 147577900
		{ &Z_Construct_UFunction_ULFPVoxelData_SetupVoxelData, "SetupVoxelData" }, // 2135786032
		{ &Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridData, "SetVoxelGridData" }, // 878729034
		{ &Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataList, "SetVoxelGridDataList" }, // 3245775166
		{ &Z_Construct_UFunction_ULFPVoxelData_SetVoxelGridDataListWithSingleData, "SetVoxelGridDataListWithSingleData" }, // 1924042767
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
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckData_Inner = { "ChuckData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPVoxelChuckData, METADATA_PARAMS(nullptr, 0) }; // 507177860
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckData_MetaData[] = {
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckData = { "ChuckData", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPVoxelData, ChuckData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckData_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckData_MetaData)) }; // 507177860
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_UpdateChuckList_ElementProp = { "UpdateChuckList", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_UpdateChuckList_MetaData[] = {
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FSetPropertyParams Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_UpdateChuckList = { "UpdateChuckList", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPVoxelData, UpdateChuckList), METADATA_PARAMS(Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_UpdateChuckList_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_UpdateChuckList_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_PoolLength_MetaData[] = {
		{ "Category", "VoxelData | Cache" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_PoolLength = { "PoolLength", nullptr, (EPropertyFlags)0x0020080000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPVoxelData, PoolLength), METADATA_PARAMS(Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_PoolLength_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_PoolLength_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckVoxelLength_MetaData[] = {
		{ "Category", "VoxelData | Cache" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckVoxelLength = { "ChuckVoxelLength", nullptr, (EPropertyFlags)0x0020080000020015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPVoxelData, ChuckVoxelLength), METADATA_PARAMS(Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckVoxelLength_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckVoxelLength_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_MeshSize_MetaData[] = {
		{ "Category", "VoxelData | Setting" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_MeshSize = { "MeshSize", nullptr, (EPropertyFlags)0x0020080000020015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPVoxelData, MeshSize), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_MeshSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_MeshSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_PoolGridSize_MetaData[] = {
		{ "Category", "VoxelData | Setting" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_PoolGridSize = { "PoolGridSize", nullptr, (EPropertyFlags)0x0020080000020015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPVoxelData, PoolGridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_PoolGridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_PoolGridSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckGridSize_MetaData[] = {
		{ "Category", "VoxelData | Setting" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckGridSize = { "ChuckGridSize", nullptr, (EPropertyFlags)0x0020080000020015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPVoxelData, ChuckGridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckGridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckGridSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_OnChuckGeneration_MetaData[] = {
		{ "DisplayName", "ChuckBegin" },
		{ "ModuleRelativePath", "Public/Container/LFPVoxelData.h" },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_OnChuckGeneration = { "OnChuckGeneration", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPVoxelData, OnChuckGeneration), Z_Construct_UDelegateFunction_ULFPVoxelData_OnChuckGeneration__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_OnChuckGeneration_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_OnChuckGeneration_MetaData)) }; // 1924044401
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULFPVoxelData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckData_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckData,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_UpdateChuckList_ElementProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_UpdateChuckList,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_PoolLength,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckVoxelLength,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_MeshSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_PoolGridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_ChuckGridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPVoxelData_Statics::NewProp_OnChuckGeneration,
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
		0x009000A0u,
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
		{ FLFPVoxelAttribute::StaticStruct, Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics::NewStructOps, TEXT("LFPVoxelAttribute"), &Z_Registration_Info_UScriptStruct_LFPVoxelAttribute, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLFPVoxelAttribute), 1933575918U) },
		{ FLFPVoxelChuckData::StaticStruct, Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics::NewStructOps, TEXT("LFPVoxelChuckData"), &Z_Registration_Info_UScriptStruct_LFPVoxelChuckData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLFPVoxelChuckData), 507177860U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ULFPVoxelData, ULFPVoxelData::StaticClass, TEXT("ULFPVoxelData"), &Z_Registration_Info_UClass_ULFPVoxelData, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULFPVoxelData), 2885843462U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_2271827938(TEXT("/Script/LohFunctionPlugin"),
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_Statics::ClassInfo),
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
