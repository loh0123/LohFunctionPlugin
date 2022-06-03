// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mesh/BaseVoxelMesh.h"
#include "HexagonVoxelMesh.generated.h"

/**
 * 
 */
UCLASS()
class LOHFUNCTIONPLUGIN_API UHexagonVoxelMesh : public UBaseVoxelMesh
{
	GENERATED_BODY()

		friend class HexaVoxelTasker;
	
public:

		void SetupPool(TObjectPtr<UBaseVoxelPool> NewVoxelPool, const FIntVector NewPoolLocation, const int32 NewPoolIndex) override;

	UFUNCTION(BlueprintCallable, Category = "HexagonVoxelMesh | Function")
		void SetupMesh(const FVector MeshSize, const FIntVector GridSize, const TArray<FLFPVoxelGridData>& GridData) override;

	UFUNCTION(BlueprintCallable, Category = "HexagonVoxelMesh | Function")
		void SetVoxelGridData(const FIntVector GridLocation, const FLFPVoxelGridData& GridData, const bool bUpdateMesh = true) override;

	UFUNCTION(BlueprintCallable, Category = "HexagonVoxelMesh | Function")
		void SetVoxelGridDataList(const TArray<FIntVector>& GridLocationList, const TArray<FLFPVoxelGridData>& GridDataList, const bool bUpdateMesh = true) override;

	UFUNCTION(BlueprintCallable, Category = "HexagonVoxelMesh | Function")
		void SetVoxelGridDataListWithSingleData(const TArray<FIntVector>& GridLocationList, const FLFPVoxelGridData& GridData, const bool bUpdateMesh) override;

	UFUNCTION(BlueprintCallable, Category = "HexagonVoxelMesh | Function")
		void SetAllVoxelGridDataWithSingleData(const FLFPVoxelGridData& GridData, const bool bUpdateMesh) override;

	UFUNCTION(BlueprintCallable, Category = "HexagonVoxelMesh | Function")
		void SetVoxelGridAreaData(const int32 OriginGridIndex, const FIntVector Range, const FLFPVoxelGridData& GridData, const bool bUpdateMesh = true);

		void UpdateMesh_Internal() override { if (GetVoxelMeshData().VertexSize.GetMax() == INDEX_NONE) UpdateVertices();  UpdateTriangles(); }

	UFUNCTION(BlueprintCallable, Category = "HexagonVoxelMesh | Function")
		FORCEINLINE void UpdateMesh() { Super::UpdateMesh(); };

protected:

	void UpdateVertices();

	void UpdateTriangles();

	FORCEINLINE void AddHexagonWall(const TArray<int32>& VertexIndexList, FLFPVoxelTriangleUpdateData& UpdateData, const int32 ID);

	FORCEINLINE void AddHexagonRoof(const TArray<int32>& VertexIndexList, FLFPVoxelTriangleUpdateData& UpdateData, const int32 ID);

	FORCEINLINE void FindBlockNeighbour(const FIntVector GridLocation, TArray<FIntVector>& NeighbourLocationList);

	FORCEINLINE void FindBlockVertices(const FIntVector GridLocation, TArray<int32>& VerticesIndexList);

};


//class HexaVoxelTasker : public FNonAbandonableTask
//{
//	friend class FAsyncTask<HexaVoxelTasker>;
//
//public:
//
//	HexaVoxelTasker(TObjectPtr<UHexagonVoxelMesh> Component, TArray<FLFPVoxelTriangleUpdateData>&& DataList) : OwnerComponent(Component), UpdateDataList(DataList) { }
//
//	void DoWork()
//	{
//		AsyncTask(ENamedThreads::GameThread, [&]()
//			{
//				FDynamicMeshChangeInfo ChangeInfo;
//				ChangeInfo.Type = EDynamicMeshChangeType::MeshChange;
//				ChangeInfo.Flags = EDynamicMeshAttributeChangeFlags::Unknown;
//				OwnerComponent->PreMeshChangedEvent.Broadcast(OwnerComponent, ChangeInfo);
//			});
//
//		OwnerComponent->EditMesh([&](FDynamicMesh3& EditMesh)
//			{
//				if (StopTaskerWork) return;
//
//				FLFPVoxelMeshData& MeshData = OwnerComponent->GetVoxelMeshData();
//
//				TArray<TObjectPtr<FDynamicMeshUVOverlay>> UVOverlayList;
//
//				UVOverlayList.SetNum(8);
//
//				for (int32 UVLayerID = 0; UVLayerID < 8; UVLayerID++)
//				{
//					UVOverlayList[UVLayerID] = EditMesh.Attributes()->GetUVLayer(UVLayerID);
//				}
//
//				int32 GroupID = 0;
//
//				TObjectPtr<FDynamicMeshMaterialAttribute> MaterialIDs = EditMesh.Attributes()->GetMaterialID();
//
//				for (auto& UpdateData : UpdateDataList)
//				{
//					if (StopTaskerWork) return;
//
//					if (UpdateData.GridIndex == INDEX_NONE) continue;
//
//					MeshData.TriangleDataList[UpdateData.GridIndex].MeshTriangleIndex.Reserve(UpdateData.NewTriangleList.Num());
//
//					for (int32 TriangleID = 0; TriangleID < UpdateData.NewTriangleList.Num(); TriangleID++)
//					{
//						FIntVector TriVertexIndex;
//
//						TriVertexIndex.X = EditMesh.AppendVertex(MeshData.VerticesList[UpdateData.NewTriangleList[TriangleID].X]);
//						TriVertexIndex.Y = EditMesh.AppendVertex(MeshData.VerticesList[UpdateData.NewTriangleList[TriangleID].Y]);
//						TriVertexIndex.Z = EditMesh.AppendVertex(MeshData.VerticesList[UpdateData.NewTriangleList[TriangleID].Z]);
//
//						const int32 TriIndex = EditMesh.AppendTriangle(TriVertexIndex, UpdateData.NewTriangleGroupList[TriangleID]);
//
//						MeshData.TriangleDataList[UpdateData.GridIndex].MeshTriangleIndex.Add(TriIndex);
//
//						const int32 UVIndex = TriangleID * 3;
//
//						int32 Elem0 = UVOverlayList[0]->AppendElement(UpdateData.NewUVList[UVIndex]);
//						int32 Elem1 = UVOverlayList[0]->AppendElement(UpdateData.NewUVList[UVIndex + 1]);
//						int32 Elem2 = UVOverlayList[0]->AppendElement(UpdateData.NewUVList[UVIndex + 2]);
//						UVOverlayList[0]->SetTriangle(TriIndex, FIndex3i(Elem0, Elem1, Elem2), true);
//
//						for (int32 CustomDataUV = 1; CustomDataUV < FMath::Min(MeshData.GridData[UpdateData.GridIndex].CustomData.Num() + 1, 8); CustomDataUV++)
//						{
//							Elem0 = UVOverlayList[CustomDataUV]->AppendElement(FVector2f(MeshData.GridData[UpdateData.GridIndex].CustomData[CustomDataUV - 1]));
//							Elem1 = UVOverlayList[CustomDataUV]->AppendElement(FVector2f(MeshData.GridData[UpdateData.GridIndex].CustomData[CustomDataUV - 1]));
//							Elem2 = UVOverlayList[CustomDataUV]->AppendElement(FVector2f(MeshData.GridData[UpdateData.GridIndex].CustomData[CustomDataUV - 1]));
//							UVOverlayList[CustomDataUV]->SetTriangle(TriIndex, FIndex3i(Elem0, Elem1, Elem2), true);
//						}
//
//						MaterialIDs->SetValue(TriIndex, MeshData.GridData[UpdateData.GridIndex].MaterialID);
//					}
//				}
//
//				FMeshNormals::InitializeMeshToPerTriangleNormals(&EditMesh);
//
//			}, EDynamicMeshChangeType::MeshChange, EDynamicMeshAttributeChangeFlags::Unknown, true);
//
//		AsyncTask(ENamedThreads::GameThread, [&]()
//			{
//				FDynamicMeshChangeInfo ChangeInfo;
//				ChangeInfo.Type = EDynamicMeshChangeType::MeshChange;
//				ChangeInfo.Flags = EDynamicMeshAttributeChangeFlags::Unknown;
//				OwnerComponent->MeshChangedEvent.Broadcast(OwnerComponent, ChangeInfo);
//				OwnerComponent->MeshModifiedBPEvent.Broadcast(OwnerComponent);
//			});
//
//		return;
//	}
//
//	FORCEINLINE TStatId GetStatId() const { RETURN_QUICK_DECLARE_CYCLE_STAT(HexaVoxelTasker, STATGROUP_ThreadPoolAsyncTasks); }
//
//protected:
//
//	UPROPERTY() TObjectPtr<UHexagonVoxelMesh> OwnerComponent = nullptr;
//
//	UPROPERTY() TArray<FLFPVoxelTriangleUpdateData> UpdateDataList;
//
//public:
//
//	FThreadSafeBool StopTaskerWork = false;
//};