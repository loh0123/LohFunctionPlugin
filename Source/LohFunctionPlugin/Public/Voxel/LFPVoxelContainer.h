// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Math/LFPGridLibrary.h"
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
struct FLFPVoxelStaticAttributeData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelStaticAttributeData")
		FColor VertexColor = FColor(255);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelStaticAttributeData")
		int32 MaterialID = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelStaticAttributeData")
		uint8 TextureOffset = uint8(0);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelStaticAttributeData")
		bool bConstanctUpdateOnTick = false;
};

USTRUCT(BlueprintType)
struct FLFPVoxelDynamicAttributeData
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SaveGame, Category = "LFPVoxelDynamicAttributeData")
		FColor VoxelColor = FColor(255);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SaveGame, Category = "LFPVoxelDynamicAttributeData")
		uint8 VoxelStatus = uint8(0);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, SaveGame, Category = "LFPVoxelDynamicAttributeData")
		uint8 VoxelType = uint8(0);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPVoxelStaticAttributeData")
		bool bUpdateOnTick = false;
};

USTRUCT()
struct FLFPVoxelWriteAction
{
	GENERATED_BODY()

public:

	UPROPERTY() TMap<int32, FName> NameData = TMap<int32, FName>();

	UPROPERTY() TMap<int32, FLFPVoxelDynamicAttributeData> AttributeData = TMap<int32, FLFPVoxelDynamicAttributeData>();

	UPROPERTY() bool bWantUpdateName = false;

	UPROPERTY() bool bWantUpdateAttribute = false;

	FLFPVoxelWriteAction& operator+=(const FLFPVoxelWriteAction& Other)
	{
		NameData.Append(Other.NameData);
		AttributeData.Append(Other.AttributeData);

		bWantUpdateName = bWantUpdateName || Other.bWantUpdateName;
		bWantUpdateAttribute = bWantUpdateAttribute || Other.bWantUpdateAttribute;

		return *this;
	}
};

DECLARE_DELEGATE(FOnVoxelChuckNameUpdate);

DECLARE_DELEGATE(FOnVoxelChuckAttributeUpdate);

USTRUCT()
struct FLFPVoxelChuckDataV2
{
	GENERATED_USTRUCT_BODY()

	FLFPVoxelChuckDataV2() {}

	FLFPVoxelChuckDataV2(const FLFPVoxelChuckDataV2& Data) : VoxelNameData(Data.VoxelNameData) {}

public:

	UPROPERTY(SaveGame) TArray<FName> VoxelNameData = {};

	UPROPERTY(SaveGame) TArray<FLFPVoxelDynamicAttributeData> VoxelAttributeData = {};

public:

	// Update Event For Notify Chuck On Voxel Update
	FOnVoxelChuckNameUpdate VoxelChuckNameUpdateEvent;

	// Update Event For Notify Chuck On Change Of Color
	FOnVoxelChuckAttributeUpdate VoxelChuckAttributeUpdateEvent;


public:

	FORCEINLINE bool IsInitialized() const
	{
		return VoxelNameData.IsEmpty() == false;
	}

	FORCEINLINE void InitChuckData(const int32 VoxelLength, const FName& VoxelName)
	{
		VoxelNameData.Init(VoxelName, VoxelLength);
		VoxelAttributeData.Init(FLFPVoxelDynamicAttributeData(), VoxelLength);
	}

	FORCEINLINE void InitChuckData(const int32 VoxelLength, const TArray<FName>& VoxelNameList, const TArray<FLFPVoxelDynamicAttributeData>& VoxelAttributeList)
	{
		check(VoxelLength == VoxelNameList.Num());
		check(VoxelLength == VoxelAttributeList.Num());

		VoxelNameData = VoxelNameList;
		VoxelAttributeData = VoxelAttributeList;
	}

	FORCEINLINE void SetVoxelNameList(const TArray<FName>& VoxelNameList)
	{
		check(VoxelNameList.Num() == VoxelNameData.Num());

		VoxelNameData = VoxelNameList;
	}

	FORCEINLINE void SetVoxelAttributeList(const TArray<FLFPVoxelDynamicAttributeData>& VoxelAttributeList)
	{
		check(VoxelAttributeList.Num() == VoxelAttributeData.Num());

		VoxelAttributeData = VoxelAttributeList;
	}

	FORCEINLINE void SetVoxelName(const int32 VoxelIndex, const FName& VoxelName)
	{
		check(VoxelNameData.IsValidIndex(VoxelIndex));

		VoxelNameData[VoxelIndex] = VoxelName;
	}

	FORCEINLINE void SetVoxelAttribute(const int32 VoxelIndex, const FLFPVoxelDynamicAttributeData& VoxelAttribute)
	{
		check(VoxelAttributeData.IsValidIndex(VoxelIndex));

		VoxelAttributeData[VoxelIndex] = VoxelAttribute;
	}

	template <typename UserClass, typename Func01, typename Func02>
	FORCEINLINE void Connect(UserClass* InUserObject, Func01 InVoxelFunc, Func02 InColorFunc)
	{
		VoxelChuckNameUpdateEvent.BindUObject(InUserObject, InVoxelFunc);
		VoxelChuckAttributeUpdateEvent.BindUObject(InUserObject, InColorFunc);
	}

	FORCEINLINE void SendNameUpdateEvent()
	{
		VoxelChuckNameUpdateEvent.ExecuteIfBound();
	}

	FORCEINLINE void SendAttributeUpdateEvent()
	{
		VoxelChuckAttributeUpdateEvent.ExecuteIfBound();
	}

	FORCEINLINE void Disconnect()
	{
		VoxelChuckNameUpdateEvent.Unbind();
		VoxelChuckAttributeUpdateEvent.Unbind();
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

	/*  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VoxelContainerSetting | Setting")
		int32 WriteActionBatchAmount = 10;

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

//DECLARE_DYNAMIC_DELEGATE_FourParams(FOnInitializeVoxelData, const FIntVector&, VoxelLocation, const ULFPVoxelContainer*, VoxelContainer, FName&, VoxelName, FLFPVoxelDynamicAttributeData&, VoxelAttribute);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnVoxelNameAction, const FLFPVoxelGridIndex, VoxelGridIndex, const FName, VoxelName);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnVoxelAttributeAction, const FLFPVoxelGridIndex, VoxelGridIndex, const FLFPVoxelDynamicAttributeData, VoxelAttribute);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChuckInitialize, const int32, ChuckIndex);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionListComplete);

/**
 *
 */
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent), ClassGroup = (LFPlugin))
class LOHFUNCTIONPLUGIN_API ULFPVoxelContainer : public UActorComponent
{
	GENERATED_BODY()

public:

	ULFPVoxelContainer();

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	virtual void Serialize(FArchive& Ar) override;

protected:

	FRWLock ContainerThreadLock;

	TAtomic<bool> bIsThreadReading = false;

public:

	UPROPERTY(BlueprintAssignable, Category = "VoxelData | Event")
		FOnVoxelNameAction OnVoxelNameUpdate;

	UPROPERTY(BlueprintAssignable, Category = "VoxelData | Event")
		FOnVoxelAttributeAction OnVoxelAttributeUpdate;


	UPROPERTY(BlueprintAssignable, Category = "VoxelData | Event")
		FOnChuckInitialize OnVoxelChuckNameUpdate;

	UPROPERTY(BlueprintAssignable, Category = "VoxelData | Event")
		FOnChuckInitialize OnVoxelChuckAttributeUpdate;


	UPROPERTY(BlueprintAssignable, Category = "VoxelData | Event")
		FOnActionListComplete OnVoxelChuckNameListComplete;

	UPROPERTY(BlueprintAssignable, Category = "VoxelData | Event")
		FOnActionListComplete OnVoxelChuckAttributeListComplete;


	UPROPERTY(BlueprintAssignable, Category = "VoxelData | Event")
		FOnActionListComplete OnChuckWriteActionListComplete;


	UPROPERTY(BlueprintAssignable, Category = "VoxelData | Event")
		FOnChuckInitialize OnChuckInitialize;

protected: // Initialize Data

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "VoxelData | Setting")
		FLFPVoxelContainerSettingV2 ContainerSetting;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "VoxelData | Setting") 
		TObjectPtr<UDataTable> VoxelAttributeTable;


protected:  // Runtime Data

	UPROPERTY(replicated, SaveGame) TArray<FLFPVoxelChuckDataV2> ChuckData;

	UPROPERTY() TSet<int32> BatchChuckNameUpdateList;

	UPROPERTY() TSet<int32> BatchChuckAttributeUpdateList;

	UPROPERTY() TMap<int32, FLFPVoxelWriteAction> ChuckWriteActionList;


protected: // Empty Data

	const FLFPVoxelStaticAttributeData DefaultVoxelStaticAttribute = FLFPVoxelStaticAttributeData();

	const FLFPVoxelDynamicAttributeData DefaultVoxelDynamicAttribute = FLFPVoxelDynamicAttributeData();


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
	FORCEINLINE const FLFPVoxelStaticAttributeData& GetVoxelStaticAttribute(const FLFPVoxelGridIndex VoxelGridIndex) const
	{
		return IsVoxelIndexValid(VoxelGridIndex) && IsChuckInitialized(VoxelGridIndex.ChuckIndex) ? GetVoxelStaticAttributeByName(GetVoxelName(VoxelGridIndex)) : DefaultVoxelStaticAttribute;
	}

	/* This Is Use To Access Atttribute On Local Chuck */
	FORCEINLINE const FLFPVoxelStaticAttributeData& GetVoxelStaticAttributeByName(const FName VoxelName) const
	{
		uint8* Data = VoxelAttributeTable != nullptr ? VoxelAttributeTable->FindRowUnchecked(VoxelName) : nullptr;

		if (Data != nullptr)
		{
			return *(reinterpret_cast<FLFPVoxelStaticAttributeData*>(Data));
		}
		else
		{
			return DefaultVoxelStaticAttribute;
		}
	}

	/* This Is Use To Access Atttribute Outside Of The Local Chuck */
	FORCEINLINE const FLFPVoxelDynamicAttributeData& GetVoxelDynamicAttribute(const FLFPVoxelGridIndex VoxelGridIndex) const
	{
		return IsVoxelIndexValid(VoxelGridIndex) && IsChuckInitialized(VoxelGridIndex.ChuckIndex) ? ChuckData[VoxelGridIndex.ChuckIndex].VoxelAttributeData[VoxelGridIndex.VoxelIndex] : DefaultVoxelDynamicAttribute;
	}

	/* This Is Use To Access Voxel Attribute On Local Chuck */
	FORCEINLINE const TArray<FLFPVoxelDynamicAttributeData>& GetVoxelDynamicAttributeList(const int32 ChuckIndex) const
	{
		check(IsChuckIndexValid(ChuckIndex));

		return ChuckData[ChuckIndex].VoxelAttributeData;
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

	/* This Is Use To Access Voxel Visible Outside Of The Local Chuck */
	FORCEINLINE bool IsVoxelVisible(const FLFPVoxelGridIndex VoxelGridIndex, const int32 CurrentMaterialID ) const
	{
		const FName& CheckName = GetVoxelName(VoxelGridIndex);

		return CheckName != ContainerSetting.InvisibleName && GetVoxelStaticAttributeByName(CheckName).MaterialID == CurrentMaterialID;
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

	FORCEINLINE void InitializeChuck(const int32 ChuckIndex, const FName& VoxelName, const bool bSkipLock = false);

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

	FORCEINLINE void AddChuckWriteAttributeAction(const FLFPVoxelGridIndex& VoxelGridIndex, const FLFPVoxelDynamicAttributeData& VoxelAttribute, const bool bWantUpdate)
	{
		FLFPVoxelWriteAction* Action = ChuckWriteActionList.Find(VoxelGridIndex.ChuckIndex);

		if (Action == nullptr)
		{
			FLFPVoxelWriteAction NewAction;

			NewAction.bWantUpdateAttribute = bWantUpdate;

			NewAction.AttributeData.Add(VoxelGridIndex.VoxelIndex, VoxelAttribute);

			ChuckWriteActionList.Add(VoxelGridIndex.ChuckIndex, NewAction);
		}
		else
		{
			Action->bWantUpdateAttribute = Action->bWantUpdateName || bWantUpdate;

			Action->AttributeData.Add(VoxelGridIndex.VoxelIndex, VoxelAttribute);
		}

		return;
	}

public:

	FORCEINLINE FLFPVoxelWriteAction* FindOrAddChuckWriteAction(const int32& ChuckIndex);

protected:

	virtual void BeginPlay() override;

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public: /* Function For External Blueprint Or C++ To Use */

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "VoxelData | Function")
		FORCEINLINE void GetInitializeVoxelData(const FName& DefaultVoxelName, const FIntVector& VoxelLocation, const ULFPVoxelContainer* VoxelContainer, FName& VoxelName, FLFPVoxelDynamicAttributeData& VoxelAttribute) const;
	virtual void GetInitializeVoxelData_Implementation(const FName& DefaultVoxelName, const FIntVector& VoxelLocation, const ULFPVoxelContainer* VoxelContainer, FName& VoxelName, FLFPVoxelDynamicAttributeData& VoxelAttribute) const { VoxelName = DefaultVoxelName; }


	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE int32 GetContainerSize();

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void UpdateChuckWriteAction(const bool bForce = false);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void UpdateChuckName();

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void UpdateChuckAttribute();

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void MarkChuckForNameUpdate(const int32 ChuckIndex, const bool bUpdateNearbyChuck = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void MarkChuckForAttributeUpdate(const int32 ChuckIndex, const bool bUpdateNearbyChuck = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE bool SetupVoxelData(UDataTable* NewVoxelAttributeTable, const FLFPVoxelContainerSettingV2 NewSetting);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE bool IsChuckInitialized(const int32 ChuckIndex) const;

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE FLFPVoxelGridIndex ToVoxelGridIndex(const FIntVector VoxelGridLocation) const;

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE FIntVector ToVoxelGridLocation(const FLFPVoxelGridIndex VoxelGridIndex) const;

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE bool GetVoxelGridAttribute(const FLFPVoxelGridIndex VoxelGridIndex, FLFPVoxelDynamicAttributeData& VoxelAttribute) const;

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE bool GetVoxelGridName(const FLFPVoxelGridIndex VoxelGridIndex, FName& VoxelName) const;

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetVoxelGridAttribute(const FLFPVoxelGridIndex VoxelGridIndex, const FLFPVoxelDynamicAttributeData VoxelAttribute, const bool bInitializeChuck = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetVoxelGridName(const FLFPVoxelGridIndex VoxelGridIndex, const FName VoxelName, const bool bInitializeChuck = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetVoxelGridNameList(const TArray<FLFPVoxelGridIndex>& VoxelGridIndexList, const FName VoxelName, const bool bInitializeChuck = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetChuckGridName(const int32 ChuckIndex, const FName VoxelName, const bool bInitializeChuck = true);

	UFUNCTION(BlueprintCallable, Category = "VoxelData | Function")
		FORCEINLINE void SetChuckGridNameWithHeight(const int32 ChuckIndex, const FIntPoint VoxelGridPosition, const float Height, const FName VoxelName, const bool bInitializeChuck = true);
};

