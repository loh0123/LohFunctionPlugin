// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LohFunctionPlugin/Public/Components/LFPWorldGrid.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLFPWorldGrid() {}
// Cross Module References
	LOHFUNCTIONPLUGIN_API UEnum* Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType();
	UPackage* Z_Construct_UPackage__Script_LohFunctionPlugin();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPWorldGrid_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPWorldGrid();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntVector();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_ELFPGridType;
	static UEnum* ELFPGridType_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_ELFPGridType.OuterSingleton)
		{
			Z_Registration_Info_UEnum_ELFPGridType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("ELFPGridType"));
		}
		return Z_Registration_Info_UEnum_ELFPGridType.OuterSingleton;
	}
	template<> LOHFUNCTIONPLUGIN_API UEnum* StaticEnum<ELFPGridType>()
	{
		return ELFPGridType_StaticEnum();
	}
	struct Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType_Statics::Enumerators[] = {
		{ "ELFPGridType::Rectangular", (int64)ELFPGridType::Rectangular },
		{ "ELFPGridType::Hexagon", (int64)ELFPGridType::Hexagon },
		{ "ELFPGridType::Triangle", (int64)ELFPGridType::Triangle },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Hexagon.DisplayName", "Hexagon" },
		{ "Hexagon.Name", "ELFPGridType::Hexagon" },
		{ "ModuleRelativePath", "Public/Components/LFPWorldGrid.h" },
		{ "Rectangular.DisplayName", "Rectangular" },
		{ "Rectangular.Name", "ELFPGridType::Rectangular" },
		{ "Triangle.DisplayName", "Triangle" },
		{ "Triangle.Name", "ELFPGridType::Triangle" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
		nullptr,
		"ELFPGridType",
		"ELFPGridType",
		Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType()
	{
		if (!Z_Registration_Info_UEnum_ELFPGridType.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ELFPGridType.InnerSingleton, Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_ELFPGridType.InnerSingleton;
	}
	DEFINE_FUNCTION(ULFPWorldGrid::execGetHalfSize)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FVector*)Z_Param__Result=P_THIS->GetHalfSize();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPWorldGrid::execIndexToWorldLocation)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_Index);
		P_GET_UBOOL(Z_Param_AddHalfGap);
		P_GET_STRUCT_REF(FVector,Z_Param_Out_ReturnLocation);
		P_GET_STRUCT_REF(FRotator,Z_Param_Out_ReturnRotation);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->IndexToWorldLocation(Z_Param_Index,Z_Param_AddHalfGap,Z_Param_Out_ReturnLocation,Z_Param_Out_ReturnRotation);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPWorldGrid::execGridLocationToWorldLocation)
	{
		P_GET_STRUCT(FIntVector,Z_Param_Location);
		P_GET_UBOOL(Z_Param_AddHalfGap);
		P_GET_STRUCT_REF(FVector,Z_Param_Out_ReturnLocation);
		P_GET_STRUCT_REF(FRotator,Z_Param_Out_ReturnRotation);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->GridLocationToWorldLocation(Z_Param_Location,Z_Param_AddHalfGap,Z_Param_Out_ReturnLocation,Z_Param_Out_ReturnRotation);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPWorldGrid::execIsWorldLocationValid)
	{
		P_GET_STRUCT(FVector,Z_Param_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->IsWorldLocationValid(Z_Param_Location);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPWorldGrid::execWordlLocationToGridLocation)
	{
		P_GET_STRUCT_REF(FVector,Z_Param_Out_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FIntVector*)Z_Param__Result=P_THIS->WordlLocationToGridLocation(Z_Param_Out_Location);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPWorldGrid::execWordlLocationToIndex)
	{
		P_GET_STRUCT_REF(FVector,Z_Param_Out_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->WordlLocationToIndex(Z_Param_Out_Location);
		P_NATIVE_END;
	}
	void ULFPWorldGrid::StaticRegisterNativesULFPWorldGrid()
	{
		UClass* Class = ULFPWorldGrid::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetHalfSize", &ULFPWorldGrid::execGetHalfSize },
			{ "GridLocationToWorldLocation", &ULFPWorldGrid::execGridLocationToWorldLocation },
			{ "IndexToWorldLocation", &ULFPWorldGrid::execIndexToWorldLocation },
			{ "IsWorldLocationValid", &ULFPWorldGrid::execIsWorldLocationValid },
			{ "WordlLocationToGridLocation", &ULFPWorldGrid::execWordlLocationToGridLocation },
			{ "WordlLocationToIndex", &ULFPWorldGrid::execWordlLocationToIndex },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULFPWorldGrid_GetHalfSize_Statics
	{
		struct LFPWorldGrid_eventGetHalfSize_Parms
		{
			FVector ReturnValue;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPWorldGrid_GetHalfSize_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventGetHalfSize_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPWorldGrid_GetHalfSize_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_GetHalfSize_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_GetHalfSize_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/Components/LFPWorldGrid.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPWorldGrid_GetHalfSize_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPWorldGrid, nullptr, "GetHalfSize", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPWorldGrid_GetHalfSize_Statics::LFPWorldGrid_eventGetHalfSize_Parms), Z_Construct_UFunction_ULFPWorldGrid_GetHalfSize_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_GetHalfSize_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_GetHalfSize_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_GetHalfSize_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPWorldGrid_GetHalfSize()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPWorldGrid_GetHalfSize_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics
	{
		struct LFPWorldGrid_eventGridLocationToWorldLocation_Parms
		{
			FIntVector Location;
			bool AddHalfGap;
			FVector ReturnLocation;
			FRotator ReturnRotation;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Location;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AddHalfGap_MetaData[];
#endif
		static void NewProp_AddHalfGap_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_AddHalfGap;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnLocation;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnRotation;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventGridLocationToWorldLocation_Parms, Location), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_Location_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_AddHalfGap_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_AddHalfGap_SetBit(void* Obj)
	{
		((LFPWorldGrid_eventGridLocationToWorldLocation_Parms*)Obj)->AddHalfGap = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_AddHalfGap = { "AddHalfGap", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPWorldGrid_eventGridLocationToWorldLocation_Parms), &Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_AddHalfGap_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_AddHalfGap_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_AddHalfGap_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_ReturnLocation = { "ReturnLocation", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventGridLocationToWorldLocation_Parms, ReturnLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_ReturnRotation = { "ReturnRotation", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventGridLocationToWorldLocation_Parms, ReturnRotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPWorldGrid_eventGridLocationToWorldLocation_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPWorldGrid_eventGridLocationToWorldLocation_Parms), &Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_Location,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_AddHalfGap,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_ReturnLocation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_ReturnRotation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/Components/LFPWorldGrid.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPWorldGrid, nullptr, "GridLocationToWorldLocation", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::LFPWorldGrid_eventGridLocationToWorldLocation_Parms), Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics
	{
		struct LFPWorldGrid_eventIndexToWorldLocation_Parms
		{
			int32 Index;
			bool AddHalfGap;
			FVector ReturnLocation;
			FRotator ReturnRotation;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Index_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Index;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AddHalfGap_MetaData[];
#endif
		static void NewProp_AddHalfGap_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_AddHalfGap;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnLocation;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnRotation;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_Index_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventIndexToWorldLocation_Parms, Index), METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_Index_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_Index_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_AddHalfGap_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_AddHalfGap_SetBit(void* Obj)
	{
		((LFPWorldGrid_eventIndexToWorldLocation_Parms*)Obj)->AddHalfGap = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_AddHalfGap = { "AddHalfGap", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPWorldGrid_eventIndexToWorldLocation_Parms), &Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_AddHalfGap_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_AddHalfGap_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_AddHalfGap_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_ReturnLocation = { "ReturnLocation", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventIndexToWorldLocation_Parms, ReturnLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_ReturnRotation = { "ReturnRotation", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventIndexToWorldLocation_Parms, ReturnRotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPWorldGrid_eventIndexToWorldLocation_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPWorldGrid_eventIndexToWorldLocation_Parms), &Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_Index,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_AddHalfGap,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_ReturnLocation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_ReturnRotation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/Components/LFPWorldGrid.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPWorldGrid, nullptr, "IndexToWorldLocation", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::LFPWorldGrid_eventIndexToWorldLocation_Parms), Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics
	{
		struct LFPWorldGrid_eventIsWorldLocationValid_Parms
		{
			FVector Location;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Location;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventIsWorldLocationValid_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::NewProp_Location_MetaData)) };
	void Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPWorldGrid_eventIsWorldLocationValid_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPWorldGrid_eventIsWorldLocationValid_Parms), &Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::NewProp_Location,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/Components/LFPWorldGrid.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPWorldGrid, nullptr, "IsWorldLocationValid", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::LFPWorldGrid_eventIsWorldLocationValid_Parms), Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics
	{
		struct LFPWorldGrid_eventWordlLocationToGridLocation_Parms
		{
			FVector Location;
			FIntVector ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Location;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventWordlLocationToGridLocation_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::NewProp_Location_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventWordlLocationToGridLocation_Parms, ReturnValue), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::NewProp_Location,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/Components/LFPWorldGrid.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPWorldGrid, nullptr, "WordlLocationToGridLocation", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::LFPWorldGrid_eventWordlLocationToGridLocation_Parms), Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics
	{
		struct LFPWorldGrid_eventWordlLocationToIndex_Parms
		{
			FVector Location;
			int32 ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Location;
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventWordlLocationToIndex_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::NewProp_Location_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventWordlLocationToIndex_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::NewProp_Location,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/Components/LFPWorldGrid.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPWorldGrid, nullptr, "WordlLocationToIndex", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::LFPWorldGrid_eventWordlLocationToIndex_Parms), Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ULFPWorldGrid);
	UClass* Z_Construct_UClass_ULFPWorldGrid_NoRegister()
	{
		return ULFPWorldGrid::StaticClass();
	}
	struct Z_Construct_UClass_ULFPWorldGrid_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bCenterOrigin_MetaData[];
#endif
		static void NewProp_bCenterOrigin_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bCenterOrigin;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridGap_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridGap;
		static const UECodeGen_Private::FBytePropertyParams NewProp_GridType_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridType_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_GridType;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULFPWorldGrid_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USceneComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ULFPWorldGrid_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULFPWorldGrid_GetHalfSize, "GetHalfSize" }, // 3521817328
		{ &Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation, "GridLocationToWorldLocation" }, // 2886816444
		{ &Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation, "IndexToWorldLocation" }, // 1433783241
		{ &Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid, "IsWorldLocationValid" }, // 1259855478
		{ &Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation, "WordlLocationToGridLocation" }, // 1538045106
		{ &Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex, "WordlLocationToIndex" }, // 1879360498
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPWorldGrid_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "Components/LFPWorldGrid.h" },
		{ "ModuleRelativePath", "Public/Components/LFPWorldGrid.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_bCenterOrigin_MetaData[] = {
		{ "Category", "LFPGridSystem | Variable" },
		{ "ModuleRelativePath", "Public/Components/LFPWorldGrid.h" },
	};
#endif
	void Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_bCenterOrigin_SetBit(void* Obj)
	{
		((ULFPWorldGrid*)Obj)->bCenterOrigin = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_bCenterOrigin = { "bCenterOrigin", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ULFPWorldGrid), &Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_bCenterOrigin_SetBit, METADATA_PARAMS(Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_bCenterOrigin_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_bCenterOrigin_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridSize_MetaData[] = {
		{ "Category", "LFPGridSystem | Variable" },
		{ "ModuleRelativePath", "Public/Components/LFPWorldGrid.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridSize = { "GridSize", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPWorldGrid, GridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridGap_MetaData[] = {
		{ "Category", "LFPGridSystem | Variable" },
		{ "ModuleRelativePath", "Public/Components/LFPWorldGrid.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridGap = { "GridGap", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPWorldGrid, GridGap), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridGap_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridGap_MetaData)) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridType_MetaData[] = {
		{ "Category", "LFPGridSystem | Variable" },
		{ "ModuleRelativePath", "Public/Components/LFPWorldGrid.h" },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridType = { "GridType", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPWorldGrid, GridType), Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType, METADATA_PARAMS(Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridType_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridType_MetaData)) }; // 2599491439
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULFPWorldGrid_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_bCenterOrigin,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridGap,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridType_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridType,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULFPWorldGrid_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULFPWorldGrid>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ULFPWorldGrid_Statics::ClassParams = {
		&ULFPWorldGrid::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ULFPWorldGrid_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ULFPWorldGrid_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ULFPWorldGrid_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPWorldGrid_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULFPWorldGrid()
	{
		if (!Z_Registration_Info_UClass_ULFPWorldGrid.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULFPWorldGrid.OuterSingleton, Z_Construct_UClass_ULFPWorldGrid_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ULFPWorldGrid.OuterSingleton;
	}
	template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<ULFPWorldGrid>()
	{
		return ULFPWorldGrid::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULFPWorldGrid);
	struct Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Components_LFPWorldGrid_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Components_LFPWorldGrid_h_Statics::EnumInfo[] = {
		{ ELFPGridType_StaticEnum, TEXT("ELFPGridType"), &Z_Registration_Info_UEnum_ELFPGridType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2599491439U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Components_LFPWorldGrid_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ULFPWorldGrid, ULFPWorldGrid::StaticClass, TEXT("ULFPWorldGrid"), &Z_Registration_Info_UClass_ULFPWorldGrid, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULFPWorldGrid), 2195748421U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Components_LFPWorldGrid_h_1203792763(TEXT("/Script/LohFunctionPlugin"),
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Components_LFPWorldGrid_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Components_LFPWorldGrid_h_Statics::ClassInfo),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Components_LFPWorldGrid_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Components_LFPWorldGrid_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
