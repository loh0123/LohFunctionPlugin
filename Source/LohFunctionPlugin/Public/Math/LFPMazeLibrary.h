// Copyright by Loh Zhi Kang

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LFPMazeLibrary.generated.h"


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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FIntVector GraphLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<int32> OpenConnection;
};

USTRUCT(BlueprintType)
struct FLFPMazeTable
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FLFPMazeStartData> StartData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FLFPMazeData> MazeData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<int32> DeadEnd;
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
		static bool GenerateMazeData(UPARAM(Ref) FLFPMazeTable& MazeTable, const FRandomStream& Seed);
};
