// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLFPMazeTable;
struct FRandomStream;
struct FIntVector;
#ifdef LOHFUNCTIONPLUGIN_LFPMazeLibrary_generated_h
#error "LFPMazeLibrary.generated.h already included, missing '#pragma once' in LFPMazeLibrary.h"
#endif
#define LOHFUNCTIONPLUGIN_LFPMazeLibrary_generated_h

#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_59_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLFPMazeTable_Statics; \
	LOHFUNCTIONPLUGIN_API static class UScriptStruct* StaticStruct();


template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<struct FLFPMazeTable>();

#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_50_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLFPMazeArea_Statics; \
	LOHFUNCTIONPLUGIN_API static class UScriptStruct* StaticStruct();


template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<struct FLFPMazeArea>();

#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_31_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLFPMazeStartData_Statics; \
	LOHFUNCTIONPLUGIN_API static class UScriptStruct* StaticStruct();


template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<struct FLFPMazeStartData>();

#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_13_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLFPMazeData_Statics; \
	LOHFUNCTIONPLUGIN_API static class UScriptStruct* StaticStruct();


template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<struct FLFPMazeData>();

#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_80_SPARSE_DATA
#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_80_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGenerateMazeArea); \
	DECLARE_FUNCTION(execRemoveMazeDeadEnd); \
	DECLARE_FUNCTION(execGenerateMazeData); \
	DECLARE_FUNCTION(execCreateMazeStartData);


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_80_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGenerateMazeArea); \
	DECLARE_FUNCTION(execRemoveMazeDeadEnd); \
	DECLARE_FUNCTION(execGenerateMazeData); \
	DECLARE_FUNCTION(execCreateMazeStartData);


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_80_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULFPMazeLibrary(); \
	friend struct Z_Construct_UClass_ULFPMazeLibrary_Statics; \
public: \
	DECLARE_CLASS(ULFPMazeLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(ULFPMazeLibrary)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_80_INCLASS \
private: \
	static void StaticRegisterNativesULFPMazeLibrary(); \
	friend struct Z_Construct_UClass_ULFPMazeLibrary_Statics; \
public: \
	DECLARE_CLASS(ULFPMazeLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(ULFPMazeLibrary)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_80_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULFPMazeLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULFPMazeLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULFPMazeLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULFPMazeLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULFPMazeLibrary(ULFPMazeLibrary&&); \
	NO_API ULFPMazeLibrary(const ULFPMazeLibrary&); \
public:


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_80_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULFPMazeLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULFPMazeLibrary(ULFPMazeLibrary&&); \
	NO_API ULFPMazeLibrary(const ULFPMazeLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULFPMazeLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULFPMazeLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULFPMazeLibrary)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_80_PRIVATE_PROPERTY_OFFSET
#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_77_PROLOG
#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_80_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_80_PRIVATE_PROPERTY_OFFSET \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_80_SPARSE_DATA \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_80_RPC_WRAPPERS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_80_INCLASS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_80_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_80_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_80_PRIVATE_PROPERTY_OFFSET \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_80_SPARSE_DATA \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_80_RPC_WRAPPERS_NO_PURE_DECLS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_80_INCLASS_NO_PURE_DECLS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_80_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<class ULFPMazeLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
