// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LFPTerrainSystem.generated.h"

USTRUCT(BlueprintType)
struct FLGPTerrainData
{
	GENERATED_USTRUCT_BODY()

public:

	FLGPTerrainData() {}
	FLGPTerrainData(FIntVector Pos) : GridPosition(Pos) {}

	UPROPERTY(BlueprintReadWrite, EditAnywhere) FIntVector GridPosition = FIntVector(-1);

	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector Offset = FVector(0);

	UPROPERTY(BlueprintReadWrite, EditAnywhere) int32 TerrainID = -1;

	FORCEINLINE bool operator==(const FLGPTerrainData& Other) const
	{
		return Other.GridPosition == GridPosition;
	}

	FORCEINLINE bool operator==(const FIntVector& Other) const
	{
		return Other == GridPosition;
	}
};

USTRUCT(BlueprintType)
struct FLGPTerrainSystemEvent
{
	GENERATED_USTRUCT_BODY()

public:

	FLGPTerrainSystemEvent() {}

	UPROPERTY()
		TArray<FLGPTerrainData> AddList;

	UPROPERTY()
		TArray<FIntVector> RemoveList;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLFPTerrainAddEvent, const TArray<FLGPTerrainData>&, AddList);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLFPTerrainRemoveEvent, const TArray<FIntVector>&, RemoveList);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPTerrainSystem : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPTerrainSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	FORCEINLINE int32 GridLocationToIndex(const FIntVector& Location) const { return Location.X + (Location.Y * GridSize.X) + (Location.Z * (GridSize.X * GridSize.Y)); }


	UFUNCTION(BlueprintPure, Category = "LFPTerrainSystem")
		FORCEINLINE FIntVector WorldToTerrainLocation(FVector Location) const;
	
	UFUNCTION(BlueprintPure, Category = "LFPTerrainSystem")
		FORCEINLINE FVector TerrainToWorldLocation(FIntVector Location) const;
	
	UFUNCTION(BlueprintPure, Category = "LFPTerrainSystem")
		FORCEINLINE bool IsTerrainLocationValid(FIntVector Location) const;


	UFUNCTION(BlueprintCallable, Category = "LFPGridSystem", BlueprintAuthorityOnly)
		FORCEINLINE bool AddTerrain(const FLGPTerrainData Data);
	
	UFUNCTION(BlueprintCallable, Category = "LFPGridSystem", BlueprintAuthorityOnly)
		FORCEINLINE bool RemoveTerrain(const FIntVector GridPosition);
	
	UFUNCTION(BlueprintPure, Category = "LFPTerrainSystem")
		FORCEINLINE bool GetTerrain(const FIntVector GridPosition, FLGPTerrainData& ReturnData);


	UFUNCTION(NetMulticast, Reliable, Server)
		void UpdateEvent(const FLGPTerrainSystemEvent& Data);

	FORCEINLINE void UpdateEvent_Implementation(const FLGPTerrainSystemEvent& Data);


	UPROPERTY(BlueprintAssignable, Category = "LFPTerrainSystem | Event")
		FLFPTerrainAddEvent OnAddTerrain;
	
	UPROPERTY(BlueprintAssignable, Category = "LFPTerrainSystem | Event")
		FLFPTerrainRemoveEvent OnRemoveTerrain;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPTerrainSystem | Variable")
		FIntVector GridSize = FIntVector(10);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPTerrainSystem | Variable")
		FVector GridGap = FVector(100.0f);

	UPROPERTY() TArray<FLGPTerrainData> TerrainData;

	UPROPERTY() FLGPTerrainSystemEvent TerrainEvent;

	UPROPERTY() uint8 IsEventDirty : 1;
};
