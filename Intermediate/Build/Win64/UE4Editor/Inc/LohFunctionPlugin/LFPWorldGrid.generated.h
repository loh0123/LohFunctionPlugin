// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FVector;
struct FRotator;
struct FIntVector;
#ifdef LOHFUNCTIONPLUGIN_LFPWorldGrid_generated_h
#error "LFPWorldGrid.generated.h already included, missing '#pragma once' in LFPWorldGrid.h"
#endif
#define LOHFUNCTIONPLUGIN_LFPWorldGrid_generated_h

#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPWorldGrid_h_23_SPARSE_DATA
#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPWorldGrid_h_23_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execIndexToWorldLocation); \
	DECLARE_FUNCTION(execGridLocationToWorldLocation); \
	DECLARE_FUNCTION(execIsWorldLocationValid); \
	DECLARE_FUNCTION(execWordlLocationToGridLocation); \
	DECLARE_FUNCTION(execWordlLocationToIndex);


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPWorldGrid_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execIndexToWorldLocation); \
	DECLARE_FUNCTION(execGridLocationToWorldLocation); \
	DECLARE_FUNCTION(execIsWorldLocationValid); \
	DECLARE_FUNCTION(execWordlLocationToGridLocation); \
	DECLARE_FUNCTION(execWordlLocationToIndex);


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPWorldGrid_h_23_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULFPWorldGrid(); \
	friend struct Z_Construct_UClass_ULFPWorldGrid_Statics; \
public: \
	DECLARE_CLASS(ULFPWorldGrid, USceneComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(ULFPWorldGrid)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPWorldGrid_h_23_INCLASS \
private: \
	static void StaticRegisterNativesULFPWorldGrid(); \
	friend struct Z_Construct_UClass_ULFPWorldGrid_Statics; \
public: \
	DECLARE_CLASS(ULFPWorldGrid, USceneComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(ULFPWorldGrid)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPWorldGrid_h_23_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULFPWorldGrid(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULFPWorldGrid) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULFPWorldGrid); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULFPWorldGrid); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULFPWorldGrid(ULFPWorldGrid&&); \
	NO_API ULFPWorldGrid(const ULFPWorldGrid&); \
public:


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPWorldGrid_h_23_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULFPWorldGrid(ULFPWorldGrid&&); \
	NO_API ULFPWorldGrid(const ULFPWorldGrid&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULFPWorldGrid); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULFPWorldGrid); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULFPWorldGrid)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPWorldGrid_h_23_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__GridSize() { return STRUCT_OFFSET(ULFPWorldGrid, GridSize); } \
	FORCEINLINE static uint32 __PPO__GridGap() { return STRUCT_OFFSET(ULFPWorldGrid, GridGap); } \
	FORCEINLINE static uint32 __PPO__GridType() { return STRUCT_OFFSET(ULFPWorldGrid, GridType); }


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPWorldGrid_h_20_PROLOG
#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPWorldGrid_h_23_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPWorldGrid_h_23_PRIVATE_PROPERTY_OFFSET \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPWorldGrid_h_23_SPARSE_DATA \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPWorldGrid_h_23_RPC_WRAPPERS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPWorldGrid_h_23_INCLASS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPWorldGrid_h_23_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPWorldGrid_h_23_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPWorldGrid_h_23_PRIVATE_PROPERTY_OFFSET \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPWorldGrid_h_23_SPARSE_DATA \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPWorldGrid_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPWorldGrid_h_23_INCLASS_NO_PURE_DECLS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPWorldGrid_h_23_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<class ULFPWorldGrid>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Helper_LFPWorldGrid_h


#define FOREACH_ENUM_ELFPGRIDTYPE(op) \
	op(ELFPGridType::Rectangular) \
	op(ELFPGridType::Hexagon) \
	op(ELFPGridType::Triangle) 

enum class ELFPGridType : uint8;
template<> LOHFUNCTIONPLUGIN_API UEnum* StaticEnum<ELFPGridType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
