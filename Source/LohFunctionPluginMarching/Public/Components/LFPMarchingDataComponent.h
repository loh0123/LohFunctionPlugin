// Copyright (c) 2023-2025 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "CoreMinimal.h"
#include "Components/LFPChunkedTagDataComponent.h"
#include "LFPMarchingDataComponent.generated.h"

UCLASS(ClassGroup=(Custom), HideCategories="Setting|IndexSize", meta=(BlueprintSpawnableComponent))
class LOHFUNCTIONPLUGINMARCHING_API ULFPMarchingDataComponent : public ULFPChunkedTagDataComponent
{
	GENERATED_BODY()

public:

	// Sets default values for this component's properties
	ULFPMarchingDataComponent( );

protected:

	// Called when the game starts
	virtual void BeginPlay( ) override;

public:

	// Called every frame
	virtual void TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;

public:

	UFUNCTION(BlueprintPure, Category="Marching|Getter")
	const FIntVector& GetDataGridSize( ) const;

	UFUNCTION(BlueprintPure, Category="Marching|Getter")
	const FIntVector& GetChunkGridSize( ) const;

	UFUNCTION(BlueprintPure, Category="Marching|Getter")
	const FIntVector& GetRegionGridSize( ) const;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting|GridSize")
	FIntVector DataGridSize = FIntVector(1);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting|GridSize")
	FIntVector ChunkGridSize = FIntVector(1);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting|GridSize")
	FIntVector RegionGridSize = FIntVector(1);
};
