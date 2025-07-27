// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/LFPGridTagDataComponent.h"

#include "Data/LFPChunkedIndexTranslator.h"

// Sets default values for this component's properties
ULFPGridTagDataComponent::ULFPGridTagDataComponent ( )
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void ULFPGridTagDataComponent::BeginPlay ( )
{
	if ( IsValid ( GridSetting ) )
	{
		DataIndexSize   = GridSetting->GetDataIndexSize ( );
		ChunkIndexSize  = GridSetting->GetChunkIndexSize ( );
		RegionIndexSize = GridSetting->GetRegionIndexSize ( );
	}

	Super::BeginPlay ( );
}

// Called every frame
void ULFPGridTagDataComponent::TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent ( DeltaTime , TickType , ThisTickFunction );

	// ...
}

ULFPChunkedIndexTranslator* ULFPGridTagDataComponent::GetGridSetting ( ) const
{
	return GridSetting;
}
