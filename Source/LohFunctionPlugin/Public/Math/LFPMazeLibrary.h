// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)


#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LFPMazeLibrary.generated.h"


UENUM(BlueprintType)
enum class EMazeCellType : uint8
{
	Maze_Open	UMETA(DisplayName = "Open"),
	Maze_Close	UMETA(DisplayName = "Close"),
	Maze_Room	UMETA(DisplayName = "Room"),
};

USTRUCT(BlueprintType)
struct FLFPMazeData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPMazeData")
		int32 WalkCount = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPMazeData")
		int32 ParentIndex = -1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPMazeData")
		TArray<int32> OpenList;
};

USTRUCT(BlueprintType)
struct FLFPMazeStartData
{
	GENERATED_USTRUCT_BODY()

	FLFPMazeStartData() {}
	FLFPMazeStartData(const FIntVector Loc, const TArray<int32>& Open) : GraphLocation(Loc), OpenConnection(Open) {}
	FLFPMazeStartData(const FIntVector Loc, const TArray<int32>& Open, EMazeCellType Type) : GraphLocation(Loc), OpenConnection(Open), CellType(Type) {}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPMazeStartData")
		FIntVector GraphLocation = FIntVector(0);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPMazeStartData")
		TArray<int32> OpenConnection;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPMazeStartData")
		EMazeCellType CellType = EMazeCellType::Maze_Open;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPMazeStartData")
		int32 CellID = 0;
};

USTRUCT(BlueprintType)
struct FLFPMazeTable
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPMazeTable")
		FIntVector MazeSize = FIntVector(0);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LFPMazeTable")
		TArray<FLFPMazeStartData> StartData;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPMazeTable")
		TArray<FLFPMazeData> MazeData;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPMazeTable")
		TArray<int32> DeadEnd;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LFPMazeTable")
		TArray<FIntVector> RoomSize;
};

/**
 * 
 */
UCLASS(meta = (BlueprintThreadSafe))
class LOHFUNCTIONPLUGIN_API ULFPMazeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "LFPMathLibrary | Maze")
		static FLFPMazeTable CreateMazeStartData(const FIntVector MazeSize);

	UFUNCTION(BlueprintCallable, Category = "LFPMathLibrary | Maze")
		static bool GenerateMazeData(UPARAM(Ref) FLFPMazeTable& MazeTable, const TSet<int32>& PreConnection, const FIntPoint RoomExit, const FRandomStream& Seed);

	UFUNCTION(BlueprintCallable, Category = "LFPMathLibrary | Maze")
		static bool RemoveMazeDeadEnd(UPARAM(Ref) FLFPMazeTable& MazeTable, const int32 Amount, const FRandomStream& Seed);

	UFUNCTION(BlueprintCallable, Category = "LFPMathLibrary | Maze")
		static bool GenerateMazeArea(UPARAM(Ref) FLFPMazeTable& MazeTable, const FIntPoint AreaSize, const FRandomStream& Seed);

	UFUNCTION(BlueprintCallable, Category = "LFPMathLibrary | Maze")
		static bool SetMazeCellType(UPARAM(Ref) FLFPMazeTable& MazeTable, const TArray<int32> Indexs, const EMazeCellType Type);

	UFUNCTION(BlueprintCallable, Category = "LFPMathLibrary | Maze")
		static bool SetMazeCellID(UPARAM(Ref) FLFPMazeTable& MazeTable, const TArray<int32> Indexs, const int32 ID);

	UFUNCTION(BlueprintPure, Category = "LFPMathLibrary | Maze")
		static TArray<int32> GetMazeCellNeighbourByType(const FLFPMazeTable& MazeTable, const int32 Index, const EMazeCellType Type);
};
