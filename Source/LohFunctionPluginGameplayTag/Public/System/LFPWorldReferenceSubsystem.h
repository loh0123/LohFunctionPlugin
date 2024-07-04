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

	FORCEINLINE void ProcessActorComponent(
		const FGameplayTagContainer& CategoryGameplayTags, 
		const FGameplayTagContainer& ComponentGameplayTags,
		const bool bHasAllTags,
		const TFunctionRef<bool(ULFPTagReferenceComponent* FoundedComponent)> OnMatchComponentFounded
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

	// Getter //

	UFUNCTION(BlueprintCallable, Category = "LFPGameplayTagSubsystem|Getter", meta = (AutoCreateRefTerm = ComponentTagList))
		bool FindComponentListByTagList(
			TArray<ULFPTagReferenceComponent*>& ComponentList, 
			UPARAM(meta = (Categories = "Component.Category")) const FGameplayTagContainer CategoryGameplayTags, 
			UPARAM(meta = (Categories = "Component.Identifiers")) const FGameplayTagContainer ComponentGameplayTags, 
			const bool bHasAllTags = false
		) const;

	UFUNCTION(BlueprintCallable, Category = "LFPGameplayTagSubsystem|Getter", meta = (AutoCreateRefTerm = ComponentTagList))
		bool FindComponentListByName(
			TArray<ULFPTagReferenceComponent*>& ComponentList, 
			const FName NameTag,
			UPARAM(meta = (Categories = "Component.Category")) const FGameplayTagContainer CategoryGameplayTags,
			UPARAM(meta = (Categories = "Component.Identifiers")) const FGameplayTagContainer ComponentGameplayTags,
			const bool bHasAllTags = false
		) const;

	UFUNCTION(BlueprintCallable, Category = "LFPGameplayTagSubsystem|Getter", meta = (AutoCreateRefTerm = ComponentTagList))
		bool FindActorListByTagList(
			TArray<AActor*>& ActorList, 
			UPARAM(meta = (Categories = "Component.Category")) const FGameplayTagContainer CategoryGameplayTags,
			UPARAM(meta = (Categories = "Component.Identifiers")) const FGameplayTagContainer ComponentGameplayTags,
			const bool bHasAllTags = false
		) const;

	UFUNCTION(BlueprintCallable, Category = "LFPGameplayTagSubsystem|Getter", meta = (AutoCreateRefTerm = ComponentTagList))
		bool FindActorListByName(
			TArray<AActor*>& ActorList,
			const FName NameTag,
			UPARAM(meta = (Categories = "Component.Category")) const FGameplayTagContainer CategoryGameplayTags,
			UPARAM(meta = (Categories = "Component.Identifiers")) const FGameplayTagContainer ComponentGameplayTags,
			const bool bHasAllTags = false
		) const;

	UFUNCTION(BlueprintCallable, Category = "LFPGameplayTagSubsystem|Getter", meta = (AutoCreateRefTerm = ComponentTagList))
		bool FindActorListByInterface(
			TArray<AActor*>& ActorList, 
			const TSubclassOf<UInterface> Interface, 
			UPARAM(meta = (Categories = "Component.Category")) const FGameplayTagContainer CategoryGameplayTags,
			UPARAM(meta = (Categories = "Component.Identifiers")) const FGameplayTagContainer ComponentGameplayTags,
			const bool bHasAllTags = false
		) const;

	// Checker //

	UFUNCTION(BlueprintCallable, Category = "LFPGameplayTagSubsystem|Checker", meta = (AutoCreateRefTerm = ComponentTagList))
		bool HasComponentWithTags(
			UPARAM(meta = (Categories = "Component.Category")) const FGameplayTagContainer CategoryGameplayTags,
			UPARAM(meta = (Categories = "Component.Identifiers")) const FGameplayTagContainer ComponentGameplayTags,
			const bool bHasAllTags = false
		) const;

	UFUNCTION(BlueprintCallable, Category = "LFPGameplayTagSubsystem|Checker", meta = (AutoCreateRefTerm = ComponentTagList))
		bool HasActorWithTags(
			const FName NameTag,
			UPARAM(meta = (Categories = "Component.Category")) const FGameplayTagContainer CategoryGameplayTags,
			UPARAM(meta = (Categories = "Component.Identifiers")) const FGameplayTagContainer ComponentGameplayTags,
			const bool bHasAllTags = false
		) const;

	// Event //

	UFUNCTION(BlueprintCallable, Category = "LFPGameplayTagSubsystem|Event")
		bool BroadcastGameplayTagEvent(
			UPARAM(meta = (Categories = "Component.Category")) const FGameplayTagContainer CategoryGameplayTags,
			UPARAM(meta = (Categories = "Component.Identifiers")) const FGameplayTagContainer ComponentGameplayTags,
			const bool bHasAllTags,
			const FGameplayTag EventTag,
			UObject* Caller,
			const FString Messages
		) const;

public:

	UPROPERTY(BlueprintAssignable, Category = Events)
		FLFPGameplayTagComponentUpdate OnRegisterComponent;

	UPROPERTY(BlueprintAssignable, Category = Events)
		FLFPGameplayTagComponentUpdate OnUnregisterComponent;

public:

	UPROPERTY()
		TMap<FGameplayTag, FLFPGameplayTagBindData> ReferenceMap = TMap<FGameplayTag, FLFPGameplayTagBindData>();
};
