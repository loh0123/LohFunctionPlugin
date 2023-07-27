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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LFPGridTickerTable") TSubclassOf<ULFPTickerObject> Ticker = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LFPGridTickerTable") int32 TickMaxIteration = INDEX_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LFPGridTickerTable") int32 TickAmount = INDEX_NONE;
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

public:

	UFUNCTION(BlueprintCallable, Category = "LFPGridTickerComponent | Function")
		FORCEINLINE void SetupContainer(ULFPGridContainerComponent* NewGridContainer);

protected:

	UFUNCTION(BlueprintNativeEvent, Category = "LFPGridTickerComponent | Event")
		bool CanGridIndexTick(const int32 RegionIndex, const int32 ChuckIndex, const int32 GridIndex, const FName& TickName, const FLFPGridPaletteData& PaletteData, ULFPIndexTickerComponent* Caller);

	UFUNCTION()
		FORCEINLINE void OnUpdateChuck(const int32 RegionIndex, const int32 ChuckIndex, const FLFPGridUpdateAction& GridUpdateAction);

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "LFPGridTickerComponent ")
		TObjectPtr<UDataTable> TickerTable = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "LFPGridTickerComponent ")
		TObjectPtr<ULFPGridContainerComponent> GridContainer = nullptr;
};