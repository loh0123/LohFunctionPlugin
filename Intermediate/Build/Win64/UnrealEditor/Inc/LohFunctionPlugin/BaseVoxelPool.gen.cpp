// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LohFunctionPlugin/Public/Mesh/BaseVoxelPool.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBaseVoxelPool() {}
// Cross Module References
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_UBaseVoxelPool_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_UBaseVoxelPool();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_LohFunctionPlugin();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntVector();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_UBaseVoxelMesh_NoRegister();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLFPVoxelMeshData();
// End Cross Module References
	DEFINE_FUNCTION(UBaseVoxelPool::execFreeAllMeshes)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->FreeAllMeshes();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBaseVoxelPool::execReturnAllMeshes)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ReturnAllMeshes();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBaseVoxelPool::execReturnMesh)
	{
		P_GET_OBJECT(UBaseVoxelMesh,Z_Param_Mesh);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ReturnMesh(Z_Param_Mesh);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBaseVoxelPool::execRequestMesh)
	{
		P_GET_STRUCT(FIntVector,Z_Param_PoolLocation);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UBaseVoxelMesh**)Z_Param__Result=P_THIS->RequestMesh(Z_Param_PoolLocation);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBaseVoxelPool::execProcessVoxelUpdate)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_Count);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ProcessVoxelUpdate(Z_Param_Count);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBaseVoxelPool::execSetupVoxelPool)
	{
		P_GET_STRUCT(FIntVector,Z_Param_NewPoolGridSize);
		P_GET_PROPERTY(FIntProperty,Z_Param_NewAllowMeshSize);
		P_GET_STRUCT(FVector,Z_Param_NewMainMeshSize);
		P_GET_STRUCT(FIntVector,Z_Param_NewMainGridSize);
		P_GET_OBJECT(UClass,Z_Param_VoxelType);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetupVoxelPool(Z_Param_NewPoolGridSize,Z_Param_NewAllowMeshSize,Z_Param_NewMainMeshSize,Z_Param_NewMainGridSize,Z_Param_VoxelType);
		P_NATIVE_END;
	}
	void UBaseVoxelPool::StaticRegisterNativesUBaseVoxelPool()
	{
		UClass* Class = UBaseVoxelPool::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "FreeAllMeshes", &UBaseVoxelPool::execFreeAllMeshes },
			{ "ProcessVoxelUpdate", &UBaseVoxelPool::execProcessVoxelUpdate },
			{ "RequestMesh", &UBaseVoxelPool::execRequestMesh },
			{ "ReturnAllMeshes", &UBaseVoxelPool::execReturnAllMeshes },
			{ "ReturnMesh", &UBaseVoxelPool::execReturnMesh },
			{ "SetupVoxelPool", &UBaseVoxelPool::execSetupVoxelPool },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UBaseVoxelPool_FreeAllMeshes_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelPool_FreeAllMeshes_Statics::Function_MetaDataParams[] = {
		{ "Category", "BaseVoxelPool" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelPool.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseVoxelPool_FreeAllMeshes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseVoxelPool, nullptr, "FreeAllMeshes", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelPool_FreeAllMeshes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelPool_FreeAllMeshes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBaseVoxelPool_FreeAllMeshes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBaseVoxelPool_FreeAllMeshes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBaseVoxelPool_ProcessVoxelUpdate_Statics
	{
		struct BaseVoxelPool_eventProcessVoxelUpdate_Parms
		{
			int32 Count;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Count_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Count;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelPool_ProcessVoxelUpdate_Statics::NewProp_Count_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UBaseVoxelPool_ProcessVoxelUpdate_Statics::NewProp_Count = { "Count", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseVoxelPool_eventProcessVoxelUpdate_Parms, Count), METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelPool_ProcessVoxelUpdate_Statics::NewProp_Count_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelPool_ProcessVoxelUpdate_Statics::NewProp_Count_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBaseVoxelPool_ProcessVoxelUpdate_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelPool_ProcessVoxelUpdate_Statics::NewProp_Count,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelPool_ProcessVoxelUpdate_Statics::Function_MetaDataParams[] = {
		{ "Category", "BaseVoxelPool | Function" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelPool.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseVoxelPool_ProcessVoxelUpdate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseVoxelPool, nullptr, "ProcessVoxelUpdate", nullptr, nullptr, sizeof(Z_Construct_UFunction_UBaseVoxelPool_ProcessVoxelUpdate_Statics::BaseVoxelPool_eventProcessVoxelUpdate_Parms), Z_Construct_UFunction_UBaseVoxelPool_ProcessVoxelUpdate_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelPool_ProcessVoxelUpdate_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelPool_ProcessVoxelUpdate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelPool_ProcessVoxelUpdate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBaseVoxelPool_ProcessVoxelUpdate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBaseVoxelPool_ProcessVoxelUpdate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBaseVoxelPool_RequestMesh_Statics
	{
		struct BaseVoxelPool_eventRequestMesh_Parms
		{
			FIntVector PoolLocation;
			UBaseVoxelMesh* ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PoolLocation_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_PoolLocation;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelPool_RequestMesh_Statics::NewProp_PoolLocation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBaseVoxelPool_RequestMesh_Statics::NewProp_PoolLocation = { "PoolLocation", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseVoxelPool_eventRequestMesh_Parms, PoolLocation), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelPool_RequestMesh_Statics::NewProp_PoolLocation_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelPool_RequestMesh_Statics::NewProp_PoolLocation_MetaData)) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBaseVoxelPool_RequestMesh_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseVoxelPool_eventRequestMesh_Parms, ReturnValue), Z_Construct_UClass_UBaseVoxelMesh_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBaseVoxelPool_RequestMesh_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelPool_RequestMesh_Statics::NewProp_PoolLocation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelPool_RequestMesh_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelPool_RequestMesh_Statics::Function_MetaDataParams[] = {
		{ "Category", "BaseVoxelPool" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelPool.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseVoxelPool_RequestMesh_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseVoxelPool, nullptr, "RequestMesh", nullptr, nullptr, sizeof(Z_Construct_UFunction_UBaseVoxelPool_RequestMesh_Statics::BaseVoxelPool_eventRequestMesh_Parms), Z_Construct_UFunction_UBaseVoxelPool_RequestMesh_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelPool_RequestMesh_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelPool_RequestMesh_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelPool_RequestMesh_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBaseVoxelPool_RequestMesh()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBaseVoxelPool_RequestMesh_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBaseVoxelPool_ReturnAllMeshes_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelPool_ReturnAllMeshes_Statics::Function_MetaDataParams[] = {
		{ "Category", "BaseVoxelPool" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelPool.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseVoxelPool_ReturnAllMeshes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseVoxelPool, nullptr, "ReturnAllMeshes", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelPool_ReturnAllMeshes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelPool_ReturnAllMeshes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBaseVoxelPool_ReturnAllMeshes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBaseVoxelPool_ReturnAllMeshes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBaseVoxelPool_ReturnMesh_Statics
	{
		struct BaseVoxelPool_eventReturnMesh_Parms
		{
			UBaseVoxelMesh* Mesh;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Mesh;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UBaseVoxelPool_ReturnMesh_Statics::NewProp_Mesh = { "Mesh", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseVoxelPool_eventReturnMesh_Parms, Mesh), Z_Construct_UClass_UBaseVoxelMesh_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBaseVoxelPool_ReturnMesh_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelPool_ReturnMesh_Statics::NewProp_Mesh,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelPool_ReturnMesh_Statics::Function_MetaDataParams[] = {
		{ "Category", "BaseVoxelPool" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelPool.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseVoxelPool_ReturnMesh_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseVoxelPool, nullptr, "ReturnMesh", nullptr, nullptr, sizeof(Z_Construct_UFunction_UBaseVoxelPool_ReturnMesh_Statics::BaseVoxelPool_eventReturnMesh_Parms), Z_Construct_UFunction_UBaseVoxelPool_ReturnMesh_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelPool_ReturnMesh_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelPool_ReturnMesh_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelPool_ReturnMesh_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBaseVoxelPool_ReturnMesh()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBaseVoxelPool_ReturnMesh_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics
	{
		struct BaseVoxelPool_eventSetupVoxelPool_Parms
		{
			FIntVector NewPoolGridSize;
			int32 NewAllowMeshSize;
			FVector NewMainMeshSize;
			FIntVector NewMainGridSize;
			TSubclassOf<UBaseVoxelMesh>  VoxelType;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NewPoolGridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_NewPoolGridSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NewAllowMeshSize_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_NewAllowMeshSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NewMainMeshSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_NewMainMeshSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NewMainGridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_NewMainGridSize;
		static const UECodeGen_Private::FClassPropertyParams NewProp_VoxelType;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::NewProp_NewPoolGridSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::NewProp_NewPoolGridSize = { "NewPoolGridSize", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseVoxelPool_eventSetupVoxelPool_Parms, NewPoolGridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::NewProp_NewPoolGridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::NewProp_NewPoolGridSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::NewProp_NewAllowMeshSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::NewProp_NewAllowMeshSize = { "NewAllowMeshSize", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseVoxelPool_eventSetupVoxelPool_Parms, NewAllowMeshSize), METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::NewProp_NewAllowMeshSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::NewProp_NewAllowMeshSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::NewProp_NewMainMeshSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::NewProp_NewMainMeshSize = { "NewMainMeshSize", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseVoxelPool_eventSetupVoxelPool_Parms, NewMainMeshSize), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::NewProp_NewMainMeshSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::NewProp_NewMainMeshSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::NewProp_NewMainGridSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::NewProp_NewMainGridSize = { "NewMainGridSize", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseVoxelPool_eventSetupVoxelPool_Parms, NewMainGridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::NewProp_NewMainGridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::NewProp_NewMainGridSize_MetaData)) };
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::NewProp_VoxelType = { "VoxelType", nullptr, (EPropertyFlags)0x0014000000000080, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BaseVoxelPool_eventSetupVoxelPool_Parms, VoxelType), Z_Construct_UClass_UBaseVoxelMesh_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::NewProp_NewPoolGridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::NewProp_NewAllowMeshSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::NewProp_NewMainMeshSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::NewProp_NewMainGridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::NewProp_VoxelType,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::Function_MetaDataParams[] = {
		{ "Category", "BaseVoxelPool | Function" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelPool.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBaseVoxelPool, nullptr, "SetupVoxelPool", nullptr, nullptr, sizeof(Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::BaseVoxelPool_eventSetupVoxelPool_Parms), Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UBaseVoxelPool);
	UClass* Z_Construct_UClass_UBaseVoxelPool_NoRegister()
	{
		return UBaseVoxelPool::StaticClass();
	}
	struct Z_Construct_UClass_UBaseVoxelPool_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_UpdateList_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_UpdateList_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_UpdateList;
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_CachedMeshes_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CachedMeshes_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_CachedMeshes;
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_ActiveMeshes_ValueProp;
		static const UECodeGen_Private::FIntPropertyParams NewProp_ActiveMeshes_Key_KeyProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ActiveMeshes_MetaData[];
#endif
		static const UECodeGen_Private::FMapPropertyParams NewProp_ActiveMeshes;
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_AllCreatedMeshes_ElementProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AllCreatedMeshes_MetaData[];
#endif
		static const UECodeGen_Private::FSetPropertyParams NewProp_AllCreatedMeshes;
		static const UECodeGen_Private::FStructPropertyParams NewProp_PoolVoxelData_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PoolVoxelData_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_PoolVoxelData;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PoolGridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_PoolGridSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PoolSize_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_PoolSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AllowMeshSize_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_AllowMeshSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MainMeshSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_MainMeshSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MainGridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_MainGridSize;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBaseVoxelPool_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UBaseVoxelPool_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UBaseVoxelPool_FreeAllMeshes, "FreeAllMeshes" }, // 3134575751
		{ &Z_Construct_UFunction_UBaseVoxelPool_ProcessVoxelUpdate, "ProcessVoxelUpdate" }, // 4187381258
		{ &Z_Construct_UFunction_UBaseVoxelPool_RequestMesh, "RequestMesh" }, // 1743741047
		{ &Z_Construct_UFunction_UBaseVoxelPool_ReturnAllMeshes, "ReturnAllMeshes" }, // 2316063127
		{ &Z_Construct_UFunction_UBaseVoxelPool_ReturnMesh, "ReturnMesh" }, // 2539310354
		{ &Z_Construct_UFunction_UBaseVoxelPool_SetupVoxelPool, "SetupVoxelPool" }, // 3116860393
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelPool_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Mesh/BaseVoxelPool.h" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelPool.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_UpdateList_Inner = { "UpdateList", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UBaseVoxelMesh_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_UpdateList_MetaData[] = {
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelPool.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_UpdateList = { "UpdateList", nullptr, (EPropertyFlags)0x0024080000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseVoxelPool, UpdateList), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_UpdateList_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_UpdateList_MetaData)) };
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_CachedMeshes_Inner = { "CachedMeshes", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UBaseVoxelMesh_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_CachedMeshes_MetaData[] = {
		{ "Comment", "/** Meshes in the pool that are available */" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelPool.h" },
		{ "ToolTip", "Meshes in the pool that are available" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_CachedMeshes = { "CachedMeshes", nullptr, (EPropertyFlags)0x0024080000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseVoxelPool, CachedMeshes), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_CachedMeshes_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_CachedMeshes_MetaData)) };
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_ActiveMeshes_ValueProp = { "ActiveMeshes", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, Z_Construct_UClass_UBaseVoxelMesh_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_ActiveMeshes_Key_KeyProp = { "ActiveMeshes_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_ActiveMeshes_MetaData[] = {
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelPool.h" },
	};
#endif
	const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_ActiveMeshes = { "ActiveMeshes", nullptr, (EPropertyFlags)0x0024080000000000, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseVoxelPool, ActiveMeshes), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_ActiveMeshes_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_ActiveMeshes_MetaData)) };
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_AllCreatedMeshes_ElementProp = { "AllCreatedMeshes", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UBaseVoxelMesh_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_AllCreatedMeshes_MetaData[] = {
		{ "Comment", "/** All meshes the pool has allocated */" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelPool.h" },
		{ "ToolTip", "All meshes the pool has allocated" },
	};
#endif
	const UECodeGen_Private::FSetPropertyParams Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_AllCreatedMeshes = { "AllCreatedMeshes", nullptr, (EPropertyFlags)0x0024080000000000, UECodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseVoxelPool, AllCreatedMeshes), METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_AllCreatedMeshes_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_AllCreatedMeshes_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_PoolVoxelData_Inner = { "PoolVoxelData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLFPVoxelMeshData, METADATA_PARAMS(nullptr, 0) }; // 4260804211
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_PoolVoxelData_MetaData[] = {
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelPool.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_PoolVoxelData = { "PoolVoxelData", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseVoxelPool, PoolVoxelData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_PoolVoxelData_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_PoolVoxelData_MetaData)) }; // 4260804211
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_PoolGridSize_MetaData[] = {
		{ "Category", "BaseVoxelPool | Setting" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelPool.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_PoolGridSize = { "PoolGridSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseVoxelPool, PoolGridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_PoolGridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_PoolGridSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_PoolSize_MetaData[] = {
		{ "Category", "BaseVoxelPool | Setting" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelPool.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_PoolSize = { "PoolSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseVoxelPool, PoolSize), METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_PoolSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_PoolSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_AllowMeshSize_MetaData[] = {
		{ "Category", "BaseVoxelPool | Setting" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelPool.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_AllowMeshSize = { "AllowMeshSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseVoxelPool, AllowMeshSize), METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_AllowMeshSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_AllowMeshSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_MainMeshSize_MetaData[] = {
		{ "Category", "BaseVoxelPool | Setting" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelPool.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_MainMeshSize = { "MainMeshSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseVoxelPool, MainMeshSize), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_MainMeshSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_MainMeshSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_MainGridSize_MetaData[] = {
		{ "Category", "BaseVoxelPool | Setting" },
		{ "ModuleRelativePath", "Public/Mesh/BaseVoxelPool.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_MainGridSize = { "MainGridSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBaseVoxelPool, MainGridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_MainGridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_MainGridSize_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBaseVoxelPool_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_UpdateList_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_UpdateList,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_CachedMeshes_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_CachedMeshes,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_ActiveMeshes_ValueProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_ActiveMeshes_Key_KeyProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_ActiveMeshes,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_AllCreatedMeshes_ElementProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_AllCreatedMeshes,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_PoolVoxelData_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_PoolVoxelData,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_PoolGridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_PoolSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_AllowMeshSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_MainMeshSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBaseVoxelPool_Statics::NewProp_MainGridSize,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBaseVoxelPool_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBaseVoxelPool>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UBaseVoxelPool_Statics::ClassParams = {
		&UBaseVoxelPool::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UBaseVoxelPool_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelPool_Statics::PropPointers),
		0,
		0x001000A8u,
		METADATA_PARAMS(Z_Construct_UClass_UBaseVoxelPool_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UBaseVoxelPool_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UBaseVoxelPool()
	{
		if (!Z_Registration_Info_UClass_UBaseVoxelPool.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBaseVoxelPool.OuterSingleton, Z_Construct_UClass_UBaseVoxelPool_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UBaseVoxelPool.OuterSingleton;
	}
	template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<UBaseVoxelPool>()
	{
		return UBaseVoxelPool::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBaseVoxelPool);
	struct Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UBaseVoxelPool, UBaseVoxelPool::StaticClass, TEXT("UBaseVoxelPool"), &Z_Registration_Info_UClass_UBaseVoxelPool, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBaseVoxelPool), 3249720661U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_3750463749(TEXT("/Script/LohFunctionPlugin"),
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
