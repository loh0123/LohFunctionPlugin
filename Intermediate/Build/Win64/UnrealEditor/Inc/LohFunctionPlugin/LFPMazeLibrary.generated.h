// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLFPMazeTable;
enum class EMazeCellType : uint8;
struct FIntPoint;
struct FRandomStream;
struct FIntVector;
#ifdef LOHFUNCTIONPLUGIN_LFPMazeLibrary_generated_h
#error "LFPMazeLibrary.generated.h already included, missing '#pragma once' in LFPMazeLibrary.h"
#endif
#define LOHFUNCTIONPLUGIN_LFPMazeLibrary_generated_h

#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_21_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLFPMazeData_Statics; \
	LOHFUNCTIONPLUGIN_API static class UScriptStruct* StaticStruct();


template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<struct FLFPMazeData>();

#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_36_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLFPMazeStartData_Statics; \
	LOHFUNCTIONPLUGIN_API static class UScriptStruct* StaticStruct();


template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<struct FLFPMazeStartData>();

#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_58_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLFPMazeTable_Statics; \
	LOHFUNCTIONPLUGIN_API static class UScriptStruct* StaticStruct();


template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<struct FLFPMazeTable>();

#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_82_SPARSE_DATA
#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_82_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetMazeCellNeighbourByType); \
	DECLARE_FUNCTION(execSetMazeCellID); \
	DECLARE_FUNCTION(execSetMazeCellType); \
	DECLARE_FUNCTION(execGenerateMazeArea); \
	DECLARE_FUNCTION(execRemoveMazeDeadEnd); \
	DECLARE_FUNCTION(execGenerateMazeData); \
	DECLARE_FUNCTION(execCreateMazeStartData);


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_82_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetMazeCellNeighbourByType); \
	DECLARE_FUNCTION(execSetMazeCellID); \
	DECLARE_FUNCTION(execSetMazeCellType); \
	DECLARE_FUNCTION(execGenerateMazeArea); \
	DECLARE_FUNCTION(execRemoveMazeDeadEnd); \
	DECLARE_FUNCTION(execGenerateMazeData); \
	DECLARE_FUNCTION(execCreateMazeStartData);


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_82_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULFPMazeLibrary(); \
	friend struct Z_Construct_UClass_ULFPMazeLibrary_Statics; \
public: \
	DECLARE_CLASS(ULFPMazeLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(ULFPMazeLibrary)


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_82_INCLASS \
private: \
	static void StaticRegisterNativesULFPMazeLibrary(); \
	friend struct Z_Construct_UClass_ULFPMazeLibrary_Statics; \
public: \
	DECLARE_CLASS(ULFPMazeLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(ULFPMazeLibrary)


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_82_STANDARD_CONSTRUCTORS \
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


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_82_ENHANCED_CONSTRUCTORS \
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


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_79_PROLOG
#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_82_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_82_SPARSE_DATA \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_82_RPC_WRAPPERS \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_82_INCLASS \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_82_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_82_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_82_SPARSE_DATA \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_82_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_82_INCLASS_NO_PURE_DECLS \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h_82_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<class ULFPMazeLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Math_LFPMazeLibrary_h


#define FOREACH_ENUM_EMAZECELLTYPE(op) \
	op(EMazeCellType::Maze_Open) \
	op(EMazeCellType::Maze_Close) \
	op(EMazeCellType::Maze_Room) 

enum class EMazeCellType : uint8;
template<> LOHFUNCTIONPLUGIN_API UEnum* StaticEnum<EMazeCellType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
