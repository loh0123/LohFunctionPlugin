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

	FLFPIndexTickData() : Interval(INDEX_NONE) {}
	FLFPIndexTickData(const FName NewTickName) : TickName(NewTickName), Interval(INDEX_NONE) {}
	FLFPIndexTickData(const FName NewTickName, const TSubclassOf<ULFPTickerObject> NewTicker, const int32 NewMaxInterval, const int32 NewTickOffset, const int32 NewAmount) : TickName(NewTickName), Ticker(NewTicker), MaxInterval(NewMaxInterval), Interval(NewMaxInterval + NewTickOffset), Amount(NewAmount) {}

public:

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

public:

	FORCEINLINE bool TryStartTicker(const FIntPoint& TickGroup, ULFPIndexTickerComponent* Caller, const int32 Index) const
	{
		if (IsValid(Ticker))
		{
			Ticker.GetDefaultObject()->OnBegin(TickGroup, Index, TickName, Caller);

			return true;
		}

		return false;
	}

	FORCEINLINE bool TryRunTicker(const FIntPoint& TickGroup, ULFPIndexTickerComponent* Caller, const int32 Index) const
	{
		if (IsValid(Ticker))
		{
			Ticker.GetDefaultObject()->OnExecute(TickGroup, Index, TickName, Caller);

			return true;
		}

		return false;
	}

	FORCEINLINE bool TryEndTicker(const FIntPoint& TickGroup, ULFPIndexTickerComponent* Caller, const int32 Index) const
	{
		if (IsValid(Ticker))
		{
			Ticker.GetDefaultObject()->OnEnd(TickGroup, Index, TickName, Caller);

			return true;
		}

		return false;
	}

	FORCEINLINE bool CanTick() const
	{
		return Interval <= 0;
	}

	FORCEINLINE bool CanRemove() const
	{
		return CanTick() && Amount == 0;
	}

	FORCEINLINE int32 DecreaseInterval()
	{
		if (Interval > -1) Interval -= 1;

		if (Interval < 0 && Amount > 0)
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
		TMap<int32, FLFPIndexTickData> MemberList = TMap<int32, FLFPIndexTickData>();

protected:

	UPROPERTY(SaveGame)
		int32 LastTickIndex = 0;

public:

	FORCEINLINE void Tick(const FLFPOnIndex& TickDelegator, const FLFPOnIndex& RemoveDelegator, const FIntPoint GroupIndex, ULFPIndexTickerComponent* Caller, const uint8 TickerRunCounter)
	{
		uint8 CurrentTickerCounter = FMath::Max(TickerRunCounter, uint8(1));

		TArray<int32> RemoveIndexList;

		int32 CurrentIndex = -1;

		if (MemberList.Num() <= LastTickIndex)
		{
			LastTickIndex = 0;
		}

		for (auto& Member : MemberList)
		{
			CurrentIndex++;

			if (CurrentIndex < LastTickIndex)
			{
				continue;
			}

			Member.Value.DecreaseInterval();

			if (Member.Value.CanTick() && CurrentTickerCounter > 0)
			{
				if (Member.Value.TryRunTicker(GroupIndex, Caller, Member.Key) == false)
				{
					TickDelegator.Broadcast(Member.Key, Member.Value.TickName, GroupIndex);
				}

				CurrentTickerCounter--;

				if (Member.Value.CanRemove())
				{
					RemoveDelegator.Broadcast(Member.Key, Member.Value.TickName, GroupIndex);

					RemoveIndexList.Add(Member.Key);
				}
			}

			if (CurrentTickerCounter == 0)
			{
				LastTickIndex = CurrentIndex;

				break;
			}
		}

		for (const int32 RemoveIndex : RemoveIndexList)
		{
			MemberList.Remove(RemoveIndex);
		}

		return;
	}

	FORCEINLINE bool CanRemove() const
	{
		return MemberList.Num() <= 0;
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
		FORCEINLINE void AddTickIndex(const FLFPIndexTickData& TickData, const int32 TickIndex, const FIntPoint GroupIndex);

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

	UPROPERTY(BlueprintReadOnly, EditAnyWhere, Category = "LFPIndexTickerComponent ")
		bool bAllowAutoTick = true;

	UPROPERTY(BlueprintReadOnly, EditAnyWhere, Category = "LFPGridTickerComponent ")
		uint8 MaxTickerRunPerGroup = uint8(255);

private:

	UPROPERTY(SaveGame) TMap<FIntPoint, FLFPIndexTickGroupData> TickList;
};
