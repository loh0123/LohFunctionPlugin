// Copyright (c) 2022 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#pragma once

#include "CoreMinimal.h"
#include "PrimitiveSceneProxy.h"
#include "LocalVertexFactory.h"
#include "PrimitiveViewRelevance.h"
#include "Rendering/StaticMeshVertexBuffer.h"
#include "Rendering/PositionVertexBuffer.h"
#include "Rendering/ColorVertexBuffer.h"
#include "Materials/Material.h"
#include "RayTracingDefinitions.h"
#include "RayTracingInstance.h"
#include "VectorUtil.h"

#include "Voxel/LFPBaseVoxelMeshComponent.h"

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

#if RHI_RAYTRACING
		if (IndexBuffer.Indices.IsEmpty() == false && IsRayTracingEnabled())
		{
			FRayTracingGeometryInitializer Initializer;
			Initializer.IndexBuffer = IndexBuffer.IndexBufferRHI;
			Initializer.TotalPrimitiveCount = IndexBuffer.Indices.Num() / 3;
			Initializer.GeometryType = RTGT_Triangles;
			Initializer.bFastBuild = true;
			Initializer.bAllowUpdate = false;

			RayTracingGeometry.SetInitializer(Initializer);
			RayTracingGeometry.InitResource();

			FRayTracingGeometrySegment Segment;
			Segment.VertexBuffer = PositionVertexBuffer.VertexBufferRHI;
			Segment.VertexBufferStride = PositionVertexBuffer.GetStride();
			Segment.NumPrimitives = RayTracingGeometry.Initializer.TotalPrimitiveCount;
			Segment.MaxVertices = PositionVertexBuffer.GetNumVertices();
			RayTracingGeometry.Initializer.Segments.Add(Segment);

			RayTracingGeometry.UpdateRHI();
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
class FLFPBaseVoxelMeshSceneProxy : public FPrimitiveSceneProxy
{
public:
	FLFPBaseVoxelMeshSceneProxy(ULFPBaseVoxelMeshComponent* Component) : FPrimitiveSceneProxy(Component), 
		  VoxelComponent(Component)
		, RenderData(Component->RenderData.GetReference())
		, MaterialRelevance(Component->GetMaterialRelevance(GetScene().GetFeatureLevel()))
	{
		bCastDynamicShadow = true;
		bVFRequiresPrimitiveUniformBuffer = !UseGPUScene(GMaxRHIShaderPlatform, GetScene().GetFeatureLevel());
		bStaticElementsAlwaysUseProxyPrimitiveUniformBuffer = true;
		bVerifyUsedMaterials = false;

		bSupportsDistanceFieldRepresentation = true;
		bSupportsMeshCardRepresentation = true;

		const TArray<FLFPBaseVoxelMeshSectionData>& BufferDataList = Component->RenderData->Sections;

		for (int32 MaterialIndex = 0; MaterialIndex < BufferDataList.Num(); MaterialIndex++)
		{
			const FLFPBaseVoxelMeshSectionData& BufferData = BufferDataList[MaterialIndex];

			if (BufferData.TriangleIndexList.IsEmpty()) continue;

			FLFPVoxelMeshRenderBufferSet* Buffer = AllocateNewBuffer(MaterialIndex);

			Buffer->PositionVertexBuffer.Init(BufferData.VertexList);

			Buffer->IndexBuffer.Indices = BufferData.TriangleIndexList;

			Buffer->ColorVertexBuffer.InitFromColorArray(BufferData.VoxelColorList);

			Buffer->StaticMeshVertexBuffer.Init(BufferData.VertexList.Num(), 4);

			ParallelFor(BufferData.UVList.Num(), [&](const int32 Index)
				{
					Buffer->StaticMeshVertexBuffer.SetVertexUV(Index, 0, BufferData.UVList[Index]);
					Buffer->StaticMeshVertexBuffer.SetVertexUV(Index, 1, BufferData.EdgeUVList[Index]);
					Buffer->StaticMeshVertexBuffer.SetVertexUV(Index, 2, BufferData.PointUVList[Index]);
					Buffer->StaticMeshVertexBuffer.SetVertexUV(Index, 3, BufferData.PositionUVList[Index]);
				});

			ParallelFor(BufferData.TriangleCount, [&](const int32 Index) {
				int32 VertexIndStart = Index * 3;

				const FVector3f TriVertices[3] = {
					BufferData.VertexList[BufferData.TriangleIndexList[VertexIndStart]],
					BufferData.VertexList[BufferData.TriangleIndexList[VertexIndStart + 1]],
					BufferData.VertexList[BufferData.TriangleIndexList[VertexIndStart + 2]],
				};

				const FVector2f TriUVs[3] = {
					BufferData.UVList[BufferData.TriangleIndexList[VertexIndStart]],
					BufferData.UVList[BufferData.TriangleIndexList[VertexIndStart + 1]],
					BufferData.UVList[BufferData.TriangleIndexList[VertexIndStart + 2]],
				};

				FVector3f Tangent, Bitangent, Normal;

				Normal = VectorUtil::Normal(TriVertices[0], TriVertices[1], TriVertices[2]);

				ComputeFaceTangent(TriVertices, TriUVs, Tangent, Bitangent);

				FVector3f ProjectedTangent = Normalized(Tangent - Tangent.Dot(Normal) * Normal);

				float BitangentSign = VectorUtil::BitangentSign(Normal, ProjectedTangent, Bitangent);
				FVector3f ReconsBitangent = VectorUtil::Bitangent(Normal, ProjectedTangent, BitangentSign);

				for (int32 VertexInd = VertexIndStart; VertexInd < VertexIndStart + 3; VertexInd++)
				{
					Buffer->StaticMeshVertexBuffer.SetVertexTangents(VertexInd, ProjectedTangent, ReconsBitangent, Normal);
				}
			});

			if (Component->GetMaterial(MaterialIndex) != nullptr)
			{
				Buffer->Material = Component->GetMaterial(MaterialIndex);
			}

			ENQUEUE_RENDER_COMMAND(FLFPBaseVoxelMeshSceneProxy)(
				[Buffer](FRHICommandListImmediate& RHICmdList)
				{
					Buffer->Upload();
				});
		}
		
		return;
	}

	virtual ~FLFPBaseVoxelMeshSceneProxy()
	{
		RenderData = nullptr;
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

	FORCEINLINE void ComputeFaceTangent(
		const FVector3f TriVertices[3], const FVector2f TriUVs[3],
		FVector3f& TangentOut, FVector3f& BitangentOut)
	{
		FVector2f UVEdge1 = TriUVs[1] - TriUVs[0];
		FVector2f UVEdge2 = TriUVs[2] - TriUVs[0];
		FVector3f TriEdge1 = TriVertices[1] - TriVertices[0];
		FVector3f TriEdge2 = TriVertices[2] - TriVertices[0];

		FVector3f TriTangent = (UVEdge2.Y * TriEdge1) - (UVEdge1.Y * TriEdge2);
		FVector3f TriBitangent = (-UVEdge2.X * TriEdge1) + (UVEdge1.X * TriEdge2);

		double UVArea = (UVEdge1.X * UVEdge2.Y) - (UVEdge1.Y * UVEdge2.X);
		bool bPreserveOrientation = (UVArea >= 0);

		UVArea = FMathd::Abs(UVArea);

		// if a triangle is zero-UV-area due to one edge being collapsed, we still have a 
		// valid direction on the other edge. We are going to keep those
		double TriTangentLength = TriTangent.Length();
		double TriBitangentLength = TriBitangent.Length();
		TangentOut = (TriTangentLength > 0) ? (TriTangent / TriTangentLength) : FVector3f::Zero();
		BitangentOut = (TriBitangentLength > 0) ? (TriBitangent / TriBitangentLength) : FVector3f::Zero();

		if (bPreserveOrientation == false)
		{
			TangentOut = -TangentOut;
			BitangentOut = -BitangentOut;
		}
	}

	virtual void DrawStaticElements(FStaticPrimitiveDrawInterface* PDI) override
	{
		for (FLFPVoxelMeshRenderBufferSet* BufferSet : AllocatedBufferSets)
		{
			if (BufferSet == nullptr)
			{
				continue;
			}

			if (BufferSet->IndexBuffer.Indices.Num() > 0)
			{
				FMeshBatch MeshBatch;

				DrawBatch(MeshBatch, *BufferSet, BufferSet->Material->GetRenderProxy(), false);

				MeshBatch.LODIndex = 0;

				PDI->DrawMesh(MeshBatch, 1.f);
			}
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

			bool bNeedDynamicPath = IsRichView(*Views[ViewIndex]->Family) || Views[ViewIndex]->Family->EngineShowFlags.Wireframe || IsSelected();

			if (bNeedDynamicPath && IsShown(View) && (VisibilityMap & (1 << ViewIndex)))
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
		MeshBatch.SegmentIndex = RenderBuffers.SectionID;

		//MeshBatch.MeshIdInPrimitive = RenderBuffers.SectionID;

		return;
	}

	virtual const FCardRepresentationData* GetMeshCardRepresentation() const
	{
		return RenderData->LumenCardData;
	}

	virtual void GetDistanceFieldAtlasData(const class FDistanceFieldVolumeData*& OutDistanceFieldData, float& SelfShadowBias) const override
	{
		OutDistanceFieldData = RenderData->DistanceFieldMeshData;
		SelfShadowBias = 1.0f;
	}

	virtual void GetDistanceFieldInstanceData(TArray<FRenderTransform>& ObjectLocalToWorldTransforms) const override
	{
		FRenderTransform CurrentLocal = (FMatrix44f)GetLocalToWorld();

		for (const FTransform& DFTransform : RenderData->DistanceFieldInstanceData)
		{
			ObjectLocalToWorldTransforms.Add(DFTransform.ToMatrixWithScale() * (FMatrix44d)GetLocalToWorld());
		}
	}

	virtual bool HasDistanceFieldRepresentation() const override
	{
		return RenderData->DistanceFieldMeshData != nullptr;
	}

#if RHI_RAYTRACING
	virtual bool IsRayTracingRelevant() const override { return true; }

	virtual bool IsRayTracingStaticRelevant() const override { return false; }

	virtual bool HasRayTracingRepresentation() const override { return true; }

	virtual void GetDynamicRayTracingInstances(FRayTracingMaterialGatheringContext& Context, TArray<FRayTracingInstance>& OutRayTracingInstances) override final
	{
		for (const FLFPVoxelMeshRenderBufferSet* Section : AllocatedBufferSets)
		{
			if (Section != nullptr)
			{
				FMaterialRenderProxy* MaterialProxy = Section->Material->GetRenderProxy();

				if (Section->RayTracingGeometry.RayTracingGeometryRHI.IsValid())
				{
					check(Section->RayTracingGeometry.Initializer.TotalPrimitiveCount > 0);
					check(Section->RayTracingGeometry.Initializer.IndexBuffer.IsValid());

					FRayTracingInstance RayTracingInstance;
					RayTracingInstance.Geometry = &Section->RayTracingGeometry;
					RayTracingInstance.InstanceTransforms.Add(GetLocalToWorld());

					FMeshBatch MeshBatch;

					DrawBatch(MeshBatch, *Section, Section->Material->GetRenderProxy(), false);

					MeshBatch.CastRayTracedShadow = IsShadowCast(Context.ReferenceView);

					RayTracingInstance.Materials.Add(MeshBatch);
					RayTracingInstance.BuildInstanceMaskAndFlags(GetScene().GetFeatureLevel());
					OutRayTracingInstances.Add(RayTracingInstance);
				}
			}
		}
	}

#endif

	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const
	{
		FPrimitiveViewRelevance Result;

		if (IsRichView(*View->Family) || IsSelected() || View->Family->EngineShowFlags.Wireframe)
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

	ULFPBaseVoxelMeshComponent* VoxelComponent = nullptr;

	TRefCountPtr<FLFPBaseVoxelMeshRenderData> RenderData = nullptr;

	TArray<FLFPVoxelMeshRenderBufferSet*> AllocatedBufferSets;

	FMaterialRelevance MaterialRelevance;
};

//class FLFPBaseVoxelMeshSceneProxyTask : public FNonAbandonableTask
//{
//	friend class FAutoDeleteAsyncTask<FLFPBaseVoxelMeshSceneProxyTask>;
//
//public:
//
//	FLFPBaseVoxelMeshSceneProxyTask() {}
//
//	void DoWork();
//
//	// This next section of code needs to be here. Not important as to why.
//
//	FORCEINLINE TStatId GetStatId() const { RETURN_QUICK_DECLARE_CYCLE_STAT(FLFPBaseVoxelMeshSceneProxyTask, STATGROUP_ThreadPoolAsyncTasks); }
//};
