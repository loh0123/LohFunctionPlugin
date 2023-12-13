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

ULFPInventoryComponent* ULFPItemInventoryFunction::GetOwner() const
{
	return GetTypedOuter<ULFPInventoryComponent>();
}
