// Copyright by Loh Zhi Kang

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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 WalkCount = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 ParentIndex = -1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<int32> OpenList;
};

USTRUCT(BlueprintType)
struct FLFPMazeStartData
{
	GENERATED_USTRUCT_BODY()

	FLFPMazeStartData() {}
	FLFPMazeStartData(const FIntVector Loc, const TArray<int32>& Open) : GraphLocation(Loc), OpenConnection(Open) {}
	FLFPMazeStartData(const FIntVector Loc, const TArray<int32>& Open, EMazeCellType Type) : GraphLocation(Loc), OpenConnection(Open), CellType(Type) {}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FIntVector GraphLocation = FIntVector(0);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<int32> OpenConnection;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EMazeCellType CellType = EMazeCellType::Maze_Open;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 CellID = 0;
};

USTRUCT(BlueprintType)
struct FLFPMazeTable
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FIntVector MazeSize = FIntVector(0);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FLFPMazeStartData> StartData;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		TArray<FLFPMazeData> MazeData;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		TArray<int32> DeadEnd;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
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
