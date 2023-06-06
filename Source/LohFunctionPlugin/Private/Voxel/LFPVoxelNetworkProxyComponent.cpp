// Copyright by Loh Zhi Kang


#include "Voxel/LFPVoxelNetworkProxyComponent.h"
#include "Voxel/LFPVoxelContainerComponent.h"
#include "Serialization/ArchiveProxy.h"
#include "Serialization/NameAsStringProxyArchive.h"
#include "Serialization/ArchiveSaveCompressedProxy.h"
#include "Serialization/ArchiveLoadCompressedProxy.h"
#include "Components/LFPTCPSocketComponent.h"

// Sets default values for this component's properties
ULFPVoxelNetworkProxyComponent::ULFPVoxelNetworkProxyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.2f;
	// ...
}


// Called when the game starts
void ULFPVoxelNetworkProxyComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULFPVoxelNetworkProxyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsServer)
	{
		if (IsValid(VoxelContainer) && IsValid(NetworkSocket) && ChuckUpdateQueue.IsEmpty() == false)
		{
			const auto& ChuckPos = ChuckUpdateQueue.CreateConstIterator();

			FIntVector ChuckPosTemp(ChuckPos->X, ChuckPos->Y, ChuckPos->Z);

			TArray<uint8> ChuckDataList;
			{
				FArchiveSaveCompressedProxy CompressedProxy(ChuckDataList, EName::Oodle, ECompressionFlags::COMPRESS_BiasMemory);

				FNameAsStringProxyArchive ProxyArchive(CompressedProxy);

				ProxyArchive << ChuckPosTemp;

				VoxelContainer->GetVoxelChuckDataByArchive(ChuckPos->X, ChuckPos->Y, ProxyArchive);
			}

			/** Insert Array Size */
			{
				int32 ChuckDataSize = ChuckDataList.Num();
				TArray<uint8> RawSizeList;

				RawSizeList.SetNumUninitialized(4);

				FMemory::Memcpy(RawSizeList.GetData(), &ChuckDataSize, 4);

				for (const uint8 RawData : RawSizeList)
				{
					ChuckDataList.Insert(RawData, 0);
				}
			}

			if (ChuckDataList.IsValidIndex(0))
			{
				NetworkSocket->SendData(ChuckDataList, SocketIndex, ChuckPosTemp.Z);
			}
		}
	}
	else
	{

	}
}

bool ULFPVoxelNetworkProxyComponent::SetupProxy(ULFPVoxelContainerComponent* InVoxelContainer, ULFPTCPSocketComponent* InNetworkSocket, const FLFPTCPSocketSetting SocketSetting, const bool InbIsServer)
{
	if (IsValid(InVoxelContainer) == false || IsValid(InNetworkSocket) == false) return false;

	if (IsValid(VoxelContainer))
	{
		VoxelContainer->OnVoxelContainerChuckUpdate.RemoveAll(this);
	}

	if (IsValid(NetworkSocket))
	{
		NetworkSocket->OnDataReceived.RemoveAll(this);
		NetworkSocket->DestroySocket(SocketIndex);
	}

	VoxelContainer = InVoxelContainer;
	NetworkSocket = InNetworkSocket;

	VoxelContainer->OnVoxelContainerChuckUpdate.AddDynamic(this, &ULFPVoxelNetworkProxyComponent::OnChuckUpdate);
	NetworkSocket->OnDataReceived.AddDynamic(this, &ULFPVoxelNetworkProxyComponent::OnNetworkMessage);

	bIsServer = InbIsServer;

	SocketIndex = NetworkSocket->CreateSocket(SocketSetting);

	return true;
}

void ULFPVoxelNetworkProxyComponent::OnChuckUpdate(const int32 RegionIndex, const int32 ChuckIndex, const FLFPVoxelUpdateAction& VoxelUpdateAction)
{
	if (bIsServer)
	{
		ChuckUpdateQueue.Add(FIntVector(RegionIndex, ChuckIndex, INDEX_NONE));
	}
	else
	{

	}
}

void ULFPVoxelNetworkProxyComponent::OnNetworkMessage(const int32 SocketID, const int32 ClientID, const TArray<uint8>& Bytes)
{
	if (bIsServer)
	{

	}
	else
	{
		
	}
}

