// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Mesh/BaseVoxelMesh.h"
#include "Components/BaseDynamicMeshComponent.h"
#include "VoxelDynamicMeshComponent.generated.h"

class FVoxelDynamicMeshSceneProxy;

UENUM()
enum class EVoxelDynamicMeshComponentUpdateMode
{
	NoUpdate = 0, // No Update Needed

	FastUpdate = 1, // Update Vertices Info Only

	FullUpdate = 2 // Reset Proxy And Update Every thing
};

/**
 * 
 */
UCLASS(hidecategories = (LOD), meta = (BlueprintSpawnableComponent), ClassGroup = Rendering)
class LOHFUNCTIONPLUGIN_API UVoxelDynamicMeshComponent : public UBaseDynamicMeshComponent
{
	GENERATED_UCLASS_BODY()

public: // Base Dynamic Mesh Function Interface

	virtual FDynamicMesh3* GetMesh() override { return VoxelMeshObject->GetMeshPtr(); }

	virtual const FDynamicMesh3* GetMesh() const override { return VoxelMeshObject->GetMeshPtr(); }
	
	virtual UDynamicMesh* GetDynamicMesh() override { return VoxelMeshObject; }

	virtual void SetMesh(UE::Geometry::FDynamicMesh3&& MoveMesh) override { VoxelMeshObject->SetMesh(MoveTemp(MoveMesh)); }

	virtual void ApplyTransform(const FTransform3d& Transform, bool bInvert) override;

public: // Mesh Data Change Function

	//virtual void ApplyChange(const FMeshVertexChange* Change, bool bRevert) override { VoxelMeshObject->ApplyChange(Change, bRevert); }

	//virtual void ApplyChange(const FMeshChange* Change, bool bRevert) override { VoxelMeshObject->ApplyChange(Change, bRevert); }

	//virtual void ApplyChange(const FMeshReplacementChange* Change, bool bRevert) override { VoxelMeshObject->ApplyChange(Change, bRevert); }

	void OnMeshObjectChanged(UDynamicMesh* ChangedMeshObject, FDynamicMeshChangeInfo ChangeInfo);

public:

	//virtual void NotifyMaterialSetUpdated();

	virtual void NotifyMeshUpdated() override { ResetProxy(); }

	//void FastNotifyUpdated();

public:

	UFUNCTION(BlueprintCallable, Category = "VoxelDynamicMeshComponent")
		void ConfigureMaterialSet(const TArray<UMaterialInterface*>& NewMaterialSet);

	UFUNCTION(BlueprintCallable, Category = "VoxelDynamicMeshComponent")
		void SetVoxelMesh(UBaseVoxelMesh* NewVoxelMesh);

	UFUNCTION(BlueprintCallable, Category = "VoxelDynamicMeshComponent")
		int32 GetVoxelSectionCount() const { return VoxelMeshObject->GetVoxelSectionCount(); };

public:

	virtual void InvalidateAutoCalculatedTangents();

	const UE::Geometry::FMeshTangentsf* GetAutoCalculatedTangents();

protected:

	/** true if AutoCalculatedTangents has been computed for current mesh */
	bool bAutoCalculatedTangentsValid = false;

	/** Set of per-triangle-vertex tangents computed for the current mesh. Only valid if bAutoCalculatedTangentsValid == true */
	UE::Geometry::FMeshTangentsf AutoCalculatedTangents;

	void UpdateAutoCalculatedTangents();

public:

	virtual FDynamicMesh3* GetRenderMesh() { return GetMesh(); }

	virtual const FDynamicMesh3* GetRenderMesh() const { return GetMesh(); }

protected:

	virtual FBaseDynamicMeshSceneProxy* GetBaseSceneProxy() override { return (FBaseDynamicMeshSceneProxy*)GetCurrentSceneProxy(); }

	FVoxelDynamicMeshSceneProxy* GetCurrentSceneProxy() { return (bProxyValid ? (FVoxelDynamicMeshSceneProxy*)SceneProxy : nullptr); }

	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;

	void ResetProxy();

protected:

	void UpdateLocalBounds();

	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;

protected: // Object Load Interface

	virtual void PostLoad() override;

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override; // ToDo : Physic
#endif

protected:

	UE::Geometry::FAxisAlignedBox3d LocalBounds; // Voxel Visible Bound

	bool bProxyValid = false;

	FDelegateHandle MeshObjectChangedHandle;

protected:

	UPROPERTY(Instanced) TObjectPtr<UBodySetup> MeshBodySetup;

	UPROPERTY(Instanced) TObjectPtr<UBaseVoxelMesh> VoxelMeshObject;
	
};
