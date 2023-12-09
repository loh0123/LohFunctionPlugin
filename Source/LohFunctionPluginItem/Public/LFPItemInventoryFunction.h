// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/LFPInventoryComponent.h"
#include "GameplayTagContainer.h"
#include "LFPItemInventoryFunction.generated.h"

class ULFPInventoryComponent;

/**
 * 
 */
UCLASS(Blueprintable, Abstract, EditInlineNew)
class LOHFUNCTIONPLUGINITEM_API ULFPItemInventoryFunction : public UObject
{
	GENERATED_BODY()

public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual int32 GetFunctionCallspace(UFunction* Function, FFrame* Stack) override;

	virtual bool CallRemoteFunction(UFunction* Function, void* Parms, struct FOutParmRec* OutParms, FFrame* Stack) override;

public:
	
	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanAddItem(const FLFPInventoryChange& ChangeData) const;
	virtual bool CanAddItem_Implementation(const FLFPInventoryChange& ChangeData) const;

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanRemoveItem(const FLFPInventoryChange& ChangeData) const;
	virtual bool CanRemoveItem_Implementation(const FLFPInventoryChange& ChangeData) const;

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanSwapItem(const FLFPInventoryChange& ChangeDataA, const FLFPInventoryChange& ChangeDataB) const;
	virtual bool CanSwapItem_Implementation(const FLFPInventoryChange& ChangeDataA, const FLFPInventoryChange& ChangeDataB) const;

	// Process Modifier

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool ProcessAddItem(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;
	virtual bool ProcessAddItem_Implementation(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool ProcessRemoveItem(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;
	virtual bool ProcessRemoveItem_Implementation(UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool ProcessSwapItem(UPARAM(ref) FLFPInventoryItem& ItemDataA, const FLFPInventoryIndex InventoryIndexA, UPARAM(ref) FLFPInventoryItem& ItemDataB, const FLFPInventoryIndex InventoryIndexB) const;
	virtual bool ProcessSwapItem_Implementation(UPARAM(ref) FLFPInventoryItem& ItemDataA, const FLFPInventoryIndex& InventoryIndexA, UPARAM(ref) FLFPInventoryItem& ItemDataB, const FLFPInventoryIndex& InventoryIndexB) const;

	// Catergorize Modifier

	UFUNCTION(BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	FGameplayTagContainer GetInventoryIndexCatergorize(const FLFPInventoryChange& ChangeData) const;
	virtual FGameplayTagContainer GetInventoryIndexCatergorize_Implementation(const FLFPInventoryChange& ChangeData) const;

	// Check Modifier

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanItemSortHigherThan(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB, const FGameplayTag& SortTag) const;
	virtual bool CanItemSortHigherThan_Implementation(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB, const FGameplayTag& SortTag) const;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool CanItemUseInventoryIndex(const FLFPInventoryChange& ChangeData, const ELFPInventoryOperation Operation) const;
	virtual bool CanItemUseInventoryIndex_Implementation(const FLFPInventoryChange& ChangeData, const ELFPInventoryOperation Operation) const;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "LFPItemInventoryFunction | Modifier")
	bool DoInventoryIndexContainItem(const FLFPInventoryChange& ChangeData) const;
	virtual bool DoInventoryIndexContainItem_Implementation(const FLFPInventoryChange& ChangeData) const;

public:

	UFUNCTION(BlueprintPure, Category = "LFPItemInventoryFunction | Getter")
	ULFPInventoryComponent* GetOwner() const;
};
