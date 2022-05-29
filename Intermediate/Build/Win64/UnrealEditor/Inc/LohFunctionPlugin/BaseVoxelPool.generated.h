// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UBaseVoxelMesh;
struct FIntVector;
#ifdef LOHFUNCTIONPLUGIN_BaseVoxelPool_generated_h
#error "BaseVoxelPool.generated.h already included, missing '#pragma once' in BaseVoxelPool.h"
#endif
#define LOHFUNCTIONPLUGIN_BaseVoxelPool_generated_h

#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_16_SPARSE_DATA
#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_16_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execFreeAllMeshes); \
	DECLARE_FUNCTION(execReturnAllMeshes); \
	DECLARE_FUNCTION(execReturnMesh); \
	DECLARE_FUNCTION(execRequestMesh); \
	DECLARE_FUNCTION(execSetupVoxelPool);


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execFreeAllMeshes); \
	DECLARE_FUNCTION(execReturnAllMeshes); \
	DECLARE_FUNCTION(execReturnMesh); \
	DECLARE_FUNCTION(execRequestMesh); \
	DECLARE_FUNCTION(execSetupVoxelPool);


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBaseVoxelPool(); \
	friend struct Z_Construct_UClass_UBaseVoxelPool_Statics; \
public: \
	DECLARE_CLASS(UBaseVoxelPool, UObject, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(UBaseVoxelPool)


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_16_INCLASS \
private: \
	static void StaticRegisterNativesUBaseVoxelPool(); \
	friend struct Z_Construct_UClass_UBaseVoxelPool_Statics; \
public: \
	DECLARE_CLASS(UBaseVoxelPool, UObject, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/LohFunctionPlugin"), NO_API) \
	DECLARE_SERIALIZER(UBaseVoxelPool)


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_16_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBaseVoxelPool(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBaseVoxelPool) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBaseVoxelPool); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBaseVoxelPool); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBaseVoxelPool(UBaseVoxelPool&&); \
	NO_API UBaseVoxelPool(const UBaseVoxelPool&); \
public:


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_16_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBaseVoxelPool(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBaseVoxelPool(UBaseVoxelPool&&); \
	NO_API UBaseVoxelPool(const UBaseVoxelPool&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBaseVoxelPool); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBaseVoxelPool); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBaseVoxelPool)


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_13_PROLOG
#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_16_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_16_SPARSE_DATA \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_16_RPC_WRAPPERS \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_16_INCLASS \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_16_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_16_SPARSE_DATA \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_16_INCLASS_NO_PURE_DECLS \
	FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<class UBaseVoxelPool>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_BaseVoxelPool_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
