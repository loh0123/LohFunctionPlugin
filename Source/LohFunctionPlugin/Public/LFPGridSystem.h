// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LFPGridSystem.generated.h"


UENUM(BlueprintType)
enum class ELFPGridType : uint8
{
	Rectangular UMETA(DisplayName = "Rectangular"),
	Hexagon		UMETA(DisplayName = "Hexagon"),
	Triangle    UMETA(DisplayName = "Triangle"),
};


USTRUCT(BlueprintType)
struct FLGPGridSystemEvent
{
	GENERATED_USTRUCT_BODY()

public:

	FLGPGridSystemEvent() {}

	UPROPERTY()
		TArray<int32> AddIndex;

	UPROPERTY()
		TArray<int32> AddData;

	UPROPERTY()
		TArray<int32> RemoveIndex;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPGridSystem : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPGridSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	FORCEINLINE bool MarkLocation_Internal(FIntVector Locations, const int32& Data, const bool& FlipX, const bool& FlipY, const bool& FlipZ, const FIntVector& MaxRange, const FIntVector& MinRange);

	FORCEINLINE bool UnmarkLocation_Internal(FIntVector Locations, const bool& FlipX, const bool& FlipY, const bool& FlipZ, const FIntVector& MaxRange, const FIntVector& MinRange);

	FORCEINLINE void GetMaxRange(const TArray<FVector>& Locations, const FVector& Offset, TArray<FIntVector>& ReturnConv, FIntVector& Max, FIntVector& Min);

public:

	FORCEINLINE void SyncEvent()
	{
		if (IsEventDirty)
		{
			UpdateEvent(GridEvent);
		}

		return;
	}

	FORCEINLINE bool IsLocationValid_Internal(const FIntVector& Location) const
	{
		return (Location.GetMin() >= 0 && Location.X < GridSize.X && Location.Y < GridSize.Y && Location.Z < GridSize.Z);
	}

	FORCEINLINE int32 GridLocationToIndex(const FIntVector& Location) const
	{
		return Location.X + (Location.Y * GridSize.X) + (Location.Z * (GridSize.X * GridSize.Y));
	}

	FORCEINLINE FIntVector IndexToGridLocation(const int32& Index) const
	{
		FIntVector ReturnData;

		ReturnData.Z = Index / (GridSize.X * GridSize.Y);
		ReturnData.Y = (Index / GridSize.X) - (ReturnData.Z * GridSize.Y);
		ReturnData.X = (Index - (ReturnData.Y * GridSize.X)) - (ReturnData.Z * (GridSize.X * GridSize.Y));

		return ReturnData;
	}

	FORCEINLINE FIntVector WordlLocationToGridLocation(const FVector& Location) const
	{
		if (Location.GetMin() < 0.0f) return FIntVector(-1);

		FVector LocalLocation;

		switch (GridType)
		{
		case ELFPGridType::Rectangular:
			LocalLocation = (Location - GetComponentLocation()) / GridGap;
			break;
		case ELFPGridType::Hexagon:
			LocalLocation = (Location - GetComponentLocation()) / GridGap;
			if ((FMath::FloorToInt(LocalLocation.X) + 1) % 2 == 0) LocalLocation.Y -= 0.5f;
			break;
		case ELFPGridType::Triangle:
			LocalLocation = (Location - GetComponentLocation()) / (GridGap * FVector(0.5, 1, 1));
			break;
		}

		return FIntVector(FMath::FloorToInt(LocalLocation.X), FMath::FloorToInt(LocalLocation.Y), FMath::FloorToInt(LocalLocation.Z));
	}

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool IsLocationValid(const FVector Location) { return IsLocationValid_Internal(WordlLocationToGridLocation(Location)); }

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool IsLocationMarked(const FVector Location);

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool IsLocationsMarked(const TArray<FVector>& Locations, const FVector& Offset, const bool FlipX, const bool FlipY, const bool FlipZ);


	UFUNCTION(BlueprintCallable, Category = "LFPGridSystem")
		FORCEINLINE bool MarkLocation(const FVector Location, const int32 Data);

	UFUNCTION(BlueprintCallable, Category = "LFPGridSystem")
		FORCEINLINE bool MarkLocations(const TArray<FVector>& Locations, const FVector& Offset, const int32 Data, const bool FlipX, const bool FlipY, const bool FlipZ);

	UFUNCTION(BlueprintCallable, Category = "LFPGridSystem")
		FORCEINLINE bool UnmarkLocation(const FVector Location);

	UFUNCTION(BlueprintCallable, Category = "LFPGridSystem")
		FORCEINLINE bool UnmarkLocations(const TArray<FVector>& Locations, const FVector& Offset, const bool FlipX, const bool FlipY, const bool FlipZ);


	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE TArray<int32> GetGridData() { SyncEvent(); return GridData; }

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE int32 GetLocationData(const FVector Location);

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool GetGridWorldLocation(const FIntVector Location,FVector& ReturnLocation, FRotator& ReturnRotation) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool GetGridWorldLocationWithIndex(const int32 Index, FVector& ReturnLocation, FRotator& ReturnRotation) const;


	UFUNCTION(NetMulticast, Reliable, Server)
		void UpdateEvent(const FLGPGridSystemEvent& Data);

	FORCEINLINE void UpdateEvent_Implementation(const FLGPGridSystemEvent& Data);

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPGridSystem | Variable")
		FIntVector GridSize = FIntVector(10);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPGridSystem | Variable")
		FVector GridGap = FVector(100.0f);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPGridSystem | Variable")
		ELFPGridType GridType = ELFPGridType::Rectangular;

	UPROPERTY() TArray<int32> GridData;

	UPROPERTY() FLGPGridSystemEvent GridEvent;

	UPROPERTY() uint8 IsEventDirty : 1;

public:
};
