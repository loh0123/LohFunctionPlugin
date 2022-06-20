// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LohFunctionPlugin/Public/Mesh/VoxelDynamicMeshComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeVoxelDynamicMeshComponent() {}
// Cross Module References
	LOHFUNCTIONPLUGIN_API UEnum* Z_Construct_UEnum_LohFunctionPlugin_EVoxelDynamicMeshComponentUpdateMode();
	UPackage* Z_Construct_UPackage__Script_LohFunctionPlugin();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_UVoxelDynamicMeshComponent_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_UVoxelDynamicMeshComponent();
	GEOMETRYFRAMEWORK_API UClass* Z_Construct_UClass_UBaseDynamicMeshComponent();
	ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
	LOHFUNCTIONPLUGIN_API UClass* Z_Construct_UClass_UBaseVoxelMesh_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UBodySetup_NoRegister();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EVoxelDynamicMeshComponentUpdateMode;
	static UEnum* EVoxelDynamicMeshComponentUpdateMode_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EVoxelDynamicMeshComponentUpdateMode.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EVoxelDynamicMeshComponentUpdateMode.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_LohFunctionPlugin_EVoxelDynamicMeshComponentUpdateMode, Z_Construct_UPackage__Script_LohFunctionPlugin(), TEXT("EVoxelDynamicMeshComponentUpdateMode"));
		}
		return Z_Registration_Info_UEnum_EVoxelDynamicMeshComponentUpdateMode.OuterSingleton;
	}
	template<> LOHFUNCTIONPLUGIN_API UEnum* StaticEnum<EVoxelDynamicMeshComponentUpdateMode>()
	{
		return EVoxelDynamicMeshComponentUpdateMode_StaticEnum();
	}
	struct Z_Construct_UEnum_LohFunctionPlugin_EVoxelDynamicMeshComponentUpdateMode_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_LohFunctionPlugin_EVoxelDynamicMeshComponentUpdateMode_Statics::Enumerators[] = {
		{ "EVoxelDynamicMeshComponentUpdateMode::NoUpdate", (int64)EVoxelDynamicMeshComponentUpdateMode::NoUpdate },
		{ "EVoxelDynamicMeshComponentUpdateMode::FastUpdate", (int64)EVoxelDynamicMeshComponentUpdateMode::FastUpdate },
		{ "EVoxelDynamicMeshComponentUpdateMode::SectionUpdate", (int64)EVoxelDynamicMeshComponentUpdateMode::SectionUpdate },
		{ "EVoxelDynamicMeshComponentUpdateMode::FullUpdate", (int64)EVoxelDynamicMeshComponentUpdateMode::FullUpdate },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_LohFunctionPlugin_EVoxelDynamicMeshComponentUpdateMode_Statics::Enum_MetaDataParams[] = {
		{ "FastUpdate.Comment", "// No Update Needed\n" },
		{ "FastUpdate.Name", "EVoxelDynamicMeshComponentUpdateMode::FastUpdate" },
		{ "FastUpdate.ToolTip", "No Update Needed" },
		{ "FullUpdate.Comment", "// Update Section Only\n" },
		{ "FullUpdate.Name", "EVoxelDynamicMeshComponentUpdateMode::FullUpdate" },
		{ "FullUpdate.ToolTip", "Update Section Only" },
		{ "ModuleRelativePath", "Public/Mesh/VoxelDynamicMeshComponent.h" },
		{ "NoUpdate.Name", "EVoxelDynamicMeshComponentUpdateMode::NoUpdate" },
		{ "SectionUpdate.Comment", "// Update Vertices Info Only\n" },
		{ "SectionUpdate.Name", "EVoxelDynamicMeshComponentUpdateMode::SectionUpdate" },
		{ "SectionUpdate.ToolTip", "Update Vertices Info Only" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_LohFunctionPlugin_EVoxelDynamicMeshComponentUpdateMode_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
		nullptr,
		"EVoxelDynamicMeshComponentUpdateMode",
		"EVoxelDynamicMeshComponentUpdateMode",
		Z_Construct_UEnum_LohFunctionPlugin_EVoxelDynamicMeshComponentUpdateMode_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_LohFunctionPlugin_EVoxelDynamicMeshComponentUpdateMode_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_LohFunctionPlugin_EVoxelDynamicMeshComponentUpdateMode_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_LohFunctionPlugin_EVoxelDynamicMeshComponentUpdateMode_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_LohFunctionPlugin_EVoxelDynamicMeshComponentUpdateMode()
	{
		if (!Z_Registration_Info_UEnum_EVoxelDynamicMeshComponentUpdateMode.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EVoxelDynamicMeshComponentUpdateMode.InnerSingleton, Z_Construct_UEnum_LohFunctionPlugin_EVoxelDynamicMeshComponentUpdateMode_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EVoxelDynamicMeshComponentUpdateMode.InnerSingleton;
	}
	DEFINE_FUNCTION(UVoxelDynamicMeshComponent::execGetVoxelSectionCount)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetVoxelSectionCount();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UVoxelDynamicMeshComponent::execSetVoxelMesh)
	{
		P_GET_OBJECT(UBaseVoxelMesh,Z_Param_NewVoxelMesh);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetVoxelMesh(Z_Param_NewVoxelMesh);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UVoxelDynamicMeshComponent::execConfigureMaterialSet)
	{
		P_GET_TARRAY_REF(UMaterialInterface*,Z_Param_Out_NewMaterialSet);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ConfigureMaterialSet(Z_Param_Out_NewMaterialSet);
		P_NATIVE_END;
	}
	void UVoxelDynamicMeshComponent::StaticRegisterNativesUVoxelDynamicMeshComponent()
	{
		UClass* Class = UVoxelDynamicMeshComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "ConfigureMaterialSet", &UVoxelDynamicMeshComponent::execConfigureMaterialSet },
			{ "GetVoxelSectionCount", &UVoxelDynamicMeshComponent::execGetVoxelSectionCount },
			{ "SetVoxelMesh", &UVoxelDynamicMeshComponent::execSetVoxelMesh },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UVoxelDynamicMeshComponent_ConfigureMaterialSet_Statics
	{
		struct VoxelDynamicMeshComponent_eventConfigureMaterialSet_Parms
		{
			TArray<UMaterialInterface*> NewMaterialSet;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_NewMaterialSet_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NewMaterialSet_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_NewMaterialSet;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UVoxelDynamicMeshComponent_ConfigureMaterialSet_Statics::NewProp_NewMaterialSet_Inner = { "NewMaterialSet", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UVoxelDynamicMeshComponent_ConfigureMaterialSet_Statics::NewProp_NewMaterialSet_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UVoxelDynamicMeshComponent_ConfigureMaterialSet_Statics::NewProp_NewMaterialSet = { "NewMaterialSet", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(VoxelDynamicMeshComponent_eventConfigureMaterialSet_Parms, NewMaterialSet), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_UVoxelDynamicMeshComponent_ConfigureMaterialSet_Statics::NewProp_NewMaterialSet_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UVoxelDynamicMeshComponent_ConfigureMaterialSet_Statics::NewProp_NewMaterialSet_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UVoxelDynamicMeshComponent_ConfigureMaterialSet_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVoxelDynamicMeshComponent_ConfigureMaterialSet_Statics::NewProp_NewMaterialSet_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVoxelDynamicMeshComponent_ConfigureMaterialSet_Statics::NewProp_NewMaterialSet,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UVoxelDynamicMeshComponent_ConfigureMaterialSet_Statics::Function_MetaDataParams[] = {
		{ "Category", "VoxelDynamicMeshComponent" },
		{ "ModuleRelativePath", "Public/Mesh/VoxelDynamicMeshComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UVoxelDynamicMeshComponent_ConfigureMaterialSet_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UVoxelDynamicMeshComponent, nullptr, "ConfigureMaterialSet", nullptr, nullptr, sizeof(Z_Construct_UFunction_UVoxelDynamicMeshComponent_ConfigureMaterialSet_Statics::VoxelDynamicMeshComponent_eventConfigureMaterialSet_Parms), Z_Construct_UFunction_UVoxelDynamicMeshComponent_ConfigureMaterialSet_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UVoxelDynamicMeshComponent_ConfigureMaterialSet_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UVoxelDynamicMeshComponent_ConfigureMaterialSet_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UVoxelDynamicMeshComponent_ConfigureMaterialSet_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UVoxelDynamicMeshComponent_ConfigureMaterialSet()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UVoxelDynamicMeshComponent_ConfigureMaterialSet_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UVoxelDynamicMeshComponent_GetVoxelSectionCount_Statics
	{
		struct VoxelDynamicMeshComponent_eventGetVoxelSectionCount_Parms
		{
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UVoxelDynamicMeshComponent_GetVoxelSectionCount_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(VoxelDynamicMeshComponent_eventGetVoxelSectionCount_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UVoxelDynamicMeshComponent_GetVoxelSectionCount_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVoxelDynamicMeshComponent_GetVoxelSectionCount_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UVoxelDynamicMeshComponent_GetVoxelSectionCount_Statics::Function_MetaDataParams[] = {
		{ "Category", "VoxelDynamicMeshComponent" },
		{ "ModuleRelativePath", "Public/Mesh/VoxelDynamicMeshComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UVoxelDynamicMeshComponent_GetVoxelSectionCount_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UVoxelDynamicMeshComponent, nullptr, "GetVoxelSectionCount", nullptr, nullptr, sizeof(Z_Construct_UFunction_UVoxelDynamicMeshComponent_GetVoxelSectionCount_Statics::VoxelDynamicMeshComponent_eventGetVoxelSectionCount_Parms), Z_Construct_UFunction_UVoxelDynamicMeshComponent_GetVoxelSectionCount_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UVoxelDynamicMeshComponent_GetVoxelSectionCount_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UVoxelDynamicMeshComponent_GetVoxelSectionCount_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UVoxelDynamicMeshComponent_GetVoxelSectionCount_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UVoxelDynamicMeshComponent_GetVoxelSectionCount()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UVoxelDynamicMeshComponent_GetVoxelSectionCount_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UVoxelDynamicMeshComponent_SetVoxelMesh_Statics
	{
		struct VoxelDynamicMeshComponent_eventSetVoxelMesh_Parms
		{
			UBaseVoxelMesh* NewVoxelMesh;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_NewVoxelMesh;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UVoxelDynamicMeshComponent_SetVoxelMesh_Statics::NewProp_NewVoxelMesh = { "NewVoxelMesh", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(VoxelDynamicMeshComponent_eventSetVoxelMesh_Parms, NewVoxelMesh), Z_Construct_UClass_UBaseVoxelMesh_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UVoxelDynamicMeshComponent_SetVoxelMesh_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVoxelDynamicMeshComponent_SetVoxelMesh_Statics::NewProp_NewVoxelMesh,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UVoxelDynamicMeshComponent_SetVoxelMesh_Statics::Function_MetaDataParams[] = {
		{ "Category", "VoxelDynamicMeshComponent" },
		{ "ModuleRelativePath", "Public/Mesh/VoxelDynamicMeshComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UVoxelDynamicMeshComponent_SetVoxelMesh_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UVoxelDynamicMeshComponent, nullptr, "SetVoxelMesh", nullptr, nullptr, sizeof(Z_Construct_UFunction_UVoxelDynamicMeshComponent_SetVoxelMesh_Statics::VoxelDynamicMeshComponent_eventSetVoxelMesh_Parms), Z_Construct_UFunction_UVoxelDynamicMeshComponent_SetVoxelMesh_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UVoxelDynamicMeshComponent_SetVoxelMesh_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UVoxelDynamicMeshComponent_SetVoxelMesh_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UVoxelDynamicMeshComponent_SetVoxelMesh_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UVoxelDynamicMeshComponent_SetVoxelMesh()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UVoxelDynamicMeshComponent_SetVoxelMesh_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UVoxelDynamicMeshComponent);
	UClass* Z_Construct_UClass_UVoxelDynamicMeshComponent_NoRegister()
	{
		return UVoxelDynamicMeshComponent::StaticClass();
	}
	struct Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MeshBodySetup_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_MeshBodySetup;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VoxelMeshObject_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_VoxelMeshObject;
		static const UECodeGen_Private::FIntPropertyParams NewProp_DirtySectionIndexList_ElementProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DirtySectionIndexList_MetaData[];
#endif
		static const UECodeGen_Private::FSetPropertyParams NewProp_DirtySectionIndexList;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBaseDynamicMeshComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_LohFunctionPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UVoxelDynamicMeshComponent_ConfigureMaterialSet, "ConfigureMaterialSet" }, // 647109098
		{ &Z_Construct_UFunction_UVoxelDynamicMeshComponent_GetVoxelSectionCount, "GetVoxelSectionCount" }, // 1416129315
		{ &Z_Construct_UFunction_UVoxelDynamicMeshComponent_SetVoxelMesh, "SetVoxelMesh" }, // 176562793
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Rendering" },
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "LOD LOD Mobility Trigger" },
		{ "IncludePath", "Mesh/VoxelDynamicMeshComponent.h" },
		{ "ModuleRelativePath", "Public/Mesh/VoxelDynamicMeshComponent.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::NewProp_MeshBodySetup_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Mesh/VoxelDynamicMeshComponent.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::NewProp_MeshBodySetup = { "MeshBodySetup", nullptr, (EPropertyFlags)0x0026080000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UVoxelDynamicMeshComponent, MeshBodySetup), Z_Construct_UClass_UBodySetup_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::NewProp_MeshBodySetup_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::NewProp_MeshBodySetup_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::NewProp_VoxelMeshObject_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Mesh/VoxelDynamicMeshComponent.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::NewProp_VoxelMeshObject = { "VoxelMeshObject", nullptr, (EPropertyFlags)0x0026080000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UVoxelDynamicMeshComponent, VoxelMeshObject), Z_Construct_UClass_UBaseVoxelMesh_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::NewProp_VoxelMeshObject_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::NewProp_VoxelMeshObject_MetaData)) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::NewProp_DirtySectionIndexList_ElementProp = { "DirtySectionIndexList", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::NewProp_DirtySectionIndexList_MetaData[] = {
		{ "ModuleRelativePath", "Public/Mesh/VoxelDynamicMeshComponent.h" },
	};
#endif
	const UECodeGen_Private::FSetPropertyParams Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::NewProp_DirtySectionIndexList = { "DirtySectionIndexList", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Set, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UVoxelDynamicMeshComponent, DirtySectionIndexList), METADATA_PARAMS(Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::NewProp_DirtySectionIndexList_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::NewProp_DirtySectionIndexList_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::NewProp_MeshBodySetup,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::NewProp_VoxelMeshObject,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::NewProp_DirtySectionIndexList_ElementProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::NewProp_DirtySectionIndexList,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UVoxelDynamicMeshComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::ClassParams = {
		&UVoxelDynamicMeshComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UVoxelDynamicMeshComponent()
	{
		if (!Z_Registration_Info_UClass_UVoxelDynamicMeshComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UVoxelDynamicMeshComponent.OuterSingleton, Z_Construct_UClass_UVoxelDynamicMeshComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UVoxelDynamicMeshComponent.OuterSingleton;
	}
	template<> LOHFUNCTIONPLUGIN_API UClass* StaticClass<UVoxelDynamicMeshComponent>()
	{
		return UVoxelDynamicMeshComponent::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UVoxelDynamicMeshComponent);
	struct Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_VoxelDynamicMeshComponent_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_VoxelDynamicMeshComponent_h_Statics::EnumInfo[] = {
		{ EVoxelDynamicMeshComponentUpdateMode_StaticEnum, TEXT("EVoxelDynamicMeshComponentUpdateMode"), &Z_Registration_Info_UEnum_EVoxelDynamicMeshComponentUpdateMode, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 4067951U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_VoxelDynamicMeshComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UVoxelDynamicMeshComponent, UVoxelDynamicMeshComponent::StaticClass, TEXT("UVoxelDynamicMeshComponent"), &Z_Registration_Info_UClass_UVoxelDynamicMeshComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UVoxelDynamicMeshComponent), 2052054859U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_VoxelDynamicMeshComponent_h_1277168538(TEXT("/Script/LohFunctionPlugin"),
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_VoxelDynamicMeshComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_VoxelDynamicMeshComponent_h_Statics::ClassInfo),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_VoxelDynamicMeshComponent_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginLab5_Plugins_LohFunctionPlugin_Source_LohFunctionPlugin_Public_Mesh_VoxelDynamicMeshComponent_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
