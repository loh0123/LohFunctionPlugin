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
struct FLFPVoxelGridIndex
{
	GENERATED_BODY()

	FLFPVoxelGridIndex() {}

	FLFPVoxelGridIndex(const int32 ChuckIndex, const int32 VoxelIndex) : ChuckIndex(ChuckIndex), VoxelIndex(VoxelIndex) {}

public:

	/** Chuck Index In Array */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelGridIndex")
		int32 ChuckIndex = INDEX_NONE;

	/** Voxel Index In Array */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelGridIndex")
		int32 VoxelIndex = INDEX_NONE;
};

USTRUCT( BlueprintType )
struct FLFPVoxelTypeData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelTypeData")
		int32 MaterialID = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelTypeData")
		uint8 VoxelR = uint8(0);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelTypeData")
		uint8 VoxelG = uint8(0);
};

/** This Struct Consume 4 Bytes and is use to save block type and state */
USTRUCT()
struct FLFPVoxelIdentifyData
{
	GENERATED_BODY()

public:

	UPROPERTY(SaveGame)
		uint16 VoxelID = 0;

	UPROPERTY(SaveGame)
		uint8 VoxelB = uint8(0);

	UPROPERTY(SaveGame)
		uint8 VoxelA = uint8(0);
};


USTRUCT()
struct FLFPVoxelChuckData
{
	GENERATED_BODY()

private:

	UPROPERTY(SaveGame) 
		TArray<FLFPVoxelIdentifyData> VoxelData = {};

public:

	FORCEINLINE bool IsInitialized() const
	{
		return VoxelData.IsEmpty() == false;
	}

	FORCEINLINE void InitChuckData(const int32 VoxelLength, const FLFPVoxelIdentifyData& VoxelIdentifyData)
	{
		VoxelData.Init(VoxelIdentifyData, VoxelLength);
	}

	FORCEINLINE void SetChuckData(const int32 VoxelIndex, const FLFPVoxelIdentifyData& VoxelIdentifyData)
	{
		check(VoxelData.IsValidIndex(VoxelIndex));

		VoxelData[VoxelIndex] = VoxelIdentifyData;
	}

	FORCEINLINE const FLFPVoxelIdentifyData& GetChuckData(const int32 VoxelIndex) const
	{
		check(VoxelData.IsValidIndex(VoxelIndex));

		return VoxelData[VoxelIndex];
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
		TMap<int32, FLFPVoxelIdentifyData> ChangeData = TMap<int32, FLFPVoxelIdentifyData>();

	UPROPERTY()
		ELFPVoxelChuckUpdateState UpdateState = ELFPVoxelChuckUpdateState::LFP_BlockState;

public: // Operator

	FLFPVoxelUpdateAction& operator+=(const FLFPVoxelUpdateAction& Other)
	{
		ChangeData.Append(Other.ChangeData);

		if (UpdateState < Other.UpdateState) UpdateState = Other.UpdateState;

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

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelContainerComponent | Function")
		FORCEINLINE FString MemorySize();

protected:

	UFUNCTION()
		FORCEINLINE void UpdateChuckState();

	UFUNCTION()
		FORCEINLINE bool UpdateChuckData();

	UFUNCTION()
		FORCEINLINE void MarkChuckForUpdate(const FIntVector ChuckVector, const FLFPVoxelUpdateAction& UpdateData);

protected:

	FRWLock ContainerThreadLock;

	TAtomic<bool> bIsThreadReading = false;

protected: // Initialize Data

	/** What setting this component use when saving the voxel */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPVoxelContainerComponent | Setting")
		FLFPVoxelContainerSetting Setting;

	/** Only support 65,535 item in table
	* This is use to determine what material to use and addition data to pass to material texture
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPVoxelContainerComponent | Setting")
		TObjectPtr<UDataTable> VoxelIDTable;

	UPROPERTY()
		TArray<FName> VoxelIDNameList;

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
