// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UBaseVoxelMesh;
#ifdef LOHFUNCTIONPLUGIN_BaseVoxelMesh_generated_h
#error "BaseVoxelMesh.generated.h already included, missing '#pragma once' in BaseVoxelMesh.h"
#endif
#define LOHFUNCTIONPLUGIN_BaseVoxelMesh_generated_h

#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_18_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLFPVoxelTriangleUpdateData_Statics; \
	LOHFUNCTIONPLUGIN_API static class UScriptStruct* StaticStruct();


template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<struct FLFPVoxelTriangleUpdateData>();

#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_32_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLFPVoxelGridData_Statics; \
	LOHFUNCTIONPLUGIN_API static class UScriptStruct* StaticStruct();


template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<struct FLFPVoxelGridData>();

#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_47_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLFPVoxelTriangleData_Statics; \
	LOHFUNCTIONPLUGIN_API static class UScriptStruct* StaticStruct();


template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<struct FLFPVoxelTriangleData>();

#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_56_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FLFPVoxelMeshData_Statics; \
	LOHFUNCTIONPLUGIN_API static class UScriptStruct* StaticStruct();


template<> LOHFUNCTIONPLUGIN_API UScriptStruct* StaticStruct<struct FLFPVoxelMeshData>();

#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_123_DELEGATE \
struct BaseVoxelMesh_eventOnVoxelBeginGenerator_Parms \
{ \
	UBaseVoxelMesh* VoxelMesh; \
}; \
static inline void FOnVoxelBeginGenerator_DelegateWrapper(const FMulticastScriptDelegate& OnVoxelBeginGenerator, UBaseVoxelMesh* VoxelMesh) \
{ \
	BaseVoxelMesh_eventOnVoxelBeginGenerator_Parms Parms; \
	Parms.VoxelMesh=VoxelMesh; \
	OnVoxelBeginGenerator.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_121_SPARSE_DATA
#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_121_RPC_WRAPPERS
#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_121_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_121_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBaseVoxelMesh(); \
	friend struct Z_Construct_UClass_UBaseVoxelMesh_Statics; \
public: \
	DECLARE_CLASS(UBaseVoxelMesh, UDynamicMesh, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(UBaseVoxelMesh)


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_121_INCLASS \
private: \
	static void StaticRegisterNativesUBaseVoxelMesh(); \
	friend struct Z_Construct_UClass_UBaseVoxelMesh_Statics; \
public: \
	DECLARE_CLASS(UBaseVoxelMesh, UDynamicMesh, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(UBaseVoxelMesh)


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_121_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBaseVoxelMesh(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBaseVoxelMesh) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBaseVoxelMesh); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBaseVoxelMesh); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBaseVoxelMesh(UBaseVoxelMesh&&); \
	NO_API UBaseVoxelMesh(const UBaseVoxelMesh&); \
public:


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_121_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBaseVoxelMesh(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBaseVoxelMesh(UBaseVoxelMesh&&); \
	NO_API UBaseVoxelMesh(const UBaseVoxelMesh&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBaseVoxelMesh); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBaseVoxelMesh); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBaseVoxelMesh)


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_118_PROLOG
#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_121_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_121_SPARSE_DATA \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_121_RPC_WRAPPERS \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_121_INCLASS \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_121_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_121_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_121_SPARSE_DATA \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_121_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_121_INCLASS_NO_PURE_DECLS \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h_121_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<class UBaseVoxelMesh>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelMesh_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
