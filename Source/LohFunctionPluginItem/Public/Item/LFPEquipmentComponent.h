#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/LFPInventoryComponent.h"
#include "Item/LFPInventoryInterface.h"
#include "LFPEquipmentComponent.generated.h"

USTRUCT(BlueprintType)
struct FLFPEquipmentSlotConfig
{
	GENERATED_BODY()

public:

	/** The inventory slot */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPEquipmentSlotConfig")
	FName SlotName = FName("All");

	/** This slot won't send any event but still can equip or unequip */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPEquipmentSlotConfig")
	bool bIsActive = true;

	/** This slot can't equip or unequip */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPEquipmentSlotConfig")
	bool bIsLock = false;
};

USTRUCT(BlueprintType)
struct FLFPEquipmentSlotData
{
	GENERATED_BODY()

public:

	FLFPEquipmentSlotData() {}

	FLFPEquipmentSlotData(const int32 InSlotIndex) : SlotIndex(InSlotIndex), bIsActive(true), bIsLock(false) {}

	FLFPEquipmentSlotData(const int32 InSlotIndex, const bool InIsActive) : SlotIndex(InSlotIndex), bIsActive(InIsActive), bIsLock(false) {}

	FLFPEquipmentSlotData(const int32 InSlotIndex, const bool InIsActive, const bool InIsLock) : SlotIndex(InSlotIndex), bIsActive(InIsActive), bIsLock(InIsLock) {}

public:

	/** The inventory slot */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPEquipmentSlotData")
		int32 SlotIndex = INDEX_NONE;

	/** This slot won't send any event but still can equip or unequip */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPEquipmentSlotData")
		bool bIsActive = true;

	/** This slot can't equip or unequip */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPEquipmentSlotData")
		bool bIsLock = false;

public:

	FORCEINLINE	bool operator==(const FLFPEquipmentSlotData& OtherData) const
	{
		return SlotIndex == OtherData.SlotIndex;
	};

	FORCEINLINE	bool operator!=(const FLFPEquipmentSlotData& OtherData) const
	{
		return SlotIndex != OtherData.SlotIndex;
	};
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnEquipmentEvent, const FLFPInventoryItemData&, ItemData, const int32, EquipmentSlotIndex, const int32, InventorySlotIndex, const FString&, EventInfo);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnEquipmentChangeEvent, const FLFPInventoryItemData&, ItemData, const int32, EquipmentSlotIndex, const int32, InventorySlotIndex, const bool, Value, const FString&, EventInfo);


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGINITEM_API ULFPEquipmentComponent : public UActorComponent, public ILFPInventoryInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPEquipmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Serialize(FArchive& Ar) override;


public:

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPEquipmentComponent | Function")
		void SetInventoryComponent(ULFPInventoryComponent* Component);
		FORCEINLINE void SetInventoryComponent_Internal(ULFPInventoryComponent* OldComponent, ULFPInventoryComponent* NewComponent);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPEquipmentComponent | Function")
		bool AddEquipmentSlotName(const FName InventorySlotName, const bool bIsSlotActive = true, const bool bIsSlotLock = true, const FString EventInfo = "");

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPEquipmentComponent | Function")
		bool AddEquipmentSlot(const int32 InventorySlotIndex, const bool bIsSlotActive = true, const bool bIsSlotLock = true, const FString EventInfo = "");

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPEquipmentComponent | Function")
		bool RemoveEquipmentSlot(const int32 InventorySlotIndex, const FString EventInfo = "");

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPEquipmentComponent | Function")
		void ClearEquipmentSlot(const FString EventInfo = "");

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPEquipmentComponent | Function")
		bool TryEquipItem(const int32 InventorySlotIndex, const bool bToActiveSlotOnly = false, const FString EventInfo = "");

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPEquipmentComponent | Function")
		bool TryUnequipItem(const int32 EquipmentSlotIndex, const FName Slotname = FName("All"), const FString EventInfo = "");

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPEquipmentComponent | Function")
		bool SetEquipmentSlotActive(const int32 EquipmentSlotIndex, const bool bIsSlotActive, const FString& EventInfo = "");

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPEquipmentComponent | Function")
		bool SetEquipmentSlotLock(const int32 EquipmentSlotIndex, const bool bIsSlotLock, const FString& EventInfo = "");


public: // Inventory Event

	UFUNCTION() void OnInventoryUpdateItem	(const FLFPInventoryItemData& OldItemData, const FLFPInventoryItemData& NewItemData, const int32 SlotIndex, const FString& EventInfo);

public: // Inventory Interface

	virtual bool CanInventoryAddItem_Implementation		(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const override;

	virtual bool CanInventoryRemoveItem_Implementation	(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const override;

	virtual bool CanInventorySwapItem_Implementation	(const FLFPInventoryItemData& FromItemData, const int32 FromSlot, const FLFPInventoryItemData& ToItemData, const int32 ToSlot, const FString& EventInfo) const override;

public: // Event

	/** Check Is Slot Locked */
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPEquipmentComponent | Event")
		bool CanEquipItem(const FLFPInventoryItemData& ItemData, const int32 EquipmentSlotIndex, const int32 InventorySlotIndex, const FString& EventInfo) const;
		virtual bool CanEquipItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 EquipmentSlotIndex, const int32 InventorySlotIndex, const FString& EventInfo) const { return IsEquipmentSlotLock(EquipmentSlotIndex) == false; }

	/** Check Is Slot Locked */
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPEquipmentComponent | Event")
		bool CanUnequipItem(const FLFPInventoryItemData& ItemData, const int32 EquipmentSlotIndex, const int32 InventorySlotIndex, const FString& EventInfo) const;
		virtual bool CanUnequipItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 EquipmentSlotIndex, const int32 InventorySlotIndex, const FString& EventInfo) const { return IsEquipmentSlotLock(EquipmentSlotIndex) == false; }


public: // Delegate

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPEquipmentComponent | Delegate")
		FOnEquipmentEvent OnEquipItem;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPEquipmentComponent | Delegate")
		FOnEquipmentEvent OnUnequipItem;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPEquipmentComponent | Delegate")
		FOnEquipmentChangeEvent OnItemActiveChanged;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = "LFPEquipmentComponent | Delegate")
		FOnEquipmentChangeEvent OnItemLockChanged;

public: // Valid Checker

	UFUNCTION(BlueprintPure, Category = "LFPEquipmentComponent | Getter")
		FORCEINLINE bool IsEquipmentSlotIndexValid(const int32 Index) const { return EquipmentSlotList.IsValidIndex(Index); };

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		FORCEINLINE bool IsEquipmentSlotItemValid(const int32 Index) const { return IsEquipmentSlotIndexValid(Index) && GetEquipmentSlot(Index).HasItem(); };

	UFUNCTION(BlueprintPure, Category = "LFPEquipmentComponent | Getter")
		FORCEINLINE bool IsEquipmentSlotActive(const int32 Index) const { return EquipmentSlotList.IsValidIndex(Index) && EquipmentSlotList[Index].bIsActive; };

	UFUNCTION(BlueprintPure, Category = "LFPEquipmentComponent | Getter")
		FORCEINLINE bool IsEquipmentSlotLock(const int32 Index) const { return EquipmentSlotList.IsValidIndex(Index) && EquipmentSlotList[Index].bIsLock; };

public: // Getter

	UFUNCTION(BlueprintPure, Category = "LFPEquipmentComponent | Getter")
		const TArray<FLFPEquipmentSlotData>& GetEquipmentSlotList() const { return EquipmentSlotList; };

	UFUNCTION(BlueprintPure, Category = "LFPEquipmentComponent | Getter")
		const FLFPInventoryItemData& GetEquipmentSlot(const int32 Index) const { return IsValid(InventoryComponent) && IsEquipmentSlotIndexValid(Index) ? InventoryComponent->GetInventorySlot(EquipmentSlotList[Index].SlotIndex) : FLFPInventoryItemData::EmptyInventoryItemData; };

	UFUNCTION(BlueprintPure, Category = "LFPEquipmentComponent | Getter")
		FLFPEquipmentSlotData FindEquipmentSlotIndex(const int32 InventorySlotIndex, int32& EquipmentIndex) const;

public:

	UFUNCTION(BlueprintNativeEvent, Category = "LFPEquipmentComponent | Event")
		void OnInventoryComponentRep(ULFPInventoryComponent* OldValue);
		virtual void OnInventoryComponentRep_Implementation(ULFPInventoryComponent* OldValue);

	UFUNCTION(BlueprintNativeEvent, Category = "LFPEquipmentComponent | Event")
		void OnEquipmentSlotListRep(TArray<FLFPEquipmentSlotData>& OldValue);
		virtual void OnEquipmentSlotListRep_Implementation(TArray<FLFPEquipmentSlotData>& OldValue);

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "LFPEquipmentComponent | Setting")
		bool bAutoSetup = true;

protected:

	UPROPERTY(VisibleAnywhere, Replicated, ReplicatedUsing = OnEquipmentSlotListRep, Category = "LFPEquipmentComponent | Cache")
		TArray<FLFPEquipmentSlotData> EquipmentSlotList = TArray<FLFPEquipmentSlotData>();

	UPROPERTY(EditDefaultsOnly, Category = "LFPEquipmentComponent | Setting")
		TArray<FLFPEquipmentSlotConfig> EquipmentSlotConfigList = TArray<FLFPEquipmentSlotConfig>();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Replicated, ReplicatedUsing = OnInventoryComponentRep, Category = "LFPEquipmentComponent | Cache")
		ULFPInventoryComponent* InventoryComponent = nullptr;
};
