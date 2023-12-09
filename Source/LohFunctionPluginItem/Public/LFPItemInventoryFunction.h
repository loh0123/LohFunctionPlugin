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
	
	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Modifier")
	bool CanAddItem(const ULFPInventoryComponent* InventoryComponent, const FLFPInventoryChange& ChangeData) const;
	virtual bool CanAddItem_Implementation(const ULFPInventoryComponent* InventoryComponent, const FLFPInventoryChange& ChangeData) const;

	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Modifier")
	bool CanRemoveItem(const ULFPInventoryComponent* InventoryComponent, const FLFPInventoryChange& ChangeData) const;
	virtual bool CanRemoveItem_Implementation(const ULFPInventoryComponent* InventoryComponent, const FLFPInventoryChange& ChangeData) const;

	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Modifier")
	bool CanSwapItem(const ULFPInventoryComponent* InventoryComponent, const FLFPInventoryChange& ChangeDataA, const FLFPInventoryChange& ChangeDataB) const;
	virtual bool CanSwapItem_Implementation(const ULFPInventoryComponent* InventoryComponent, const FLFPInventoryChange& ChangeDataA, const FLFPInventoryChange& ChangeDataB) const;

	// Process Modifier

	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Modifier")
	bool ProcessAddItem(const ULFPInventoryComponent* InventoryComponent, UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;
	virtual bool ProcessAddItem_Implementation(const ULFPInventoryComponent* InventoryComponent, UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;

	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Modifier")
	bool ProcessRemoveItem(const ULFPInventoryComponent* InventoryComponent, UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;
	virtual bool ProcessRemoveItem_Implementation(const ULFPInventoryComponent* InventoryComponent, UPARAM(ref) FLFPInventoryItem& ItemData, UPARAM(ref) FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const;

	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Modifier")
	bool ProcessSwapItem(const ULFPInventoryComponent* InventoryComponent, UPARAM(ref) FLFPInventoryItem& ItemDataA, const FLFPInventoryIndex InventoryIndexA, UPARAM(ref) FLFPInventoryItem& ItemDataB, const FLFPInventoryIndex InventoryIndexB) const;
	virtual bool ProcessSwapItem_Implementation(const ULFPInventoryComponent* InventoryComponent, UPARAM(ref) FLFPInventoryItem& ItemDataA, const FLFPInventoryIndex& InventoryIndexA, UPARAM(ref) FLFPInventoryItem& ItemDataB, const FLFPInventoryIndex& InventoryIndexB) const;

	// Catergorize Modifier

	UFUNCTION(BlueprintNativeEvent, Category = "LFPInventoryComponent | Modifier")
	FGameplayTagContainer GetInventoryIndexCatergorize(const ULFPInventoryComponent* InventoryComponent, const FLFPInventoryChange& ChangeData) const;
	virtual FGameplayTagContainer GetInventoryIndexCatergorize_Implementation(const ULFPInventoryComponent* InventoryComponent, const FLFPInventoryChange& ChangeData) const;
};
