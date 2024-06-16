#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include <GameplayTagContainer.h>
#include "LFPHashBoxGridComponent.generated.h"

USTRUCT(BlueprintType)
struct FLFHashBoxGridKey
{
	GENERATED_BODY()

public:

	FLFHashBoxGridKey() {}

	FLFHashBoxGridKey(const uint8 NewConnectID, const FGameplayTag& NewObjectTag) : ConnectID(NewConnectID), ObjectTag(NewObjectTag) {}

public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default, meta = (Bitmask))
	uint8 ConnectID = uint8(255);

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Default)
	FGameplayTag ObjectTag = FGameplayTag::EmptyTag;

public:

	FORCEINLINE void SetConnectOccupation(const int32 Index, const bool bNewValue)
	{
		if (Index < 0 || Index > 7)
		{
			return;
		}

		if (bNewValue)
		{
			ConnectID |= 1 << (Index & (NumBitsPerDWORD - 1));
		}
		else
		{
			ConnectID &= ~(1 << (Index & (NumBitsPerDWORD - 1)));
		}
	}

public:

	bool operator==(const FLFHashBoxGridKey& Other) const
	{
		return ConnectID == Other.ConnectID && ObjectTag == Other.ObjectTag;
	}
};

FORCEINLINE uint32 GetTypeHash(const FLFHashBoxGridKey& Thing)
{
	uint32 Hash = FCrc::MemCrc32(&Thing, sizeof(FLFHashBoxGridKey));
	return Hash;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHashBoxGridPointUpdate, const FLFHashBoxGridKey&, HashValue);

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPHashBoxGridComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULFPHashBoxGridComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UFUNCTION(BlueprintCallable, Category = "LFPHashBoxGridComponent | Setter")
	FORCEINLINE void SetGridSize(const FIntVector NewSize);

	UFUNCTION(BlueprintCallable, Category = "LFPHashBoxGridComponent | Setter")
	FORCEINLINE void UpdateGridIndex(const int32 GridIndex);

protected:

	UFUNCTION(BlueprintNativeEvent)
	bool GetGridOccupation(const FIntVector& GridPosition, const FIntVector& LocalPosition, const FGameplayTag& CurrentGridTag) const;
	virtual bool GetGridOccupation_Implementation(const FIntVector& GridPosition, const FIntVector& LocalPosition, const FGameplayTag& CurrentGridTag) const { return false; }

	UFUNCTION(BlueprintNativeEvent)
	FGameplayTag GetGridTag(const FIntVector& GridPosition) const;
	virtual FGameplayTag GetGridTag_Implementation(const FIntVector& GridPosition) const { return FGameplayTag(); }

public: /** Delegate */

	UPROPERTY(BlueprintAssignable, Category = "LFPGridContainerComponent | Delegate")
		FOnHashBoxGridPointUpdate OnHashBoxGridPointUpdate;

protected: // Initialize Data

	UPROPERTY(EditAnywhere, Category = "LFPHashBoxGridComponent | Setting")
		FIntVector GridSize = FIntVector(0);
};
