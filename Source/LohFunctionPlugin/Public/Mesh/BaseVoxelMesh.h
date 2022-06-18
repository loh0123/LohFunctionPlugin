// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "UDynamicMesh.h"
#include "GeometryScriptingCore/Public/GeometryScript/GeometryScriptTypes.h"
#include "Components/DynamicMeshComponent.h"
#include "BaseVoxelMesh.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(BaseVoxelMesh, Warning, All);

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

USTRUCT(BlueprintType)
struct FLFPVoxelTriangleData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelTriangleData")
		TArray<int32> MeshTriangleIndex = {};
};

/**
 *  This class is the base of voxel and is design to be override
 */
UCLASS()
class LOHFUNCTIONPLUGIN_API UBaseVoxelMesh : public UDynamicMesh
{
	GENERATED_BODY()

public:

	virtual void SetupMesh(ULFPVoxelData* NewVoxelData, const int32 NewChuckIndex);

	FORCEINLINE void UpdateMesh() { unimplemented(); }  // Override This

	FORCEINLINE void MarkTrianglesDataForUpdate(const int32 VoxelIndex);

	FORCEINLINE void MarkVoxelDataForUpdate(const int32 VoxelIndex, const bool IsNotSingle) { unimplemented(); }  // Override This

	FORCEINLINE int32 GetVoxelSectionCount() const;

	FORCEINLINE bool isVoxelDataValid() const;

protected:

	FORCEINLINE void UpdateVertices() { unimplemented(); }  // Override This

	FORCEINLINE void UpdateTriangles(const TArray<FLFPVoxelTriangleUpdateData>& UpdateDataList);

	FORCEINLINE bool IsBlockVisible(const FIntVector GridLocation, const int32 SelfMaterialID) const;

protected: // Initialize Data

	UPROPERTY() TObjectPtr<ULFPVoxelData> VoxelData;

	UPROPERTY() FIntVector ChuckGridLocation = FIntVector::NoneValue;

	UPROPERTY() FIntVector StartVoxelLocation = FIntVector::NoneValue;

	UPROPERTY() int32 ChuckIndex = INDEX_NONE;

	UPROPERTY() FVector MeshSize = FVector(400, 346.4, 300);

	UPROPERTY() FIntVector VoxelGridSize = FIntVector(1);


protected: // Runtime Data

	UPROPERTY() TArray<FVector> VerticesList = {};

	UPROPERTY() FIntVector VertexSize = FIntVector::NoneValue;

	UPROPERTY() TArray<FLFPVoxelTriangleData> TriangleDataList = {};

	UPROPERTY() TSet<int32> DataUpdateList = {};

	UPROPERTY() TSet<int32> BufferUpdateList = {};


};
