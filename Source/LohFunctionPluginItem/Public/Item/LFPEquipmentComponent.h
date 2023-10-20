#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/LFPInventoryComponent.h"
#include "Item/LFPInventoryInterface.h"
#include "LFPItemGameplayTag.h"
#include "LFPEquipmentComponent.generated.h"

USTRUCT(BlueprintType)
struct FLFPEquipmentSlotConfig
{
	GENERATED_BODY()

public:

	/** The inventory slot */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPEquipmentSlotConfig", meta = (Categories = "Item.SlotNames"))
	FGameplayTag SlotName = FLFPItemGameplayTag::ItemGameplayTag.SlotNames_All;

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
		bool AddEquipmentSlotName(const FGameplayTag InventorySlotName, const bool bIsSlotActive = true, const bool bIsSlotLock = true, const FString EventInfo = "");

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPEquipmentComponent | Function")
		bool AddEquipmentSlot(const int32 InventorySlotIndex, const bool bIsSlotActive = true, const bool bIsSlotLock = true, const FString EventInfo = "");

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPEquipmentComponent | Function")
		bool RemoveEquipmentSlot(const int32 InventorySlotIndex, const FString EventInfo = "");

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPEquipmentComponent | Function")
		void ClearEquipmentSlot(const FString EventInfo = "");

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPEquipmentComponent | Function")
		bool TryEquipItem(const int32 InventorySlotIndex, const bool bToActiveSlotOnly = false, const FString EventInfo = "");

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPEquipmentComponent | Function")
		bool TryUnequipItem(const int32 EquipmentSlotIndex, const FGameplayTag SlotName, const FString EventInfo = "");

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPEquipmentComponent | Function")
		bool SetEquipmentSlotActive(const int32 EquipmentSlotIndex, const bool bIsSlotActive, const FString& EventInfo = "");

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPEquipmentComponent | Function")
		bool SetEquipmentSlotLock(const int32 EquipmentSlotIndex, const bool bIsSlotLock, const FString& EventInfo = "");


public: // Event

	UFUNCTION() void OnInventoryUpdateItem (const FLFPInventoryItemData& OldItemData, const FLFPInventoryItemData& NewItemData, const int32 InventorySlotIndex, const FString& EventInfo);

	UFUNCTION() void OnEquipmentSlotUpdate (const FLFPEquipmentSlotData& OldItemData, const FLFPEquipmentSlotData& NewItemData, const int32 EquipmentSlotIndex, const FString& EventInfo) const;

public: // Inventory Interface

	virtual bool CanInventoryAddItem_Implementation		(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const override;

	virtual bool CanInventoryRemoveItem_Implementation	(const FLFPInventoryItemData& ItemData, const int32 SlotIndex, const FString& EventInfo) const override;

	virtual bool CanInventorySwapItem_Implementation	(const FLFPInventoryItemData& FromItemData, const int32 FromSlot, const FLFPInventoryItemData& ToItemData, const int32 ToSlot, const FString& EventInfo) const override;

public: // Event

	/** Check Is Slot Locked */
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPEquipmentComponent | Event")
		bool CanEquipItem(const FLFPInventoryItemData& ItemData, const int32 ToEquipmentSlotIndex, const int32 ToInventorySlotIndex, const int32 FromInventorySlotIndex, const FString& EventInfo) const;
		virtual bool CanEquipItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 ToEquipmentSlotIndex, const int32 ToInventorySlotIndex, const int32 FromInventorySlotIndex, const FString& EventInfo) const { return IsEquipmentSlotLock(ToEquipmentSlotIndex) == false; }

	/** Check Is Slot Locked */
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPEquipmentComponent | Event")
		bool CanUnequipItem(const FLFPInventoryItemData& ItemData, const int32 ToEquipmentSlotIndex, const int32 ToInventorySlotIndex, const int32 FromInventorySlotIndex, const FString& EventInfo) const;
		virtual bool CanUnequipItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 ToEquipmentSlotIndex, const int32 ToInventorySlotIndex, const int32 FromInventorySlotIndex, const FString& EventInfo) const { return IsEquipmentSlotLock(ToEquipmentSlotIndex) == false; }


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
		FORCEINLINE bool IsEquipmentSlotIndexValid(const int32 EquipmentSlotIndex) const { return EquipmentSlotList.IsValidIndex(EquipmentSlotIndex); };

	UFUNCTION(BlueprintPure, Category = "LFPInventoryComponent | Getter")
		FORCEINLINE bool IsEquipmentSlotItemValid(const int32 EquipmentSlotIndex) const { return IsEquipmentSlotIndexValid(EquipmentSlotIndex) && GetInventorySlot(EquipmentSlotIndex).HasItem(); };

	UFUNCTION(BlueprintPure, Category = "LFPEquipmentComponent | Getter")
		FORCEINLINE bool IsEquipmentSlotActive(const int32 EquipmentSlotIndex) const { return IsEquipmentSlotIndexValid(EquipmentSlotIndex) && EquipmentSlotList[EquipmentSlotIndex].bIsActive; };

	UFUNCTION(BlueprintPure, Category = "LFPEquipmentComponent | Getter")
		FORCEINLINE bool IsEquipmentSlotLock(const int32 EquipmentSlotIndex) const { return IsEquipmentSlotIndexValid(EquipmentSlotIndex) && EquipmentSlotList[EquipmentSlotIndex].bIsLock; };

	UFUNCTION(BlueprintPure, Category = "LFPEquipmentComponent | Getter")
		FORCEINLINE bool IsEquipmentSlotUsable(const int32 EquipmentSlotIndex) const { return IsEquipmentSlotIndexValid(EquipmentSlotIndex) && EquipmentSlotList[EquipmentSlotIndex].bIsActive && GetInventorySlot(EquipmentSlotIndex).HasItem(); };

	UFUNCTION(BlueprintPure, Category = "LFPEquipmentComponent | Getter", meta = (GameplayTagFilter = "Item.SlotNames"))
		FORCEINLINE bool IsInventorySlotUsable(const int32 InventorySlotIndex, const FGameplayTag SlotName) const { int32 EquipmentSlotIndex = INDEX_NONE; FindEquipmentSlotIndex(InventorySlotIndex, SlotName, EquipmentSlotIndex); return IsEquipmentSlotUsable(EquipmentSlotIndex); };

public: // Getter

	UFUNCTION(BlueprintPure, Category = "LFPEquipmentComponent | Getter")
		const TArray<FLFPEquipmentSlotData>& GetEquipmentSlotList() const { return EquipmentSlotList; };

	UFUNCTION(BlueprintPure, Category = "LFPEquipmentComponent | Getter")
		FLFPEquipmentSlotData GetEquipmentSlot(const int32 EquipmentSlotIndex) const { return IsEquipmentSlotIndexValid(EquipmentSlotIndex) ? EquipmentSlotList[EquipmentSlotIndex] : FLFPEquipmentSlotData(); };

	UFUNCTION(BlueprintPure, Category = "LFPEquipmentComponent | Getter")
		const FLFPInventoryItemData& GetInventorySlot(const int32 EquipmentSlotIndex) const { return IsValid(InventoryComponent) && IsEquipmentSlotIndexValid(EquipmentSlotIndex) ? InventoryComponent->GetInventorySlot(EquipmentSlotList[EquipmentSlotIndex].SlotIndex, FGameplayTag()) : FLFPInventoryItemData::EmptyInventoryItemData; };

	UFUNCTION(BlueprintPure, Category = "LFPEquipmentComponent | Getter")
		FLFPEquipmentSlotData FindEquipmentSlotIndex(const int32 InventorySlotIndex, const FGameplayTag SlotName, int32& EquipmentSlotIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPEquipmentComponent | Getter")
		const FLFPInventoryItemData& FindEquipmentSlotItem(const int32 InventorySlotIndex, const FGameplayTag SlotName) const;

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

	UPROPERTY(VisibleAnywhere, Transient, Replicated, ReplicatedUsing = OnEquipmentSlotListRep, Category = "LFPEquipmentComponent | Cache")
		TArray<FLFPEquipmentSlotData> EquipmentSlotList = TArray<FLFPEquipmentSlotData>();

UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Replicated, ReplicatedUsing = OnInventoryComponentRep, Category = "LFPEquipmentComponent | Cache")
		ULFPInventoryComponent* InventoryComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "LFPEquipmentComponent | Setting")
		TArray<FLFPEquipmentSlotConfig> EquipmentSlotConfigList = TArray<FLFPEquipmentSlotConfig>();
};
