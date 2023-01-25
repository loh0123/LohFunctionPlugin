// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LFPInventoryRelatedInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class LOHFUNCTIONPLUGIN_API ULFPInventoryRelatedInterface : public UInterface
{
	GENERATED_BODY()
};

class ULFPInventoryComponent;
class ULFPEquipmentComponent;
class ULFPItemMutatorComponent;

/**
 * 
 */
class LOHFUNCTIONPLUGIN_API ILFPInventoryRelatedInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "LFPInventoryRelatedInterface")
		ULFPInventoryComponent* GetInventoryComponent();
		virtual ULFPInventoryComponent* GetInventoryComponent_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "LFPInventoryRelatedInterface")
		ULFPEquipmentComponent* GetEquipmentComponent();
		virtual ULFPEquipmentComponent* GetEquipmentComponent_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "LFPInventoryRelatedInterface")
		ULFPItemMutatorComponent* GetItemMutatorComponent();
		virtual ULFPItemMutatorComponent* GetItemMutatorComponent_Implementation();
};
