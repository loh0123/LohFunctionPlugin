// Copyright (c) 2022 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#pragma once

#include "CoreMinimal.h"
#include "Math/LFPGridLibrary.h"
#include "Components/SceneComponent.h"
#include "LFPWorldGrid.generated.h"


UENUM(BlueprintType)
enum class ELFPGridType : uint8
{
	Rectangular UMETA(DisplayName = "Rectangular"),
	Hexagon		UMETA(DisplayName = "Hexagon"),
	Triangle    UMETA(DisplayName = "Triangle"),
};


UCLASS( ClassGroup=(LFPlugin), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPWorldGrid : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPWorldGrid();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE int32 WorldLocationToIndex(const FVector& Location) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE FIntVector WorldLocationToGridLocation(const FVector& Location) const;


	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool IsWorldLocationValid(const FVector Location) const { return ULFPGridLibrary::IsGridLocationValid(WorldLocationToGridLocation(Location), GridSize); }


	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool GridLocationToWorldLocation(const FIntVector Location, const bool AddHalfGap, FVector& ReturnLocation, FRotator& ReturnRotation) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool IndexToWorldLocation(const int32 Index, const bool AddHalfGap, FVector& ReturnLocation, FRotator& ReturnRotation) const;


	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE int32 GetGridLength() const { return GridSize.X * GridSize.Y * GridSize.Z; }

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE FVector GetVolumeSize(const bool bHalfVolume) const { return FVector(GridSize) * (GridGap * (bHalfVolume ? 0.5 : 1.0)); }

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool GetCenterOrigin() const { return bCenterOrigin; }

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE FIntVector GetGridSize() const { return GridSize; }

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE FVector GetGridGap() const { return GridGap; }

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE ELFPGridType GetGridType() const { return GridType; }

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPGridSystem | Variable")
		bool bCenterOrigin = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPGridSystem | Variable")
		FIntVector GridSize = FIntVector(10);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPGridSystem | Variable")
		FVector GridGap = FVector(100.0f);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPGridSystem | Variable")
		ELFPGridType GridType = ELFPGridType::Rectangular;
};
