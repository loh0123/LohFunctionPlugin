// Copyright (c) 2022 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Math/LFPGridLibrary.h"
#include "Voxel/LFPVoxelContainerInterface.h"
#include "LFPVoxelContainer.generated.h"

USTRUCT(BlueprintType)
struct FLFPVoxelChuckInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelChuckInfo")
		int32 ChuckIndex = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelChuckInfo")
		FIntVector StartVoxelLocation = FIntVector::NoneValue;
};

USTRUCT(BlueprintType)
struct FLFPVoxelGridIndex
{
	GENERATED_USTRUCT_BODY()

	FLFPVoxelGridIndex() {}

	FLFPVoxelGridIndex(const int32 ChuckIndex, const int32 VoxelIndex) : ChuckIndex(ChuckIndex), VoxelIndex(VoxelIndex) {}

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelGridIndex")
		int32 ChuckIndex = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelGridIndex")
		int32 VoxelIndex = INDEX_NONE;
};

USTRUCT(BlueprintType)
struct FLFPVoxelAttributeV2 : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelAttribute")
		FColor VertexColor = FColor(255);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelAttribute")
		int32 MaterialID = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelAttribute")
		uint8 TextureOffset = uint8(0);
};

USTRUCT()
struct FLFPVoxelWriteAction
{
	GENERATED_BODY()

public:

	UPROPERTY() TMap<int32, FName> NameData = TMap<int32, FName>();

	UPROPERTY() TMap<int32, FColor> ColorData = TMap<int32, FColor>();

	UPROPERTY() bool bWantUpdateName = false;

	UPROPERTY() bool bWantUpdateColor = false;

	UPROPERTY() uint16 TickDelayCount = 0;

	FLFPVoxelWriteAction& operator+=(const FLFPVoxelWriteAction& Other)
	{
		NameData.Append(Other.NameData);
		ColorData.Append(Other.ColorData);

		bWantUpdateName = bWantUpdateName || Other.bWantUpdateName;
		bWantUpdateColor = bWantUpdateColor || Other.bWantUpdateColor;

		TickDelayCount = FMath::Max(TickDelayCount, Other.TickDelayCount);

		return *this;
	}
};

DECLARE_DELEGATE(FOnVoxelChuckNameUpdate);

DECLARE_DELEGATE(FOnVoxelChuckColorUpdate);

USTRUCT()
struct FLFPVoxelChuckDataV2
{
	GENERATED_USTRUCT_BODY()

	FLFPVoxelChuckDataV2() {}

	FLFPVoxelChuckDataV2(const FLFPVoxelChuckDataV2& Data) : VoxelNameData(Data.VoxelNameData) {}

public:

	UPROPERTY() TArray<FName> VoxelNameData = {};

	UPROPERTY() TArray<FColor> VoxelColorData = {};

public:

	// Update Event For Notify Chuck On Voxel Update
	FOnVoxelChuckNameUpdate VoxelChuckNameUpdateEvent;

	// Update Event For Notify Chuck On Change Of Color
	FOnVoxelChuckColorUpdate VoxelChuckColorUpdateEvent;

public:

	FORCEINLINE bool IsInitialized() const
	{
		return VoxelNameData.IsEmpty() == false;
	}

	FORCEINLINE void InitChuckData(const int32 VoxelLength, const FName& VoxelName)
	{
		VoxelNameData.Init(VoxelName, VoxelLength);
		VoxelColorData.Init(FColor(0), VoxelLength);
	}

	FORCEINLINE void SetVoxelName(const int32 VoxelIndex, const FName& VoxelName)
	{
		check(VoxelNameData.IsValidIndex(VoxelIndex));

		VoxelNameData[VoxelIndex] = VoxelName;
	}

	FORCEINLINE void SetVoxelColor(const int32 VoxelIndex, const FColor& VoxelColor)
	{
		check(VoxelColorData.IsValidIndex(VoxelIndex));

		VoxelColorData[VoxelIndex] = VoxelColor;
	}

	template <typename UserClass, typename Func01, typename Func02>
	FORCEINLINE void Connect(UserClass* InUserObject, Func01 InVoxelFunc, Func02 InColorFunc)
	{
		VoxelChuckNameUpdateEvent.BindUObject(InUserObject, InVoxelFunc);
		VoxelChuckColorUpdateEvent.BindUObject(InUserObject, InColorFunc);
	}

	FORCEINLINE void SendNameUpdateEvent()
	{
		VoxelChuckNameUpdateEvent.ExecuteIfBound();
	}

	FORCEINLINE void SendColorUpdateEvent()
	{
		VoxelChuckColorUpdateEvent.ExecuteIfBound();
	}

	FORCEINLINE void Disconnect()
	{
		VoxelChuckNameUpdateEvent.Unbind();
		VoxelChuckColorUpdateEvent.Unbind();
	}
};

USTRUCT(BlueprintType)
struct FLFPVoxelContainerSettingV2
{
	GENERATED_USTRUCT_BODY()

public:

	FLFPVoxelContainerSettingV2() {}

	FLFPVoxelContainerSettingV2(FIntVector NewVoxelGridSize, FIntVector NewChuckGridSize, FName NewInvisibleName) : 
		VoxelGridSize(NewVoxelGridSize), ChuckGridSize(NewChuckGridSize), InvisibleName(NewInvisibleName) {}

public:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelContainerSetting | Cache")
		int32 ChuckLength = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelContainerSetting | Cache")
		int32 VoxelLength = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "VoxelContainerSetting | Cache")
		FVector HalfRenderBound = FVector(-1.0f);

public:

	/* Size Of Voxel Inside Of A Chuck */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelContainerSetting | Setting")
		FIntVector VoxelGridSize = FIntVector(1);

	/* Size Of Chuck Store In This Container */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelContainerSetting | Setting")
		FIntVector ChuckGridSize = FIntVector(1);

	/* The Name To Check For Voxel Visible */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelContainerSetting | Setting")
		FName InvisibleName = FName("None");

	/* Half Of The Size Of The Voxel Should Be Render */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelContainerSetting | Setting")
		FVector VoxelHalfSize = FVector(100);

	/* Size Of The UV This Mesh Is Render On */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelContainerSetting | Setting")
		FIntPoint VoxelUVRound = FIntPoint(1);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelContainerSetting | Setting")
		int32 WriteActionTickDelay = 10;

public:

	FORCEINLINE void InitSetting()
	{
		if (VoxelGridSize.GetMin() <= 0) VoxelGridSize = FIntVector(1);
		if (ChuckGridSize.GetMin() <= 0) ChuckGridSize = FIntVector(1);
		if (VoxelHalfSize.GetMin() <= 0) VoxelHalfSize = FVector(50.0f);
		if (VoxelUVRound.GetMin() <= 0) VoxelUVRound = FIntPoint(1);

		VoxelLength = VoxelGridSize.X * VoxelGridSize.Y * VoxelGridSize.Z;
		ChuckLength = ChuckGridSize.X * ChuckGridSize.Y * ChuckGridSize.Z;
		HalfRenderBound = VoxelHalfSize * FVector(VoxelGridSize);
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChuckInitialize, const int32, ChuckIndex);

/**
 *
 */
UCLASS(meta = (BlueprintSpawnableComponent), ClassGroup = Voxel)
class LOHFUNCTIONPLUGIN_API ULFPVoxelContainer : public UActorComponent
{
	GENERATED_BODY()

public:

	ULFPVoxelContainer();

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

protected:

	FRWLock ContainerThreadLock;

	TAtomic<bool> bIsThreadReading = false;

public:

	UPROPERTY(BlueprintAssignable, Category = "VoxelData | Event")
		FOnChuckInitialize VoxelChuckNameUpdateEvent;

protected: // Initialize Data

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "VoxelData | Setting")
		FLFPVoxelContainerSettingV2 ContainerSetting;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "VoxelData | Setting") 
		TObjectPtr<UDataTable> VoxelAttributeTable;


protected:  // Runtime Data

	UPROPERTY(replicated) TArray<FLFPVoxelChuckDataV2> ChuckData;

	UPROPERTY() TSet<int32> BatchChuckNameUpdateList;

	UPROPERTY() TSet<int32> BatchChuckColorUpdateList;

	UPROPERTY() TMap<int32, FLFPVoxelWriteAction> ChuckWriteActionList;


protected: // Empty Data

	const FLFPVoxelAttributeV2 DefaultVoxelAttribute = FLFPVoxelAttributeV2();


public: /* Function For Render Component To Multithread */

	FORCEINLINE FRWLock& GetContainerThreadLock() { return ContainerThreadLock; }

	FORCEINLINE void SetContainerThreadReading(const bool bIsReading) { bIsThreadReading = bIsReading; }


public: /* Function For Render Component To Getting Container Init Data */

	FORCEINLINE const FLFPVoxelContainerSettingV2& GetContainerSetting() const { return ContainerSetting; }


public:  /* Function For Render Component To Check Container Data Is Safe */

	FORCEINLINE bool IsChuckIndexValid(const int32 ChuckIndex) const { return ChuckData.IsValidIndex(ChuckIndex); }

	FORCEINLINE bool IsVoxelIndexValid(const FLFPVoxelGridIndex VoxelGridIndex) const { return IsChuckIndexValid(VoxelGridIndex.ChuckIndex) ? ChuckData[VoxelGridIndex.ChuckIndex].VoxelNameData.IsValidIndex(VoxelGridIndex.VoxelIndex) : false; }


public: /* Function For Render Component To Get Container Data */

	FORCEINLINE FLFPVoxelChuckInfo GetChuckInfo(const int32 ChuckIndex) const
	{
		check(IsChuckIndexValid(ChuckIndex));

		FLFPVoxelChuckInfo ChuckInfo;

		const FIntVector ChuckGridLocation = ULFPGridLibrary::ToGridLocation(ChuckIndex, ContainerSetting.ChuckGridSize);

		ChuckInfo.ChuckIndex = ChuckIndex;
		ChuckInfo.StartVoxelLocation = FIntVector(ChuckGridLocation.X * ContainerSetting.VoxelGridSize.X, ChuckGridLocation.Y * ContainerSetting.VoxelGridSize.Y, ChuckGridLocation.Z * ContainerSetting.VoxelGridSize.Z);

		return ChuckInfo;
	}

	/* This Is Use To Access Atttribute Outside Of The Local Chuck */
	FORCEINLINE const FLFPVoxelAttributeV2& GetVoxelAttribute(const FLFPVoxelGridIndex VoxelGridIndex) const
	{
		return IsVoxelIndexValid(VoxelGridIndex) && IsChuckInitialized(VoxelGridIndex.ChuckIndex) ? GetVoxelAttributeByName(GetVoxelName(VoxelGridIndex)) : DefaultVoxelAttribute;
	}

	/* This Is Use To Access Atttribute On Local Chuck */
	FORCEINLINE const FLFPVoxelAttributeV2& GetVoxelAttributeByName(const FName VoxelName) const
	{
		uint8* Data = VoxelAttributeTable != nullptr ? VoxelAttributeTable->FindRowUnchecked(VoxelName) : nullptr;

		if (Data != nullptr)
		{
			return *(reinterpret_cast<FLFPVoxelAttributeV2*>(Data));
		}
		else
		{
			return DefaultVoxelAttribute;
		}
	}

	/* This Is Use To Access Voxel Name Outside Of The Local Chuck */
	FORCEINLINE const FName& GetVoxelName(const FLFPVoxelGridIndex VoxelGridIndex) const
	{
		return IsVoxelIndexValid(VoxelGridIndex) && IsChuckInitialized(VoxelGridIndex.ChuckIndex) ? ChuckData[VoxelGridIndex.ChuckIndex].VoxelNameData[VoxelGridIndex.VoxelIndex] : ContainerSetting.InvisibleName;
	}

	/* This Is Use To Access Voxel Name On Local Chuck */
	FORCEINLINE const TArray<FName>& GetVoxelNameList(const int32 ChuckIndex) const
	{
		check(IsChuckIndexValid(ChuckIndex));

		return ChuckData[ChuckIndex].VoxelNameData;
	}

	/* This Is Use To Access Voxel Name On Local Chuck */
	FORCEINLINE const TArray<FColor>& GetVoxelColorList(const int32 ChuckIndex) const
	{
		check(IsChuckIndexValid(ChuckIndex));

		return ChuckData[ChuckIndex].VoxelColorData;
	}

	/* This Is Use To Access Voxel Visible Outside Of The Local Chuck */
	FORCEINLINE bool IsVoxelVisible(const FLFPVoxelGridIndex VoxelGridIndex, const int32 CurrentMaterialID ) const
	{
		const FName& CheckName = GetVoxelName(VoxelGridIndex);

		return CheckName != ContainerSetting.InvisibleName && GetVoxelAttributeByName(CheckName).MaterialID == CurrentMaterialID;
	}

	/* This Is Use To Access Voxel Visible On Local Chuck */
	FORCEINLINE bool IsVoxelVisibleByName(const FName& VoxelName) const
	{
		return VoxelName != ContainerSetting.InvisibleName;
	}


public: /* Function For Prepare Render Component To Use Container Data */

	template <typename UserClass, typename Func01, typename Func02>
	FORCEINLINE void ConnectVoxelUpdateEvent(const int32 ChuckIndex, UserClass* InUserObject, Func01 InVoxelFunc, Func02 InColorFunc)
	{
		check(ChuckData.IsValidIndex(ChuckIndex));

		ChuckData[ChuckIndex].Connect(InUserObject, InVoxelFunc, InColorFunc);
	}

	FORCEINLINE void DiconnectVoxelUpdateEvent(const int32 ChuckIndex)
	{
		check(ChuckData.IsValidIndex(ChuckIndex));

		ChuckData[ChuckIndex].Disconnect();
	}

	FORCEINLINE void InitializeChuck(const int32 ChuckIndex, const FName& VoxelName, const bool bSkipLock = false)
	{
		check(IsChuckIndexValid(ChuckIndex));

		if (bSkipLock == false) FRWScopeLock WriteLock(GetContainerThreadLock(), SLT_Write);

		if (ChuckData[ChuckIndex].IsInitialized() == false)
		{
			ChuckData[ChuckIndex].InitChuckData(ContainerSetting.VoxelLength, VoxelName);

			if (GetOwner()->Implements<ULFPVoxelContainerInterface>())
			{
				const FIntVector ChuckGridLocation = ULFPGridLibrary::ToGridLocation(ChuckIndex, ContainerSetting.ChuckGridSize);
			
				const FIntVector VoxelStartLocation = FIntVector(ChuckGridLocation.X * ContainerSetting.VoxelGridSize.X, ChuckGridLocation.Y * ContainerSetting.VoxelGridSize.Y, ChuckGridLocation.Z * ContainerSetting.VoxelGridSize.Z);

				ParallelFor(ContainerSetting.VoxelLength, [&](const int32 VoxelIndex) {
					FName TargetVoxelName;
					FColor TargetVoxelColor;

					ILFPVoxelContainerInterface::Execute_InitializeVoxelData(GetOwner(), VoxelStartLocation + ULFPGridLibrary::ToGridLocation(VoxelIndex, ContainerSetting.VoxelGridSize), TargetVoxelName, TargetVoxelColor);

					ChuckData[ChuckIndex].SetVoxelName(VoxelIndex, TargetVoxelName);
					ChuckData[ChuckIndex].SetVoxelColor(VoxelIndex, TargetVoxelColor);
					});
			}
		}

		//ChuckData[ChuckIndex].SendNameUpdateEvent();
		//ChuckData[ChuckIndex].SendColorUpdateEvent();
		
		VoxelChuckNameUpdateEvent.Broadcast(ChuckIndex);
	}

protected: /* Helper Function */

	FORCEINLINE void AddChuckWriteNameAction(const FLFPVoxelGridIndex& VoxelGridIndex, const FName& VoxelName, const bool bWantUpdate)
	{
		FLFPVoxelWriteAction* Action = ChuckWriteActionList.Find(VoxelGridIndex.ChuckIndex);

		if (Action == nullptr)
		{
			FLFPVoxelWriteAction NewAction;

			NewAction.bWantUpdateName = bWantUpdate;

			NewAction.NameData.Add(VoxelGridIndex.VoxelIndex, VoxelName);

			ChuckWriteActionList.Add(VoxelGridIndex.ChuckIndex, NewAction);
		}
		else
		{
			Action->bWantUpdateName = Action->bWantUpdateName || bWantUpdate;

			Action->NameData.Add(VoxelGridIndex.VoxelIndex, VoxelName);
		}

		return;
	}

	FORCEINLINE void AddChuckWriteColorAction(const FLFPVoxelGridIndex& VoxelGridIndex, const FColor& VoxelColor, const bool bWantUpdate)
	{
		FLFPVoxelWriteAction* Action = ChuckWriteActionList.Find(VoxelGridIndex.ChuckIndex);

		if (Action == nullptr)
		{
			FLFPVoxelWriteAction NewAction;

			NewAction.bWantUpdateColor = bWantUpdate;

			NewAction.ColorData.Add(VoxelGridIndex.VoxelIndex, VoxelColor);

			ChuckWriteActionList.Add(VoxelGridIndex.ChuckIndex, NewAction);
		}
		else
		{
			Action->bWantUpdateColor = Action->bWantUpdateName || bWantUpdate;

			Action->ColorData.Add(VoxelGridIndex.VoxelIndex, VoxelColor);
		}

		return;
	}

public:

	FORCEINLINE FLFPVoxelWriteAction* FindOrAddChuckWriteAction(const int32& ChuckIndex, const bool bResetDelay = true);

protected:

	virtual void BeginPlay() override;

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public: /* Function For External Blueprint Or C++ To Use */

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE int32 GetContainerSize();

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void UpdateChuckWriteAction();

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void UpdateChuckName();

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void UpdateChuckColor();

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void MarkChuckForNameUpdate(const int32 ChuckIndex, const bool bUpdateNearbyChuck = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void MarkChuckForColorUpdate(const int32 ChuckIndex, const bool bUpdateNearbyChuck = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE bool SetupVoxelData(UDataTable* NewVoxelAttributeTable, const FLFPVoxelContainerSettingV2 NewSetting);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE bool IsChuckInitialized(const int32 ChuckIndex) const;

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE FLFPVoxelGridIndex ToVoxelGridIndex(const FIntVector VoxelGridLocation) const;

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE FIntVector ToVoxelGridLocation(const FLFPVoxelGridIndex VoxelGridIndex) const;

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetVoxelGridColor(const FLFPVoxelGridIndex VoxelGridIndex, const FColor VoxelColor, const bool bInitializeChuck = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetVoxelGridName(const FLFPVoxelGridIndex VoxelGridIndex, const FName VoxelAttributeName, const bool bInitializeChuck = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetVoxelGridNameList(const TArray<FLFPVoxelGridIndex>& VoxelGridIndexList, const FName VoxelAttributeName, const bool bInitializeChuck = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetChuckGridName(const int32 ChuckIndex, const FName VoxelAttributeName, const bool bInitializeChuck = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetChuckGridNameWithHeight(const int32 ChuckIndex, const FIntPoint VoxelGridPosition, const float Height, const FName VoxelAttributeName, const bool bInitializeChuck = true);
};

