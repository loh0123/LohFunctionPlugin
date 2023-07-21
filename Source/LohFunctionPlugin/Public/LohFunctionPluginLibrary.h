// Copyright (c) 2022 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "LohFunctionPluginLibrary.generated.h"

USTRUCT(BlueprintType)
struct FLFPCompactIntArray
{
	GENERATED_BODY()

	FLFPCompactIntArray() {}

	FLFPCompactIntArray(const uint32 NewIndexSize) : IndexSize(NewIndexSize) {}

private:

	UPROPERTY(SaveGame)
		TArray<uint32> IndexList = TArray<uint32>();

	UPROPERTY(SaveGame)
		uint32 EncodeBtye = 0;

	UPROPERTY(SaveGame)
		uint32 IndexSize = 0;

	UPROPERTY(SaveGame)
		uint32 MaxSize = 0;

private:

	/** Read / Write Bit Function */

	FORCEINLINE FBitReference GetIndexRef(TArray<uint32>& GridIndexListRef, const int32 Index)
	{
		return FBitReference(
			GridIndexListRef.GetData()[Index / NumBitsPerDWORD],
			1 << (Index & (NumBitsPerDWORD - 1))
		);
	}

	FORCEINLINE FConstBitReference GetIndexConstRef(const TArray<uint32>& GridIndexListRef, const int32 Index) const
	{
		return FConstBitReference(
			GridIndexListRef.GetData()[Index / NumBitsPerDWORD],
			1 << (Index & (NumBitsPerDWORD - 1))
		);
	}

	FORCEINLINE void ResizeBitArray(const uint32 NewSize)
	{
		if (NewSize == EncodeBtye) return;

		const TArray<uint32> OldGridIndexList = IndexList;

		const uint32 OldSize = EncodeBtye;

		EncodeBtye = NewSize;

		const int32 ChuckBitSize = FMath::DivideAndRoundUp(IndexSize, uint32(32));

		IndexList.Init(0, (NewSize * ChuckBitSize) + 1);

		if (OldSize == 0) return;

		for (uint32 GridIndex = 0; GridIndex < IndexSize; GridIndex++)
		{
			for (uint32 EncodeIndex = 0; EncodeIndex < OldSize; EncodeIndex++)
			{
				const int32 OldBitIndex = int32((GridIndex * OldSize) + EncodeIndex);
				const int32 NewBitIndex = int32((GridIndex * EncodeBtye) + EncodeIndex);

				GetIndexRef(IndexList, NewBitIndex) = GetIndexConstRef(OldGridIndexList, OldBitIndex);
			}
		}
	}

public:

	FORCEINLINE bool IsValidIndex(const int32 Index) const
	{
		return Index >= 0 && Index < int32(IndexSize);
	}

	/** Resize Function */

	FORCEINLINE void Resize(const int32 NewMaxSize)
	{
		if (MaxSize == NewMaxSize) return;

		for (uint8 NewEncodeSize = 0; NewEncodeSize < NumBitsPerDWORD; NewEncodeSize++)
		{
			if (NewMaxSize < 1 << NewEncodeSize)
			{
				ResizeBitArray(NewEncodeSize);

				break;
			}
		}

		return;
	}

	/** Read / Write Function */

	FORCEINLINE void SetIndexNumber(const int32 Index, const uint32 Number)
	{
		check(Index >= 0 && Index < int32(IndexSize) && EncodeBtye > 0);

		for (uint32 EncodeIndex = 0; EncodeIndex < EncodeBtye; EncodeIndex++)
		{
			const int32 BitIndex = (Index * EncodeBtye) + EncodeIndex;

			GetIndexRef(IndexList, BitIndex) = FConstBitReference(Number, 1 << EncodeIndex);
		}
	}

	FORCEINLINE uint32 GetIndexNumber(const int32 Index) const
	{
		check(Index >= 0 && Index < int32(IndexSize) && EncodeBtye > 0);

		uint32 OutIndex = 0;

		for (uint32 EncodeIndex = 0; EncodeIndex < EncodeBtye; EncodeIndex++)
		{
			const int32 BitIndex = (Index * EncodeBtye) + EncodeIndex;

			FBitReference(OutIndex, 1 << EncodeIndex) = GetIndexConstRef(IndexList, BitIndex);
		}

		return OutIndex;
	}

	/** Debug Function */

	FORCEINLINE uint32 GetEncodeLength() const
	{
		return EncodeBtye;
	}

	FORCEINLINE uint32 GetIndexSize() const
	{
		return IndexSize;
	}

	FORCEINLINE uint32 GetMaxSize() const
	{
		return MaxSize;
	}

public:

	friend FArchive& operator<<(FArchive& Ar, FLFPCompactIntArray& Data)
	{
		return Ar << Data.IndexList << Data.EncodeBtye << Data.IndexSize;
	}

};

USTRUCT(BlueprintType)
struct FLFPFunctionData
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPFunctionData")
		TObjectPtr<UObject> Caller = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPFunctionData")
		FString NameAndParam = FString("");
};

UCLASS()
class LOHFUNCTIONPLUGIN_API ULohFunctionPluginLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginTesting")
		static bool CallFunctionByFunctionData(const FLFPFunctionData& FunctionData, const bool bForce = true);
};
