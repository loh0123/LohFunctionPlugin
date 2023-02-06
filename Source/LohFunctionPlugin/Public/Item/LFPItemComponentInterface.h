// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LFPItemComponentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class LOHFUNCTIONPLUGIN_API ULFPItemComponentInterface : public UInterface
{
	GENERATED_BODY()
};

class ULFPInventoryComponent;
class ULFPEquipmentComponent;
class ULFPItemMutatorComponent;

/**
 * 
 */
class LOHFUNCTIONPLUGIN_API ILFPItemComponentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "LFPItemComponentInterface")
		ULFPInventoryComponent* GetInventoryComponent();
		virtual ULFPInventoryComponent* GetInventoryComponent_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "LFPItemComponentInterface")
		ULFPEquipmentComponent* GetEquipmentComponent();
		virtual ULFPEquipmentComponent* GetEquipmentComponent_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "LFPItemComponentInterface")
		TArray<ULFPItemMutatorComponent*> GetItemMutatorComponent();
		virtual TArray<ULFPItemMutatorComponent*> GetItemMutatorComponent_Implementation();
};
