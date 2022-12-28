// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LFPInstanceGridComponent.generated.h"

class UInstancedStaticMeshComponent;
class ULFPWorldGrid;

USTRUCT(BlueprintType)
struct FLFPInstanceGridInstanceInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInstanceGridInstanceInfo")
		FIntVector Location = FIntVector(0);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInstanceGridInstanceInfo")
		FVector LocationOffset = FVector(0);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInstanceGridInstanceInfo")
		FRotator RotationOffset = FRotator(0);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInstanceGridInstanceInfo")
		FVector Scale = FVector(1);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInstanceGridInstanceInfo")
		bool bIsWorld = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInstanceGridInstanceInfo")
		int32 InstanceIndex = 0;
};


USTRUCT(BlueprintType)
struct FLFPInstanceGridMeshData
{
	GENERATED_USTRUCT_BODY()

	FLFPInstanceGridMeshData() {}

	FLFPInstanceGridMeshData(UInstancedStaticMeshComponent* ISM) : ISMComponent(ISM) {}

public:

	UPROPERTY(VisibleAnywhere, SaveGame, Category = "LFPInstanceGridMeshData")
		TObjectPtr<UInstancedStaticMeshComponent> ISMComponent;

	UPROPERTY(VisibleAnywhere, SaveGame, Category = "LFPInstanceGridMeshData")
		TArray<int32> InstanceGridIndexList;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPInstanceGridComponent : public USceneComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, SaveGame, Category = "LFPInstanceGridComponent")
		TArray<uint8> GridInstanceIndexList = TArray<uint8>();

	UPROPERTY(VisibleAnywhere, SaveGame, Category = "LFPInstanceGridComponent")
		TArray<FLFPInstanceGridMeshData> MeshList = TArray<FLFPInstanceGridMeshData>();

	UPROPERTY(VisibleAnywhere, Category = "LFPInstanceGridComponent")
		TObjectPtr<ULFPWorldGrid> WorldGrid = nullptr;


public:	
	// Sets default values for this component's properties
	ULFPInstanceGridComponent();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called when the game end
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
public: /* Function For External Blueprint Or C++ To Use */

	UFUNCTION(BlueprintPure, Category = "LFPInstanceGridComponent | Function")
		FORCEINLINE bool IsMeshIndexValid(const int32 Index) const;


	UFUNCTION(BlueprintCallable, Category = "LFPInstanceGridComponent | Function")
		FORCEINLINE void SetupGrid(ULFPWorldGrid* NewWorldGrid);

	UFUNCTION(BlueprintCallable, Category = "LFPInstanceGridComponent | Function")
		FORCEINLINE int32 RegisterInstanceStaticMeshComponent(UInstancedStaticMeshComponent* ISM);

	UFUNCTION(BlueprintCallable, Category = "LFPInstanceGridComponent | Function")
		FORCEINLINE int32 RegisterInstanceStaticMeshComponentList(TArray<UInstancedStaticMeshComponent*> ISMList);
	
	/** Set Instance Type On This Grid Location (Use -1 To Remove) */
	UFUNCTION(BlueprintCallable, Category = "LFPInstanceGridComponent | Function")
		FORCEINLINE bool SetInstance(const FLFPInstanceGridInstanceInfo& InstanceInfo);
	
	UFUNCTION(BlueprintCallable, Category = "LFPInstanceGridComponent | Function")
		FORCEINLINE bool SetInstances(const TArray<FLFPInstanceGridInstanceInfo>& InstanceInfoList);
	
	UFUNCTION(BlueprintCallable, Category = "LFPInstanceGridComponent | Function")
		FORCEINLINE bool SetCustomData(const FIntVector Location, const int32 DataIndex, const float DataValue, const bool bMarkRenderStateDirty = false);

	UFUNCTION(BlueprintCallable, Category = "LFPInstanceGridComponent | Function")
		FORCEINLINE bool SetCustomDatas(const FIntVector Location, const TArray<float>& DataList, const bool bMarkRenderStateDirty = false);
};
