// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FIntVector;
struct FLGPTerrainData;
struct FLGPTerrainSystemEvent;
struct FVector;
#ifdef LOHFUNCTIONPLUGIN_LFPTerrainSystem_generated_h
#error "LFPTerrainSystem.generated.h already included, missing '#pragma once' in LFPTerrainSystem.h"
#endif
#define LOHFUNCTIONPLUGIN_LFPTerrainSystem_generated_h

#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_39_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLGPTerrainSystemEvent_Statics; \
	LOHFUNCTIONPLUGIN_API static class UScriptStruct* StaticStruct();


template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<struct FLGPTerrainSystemEvent>();

#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_12_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLGPTerrainData_Statics; \
	LOHFUNCTIONPLUGIN_API static class UScriptStruct* StaticStruct();


template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<struct FLGPTerrainData>();

#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_54_DELEGATE \
struct _Script_LohFunctionPlugin_eventLFPTerrainRemoveEvent_Parms \
{ \
	TArray<FIntVector> RemoveList; \
}; \
static inline void FLFPTerrainRemoveEvent_DelegateWrapper(const FMulticastScriptDelegate& LFPTerrainRemoveEvent, TArray<FIntVector> const& RemoveList) \
{ \
	_Script_LohFunctionPlugin_eventLFPTerrainRemoveEvent_Parms Parms; \
	Parms.RemoveList=RemoveList; \
	LFPTerrainRemoveEvent.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_53_DELEGATE \
struct _Script_LohFunctionPlugin_eventLFPTerrainAddEvent_Parms \
{ \
	TArray<FLGPTerrainData> AddList; \
}; \
static inline void FLFPTerrainAddEvent_DelegateWrapper(const FMulticastScriptDelegate& LFPTerrainAddEvent, TArray<FLGPTerrainData> const& AddList) \
{ \
	_Script_LohFunctionPlugin_eventLFPTerrainAddEvent_Parms Parms; \
	Parms.AddList=AddList; \
	LFPTerrainAddEvent.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_SPARSE_DATA
#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_RPC_WRAPPERS \
	virtual void UpdateEvent_Implementation(FLGPTerrainSystemEvent const& Data); \
 \
	DECLARE_FUNCTION(execUpdateEvent); \
	DECLARE_FUNCTION(execGetTerrain); \
	DECLARE_FUNCTION(execRemoveTerrain); \
	DECLARE_FUNCTION(execAddTerrain); \
	DECLARE_FUNCTION(execIsTerrainLocationValid); \
	DECLARE_FUNCTION(execTerrainToWorldLocation); \
	DECLARE_FUNCTION(execWorldToTerrainLocation);


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execUpdateEvent); \
	DECLARE_FUNCTION(execGetTerrain); \
	DECLARE_FUNCTION(execRemoveTerrain); \
	DECLARE_FUNCTION(execAddTerrain); \
	DECLARE_FUNCTION(execIsTerrainLocationValid); \
	DECLARE_FUNCTION(execTerrainToWorldLocation); \
	DECLARE_FUNCTION(execWorldToTerrainLocation);


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_EVENT_PARMS \
	struct LFPTerrainSystem_eventUpdateEvent_Parms \
	{ \
		FLGPTerrainSystemEvent Data; \
	};


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_CALLBACK_WRAPPERS
#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULFPTerrainSystem(); \
	friend struct Z_Construct_UClass_ULFPTerrainSystem_Statics; \
public: \
	DECLARE_CLASS(ULFPTerrainSystem, USceneComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(ULFPTerrainSystem)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_INCLASS \
private: \
	static void StaticRegisterNativesULFPTerrainSystem(); \
	friend struct Z_Construct_UClass_ULFPTerrainSystem_Statics; \
public: \
	DECLARE_CLASS(ULFPTerrainSystem, USceneComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(ULFPTerrainSystem)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULFPTerrainSystem(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULFPTerrainSystem) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULFPTerrainSystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULFPTerrainSystem); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULFPTerrainSystem(ULFPTerrainSystem&&); \
	NO_API ULFPTerrainSystem(const ULFPTerrainSystem&); \
public:


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ULFPTerrainSystem(ULFPTerrainSystem&&); \
	NO_API ULFPTerrainSystem(const ULFPTerrainSystem&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULFPTerrainSystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULFPTerrainSystem); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULFPTerrainSystem)


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_PRIVATE_PROPERTY_OFFSET
#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_56_PROLOG \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_EVENT_PARMS


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_PRIVATE_PROPERTY_OFFSET \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_SPARSE_DATA \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_RPC_WRAPPERS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_CALLBACK_WRAPPERS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_INCLASS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_PRIVATE_PROPERTY_OFFSET \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_SPARSE_DATA \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_RPC_WRAPPERS_NO_PURE_DECLS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_CALLBACK_WRAPPERS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_INCLASS_NO_PURE_DECLS \
	PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h_59_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<class ULFPTerrainSystem>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID PluginLab_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Terrain_LFPTerrainSystem_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
