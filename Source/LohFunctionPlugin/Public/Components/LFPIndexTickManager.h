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
	FLFPIndexTickData(const int32 NewIndex, const int32 NewStartInterval) : Index(NewIndex), Interval(NewStartInterval){}

public:

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "LFPIndexTickData")
		int32 Index = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "LFPIndexTickData")
		int32 Interval = INDEX_NONE;

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

	FORCEINLINE int32 DecreaseInterval()
	{
		return --Interval;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTick, const int32, TickIndex);

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

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelContainerComponent | Getter")
		FORCEINLINE void AddTickIndex(const FLFPIndexTickData& TickData);

	UFUNCTION(BlueprintCallable, Category = "LFPVoxelContainerComponent | Getter")
		FORCEINLINE bool RemoveTickIndex(const int32 TickIndex);

public: /** Delegate */

	UPROPERTY(BlueprintAssignable, Category = "LFPIndexTickManager | Delegate")
		FOnTick OnTick;

private:

	UPROPERTY(SaveGame) TArray<FLFPIndexTickData> TickList;
};