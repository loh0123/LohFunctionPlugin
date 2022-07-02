// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "UDynamicMesh.h"
#include "GeometryScriptingCore/Public/GeometryScript/GeometryScriptTypes.h"
#include "Components/DynamicMeshComponent.h"
#include "BaseVoxelMesh.generated.h"

class ULFPVoxelData;

USTRUCT()
struct FLFPVoxelTriangleUpdateData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() int32 GridIndex = INDEX_NONE;

	UPROPERTY() TArray<FIntVector> NewTriangleList;

	UPROPERTY() TArray<int32> NewTriangleGroupList;

	UPROPERTY() TArray<FVector2f> NewUVList;

	UPROPERTY() int32 MaterialID = 0;
};

USTRUCT()
struct FLFPVoxelTriangleData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() TArray<int32> MeshTriangleIndex = {};
};

USTRUCT()
struct FLFPVoxelSectionData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() TSet<int32> TriangleIndexList = {};
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnVoxelSectionUpdate, TSet<int32>);

/**
 *  This class is the base of voxel and is design to be override
 */
UCLASS()
class LOHFUNCTIONPLUGIN_API UBaseVoxelMesh : public UDynamicMesh
{
	GENERATED_UCLASS_BODY()

public:

	virtual void SetupMesh(ULFPVoxelData* NewVoxelData, const int32 NewChuckIndex);

	FORCEINLINE void UpdateMesh() { unimplemented(); }  // Override This

	FORCEINLINE void MarkTrianglesDataForUpdate(const int32 VoxelIndex);

public:

	FORCEINLINE const TArray<FLFPVoxelSectionData>& GetSectionTriangleList() const { return SectionTriangleList; }

	FORCEINLINE int32 GetVoxelSectionCount() const;

	FORCEINLINE bool IsVoxelDataValid() const;

public:

	FORCEINLINE FColor GetTriangleColour(const int32 TriID) const;

protected:

	FORCEINLINE void UpdateVertices(const TArray<FVector>& VerticesList);

	FORCEINLINE void UpdateTriangles(const TArray<FLFPVoxelTriangleUpdateData>& UpdateDataList);

	FORCEINLINE bool IsBlockVisible(const FIntVector GridLocation, const int32 SelfMaterialID) const;

protected: // Initialize Data

	UPROPERTY() TObjectPtr<ULFPVoxelData> VoxelData;

	//UPROPERTY() FIntVector ChuckGridLocation = FIntVector::NoneValue;

	UPROPERTY() int32 ChuckIndex = INDEX_NONE; // Chuck Index On Voxel Data Chuck Array

	UPROPERTY() FVector MeshSize = FVector(400, 346.4, 300); // Voxel Mesh Size

	UPROPERTY() FIntVector VoxelGridSize = FIntVector(1); // How Big This Chuck Is Rendering

	UPROPERTY() FIntVector StartVoxelLocation = FIntVector::NoneValue;  // Start Voxel Location Of The Chuck


protected: // Runtime Data

	//UPROPERTY() TArray<FVector> VerticesList = {};

	UPROPERTY() FIntVector VertexSize = FIntVector::NoneValue;

	UPROPERTY() TSet<int32> DataUpdateList = {};

	UPROPERTY() TArray<FLFPVoxelTriangleData> TriangleDataList = {};

	UPROPERTY() TArray<FLFPVoxelSectionData> SectionTriangleList = {};

	UPROPERTY() TArray<int32> TriangleVoxelIndexList = {};


	//UPROPERTY() TArray<FColor> TriangleColourList = {};

protected:

	FOnVoxelSectionUpdate OnVoxelSectionUpdate;

public:

	FOnVoxelSectionUpdate& OnSectionUpdate() { return OnVoxelSectionUpdate; }
};
