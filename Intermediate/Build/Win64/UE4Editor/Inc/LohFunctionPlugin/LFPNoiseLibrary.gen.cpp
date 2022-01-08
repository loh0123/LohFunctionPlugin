// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LohFunctionPlugin/Public/Math/LFPNoiseLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLFPNoiseLibrary() {}
// Cross Module References
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPNoiseTable();
	UPackage* Z_Construct_UPackage__Script_LohFunctionPlugin();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPNoiseMixTable();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPNoiseLibrary_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPNoiseLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRandomStream();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntVector();
// End Cross Module References
class UScriptStruct* FLFPNoiseTable::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOHFUNCTIONPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FLFPNoiseTable_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLFPNoiseTable, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("LFPNoiseTable"), sizeof(FLFPNoiseTable), Get_Z_Construct_UScriptStruct_FLFPNoiseTable_Hash());
	}
	return Singleton;
}
template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<FLFPNoiseTable>()
{
	return FLFPNoiseTable::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLFPNoiseTable(FLFPNoiseTable::StaticStruct, TEXT("/Script/LohFunctionPlugin"), TEXT("LFPNoiseTable"), false, nullptr, nullptr);
static struct FScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLFPNoiseTable
{
	FScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLFPNoiseTable()
	{
		UScriptStruct::DeferCppStructOps<FLFPNoiseTable>(FName(TEXT("LFPNoiseTable")));
	}
} ScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLFPNoiseTable;
	struct Z_Construct_UScriptStruct_FLFPNoiseTable_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_NoiseData_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NoiseData_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_NoiseData;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPNoiseTable_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Math/LFPNoiseLibrary.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLFPNoiseTable_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLFPNoiseTable>();
	}
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FLFPNoiseTable_Statics::NewProp_NoiseData_Inner = { "NoiseData", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPNoiseTable_Statics::NewProp_NoiseData_MetaData[] = {
		{ "Category", "LFPNoiseTable" },
		{ "ModuleRelativePath", "Public/Math/LFPNoiseLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLFPNoiseTable_Statics::NewProp_NoiseData = { "NoiseData", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPNoiseTable, NoiseData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPNoiseTable_Statics::NewProp_NoiseData_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPNoiseTable_Statics::NewProp_NoiseData_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPNoiseTable_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPNoiseTable_Statics::NewProp_NoiseData_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPNoiseTable_Statics::NewProp_NoiseData,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLFPNoiseTable_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
		nullptr,
		&NewStructOps,
		"LFPNoiseTable",
		sizeof(FLFPNoiseTable),
		alignof(FLFPNoiseTable),
		Z_Construct_UScriptStruct_FLFPNoiseTable_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPNoiseTable_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPNoiseTable_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPNoiseTable_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLFPNoiseTable()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLFPNoiseTable_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LohFunctionPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LFPNoiseTable"), sizeof(FLFPNoiseTable), Get_Z_Construct_UScriptStruct_FLFPNoiseTable_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLFPNoiseTable_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLFPNoiseTable_Hash() { return 486658148U; }
class UScriptStruct* FLFPNoiseMixTable::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOHFUNCTIONPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FLFPNoiseMixTable_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLFPNoiseMixTable, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("LFPNoiseMixTable"), sizeof(FLFPNoiseMixTable), Get_Z_Construct_UScriptStruct_FLFPNoiseMixTable_Hash());
	}
	return Singleton;
}
template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<FLFPNoiseMixTable>()
{
	return FLFPNoiseMixTable::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLFPNoiseMixTable(FLFPNoiseMixTable::StaticStruct, TEXT("/Script/LohFunctionPlugin"), TEXT("LFPNoiseMixTable"), false, nullptr, nullptr);
static struct FScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLFPNoiseMixTable
{
	FScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLFPNoiseMixTable()
	{
		UScriptStruct::DeferCppStructOps<FLFPNoiseMixTable>(FName(TEXT("LFPNoiseMixTable")));
	}
} ScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLFPNoiseMixTable;
	struct Z_Construct_UScriptStruct_FLFPNoiseMixTable_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Multiply_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Multiply;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MixValue_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MixValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPNoiseMixTable_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Math/LFPNoiseLibrary.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLFPNoiseMixTable_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLFPNoiseMixTable>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPNoiseMixTable_Statics::NewProp_Multiply_MetaData[] = {
		{ "Category", "LFPNoiseMixTable" },
		{ "ModuleRelativePath", "Public/Math/LFPNoiseLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLFPNoiseMixTable_Statics::NewProp_Multiply = { "Multiply", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPNoiseMixTable, Multiply), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPNoiseMixTable_Statics::NewProp_Multiply_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPNoiseMixTable_Statics::NewProp_Multiply_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLFPNoiseMixTable_Statics::NewProp_MixValue_MetaData[] = {
		{ "Category", "LFPNoiseMixTable" },
		{ "ModuleRelativePath", "Public/Math/LFPNoiseLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FLFPNoiseMixTable_Statics::NewProp_MixValue = { "MixValue", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLFPNoiseMixTable, MixValue), METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPNoiseMixTable_Statics::NewProp_MixValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPNoiseMixTable_Statics::NewProp_MixValue_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLFPNoiseMixTable_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPNoiseMixTable_Statics::NewProp_Multiply,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLFPNoiseMixTable_Statics::NewProp_MixValue,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLFPNoiseMixTable_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
		nullptr,
		&NewStructOps,
		"LFPNoiseMixTable",
		sizeof(FLFPNoiseMixTable),
		alignof(FLFPNoiseMixTable),
		Z_Construct_UScriptStruct_FLFPNoiseMixTable_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPNoiseMixTable_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLFPNoiseMixTable_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLFPNoiseMixTable_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLFPNoiseMixTable()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLFPNoiseMixTable_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LohFunctionPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LFPNoiseMixTable"), sizeof(FLFPNoiseMixTable), Get_Z_Construct_UScriptStruct_FLFPNoiseMixTable_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLFPNoiseMixTable_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLFPNoiseMixTable_Hash() { return 1780888902U; }
	DEFINE_FUNCTION(ULFPNoiseLibrary::execMixLerpDirection)
	{
		P_GET_STRUCT_REF(FLFPNoiseTable,Z_Param_Out_NoiseTable);
		P_GET_STRUCT(FVector,Z_Param_Location);
		P_GET_TARRAY_REF(FLFPNoiseMixTable,Z_Param_Out_MixTable);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FVector*)Z_Param__Result=ULFPNoiseLibrary::MixLerpDirection(Z_Param_Out_NoiseTable,Z_Param_Location,Z_Param_Out_MixTable);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPNoiseLibrary::execMixLerpVector)
	{
		P_GET_STRUCT_REF(FLFPNoiseTable,Z_Param_Out_NoiseTable);
		P_GET_STRUCT(FVector,Z_Param_Location);
		P_GET_TARRAY_REF(FLFPNoiseMixTable,Z_Param_Out_MixTable);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FVector*)Z_Param__Result=ULFPNoiseLibrary::MixLerpVector(Z_Param_Out_NoiseTable,Z_Param_Location,Z_Param_Out_MixTable);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPNoiseLibrary::execMixLerpNoise)
	{
		P_GET_STRUCT_REF(FLFPNoiseTable,Z_Param_Out_NoiseTable);
		P_GET_STRUCT(FVector,Z_Param_Location);
		P_GET_TARRAY_REF(FLFPNoiseMixTable,Z_Param_Out_MixTable);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=ULFPNoiseLibrary::MixLerpNoise(Z_Param_Out_NoiseTable,Z_Param_Location,Z_Param_Out_MixTable);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPNoiseLibrary::execGetLerpDirectionNoise)
	{
		P_GET_STRUCT_REF(FLFPNoiseTable,Z_Param_Out_NoiseTable);
		P_GET_STRUCT(FVector,Z_Param_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FVector*)Z_Param__Result=ULFPNoiseLibrary::GetLerpDirectionNoise(Z_Param_Out_NoiseTable,Z_Param_Location);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPNoiseLibrary::execGetLerpVectorNoise)
	{
		P_GET_STRUCT_REF(FLFPNoiseTable,Z_Param_Out_NoiseTable);
		P_GET_STRUCT(FVector,Z_Param_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FVector*)Z_Param__Result=ULFPNoiseLibrary::GetLerpVectorNoise(Z_Param_Out_NoiseTable,Z_Param_Location);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPNoiseLibrary::execGetLerpNoise)
	{
		P_GET_STRUCT_REF(FLFPNoiseTable,Z_Param_Out_NoiseTable);
		P_GET_STRUCT(FVector,Z_Param_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=ULFPNoiseLibrary::GetLerpNoise(Z_Param_Out_NoiseTable,Z_Param_Location);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPNoiseLibrary::execGetDirectionNoise)
	{
		P_GET_STRUCT_REF(FLFPNoiseTable,Z_Param_Out_NoiseTable);
		P_GET_STRUCT(FIntVector,Z_Param_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FVector*)Z_Param__Result=ULFPNoiseLibrary::GetDirectionNoise(Z_Param_Out_NoiseTable,Z_Param_Location);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPNoiseLibrary::execGetVectorNoise)
	{
		P_GET_STRUCT_REF(FLFPNoiseTable,Z_Param_Out_NoiseTable);
		P_GET_STRUCT(FIntVector,Z_Param_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FVector*)Z_Param__Result=ULFPNoiseLibrary::GetVectorNoise(Z_Param_Out_NoiseTable,Z_Param_Location);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPNoiseLibrary::execGetFloatNoise)
	{
		P_GET_STRUCT_REF(FLFPNoiseTable,Z_Param_Out_NoiseTable);
		P_GET_STRUCT(FIntVector,Z_Param_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=ULFPNoiseLibrary::GetFloatNoise(Z_Param_Out_NoiseTable,Z_Param_Location);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPNoiseLibrary::execCreateNoiseTable)
	{
		P_GET_STRUCT_REF(FRandomStream,Z_Param_Out_Seed);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FLFPNoiseTable*)Z_Param__Result=ULFPNoiseLibrary::CreateNoiseTable(Z_Param_Out_Seed);
		P_NATIVE_END;
	}
	void ULFPNoiseLibrary::StaticRegisterNativesULFPNoiseLibrary()
	{
		UClass* Class = ULFPNoiseLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CreateNoiseTable", &ULFPNoiseLibrary::execCreateNoiseTable },
			{ "GetDirectionNoise", &ULFPNoiseLibrary::execGetDirectionNoise },
			{ "GetFloatNoise", &ULFPNoiseLibrary::execGetFloatNoise },
			{ "GetLerpDirectionNoise", &ULFPNoiseLibrary::execGetLerpDirectionNoise },
			{ "GetLerpNoise", &ULFPNoiseLibrary::execGetLerpNoise },
			{ "GetLerpVectorNoise", &ULFPNoiseLibrary::execGetLerpVectorNoise },
			{ "GetVectorNoise", &ULFPNoiseLibrary::execGetVectorNoise },
			{ "MixLerpDirection", &ULFPNoiseLibrary::execMixLerpDirection },
			{ "MixLerpNoise", &ULFPNoiseLibrary::execMixLerpNoise },
			{ "MixLerpVector", &ULFPNoiseLibrary::execMixLerpVector },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULFPNoiseLibrary_CreateNoiseTable_Statics
	{
		struct LFPNoiseLibrary_eventCreateNoiseTable_Parms
		{
			FRandomStream Seed;
			FLFPNoiseTable ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Seed_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Seed;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_CreateNoiseTable_Statics::NewProp_Seed_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_CreateNoiseTable_Statics::NewProp_Seed = { "Seed", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventCreateNoiseTable_Parms, Seed), Z_Construct_UScriptStruct_FRandomStream, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_CreateNoiseTable_Statics::NewProp_Seed_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_CreateNoiseTable_Statics::NewProp_Seed_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_CreateNoiseTable_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventCreateNoiseTable_Parms, ReturnValue), Z_Construct_UScriptStruct_FLFPNoiseTable, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPNoiseLibrary_CreateNoiseTable_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_CreateNoiseTable_Statics::NewProp_Seed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_CreateNoiseTable_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_CreateNoiseTable_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Noise" },
		{ "ModuleRelativePath", "Public/Math/LFPNoiseLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPNoiseLibrary_CreateNoiseTable_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPNoiseLibrary, nullptr, "CreateNoiseTable", nullptr, nullptr, sizeof(LFPNoiseLibrary_eventCreateNoiseTable_Parms), Z_Construct_UFunction_ULFPNoiseLibrary_CreateNoiseTable_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_CreateNoiseTable_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C42401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_CreateNoiseTable_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_CreateNoiseTable_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPNoiseLibrary_CreateNoiseTable()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPNoiseLibrary_CreateNoiseTable_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise_Statics
	{
		struct LFPNoiseLibrary_eventGetDirectionNoise_Parms
		{
			FLFPNoiseTable NoiseTable;
			FIntVector Location;
			FVector ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NoiseTable_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_NoiseTable;
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise_Statics::NewProp_NoiseTable_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise_Statics::NewProp_NoiseTable = { "NoiseTable", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventGetDirectionNoise_Parms, NoiseTable), Z_Construct_UScriptStruct_FLFPNoiseTable, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise_Statics::NewProp_NoiseTable_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise_Statics::NewProp_NoiseTable_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventGetDirectionNoise_Parms, Location), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise_Statics::NewProp_Location_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventGetDirectionNoise_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise_Statics::NewProp_NoiseTable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Noise" },
		{ "ModuleRelativePath", "Public/Math/LFPNoiseLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPNoiseLibrary, nullptr, "GetDirectionNoise", nullptr, nullptr, sizeof(LFPNoiseLibrary_eventGetDirectionNoise_Parms), Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C42401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise_Statics
	{
		struct LFPNoiseLibrary_eventGetFloatNoise_Parms
		{
			FLFPNoiseTable NoiseTable;
			FIntVector Location;
			float ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NoiseTable_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_NoiseTable;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Location;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise_Statics::NewProp_NoiseTable_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise_Statics::NewProp_NoiseTable = { "NoiseTable", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventGetFloatNoise_Parms, NoiseTable), Z_Construct_UScriptStruct_FLFPNoiseTable, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise_Statics::NewProp_NoiseTable_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise_Statics::NewProp_NoiseTable_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventGetFloatNoise_Parms, Location), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise_Statics::NewProp_Location_MetaData)) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventGetFloatNoise_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise_Statics::NewProp_NoiseTable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Noise" },
		{ "ModuleRelativePath", "Public/Math/LFPNoiseLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPNoiseLibrary, nullptr, "GetFloatNoise", nullptr, nullptr, sizeof(LFPNoiseLibrary_eventGetFloatNoise_Parms), Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C42401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise_Statics
	{
		struct LFPNoiseLibrary_eventGetLerpDirectionNoise_Parms
		{
			FLFPNoiseTable NoiseTable;
			FVector Location;
			FVector ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NoiseTable_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_NoiseTable;
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise_Statics::NewProp_NoiseTable_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise_Statics::NewProp_NoiseTable = { "NoiseTable", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventGetLerpDirectionNoise_Parms, NoiseTable), Z_Construct_UScriptStruct_FLFPNoiseTable, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise_Statics::NewProp_NoiseTable_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise_Statics::NewProp_NoiseTable_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventGetLerpDirectionNoise_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise_Statics::NewProp_Location_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventGetLerpDirectionNoise_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise_Statics::NewProp_NoiseTable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Noise" },
		{ "ModuleRelativePath", "Public/Math/LFPNoiseLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPNoiseLibrary, nullptr, "GetLerpDirectionNoise", nullptr, nullptr, sizeof(LFPNoiseLibrary_eventGetLerpDirectionNoise_Parms), Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C42401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise_Statics
	{
		struct LFPNoiseLibrary_eventGetLerpNoise_Parms
		{
			FLFPNoiseTable NoiseTable;
			FVector Location;
			float ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NoiseTable_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_NoiseTable;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Location;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise_Statics::NewProp_NoiseTable_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise_Statics::NewProp_NoiseTable = { "NoiseTable", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventGetLerpNoise_Parms, NoiseTable), Z_Construct_UScriptStruct_FLFPNoiseTable, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise_Statics::NewProp_NoiseTable_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise_Statics::NewProp_NoiseTable_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventGetLerpNoise_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise_Statics::NewProp_Location_MetaData)) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventGetLerpNoise_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise_Statics::NewProp_NoiseTable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Noise" },
		{ "ModuleRelativePath", "Public/Math/LFPNoiseLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPNoiseLibrary, nullptr, "GetLerpNoise", nullptr, nullptr, sizeof(LFPNoiseLibrary_eventGetLerpNoise_Parms), Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C42401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise_Statics
	{
		struct LFPNoiseLibrary_eventGetLerpVectorNoise_Parms
		{
			FLFPNoiseTable NoiseTable;
			FVector Location;
			FVector ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NoiseTable_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_NoiseTable;
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise_Statics::NewProp_NoiseTable_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise_Statics::NewProp_NoiseTable = { "NoiseTable", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventGetLerpVectorNoise_Parms, NoiseTable), Z_Construct_UScriptStruct_FLFPNoiseTable, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise_Statics::NewProp_NoiseTable_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise_Statics::NewProp_NoiseTable_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventGetLerpVectorNoise_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise_Statics::NewProp_Location_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventGetLerpVectorNoise_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise_Statics::NewProp_NoiseTable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Noise" },
		{ "ModuleRelativePath", "Public/Math/LFPNoiseLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPNoiseLibrary, nullptr, "GetLerpVectorNoise", nullptr, nullptr, sizeof(LFPNoiseLibrary_eventGetLerpVectorNoise_Parms), Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C42401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise_Statics
	{
		struct LFPNoiseLibrary_eventGetVectorNoise_Parms
		{
			FLFPNoiseTable NoiseTable;
			FIntVector Location;
			FVector ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NoiseTable_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_NoiseTable;
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise_Statics::NewProp_NoiseTable_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise_Statics::NewProp_NoiseTable = { "NoiseTable", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventGetVectorNoise_Parms, NoiseTable), Z_Construct_UScriptStruct_FLFPNoiseTable, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise_Statics::NewProp_NoiseTable_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise_Statics::NewProp_NoiseTable_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventGetVectorNoise_Parms, Location), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise_Statics::NewProp_Location_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventGetVectorNoise_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise_Statics::NewProp_NoiseTable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Noise" },
		{ "ModuleRelativePath", "Public/Math/LFPNoiseLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPNoiseLibrary, nullptr, "GetVectorNoise", nullptr, nullptr, sizeof(LFPNoiseLibrary_eventGetVectorNoise_Parms), Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C42401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics
	{
		struct LFPNoiseLibrary_eventMixLerpDirection_Parms
		{
			FLFPNoiseTable NoiseTable;
			FVector Location;
			TArray<FLFPNoiseMixTable> MixTable;
			FVector ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NoiseTable_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_NoiseTable;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Location;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MixTable_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MixTable_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_MixTable;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::NewProp_NoiseTable_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::NewProp_NoiseTable = { "NoiseTable", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventMixLerpDirection_Parms, NoiseTable), Z_Construct_UScriptStruct_FLFPNoiseTable, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::NewProp_NoiseTable_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::NewProp_NoiseTable_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventMixLerpDirection_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::NewProp_MixTable_Inner = { "MixTable", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPNoiseMixTable, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::NewProp_MixTable_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::NewProp_MixTable = { "MixTable", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventMixLerpDirection_Parms, MixTable), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::NewProp_MixTable_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::NewProp_MixTable_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventMixLerpDirection_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::NewProp_NoiseTable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::NewProp_MixTable_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::NewProp_MixTable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Noise" },
		{ "ModuleRelativePath", "Public/Math/LFPNoiseLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPNoiseLibrary, nullptr, "MixLerpDirection", nullptr, nullptr, sizeof(LFPNoiseLibrary_eventMixLerpDirection_Parms), Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C42401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics
	{
		struct LFPNoiseLibrary_eventMixLerpNoise_Parms
		{
			FLFPNoiseTable NoiseTable;
			FVector Location;
			TArray<FLFPNoiseMixTable> MixTable;
			float ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NoiseTable_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_NoiseTable;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Location;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MixTable_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MixTable_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_MixTable;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::NewProp_NoiseTable_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::NewProp_NoiseTable = { "NoiseTable", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventMixLerpNoise_Parms, NoiseTable), Z_Construct_UScriptStruct_FLFPNoiseTable, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::NewProp_NoiseTable_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::NewProp_NoiseTable_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventMixLerpNoise_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::NewProp_MixTable_Inner = { "MixTable", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPNoiseMixTable, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::NewProp_MixTable_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::NewProp_MixTable = { "MixTable", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventMixLerpNoise_Parms, MixTable), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::NewProp_MixTable_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::NewProp_MixTable_MetaData)) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventMixLerpNoise_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::NewProp_NoiseTable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::NewProp_MixTable_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::NewProp_MixTable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Noise" },
		{ "ModuleRelativePath", "Public/Math/LFPNoiseLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPNoiseLibrary, nullptr, "MixLerpNoise", nullptr, nullptr, sizeof(LFPNoiseLibrary_eventMixLerpNoise_Parms), Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C42401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics
	{
		struct LFPNoiseLibrary_eventMixLerpVector_Parms
		{
			FLFPNoiseTable NoiseTable;
			FVector Location;
			TArray<FLFPNoiseMixTable> MixTable;
			FVector ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NoiseTable_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_NoiseTable;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Location;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MixTable_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MixTable_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_MixTable;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::NewProp_NoiseTable_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::NewProp_NoiseTable = { "NoiseTable", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventMixLerpVector_Parms, NoiseTable), Z_Construct_UScriptStruct_FLFPNoiseTable, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::NewProp_NoiseTable_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::NewProp_NoiseTable_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventMixLerpVector_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::NewProp_MixTable_Inner = { "MixTable", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPNoiseMixTable, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::NewProp_MixTable_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::NewProp_MixTable = { "MixTable", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventMixLerpVector_Parms, MixTable), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::NewProp_MixTable_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::NewProp_MixTable_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPNoiseLibrary_eventMixLerpVector_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::NewProp_NoiseTable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::NewProp_MixTable_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::NewProp_MixTable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPMathLibrary | Noise" },
		{ "ModuleRelativePath", "Public/Math/LFPNoiseLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPNoiseLibrary, nullptr, "MixLerpVector", nullptr, nullptr, sizeof(LFPNoiseLibrary_eventMixLerpVector_Parms), Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C42401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ULFPNoiseLibrary_NoRegister()
	{
		return ULFPNoiseLibrary::StaticClass();
	}
	struct Z_Construct_UClass_ULFPNoiseLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULFPNoiseLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ULFPNoiseLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULFPNoiseLibrary_CreateNoiseTable, "CreateNoiseTable" }, // 1704848252
		{ &Z_Construct_UFunction_ULFPNoiseLibrary_GetDirectionNoise, "GetDirectionNoise" }, // 125810379
		{ &Z_Construct_UFunction_ULFPNoiseLibrary_GetFloatNoise, "GetFloatNoise" }, // 2297710377
		{ &Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpDirectionNoise, "GetLerpDirectionNoise" }, // 1931008952
		{ &Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpNoise, "GetLerpNoise" }, // 3216317568
		{ &Z_Construct_UFunction_ULFPNoiseLibrary_GetLerpVectorNoise, "GetLerpVectorNoise" }, // 2742870359
		{ &Z_Construct_UFunction_ULFPNoiseLibrary_GetVectorNoise, "GetVectorNoise" }, // 77843199
		{ &Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpDirection, "MixLerpDirection" }, // 315602362
		{ &Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpNoise, "MixLerpNoise" }, // 2663453641
		{ &Z_Construct_UFunction_ULFPNoiseLibrary_MixLerpVector, "MixLerpVector" }, // 4136429264
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPNoiseLibrary_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n *\n */" },
		{ "IncludePath", "Math/LFPNoiseLibrary.h" },
		{ "ModuleRelativePath", "Public/Math/LFPNoiseLibrary.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULFPNoiseLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULFPNoiseLibrary>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULFPNoiseLibrary_Statics::ClassParams = {
		&ULFPNoiseLibrary::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_ULFPNoiseLibrary_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPNoiseLibrary_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULFPNoiseLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULFPNoiseLibrary_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULFPNoiseLibrary, 162733969);
	template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<ULFPNoiseLibrary>()
	{
		return ULFPNoiseLibrary::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULFPNoiseLibrary(Z_Construct_UClass_ULFPNoiseLibrary, &ULFPNoiseLibrary::StaticClass, TEXT("/Script/LohFunctionPlugin"), TEXT("ULFPNoiseLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULFPNoiseLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
