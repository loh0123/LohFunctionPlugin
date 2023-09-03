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
	FLFPIndexTickData(const TSubclassOf<ULFPTickerObject> NewTicker) : Ticker(NewTicker), Delay(INDEX_NONE) {}
	FLFPIndexTickData(const TSubclassOf<ULFPTickerObject> NewTicker, const int32 NewDelay) : Ticker(NewTicker), Delay(NewDelay) {}

public:

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "LFPIndexTickData")
		TSubclassOf<ULFPTickerObject> Ticker = nullptr;

	UPROPERTY(BlueprintReadOnly, SaveGame, Category = "LFPIndexTickData")
		int32 Delay = INDEX_NONE;

public:

	FORCEINLINE bool TryRunTicker(const FIntPoint& TickGroup, ULFPIndexTickerComponent* Caller, bool& bCanRemove, const int32 TickIndex) const
	{
		if (IsValid(Ticker))
		{
			Ticker.GetDefaultObject()->OnExecute(TickGroup, TickIndex, Caller);

			return true;
		}

		return false;
	}

	FORCEINLINE bool DecreaseDelay()
	{
		if (Delay > 0) Delay -= 1;

		return Delay <= 0;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLFPOnIndex, const int32, TickIndex, const FIntPoint, GroupIndex);

USTRUCT(BlueprintType)
struct FLFPIndexTickGroupData
{
	GENERATED_BODY()

	FLFPIndexTickGroupData() {}

	FLFPIndexTickGroupData(const int32 StartIndex) : RandomTickIndex(StartIndex) {}

public:

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "LFPIndexTickGroupData")
		int32 RandomTickIndex = 0;

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "LFPIndexTickGroupData")
		TMap<int32, FLFPIndexTickData> ScheduledTickList = TMap<int32, FLFPIndexTickData>();
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
		FORCEINLINE void CallTick(const bool bRandomTick = true, const bool bScheduledTick = true);

	UFUNCTION(BlueprintCallable, Category = "LFPIndexTickerComponent | Function")
		FORCEINLINE void AddTickGroup(const FIntPoint GroupIndex);

	UFUNCTION(BlueprintCallable, Category = "LFPIndexTickerComponent | Function")
		FORCEINLINE void ScheduledTickIndex(const FLFPIndexTickData& TickData, const int32 TickIndex, const FIntPoint GroupIndex);

	UFUNCTION(BlueprintCallable, Category = "LFPIndexTickerComponent | Group")
		FORCEINLINE void LoadGroupList(const TMap<FIntPoint, FLFPIndexTickGroupData>& SaveVariable, const TArray<FIntPoint>& GroupIndexList);

	UFUNCTION(BlueprintCallable, Category = "LFPIndexTickerComponent | Group")
		FORCEINLINE void SaveGroupList(TMap<FIntPoint, FLFPIndexTickGroupData>& SaveVariable, const TArray<FIntPoint>& GroupIndexList, const bool bUnload);

protected:

	UFUNCTION()
		FORCEINLINE int32 GetCacheRandomTickIndex(FLFPIndexTickGroupData& Data);

	UFUNCTION()
		virtual ULFPTickerObject* GetRandomTicker(const FIntPoint GroupIndex, const int32 TickIndex) const { return nullptr; }

public: /** Delegate */

	UPROPERTY(BlueprintAssignable, Category = "LFPIndexTickerComponent | Delegate")
		FLFPOnIndex OnRandomTick;

	UPROPERTY(BlueprintAssignable, Category = "LFPIndexTickerComponent | Delegate")
		FLFPOnIndex OnScheduledTick;

	UPROPERTY(BlueprintAssignable, Category = "LFPIndexTickerComponent | Delegate")
		FLFPOnIndex OnScheduledRemove;

	UPROPERTY(BlueprintAssignable, Category = "LFPIndexTickerComponent | Delegate")
		FLFPOnIndex OnScheduledAdded;

protected:

	UPROPERTY(BlueprintReadOnly, EditAnyWhere, Category = "LFPIndexTickerComponent ")
		bool bAllowAutoRandomTick = true;

	UPROPERTY(BlueprintReadOnly, EditAnyWhere, Category = "LFPIndexTickerComponent ")
		bool bAllowAutoScheduledTick = true;

	UPROPERTY(BlueprintReadOnly, EditAnyWhere, Category = "LFPIndexTickerComponent ")
		int32 RandomTickCount = 256;

	UPROPERTY(BlueprintReadOnly, EditAnyWhere, Category = "LFPIndexTickerComponent ")
		int32 RandomTickSeed = 01234567;

	UPROPERTY(BlueprintReadOnly, EditAnyWhere, Category = "LFPIndexTickerComponent ")
		int32 RandomTickMaxIndex = 4096;

private:

	UPROPERTY()
		TArray<int32> CacheRandomTickList = TArray<int32>();

	UPROPERTY(SaveGame) 
		TMap<FIntPoint, FLFPIndexTickGroupData> TickList = TMap<FIntPoint, FLFPIndexTickGroupData>();
};
