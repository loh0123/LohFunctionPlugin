// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LohFunctionPlugin/Public/LFPGridSystem.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLFPGridSystem() {}
// Cross Module References
	LOHFUNCTIONPLUGIN_API UEnum* Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType();
	UPackage* Z_Construct_UPackage__Script_LohFunctionPlugin();
	LOHFUNCTIONPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FLGPGridSystemEvent();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPGridSystem_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_ULFPGridSystem();
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
	uint32 Get_Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType_Hash() { return 1946351231U; }
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
				{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
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
class UScriptStruct* FLGPGridSystemEvent::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern LOHFUNCTIONPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FLGPGridSystemEvent_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FLGPGridSystemEvent, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("LGPGridSystemEvent"), sizeof(FLGPGridSystemEvent), Get_Z_Construct_UScriptStruct_FLGPGridSystemEvent_Hash());
	}
	return Singleton;
}
template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<FLGPGridSystemEvent>()
{
	return FLGPGridSystemEvent::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FLGPGridSystemEvent(FLGPGridSystemEvent::StaticStruct, TEXT("/Script/LohFunctionPlugin"), TEXT("LGPGridSystemEvent"), false, nullptr, nullptr);
static struct FScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLGPGridSystemEvent
{
	FScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLGPGridSystemEvent()
	{
		UScriptStruct::DeferCppStructOps<FLGPGridSystemEvent>(FName(TEXT("LGPGridSystemEvent")));
	}
} ScriptStruct_LohFunctionPlugin_StaticRegisterNativesFLGPGridSystemEvent;
	struct Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_AddIndex_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AddIndex_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_AddIndex;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_AddData_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AddData_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_AddData;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_RemoveIndex_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_RemoveIndex_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_RemoveIndex;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLGPGridSystemEvent>();
	}
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::NewProp_AddIndex_Inner = { "AddIndex", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::NewProp_AddIndex_MetaData[] = {
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::NewProp_AddIndex = { "AddIndex", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLGPGridSystemEvent, AddIndex), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::NewProp_AddIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::NewProp_AddIndex_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::NewProp_AddData_Inner = { "AddData", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::NewProp_AddData_MetaData[] = {
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::NewProp_AddData = { "AddData", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLGPGridSystemEvent, AddData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::NewProp_AddData_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::NewProp_AddData_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::NewProp_RemoveIndex_Inner = { "RemoveIndex", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::NewProp_RemoveIndex_MetaData[] = {
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::NewProp_RemoveIndex = { "RemoveIndex", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FLGPGridSystemEvent, RemoveIndex), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::NewProp_RemoveIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::NewProp_RemoveIndex_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::NewProp_AddIndex_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::NewProp_AddIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::NewProp_AddData_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::NewProp_AddData,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::NewProp_RemoveIndex_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::NewProp_RemoveIndex,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
		nullptr,
		&NewStructOps,
		"LGPGridSystemEvent",
		sizeof(FLGPGridSystemEvent),
		alignof(FLGPGridSystemEvent),
		Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FLGPGridSystemEvent()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FLGPGridSystemEvent_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_LohFunctionPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("LGPGridSystemEvent"), sizeof(FLGPGridSystemEvent), Get_Z_Construct_UScriptStruct_FLGPGridSystemEvent_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FLGPGridSystemEvent_Hash() { return 983742503U; }
	DEFINE_FUNCTION(ULFPGridSystem::execUpdateEvent)
	{
		P_GET_STRUCT(FLGPGridSystemEvent,Z_Param_Data);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->UpdateEvent_Implementation(Z_Param_Data);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridSystem::execTryFitTemplateNear)
	{
		P_GET_TARRAY_REF(FVector,Z_Param_Out_Template);
		P_GET_STRUCT_REF(FVector,Z_Param_Out_Offset);
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_CheckSize);
		P_GET_STRUCT_REF(FVector,Z_Param_Out_FitOffset);
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_NeedRotation);
		P_GET_UBOOL(Z_Param_CanRotateX);
		P_GET_UBOOL(Z_Param_CanRotateY);
		P_GET_UBOOL(Z_Param_CanRotateZ);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->TryFitTemplateNear(Z_Param_Out_Template,Z_Param_Out_Offset,Z_Param_Out_CheckSize,Z_Param_Out_FitOffset,Z_Param_Out_NeedRotation,Z_Param_CanRotateX,Z_Param_CanRotateY,Z_Param_CanRotateZ);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridSystem::execTryFitTemplates)
	{
		P_GET_TARRAY_REF(FVector,Z_Param_Out_Template);
		P_GET_TARRAY_REF(FVector,Z_Param_Out_Offsets);
		P_GET_STRUCT_REF(FVector,Z_Param_Out_FitOffset);
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_NeedRotation);
		P_GET_UBOOL(Z_Param_CanRotateX);
		P_GET_UBOOL(Z_Param_CanRotateY);
		P_GET_UBOOL(Z_Param_CanRotateZ);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->TryFitTemplates(Z_Param_Out_Template,Z_Param_Out_Offsets,Z_Param_Out_FitOffset,Z_Param_Out_NeedRotation,Z_Param_CanRotateX,Z_Param_CanRotateY,Z_Param_CanRotateZ);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridSystem::execTryFitTemplate)
	{
		P_GET_TARRAY_REF(FVector,Z_Param_Out_Template);
		P_GET_STRUCT_REF(FVector,Z_Param_Out_Offset);
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_NeedRotation);
		P_GET_UBOOL(Z_Param_CanRotateX);
		P_GET_UBOOL(Z_Param_CanRotateY);
		P_GET_UBOOL(Z_Param_CanRotateZ);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->TryFitTemplate(Z_Param_Out_Template,Z_Param_Out_Offset,Z_Param_Out_NeedRotation,Z_Param_CanRotateX,Z_Param_CanRotateY,Z_Param_CanRotateZ);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridSystem::execGetGridWorldLocationWithIndex)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_Index);
		P_GET_STRUCT_REF(FVector,Z_Param_Out_ReturnLocation);
		P_GET_STRUCT_REF(FRotator,Z_Param_Out_ReturnRotation);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->GetGridWorldLocationWithIndex(Z_Param_Index,Z_Param_Out_ReturnLocation,Z_Param_Out_ReturnRotation);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridSystem::execGetGridWorldLocation)
	{
		P_GET_STRUCT(FIntVector,Z_Param_Location);
		P_GET_STRUCT_REF(FVector,Z_Param_Out_ReturnLocation);
		P_GET_STRUCT_REF(FRotator,Z_Param_Out_ReturnRotation);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->GetGridWorldLocation(Z_Param_Location,Z_Param_Out_ReturnLocation,Z_Param_Out_ReturnRotation);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridSystem::execGetLocationData)
	{
		P_GET_STRUCT(FVector,Z_Param_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetLocationData(Z_Param_Location);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridSystem::execGetGridData)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<int32>*)Z_Param__Result=P_THIS->GetGridData();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridSystem::execUnmarkLocations)
	{
		P_GET_TARRAY_REF(FVector,Z_Param_Out_Locations);
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_Rotation);
		P_GET_STRUCT_REF(FVector,Z_Param_Out_Offset);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->UnmarkLocations(Z_Param_Out_Locations,Z_Param_Out_Rotation,Z_Param_Out_Offset);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridSystem::execUnmarkLocation)
	{
		P_GET_STRUCT(FVector,Z_Param_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->UnmarkLocation(Z_Param_Location);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridSystem::execMarkLocations)
	{
		P_GET_TARRAY_REF(FVector,Z_Param_Out_Locations);
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_Rotation);
		P_GET_STRUCT_REF(FVector,Z_Param_Out_Offset);
		P_GET_PROPERTY(FIntProperty,Z_Param_Data);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->MarkLocations(Z_Param_Out_Locations,Z_Param_Out_Rotation,Z_Param_Out_Offset,Z_Param_Data);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridSystem::execMarkLocation)
	{
		P_GET_STRUCT(FVector,Z_Param_Location);
		P_GET_PROPERTY(FIntProperty,Z_Param_Data);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->MarkLocation(Z_Param_Location,Z_Param_Data);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridSystem::execIsLocationsMarked)
	{
		P_GET_TARRAY_REF(FVector,Z_Param_Out_Locations);
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_Rotation);
		P_GET_STRUCT_REF(FVector,Z_Param_Out_Offset);
		P_GET_UBOOL(Z_Param_MarkInvalid);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->IsLocationsMarked(Z_Param_Out_Locations,Z_Param_Out_Rotation,Z_Param_Out_Offset,Z_Param_MarkInvalid);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridSystem::execIsLocationMarked)
	{
		P_GET_STRUCT(FVector,Z_Param_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->IsLocationMarked(Z_Param_Location);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridSystem::execIsLocationValid)
	{
		P_GET_STRUCT(FVector,Z_Param_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->IsLocationValid(Z_Param_Location);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridSystem::execWordlLocationToGridLocation)
	{
		P_GET_STRUCT_REF(FVector,Z_Param_Out_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FIntVector*)Z_Param__Result=P_THIS->WordlLocationToGridLocation(Z_Param_Out_Location);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridSystem::execIndexToGridLocation)
	{
		P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_Index);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FIntVector*)Z_Param__Result=P_THIS->IndexToGridLocation(Z_Param_Out_Index);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ULFPGridSystem::execGridLocationToIndex)
	{
		P_GET_STRUCT_REF(FIntVector,Z_Param_Out_Location);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GridLocationToIndex(Z_Param_Out_Location);
		P_NATIVE_END;
	}
	static FName NAME_ULFPGridSystem_UpdateEvent = FName(TEXT("UpdateEvent"));
	void ULFPGridSystem::UpdateEvent(FLGPGridSystemEvent const& Data)
	{
		LFPGridSystem_eventUpdateEvent_Parms Parms;
		Parms.Data=Data;
		ProcessEvent(FindFunctionChecked(NAME_ULFPGridSystem_UpdateEvent),&Parms);
	}
	void ULFPGridSystem::StaticRegisterNativesULFPGridSystem()
	{
		UClass* Class = ULFPGridSystem::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetGridData", &ULFPGridSystem::execGetGridData },
			{ "GetGridWorldLocation", &ULFPGridSystem::execGetGridWorldLocation },
			{ "GetGridWorldLocationWithIndex", &ULFPGridSystem::execGetGridWorldLocationWithIndex },
			{ "GetLocationData", &ULFPGridSystem::execGetLocationData },
			{ "GridLocationToIndex", &ULFPGridSystem::execGridLocationToIndex },
			{ "IndexToGridLocation", &ULFPGridSystem::execIndexToGridLocation },
			{ "IsLocationMarked", &ULFPGridSystem::execIsLocationMarked },
			{ "IsLocationsMarked", &ULFPGridSystem::execIsLocationsMarked },
			{ "IsLocationValid", &ULFPGridSystem::execIsLocationValid },
			{ "MarkLocation", &ULFPGridSystem::execMarkLocation },
			{ "MarkLocations", &ULFPGridSystem::execMarkLocations },
			{ "TryFitTemplate", &ULFPGridSystem::execTryFitTemplate },
			{ "TryFitTemplateNear", &ULFPGridSystem::execTryFitTemplateNear },
			{ "TryFitTemplates", &ULFPGridSystem::execTryFitTemplates },
			{ "UnmarkLocation", &ULFPGridSystem::execUnmarkLocation },
			{ "UnmarkLocations", &ULFPGridSystem::execUnmarkLocations },
			{ "UpdateEvent", &ULFPGridSystem::execUpdateEvent },
			{ "WordlLocationToGridLocation", &ULFPGridSystem::execWordlLocationToGridLocation },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ULFPGridSystem_GetGridData_Statics
	{
		struct LFPGridSystem_eventGetGridData_Parms
		{
			TArray<int32> ReturnValue;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ReturnValue_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridSystem_GetGridData_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPGridSystem_GetGridData_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventGetGridData_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridSystem_GetGridData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_GetGridData_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_GetGridData_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_GetGridData_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridSystem_GetGridData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridSystem, nullptr, "GetGridData", nullptr, nullptr, sizeof(LFPGridSystem_eventGetGridData_Parms), Z_Construct_UFunction_ULFPGridSystem_GetGridData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_GetGridData_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_GetGridData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_GetGridData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridSystem_GetGridData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridSystem_GetGridData_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation_Statics
	{
		struct LFPGridSystem_eventGetGridWorldLocation_Parms
		{
			FIntVector Location;
			FVector ReturnLocation;
			FRotator ReturnRotation;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Location;
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventGetGridWorldLocation_Parms, Location), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation_Statics::NewProp_Location_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation_Statics::NewProp_ReturnLocation = { "ReturnLocation", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventGetGridWorldLocation_Parms, ReturnLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation_Statics::NewProp_ReturnRotation = { "ReturnRotation", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventGetGridWorldLocation_Parms, ReturnRotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPGridSystem_eventGetGridWorldLocation_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridSystem_eventGetGridWorldLocation_Parms), &Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation_Statics::NewProp_ReturnLocation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation_Statics::NewProp_ReturnRotation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridSystem, nullptr, "GetGridWorldLocation", nullptr, nullptr, sizeof(LFPGridSystem_eventGetGridWorldLocation_Parms), Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex_Statics
	{
		struct LFPGridSystem_eventGetGridWorldLocationWithIndex_Parms
		{
			int32 Index;
			FVector ReturnLocation;
			FRotator ReturnRotation;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Index_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Index;
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex_Statics::NewProp_Index_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventGetGridWorldLocationWithIndex_Parms, Index), METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex_Statics::NewProp_Index_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex_Statics::NewProp_Index_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex_Statics::NewProp_ReturnLocation = { "ReturnLocation", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventGetGridWorldLocationWithIndex_Parms, ReturnLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex_Statics::NewProp_ReturnRotation = { "ReturnRotation", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventGetGridWorldLocationWithIndex_Parms, ReturnRotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPGridSystem_eventGetGridWorldLocationWithIndex_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridSystem_eventGetGridWorldLocationWithIndex_Parms), &Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex_Statics::NewProp_Index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex_Statics::NewProp_ReturnLocation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex_Statics::NewProp_ReturnRotation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridSystem, nullptr, "GetGridWorldLocationWithIndex", nullptr, nullptr, sizeof(LFPGridSystem_eventGetGridWorldLocationWithIndex_Parms), Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridSystem_GetLocationData_Statics
	{
		struct LFPGridSystem_eventGetLocationData_Parms
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_GetLocationData_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_GetLocationData_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventGetLocationData_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_GetLocationData_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_GetLocationData_Statics::NewProp_Location_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridSystem_GetLocationData_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventGetLocationData_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridSystem_GetLocationData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_GetLocationData_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_GetLocationData_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_GetLocationData_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridSystem_GetLocationData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridSystem, nullptr, "GetLocationData", nullptr, nullptr, sizeof(LFPGridSystem_eventGetLocationData_Parms), Z_Construct_UFunction_ULFPGridSystem_GetLocationData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_GetLocationData_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_GetLocationData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_GetLocationData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridSystem_GetLocationData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridSystem_GetLocationData_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridSystem_GridLocationToIndex_Statics
	{
		struct LFPGridSystem_eventGridLocationToIndex_Parms
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_GridLocationToIndex_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_GridLocationToIndex_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventGridLocationToIndex_Parms, Location), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_GridLocationToIndex_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_GridLocationToIndex_Statics::NewProp_Location_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridSystem_GridLocationToIndex_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventGridLocationToIndex_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridSystem_GridLocationToIndex_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_GridLocationToIndex_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_GridLocationToIndex_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_GridLocationToIndex_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridSystem_GridLocationToIndex_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridSystem, nullptr, "GridLocationToIndex", nullptr, nullptr, sizeof(LFPGridSystem_eventGridLocationToIndex_Parms), Z_Construct_UFunction_ULFPGridSystem_GridLocationToIndex_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_GridLocationToIndex_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_GridLocationToIndex_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_GridLocationToIndex_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridSystem_GridLocationToIndex()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridSystem_GridLocationToIndex_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridSystem_IndexToGridLocation_Statics
	{
		struct LFPGridSystem_eventIndexToGridLocation_Parms
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_IndexToGridLocation_Statics::NewProp_Index_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridSystem_IndexToGridLocation_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventIndexToGridLocation_Parms, Index), METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_IndexToGridLocation_Statics::NewProp_Index_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_IndexToGridLocation_Statics::NewProp_Index_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_IndexToGridLocation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventIndexToGridLocation_Parms, ReturnValue), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridSystem_IndexToGridLocation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_IndexToGridLocation_Statics::NewProp_Index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_IndexToGridLocation_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_IndexToGridLocation_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridSystem_IndexToGridLocation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridSystem, nullptr, "IndexToGridLocation", nullptr, nullptr, sizeof(LFPGridSystem_eventIndexToGridLocation_Parms), Z_Construct_UFunction_ULFPGridSystem_IndexToGridLocation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_IndexToGridLocation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_IndexToGridLocation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_IndexToGridLocation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridSystem_IndexToGridLocation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridSystem_IndexToGridLocation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridSystem_IsLocationMarked_Statics
	{
		struct LFPGridSystem_eventIsLocationMarked_Parms
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_IsLocationMarked_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_IsLocationMarked_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventIsLocationMarked_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_IsLocationMarked_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_IsLocationMarked_Statics::NewProp_Location_MetaData)) };
	void Z_Construct_UFunction_ULFPGridSystem_IsLocationMarked_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPGridSystem_eventIsLocationMarked_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridSystem_IsLocationMarked_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridSystem_eventIsLocationMarked_Parms), &Z_Construct_UFunction_ULFPGridSystem_IsLocationMarked_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridSystem_IsLocationMarked_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_IsLocationMarked_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_IsLocationMarked_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_IsLocationMarked_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridSystem_IsLocationMarked_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridSystem, nullptr, "IsLocationMarked", nullptr, nullptr, sizeof(LFPGridSystem_eventIsLocationMarked_Parms), Z_Construct_UFunction_ULFPGridSystem_IsLocationMarked_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_IsLocationMarked_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_IsLocationMarked_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_IsLocationMarked_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridSystem_IsLocationMarked()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridSystem_IsLocationMarked_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics
	{
		struct LFPGridSystem_eventIsLocationsMarked_Parms
		{
			TArray<FVector> Locations;
			FIntVector Rotation;
			FVector Offset;
			bool MarkInvalid;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Locations_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Locations_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Locations;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Rotation_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Rotation;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Offset_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Offset;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MarkInvalid_MetaData[];
#endif
		static void NewProp_MarkInvalid_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_MarkInvalid;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_Locations_Inner = { "Locations", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_Locations_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_Locations = { "Locations", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventIsLocationsMarked_Parms, Locations), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_Locations_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_Locations_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_Rotation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_Rotation = { "Rotation", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventIsLocationsMarked_Parms, Rotation), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_Rotation_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_Rotation_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_Offset_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_Offset = { "Offset", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventIsLocationsMarked_Parms, Offset), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_Offset_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_Offset_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_MarkInvalid_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_MarkInvalid_SetBit(void* Obj)
	{
		((LFPGridSystem_eventIsLocationsMarked_Parms*)Obj)->MarkInvalid = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_MarkInvalid = { "MarkInvalid", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridSystem_eventIsLocationsMarked_Parms), &Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_MarkInvalid_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_MarkInvalid_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_MarkInvalid_MetaData)) };
	void Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPGridSystem_eventIsLocationsMarked_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridSystem_eventIsLocationsMarked_Parms), &Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_Locations_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_Locations,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_Rotation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_Offset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_MarkInvalid,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "CPP_Default_MarkInvalid", "false" },
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridSystem, nullptr, "IsLocationsMarked", nullptr, nullptr, sizeof(LFPGridSystem_eventIsLocationsMarked_Parms), Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridSystem_IsLocationValid_Statics
	{
		struct LFPGridSystem_eventIsLocationValid_Parms
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_IsLocationValid_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_IsLocationValid_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventIsLocationValid_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_IsLocationValid_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_IsLocationValid_Statics::NewProp_Location_MetaData)) };
	void Z_Construct_UFunction_ULFPGridSystem_IsLocationValid_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPGridSystem_eventIsLocationValid_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridSystem_IsLocationValid_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridSystem_eventIsLocationValid_Parms), &Z_Construct_UFunction_ULFPGridSystem_IsLocationValid_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridSystem_IsLocationValid_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_IsLocationValid_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_IsLocationValid_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_IsLocationValid_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridSystem_IsLocationValid_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridSystem, nullptr, "IsLocationValid", nullptr, nullptr, sizeof(LFPGridSystem_eventIsLocationValid_Parms), Z_Construct_UFunction_ULFPGridSystem_IsLocationValid_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_IsLocationValid_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_IsLocationValid_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_IsLocationValid_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridSystem_IsLocationValid()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridSystem_IsLocationValid_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics
	{
		struct LFPGridSystem_eventMarkLocation_Parms
		{
			FVector Location;
			int32 Data;
			bool ReturnValue;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Location;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Data_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Data;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventMarkLocation_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics::NewProp_Location_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics::NewProp_Data_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics::NewProp_Data = { "Data", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventMarkLocation_Parms, Data), METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics::NewProp_Data_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics::NewProp_Data_MetaData)) };
	void Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPGridSystem_eventMarkLocation_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridSystem_eventMarkLocation_Parms), &Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics::NewProp_Data,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridSystem, nullptr, "MarkLocation", nullptr, nullptr, sizeof(LFPGridSystem_eventMarkLocation_Parms), Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridSystem_MarkLocation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridSystem_MarkLocation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics
	{
		struct LFPGridSystem_eventMarkLocations_Parms
		{
			TArray<FVector> Locations;
			FIntVector Rotation;
			FVector Offset;
			int32 Data;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Locations_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Locations_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Locations;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Rotation_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Rotation;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Offset_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Offset;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Data_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Data;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_Locations_Inner = { "Locations", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_Locations_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_Locations = { "Locations", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventMarkLocations_Parms, Locations), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_Locations_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_Locations_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_Rotation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_Rotation = { "Rotation", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventMarkLocations_Parms, Rotation), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_Rotation_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_Rotation_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_Offset_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_Offset = { "Offset", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventMarkLocations_Parms, Offset), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_Offset_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_Offset_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_Data_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_Data = { "Data", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventMarkLocations_Parms, Data), METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_Data_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_Data_MetaData)) };
	void Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPGridSystem_eventMarkLocations_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridSystem_eventMarkLocations_Parms), &Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_Locations_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_Locations,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_Rotation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_Offset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_Data,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridSystem, nullptr, "MarkLocations", nullptr, nullptr, sizeof(LFPGridSystem_eventMarkLocations_Parms), Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridSystem_MarkLocations()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridSystem_MarkLocations_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics
	{
		struct LFPGridSystem_eventTryFitTemplate_Parms
		{
			TArray<FVector> Template;
			FVector Offset;
			FIntVector NeedRotation;
			bool CanRotateX;
			bool CanRotateY;
			bool CanRotateZ;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Template_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Template_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Template;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Offset_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Offset;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_NeedRotation;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CanRotateX_MetaData[];
#endif
		static void NewProp_CanRotateX_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_CanRotateX;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CanRotateY_MetaData[];
#endif
		static void NewProp_CanRotateY_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_CanRotateY;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CanRotateZ_MetaData[];
#endif
		static void NewProp_CanRotateZ_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_CanRotateZ;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_Template_Inner = { "Template", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_Template_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_Template = { "Template", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventTryFitTemplate_Parms, Template), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_Template_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_Template_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_Offset_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_Offset = { "Offset", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventTryFitTemplate_Parms, Offset), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_Offset_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_Offset_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_NeedRotation = { "NeedRotation", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventTryFitTemplate_Parms, NeedRotation), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_CanRotateX_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_CanRotateX_SetBit(void* Obj)
	{
		((LFPGridSystem_eventTryFitTemplate_Parms*)Obj)->CanRotateX = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_CanRotateX = { "CanRotateX", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridSystem_eventTryFitTemplate_Parms), &Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_CanRotateX_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_CanRotateX_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_CanRotateX_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_CanRotateY_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_CanRotateY_SetBit(void* Obj)
	{
		((LFPGridSystem_eventTryFitTemplate_Parms*)Obj)->CanRotateY = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_CanRotateY = { "CanRotateY", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridSystem_eventTryFitTemplate_Parms), &Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_CanRotateY_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_CanRotateY_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_CanRotateY_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_CanRotateZ_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_CanRotateZ_SetBit(void* Obj)
	{
		((LFPGridSystem_eventTryFitTemplate_Parms*)Obj)->CanRotateZ = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_CanRotateZ = { "CanRotateZ", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridSystem_eventTryFitTemplate_Parms), &Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_CanRotateZ_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_CanRotateZ_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_CanRotateZ_MetaData)) };
	void Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPGridSystem_eventTryFitTemplate_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridSystem_eventTryFitTemplate_Parms), &Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_Template_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_Template,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_Offset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_NeedRotation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_CanRotateX,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_CanRotateY,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_CanRotateZ,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridSystem, nullptr, "TryFitTemplate", nullptr, nullptr, sizeof(LFPGridSystem_eventTryFitTemplate_Parms), Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics
	{
		struct LFPGridSystem_eventTryFitTemplateNear_Parms
		{
			TArray<FVector> Template;
			FVector Offset;
			FIntVector CheckSize;
			FVector FitOffset;
			FIntVector NeedRotation;
			bool CanRotateX;
			bool CanRotateY;
			bool CanRotateZ;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Template_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Template_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Template;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Offset_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Offset;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CheckSize_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_CheckSize;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_FitOffset;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_NeedRotation;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CanRotateX_MetaData[];
#endif
		static void NewProp_CanRotateX_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_CanRotateX;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CanRotateY_MetaData[];
#endif
		static void NewProp_CanRotateY_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_CanRotateY;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CanRotateZ_MetaData[];
#endif
		static void NewProp_CanRotateZ_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_CanRotateZ;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_Template_Inner = { "Template", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_Template_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_Template = { "Template", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventTryFitTemplateNear_Parms, Template), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_Template_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_Template_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_Offset_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_Offset = { "Offset", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventTryFitTemplateNear_Parms, Offset), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_Offset_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_Offset_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CheckSize_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CheckSize = { "CheckSize", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventTryFitTemplateNear_Parms, CheckSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CheckSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CheckSize_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_FitOffset = { "FitOffset", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventTryFitTemplateNear_Parms, FitOffset), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_NeedRotation = { "NeedRotation", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventTryFitTemplateNear_Parms, NeedRotation), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CanRotateX_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CanRotateX_SetBit(void* Obj)
	{
		((LFPGridSystem_eventTryFitTemplateNear_Parms*)Obj)->CanRotateX = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CanRotateX = { "CanRotateX", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridSystem_eventTryFitTemplateNear_Parms), &Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CanRotateX_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CanRotateX_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CanRotateX_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CanRotateY_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CanRotateY_SetBit(void* Obj)
	{
		((LFPGridSystem_eventTryFitTemplateNear_Parms*)Obj)->CanRotateY = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CanRotateY = { "CanRotateY", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridSystem_eventTryFitTemplateNear_Parms), &Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CanRotateY_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CanRotateY_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CanRotateY_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CanRotateZ_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CanRotateZ_SetBit(void* Obj)
	{
		((LFPGridSystem_eventTryFitTemplateNear_Parms*)Obj)->CanRotateZ = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CanRotateZ = { "CanRotateZ", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridSystem_eventTryFitTemplateNear_Parms), &Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CanRotateZ_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CanRotateZ_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CanRotateZ_MetaData)) };
	void Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPGridSystem_eventTryFitTemplateNear_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridSystem_eventTryFitTemplateNear_Parms), &Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_Template_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_Template,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_Offset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CheckSize,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_FitOffset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_NeedRotation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CanRotateX,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CanRotateY,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_CanRotateZ,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridSystem, nullptr, "TryFitTemplateNear", nullptr, nullptr, sizeof(LFPGridSystem_eventTryFitTemplateNear_Parms), Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics
	{
		struct LFPGridSystem_eventTryFitTemplates_Parms
		{
			TArray<FVector> Template;
			TArray<FVector> Offsets;
			FVector FitOffset;
			FIntVector NeedRotation;
			bool CanRotateX;
			bool CanRotateY;
			bool CanRotateZ;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Template_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Template_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Template;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Offsets_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Offsets_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Offsets;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_FitOffset;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_NeedRotation;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CanRotateX_MetaData[];
#endif
		static void NewProp_CanRotateX_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_CanRotateX;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CanRotateY_MetaData[];
#endif
		static void NewProp_CanRotateY_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_CanRotateY;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CanRotateZ_MetaData[];
#endif
		static void NewProp_CanRotateZ_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_CanRotateZ;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_Template_Inner = { "Template", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_Template_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_Template = { "Template", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventTryFitTemplates_Parms, Template), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_Template_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_Template_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_Offsets_Inner = { "Offsets", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_Offsets_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_Offsets = { "Offsets", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventTryFitTemplates_Parms, Offsets), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_Offsets_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_Offsets_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_FitOffset = { "FitOffset", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventTryFitTemplates_Parms, FitOffset), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_NeedRotation = { "NeedRotation", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventTryFitTemplates_Parms, NeedRotation), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_CanRotateX_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_CanRotateX_SetBit(void* Obj)
	{
		((LFPGridSystem_eventTryFitTemplates_Parms*)Obj)->CanRotateX = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_CanRotateX = { "CanRotateX", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridSystem_eventTryFitTemplates_Parms), &Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_CanRotateX_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_CanRotateX_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_CanRotateX_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_CanRotateY_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_CanRotateY_SetBit(void* Obj)
	{
		((LFPGridSystem_eventTryFitTemplates_Parms*)Obj)->CanRotateY = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_CanRotateY = { "CanRotateY", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridSystem_eventTryFitTemplates_Parms), &Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_CanRotateY_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_CanRotateY_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_CanRotateY_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_CanRotateZ_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	void Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_CanRotateZ_SetBit(void* Obj)
	{
		((LFPGridSystem_eventTryFitTemplates_Parms*)Obj)->CanRotateZ = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_CanRotateZ = { "CanRotateZ", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridSystem_eventTryFitTemplates_Parms), &Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_CanRotateZ_SetBit, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_CanRotateZ_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_CanRotateZ_MetaData)) };
	void Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPGridSystem_eventTryFitTemplates_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridSystem_eventTryFitTemplates_Parms), &Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_Template_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_Template,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_Offsets_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_Offsets,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_FitOffset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_NeedRotation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_CanRotateX,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_CanRotateY,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_CanRotateZ,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridSystem, nullptr, "TryFitTemplates", nullptr, nullptr, sizeof(LFPGridSystem_eventTryFitTemplates_Parms), Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridSystem_UnmarkLocation_Statics
	{
		struct LFPGridSystem_eventUnmarkLocation_Parms
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_UnmarkLocation_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_UnmarkLocation_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventUnmarkLocation_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_UnmarkLocation_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_UnmarkLocation_Statics::NewProp_Location_MetaData)) };
	void Z_Construct_UFunction_ULFPGridSystem_UnmarkLocation_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPGridSystem_eventUnmarkLocation_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridSystem_UnmarkLocation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridSystem_eventUnmarkLocation_Parms), &Z_Construct_UFunction_ULFPGridSystem_UnmarkLocation_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridSystem_UnmarkLocation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_UnmarkLocation_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_UnmarkLocation_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_UnmarkLocation_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridSystem_UnmarkLocation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridSystem, nullptr, "UnmarkLocation", nullptr, nullptr, sizeof(LFPGridSystem_eventUnmarkLocation_Parms), Z_Construct_UFunction_ULFPGridSystem_UnmarkLocation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_UnmarkLocation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_UnmarkLocation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_UnmarkLocation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridSystem_UnmarkLocation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridSystem_UnmarkLocation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics
	{
		struct LFPGridSystem_eventUnmarkLocations_Parms
		{
			TArray<FVector> Locations;
			FIntVector Rotation;
			FVector Offset;
			bool ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Locations_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Locations_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Locations;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Rotation_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Rotation;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Offset_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Offset;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::NewProp_Locations_Inner = { "Locations", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::NewProp_Locations_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::NewProp_Locations = { "Locations", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventUnmarkLocations_Parms, Locations), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::NewProp_Locations_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::NewProp_Locations_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::NewProp_Rotation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::NewProp_Rotation = { "Rotation", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventUnmarkLocations_Parms, Rotation), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::NewProp_Rotation_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::NewProp_Rotation_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::NewProp_Offset_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::NewProp_Offset = { "Offset", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventUnmarkLocations_Parms, Offset), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::NewProp_Offset_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::NewProp_Offset_MetaData)) };
	void Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((LFPGridSystem_eventUnmarkLocations_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(LFPGridSystem_eventUnmarkLocations_Parms), &Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::NewProp_Locations_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::NewProp_Locations,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::NewProp_Rotation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::NewProp_Offset,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridSystem, nullptr, "UnmarkLocations", nullptr, nullptr, sizeof(LFPGridSystem_eventUnmarkLocations_Parms), Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridSystem_UpdateEvent_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Data_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Data;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_UpdateEvent_Statics::NewProp_Data_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_UpdateEvent_Statics::NewProp_Data = { "Data", nullptr, (EPropertyFlags)0x0010000008000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventUpdateEvent_Parms, Data), Z_Construct_UScriptStruct_FLGPGridSystemEvent, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_UpdateEvent_Statics::NewProp_Data_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_UpdateEvent_Statics::NewProp_Data_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridSystem_UpdateEvent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_UpdateEvent_Statics::NewProp_Data,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_UpdateEvent_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridSystem_UpdateEvent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridSystem, nullptr, "UpdateEvent", nullptr, nullptr, sizeof(LFPGridSystem_eventUpdateEvent_Parms), Z_Construct_UFunction_ULFPGridSystem_UpdateEvent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_UpdateEvent_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00224CC0, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_UpdateEvent_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_UpdateEvent_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridSystem_UpdateEvent()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridSystem_UpdateEvent_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ULFPGridSystem_WordlLocationToGridLocation_Statics
	{
		struct LFPGridSystem_eventWordlLocationToGridLocation_Parms
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
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_WordlLocationToGridLocation_Statics::NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_WordlLocationToGridLocation_Statics::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventWordlLocationToGridLocation_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_WordlLocationToGridLocation_Statics::NewProp_Location_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_WordlLocationToGridLocation_Statics::NewProp_Location_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULFPGridSystem_WordlLocationToGridLocation_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(LFPGridSystem_eventWordlLocationToGridLocation_Parms, ReturnValue), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULFPGridSystem_WordlLocationToGridLocation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_WordlLocationToGridLocation_Statics::NewProp_Location,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULFPGridSystem_WordlLocationToGridLocation_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ULFPGridSystem_WordlLocationToGridLocation_Statics::Function_MetaDataParams[] = {
		{ "Category", "LFPGridSystem" },
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ULFPGridSystem_WordlLocationToGridLocation_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULFPGridSystem, nullptr, "WordlLocationToGridLocation", nullptr, nullptr, sizeof(LFPGridSystem_eventWordlLocationToGridLocation_Parms), Z_Construct_UFunction_ULFPGridSystem_WordlLocationToGridLocation_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_WordlLocationToGridLocation_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54C20401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ULFPGridSystem_WordlLocationToGridLocation_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ULFPGridSystem_WordlLocationToGridLocation_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ULFPGridSystem_WordlLocationToGridLocation()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ULFPGridSystem_WordlLocationToGridLocation_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ULFPGridSystem_NoRegister()
	{
		return ULFPGridSystem::StaticClass();
	}
	struct Z_Construct_UClass_ULFPGridSystem_Statics
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
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_GridData_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GridData_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_GridData;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GridEvent_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_GridEvent;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_IsEventDirty_MetaData[];
#endif
		static void NewProp_IsEventDirty_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_IsEventDirty;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULFPGridSystem_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USceneComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ULFPGridSystem_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ULFPGridSystem_GetGridData, "GetGridData" }, // 4255532305
		{ &Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocation, "GetGridWorldLocation" }, // 3193985413
		{ &Z_Construct_UFunction_ULFPGridSystem_GetGridWorldLocationWithIndex, "GetGridWorldLocationWithIndex" }, // 1385035453
		{ &Z_Construct_UFunction_ULFPGridSystem_GetLocationData, "GetLocationData" }, // 3081736711
		{ &Z_Construct_UFunction_ULFPGridSystem_GridLocationToIndex, "GridLocationToIndex" }, // 1613141414
		{ &Z_Construct_UFunction_ULFPGridSystem_IndexToGridLocation, "IndexToGridLocation" }, // 801803888
		{ &Z_Construct_UFunction_ULFPGridSystem_IsLocationMarked, "IsLocationMarked" }, // 3524257873
		{ &Z_Construct_UFunction_ULFPGridSystem_IsLocationsMarked, "IsLocationsMarked" }, // 3564864521
		{ &Z_Construct_UFunction_ULFPGridSystem_IsLocationValid, "IsLocationValid" }, // 2159388669
		{ &Z_Construct_UFunction_ULFPGridSystem_MarkLocation, "MarkLocation" }, // 2107939844
		{ &Z_Construct_UFunction_ULFPGridSystem_MarkLocations, "MarkLocations" }, // 3929842548
		{ &Z_Construct_UFunction_ULFPGridSystem_TryFitTemplate, "TryFitTemplate" }, // 3500389390
		{ &Z_Construct_UFunction_ULFPGridSystem_TryFitTemplateNear, "TryFitTemplateNear" }, // 673480265
		{ &Z_Construct_UFunction_ULFPGridSystem_TryFitTemplates, "TryFitTemplates" }, // 2274225222
		{ &Z_Construct_UFunction_ULFPGridSystem_UnmarkLocation, "UnmarkLocation" }, // 3312285724
		{ &Z_Construct_UFunction_ULFPGridSystem_UnmarkLocations, "UnmarkLocations" }, // 3431962735
		{ &Z_Construct_UFunction_ULFPGridSystem_UpdateEvent, "UpdateEvent" }, // 3141150907
		{ &Z_Construct_UFunction_ULFPGridSystem_WordlLocationToGridLocation, "WordlLocationToGridLocation" }, // 3987125714
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPGridSystem_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "LFPGridSystem.h" },
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridSize_MetaData[] = {
		{ "Category", "LFPGridSystem | Variable" },
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridSize = { "GridSize", nullptr, (EPropertyFlags)0x0020080000000015, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPGridSystem, GridSize), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridSize_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridSize_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridGap_MetaData[] = {
		{ "Category", "LFPGridSystem | Variable" },
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridGap = { "GridGap", nullptr, (EPropertyFlags)0x0020080000000015, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPGridSystem, GridGap), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridGap_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridGap_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridType_MetaData[] = {
		{ "Category", "LFPGridSystem | Variable" },
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridType = { "GridType", nullptr, (EPropertyFlags)0x0020080000000015, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPGridSystem, GridType), Z_Construct_UEnum_LohFunctionPlugin_ELFPGridType, METADATA_PARAMS(Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridType_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridType_MetaData)) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridData_Inner = { "GridData", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridData_MetaData[] = {
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridData = { "GridData", nullptr, (EPropertyFlags)0x0020080000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPGridSystem, GridData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridData_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridData_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridEvent_MetaData[] = {
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridEvent = { "GridEvent", nullptr, (EPropertyFlags)0x0020080000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ULFPGridSystem, GridEvent), Z_Construct_UScriptStruct_FLGPGridSystemEvent, METADATA_PARAMS(Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridEvent_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridEvent_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_IsEventDirty_MetaData[] = {
		{ "ModuleRelativePath", "Public/LFPGridSystem.h" },
	};
#endif
	void Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_IsEventDirty_SetBit(void* Obj)
	{
		((ULFPGridSystem*)Obj)->IsEventDirty = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_IsEventDirty = { "IsEventDirty", nullptr, (EPropertyFlags)0x0020080000000000, UE4CodeGen_Private::EPropertyGenFlags::Bool , RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(uint8), sizeof(ULFPGridSystem), &Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_IsEventDirty_SetBit, METADATA_PARAMS(Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_IsEventDirty_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_IsEventDirty_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULFPGridSystem_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridSize,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridGap,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridType_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridData_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridData,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_GridEvent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULFPGridSystem_Statics::NewProp_IsEventDirty,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULFPGridSystem_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULFPGridSystem>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULFPGridSystem_Statics::ClassParams = {
		&ULFPGridSystem::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ULFPGridSystem_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ULFPGridSystem_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ULFPGridSystem_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULFPGridSystem_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULFPGridSystem()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULFPGridSystem_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULFPGridSystem, 1572416494);
	template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<ULFPGridSystem>()
	{
		return ULFPGridSystem::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULFPGridSystem(Z_Construct_UClass_ULFPGridSystem, &ULFPGridSystem::StaticClass, TEXT("/Script/LohFunctionPlugin"), TEXT("ULFPGridSystem"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULFPGridSystem);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
