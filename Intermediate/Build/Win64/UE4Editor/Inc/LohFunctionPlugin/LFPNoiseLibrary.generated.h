// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLFPNoiseTable;
struct FVector;
struct FLFPNoiseMixTable;
struct FIntVector;
struct FRandomStream;
#ifdef LOHFUNCTIONPLUGIN_LFPNoiseLibrary_generated_h
#error "LFPNoiseLibrary.generated.h already included, missing '#pragma once' in LFPNoiseLibrary.h"
#endif
#define LOHFUNCTIONPLUGIN_LFPNoiseLibrary_generated_h

#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_25_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLFPNoiseTable_Statics; \
	LOHFUNCTIONPLUGIN_API static class UScriptStruct* StaticStruct();


template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<struct FLFPNoiseTable>();

#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_13_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLFPNoiseMixTable_Statics; \
	LOHFUNCTIONPLUGIN_API static class UScriptStruct* StaticStruct();


template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<struct FLFPNoiseMixTable>();

#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_37_SPARSE_DATA
#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_37_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execMixLerpDirection); \
	DECLARE_FUNCTION(execMixLerpVector); \
	DECLARE_FUNCTION(execMixLerpNoise); \
	DECLARE_FUNCTION(execGetLerpDirectionNoise); \
	DECLARE_FUNCTION(execGetLerpVectorNoise); \
	DECLARE_FUNCTION(execGetLerpNoise); \
	DECLARE_FUNCTION(execGetDirectionNoise); \
	DECLARE_FUNCTION(execGetVectorNoise); \
	DECLARE_FUNCTION(execGetFloatNoise); \
	DECLARE_FUNCTION(execCreateNoiseTable);


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_37_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execMixLerpDirection); \
	DECLARE_FUNCTION(execMixLerpVector); \
	DECLARE_FUNCTION(execMixLerpNoise); \
	DECLARE_FUNCTION(execGetLerpDirectionNoise); \
	DECLARE_FUNCTION(execGetLerpVectorNoise); \
	DECLARE_FUNCTION(execGetLerpNoise); \
	DECLARE_FUNCTION(execGetDirectionNoise); \
	DECLARE_FUNCTION(execGetVectorNoise); \
	DECLARE_FUNCTION(execGetFloatNoise); \
	DECLARE_FUNCTION(execCreateNoiseTable);


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_37_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULFPNoiseLibrary(); \
	friend struct Z_Construct_UClass_ULFPNoiseLibrary_Statics; \
public: \
	DECLARE_CLASS(ULFPNoiseLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(ULFPNoiseLibrary)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_37_INCLASS \
private: \
	static void StaticRegisterNativesULFPNoiseLibrary(); \
	friend struct Z_Construct_UClass_ULFPNoiseLibrary_Statics; \
public: \
	DECLARE_CLASS(ULFPNoiseLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(ULFPNoiseLibrary)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_37_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULFPNoiseLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULFPNoiseLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULFPNoiseLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULFPNoiseLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULFPNoiseLibrary(ULFPNoiseLibrary&&); \
	NO_API ULFPNoiseLibrary(const ULFPNoiseLibrary&); \
public:


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_37_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULFPNoiseLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULFPNoiseLibrary(ULFPNoiseLibrary&&); \
	NO_API ULFPNoiseLibrary(const ULFPNoiseLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULFPNoiseLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULFPNoiseLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULFPNoiseLibrary)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_37_PRIVATE_PROPERTY_OFFSET
#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_34_PROLOG
#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_37_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_37_PRIVATE_PROPERTY_OFFSET \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_37_SPARSE_DATA \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_37_RPC_WRAPPERS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_37_INCLASS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_37_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_37_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_37_PRIVATE_PROPERTY_OFFSET \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_37_SPARSE_DATA \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_37_RPC_WRAPPERS_NO_PURE_DECLS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_37_INCLASS_NO_PURE_DECLS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h_37_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<class ULFPNoiseLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPNoiseLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
