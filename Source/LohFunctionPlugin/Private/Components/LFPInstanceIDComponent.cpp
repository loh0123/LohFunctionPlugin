// Copyright by Loh Zhi Kang


#include "Components/LFPInstanceIDComponent.h"
#include "Components/LFPWorldGrid.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Math/LFPGridLibrary.h"


bool FLFPInstanceGridMeshData::IsDataValid() const
{
	return IsValid( ISMComponent.Get() );
}

void FLFPInstanceGridMeshData::GetInstanceIndexList( TArray<int32>& ResultList ) const
{
	InstanceIDList.GetKeys( ResultList );
}

FPrimitiveInstanceId FLFPInstanceGridMeshData::FindInstanceIDByIndex( const int32 Item ) const
{
	const auto ID = InstanceIDList.Find( Item );

	return ID == nullptr ? FPrimitiveInstanceId() : *ID;
}

FPrimitiveInstanceId FLFPInstanceGridMeshData::AddInstanceAtIndex( const int32 InstanceIndex , const FTransform& InstanceTransform , bool bWorldSpace )
{
	return InstanceIDList.Add( InstanceIndex , ISMComponent->AddInstanceById( InstanceTransform , bWorldSpace ) );
}

bool FLFPInstanceGridMeshData::RemoveInstanceAtIndex( const int32 InstanceIndex )
{
	const auto TargetID = FindInstanceIDByIndex( InstanceIndex );

	if ( TargetID.IsValid() == false )
	{
		return false;
	}

	InstanceIDList.Remove( InstanceIndex );

	ISMComponent->RemoveInstanceById( TargetID );

	return true;
}

bool FLFPInstanceGridMeshData::UpdateInstance( const int32 InstanceIndex , const FTransform& NewInstanceTransform , const bool bWorldSpace )
{
	const auto TargetID = FindInstanceIDByIndex( InstanceIndex );

	if ( TargetID.IsValid() == false )
	{
		return false;
	}

	ISMComponent->UpdateInstanceTransformById( TargetID , NewInstanceTransform , bWorldSpace );

	return true;
}

bool FLFPInstanceGridMeshData::SetCustomDataValue( const int32 InstanceIndex , const int32 CustomDataIndex , const float CustomDataValue )
{
	const auto TargetID = FindInstanceIDByIndex( InstanceIndex );

	if ( TargetID.IsValid() == false )
	{
		return false;
	}

	ISMComponent->SetCustomDataValueById( TargetID , CustomDataIndex , CustomDataValue );

	return true;
}

bool FLFPInstanceGridMeshData::SetCustomData( const int32 InstanceIndex , const TArray<float>& InCustomData )
{
	const auto TargetID = FindInstanceIDByIndex( InstanceIndex );

	if ( TargetID.IsValid() == false )
	{
		return false;
	}

	ISMComponent->SetCustomDataById( TargetID , InCustomData );

	return true;
}

// Sets default values for this component's properties
ULFPInstanceIDComponent::ULFPInstanceIDComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void ULFPInstanceIDComponent::BeginPlay()
{
	Super::BeginPlay();

	for ( int32 Index = 0; Index < GetNumChildrenComponents(); Index++ )
	{
		RegisterInstanceStaticMeshComponent( Cast<UInstancedStaticMeshComponent>( GetChildComponent( Index ) ) );
	}
}

void ULFPInstanceIDComponent::EndPlay( const EEndPlayReason::Type EndPlayReason )
{
	Super::EndPlay( EndPlayReason );
}


// Called every frame
void ULFPInstanceIDComponent::TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime , TickType , ThisTickFunction );

	// ...
}

bool ULFPInstanceIDComponent::IsMeshIndexValid( const int32 MeshIndex ) const
{
	return MeshList.IsValidIndex( MeshIndex ) && MeshList[ MeshIndex ].IsDataValid();
}

int32 ULFPInstanceIDComponent::GetMeshIndexByInstance( const int32 InstanceIndex ) const
{
	for ( int32 MeshIndex = 0; MeshIndex < MeshList.Num(); MeshIndex++ )
	{
		const auto& MeshData = MeshList[ MeshIndex ];

		if ( MeshData.IsDataValid() && MeshData.FindInstanceIDByIndex( InstanceIndex ).IsValid() )
		{
			return MeshIndex;
		}
	}

	return INDEX_NONE;
}

TArray<int32> ULFPInstanceIDComponent::GetInstanceIndexListByMesh( const int32 MeshIndex ) const
{
	TArray<int32> ResultList;

	if ( IsMeshIndexValid( MeshIndex ) == false )
	{
		return ResultList;
	}

	MeshList[ MeshIndex ].GetInstanceIndexList( ResultList );

	return ResultList;
}

int32 ULFPInstanceIDComponent::RegisterInstanceStaticMeshComponent( UInstancedStaticMeshComponent* ISM )
{
	if ( IsValid( ISM ) == false )
	{
		return INDEX_NONE;
	}

	return MeshList.Add( FLFPInstanceGridMeshData( ISM ) );
}

int32 ULFPInstanceIDComponent::RegisterInstanceStaticMeshComponentList( TArray<UInstancedStaticMeshComponent*> ISMList )
{
	int32 Count = 0;

	for ( UInstancedStaticMeshComponent* ISM : ISMList )
	{
		if ( IsValid( ISM ) )
		{
			MeshList.Add( FLFPInstanceGridMeshData( ISM ) );

			Count++;
		}
	}

	return Count;
}

bool ULFPInstanceIDComponent::SetInstance( const FLFPInstanceGridInstanceInfo& InstanceInfo )
{
	if ( IsMeshIndexValid( InstanceInfo.MeshIndex ) == false )
	{
		return false;
	}

	const int32 OccupationID = GetMeshIndexByInstance( InstanceInfo.InstanceIndex );

	/* Find The Prev Data Is Valid And Remove Or Update It */
	if ( OccupationID != INDEX_NONE )
	{
		FLFPInstanceGridMeshData& ISMData = MeshList[ OccupationID ];

		/* Same Instance So Just Update Transform */
		if ( OccupationID == InstanceInfo.MeshIndex )
		{
			ISMData.UpdateInstance( InstanceInfo.InstanceIndex , InstanceInfo.Transform , InstanceInfo.bIsWorldSpace );

			return true;
		}

		/* Remove Operation */
		else
		{
			ISMData.RemoveInstanceAtIndex( InstanceInfo.InstanceIndex );
		}
	}

	/* Add Operation */
	MeshList[ InstanceInfo.MeshIndex ].AddInstanceAtIndex( InstanceInfo.InstanceIndex , InstanceInfo.Transform , InstanceInfo.bIsWorldSpace );

	return true;
}

bool ULFPInstanceIDComponent::SetInstances( const TArray<FLFPInstanceGridInstanceInfo>& InstanceInfoList )
{
	bool bResult = true;

	for ( const FLFPInstanceGridInstanceInfo& Info : InstanceInfoList )
	{
		if ( SetInstance( Info ) == false )
		{
			bResult = false;
		}
	}

	return bResult;
}

bool ULFPInstanceIDComponent::SetCustomData( const int32 InstanceIndex , const int32 DataIndex , const float DataValue )
{
	const int32 MeshIndex = GetMeshIndexByInstance( InstanceIndex );

	if ( IsMeshIndexValid( MeshIndex ) == false )
	{
		return false;
	}

	return MeshList[ MeshIndex ].SetCustomDataValue( InstanceIndex , DataIndex , DataValue );
}

bool ULFPInstanceIDComponent::SetCustomDatas( const int32 InstanceIndex , const TArray<float>& DataList )
{
	const int32 MeshIndex = GetMeshIndexByInstance( InstanceIndex );

	if ( IsMeshIndexValid( MeshIndex ) == false )
	{
		return false;
	}

	return MeshList[ MeshIndex ].SetCustomData( InstanceIndex , DataList );
}