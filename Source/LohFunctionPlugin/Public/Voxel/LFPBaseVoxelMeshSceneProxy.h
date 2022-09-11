// Copyright by Loh Zhi Kang

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
		, Material(UMaterial::GetDefaultMaterial(MD_Surface))
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
		, VoxelMeshRenderData(Component->VoxelMeshRenderData)
		, MaterialRelevance(Component->GetMaterialRelevance(GetScene().GetFeatureLevel()))
	{
		bSupportsDistanceFieldRepresentation = true;
		bSupportsMeshCardRepresentation = true;

		bStaticElementsAlwaysUseProxyPrimitiveUniformBuffer = true;

		const TArray<FVoxelMeshSectionData>& BufferDataList = Component->VoxelMeshRenderData->Sections;

		for (int32 MaterialIndex = 0; MaterialIndex < BufferDataList.Num(); MaterialIndex++)
		{
			const FVoxelMeshSectionData& BufferData = BufferDataList[MaterialIndex];

			if (BufferData.TriangleIndexList.IsEmpty()) continue;

			FLFPVoxelMeshRenderBufferSet* Buffer = AllocateNewBuffer(MaterialIndex);

			Buffer->PositionVertexBuffer.Init(BufferData.VertexList);

			Buffer->IndexBuffer.Indices = BufferData.TriangleIndexList;

			Buffer->ColorVertexBuffer.Init(BufferData.VertexList.Num());

			Buffer->StaticMeshVertexBuffer.Init(BufferData.VertexList.Num(), 1);

			ParallelFor(BufferData.TriangleCount, [&](const int32 Index) {
				int32 VertexIndStart = Index * 3;

				FVector3f TriVertices[3] = {
					BufferData.VertexList[BufferData.TriangleIndexList[VertexIndStart]],
					BufferData.VertexList[BufferData.TriangleIndexList[VertexIndStart + 1]],
					BufferData.VertexList[BufferData.TriangleIndexList[VertexIndStart + 2]],
				};

				FVector2f TriUVs[3] = {
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
					Buffer->StaticMeshVertexBuffer.SetVertexUV(VertexInd, 0, TriUVs[VertexInd - VertexIndStart]);

					Buffer->StaticMeshVertexBuffer.SetVertexTangents(VertexInd, ProjectedTangent, ReconsBitangent, Normal);

					Buffer->ColorVertexBuffer.VertexColor(VertexInd) = BufferData.VoxelColorList[Index];
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
		VoxelComponent = nullptr;

		delete VoxelMeshRenderData;

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
		FVector3f TriVertices[3], FVector2f TriUVs[3],
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
		// set up wireframe material. Probably bad to reference GEngine here...also this material is very bad?
		FColoredMaterialRenderProxy* WireframeMaterialInstance = new FColoredMaterialRenderProxy(
			GEngine->WireframeMaterial ? GEngine->WireframeMaterial->GetRenderProxy() : nullptr,
			FLinearColor(0, 0.5f, 1.f)
		);

		Collector.RegisterOneFrameMaterialProxy(WireframeMaterialInstance);
	
		for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++)
		{
			if (VisibilityMap & (1 << ViewIndex))
			{
				const FSceneView* View = Views[ViewIndex];

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
	
						DrawBatch(MeshBatch, *BufferSet, WireframeMaterialInstance, false);

						MeshBatch.bWireframe = true;
					
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
		BatchElement.IndexBuffer = &RenderBuffers.IndexBuffer;
		BatchElement.FirstIndex = 0;
		BatchElement.NumPrimitives = RenderBuffers.IndexBuffer.Indices.Num() / 3;
		BatchElement.MinVertexIndex = 0;
		BatchElement.MaxVertexIndex = RenderBuffers.PositionVertexBuffer.GetNumVertices() - 1;

		MeshBatch.VertexFactory = &RenderBuffers.VertexFactory;
		MeshBatch.MaterialRenderProxy = UseMaterial;

		MeshBatch.ReverseCulling = IsLocalToWorldDeterminantNegative();
		MeshBatch.Type = PT_TriangleList;
		MeshBatch.DepthPriorityGroup = SDPG_World;
		MeshBatch.bCanApplyViewModeOverrides = false;
		MeshBatch.SegmentIndex = RenderBuffers.SectionID;
		MeshBatch.LODIndex = 0;

		MeshBatch.MeshIdInPrimitive = RenderBuffers.SectionID;

#if RHI_RAYTRACING
		MeshBatch.CastRayTracedShadow = MeshBatch.CastShadow && bCastDynamicShadow;
#endif

		return;
	}

	virtual const FCardRepresentationData* GetMeshCardRepresentation() const
	{
		return VoxelMeshRenderData->LumenCardData;
	}

	virtual void GetDistanceFieldAtlasData(const class FDistanceFieldVolumeData*& OutDistanceFieldData, float& SelfShadowBias) const override
	{
		OutDistanceFieldData = VoxelMeshRenderData->DistanceFieldMeshData;
		SelfShadowBias = 1.0f;
	}

	virtual void GetDistanceFieldInstanceData(TArray<FRenderTransform>& ObjectLocalToWorldTransforms) const override
	{
		FRenderTransform CurrentLocal = (FMatrix44f)GetLocalToWorld();

		for (const FTransform& DFTransform : VoxelMeshRenderData->DistanceFieldInstanceData)
		{
			ObjectLocalToWorldTransforms.Add(DFTransform.ToMatrixWithScale() * (FMatrix44d)GetLocalToWorld());
		}
	}

	virtual bool HasDistanceFieldRepresentation() const override
	{
		return VoxelMeshRenderData->DistanceFieldMeshData != nullptr;
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
					check(Section->RayTracingGeometry.Initializer.IndexBuffer.IsValid());

					FRayTracingInstance RayTracingInstance;
					RayTracingInstance.Geometry = &Section->RayTracingGeometry;
					RayTracingInstance.InstanceTransforms.Add(GetLocalToWorld());

					uint32 SectionIdx = 0;
					FMeshBatch MeshBatch;

					MeshBatch.VertexFactory = &Section->VertexFactory;
					MeshBatch.SegmentIndex = 0;
					MeshBatch.MaterialRenderProxy = Section->Material->GetRenderProxy();
					MeshBatch.ReverseCulling = IsLocalToWorldDeterminantNegative();
					MeshBatch.Type = PT_TriangleList;
					MeshBatch.DepthPriorityGroup = SDPG_World;
					MeshBatch.bCanApplyViewModeOverrides = false;
					MeshBatch.CastRayTracedShadow = IsShadowCast(Context.ReferenceView);

					FMeshBatchElement& BatchElement = MeshBatch.Elements[0];
					BatchElement.IndexBuffer = &Section->IndexBuffer;

					bool bHasPrecomputedVolumetricLightmap;
					FMatrix PreviousLocalToWorld;
					int32 SingleCaptureIndex;
					bool bOutputVelocity;
					GetScene().GetPrimitiveUniformShaderParameters_RenderThread(GetPrimitiveSceneInfo(), bHasPrecomputedVolumetricLightmap, PreviousLocalToWorld, SingleCaptureIndex, bOutputVelocity);

					FDynamicPrimitiveUniformBuffer& DynamicPrimitiveUniformBuffer = Context.RayTracingMeshResourceCollector.AllocateOneFrameResource<FDynamicPrimitiveUniformBuffer>();
					DynamicPrimitiveUniformBuffer.Set(GetLocalToWorld(), PreviousLocalToWorld, GetBounds(), GetLocalBounds(), GetLocalBounds(), true, bHasPrecomputedVolumetricLightmap, DrawsVelocity(), bOutputVelocity, GetCustomPrimitiveData());
					BatchElement.PrimitiveUniformBufferResource = &DynamicPrimitiveUniformBuffer.UniformBuffer;

					BatchElement.FirstIndex = 0;
					BatchElement.NumPrimitives = Section->IndexBuffer.Indices.Num() / 3;
					BatchElement.MinVertexIndex = 0;
					BatchElement.MaxVertexIndex = Section->PositionVertexBuffer.GetNumVertices() - 1;

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

		if (AllowDebugViewmodes() && View->Family->EngineShowFlags.Wireframe)
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

	FVoxelMeshRenderData* VoxelMeshRenderData = nullptr;

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