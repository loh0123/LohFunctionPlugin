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

	FLFPIndexTickData() {}
	FLFPIndexTickData(const int32 NewTickIndex, const FName NewTickName) : TickIndex(NewTickIndex), TickName(NewTickName) {}
	FLFPIndexTickData(const int32 NewTickIndex, const FName NewTickName, const TSubclassOf<ULFPTickerObject> NewTicker, const int32 NewDelay) : TickIndex(NewTickIndex), TickName(NewTickName), Ticker(NewTicker), Delay(NewDelay) {}

public:

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "LFPIndexTickData")
		int32 TickIndex = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "LFPIndexTickData")
		FName TickName = FName();

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "LFPIndexTickData")
		TSubclassOf<ULFPTickerObject> Ticker = nullptr;

	UPROPERTY(BlueprintReadOnly, SaveGame, Category = "LFPIndexTickData")
		int32 Delay = INDEX_NONE;

public:

	FORCEINLINE bool TryStartTicker(const FIntPoint& TickGroup, ULFPIndexTickerComponent* Caller) const
	{
		if (IsValid(Ticker))
		{
			Ticker.GetDefaultObject()->OnBegin(TickGroup, TickIndex, TickName, Caller);

			return true;
		}

		return false;
	}

	FORCEINLINE bool TryRunTicker(const FIntPoint& TickGroup, ULFPIndexTickerComponent* Caller, bool& bCanRemove) const
	{
		if (IsValid(Ticker))
		{
			bCanRemove = Ticker.GetDefaultObject()->OnExecute(TickGroup, TickIndex, TickName, Caller);

			return true;
		}

		return false;
	}

	FORCEINLINE bool TryEndTicker(const FIntPoint& TickGroup, ULFPIndexTickerComponent* Caller) const
	{
		if (IsValid(Ticker))
		{
			Ticker.GetDefaultObject()->OnEnd(TickGroup, TickIndex, TickName, Caller);

			return true;
		}

		return false;
	}

	FORCEINLINE bool IsDataValid() const
	{
		return TickIndex >= 0 && TickName.IsNone() == false;
	}

	FORCEINLINE bool CanTick() const
	{
		return Delay <= 0;
	}

	FORCEINLINE bool DecreaseDelay()
	{
		if (Delay > 0) Delay -= 1;

		return Delay <= 0;
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
		TArray<FLFPIndexTickData> RandomTickList = TArray<FLFPIndexTickData>();

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "LFPIndexTickGroupData")
		TArray<FLFPIndexTickData> ScheduledTickList = TArray<FLFPIndexTickData>();

public:

	FORCEINLINE void Tick(const FLFPOnIndex& TickDelegator, const FLFPOnIndex& RemoveDelegator, const FIntPoint GroupIndex, ULFPIndexTickerComponent* Caller, const int32 RandomTickCount, const bool bRandomTick, const bool bScheduledTick)
	{
		auto TickFunction = [&](FLFPIndexTickData& Data)
		{
			if (Data.DecreaseDelay())
			{
				bool bCanRemove = true;

				if (Data.TryRunTicker(GroupIndex, Caller, bCanRemove) == false)
				{
					TickDelegator.Broadcast(Data.TickIndex, Data.TickName, GroupIndex);
				}

				return bCanRemove;
			}

			return false;
		};

		if (bScheduledTick) ScheduledTickList.RemoveAllSwap(TickFunction);

		if (bRandomTick)
		{
			const int32 CacheTickCount = FMath::Min(RandomTickList.Num(), RandomTickCount);

			for (int32 Index = 0; Index < CacheTickCount; Index++)
			{
				if (RandomTickList.IsEmpty()) break;

				const int32 TickTarget = FMath::RandHelper(RandomTickList.Num() - 1);

				if (TickFunction(RandomTickList[TickTarget]))
				{
					RandomTickList.RemoveAtSwap(TickTarget);
				}
			}
		}

		return;
	}

	FORCEINLINE bool CanRemove() const
	{
		return RandomTickList.Num() <= 0 && ScheduledTickList.Num() <= 0;
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
		FORCEINLINE bool CallTick(const bool bRandomTick = true, const bool bScheduledTick = true);

	UFUNCTION(BlueprintCallable, Category = "LFPIndexTickerComponent | Function")
		FORCEINLINE void AddTickIndex(const FLFPIndexTickData& TickData, const bool bIsRandomTick, const FIntPoint GroupIndex);

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

protected:

	UPROPERTY(BlueprintReadOnly, EditAnyWhere, Category = "LFPIndexTickerComponent ")
		bool bAllowAutoRandomTick = true;

	UPROPERTY(BlueprintReadOnly, EditAnyWhere, Category = "LFPIndexTickerComponent ")
		bool bAllowAutoScheduledTick = true;

	UPROPERTY(BlueprintReadOnly, EditAnyWhere, Category = "LFPIndexTickerComponent ")
		int32 RandomTickCount = 256;

private:

	UPROPERTY(SaveGame) TMap<FIntPoint, FLFPIndexTickGroupData> TickList;
};
