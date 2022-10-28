// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LohFunctionPlugin/Public/Math/LFPGridLibrary.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLFPGridLibrary() {}
// Cross Module References
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPGridLibrary_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPGridLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_LohFunctionPlugin();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntVector();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRandomStream();
// End Cross Module References
	DEFINE_FUNCTION(ULFPGridLibrary::execGetGridAreaIndex)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_Index);
		P_GET_STRUCT(FIntVector,Z_Param_Offset);
		P_GET_STRUCT(FIntVector,Z_Param_AreaSize);
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_GridSize);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<int32>*)Z_Param__Result=ULFPGridLibrary::GetGridAreaIndex(Z_Param_Index,Z_Param_Offset,Z_Param_AreaSize,Z_Param_Out_GridSize);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridLibrary::execRandomSectionGridIndex)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_Amount);
		P_GET_STRUCT(FIntVector,Z_Param_SectionSize);
		P_GET_TSET_REF(int32,Z_Param_Out_IgnoreIndexs);
		P_GET_STRUCT_REF(FRandomStream,Z_Param_Out_Seed);
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_GridSize);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<int32>*)Z_Param__Result=ULFPGridLibrary::RandomSectionGridIndex(Z_Param_Amount,Z_Param_SectionSize,Z_Param_Out_IgnoreIndexs,Z_Param_Out_Seed,Z_Param_Out_GridSize);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridLibrary::execSectionGridIndex)
	{
		P_GET_STRUCT(FIntVector,Z_Param_SectionSize);
		P_GET_TSET_REF(int32,Z_Param_Out_IgnoreIndexs);
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_GridSize);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<int32>*)Z_Param__Result=ULFPGridLibrary::SectionGridIndex(Z_Param_SectionSize,Z_Param_Out_IgnoreIndexs,Z_Param_Out_GridSize);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridLibrary::execToGridLocationList)
	{
		P_GET_TARRAY_REF(int32,Z_Param_Out_Indexs);
		P_GET_PROPERTY(FIntProperty,Z_Param_Offset);
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_GridSize);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FIntVector>*)Z_Param__Result=ULFPGridLibrary::ToGridLocationList(Z_Param_Out_Indexs,Z_Param_Offset,Z_Param_Out_GridSize);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridLibrary::execToGridLocation)
	{
		P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_Index);
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_GridSize);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FIntVector*)Z_Param__Result=ULFPGridLibrary::ToGridLocation(Z_Param_Out_Index,Z_Param_Out_GridSize);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridLibrary::execToIndexList)
	{
		P_GET_TARRAY_REF(FIntVector,Z_Param_Out_GridLocations);
		P_GET_STRUCT(FIntVector,Z_Param_Offset);
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_GridSize);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<int32>*)Z_Param__Result=ULFPGridLibrary::ToIndexList(Z_Param_Out_GridLocations,Z_Param_Offset,Z_Param_Out_GridSize);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridLibrary::execToIndex)
	{
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_Location);
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_GridSize);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=ULFPGridLibrary::ToIndex(Z_Param_Out_Location,Z_Param_Out_GridSize);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridLibrary::execIsOnGridEdge)
	{
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_Location);
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_GridSize);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=ULFPGridLibrary::IsOnGridEdge(Z_Param_Out_Location,Z_Param_Out_GridSize);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridLibrary::execIsLocationValid)
	{
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_Location);
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_GridSize);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=ULFPGridLibrary::IsLocationValid(Z_Param_Out_Location,Z_Param_Out_GridSize);
		P_NATIVE_END;
	}
	void ULFPGridLibrary::StaticRegisterNativesULFPGridLibrary()
	{
		UClass* Class = ULFPGridLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetGridAreaIndex", &ULFPGridLibrary::execGetGridAreaIndex },
			{ "IsLocationValid", &ULFPGridLibrary::execIsLocationValid },
			{ "IsOnGridEdge", &ULFPGridLibrary::execIsOnGridEdge },
			{ "RandomSectionGridIndex", &ULFPGridLibrary::execRandomSectionGridIndex },
			{ "SectionGridIndex", &ULFPGridLibrary::execSectionGridIndex },
			{ "ToGridLocation", &ULFPGridLibrary::execToGridLocation },
			{ "ToGridLocationList", &ULFPGridLibrary::execToGridLocationList },
			{ "ToIndex", &ULFPGridLibrary::execToIndex },
			{ "ToIndexList", &ULFPGridLibrary::execToIndexList },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics
	{
		struct LFPGridLibrary_eventGetGridAreaIndex_Parms
		{
			int32 Index;
			FIntVector Offset;
			FIntVector AreaSize;
			FIntVector GridSize;
			TArray<int32> ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Index_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Index;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Offset_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Offset;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AreaSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_AreaSize;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridSize;
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_Index_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventGetGridAreaIndex_Parms, Index), METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_Index_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_Index_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_Offset_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_Offset = { "Offset", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventGetGridAreaIndex_Parms, Offset), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_Offset_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_Offset_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_AreaSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_AreaSize = { "AreaSize", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventGetGridAreaIndex_Parms, AreaSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_AreaSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_AreaSize_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_GridSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_GridSize = { "GridSize", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventGetGridAreaIndex_Parms, GridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_GridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_GridSize_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventGetGridAreaIndex_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_Index,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_Offset,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_AreaSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_GridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridLibrary" },
		{ "ModuleRelativePath", "Public/Math/LFPGridLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridLibrary, nullptr, "GetGridAreaIndex", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::LFPGridLibrary_eventGetGridAreaIndex_Parms), Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics
	{
		struct LFPGridLibrary_eventIsLocationValid_Parms
		{
			FIntVector Location;
			FIntVector GridSize;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Location;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridSize;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventIsLocationValid_Parms, Location), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::NewProp_Location_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::NewProp_GridSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::NewProp_GridSize = { "GridSize", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventIsLocationValid_Parms, GridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::NewProp_GridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::NewProp_GridSize_MetaData)) };
	void Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPGridLibrary_eventIsLocationValid_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridLibrary_eventIsLocationValid_Parms), &Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::NewProp_Location,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::NewProp_GridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/Math/LFPGridLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridLibrary, nullptr, "IsLocationValid", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::LFPGridLibrary_eventIsLocationValid_Parms), Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics
	{
		struct LFPGridLibrary_eventIsOnGridEdge_Parms
		{
			FIntVector Location;
			FIntVector GridSize;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Location;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridSize;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventIsOnGridEdge_Parms, Location), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::NewProp_Location_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::NewProp_GridSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::NewProp_GridSize = { "GridSize", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventIsOnGridEdge_Parms, GridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::NewProp_GridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::NewProp_GridSize_MetaData)) };
	void Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPGridLibrary_eventIsOnGridEdge_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridLibrary_eventIsOnGridEdge_Parms), &Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::NewProp_Location,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::NewProp_GridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/Math/LFPGridLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridLibrary, nullptr, "IsOnGridEdge", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::LFPGridLibrary_eventIsOnGridEdge_Parms), Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics
	{
		struct LFPGridLibrary_eventRandomSectionGridIndex_Parms
		{
			int32 Amount;
			FIntVector SectionSize;
			TSet<int32> IgnoreIndexs;
			FRandomStream Seed;
			FIntVector GridSize;
			TArray<int32> ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Amount_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Amount;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SectionSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_SectionSize;
		static const UECodeGen_Private::FIntPropertyParams NewProp_IgnoreIndexs_ElementProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IgnoreIndexs_MetaData[];
#endif
		static const UECodeGen_Private::FSetPropertyParams NewProp_IgnoreIndexs;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Seed_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Seed;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridSize;
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_Amount_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_Amount = { "Amount", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventRandomSectionGridIndex_Parms, Amount), METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_Amount_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_Amount_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_SectionSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_SectionSize = { "SectionSize", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventRandomSectionGridIndex_Parms, SectionSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_SectionSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_SectionSize_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_IgnoreIndexs_ElementProp = { "IgnoreIndexs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_IgnoreIndexs_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FSetPropertyParams Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_IgnoreIndexs = { "IgnoreIndexs", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventRandomSectionGridIndex_Parms, IgnoreIndexs), METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_IgnoreIndexs_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_IgnoreIndexs_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_Seed_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_Seed = { "Seed", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventRandomSectionGridIndex_Parms, Seed), Z_Construct_UScriptStruct_FRandomStream, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_Seed_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_Seed_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_GridSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_GridSize = { "GridSize", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventRandomSectionGridIndex_Parms, GridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_GridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_GridSize_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventRandomSectionGridIndex_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_Amount,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_SectionSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_IgnoreIndexs_ElementProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_IgnoreIndexs,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_Seed,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_GridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridLibrary" },
		{ "ModuleRelativePath", "Public/Math/LFPGridLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridLibrary, nullptr, "RandomSectionGridIndex", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::LFPGridLibrary_eventRandomSectionGridIndex_Parms), Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics
	{
		struct LFPGridLibrary_eventSectionGridIndex_Parms
		{
			FIntVector SectionSize;
			TSet<int32> IgnoreIndexs;
			FIntVector GridSize;
			TArray<int32> ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SectionSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_SectionSize;
		static const UECodeGen_Private::FIntPropertyParams NewProp_IgnoreIndexs_ElementProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IgnoreIndexs_MetaData[];
#endif
		static const UECodeGen_Private::FSetPropertyParams NewProp_IgnoreIndexs;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridSize;
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::NewProp_SectionSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::NewProp_SectionSize = { "SectionSize", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventSectionGridIndex_Parms, SectionSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::NewProp_SectionSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::NewProp_SectionSize_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::NewProp_IgnoreIndexs_ElementProp = { "IgnoreIndexs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::NewProp_IgnoreIndexs_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FSetPropertyParams Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::NewProp_IgnoreIndexs = { "IgnoreIndexs", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventSectionGridIndex_Parms, IgnoreIndexs), METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::NewProp_IgnoreIndexs_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::NewProp_IgnoreIndexs_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::NewProp_GridSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::NewProp_GridSize = { "GridSize", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventSectionGridIndex_Parms, GridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::NewProp_GridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::NewProp_GridSize_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventSectionGridIndex_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::NewProp_SectionSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::NewProp_IgnoreIndexs_ElementProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::NewProp_IgnoreIndexs,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::NewProp_GridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridLibrary" },
		{ "ModuleRelativePath", "Public/Math/LFPGridLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridLibrary, nullptr, "SectionGridIndex", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::LFPGridLibrary_eventSectionGridIndex_Parms), Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation_Statics
	{
		struct LFPGridLibrary_eventToGridLocation_Parms
		{
			int32 Index;
			FIntVector GridSize;
			FIntVector ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Index_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Index;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridSize;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation_Statics::NewProp_Index_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventToGridLocation_Parms, Index), METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation_Statics::NewProp_Index_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation_Statics::NewProp_Index_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation_Statics::NewProp_GridSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation_Statics::NewProp_GridSize = { "GridSize", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventToGridLocation_Parms, GridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation_Statics::NewProp_GridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation_Statics::NewProp_GridSize_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventToGridLocation_Parms, ReturnValue), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation_Statics::NewProp_Index,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation_Statics::NewProp_GridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridLibrary" },
		{ "ModuleRelativePath", "Public/Math/LFPGridLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridLibrary, nullptr, "ToGridLocation", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation_Statics::LFPGridLibrary_eventToGridLocation_Parms), Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics
	{
		struct LFPGridLibrary_eventToGridLocationList_Parms
		{
			TArray<int32> Indexs;
			int32 Offset;
			FIntVector GridSize;
			TArray<FIntVector> ReturnValue;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_Indexs_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Indexs_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Indexs;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Offset_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Offset;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridSize;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::NewProp_Indexs_Inner = { "Indexs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::NewProp_Indexs_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::NewProp_Indexs = { "Indexs", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventToGridLocationList_Parms, Indexs), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::NewProp_Indexs_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::NewProp_Indexs_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::NewProp_Offset_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::NewProp_Offset = { "Offset", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventToGridLocationList_Parms, Offset), METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::NewProp_Offset_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::NewProp_Offset_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::NewProp_GridSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::NewProp_GridSize = { "GridSize", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventToGridLocationList_Parms, GridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::NewProp_GridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::NewProp_GridSize_MetaData)) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventToGridLocationList_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::NewProp_Indexs_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::NewProp_Indexs,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::NewProp_Offset,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::NewProp_GridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridLibrary" },
		{ "ModuleRelativePath", "Public/Math/LFPGridLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridLibrary, nullptr, "ToGridLocationList", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::LFPGridLibrary_eventToGridLocationList_Parms), Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridLibrary_ToIndex_Statics
	{
		struct LFPGridLibrary_eventToIndex_Parms
		{
			FIntVector Location;
			FIntVector GridSize;
			int32 ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Location;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridSize;
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_ToIndex_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridLibrary_ToIndex_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventToIndex_Parms, Location), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_ToIndex_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_ToIndex_Statics::NewProp_Location_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_ToIndex_Statics::NewProp_GridSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridLibrary_ToIndex_Statics::NewProp_GridSize = { "GridSize", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventToIndex_Parms, GridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_ToIndex_Statics::NewProp_GridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_ToIndex_Statics::NewProp_GridSize_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridLibrary_ToIndex_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventToIndex_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridLibrary_ToIndex_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_ToIndex_Statics::NewProp_Location,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_ToIndex_Statics::NewProp_GridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_ToIndex_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_ToIndex_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridLibrary" },
		{ "ModuleRelativePath", "Public/Math/LFPGridLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridLibrary_ToIndex_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridLibrary, nullptr, "ToIndex", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPGridLibrary_ToIndex_Statics::LFPGridLibrary_eventToIndex_Parms), Z_Construct_UFunction_ULFPGridLibrary_ToIndex_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_ToIndex_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C22401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_ToIndex_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_ToIndex_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridLibrary_ToIndex()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPGridLibrary_ToIndex_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics
	{
		struct LFPGridLibrary_eventToIndexList_Parms
		{
			TArray<FIntVector> GridLocations;
			FIntVector Offset;
			FIntVector GridSize;
			TArray<int32> ReturnValue;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridLocations_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridLocations_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_GridLocations;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Offset_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Offset;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GridSize_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_GridSize;
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::NewProp_GridLocations_Inner = { "GridLocations", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::NewProp_GridLocations_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::NewProp_GridLocations = { "GridLocations", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventToIndexList_Parms, GridLocations), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::NewProp_GridLocations_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::NewProp_GridLocations_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::NewProp_Offset_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::NewProp_Offset = { "Offset", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventToIndexList_Parms, Offset), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::NewProp_Offset_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::NewProp_Offset_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::NewProp_GridSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::NewProp_GridSize = { "GridSize", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventToIndexList_Parms, GridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::NewProp_GridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::NewProp_GridSize_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridLibrary_eventToIndexList_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::NewProp_GridLocations_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::NewProp_GridLocations,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::NewProp_Offset,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::NewProp_GridSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridLibrary" },
		{ "ModuleRelativePath", "Public/Math/LFPGridLibrary.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridLibrary, nullptr, "ToIndexList", nullptr, nullptr, sizeof(Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::LFPGridLibrary_eventToIndexList_Parms), Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C22401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridLibrary_ToIndexList()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULFPGridLibrary_ToIndexList_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ULFPGridLibrary);
	UClass* Z_Construct_UClass_ULFPGridLibrary_NoRegister()
	{
		return ULFPGridLibrary::StaticClass();
	}
	struct Z_Construct_UClass_ULFPGridLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULFPGridLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ULFPGridLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULFPGridLibrary_GetGridAreaIndex, "GetGridAreaIndex" }, // 2430488175
		{ &Z_Construct_UFunction_ULFPGridLibrary_IsLocationValid, "IsLocationValid" }, // 2932496045
		{ &Z_Construct_UFunction_ULFPGridLibrary_IsOnGridEdge, "IsOnGridEdge" }, // 2854277419
		{ &Z_Construct_UFunction_ULFPGridLibrary_RandomSectionGridIndex, "RandomSectionGridIndex" }, // 1741548676
		{ &Z_Construct_UFunction_ULFPGridLibrary_SectionGridIndex, "SectionGridIndex" }, // 2768533865
		{ &Z_Construct_UFunction_ULFPGridLibrary_ToGridLocation, "ToGridLocation" }, // 2442636609
		{ &Z_Construct_UFunction_ULFPGridLibrary_ToGridLocationList, "ToGridLocationList" }, // 2205632229
		{ &Z_Construct_UFunction_ULFPGridLibrary_ToIndex, "ToIndex" }, // 1969200034
		{ &Z_Construct_UFunction_ULFPGridLibrary_ToIndexList, "ToIndexList" }, // 1497738454
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPGridLibrary_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "Math/LFPGridLibrary.h" },
		{ "ModuleRelativePath", "Public/Math/LFPGridLibrary.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULFPGridLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULFPGridLibrary>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ULFPGridLibrary_Statics::ClassParams = {
		&ULFPGridLibrary::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_ULFPGridLibrary_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPGridLibrary_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULFPGridLibrary()
	{
		if (!Z_Registration_Info_UClass_ULFPGridLibrary.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULFPGridLibrary.OuterSingleton, Z_Construct_UClass_ULFPGridLibrary_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ULFPGridLibrary.OuterSingleton;
	}
	template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<ULFPGridLibrary>()
	{
		return ULFPGridLibrary::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULFPGridLibrary);
	struct Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPGridLibrary_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPGridLibrary_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ULFPGridLibrary, ULFPGridLibrary::StaticClass, TEXT("ULFPGridLibrary"), &Z_Registration_Info_UClass_ULFPGridLibrary, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULFPGridLibrary), 423352136U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPGridLibrary_h_1728342778(TEXT("/Script/LohFunctionPlugin"),
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPGridLibrary_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPGridLibrary_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
