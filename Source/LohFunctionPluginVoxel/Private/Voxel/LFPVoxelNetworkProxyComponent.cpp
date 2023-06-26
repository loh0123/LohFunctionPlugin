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
	PrimaryComponentTick.TickInterval = 2.0f;
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
		for (auto& SendInfo : ChuckUpdateQueue)
		{
			int32 SendAmount = SendInfo.Value.ChuckList.Num();

			TArray<uint8> BatchChuckDataList;
			{
				FArchiveSaveCompressedProxy CompressedProxy(BatchChuckDataList, EName::Oodle, ECompressionFlags::COMPRESS_BiasMemory);

				FNameAsStringProxyArchive ProxyArchive(CompressedProxy);

				for (auto& ChuckUpdateInfo : SendInfo.Value.ChuckList)
				{
					ProxyArchive << ChuckUpdateInfo;

					if (VoxelContainer->GetVoxelChuckDataByArchive(ChuckUpdateInfo.X, ChuckUpdateInfo.Y, ProxyArchive) == false)
					{
						UE_LOG(LogTemp, Warning, TEXT("Invalid Chuck Pos : %s / Client ID : %d"), *ChuckUpdateInfo.ToString(), SendInfo.Key);

						SendAmount--;
					}
				}
			}

			/** Data Info */
			TArray<uint8> PackageInfoList;
			{
				FMemoryWriter MemoryProxy(PackageInfoList);

				FNameAsStringProxyArchive ProxyArchive(MemoryProxy);

				int32 DataSize = BatchChuckDataList.Num();

				ProxyArchive << SendAmount;
				ProxyArchive << DataSize;
			}

			if (SendAmount > 0)
			{
				if (NetworkSocket->SendData(PackageInfoList, SocketIndex, SendInfo.Key) == false)
				{
					UE_LOG(LogTemp, Warning, TEXT("Fail To Send Client Data : %d"), SendInfo.Key);

					continue;
				}

				if (NetworkSocket->SendData(BatchChuckDataList, SocketIndex, SendInfo.Key) == false)
				{
					UE_LOG(LogTemp, Warning, TEXT("Fail To Send Client Chuck Data : %d"), SendInfo.Key);

					continue;
				}
			}
		}
	}
	else
	{
		for (auto& SendInfo : ChuckUpdateQueue)
		{
			TArray<uint8> RequestDataList;
			{
				FMemoryWriter MemoryProxy(RequestDataList);

				FNameAsStringProxyArchive ProxyArchive(MemoryProxy);

				TArray<FIntPoint> TempArray = SendInfo.Value.ChuckList.Array();

				ProxyArchive << TempArray;

				UE_LOG(LogTemp, Warning, TEXT("TempArray : %d"), TempArray.Num());
			}

			/** Data Info */
			TArray<uint8> PackageInfoList;
			{
				FMemoryWriter MemoryProxy(PackageInfoList);

				FNameAsStringProxyArchive ProxyArchive(MemoryProxy);

				int32 DataSize = RequestDataList.Num();

				ProxyArchive << DataSize;
			}

			if (NetworkSocket->SendData(PackageInfoList, SocketIndex, SendInfo.Key) == false)
			{
				UE_LOG(LogTemp, Warning, TEXT("Fail To Send Chuck Request Info Data : %d"), RequestDataList.Num());
			}

			if (NetworkSocket->SendData(RequestDataList, SocketIndex, SendInfo.Key) == false)
			{
				UE_LOG(LogTemp, Warning, TEXT("Fail To Send Chuck Request Data : %d"), SendInfo.Value.ChuckList.Num());
			}
		}
	}

	ChuckUpdateQueue.Empty();
}

float ULFPVoxelNetworkProxyComponent::GetDataCompleteness(const int32 ClientID) const
{
	return IncomeDataMap.Contains(ClientID) ? IncomeDataMap.FindChecked(ClientID).GetDataCompleteness() : -1.0f;
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

	if (bIsServer == false && ClientID != INDEX_NONE)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't Ask Chuck Data For Other Than -1 On Client"));

		return false;
	}

	ChuckUpdateQueue.FindOrAdd(ClientID).ChuckList.Add(FIntPoint(RegionIndex, ChuckIndex));

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
	if (IsValid(VoxelContainer) == false || Bytes.IsEmpty() || SocketID != SocketIndex) return;

	FLFPVoxelNetworkProxyReceiveInfo& IncomeData = IncomeDataMap.FindOrAdd(ClientID);

	IncomeData.Data.Append(Bytes);;

	if (bIsServer)
	{
		/** Do we not has package info */
		if (IncomeData.HasDataInfo() == false)
		{
			if (IncomeData.Data.Num() < 4) return; /** Data Still Not Complete */

			FMemoryReader MemoryProxy(IncomeData.Data);

			FNameAsStringProxyArchive ProxyArchive(MemoryProxy);

			//ProxyArchive << IncomeData.DataSendAmount;
			ProxyArchive << IncomeData.DataSize;

			IncomeData.Data.RemoveAt(0, 4, false);
		}

		if (IncomeData.IsDataComplete())
		{
			FMemoryReader MemoryProxy(IncomeData.Data);

			FNameAsStringProxyArchive ProxyArchive(MemoryProxy);

			TArray<FIntPoint> RequestChuckList;

			ProxyArchive << RequestChuckList;

			for (const auto& ChuckPos : RequestChuckList)
			{
				RequestChuckData(ChuckPos.X, ChuckPos.Y, ClientID);
			}

			IncomeData.Data.RemoveAt(0, IncomeData.DataSize, false);

			if (IncomeData.Data.IsEmpty()) IncomeDataMap.Remove(ClientID);
		}
	}
	else
	{
		/** Do we not has package info */
		if (IncomeData.HasDataInfo() == false)
		{
			if (IncomeData.Data.Num() < 8) return; /** Data Still Not Complete */

			FMemoryReader MemoryProxy(IncomeData.Data);

			FNameAsStringProxyArchive ProxyArchive(MemoryProxy);

			ProxyArchive << IncomeData.DataSendAmount;
			ProxyArchive << IncomeData.DataSize;

			IncomeData.Data.RemoveAt(0, 8, false);
		}
		
		if (IncomeData.IsDataComplete())
		{
			FArchiveLoadCompressedProxy MemoryProxy(IncomeData.Data, EName::Oodle, ECompressionFlags::COMPRESS_BiasMemory);

			FNameAsStringProxyArchive ProxyArchive(MemoryProxy);

			for (int32 DataIndex = 0; DataIndex < IncomeData.DataSendAmount; DataIndex++)
			{
				FIntPoint ChuckPosTemp;

				ProxyArchive << ChuckPosTemp;

				VoxelContainer->SetVoxelChuckDataByArchive(ChuckPosTemp.X, ChuckPosTemp.Y, ProxyArchive);
			}

			CurrentDataCompleteness = -1.0f;

			IncomeData.Data.RemoveAt(0, IncomeData.DataSize, false);

			if (IncomeData.Data.IsEmpty()) IncomeDataMap.Remove(ClientID);
		}
	}
}

