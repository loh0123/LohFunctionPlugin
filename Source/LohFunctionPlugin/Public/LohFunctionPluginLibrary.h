// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "GameplayTagContainer.h"
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

		IndexList.Init(0, (NewSize * ChuckBitSize));

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

		for (uint8 NewEncodeSize = 1; NewEncodeSize < NumBitsPerDWORD; NewEncodeSize++)
		{
			if (NewMaxSize <= (1 << NewEncodeSize) - 1)
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
		checkf(Index >= 0 && Index < int32(IndexSize) && EncodeBtye > 0, TEXT("Index : %d, EncodeBtye : %u"), Index, EncodeBtye);

		for (uint32 EncodeIndex = 0; EncodeIndex < EncodeBtye; EncodeIndex++)
		{
			const int32 BitIndex = (Index * EncodeBtye) + EncodeIndex;

			GetIndexRef(IndexList, BitIndex) = FConstBitReference(Number, 1 << EncodeIndex);
		}
	}

	FORCEINLINE uint32 GetIndexNumber(const int32 Index) const
	{
		checkf(Index >= 0 && Index < int32(IndexSize) && EncodeBtye > 0, TEXT("Index : %d, EncodeBtye : %u"), Index, EncodeBtye);

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
struct FLFPCompactIntNameArray : public FLFPCompactIntArray
{
	GENERATED_USTRUCT_BODY()

	FLFPCompactIntNameArray() {}

	FLFPCompactIntNameArray(const FName& NewName) : Name(NewName) {}

	FLFPCompactIntNameArray(const FName& NewName, const FLFPCompactIntArray& Setting) : Super(Setting), Name(NewName) {}

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPFunctionData")
		FName Name = FName();

public:

	FORCEINLINE bool operator==(const FLFPCompactIntNameArray& Other) const
	{
		return Name == Other.Name;
	}

	FORCEINLINE bool operator==(const FName& Other) const
	{
		return Name == Other;
	}
};

USTRUCT(BlueprintType)
struct FLFPIntPointList
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, SaveGame)
		TArray<FIntPoint> PointList = TArray<FIntPoint>();

public:

	FORCEINLINE bool ContainIndex(const int32 Index) const
	{
		for (const FIntPoint Point : PointList)
		{
			if (Point.X <= Index && Point.Y >= Index) return true;
		}

		return false;
	}

	FORCEINLINE FIntPoint GetOverlapIndex(const FIntPoint Point) const
	{
		FIntPoint Result(INDEX_NONE);

		for (int32 Index = 0; Index < PointList.Num(); Index++)
		{
			if (PointList[Index].Y < Point.X) continue;

			if (PointList[Index].X > Point.Y)
			{
				/* Search Too Far */

				Result.Y = Index;

				break;
			}
			
			Result.X = Index;

			break;
		}

		if (Result.X == INDEX_NONE) return Result;

		for (int32 Index = PointList.Num() - 1; Index >= Result.X ; Index--)
		{
			if (PointList[Index].X > Point.Y) continue;

			Result.Y = Index;

			break;
		}

		return Result;
	}

	FORCEINLINE void Merge(const int32 Index, const FIntPoint Point)
	{
		check(PointList.IsValidIndex(Index));

		if (PointList[Index].X > Point.X) PointList[Index].X = Point.X;
		if (PointList[Index].Y < Point.Y) PointList[Index].Y = Point.Y;

		return;
	}

	FORCEINLINE void Cut(const int32 Index, const FIntPoint Point)
	{
		if (PointList[Index].X > Point.Y || PointList[Index].Y < Point.X) return;

		check(PointList.IsValidIndex(Index));

		if (PointList[Index].Y <= Point.Y && PointList[Index].X >= Point.X)
		{
			PointList.RemoveAt(Index);
		}
		else if (PointList[Index].Y > Point.Y && PointList[Index].X < Point.X)
		{
			PointList.Insert(FIntPoint(Point.Y + 1, PointList[Index].Y), Index + 1);

			PointList[Index].Y = Point.X - 1;
		}
		else if (PointList[Index].Y > Point.Y)
		{
			PointList[Index].X = Point.Y + 1;
		}
		else if (PointList[Index].X < Point.X)
		{
			PointList[Index].Y = Point.X - 1;
		}
	}

	FORCEINLINE void Add(const FIntPoint Point)
	{
		const FIntPoint OverlapIndexPoint(GetOverlapIndex(Point + FIntPoint(-1, 1)));

		if (OverlapIndexPoint.X == INDEX_NONE)
		{
			if (OverlapIndexPoint.Y == INDEX_NONE)
			{
				PointList.Add(Point);
			}
			else
			{
				PointList.Insert(Point, OverlapIndexPoint.Y);
			}

			return;
		}

		check(OverlapIndexPoint.Y != INDEX_NONE);

		Merge(OverlapIndexPoint.X, FIntPoint(Point.X, FMath::Max(Point.Y, PointList[OverlapIndexPoint.Y].Y)));

		for (int32 Index = OverlapIndexPoint.Y; Index > OverlapIndexPoint.X; Index--)
		{
			PointList.RemoveAt(Index);
		}
	}

	FORCEINLINE void Remove(const FIntPoint Point)
	{
		const FIntPoint OverlapIndexPoint(GetOverlapIndex(Point));

		for (int32 Index = OverlapIndexPoint.Y; Index >= OverlapIndexPoint.X; Index--)
		{
			Cut(Index, Point);
		}
	}
};

UCLASS()
class LOHFUNCTIONPLUGIN_API ULohFunctionPluginLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "LohFunctionPluginLibrary | LFPIntPointList")
		static bool ContainPoint(const FLFPIntPointList& List, const int32 Index);
	
	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary | LFPIntPointList")
		static void AddPoint(UPARAM(ref) FLFPIntPointList& List, const FIntPoint Range);
	
	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary | LFPIntPointList")
		static void RemovePoint(UPARAM(ref) FLFPIntPointList& List, const FIntPoint Range);


	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary | Bit")
		static TArray<uint8> GenerateBitMatrixNumberTop(const uint8 BitList);


	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary | Other")
		static FGameplayTag GetGameplayTagFromName(const FName TagName);
};
