// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/LFPWorldGrid.h"
#include "LFPInstanceGridComponent.generated.h"


USTRUCT(BlueprintType)
struct FLFPInstanceGridMeshData
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInstanceGridMeshData")
		TObjectPtr<UStaticMesh> Mesh = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInstanceGridMeshData")
		TArray<TObjectPtr<UMaterialInterface>> Material;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInstanceGridMeshData")
		int32 CustomDataAmount = 0;

	UPROPERTY(VisibleAnywhere, Category = "LFPInstanceGridMeshData")
		TArray<int32> InstanceGridIndexList;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPInstanceGridComponent : public ULFPWorldGrid
{
	GENERATED_BODY()

	UPROPERTY() TArray<TObjectPtr<class UInstancedStaticMeshComponent>> ISMList;

public:

	UPROPERTY(VisibleAnywhere, Category = "LFPInstanceGridMeshData")
		TArray<int32> GridInstanceIndexList;

private:

	UPROPERTY(EditAnywhere, Category = "LFPInstanceGridComponent")
		TArray<FLFPInstanceGridMeshData> MeshList;


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

	//UFUNCTION(BlueprintCallable, Category = "LFPInstanceGridComponent | Function")
	//	FORCEINLINE void SetupGrid(const FIntVector GridSize, const FVector GridGap, const ELFPGridType GridType = ELFPGridType::Rectangular);
	//
	//UFUNCTION(BlueprintCallable, Category = "LFPInstanceGridComponent | Function")
	//	FORCEINLINE bool AddInstance(const FIntVector GridLocation, const int32 InstanceIndex);
	//
	//UFUNCTION(BlueprintCallable, Category = "LFPInstanceGridComponent | Function")
	//	FORCEINLINE bool AddInstances(const TArray<FIntVector> GridLocationList, const int32 InstanceIndex);
	//
	//UFUNCTION(BlueprintCallable, Category = "LFPInstanceGridComponent | Function")
	//	FORCEINLINE bool RemoveInstance(const FIntVector GridLocation);
	//
	//UFUNCTION(BlueprintCallable, Category = "LFPInstanceGridComponent | Function")
	//	FORCEINLINE bool RemoveInstances(const TArray<FIntVector> GridLocationList);
};
