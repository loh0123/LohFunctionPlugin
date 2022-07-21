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

#include "Voxel/LFPBaseVoxelMeshComponent.h"


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

/**
 *
 */
class FLFPBaseVoxelMeshSceneProxy : public FPrimitiveSceneProxy
{
public:
	FLFPBaseVoxelMeshSceneProxy(ULFPBaseVoxelMeshComponent* Component) : FPrimitiveSceneProxy(Component), 
		VoxelComponent(Component), 
		MaterialRelevance(Component->GetMaterialRelevance(GetScene().GetFeatureLevel()))
	{
		FLFPVoxelMeshRenderBufferSet* Buffer = AllocateNewBuffer(0);

		Buffer->PositionVertexBuffer.Init(3);
		Buffer->ColorVertexBuffer.Init(3);
		Buffer->StaticMeshVertexBuffer.Init(3, 1);

		Buffer->IndexBuffer.Indices = { 0,1,2 };

		Buffer->PositionVertexBuffer.VertexPosition(0) = FVector3f(0, 0, 0);
		Buffer->PositionVertexBuffer.VertexPosition(1) = FVector3f(0, 100, 0);
		Buffer->PositionVertexBuffer.VertexPosition(2) = FVector3f(100, 0, 0);

		Buffer->StaticMeshVertexBuffer.SetVertexTangents(0, FVector3f(1, 0, 0), FVector3f(0, 1, 0), FVector3f(0, 0, 1));
		Buffer->StaticMeshVertexBuffer.SetVertexTangents(1, FVector3f(1, 0, 0), FVector3f(0, 1, 0), FVector3f(0, 0, 1));
		Buffer->StaticMeshVertexBuffer.SetVertexTangents(2, FVector3f(1, 0, 0), FVector3f(0, 1, 0), FVector3f(0, 0, 1));

		Buffer->StaticMeshVertexBuffer.SetVertexUV(0, 0, FVector2f(0, 0));
		Buffer->StaticMeshVertexBuffer.SetVertexUV(1, 0, FVector2f(0, 1));
		Buffer->StaticMeshVertexBuffer.SetVertexUV(2, 0, FVector2f(1, 0));

		ENQUEUE_RENDER_COMMAND(FLFPBaseVoxelMeshSceneProxy)(
			[Buffer](FRHICommandListImmediate& RHICmdList)
			{
				Buffer->Upload();
			});

		return;
	}

	virtual ~FLFPBaseVoxelMeshSceneProxy()
	{
		VoxelComponent = nullptr;

		for (FLFPVoxelMeshRenderBufferSet* Buffer : AllocatedBufferSets)
		{
			if (Buffer != nullptr)
			{
				Buffer->Release();

				delete Buffer;
			}
		}

		return;
	}

	FORCEINLINE FLFPVoxelMeshRenderBufferSet* AllocateNewBuffer(const int32 BufferID)
	{
		FLFPVoxelMeshRenderBufferSet* Buffer = new FLFPVoxelMeshRenderBufferSet(GetScene().GetFeatureLevel());

		if (AllocatedBufferSets.IsValidIndex(BufferID) == false)
		{
			AllocatedBufferSets.SetNum(BufferID + 1);
		}

		// Clean Up Existing Buffer
		if (AllocatedBufferSets[BufferID] != nullptr)
		{
			AllocatedBufferSets[BufferID]->Release();

			delete AllocatedBufferSets[BufferID];
		}

		// Set New Buffer To Array
		AllocatedBufferSets[BufferID] = Buffer;

		return Buffer;
	}

	virtual void GetDynamicMeshElements(
		const TArray<const FSceneView*>& Views,
		const FSceneViewFamily& ViewFamily,
		uint32 VisibilityMap,
		FMeshElementCollector& Collector) const override
	{
		const bool bWireframe = (AllowDebugViewmodes() && ViewFamily.EngineShowFlags.Wireframe);

		// set up wireframe material. Probably bad to reference GEngine here...also this material is very bad?
		FMaterialRenderProxy* WireframeMaterialProxy = nullptr;
		if (bWireframe)
		{
			FColoredMaterialRenderProxy* WireframeMaterialInstance = new FColoredMaterialRenderProxy(
				GEngine->WireframeMaterial ? GEngine->WireframeMaterial->GetRenderProxy() : nullptr,
				FLinearColor(0, 0.5f, 1.f)
			);
			Collector.RegisterOneFrameMaterialProxy(WireframeMaterialInstance);
			WireframeMaterialProxy = WireframeMaterialInstance;
		}

		ESceneDepthPriorityGroup DepthPriority = SDPG_World;

		for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++)
		{
			if (VisibilityMap & (1 << ViewIndex))
			{
				const FSceneView* View = Views[ViewIndex];

				bool bHasPrecomputedVolumetricLightmap;
				FMatrix PreviousLocalToWorld;
				int32 SingleCaptureIndex;
				bool bOutputVelocity;
				GetScene().GetPrimitiveUniformShaderParameters_RenderThread(GetPrimitiveSceneInfo(), bHasPrecomputedVolumetricLightmap, PreviousLocalToWorld, SingleCaptureIndex, bOutputVelocity);

				// Draw the mesh.
				for (FLFPVoxelMeshRenderBufferSet* BufferSet : AllocatedBufferSets)
				{
					if (BufferSet == nullptr)
					{
						continue;
					}

					UMaterialInterface* UseMaterial = BufferSet->Material;

					FMaterialRenderProxy* MaterialProxy = UseMaterial->GetRenderProxy();

					// do we need separate one of these for each MeshRenderBufferSet?
					FDynamicPrimitiveUniformBuffer& DynamicPrimitiveUniformBuffer = Collector.AllocateOneFrameResource<FDynamicPrimitiveUniformBuffer>();
					DynamicPrimitiveUniformBuffer.Set(GetLocalToWorld(), PreviousLocalToWorld, GetBounds(), GetLocalBounds(), GetLocalBounds(), true, bHasPrecomputedVolumetricLightmap, DrawsVelocity(), bOutputVelocity, GetCustomPrimitiveData());

					if (BufferSet->IndexBuffer.Indices.Num() > 0)
					{
						DrawBatch(Collector, *BufferSet, BufferSet->IndexBuffer, MaterialProxy, bWireframe, DepthPriority, ViewIndex, DynamicPrimitiveUniformBuffer);
					}
				}
			}
		}
	}

	virtual void DrawBatch(FMeshElementCollector& Collector,
		const FLFPVoxelMeshRenderBufferSet& RenderBuffers,
		const FDynamicMeshIndexBuffer32& IndexBuffer,
		FMaterialRenderProxy* UseMaterial,
		bool bWireframe,
		ESceneDepthPriorityGroup DepthPriority,
		int ViewIndex,
		FDynamicPrimitiveUniformBuffer& DynamicPrimitiveUniformBuffer) const
	{
		FMeshBatch& Mesh = Collector.AllocateMesh();
		FMeshBatchElement& BatchElement = Mesh.Elements[0];
		BatchElement.IndexBuffer = &IndexBuffer;
		Mesh.bWireframe = bWireframe;
		Mesh.VertexFactory = &RenderBuffers.VertexFactory;
		Mesh.MaterialRenderProxy = UseMaterial;

		BatchElement.PrimitiveUniformBufferResource = &DynamicPrimitiveUniformBuffer.UniformBuffer;

		BatchElement.FirstIndex = 0;
		BatchElement.NumPrimitives = IndexBuffer.Indices.Num() / 3;
		BatchElement.MinVertexIndex = 0;
		BatchElement.MaxVertexIndex = RenderBuffers.PositionVertexBuffer.GetNumVertices() - 1;
		Mesh.ReverseCulling = IsLocalToWorldDeterminantNegative();
		Mesh.Type = PT_TriangleList;
		Mesh.DepthPriorityGroup = DepthPriority;
		Mesh.bCanApplyViewModeOverrides = false;
		Collector.AddMesh(ViewIndex, Mesh);
	}

	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const
	{
		FPrimitiveViewRelevance Result;
		Result.bDrawRelevance = IsShown(View);
		Result.bShadowRelevance = IsShadowCast(View);
		Result.bDynamicRelevance = true;
		Result.bRenderInMainPass = ShouldRenderInMainPass();
		Result.bUsesLightingChannels = GetLightingChannelMask() != GetDefaultLightingChannelMask();
		Result.bRenderCustomDepth = ShouldRenderCustomDepth();
		Result.bTranslucentSelfShadow = bCastVolumetricTranslucentShadow;
		MaterialRelevance.SetPrimitiveViewRelevance(Result);
		Result.bVelocityRelevance = DrawsVelocity() && Result.bOpaque && Result.bRenderInMainPass;
		return Result;
	}

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

protected:

	ULFPBaseVoxelMeshComponent* VoxelComponent = nullptr;

	TArray<FLFPVoxelMeshRenderBufferSet*> AllocatedBufferSets;

	FMaterialRelevance MaterialRelevance;
};

class FLFPBaseVoxelMeshSceneProxyTask : public FNonAbandonableTask
{
	friend class FAutoDeleteAsyncTask<FLFPBaseVoxelMeshSceneProxyTask>;

public:

	FLFPBaseVoxelMeshSceneProxyTask() {}

	void DoWork();

	// This next section of code needs to be here. Not important as to why.

	FORCEINLINE TStatId GetStatId() const { RETURN_QUICK_DECLARE_CYCLE_STAT(FLFPBaseVoxelMeshSceneProxyTask, STATGROUP_ThreadPoolAsyncTasks); }
};
