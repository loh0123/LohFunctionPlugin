// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LohFunctionPluginLibrary.h"
#include "LFPInstanceIDComponent.generated.h"

class UInstancedStaticMeshComponent;
class ULFPWorldGrid;

USTRUCT( BlueprintType )
struct FLFPInstanceGridInstanceInfo
{
	GENERATED_BODY()

public:

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "LFPInstanceGridInstanceInfo" )
	FTransform Transform = FTransform();

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "LFPInstanceGridInstanceInfo" )
	bool bIsWorldSpace = true;

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "LFPInstanceGridInstanceInfo" )
	int32 InstanceIndex = 0;

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "LFPInstanceGridInstanceInfo" )
	int32 MeshIndex = 0;
};


USTRUCT( BlueprintType )
struct FLFPInstanceGridMeshData
{
	GENERATED_BODY()

public:

	FLFPInstanceGridMeshData() {}

	FLFPInstanceGridMeshData( UInstancedStaticMeshComponent* ISM ) : ISMComponent( ISM ) {}

protected:

	UPROPERTY( VisibleAnywhere , Category = "LFPInstanceGridMeshData" )
	TObjectPtr<UInstancedStaticMeshComponent> ISMComponent = nullptr;

	TMap<int32 , FPrimitiveInstanceId> InstanceIDList = TMap<int32 , FPrimitiveInstanceId>();

public:

	FORCEINLINE bool IsDataValid() const;

	FORCEINLINE void GetInstanceIndexList( TArray<int32>& ResultList ) const;

	FORCEINLINE FPrimitiveInstanceId FindInstanceIDByIndex( const int32 Item ) const;

	FORCEINLINE FPrimitiveInstanceId AddInstanceAtIndex( const int32 InstanceIndex , const FTransform& InstanceTransform , bool bWorldSpace );

	FORCEINLINE bool RemoveInstanceAtIndex( const int32 InstanceIndex );

	FORCEINLINE bool UpdateInstance( const int32 InstanceIndex , const FTransform& NewInstanceTransform , const bool bWorldSpace = false );

	FORCEINLINE bool SetCustomDataValue( const int32 InstanceIndex , const int32 CustomDataIndex , const float CustomDataValue );

	FORCEINLINE bool SetCustomData( const int32 InstanceIndex , const TArray<float>& InCustomData );
};

UCLASS( ClassGroup = ( LFPlugin ) , meta = ( BlueprintSpawnableComponent ) )
class LOHFUNCTIONPLUGIN_API ULFPInstanceIDComponent : public USceneComponent
{
	GENERATED_BODY()

private:

	UPROPERTY( VisibleAnywhere , Category = "LFPInstanceIDComponent" )
	TArray<FLFPInstanceGridMeshData> MeshList = TArray<FLFPInstanceGridMeshData>();

public:
	// Sets default values for this component's properties
	ULFPInstanceIDComponent();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called when the game end
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

public:
	// Called every frame
	virtual void TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;


public: /* Function For External Blueprint Or C++ To Use */

	UFUNCTION( BlueprintPure , Category = "LFPInstanceIDComponent | Getter" )
	bool IsMeshIndexValid( const int32 MeshIndex ) const;

	UFUNCTION( BlueprintPure , Category = "LFPInstanceIDComponent | Getter" )
	int32 GetMeshIndexByInstance( const int32 InstanceIndex ) const;

	UFUNCTION( BlueprintPure , Category = "LFPInstanceIDComponent | Getter" )
	TArray<int32> GetInstanceIndexListByMesh( const int32 MeshIndex ) const;


	UFUNCTION( BlueprintCallable , Category = "LFPInstanceIDComponent | Initializer" )
	int32 RegisterInstanceStaticMeshComponent( UInstancedStaticMeshComponent* ISM );

	UFUNCTION( BlueprintCallable , Category = "LFPInstanceIDComponent | Initializer" )
	int32 RegisterInstanceStaticMeshComponentList( TArray<UInstancedStaticMeshComponent*> ISMList );

	/** Set Instance Type On This Grid Location (Use -1 To Remove) */
	UFUNCTION( BlueprintCallable , Category = "LFPInstanceIDComponent | Setter" )
	bool SetInstance( const FLFPInstanceGridInstanceInfo& InstanceInfo );

	UFUNCTION( BlueprintCallable , Category = "LFPInstanceIDComponent | Setter" )
	bool SetInstances( const TArray<FLFPInstanceGridInstanceInfo>& InstanceInfoList );

	UFUNCTION( BlueprintCallable , Category = "LFPInstanceIDComponent | Setter" )
	bool SetCustomData( const int32 InstanceIndex , const int32 DataIndex , const float DataValue );

	UFUNCTION( BlueprintCallable , Category = "LFPInstanceIDComponent | Setter" )
	bool SetCustomDatas( const int32 InstanceIndex , const TArray<float>& DataList );
};
