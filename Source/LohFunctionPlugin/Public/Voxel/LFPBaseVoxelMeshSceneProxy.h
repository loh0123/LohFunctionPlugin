// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "PrimitiveSceneProxy.h"
#include "VertexFactory.h"
#include "LocalVertexFactory.h"
#include "PrimitiveViewRelevance.h"
#include "Rendering/StaticMeshVertexBuffer.h"
#include "Rendering/PositionVertexBuffer.h"
#include "Rendering/ColorVertexBuffer.h"
#include "DynamicMeshBuilder.h"
#include "Components/BaseDynamicMeshComponent.h"
#include "Materials/Material.h"
#include "RayTracingDefinitions.h"
#include "RayTracingInstance.h"
#include "Async/AsyncWork.h"

#include "Voxel/LFPBaseVoxelMeshComponent.h"


struct FRawBufferData
{
	/** Raw Vertex Generated For The Function */
	TArray<FVector3f> VertexList;

	/** Raw Triangle Index Generated For The Function */
	TArray<int32> TriangleIndexList;

	/** Raw Vertex Generated For The Function */
	TArray<FVector2f> UVList;

	/** Voxel Index For The Generated Vertex To Get Attribute Data */
	TArray<uint32> VoxelIndexList;

	/** How Many Triangle Has Been Generated */
	int32 TriangleCount = 0;
};

class FLFPVoxelMeshRenderBufferSet
{
public:

	FLFPVoxelMeshRenderBufferSet(ERHIFeatureLevel::Type InFeatureLevel)
		: VertexFactory(InFeatureLevel, "FLFPVoxelMeshRenderBufferSet")
		, Material(UMaterial::GetDefaultMaterial(MD_Surface))
	{
		StaticMeshVertexBuffer.SetUseFullPrecisionUVs(true);
		StaticMeshVertexBuffer.SetUseHighPrecisionTangentBasis(true);
	}

	FORCEINLINE void InitOrUpdateResource(FRenderResource* Resource)
	{
		if (!Resource->IsInitialized())
		{
			Resource->InitResource();
		}
		else
		{
			Resource->UpdateRHI();
		}
	}

	// This will upload mesh buffer data to gpu
	void Upload()
	{
		check(IsInRenderingThread());

		if (IndexBuffer.Indices.Num() == 0)
		{
			return;
		}

		InitOrUpdateResource(&this->IndexBuffer);

		InitOrUpdateResource(&this->PositionVertexBuffer);
		InitOrUpdateResource(&this->StaticMeshVertexBuffer);
		InitOrUpdateResource(&this->ColorVertexBuffer);

		FLocalVertexFactory::FDataType Data;

		this->PositionVertexBuffer.BindPositionVertexBuffer(&this->VertexFactory, Data);
		this->StaticMeshVertexBuffer.BindTangentVertexBuffer(&this->VertexFactory, Data);
		this->StaticMeshVertexBuffer.BindPackedTexCoordVertexBuffer(&this->VertexFactory, Data);
		//this->StaticMeshVertexBuffer.BindLightMapVertexBuffer(&this->VertexFactory, Data, 0);
		this->ColorVertexBuffer.BindColorVertexBuffer(&this->VertexFactory, Data);

		this->VertexFactory.SetData(Data);

		InitOrUpdateResource(&this->VertexFactory);

		//InvalidateRayTracingData();
		//ValidateRayTracingData();		// currently we are immediately validating. This may be revisited in future.
	}

	void Release()
	{
		PositionVertexBuffer.ReleaseResource();
		StaticMeshVertexBuffer.ReleaseResource();
		ColorVertexBuffer.ReleaseResource();
		IndexBuffer.ReleaseResource();
		VertexFactory.ReleaseResource();

		// todo : Ray Trace Clean Up

		Material = nullptr;

		return;
	}

public:

	/** The buffer containing vertex data. */
	FStaticMeshVertexBuffer StaticMeshVertexBuffer;

	/** The buffer containing the position vertex data. */
	FPositionVertexBuffer PositionVertexBuffer;

	/** The buffer containing the vertex color data. */
	FColorVertexBuffer ColorVertexBuffer;

	/** triangle indices */
	FDynamicMeshIndexBuffer32 IndexBuffer;

	/** vertex factory */
	FLocalVertexFactory VertexFactory;

	/** Material to draw this mesh with */
	UMaterialInterface* Material = nullptr;
};

class FLFPBaseVoxelMeshSceneProxyTask;

/**
 *
 */
class FLFPBaseVoxelMeshSceneProxy : public FPrimitiveSceneProxy
{
public:
	FLFPBaseVoxelMeshSceneProxy(ULFPBaseVoxelMeshComponent* Component, const int32 BufferCount);

	virtual ~FLFPBaseVoxelMeshSceneProxy();

	FORCEINLINE FLFPVoxelMeshRenderBufferSet* AllocateNewBuffer();

	FORCEINLINE void SetBufferSet(const int32 BufferID, FLFPVoxelMeshRenderBufferSet* Buffer, const int32 WorkVersion);

	virtual void GetDynamicMeshElements(
		const TArray<const FSceneView*>& Views,
		const FSceneViewFamily& ViewFamily,
		uint32 VisibilityMap,
		FMeshElementCollector& Collector) const override;

	virtual void DrawBatch(FMeshElementCollector& Collector,
		const FLFPVoxelMeshRenderBufferSet& RenderBuffers,
		const FDynamicMeshIndexBuffer32& IndexBuffer,
		FMaterialRenderProxy* UseMaterial,
		bool bWireframe,
		ESceneDepthPriorityGroup DepthPriority,
		int ViewIndex,
		FDynamicPrimitiveUniformBuffer& DynamicPrimitiveUniformBuffer) const;

	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const;

	virtual bool CanBeOccluded() const override
	{
		return !MaterialRelevance.bDisableDepthTest;
	}

	SIZE_T GetTypeHash() const override
	{
		static size_t UniquePointer;
		return reinterpret_cast<size_t>(&UniquePointer);
	}

	virtual uint32 GetMemoryFootprint(void) const override
	{
		return(sizeof(*this) + GetAllocatedSize());
	}

	uint32 GetAllocatedSize(void) const
	{
		return(FPrimitiveSceneProxy::GetAllocatedSize());
	}

	FORCEINLINE uint32 GetVersion() const
	{
		return Version;
	}

protected:

	ULFPBaseVoxelMeshComponent* VoxelComponent = nullptr;

	TArray<FLFPVoxelMeshRenderBufferSet*> AllocatedBufferSets;

	FMaterialRelevance MaterialRelevance;

	uint32 Version = 0;

	FCriticalSection AllocatedBufferSetsLock;
};

class FLFPBaseVoxelMeshSceneProxyTask : public FNonAbandonableTask
{
	friend class FAutoDeleteAsyncTask<FLFPBaseVoxelMeshSceneProxyTask>;

public:

	FLFPBaseVoxelMeshSceneProxyTask(FLFPBaseVoxelMeshSceneProxy* NewProxy, const uint32 NewBufferID) : Proxy(NewProxy), BufferID(NewBufferID), WorkVersion(NewProxy->GetVersion()) {}

	void DoWork();

	// This next section of code needs to be here. Not important as to why.

	FORCEINLINE TStatId GetStatId() const { RETURN_QUICK_DECLARE_CYCLE_STAT(FLFPBaseVoxelMeshSceneProxyTask, STATGROUP_ThreadPoolAsyncTasks); }

private:

	/** Raw Buffer Data To Store Generated Mesh Data */
	FRawBufferData RawBufferData;

	/** Proxy For Holding The Buffer */
	FLFPBaseVoxelMeshSceneProxy* Proxy;

	/** BufferID For Data To Submit */
	int32 BufferID = 0;

	/** Version Number To Check Is This Task Is Older */
	uint32 WorkVersion = 0;
};
