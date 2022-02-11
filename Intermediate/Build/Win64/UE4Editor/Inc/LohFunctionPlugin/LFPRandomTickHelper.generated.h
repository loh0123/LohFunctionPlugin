// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
#ifdef LOHFUNCTIONPLUGIN_LFPRandomTickHelper_generated_h
#error "LFPRandomTickHelper.generated.h already included, missing '#pragma once' in LFPRandomTickHelper.h"
#endif
#define LOHFUNCTIONPLUGIN_LFPRandomTickHelper_generated_h

#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPRandomTickHelper_h_13_SPARSE_DATA
#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPRandomTickHelper_h_13_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execRemoveTickActor); \
	DECLARE_FUNCTION(execAddTickActor); \
	DECLARE_FUNCTION(execSendTick);


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPRandomTickHelper_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execRemoveTickActor); \
	DECLARE_FUNCTION(execAddTickActor); \
	DECLARE_FUNCTION(execSendTick);


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPRandomTickHelper_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULFPRandomTickHelper(); \
	friend struct Z_Construct_UClass_ULFPRandomTickHelper_Statics; \
public: \
	DECLARE_CLASS(ULFPRandomTickHelper, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(ULFPRandomTickHelper)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPRandomTickHelper_h_13_INCLASS \
private: \
	static void StaticRegisterNativesULFPRandomTickHelper(); \
	friend struct Z_Construct_UClass_ULFPRandomTickHelper_Statics; \
public: \
	DECLARE_CLASS(ULFPRandomTickHelper, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(ULFPRandomTickHelper)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPRandomTickHelper_h_13_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULFPRandomTickHelper(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULFPRandomTickHelper) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULFPRandomTickHelper); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULFPRandomTickHelper); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULFPRandomTickHelper(ULFPRandomTickHelper&&); \
	NO_API ULFPRandomTickHelper(const ULFPRandomTickHelper&); \
public:


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPRandomTickHelper_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULFPRandomTickHelper(ULFPRandomTickHelper&&); \
	NO_API ULFPRandomTickHelper(const ULFPRandomTickHelper&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULFPRandomTickHelper); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULFPRandomTickHelper); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULFPRandomTickHelper)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPRandomTickHelper_h_13_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__TickActorList() { return STRUCT_OFFSET(ULFPRandomTickHelper, TickActorList); }


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPRandomTickHelper_h_10_PROLOG
#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPRandomTickHelper_h_13_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPRandomTickHelper_h_13_PRIVATE_PROPERTY_OFFSET \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPRandomTickHelper_h_13_SPARSE_DATA \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPRandomTickHelper_h_13_RPC_WRAPPERS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPRandomTickHelper_h_13_INCLASS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPRandomTickHelper_h_13_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPRandomTickHelper_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPRandomTickHelper_h_13_PRIVATE_PROPERTY_OFFSET \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPRandomTickHelper_h_13_SPARSE_DATA \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPRandomTickHelper_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPRandomTickHelper_h_13_INCLASS_NO_PURE_DECLS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPRandomTickHelper_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<class ULFPRandomTickHelper>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPRandomTickHelper_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
