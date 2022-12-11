// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/LFPWorldGrid.h"
#include "LFPInstanceGridComponent.generated.h"

USTRUCT(BlueprintType)
struct FLFPInstanceGridInstanceInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInstanceGridInstanceInfo")
		FIntVector Location = FIntVector(0);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInstanceGridInstanceInfo")
		FRotator Rotation = FRotator(0);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInstanceGridInstanceInfo")
		int32 InstanceIndex = 0;
};


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

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPInstanceGridMeshData")
		TObjectPtr<class UInstancedStaticMeshComponent> ISMComponent;

	UPROPERTY(VisibleAnywhere, Category = "LFPInstanceGridMeshData")
		TArray<int32> InstanceGridIndexList;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPInstanceGridComponent : public ULFPWorldGrid
{
	GENERATED_BODY()

	//UPROPERTY() TArray<TObjectPtr<class UInstancedStaticMeshComponent>> ISMList;

public:

	UPROPERTY(VisibleAnywhere, Category = "LFPInstanceGridMeshData")
		TArray<uint8> GridInstanceIndexList;

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

	UFUNCTION(BlueprintCallable, Category = "LFPInstanceGridComponent | Function")
		FORCEINLINE void SetupGrid(const FIntVector NewGridSize, const FVector NewGridGap, const ELFPGridType NewGridType = ELFPGridType::Rectangular);
	
	/** Set Instance Type On This Grid Location (Use -1 To Remove) */
	UFUNCTION(BlueprintCallable, Category = "LFPInstanceGridComponent | Function")
		FORCEINLINE bool SetInstance(const FLFPInstanceGridInstanceInfo& InstanceInfo);
	
	UFUNCTION(BlueprintCallable, Category = "LFPInstanceGridComponent | Function")
		FORCEINLINE bool SetInstances(const TArray<FLFPInstanceGridInstanceInfo>& InstanceInfoList);
	
	//UFUNCTION(BlueprintCallable, Category = "LFPInstanceGridComponent | Function")
	//	FORCEINLINE bool RemoveInstance(const FIntVector GridLocation);
	//
	//UFUNCTION(BlueprintCallable, Category = "LFPInstanceGridComponent | Function")
	//	FORCEINLINE bool RemoveInstances(const TArray<FIntVector> GridLocationList);
};
