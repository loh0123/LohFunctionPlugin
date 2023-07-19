// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LFPIndexTickManager.generated.h"


USTRUCT(BlueprintType)
struct FLFPIndexTickData
{
	GENERATED_BODY()

public:

	FLFPIndexTickData() : Index(INDEX_NONE), Interval(INDEX_NONE) {}
	FLFPIndexTickData(const int32 NewIndex) : Index(NewIndex), Interval(INDEX_NONE) {}
	FLFPIndexTickData(const int32 NewIndex, const FName NewTickName) : Index(NewIndex), TickName(NewTickName), Interval(INDEX_NONE) {}
	FLFPIndexTickData(const int32 NewIndex, const FName NewTickName, const int32 NewMaxInterval, const int32 NewAmount) : Index(NewIndex), TickName(NewTickName), MaxInterval(NewMaxInterval), Interval(NewMaxInterval), Amount(NewAmount) {}

public:

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "LFPIndexTickData")
		int32 Index = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "LFPIndexTickData")
		FName TickName = FName();

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "LFPIndexTickData")
		int32 MaxInterval = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "LFPIndexTickData")
		int32 Interval = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "LFPIndexTickData")
		int32 Amount = INDEX_NONE;

public: // Operator

	bool operator==(const FLFPIndexTickData& Other) const
	{
		return Index == Other.Index;
	}

public:

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
		if (CanTick())
		{
			if (Amount > 0) Amount -= 1;

			Interval = MaxInterval;

			return Interval;
		}
		else
		{
			return --Interval;
		}
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLFPOnTick, const int32, TickIndex, const FName&, TickName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FLFPOnIndex, const int32, TickIndex, const FName&, TickName, const int32, GroupIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLFPOnGroup, const int32, GroupIndex);

USTRUCT(BlueprintType)
struct FLFPIndexTickGroupData
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "LFPIndexTickGroupData")
		TArray<FLFPIndexTickData> Members = TArray<FLFPIndexTickData>();

public:

	FORCEINLINE void Tick(const FLFPOnTick& TickDelegator, const FLFPOnIndex& RemoveDelegator, const int32 GroupIndex)
	{
		Members.RemoveAllSwap([&](FLFPIndexTickData& CurrentTickIndex)
			{
				CurrentTickIndex.DecreaseInterval();

				if (CurrentTickIndex.CanTick())
				{
					TickDelegator.Broadcast(CurrentTickIndex.Index, CurrentTickIndex.TickName);
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
class LOHFUNCTIONPLUGIN_API ULFPIndexTickManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPIndexTickManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UFUNCTION(BlueprintCallable, Category = "LFPIndexTickManager | Function")
		FORCEINLINE bool CallTick();

	UFUNCTION(BlueprintCallable, Category = "LFPIndexTickManager | Function")
		FORCEINLINE void AddTickIndex(const FLFPIndexTickData& TickData, const int32 GroupIndex);

	UFUNCTION(BlueprintCallable, Category = "LFPIndexTickManager | Function")
		FORCEINLINE bool RemoveTickIndex(const int32 TickIndex, const int32 GroupIndex);

	UFUNCTION(BlueprintCallable, Category = "LFPIndexTickManager | Group")
		FORCEINLINE bool LoadGroup(const TMap<int32, FLFPIndexTickGroupData>& SaveVariable, const int32 GroupIndex);

	UFUNCTION(BlueprintCallable, Category = "LFPIndexTickManager | Group")
		FORCEINLINE bool SaveGroup(TMap<int32, FLFPIndexTickGroupData>& SaveVariable, const int32 GroupIndex);

public: /** Delegate */

	UPROPERTY(BlueprintAssignable, Category = "LFPIndexTickManager | Delegate")
		FLFPOnTick OnTick;

	UPROPERTY(BlueprintAssignable, Category = "LFPIndexTickManager | Delegate")
		FLFPOnGroup OnGroupRemove;

	UPROPERTY(BlueprintAssignable, Category = "LFPIndexTickManager | Delegate")
		FLFPOnGroup OnGroupAdded;

	UPROPERTY(BlueprintAssignable, Category = "LFPIndexTickManager | Delegate")
		FLFPOnIndex OnIndexRemove;

	UPROPERTY(BlueprintAssignable, Category = "LFPIndexTickManager | Delegate")
		FLFPOnIndex OnIndexAdded;

	UPROPERTY(BlueprintAssignable, Category = "LFPIndexTickManager | Delegate")
		FLFPOnIndex OnIndexUpdated;

protected:

	UPROPERTY(BlueprintReadWrite, Category = "LFPIndexTickManager ")
		bool bAllowAutoTick = true;

private:

	UPROPERTY(SaveGame) TMap<int32, FLFPIndexTickGroupData> TickList;
};
