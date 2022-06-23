// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeometryFramework/Public/Components/BaseDynamicMeshSceneProxy.h"
#include "Mesh/VoxelDynamicMeshComponent.h"

/**
 * 
 */
class FVoxelDynamicMeshSceneProxy final : public FBaseDynamicMeshSceneProxy
{
public:

	FVoxelDynamicMeshSceneProxy(UVoxelDynamicMeshComponent* Component)
		: FBaseDynamicMeshSceneProxy(Component)
		, MaterialRelevance(Component->GetMaterialRelevance(GetScene().GetFeatureLevel()))
		, SectionCount(Component->GetVoxelSectionCount())
	{
		ParentComponent = Component;
	}

	virtual ~FVoxelDynamicMeshSceneProxy() 
	{
		ParentComponent = nullptr;
	}

	virtual void GetActiveRenderBufferSets(TArray<FMeshRenderBufferSet*>& Buffers) const override
	{
		for (FMeshRenderBufferSet* Buffer : RenderBufferSets)
		{
			if (Buffer != nullptr && Buffer->TriangleCount > 0) Buffers.Add(Buffer);
		}
	}

	TUniqueFunction<void(int, int, int, const FVector3f&, FVector3f&, FVector3f&)> MakeTangentsFunc(bool bSkipAutoCompute = false)
	{
		if (bSkipAutoCompute == false)
		{
			const UE::Geometry::FMeshTangentsf* Tangents = ParentComponent->GetAutoCalculatedTangents();
			if (Tangents != nullptr)
			{
				return [Tangents](int VertexID, int TriangleID, int TriVtxIdx, const FVector3f& Normal, FVector3f& TangentX, FVector3f& TangentY) -> void
				{
					Tangents->GetTriangleVertexTangentVectors(TriangleID, TriVtxIdx, TangentX, TangentY);
				};
			}
		}

		// fallback to orthogonal basis
		return [](int VertexID, int TriangleID, int TriVtxIdx, const FVector3f& Normal, FVector3f& TangentX, FVector3f& TangentY) -> void
		{
			UE::Geometry::VectorUtil::MakePerpVectors(Normal, TangentX, TangentY);
		};
	}

	void Initialize()
	{
		if (SectionCount != GetNumMaterials()) return;

		// allocate buffer sets based on materials
		ensure(RenderBufferSets.Num() == 0);
		int32 NumMaterials = GetNumMaterials();
		if (NumMaterials == 0)
		{
			RenderBufferSets.SetNum(1);
			RenderBufferSets[0] = AllocateNewRenderBufferSet();
			RenderBufferSets[0]->Material = UMaterial::GetDefaultMaterial(MD_Surface);
		}
		else
		{
			RenderBufferSets.SetNum(NumMaterials);
			for (int32 k = 0; k < NumMaterials; ++k)
			{
				RenderBufferSets[k] = AllocateNewRenderBufferSet();
				RenderBufferSets[k]->Material = GetMaterial(k);
			}
		}

		InitializeByMaterial(RenderBufferSets);
	}

	void InitializeByMaterial(TArray<FMeshRenderBufferSet*>& BufferSets)
	{
		const FDynamicMesh3* Mesh = ParentComponent->GetRenderMesh();
		if (ensure(Mesh->HasAttributes() && Mesh->Attributes()->HasMaterialID()) == false)
		{
			return;
		}

		const FDynamicMeshAttributeSet* Attributes = Mesh->Attributes();

		// find suitable overlays
		const FDynamicMeshMaterialAttribute* MaterialID = Attributes->GetMaterialID();
		const FDynamicMeshNormalOverlay* NormalOverlay = Mesh->Attributes()->PrimaryNormals();
		const FDynamicMeshColorOverlay* ColorOverlay = Mesh->Attributes()->PrimaryColors();

		TArray<const FDynamicMeshUVOverlay*, TInlineAllocator<8>> UVOverlays;
		UVOverlays.SetNum(Attributes->NumUVLayers());
		for (int32 k = 0; k < UVOverlays.Num(); ++k)
		{
			UVOverlays[k] = Attributes->GetUVLayer(k);
		}

		TUniqueFunction<void(int, int, int, const FVector3f&, FVector3f&, FVector3f&)> TangentsFunc = MakeTangentsFunc();

		// count number of triangles for each material (could do in parallel?)
		int NumMaterials = BufferSets.Num();
		TArray<FThreadSafeCounter> Counts;
		Counts.SetNum(NumMaterials);
		for (int k = 0; k < NumMaterials; ++k)
		{
			Counts[k].Reset();
		}
		ParallelFor(Mesh->MaxTriangleID(), [&](int tid)
			{
				if (!Mesh->IsTriangle(tid))
				{
					return;
				}
				int MatIdx;
				MaterialID->GetValue(tid, &MatIdx);
				if (MatIdx >= 0 && MatIdx < NumMaterials)
				{
					Counts[MatIdx].Increment();
				}
			});

		// find max count
		int32 MaxCount = 0;
		for (FThreadSafeCounter& Count : Counts)
		{
			MaxCount = FMath::Max(Count.GetValue(), MaxCount);
		}

		// init renderbuffers for each material
		// could do this in parallel but then we need to allocate separate triangle arrays...is it worth it?
		TArray<int> Triangles;
		Triangles.Reserve(MaxCount);
		for (int k = 0; k < NumMaterials; ++k)
		{
			if (Counts[k].GetValue() > 0)
			{
				FMeshRenderBufferSet* RenderBuffers = BufferSets[k];

				Triangles.Reset();
				for (int tid : Mesh->TriangleIndicesItr())
				{
					int MatIdx;
					MaterialID->GetValue(tid, &MatIdx);
					if (MatIdx == k)
					{
						Triangles.Add(tid);
					}
				}

				InitializeBuffersFromOverlays(RenderBuffers, Mesh,
					Triangles.Num(), Triangles,
					UVOverlays, NormalOverlay, ColorOverlay, TangentsFunc);

				RenderBuffers->Triangles = Triangles;

				ENQUEUE_RENDER_COMMAND(FDynamicMeshSceneProxyInitializeByMaterial)(
					[RenderBuffers](FRHICommandListImmediate& RHICmdList)
					{
						RenderBuffers->Upload();
					});
			}
		}
	}

	void UpdateSectionList(const TArray<int32>& SectionList, const TArray<FLFPVoxelSectionData>& SectionData)
	{
		// remove sets to update
		ENQUEUE_RENDER_COMMAND(FOctreeDynamicMeshSceneProxyUpdatePreClean)(
			[this, SectionList](FRHICommandListImmediate& RHICmdList)
			{
				for (const int32 SetID : SectionList)
				{
					if (RenderBufferSets.IsValidIndex(SetID) && RenderBufferSets[SetID] != nullptr)
					{
						ReleaseRenderBufferSet(RenderBufferSets[SetID]);
						RenderBufferSets[SetID] = nullptr;
					}
				}
			});

		FDynamicMesh3* Mesh = ParentComponent->GetMesh();

		// find suitable overlays
		FDynamicMeshMaterialAttribute* MaterialID = nullptr;
		TArray<const FDynamicMeshUVOverlay*, TInlineAllocator<8>> UVOverlays = { nullptr };
		FDynamicMeshNormalOverlay* NormalOverlay = nullptr;
		FDynamicMeshColorOverlay* ColorOverlay = nullptr;
		if (Mesh->HasAttributes())
		{
			MaterialID = Mesh->Attributes()->GetMaterialID();
			UVOverlays.SetNum(Mesh->Attributes()->NumUVLayers());
			for (int32 k = 0; k < UVOverlays.Num(); ++k)
			{
				UVOverlays[k] = Mesh->Attributes()->GetUVLayer(k);
			}
			NormalOverlay = Mesh->Attributes()->PrimaryNormals();
			ColorOverlay = Mesh->Attributes()->PrimaryColors();
		}

		TUniqueFunction<void(int, int, int, const FVector3f&, FVector3f&, FVector3f&)> TangentsFunc = MakeTangentsFunc();

		{
			TArray<int> Triangles;
			Triangles.Reserve(Mesh->MaxTriangleID() / RenderBufferSets.Num());

			for (const int32 SetID : SectionList)
			{
				if (RenderBufferSets.IsValidIndex(SetID))
				{
					Triangles.Reset();

					FMeshRenderBufferSet* RenderBuffers = AllocateNewRenderBufferSet();
					RenderBuffers->Material = GetMaterial(SetID);

					Triangles = SectionData[SetID].TriangleIndexList.Array();

					InitializeBuffersFromOverlays(RenderBuffers, Mesh,
						Triangles.Num(), Triangles,
						UVOverlays, NormalOverlay, ColorOverlay, TangentsFunc);

					RenderBuffers->Triangles = Triangles;

					ENQUEUE_RENDER_COMMAND(FOctreeDynamicMeshSceneProxyUpdateAddOne)(
						[this, SetID, RenderBuffers](FRHICommandListImmediate& RHICmdList)
						{
							RenderBuffers->Upload();
							RenderBufferSets[SetID] = RenderBuffers;
						});
				}
			}
		}

		return;
	}

	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override
	{
		FPrimitiveViewRelevance Result;

		Result.bDrawRelevance = IsShown(View);
		Result.bShadowRelevance = IsShadowCast(View);
		Result.bDynamicRelevance = true;
		Result.bRenderInMainPass = ShouldRenderInMainPass();
		Result.bUsesLightingChannels = GetLightingChannelMask() != GetDefaultLightingChannelMask();
		Result.bTranslucentSelfShadow = bCastVolumetricTranslucentShadow;
		Result.bRenderCustomDepth = ShouldRenderCustomDepth();
		// Note that this is actually a getter. One may argue that it is poorly named.
		MaterialRelevance.SetPrimitiveViewRelevance(Result);
		Result.bVelocityRelevance = DrawsVelocity() && Result.bOpaque && Result.bRenderInMainPass;

		return Result;
	}

	virtual void UpdatedReferencedMaterials() override
	{
		FBaseDynamicMeshSceneProxy::UpdatedReferencedMaterials();

		// The material relevance may need updating.
		MaterialRelevance = ParentComponent->GetMaterialRelevance(GetScene().GetFeatureLevel());
	}


	virtual void GetLightRelevance(const FLightSceneProxy* LightSceneProxy, bool& bDynamic, bool& bRelevant, bool& bLightMapped, bool& bShadowMapped) const override
	{
		FPrimitiveSceneProxy::GetLightRelevance(LightSceneProxy, bDynamic, bRelevant, bLightMapped, bShadowMapped);
	}

	virtual bool CanBeOccluded() const override
	{
		return !MaterialRelevance.bDisableDepthTest;
	}

	virtual uint32 GetMemoryFootprint(void) const override 
	{ 
		return(sizeof(*this) + GetAllocatedSize()); 
	}

	uint32 GetAllocatedSize(void) const { return(FPrimitiveSceneProxy::GetAllocatedSize()); }

	SIZE_T GetTypeHash() const override
	{
		static size_t UniquePointer;
		return reinterpret_cast<size_t>(&UniquePointer);
	}

private:

	TArray<FMeshRenderBufferSet*> RenderBufferSets;

	FMaterialRelevance MaterialRelevance;

	int32 SectionCount = 1;

public:

	UVoxelDynamicMeshComponent* ParentComponent;
};
