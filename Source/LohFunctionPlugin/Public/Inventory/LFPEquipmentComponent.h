// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory/LFPInventoryComponent.h"
#include "LFPEquipmentComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnEquipmentEvent, const FLFPInventoryItemData&, ItemData, const int32, EquipmentSlotIndex, const int32, InventorySlotIndex, const FString&, EventInfo);


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPEquipmentComponent : public UActorComponent
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
		bool SetInventoryComponent(ULFPInventoryComponent* Component);

	/**
	* Equip Item In Inventory
	* @param InventorySlotIndex Inventory slot index to equip
	* @param EventInfo Info to pass to trigger event
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPEquipmentComponent | Function")
		bool EquipItem(const int32 EquipmentSlotIndex, const int32 InventorySlotIndex, const int32 ToInventorySlotIndex = -1, const FString EventInfo = FString("None"));

	/**
	* Unequip Item In Inventory
	* @param EquipmentSlotIndex Equipment slot index to remove
	* @param EventInfo Info to pass to trigger event
	* @return Index of the item in the Inventory
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPEquipmentComponent | Function")
		bool UnequipItem(const int32 EquipmentSlotIndex, const int32 ToInventorySlotIndex = -1, const FString EventInfo = FString("None"));


public: // Event

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPEquipmentComponent | Event")
		bool CanEquipItem(const FLFPInventoryItemData& ItemData, const int32 EquipmentSlotIndex, const int32 InventorySlotIndex, const FString& EventInfo) const;
		virtual bool CanEquipItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 EquipmentSlotIndex, const int32 InventorySlotIndex, const FString& EventInfo) const { return true; }

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPEquipmentComponent | Event")
		bool CanUnequipItem(const FLFPInventoryItemData& ItemData, const int32 EquipmentSlotIndex, const int32 InventorySlotIndex, const FString& EventInfo) const;
		virtual bool CanUnequipItem_Implementation(const FLFPInventoryItemData& ItemData, const int32 EquipmentSlotIndex, const int32 InventorySlotIndex, const FString& EventInfo) const { return true; }


	UFUNCTION(BlueprintNativeEvent, Category = "LFPEquipmentComponent | Event")
		void OnEquipmentSlotRep(const TArray<int32>& OldValue);
		virtual void OnEquipmentSlotRep_Implementation(const TArray<int32>& OldValue) { }

public: // Delegate

	UPROPERTY(BlueprintAssignable, BlueprintAuthorityOnly, BlueprintReadWrite, Category = "LFPEquipmentComponent | Delegate")
		FOnEquipmentEvent OnEquipItem;

	UPROPERTY(BlueprintAssignable, BlueprintAuthorityOnly, BlueprintReadWrite, Category = "LFPEquipmentComponent | Delegate")
		FOnEquipmentEvent OnUnequipItem;

public: // Valid Checker

	UFUNCTION(BlueprintPure, Category = "LFPEquipmentComponent | Getter")
		FORCEINLINE bool IsEquipmentSlotIndexValid(const int32 Index) const { return EquipmentSlotList.IsValidIndex(Index); };

public: // Getter

	UFUNCTION(BlueprintPure, Category = "LFPEquipmentComponent | Getter")
		const TArray<int32>& GetEquipmentSlotList() const { return EquipmentSlotList; };

	UFUNCTION(BlueprintPure, Category = "LFPEquipmentComponent | Getter")
		const FLFPInventoryItemData GetEquipmentSlot(const int32 Index) const { return IsValid(InventoryComponent) && IsEquipmentSlotIndexValid(Index) ? InventoryComponent->GetInventorySlot(EquipmentSlotList[Index]) : FLFPInventoryItemData(); };

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "LFPEquipmentComponent | Setting", meta = (ClampMin = "0"))
		int32 MaxEquipmentSlotAmount = 5;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "LFPEquipmentComponent | Setting")
		bool bUnequipOnEndPlay = false;

protected:

	UPROPERTY(VisibleAnywhere, Replicated, Savegame, ReplicatedUsing = OnEquipmentSlotRep, Category = "LFPEquipmentComponent | Cache")
		TArray<int32> EquipmentSlotList;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Savegame, Category = "LFPEquipmentComponent | Cache")
		TObjectPtr<ULFPInventoryComponent> InventoryComponent = nullptr;
};
