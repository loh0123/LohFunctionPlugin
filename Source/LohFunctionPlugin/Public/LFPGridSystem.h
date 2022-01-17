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

	UPROPERTY() TArray<int32> AddIndex;

	UPROPERTY() TArray<int32> AddData;

	UPROPERTY() TArray<int32> RemoveIndex;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLFPGridUpdateEvent, const FLGPGridSystemEvent&, Data);


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

	UPROPERTY(BlueprintAssignable, Category = "LFPGridSystem | Event")
		FLFPGridUpdateEvent OnUpdateGrid;

private:

	FORCEINLINE bool MarkLocation_Internal(FIntVector Locations, const int32& Data);

	FORCEINLINE bool UnmarkLocation_Internal(FIntVector Locations);

	FORCEINLINE void GetMaxRange(const TArray<FVector>& Locations, const FIntVector& Rotation, const FVector& Offset, TArray<FIntVector>& ReturnConv, FIntVector& Max, FIntVector& Min);

public:

	FORCEINLINE void SyncEvent()
	{
		if (IsEventDirty)
		{
			UpdateEvent(GridEvent);
		}

		return;
	}


	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE int32 GridLocationToIndex(const FIntVector& Location) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE FIntVector IndexToGridLocation(const int32& Index) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE int32 WordlLocationToIndex(const FVector& Location) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE FIntVector WordlLocationToGridLocation(const FVector& Location) const;


	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool IsLocationValid(const FIntVector& Location) const { return (Location.GetMin() >= 0 && Location.X < GridSize.X&& Location.Y < GridSize.Y&& Location.Z < GridSize.Z); }

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool IsLocationMarked(const FIntVector& Location);


	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool IsWorldLocationValid(const FVector Location) const { return IsLocationValid(WordlLocationToGridLocation(Location)); }

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool IsWorldLocationMarked(const FVector Location);

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool IsWorldLocationsMarked(const TArray<FVector>& Locations, const FIntVector& Rotation, const FVector& Offset, const bool MarkInvalid = false);


	UFUNCTION(BlueprintCallable, Category = "LFPGridSystem")
		FORCEINLINE bool MarkLocation(const FVector Location, const int32 Data);

	UFUNCTION(BlueprintCallable, Category = "LFPGridSystem")
		FORCEINLINE bool MarkLocations(const TArray<FVector>& Locations, const FIntVector& Rotation, const FVector& Offset, const int32 Data);

	UFUNCTION(BlueprintCallable, Category = "LFPGridSystem")
		FORCEINLINE bool UnmarkLocation(const FVector Location);

	UFUNCTION(BlueprintCallable, Category = "LFPGridSystem")
		FORCEINLINE bool UnmarkLocations(const TArray<FVector>& Locations, const FIntVector& Rotation, const FVector& Offset);


	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE TArray<int32> GetGridData() { SyncEvent(); return GridData; }

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE int32 GetLocationData(const FVector Location);

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool GetGridWorldLocation(const FIntVector Location,FVector& ReturnLocation, FRotator& ReturnRotation) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool GetGridWorldLocationWithIndex(const int32 Index, FVector& ReturnLocation, FRotator& ReturnRotation) const;


	UFUNCTION(BlueprintCallable, Category = "LFPGridSystem")
		FORCEINLINE bool TryFitTemplate(const TArray<FVector>& Template, const FVector& Offset, FIntVector& NeedRotation, const bool CanRotateX, const bool CanRotateY, const bool CanRotateZ);

	UFUNCTION(BlueprintCallable, Category = "LFPGridSystem")
		FORCEINLINE bool TryFitTemplates(const TArray<FVector>& Template, const TArray<FVector>& Offsets, FVector& FitOffset, FIntVector& NeedRotation, const bool CanRotateX, const bool CanRotateY, const bool CanRotateZ);

	UFUNCTION(BlueprintCallable, Category = "LFPGridSystem")
		FORCEINLINE bool TryFitTemplateNear(const TArray<FVector>& Template, const FVector& Offset, const FIntVector& CheckSize, FVector& FitOffset, FIntVector& NeedRotation, const bool CanRotateX, const bool CanRotateY, const bool CanRotateZ);


	UFUNCTION(BlueprintCallable, Category = "LFPGridSystem")
		FORCEINLINE TArray<int32> RandomGridIndex(const int32 Amount, const FIntVector SectionSize, const bool ReturnCenterIndex, const FRandomStream& Seed);


	UFUNCTION(BlueprintCallable, Category = "LFPGridSystem")
		FORCEINLINE TArray<int32> GetAreaIndex(const int32 CenterIndex, const FIntVector AreaSize);


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
