// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LFPChunkedEntityListDataComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN ( LogChunkedEntityListDataComponent , Log , All );

USTRUCT (  )
struct FLFPEntityData
{
	GENERATED_BODY ( )

	FLFPEntityData ( ) = default;

private:

	UPROPERTY ( )
	TArray < uint8 > DataByteList = TArray < uint8 > ( );

public:

	FORCEINLINE void InitializeData ( const int32 ByteSize )
	{
		DataByteList.SetNumZeroed ( ByteSize );
	}

	FORCEINLINE void DeinitializeData ( )
	{
		DataByteList.Empty ( );
	}

public:

	FORCEINLINE bool IsInitialized ( ) const
	{
		return DataByteList.IsEmpty ( ) == false;
	}

	FORCEINLINE bool IsDataIndexValid ( const int32 DataIndex ) const
	{
		return DataByteList.IsValidIndex ( DataIndex );
	}

public:

	FORCEINLINE const TArray < uint8 >& GetData ( ) const
	{
		return DataByteList;
	}

	FORCEINLINE void SetData ( const TArray < uint8 >& NewData )
	{
		DataByteList = NewData;
	}
};

USTRUCT ( )
struct FLFPEntityListRegionData
{
	GENERATED_BODY ( )

private:

	UPROPERTY ( )
	TArray < FLFPEntityData > EntityList = TArray < FLFPEntityData > ( );

public:

	FORCEINLINE bool IsEntityIndexValid ( const int32 EntityIndex ) const
	{
		return EntityList.IsValidIndex ( EntityIndex );
	}

public:

	FORCEINLINE const TArray < FLFPEntityData >& GetDataList ( ) const
	{
		return EntityList;
	}

public:

	FORCEINLINE const FLFPEntityData& GetData ( const int32 EntityIndex ) const
	{
		checkf ( IsEntityIndexValid ( EntityIndex ) ,
		         TEXT(
			         "EntityIndex invalid"
		         ) );

		return EntityList [ EntityIndex ];
	}

	FORCEINLINE FLFPEntityData& GetData ( const int32 EntityIndex )
	{
		checkf ( IsEntityIndexValid ( EntityIndex ) ,
		         TEXT(
			         "EntityIndex invalid"
		         ) );

		return EntityList [ EntityIndex ];
	}

public:

	FORCEINLINE FLFPEntityData& AllocateEntity ( )
	{
		return EntityList.Add_GetRef ( FLFPEntityData ( ) );
	}

	FORCEINLINE void RemoveEntity ( const int32 EntityIndex )
	{
		EntityList.RemoveAt ( EntityIndex );
	}
};

USTRUCT ( BlueprintType )
struct FLFPChunkedEntityListSerializeData
{
	GENERATED_BODY ( )

public:

	UPROPERTY ( )
	TArray < uint8 > DataList = TArray < uint8 > ( );

	UPROPERTY ( )
	FName CompressionName = NAME_Oodle;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams ( FLFPhunkedEntityListata_DataChanged , const int32 , RegionIndex , const int32 , ChunkIndex , const int32 , DataIndex , const TArray<uint8>& , OldData , const TArray<uint8>& , NewData );

UCLASS ( ClassGroup=(Custom) , meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPChunkedEntityListDataComponent : public UActorComponent
{
	GENERATED_BODY ( )

public:

	// Sets default values for this component's properties
	ULFPChunkedEntityListDataComponent ( );

protected:

	// Called when the game starts
	virtual void BeginPlay ( ) override;

public:

	// Called every frame
	virtual void TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;

public:

	UFUNCTION ( BlueprintCallable )
	void SetSize ( const int32& NewRegionSize );

public:

	UFUNCTION ( BlueprintCallable )
	void LoadRegion ( const int32 RegionIndex , const FLFPChunkedEntityListSerializeData& LoadData );

	UFUNCTION ( BlueprintCallable )
	void SaveRegion ( const int32 RegionIndex , FLFPChunkedEntityListSerializeData& SaveData );

public:

	// Faster version of get data ID without check
	FORCEINLINE const TArray < FLFPEntityData >& GetDataList_Checked ( const int32 RegionIndex ) const;

	FORCEINLINE const FLFPEntityData& GetData_Checked ( const int32 RegionIndex , const int32 EntityIndex ) const;

public:

	UFUNCTION ( BlueprintCallable )
	TArray < uint8 > GetData ( const int32 RegionIndex , const int32 EntityIndex ) const;

	UFUNCTION ( BlueprintCallable )
	void SetData ( const int32 RegionIndex , const int32 EntityIndex , const TArray < uint8 >& NewData );

public:

	UFUNCTION ( BlueprintCallable )
	bool IsDataIndexValid ( const int32 RegionIndex , const int32 EntityIndex ) const;

	UFUNCTION ( BlueprintCallable )
	bool IsRegionIndexValid ( const int32 RegionIndex ) const;

public:

	UFUNCTION ( BlueprintPure )
	int32 GetRegionIndexSize ( ) const;

public:

	UPROPERTY ( BlueprintAssignable )
	FLFPhunkedEntityListata_DataChanged OnDataChanged;

private:

	UPROPERTY ( )
	TArray < FLFPEntityListRegionData > RegionDataList = TArray < FLFPEntityListRegionData > ( );

protected:

	UPROPERTY ( EditAnywhere , Category = "Setting|IndexSize" )
	int32 RegionIndexSize = 1;
};
