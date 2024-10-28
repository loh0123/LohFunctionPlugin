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

	FLFPWorldMessageBindData( const FGameplayTag& NewTagChannel ) : TagChannel( NewTagChannel ) {}

protected:

	UPROPERTY()
	FGameplayTag TagChannel = FGameplayTag::EmptyTag;

public:

	UPROPERTY()
	FLFPWorldMessageCallbackDelegate CallbackDelegate;

public:

	const FGameplayTag& GetTagChannel() const
	{
		return TagChannel;
	}

	bool operator==( const FGameplayTag& other ) const
	{
		return TagChannel == other;
	}
};

UCLASS()
class LOHFUNCTIONPLUGININFOMATION_API ULFPWorldMessageSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:

	UPROPERTY( Transient )
	TArray<FLFPWorldMessageBindData> BindList = TArray<FLFPWorldMessageBindData>();

public:

	UFUNCTION()
	FLFPWorldMessageCallbackDelegate& AddListener( const FGameplayTag TagChannel , UObject* ListenerObject );

	UFUNCTION()
	void RemoveListener( const FGameplayTag TagChannel , UObject* ListenerObject );

public:

	UFUNCTION( BlueprintCallable , Category = LFPWorldMessageSubsystem )
	void BroadcastMessage( const FGameplayTag TagChannel , UObject* Payload ) const;
};
