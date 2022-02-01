// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LFPGridArrayHelper.generated.h"


UENUM(BlueprintType)
enum class ELFPGridType : uint8
{
	Rectangular UMETA(DisplayName = "Rectangular"),
	Hexagon		UMETA(DisplayName = "Hexagon"),
	Triangle    UMETA(DisplayName = "Triangle"),
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPGridArrayHelper : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPGridArrayHelper();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE int32 GridLocationToIndex(const FIntVector& Location) const;

	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "LFPGridSystem")
		FORCEINLINE TArray<int32> GridLocationsToIndex(const TArray<FIntVector>& GridLocations, const FIntVector Offset) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE FIntVector IndexToGridLocation(const int32& Index) const;

	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "LFPGridSystem")
		FORCEINLINE TArray<FIntVector> IndexsToGridLocation(const TArray<int32>& Indexs, const int32 Offset) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE int32 WordlLocationToIndex(const FVector& Location) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE FIntVector WordlLocationToGridLocation(const FVector& Location) const;


	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool IsLocationValid(const FIntVector& Location) const { return (Location.GetMin() >= 0 && Location.X < GridSize.X&& Location.Y < GridSize.Y&& Location.Z < GridSize.Z); }


	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool IsWorldLocationValid(const FVector Location) const { return IsLocationValid(WordlLocationToGridLocation(Location)); }


	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool GetGridWorldLocation(const FIntVector Location, const bool AddHalfGap, FVector& ReturnLocation, FRotator& ReturnRotation) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool GetGridWorldLocationWithIndex(const int32 Index, const bool AddHalfGap, FVector& ReturnLocation, FRotator& ReturnRotation) const;


	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "LFPGridSystem")
		FORCEINLINE TArray<int32> SectionGridIndex(const FIntVector SectionSize, const TSet<int32>& IgnoreIndexs) const;

	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "LFPGridSystem")
		FORCEINLINE TArray<int32> RandomSectionGridIndex(const int32 Amount, const FIntVector SectionSize, const TSet<int32>& IgnoreIndexs, const FRandomStream& Seed) const;


	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "LFPGridSystem")
		FORCEINLINE TArray<int32> GetAreaIndex(const int32 Index, const FIntVector Offset, const FIntVector AreaSize) const;

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPGridSystem | Variable")
		int32 GridArratSize = -1;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPGridSystem | Variable")
		FIntVector GridSize = FIntVector(10);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPGridSystem | Variable")
		FVector GridGap = FVector(100.0f);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPGridSystem | Variable")
		ELFPGridType GridType = ELFPGridType::Rectangular;
};
