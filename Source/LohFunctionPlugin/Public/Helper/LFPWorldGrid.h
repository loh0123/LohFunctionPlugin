// Copyright by Loh Zhi Kang

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


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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
		FORCEINLINE int32 WordlLocationToIndex(const FVector& Location) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE FIntVector WordlLocationToGridLocation(const FVector& Location) const;


	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool IsWorldLocationValid(const FVector Location) const { return ULFPGridLibrary::IsLocationValid(WordlLocationToGridLocation(Location), GridSize); }


	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool GridLocationToWorldLocation(const FIntVector Location, const bool AddHalfGap, FVector& ReturnLocation, FRotator& ReturnRotation) const;

	UFUNCTION(BlueprintPure, Category = "LFPGridSystem")
		FORCEINLINE bool IndexToWorldLocation(const int32 Index, const bool AddHalfGap, FVector& ReturnLocation, FRotator& ReturnRotation) const;

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPGridSystem | Variable")
		FIntVector GridSize = FIntVector(10);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPGridSystem | Variable")
		FVector GridGap = FVector(100.0f);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPGridSystem | Variable")
		ELFPGridType GridType = ELFPGridType::Rectangular;
};
