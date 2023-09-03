// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Components/LFPIndexTickerComponent.h"
#include "Components/LFPGridContainerComponent.h"
#include "LFPGridTickerComponent.generated.h"

USTRUCT(BlueprintType)
struct FLFPGridTickerTable : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LFPGridTickerTable") 
		bool bIsRandomOnly = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LFPGridTickerTable")
		TSubclassOf<ULFPTickerObject> RandomTicker = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LFPGridTickerTable", meta = (EditCondition = "!bIsRandomOnly"))
		TSubclassOf<ULFPTickerObject> ScheduleTicker = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LFPGridTickerTable", meta = (EditCondition = "!bIsRandomOnly")) 
		int32 TickDelay = INDEX_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LFPGridTickerTable", meta = (EditCondition = "!bIsRandomOnly")) 
		int32 TickRandomOffset = 0;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPGridTickerComponent : public ULFPIndexTickerComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPGridTickerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual ULFPTickerObject* GetRandomTicker(const FIntPoint GroupIndex, const int32 TickIndex) const override;

public:

	UFUNCTION(BlueprintCallable, Category = "LFPGridTickerComponent | Function")
		FORCEINLINE void SetupContainer(ULFPGridContainerComponent* NewGridContainer);

protected:

	UFUNCTION()
		FORCEINLINE void OnUpdateChuck(const int32 RegionIndex, const int32 ChuckIndex, const FLFPGridUpdateAction& GridUpdateAction);

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPGridTickerComponent ")
		TObjectPtr<UDataTable> TickerTable = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "LFPGridTickerComponent ")
		TObjectPtr<ULFPGridContainerComponent> GridContainer = nullptr;
};
