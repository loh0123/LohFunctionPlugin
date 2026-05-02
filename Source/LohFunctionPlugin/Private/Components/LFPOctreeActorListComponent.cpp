// Copyright by LOH ZHI KANG


#include "Components/LFPOctreeActorListComponent.h"


FLFPOctreeActorOctree::FLFPOctreeActorOctree ( )
{
}

FLFPOctreeActorOctree::FLFPOctreeActorOctree ( const FVector& Origin , FVector::FReal Radius ) : TOctree2 < FLFPOctreeActorElement , FLFPOctreeActorSemantics > ( Origin , Radius )
{
}

FLFPOctreeActorOctree::~FLFPOctreeActorOctree ( )
{
}

void FLFPOctreeActorOctree::AddNode ( const FBoxCenterAndExtent& Bounds , AActor* Actor , const FLFPOctreeActorOctreeIDSharedRef& ID )
{
	AddElement ( FLFPOctreeActorElement ( Actor , Bounds , ID ) );
}

void FLFPOctreeActorOctree::UpdateNode ( const FOctreeElementId2& Id , const FBox& NewBounds )
{
	FLFPOctreeActorElement ElementCopy = GetElementById ( Id );
	RemoveElement ( Id );
	ElementCopy.Bounds = NewBounds;
	AddElement ( ElementCopy );
}

void FLFPOctreeActorOctree::RemoveNode ( const FOctreeElementId2& Id )
{
	RemoveElement ( Id );
}

// Sets default values for this component's properties
ULFPOctreeActorListComponent::ULFPOctreeActorListComponent ( )
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void ULFPOctreeActorListComponent::BeginPlay ( )
{
	Super::BeginPlay ( );

	UpdateOctreeBounds ( );
}


// Called every frame
void ULFPOctreeActorListComponent::TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent ( DeltaTime , TickType , ThisTickFunction );

	// ...
}

void ULFPOctreeActorListComponent::Add ( AActor* Actor , const FBox& OctreeBounds , const FLFPOctreeActorOctreeHandle& OutHandle )
{
	ActorOctree.AddNode ( OctreeBounds , Actor , OutHandle.SharedOctreeID );
}

void ULFPOctreeActorListComponent::Remove ( const FLFPOctreeActorOctreeHandle& Handle )
{
	ActorOctree.RemoveNode ( Handle.SharedOctreeID.Get ( ).ID );
}

void ULFPOctreeActorListComponent::Find ( const FBox& QueryBox , TArray < AActor* >& OutResults ) const
{
	ActorOctree.FindElementsWithBoundsTest ( QueryBox ,
	                                         [&OutResults] ( const FLFPOctreeActorElement& Element )
	                                         {
		                                         if ( Element.Value.IsValid ( ) )
		                                         {
			                                         OutResults.Add ( Element.Value.Get ( ) );
		                                         }
	                                         } );
}

void ULFPOctreeActorListComponent::UpdateOctreeBounds ( )
{
	ActorOctree = FLFPOctreeActorOctree ( GetComponentLocation ( ) , Bounds.BoxExtent.Size ( ) );
}
