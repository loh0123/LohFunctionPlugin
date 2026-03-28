// Copyright by LOH ZHI KANG

#pragma once

#include "CoreMinimal.h"
#include "LFPItemInventoryFunction.h"
#include "LFPItemEquipmentBasicFunction.generated.h"

struct FLFPInventoryItemOperationData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam ( FLFPEquipmentUnequipEvent , const FLFPInventoryItemOperationData& , ItemOperationData );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam ( FLFPEquipmentEquipEvent , const FLFPInventoryIndex& , EquipInventoryIndexIndex );

/**
 * 
 */
UCLASS ( )
class LOHFUNCTIONPLUGINITEM_API ULFPItemEquipmentBasicFunction : public ULFPItemInventoryFunction
{
	GENERATED_BODY ( )

public:

	virtual void GetLifetimeReplicatedProps ( TArray < FLifetimeProperty >& OutLifetimeProps ) const override;

	virtual void InitializeComponent ( ) override;

	virtual void UninitializeComponent ( ) override;

public:

	UFUNCTION ( BlueprintCallable , Category = "LFPItemBasicFunction | Function" )
	void SelectIndex ( const int32 Index );

	UFUNCTION ( BlueprintCallable , Category = "LFPItemBasicFunction | Function" )
	int32 GetSelectedIndex ( ) const;

protected:

	UFUNCTION ( )
	void OnInventoryUpdateItem ( const TArray < FLFPInventoryItemOperationData >& ItemOperationDataList );

	UFUNCTION ( )
	void OnRep_SelectedIndex ( const int32& OldValue ) const;

protected:

	UPROPERTY ( EditDefaultsOnly , Category=Default )
	FGameplayTag HandleSlotTag = FGameplayTag::EmptyTag;

	UPROPERTY ( EditDefaultsOnly , Category=Default , ReplicatedUsing=OnRep_SelectedIndex )
	int32 SelectedIndex = INDEX_NONE;

public:

	UPROPERTY ( BlueprintAssignable , BlueprintReadWrite , Category = "LFPEquipmentComponent | Delegate" )
	FLFPEquipmentEquipEvent OnEquipItem;

	UPROPERTY ( BlueprintAssignable , BlueprintReadWrite , Category = "LFPEquipmentComponent | Delegate" )
	FLFPEquipmentUnequipEvent OnUnequipItem;
};
