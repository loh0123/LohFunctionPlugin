// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LohFunctionPlugin/Public/Helper/LFPRandomTickHelper.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLFPRandomTickHelper() {}
// Cross Module References
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPRandomTickHelper_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPRandomTickHelper();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	UPackage* Z_Construct_UPackage__Script_LohFunctionPlugin();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRandomStream();
// End Cross Module References
	DEFINE_FUNCTION(ULFPRandomTickHelper::execRemoveTickActor)
	{
		P_GET_OBJECT(AActor,Z_Param_Actor);
		P_GET_UBOOL(Z_Param_RemoveAll);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->RemoveTickActor(Z_Param_Actor,Z_Param_RemoveAll);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPRandomTickHelper::execAddTickActor)
	{
		P_GET_OBJECT(AActor,Z_Param_Actor);
		P_GET_UBOOL(Z_Param_CheckDuplication);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->AddTickActor(Z_Param_Actor,Z_Param_CheckDuplication);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPRandomTickHelper::execSendTick)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(AActor**)Z_Param__Result=P_THIS->SendTick();
		P_NATIVE_END;
	}
	void ULFPRandomTickHelper::StaticRegisterNativesULFPRandomTickHelper()
	{
		UClass* Class = ULFPRandomTickHelper::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AddTickActor", &ULFPRandomTickHelper::execAddTickActor },
			{ "RemoveTickActor", &ULFPRandomTickHelper::execRemoveTickActor },
			{ "SendTick", &ULFPRandomTickHelper::execSendTick },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor_Statics
	{
		struct LFPRandomTickHelper_eventAddTickActor_Parms
		{
			AActor* Actor;
			bool CheckDuplication;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Actor;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CheckDuplication_MetaData[];
#endif
		static void NewProp_CheckDuplication_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_CheckDuplication;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor_Statics::NewProp_Actor = { "Actor", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPRandomTickHelper_eventAddTickActor_Parms, Actor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor_Statics::NewProp_CheckDuplication_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor_Statics::NewProp_CheckDuplication_SetBit(void* Obj)
	{
		((LFPRandomTickHelper_eventAddTickActor_Parms*)Obj)->CheckDuplication = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor_Statics::NewProp_CheckDuplication = { "CheckDuplication", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPRandomTickHelper_eventAddTickActor_Parms), &Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor_Statics::NewProp_CheckDuplication_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor_Statics::NewProp_CheckDuplication_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor_Statics::NewProp_CheckDuplication_MetaData)) };
	void Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPRandomTickHelper_eventAddTickActor_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPRandomTickHelper_eventAddTickActor_Parms), &Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor_Statics::NewProp_Actor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor_Statics::NewProp_CheckDuplication,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPRandomTickHelper" },
		{ "ModuleRelativePath", "Public/Helper/LFPRandomTickHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPRandomTickHelper, nullptr, "AddTickActor", nullptr, nullptr, sizeof(LFPRandomTickHelper_eventAddTickActor_Parms), Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor_Statics
	{
		struct LFPRandomTickHelper_eventRemoveTickActor_Parms
		{
			AActor* Actor;
			bool RemoveAll;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Actor;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RemoveAll_MetaData[];
#endif
		static void NewProp_RemoveAll_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_RemoveAll;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor_Statics::NewProp_Actor = { "Actor", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPRandomTickHelper_eventRemoveTickActor_Parms, Actor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor_Statics::NewProp_RemoveAll_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor_Statics::NewProp_RemoveAll_SetBit(void* Obj)
	{
		((LFPRandomTickHelper_eventRemoveTickActor_Parms*)Obj)->RemoveAll = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor_Statics::NewProp_RemoveAll = { "RemoveAll", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPRandomTickHelper_eventRemoveTickActor_Parms), &Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor_Statics::NewProp_RemoveAll_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor_Statics::NewProp_RemoveAll_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor_Statics::NewProp_RemoveAll_MetaData)) };
	void Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPRandomTickHelper_eventRemoveTickActor_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPRandomTickHelper_eventRemoveTickActor_Parms), &Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor_Statics::NewProp_Actor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor_Statics::NewProp_RemoveAll,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPRandomTickHelper" },
		{ "ModuleRelativePath", "Public/Helper/LFPRandomTickHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPRandomTickHelper, nullptr, "RemoveTickActor", nullptr, nullptr, sizeof(LFPRandomTickHelper_eventRemoveTickActor_Parms), Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPRandomTickHelper_SendTick_Statics
	{
		struct LFPRandomTickHelper_eventSendTick_Parms
		{
			AActor* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ULFPRandomTickHelper_SendTick_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPRandomTickHelper_eventSendTick_Parms, ReturnValue), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPRandomTickHelper_SendTick_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPRandomTickHelper_SendTick_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPRandomTickHelper_SendTick_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPRandomTickHelper" },
		{ "ModuleRelativePath", "Public/Helper/LFPRandomTickHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPRandomTickHelper_SendTick_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPRandomTickHelper, nullptr, "SendTick", nullptr, nullptr, sizeof(LFPRandomTickHelper_eventSendTick_Parms), Z_Construct_UFunction_ULFPRandomTickHelper_SendTick_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPRandomTickHelper_SendTick_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPRandomTickHelper_SendTick_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPRandomTickHelper_SendTick_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPRandomTickHelper_SendTick()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPRandomTickHelper_SendTick_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ULFPRandomTickHelper_NoRegister()
	{
		return ULFPRandomTickHelper::StaticClass();
	}
	struct Z_Construct_UClass_ULFPRandomTickHelper_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Seed_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Seed;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CallFunctionName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_CallFunctionName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TickCount_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_TickCount;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurrentArrayIndex_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_CurrentArrayIndex;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TickDelay_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_TickDelay;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurrentTickDelay_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_CurrentTickDelay;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_TickActorList_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TickActorList_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_TickActorList;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULFPRandomTickHelper_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ULFPRandomTickHelper_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULFPRandomTickHelper_AddTickActor, "AddTickActor" }, // 2407481979
		{ &Z_Construct_UFunction_ULFPRandomTickHelper_RemoveTickActor, "RemoveTickActor" }, // 2064441476
		{ &Z_Construct_UFunction_ULFPRandomTickHelper_SendTick, "SendTick" }, // 3221695775
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPRandomTickHelper_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "Helper/LFPRandomTickHelper.h" },
		{ "ModuleRelativePath", "Public/Helper/LFPRandomTickHelper.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_Seed_MetaData[] = {
		{ "Category", "LFPRandomTickHelper | Variable" },
		{ "ModuleRelativePath", "Public/Helper/LFPRandomTickHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_Seed = { "Seed", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPRandomTickHelper, Seed), Z_Construct_UScriptStruct_FRandomStream, METADATA_PARAMS(Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_Seed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_Seed_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_CallFunctionName_MetaData[] = {
		{ "Category", "LFPRandomTickHelper | Variable" },
		{ "ModuleRelativePath", "Public/Helper/LFPRandomTickHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_CallFunctionName = { "CallFunctionName", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPRandomTickHelper, CallFunctionName), METADATA_PARAMS(Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_CallFunctionName_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_CallFunctionName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_TickCount_MetaData[] = {
		{ "Category", "LFPRandomTickHelper | Variable" },
		{ "ModuleRelativePath", "Public/Helper/LFPRandomTickHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_TickCount = { "TickCount", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPRandomTickHelper, TickCount), METADATA_PARAMS(Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_TickCount_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_TickCount_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_CurrentArrayIndex_MetaData[] = {
		{ "Category", "LFPRandomTickHelper | Variable" },
		{ "ModuleRelativePath", "Public/Helper/LFPRandomTickHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_CurrentArrayIndex = { "CurrentArrayIndex", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPRandomTickHelper, CurrentArrayIndex), METADATA_PARAMS(Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_CurrentArrayIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_CurrentArrayIndex_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_TickDelay_MetaData[] = {
		{ "Category", "LFPRandomTickHelper | Variable" },
		{ "ModuleRelativePath", "Public/Helper/LFPRandomTickHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_TickDelay = { "TickDelay", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPRandomTickHelper, TickDelay), METADATA_PARAMS(Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_TickDelay_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_TickDelay_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_CurrentTickDelay_MetaData[] = {
		{ "Category", "LFPRandomTickHelper | Variable" },
		{ "ModuleRelativePath", "Public/Helper/LFPRandomTickHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_CurrentTickDelay = { "CurrentTickDelay", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPRandomTickHelper, CurrentTickDelay), METADATA_PARAMS(Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_CurrentTickDelay_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_CurrentTickDelay_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_TickActorList_Inner = { "TickActorList", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_TickActorList_MetaData[] = {
		{ "ModuleRelativePath", "Public/Helper/LFPRandomTickHelper.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_TickActorList = { "TickActorList", nullptr, (EPropertyFlags)0x0020080000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPRandomTickHelper, TickActorList), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_TickActorList_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_TickActorList_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULFPRandomTickHelper_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_Seed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_CallFunctionName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_TickCount,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_CurrentArrayIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_TickDelay,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_CurrentTickDelay,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_TickActorList_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPRandomTickHelper_Statics::NewProp_TickActorList,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULFPRandomTickHelper_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULFPRandomTickHelper>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULFPRandomTickHelper_Statics::ClassParams = {
		&ULFPRandomTickHelper::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ULFPRandomTickHelper_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ULFPRandomTickHelper_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ULFPRandomTickHelper_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPRandomTickHelper_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULFPRandomTickHelper()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULFPRandomTickHelper_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULFPRandomTickHelper, 4225367869);
	template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<ULFPRandomTickHelper>()
	{
		return ULFPRandomTickHelper::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULFPRandomTickHelper(Z_Construct_UClass_ULFPRandomTickHelper, &ULFPRandomTickHelper::StaticClass, TEXT("/Script/LohFunctionPlugin"), TEXT("ULFPRandomTickHelper"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULFPRandomTickHelper);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
