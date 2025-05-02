// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/LFPMarchingWorldSubsystem.h"

void ULFPMarchingWorldSubsystem::Initialize ( FSubsystemCollectionBase& Collection )
{
	Super::Initialize ( Collection );
}

void ULFPMarchingWorldSubsystem::Tick ( float DeltaTime )
{
	Super::Tick ( DeltaTime );

	for ( int32 JobIndex = 0 ; GameThreadJobQueue.IsEmpty ( ) == false && JobIndex < 5 ; ++JobIndex )
	{
		TFunction < void  ( ) > GameThreadJob;
		GameThreadJobQueue.Dequeue ( GameThreadJob );

		GameThreadJob ( );
	}
}

void ULFPMarchingWorldSubsystem::Deinitialize ( )
{
	Super::Deinitialize ( );

	bIsShuttingDown = true;
	FScopeLock PendingLock ( &PendingJobsLock );
	for ( int32 k = 0 ; k < PendingJobs.Num ( ) ; ++k )
	{
		UE::Tasks::Wait ( { PendingJobs [ k ]->Task } );
	}

	PendingJobs.Empty ( );
	GameThreadJobQueue.Empty ( );
}

TStatId ULFPMarchingWorldSubsystem::GetStatId ( ) const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT ( ULFPMarchingWorldSubsystem , STATGROUP_Tickables );
}

TWeakPtr < FMarchingComputeJob > ULFPMarchingWorldSubsystem::LaunchJob ( const TCHAR* DebugName , const TFunction < void  ( FProgressCancel& Progress , TQueue < TFunction < void  ( ) > , EQueueMode::Mpsc >& GameThreadJob ) >& JobWork )
{
	check ( IsInGameThread ( ) ); // Must In Game Thread

	if ( !ensure ( bIsShuttingDown == false ) )
	{
		return TWeakPtr < FMarchingComputeJob > ( );
	}

	{
		FScopeLock RemovePending ( &PendingJobsLock );
		for ( int32 JobIndex = 0 ; JobIndex < PendingJobs.Num ( ) ; ++JobIndex )
		{
			if ( const TSharedPtr < FMarchingComputeJob >& Job = PendingJobs [ JobIndex ] ; Job->bHasCompleted )
			{
				PendingJobs.RemoveAtSwap ( JobIndex , 1 , EAllowShrinking::No );
				JobIndex -= 1; // rerun the index again to launch the job
			}
		}
	}

	// set up the new job
	TSharedPtr < FMarchingComputeJob > NewJob = MakeShared < FMarchingComputeJob > ( );
	FMarchingComputeJob*               JobPtr = NewJob.Get ( );
	NewJob->Progress                          = MakeUnique < FProgressCancel > ( );
	NewJob->Progress->CancelF                 = [this, JobPtr] ( ) { return bIsShuttingDown || JobPtr->bCancelled; };
	NewJob->DebugName                         = DebugName;
	NewJob->JobWork                           = JobWork;
	NewJob->Task                              = LaunchJobInternal ( NewJob.Get ( ) );

	// add a new job
	FScopeLock                       AddJob ( &PendingJobsLock );
	TWeakPtr < FMarchingComputeJob > ResultData = PendingJobs.Add_GetRef ( MoveTemp ( NewJob ) );

	return ResultData;
}

UE::Tasks::FTask ULFPMarchingWorldSubsystem::LaunchJobInternal ( FMarchingComputeJob* JobPtr )
{
	return UE::Tasks::Launch ( *JobPtr->DebugName ,
	                           [this, JobPtr] ( )
	                           {
		                           JobPtr->JobWork ( *JobPtr->Progress , GameThreadJobQueue );
		                           JobPtr->bHasCompleted = true;
	                           } ,
	                           LowLevelTasks::ETaskPriority::BackgroundHigh );
}
