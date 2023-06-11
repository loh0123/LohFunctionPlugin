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

	if (IsValid(VoxelContainer) == false || IsValid(NetworkSocket) == false || ChuckUpdateQueue.IsEmpty()) return;

	if (bIsServer)
	{
		const auto ChuckPos = *ChuckUpdateQueue.CreateConstIterator();

		FIntPoint ChuckPosTemp(ChuckPos.X, ChuckPos.Y);

		TArray<uint8> ChuckDataList;
		{
			FArchiveSaveCompressedProxy CompressedProxy(ChuckDataList, EName::Oodle, ECompressionFlags::COMPRESS_BiasMemory);

			FNameAsStringProxyArchive ProxyArchive(CompressedProxy);

			ProxyArchive << ChuckPosTemp;

			if (VoxelContainer->GetVoxelChuckDataByArchive(ChuckPos.X, ChuckPos.Y, ProxyArchive) == false)
			{
				UE_LOG(LogTemp, Warning, TEXT("Invalid Chuck Pos : %s"), *ChuckPos.ToString());

				ChuckUpdateQueue.Remove(ChuckPos);

				return;
			}
		}

		/** Insert Array Size */
		{
			int32 ChuckDataSize = ChuckDataList.Num();
			TArray<uint8> RawSizeList;

			RawSizeList.SetNumUninitialized(4);

			FMemory::Memcpy(RawSizeList.GetData(), &ChuckDataSize, 4);

			for (int32 Index = 3; Index >= 0; Index--)
			{
				ChuckDataList.Insert(RawSizeList[Index], 0);
			}
		}

		if (ChuckDataList.IsValidIndex(0))
		{
			if (NetworkSocket->SendData(ChuckDataList, SocketIndex, ChuckPos.Z) == false)
			{
				UE_LOG(LogTemp, Warning, TEXT("Fail To Send Chuck Data : %s"), *ChuckPos.ToString());
			}
		}

		ChuckUpdateQueue.Remove(ChuckPos);
	}
	else
	{
		const auto ChuckPos = *ChuckUpdateQueue.CreateConstIterator();

		int32 DataType = ChuckPos.Z;

		FIntPoint ChuckPosTemp(ChuckPos.X, ChuckPos.Y);

		TArray<uint8> ChuckDataList;
		{
			FMemoryWriter MemoryProxy(ChuckDataList);

			FNameAsStringProxyArchive ProxyArchive(MemoryProxy);

			ProxyArchive << DataType; /** Data Type */

			ProxyArchive << ChuckPosTemp;
		}

		/** Don't need data size because it always the same */

		if (ChuckDataList.IsValidIndex(0))
		{
			if (NetworkSocket->SendData(ChuckDataList, SocketIndex, ChuckPos.Z) == false)
			{
				UE_LOG(LogTemp, Warning, TEXT("Fail To Send Chuck Request Data : %s"), *ChuckPosTemp.ToString());
			}
		}

		ChuckUpdateQueue.Remove(ChuckPos);
	}
}

float ULFPVoxelNetworkProxyComponent::GetDataCompleteness() const
{
	return CurrentDataCompleteness;
}

bool ULFPVoxelNetworkProxyComponent::SetupProxy(ULFPVoxelContainerComponent* InVoxelContainer, ULFPTCPSocketComponent* InNetworkSocket, const FLFPTCPSocketSetting SocketSetting, const bool IsServer)
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

	bIsServer = IsServer;

	SocketIndex = NetworkSocket->CreateSocket(SocketSetting);

	return true;
}

bool ULFPVoxelNetworkProxyComponent::RequestChuckData(const int32 RegionIndex, const int32 ChuckIndex, const int32 ClientID)
{
	if (IsValid(NetworkSocket) == false || NetworkSocket->IsSocketValid(SocketIndex, ClientID) == false || VoxelContainer->IsChuckPositionValid(RegionIndex, ChuckIndex) == false) return false;

	ChuckUpdateQueue.Add(FIntVector(RegionIndex, ChuckIndex, ClientID));

	return true;
}

void ULFPVoxelNetworkProxyComponent::OnChuckUpdate(const int32 RegionIndex, const int32 ChuckIndex, const FLFPVoxelUpdateAction& VoxelUpdateAction)
{
	if (bIsServer)
	{
		RequestChuckData(RegionIndex, ChuckIndex, INDEX_NONE);
	}
	else
	{

	}
}

void ULFPVoxelNetworkProxyComponent::OnNetworkMessage(const int32 SocketID, const int32 ClientID, const TArray<uint8>& Bytes)
{
	if (IsValid(VoxelContainer) == false || Bytes.IsEmpty()) return;

	IncomeDataBuffer.Append(Bytes);

	if (bIsServer)
	{
		if (IncomeDataBuffer.Num() >= 12) return; /** Data Still Not Complete */

		int32 DataType = INDEX_NONE;

		FIntPoint ChuckPosTemp(INDEX_NONE);

		FMemoryReader MemoryProxy(IncomeDataBuffer);

		FNameAsStringProxyArchive ProxyArchive(MemoryProxy);

		ProxyArchive << DataType; /** Data Type */

		switch (DataType)
		{
		case 0: /** Chuck Request */
			{
				ProxyArchive << ChuckPosTemp;

				RequestChuckData(ChuckPosTemp.X, ChuckPosTemp.Y, ClientID);
			}
		break;
		}

		IncomeDataBuffer.Empty();
	}
	else
	{
		if (IncomeDataBuffer.IsValidIndex(3) == false) return; /** Data Still Not Complete For Size */
		
		int32 ChuckDataSize = INDEX_NONE;
		{
			FMemory::Memcpy(&ChuckDataSize, IncomeDataBuffer.GetData(), 4);
		}

		CurrentDataCompleteness = float(IncomeDataBuffer.Num() - 4) / float(ChuckDataSize);

		if (ChuckDataSize != IncomeDataBuffer.Num() - 4) return; /** Data Still Not Complete */

		for (int32 RemoveCount = 0; RemoveCount < 4; RemoveCount++)
		{
			IncomeDataBuffer.RemoveAt(0);
		}

		FIntPoint ChuckPosTemp;

		FArchiveLoadCompressedProxy CompressedProxy(IncomeDataBuffer, EName::Oodle, ECompressionFlags::COMPRESS_BiasMemory);

		FNameAsStringProxyArchive ProxyArchive(CompressedProxy);

		ProxyArchive << ChuckPosTemp;

		VoxelContainer->SetVoxelChuckDataByArchive(ChuckPosTemp.X, ChuckPosTemp.Y, ProxyArchive);

		CurrentDataCompleteness = -1.0f;

		IncomeDataBuffer.Empty();
	}
}

