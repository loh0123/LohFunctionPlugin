// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/WorldSubsystem.h"
#include "LFPWorldMessageSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN( LFPWorldMessageSubsystem , Log , All );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FLFPWorldMessageCallbackDelegate , const FGameplayTag& , Tag , UObject* , Payload );

USTRUCT()
struct FLFPWorldMessageBindData
{
	GENERATED_BODY()

	FLFPWorldMessageBindData() = default;

public:

	UPROPERTY()
	FLFPWorldMessageCallbackDelegate CallbackDelegate;

	UPROPERTY()
	TSet<FGameplayTag> ChildTagList = TSet<FGameplayTag>();

public:

	bool CanRemove() const
	{
		return ChildTagList.IsEmpty() && CallbackDelegate.IsBound() == false;
	}
};

UCLASS()
class LOHFUNCTIONPLUGININFOMATION_API ULFPWorldMessageSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:

	UPROPERTY( Transient )
	TMap<FGameplayTag , FLFPWorldMessageBindData> BindList = TMap<FGameplayTag , FLFPWorldMessageBindData>();

public:

	UFUNCTION()
	FLFPWorldMessageCallbackDelegate& AddListener( const FGameplayTag TagChannel , UObject* ListenerObject );

	UFUNCTION()
	void RemoveListener( const FGameplayTag TagChannel , UObject* ListenerObject );

public:

	UFUNCTION( BlueprintCallable , Category = LFPWorldMessageSubsystem )
	void BroadcastMessage( const FGameplayTag TagChannel , UObject* Payload ) const;
};
