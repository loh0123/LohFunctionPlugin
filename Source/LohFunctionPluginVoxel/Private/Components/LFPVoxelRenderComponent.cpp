// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/LFPVoxelRenderComponent.h"

#include "Components/LFPChunkedTagDataComponent.h"
#include "Components/LFPGridTagDataComponent.h"
#include "Data/LFPGridSetting.h"
#include "Data/LFPVoxelSetting.h"
#include "DynamicMesh/DynamicMeshAABBTree3.h"
#include "DynamicMesh/Operations/MergeCoincidentMeshEdges.h"
#include "Generators/MarchingCubes.h"
#include "Math/LFPGridLibrary.h"
#include "Operations/MeshBevel.h"
#include "Render/LFPRenderLibrary.h"
#include "Runtime/GeometryFramework/Private/Components/DynamicMeshSceneProxy.h"
#include "Selections/GeometrySelectionUtil.h"
#include "Spatial/FastWinding.h"

class ULFPVoxelSetting;

// Sets default values for this component's properties
ULFPVoxelRenderComponent::ULFPVoxelRenderComponent( )
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	VoxelMeshComputeQueue.OnComputeCompleted = [&] ( TUniquePtr< FDynamicMesh3 > NewData )
	{
		OnComputeNewVoxelMesh_Completed(MoveTemp(NewData));
	};
	// ...
}

// Called when the game starts
void ULFPVoxelRenderComponent::BeginPlay( )
{
	Super::BeginPlay();

}

// Called every frame
void ULFPVoxelRenderComponent::TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULFPVoxelRenderComponent::Initialize( class ULFPGridTagDataComponent* NewDataComponent , const int32 NewRegionIndex , const int32 NewChunkIndex )
{
	DataComponent = NewDataComponent;
	RegionIndex   = NewRegionIndex;
	ChunkIndex    = NewChunkIndex;
}

void ULFPVoxelRenderComponent::Uninitialize( )
{
	DataComponent = nullptr;
}

void ULFPVoxelRenderComponent::UpdateVoxel( )
{
	if ( IsValid(DataComponent) == false )
	{
		return;
	}

	const ULFPGridSetting*  GridSetting  = DataComponent->GetGridSetting();
	const ULFPVoxelSetting* VoxelSetting = GridSetting->FindGridFragmentByClass< ULFPVoxelSetting >();

	if ( IsValid(GridSetting) == false || IsValid(VoxelSetting) == false )
	{
		return;
	}

	OnVoxelMeshRebuild.Broadcast();

	const double StartTime = FPlatformTime::Seconds();

	FDynamicMesh3 MeshData;
	{
		MeshData.Clear();

		int32 MaxMaterialIndex = 1;

		const FVector VoxelFullSize = VoxelSetting->GetVoxelSize();

		const FVector VoxelBoundFullSize = VoxelFullSize * FVector(GridSetting->GetDataGridSize());
		const FVector VoxelBoundHalfSize = VoxelBoundFullSize * 0.5f;

		TMap< FIntVector4 , int32 > VertexMapping;

		TArray< FVector >    VertexList;
		TArray< FIntVector > TriangleList;
		TArray< int32 >      GroupID;
		TArray< FVector3f >  NormalList;
		TArray< FVector2f >  UVList;
		TArray< FIntVector > TriangleNormalList;
		TArray< FIntVector > TriangleUVList;
		TArray< int32 >      MaterialIDList;

		int32 FaceGroupID = 1; // Why
		int32 AttribIndex = 0;

		const auto& CreateFace = [&] ( const int32& VoxelIndex , const int32& RotationID , const int32 MaterialID )
		{
			const FIntVector VoxelGridPos = ULFPGridLibrary::ToGridLocation(VoxelIndex, GridSetting->GetDataGridSize());
			const FVector    CenterPos    = FVector(VoxelGridPos) + 0.5f;
			const FRotator   Rotation     = LFPVoxelRenderConstantData::VertexRotationList[RotationID];
			const FVector3f  Normal       = FVector3f(LFPVoxelRenderConstantData::FaceDirection[RotationID].Up);

			/* Handle Tri Data */
			{
				const TArray< FVector > FaceVertexList          = ULFPRenderLibrary::CreateVertexPosList(CenterPos, Rotation, FVector(0.5f));
				const FVector           FaceVertexPosList[2][3] =
					{
						{
							FaceVertexList[1]
							, FaceVertexList[0]
							, FaceVertexList[3]
						}
						, {
							FaceVertexList[2]
							, FaceVertexList[3]
							, FaceVertexList[0]
						}
					};

				for ( int32 FaceIndex = 0 ; FaceIndex < 2 ; ++FaceIndex )
				{
					FIntVector FaceVertexIndexList;

					for ( int32 FaceVertexIndex = 0 ; FaceVertexIndex < 3 ; ++FaceVertexIndex )
					{
						const FVector&    FaceVertexKey  = FaceVertexPosList[FaceIndex][FaceVertexIndex];
						const FVector&    FaceVertexPos  = (FaceVertexKey * VoxelFullSize) - VoxelBoundHalfSize;
						const FIntVector4 VertexKey      = FIntVector4(FMath::RoundToInt32(FaceVertexKey.X), FMath::RoundToInt32(FaceVertexKey.Y), FMath::RoundToInt32(FaceVertexKey.Z), VoxelIndex);
						const int32*      VertexIndexPtr = VertexMapping.Find(VertexKey);

						if ( VertexIndexPtr == nullptr )
						{
							VertexIndexPtr = &VertexMapping.Add(VertexKey, VertexList.Num());
							VertexList.Add(FaceVertexPos);
						}

						FaceVertexIndexList[FaceVertexIndex] = *VertexIndexPtr;
					}

					TriangleList.Add(FaceVertexIndexList);
					GroupID.Add(FaceGroupID);
				}

				FaceGroupID++;
			}

			/* Handle Attribute Data */
			int32 ElementIndexList[4];
			{
				const FVector2f MinUVOffset = FVector2f(0);
				const FVector2f MaxUVOffset = FVector2f(1);

				const FVector2f UVCacheList[4] =
					{
						FVector2f(MinUVOffset.X, MinUVOffset.Y)
						, FVector2f(MaxUVOffset.X, MinUVOffset.Y)
						, FVector2f(MinUVOffset.X, MaxUVOffset.Y)
						, FVector2f(MaxUVOffset.X, MaxUVOffset.Y)
					};

				for ( int32 ElementIndex = 0 ; ElementIndex < 4 ; ++ElementIndex )
				{
					ElementIndexList[ElementIndex] = AttribIndex;
					UVList.Add(UVCacheList[ElementIndex]);
					NormalList.Add(Normal);
					AttribIndex += 1;
				}
			}

			/* Handle UV Triangle Data */
			{
				TriangleUVList.Add(FIntVector(ElementIndexList[0], ElementIndexList[2], ElementIndexList[1]));
				TriangleUVList.Add(FIntVector(ElementIndexList[3], ElementIndexList[1], ElementIndexList[2]));
			}

			/* Handle Normal Triangle Data */
			{
				TriangleNormalList.Add(FIntVector(ElementIndexList[0], ElementIndexList[2], ElementIndexList[1]));
				TriangleNormalList.Add(FIntVector(ElementIndexList[3], ElementIndexList[1], ElementIndexList[2]));
			}

			/* Handle Material Data */
			{
				MaterialIDList.Add(MaterialID);
				MaterialIDList.Add(MaterialID);
			}
		};

		/* Generate Voxel Mesh Data */
		for ( int32 VoxelIndex = 0 ; VoxelIndex < GridSetting->GetDataIndexSize() ; ++VoxelIndex )
		{
			const FGameplayTag& SelfVoxelTag = DataComponent->GetDataTag(RegionIndex, ChunkIndex, VoxelIndex);

			if ( SelfVoxelTag.MatchesTag(HandleTag) )
			{
				for ( int32 FaceDirectionIndex = 0 ; FaceDirectionIndex < 6 ; ++FaceDirectionIndex )
				{
					const FIntVector& TargetIndex = DataComponent->AddOffsetToGridIndex(FIntVector(RegionIndex, ChunkIndex, VoxelIndex), LFPVoxelRenderConstantData::FaceDirection[FaceDirectionIndex].Up);

					/** Check Do We Ignore Border Data And Always Fill The Face */
					const bool bForceRender = (VoxelSetting->IsChunkFaceCullingDisable() && ChunkIndex != TargetIndex.Y) || (VoxelSetting->IsRegionFaceCullingDisable() && RegionIndex != TargetIndex.X) || TargetIndex == FIntVector::NoneValue;

					const FGameplayTag& TargetVoxelTag = bForceRender
						                                     ? FGameplayTag::EmptyTag
						                                     : DataComponent->GetDataTag(TargetIndex.X, TargetIndex.Y, TargetIndex.Z);

					if ( TargetVoxelTag.MatchesTag(HandleTag) == false )
					{
						// TODO : Render Water
						CreateFace(VoxelIndex, FaceDirectionIndex, 0);
					}
				}
			}
		}

		/* Apply Voxel Mesh Data */
		{
			MeshData.EnableTriangleGroups();

			for ( const FVector& VertexData : VertexList )
			{
				MeshData.AppendVertex(VertexData);
			}

			check(TriangleList.Num() == GroupID.Num());

			for ( int32 TriangleIndex = 0 ; TriangleIndex < TriangleList.Num() ; ++TriangleIndex )
			{
				const int32 TriCode = MeshData.AppendTriangle(TriangleList[TriangleIndex], GroupID[TriangleIndex]);

				check(TriCode == TriangleIndex);
			}

			MeshData.EnableAttributes();
			MeshData.Attributes()->EnableMaterialID();

			UE::Geometry::FDynamicMeshUVOverlay*         UVOverlay       = MeshData.Attributes()->PrimaryUV();
			UE::Geometry::FDynamicMeshNormalOverlay*     NormalOverlay   = MeshData.Attributes()->PrimaryNormals();
			UE::Geometry::FDynamicMeshMaterialAttribute* MaterialOverlay = MeshData.Attributes()->GetMaterialID();

			for ( int i = 0 ; i < UVList.Num() ; ++i )
			{
				UVOverlay->AppendElement(UVList[i]);
			}

			for ( int i = 0 ; i < NormalList.Num() ; ++i )
			{
				NormalOverlay->AppendElement(NormalList[i]);
			}

			check(TriangleUVList.Num() == TriangleList.Num());
			check(TriangleNormalList.Num() == TriangleList.Num());

			for ( int i = 0 ; i < TriangleList.Num() ; ++i )
			{
				UVOverlay->SetTriangle(i, TriangleUVList[i]);
				NormalOverlay->SetTriangle(i, TriangleNormalList[i]);
			}

			for ( int i = 0 ; i < MaterialIDList.Num() ; ++i )
			{
				MaterialOverlay->SetValue(i, MaterialIDList[i]);
			}
		}
	}

	VoxelMeshComputeQueue.LaunchJob(TEXT("VoxelDynamicMeshGenerator"),
	                                [this, StartTime, TempBevelSize = BevelSize , MovedMeshDta = MoveTemp(MeshData)] ( FProgressCancel& Progress )
	                                {
		                                TUniquePtr< FDynamicMesh3 > MeshPtr = MakeUnique< FDynamicMesh3 >(MovedMeshDta);
		                                ComputeNewVoxelMesh_TaskFunction(Progress, *MeshPtr, TempBevelSize);

		                                UE_LOG(LogTemp, Warning, TEXT("UpdateVoxel Generate Time Use : %f"), (float)(FPlatformTime::Seconds() - StartTime));
		                                return MeshPtr;
	                                });
}

void ULFPVoxelRenderComponent::RebuildPhysicsData( )
{
	if ( IsValid(DataComponent) == false )
	{
		Super::RebuildPhysicsData();

		return;
	}

	{
		const double StartTime = FPlatformTime::Seconds();

		const ULFPGridSetting*  GridSetting  = DataComponent->GetGridSetting();
		const ULFPVoxelSetting* VoxelSetting = GridSetting->FindGridFragmentByClass< ULFPVoxelSetting >();

		const FVector VoxelFullSize = VoxelSetting->GetVoxelSize();
		const FVector VoxelHalfSize = VoxelFullSize * 0.5f;

		const FVector VoxelBoundFullSize = VoxelFullSize * FVector(GridSetting->GetDataGridSize());
		const FVector VoxelBoundHalfSize = VoxelBoundFullSize * 0.5f;

		TMap< FIntVector , FIntVector > BatchDataMap;

		TPair< FIntVector , FIntVector > CurrentBatchData(INDEX_NONE, INDEX_NONE);

		bool IsBatchValid = false;

		const auto& PushData = [&]( )
		{
			{
				const FIntVector  TargetMax    = CurrentBatchData.Key - FIntVector(0, 1, 0);
				const FIntVector* TargetMinPtr = BatchDataMap.Find(TargetMax);

				if ( TargetMinPtr != nullptr && TargetMinPtr->X == CurrentBatchData.Value.X && TargetMinPtr->Z == CurrentBatchData.Value.Z )
				{
					const FIntVector TargetMin = BatchDataMap.FindAndRemoveChecked(TargetMax);

					CurrentBatchData.Value.Y = TargetMin.Y;
				}
			}

			{
				const FIntVector  TargetMax    = CurrentBatchData.Key - FIntVector(0, 0, 1);
				const FIntVector* TargetMinPtr = BatchDataMap.Find(TargetMax);

				if ( TargetMinPtr != nullptr && TargetMinPtr->X == CurrentBatchData.Value.X && TargetMinPtr->Y == CurrentBatchData.Value.Y )
				{
					const FIntVector TargetMin = BatchDataMap.FindAndRemoveChecked(TargetMax);

					CurrentBatchData.Value.Z = TargetMin.Z;
				}
			}

			BatchDataMap.Add(CurrentBatchData.Key, CurrentBatchData.Value);
			IsBatchValid = false;
		};

		/** Generate Batch Data Map */
		for ( int32 Z = 0 ; Z < GridSetting->GetDataGridSize().Z ; Z++ )
		{
			for ( int32 Y = 0 ; Y < GridSetting->GetDataGridSize().Y ; Y++ )
			{
				for ( int32 X = 0 ; X < GridSetting->GetDataGridSize().X ; X++ )
				{
					/***************** Identify Data *****************/
					const FIntVector CurrentPos(X, Y, Z);

					const int32 CurrentIndex = ULFPGridLibrary::ToGridIndex(CurrentPos, GridSetting->GetDataGridSize());

					const FGameplayTag& SelfVoxelTag = DataComponent->GetDataTag(RegionIndex, ChunkIndex, CurrentIndex);

					/*************************************************/

					if ( SelfVoxelTag.MatchesTag(HandleTag) )
					{
						if ( (CurrentBatchData.Key.Y != Y || CurrentBatchData.Key.Z != Z) && IsBatchValid )
						{
							PushData();
						}

						if ( IsBatchValid )
						{
							CurrentBatchData.Key.X += 1;
						}
						else
						{
							CurrentBatchData.Key   = CurrentPos;
							CurrentBatchData.Value = CurrentPos;
							IsBatchValid           = true;
						}
					}
					else if ( IsBatchValid )
					{
						PushData();
					}
				}
			}
		}

		if ( IsBatchValid )
		{
			PushData();
		}

		AggGeom.BoxElems.Empty();

		/** Add To Result */
		for ( const auto& BatchData : BatchDataMap )
		{
			const FVector MinPos = FVector(BatchData.Value) * VoxelFullSize;
			const FVector MaxPos = FVector(BatchData.Key + FIntVector(1)) * VoxelFullSize;
			const FVector Scale  = (MaxPos - MinPos);
			const FVector Center = FMath::Lerp(MinPos, MaxPos, 0.5f) - VoxelBoundHalfSize;

			FKBoxElem CurrentBoxElem(Scale.X, Scale.Y, Scale.Z);

			CurrentBoxElem.Center = Center;

			AggGeom.BoxElems.Add(CurrentBoxElem);
		}

		UE_LOG(LogTemp, Warning, TEXT("Collision Generate Time Use : %f"), (float)(FPlatformTime::Seconds() - StartTime));
	}

	Super::RebuildPhysicsData();
}

void ULFPVoxelRenderComponent::UpdateDistanceField( )
{
	if ( DistanceFieldMode == EDynamicMeshComponentDistanceFieldMode::NoDistanceField )
	{
		FScopeLock Lock(&DistanceFieldLock);
		CurrentDistanceField = TSharedPtr< FDistanceFieldVolumeData >();
		if ( GetCurrentSceneProxy() != nullptr )
		{
			GetCurrentSceneProxy()->SetNewDistanceField(CurrentDistanceField, false);
		}
		return;
	}

	// For safety, run the distance field compute on a (geometry-only) copy of the mesh
	FDynamicMesh3 GeoOnlyCopy;
	// Compute whether the mesh uses mainly two-sided materials before, as this is the only info the distance field compute needs from the mesh attributes
	bool bMostlyTwoSided = false;
	ProcessMesh([&] ( const FDynamicMesh3& ReadMesh )
	{
		if ( ReadMesh.Attributes() && ReadMesh.Attributes()->GetMaterialID() )
		{
			TArray< bool > MatIsTwoSided;
			MatIsTwoSided.SetNumUninitialized(BaseMaterials.Num());
			for ( int32 Idx = 0 ; Idx < BaseMaterials.Num() ; ++Idx )
			{
				MatIsTwoSided[Idx] = BaseMaterials[Idx]
					                     ? BaseMaterials[Idx]->IsTwoSided()
					                     : false;
			}
			const UE::Geometry::FDynamicMeshMaterialAttribute* Materials        = ReadMesh.Attributes()->GetMaterialID();
			int32                                              TwoSidedTriCount = 0;
			for ( int32 TID : ReadMesh.TriangleIndicesItr() )
			{
				int32 MID = Materials->GetValue(TID);
				TwoSidedTriCount += MatIsTwoSided.IsValidIndex(MID)
					                    ? static_cast< int32 >(MatIsTwoSided[MID])
					                    : 0;
			}
			bMostlyTwoSided = TwoSidedTriCount * 2 >= ReadMesh.TriangleCount();
		}

		GeoOnlyCopy.Copy(ReadMesh, false, false, false, false);
	});
	DistanceFieldComputeQueue.LaunchJob(TEXT("VoxelDynamicMeshComponentDistanceField"),
	                                    [this, MovedGeoOnlyCopy = MoveTemp(GeoOnlyCopy), bMostlyTwoSided] ( FProgressCancel& Progress )
	                                    {
		                                    return ComputeNewDistanceField_TaskFunctionV2(Progress, MovedGeoOnlyCopy, bMostlyTwoSided);
	                                    });
}

void ULFPVoxelRenderComponent::ComputeNewVoxelMesh_TaskFunction( FProgressCancel& Progress , FDynamicMesh3& Mesh , const float CurrentBevelSize ) const
{
	if ( Progress.Cancelled() ) { return; }

	UE::Geometry::FMergeCoincidentMeshEdges Welder(&Mesh);
	Welder.MergeVertexTolerance = 0.5f;
	Welder.OnlyUniquePairs      = false;

	if ( Welder.Apply() == false )
	{
		return;
	}

	if ( Progress.Cancelled() ) { return; }

	TArray< int32 > Edges;
	{
		TSet< int32 > UniqueEdges;

		constexpr float MinAngleDeg = 20.0f;
		double          CosThresh   = FMath::Cos(FMathd::DegToRad * MinAngleDeg);

		for ( int32 EID : Mesh.EdgeIndicesItr() )
		{
			UE::Geometry::FIndex2i EdgeT = Mesh.GetEdgeT(EID);
			if ( EdgeT.B == INDEX_NONE )
			{
				continue;
			}
			FVector3d NormalA = Mesh.GetTriNormal(EdgeT.A);
			FVector3d NormalB = Mesh.GetTriNormal(EdgeT.B);
			if ( NormalA.Dot(NormalB) <= CosThresh )
			{
				UniqueEdges.Add(EID);
			}
		}

		Edges = UniqueEdges.Array();
	}

	if ( Progress.Cancelled() ) { return; }

	{
		UE::Geometry::FMeshBevel Bevel;
		Bevel.InsetDistance         = CurrentBevelSize;
		Bevel.MaterialIDMode        = UE::Geometry::FMeshBevel::EMaterialIDMode::InferMaterialID;
		Bevel.SetConstantMaterialID = 0;
		Bevel.NumSubdivisions       = 1;
		Bevel.RoundWeight           = 1.0f;

		// Note: Using group junctions as corner vertices tends to help the bevel match the result of a similar polygroup bevel in the UI
		// (though is often very similar to the no-corner bevel; necessary corners where more than 2 selected edges meet are automatically detected)
		Bevel.InitializeFromTriangleEdges(Mesh, Edges, [&Mesh] ( int32 VID )
		{
			return Mesh.IsGroupJunctionVertex(VID);
		});

		Bevel.Apply(Mesh, nullptr);
	}
}

void ULFPVoxelRenderComponent::OnComputeNewVoxelMesh_Completed( TUniquePtr< FDynamicMesh3 > NewMeshData )
{
	AsyncTask(
		ENamedThreads::GameThread,
		[this, MovedMeshData = MoveTemp(*NewMeshData.Release())]( )
		{
			EditMesh([&] ( FDynamicMesh3& MeshData )
			{
				MeshData = MovedMeshData;
			});

			OnVoxelMeshGenerated.Broadcast();
		}
		);
}

TUniquePtr< FDistanceFieldVolumeData > ULFPVoxelRenderComponent::ComputeNewDistanceField_TaskFunctionV2( FProgressCancel& Progress , const FDynamicMesh3& Mesh , bool bMostlyTwoSided ) const
{
	if ( Progress.Cancelled() )
	{
		return nullptr;
	}

	TUniquePtr< FDistanceFieldVolumeData > NewDistanceField =
		ComputeDistanceFieldForMesh(Mesh, Progress, bMostlyTwoSided);
	return NewDistanceField;
}

bool ULFPVoxelRenderComponent::DynamicMesh_GenerateSignedDistanceFieldVolumeData( const FDynamicMesh3& Mesh , bool bGenerateAsIfTwoSided , FDistanceFieldVolumeData& VolumeDataOut , FProgressCancel& Progress ) const
{
	TRACE_CPUPROFILER_EVENT_SCOPE(DynamicMesh_GenerateSignedDistanceFieldVolumeData);

	if ( DoesProjectSupportDistanceFields() == false )
	{
		return false;
	}

	if ( DistanceFieldResolutionScale <= 0 )
	{
		return false;
	}

	const double StartTime = FPlatformTime::Seconds();

	UE::Geometry::FDynamicMeshAABBTree3 Spatial(&Mesh, true);
	if ( Progress.Cancelled() ) { return false; }
	UE::Geometry::FAxisAlignedBox3d                 MeshBounds = Spatial.GetBoundingBox();
	UE::Geometry::TFastWindingTree< FDynamicMesh3 > WindingTree(&Spatial, true);
	if ( Progress.Cancelled() ) { return false; }

	static const auto CVar       = IConsoleManager::Get().FindTConsoleVariableDataInt(TEXT("r.DistanceFields.MaxPerMeshResolution"));
	const int32       PerMeshMax = CVar->GetValueOnAnyThread();

	// Meshes with explicit artist-specified scale can go higher
	const int32 MaxNumBlocksOneDim = FMath::Min< int32 >(FMath::DivideAndRoundNearest(DistanceFieldResolutionScale <= 1
		                                                                                  ? PerMeshMax / 2
		                                                                                  : PerMeshMax, DistanceField::UniqueDataBrickSize), DistanceField::MaxIndirectionDimension - 1);

	static const auto CVarDensity  = IConsoleManager::Get().FindTConsoleVariableDataFloat(TEXT("r.DistanceFields.DefaultVoxelDensity"));
	const float       VoxelDensity = CVarDensity->GetValueOnAnyThread();

	const float NumVoxelsPerLocalSpaceUnit = VoxelDensity * DistanceFieldResolutionScale;
	FBox3f      LocalSpaceMeshBounds       = (FBox3f)MeshBounds;

	// Make sure the mesh bounding box has positive extents to handle planes
	{
		FVector3f MeshBoundsCenter = LocalSpaceMeshBounds.GetCenter();
		FVector3f MeshBoundsExtent = FVector3f::Max(LocalSpaceMeshBounds.GetExtent(), FVector3f(1.0f, 1.0f, 1.0f));
		LocalSpaceMeshBounds.Min   = MeshBoundsCenter - MeshBoundsExtent;
		LocalSpaceMeshBounds.Max   = MeshBoundsCenter + MeshBoundsExtent;
	}

	// We sample on voxel corners and use central differencing for gradients, so a box mesh using two-sided materials whose vertices lie on LocalSpaceMeshBounds produces a zero gradient on intersection
	// Expand the mesh bounds by a fraction of a voxel to allow room for a pullback on the hit location for computing the gradient.
	// Only expand for two sided meshes as this adds significant Mesh SDF tracing cost
	if ( bGenerateAsIfTwoSided )
	{
		const FVector3f  DesiredDimensions         = FVector3f(LocalSpaceMeshBounds.GetSize() * FVector3f(NumVoxelsPerLocalSpaceUnit / (float)DistanceField::UniqueDataBrickSize));
		const FIntVector Mip0IndirectionDimensions = FIntVector(
			FMath::Clamp(FMath::RoundToInt(DesiredDimensions.X), 1, MaxNumBlocksOneDim),
			FMath::Clamp(FMath::RoundToInt(DesiredDimensions.Y), 1, MaxNumBlocksOneDim),
			FMath::Clamp(FMath::RoundToInt(DesiredDimensions.Z), 1, MaxNumBlocksOneDim));

		const float     CentralDifferencingExpandInVoxels = .25f;
		const FVector3f TexelObjectSpaceSize              = LocalSpaceMeshBounds.GetSize() / FVector3f(Mip0IndirectionDimensions * DistanceField::UniqueDataBrickSize - FIntVector(2 * CentralDifferencingExpandInVoxels));
		LocalSpaceMeshBounds                              = LocalSpaceMeshBounds.ExpandBy(TexelObjectSpaceSize);
	}

	// The tracing shader uses a Volume space that is normalized by the maximum extent, to keep Volume space within [-1, 1], we must match that behavior when encoding
	const float LocalToVolumeScale = 1.0f / LocalSpaceMeshBounds.GetExtent().GetMax();

	const FVector3f  DesiredDimensions         = FVector3f(LocalSpaceMeshBounds.GetSize() * FVector3f(NumVoxelsPerLocalSpaceUnit / (float)DistanceField::UniqueDataBrickSize));
	const FIntVector Mip0IndirectionDimensions = FIntVector(
		FMath::Clamp(FMath::RoundToInt(DesiredDimensions.X), 1, MaxNumBlocksOneDim),
		FMath::Clamp(FMath::RoundToInt(DesiredDimensions.Y), 1, MaxNumBlocksOneDim),
		FMath::Clamp(FMath::RoundToInt(DesiredDimensions.Z), 1, MaxNumBlocksOneDim));

	TArray< uint8 > StreamableMipData;

	struct FDistanceFieldBrick
	{
		FDistanceFieldBrick(
			float      InLocalSpaceTraceDistance ,
			FBox3f     InVolumeBounds ,
			float      InLocalToVolumeScale ,
			FVector2f  InDistanceFieldToVolumeScaleBias ,
			FIntVector InBrickCoordinate ,
			FIntVector InIndirectionSize ) :
			LocalSpaceTraceDistance(InLocalSpaceTraceDistance),
			VolumeBounds(InVolumeBounds),
			LocalToVolumeScale(InLocalToVolumeScale),
			DistanceFieldToVolumeScaleBias(InDistanceFieldToVolumeScaleBias),
			BrickCoordinate(InBrickCoordinate),
			IndirectionSize(InIndirectionSize),
			BrickMaxDistance(MIN_uint8),
			BrickMinDistance(MAX_uint8)
		{
		}

		float      LocalSpaceTraceDistance;
		FBox3f     VolumeBounds;
		float      LocalToVolumeScale;
		FVector2f  DistanceFieldToVolumeScaleBias;
		FIntVector BrickCoordinate;
		FIntVector IndirectionSize;

		// Output
		uint8           BrickMaxDistance;
		uint8           BrickMinDistance;
		TArray< uint8 > DistanceFieldVolume;
	};

	for ( int32 MipIndex = 0 ; MipIndex < DistanceField::NumMips ; MipIndex++ )
	{
		if ( Progress.Cancelled() ) { return false; }

		const FIntVector IndirectionDimensions = FIntVector(
			FMath::DivideAndRoundUp(Mip0IndirectionDimensions.X, 1 << MipIndex),
			FMath::DivideAndRoundUp(Mip0IndirectionDimensions.Y, 1 << MipIndex),
			FMath::DivideAndRoundUp(Mip0IndirectionDimensions.Z, 1 << MipIndex));

		// Expand to guarantee one voxel border for gradient reconstruction using bilinear filtering
		const FVector3f TexelObjectSpaceSize      = LocalSpaceMeshBounds.GetSize() / FVector3f(IndirectionDimensions * DistanceField::UniqueDataBrickSize - FIntVector(2 * DistanceField::MeshDistanceFieldObjectBorder));
		const FBox3f    DistanceFieldVolumeBounds = LocalSpaceMeshBounds.ExpandBy(TexelObjectSpaceSize);

		const FVector3f IndirectionVoxelSize   = DistanceFieldVolumeBounds.GetSize() / FVector3f(IndirectionDimensions);
		const float     IndirectionVoxelRadius = IndirectionVoxelSize.Size();

		const FVector3f VolumeSpaceDistanceFieldVoxelSize = IndirectionVoxelSize * LocalToVolumeScale / FVector3f(DistanceField::UniqueDataBrickSize);
		const float     MaxDistanceForEncoding            = VolumeSpaceDistanceFieldVoxelSize.Size() * DistanceField::BandSizeInVoxels;
		const float     LocalSpaceTraceDistance           = MaxDistanceForEncoding / LocalToVolumeScale;
		const FVector2f DistanceFieldToVolumeScaleBias(2.0f * MaxDistanceForEncoding, -MaxDistanceForEncoding);

		TArray< FDistanceFieldBrick > BricksToCompute;
		BricksToCompute.Reserve(IndirectionDimensions.X * IndirectionDimensions.Y * IndirectionDimensions.Z / 8);
		for ( int32 ZIndex = 0 ; ZIndex < IndirectionDimensions.Z ; ZIndex++ )
		{
			for ( int32 YIndex = 0 ; YIndex < IndirectionDimensions.Y ; YIndex++ )
			{
				for ( int32 XIndex = 0 ; XIndex < IndirectionDimensions.X ; XIndex++ )
				{
					BricksToCompute.Emplace(
						LocalSpaceTraceDistance,
						DistanceFieldVolumeBounds,
						LocalToVolumeScale,
						DistanceFieldToVolumeScaleBias,
						FIntVector(XIndex, YIndex, ZIndex),
						IndirectionDimensions);
				}
			}
		}

		if ( Progress.Cancelled() ) { return false; }

		// compute bricks now
		ParallelFor(BricksToCompute.Num(), [&] ( const int32 BrickIndex )
		            //for ( FDistanceFieldBrick& Brick : BricksToCompute )
		            {
			            FDistanceFieldBrick& Brick                     = BricksToCompute[BrickIndex];
			            const FVector3f      BrickIndirectionVoxelSize = Brick.VolumeBounds.GetSize() / FVector3f(Brick.IndirectionSize);
			            const FVector3f      DistanceFieldVoxelSize    = BrickIndirectionVoxelSize / FVector3f(DistanceField::UniqueDataBrickSize);
			            const FVector3f      BrickMinPosition          = Brick.VolumeBounds.Min + FVector3f(Brick.BrickCoordinate) * BrickIndirectionVoxelSize;

			            Brick.DistanceFieldVolume.Empty(DistanceField::BrickSize * DistanceField::BrickSize * DistanceField::BrickSize);
			            Brick.DistanceFieldVolume.AddZeroed(DistanceField::BrickSize * DistanceField::BrickSize * DistanceField::BrickSize);

			            for ( int32 ZIndex = 0 ; ZIndex < DistanceField::BrickSize ; ZIndex++ )
			            {
				            if ( Progress.Cancelled() ) { return; }

				            for ( int32 YIndex = 0 ; YIndex < DistanceField::BrickSize ; YIndex++ )
				            {
					            if ( Progress.Cancelled() ) { return; }

					            for ( int32 XIndex = 0 ; XIndex < DistanceField::BrickSize ; XIndex++ )
					            {
						            const FVector3f VoxelPosition = FVector3f(XIndex, YIndex, ZIndex) * DistanceFieldVoxelSize + BrickMinPosition;
						            const int32     Index         = (ZIndex * DistanceField::BrickSize * DistanceField::BrickSize + YIndex * DistanceField::BrickSize + XIndex);

						            float MinLocalSpaceDistance = LocalSpaceTraceDistance;

						            double NearestDistSqr    = 0;
						            int32  NearestTriangleID = Spatial.FindNearestTriangle((FVector3d)VoxelPosition, NearestDistSqr,
						                                                                  UE::Geometry::IMeshSpatial::FQueryOptions(LocalSpaceTraceDistance));
						            if ( NearestTriangleID != IndexConstants::InvalidID )
						            {
							            const float ClosestDistance = FMath::Sqrt(NearestDistSqr);
							            MinLocalSpaceDistance       = FMath::Min(MinLocalSpaceDistance, ClosestDistance);

							            // found closest point within search radius
							            double IsoThreshold = 0.5;
							            bool   bInside      = WindingTree.IsInside((FVector3d)VoxelPosition, 0.5);
							            if ( bInside )
							            {
								            MinLocalSpaceDistance *= -1;
							            }
						            }
						            else
						            {
							            // no closest point...
							            MinLocalSpaceDistance = LocalSpaceTraceDistance;
						            }

						            // Transform to the tracing shader's Volume space
						            const float VolumeSpaceDistance = MinLocalSpaceDistance * LocalToVolumeScale;
						            // Transform to the Distance Field texture's space
						            const float RescaledDistance = (VolumeSpaceDistance - DistanceFieldToVolumeScaleBias.Y) / DistanceFieldToVolumeScaleBias.X;
						            check(DistanceField::DistanceFieldFormat == PF_G8);
						            const uint8 QuantizedDistance    = FMath::Clamp< int32 >(FMath::FloorToInt(RescaledDistance * 255.0f + .5f), 0, 255);
						            Brick.DistanceFieldVolume[Index] = QuantizedDistance;
						            Brick.BrickMaxDistance           = FMath::Max(Brick.BrickMaxDistance, QuantizedDistance);
						            Brick.BrickMinDistance           = FMath::Min(Brick.BrickMinDistance, QuantizedDistance);

					            } // X iteration 
				            }     // Y iteration
			            }         // Z iteration

		            }, EParallelForFlags::Unbalanced); // Bricks iteration

		if ( Progress.Cancelled() ) { return false; }

		FSparseDistanceFieldMip& OutMip = VolumeDataOut.Mips[MipIndex];
		TArray< uint32 >         IndirectionTable;
		IndirectionTable.Empty(IndirectionDimensions.X * IndirectionDimensions.Y * IndirectionDimensions.Z);
		IndirectionTable.AddUninitialized(IndirectionDimensions.X * IndirectionDimensions.Y * IndirectionDimensions.Z);

		for ( int32 i = 0 ; i < IndirectionTable.Num() ; i++ )
		{
			IndirectionTable[i] = DistanceField::InvalidBrickIndex;
		}

		TArray< FDistanceFieldBrick* > ValidBricks;
		ValidBricks.Reserve(BricksToCompute.Num());

		for ( int32 k = 0 ; k < BricksToCompute.Num() ; k++ )
		{
			const FDistanceFieldBrick& ComputedBrick = BricksToCompute[k];
			if ( ComputedBrick.BrickMinDistance < MAX_uint8 && ComputedBrick.BrickMaxDistance > MIN_uint8 )
			{
				ValidBricks.Add(&BricksToCompute[k]);
			}
		}

		const uint32 NumBricks      = ValidBricks.Num();
		const uint32 BrickSizeBytes = DistanceField::BrickSize * DistanceField::BrickSize * DistanceField::BrickSize * GPixelFormats[DistanceField::DistanceFieldFormat].BlockBytes;

		TArray< uint8 > DistanceFieldBrickData;
		DistanceFieldBrickData.Empty(BrickSizeBytes * NumBricks);
		DistanceFieldBrickData.AddUninitialized(BrickSizeBytes * NumBricks);

		if ( Progress.Cancelled() ) { return false; }

		for ( int32 BrickIndex = 0 ; BrickIndex < ValidBricks.Num() ; BrickIndex++ )
		{
			const FDistanceFieldBrick& Brick            = *ValidBricks[BrickIndex];
			const int32                IndirectionIndex = ComputeLinearVoxelIndex(Brick.BrickCoordinate, IndirectionDimensions);
			IndirectionTable[IndirectionIndex]          = BrickIndex;

			check(BrickSizeBytes == Brick.DistanceFieldVolume.Num() * Brick.DistanceFieldVolume.GetTypeSize());
			FPlatformMemory::Memcpy(&DistanceFieldBrickData[BrickIndex * BrickSizeBytes], Brick.DistanceFieldVolume.GetData(), Brick.DistanceFieldVolume.Num() * Brick.DistanceFieldVolume.GetTypeSize());
		}

		const int32 IndirectionTableBytes = IndirectionTable.Num() * IndirectionTable.GetTypeSize();
		const int32 MipDataBytes          = IndirectionTableBytes + DistanceFieldBrickData.Num();

		if ( MipIndex == DistanceField::NumMips - 1 )
		{
			VolumeDataOut.AlwaysLoadedMip.Empty(MipDataBytes);
			VolumeDataOut.AlwaysLoadedMip.AddUninitialized(MipDataBytes);

			FPlatformMemory::Memcpy(&VolumeDataOut.AlwaysLoadedMip[0], IndirectionTable.GetData(), IndirectionTableBytes);

			if ( DistanceFieldBrickData.Num() > 0 )
			{
				FPlatformMemory::Memcpy(&VolumeDataOut.AlwaysLoadedMip[IndirectionTableBytes], DistanceFieldBrickData.GetData(), DistanceFieldBrickData.Num());
			}
		}
		else
		{
			OutMip.BulkOffset = StreamableMipData.Num();
			StreamableMipData.AddUninitialized(MipDataBytes);
			OutMip.BulkSize = StreamableMipData.Num() - OutMip.BulkOffset;
			checkf(OutMip.BulkSize > 0, TEXT("DynamicMeshComponent - BulkSize was 0 with %ux%ux%u indirection"), IndirectionDimensions.X, IndirectionDimensions.Y, IndirectionDimensions.Z);

			FPlatformMemory::Memcpy(&StreamableMipData[OutMip.BulkOffset], IndirectionTable.GetData(), IndirectionTableBytes);

			if ( DistanceFieldBrickData.Num() > 0 )
			{
				FPlatformMemory::Memcpy(&StreamableMipData[OutMip.BulkOffset + IndirectionTableBytes], DistanceFieldBrickData.GetData(), DistanceFieldBrickData.Num());
			}
		}

		if ( Progress.Cancelled() ) { return false; }

		OutMip.IndirectionDimensions          = IndirectionDimensions;
		OutMip.DistanceFieldToVolumeScaleBias = DistanceFieldToVolumeScaleBias;
		OutMip.NumDistanceFieldBricks         = NumBricks;

		// Account for the border voxels we added
		const FVector3f VirtualUVMin  = FVector3f(DistanceField::MeshDistanceFieldObjectBorder) / FVector3f(IndirectionDimensions * DistanceField::UniqueDataBrickSize);
		const FVector3f VirtualUVSize = FVector3f(IndirectionDimensions * DistanceField::UniqueDataBrickSize - FIntVector(2 * DistanceField::MeshDistanceFieldObjectBorder)) / FVector3f(IndirectionDimensions * DistanceField::UniqueDataBrickSize);

		const FVector3f VolumePositionExtent = LocalSpaceMeshBounds.GetExtent() * LocalToVolumeScale;

		// [-VolumePositionExtent, VolumePositionExtent] -> [VirtualUVMin, VirtualUVMin + VirtualUVSize]
		OutMip.VolumeToVirtualUVScale = VirtualUVSize / (2 * VolumePositionExtent);
		OutMip.VolumeToVirtualUVAdd   = VolumePositionExtent * OutMip.VolumeToVirtualUVScale + VirtualUVMin;
	}

	VolumeDataOut.bMostlyTwoSided      = bGenerateAsIfTwoSided;
	VolumeDataOut.LocalSpaceMeshBounds = LocalSpaceMeshBounds;

	if ( Progress.Cancelled() ) { return false; }

	VolumeDataOut.StreamableMips.Lock(LOCK_READ_WRITE);
	uint8* Ptr = (uint8*)VolumeDataOut.StreamableMips.Realloc(StreamableMipData.Num());
	FMemory::Memcpy(Ptr, StreamableMipData.GetData(), StreamableMipData.Num());
	VolumeDataOut.StreamableMips.Unlock();
	VolumeDataOut.StreamableMips.SetBulkDataFlags(BULKDATA_Force_NOT_InlinePayload);

	const float BuildTime = (float)(FPlatformTime::Seconds() - StartTime);

	UE_LOG(LogGeometry, Log, TEXT("DynamicMeshComponent - Finished distance field build in %.1fs - %ux%ux%u sparse distance field, %.1fMb total, %.1fMb always loaded, %u%% occupied, %u triangles"),
	       BuildTime,
	       Mip0IndirectionDimensions.X * DistanceField::UniqueDataBrickSize,
	       Mip0IndirectionDimensions.Y * DistanceField::UniqueDataBrickSize,
	       Mip0IndirectionDimensions.Z * DistanceField::UniqueDataBrickSize,
	       (VolumeDataOut.GetResourceSizeBytes() + VolumeDataOut.StreamableMips.GetBulkDataSize()) / 1024.0f / 1024.0f,
	       (VolumeDataOut.AlwaysLoadedMip.GetAllocatedSize()) / 1024.0f / 1024.0f,
	       FMath::RoundToInt(100.0f * VolumeDataOut.Mips[0].NumDistanceFieldBricks / (float)(Mip0IndirectionDimensions.X * Mip0IndirectionDimensions.Y * Mip0IndirectionDimensions.Z)),
	       Mesh.TriangleCount());

	return true;
}

TUniquePtr< FDistanceFieldVolumeData > ULFPVoxelRenderComponent::ComputeDistanceFieldForMesh( const FDynamicMesh3& Mesh , FProgressCancel& Progress , bool bGenerateAsIfTwoSided ) const
{
	TUniquePtr< FDistanceFieldVolumeData > NewDistanceField = MakeUnique< FDistanceFieldVolumeData >();
	const bool                             bCompleted       = DynamicMesh_GenerateSignedDistanceFieldVolumeData(Mesh, bGenerateAsIfTwoSided, *NewDistanceField, Progress);
	if ( bCompleted )
	{
		return NewDistanceField;
	}

	return TUniquePtr< FDistanceFieldVolumeData >();
}
