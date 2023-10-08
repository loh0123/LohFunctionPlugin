// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/WorldSubsystem.h"
#include "LFPGameplayTagSubsystem.generated.h"

USTRUCT()
struct FLFPGameplayTagBindData
{
    GENERATED_BODY()

private:

    UPROPERTY()
        TArray<TObjectPtr<UActorComponent>> BindedObjectList = TArray<TObjectPtr<UActorComponent>>();

public:

    void BindObject(UActorComponent* Component)
    {
        BindedObjectList.Add(Component);
    }

    void UnbindObject(UActorComponent* Component)
    {
        BindedObjectList.RemoveSingle(Component);
    }

    const TArray<TObjectPtr<UActorComponent>>& GetBindedObjectList() const
    {
        return BindedObjectList;
    }

    int32 BindedObjectNum() const
    {
        return BindedObjectList.Num();
    }
};

/**
 * 
 */
UCLASS()
class LOHFUNCTIONPLUGINGAMEPLAYTAG_API ULFPGameplayTagSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

    // Begin USubsystem
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    // End USubsystem

    UFUNCTION(BlueprintCallable, Category = "LFPGameplayTagSubsystem|Set", meta = (GameplayTagFilter = "Component.Identifiers"))
        void RegisterComponent(const FGameplayTag Tag, UActorComponent* Component);

    UFUNCTION(BlueprintCallable, Category = "LFPGameplayTagSubsystem|Set", meta = (GameplayTagFilter = "Component.Identifiers"))
        void RegisterComponentByContainer(const FGameplayTagContainer Tags, UActorComponent* Component);

    UFUNCTION(BlueprintCallable, Category = "LFPGameplayTagSubsystem|Set", meta = (GameplayTagFilter = "Component.Identifiers"))
        void UnregisterComponent(const FGameplayTag Tag, UActorComponent* Component);

    UFUNCTION(BlueprintCallable, Category = "LFPGameplayTagSubsystem|Set", meta = (GameplayTagFilter = "Component.Identifiers"))
        void UnregisterComponentByContainer(const FGameplayTagContainer Tags, UActorComponent* Component);

    UFUNCTION(BlueprintCallable, Category = "LFPGameplayTagSubsystem|Get", meta = (GameplayTagFilter = "Component.Identifiers", AutoCreateRefTerm = ComponentTagList))
        void FindComponentListByTag(TArray<UActorComponent*>& ComponentList, const FGameplayTag ComponentGameplayTag, const TArray<FName>& ComponentTagList, const bool bHasAllTags = false) const;

    UFUNCTION(BlueprintCallable, Category = "LFPGameplayTagSubsystem|Get", meta = (GameplayTagFilter = "Component.Identifiers", AutoCreateRefTerm = ComponentTagList))
        void FindComponentListByTags(TArray<UActorComponent*>& ComponentList, const FGameplayTagContainer ComponentGameplayTags, const TArray<FName>& ComponentTagList, const bool bHasAllTags = false) const;

    UFUNCTION(BlueprintCallable, Category = "LFPGameplayTagSubsystem|Event", meta = (GameplayTagFilter = "Component"))
        void BroadcastGameplayTagEvent(const FGameplayTagContainer ComponentTags, const FGameplayTag EventTag, UObject* Caller, const FString Messages) const;


    UFUNCTION(BlueprintCallable, Category = "LFPGameplayTagSubsystem|Get", meta = (GameplayTagFilter = "Component.Identifiers", AutoCreateRefTerm = ComponentTagList))
        bool HasComponentWithTag(const FGameplayTag ComponentGameplayTag, const TArray<FName>& ComponentTagList, const bool bHasAllTags = false) const;

    UFUNCTION(BlueprintCallable, Category = "LFPGameplayTagSubsystem|Get", meta = (GameplayTagFilter = "Component.Identifiers", AutoCreateRefTerm = ComponentTagList))
        bool HasComponentWithTags(const FGameplayTagContainer ComponentGameplayTags, const TArray<FName>& ComponentTagList, const bool bHasAllTags = false) const;

public:

    UPROPERTY()
        TMap<FGameplayTag, FLFPGameplayTagBindData> ReferenceMap = TMap<FGameplayTag, FLFPGameplayTagBindData>();

    UPROPERTY() 
        FGameplayTagContainer TagContainer = FGameplayTagContainer();
};
