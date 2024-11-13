#pragma once

#include "Engine/CancellableAsyncAction.h"
#include "GameplayTagContainer.h"
#include "LFPInfomationAsync_ListenForWorldMessage.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FLFPListenForWorldMessageDelegate , UObject* , Payload );

class ULFPWorldMessageSubsystem;

UCLASS()
class LOHFUNCTIONPLUGININFOMATION_API ULFPInfomationAsync_ListenForWorldMessage : public UCancellableAsyncAction
{
	GENERATED_BODY()

protected:

	virtual void Cancel() override;

	virtual void Activate() override;

public:

	UFUNCTION( BlueprintCallable , Category = "Information|Tasks" , meta = ( WorldContext = "WorldContext" , BlueprintInternalUseOnly = "TRUE" ) )
	static ULFPInfomationAsync_ListenForWorldMessage* ListenForWorldMessage( UObject* WorldContext , const FGameplayTag TagChannel , const  bool bExactOnly = false , const bool bOnlyTriggerOnce = false );

protected:

	UFUNCTION()
	void BroadcastMessage( const FGameplayTag& Tag , UObject* Payload );

public:

	UPROPERTY( BlueprintAssignable )
	FLFPListenForWorldMessageDelegate OnEvent;

public:

	UPROPERTY()
	TWeakObjectPtr<ULFPWorldMessageSubsystem> EventSubsystem = nullptr;

	UPROPERTY()
	FGameplayTag TagChannel = FGameplayTag::EmptyTag;

	UPROPERTY()
	bool bExactOnly = false;

	UPROPERTY()
	bool bOnlyTriggerOnce = false;
};
