// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/LFPMarchingWorldSubsystem.h"

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
}

TWeakPtr < FMarchingComputeJob > ULFPMarchingWorldSubsystem::LaunchJob ( const TCHAR* DebugName , const TFunction < void  ( FProgressCancel& Progress ) >& JobWork )
{
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
	if ( PendingJobs.Num ( ) < MaxAsyncJob )
	{
		return UE::Tasks::Launch ( *JobPtr->DebugName ,
		                           [this, JobPtr] ( )
		                           {
			                           JobPtr->JobWork ( *JobPtr->Progress );
			                           JobPtr->bHasCompleted = true;
		                           } ,
		                           LowLevelTasks::ETaskPriority::BackgroundHigh );
	}
	else
	{
		const int32 CurrentReqJobIndex = PendingJobs.Num ( ) % MaxAsyncJob;

		return UE::Tasks::Launch ( *JobPtr->DebugName ,
		                           [this, JobPtr] ( )
		                           {
			                           JobPtr->JobWork ( *JobPtr->Progress );
			                           JobPtr->bHasCompleted = true;
		                           } ,
		                           PendingJobs [ CurrentReqJobIndex ]->Task ,
		                           LowLevelTasks::ETaskPriority::BackgroundHigh );
	}
}
