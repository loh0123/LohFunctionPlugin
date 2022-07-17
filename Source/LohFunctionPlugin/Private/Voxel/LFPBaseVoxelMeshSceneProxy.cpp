// Copyright by Loh Zhi Kang


#include "Voxel/LFPBaseVoxelMeshSceneProxy.h"

FLFPBaseVoxelMeshSceneProxy::FLFPBaseVoxelMeshSceneProxy(ULFPBaseVoxelMeshComponent* Component, const int32 BufferCount) : FPrimitiveSceneProxy(Component), VoxelComponent(Component), MaterialRelevance(Component->GetMaterialRelevance(GetScene().GetFeatureLevel()))
{
	(new FAutoDeleteAsyncTask<FLFPBaseVoxelMeshSceneProxyTask>(this, 0))->StartBackgroundTask();

	return;
}

FLFPBaseVoxelMeshSceneProxy::~FLFPBaseVoxelMeshSceneProxy()
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

FLFPVoxelMeshRenderBufferSet* FLFPBaseVoxelMeshSceneProxy::AllocateNewBuffer()
{
	return new FLFPVoxelMeshRenderBufferSet(GetScene().GetFeatureLevel());
}

void FLFPBaseVoxelMeshSceneProxy::SetBufferSet(const int32 BufferID, FLFPVoxelMeshRenderBufferSet* Buffer, const int32 WorkVersion)
{
	AllocatedBufferSetsLock.Lock();

	if (WorkVersion == Version)
	{
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

		ENQUEUE_RENDER_COMMAND(FLFPBaseVoxelMeshSceneProxy)(
			[Buffer](FRHICommandListImmediate& RHICmdList)
			{
				Buffer->Upload();
			});
	}

	AllocatedBufferSetsLock.Unlock();

	return;
}

void FLFPBaseVoxelMeshSceneProxy::GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const
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

void FLFPBaseVoxelMeshSceneProxy::DrawBatch(FMeshElementCollector& Collector, const FLFPVoxelMeshRenderBufferSet& RenderBuffers, const FDynamicMeshIndexBuffer32& IndexBuffer, FMaterialRenderProxy* UseMaterial, bool bWireframe, ESceneDepthPriorityGroup DepthPriority, int ViewIndex, FDynamicPrimitiveUniformBuffer& DynamicPrimitiveUniformBuffer) const
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

FPrimitiveViewRelevance FLFPBaseVoxelMeshSceneProxy::GetViewRelevance(const FSceneView* View) const
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



void FLFPBaseVoxelMeshSceneProxyTask::DoWork()
{
	if (Proxy == nullptr || Proxy->GetVersion() != WorkVersion) return;

	FLFPVoxelMeshRenderBufferSet* Buffer = Proxy->AllocateNewBuffer();

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

	Proxy->SetBufferSet(BufferID, Buffer, WorkVersion);

	return;
}
