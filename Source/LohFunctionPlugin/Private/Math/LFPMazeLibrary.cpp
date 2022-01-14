// Copyright by Loh Zhi Kang


#include "Math/LFPMazeLibrary.h"

FLFPMazeTable ULFPMazeLibrary::CreateMazeStartData(const FIntVector MazeSize, const TSet<int32>& BlockID)
{
    FLFPMazeTable MazeTable;

    MazeTable.StartData.Reserve(MazeSize.X * MazeSize.Y * MazeSize.Z);

    int32 Index = 0;

    for (int32 Z = 0; Z < MazeSize.Z; Z++)
    for (int32 Y = 0; Y < MazeSize.Y; Y++)
    for (int32 X = 0; X < MazeSize.X; X++)
    {
        FIntVector Location = FIntVector(X, Y, Z);

        if (BlockID.Contains(Index)) { MazeTable.StartData.Add(FLFPMazeStartData(Location, true)); Index++; continue; }

        TArray<int32> Open;
        Open.Reserve(6);

        if (!BlockID.Contains(Index - 1)                            && X - 1 >= 0)         Open.Emplace(Index - 1);
        if (!BlockID.Contains(Index + 1)                            && X + 1 < MazeSize.X) Open.Emplace(Index + 1);
        if (!BlockID.Contains(Index - MazeSize.X)                   && Y - 1 >= 0)         Open.Emplace(Index - MazeSize.X);
        if (!BlockID.Contains(Index + MazeSize.X)                   && Y + 1 < MazeSize.Y) Open.Emplace(Index + MazeSize.X);
        if (!BlockID.Contains(Index - (MazeSize.X * MazeSize.Y))    && Z - 1 >= 0)         Open.Emplace(Index - (MazeSize.X * MazeSize.Y));
        if (!BlockID.Contains(Index + (MazeSize.X * MazeSize.Y))    && Z + 1 < MazeSize.Z) Open.Emplace(Index + (MazeSize.X * MazeSize.Y));

        MazeTable.StartData.Add(FLFPMazeStartData(Location, Open));

        Index++;
    }

    return MazeTable;
}

bool ULFPMazeLibrary::GenerateMazeData(UPARAM(Ref)FLFPMazeTable& MazeTable, const FRandomStream& Seed)
{
    if (MazeTable.StartData.Num() == 0) return false;

    int32 CurrentIndex = Seed.RandRange(0, MazeTable.StartData.Num() - 1);

    // Setup Unvist List For Visit Check
    TSet<int32> UnVisit;
    // Reserve List To Fill Faster
    UnVisit.Reserve(MazeTable.StartData.Num());
    // Fill Unvisit List With Index
    for (int32 i = 0; i < MazeTable.StartData.Num(); i++)
        UnVisit.Add(i);

    // Fill Output Data With EmptyMazeData
    MazeTable.MazeData.Init(FLFPMazeData(), MazeTable.StartData.Num());

    while (UnVisit.Num() != 0)
    {
        //Remove Current Index For List
        UnVisit.Remove(CurrentIndex);

        TArray<int32> OpenIndex = MazeTable.StartData[CurrentIndex].OpenConnection;

        int32 ChooseIndex = -1;

        // Find Choose Index
        while (OpenIndex.Num() != 0)
        {
            int32 RandInd = Seed.RandRange(0, OpenIndex.Num() - 1);

            if (UnVisit.Contains(OpenIndex[RandInd]))
            {
                ChooseIndex = OpenIndex[RandInd];

                break;
            }

            OpenIndex.RemoveAtSwap(RandInd);
        }

        if (ChooseIndex != -1)
        {
            MazeTable.MazeData[CurrentIndex].OpenList.Add(ChooseIndex);
            MazeTable.MazeData[ChooseIndex].OpenList.Add(CurrentIndex);

            MazeTable.MazeData[ChooseIndex].ParentIndex = CurrentIndex;
            MazeTable.MazeData[ChooseIndex].WalkCount = MazeTable.MazeData[CurrentIndex].WalkCount + 1;

            CurrentIndex = ChooseIndex;
        }
        else
        {
            if (MazeTable.MazeData[CurrentIndex].OpenList.Num() == 1)
            {
                MazeTable.DeadEnd.Add(CurrentIndex);
            }

            if (MazeTable.MazeData[CurrentIndex].ParentIndex != -1)
            {
                CurrentIndex = MazeTable.MazeData[CurrentIndex].ParentIndex;
            }
            else if (UnVisit.Num() != 0)
            {
                // Get First Item In List
                for (const int32 Item : UnVisit)
                {
                    CurrentIndex = Item;

                    break;
                }
            }
        }
    }

    return true;
}
