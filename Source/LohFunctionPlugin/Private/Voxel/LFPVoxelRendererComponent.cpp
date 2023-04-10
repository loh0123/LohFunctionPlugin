// Copyright by Loh Zhi Kang


#include "Voxel/LFPVoxelRendererComponent.h"

// Sets default values for this component's properties
ULFPVoxelRendererComponent::ULFPVoxelRendererComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULFPVoxelRendererComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

void ULFPVoxelRendererComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (IsValid(VoxelContainer))
	{
		VoxelContainer->RemoveRenderChuck(RegionIndex, ChuckIndex);
	}
}


// Called every frame
void ULFPVoxelRendererComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool ULFPVoxelRendererComponent::InitializeRenderer(const int32 NewRegionIndex, const int32 NewChuckIndex, ULFPVoxelContainerComponent* NewVoxelContainer)
{
	if (IsValid(NewVoxelContainer) == false) return false;

	if (IsValid(VoxelContainer))
	{
		FLFPVoxelChuckDelegate Delegate;

		Delegate.VoxelChuckUpdateEvent.BindUObject(this, &ULFPVoxelRendererComponent::OnChuckUpdate);

		if (VoxelContainer->AddRenderChuck(NewRegionIndex, NewChuckIndex, Delegate))
		{
			RegionIndex = NewRegionIndex;

			ChuckIndex = NewChuckIndex;

			return true;
		}
	}

	return false;
}

bool ULFPVoxelRendererComponent::ReleaseRenderer()
{
	if (IsValid(VoxelContainer) == false) return false;

	VoxelContainer->RemoveRenderChuck(RegionIndex, ChuckIndex);

	VoxelContainer = nullptr;

	RegionIndex = INDEX_NONE;
	ChuckIndex = INDEX_NONE;

	return true;
}

void ULFPVoxelRendererComponent::OnChuckUpdate(const FLFPChuckUpdateAction& Data)
{
}

