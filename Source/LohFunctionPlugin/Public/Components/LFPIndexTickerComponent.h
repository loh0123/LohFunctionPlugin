// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Object/LFPTickerObject.h"
#include "LFPIndexTickerComponent.generated.h"


USTRUCT(BlueprintType)
struct FLFPIndexTickData
{
	GENERATED_BODY()

public:

	FLFPIndexTickData() : Index(INDEX_NONE), Interval(INDEX_NONE) {}
	FLFPIndexTickData(const int32 NewIndex) : Index(NewIndex), Interval(INDEX_NONE) {}
	FLFPIndexTickData(const int32 NewIndex, const FName NewTickName) : Index(NewIndex), TickName(NewTickName), Interval(INDEX_NONE) {}
	FLFPIndexTickData(const int32 NewIndex, const FName NewTickName, const TSubclassOf<ULFPTickerObject> NewTicker, const int32 NewMaxInterval, const int32 NewAmount) : Index(NewIndex), TickName(NewTickName), Ticker(NewTicker), MaxInterval(NewMaxInterval), Interval(NewMaxInterval), Amount(NewAmount) {}

public:

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "LFPIndexTickData")
		int32 Index = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "LFPIndexTickData")
		FName TickName = FName();

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "LFPIndexTickData")
		TSubclassOf<ULFPTickerObject> Ticker = nullptr;

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "LFPIndexTickData")
		int32 MaxInterval = INDEX_NONE;

	UPROPERTY(BlueprintReadOnly, SaveGame, Category = "LFPIndexTickData")
		int32 Interval = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "LFPIndexTickData")
		int32 Amount = INDEX_NONE;

public: // Operator

	bool operator==(const FLFPIndexTickData& Other) const
	{
		return Index == Other.Index;
	}

public:

	FORCEINLINE void TryRunTicker(const FIntPoint& TickGroup, ULFPIndexTickerComponent* Caller) const
	{
		if (IsValid(Ticker))
		{
			Ticker.GetDefaultObject()->OnExecute(TickGroup, Index, TickName, Caller);
		}
	}

	FORCEINLINE bool CanTick() const
	{
		return Interval <= 0;
	}

	FORCEINLINE bool CanRemove() const
	{
		return Interval <= 0 && Amount == 0;
	}

	FORCEINLINE int32 DecreaseInterval()
	{
		Interval -= 1;

		if (Interval < 0)
		{
			Interval = MaxInterval;
		}

		if (CanTick() && Amount > 0)
		{
			Amount -= 1;
		}

		return Interval;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FLFPOnIndex, const int32, TickIndex, const FName&, TickName, const FIntPoint, GroupIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLFPOnGroup, const FIntPoint, GroupIndex);

USTRUCT(BlueprintType)
struct FLFPIndexTickGroupData
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "LFPIndexTickGroupData")
		TArray<FLFPIndexTickData> Members = TArray<FLFPIndexTickData>();

public:

	FORCEINLINE void Tick(const FLFPOnIndex& TickDelegator, const FLFPOnIndex& RemoveDelegator, const FIntPoint GroupIndex, ULFPIndexTickerComponent* Caller)
	{
		Members.RemoveAllSwap([&](FLFPIndexTickData& CurrentTickIndex)
			{
				CurrentTickIndex.DecreaseInterval();

				if (CurrentTickIndex.CanTick())
				{
					CurrentTickIndex.TryRunTicker(GroupIndex, Caller);

					TickDelegator.Broadcast(CurrentTickIndex.Index, CurrentTickIndex.TickName, GroupIndex);
				}

				if (CurrentTickIndex.CanRemove())
				{
					RemoveDelegator.Broadcast(CurrentTickIndex.Index, CurrentTickIndex.TickName, GroupIndex);

					return true;
				}

				return false;
			});

		return;
	}

	FORCEINLINE bool CanRemove() const
	{
		return Members.Num() <= 0;
	}
};

UCLASS( ClassGroup=(LFPlugin), meta=(BlueprintSpawnableComponent), Blueprintable )
class LOHFUNCTIONPLUGIN_API ULFPIndexTickerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPIndexTickerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UFUNCTION(BlueprintCallable, Category = "LFPIndexTickerComponent | Function")
		virtual bool CallTick();

	UFUNCTION(BlueprintCallable, Category = "LFPIndexTickerComponent | Function")
		FORCEINLINE void AddTickIndex(const FLFPIndexTickData& TickData, const FIntPoint GroupIndex);

	UFUNCTION(BlueprintCallable, Category = "LFPIndexTickerComponent | Function")
		FORCEINLINE bool RemoveTickIndex(const int32 TickIndex, const FIntPoint GroupIndex);

	UFUNCTION(BlueprintCallable, Category = "LFPIndexTickerComponent | Group")
		FORCEINLINE void LoadGroupList(const TMap<FIntPoint, FLFPIndexTickGroupData>& SaveVariable, const TArray<FIntPoint>& GroupIndexList);

	UFUNCTION(BlueprintCallable, Category = "LFPIndexTickerComponent | Group")
		FORCEINLINE void SaveGroupList(TMap<FIntPoint, FLFPIndexTickGroupData>& SaveVariable, const TArray<FIntPoint>& GroupIndexList);

public: /** Delegate */

	UPROPERTY(BlueprintAssignable, Category = "LFPIndexTickerComponent | Delegate")
		FLFPOnIndex OnTick;

	UPROPERTY(BlueprintAssignable, Category = "LFPIndexTickerComponent | Delegate")
		FLFPOnGroup OnGroupRemove;

	UPROPERTY(BlueprintAssignable, Category = "LFPIndexTickerComponent | Delegate")
		FLFPOnGroup OnGroupAdded;

	UPROPERTY(BlueprintAssignable, Category = "LFPIndexTickerComponent | Delegate")
		FLFPOnIndex OnIndexRemove;

	UPROPERTY(BlueprintAssignable, Category = "LFPIndexTickerComponent | Delegate")
		FLFPOnIndex OnIndexAdded;

	UPROPERTY(BlueprintAssignable, Category = "LFPIndexTickerComponent | Delegate")
		FLFPOnIndex OnIndexUpdated;

protected:

	UPROPERTY(BlueprintReadWrite, Category = "LFPIndexTickerComponent ")
		bool bAllowAutoTick = true;

private:

	UPROPERTY(SaveGame) TMap<FIntPoint, FLFPIndexTickGroupData> TickList;
};
