// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/LFPTickerObject.h"
#include "Components/LFPIndexTickerComponent.h"

void ULFPTickerObject::OnBegin_Implementation(const FIntPoint& TickGroup, const int32 TickIndex, const FName& TickName, ULFPIndexTickerComponent* Caller)
{
}

void ULFPTickerObject::OnExecute_Implementation(const FIntPoint& TickGroup, const int32 TickIndex, const FName& TickName, ULFPIndexTickerComponent* Caller)
{
}

bool ULFPTickerObject::CanEnd_Implementation(const FIntPoint& TickGroup, const int32 TickIndex, const FName& TickName, ULFPIndexTickerComponent* Caller)
{
	return true;
}

void ULFPTickerObject::OnEnd_Implementation(const FIntPoint& TickGroup, const int32 TickIndex, const FName& TickName, ULFPIndexTickerComponent* Caller)
{
}
