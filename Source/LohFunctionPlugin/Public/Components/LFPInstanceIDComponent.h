// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LohFunctionPluginLibrary.h"
#include "LFPInstanceIDComponent.generated.h"

class UInstancedStaticMeshComponent;
class ULFPWorldGrid;

USTRUCT(BlueprintType)
struct FLFPInstanceGridInstanceInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInstanceGridInstanceInfo")
		FTransform Transform = FTransform();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInstanceGridInstanceInfo")
		bool bIsWorldSpace = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInstanceGridInstanceInfo")
		int32 InstanceIndex = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPInstanceGridInstanceInfo")
		int32 MeshIndex = 0;
};


USTRUCT(BlueprintType)
struct FLFPInstanceGridMeshData
{
	GENERATED_BODY()

public:

	FLFPInstanceGridMeshData() {}

	FLFPInstanceGridMeshData(UInstancedStaticMeshComponent* ISM) : ISMComponent(ISM) {}

protected:

	UPROPERTY(VisibleAnywhere, Category = "LFPInstanceGridMeshData")
		TObjectPtr<UInstancedStaticMeshComponent> ISMComponent = nullptr;

		TMap<int32, FPrimitiveInstanceId> InstanceIDList = TMap<int32, FPrimitiveInstanceId>();

public:

	FORCEINLINE bool IsValid() const;

	FORCEINLINE FPrimitiveInstanceId FindInstanceID(const int32 Item) const;

	FORCEINLINE FPrimitiveInstanceId AddInstance(const int32 InstanceIndex, const FTransform& InstanceTransform, bool bWorldSpace);

	FORCEINLINE bool RemoveInstanceAt(const int32 InstanceIndex);

	FORCEINLINE bool UpdateInstance(const int32 InstanceIndex, const FTransform& NewInstanceTransform, const bool bWorldSpace = false, const bool bMarkRenderStateDirty = false);

	FORCEINLINE bool SetCustomDataValue(const int32 InstanceIndex, const int32 CustomDataIndex, const float CustomDataValue, const bool bMarkRenderStateDirty = false);

	FORCEINLINE bool SetCustomData(const int32 InstanceIndex, const TArray<float>& InCustomData, const bool bMarkRenderStateDirty = false);
};

UCLASS( ClassGroup=(LFPlugin), meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPInstanceIDComponent : public USceneComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, Category = "LFPInstanceIDComponent")
		TArray<FLFPInstanceGridMeshData> MeshList = TArray<FLFPInstanceGridMeshData>();

public:	
	// Sets default values for this component's properties
	ULFPInstanceIDComponent();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called when the game end
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
public: /* Function For External Blueprint Or C++ To Use */

	UFUNCTION(BlueprintPure, Category = "LFPInstanceIDComponent | Function")
		FORCEINLINE bool IsMeshIndexValid(const int32 MeshIndex) const;

	UFUNCTION(BlueprintPure, Category = "LFPInstanceIDComponent | Function")
		FORCEINLINE int32 GetInstanceIndexOccupation(const int32 InstanceIndex) const;


	UFUNCTION(BlueprintCallable, Category = "LFPInstanceIDComponent | Function")
		FORCEINLINE int32 RegisterInstanceStaticMeshComponent(UInstancedStaticMeshComponent* ISM);

	UFUNCTION(BlueprintCallable, Category = "LFPInstanceIDComponent | Function")
		FORCEINLINE int32 RegisterInstanceStaticMeshComponentList(TArray<UInstancedStaticMeshComponent*> ISMList);
	
	/** Set Instance Type On This Grid Location (Use -1 To Remove) */
	UFUNCTION(BlueprintCallable, Category = "LFPInstanceIDComponent | Function")
		FORCEINLINE bool SetInstance(const FLFPInstanceGridInstanceInfo& InstanceInfo);
	
	UFUNCTION(BlueprintCallable, Category = "LFPInstanceIDComponent | Function")
		FORCEINLINE bool SetInstances(const TArray<FLFPInstanceGridInstanceInfo>& InstanceInfoList);
	
	UFUNCTION(BlueprintCallable, Category = "LFPInstanceIDComponent | Function")
		FORCEINLINE bool SetCustomData(const int32 InstanceIndex, const int32 DataIndex, const float DataValue, const bool bMarkRenderStateDirty = false);

	UFUNCTION(BlueprintCallable, Category = "LFPInstanceIDComponent | Function")
		FORCEINLINE bool SetCustomDatas(const int32 InstanceIndex, const TArray<float>& DataList, const bool bMarkRenderStateDirty = false);
};
