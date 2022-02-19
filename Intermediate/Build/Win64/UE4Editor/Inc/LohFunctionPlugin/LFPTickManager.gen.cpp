// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LohFunctionPlugin/Public/Helper/LFPTickManager.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLFPTickManager() {}
// Cross Module References
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPTickManager_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPTickManager();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	UPackage* Z_Construct_UPackage__Script_LohFunctionPlugin();
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRandomStream();
// End Cross Module References
	DEFINE_FUNCTION(ULFPTickManager::execSendTickInternal)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SendTickInternal();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPTickManager::execRemoveTickActor)
	{
		P_GET_OBJECT(AActor,Z_Param_Actor);
		P_GET_UBOOL(Z_Param_RemoveAll);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->RemoveTickActor(Z_Param_Actor,Z_Param_RemoveAll);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPTickManager::execAddTickActor)
	{
		P_GET_OBJECT(AActor,Z_Param_Actor);
		P_GET_UBOOL(Z_Param_IsRandom);
		P_GET_UBOOL(Z_Param_CheckDuplication);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->AddTickActor(Z_Param_Actor,Z_Param_IsRandom,Z_Param_CheckDuplication);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPTickManager::execSendTick)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->SendTick();
		P_NATIVE_END;
	}
	void ULFPTickManager::StaticRegisterNativesULFPTickManager()
	{
		UClass* Class = ULFPTickManager::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AddTickActor", &ULFPTickManager::execAddTickActor },
			{ "RemoveTickActor", &ULFPTickManager::execRemoveTickActor },
			{ "SendTick", &ULFPTickManager::execSendTick },
			{ "SendTickInternal", &ULFPTickManager::execSendTickInternal },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics
	{
		struct LFPTickManager_eventAddTickActor_Parms
		{
			AActor* Actor;
			bool IsRandom;
			bool CheckDuplication;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Actor;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_IsRandom_MetaData[];
#endif
		static void NewProp_IsRandom_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_IsRandom;
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
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::NewProp_Actor = { "Actor", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPTickManager_eventAddTickActor_Parms, Actor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::NewProp_IsRandom_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::NewProp_IsRandom_SetBit(void* Obj)
	{
		((LFPTickManager_eventAddTickActor_Parms*)Obj)->IsRandom = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::NewProp_IsRandom = { "IsRandom", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPTickManager_eventAddTickActor_Parms), &Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::NewProp_IsRandom_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::NewProp_IsRandom_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::NewProp_IsRandom_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::NewProp_CheckDuplication_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::NewProp_CheckDuplication_SetBit(void* Obj)
	{
		((LFPTickManager_eventAddTickActor_Parms*)Obj)->CheckDuplication = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::NewProp_CheckDuplication = { "CheckDuplication", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPTickManager_eventAddTickActor_Parms), &Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::NewProp_CheckDuplication_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::NewProp_CheckDuplication_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::NewProp_CheckDuplication_MetaData)) };
	void Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPTickManager_eventAddTickActor_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPTickManager_eventAddTickActor_Parms), &Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::NewProp_Actor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::NewProp_IsRandom,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::NewProp_CheckDuplication,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPRandomTickHelper" },
		{ "CPP_Default_CheckDuplication", "false" },
		{ "ModuleRelativePath", "Public/Helper/LFPTickManager.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPTickManager, nullptr, "AddTickActor", nullptr, nullptr, sizeof(LFPTickManager_eventAddTickActor_Parms), Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPTickManager_AddTickActor()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPTickManager_AddTickActor_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPTickManager_RemoveTickActor_Statics
	{
		struct LFPTickManager_eventRemoveTickActor_Parms
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
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ULFPTickManager_RemoveTickActor_Statics::NewProp_Actor = { "Actor", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPTickManager_eventRemoveTickActor_Parms, Actor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPTickManager_RemoveTickActor_Statics::NewProp_RemoveAll_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPTickManager_RemoveTickActor_Statics::NewProp_RemoveAll_SetBit(void* Obj)
	{
		((LFPTickManager_eventRemoveTickActor_Parms*)Obj)->RemoveAll = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPTickManager_RemoveTickActor_Statics::NewProp_RemoveAll = { "RemoveAll", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPTickManager_eventRemoveTickActor_Parms), &Z_Construct_UFunction_ULFPTickManager_RemoveTickActor_Statics::NewProp_RemoveAll_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPTickManager_RemoveTickActor_Statics::NewProp_RemoveAll_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTickManager_RemoveTickActor_Statics::NewProp_RemoveAll_MetaData)) };
	void Z_Construct_UFunction_ULFPTickManager_RemoveTickActor_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPTickManager_eventRemoveTickActor_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPTickManager_RemoveTickActor_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPTickManager_eventRemoveTickActor_Parms), &Z_Construct_UFunction_ULFPTickManager_RemoveTickActor_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPTickManager_RemoveTickActor_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPTickManager_RemoveTickActor_Statics::NewProp_Actor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPTickManager_RemoveTickActor_Statics::NewProp_RemoveAll,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPTickManager_RemoveTickActor_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPTickManager_RemoveTickActor_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPRandomTickHelper" },
		{ "ModuleRelativePath", "Public/Helper/LFPTickManager.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPTickManager_RemoveTickActor_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPTickManager, nullptr, "RemoveTickActor", nullptr, nullptr, sizeof(LFPTickManager_eventRemoveTickActor_Parms), Z_Construct_UFunction_ULFPTickManager_RemoveTickActor_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTickManager_RemoveTickActor_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPTickManager_RemoveTickActor_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTickManager_RemoveTickActor_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPTickManager_RemoveTickActor()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPTickManager_RemoveTickActor_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPTickManager_SendTick_Statics
	{
		struct LFPTickManager_eventSendTick_Parms
		{
			int32 ReturnValue;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPTickManager_SendTick_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPTickManager_eventSendTick_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPTickManager_SendTick_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPTickManager_SendTick_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPTickManager_SendTick_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPRandomTickHelper" },
		{ "ModuleRelativePath", "Public/Helper/LFPTickManager.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPTickManager_SendTick_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPTickManager, nullptr, "SendTick", nullptr, nullptr, sizeof(LFPTickManager_eventSendTick_Parms), Z_Construct_UFunction_ULFPTickManager_SendTick_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTickManager_SendTick_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPTickManager_SendTick_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTickManager_SendTick_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPTickManager_SendTick()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPTickManager_SendTick_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPTickManager_SendTickInternal_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPTickManager_SendTickInternal_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Helper/LFPTickManager.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPTickManager_SendTickInternal_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPTickManager, nullptr, "SendTickInternal", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPTickManager_SendTickInternal_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPTickManager_SendTickInternal_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPTickManager_SendTickInternal()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPTickManager_SendTickInternal_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ULFPTickManager_NoRegister()
	{
		return ULFPTickManager::StaticClass();
	}
	struct Z_Construct_UClass_ULFPTickManager_Statics
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
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TickPerCall_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_TickPerCall;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TickCount_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_TickCount;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurrentArrayIndex_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_CurrentArrayIndex;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CurrentCallCount_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_CurrentCallCount;
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
	UObject* (*const Z_Construct_UClass_ULFPTickManager_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ULFPTickManager_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULFPTickManager_AddTickActor, "AddTickActor" }, // 2965622274
		{ &Z_Construct_UFunction_ULFPTickManager_RemoveTickActor, "RemoveTickActor" }, // 3363407176
		{ &Z_Construct_UFunction_ULFPTickManager_SendTick, "SendTick" }, // 4122285203
		{ &Z_Construct_UFunction_ULFPTickManager_SendTickInternal, "SendTickInternal" }, // 2526111842
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPTickManager_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "Helper/LFPTickManager.h" },
		{ "ModuleRelativePath", "Public/Helper/LFPTickManager.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPTickManager_Statics::NewProp_Seed_MetaData[] = {
		{ "Category", "LFPRandomTickHelper | Variable" },
		{ "ModuleRelativePath", "Public/Helper/LFPTickManager.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULFPTickManager_Statics::NewProp_Seed = { "Seed", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPTickManager, Seed), Z_Construct_UScriptStruct_FRandomStream, METADATA_PARAMS(Z_Construct_UClass_ULFPTickManager_Statics::NewProp_Seed_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPTickManager_Statics::NewProp_Seed_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPTickManager_Statics::NewProp_CallFunctionName_MetaData[] = {
		{ "Category", "LFPRandomTickHelper | Variable" },
		{ "ModuleRelativePath", "Public/Helper/LFPTickManager.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_ULFPTickManager_Statics::NewProp_CallFunctionName = { "CallFunctionName", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPTickManager, CallFunctionName), METADATA_PARAMS(Z_Construct_UClass_ULFPTickManager_Statics::NewProp_CallFunctionName_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPTickManager_Statics::NewProp_CallFunctionName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPTickManager_Statics::NewProp_TickPerCall_MetaData[] = {
		{ "Category", "LFPRandomTickHelper | Variable" },
		{ "ModuleRelativePath", "Public/Helper/LFPTickManager.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_ULFPTickManager_Statics::NewProp_TickPerCall = { "TickPerCall", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPTickManager, TickPerCall), METADATA_PARAMS(Z_Construct_UClass_ULFPTickManager_Statics::NewProp_TickPerCall_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPTickManager_Statics::NewProp_TickPerCall_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPTickManager_Statics::NewProp_TickCount_MetaData[] = {
		{ "Category", "LFPRandomTickHelper | Variable" },
		{ "ModuleRelativePath", "Public/Helper/LFPTickManager.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_ULFPTickManager_Statics::NewProp_TickCount = { "TickCount", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPTickManager, TickCount), METADATA_PARAMS(Z_Construct_UClass_ULFPTickManager_Statics::NewProp_TickCount_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPTickManager_Statics::NewProp_TickCount_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPTickManager_Statics::NewProp_CurrentArrayIndex_MetaData[] = {
		{ "Category", "LFPRandomTickHelper | Variable" },
		{ "ModuleRelativePath", "Public/Helper/LFPTickManager.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_ULFPTickManager_Statics::NewProp_CurrentArrayIndex = { "CurrentArrayIndex", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPTickManager, CurrentArrayIndex), METADATA_PARAMS(Z_Construct_UClass_ULFPTickManager_Statics::NewProp_CurrentArrayIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPTickManager_Statics::NewProp_CurrentArrayIndex_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPTickManager_Statics::NewProp_CurrentCallCount_MetaData[] = {
		{ "Category", "LFPRandomTickHelper | Variable" },
		{ "ModuleRelativePath", "Public/Helper/LFPTickManager.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_ULFPTickManager_Statics::NewProp_CurrentCallCount = { "CurrentCallCount", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPTickManager, CurrentCallCount), METADATA_PARAMS(Z_Construct_UClass_ULFPTickManager_Statics::NewProp_CurrentCallCount_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPTickManager_Statics::NewProp_CurrentCallCount_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPTickManager_Statics::NewProp_TickDelay_MetaData[] = {
		{ "Category", "LFPRandomTickHelper | Variable" },
		{ "ModuleRelativePath", "Public/Helper/LFPTickManager.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ULFPTickManager_Statics::NewProp_TickDelay = { "TickDelay", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPTickManager, TickDelay), METADATA_PARAMS(Z_Construct_UClass_ULFPTickManager_Statics::NewProp_TickDelay_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPTickManager_Statics::NewProp_TickDelay_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPTickManager_Statics::NewProp_CurrentTickDelay_MetaData[] = {
		{ "Category", "LFPRandomTickHelper | Variable" },
		{ "ModuleRelativePath", "Public/Helper/LFPTickManager.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ULFPTickManager_Statics::NewProp_CurrentTickDelay = { "CurrentTickDelay", nullptr, (EPropertyFlags)0x0010000000020015, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPTickManager, CurrentTickDelay), METADATA_PARAMS(Z_Construct_UClass_ULFPTickManager_Statics::NewProp_CurrentTickDelay_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPTickManager_Statics::NewProp_CurrentTickDelay_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ULFPTickManager_Statics::NewProp_TickActorList_Inner = { "TickActorList", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPTickManager_Statics::NewProp_TickActorList_MetaData[] = {
		{ "ModuleRelativePath", "Public/Helper/LFPTickManager.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ULFPTickManager_Statics::NewProp_TickActorList = { "TickActorList", nullptr, (EPropertyFlags)0x0020080000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPTickManager, TickActorList), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_ULFPTickManager_Statics::NewProp_TickActorList_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPTickManager_Statics::NewProp_TickActorList_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULFPTickManager_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPTickManager_Statics::NewProp_Seed,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPTickManager_Statics::NewProp_CallFunctionName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPTickManager_Statics::NewProp_TickPerCall,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPTickManager_Statics::NewProp_TickCount,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPTickManager_Statics::NewProp_CurrentArrayIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPTickManager_Statics::NewProp_CurrentCallCount,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPTickManager_Statics::NewProp_TickDelay,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPTickManager_Statics::NewProp_CurrentTickDelay,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPTickManager_Statics::NewProp_TickActorList_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPTickManager_Statics::NewProp_TickActorList,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULFPTickManager_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULFPTickManager>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULFPTickManager_Statics::ClassParams = {
		&ULFPTickManager::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ULFPTickManager_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ULFPTickManager_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ULFPTickManager_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPTickManager_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULFPTickManager()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULFPTickManager_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULFPTickManager, 1571898937);
	template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<ULFPTickManager>()
	{
		return ULFPTickManager::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULFPTickManager(Z_Construct_UClass_ULFPTickManager, &ULFPTickManager::StaticClass, TEXT("/Script/LohFunctionPlugin"), TEXT("ULFPTickManager"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULFPTickManager);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
