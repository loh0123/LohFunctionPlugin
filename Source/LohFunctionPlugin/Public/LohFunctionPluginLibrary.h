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
struct FLFPCompactTagArray : public FLFPCompactIntArray
{
	GENERATED_USTRUCT_BODY()

	FLFPCompactTagArray() {}

	FLFPCompactTagArray(const uint32 NewIndexSize) : Super(NewIndexSize) 
	{
		ItemList.Add(FGameplayTag::EmptyTag);
		RefList.Add(NewIndexSize);
	}

private:

	UPROPERTY(SaveGame)
	TArray<FGameplayTag> ItemList = {};

	UPROPERTY(SaveGame)
	TArray<int32> OpenIndexList = {};

	UPROPERTY(SaveGame)
	TArray<int32> RefList = {};

private:

	/** Item Function */

	FORCEINLINE int32 AddItem(const FGameplayTag& NewItem, const bool bResizeList)
	{
		int32 ItemIndex = ItemList.Find(NewItem);

		if (ItemIndex == INDEX_NONE)
		{
			if (OpenIndexList.IsEmpty() == false)
			{
				ItemIndex = OpenIndexList.Pop();

				ItemList[ItemIndex] = NewItem;
			}
			else
			{
				ItemIndex = ItemList.Add(NewItem);
			}

			if (RefList.IsValidIndex(ItemIndex) == false) RefList.SetNum(ItemIndex + 1);

			if (bResizeList) ResizeList();
		}

		RefList[ItemIndex] += 1;

		return ItemIndex;
	}

	FORCEINLINE void RemoveItem(const int32 Index, const bool bResizeList)
	{
		check(RefList.IsValidIndex(Index));

		check(RefList[Index] > 0);

		RefList[Index] -= 1;

		if (RefList[Index] > 0) return;

		/** Sort And Push Into Open Index List */
		OpenIndexList.HeapPush(Index);

		ItemList.RemoveAt(Index);

		/* Remove Redundant Open Index */
		const int32 RemoveAmount = OpenIndexList.RemoveAll([&](const int32 Item)
			{
				return Item >= ItemList.Num();
			}
		);

		if (RemoveAmount > 0) OpenIndexList.HeapSort();

		if (bResizeList) ResizeList();

		return;
	}

	/** Resize Function */

	FORCEINLINE void ResizeList()
	{
		Resize(ItemList.Num());

		return;
	}

public:

	/** Read / Write Function */

	FORCEINLINE const TArray<FGameplayTag>& GetItemList() const
	{
		return ItemList;
	}

	FORCEINLINE void SetIndexItem(const int32 CompactIndex, const FGameplayTag& NewItem)
	{
		check(CompactIndex >= 0);

		RemoveItem(GetIndexNumber(CompactIndex), true);

		const int32 NewIndex = AddItem(NewItem, true);

		SetIndexNumber(CompactIndex, NewIndex);
	}

	FORCEINLINE const FGameplayTag& GetIndexItem(const int32 CompactIndex) const
	{
		return ItemList[GetIndexNumber(CompactIndex)];
	}

public:

	friend FArchive& operator<<(FArchive& Ar, FLFPCompactTagArray& Data)
	{
		return Ar << Data.ItemList << Data.OpenIndexList << Data.RefList;
	}
};

USTRUCT(BlueprintType)
struct FLFPCompactMetaData
{
	GENERATED_BODY()

	FLFPCompactMetaData() {}

	FLFPCompactMetaData(const FGameplayTag& Tag) : MetaTag(Tag), MetaData(TArray<uint8>()) {}

	FLFPCompactMetaData(const FGameplayTag& Tag, const TArray<uint8>& Data) : MetaTag(Tag), MetaData(Data) {}

	FLFPCompactMetaData(const FLFPCompactMetaData& Other) : MetaTag(Other.MetaTag), MetaData(Other.MetaData) {}

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	FGameplayTag MetaTag = FGameplayTag();

private:

	UPROPERTY()
	TArray<uint8> MetaData = TArray<uint8>();

public:

	FORCEINLINE	FString ToString() const
	{
		return FString::Printf(TEXT("| %s : %s |"), *MetaTag.ToString(), *GetDataAsString());
	}

public:

	FORCEINLINE	int32 GetDataAsInt() const
	{
		if (MetaData.Num() < 4) return -1;

		return *(reinterpret_cast<const int32*>(MetaData.GetData()));
	}

	FORCEINLINE	void SetDataAsInt(const int32 NewData)
	{
		MetaData.SetNum(4);

		*(reinterpret_cast<int32*>(MetaData.GetData())) = NewData;
	}

	FORCEINLINE	float GetDataAsFloat() const
	{
		if (MetaData.Num() < 4) return -1.0f;

		return *(reinterpret_cast<const float*>(MetaData.GetData()));
	}

	FORCEINLINE	void SetDataAsFloat(const float NewData)
	{
		MetaData.SetNum(4);

		*(reinterpret_cast<float*>(MetaData.GetData())) = NewData;
	}

	FORCEINLINE	bool GetDataAsBool() const
	{
		if (MetaData.Num() < 1) return false;

		return MetaData[0] == uint8(1) ? true : false;
	}

	FORCEINLINE	void SetDataAsBool(const bool NewData)
	{
		MetaData = { NewData ? uint8(1) : uint8(0) };
	}

	FORCEINLINE	FString GetDataAsString() const
	{
		if (MetaData.Num() < 1) return FString();

		return BytesToString(MetaData.GetData(), MetaData.Num());
	}

	FORCEINLINE	void SetDataAsString(const FString NewData)
	{
		MetaData.SetNum(NewData.Len());

		StringToBytes(NewData, MetaData.GetData(), MetaData.Num());
	}

public:

	FORCEINLINE bool operator==(const FGameplayTag& Tag) const { return MetaTag == Tag; }

	FORCEINLINE bool operator==(const FLFPCompactMetaData& Other) const { return MetaTag == Other.MetaTag && MetaData == Other.MetaData; }

public:

	friend FArchive& operator<<(FArchive& Ar, FLFPCompactMetaData& Data)
	{
		return Ar << Data.MetaTag << Data.MetaData;
	}
};

USTRUCT(BlueprintType)
struct FLFPCompactMetaArray : public FLFPCompactIntArray
{
	GENERATED_USTRUCT_BODY()

	FLFPCompactMetaArray() {}

	FLFPCompactMetaArray(const uint32 NewIndexSize) : Super(NewIndexSize)
	{
		ItemList.Add(FLFPCompactMetaData());
	}

private:

	UPROPERTY(SaveGame)
	TArray<FLFPCompactMetaData> ItemList = {};

	UPROPERTY(SaveGame)
	TArray<int32> OpenIndexList = {};

private:

	/** Item Function */

	FORCEINLINE int32 AddItem(const FLFPCompactMetaData& NewItem, const bool bResizeList)
	{
		int32 ItemIndex = ItemList.Find(NewItem);

		if (ItemIndex == INDEX_NONE)
		{
			if (OpenIndexList.IsEmpty() == false)
			{
				ItemIndex = OpenIndexList.Pop();

				ItemList[ItemIndex] = NewItem;
			}
			else
			{
				ItemIndex = ItemList.Add(NewItem);
			}

			if (bResizeList) ResizeList();
		}

		return ItemIndex;
	}

	FORCEINLINE void RemoveItem(const int32 Index, const bool bResizeList)
	{
		/** Sort And Push Into Open Index List */
		OpenIndexList.HeapPush(Index);

		ItemList.RemoveAt(Index);

		/* Remove Redundant Open Index */
		const int32 RemoveAmount = OpenIndexList.RemoveAll([&](const int32 Item)
			{
				return Item >= ItemList.Num();
			}
		);

		if (RemoveAmount > 0) OpenIndexList.HeapSort();

		if (bResizeList) ResizeList();

		return;
	}

	/** Resize Function */

	FORCEINLINE void ResizeList()
	{
		Resize(ItemList.Num());

		return;
	}

public:

	/** Read / Write Function */

	FORCEINLINE const TArray<FLFPCompactMetaData>& GetItemList() const
	{
		return ItemList;
	}

	FORCEINLINE void SetIndexItem(const int32 CompactIndex, const FLFPCompactMetaData& NewItem)
	{
		check(CompactIndex >= 0);

		RemoveItem(GetIndexNumber(CompactIndex), true);

		const int32 NewIndex = AddItem(NewItem, true);

		SetIndexNumber(CompactIndex, NewIndex);
	}

	FORCEINLINE const FLFPCompactMetaData& GetIndexItem(const int32 CompactIndex) const
	{
		return ItemList[GetIndexNumber(CompactIndex)];
	}

public:

	friend FArchive& operator<<(FArchive& Ar, FLFPCompactMetaArray& Data)
	{
		return Ar << Data.ItemList << Data.OpenIndexList;
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


	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary | Other")
		static FGameplayTag GetGameplayTagFromName(const FName TagName);


	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary | LFPCompactMetaData")
		static int32 GetMetaDataAsInt(UPARAM(ref) FLFPCompactMetaData& MetaData);

	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary | LFPCompactMetaData")
		static void SetMetaDataAsInt(UPARAM(ref) FLFPCompactMetaData& MetaData, const int32 Value);

	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary | LFPCompactMetaData")
		static float GetMetaDataAsFloat(UPARAM(ref) FLFPCompactMetaData& MetaData);

	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary | LFPCompactMetaData")
		static void SetMetaDataAsFloat(UPARAM(ref) FLFPCompactMetaData& MetaData, const float Value);

	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary | LFPCompactMetaData")
		static bool GetMetaDataAsBool(UPARAM(ref) FLFPCompactMetaData& MetaData);

	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary | LFPCompactMetaData")
		static void SetMetaDataAsBool(UPARAM(ref) FLFPCompactMetaData& MetaData, const bool Value);

	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary | LFPCompactMetaData")
		static FString GetMetaDataAsString(UPARAM(ref) FLFPCompactMetaData& MetaData);

	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary | LFPCompactMetaData")
		static void SetMetaDataAsString(UPARAM(ref) FLFPCompactMetaData& MetaData, const FString Value);
};
