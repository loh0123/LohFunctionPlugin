// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "LFPVoxelContainerComponent.generated.h"

USTRUCT( BlueprintType )
struct FLFPVoxelContainerSetting
{
	GENERATED_BODY()

public:

	FLFPVoxelContainerSetting() {}

	FLFPVoxelContainerSetting(FIntVector NewVoxelGridSize, FIntVector NewChuckGridSize) :
		VoxelGridSize(NewVoxelGridSize) {}

private:

	UPROPERTY() int32 VoxelLength = 1;

public:

	/* Size Of Voxel Inside Of A Chuck */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelContainerSetting | Setting")
		FIntVector VoxelGridSize = FIntVector(1);

public:

	FORCEINLINE void InitSetting()
	{
		if (VoxelGridSize.GetMin() <= 0.0 ) VoxelGridSize = FIntVector(1);

		VoxelLength = VoxelGridSize.X * VoxelGridSize.Y * VoxelGridSize.Z;
	}

	FORCEINLINE int32 GetVoxelLength() const
	{
		return VoxelLength;
	}
};

USTRUCT( BlueprintType )
struct FLFPVoxelGridPosition
{
	GENERATED_BODY()

	FLFPVoxelGridPosition() {}

	FLFPVoxelGridPosition(const FIntVector NewChuckVector, const int32 NewVoxelIndex) : ChuckVector(ChuckVector), VoxelIndex(NewVoxelIndex) {}

public:

	/** Chuck Index In Array */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelGridPosition")
		FIntVector ChuckVector = FIntVector::NoneValue;

	/** Voxel Index In Array */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelGridPosition")
		int32 VoxelIndex = INDEX_NONE;
};


USTRUCT()
struct FLFPVoxelChuckData
{
	GENERATED_BODY()

private:

	UPROPERTY(SaveGame)
		TArray<uint8> VoxelMaterial = {};

	UPROPERTY(SaveGame) 
		TArray<FColor> VoxelColor = {};

public:

	FORCEINLINE bool IsInitialized() const
	{
		return VoxelMaterial.IsEmpty() == false;
	}

	FORCEINLINE void InitChuckData(const int32 VoxelLength, const uint8 NewVoxelMaterial, const FColor& NewVoxelColor)
	{
		VoxelMaterial.Init(NewVoxelMaterial, VoxelLength);
		VoxelColor.Init(NewVoxelColor, VoxelLength);
	}

	FORCEINLINE void SetChuckMaterial(const int32 VoxelIndex, const uint8 NewVoxelMaterial)
	{
		check(VoxelMaterial.IsValidIndex(VoxelIndex));

		VoxelMaterial[VoxelIndex] = NewVoxelMaterial;
	}

	FORCEINLINE void SetChuckColor(const int32 VoxelIndex, const FColor& NewVoxelColor)
	{
		check(VoxelColor.IsValidIndex(VoxelIndex));

		VoxelColor[VoxelIndex] = NewVoxelColor;
	}

	FORCEINLINE const uint8 GetChuckMaterial(const int32 VoxelIndex) const
	{
		check(VoxelMaterial.IsValidIndex(VoxelIndex));

		return VoxelMaterial[VoxelIndex];
	}

	FORCEINLINE const FColor& GetChuckColor(const int32 VoxelIndex) const
	{
		check(VoxelData.IsValidIndex(VoxelIndex));

		return VoxelColor[VoxelIndex];
	}

};

UENUM( BlueprintType )
enum class ELFPVoxelChuckUpdateState : uint8 {
	LFP_BlockState      UMETA(DisplayName = "BlockState"),
	LFP_BlockSwap       UMETA(DisplayName = "BlockSwap"),
	LFP_Full			UMETA(DisplayName = "Full"),
};


DECLARE_DELEGATE_OneParam(FOnVoxelChuckUpdate, const ELFPVoxelChuckUpdateState);

USTRUCT()
struct FLFPVoxelChuckDelegate
{
	GENERATED_BODY()

public:

	// Update Event For Notify Chuck On Voxel Update
	FOnVoxelChuckUpdate VoxelChuckUpdateEvent;

};

USTRUCT()
struct FLFPVoxelUpdateAction
{
	GENERATED_BODY()

public:

	UPROPERTY()
		TMap<int32, FColor> ChangeColor = TMap<int32, FColor>();

	UPROPERTY()
		TMap<int32, uint8> ChangeMaterial = TMap<int32, uint8>();

	UPROPERTY()
		ELFPVoxelChuckUpdateState UpdateState = ELFPVoxelChuckUpdateState::LFP_BlockState;

public:

	FORCEINLINE void SetUpdateState(ELFPVoxelChuckUpdateState Other) { if (UpdateState < Other) UpdateState = Other; }

public: // Operator

	FLFPVoxelUpdateAction& operator+=(const FLFPVoxelUpdateAction& Other)
	{
		ChangeColor.Append(Other.ChangeColor);
		ChangeMaterial.Append(Other.ChangeMaterial);

		SetUpdateState(Other.UpdateState);

		return *this;
	}
};


UCLASS( Blueprintable, meta = (BlueprintSpawnableComponent), ClassGroup = (LFPlugin) )
class LOHFUNCTIONPLUGIN_API ULFPVoxelContainerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPVoxelContainerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Function")
		FORCEINLINE bool IsVoxelGridPositionValid(const FLFPVoxelGridPosition& VoxelGridPosition) const;

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelContainerComponent | Function")
		FORCEINLINE FString MemorySize();

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelContainerComponent | Setter")
		FORCEINLINE bool SetVoxelData(const FLFPVoxelGridPosition& VoxelGridPosition, const FName VoxelName, const uint8 VoxelStateB, const uint8 VoxelStateA, const bool bInitializeChuck = true);

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelContainerComponent | Setter")
		FORCEINLINE bool SetVoxelState(const FLFPVoxelGridPosition& VoxelGridPosition, const uint8 VoxelStateB, const uint8 VoxelStateA);

	//UFUNCTION(BlueprintPure, Category = "LFPVoxelContainerComponent | Getter")
	//	FORCEINLINE FLFPVoxelIdentifyData GetVoxelData(const FLFPVoxelGridPosition& VoxelGridPosition) const;

protected:

	UFUNCTION()
		FORCEINLINE void UpdateChuckState();

	UFUNCTION()
		FORCEINLINE bool UpdateChuckData();

	UFUNCTION() // Need Rework
		FORCEINLINE void MarkChuckForUpdate(const FIntVector ChuckVector, const FLFPVoxelUpdateAction& UpdateData);

protected:

	FRWLock ContainerThreadLock;

protected: // Initialize Data

	/** What setting this component use when saving the voxel */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPVoxelContainerComponent | Setting")
		FLFPVoxelContainerSetting Setting;

protected:  // Runtime Data

	/** This store the chuck */
	UPROPERTY(SaveGame) 
		TMap<FIntVector, FLFPVoxelChuckData> ChuckDataList;

	/** This store chuck delegate to call */
	UPROPERTY() 
		TMap<FIntVector, FLFPVoxelChuckDelegate> ChuckDelegateList;

	/** This store future chuck update data to apply */
	UPROPERTY() 
		TMap<FIntVector, FLFPVoxelUpdateAction> ChuckUpdateDataList;

	/** This store future chuck update data to apply */
	UPROPERTY()
		TMap<FIntVector, ELFPVoxelChuckUpdateState> ChuckUpdateStateList;
};
