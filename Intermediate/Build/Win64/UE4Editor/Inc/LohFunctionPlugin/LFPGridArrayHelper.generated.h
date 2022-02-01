// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FIntVector;
struct FRandomStream;
struct FVector;
struct FRotator;
#ifdef LOHFUNCTIONPLUGIN_LFPGridArrayHelper_generated_h
#error "LFPGridArrayHelper.generated.h already included, missing '#pragma once' in LFPGridArrayHelper.h"
#endif
#define LOHFUNCTIONPLUGIN_LFPGridArrayHelper_generated_h

#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridArrayHelper_h_22_SPARSE_DATA
#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridArrayHelper_h_22_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetAreaIndex); \
	DECLARE_FUNCTION(execRandomSectionGridIndex); \
	DECLARE_FUNCTION(execSectionGridIndex); \
	DECLARE_FUNCTION(execGetGridWorldLocationWithIndex); \
	DECLARE_FUNCTION(execGetGridWorldLocation); \
	DECLARE_FUNCTION(execIsWorldLocationValid); \
	DECLARE_FUNCTION(execIsLocationValid); \
	DECLARE_FUNCTION(execWordlLocationToGridLocation); \
	DECLARE_FUNCTION(execWordlLocationToIndex); \
	DECLARE_FUNCTION(execIndexsToGridLocation); \
	DECLARE_FUNCTION(execIndexToGridLocation); \
	DECLARE_FUNCTION(execGridLocationsToIndex); \
	DECLARE_FUNCTION(execGridLocationToIndex);


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridArrayHelper_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetAreaIndex); \
	DECLARE_FUNCTION(execRandomSectionGridIndex); \
	DECLARE_FUNCTION(execSectionGridIndex); \
	DECLARE_FUNCTION(execGetGridWorldLocationWithIndex); \
	DECLARE_FUNCTION(execGetGridWorldLocation); \
	DECLARE_FUNCTION(execIsWorldLocationValid); \
	DECLARE_FUNCTION(execIsLocationValid); \
	DECLARE_FUNCTION(execWordlLocationToGridLocation); \
	DECLARE_FUNCTION(execWordlLocationToIndex); \
	DECLARE_FUNCTION(execIndexsToGridLocation); \
	DECLARE_FUNCTION(execIndexToGridLocation); \
	DECLARE_FUNCTION(execGridLocationsToIndex); \
	DECLARE_FUNCTION(execGridLocationToIndex);


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridArrayHelper_h_22_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULFPGridArrayHelper(); \
	friend struct Z_Construct_UClass_ULFPGridArrayHelper_Statics; \
public: \
	DECLARE_CLASS(ULFPGridArrayHelper, USceneComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(ULFPGridArrayHelper)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridArrayHelper_h_22_INCLASS \
private: \
	static void StaticRegisterNativesULFPGridArrayHelper(); \
	friend struct Z_Construct_UClass_ULFPGridArrayHelper_Statics; \
public: \
	DECLARE_CLASS(ULFPGridArrayHelper, USceneComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(ULFPGridArrayHelper)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridArrayHelper_h_22_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULFPGridArrayHelper(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULFPGridArrayHelper) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULFPGridArrayHelper); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULFPGridArrayHelper); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULFPGridArrayHelper(ULFPGridArrayHelper&&); \
	NO_API ULFPGridArrayHelper(const ULFPGridArrayHelper&); \
public:


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridArrayHelper_h_22_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULFPGridArrayHelper(ULFPGridArrayHelper&&); \
	NO_API ULFPGridArrayHelper(const ULFPGridArrayHelper&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULFPGridArrayHelper); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULFPGridArrayHelper); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULFPGridArrayHelper)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridArrayHelper_h_22_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__GridArratSize() { return STRUCT_OFFSET(ULFPGridArrayHelper, GridArratSize); } \
	FORCEINLINE static uint32 __PPO__GridSize() { return STRUCT_OFFSET(ULFPGridArrayHelper, GridSize); } \
	FORCEINLINE static uint32 __PPO__GridGap() { return STRUCT_OFFSET(ULFPGridArrayHelper, GridGap); } \
	FORCEINLINE static uint32 __PPO__GridType() { return STRUCT_OFFSET(ULFPGridArrayHelper, GridType); }


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridArrayHelper_h_19_PROLOG
#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridArrayHelper_h_22_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridArrayHelper_h_22_PRIVATE_PROPERTY_OFFSET \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridArrayHelper_h_22_SPARSE_DATA \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridArrayHelper_h_22_RPC_WRAPPERS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridArrayHelper_h_22_INCLASS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridArrayHelper_h_22_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridArrayHelper_h_22_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridArrayHelper_h_22_PRIVATE_PROPERTY_OFFSET \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridArrayHelper_h_22_SPARSE_DATA \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridArrayHelper_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridArrayHelper_h_22_INCLASS_NO_PURE_DECLS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridArrayHelper_h_22_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<class ULFPGridArrayHelper>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridArrayHelper_h


#define FOREACH_ENUM_ELFPGRIDTYPE(op) \
	op(ELFPGridType::Rectangular) \
	op(ELFPGridType::Hexagon) \
	op(ELFPGridType::Triangle) 

enum class ELFPGridType : uint8;
template<> LOHFUNCTIONPLUGIN_API UEnum* StaticEnum<ELFPGridType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
