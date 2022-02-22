// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LohFunctionPlugin/Public/Helper/LFPWorldGrid.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLFPWorldGrid() {}
// Cross Module References
	LOHFUNCTIONPLUGIN_API UEnum* Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType();
	UPackage* Z_Construct_UPackage__Script_LohFunctionPlugin();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPWorldGrid_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPWorldGrid();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntVector();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
// End Cross Module References
	static UEnum* ELFPGridType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("ELFPGridType"));
		}
		return Singleton;
	}
	template<> LOHFUNCTIONPLUGIN_API UEnum* StaticEnum<ELFPGridType>()
	{
		return ELFPGridType_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ELFPGridType(ELFPGridType_StaticEnum, TEXT("/Script/LohFunctionPlugin"), TEXT("ELFPGridType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType_Hash() { return 323318376U; }
	UEnum* Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_LohFunctionPlugin();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ELFPGridType"), 0, Get_Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ELFPGridType::Rectangular", (int64)ELFPGridType::Rectangular },
				{ "ELFPGridType::Hexagon", (int64)ELFPGridType::Hexagon },
				{ "ELFPGridType::Triangle", (int64)ELFPGridType::Triangle },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "Hexagon.DisplayName", "Hexagon" },
				{ "Hexagon.Name", "ELFPGridType::Hexagon" },
				{ "ModuleRelativePath", "Public/Helper/LFPWorldGrid.h" },
				{ "Rectangular.DisplayName", "Rectangular" },
				{ "Rectangular.Name", "ELFPGridType::Rectangular" },
				{ "Triangle.DisplayName", "Triangle" },
				{ "Triangle.Name", "ELFPGridType::Triangle" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
				nullptr,
				"ELFPGridType",
				"ELFPGridType",
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
			{ "GridLocationToWorldLocation", &ULFPWorldGrid::execGridLocationToWorldLocation },
			{ "IndexToWorldLocation", &ULFPWorldGrid::execIndexToWorldLocation },
			{ "IsWorldLocationValid", &ULFPWorldGrid::execIsWorldLocationValid },
			{ "WordlLocationToGridLocation", &ULFPWorldGrid::execWordlLocationToGridLocation },
			{ "WordlLocationToIndex", &ULFPWorldGrid::execWordlLocationToIndex },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
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
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Location;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AddHalfGap_MetaData[];
#endif
		static void NewProp_AddHalfGap_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_AddHalfGap;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnLocation;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnRotation;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventGridLocationToWorldLocation_Parms, Location), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_Location_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_AddHalfGap_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_AddHalfGap_SetBit(void* Obj)
	{
		((LFPWorldGrid_eventGridLocationToWorldLocation_Parms*)Obj)->AddHalfGap = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_AddHalfGap = { "AddHalfGap", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPWorldGrid_eventGridLocationToWorldLocation_Parms), &Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_AddHalfGap_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_AddHalfGap_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_AddHalfGap_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_ReturnLocation = { "ReturnLocation", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventGridLocationToWorldLocation_Parms, ReturnLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_ReturnRotation = { "ReturnRotation", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventGridLocationToWorldLocation_Parms, ReturnRotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPWorldGrid_eventGridLocationToWorldLocation_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPWorldGrid_eventGridLocationToWorldLocation_Parms), &Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_AddHalfGap,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_ReturnLocation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_ReturnRotation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/Helper/LFPWorldGrid.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPWorldGrid, nullptr, "GridLocationToWorldLocation", nullptr, nullptr, sizeof(LFPWorldGrid_eventGridLocationToWorldLocation_Parms), Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation_Statics::FuncParams);
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
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Index_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Index;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AddHalfGap_MetaData[];
#endif
		static void NewProp_AddHalfGap_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_AddHalfGap;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnLocation;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnRotation;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_Index_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventIndexToWorldLocation_Parms, Index), METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_Index_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_Index_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_AddHalfGap_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_AddHalfGap_SetBit(void* Obj)
	{
		((LFPWorldGrid_eventIndexToWorldLocation_Parms*)Obj)->AddHalfGap = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_AddHalfGap = { "AddHalfGap", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPWorldGrid_eventIndexToWorldLocation_Parms), &Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_AddHalfGap_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_AddHalfGap_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_AddHalfGap_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_ReturnLocation = { "ReturnLocation", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventIndexToWorldLocation_Parms, ReturnLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_ReturnRotation = { "ReturnRotation", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventIndexToWorldLocation_Parms, ReturnRotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPWorldGrid_eventIndexToWorldLocation_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPWorldGrid_eventIndexToWorldLocation_Parms), &Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_Index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_AddHalfGap,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_ReturnLocation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_ReturnRotation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/Helper/LFPWorldGrid.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPWorldGrid, nullptr, "IndexToWorldLocation", nullptr, nullptr, sizeof(LFPWorldGrid_eventIndexToWorldLocation_Parms), Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation_Statics::FuncParams);
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
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Location;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventIsWorldLocationValid_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::NewProp_Location_MetaData)) };
	void Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPWorldGrid_eventIsWorldLocationValid_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPWorldGrid_eventIsWorldLocationValid_Parms), &Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/Helper/LFPWorldGrid.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPWorldGrid, nullptr, "IsWorldLocationValid", nullptr, nullptr, sizeof(LFPWorldGrid_eventIsWorldLocationValid_Parms), Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid_Statics::FuncParams);
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
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Location;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventWordlLocationToGridLocation_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::NewProp_Location_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventWordlLocationToGridLocation_Parms, ReturnValue), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/Helper/LFPWorldGrid.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPWorldGrid, nullptr, "WordlLocationToGridLocation", nullptr, nullptr, sizeof(LFPWorldGrid_eventWordlLocationToGridLocation_Parms), Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation_Statics::FuncParams);
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
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Location;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventWordlLocationToIndex_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::NewProp_Location_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPWorldGrid_eventWordlLocationToIndex_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/Helper/LFPWorldGrid.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPWorldGrid, nullptr, "WordlLocationToIndex", nullptr, nullptr, sizeof(LFPWorldGrid_eventWordlLocationToIndex_Parms), Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ULFPWorldGrid_NoRegister()
	{
		return ULFPWorldGrid::StaticClass();
	}
	struct Z_Construct_UClass_ULFPWorldGrid_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GridSize_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_GridSize;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GridGap_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_GridGap;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_GridType_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GridType_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_GridType;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULFPWorldGrid_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USceneComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ULFPWorldGrid_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULFPWorldGrid_GridLocationToWorldLocation, "GridLocationToWorldLocation" }, // 1857083855
		{ &Z_Construct_UFunction_ULFPWorldGrid_IndexToWorldLocation, "IndexToWorldLocation" }, // 4126935395
		{ &Z_Construct_UFunction_ULFPWorldGrid_IsWorldLocationValid, "IsWorldLocationValid" }, // 3343893890
		{ &Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToGridLocation, "WordlLocationToGridLocation" }, // 3821230937
		{ &Z_Construct_UFunction_ULFPWorldGrid_WordlLocationToIndex, "WordlLocationToIndex" }, // 1407295348
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPWorldGrid_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "Helper/LFPWorldGrid.h" },
		{ "ModuleRelativePath", "Public/Helper/LFPWorldGrid.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridSize_MetaData[] = {
		{ "Category", "LFPGridSystem | Variable" },
		{ "ModuleRelativePath", "Public/Helper/LFPWorldGrid.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridSize = { "GridSize", nullptr, (EPropertyFlags)0x0020080000000015, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPWorldGrid, GridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridSize_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridGap_MetaData[] = {
		{ "Category", "LFPGridSystem | Variable" },
		{ "ModuleRelativePath", "Public/Helper/LFPWorldGrid.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridGap = { "GridGap", nullptr, (EPropertyFlags)0x0020080000000015, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPWorldGrid, GridGap), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridGap_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridGap_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridType_MetaData[] = {
		{ "Category", "LFPGridSystem | Variable" },
		{ "ModuleRelativePath", "Public/Helper/LFPWorldGrid.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridType = { "GridType", nullptr, (EPropertyFlags)0x0020080000000015, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPWorldGrid, GridType), Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType, METADATA_PARAMS(Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridType_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridType_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULFPWorldGrid_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridSize,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridGap,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridType_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPWorldGrid_Statics::NewProp_GridType,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULFPWorldGrid_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULFPWorldGrid>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULFPWorldGrid_Statics::ClassParams = {
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
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULFPWorldGrid_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULFPWorldGrid, 2119470376);
	template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<ULFPWorldGrid>()
	{
		return ULFPWorldGrid::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULFPWorldGrid(Z_Construct_UClass_ULFPWorldGrid, &ULFPWorldGrid::StaticClass, TEXT("/Script/LohFunctionPlugin"), TEXT("ULFPWorldGrid"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULFPWorldGrid);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
