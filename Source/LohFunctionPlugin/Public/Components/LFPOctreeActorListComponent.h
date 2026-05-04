// Copyright by LOH ZHI KANG

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "LFPOctreeActorListComponent.generated.h"

using FLFPOctreeActorOctreeIDSharedRef = TSharedRef < struct FLFPOctreeActorOctreeID , ESPMode::ThreadSafe >;

struct FLFPOctreeActorOctreeID : public TSharedFromThis < FLFPOctreeActorOctreeID , ESPMode::ThreadSafe >
{
	FOctreeElementId2 ID;
};

struct FLFPOctreeActorElement
{
	FLFPOctreeActorElement ( ) = default;

	explicit FLFPOctreeActorElement ( AActor* InValue , const FBoxCenterAndExtent& InBounds , const FLFPOctreeActorOctreeIDSharedRef& InID ) : ID ( InID )
	                                                                                                                                           , Value ( InValue )
	                                                                                                                                           , Bounds ( InBounds )
	{
	}

	FLFPOctreeActorOctreeIDSharedRef ID     = FLFPOctreeActorOctreeIDSharedRef ( );
	TWeakObjectPtr < AActor >        Value  = nullptr;
	FBoxCenterAndExtent              Bounds = { };
};

struct FLFPOctreeActorSemantics
{
	enum { MaxElementsPerLeaf = 16 };

	enum { MinInclusiveElementsPerNode = 7 };

	enum { MaxNodeDepth = 12 };

	using ElementAllocator = TInlineAllocator < MaxElementsPerLeaf >;

	inline static const FBoxCenterAndExtent& GetBoundingBox ( const FLFPOctreeActorElement& Element )
	{
		return Element.Bounds;
	}

	inline static bool AreElementsEqual ( const FLFPOctreeActorElement& A , const FLFPOctreeActorElement& B )
	{
		return A.Value == B.Value;
	}

	static void SetElementId ( const FLFPOctreeActorElement& Element , FOctreeElementId2 OctreeElementID )
	{
		Element.ID.Get ( ).ID = OctreeElementID;
	}
};

struct FLFPOctreeActorOctree : TOctree2 < FLFPOctreeActorElement , FLFPOctreeActorSemantics >
{
public:

	FLFPOctreeActorOctree ( );
	FLFPOctreeActorOctree ( const FVector& Origin , FVector::FReal Radius );
	virtual ~FLFPOctreeActorOctree ( );

	/** Add new node and initialize using SmartObject runtime data */
	void AddNode ( const FBoxCenterAndExtent& Bounds , AActor* Actor , const FLFPOctreeActorOctreeIDSharedRef& ID );

	/** Updates element bounds remove/add operation */
	void UpdateNode ( const FOctreeElementId2& Id , const FBox& NewBounds );

	/** Remove node */
	void RemoveNode ( const FOctreeElementId2& Id );
};

USTRUCT ( BlueprintType )
struct FLFPOctreeActorOctreeHandle
{
	GENERATED_BODY ( )

	FLFPOctreeActorOctreeHandle ( ) : SharedOctreeID ( MakeShareable ( new FLFPOctreeActorOctreeID ( ) ) )
	{
	}

	FLFPOctreeActorOctreeIDSharedRef SharedOctreeID;
};

UCLASS ( ClassGroup=(Custom) , meta=(BlueprintSpawnableComponent) )
class LOHFUNCTIONPLUGIN_API ULFPOctreeActorListComponent : public UBoxComponent
{
	GENERATED_BODY ( )

public:

	// Sets default values for this component's properties
	ULFPOctreeActorListComponent ( );

protected:

	// Called when the game starts
	virtual void BeginPlay ( ) override;

public:

	// Called every frame
	virtual void TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;

protected:

	UFUNCTION ( BlueprintCallable , Category=Default )
	void AddActor ( AActor* Actor , const FBox& OctreeBounds , const FLFPOctreeActorOctreeHandle& ID );

	UFUNCTION ( BlueprintCallable , Category=Default )
	void RemoveActor ( const FLFPOctreeActorOctreeHandle& Handle );

	UFUNCTION ( BlueprintCallable , Category=Default )
	void FindActor ( const FBox& QueryBox , TArray < AActor* >& OutResults ) const;

	//UFUNCTION ( BlueprintCallable , Category=Default )
	void UpdateOctreeBounds ( );

private:

	FLFPOctreeActorOctree ActorOctree;
};
