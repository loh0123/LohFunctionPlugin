// Fill out your copyright notice in the Description page of Project Settings.


#include "LFPItemInventoryFunction.h"

void ULFPItemInventoryFunction::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	// Add any Blueprint properties
	if (const UBlueprintGeneratedClass* BPClass = Cast<UBlueprintGeneratedClass>(GetClass()))
	{
		BPClass->GetLifetimeBlueprintReplicationList(OutLifetimeProps);
	}
}

int32 ULFPItemInventoryFunction::GetFunctionCallspace(UFunction* Function, FFrame* Stack)
{
	check(GetOuter() != nullptr);
	return GetOuter()->GetFunctionCallspace(Function, Stack);
}

bool ULFPItemInventoryFunction::CallRemoteFunction(UFunction* Function, void* Parms, FOutParmRec* OutParms, FFrame* Stack)
{
	check(!HasAnyFlags(RF_ClassDefaultObject));

	UActorComponent* Owner = GetTypedOuter<UActorComponent>();
	UNetDriver* NetDriver = Owner->GetOwner()->GetNetDriver();
	if (NetDriver)
	{
		NetDriver->ProcessRemoteFunction(Owner->GetOwner(), Function, Parms, OutParms, Stack, this);
		return true;
	}
	return false;
}

bool ULFPItemInventoryFunction::CanAddItem_Implementation(const FLFPInventoryChange& ChangeData) const
{
	return true;
}

bool ULFPItemInventoryFunction::CanRemoveItem_Implementation(const FLFPInventoryChange& ChangeData) const
{
	return true;
}

bool ULFPItemInventoryFunction::CanSwapItem_Implementation(const FLFPInventoryChange& ChangeDataA, const FLFPInventoryChange& ChangeDataB) const
{
	return true;
}

bool ULFPItemInventoryFunction::ProcessAddItem_Implementation(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	return true;
}

bool ULFPItemInventoryFunction::ProcessRemoveItem_Implementation(UPARAM(ref)FLFPInventoryItem& ItemData, UPARAM(ref)FLFPInventoryItem& ProcessData, const FLFPInventoryIndex InventoryIndex) const
{
	return true;
}

bool ULFPItemInventoryFunction::ProcessSwapItem_Implementation(UPARAM(ref)FLFPInventoryItem& ItemDataA, const FLFPInventoryIndex& InventoryIndexA, UPARAM(ref)FLFPInventoryItem& ItemDataB, const FLFPInventoryIndex& InventoryIndexB) const
{
	return true;
}

FGameplayTagContainer ULFPItemInventoryFunction::GetInventoryIndexCatergorize_Implementation(const FLFPInventoryChange& ChangeData) const
{
	return FGameplayTagContainer();
}

bool ULFPItemInventoryFunction::CanItemSortHigherThan_Implementation(const FLFPInventoryItem& ItemDataA, const FLFPInventoryItem& ItemDataB, const FGameplayTag& SortTag) const
{
	return false;
}

bool ULFPItemInventoryFunction::CanItemUseInventoryIndex_Implementation(const FLFPInventoryChange& ChangeData, const ELFPInventoryOperation Operation) const
{
	return false;
}

bool ULFPItemInventoryFunction::DoInventoryIndexContainItem_Implementation(const FLFPInventoryChange& ChangeData) const
{
	return false;
}

ULFPInventoryComponent* ULFPItemInventoryFunction::GetOwner() const
{
	return GetTypedOuter<ULFPInventoryComponent>();
}
