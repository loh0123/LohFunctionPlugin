// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Tasks/Task.h"
#include "Components/MeshComponent.h"
#include "Components/LFPGridContainerComponent.h"
#include "Rendering/StaticMeshVertexBuffer.h"
#include "Rendering/PositionVertexBuffer.h"
#include "DynamicMeshBuilder.h"
#include "Render/LFPRenderLibrary.h"
#include "PhysicsEngine/BodySetup.h"
#include "PhysicsEngine/PhysicsSettings.h"
#include "LFPVoxelRendererComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LFPVoxelRendererComponent, Log, All);

struct FLFPVoxelRendererFaceDirection
{
	FLFPVoxelRendererFaceDirection(FIntVector F, FIntVector R, FIntVector U) : Forward(F), Right(R), Up(U) {}

	FIntVector Forward, Right, Up = FIntVector::NoneValue;

public:

	FORCEINLINE void SetAxis(FVector3f& X, FVector3f& Y, FVector3f& Z) const
	{
		X = FVector3f(Forward);
		Y = FVector3f(Right);
		Z = FVector3f(Up);
	}
};

namespace LFPVoxelRendererConstantData
{
	static const TArray<FRotator> VertexRotationList =
	{
		FRotator(0.0f	,   0.0f, 0.0f),
		FRotator(90.0f	,   0.0f, 0.0f),
		FRotator(90.0f	, 270.0f, 0.0f),
		FRotator(90.0f	, 180.0f, 0.0f),
		FRotator(90.0f	,  90.0f, 0.0f),
		FRotator(180.0f	,   0.0f, 0.0f),
	};

	static const TArray<FLFPVoxelRendererFaceDirection> FaceDirection = {
		FLFPVoxelRendererFaceDirection(FIntVector(1, 0, 0), FIntVector(0, 1, 0), FIntVector(0, 0, 1)),
		FLFPVoxelRendererFaceDirection(FIntVector(0, 0, 1), FIntVector(0, 1, 0), FIntVector(-1, 0, 0)),
		FLFPVoxelRendererFaceDirection(FIntVector(0, 0, 1), FIntVector(1, 0, 0), FIntVector(0, 1, 0)),
		FLFPVoxelRendererFaceDirection(FIntVector(0, 0, 1), FIntVector(0,-1, 0), FIntVector(1, 0, 0)),
		FLFPVoxelRendererFaceDirection(FIntVector(0, 0, 1), FIntVector(-1, 0, 0), FIntVector(0,-1, 0)),
		FLFPVoxelRendererFaceDirection(FIntVector(-1, 0, 0), FIntVector(0, 1, 0), FIntVector(0, 0,-1)),
	};

	static const TArray<FIntVector> FaceLoopDirectionList = {
		FIntVector(0, 1, 2),
		FIntVector(2, 1, 0),
		FIntVector(2, 0, 1),
		FIntVector(2, 1, 0),
		FIntVector(2, 0, 1),
		FIntVector(0, 1, 2),
	};

	static const TArray<int32> FacePositiveList = {
	 1,
	-1,
	 1,
	 1,
	-1,
	-1,
	};

	static const TArray<int32> SurfaceDirectionID = {
		5,0,3,1,2,4
	};
};

struct FLFPVoxelRendererFaceData
{
	FLFPVoxelRendererFaceData() {}
	FLFPVoxelRendererFaceData(const int32 Reserve)
	{
		FaceDataList.Reserve(Reserve);
	}

	TArray<FInt32Rect> FaceDataList = TArray<FInt32Rect>();
	TArray<FInt32Rect> HiddenFaceDataList = TArray<FInt32Rect>();
};

struct FLFPVoxelRendererSectionData
{
	FLFPVoxelRendererSectionData() {}
	FLFPVoxelRendererSectionData(const FIntVector NewFaceDirectionAmount)
	{
		SetFaceDirectionAmount(NewFaceDirectionAmount);
	}

	TArray<FLFPVoxelRendererFaceData> DataList = TArray<FLFPVoxelRendererFaceData>();

	FIntVector FaceDirectionAmount = FIntVector(0);

	uint32 TriangleCount = 0;

public:

	FORCEINLINE void SetFaceDirectionAmount(const FIntVector NewFaceDirectionAmount)
	{
		FaceDirectionAmount = NewFaceDirectionAmount;

		const int32 MaxFace = FaceDirectionAmount.GetMax();

		const int32 FaceAmount = (FaceDirectionAmount.X * 2) + (FaceDirectionAmount.Y * 2) + (FaceDirectionAmount.Z * 2);

		DataList.Init(FLFPVoxelRendererFaceData(MaxFace), FaceAmount);
	}

	FORCEINLINE FLFPVoxelRendererFaceData& GetVoxelFaceData(const int32 DirectionIndex, const int32 FaceIndex)
	{
		int32 FaceDataIndex = 0;

		for (int32 CurrentLoopIndex = 0; CurrentLoopIndex < DirectionIndex; CurrentLoopIndex++)
		{
			FaceDataIndex += FaceDirectionAmount[LFPVoxelRendererConstantData::FaceLoopDirectionList[CurrentLoopIndex].Z];
		}

		check(DataList.IsValidIndex(FaceDataIndex + FaceIndex));

		return DataList[FaceDataIndex + FaceIndex];
	}

	FORCEINLINE void GenerateRawFaceData(const FVector3f& VoxelHalfSize, const FVector3f& VoxelRenderOffset, TArray<FVector3f>& VertexPosList, TArray<uint32>& IndexList, TArray<FVector2f>& UVList, TArray<FColor>& ColorList, const TFunctionRef<void(const FLFPVoxelRendererFaceDirection&, const int32, const FVector2f&)>& LoopFunc) const
	{
		const FVector3f VoxelFullSize = VoxelHalfSize * 2;

		int32 CurrentFaceIndex = 0;

		for (const auto& Data : DataList)
		{
			int32 CurrentDepthIndex = CurrentFaceIndex;
			int32 CurrentRotationIndex = 0;
			{
				int32 CheckFaceAmount = FaceDirectionAmount[LFPVoxelRendererConstantData::FaceLoopDirectionList[0].Z];

				for (CurrentRotationIndex = 0; CurrentRotationIndex < 5; CurrentRotationIndex++)
				{
					if (CheckFaceAmount > CurrentFaceIndex)
					{
						break;
					}

					CurrentDepthIndex = CurrentFaceIndex - CheckFaceAmount;

					CheckFaceAmount += FaceDirectionAmount[LFPVoxelRendererConstantData::FaceLoopDirectionList[CurrentRotationIndex + 1].Z];
				}
			}

			const FIntVector FaceLoopDirection = LFPVoxelRendererConstantData::FaceLoopDirectionList[CurrentRotationIndex];

			const FLFPVoxelRendererFaceDirection& FaceDirectionData = LFPVoxelRendererConstantData::FaceDirection[CurrentRotationIndex];

			for (const auto& FaceData : Data.FaceDataList)
			{
				FVector2f Scale2D;
				FVector3f APoint, BPoint, Scale;

				APoint[FaceLoopDirection.X] = FaceData.Min.X;
				APoint[FaceLoopDirection.Y] = FaceData.Min.Y;
				APoint[FaceLoopDirection.Z] = CurrentDepthIndex;

				BPoint[FaceLoopDirection.X] = FaceData.Max.X;
				BPoint[FaceLoopDirection.Y] = FaceData.Max.Y;
				BPoint[FaceLoopDirection.Z] = CurrentDepthIndex;

				Scale[FaceLoopDirection.X] = Scale2D.Y = (FaceData.Max.X - FaceData.Min.X) + 1;
				Scale[FaceLoopDirection.Y] = Scale2D.X = (FaceData.Max.Y - FaceData.Min.Y) + 1;
				Scale[FaceLoopDirection.Z] = 1;

				ULFPRenderLibrary::CreateFaceData(
					ULFPRenderLibrary::CreateVertexPosList(
						(FMath::Lerp(APoint, BPoint, 0.5f) * VoxelFullSize) + VoxelRenderOffset,
						FRotator3f(LFPVoxelRendererConstantData::VertexRotationList[CurrentRotationIndex]),
						VoxelHalfSize * Scale
					),
					VertexPosList,
					UVList,
					IndexList
				);

				{
					auto LocalVertPosToColor = [&](const int32 Index)
						{
							FVector3f LocalPos = (VertexPosList[(VertexPosList.Num() - 1) - Index] - VoxelRenderOffset) / VoxelFullSize;

							return FColor(FMath::RoundToInt(LocalPos.X), FMath::RoundToInt(LocalPos.Y), FMath::RoundToInt(LocalPos.Z));
						};

					ColorList.Append(
						{
							LocalVertPosToColor(5),
							LocalVertPosToColor(4),
							LocalVertPosToColor(3),
							LocalVertPosToColor(2),
							LocalVertPosToColor(1),
							LocalVertPosToColor(0)
						}
					);
				}

				LoopFunc(FaceDirectionData, VertexPosList.Num() - 6, Scale2D);
			}

			CurrentFaceIndex++;
		}
	}

	FORCEINLINE void GenerateFaceData(const FVector3f& VoxelHalfSize, const FVector3f& VoxelRenderOffset, FStaticMeshVertexBuffer& VertexDataBuffer, FPositionVertexBuffer& PositionVertexBuffer, FDynamicMeshIndexBuffer32& IndexBuffer, FColorVertexBuffer& ColorVertexBuffer) const
	{
		TArray<FVector3f> VertexPosList;
		TArray<FVector2f> UVDataList;
		TArray<FColor> ColorList;

		const int32 VertexAmount = TriangleCount * 3;

		VertexPosList.Reserve(VertexAmount);
		IndexBuffer.Indices.Reserve(VertexAmount);
		ColorList.Reserve(VertexAmount);

		VertexDataBuffer.Init(VertexAmount, 2);

		GenerateRawFaceData(VoxelHalfSize, VoxelRenderOffset, VertexPosList, IndexBuffer.Indices, UVDataList, ColorList,
			[&](const FLFPVoxelRendererFaceDirection& FaceDirection, const int32 Index, const FVector2f& Scale2D)
			{
				for (int32 Loop = Index; Loop < Index + 6; Loop++)
				{
					VertexDataBuffer.SetVertexTangents(Loop, FVector3f(FaceDirection.Forward), FVector3f(FaceDirection.Right), FVector3f(FaceDirection.Up));
					VertexDataBuffer.SetVertexUV(Loop, 0, UVDataList[Loop] * Scale2D);
					VertexDataBuffer.SetVertexUV(Loop, 1, ((UVDataList[Loop] * -1) + 1) * Scale2D);
				}
			}
		);

		ColorVertexBuffer.InitFromColorArray(ColorList);

		PositionVertexBuffer.Init(VertexPosList, true);
	}

	FORCEINLINE void GenerateCollisionData(const FVector3f& VoxelHalfSize, const FVector3f& VoxelRenderOffset, const int32 SectionIndex, FTriMeshCollisionData* ReturnData) const
	{
		const FVector3f VoxelFullSize = VoxelHalfSize * 2;

		const int32 VertexAmount = TriangleCount * 3;

		const int32 VertexStartIndex = ReturnData->Vertices.Num();

		ReturnData->Indices.Reserve(ReturnData->Indices.Num() + TriangleCount);
		ReturnData->MaterialIndices.Reserve(ReturnData->MaterialIndices.Num() + TriangleCount);

		// See if we should copy UVs
		bool bCopyUVs = UPhysicsSettings::Get()->bSupportUVFromHitResults;
		if (bCopyUVs)
		{
			ReturnData->UVs.AddZeroed(1); // only one UV channel
			ReturnData->UVs[0].Reserve(ReturnData->UVs[0].Num() + VertexAmount);
		}

		TArray<uint32> IndexList;
		TArray<FVector3f> VerticeList;
		TArray<FVector2f> UVDataList;
		TArray<FColor> ColorList;

		IndexList.Reserve(VertexAmount);
		VerticeList.Reserve(VertexAmount);
		UVDataList.Reserve(VertexAmount);
		ColorList.Reserve(VertexAmount);

		GenerateRawFaceData(VoxelHalfSize, VoxelRenderOffset, VerticeList, IndexList, UVDataList, ColorList,
			[&](const FLFPVoxelRendererFaceDirection& FaceDirection, const int32 Index, const FVector2f& Scale2D){}
		);

		ReturnData->Vertices.Append(VerticeList);

		for (int32 Index = 0; Index < IndexList.Num(); Index += 3)
		{
			FTriIndices Triangle;
			Triangle.v0 = IndexList[Index + 0] + VertexStartIndex;
			Triangle.v1 = IndexList[Index + 1] + VertexStartIndex;
			Triangle.v2 = IndexList[Index + 2] + VertexStartIndex;
			ReturnData->Indices.Add(Triangle);
		
			ReturnData->MaterialIndices.Add(SectionIndex);
		
			if (bCopyUVs)
			{
				ReturnData->UVs[0].Append(
					{
						FVector2D(UVDataList[Index + 0]),
						FVector2D(UVDataList[Index + 1]),
						FVector2D(UVDataList[Index + 2])
					}
				);
			}
		}
	}

	FORCEINLINE void GenerateDistanceBoxData(const FIntVector& LocalPosition, const bool bIsInner, int32 Range, TArray<FBox>& ReturnList) const
	{
		const auto& LookUpList = LFPVoxelRendererConstantData::FaceLoopDirectionList;
		const auto& PositiveList = LFPVoxelRendererConstantData::FacePositiveList;

		int32 Offset = 0;

		if (bIsInner) Range--;
		
		for (int32 Index = 0; Index < 6; Index++)
		{
			int32 ScanIndex = LocalPosition[LookUpList[Index].Z];
		
			//if (PositiveList[Index] < 0) ScanIndex = FaceDirectionAmount[LookUpList[Index].Z] - ScanIndex - 1;
		
			ScanIndex += (bIsInner ? PositiveList[Index] * Range : PositiveList[Index] * -1 * Range);
		
			ScanIndex = ScanIndex >= 0 && ScanIndex < FaceDirectionAmount[LookUpList[Index].Z] ? ScanIndex : INDEX_NONE;
		
			const FIntVector4& ScanPosition = FIntVector4(LocalPosition[LookUpList[Index].X], LocalPosition[LookUpList[Index].Y], ScanIndex + Offset, ScanIndex);
		
			//UE_LOG(LogTemp, Warning, TEXT("ScanIndex value is: %d : %d"), ScanIndex + Offset, ScanIndex);
		
			Offset += FaceDirectionAmount[LookUpList[Index].Z];
		
			{
				if (ScanPosition.W == INDEX_NONE) continue;
		
				const FInt32Rect IncludeRange =
					FInt32Rect(
						ScanPosition.X - Range,
						ScanPosition.Y - Range,
						ScanPosition.X + Range,
						ScanPosition.Y + Range
					);
		
				//UE_LOG(LogTemp, Warning, TEXT("IncludeRange is %s"), *IncludeRange.ToString());

				auto ConvertFaceData = [&](const TArray<FInt32Rect>& FaceDataList)
					{
						for (const auto& FaceData : FaceDataList)
						{
							//UE_LOG(LogTemp, Warning, TEXT("Check is %s"), *FaceData.ToString());

							if (IncludeRange.Min.X <= FaceData.Max.X && IncludeRange.Max.X >= FaceData.Min.X && IncludeRange.Min.Y <= FaceData.Max.Y && IncludeRange.Max.Y >= FaceData.Min.Y)
								//if (FaceData.Intersect(IncludeRange))
							{
								FVector Min, Max;

								const float Depth = float(ScanPosition.W) + (float(PositiveList[Index])) * 0.5f;

								//const FVector2D Depth(float(ScanPosition.W) + (float(PositiveList[Index]) * -0.5f), float(ScanPosition.W) + (float(PositiveList[Index]) * 0.5f));

								Min[LookUpList[Index].X] = FaceData.Min.X - 0.5f;
								Min[LookUpList[Index].Y] = FaceData.Min.Y - 0.5f;
								Min[LookUpList[Index].Z] = Depth;

								Max[LookUpList[Index].X] = FaceData.Max.X + 0.5f;
								Max[LookUpList[Index].Y] = FaceData.Max.Y + 0.5f;
								Max[LookUpList[Index].Z] = Depth;

								ReturnList.Add(FBox(Min, Max));
							}
						}
					};

				ConvertFaceData(DataList[ScanPosition.Z].FaceDataList);
				ConvertFaceData(DataList[ScanPosition.Z].HiddenFaceDataList);
			}
		}
	}
};

struct FLFPVoxelRendererThreadResult
{
public:

	TArray<FLFPVoxelRendererSectionData> SectionData = TArray<FLFPVoxelRendererSectionData>();

	//FBox RenderBounds = FBox(EForceInit::ForceInitToZero);

	FKAggregateGeom CollisionData = FKAggregateGeom();

	TSharedPtr<class FDistanceFieldVolumeData> DistanceFieldMeshData = nullptr;

	TSharedPtr<class FCardRepresentationData> LumenCardData = nullptr;

	bool bIsDynamic = true;

public:

	FORCEINLINE void Init(const int32 SectionAmount)
	{
		SectionData.Init(FLFPVoxelRendererSectionData(), SectionAmount);
	}

	FORCEINLINE FLFPVoxelRendererSectionData& AddOrFindSectionData(const int32 SectionIndex)
	{
		if (SectionData.Num() <= SectionIndex)
		{
			SectionData.SetNum(SectionIndex + 1);
		}

		return SectionData[SectionIndex];
	}
};

USTRUCT(BlueprintType)
struct FLFPVoxelRendererSetting
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "VoxelRendererSetting")
		FColor EmptyVoxelNameColor = FColor(uint8(0), uint8(0), uint8(0), uint8(255));

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "VoxelRendererSetting")
		float LumenBoundMultipy = 0.5f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "VoxelRendererSetting")
		FVector VoxelHalfSize = FVector(50.0f);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "VoxelRendererSetting")
		bool bPrintGenerateTime = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "VoxelRendererSetting")
		bool bDisableChuckFaceCulling = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "VoxelRendererSetting")
		bool bDisableRegionFaceCulling = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "VoxelRendererSetting")
		bool bGenerateComplexCollisionData = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "VoxelRendererSetting")
		bool bGenerateSimpleCollisionData = false;

	/* Generate Distance Field And Lumen Card */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "VoxelRendererSetting")
		bool bGenerateLumenData = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "VoxelRendererSetting")
		uint8 LumenQuality = 3;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "VoxelRendererSetting")
		TEnumAsByte<ECollisionTraceFlag> CollisionTraceFlag = ECollisionTraceFlag::CTF_UseDefault;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "VoxelRendererSetting")
		uint8 DynamicUpdateDelayPerComponent = uint8(0);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "VoxelRendererSetting")
		uint8 StaticUpdateDelayPerComponent = uint8(5);

public:

	FORCEINLINE bool HasCollision() const
	{
		return bGenerateComplexCollisionData || bGenerateSimpleCollisionData;
	}
};

UENUM(BlueprintType)
enum class ELFPVoxelRendererMode : uint8
{
	LFP_Dynamic		UMETA(DisplayName = "Dynamic"),
	LFP_Static		UMETA(DisplayName = "Static"),
	LFP_Render		UMETA(DisplayName = "Render"),
	LFP_None		UMETA(DisplayName = "None"),
};

USTRUCT(BlueprintType)
struct FLFPVoxelRendererStatus
{
	GENERATED_BODY()

public:

	FLFPVoxelRendererStatus() : 
		CurrentRendererMode(ELFPVoxelRendererMode::LFP_None),
		NextRendererMode(ELFPVoxelRendererMode::LFP_None),
		DynamicUpdateDelay(0),
		StaticUpdateDelay(0),
		VoxelAttributeDirtyHeightList(TSet<int32>()),
		bIsBodyInvalid(false)
	{}

protected:

	UPROPERTY(VisibleAnywhere, Category = "VoxelRendererStatus") 
		ELFPVoxelRendererMode CurrentRendererMode;

	UPROPERTY(VisibleAnywhere, Category = "VoxelRendererStatus")
		ELFPVoxelRendererMode NextRendererMode;

public:

	UPROPERTY(VisibleAnywhere, Category = "VoxelRendererStatus")
		uint8 DynamicUpdateDelay;

	UPROPERTY(VisibleAnywhere, Category = "VoxelRendererStatus")
		uint8 StaticUpdateDelay;

public:

	UPROPERTY(VisibleAnywhere, Category = "VoxelRendererStatus") 
		TSet<int32> VoxelAttributeDirtyHeightList;

public:

	UPROPERTY(VisibleAnywhere, Category = "VoxelRendererStatus") 
		uint8 bIsBodyInvalid : 1;

public:

	static uint32 CurrentDynamicAmount;

	static uint32 CurrentStaticAmount;

public:

	UPROPERTY() 
		uint32 TickCounter = uint32(0);

public:

	FORCEINLINE ELFPVoxelRendererMode GetCurrentRenderMode() const
	{
		return CurrentRendererMode;
	}

public:

	FORCEINLINE void MarkAttributeDirty(const TSet<int32>& DirtyHeightIndexList)
	{
		VoxelAttributeDirtyHeightList.Append(DirtyHeightIndexList);
	}

	FORCEINLINE void MarkRendererModeDirty(const bool bIsDynamic = true)
	{
		NextRendererMode = bIsDynamic ? ELFPVoxelRendererMode::LFP_Dynamic : ELFPVoxelRendererMode::LFP_Static;

		if (bIsDynamic && CurrentRendererMode == ELFPVoxelRendererMode::LFP_Static)
		{
			UpdateNextRenderMode();
		}
	}

	FORCEINLINE void UpdateNextRenderMode()
	{
		UpdateRenderMode(NextRendererMode);

		NextRendererMode = ELFPVoxelRendererMode::LFP_None;
	}

	FORCEINLINE void UpdateRenderMode(const ELFPVoxelRendererMode NewMode)
	{
		if (CurrentRendererMode == NewMode)
		{
			return;
		}

		if (CurrentRendererMode == ELFPVoxelRendererMode::LFP_Static)
		{
			CurrentStaticAmount--;
		}

		if (CurrentRendererMode == ELFPVoxelRendererMode::LFP_Dynamic)
		{
			CurrentDynamicAmount--;

			MarkRendererModeDirty(false);
		}

		if (NewMode == ELFPVoxelRendererMode::LFP_Static)
		{
			CurrentStaticAmount++;

			ResetStaticCounter();
		}

		if (NewMode == ELFPVoxelRendererMode::LFP_Dynamic)
		{
			CurrentDynamicAmount++;

			ResetDynamicCounter();
		}

		CurrentRendererMode = NewMode;
	}

	FORCEINLINE bool HasRenderDirty() const
	{
		return CanUpdateAttribute() || CurrentRendererMode != ELFPVoxelRendererMode::LFP_None || NextRendererMode != ELFPVoxelRendererMode::LFP_None;
	}

	FORCEINLINE bool CanUpdateAttribute() const
	{
		return VoxelAttributeDirtyHeightList.IsEmpty() == false;
	}

	FORCEINLINE bool DecreaseTickCounter()
	{
		if (TickCounter > 0) TickCounter--;

		return TickCounter == 0;
	}

private:

	FORCEINLINE void ResetDynamicCounter()
	{
		if (TickCounter < CurrentDynamicAmount * DynamicUpdateDelay && TickCounter != 0) return;

		TickCounter = CurrentDynamicAmount * DynamicUpdateDelay;
	}

	FORCEINLINE void ResetStaticCounter()
	{
		TickCounter = CurrentStaticAmount * StaticUpdateDelay;
	}
};

class ULFPGridContainerComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVoxelRendererUpdate);

/**
 * 
 */
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent), ClassGroup = (LFPlugin))
class LOHFUNCTIONPLUGINVOXEL_API ULFPVoxelRendererComponent : public UMeshComponent, public IInterface_CollisionDataProvider
{
	GENERATED_BODY()

/** Core Handling */

public:
	// Sets default values for this component's properties
	ULFPVoxelRendererComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelRendererComponent | Setter")
		FORCEINLINE bool InitializeRenderer(const int32 RegionIndex, const int32 ChuckIndex, ULFPGridContainerComponent* NewVoxelContainer, TArray<UMaterialInstanceDynamic*>& OutDynamicMaterial);

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelRendererComponent | Setter")
		FORCEINLINE bool ReleaseRenderer();

public:

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelRendererComponent | Function")
		FORCEINLINE void UpdateMesh();

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelRendererComponent | Function")
		FORCEINLINE void UpdateAttribute(const TArray<int32>& DirtyIndexList);

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelRendererComponent | Function")
		FORCEINLINE void SetDisableFaceCulling(const bool bChuck, const bool bRegion);

public:

	UFUNCTION(BlueprintPure, Category = "LFPVoxelRendererComponent | Function")
		FORCEINLINE int32 ToGridIndex(const FVector Location) const;

	UFUNCTION(BlueprintPure, Category = "LFPVoxelRendererComponent | Function")
		FORCEINLINE FVector ToWorldLocation(const int32 GridIndex) const;

public:

	UFUNCTION()
		FORCEINLINE void OnChuckUpdate(const FLFPChuckUpdateAction& Data);

	UFUNCTION()
		virtual bool CanUpdateMesh(const FLFPChuckUpdateAction& Data) const;

	UFUNCTION()
		virtual bool CanUpdateAttribute(const FLFPChuckUpdateAction& Data) const;

public: /** Delegate */

	UPROPERTY(BlueprintAssignable, Category = "LFPVoxelRendererComponent | Delegate")
		FOnVoxelRendererUpdate OnVoxelRendererUpdate;

	UPROPERTY(BlueprintAssignable, Category = "LFPVoxelRendererComponent | Delegate")
		FOnVoxelRendererUpdate OnVoxelMeshUpdate;

	UPROPERTY(BlueprintAssignable, Category = "LFPVoxelRendererComponent | Delegate")
		FOnVoxelRendererUpdate OnVoxelAttributesUpdate;


/**********************/

/** Material Handling */

public: // Blueprint Expose Function

	/* This Create A List Of Dynamic Material Instance And Apply VoxelDataTexture And VoxelColorTexture To It (Use Name On Texture Parameter : VoxelAttributesTexture) */
	UFUNCTION(BlueprintCallable, Category = "LFPVoxelRendererComponent | Function")
		FORCEINLINE void SetMaterialList(const TArray<UMaterialInterface*>& Material);

public: // override Handler

	virtual UMaterialInterface* GetMaterialFromCollisionFaceIndex(int32 FaceIndex, int32& SectionIndex) const override;

	virtual int32 GetNumMaterials() const override;

	virtual void SetMaterial(int32 ElementIndex, UMaterialInterface* Material) override;

	/* This Create Dynamic Material Instance And Apply VoxelDataTexture And VoxelColorTexture To It (Use Name On Texture Parameter : VoxelAttributesTexture) */
	virtual UMaterialInstanceDynamic* CreateDynamicMaterialInstance(int32 ElementIndex, class UMaterialInterface* SourceMaterial = nullptr, FName OptionalName = NAME_None) override;

	FORCEINLINE TArray<UMaterialInstanceDynamic*> UpdateMaterialTexture();

/**********************/

/** Share Data Generation Handling */

public:

	/** Get Generation Setting OutSide The Class */
	FORCEINLINE const FLFPVoxelRendererSetting& GetGenerationSetting() const;

	FORCEINLINE const TSharedPtr<FLFPVoxelRendererThreadResult>& GetThreadResult();

private:

	FORCEINLINE bool IsFaceVisible(const FLFPGridPaletteData& FromPaletteData, const FLFPGridPaletteData& ToPaletteData) const;

private:

	FORCEINLINE void GenerateBatchFaceData(ULFPGridContainerComponent* TargetVoxelContainer, TSharedPtr<FLFPVoxelRendererThreadResult>& TargetThreadResult, const FLFPVoxelRendererSetting& TargetGenerationSetting);

	FORCEINLINE void GenerateSimpleCollisionData(ULFPGridContainerComponent* TargetVoxelContainer, TSharedPtr<FLFPVoxelRendererThreadResult>& TargetThreadResult, const FLFPVoxelRendererSetting& TargetGenerationSetting);

	FORCEINLINE void GenerateLumenData(ULFPGridContainerComponent* TargetVoxelContainer, TSharedPtr<FLFPVoxelRendererThreadResult>& TargetThreadResult, const FLFPVoxelRendererSetting& TargetGenerationSetting, const TArray<bool>& MaterialLumenSupportList);

protected: /** Can be override to provide custom behavir */

	virtual FColor GetVoxelAttribute(const FLFPGridPaletteData& VoxelPalette, const TMap<FName, uint8>& TagDataList) const;

	virtual int32 GetVoxelMaterialIndex(const FLFPGridPaletteData& VoxelPalette) const;

private: // Variable

	FLFPVoxelRendererStatus Status;

	UE::Tasks::TTask<void> AttributeOutput;

	UE::Tasks::TTask<TSharedPtr<FLFPVoxelRendererThreadResult>> ThreadOutput;

	TSharedPtr<FLFPVoxelRendererThreadResult> ThreadResult;

public:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPVoxelRendererComponent | Cache")
		TObjectPtr<UTexture2D> AttributesTexture = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "LFPVoxelRendererComponent | Cache")
		TObjectPtr<ULFPGridContainerComponent> VoxelContainer = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "LFPVoxelRendererComponent | Cache")
		int32 RegionIndex = INDEX_NONE;

	UPROPERTY(BlueprintReadOnly, Category = "LFPVoxelRendererComponent | Cache")
		int32 ChuckIndex = INDEX_NONE;

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPVoxelRendererComponent | Setting")
		FLFPVoxelRendererSetting GenerationSetting = FLFPVoxelRendererSetting();

/**********************/

/** Rendering Handling */

protected: // Rendering Handler

	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;

	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "VoxelRendererSetting")
		float DistanceFieldSelfShadowBias = 1.0f;

/**********************/

/** Collision Handling */

public: // Collision Handler

	virtual bool GetTriMeshSizeEstimates(struct FTriMeshCollisionDataEstimates& OutTriMeshEstimates, bool bInUseAllTriData) const override;

	virtual bool GetPhysicsTriMeshData(struct FTriMeshCollisionData* CollisionData, bool InUseAllTriData) override;

	virtual bool ContainsPhysicsTriMeshData(bool InUseAllTriData) const override;

	virtual bool WantsNegXTriMesh() override;

	virtual UBodySetup* GetBodySetup() override;

	FORCEINLINE UBodySetup* CreateBodySetup();

	FORCEINLINE void RebuildPhysicsData();

	FORCEINLINE void FinishPhysicsAsyncCook(bool bSuccess, UBodySetup* FinishedBodySetup);;

private:

	UPROPERTY(Instanced) TObjectPtr<UBodySetup> BodySetup;

/**********************/
};
