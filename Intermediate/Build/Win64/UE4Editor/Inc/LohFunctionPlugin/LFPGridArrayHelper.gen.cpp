// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LohFunctionPlugin/Public/LFPGridArrayHelper.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLFPGridArrayHelper() {}
// Cross Module References
	LOHFUNCTIONPLUGIN_API UEnum* Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType();
	UPackage* Z_Construct_UPackage__Script_LohFunctionPlugin();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPGridArrayHelper_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPGridArrayHelper();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntVector();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRandomStream();
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
	uint32 Get_Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType_Hash() { return 738950003U; }
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
				{ "ModuleRelativePath", "Public/LFPGridArrayHelper.h" },
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
	DEFINE_FUNCTION(ULFPGridArrayHelper::execGetAreaIndex)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_Index);
		P_GET_STRUCT(FIntVector,Z_Param_Offset);
		P_GET_STRUCT(FIntVector,Z_Param_AreaSize);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<int32>*)Z_Param__Result=P_THIS->GetAreaIndex(Z_Param_Index,Z_Param_Offset,Z_Param_AreaSize);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridArrayHelper::execRandomSectionGridIndex)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_Amount);
		P_GET_STRUCT(FIntVector,Z_Param_SectionSize);
		P_GET_TSET_REF(int32,Z_Param_Out_IgnoreIndexs);
		P_GET_STRUCT_REF(FRandomStream,Z_Param_Out_Seed);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<int32>*)Z_Param__Result=P_THIS->RandomSectionGridIndex(Z_Param_Amount,Z_Param_SectionSize,Z_Param_Out_IgnoreIndexs,Z_Param_Out_Seed);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridArrayHelper::execSectionGridIndex)
	{
		P_GET_STRUCT(FIntVector,Z_Param_SectionSize);
		P_GET_TSET_REF(int32,Z_Param_Out_IgnoreIndexs);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<int32>*)Z_Param__Result=P_THIS->SectionGridIndex(Z_Param_SectionSize,Z_Param_Out_IgnoreIndexs);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridArrayHelper::execGetGridWorldLocationWithIndex)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_Index);
		P_GET_UBOOL(Z_Param_AddHalfGap);
		P_GET_STRUCT_REF(FVector,Z_Param_Out_ReturnLocation);
		P_GET_STRUCT_REF(FRotator,Z_Param_Out_ReturnRotation);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->GetGridWorldLocationWithIndex(Z_Param_Index,Z_Param_AddHalfGap,Z_Param_Out_ReturnLocation,Z_Param_Out_ReturnRotation);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridArrayHelper::execGetGridWorldLocation)
	{
		P_GET_STRUCT(FIntVector,Z_Param_Location);
		P_GET_UBOOL(Z_Param_AddHalfGap);
		P_GET_STRUCT_REF(FVector,Z_Param_Out_ReturnLocation);
		P_GET_STRUCT_REF(FRotator,Z_Param_Out_ReturnRotation);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->GetGridWorldLocation(Z_Param_Location,Z_Param_AddHalfGap,Z_Param_Out_ReturnLocation,Z_Param_Out_ReturnRotation);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridArrayHelper::execIsWorldLocationValid)
	{
		P_GET_STRUCT(FVector,Z_Param_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->IsWorldLocationValid(Z_Param_Location);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridArrayHelper::execIsLocationValid)
	{
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->IsLocationValid(Z_Param_Out_Location);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridArrayHelper::execWordlLocationToGridLocation)
	{
		P_GET_STRUCT_REF(FVector,Z_Param_Out_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FIntVector*)Z_Param__Result=P_THIS->WordlLocationToGridLocation(Z_Param_Out_Location);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridArrayHelper::execWordlLocationToIndex)
	{
		P_GET_STRUCT_REF(FVector,Z_Param_Out_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->WordlLocationToIndex(Z_Param_Out_Location);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridArrayHelper::execIndexsToGridLocation)
	{
		P_GET_TARRAY_REF(int32,Z_Param_Out_Indexs);
		P_GET_PROPERTY(FIntProperty,Z_Param_Offset);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FIntVector>*)Z_Param__Result=P_THIS->IndexsToGridLocation(Z_Param_Out_Indexs,Z_Param_Offset);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridArrayHelper::execIndexToGridLocation)
	{
		P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_Index);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FIntVector*)Z_Param__Result=P_THIS->IndexToGridLocation(Z_Param_Out_Index);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridArrayHelper::execGridLocationsToIndex)
	{
		P_GET_TARRAY_REF(FIntVector,Z_Param_Out_GridLocations);
		P_GET_STRUCT(FIntVector,Z_Param_Offset);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<int32>*)Z_Param__Result=P_THIS->GridLocationsToIndex(Z_Param_Out_GridLocations,Z_Param_Offset);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridArrayHelper::execGridLocationToIndex)
	{
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GridLocationToIndex(Z_Param_Out_Location);
		P_NATIVE_END;
	}
	void ULFPGridArrayHelper::StaticRegisterNativesULFPGridArrayHelper()
	{
		UClass* Class = ULFPGridArrayHelper::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetAreaIndex", &ULFPGridArrayHelper::execGetAreaIndex },
			{ "GetGridWorldLocation", &ULFPGridArrayHelper::execGetGridWorldLocation },
			{ "GetGridWorldLocationWithIndex", &ULFPGridArrayHelper::execGetGridWorldLocationWithIndex },
			{ "GridLocationsToIndex", &ULFPGridArrayHelper::execGridLocationsToIndex },
			{ "GridLocationToIndex", &ULFPGridArrayHelper::execGridLocationToIndex },
			{ "IndexsToGridLocation", &ULFPGridArrayHelper::execIndexsToGridLocation },
			{ "IndexToGridLocation", &ULFPGridArrayHelper::execIndexToGridLocation },
			{ "IsLocationValid", &ULFPGridArrayHelper::execIsLocationValid },
			{ "IsWorldLocationValid", &ULFPGridArrayHelper::execIsWorldLocationValid },
			{ "RandomSectionGridIndex", &ULFPGridArrayHelper::execRandomSectionGridIndex },
			{ "SectionGridIndex", &ULFPGridArrayHelper::execSectionGridIndex },
			{ "WordlLocationToGridLocation", &ULFPGridArrayHelper::execWordlLocationToGridLocation },
			{ "WordlLocationToIndex", &ULFPGridArrayHelper::execWordlLocationToIndex },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics
	{
		struct LFPGridArrayHelper_eventGetAreaIndex_Parms
		{
			int32 Index;
			FIntVector Offset;
			FIntVector AreaSize;
			TArray<int32> ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Index_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Index;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Offset_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Offset;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AreaSize_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_AreaSize;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ReturnValue_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::NewProp_Index_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventGetAreaIndex_Parms, Index), METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::NewProp_Index_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::NewProp_Index_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::NewProp_Offset_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::NewProp_Offset = { "Offset", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventGetAreaIndex_Parms, Offset), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::NewProp_Offset_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::NewProp_Offset_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::NewProp_AreaSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::NewProp_AreaSize = { "AreaSize", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventGetAreaIndex_Parms, AreaSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::NewProp_AreaSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::NewProp_AreaSize_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventGetAreaIndex_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::NewProp_Index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::NewProp_Offset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::NewProp_AreaSize,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridArrayHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridArrayHelper, nullptr, "GetAreaIndex", nullptr, nullptr, sizeof(LFPGridArrayHelper_eventGetAreaIndex_Parms), Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x44820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics
	{
		struct LFPGridArrayHelper_eventGetGridWorldLocation_Parms
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventGetGridWorldLocation_Parms, Location), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::NewProp_Location_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::NewProp_AddHalfGap_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::NewProp_AddHalfGap_SetBit(void* Obj)
	{
		((LFPGridArrayHelper_eventGetGridWorldLocation_Parms*)Obj)->AddHalfGap = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::NewProp_AddHalfGap = { "AddHalfGap", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridArrayHelper_eventGetGridWorldLocation_Parms), &Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::NewProp_AddHalfGap_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::NewProp_AddHalfGap_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::NewProp_AddHalfGap_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::NewProp_ReturnLocation = { "ReturnLocation", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventGetGridWorldLocation_Parms, ReturnLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::NewProp_ReturnRotation = { "ReturnRotation", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventGetGridWorldLocation_Parms, ReturnRotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPGridArrayHelper_eventGetGridWorldLocation_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridArrayHelper_eventGetGridWorldLocation_Parms), &Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::NewProp_AddHalfGap,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::NewProp_ReturnLocation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::NewProp_ReturnRotation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridArrayHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridArrayHelper, nullptr, "GetGridWorldLocation", nullptr, nullptr, sizeof(LFPGridArrayHelper_eventGetGridWorldLocation_Parms), Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics
	{
		struct LFPGridArrayHelper_eventGetGridWorldLocationWithIndex_Parms
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::NewProp_Index_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventGetGridWorldLocationWithIndex_Parms, Index), METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::NewProp_Index_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::NewProp_Index_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::NewProp_AddHalfGap_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::NewProp_AddHalfGap_SetBit(void* Obj)
	{
		((LFPGridArrayHelper_eventGetGridWorldLocationWithIndex_Parms*)Obj)->AddHalfGap = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::NewProp_AddHalfGap = { "AddHalfGap", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridArrayHelper_eventGetGridWorldLocationWithIndex_Parms), &Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::NewProp_AddHalfGap_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::NewProp_AddHalfGap_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::NewProp_AddHalfGap_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::NewProp_ReturnLocation = { "ReturnLocation", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventGetGridWorldLocationWithIndex_Parms, ReturnLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::NewProp_ReturnRotation = { "ReturnRotation", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventGetGridWorldLocationWithIndex_Parms, ReturnRotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPGridArrayHelper_eventGetGridWorldLocationWithIndex_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridArrayHelper_eventGetGridWorldLocationWithIndex_Parms), &Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::NewProp_Index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::NewProp_AddHalfGap,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::NewProp_ReturnLocation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::NewProp_ReturnRotation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridArrayHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridArrayHelper, nullptr, "GetGridWorldLocationWithIndex", nullptr, nullptr, sizeof(LFPGridArrayHelper_eventGetGridWorldLocationWithIndex_Parms), Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics
	{
		struct LFPGridArrayHelper_eventGridLocationsToIndex_Parms
		{
			TArray<FIntVector> GridLocations;
			FIntVector Offset;
			TArray<int32> ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_GridLocations_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GridLocations_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_GridLocations;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Offset_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Offset;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ReturnValue_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::NewProp_GridLocations_Inner = { "GridLocations", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::NewProp_GridLocations_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::NewProp_GridLocations = { "GridLocations", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventGridLocationsToIndex_Parms, GridLocations), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::NewProp_GridLocations_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::NewProp_GridLocations_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::NewProp_Offset_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::NewProp_Offset = { "Offset", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventGridLocationsToIndex_Parms, Offset), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::NewProp_Offset_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::NewProp_Offset_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventGridLocationsToIndex_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::NewProp_GridLocations_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::NewProp_GridLocations,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::NewProp_Offset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridArrayHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridArrayHelper, nullptr, "GridLocationsToIndex", nullptr, nullptr, sizeof(LFPGridArrayHelper_eventGridLocationsToIndex_Parms), Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x44C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationToIndex_Statics
	{
		struct LFPGridArrayHelper_eventGridLocationToIndex_Parms
		{
			FIntVector Location;
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationToIndex_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationToIndex_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventGridLocationToIndex_Parms, Location), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationToIndex_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationToIndex_Statics::NewProp_Location_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationToIndex_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventGridLocationToIndex_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationToIndex_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationToIndex_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationToIndex_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationToIndex_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridArrayHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationToIndex_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridArrayHelper, nullptr, "GridLocationToIndex", nullptr, nullptr, sizeof(LFPGridArrayHelper_eventGridLocationToIndex_Parms), Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationToIndex_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationToIndex_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationToIndex_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationToIndex_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationToIndex()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationToIndex_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics
	{
		struct LFPGridArrayHelper_eventIndexsToGridLocation_Parms
		{
			TArray<int32> Indexs;
			int32 Offset;
			TArray<FIntVector> ReturnValue;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Indexs_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Indexs_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Indexs;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Offset_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Offset;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::NewProp_Indexs_Inner = { "Indexs", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::NewProp_Indexs_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::NewProp_Indexs = { "Indexs", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventIndexsToGridLocation_Parms, Indexs), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::NewProp_Indexs_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::NewProp_Indexs_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::NewProp_Offset_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::NewProp_Offset = { "Offset", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventIndexsToGridLocation_Parms, Offset), METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::NewProp_Offset_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::NewProp_Offset_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventIndexsToGridLocation_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::NewProp_Indexs_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::NewProp_Indexs,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::NewProp_Offset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridArrayHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridArrayHelper, nullptr, "IndexsToGridLocation", nullptr, nullptr, sizeof(LFPGridArrayHelper_eventIndexsToGridLocation_Parms), Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x44420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridArrayHelper_IndexToGridLocation_Statics
	{
		struct LFPGridArrayHelper_eventIndexToGridLocation_Parms
		{
			int32 Index;
			FIntVector ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Index_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Index;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_IndexToGridLocation_Statics::NewProp_Index_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_IndexToGridLocation_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventIndexToGridLocation_Parms, Index), METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_IndexToGridLocation_Statics::NewProp_Index_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_IndexToGridLocation_Statics::NewProp_Index_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_IndexToGridLocation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventIndexToGridLocation_Parms, ReturnValue), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridArrayHelper_IndexToGridLocation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_IndexToGridLocation_Statics::NewProp_Index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_IndexToGridLocation_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_IndexToGridLocation_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridArrayHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridArrayHelper_IndexToGridLocation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridArrayHelper, nullptr, "IndexToGridLocation", nullptr, nullptr, sizeof(LFPGridArrayHelper_eventIndexToGridLocation_Parms), Z_Construct_UFunction_ULFPGridArrayHelper_IndexToGridLocation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_IndexToGridLocation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_IndexToGridLocation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_IndexToGridLocation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridArrayHelper_IndexToGridLocation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridArrayHelper_IndexToGridLocation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridArrayHelper_IsLocationValid_Statics
	{
		struct LFPGridArrayHelper_eventIsLocationValid_Parms
		{
			FIntVector Location;
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_IsLocationValid_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_IsLocationValid_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventIsLocationValid_Parms, Location), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_IsLocationValid_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_IsLocationValid_Statics::NewProp_Location_MetaData)) };
	void Z_Construct_UFunction_ULFPGridArrayHelper_IsLocationValid_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPGridArrayHelper_eventIsLocationValid_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_IsLocationValid_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridArrayHelper_eventIsLocationValid_Parms), &Z_Construct_UFunction_ULFPGridArrayHelper_IsLocationValid_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridArrayHelper_IsLocationValid_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_IsLocationValid_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_IsLocationValid_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_IsLocationValid_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridArrayHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridArrayHelper_IsLocationValid_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridArrayHelper, nullptr, "IsLocationValid", nullptr, nullptr, sizeof(LFPGridArrayHelper_eventIsLocationValid_Parms), Z_Construct_UFunction_ULFPGridArrayHelper_IsLocationValid_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_IsLocationValid_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_IsLocationValid_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_IsLocationValid_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridArrayHelper_IsLocationValid()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridArrayHelper_IsLocationValid_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridArrayHelper_IsWorldLocationValid_Statics
	{
		struct LFPGridArrayHelper_eventIsWorldLocationValid_Parms
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_IsWorldLocationValid_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_IsWorldLocationValid_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventIsWorldLocationValid_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_IsWorldLocationValid_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_IsWorldLocationValid_Statics::NewProp_Location_MetaData)) };
	void Z_Construct_UFunction_ULFPGridArrayHelper_IsWorldLocationValid_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPGridArrayHelper_eventIsWorldLocationValid_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_IsWorldLocationValid_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridArrayHelper_eventIsWorldLocationValid_Parms), &Z_Construct_UFunction_ULFPGridArrayHelper_IsWorldLocationValid_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridArrayHelper_IsWorldLocationValid_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_IsWorldLocationValid_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_IsWorldLocationValid_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_IsWorldLocationValid_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridArrayHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridArrayHelper_IsWorldLocationValid_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridArrayHelper, nullptr, "IsWorldLocationValid", nullptr, nullptr, sizeof(LFPGridArrayHelper_eventIsWorldLocationValid_Parms), Z_Construct_UFunction_ULFPGridArrayHelper_IsWorldLocationValid_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_IsWorldLocationValid_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_IsWorldLocationValid_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_IsWorldLocationValid_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridArrayHelper_IsWorldLocationValid()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridArrayHelper_IsWorldLocationValid_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics
	{
		struct LFPGridArrayHelper_eventRandomSectionGridIndex_Parms
		{
			int32 Amount;
			FIntVector SectionSize;
			TSet<int32> IgnoreIndexs;
			FRandomStream Seed;
			TArray<int32> ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Amount_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Amount;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SectionSize_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_SectionSize;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_IgnoreIndexs_ElementProp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_IgnoreIndexs_MetaData[];
#endif
		static const UE4CodeGen_Private::FSetPropertyParams NewProp_IgnoreIndexs;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Seed_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Seed;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ReturnValue_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_Amount_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_Amount = { "Amount", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventRandomSectionGridIndex_Parms, Amount), METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_Amount_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_Amount_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_SectionSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_SectionSize = { "SectionSize", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventRandomSectionGridIndex_Parms, SectionSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_SectionSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_SectionSize_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_IgnoreIndexs_ElementProp = { "IgnoreIndexs", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_IgnoreIndexs_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FSetPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_IgnoreIndexs = { "IgnoreIndexs", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventRandomSectionGridIndex_Parms, IgnoreIndexs), METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_IgnoreIndexs_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_IgnoreIndexs_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_Seed_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_Seed = { "Seed", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventRandomSectionGridIndex_Parms, Seed), Z_Construct_UScriptStruct_FRandomStream, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_Seed_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_Seed_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventRandomSectionGridIndex_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_Amount,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_SectionSize,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_IgnoreIndexs_ElementProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_IgnoreIndexs,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_Seed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridArrayHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridArrayHelper, nullptr, "RandomSectionGridIndex", nullptr, nullptr, sizeof(LFPGridArrayHelper_eventRandomSectionGridIndex_Parms), Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x44C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics
	{
		struct LFPGridArrayHelper_eventSectionGridIndex_Parms
		{
			FIntVector SectionSize;
			TSet<int32> IgnoreIndexs;
			TArray<int32> ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SectionSize_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_SectionSize;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_IgnoreIndexs_ElementProp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_IgnoreIndexs_MetaData[];
#endif
		static const UE4CodeGen_Private::FSetPropertyParams NewProp_IgnoreIndexs;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ReturnValue_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::NewProp_SectionSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::NewProp_SectionSize = { "SectionSize", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventSectionGridIndex_Parms, SectionSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::NewProp_SectionSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::NewProp_SectionSize_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::NewProp_IgnoreIndexs_ElementProp = { "IgnoreIndexs", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::NewProp_IgnoreIndexs_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FSetPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::NewProp_IgnoreIndexs = { "IgnoreIndexs", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventSectionGridIndex_Parms, IgnoreIndexs), METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::NewProp_IgnoreIndexs_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::NewProp_IgnoreIndexs_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventSectionGridIndex_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::NewProp_SectionSize,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::NewProp_IgnoreIndexs_ElementProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::NewProp_IgnoreIndexs,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridArrayHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridArrayHelper, nullptr, "SectionGridIndex", nullptr, nullptr, sizeof(LFPGridArrayHelper_eventSectionGridIndex_Parms), Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x44C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToGridLocation_Statics
	{
		struct LFPGridArrayHelper_eventWordlLocationToGridLocation_Parms
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToGridLocation_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToGridLocation_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventWordlLocationToGridLocation_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToGridLocation_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToGridLocation_Statics::NewProp_Location_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToGridLocation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventWordlLocationToGridLocation_Parms, ReturnValue), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToGridLocation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToGridLocation_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToGridLocation_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToGridLocation_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridArrayHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToGridLocation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridArrayHelper, nullptr, "WordlLocationToGridLocation", nullptr, nullptr, sizeof(LFPGridArrayHelper_eventWordlLocationToGridLocation_Parms), Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToGridLocation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToGridLocation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToGridLocation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToGridLocation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToGridLocation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToGridLocation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToIndex_Statics
	{
		struct LFPGridArrayHelper_eventWordlLocationToIndex_Parms
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToIndex_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToIndex_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventWordlLocationToIndex_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToIndex_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToIndex_Statics::NewProp_Location_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToIndex_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridArrayHelper_eventWordlLocationToIndex_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToIndex_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToIndex_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToIndex_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToIndex_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridArrayHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToIndex_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridArrayHelper, nullptr, "WordlLocationToIndex", nullptr, nullptr, sizeof(LFPGridArrayHelper_eventWordlLocationToIndex_Parms), Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToIndex_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToIndex_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToIndex_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToIndex_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToIndex()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToIndex_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ULFPGridArrayHelper_NoRegister()
	{
		return ULFPGridArrayHelper::StaticClass();
	}
	struct Z_Construct_UClass_ULFPGridArrayHelper_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GridArratSize_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_GridArratSize;
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
	UObject* (*const Z_Construct_UClass_ULFPGridArrayHelper_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USceneComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ULFPGridArrayHelper_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULFPGridArrayHelper_GetAreaIndex, "GetAreaIndex" }, // 3472462951
		{ &Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocation, "GetGridWorldLocation" }, // 2927021256
		{ &Z_Construct_UFunction_ULFPGridArrayHelper_GetGridWorldLocationWithIndex, "GetGridWorldLocationWithIndex" }, // 4234257398
		{ &Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationsToIndex, "GridLocationsToIndex" }, // 2239969966
		{ &Z_Construct_UFunction_ULFPGridArrayHelper_GridLocationToIndex, "GridLocationToIndex" }, // 2661429419
		{ &Z_Construct_UFunction_ULFPGridArrayHelper_IndexsToGridLocation, "IndexsToGridLocation" }, // 1597754219
		{ &Z_Construct_UFunction_ULFPGridArrayHelper_IndexToGridLocation, "IndexToGridLocation" }, // 3201785013
		{ &Z_Construct_UFunction_ULFPGridArrayHelper_IsLocationValid, "IsLocationValid" }, // 1796866098
		{ &Z_Construct_UFunction_ULFPGridArrayHelper_IsWorldLocationValid, "IsWorldLocationValid" }, // 416822519
		{ &Z_Construct_UFunction_ULFPGridArrayHelper_RandomSectionGridIndex, "RandomSectionGridIndex" }, // 3046198752
		{ &Z_Construct_UFunction_ULFPGridArrayHelper_SectionGridIndex, "SectionGridIndex" }, // 2412836215
		{ &Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToGridLocation, "WordlLocationToGridLocation" }, // 1703474531
		{ &Z_Construct_UFunction_ULFPGridArrayHelper_WordlLocationToIndex, "WordlLocationToIndex" }, // 3083785114
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPGridArrayHelper_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "LFPGridArrayHelper.h" },
		{ "ModuleRelativePath", "Public/LFPGridArrayHelper.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPGridArrayHelper_Statics::NewProp_GridArratSize_MetaData[] = {
		{ "Category", "LFPGridSystem | Variable" },
		{ "ModuleRelativePath", "Public/LFPGridArrayHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_ULFPGridArrayHelper_Statics::NewProp_GridArratSize = { "GridArratSize", nullptr, (EPropertyFlags)0x0020080000020015, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPGridArrayHelper, GridArratSize), METADATA_PARAMS(Z_Construct_UClass_ULFPGridArrayHelper_Statics::NewProp_GridArratSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPGridArrayHelper_Statics::NewProp_GridArratSize_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPGridArrayHelper_Statics::NewProp_GridSize_MetaData[] = {
		{ "Category", "LFPGridSystem | Variable" },
		{ "ModuleRelativePath", "Public/LFPGridArrayHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULFPGridArrayHelper_Statics::NewProp_GridSize = { "GridSize", nullptr, (EPropertyFlags)0x0020080000000015, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPGridArrayHelper, GridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UClass_ULFPGridArrayHelper_Statics::NewProp_GridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPGridArrayHelper_Statics::NewProp_GridSize_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPGridArrayHelper_Statics::NewProp_GridGap_MetaData[] = {
		{ "Category", "LFPGridSystem | Variable" },
		{ "ModuleRelativePath", "Public/LFPGridArrayHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULFPGridArrayHelper_Statics::NewProp_GridGap = { "GridGap", nullptr, (EPropertyFlags)0x0020080000000015, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPGridArrayHelper, GridGap), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_ULFPGridArrayHelper_Statics::NewProp_GridGap_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPGridArrayHelper_Statics::NewProp_GridGap_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_ULFPGridArrayHelper_Statics::NewProp_GridType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPGridArrayHelper_Statics::NewProp_GridType_MetaData[] = {
		{ "Category", "LFPGridSystem | Variable" },
		{ "ModuleRelativePath", "Public/LFPGridArrayHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_ULFPGridArrayHelper_Statics::NewProp_GridType = { "GridType", nullptr, (EPropertyFlags)0x0020080000000015, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPGridArrayHelper, GridType), Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType, METADATA_PARAMS(Z_Construct_UClass_ULFPGridArrayHelper_Statics::NewProp_GridType_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPGridArrayHelper_Statics::NewProp_GridType_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULFPGridArrayHelper_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPGridArrayHelper_Statics::NewProp_GridArratSize,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPGridArrayHelper_Statics::NewProp_GridSize,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPGridArrayHelper_Statics::NewProp_GridGap,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPGridArrayHelper_Statics::NewProp_GridType_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPGridArrayHelper_Statics::NewProp_GridType,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULFPGridArrayHelper_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULFPGridArrayHelper>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULFPGridArrayHelper_Statics::ClassParams = {
		&ULFPGridArrayHelper::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ULFPGridArrayHelper_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ULFPGridArrayHelper_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ULFPGridArrayHelper_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPGridArrayHelper_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULFPGridArrayHelper()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULFPGridArrayHelper_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULFPGridArrayHelper, 1329776530);
	template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<ULFPGridArrayHelper>()
	{
		return ULFPGridArrayHelper::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULFPGridArrayHelper(Z_Construct_UClass_ULFPGridArrayHelper, &ULFPGridArrayHelper::StaticClass, TEXT("/Script/LohFunctionPlugin"), TEXT("ULFPGridArrayHelper"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULFPGridArrayHelper);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
