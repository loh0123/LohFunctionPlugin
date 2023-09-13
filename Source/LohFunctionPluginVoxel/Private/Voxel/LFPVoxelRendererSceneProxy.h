// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#pragma once

#include "CoreMinimal.h"
#include "MaterialDomain.h"
#include "PrimitiveSceneProxy.h"
#include "LocalVertexFactory.h"
#include "Materials/MaterialRenderProxy.h"
#include "PrimitiveViewRelevance.h"
#include "Rendering/StaticMeshVertexBuffer.h"
#include "Rendering/PositionVertexBuffer.h"
#include "Rendering/ColorVertexBuffer.h"
#include "Materials/Material.h"
#include "RayTracingDefinitions.h"
#include "RayTracingInstance.h"
#include "VectorUtil.h"
#include "RenderResource.h"
#include "DynamicMeshBuilder.h"
#include "Voxel/LFPVoxelRendererComponent.h"

using namespace UE::Geometry;


class FLFPVoxelMeshRenderBufferSet
{
public:

	FLFPVoxelMeshRenderBufferSet(ERHIFeatureLevel::Type InFeatureLevel, int32 ID)
		: VertexFactory(InFeatureLevel, "FLFPVoxelMeshRenderBufferSet")
		, Material(nullptr)
		, SectionID(ID)
	{
		StaticMeshVertexBuffer.SetUseFullPrecisionUVs(true);
		StaticMeshVertexBuffer.SetUseHighPrecisionTangentBasis(true);
	}

	FORCEINLINE void InitOrUpdateResource(FRenderResource* Resource)
	{
		if (!Resource->IsInitialized())
		{
			Resource->InitResource(FRHICommandListExecutor::GetImmediateCommandList());
		}
		else
		{
			Resource->UpdateRHI(FRHICommandListExecutor::GetImmediateCommandList());
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

#if RHI_RAYTRACING
		if (IndexBuffer.Indices.IsEmpty() == false && IsRayTracingEnabled())
		{
			FRayTracingGeometryInitializer Initializer;
			Initializer.IndexBuffer = IndexBuffer.IndexBufferRHI;
			Initializer.TotalPrimitiveCount = IndexBuffer.Indices.Num() / 3;
			Initializer.GeometryType = RTGT_Triangles;
			Initializer.bFastBuild = true;
			Initializer.bAllowUpdate = false;

			FRayTracingGeometrySegment Segment;
			Segment.VertexBuffer = PositionVertexBuffer.VertexBufferRHI;
			Segment.VertexBufferStride = PositionVertexBuffer.GetStride();
			Segment.NumPrimitives = Initializer.TotalPrimitiveCount;
			Segment.MaxVertices = PositionVertexBuffer.GetNumVertices();
			Initializer.Segments.Add(Segment);

			RayTracingGeometry.SetInitializer(Initializer);
			RayTracingGeometry.InitResource(FRHICommandListExecutor::GetImmediateCommandList());

			RayTracingGeometry.UpdateRHI(FRHICommandListExecutor::GetImmediateCommandList());
		}
#endif
	}

	void Release()
	{
		PositionVertexBuffer.ReleaseResource();
		StaticMeshVertexBuffer.ReleaseResource();
		ColorVertexBuffer.ReleaseResource();
		IndexBuffer.ReleaseResource();
		VertexFactory.ReleaseResource();

#if RHI_RAYTRACING
		if (IsRayTracingEnabled())
		{
			RayTracingGeometry.ReleaseResource();
		}
#endif

		Material = nullptr;

		delete this;

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

	int32 SectionID = INDEX_NONE;

#if RHI_RAYTRACING
	/** The buffer containing the Ray Tracing Geometry data. */
	FRayTracingGeometry RayTracingGeometry;
#endif
};

/**
 *
 */
class FLFPVoxelRendererSceneProxy : public FPrimitiveSceneProxy
{
public:
	FLFPVoxelRendererSceneProxy(ULFPVoxelRendererComponent* Component, bool IsDynamic) : FPrimitiveSceneProxy(Component),
		VoxelComponent(Component),
		RenderData(Component->GetThreadResult()),
		CollisionBody(Component->GetBodySetup()),
		MaterialRelevance(Component->GetMaterialRelevance(GetScene().GetFeatureLevel())),
		bForceDynamic(IsDynamic)
	{
		//const double StartTime = FPlatformTime::Seconds();

		EnableGPUSceneSupportFlags();

		//bSupportsInstanceDataBuffer = true;

		bHasDeformableMesh = false;
		bCastDynamicShadow = true;
		bStaticElementsAlwaysUseProxyPrimitiveUniformBuffer = true;
		bVerifyUsedMaterials = false;

		bSupportsDistanceFieldRepresentation = RenderData.IsValid() && RenderData->DistanceFieldMeshData.IsValid();
		bVisibleInLumenScene = RenderData.IsValid() && RenderData->LumenCardData.IsValid();

		//bIsNaniteMesh = true;
		//bSupportsMeshCardRepresentation = RenderData.IsValid() && RenderData->LumenCardData.IsValid();

		//if (Component->bOverrideDistanceFieldSelfShadowBias) DistanceFieldSelfShadowBias = Component->DistanceFieldSelfShadowBias;

		const FVector3f VoxelHalfSize = FVector3f(Component->GetGenerationSetting().VoxelHalfSize);
		const FVector3f VoxelHalfBounds = VoxelHalfSize * FVector3f(Component->VoxelContainer->GetSetting().GetPaletteGrid());
		const FVector3f VoxelRenderOffset = FVector3f(-VoxelHalfBounds + VoxelHalfSize);

		for (int32 MaterialIndex = 0; MaterialIndex < RenderData->SectionData.Num(); MaterialIndex++)
		{
			const auto& BufferData = RenderData->SectionData[MaterialIndex];

			if (BufferData.TriangleCount == 0) continue;

			FLFPVoxelMeshRenderBufferSet* Buffer = AllocateNewBuffer(MaterialIndex);

			BufferData.GenerateFaceData(VoxelHalfSize, VoxelRenderOffset, Buffer->StaticMeshVertexBuffer, Buffer->PositionVertexBuffer, Buffer->IndexBuffer, Buffer->ColorVertexBuffer);

			if (Component->GetMaterial(MaterialIndex) != nullptr)
			{
				Buffer->Material = Component->GetMaterial(MaterialIndex);
			}
			else
			{
				Buffer->Material = UMaterial::GetDefaultMaterial(MD_Surface);
			}

			ENQUEUE_RENDER_COMMAND(FLFPBaseVoxelMeshSceneProxy)(
				[Buffer](FRHICommandListImmediate& RHICmdList)
				{
					Buffer->Upload();
				}
			);
		}

		bSupportsSortedTriangles = true;

		//UE_LOG(LogTemp, Warning, TEXT("VoxelRendererSceneProxy Generate Time Use : %f"), (float)(FPlatformTime::Seconds() - StartTime));

		return;
	}

	virtual ~FLFPVoxelRendererSceneProxy()
	{
		RenderData = nullptr;
		//LumenData = nullptr;
		VoxelComponent = nullptr;

		for (FLFPVoxelMeshRenderBufferSet* Buffer : AllocatedBufferSets)
		{
			if (Buffer != nullptr)
			{
				Buffer->Release();
			}
		}

		return;
	}

	FORCEINLINE FLFPVoxelMeshRenderBufferSet* AllocateNewBuffer(const int32 BufferID)
	{
		FLFPVoxelMeshRenderBufferSet* Buffer = new FLFPVoxelMeshRenderBufferSet(GetScene().GetFeatureLevel(), BufferID);

		if (AllocatedBufferSets.IsValidIndex(BufferID) == false)
		{
			AllocatedBufferSets.SetNum(BufferID + 1);
		}

		check(AllocatedBufferSets[BufferID] == nullptr); // Check Current Buffer Is Null

		// Set New Buffer To Array
		AllocatedBufferSets[BufferID] = Buffer;

		return Buffer;
	}

	virtual void DrawStaticElements(FStaticPrimitiveDrawInterface* PDI) override
	{
		for (FLFPVoxelMeshRenderBufferSet* BufferSet : AllocatedBufferSets)
		{
			if (BufferSet == nullptr || BufferSet->IndexBuffer.Indices.Num() == 0)
			{
				continue;
			}

			FMeshBatch MeshBatch;

			DrawBatch(MeshBatch, *BufferSet, BufferSet->Material->GetRenderProxy(), false);

			MeshBatch.LODIndex = 0;

			PDI->DrawMesh(MeshBatch, FLT_MAX);
		}
	}

	virtual void GetDynamicMeshElements(
		const TArray<const FSceneView*>& Views,
		const FSceneViewFamily& ViewFamily,
		uint32 VisibilityMap,
		FMeshElementCollector& Collector) const override
	{
		const bool bWireframe = AllowDebugViewmodes() && ViewFamily.EngineShowFlags.Wireframe;

		FColoredMaterialRenderProxy* WireframeMaterialInstance = nullptr;

		// set up wireframe material. Probably bad to reference GEngine here...also this material is very bad?
		if (bWireframe)
		{
			WireframeMaterialInstance = new FColoredMaterialRenderProxy(
				GEngine->WireframeMaterial ? GEngine->WireframeMaterial->GetRenderProxy() : nullptr,
				FLinearColor(0, 0.5f, 1.f)
			);

			Collector.RegisterOneFrameMaterialProxy(WireframeMaterialInstance);
		}

		for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++)
		{
			const FSceneView* View = Views[ViewIndex];

			if (IsShown(View) && (VisibilityMap & (1 << ViewIndex)))
			{
				FFrozenSceneViewMatricesGuard FrozenMatricesGuard(*const_cast<FSceneView*>(Views[ViewIndex]));

				// Draw the mesh.
				for (FLFPVoxelMeshRenderBufferSet* BufferSet : AllocatedBufferSets)
				{
					if (BufferSet == nullptr)
					{
						continue;
					}

					if (BufferSet->IndexBuffer.Indices.Num() > 0)
					{
						FMeshBatch& MeshBatch = Collector.AllocateMesh();

						DrawBatch(MeshBatch, *BufferSet, bWireframe ? WireframeMaterialInstance : BufferSet->Material->GetRenderProxy(), false);

						MeshBatch.bWireframe = bWireframe;
						MeshBatch.bDitheredLODTransition = false;

						Collector.AddMesh(ViewIndex, MeshBatch);
					}
				}
			}
		}

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
		for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++)
		{
			if (VisibilityMap & (1 << ViewIndex))
			{
				// Draw simple collision as wireframe if 'show collision', and collision is enabled, and we are not using the complex as the simple
				if (CollisionBody && ViewFamily.EngineShowFlags.Collision && IsCollisionEnabled() && CollisionBody->GetCollisionTraceFlag() != ECollisionTraceFlag::CTF_UseComplexAsSimple)
				{
					FTransform GeomTransform(GetLocalToWorld());
					CollisionBody->AggGeom.GetAggGeom(GeomTransform, GetSelectionColor(FColor(157, 149, 223, 255), IsSelected(), IsHovered()).ToFColor(true), NULL, false, false, DrawsVelocity(), ViewIndex, Collector);
				}
				// Render bounds
				RenderBounds(Collector.GetPDI(ViewIndex), ViewFamily.EngineShowFlags, GetBounds(), IsSelected());
			}
		}
#endif
	}

	FORCEINLINE void DrawBatch(FMeshBatch& MeshBatch,
		const FLFPVoxelMeshRenderBufferSet& RenderBuffers,
		FMaterialRenderProxy* UseMaterial,
		bool bForRayTracing) const
	{
		FMeshBatchElement& BatchElement = MeshBatch.Elements[0];
		BatchElement.PrimitiveUniformBuffer = GetUniformBuffer();
		BatchElement.IndexBuffer = &RenderBuffers.IndexBuffer;
		BatchElement.FirstIndex = 0;
		BatchElement.NumPrimitives = RenderBuffers.IndexBuffer.Indices.Num() / 3;
		BatchElement.MinVertexIndex = 0;
		BatchElement.MaxVertexIndex = RenderBuffers.PositionVertexBuffer.GetNumVertices() - 1;

		MeshBatch.VertexFactory = &RenderBuffers.VertexFactory;
		MeshBatch.MaterialRenderProxy = UseMaterial;
		MeshBatch.bDitheredLODTransition = !bForRayTracing && !IsMovable() && UseMaterial->GetMaterialInterface()->IsDitheredLODTransition();

		MeshBatch.ReverseCulling = IsLocalToWorldDeterminantNegative();
		MeshBatch.Type = PT_TriangleList;
		MeshBatch.DepthPriorityGroup = SDPG_World;
		MeshBatch.bCanApplyViewModeOverrides = false;
		MeshBatch.SegmentIndex = 0;
		MeshBatch.MeshIdInPrimitive = RenderBuffers.SectionID;

		return;
	}

	virtual const FCardRepresentationData* GetMeshCardRepresentation() const
	{
		return RenderData->LumenCardData.Get();
	}
	
	virtual void GetDistanceFieldAtlasData(const class FDistanceFieldVolumeData*& OutDistanceFieldData, float& SelfShadowBias) const override
	{
		OutDistanceFieldData = RenderData->DistanceFieldMeshData.Get();
		SelfShadowBias = VoxelComponent->DistanceFieldSelfShadowBias;
	}

	virtual void GetDistanceFieldInstanceData(TArray<FRenderTransform>& ObjectLocalToWorldTransforms) const override
	{
		ObjectLocalToWorldTransforms.Add(FRenderTransform::Identity);
	}

	virtual bool HasDistanceFieldRepresentation() const override
	{
		return RenderData.IsValid() && RenderData->DistanceFieldMeshData.IsValid();
	}

#if RHI_RAYTRACING
	virtual bool IsRayTracingRelevant() const override { return true; }
	
	virtual bool IsRayTracingStaticRelevant() const override { return false; }
	
	virtual bool HasRayTracingRepresentation() const override { return true; }
	
	virtual void GetDynamicRayTracingInstances(FRayTracingMaterialGatheringContext& Context, TArray<FRayTracingInstance>& OutRayTracingInstances) override final
	{
		for (const FLFPVoxelMeshRenderBufferSet* Section : AllocatedBufferSets)
		{
			if (Section == nullptr || Section->IndexBuffer.Indices.Num() == 0 || Section->RayTracingGeometry.RayTracingGeometryRHI.IsValid() == false)
			{
				continue;
			}

			FMaterialRenderProxy* MaterialProxy = Section->Material->GetRenderProxy();

			check(Section->RayTracingGeometry.RayTracingGeometryRHI);
			check(Section->RayTracingGeometry.Initializer.TotalPrimitiveCount > 0);
			check(Section->RayTracingGeometry.Initializer.IndexBuffer.IsValid());

			FRayTracingInstance& RayTracingInstance = OutRayTracingInstances.AddDefaulted_GetRef();

			RayTracingInstance.Geometry = &Section->RayTracingGeometry;
			RayTracingInstance.InstanceTransforms.Add(GetLocalToWorld());

			FMeshBatch MeshBatch;

			DrawBatch(MeshBatch, *Section, Section->Material->GetRenderProxy(), true);

			MeshBatch.CastRayTracedShadow = IsShadowCast(Context.ReferenceView);

			RayTracingInstance.Materials.Add(MeshBatch);
		}
	}

#endif

	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const
	{
		FPrimitiveViewRelevance Result;

		if (IsRichView(*View->Family) || IsSelected() || View->Family->EngineShowFlags.Wireframe || bForceDynamic)
		{
			Result.bDynamicRelevance = true;
		}
		else
		{
			Result.bStaticRelevance = true;
		}


		Result.bDrawRelevance = IsShown(View);
		Result.bShadowRelevance = IsShadowCast(View);
		Result.bRenderInMainPass = ShouldRenderInMainPass();
		Result.bUsesLightingChannels = GetLightingChannelMask() != GetDefaultLightingChannelMask();
		Result.bRenderCustomDepth = ShouldRenderCustomDepth();
		Result.bTranslucentSelfShadow = bCastVolumetricTranslucentShadow;
		MaterialRelevance.SetPrimitiveViewRelevance(Result);
		Result.bVelocityRelevance = IsMovable() && DrawsVelocity() && Result.bOpaque && Result.bRenderInMainPass;
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

	TObjectPtr<ULFPVoxelRendererComponent> VoxelComponent = nullptr;

	TSharedPtr<FLFPVoxelRendererThreadResult> RenderData = nullptr;

	TArray<FLFPVoxelMeshRenderBufferSet*> AllocatedBufferSets;

	TObjectPtr<UBodySetup> CollisionBody = nullptr;

	FMaterialRelevance MaterialRelevance;

	const bool bForceDynamic;
};

