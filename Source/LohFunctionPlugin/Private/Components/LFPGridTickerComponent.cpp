// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LFPGridTickerComponent.h"

// Sets default values for this component's properties
ULFPGridTickerComponent::ULFPGridTickerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	// ...
}


// Called when the game starts
void ULFPGridTickerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(TickerTable))
	{
		if (TickerTable->GetRowStruct()->IsChildOf(FLFPGridTickerTable::StaticStruct()) == false)
		{
			TickerTable = nullptr;

			UE_LOG(LogTemp, Warning, TEXT("TickerTable Is Not Using Struct ( FLFPGridTickerTable )"));
		}
	}
}

void ULFPGridTickerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	SetupContainer(nullptr);
}


// Called every frame
void ULFPGridTickerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

ULFPTickerObject* ULFPGridTickerComponent::GetRandomTicker(const FIntPoint GroupIndex, const int32 TickIndex) const
{
	const auto& GridPalette = GridContainer->GetGridPalette(GroupIndex.X, GroupIndex.Y, TickIndex);

	const auto TickerStruct = reinterpret_cast<FLFPGridTickerTable*>(TickerTable->FindRowUnchecked(GridPalette.Name));

	if (TickerStruct != nullptr && IsValid(TickerStruct->RandomTicker))
	{
		return TickerStruct->RandomTicker->GetDefaultObject<ULFPTickerObject>();
	}

	return nullptr;
}

void ULFPGridTickerComponent::SetupContainer(ULFPGridContainerComponent* NewGridContainer)
{
	if (IsValid(GridContainer))
	{
		GridContainer->OnGridContainerChuckUpdate.RemoveDynamic(this, &ULFPGridTickerComponent::OnUpdateChuck);
	}

	GridContainer = nullptr;

	if (IsValid(NewGridContainer))
	{
		NewGridContainer->OnGridContainerChuckUpdate.AddDynamic(this, &ULFPGridTickerComponent::OnUpdateChuck);

		GridContainer = NewGridContainer;
	}
}

void ULFPGridTickerComponent::OnUpdateChuck(const int32 RegionIndex, const int32 ChuckIndex, const FLFPGridUpdateAction& GridUpdateAction)
{
	if (IsValid(GridContainer) == false || IsValid(TickerTable) == false) return;

	for (const auto& GridData : GridUpdateAction.ChangePalette)
	{
		const auto& GridPalette = GridContainer->GetGridPalette(RegionIndex, ChuckIndex, GridData.Key);

		const auto TickerStruct = reinterpret_cast<FLFPGridTickerTable*>(TickerTable->FindRowUnchecked(GridPalette.Name));

		if (TickerStruct != nullptr)
		{
			if (TickerStruct->bIsRandomOnly)
			{
				AddTickGroup(FIntPoint(RegionIndex, ChuckIndex));
			}
			else
			{
				const FLFPIndexTickData NewTickData = FLFPIndexTickData(TickerStruct->ScheduleTicker, TickerStruct->TickDelay + FMath::RandHelper(TickerStruct->TickRandomOffset));

				ScheduledTickIndex(NewTickData, GridData.Key, FIntPoint(RegionIndex, ChuckIndex));
			}
		}
	}
}

