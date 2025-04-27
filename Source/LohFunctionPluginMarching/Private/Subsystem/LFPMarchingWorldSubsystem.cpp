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
}

TWeakPtr < FMarchingComputeJob > ULFPMarchingWorldSubsystem::LaunchJob ( const TCHAR* DebugName , const TFunction < void  ( FProgressCancel& Progress ) >& JobWork )
{
	if ( !ensure ( bIsShuttingDown == false ) )
	{
		return TWeakPtr < FMarchingComputeJob > ( );
	}

	// set up the new job
	TSharedPtr < FMarchingComputeJob > NewJob = MakeShared < FMarchingComputeJob > ( );
	FMarchingComputeJob*               JobPtr = NewJob.Get ( );
	NewJob->Progress                          = MakeUnique < FProgressCancel > ( );
	NewJob->Progress->CancelF                 = [this, JobPtr] ( ) { return bIsShuttingDown || JobPtr->bCancelled; };
	NewJob->DebugName                         = DebugName;
	NewJob->JobWork                           = JobWork;

	if ( PendingJobs.Num ( ) < MaxAsyncJob )
	{
		// launch it
		NewJob->Task = LaunchJobInternal ( NewJob.Get ( ) );
	}

	// add a new job
	FScopeLock                       AddJob ( &PendingJobsLock );
	TWeakPtr < FMarchingComputeJob > ResultData = PendingJobs.Add_GetRef ( MoveTemp ( NewJob ) );

	return ResultData;
}

void ULFPMarchingWorldSubsystem::OnJobCompleted ( )
{
	if ( !ensure ( bIsShuttingDown == false ) )
	{
		return;
	}

	FScopeLock RemovePending ( &PendingJobsLock );
	for ( int32 JobIndex = 0 ; JobIndex < PendingJobs.Num ( ) && JobIndex < MaxAsyncJob ; ++JobIndex )
	{
		const TSharedPtr < FMarchingComputeJob >& Job = PendingJobs [ JobIndex ];

		if ( Job->bHasCompleted )
		{
			PendingJobs.RemoveAtSwap ( JobIndex , 1 , EAllowShrinking::No );
			JobIndex -= 1; // rerun the index again to launch the job
		}
		else if ( Job->Task.IsValid ( ) == false )
		{
			// launch it
			Job->Task = LaunchJobInternal ( Job.Get ( ) );
		}
	}
}

UE::Tasks::FTask ULFPMarchingWorldSubsystem::LaunchJobInternal ( FMarchingComputeJob* JobPtr )
{
	return UE::Tasks::Launch ( *JobPtr->DebugName ,
	                           [this, JobPtr] ( )
	                           {
		                           JobPtr->JobWork ( *JobPtr->Progress );
		                           JobPtr->bHasCompleted = true;

		                           AsyncTask (
		                                      ENamedThreads::GameThread ,
		                                      [this] ( )
		                                      {
			                                      if ( IsValid ( this ) == false )
			                                      {
				                                      return;
			                                      }

			                                      if ( bIsShuttingDown == false )
			                                      {
				                                      OnJobCompleted ( );
			                                      }
		                                      }
		                                     );
	                           } ,
	                           LowLevelTasks::ETaskPriority::BackgroundNormal ,
	                           UE::Tasks::EExtendedTaskPriority::None );
}
