// Copyright (c) 2022 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LFPVoxelContainerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class ULFPVoxelContainerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LOHFUNCTIONPLUGIN_API ILFPVoxelContainerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/* Warning This Function Run On Other Thread */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = LFPVoxelContainerInterface, meta = (NotBlueprintThreadSafe))
		void InitializeVoxelData(const FIntVector& VoxelLocation, FName& VoxelName, FLFPVoxelDynamicAttributeData& VoxelAttribute) const;

		virtual void InitializeVoxelData_Implementation(const FIntVector& VoxelLocation, FName& VoxelName, FLFPVoxelDynamicAttributeData& VoxelAttribute) const {}
};
