// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)



#include "Math/LFPMazeLibrary.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

FLFPMazeTable ULFPMazeLibrary::CreateMazeStartData(const FIntVector MazeSize)
{
    FLFPMazeTable MazeTable;

    MazeTable.StartData.Reserve(MazeSize.X * MazeSize.Y * MazeSize.Z);
    MazeTable.MazeSize = MazeSize;

    int32 Index = 0;

    int32 JumpZ = MazeSize.X * MazeSize.Y;

    for (int32 Z = 0; Z < MazeSize.Z; Z++)
    for (int32 Y = 0; Y < MazeSize.Y; Y++)
    for (int32 X = 0; X < MazeSize.X; X++)
    {
        FIntVector Location = FIntVector(X, Y, Z);

        TArray<int32> Open;
        Open.Reserve(6);

        if (X - 1 >= 0)         Open.Emplace(Index - 1);
        if (Y - 1 >= 0)         Open.Emplace(Index - MazeSize.X);
        if (Z - 1 >= 0)         Open.Emplace(Index - JumpZ);
        if (X + 1 < MazeSize.X) Open.Emplace(Index + 1);
        if (Y + 1 < MazeSize.Y) Open.Emplace(Index + MazeSize.X);
        if (Z + 1 < MazeSize.Z) Open.Emplace(Index + JumpZ);

        MazeTable.StartData.Add(FLFPMazeStartData(Location, Open));

        Index++;
    }

    return MazeTable;
}

bool ULFPMazeLibrary::GenerateMazeData(UPARAM(Ref)FLFPMazeTable& MazeTable, const TSet<int32>& PreConnection, const FIntPoint RoomExit, const FRandomStream& Seed)
{
    if (MazeTable.StartData.Num() == 0) return false;

    // Fill Output Data With EmptyMazeData
    MazeTable.MazeData.Init(FLFPMazeData(), MazeTable.StartData.Num());

    TArray<int32> RoomIndexs;
    RoomIndexs.Reserve(MazeTable.StartData.Num());
    TSet<int32> NextVisitList;
    NextVisitList.Reserve(PreConnection.Num() * 26);

    // Setup Unvist List For Visit Check
    TSet<int32> UnVisit;
    {
        TArray<int32> UnVisitArray;

        UnVisitArray.Reserve(MazeTable.StartData.Num());

        for (int32 i = 0; i < MazeTable.StartData.Num(); i++)
            switch (MazeTable.StartData[i].CellType)
            {
            case EMazeCellType::Maze_Open: UnVisitArray.Add(i);
                break;
            case EMazeCellType::Maze_Room: RoomIndexs.Add(i);
                break;
            }

        for (int32 i = 0; i < UnVisitArray.Num(); i++)
            UnVisitArray.Swap(i, Seed.RandHelper(UnVisitArray.Num() - 1));

        UnVisit.Append(UnVisitArray);
    }

    // Add All Pre Connection Room
    for (const int32 Item : PreConnection)
    {
        if (!UnVisit.Contains(Item)) continue;

        UnVisit.Remove(Item);

        for (const int32 OpenIndex : MazeTable.StartData[Item].OpenConnection)
        {
            if (!UnVisit.Contains(OpenIndex)) continue;

            if (PreConnection.Contains(OpenIndex))
            {
                MazeTable.MazeData[Item].OpenList.Add(OpenIndex);
                MazeTable.MazeData[OpenIndex].OpenList.Add(Item);
            }
            else
            {
                NextVisitList.Add(OpenIndex);

                MazeTable.MazeData[OpenIndex].ParentIndex = Item;
                MazeTable.MazeData[OpenIndex].WalkCount = 1;
            }
        }
    }

    // Select Index For VisitList If Available
    int32 CurrentIndex = NextVisitList.Num() > 0 ? *NextVisitList.begin() : -1;;

    while (UnVisit.Num() != 0)
    {
        // Get First Item In List
        if (CurrentIndex == -1)
            CurrentIndex = *UnVisit.begin();

        //Mark As Visit
        UnVisit.Remove(CurrentIndex);
        NextVisitList.Remove(CurrentIndex);

        // Connect To Parent If Valid
        if (MazeTable.MazeData[CurrentIndex].ParentIndex != -1)
        {
            MazeTable.MazeData[CurrentIndex].OpenList.Add(MazeTable.MazeData[CurrentIndex].ParentIndex);
            MazeTable.MazeData[MazeTable.MazeData[CurrentIndex].ParentIndex].OpenList.Add(CurrentIndex);
        }

        // Fill Open List
        TArray<int32> OpenIndex = MazeTable.StartData[CurrentIndex].OpenConnection;

        // Swap Array
        for (int32 i = 0; i < OpenIndex.Num(); i++)
            OpenIndex.Swap(i, Seed.RandHelper(OpenIndex.Num() - 1));

        // Add To Next Visit
        for (const int32 Item : OpenIndex)
        {
            if (MazeTable.StartData[Item].CellType == EMazeCellType::Maze_Open)
            {
                if (UnVisit.Contains(Item))
                {
                    NextVisitList.Add(Item);
                    MazeTable.MazeData[Item].ParentIndex = CurrentIndex;
                    MazeTable.MazeData[Item].WalkCount = MazeTable.MazeData[CurrentIndex].WalkCount + 1;
                }
            }
        }

        // Next Index
        CurrentIndex = NextVisitList.Num() > 0 ? *NextVisitList.begin() : -1;
    }

    for (int32 i = 0; i < MazeTable.MazeData.Num(); i++)
        if (MazeTable.MazeData[i].OpenList.Num() == 1)
            MazeTable.DeadEnd.Add(i);


    TArray<int32> RoomCount;

    // Sawp Room Index First
    for (int32 i = 0; i < RoomIndexs.Num(); i++)
        RoomIndexs.Swap(i, Seed.RandHelper(RoomIndexs.Num() - 1));

    for (const int32 Item : RoomIndexs)
    {
        const int32 CellID = MazeTable.StartData[Item].CellID;
    
        // Resize array if too small
        if (!RoomCount.IsValidIndex(CellID))
        {
            const int32 Start = RoomCount.Num();
    
            RoomCount.SetNum(CellID + 1);
    
            for (int32 i = Start; i < RoomCount.Num(); i++)
                RoomCount[i] = Seed.RandRange(RoomExit.X, RoomExit.Y);
        }

        bool CanConnect = RoomCount[CellID] > 0;

        // Fill Open List
        TArray<int32> OpenIndex = MazeTable.StartData[Item].OpenConnection;

        // Swap Array
        for (int32 i = 0; i < OpenIndex.Num(); i++)
            OpenIndex.Swap(i, Seed.RandHelper(OpenIndex.Num() - 1));

        // Process Array
        for (const int32 ConnectIndex : OpenIndex)
        {
            switch (MazeTable.StartData[ConnectIndex].CellType)
            {
            case EMazeCellType::Maze_Open:
                if (CanConnect)
                {
                    MazeTable.MazeData[Item].OpenList.Add(ConnectIndex);
                    MazeTable.MazeData[ConnectIndex].OpenList.Add(Item);
                    CanConnect = false;
                    RoomCount[CellID] -= 1;
                }
                break;
            case EMazeCellType::Maze_Room:
                MazeTable.MazeData[Item].OpenList.Add(ConnectIndex);
                MazeTable.MazeData[ConnectIndex].OpenList.Add(Item);
                break;
            }
        }
    }

    return true;
}

bool ULFPMazeLibrary::RemoveMazeDeadEnd(UPARAM(Ref)FLFPMazeTable& MazeTable, const int32 Amount, const FRandomStream& Seed)
{
    if (MazeTable.MazeData.Num() == 0 || Amount <= 0 || MazeTable.DeadEnd.Num() < Amount) return false;

    for (int32 i = 0; i < Amount; i++)
    {
        int32 CurrentIndex = MazeTable.DeadEnd.Pop();

        TArray<int32> OpenIndex = MazeTable.StartData[CurrentIndex].OpenConnection;

        for (const int32 RemoveIndex : MazeTable.MazeData[CurrentIndex].OpenList)
            OpenIndex.RemoveSingleSwap(RemoveIndex);

        if (OpenIndex.Num() == 0) continue;

        int32 ChooseIndex = OpenIndex[Seed.RandHelper(OpenIndex.Num() - 1)];

        MazeTable.MazeData[CurrentIndex].OpenList.Add(ChooseIndex);
        MazeTable.MazeData[ChooseIndex].OpenList.Add(CurrentIndex);

        if (MazeTable.DeadEnd.RemoveSingleSwap(ChooseIndex) == 1)
            i++;
    }

    return true;
}

bool ULFPMazeLibrary::GenerateMazeArea(UPARAM(Ref)FLFPMazeTable& MazeTable, const FIntPoint AreaSize, const FRandomStream& Seed)
{
    if (MazeTable.StartData.Num() == 0 || AreaSize.X <= 0 || AreaSize.Y <= 0) return false;

    int32 AreaID = 0;
    int32 AreaCount = Seed.RandRange(AreaSize.X, AreaSize.Y);

    TArray<int32> NextVisitList;
    NextVisitList.Reserve(MazeTable.StartData.Num());

    // Setup Unvist List For Visit Check
    TSet<int32> UnVisit;
    {
        TArray<int32> UnVisitArray;

        UnVisitArray.Reserve(MazeTable.StartData.Num());

        for (int32 i = 0; i < MazeTable.StartData.Num(); i++)
            if (MazeTable.StartData[i].CellType == EMazeCellType::Maze_Open)
                UnVisitArray.Add(i);

        for (int32 i = 0; i < UnVisitArray.Num(); i++)
            UnVisitArray.Swap(i, Seed.RandHelper(UnVisitArray.Num() - 1));

        UnVisit.Append(UnVisitArray);
    }

    while (UnVisit.Num() > 0)
    {
        if (NextVisitList.Num() == 0)
        {
            NextVisitList.Add(*UnVisit.begin());
            UnVisit.Remove(NextVisitList[0]);
        }

        if (MazeTable.MazeData.Num() == 0)
        {
            // Fill Out For Maze
        }
        else
        {
            const int32 CurrentIndex = NextVisitList.Pop(false);

            // Fill Open List
            TArray<int32> OpenIndex = MazeTable.MazeData[CurrentIndex].OpenList;

            // Swap Array
            for (int32 i = 0; i < OpenIndex.Num(); i++)
                OpenIndex.Swap(i, Seed.RandHelper(OpenIndex.Num() - 1));

            // Add To Next Visit
            for (const int32 Item : OpenIndex)
            {
                if (UnVisit.Contains(Item))
                {
                    NextVisitList.Add(Item);
                    UnVisit.Remove(CurrentIndex);
                    MazeTable.StartData[Item].CellID = AreaID;
                }

                if (--AreaCount == 0)
                {
                    NextVisitList.Empty(MazeTable.StartData.Num());
                    AreaID++;
                    break;
                }
            }
        }
    }

    return true;
}

bool ULFPMazeLibrary::SetMazeCellType(UPARAM(Ref)FLFPMazeTable& MazeTable, const TArray<int32> Indexs, const EMazeCellType Type)
{
    if (MazeTable.StartData.Num() == 0) return false;

    for (const int32 Item : Indexs)
    {
        if (MazeTable.StartData.IsValidIndex(Item))
            MazeTable.StartData[Item].CellType = Type;
    }

    return true;
}

bool ULFPMazeLibrary::SetMazeCellID(UPARAM(Ref)FLFPMazeTable& MazeTable, const TArray<int32> Indexs, const int32 ID)
{
    if (MazeTable.StartData.Num() == 0) return false;

    for (const int32 Item : Indexs)
    {
        if (MazeTable.StartData.IsValidIndex(Item))
            MazeTable.StartData[Item].CellID = ID;
    }

    return true;
}

TArray<int32> ULFPMazeLibrary::GetMazeCellNeighbourByType(const FLFPMazeTable& MazeTable, const int32 Index, const EMazeCellType Type)
{
    TArray<int32> ReturnData;

    if (!MazeTable.StartData.IsValidIndex(Index)) return ReturnData;

    for (const int32 Item : MazeTable.StartData[Index].OpenConnection)
    {
        if (MazeTable.StartData[Item].CellType == Type)
            ReturnData.Add(Item);
    }

    return ReturnData;
}
