// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
#ifdef LOHFUNCTIONPLUGIN_LFPTickManager_generated_h
#error "LFPTickManager.generated.h already included, missing '#pragma once' in LFPTickManager.h"
#endif
#define LOHFUNCTIONPLUGIN_LFPTickManager_generated_h

#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPTickManager_h_14_SPARSE_DATA
#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPTickManager_h_14_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSendTickInternal); \
	DECLARE_FUNCTION(execRemoveTickActor); \
	DECLARE_FUNCTION(execAddTickActor); \
	DECLARE_FUNCTION(execSendTick);


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPTickManager_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSendTickInternal); \
	DECLARE_FUNCTION(execRemoveTickActor); \
	DECLARE_FUNCTION(execAddTickActor); \
	DECLARE_FUNCTION(execSendTick);


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPTickManager_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULFPTickManager(); \
	friend struct Z_Construct_UClass_ULFPTickManager_Statics; \
public: \
	DECLARE_CLASS(ULFPTickManager, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(ULFPTickManager)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPTickManager_h_14_INCLASS \
private: \
	static void StaticRegisterNativesULFPTickManager(); \
	friend struct Z_Construct_UClass_ULFPTickManager_Statics; \
public: \
	DECLARE_CLASS(ULFPTickManager, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(ULFPTickManager)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPTickManager_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULFPTickManager(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULFPTickManager) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULFPTickManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULFPTickManager); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULFPTickManager(ULFPTickManager&&); \
	NO_API ULFPTickManager(const ULFPTickManager&); \
public:


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPTickManager_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULFPTickManager(ULFPTickManager&&); \
	NO_API ULFPTickManager(const ULFPTickManager&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULFPTickManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULFPTickManager); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULFPTickManager)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPTickManager_h_14_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__TickActorList() { return STRUCT_OFFSET(ULFPTickManager, TickActorList); }


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPTickManager_h_11_PROLOG
#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPTickManager_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPTickManager_h_14_PRIVATE_PROPERTY_OFFSET \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPTickManager_h_14_SPARSE_DATA \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPTickManager_h_14_RPC_WRAPPERS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPTickManager_h_14_INCLASS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPTickManager_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPTickManager_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPTickManager_h_14_PRIVATE_PROPERTY_OFFSET \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPTickManager_h_14_SPARSE_DATA \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPTickManager_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPTickManager_h_14_INCLASS_NO_PURE_DECLS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPTickManager_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<class ULFPTickManager>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPTickManager_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS