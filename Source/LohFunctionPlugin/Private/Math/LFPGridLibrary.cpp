// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)



#include "Math/LFPGridLibrary.h"

bool ULFPGridLibrary::IsGridLocationValid(const FIntVector& Location, const FIntVector& GridSize)
{
	return (Location.GetMin() >= 0 && Location.X < GridSize.X && Location.Y < GridSize.Y && Location.Z < GridSize.Z);
}

bool ULFPGridLibrary::IsOnGridEdge(const FIntVector& Location, const FIntVector& GridSize)
{
	return Location.GetMin() == 0 || Location.X == GridSize.X - 1 || Location.Y == GridSize.Y - 1 || Location.Z == GridSize.Z - 1;
}

TArray<FIntVector> ULFPGridLibrary::GetGridEdgeDirection(const FIntVector& Location, const FIntVector& GridSize)
{
	TArray<FIntVector> ReturnList;

	if (Location.X == GridSize.X - 1)
	{
		ReturnList.Add(FIntVector(1, 0, 0));
	}

	if (Location.Y == GridSize.Y - 1)
	{
		ReturnList.Add(FIntVector(0, 1, 0));
	}

	if (Location.Z == GridSize.Z - 1)
	{
		ReturnList.Add(FIntVector(0, 0, 1));
	}

	if (Location.X == 0)
	{
		ReturnList.Add(FIntVector(-1, 0, 0));
	}

	if (Location.Y == 0)
	{
		ReturnList.Add(FIntVector(0, -1, 0));
	}

	if (Location.Z == 0)
	{
		ReturnList.Add(FIntVector(0, 0, -1));
	}

	return ReturnList;
}

int32 ULFPGridLibrary::ToGridIndex(FIntVector Location, const FIntVector& GridSize, const bool bRoundLocation)
{
	if (bRoundLocation)
	{
		Location.X %= GridSize.X;
		Location.Y %= GridSize.Y;
		Location.Z %= GridSize.Z;

		if (Location.X < 0) Location.X += GridSize.X;
		if (Location.Y < 0) Location.Y += GridSize.Y;
		if (Location.Z < 0) Location.Z += GridSize.Z;
	}
	else if (IsGridLocationValid(Location, GridSize) == false)
	{
		return INDEX_NONE;
	}

	return Location.X + (Location.Y * GridSize.X) + (Location.Z * (GridSize.X * GridSize.Y));
}

TArray<int32> ULFPGridLibrary::ToGridIndexList(const TArray<FIntVector>& GridLocations, const FIntVector Offset, const FIntVector& GridSize)
{
	TArray<int32> ReturnData;

	for (const FIntVector Item : GridLocations)
	{
		if (!IsGridLocationValid(Item + Offset, GridSize)) continue;

		ReturnData.Add(ToGridIndex(Item + Offset, GridSize));
	}

	return ReturnData;
}

FIntVector ULFPGridLibrary::ToGridLocation(int32 Index, const FIntVector& GridSize, const bool bRoundIndex)
{
	FIntVector ReturnData = FIntVector(INDEX_NONE);

	const int32 TotalSize = (GridSize.X * GridSize.Y * GridSize.Z);

	if (bRoundIndex)
	{
		Index %= TotalSize;

		if (Index < 0) Index += TotalSize;
	}
	else if (Index < 0 || Index >= TotalSize)
	{
		return ReturnData;
	}

	ReturnData.Z = Index / (GridSize.X * GridSize.Y);
	ReturnData.Y = (Index / GridSize.X) - (ReturnData.Z * GridSize.Y);
	ReturnData.X = Index % GridSize.X;

	return ReturnData;
}

TArray<FIntVector> ULFPGridLibrary::ToGridLocationList(const TArray<int32>& Indexs, const int32 Offset, const FIntVector& GridSize)
{
	TArray<FIntVector> ReturnData;

	int32 GridArratSize = GridSize.X * GridSize.Y * GridSize.Z;

	for (const int32 Item : Indexs)
	{
		if (GridArratSize <= Item || Item < 0) continue;

		ReturnData.Add(ToGridLocation(Item, GridSize));
	}

	return ReturnData;
}

TArray<int32> ULFPGridLibrary::SectionGridIndex(const FIntVector SectionSize, const TSet<int32>& IgnoreIndexs, const FIntVector& GridSize)
{
	TArray<int32> ReturnData;

	if (SectionSize.GetMin() <= 0) return ReturnData;

	FIntVector Size = FIntVector(GridSize.X / SectionSize.X, GridSize.Y / SectionSize.Y, GridSize.Z / SectionSize.Z);

	ReturnData.Reserve(Size.X * Size.Y * Size.Z);

	// Fill Unvisit List With Index
	for (int32 Z = 0; Z < GridSize.Z; Z += SectionSize.Z)
		for (int32 Y = 0; Y < GridSize.Y; Y += SectionSize.Y)
			for (int32 X = 0; X < GridSize.X; X += SectionSize.X)
			{
				int32 Index = ToGridIndex(FIntVector(X, Y, Z), GridSize);

				if (!IgnoreIndexs.Contains(Index)) ReturnData.Add(Index);
			}

	return ReturnData;
}

TArray<int32> ULFPGridLibrary::RandomSectionGridIndex(const int32 Amount, const FIntVector SectionSize, const TSet<int32>& IgnoreIndexs, const FRandomStream& Seed, const FIntVector& GridSize)
{
	TArray<int32> ReturnData;

	if (SectionSize.GetMin() <= 0) return ReturnData;

	FIntVector Size = FIntVector(GridSize.X / SectionSize.X, GridSize.Y / SectionSize.Y, GridSize.Z / SectionSize.Z);

	// Setup Unvist List
	TArray<int32> UnVisit;
	// Reserve List To Fill Faster
	UnVisit.Reserve(GridSize.X * GridSize.Y * GridSize.Z);
	// Fill Unvisit List With Index
	for (int32 Z = 0; Z < GridSize.Z; Z += SectionSize.Z)
		for (int32 Y = 0; Y < GridSize.Y; Y += SectionSize.Y)
			for (int32 X = 0; X < GridSize.X; X += SectionSize.X)
			{
				int32 Index = ToGridIndex(FIntVector(X, Y, Z), GridSize);

				if (!IgnoreIndexs.Contains(Index)) UnVisit.Add(Index);
			}

	// Shuffle Array Item
	for (int32 i = 0; i < UnVisit.Num(); i++)
	{
		UnVisit.Swap(i, Seed.RandRange(0, UnVisit.Num() - 1));
	}

	ReturnData.Reserve(Amount);

	for (int32 i = 0; i < Amount; i++)
	{
		ReturnData.Add(UnVisit.Pop());
	}

	return ReturnData;
}

TArray<int32> ULFPGridLibrary::GetGridAreaIndex(const int32 Index, const FIntVector Offset, const FIntVector AreaSize, const FIntVector& GridSize)
{
	FIntVector StartLoc = ToGridLocation(Index, GridSize) + Offset;
	TArray<int32> ReturnData;

	ReturnData.Reserve(((AreaSize.X * AreaSize.Y * AreaSize.Z) * 2) + 1);

	for (int32 Z = -AreaSize.Z; Z <= AreaSize.Z; Z++)
		for (int32 Y = -AreaSize.Y; Y <= AreaSize.Y; Y++)
			for (int32 X = -AreaSize.X; X <= AreaSize.X; X++)
			{
				FIntVector LoopLoc = FIntVector(X, Y, Z) + StartLoc;

				if (IsGridLocationValid(LoopLoc, GridSize))
				{
					ReturnData.Add(ToGridIndex(LoopLoc, GridSize));
				}
			}

	return ReturnData;
}
