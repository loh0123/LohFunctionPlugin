// Copyright (c) 2023-2024 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#include "Item/FunctionObject/LFPItemInventoryFunction.h"

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

bool ULFPItemInventoryFunction::IsSupportedForNetworking() const
{
	return true;
}

void ULFPItemInventoryFunction::InitializeComponent()
{
	check(GetOwner() != nullptr);
}

ULFPInventoryComponent* ULFPItemInventoryFunction::GetOwner() const
{
	return GetTypedOuter<ULFPInventoryComponent>();
}
