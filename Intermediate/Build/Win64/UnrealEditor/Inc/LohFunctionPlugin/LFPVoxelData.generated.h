// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLFPVoxelAttribute;
struct FIntVector;
#ifdef LOHFUNCTIONPLUGIN_LFPVoxelData_generated_h
#error "LFPVoxelData.generated.h already included, missing '#pragma once' in LFPVoxelData.h"
#endif
#define LOHFUNCTIONPLUGIN_LFPVoxelData_generated_h

#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_14_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLFPVoxelAttribute_Statics; \
	LOHFUNCTIONPLUGIN_API static class UScriptStruct* StaticStruct();


template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<struct FLFPVoxelAttribute>();

#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_42_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLFPVoxelChuckData_Statics; \
	LOHFUNCTIONPLUGIN_API static class UScriptStruct* StaticStruct();


template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<struct FLFPVoxelChuckData>();

#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_71_SPARSE_DATA
#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_71_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSetAllVoxelGridDataWithSingleData); \
	DECLARE_FUNCTION(execSetVoxelGridDataListWithSingleData); \
	DECLARE_FUNCTION(execSetVoxelGridDataList); \
	DECLARE_FUNCTION(execSetVoxelGridData); \
	DECLARE_FUNCTION(execIsChuckInitialized); \
	DECLARE_FUNCTION(execGetPoolAttribute); \
	DECLARE_FUNCTION(execSetupVoxelData); \
	DECLARE_FUNCTION(execMarkChuckForUpdate); \
	DECLARE_FUNCTION(execUpdateChuck);


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_71_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSetAllVoxelGridDataWithSingleData); \
	DECLARE_FUNCTION(execSetVoxelGridDataListWithSingleData); \
	DECLARE_FUNCTION(execSetVoxelGridDataList); \
	DECLARE_FUNCTION(execSetVoxelGridData); \
	DECLARE_FUNCTION(execIsChuckInitialized); \
	DECLARE_FUNCTION(execGetPoolAttribute); \
	DECLARE_FUNCTION(execSetupVoxelData); \
	DECLARE_FUNCTION(execMarkChuckForUpdate); \
	DECLARE_FUNCTION(execUpdateChuck);


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_71_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULFPVoxelData(); \
	friend struct Z_Construct_UClass_ULFPVoxelData_Statics; \
public: \
	DECLARE_CLASS(ULFPVoxelData, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(ULFPVoxelData)


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_71_INCLASS \
private: \
	static void StaticRegisterNativesULFPVoxelData(); \
	friend struct Z_Construct_UClass_ULFPVoxelData_Statics; \
public: \
	DECLARE_CLASS(ULFPVoxelData, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(ULFPVoxelData)


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_71_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULFPVoxelData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULFPVoxelData) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULFPVoxelData); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULFPVoxelData); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULFPVoxelData(ULFPVoxelData&&); \
	NO_API ULFPVoxelData(const ULFPVoxelData&); \
public:


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_71_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULFPVoxelData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULFPVoxelData(ULFPVoxelData&&); \
	NO_API ULFPVoxelData(const ULFPVoxelData&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULFPVoxelData); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULFPVoxelData); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULFPVoxelData)


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_68_PROLOG
#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_71_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_71_SPARSE_DATA \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_71_RPC_WRAPPERS \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_71_INCLASS \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_71_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_71_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_71_SPARSE_DATA \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_71_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_71_INCLASS_NO_PURE_DECLS \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h_71_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class LFPVoxelData."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<class ULFPVoxelData>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Container_LFPVoxelData_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
