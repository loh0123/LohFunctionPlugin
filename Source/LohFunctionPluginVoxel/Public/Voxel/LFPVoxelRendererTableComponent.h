// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Voxel/LFPVoxelRendererComponent.h"
#include "LFPVoxelRendererTableComponent.generated.h"

USTRUCT(BlueprintType)
struct FLFPVoxelTypeTable : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VoxelTypeTable") int32 VoxelMaterial = INDEX_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VoxelTypeTable") FColor VoxelDefaultColor = FColor(0);
};

UENUM(BlueprintType)
enum class ELFPVoxelAttributeOperation : uint8
{
	Addition	UMETA(DisplayName = "Addition"),
	Override	UMETA(DisplayName = "Override"),
	Blend		UMETA(DisplayName = "Blend"),
	Min			UMETA(DisplayName = "Min"),
	Max			UMETA(DisplayName = "Max"),
};

USTRUCT(BlueprintType)
struct FLFPVoxelAttributeTable : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VoxelAttributeTable") FColor VoxelColor = FColor(0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VoxelAttributeTable") FColor VoxelData = FColor(0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VoxelAttributeTable") ELFPVoxelAttributeOperation Operation = ELFPVoxelAttributeOperation::Addition;
};

/**
 * 
 */
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent), ClassGroup = (LFPlugin))
class LOHFUNCTIONPLUGINVOXEL_API ULFPVoxelRendererTableComponent : public ULFPVoxelRendererComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	
	virtual FColor GetVoxelAttribute(const FLFPGridPaletteData& VoxelPalette, const TMap<FName, uint8>& TagDataList) const override;

	virtual int32 GetVoxelMaterialIndex(const FLFPGridPaletteData& VoxelPalette) const override;

	virtual bool CanUpdateMesh(const FLFPChuckUpdateAction& Data) const override;

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPVoxelRendererTableComponent | Setting")
		TObjectPtr<UDataTable> VoxelTypeTable = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPVoxelRendererTableComponent | Setting")
		TObjectPtr<UDataTable> VoxelAttributeTable = nullptr;
};
