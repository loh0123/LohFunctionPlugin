// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/WorldSubsystem.h"
#include "Components/LFPTagReferenceComponent.h"
#include "LFPWorldReferenceSubsystem.generated.h"

USTRUCT()
struct FLFPGameplayTagBindData
{
	GENERATED_BODY()

private:

	UPROPERTY()
		TArray<TObjectPtr<ULFPTagReferenceComponent>> BindedObjectList = TArray<TObjectPtr<ULFPTagReferenceComponent>>();

public:

	UPROPERTY()
		TSet<FGameplayTag> ChildTagList = TSet<FGameplayTag>();

public:

	void BindObject(ULFPTagReferenceComponent* Component)
	{
		BindedObjectList.Add(Component);
	}

	void UnbindObject(ULFPTagReferenceComponent* Component)
	{
		BindedObjectList.RemoveSingle(Component);
	}

	const TArray<TObjectPtr<ULFPTagReferenceComponent>>& GetBindedObjectList() const
	{
		return BindedObjectList;
	}

	int32 BindedObjectNum() const
	{
		return BindedObjectList.Num();
	}

	bool CanRemove() const
	{
		return BindedObjectList.IsEmpty() && ChildTagList.IsEmpty();
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLFPGameplayTagComponentUpdate, UActorComponent*, Component);

/**
 * 
 */
UCLASS()
class LOHFUNCTIONPLUGINGAMEPLAYTAG_API ULFPWorldReferenceSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

private:

	FORCEINLINE bool ProcessActorComponent(
		const FGameplayTagContainer& CategoryGameplayTags, 
		const FGameplayTagContainer& ComponentGameplayTags,
		const bool bHasAllTags,
		const TFunctionRef<bool(ULFPTagReferenceComponent* FoundedComponent)> OnMatchComponentFounded,
		const TFunctionRef<bool()> OnEnd
	) const;

public:

	UFUNCTION()
	void RegisterComponent(ULFPTagReferenceComponent* Component);

	UFUNCTION()
	void UnregisterComponent(ULFPTagReferenceComponent* Component);

public:

	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem

	UFUNCTION(BlueprintCallable, Category = "LFPGameplayTagSubsystem|Get", meta = (GameplayTagFilter = "Component.Identifiers", AutoCreateRefTerm = ComponentTagList))
		bool FindComponentListByTagList(TArray<ULFPTagReferenceComponent*>& ComponentList, const FGameplayTagContainer CategoryGameplayTags, const FGameplayTagContainer ComponentGameplayTags, const bool bHasAllTags = false) const;

	UFUNCTION(BlueprintCallable, Category = "LFPGameplayTagSubsystem|Get", meta = (GameplayTagFilter = "Component.Identifiers", AutoCreateRefTerm = ComponentTagList))
		bool FindActorListByTagList(TArray<AActor*>& ActorList, const FGameplayTagContainer CategoryGameplayTags, const FGameplayTagContainer ComponentGameplayTags, const bool bHasAllTags = false) const;

	UFUNCTION(BlueprintCallable, Category = "LFPGameplayTagSubsystem|Get", meta = (GameplayTagFilter = "Component.Identifiers", AutoCreateRefTerm = ComponentTagList))
		bool FindActorListByInterface(TArray<AActor*>& ActorList, const TSubclassOf<UInterface> Interface, const FGameplayTagContainer CategoryGameplayTags, const FGameplayTagContainer ComponentGameplayTags, const bool bHasAllTags = false) const;

	UFUNCTION(BlueprintCallable, Category = "LFPGameplayTagSubsystem|Event", meta = (GameplayTagFilter = "Component"))
		bool BroadcastGameplayTagEvent(const FGameplayTagContainer CategoryGameplayTags, const FGameplayTagContainer ComponentGameplayTags, const bool bHasAllTags, const FGameplayTag EventTag, UObject* Caller, const FString Messages) const;


	UFUNCTION(BlueprintCallable, Category = "LFPGameplayTagSubsystem|Get", meta = (GameplayTagFilter = "Component.Identifiers", AutoCreateRefTerm = ComponentTagList))
		bool HasComponentWithTags(const FGameplayTagContainer CategoryGameplayTags, const FGameplayTagContainer ComponentGameplayTags, const bool bHasAllTags = false) const;

public:

	UPROPERTY(BlueprintAssignable, Category = Events)
		FLFPGameplayTagComponentUpdate OnRegisterComponent;

	UPROPERTY(BlueprintAssignable, Category = Events)
		FLFPGameplayTagComponentUpdate OnUnregisterComponent;

public:

	UPROPERTY()
		TMap<FGameplayTag, FLFPGameplayTagBindData> ReferenceMap = TMap<FGameplayTag, FLFPGameplayTagBindData>();
};
