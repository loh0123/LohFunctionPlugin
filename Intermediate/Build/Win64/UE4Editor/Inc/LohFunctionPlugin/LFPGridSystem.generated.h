// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLGPGridSystemEvent;
struct FVector;
struct FRotator;
struct FIntVector;
#ifdef LOHFUNCTIONPLUGIN_LFPGridSystem_generated_h
#error "LFPGridSystem.generated.h already included, missing '#pragma once' in LFPGridSystem.h"
#endif
#define LOHFUNCTIONPLUGIN_LFPGridSystem_generated_h

#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_22_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLGPGridSystemEvent_Statics; \
	LOHFUNCTIONPLUGIN_API static class UScriptStruct* StaticStruct();


template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<struct FLGPGridSystemEvent>();

#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_SPARSE_DATA
#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_RPC_WRAPPERS \
	virtual void UpdateEvent_Implementation(FLGPGridSystemEvent const& Data); \
 \
	DECLARE_FUNCTION(execUpdateEvent); \
	DECLARE_FUNCTION(execGetGridWorldLocationWithIndex); \
	DECLARE_FUNCTION(execGetGridWorldLocation); \
	DECLARE_FUNCTION(execGetLocationData); \
	DECLARE_FUNCTION(execGetGridData); \
	DECLARE_FUNCTION(execUnmarkLocations); \
	DECLARE_FUNCTION(execUnmarkLocation); \
	DECLARE_FUNCTION(execMarkLocations); \
	DECLARE_FUNCTION(execMarkLocation); \
	DECLARE_FUNCTION(execIsLocationsMarked); \
	DECLARE_FUNCTION(execIsLocationMarked); \
	DECLARE_FUNCTION(execIsLocationValid);


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execUpdateEvent); \
	DECLARE_FUNCTION(execGetGridWorldLocationWithIndex); \
	DECLARE_FUNCTION(execGetGridWorldLocation); \
	DECLARE_FUNCTION(execGetLocationData); \
	DECLARE_FUNCTION(execGetGridData); \
	DECLARE_FUNCTION(execUnmarkLocations); \
	DECLARE_FUNCTION(execUnmarkLocation); \
	DECLARE_FUNCTION(execMarkLocations); \
	DECLARE_FUNCTION(execMarkLocation); \
	DECLARE_FUNCTION(execIsLocationsMarked); \
	DECLARE_FUNCTION(execIsLocationMarked); \
	DECLARE_FUNCTION(execIsLocationValid);


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_EVENT_PARMS \
	struct LFPGridSystem_eventUpdateEvent_Parms \
	{ \
		FLGPGridSystemEvent Data; \
	};


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_CALLBACK_WRAPPERS
#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULFPGridSystem(); \
	friend struct Z_Construct_UClass_ULFPGridSystem_Statics; \
public: \
	DECLARE_CLASS(ULFPGridSystem, USceneComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(ULFPGridSystem)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_INCLASS \
private: \
	static void StaticRegisterNativesULFPGridSystem(); \
	friend struct Z_Construct_UClass_ULFPGridSystem_Statics; \
public: \
	DECLARE_CLASS(ULFPGridSystem, USceneComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(ULFPGridSystem)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULFPGridSystem(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULFPGridSystem) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULFPGridSystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULFPGridSystem); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULFPGridSystem(ULFPGridSystem&&); \
	NO_API ULFPGridSystem(const ULFPGridSystem&); \
public:


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULFPGridSystem(ULFPGridSystem&&); \
	NO_API ULFPGridSystem(const ULFPGridSystem&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULFPGridSystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULFPGridSystem); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULFPGridSystem)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__GridSize() { return STRUCT_OFFSET(ULFPGridSystem, GridSize); } \
	FORCEINLINE static uint32 __PPO__GridGap() { return STRUCT_OFFSET(ULFPGridSystem, GridGap); } \
	FORCEINLINE static uint32 __PPO__GridType() { return STRUCT_OFFSET(ULFPGridSystem, GridType); } \
	FORCEINLINE static uint32 __PPO__GridData() { return STRUCT_OFFSET(ULFPGridSystem, GridData); } \
	FORCEINLINE static uint32 __PPO__GridEvent() { return STRUCT_OFFSET(ULFPGridSystem, GridEvent); }


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_39_PROLOG \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_EVENT_PARMS


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_PRIVATE_PROPERTY_OFFSET \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_SPARSE_DATA \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_RPC_WRAPPERS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_CALLBACK_WRAPPERS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_INCLASS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_PRIVATE_PROPERTY_OFFSET \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_SPARSE_DATA \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_RPC_WRAPPERS_NO_PURE_DECLS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_CALLBACK_WRAPPERS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_INCLASS_NO_PURE_DECLS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h_42_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<class ULFPGridSystem>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_LFPGridSystem_h


#define FOREACH_ENUM_ELFPGRIDTYPE(op) \
	op(ELFPGridType::Rectangular) \
	op(ELFPGridType::Hexagon) \
	op(ELFPGridType::Triangle) 

enum class ELFPGridType : uint8;
template<> LOHFUNCTIONPLUGIN_API UEnum* StaticEnum<ELFPGridType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
