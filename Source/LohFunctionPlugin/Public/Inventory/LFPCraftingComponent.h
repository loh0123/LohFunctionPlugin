// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LFPCraftingComponent.generated.h"


/**
* Crafting System
* Has a crafting queue
* Can connect inventory
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPCraftingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPCraftingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public: // Function

	//UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPCraftingComponent | Function")
	//	bool SetInventoryComponent();
	//
	//UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPCraftingComponent | Function")
	//	bool StartCraftItem();
	//
	//UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPCraftingComponent | Function")
	//	bool StopCraftItem();
	//
	//UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPCraftingComponent | Function")
	//	bool PauseCraftItem();
	//
	//UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPCraftingComponent | Function")
	//	bool ResumeCraftItem();
	//
	//UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPCraftingComponent | Function")
	//	bool DeleteCraftItem();
	//
	//UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "LFPCraftingComponent | Function")
	//	bool ClearCraftQueue();
	
public: // Event

	//UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "LFPCraftingComponent | Event")
	//	bool CanCraftItem() const;
	//	virtual bool CanCraftItem_Implementation() const { return true; }


public: // Getter

	//UFUNCTION(BlueprintPure, Category = "LFPCraftingComponent | Function")
	//	void GetQueueItem();
};
