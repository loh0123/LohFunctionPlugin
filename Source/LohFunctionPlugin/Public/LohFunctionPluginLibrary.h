// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#pragma once

#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "LohFunctionPluginLibrary.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LFPCompactIntArray, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LFPCompactIDArray, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LFPCompactTagArray, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LFPCompactMetaArray, Log, All);

USTRUCT(BlueprintType)
struct FLFPCompactIntArray
{
	GENERATED_BODY()

	FLFPCompactIntArray() {}

	FLFPCompactIntArray(const uint32 NewIndexSize) : IndexSize(NewIndexSize) {}

	FLFPCompactIntArray(const uint32 NewIndexSize, const uint32 NewMinSize) : IndexSize(NewIndexSize), MinBitSize(NewMinSize) {}

private:

	UPROPERTY()
		TArray<uint32> IndexList = TArray<uint32>();

	UPROPERTY()
		uint32 IndexSize = 0;

	UPROPERTY()
		uint8 EncodeBit = 0;

	UPROPERTY()
		uint8 MinBitSize = 0;

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

	FORCEINLINE void ResizeBitArray(uint8 NewSize)
	{
		check(NewSize >= 0);

		UE_LOG(LFPCompactIntArray, Log, TEXT("FLFPCompactIntArray : Resize Bit To %d"), NewSize);

		if (NewSize > 0)
		{
			NewSize = FMath::Max(NewSize, MinBitSize);
		}

		if (NewSize == EncodeBit) return;

		if (NewSize == 0)
		{
			IndexList.Empty();

			EncodeBit = NewSize;

			return;
		}

		const TArray<uint32> OldGridIndexList = IndexList;

		const uint8 OldSize = EncodeBit;

		EncodeBit = NewSize;

		const int32 ChuckBitSize = FMath::DivideAndRoundUp(IndexSize, uint32(32));

		IndexList.Init(0, (NewSize * ChuckBitSize));

		if (OldSize == 0) return;

		for (uint32 GridIndex = 0; GridIndex < IndexSize; GridIndex++)
		{
			for (uint8 EncodeIndex = 0; EncodeIndex < OldSize; EncodeIndex++)
			{
				const int32 OldBitIndex = int32((GridIndex * OldSize) + EncodeIndex);
				const int32 NewBitIndex = int32((GridIndex * EncodeBit) + EncodeIndex);

				GetIndexRef(IndexList, NewBitIndex) = GetIndexConstRef(OldGridIndexList, OldBitIndex);
			}
		}
	}

public:

	FORCEINLINE bool HasData() const
	{
		return EncodeBit > 0 && IndexSize > 0;
	}

	FORCEINLINE bool IsInitialized() const
	{
		return IndexSize > 0;
	}

	FORCEINLINE bool IsValidIndex(const int32 Index) const
	{
		return Index >= 0 && Index < int32(IndexSize);
	}

	/** Resize Function */

	FORCEINLINE void Resize(const int32 NewMaxSize)
	{
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
		checkf(IsValidIndex(Index) && HasData(), TEXT("Index : %d, EncodeBtye : %u"), Index, EncodeBit);

		for (uint8 EncodeIndex = 0; EncodeIndex < EncodeBit; EncodeIndex++)
		{
			const int32 BitIndex = (Index * EncodeBit) + EncodeIndex;

			GetIndexRef(IndexList, BitIndex) = FConstBitReference(Number, 1 << EncodeIndex);
		}
	}

	FORCEINLINE uint32 GetIndexNumber(const int32 Index) const
	{
		checkf(IsValidIndex(Index), TEXT("Index : %d, EncodeBtye : %u"), Index, EncodeBit);

		uint32 OutIndex = 0;

		for (uint8 EncodeIndex = 0; EncodeIndex < EncodeBit; EncodeIndex++)
		{
			const int32 BitIndex = (Index * EncodeBit) + EncodeIndex;

			FBitReference(OutIndex, 1 << EncodeIndex) = GetIndexConstRef(IndexList, BitIndex);
		}

		return OutIndex;
	}

	/** Debug Function */

	FORCEINLINE uint8 GetEncodeLength() const
	{
		return EncodeBit;
	}

	FORCEINLINE uint32 GetIndexSize() const
	{
		return IndexSize;
	}

public:

	friend FArchive& operator<<(FArchive& Ar, FLFPCompactIntArray& Data)
	{
		return Ar << Data.IndexList << Data.EncodeBit << Data.IndexSize;
	}

};

USTRUCT(BlueprintType)
struct FLFPCompactIDArray : public FLFPCompactIntArray
{
	GENERATED_USTRUCT_BODY()

	FLFPCompactIDArray() {}

	FLFPCompactIDArray(const uint32 NewIndexSize) : Super(NewIndexSize) {}

	FLFPCompactIDArray(const uint32 NewIndexSize, const uint32 NewMinSize) : Super(NewIndexSize, NewMinSize) {}

private:

	UPROPERTY()
	TArray<int32> OpenIDList = {};

	UPROPERTY()
	TArray<int32> IDRefList = {};

protected:

	/** Resize Function */

	FORCEINLINE void ResizeID()
	{
		bool bNeedSort = false;

		for (int32 IDIndex = IDRefList.Num() - 1; IDIndex >= 0; --IDIndex)
		{
			if (IDRefList[IDIndex] == 0)
			{
				IDRefList.RemoveAt(IDIndex);

				OpenIDList.RemoveSingle(IDIndex);

				bNeedSort = true;
			}
			else
			{
				break;
			}
		}

		if (bNeedSort)
		{
			OpenIDList.HeapSort();
		}

		Resize(IDRefList.Num());

		return;
	}

private:

	FORCEINLINE bool SetID_Internal(const int32 Index, const int32 ID, const bool bCheckOpenID = true)
	{
		if (IsValidIndex(Index) == false)
		{
			UE_LOG(LFPCompactIDArray, Warning, TEXT("FLFPCompactIDArray : SetID_Internal Index Invalid : Index = %d, IndexSize = %d"), Index, GetIndexSize());

			return false;
		}

		// Remove the ID on current index
		RemoveID(Index, false);

		int32& IDRef = IDRefList[ID];

		if (IDRef == 0 && bCheckOpenID)
		{
			const int32 IDIndex = OpenIDList.Find(ID);

			check(IDIndex == INDEX_NONE);

			OpenIDList.HeapRemoveAt(IDIndex);
		}

		IDRef += 1;

		SetIndexNumber(Index, ID + 1);

		return true;
	}

	FORCEINLINE int32 AssignID_Internal()
	{
		int32 NewID = INDEX_NONE;

		if (OpenIDList.IsEmpty() == false)
		{
			OpenIDList.HeapPop(NewID);
		}
		else
		{
			NewID = IDRefList.Add(0);
		}

		check(IDRefList.IsValidIndex(NewID));

		Resize(IDRefList.Num());

		return NewID;
	}

public:

	/* Set Index List To Use New ID */
	FORCEINLINE int32 AssignID(const TArray<int32>& NewIndexList)
	{
		const int32 NewID = AssignID_Internal();

		int32& IDRef = IDRefList[NewID];

		for (const int32 Index : NewIndexList)
		{
			SetID_Internal(Index, NewID, false);
		}

		ResizeID();

		return NewID;
	}

	FORCEINLINE int32 AssignArray()
	{
		const int32 NewID = AssignID_Internal();

		int32& IDRef = IDRefList[NewID];

		for (int32 Index = 0; Index < int32(GetIndexSize()); Index++)
		{
			SetID_Internal(Index, NewID, false);
		}

		ResizeID();

		return NewID;
	}

	FORCEINLINE bool SetID(const int32 Index, const int32 ID)
	{
		if (IsValidIndex(Index) == false || IDRefList.IsValidIndex(ID) == false)
		{
			UE_LOG(LFPCompactIDArray, Warning, TEXT("FLFPCompactIDArray : SetID Index Invalid : Index = %d, IndexSize = %d, IDRefList Num = %d"), Index, GetIndexSize(), IDRefList.Num());

			return false;
		}

		if (SetID_Internal(Index, ID))
		{
			ResizeID();
		}

		return true;
	}

	FORCEINLINE bool SetIDList(const TArray<int32>& NewIndexList, const int32 ID)
	{
		if (IDRefList.IsValidIndex(ID) == false)
		{
			UE_LOG(LFPCompactIDArray, Warning, TEXT("FLFPCompactIDArray : SetIDList ID Invalid : ID = %d, IDRefList Num = %d"), ID, IDRefList.Num());

			return false;
		}

		for (const int32 Index : NewIndexList)
		{
			SetID_Internal(Index, ID);
		}

		ResizeID();

		return true;
	}

	FORCEINLINE bool RemoveID(const int32 Index, const bool bResize = true)
	{
		if (IsValidIndex(Index) == false || HasData() == false)
		{
			UE_LOG(LFPCompactIDArray, Warning, TEXT("FLFPCompactIDArray : RemoveID Index Invalid : Index = %d, IndexSize = %d, IsInitialized = %s"), Index, GetIndexSize(), (HasData() ? TEXT("true") : TEXT("false")));

			return false;
		}

		int32 CorrectID = INDEX_NONE;
		{
			const uint32 RemoveID = GetIndexNumber(Index);

			// ID is not valid
			if (RemoveID == 0)
			{
				return false;
			}

			CorrectID = RemoveID - 1;
		}

		int32& IDRef = IDRefList[CorrectID];

		IDRef -= 1;

		SetIndexNumber(Index, 0);

		// Check ID Is Not Smaller Than Index NONE
		check(IDRef >= 0);

		if (IDRef == 0)
		{
			OpenIDList.HeapPush(IDRef);
		}

		if (bResize)
		{
			ResizeID();
		}

		return true;
	}

	FORCEINLINE int32 GetID(const int32 Index) const
	{
		if (IsValidIndex(Index) == false || HasData() == false)
		{
			return INDEX_NONE;
		}

		return GetIndexNumber(Index) - 1;
	}

	FORCEINLINE int32 IDLength() const
	{
		if (HasData() == false)
		{
			return 0;
		}

		return IDRefList.Num();
	}
};

USTRUCT(BlueprintType)
struct FLFPCompactTagArray : public FLFPCompactIDArray
{
	GENERATED_USTRUCT_BODY()

	FLFPCompactTagArray() {}

	FLFPCompactTagArray(const uint32 NewIndexSize) : Super(NewIndexSize) {}

	FLFPCompactTagArray(const uint32 NewIndexSize, const uint32 NewMinSize, const FGameplayTag& StartTag) : Super(NewIndexSize, NewMinSize)
	{
		if (StartTag.IsValid() == false)
		{
			return;
		}

		ItemList.Add(StartTag);

		AssignArray();
	}

private:

	UPROPERTY()
	TArray<FGameplayTag> ItemList = {};

protected:

	/** Resize Function */

	FORCEINLINE void ResizeArray()
	{
		ItemList.SetNum(IDLength());

		return;
	}

	FORCEINLINE int32 SetIndexListToItem(const TArray<int32>& NewIndexList, const FGameplayTag& Item)
	{
		int32 ItemID = ItemList.IndexOfByKey(Item);

		if (ItemID == INDEX_NONE)
		{
			const int32 NewID = AssignID(NewIndexList);

			ItemList.SetNum(NewID + 1);

			ItemList[NewID] = Item;

			return ItemID;
		}

		SetIDList(NewIndexList, ItemID);

		return ItemID;
	}

public:

	/** Read / Write Function */

	FORCEINLINE void RemoveItem(const int32 CompactIndex)
	{
		if (IsValidIndex(CompactIndex) == false)
		{
			UE_LOG(LFPCompactTagArray, Warning, TEXT("FLFPCompactTagArray : RemoveItem Has Invalid CompactIndex (%d)"), CompactIndex);

			return;
		}

		if (RemoveID(CompactIndex))
		{
			ResizeArray();
		}
	}

	FORCEINLINE void AddItem(const int32 CompactIndex, const FGameplayTag& NewItem)
	{
		if (IsValidIndex(CompactIndex) == false)
		{
			UE_LOG(LFPCompactTagArray, Warning, TEXT("FLFPCompactTagArray : AddItem Has Invalid CompactIndex (%d)"), CompactIndex);

			return;
		}

		if (NewItem.IsValid() == false)
		{
			RemoveItem(CompactIndex);

			return;
		}

		SetIndexListToItem({ CompactIndex }, NewItem);
	}

	FORCEINLINE bool AddItemList(const TArray<int32>& CompactIndexList, const FGameplayTag& NewItem)
	{
		bool bAllValid = true;

		if (NewItem.IsValid() == false)
		{
			for (const int32& CompactIndex : CompactIndexList)
			{
				if (IsValidIndex(CompactIndex) == false)
				{
					UE_LOG(LFPCompactTagArray, Warning, TEXT("FLFPCompactTagArray : AddItemList Has Invalid CompactIndex (%d)"), CompactIndex);

					bAllValid = false;

					continue;
				}

				RemoveItem(CompactIndex);
			}

			return bAllValid;
		}

		SetIndexListToItem(CompactIndexList, NewItem);

		return bAllValid;
	}

	FORCEINLINE const TArray<FGameplayTag>& GetItemList() const
	{
		return ItemList;
	}

	FORCEINLINE FGameplayTag GetItem(const int32 CompactIndex) const
	{
		const int32 ID = GetID(CompactIndex);

		return ID != INDEX_NONE ? ItemList[ID] : FGameplayTag::EmptyTag;
	}
};

UENUM(BlueprintType)
enum class ELFPCompactMetaType : uint8 
{
	LFP_None	UMETA(DisplayName = "None"),
	LFP_Int		UMETA(DisplayName = "Int"),
	LFP_Float	UMETA(DisplayName = "Float"),
	LFP_Boolean	UMETA(DisplayName = "Boolean"),
	LFP_String	UMETA(DisplayName = "String"),
	LFP_Custom	UMETA(DisplayName = "Custom"),
};

USTRUCT(BlueprintType)
struct FLFPCompactMetaData
{
	GENERATED_BODY()

	FLFPCompactMetaData() {}

	FLFPCompactMetaData(const FGameplayTag& Tag) : MetaTag(Tag), MetaType(ELFPCompactMetaType::LFP_None), MetaData(TArray<uint8>()) {}

	FLFPCompactMetaData(const FGameplayTag& Tag, const TArray<uint8>& Data, const ELFPCompactMetaType Type) : MetaTag(Tag), MetaType(Type), MetaData(Data) {}

	FLFPCompactMetaData(const FLFPCompactMetaData& Other) : MetaTag(Other.MetaTag), MetaType(Other.MetaType), MetaData(Other.MetaData) {}

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	FGameplayTag MetaTag = FGameplayTag();

private:

	UPROPERTY()
	ELFPCompactMetaType MetaType = ELFPCompactMetaType::LFP_None;

	UPROPERTY()
	TArray<uint8> MetaData = TArray<uint8>();

public:

	FORCEINLINE	FString ToString() const
	{
		return FString::Printf(TEXT("| %s : %s |"), *MetaTag.ToString(), *GetDataAsString());
	}

public:

	FORCEINLINE	void ClearData()
	{
		MetaType = ELFPCompactMetaType::LFP_None;

		MetaData.Empty();
	}

	FORCEINLINE	bool HasData() const
	{
		return MetaType != ELFPCompactMetaType::LFP_None;
	}

	FORCEINLINE	int32 GetDataAsInt() const
	{
		if (MetaType != ELFPCompactMetaType::LFP_Int || MetaData.Num() < 4) return -1;

		return *(reinterpret_cast<const int32*>(MetaData.GetData()));
	}

	FORCEINLINE	void SetDataAsInt(const int32 NewData)
	{
		MetaData.SetNum(4);

		*(reinterpret_cast<int32*>(MetaData.GetData())) = NewData;

		MetaType = ELFPCompactMetaType::LFP_Int;
	}

	FORCEINLINE	float GetDataAsFloat() const
	{
		if (MetaType != ELFPCompactMetaType::LFP_Float || MetaData.Num() < 4) return -1.0f;

		return *(reinterpret_cast<const float*>(MetaData.GetData()));
	}

	FORCEINLINE	void SetDataAsFloat(const float NewData)
	{
		MetaData.SetNum(4);

		*(reinterpret_cast<float*>(MetaData.GetData())) = NewData;

		MetaType = ELFPCompactMetaType::LFP_Float;
	}

	FORCEINLINE	bool GetDataAsBool() const
	{
		if (MetaType != ELFPCompactMetaType::LFP_Boolean || MetaData.Num() < 1) return false;

		return MetaData[0] == uint8(1) ? true : false;
	}

	FORCEINLINE	void SetDataAsBool(const bool NewData)
	{
		MetaData = { NewData ? uint8(1) : uint8(0) };
		MetaType = ELFPCompactMetaType::LFP_Boolean;
	}

	FORCEINLINE	FString GetDataAsString() const
	{
		if (MetaType == ELFPCompactMetaType::LFP_None || MetaData.Num() < 1) return FString();

		switch (MetaType)
		{
		case ELFPCompactMetaType::LFP_Int:
			return FString::FromInt(GetDataAsInt());
		case ELFPCompactMetaType::LFP_Float:
			return FString::SanitizeFloat(GetDataAsFloat());
		case ELFPCompactMetaType::LFP_Boolean:
			return GetDataAsBool() ? "True" : "False";
		case ELFPCompactMetaType::LFP_String:
			return BytesToString(MetaData.GetData(), MetaData.Num());;
		}

		return FString();
	}

	FORCEINLINE	void SetDataAsString(const FString NewData)
	{
		MetaData.SetNum(NewData.Len());

		StringToBytes(NewData, MetaData.GetData(), MetaData.Num());

		MetaType = ELFPCompactMetaType::LFP_String;
	}

	FORCEINLINE	const TArray<uint8>& GetData() const
	{
		return MetaData;
	}

	FORCEINLINE	void SetData(const TArray<uint8>& NewData)
	{
		if (NewData.IsEmpty())
		{
			ClearData();
		}
		else
		{
			MetaType = ELFPCompactMetaType::LFP_Custom;

			MetaData = NewData;
		}
	}

	template <typename T>
	FORCEINLINE T GetData() const
	{
		if (MetaType == ELFPCompactMetaType::LFP_Custom || MetaData.Num() < 1) return T();

		FMemoryReader MemoryReader(MetaData, true);

		T NewData;

		T::StaticStruct()->SerializeBin(MemoryReader, &NewData);

		return MetaData;
	}

	template <typename T>
	FORCEINLINE void GetData(T& NewData) const
	{
		if (MetaType == ELFPCompactMetaType::LFP_Custom || MetaData.Num() < 1) return T();

		FMemoryReader MemoryReader(MetaData, true);

		T::StaticStruct()->SerializeBin(MemoryReader, &NewData);

		return MetaData;
	}
	
	template <typename T>
	FORCEINLINE	void SetData(const T& NewData)
	{
		MetaData.Empty();

		MetaType = ELFPCompactMetaType::LFP_Custom;

		FMemoryWriter MemoryWriter(MetaData, true);

		T::StaticStruct()->SerializeBin(MemoryWriter, &NewData);
	}

public:

	FORCEINLINE bool operator==(const FGameplayTag& Tag) const { return MetaTag == Tag; }

	FORCEINLINE bool operator==(const FLFPCompactMetaData& Other) const { return MetaTag == Other.MetaTag && MetaData == Other.MetaData && MetaType == Other.MetaType; }
};

USTRUCT(BlueprintType)
struct FLFPCompactMetaArray : public FLFPCompactIDArray
{
	GENERATED_USTRUCT_BODY()

	FLFPCompactMetaArray() {}

	FLFPCompactMetaArray(const uint32 NewIndexSize) : Super(NewIndexSize) {}

	FLFPCompactMetaArray(const uint32 NewIndexSize, const uint32 NewMinSize) : Super(NewIndexSize, NewMinSize) {}

private:

	UPROPERTY()
	TArray<FLFPCompactMetaData> ItemList = {};

protected:

	/** Resize Function */

	FORCEINLINE void ResizeArray()
	{
		ItemList.SetNum(IDLength());

		return;
	}

public:

	/** Read / Write Function */

	FORCEINLINE void RemoveItem(const int32 CompactIndex)
	{
		if (IsValidIndex(CompactIndex) == false)
		{
			UE_LOG(LFPCompactMetaArray, Warning, TEXT("FLFPCompactMetaArray : RemoveItem Has Invalid CompactIndex (%d)"), CompactIndex);

			return;
		}

		const int32 ID = GetID(CompactIndex);

		if (RemoveID(CompactIndex))
		{
			ItemList[ID] = FLFPCompactMetaData();

			ResizeArray();
		}
	}

	FORCEINLINE void AddItem(const int32 CompactIndex, const FLFPCompactMetaData& NewItem)
	{
		if (IsValidIndex(CompactIndex) == false)
		{
			UE_LOG(LFPCompactMetaArray, Warning, TEXT("FLFPCompactMetaArray : AddItem Has Invalid CompactIndex (%d)"), CompactIndex);

			return;
		}

		if (NewItem.MetaTag.IsValid() == false)
		{
			RemoveItem(CompactIndex);

			return;
		}

		const int32 FindedID = ItemList.IndexOfByKey(NewItem.MetaTag);

		if (FindedID != INDEX_NONE)
		{
			ItemList[FindedID] = NewItem;

			SetID(CompactIndex, FindedID);

			return;
		}

		const int32 NewID = AssignID({ CompactIndex });

		if (ItemList.Num() <= NewID)
		{
			ItemList.SetNum(NewID + 1);
		}

		ItemList[NewID] = NewItem;
	}

	FORCEINLINE const TArray<FLFPCompactMetaData>& GetItemList() const
	{
		return ItemList;
	}

	FORCEINLINE const FLFPCompactMetaData* GetItem(const int32 CompactIndex) const
	{
		const int32 ID = GetID(CompactIndex);

		return ID != INDEX_NONE ? &ItemList[ID] : nullptr;
	}
};

USTRUCT(BlueprintType)
struct FLFPCompactUniqueMetaArray : public FLFPCompactIDArray
{
	GENERATED_USTRUCT_BODY()

	FLFPCompactUniqueMetaArray() {}

	FLFPCompactUniqueMetaArray(const uint32 NewIndexSize) : Super(NewIndexSize) {}

	FLFPCompactUniqueMetaArray(const uint32 NewIndexSize, const uint32 NewMinSize) : Super(NewIndexSize, NewMinSize) {}

private:

	UPROPERTY()
	TArray<FLFPCompactMetaData> ItemList = {};

protected:

	/** Resize Function */

	FORCEINLINE void ResizeArray()
	{
		ItemList.SetNum(IDLength());

		return;
	}

public:

	/** Read / Write Function */

	FORCEINLINE void RemoveItem(const int32 CompactIndex)
	{
		if (IsValidIndex(CompactIndex) == false)
		{
			UE_LOG(LFPCompactMetaArray, Warning, TEXT("FLFPCompactUniqueMetaArray : RemoveItem Has Invalid CompactIndex (%d)"), CompactIndex);

			return;
		}

		const int32 ID = GetID(CompactIndex);

		if (RemoveID(CompactIndex))
		{
			ItemList[ID] = FLFPCompactMetaData();

			ResizeArray();
		}
	}

	FORCEINLINE void AddItem(const int32 CompactIndex, const FLFPCompactMetaData& NewItem)
	{
		if (IsValidIndex(CompactIndex) == false)
		{
			UE_LOG(LFPCompactMetaArray, Warning, TEXT("FLFPCompactUniqueMetaArray : AddItem Has Invalid CompactIndex (%d)"), CompactIndex);

			return;
		}

		if (NewItem.MetaTag.IsValid() == false)
		{
			RemoveItem(CompactIndex);

			return;
		}

		int32 NewID = GetID(CompactIndex);

		if (NewID != INDEX_NONE)
		{
			ItemList[NewID] = NewItem;

			return;
		}

		NewID = AssignID({ CompactIndex });

		if (ItemList.Num() <= NewID)
		{
			ItemList.SetNum(NewID + 1);
		}

		ItemList[NewID] = NewItem;
	}

	FORCEINLINE const TArray<FLFPCompactMetaData>& GetItemList() const
	{
		return ItemList;
	}

	FORCEINLINE const FLFPCompactMetaData* GetItem(const int32 CompactIndex) const
	{
		const int32 ID = GetID(CompactIndex);

		return ID != INDEX_NONE ? &ItemList[ID] : nullptr;
	}
};

USTRUCT(BlueprintType)
struct FLFPMetaArray
{
	GENERATED_USTRUCT_BODY()

	FLFPMetaArray() {}

	FLFPMetaArray(const int32 NewIndexSize) { ItemList.SetNum(NewIndexSize); }

private:

	UPROPERTY()
	TArray<FLFPCompactMetaData> ItemList = {};

public:

	/** Read / Write Function */

	FORCEINLINE void SetItem(const FLFPCompactMetaData& NewItem)
	{
		const int32 ItemIndex = ItemList.IndexOfByKey(NewItem.MetaTag);

		if (ItemIndex != INDEX_NONE)
		{
			if (NewItem.HasData())
			{
				ItemList[ItemIndex] = NewItem;
			}
			else
			{
				ItemList.RemoveAtSwap(ItemIndex);
			}
		}
		else if (NewItem.HasData())
		{
			ItemList.Add(NewItem);
		}
	}

	FORCEINLINE const TArray<FLFPCompactMetaData>& GetItemList() const
	{
		return ItemList;
	}

	FORCEINLINE const FLFPCompactMetaData* GetItemConst(const FGameplayTag& ItemTag) const
	{
		return ItemList.FindByKey(ItemTag);
	}

	FORCEINLINE FLFPCompactMetaData* GetItem(const FGameplayTag& ItemTag)
	{
		return ItemList.FindByKey(ItemTag);
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


	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary | LFPCompactIDArray")
		static void InitializeIDArray(UPARAM(ref) FLFPCompactIDArray& List, const int32 IndexSize);


	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary | LFPCompactIDArray")
		static int32 AssignID(UPARAM(ref) FLFPCompactIDArray& List, const TArray<int32>& NewIndexList);

	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary | LFPCompactIDArray")
		static bool SetID(UPARAM(ref) FLFPCompactIDArray& List, const int32 Index, const int32 ID);

	UFUNCTION(BlueprintCallable, Category = "LohFunctionPluginLibrary | LFPCompactIDArray")
		static bool RemoveID(UPARAM(ref) FLFPCompactIDArray& List, const int32 Index);

	UFUNCTION(BlueprintPure, Category = "LohFunctionPluginLibrary | LFPCompactIDArray")
		static int32 GetID(UPARAM(ref) FLFPCompactIDArray& List, const int32 Index);


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
