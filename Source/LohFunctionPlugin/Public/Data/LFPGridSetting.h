// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LFPGridSetting.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class LOHFUNCTIONPLUGIN_API ULFPGridFragmentSettingBase : public UObject
{
	GENERATED_BODY()
};

/**
 * 
 */
UCLASS(Blueprintable)
class LOHFUNCTIONPLUGIN_API ULFPGridSetting : public UDataAsset
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting|GridSize")
	FIntVector DataGridSize = FIntVector(1);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting|GridSize")
	FIntVector ChunkGridSize = FIntVector(1);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setting|GridSize")
	FIntVector RegionGridSize = FIntVector(1);

protected:

	UPROPERTY(EditAnywhere, Instanced, Category = "Setting|GridFragment")
	TSet< TObjectPtr< ULFPGridFragmentSettingBase > > GridFragmentList = TSet< TObjectPtr< ULFPGridFragmentSettingBase > >();

public:

	UFUNCTION(BlueprintPure, Category = "Setting|GridFragment", meta = (AutoCreateRefTerm = "ClassType"))
	ULFPGridFragmentSettingBase* GetGridFragment( const TSubclassOf< ULFPGridFragmentSettingBase >& ClassType ) const;

public:

	template < class FragmentClass >
	FORCEINLINE FragmentClass* FindGridFragmentByClass( ) const;

public:

	FORCEINLINE const FIntVector& GetDataGridSize( ) const { return DataGridSize; }

	FORCEINLINE const FIntVector& GetChunkGridSize( ) const { return ChunkGridSize; }

	FORCEINLINE const FIntVector& GetRegionGridSize( ) const { return RegionGridSize; }

public:

	FORCEINLINE int32 GetDataIndexSize( ) const { return DataGridSize.X * DataGridSize.Y * DataGridSize.Z; }

	FORCEINLINE int32 GetChunkIndexSize( ) const { return ChunkGridSize.X * ChunkGridSize.Y * ChunkGridSize.Z; }

	FORCEINLINE int32 GetRegionIndexSize( ) const { return RegionGridSize.X * RegionGridSize.Y * RegionGridSize.Z; }
};

template < class FragmentClass >
FragmentClass* ULFPGridSetting::FindGridFragmentByClass( ) const
{
	for ( const TObjectPtr< ULFPGridFragmentSettingBase >& Fragment : GridFragmentList )
	{
		if ( IsValid(Fragment) && Fragment->IsA(FragmentClass::StaticClass()) )
		{
			return Cast< FragmentClass >(Fragment);
		}
	}

	return nullptr;
}
