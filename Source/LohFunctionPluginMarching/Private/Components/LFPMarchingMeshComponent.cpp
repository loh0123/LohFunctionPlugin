// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/LFPMarchingMeshComponent.h"

#include "DynamicMeshEditor.h"
#include "MeshCardBuild.h"
#include "MeshSimplification.h"
#include "Components/LFPGridTagDataComponent.h"
#include "Data/LFPGridSetting.h"
#include "Data/LFPMarchingData.h"
#include "DynamicMesh/DynamicMeshAABBTree3.h"
#include "DynamicMesh/Operations/MergeCoincidentMeshEdges.h"
#include "Library/LFPMarchingFunctionLibrary.h"
#include "Math/LFPGridLibrary.h"
#include "Operations/MeshPlaneCut.h"
#include "Render/LFPRenderLibrary.h"
#include "Runtime/GeometryFramework/Private/Components/DynamicMeshSceneProxy.h"
#include "Spatial/FastWinding.h"
#include "Windows/WindowsSemaphore.h"

// Sets default values for this component's properties
ULFPMarchingMeshComponent::ULFPMarchingMeshComponent ( )
{
	// Set this component to be initialized when the game starts and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void ULFPMarchingMeshComponent::BeginPlay ( )
{
	Super::BeginPlay ( );

	// ...
}

void ULFPMarchingMeshComponent::EndPlay ( const EEndPlayReason::Type EndPlayReason )
{
	Super::EndPlay ( EndPlayReason );

	ClearRender ( );

	if ( IsValid ( MeshBodySetup ) )
	{
		MeshBodySetup->InvalidatePhysicsData ( );
		MeshBodySetup->MarkAsGarbage ( );
		MeshBodySetup = nullptr;
	}
}

// Called every frame
void ULFPMarchingMeshComponent::TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent ( DeltaTime , TickType , ThisTickFunction );

	// ...
}

FIntVector ULFPMarchingMeshComponent::GetDataSize ( ) const
{
	if ( IsDataComponentValid ( ) )
	{
		const ULFPGridSetting* GridSetting = DataComponent->GetGridSetting ( );

		return IsValid ( GridSetting ) ? GridSetting->GetDataGridSize ( ) : FIntVector::NoneValue;
	}

	return FIntVector::NoneValue;
}

int32 ULFPMarchingMeshComponent::GetDataNum ( ) const
{
	const FIntVector& DataSize = GetDataSize ( );

	if ( DataSize == FIntVector::NoneValue )
	{
		return INDEX_NONE;
	}

	return DataSize.X * DataSize.Y * DataSize.Z;
}

FVector ULFPMarchingMeshComponent::GetMeshSize ( ) const
{
	if ( IsDataComponentValid ( ) )
	{
		return RenderSetting->GetMarchingSize ( );
	}

	return FVector ( 0.0f );
}

bool ULFPMarchingMeshComponent::IsDataComponentValid ( ) const
{
	if ( IsValid ( DataComponent ) == false || IsValid ( RenderSetting ) == false )
	{
		return false;
	}

	const ULFPGridSetting* GridSetting = DataComponent->GetGridSetting ( );

	if ( IsValid ( GridSetting ) == false )
	{
		return false;
	}

	return true;
}

void ULFPMarchingMeshComponent::GetFaceCullingSetting ( bool& bIsChunkFaceCullingDisable , bool& bIsRegionFaceCullingDisable ) const
{
	bIsChunkFaceCullingDisable  = false;
	bIsRegionFaceCullingDisable = false;

	if ( IsDataComponentValid ( ) )
	{
		bIsChunkFaceCullingDisable  = RenderSetting->IsChunkFaceCullingDisable ( );
		bIsRegionFaceCullingDisable = RenderSetting->IsRegionFaceCullingDisable ( );
	}
}

uint8 ULFPMarchingMeshComponent::GetMarchingID ( const FIntVector& Offset ) const
{
	if ( IsDataComponentValid ( ) )
	{
		uint8 MarchingID = 0;

		for ( int32 MarchingIndex = 0 ; MarchingIndex < 8 ; ++MarchingIndex )
		{
			const FIntVector   MarchingOffset = ULFPGridLibrary::ToGridLocation ( MarchingIndex , FIntVector ( 2 ) );
			const FIntVector   DataIndex      = DataComponent->AddOffsetToGridIndex ( FIntVector ( RegionIndex , ChunkIndex , 0 ) , Offset + MarchingOffset );
			const FGameplayTag DataTag        = DataComponent->GetDataTag ( DataIndex.X , DataIndex.Y , DataIndex.Z );

			if ( DataTag.MatchesTag ( HandleTag ) )
			{
				MarchingID |= ( 1 << MarchingIndex );
			}
		}

		return MarchingID;
	}

	return 0;
}

void ULFPMarchingMeshComponent::Initialize ( ULFPGridTagDataComponent* NewDataComponent , const int32 NewRegionIndex , const int32 NewChunkIndex )
{
	DataComponent = NewDataComponent;
	RegionIndex   = NewRegionIndex;
	ChunkIndex    = NewChunkIndex;
}

void ULFPMarchingMeshComponent::Uninitialize ( )
{
	DataComponent = nullptr;

	ClearRender ( );
}

void ULFPMarchingMeshComponent::ClearRender ( )
{
	MeshComputeData.CancelJob ( );
	DistanceFieldComputeData.CancelJob ( );

	{
		FScopeLock TDLock ( &ThreadDataLock );
		FScopeLock DFLock ( &DistanceFieldLock );

		LocalThreadData.Reset ( );
		CurrentDistanceField.Reset ( );
	}

	AggGeom.EmptyElements ( );

	InvalidatePhysicsData ( );

	EditMesh ( [] ( FDynamicMesh3& Mesh )
	{
		Mesh.Clear ( );
	} );
}

bool ULFPMarchingMeshComponent::UpdateRender ( const bool bSimplify )
{
	if ( IsDataComponentValid ( ) == false )
	{
		ClearRender ( );

		return false;
	}

	const FIntVector& CacheDataSize  = GetDataSize ( ) + FIntVector ( 2 );
	const int32       CacheDataIndex = CacheDataSize.X * CacheDataSize.Y * CacheDataSize.Z;

	int32 ValidCount = 0;

	TBitArray < > CacheDataList = TBitArray ( false , CacheDataIndex );
	{
		/* Generate Marching Mesh Data */
		for ( int32 SolidIndex = 0 ; SolidIndex < CacheDataIndex ; ++SolidIndex )
		{
			const FIntVector CheckOffset = ULFPGridLibrary::ToGridLocation ( SolidIndex , CacheDataSize ) - FIntVector ( 1 );
			const FIntVector CheckIndex  = DataComponent->AddOffsetToGridIndex ( FIntVector ( RegionIndex , ChunkIndex , 0 ) , CheckOffset );

			if ( CheckIndex.GetMin ( ) == INDEX_NONE )
			{
				continue;
			}

			CacheDataList [ SolidIndex ] = DataComponent->GetDataTag ( CheckIndex.X , CheckIndex.Y , CheckIndex.Z ).MatchesTag ( HandleTag );

			if ( CacheDataList [ SolidIndex ] )
			{
				ValidCount += 1;
			}
		}
	}

	// Complete Empty No Need Render Or Inside Other Chunk So Don't Need To Render
	if ( ValidCount == 0 || CacheDataIndex == ValidCount )
	{
		ClearRender ( );
		return false;
	}

	{
		FScopeLock Lock ( &ThreadDataLock );

		LocalThreadData.Reset ( );
	}

	OnMeshRebuilding.Broadcast ( this );

	FLFPMarchingPassData PassData;

	GetFaceCullingSetting ( PassData.bIsChunkFaceCullingDisable , PassData.bIsRegionFaceCullingDisable );

	PassData.MeshFullSize   = GetMeshSize ( );
	PassData.DataSize       = GetDataSize ( );
	PassData.bSimplify      = bSimplify;
	PassData.BoundExpand    = BoundExpand;
	PassData.StartTime      = FDateTime::UtcNow ( );
	PassData.bNeedCollision = IsCollisionEnabled ( ) && CollisionType != CTF_UseComplexAsSimple && bOverrideBoxCollision;

	PassData.RenderSetting = RenderSetting;

	MeshComputeData.LaunchJob ( TEXT ( "MarchingDynamicMeshComponentMeshData" ) ,
	                            [this, MovedCacheDataList = MoveTemp ( CacheDataList ),MovedPassData = MoveTemp ( PassData )] ( FProgressCancel& Progress , TQueue < TFunction < void  ( ) > , EQueueMode::Mpsc >& GameThreadJob )
	                            {
		                            TUniquePtr < FLFPMarchingThreadData > ThreadData = ComputeNewMarchingMesh_TaskFunction ( Progress , MovedCacheDataList , MovedPassData );

		                            if ( Progress.Cancelled ( ) == false )
		                            {
			                            ComputeNewMarchingMesh_Completed ( MoveTemp ( ThreadData ) , GameThreadJob );
		                            }
	                            } );

	return true;
}

void ULFPMarchingMeshComponent::SetDistanceFieldResolution ( const float NewResolutionScale , const bool bDeferUpdate )
{
	DistanceFieldResolutionScale = NewResolutionScale;

	if ( bDeferUpdate == false )
	{
		UpdateDistanceField ( );
	}
}

void ULFPMarchingMeshComponent::RebuildPhysicsData ( )
{
	if ( IsValid ( DataComponent ) == false )
	{
		Super::RebuildPhysicsData ( );

		return;
	}

	{
		FScopeLock Lock ( &ThreadDataLock );

		if ( bOverrideBoxCollision && IsCollisionEnabled ( ) && CollisionType != CTF_UseComplexAsSimple && LocalThreadData.IsValid ( ) )
		{
			AggGeom.BoxElems = LocalThreadData->CollisionBoxElems;
		}
	}

	Super::RebuildPhysicsData ( );
}

void ULFPMarchingMeshComponent::UpdateDistanceField ( )
{
	{
		FScopeLock Lock ( &ThreadDataLock );

		if ( DistanceFieldMode == EDynamicMeshComponentDistanceFieldMode::NoDistanceField || LocalThreadData.IsValid ( ) == false || IsDataComponentValid ( ) == false || GetDynamicMesh ( )->IsEmpty ( ) )
		{
			FScopeLock JobLock ( &DistanceFieldComputeQueue.PendingJobsLock );

			for ( TUniquePtr < TAsyncComponentDataComputeQueue < FDistanceFieldVolumeData >::FComputeJob >& PendingJob : DistanceFieldComputeQueue.PendingJobs )
			{
				PendingJob->bCancelled = true;
			}

			return;
		}
	}

	OnDistanceFieldRebuilding.Broadcast ( this );

	// For safety, run the distance field compute on a (geometry-only) copy of the mesh
	FDynamicMesh3 GeoOnlyCopy;

	// Compute whether the mesh uses mainly two-sided materials before, as this is the only info the distance field compute needs from the mesh attributes
	bool bMostlyTwoSided = bForceTwoSide;
	ProcessMesh ( [&] ( const FDynamicMesh3& ReadMesh )
	{
		if ( ReadMesh.Attributes ( ) && ReadMesh.Attributes ( )->GetMaterialID ( ) && bMostlyTwoSided == false )
		{
			TArray < bool > MatIsTwoSided;
			MatIsTwoSided.SetNumUninitialized ( BaseMaterials.Num ( ) );
			for ( int32 Idx = 0 ; Idx < BaseMaterials.Num ( ) ; ++Idx )
			{
				MatIsTwoSided [ Idx ] = BaseMaterials [ Idx ]
				                        ? BaseMaterials [ Idx ]->IsTwoSided ( )
				                        : false;
			}
			const UE::Geometry::FDynamicMeshMaterialAttribute* Materials        = ReadMesh.Attributes ( )->GetMaterialID ( );
			int32                                              TwoSidedTriCount = 0;
			for ( int32 TID : ReadMesh.TriangleIndicesItr ( ) )
			{
				int32 MID = Materials->GetValue ( TID );
				TwoSidedTriCount += MatIsTwoSided.IsValidIndex ( MID )
				                    ? static_cast < int32 > ( MatIsTwoSided [ MID ] )
				                    : 0;
			}
			bMostlyTwoSided = TwoSidedTriCount * 2 >= ReadMesh.TriangleCount ( );
		}

		GeoOnlyCopy.Copy ( ReadMesh , false , false , false , false );
	} );

	// Fill Mesh Hole
	{
		const FIntVector& DataSize = GetDataSize ( );

		const int32 DataNum = GetDataNum ( );

		const FVector MeshFullSize = GetMeshSize ( );
		const FVector MeshHalfSize = MeshFullSize * 0.5f;

		const FVector MeshBoundFullSize = MeshFullSize * FVector ( DataSize );
		const FVector MeshBoundHalfSize = MeshBoundFullSize * 0.5f;

		const auto& CreateFace = [&] ( const int32& VoxelIndex , const int32& RotationID )
		{
			const FIntVector         VoxelGridPos                  = ULFPGridLibrary::ToGridLocation ( VoxelIndex , DataSize );
			const FVector            CenterPos                     = ( FVector ( VoxelGridPos ) + 0.5f ) * MeshFullSize;
			const FRotator           Rotation                      = LFPMarchingRenderConstantData::VertexRotationList [ RotationID ];
			const TArray < FVector > FaceVertexList                = ULFPRenderLibrary::CreateVertexPosList ( CenterPos , Rotation , MeshHalfSize );
			const FVector            FaceVertexPosList [ 2 ] [ 3 ] =
			{
				{
					FaceVertexList [ 1 ] , FaceVertexList [ 0 ] , FaceVertexList [ 3 ]
				} ,
				{
					FaceVertexList [ 2 ] , FaceVertexList [ 3 ] , FaceVertexList [ 0 ]
				}
			};

			for ( int32 FaceIndex = 0 ; FaceIndex < 2 ; ++FaceIndex )
			{
				FIntVector FaceVertexIndexList;

				for ( int32 FaceVertexIndex = 0 ; FaceVertexIndex < 3 ; ++FaceVertexIndex )
				{
					const FVector& FaceVertexPos = FaceVertexPosList [ FaceIndex ] [ FaceVertexIndex ] - MeshBoundHalfSize;

					FaceVertexIndexList [ FaceVertexIndex ] = GeoOnlyCopy.AppendVertex ( FaceVertexPos );
				}

				GeoOnlyCopy.AppendTriangle ( FaceVertexIndexList );
			}
		};

		/* Generate Voxel Mesh Data */
		for ( int32 DataIndex = 0 ; DataIndex < DataNum ; ++DataIndex )
		{
			const FIntVector VoxelPos       = ULFPGridLibrary::ToGridLocation ( DataIndex , DataSize );
			const FIntVector VoxelDataIndex = DataComponent->AddOffsetToGridIndex ( FIntVector ( RegionIndex , ChunkIndex , 0 ) , VoxelPos );

			const FGameplayTag& SelfVoxelTag = DataComponent->GetDataTag ( VoxelDataIndex.X , VoxelDataIndex.Y , VoxelDataIndex.Z );

			if ( SelfVoxelTag.MatchesTag ( HandleTag ) )
			{
				for ( int32 FaceDirectionIndex = 0 ; FaceDirectionIndex < 6 ; ++FaceDirectionIndex )
				{
					const FIntVector& TargetIndex = DataComponent->AddOffsetToGridIndex ( VoxelDataIndex , LFPMarchingRenderConstantData::FaceDirection [ FaceDirectionIndex ].Up );

					const bool bForceRender = ULFPGridLibrary::IsGridLocationValid ( VoxelPos + LFPMarchingRenderConstantData::FaceDirection [ FaceDirectionIndex ].Up , DataSize ) == false;

					const bool TargetVoxelValid = TargetIndex.GetMin ( ) != INDEX_NONE && DataComponent->GetDataTag ( TargetIndex.X , TargetIndex.Y , TargetIndex.Z ).MatchesTag ( HandleTag );

					// Check Is Border
					if ( bForceRender && TargetVoxelValid )
					{
						CreateFace ( DataIndex , FaceDirectionIndex );
					}
				}
			}
		}
	}

	DistanceFieldComputeData.LaunchJob ( TEXT ( "MarchingDynamicMeshComponentDistanceField" ) ,
	                                     [this,MovedGeoOnlyCopy = MoveTemp ( GeoOnlyCopy ), CurrentDistanceFieldResolutionScale = DistanceFieldResolutionScale, bMostlyTwoSided] ( FProgressCancel& Progress , TQueue < TFunction < void  ( ) > , EQueueMode::Mpsc >& GameThreadJob )
	                                     {
		                                     TUniquePtr < FDistanceFieldVolumeData > ThreadData = ComputeNewDistanceField_TaskFunctionV2 ( Progress , MovedGeoOnlyCopy , bMostlyTwoSided , CurrentDistanceFieldResolutionScale );

		                                     if ( Progress.Cancelled ( ) == false )
		                                     {
			                                     ComputeNewDistanceFieldData_Completed ( MoveTemp ( ThreadData ) , GameThreadJob );
		                                     }
	                                     } );
}

FPrimitiveSceneProxy* ULFPMarchingMeshComponent::CreateSceneProxy ( )
{
	FPrimitiveSceneProxy* NewProxy = Super::CreateSceneProxy ( );

	if ( NewProxy == nullptr )
	{
		return nullptr;
	}

	if ( IsDataComponentValid ( ) == false )
	{
		return NewProxy;
	}

	{
		FScopeLock Lock ( &DistanceFieldLock );

		if ( GetDistanceFieldMode ( ) == EDynamicMeshComponentDistanceFieldMode::NoDistanceField || CurrentDistanceField.IsValid ( ) == false )
		{
			return NewProxy;
		}
	}

	// Hijack The Data And Force Edit It
	FCardRepresentationData* LumenCard = const_cast < FCardRepresentationData* > ( NewProxy->GetMeshCardRepresentation ( ) );

	{
		FScopeLock Lock ( &ThreadDataLock );

		if ( LumenCard == nullptr || LocalThreadData.IsValid ( ) == false )
		{
			return NewProxy;
		}

		LumenCard->MeshCardsBuildData.Bounds        = LocalThreadData->LumenBound;
		LumenCard->MeshCardsBuildData.CardBuildData = LocalThreadData->LumenCardData;
	}

	return NewProxy;
}

TUniquePtr < FLFPMarchingThreadData > ULFPMarchingMeshComponent::ComputeNewMarchingMesh_TaskFunction ( FProgressCancel& Progress , const TBitArray < >& SolidList , const FLFPMarchingPassData& PassData )
{
	if ( Progress.Cancelled ( ) )
	{
		return nullptr;
	}

	TRACE_CPUPROFILER_EVENT_SCOPE ( MarchingMesh_GeneratingThreadData );

	TUniquePtr < FLFPMarchingThreadData > NewMeshData = MakeUnique < FLFPMarchingThreadData > ( );

	NewMeshData->StartTime = PassData.StartTime;

	const FVector& MeshFullSize = PassData.MeshFullSize;
	const FVector  MeshGapSize  = MeshFullSize;

	const FIntVector& DataSize      = PassData.DataSize;
	const FIntVector& CacheDataSize = DataSize + FIntVector ( 2 );

	const FVector MeshBoundFullSize = MeshGapSize * FVector ( DataSize );
	const FVector MeshBoundHalfSize = MeshBoundFullSize * FVector ( 0.5f );

	const FIntVector MarchingSize = DataSize + FIntVector ( 1 );
	const int32      MarchingNum  = MarchingSize.X * MarchingSize.Y * MarchingSize.Z;

	const FBox CurrentLocalBounds = FBox ( -MeshBoundHalfSize , MeshBoundHalfSize );

	const float BoundExpand = PassData.BoundExpand;

	const auto GetMarchingID = [&] ( const FIntVector& StartPosition )
	{
		uint8 MarchingID = 0;

		for ( int32 MarchingIndex = 0 ; MarchingIndex < 8 ; ++MarchingIndex )
		{
			const FIntVector MarchingPosition = ULFPGridLibrary::ToGridLocation ( MarchingIndex , FIntVector ( 2 ) ) + StartPosition;
			const int32      SolidIndex       = ULFPGridLibrary::ToGridIndex ( MarchingPosition , DataSize + FIntVector ( 2 ) );

			if ( SolidList [ SolidIndex ] )
			{
				MarchingID |= 1 << MarchingIndex;
			}
		}

		return MarchingID;
	};

	if ( Progress.Cancelled ( ) )
	{
		return nullptr;
	}

	// Mesh Data
	{
		TRACE_CPUPROFILER_EVENT_SCOPE ( MarchingMesh_GeneratingMesh );

		FDynamicMesh3& MeshData = NewMeshData->MeshData;
		{
			MeshData.EnableAttributes ( );
		}

		const TObjectPtr < ULFPMarchingData >& MeshAsset = PassData.RenderSetting;

		TArray < uint8 > MarchingIDList;
		{
			MarchingIDList.SetNum ( MarchingNum );

			for ( int32 MarchingIndex = 0 ; MarchingIndex < MarchingNum ; ++MarchingIndex )
			{
				const FIntVector CheckPos = ULFPGridLibrary::ToGridLocation ( MarchingIndex , MarchingSize );

				MarchingIDList [ MarchingIndex ] = GetMarchingID ( CheckPos );
			}
		}

		UE::Geometry::FDynamicMeshEditor Editor ( &MeshData );

		/* Generate Marching Mesh Data */
		for ( int32 MarchingIndex = 0 ; MarchingIndex < MarchingNum ; ++MarchingIndex )
		{
			const FIntVector MarchingGridLocation = ULFPGridLibrary::ToGridLocation ( MarchingIndex , MarchingSize );
			const FVector    MarchingMeshLocation = ( MeshGapSize * FVector ( MarchingGridLocation ) ) - MeshBoundHalfSize;
			const uint8      MarchingID           = MarchingIDList [ MarchingIndex ];

			if ( Progress.Cancelled ( ) )
			{
				return nullptr;
			}

			if ( const FLFPMarchingMeshMappingDataV2& MeshMappingData = MeshAsset->GetMappingData ( MarchingID ) ; MeshMappingData.MeshID != INDEX_NONE )
			{
				const FDynamicMesh3* AppendMesh = MeshAsset->GetDynamicMesh ( MeshMappingData.MeshID );

				if ( AppendMesh == nullptr )
				{
					continue;
				}

				const FTransform AppendTransform (
				                                  MeshMappingData.GetRotation ( ) ,
				                                  MarchingMeshLocation ,
				                                  FVector ( 1.0f )
				                                 );

				UE::Geometry::FTransformSRT3d    XForm ( AppendTransform );
				UE::Geometry::FMeshIndexMappings TmpMappings;
				Editor.AppendMesh ( AppendMesh , TmpMappings ,
				                    [&XForm] ( const int32 VID , const FVector3d& Position ) { return XForm.TransformPosition ( Position ); } ,
				                    [&XForm] ( const int32 NID , const FVector3d& Normal ) { return XForm.TransformNormal ( Normal ); } ,
				                    XForm.GetDeterminant ( ) < 0 );
			}
		}

		const FVector EdgeDirectionList [ 6 ] =
		{
			FVector ( 1 , 0 , 0 ) ,
			FVector ( 0 , 1 , 0 ) ,
			FVector ( 0 , 0 , 1 ) ,
			FVector ( -1 , 0 , 0 ) ,
			FVector ( 0 , -1 , 0 ) ,
			FVector ( 0 , 0 , -1 )
		};

		for ( const FVector& EdgeDirection : EdgeDirectionList )
		{
			UE::Geometry::FMeshPlaneCut Cut ( &MeshData , EdgeDirection * MeshBoundHalfSize , EdgeDirection );
			Cut.Cut ( );
		}

		UE::Geometry::FMergeCoincidentMeshEdges Welder ( &MeshData );
		Welder.MergeVertexTolerance = 1.0f;
		Welder.OnlyUniquePairs      = false;
		Welder.Apply ( );

		if ( PassData.bSimplify )
		{
			UE::Geometry::FQEMSimplification Simplifier ( &MeshData );

			constexpr float AngleThreshold = 0.001;

			Simplifier.CollapseMode = UE::Geometry::FQEMSimplification::ESimplificationCollapseModes::MinimalQuadricPositionError;
			Simplifier.SimplifyToMinimalPlanar ( AngleThreshold );
		}

		MeshData.CompactInPlace ( nullptr );
	}

	if ( Progress.Cancelled ( ) )
	{
		return nullptr;
	}

	// Lumen Card
	{
		TRACE_CPUPROFILER_EVENT_SCOPE ( MarchingMesh_GeneratingLumen );

		auto SetCoverIndex = [&] ( FIntPoint& CoverIndex , const int32 Index )
		{
			if ( Index <= -1 )
			{
				CoverIndex = FIntPoint ( INDEX_NONE );
			}
			else if ( CoverIndex.GetMin ( ) == INDEX_NONE )
			{
				CoverIndex = FIntPoint ( Index );
			}
			else if ( CoverIndex.X > Index )
			{
				CoverIndex.X = Index;
			}
			else if ( CoverIndex.Y < Index )
			{
				CoverIndex.Y = Index;
			}
		};

		auto CheckFaceVisible = [&] ( const FIntVector& CurrentPos , const FIntVector& FromDirection )
		{
			const FIntVector TargetCheckPos  = CurrentPos + FIntVector ( 1 );
			const FIntVector CurrentCheckPos = TargetCheckPos + FromDirection;

			const int32 TargetIndex  = ULFPGridLibrary::ToGridIndex ( TargetCheckPos , CacheDataSize );
			const int32 CurrentIndex = ULFPGridLibrary::ToGridIndex ( CurrentCheckPos , CacheDataSize );

			return SolidList [ CurrentIndex ] == false && SolidList [ TargetIndex ];
		};

		auto AddCardBuild = [&] ( TArray < FLumenCardBuildData >& CardBuildList , const FIntPoint& CoverIndex , const int32 DirectionIndex )
		{
			FBox3f LumenBox;

			switch ( DirectionIndex )
			{
				case 0 :
				case 3 : LumenBox = FBox3f (
				                            FVector3f ( CurrentLocalBounds.Min.X , CurrentLocalBounds.Min.Y , ( CoverIndex.X * MeshFullSize.Z ) - MeshBoundHalfSize.Z - BoundExpand ) ,
				                            FVector3f ( CurrentLocalBounds.Max.X , CurrentLocalBounds.Max.Y , ( CoverIndex.Y * MeshFullSize.Z ) - MeshBoundHalfSize.Z + BoundExpand )
				                           );

					if ( DirectionIndex == 0 )
					{
						LumenBox = LumenBox.ShiftBy ( FVector3f ( 0.0f , 0.0f , MeshFullSize.Z ) );
					}
					break;

				case 1 :
				case 4 : LumenBox = FBox3f (
				                            FVector3f ( ( CoverIndex.X * MeshFullSize.X ) - MeshBoundHalfSize.X - BoundExpand , CurrentLocalBounds.Min.Y , CurrentLocalBounds.Min.Z ) ,
				                            FVector3f ( ( CoverIndex.Y * MeshFullSize.X ) - MeshBoundHalfSize.X + BoundExpand , CurrentLocalBounds.Max.Y , CurrentLocalBounds.Max.Z )
				                           );

					if ( DirectionIndex == 4 )
					{
						LumenBox = LumenBox.ShiftBy ( FVector3f ( MeshFullSize.X , 0.0f , 0.0f ) );
					}
					break;

				case 2 :
				case 5 : LumenBox = FBox3f (
				                            FVector3f ( CurrentLocalBounds.Min.X , ( CoverIndex.X * MeshFullSize.Y ) - MeshBoundHalfSize.Y - BoundExpand , CurrentLocalBounds.Min.Z ) ,
				                            FVector3f ( CurrentLocalBounds.Max.X , ( CoverIndex.Y * MeshFullSize.Y ) - MeshBoundHalfSize.Y + BoundExpand , CurrentLocalBounds.Max.Z )
				                           );

					if ( DirectionIndex == 2 )
					{
						LumenBox = LumenBox.ShiftBy ( FVector3f ( 0.0f , MeshFullSize.Y , 0.0f ) );
					}
					break;
				default : break;
			}

			FLumenCardBuildData BuildData;

			BuildData.AxisAlignedDirectionIndex = LFPMarchingRenderConstantData::SurfaceDirectionID [ DirectionIndex ];

			LFPMarchingRenderConstantData::FaceDirection [ DirectionIndex ].SetAxis (
			                                                                         BuildData.OBB.AxisX ,
			                                                                         BuildData.OBB.AxisY ,
			                                                                         BuildData.OBB.AxisZ
			                                                                        );

			BuildData.OBB.Origin = FVector3f ( LumenBox.GetCenter ( ) );
			BuildData.OBB.Extent = FVector3f ( LFPMarchingRenderConstantData::VertexRotationList [ DirectionIndex ].UnrotateVector ( FVector ( LumenBox.GetExtent ( ) ) ).GetAbs ( ) );

			CardBuildList.Add ( BuildData );
		};

		NewMeshData->LumenBound = FBox ( CurrentLocalBounds );

		TArray < FLumenCardBuildData >& CardBuildList = NewMeshData->LumenCardData;

		CardBuildList.Empty ( );

		struct FLFPFaceListData
		{
			FLFPFaceListData ( const FIntVector InID , const int32 InFaceID , const bool InbIsReverse ) : ID ( InID ), FaceID ( InFaceID ), bIsReverse ( InbIsReverse )
			{
			}

			const FIntVector ID         = FIntVector ( 0 , 1 , 2 );
			const int32      FaceID     = 0;
			const bool       bIsReverse = false;
		};

		constexpr bool FaceReverseList [ ] =
		{
			true , false , true , false , true , false
		};

		for ( int32 Direction = 0 ; Direction < 6 ; ++Direction )
		{
			if ( Progress.Cancelled ( ) )
			{
				return nullptr;
			}

			const FIntVector MarchingDimension = FIntVector (
			                                                 DataSize [ LFPMarchingRenderConstantData::FaceLoopDirectionList [ Direction ].X ] ,
			                                                 DataSize [ LFPMarchingRenderConstantData::FaceLoopDirectionList [ Direction ].Y ] ,
			                                                 DataSize [ LFPMarchingRenderConstantData::FaceLoopDirectionList [ Direction ].Z ]
			                                                );

			const int32 MarchingPlaneLength = MarchingDimension.X * MarchingDimension.Y;

			FIntPoint CoverIndex = FIntPoint ( INDEX_NONE );

			TBitArray < > BlockMap = TBitArray ( false , MarchingPlaneLength );

			const bool& bIsReverse = FaceReverseList [ Direction ];

			for ( int32 DepthIndex = bIsReverse
			                         ? MarchingDimension.Z - 1
			                         : 0 ; bIsReverse
			                               ? DepthIndex > -1
			                               : DepthIndex < MarchingDimension.Z ; bIsReverse
			                                                                    ? DepthIndex--
			                                                                    : DepthIndex++ )
			{
			StartCheck:

				for ( int32 X = 0 ; X < MarchingDimension.X ; X++ )
				{
					for ( int32 Y = 0 ; Y < MarchingDimension.Y ; Y++ )
					{
						FIntVector MarchingGridLocation;
						MarchingGridLocation [ LFPMarchingRenderConstantData::FaceLoopDirectionList [ Direction ].X ] = X;
						MarchingGridLocation [ LFPMarchingRenderConstantData::FaceLoopDirectionList [ Direction ].Y ] = Y;
						MarchingGridLocation [ LFPMarchingRenderConstantData::FaceLoopDirectionList [ Direction ].Z ] = DepthIndex;

						const int32 MarchingPlaneIndex = X + ( Y * MarchingDimension.X );

						const bool bIsFaceVisible = CheckFaceVisible ( MarchingGridLocation , LFPMarchingRenderConstantData::FaceDirection [ Direction ].Up );

						if ( BlockMap [ MarchingPlaneIndex ] )
						{
							if ( bIsFaceVisible )
							{
								AddCardBuild ( CardBuildList , CoverIndex , Direction );

								/* Reset */
								BlockMap = TBitArray ( false , MarchingPlaneLength );

								SetCoverIndex ( CoverIndex , INDEX_NONE );

								goto StartCheck;
							}
						}
						else if ( bIsFaceVisible )
						{
							BlockMap [ MarchingPlaneIndex ] = bIsFaceVisible;

							SetCoverIndex ( CoverIndex , DepthIndex );
						}
					}
				}
			}

			if ( CoverIndex.GetMin ( ) != INDEX_NONE )
			{
				AddCardBuild ( CardBuildList , CoverIndex , Direction );
			}
		}
	}

	if ( Progress.Cancelled ( ) )
	{
		return nullptr;
	}

	// Collision Box
	if ( PassData.bNeedCollision )
	{
		TRACE_CPUPROFILER_EVENT_SCOPE ( MarchingMesh_GeneratingBoxCollision );

		TMap < FIntVector , FIntVector > BatchDataMap;

		TPair < FIntVector , FIntVector > CurrentBatchData ( INDEX_NONE , INDEX_NONE );

		bool IsBatchValid = false;

		const auto& PushData = [&] ( )
		{
			{
				const FIntVector  TargetMax    = CurrentBatchData.Key - FIntVector ( 0 , 1 , 0 );
				const FIntVector* TargetMinPtr = BatchDataMap.Find ( TargetMax );

				if ( TargetMinPtr != nullptr && TargetMinPtr->X == CurrentBatchData.Value.X && TargetMinPtr->Z == CurrentBatchData.Value.Z )
				{
					const FIntVector TargetMin = BatchDataMap.FindAndRemoveChecked ( TargetMax );

					CurrentBatchData.Value.Y = TargetMin.Y;
				}
			}

			{
				const FIntVector  TargetMax    = CurrentBatchData.Key - FIntVector ( 0 , 0 , 1 );
				const FIntVector* TargetMinPtr = BatchDataMap.Find ( TargetMax );

				if ( TargetMinPtr != nullptr && TargetMinPtr->X == CurrentBatchData.Value.X && TargetMinPtr->Y == CurrentBatchData.Value.Y )
				{
					const FIntVector TargetMin = BatchDataMap.FindAndRemoveChecked ( TargetMax );

					CurrentBatchData.Value.Z = TargetMin.Z;
				}
			}

			BatchDataMap.Add ( CurrentBatchData.Key , CurrentBatchData.Value );
			IsBatchValid = false;
		};

		/** Generate Batch Data Map */
		for ( int32 Z = 0 ; Z < DataSize.Z ; Z++ )
		{
			if ( Progress.Cancelled ( ) )
			{
				return nullptr;
			}

			for ( int32 Y = 0 ; Y < DataSize.Y ; Y++ )
			{
				for ( int32 X = 0 ; X < DataSize.X ; X++ )
				{
					/***************** Identify Data *****************/
					const FIntVector CurrentPos ( X , Y , Z );

					const int32 CurrentIndex = ULFPGridLibrary::ToGridIndex ( CurrentPos + FIntVector ( 1 ) , CacheDataSize );

					/*************************************************/

					if ( SolidList [ CurrentIndex ] )
					{
						if ( ( CurrentBatchData.Key.Y != Y || CurrentBatchData.Key.Z != Z ) && IsBatchValid )
						{
							PushData ( );
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
						PushData ( );
					}
				}
			}
		}

		if ( IsBatchValid )
		{
			PushData ( );
		}

		if ( Progress.Cancelled ( ) )
		{
			return nullptr;
		}

		/** Add To Result */
		for ( const auto& BatchData : BatchDataMap )
		{
			const FVector MinPos = FVector ( BatchData.Value ) * MeshGapSize;
			const FVector MaxPos = FVector ( BatchData.Key + FIntVector ( 1 ) ) * MeshGapSize;
			const FVector Scale  = ( MaxPos - MinPos );
			const FVector Center = FMath::Lerp ( MinPos , MaxPos , 0.5f ) - MeshBoundHalfSize;

			FKBoxElem CurrentBoxElem ( Scale.X , Scale.Y , Scale.Z );

			CurrentBoxElem.Center = Center;

			NewMeshData->CollisionBoxElems.Add ( CurrentBoxElem );
		}
	}

	if ( Progress.Cancelled ( ) )
	{
		return nullptr;
	}

	return
		NewMeshData;
}

void ULFPMarchingMeshComponent::ComputeNewMarchingMesh_Completed ( TUniquePtr < FLFPMarchingThreadData > ThreadData , TQueue < TFunction < void  ( ) > , EQueueMode::Mpsc >& GameThreadJob )
{
	if ( IsValid ( this ) == false )
	{
		return;
	}

	// Write Data
	{
		FScopeLock Lock ( &ThreadDataLock );

		if ( ThreadData.IsValid ( ) )
		{
			LocalThreadData = MakeShareable ( ThreadData.Release ( ) );
		}
		else
		{
			LocalThreadData.Reset ( );
		}
	}

	if ( bUpdatingThreadData == false )
	{
		bUpdatingThreadData = true;

		GameThreadJob.Enqueue ( [this] ( )
		{
			if ( IsValid ( this ) == false )
			{
				return;
			}

			bUpdatingThreadData = false;

			{
				FScopeLock Lock ( &ThreadDataLock );

				if ( LocalThreadData.IsValid ( ) == false )
				{
					EditMesh ( [] ( FDynamicMesh3& Mesh )
					{
						Mesh.Clear ( );
					} );
				}
				else
				{
					//const float CompactMetric = LocalThreadData->MeshData.CompactMetric ( );

					SetMesh ( MoveTemp ( LocalThreadData->MeshData ) );

					//UE_LOG ( LogTemp , Warning , TEXT("Marching Data Time Use : %d ms : Compact %f") , (int32)(FDateTime::UtcNow() - LocalThreadData->StartTime).GetTotalMilliseconds() , CompactMetric );

					OnMeshGenerated.Broadcast ( this );
				}
			}
		} );
	}
}

TUniquePtr < FDistanceFieldVolumeData > ULFPMarchingMeshComponent::ComputeNewDistanceField_TaskFunctionV2 ( FProgressCancel& Progress , const FDynamicMesh3& Mesh , const bool bGenerateAsIfTwoSided , const float CurrentDistanceFieldResolutionScale )
{
	if ( Progress.Cancelled ( ) )
	{
		return nullptr;
	}

	TUniquePtr < FDistanceFieldVolumeData > NewDistanceField = MakeUnique < FDistanceFieldVolumeData > ( );
	FDistanceFieldVolumeData&               VolumeDataOut    = *NewDistanceField;

	{
		TRACE_CPUPROFILER_EVENT_SCOPE ( DynamicMesh_GenerateSignedDistanceFieldVolumeData );

		if ( DoesProjectSupportDistanceFields ( ) == false )
		{
			return nullptr;
		}

		if ( CurrentDistanceFieldResolutionScale <= 0 )
		{
			return nullptr;
		}

		//const double StartTime = FPlatformTime::Seconds ( );

		const auto ComputeLinearMarchingIndex = [&] ( FIntVector MarchingCoordinate , FIntVector VolumeDimensions )
		{
			return ( MarchingCoordinate.Z * VolumeDimensions.Y + MarchingCoordinate.Y ) * VolumeDimensions.X + MarchingCoordinate.X;
		};

		UE::Geometry::FDynamicMeshAABBTree3 Spatial ( &Mesh , true );
		if ( Progress.Cancelled ( ) )
		{
			return nullptr;
		}
		UE::Geometry::FAxisAlignedBox3d                  MeshBounds = Spatial.GetBoundingBox ( );
		UE::Geometry::TFastWindingTree < FDynamicMesh3 > WindingTree ( &Spatial , true );
		if ( Progress.Cancelled ( ) )
		{
			return nullptr;
		}

		static const auto CVar       = IConsoleManager::Get ( ).FindTConsoleVariableDataInt ( TEXT ( "r.DistanceFields.MaxPerMeshResolution" ) );
		const int32       PerMeshMax = CVar->GetValueOnAnyThread ( );

		// Meshes with an explicit artist-specified scale can go higher
		const int32 MaxNumBlocksOneDim = FMath::Min < int32 > ( FMath::DivideAndRoundNearest ( CurrentDistanceFieldResolutionScale <= 1
		                                                                                       ? PerMeshMax / 2
		                                                                                       : PerMeshMax , DistanceField::UniqueDataBrickSize ) , DistanceField::MaxIndirectionDimension - 1 );

		static const auto CVarDensity  = IConsoleManager::Get ( ).FindTConsoleVariableDataFloat ( TEXT ( "r.DistanceFields.DefaultVoxelDensity" ) );
		const float       VoxelDensity = CVarDensity->GetValueOnAnyThread ( );

		const float NumVoxelsPerLocalSpaceUnit = VoxelDensity * CurrentDistanceFieldResolutionScale;
		FBox3f      LocalSpaceMeshBounds       = FBox3f ( MeshBounds );

		// Make sure the mesh bounding box has positive extents to handle planes
		{
			FVector3f MeshBoundsCenter = LocalSpaceMeshBounds.GetCenter ( );
			FVector3f MeshBoundsExtent = FVector3f::Max ( LocalSpaceMeshBounds.GetExtent ( ) , FVector3f ( 1.0f , 1.0f , 1.0f ) );
			LocalSpaceMeshBounds.Min   = MeshBoundsCenter - MeshBoundsExtent;
			LocalSpaceMeshBounds.Max   = MeshBoundsCenter + MeshBoundsExtent;
		}

		// We sample on voxel corners and use central differencing for gradients, so a box mesh using two-sided materials whose vertices lie on LocalSpaceMeshBounds produces a zero gradient on intersection
		// Expand the mesh bounds by a fraction of a voxel to allow room for a pullback on the hit location for computing the gradient.
		// Only expand for two-sided meshes as this adds significant Mesh SDF tracing cost
		if ( bGenerateAsIfTwoSided )
		{
			const FVector3f  DesiredDimensions         = FVector3f ( LocalSpaceMeshBounds.GetSize ( ) * FVector3f ( NumVoxelsPerLocalSpaceUnit / static_cast < float > ( DistanceField::UniqueDataBrickSize ) ) );
			const FIntVector Mip0IndirectionDimensions = FIntVector (
			                                                         FMath::Clamp ( FMath::RoundToInt ( DesiredDimensions.X ) , 1 , MaxNumBlocksOneDim ) ,
			                                                         FMath::Clamp ( FMath::RoundToInt ( DesiredDimensions.Y ) , 1 , MaxNumBlocksOneDim ) ,
			                                                         FMath::Clamp ( FMath::RoundToInt ( DesiredDimensions.Z ) , 1 , MaxNumBlocksOneDim ) );

			constexpr float CentralDifferencingExpandInVoxels = .25f;
			const FVector3f TexelObjectSpaceSize              = LocalSpaceMeshBounds.GetSize ( ) / FVector3f ( Mip0IndirectionDimensions * DistanceField::UniqueDataBrickSize - FIntVector ( 2 * CentralDifferencingExpandInVoxels ) );
			LocalSpaceMeshBounds                              = LocalSpaceMeshBounds.ExpandBy ( TexelObjectSpaceSize );
		}

		// The tracing shader uses a Volume space normalized by the maximum extent. To keep Volume space within [-1, 1], we must match that behavior when encoding
		const float LocalToVolumeScale = 1.0f / LocalSpaceMeshBounds.GetExtent ( ).GetMax ( );

		const FVector3f  DesiredDimensions         = FVector3f ( LocalSpaceMeshBounds.GetSize ( ) * FVector3f ( NumVoxelsPerLocalSpaceUnit / static_cast < float > ( DistanceField::UniqueDataBrickSize ) ) );
		const FIntVector Mip0IndirectionDimensions = FIntVector (
		                                                         FMath::Clamp ( FMath::RoundToInt ( DesiredDimensions.X ) , 1 , MaxNumBlocksOneDim ) ,
		                                                         FMath::Clamp ( FMath::RoundToInt ( DesiredDimensions.Y ) , 1 , MaxNumBlocksOneDim ) ,
		                                                         FMath::Clamp ( FMath::RoundToInt ( DesiredDimensions.Z ) , 1 , MaxNumBlocksOneDim ) );

		TArray < uint8 > StreamableMipData;

		struct FDistanceFieldBrick
		{
			FDistanceFieldBrick (
				float         InLocalSpaceTraceDistance ,
				const FBox3f& InVolumeBounds ,
				float         InLocalToVolumeScale ,
				FVector2f     InDistanceFieldToVolumeScaleBias ,
				FIntVector    InBrickCoordinate ,
				FIntVector    InIndirectionSize ) : LocalSpaceTraceDistance ( InLocalSpaceTraceDistance ),
				                                 VolumeBounds ( InVolumeBounds ),
				                                 LocalToVolumeScale ( InLocalToVolumeScale ),
				                                 DistanceFieldToVolumeScaleBias ( InDistanceFieldToVolumeScaleBias ),
				                                 BrickCoordinate ( InBrickCoordinate ),
				                                 IndirectionSize ( InIndirectionSize ),
				                                 BrickMaxDistance ( MIN_uint8 ),
				                                 BrickMinDistance ( MAX_uint8 )
			{
			}

			float      LocalSpaceTraceDistance;
			FBox3f     VolumeBounds;
			float      LocalToVolumeScale;
			FVector2f  DistanceFieldToVolumeScaleBias;
			FIntVector BrickCoordinate;
			FIntVector IndirectionSize;

			// Output
			uint8            BrickMaxDistance;
			uint8            BrickMinDistance;
			TArray < uint8 > DistanceFieldVolume;
		};

		for ( int32 MipIndex = 0 ; MipIndex < DistanceField::NumMips ; MipIndex++ )
		{
			if ( Progress.Cancelled ( ) )
			{
				return nullptr;
			}

			const FIntVector IndirectionDimensions = FIntVector (
			                                                     FMath::DivideAndRoundUp ( Mip0IndirectionDimensions.X , 1 << MipIndex ) ,
			                                                     FMath::DivideAndRoundUp ( Mip0IndirectionDimensions.Y , 1 << MipIndex ) ,
			                                                     FMath::DivideAndRoundUp ( Mip0IndirectionDimensions.Z , 1 << MipIndex ) );

			// Expand to guarantee one voxel border for gradient reconstruction using bilinear filtering
			const FVector3f TexelObjectSpaceSize      = LocalSpaceMeshBounds.GetSize ( ) / FVector3f ( IndirectionDimensions * DistanceField::UniqueDataBrickSize - FIntVector ( 2 * DistanceField::MeshDistanceFieldObjectBorder ) );
			const FBox3f    DistanceFieldVolumeBounds = LocalSpaceMeshBounds.ExpandBy ( TexelObjectSpaceSize );

			const FVector3f IndirectionMarchingSize = DistanceFieldVolumeBounds.GetSize ( ) / FVector3f ( IndirectionDimensions );

			const FVector3f VolumeSpaceDistanceFieldMarchingSize = IndirectionMarchingSize * LocalToVolumeScale / FVector3f ( DistanceField::UniqueDataBrickSize );
			const float     MaxDistanceForEncoding               = VolumeSpaceDistanceFieldMarchingSize.Size ( ) * DistanceField::BandSizeInVoxels;
			const float     LocalSpaceTraceDistance              = MaxDistanceForEncoding / LocalToVolumeScale;
			const FVector2f DistanceFieldToVolumeScaleBias ( 2.0f * MaxDistanceForEncoding , -MaxDistanceForEncoding );

			TArray < FDistanceFieldBrick > BricksToCompute;
			BricksToCompute.Reserve ( IndirectionDimensions.X * IndirectionDimensions.Y * IndirectionDimensions.Z / 8 );
			for ( int32 ZIndex = 0 ; ZIndex < IndirectionDimensions.Z ; ZIndex++ )
			{
				for ( int32 YIndex = 0 ; YIndex < IndirectionDimensions.Y ; YIndex++ )
				{
					for ( int32 XIndex = 0 ; XIndex < IndirectionDimensions.X ; XIndex++ )
					{
						BricksToCompute.Emplace (
						                         LocalSpaceTraceDistance ,
						                         DistanceFieldVolumeBounds ,
						                         LocalToVolumeScale ,
						                         DistanceFieldToVolumeScaleBias ,
						                         FIntVector ( XIndex , YIndex , ZIndex ) ,
						                         IndirectionDimensions );
					}
				}
			}

			if ( Progress.Cancelled ( ) )
			{
				return nullptr;
			}

			// compute bricks now
			ParallelFor ( BricksToCompute.Num ( ) , [&] ( const int32 BrickIndex )
			{
				FDistanceFieldBrick& Brick                        = BricksToCompute [ BrickIndex ];
				const FVector3f      BrickIndirectionMarchingSize = Brick.VolumeBounds.GetSize ( ) / FVector3f ( Brick.IndirectionSize );
				const FVector3f      DistanceFieldMarchingSize    = BrickIndirectionMarchingSize / FVector3f ( DistanceField::UniqueDataBrickSize );
				const FVector3f      BrickMinPosition             = Brick.VolumeBounds.Min + FVector3f ( Brick.BrickCoordinate ) * BrickIndirectionMarchingSize;

				Brick.DistanceFieldVolume.Empty ( DistanceField::BrickSize * DistanceField::BrickSize * DistanceField::BrickSize );
				Brick.DistanceFieldVolume.AddZeroed ( DistanceField::BrickSize * DistanceField::BrickSize * DistanceField::BrickSize );

				for ( int32 ZIndex = 0 ; ZIndex < DistanceField::BrickSize ; ZIndex++ )
				{
					if ( Progress.Cancelled ( ) ) { return; }

					for ( int32 YIndex = 0 ; YIndex < DistanceField::BrickSize ; YIndex++ )
					{
						if ( Progress.Cancelled ( ) ) { return; }

						for ( int32 XIndex = 0 ; XIndex < DistanceField::BrickSize ; XIndex++ )
						{
							const FVector3f MarchingPosition = FVector3f ( XIndex , YIndex , ZIndex ) * DistanceFieldMarchingSize + BrickMinPosition;
							const int32     Index            = ( ZIndex * DistanceField::BrickSize * DistanceField::BrickSize + YIndex * DistanceField::BrickSize + XIndex );

							float MinLocalSpaceDistance = LocalSpaceTraceDistance;

							double NearestDistSqr    = 0;
							int32  NearestTriangleID = Spatial.FindNearestTriangle ( FVector3d ( MarchingPosition ) , NearestDistSqr ,
							                                                        UE::Geometry::IMeshSpatial::FQueryOptions ( LocalSpaceTraceDistance ) );
							if ( NearestTriangleID != IndexConstants::InvalidID )
							{
								const float ClosestDistance = FMath::Sqrt ( NearestDistSqr );
								MinLocalSpaceDistance       = FMath::Min ( MinLocalSpaceDistance , ClosestDistance );

								if ( WindingTree.IsInside ( FVector3d ( MarchingPosition ) , 0.5 ) )
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
							const float RescaledDistance = ( VolumeSpaceDistance - DistanceFieldToVolumeScaleBias.Y ) / DistanceFieldToVolumeScaleBias.X;
							check ( DistanceField::DistanceFieldFormat == PF_G8 );
							const uint8 QuantizedDistance       = FMath::Clamp < int32 > ( FMath::FloorToInt ( RescaledDistance * 255.0f + .5f ) , 0 , 255 );
							Brick.DistanceFieldVolume [ Index ] = QuantizedDistance;
							Brick.BrickMaxDistance              = FMath::Max ( Brick.BrickMaxDistance , QuantizedDistance );
							Brick.BrickMinDistance              = FMath::Min ( Brick.BrickMinDistance , QuantizedDistance );
						}                        // X iteration 
					}                            // Y iteration
				}                                // Z iteration
			} , EParallelForFlags::Unbalanced ); // Bricks iteration

			if ( Progress.Cancelled ( ) )
			{
				return nullptr;
			}

			FSparseDistanceFieldMip& OutMip = VolumeDataOut.Mips [ MipIndex ];
			TArray < uint32 >        IndirectionTable;
			IndirectionTable.Empty ( IndirectionDimensions.X * IndirectionDimensions.Y * IndirectionDimensions.Z );
			IndirectionTable.AddUninitialized ( IndirectionDimensions.X * IndirectionDimensions.Y * IndirectionDimensions.Z );

			for ( int32 i = 0 ; i < IndirectionTable.Num ( ) ; i++ )
			{
				IndirectionTable [ i ] = DistanceField::InvalidBrickIndex;
			}

			TArray < FDistanceFieldBrick* > ValidBricks;
			ValidBricks.Reserve ( BricksToCompute.Num ( ) );

			for ( int32 k = 0 ; k < BricksToCompute.Num ( ) ; k++ )
			{
				const FDistanceFieldBrick& ComputedBrick = BricksToCompute [ k ];
				if ( ComputedBrick.BrickMinDistance < MAX_uint8 && ComputedBrick.BrickMaxDistance > MIN_uint8 )
				{
					ValidBricks.Add ( &BricksToCompute [ k ] );
				}
			}

			const uint32 NumBricks      = ValidBricks.Num ( );
			const uint32 BrickSizeBytes = DistanceField::BrickSize * DistanceField::BrickSize * DistanceField::BrickSize * GPixelFormats [ DistanceField::DistanceFieldFormat ].BlockBytes;

			TArray < uint8 > DistanceFieldBrickData;
			DistanceFieldBrickData.Empty ( BrickSizeBytes * NumBricks );
			DistanceFieldBrickData.AddUninitialized ( BrickSizeBytes * NumBricks );

			if ( Progress.Cancelled ( ) )
			{
				return nullptr;
			}

			for ( int32 BrickIndex = 0 ; BrickIndex < ValidBricks.Num ( ) ; BrickIndex++ )
			{
				const FDistanceFieldBrick& Brick            = *ValidBricks [ BrickIndex ];
				const int32                IndirectionIndex = ComputeLinearMarchingIndex ( Brick.BrickCoordinate , IndirectionDimensions );
				IndirectionTable [ IndirectionIndex ]       = BrickIndex;

				check ( BrickSizeBytes == Brick.DistanceFieldVolume.Num() * Brick.DistanceFieldVolume.GetTypeSize() );
				FPlatformMemory::Memcpy ( &DistanceFieldBrickData [ BrickIndex * BrickSizeBytes ] , Brick.DistanceFieldVolume.GetData ( ) , Brick.DistanceFieldVolume.Num ( ) * Brick.DistanceFieldVolume.GetTypeSize ( ) );
			}

			const int32 IndirectionTableBytes = IndirectionTable.Num ( ) * IndirectionTable.GetTypeSize ( );
			const int32 MipDataBytes          = IndirectionTableBytes + DistanceFieldBrickData.Num ( );

			if ( MipIndex == DistanceField::NumMips - 1 )
			{
				VolumeDataOut.AlwaysLoadedMip.Empty ( MipDataBytes );
				VolumeDataOut.AlwaysLoadedMip.AddUninitialized ( MipDataBytes );

				FPlatformMemory::Memcpy ( &VolumeDataOut.AlwaysLoadedMip [ 0 ] , IndirectionTable.GetData ( ) , IndirectionTableBytes );

				if ( DistanceFieldBrickData.Num ( ) > 0 )
				{
					FPlatformMemory::Memcpy ( &VolumeDataOut.AlwaysLoadedMip [ IndirectionTableBytes ] , DistanceFieldBrickData.GetData ( ) , DistanceFieldBrickData.Num ( ) );
				}
			}
			else
			{
				OutMip.BulkOffset = StreamableMipData.Num ( );
				StreamableMipData.AddUninitialized ( MipDataBytes );
				OutMip.BulkSize = StreamableMipData.Num ( ) - OutMip.BulkOffset;
				checkf ( OutMip.BulkSize > 0 , TEXT("DynamicMeshComponent - BulkSize was 0 with %ux%ux%u indirection") , IndirectionDimensions.X , IndirectionDimensions.Y , IndirectionDimensions.Z );

				FPlatformMemory::Memcpy ( &StreamableMipData [ OutMip.BulkOffset ] , IndirectionTable.GetData ( ) , IndirectionTableBytes );

				if ( DistanceFieldBrickData.Num ( ) > 0 )
				{
					FPlatformMemory::Memcpy ( &StreamableMipData [ OutMip.BulkOffset + IndirectionTableBytes ] , DistanceFieldBrickData.GetData ( ) , DistanceFieldBrickData.Num ( ) );
				}
			}

			if ( Progress.Cancelled ( ) )
			{
				return nullptr;
			}

			OutMip.IndirectionDimensions          = IndirectionDimensions;
			OutMip.DistanceFieldToVolumeScaleBias = DistanceFieldToVolumeScaleBias;
			OutMip.NumDistanceFieldBricks         = NumBricks;

			// Account for the border voxels we added
			const FVector3f VirtualUVMin  = FVector3f ( DistanceField::MeshDistanceFieldObjectBorder ) / FVector3f ( IndirectionDimensions * DistanceField::UniqueDataBrickSize );
			const FVector3f VirtualUVSize = FVector3f ( IndirectionDimensions * DistanceField::UniqueDataBrickSize - FIntVector ( 2 * DistanceField::MeshDistanceFieldObjectBorder ) ) / FVector3f ( IndirectionDimensions * DistanceField::UniqueDataBrickSize );

			const FVector3f VolumePositionExtent = LocalSpaceMeshBounds.GetExtent ( ) * LocalToVolumeScale;

			// [-VolumePositionExtent, VolumePositionExtent] -> [VirtualUVMin, VirtualUVMin + VirtualUVSize]
			OutMip.VolumeToVirtualUVScale = VirtualUVSize / ( 2 * VolumePositionExtent );
			OutMip.VolumeToVirtualUVAdd   = VolumePositionExtent * OutMip.VolumeToVirtualUVScale + VirtualUVMin;
		}

		VolumeDataOut.bMostlyTwoSided      = bGenerateAsIfTwoSided;
		VolumeDataOut.LocalSpaceMeshBounds = LocalSpaceMeshBounds;

		if ( Progress.Cancelled ( ) )
		{
			return nullptr;
		}

		VolumeDataOut.StreamableMips.Lock ( LOCK_READ_WRITE );
		uint8* Ptr = ( uint8* ) VolumeDataOut.StreamableMips.Realloc ( StreamableMipData.Num ( ) );
		FMemory::Memcpy ( Ptr , StreamableMipData.GetData ( ) , StreamableMipData.Num ( ) );
		VolumeDataOut.StreamableMips.Unlock ( );
		VolumeDataOut.StreamableMips.SetBulkDataFlags ( BULKDATA_Force_NOT_InlinePayload );

		//const float BuildTime = static_cast < float > ( FPlatformTime::Seconds ( ) - StartTime );

		//UE_LOG ( LogGeometry , Log , TEXT("DynamicMeshComponent - Finished distance field build in %.1fs - %ux%ux%u sparse distance field, %.1fMb total, %.1fMb always loaded, %u%% occupied, %u triangles") ,
		//         BuildTime ,
		//         Mip0IndirectionDimensions.X * DistanceField::UniqueDataBrickSize ,
		//         Mip0IndirectionDimensions.Y * DistanceField::UniqueDataBrickSize ,
		//         Mip0IndirectionDimensions.Z * DistanceField::UniqueDataBrickSize ,
		//         (VolumeDataOut.GetResourceSizeBytes() + VolumeDataOut.StreamableMips.GetBulkDataSize()) / 1024.0f / 1024.0f ,
		//         (VolumeDataOut.AlwaysLoadedMip.GetAllocatedSize()) / 1024.0f / 1024.0f ,
		//         FMath::RoundToInt(100.0f * VolumeDataOut.Mips[0].NumDistanceFieldBricks / (float)(Mip0IndirectionDimensions.X * Mip0IndirectionDimensions.Y * Mip0IndirectionDimensions.Z)) ,
		//         Mesh.TriangleCount() );

		if ( Progress.Cancelled ( ) )
		{
			return nullptr;
		}
	}

	return NewDistanceField;
}

void ULFPMarchingMeshComponent::ComputeNewDistanceFieldData_Completed ( TUniquePtr < FDistanceFieldVolumeData > NewData , TQueue < TFunction < void  ( ) > , EQueueMode::Mpsc >& GameThreadJob )
{
	if ( IsValid ( this ) == false )
	{
		return;
	}

	// Write Data
	{
		FScopeLock Lock ( &DistanceFieldLock );

		CurrentDistanceField = MakeShareable ( NewData.Release ( ) );
	}

	if ( bUpdatingDistanceFieldData == false )
	{
		// mark render state dirty on the game thread to ensure it updates at a safe time (e.g., cannot update when bPostTickComponentUpdate == true)
		bUpdatingDistanceFieldData = true;

		GameThreadJob.Enqueue (
		                       [this] ( )
		                       {
			                       if ( IsValid ( this ) == false )
			                       {
				                       return;
			                       }

			                       bUpdatingDistanceFieldData = false;

			                       OnDistanceFieldGenerated.Broadcast ( this );

			                       // the new distance field will be set when the scene proxy is re-created
			                       if ( GetCurrentSceneProxy ( ) != nullptr )
			                       {
				                       MarkRenderStateDirty ( );
			                       }
		                       }
		                      );
	}
}
