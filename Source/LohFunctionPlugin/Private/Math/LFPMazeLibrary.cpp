// Copyright by Loh Zhi Kang


#include "Math/LFPMazeLibrary.h"

FLFPMazeTable ULFPMazeLibrary::CreateMazeStartData(const FIntVector MazeSize, const TSet<int32>& BlockID)
{
    FLFPMazeTable MazeTable;

    MazeTable.StartData.Reserve(MazeSize.X * MazeSize.Y * MazeSize.Z);

    int32 Index = 0;

    int32 JumpZ = MazeSize.X * MazeSize.Y;

    for (int32 Z = 0; Z < MazeSize.Z; Z++)
    for (int32 Y = 0; Y < MazeSize.Y; Y++)
    for (int32 X = 0; X < MazeSize.X; X++)
    {
        FIntVector Location = FIntVector(X, Y, Z);

        if (BlockID.Contains(Index)) { MazeTable.StartData.Add(FLFPMazeStartData(Location, true)); Index++; continue; }

        TArray<int32> Open;
        Open.Reserve(6);

        if (!BlockID.Contains(Index - 1)            && X - 1 >= 0)         Open.Emplace(Index - 1);
        if (!BlockID.Contains(Index + 1)            && X + 1 < MazeSize.X) Open.Emplace(Index + 1);
        if (!BlockID.Contains(Index - MazeSize.X)   && Y - 1 >= 0)         Open.Emplace(Index - MazeSize.X);
        if (!BlockID.Contains(Index + MazeSize.X)   && Y + 1 < MazeSize.Y) Open.Emplace(Index + MazeSize.X);
        if (!BlockID.Contains(Index - JumpZ)        && Z - 1 >= 0)         Open.Emplace(Index - JumpZ);
        if (!BlockID.Contains(Index + JumpZ)        && Z + 1 < MazeSize.Z) Open.Emplace(Index + JumpZ);

        MazeTable.StartData.Add(FLFPMazeStartData(Location, Open));

        Index++;
    }

    return MazeTable;
}

bool ULFPMazeLibrary::GenerateMazeData(UPARAM(Ref)FLFPMazeTable& MazeTable, const FRandomStream& Seed)
{
    if (MazeTable.StartData.Num() == 0) return false;

    // Setup Unvist List For Visit Check
    TSet<int32> UnVisit;
    {
        TArray<int32> UnVisitArray;

        UnVisitArray.Reserve(MazeTable.StartData.Num());

        for (int32 i = 0; i < MazeTable.StartData.Num(); i++)
            if (!MazeTable.StartData[i].IsBlock) UnVisitArray.Add(i);

        for (int32 i = 0; i < UnVisitArray.Num(); i++)
            UnVisitArray.Swap(i, Seed.RandHelper(UnVisitArray.Num() - 1));

        UnVisit.Append(UnVisitArray);
    }

    // Fill Output Data With EmptyMazeData
    MazeTable.MazeData.Init(FLFPMazeData(), MazeTable.StartData.Num());

    TSet<int32> NextVisitList;

    int32 CurrentIndex = -1;

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

        // Swap Open List
        for (int32 i = 0; i < OpenIndex.Num(); i++)
            OpenIndex.Swap(i, Seed.RandHelper(OpenIndex.Num() - 1));

        // Add To Next Visit
        for (const int32 Item : OpenIndex)
        {
            if (UnVisit.Contains(Item))
            {
                NextVisitList.Add(Item);

                MazeTable.MazeData[Item].ParentIndex = CurrentIndex;
                MazeTable.MazeData[Item].WalkCount = MazeTable.MazeData[CurrentIndex].WalkCount + 1;
            }
        }

        // Next Index
        CurrentIndex = NextVisitList.Num() > 0 ? *NextVisitList.begin() : -1;
    }

    for (int32 i = 0; i < MazeTable.MazeData.Num(); i++)
        if (MazeTable.MazeData[i].OpenList.Num() == 1)
            MazeTable.DeadEnd.Add(i);

    return true;
}

bool ULFPMazeLibrary::RemoveMazeDeadEnd(UPARAM(Ref)FLFPMazeTable& MazeTable, const int32 Amount, const FRandomStream& Seed)
{
    if (MazeTable.MazeData.Num() == 0 || Amount <= 0) return false;

    for (int32 i = 0; i < Amount; i++)
    {
        if (MazeTable.DeadEnd.Num() == 0) break;

        int32 CurrentIndex = MazeTable.DeadEnd.Pop();

        TArray<int32> OpenIndex = MazeTable.StartData[CurrentIndex].OpenConnection;

        OpenIndex.Remove(MazeTable.MazeData[CurrentIndex].OpenList[0]);

        int32 ChooseIndex = OpenIndex[Seed.RandHelper(OpenIndex.Num() - 1)];

        MazeTable.MazeData[CurrentIndex].OpenList.Add(ChooseIndex);
        MazeTable.MazeData[ChooseIndex].OpenList.Add(CurrentIndex);

        MazeTable.DeadEnd.RemoveSingleSwap(ChooseIndex);
    }

    return true;
}

bool ULFPMazeLibrary::GenerateMazeArea(UPARAM(Ref)FLFPMazeTable& MazeTable)
{
    if (MazeTable.MazeData.Num() == 0) return false;

    // Setup Unvist List For Visit Check
    TSet<int32> UnVisit;

    for (int32 i = 0; i < MazeTable.MazeData.Num(); i++)
        if (MazeTable.MazeData[i].OpenList.Num() <= 2 && MazeTable.MazeData[i].OpenList.Num() != 0) UnVisit.Add(i);

    int32 CurrentIndex = -1;

    while (UnVisit.Num() != 0)
    {
        if (CurrentIndex == -1)
            CurrentIndex = *UnVisit.begin();

        UnVisit.Remove(CurrentIndex);

        if (MazeTable.MazeData[CurrentIndex].AreaID == -1)
        {
            MazeTable.MazeData[CurrentIndex].AreaID = MazeTable.MazeArea.Add(FLFPMazeArea());
        }

        MazeTable.MazeArea[MazeTable.MazeData[CurrentIndex].AreaID].Cell.Add(CurrentIndex);

        bool bHasNext = false;

        for (const int32 Item : MazeTable.MazeData[CurrentIndex].OpenList)
        {
            if (MazeTable.MazeData[Item].OpenList.Num() <= 2 && UnVisit.Contains(Item))
            {
                MazeTable.MazeData[Item].AreaID = MazeTable.MazeData[CurrentIndex].AreaID;

                CurrentIndex = Item;

                bHasNext = true;

                break;
            }
        }

        if (!bHasNext)
        {
            CurrentIndex = -1;
        }
    }

    return true;
}
