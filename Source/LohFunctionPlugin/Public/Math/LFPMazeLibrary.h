// MIT License
// 
// Copyright(c) 2022 loh0123
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright noticeand this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
UCLASS()
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
