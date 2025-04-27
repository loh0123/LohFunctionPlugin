// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Util/ProgressCancel.h"
#include "LFPMarchingWorldSubsystem.generated.h"

struct FMarchingComputeJob
{
	UE::Tasks::FTask               Task;
	TUniquePtr < FProgressCancel > Progress      = nullptr;
	bool                           bCancelled    = false;
	bool                           bHasCompleted = false;

	FString                                           DebugName = "";
	TFunction < void  ( FProgressCancel& Progress ) > JobWork   = nullptr;
};

/**
 * 
 */
UCLASS ( )
class LOHFUNCTIONPLUGINMARCHING_API ULFPMarchingWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY ( )

public:

	virtual void Deinitialize ( ) override;

public:

	TWeakPtr < FMarchingComputeJob > LaunchJob ( const TCHAR* DebugName , const TFunction < void  ( FProgressCancel& Progress ) >& JobWork );

	void OnJobCompleted ( );

protected:

	FORCEINLINE UE::Tasks::FTask LaunchJobInternal ( FMarchingComputeJob* JobPtr );

public:

	uint8 MaxAsyncJob = 32;

	FCriticalSection PendingJobsLock;

	bool bIsShuttingDown = false;

	TArray < TSharedPtr < FMarchingComputeJob > > PendingJobs;
};

struct TAsyncMarchingData
{
	explicit TAsyncMarchingData ( UObject* InOuter ) : Outer ( InOuter )
	{
	}

	~TAsyncMarchingData ( )
	{
		if ( LastPendingJobs.IsValid ( ) )
		{
			TSharedPtr < FMarchingComputeJob > LastJob = LastPendingJobs.Pin ( );
			LastJob->bCancelled                        = true;
			UE::Tasks::Wait ( { LastJob->Task } );
		}
	}

	TWeakPtr < FMarchingComputeJob > LastPendingJobs = nullptr;

	TObjectPtr < UObject > Outer = nullptr;

	void LaunchJob ( const TCHAR* DebugName , const TFunction < void  ( FProgressCancel& Progress ) >& JobWork )
	{
		check ( Outer );

		ULFPMarchingWorldSubsystem* Subsystem = Outer->GetWorld ( )->GetSubsystem < ULFPMarchingWorldSubsystem > ( );

		if ( LastPendingJobs.IsValid ( ) )
		{
			LastPendingJobs.Pin ( )->bCancelled = true;
		}

		LastPendingJobs = Subsystem->LaunchJob ( DebugName , JobWork );
	}
};
