// Fill out your copyright notice in the Description page of Project Settings.


#include "LFPMultiLevelManager.h"

#include "AudioDevice.h"
#include "IXRTrackingSystem.h"
#include "ShaderCompiler.h"
#include "AI/NavigationSystemBase.h"
#include "Components/ActorComponent.h"

TArray < AActor* > ULFPMultiLevelHandler::GetCaptureActorList ( ) const
{
	TArray < AActor* > ReturnList;

	ReturnList.Reserve ( CaptureActorList.Num ( ) );

	for ( const TObjectPtr < AActor >& CaptureActor : CaptureActorList )
	{
		ReturnList.Add ( CaptureActor );
	}

	return ReturnList;
}

void ULFPMultiLevelManager::Deinitialize ( )
{
	Super::Deinitialize ( );

	for ( TObjectPtr < ULFPMultiLevelHandler >& Handler : MultiLevelHandlerList )
	{
		if ( Handler->LoadedWorld )
		{
			GEngine->DestroyWorldContext ( Handler->LoadedWorld );
		}

		if ( UWorld* HandleWorld = Handler->LoadedWorld ; IsValid ( HandleWorld ) && HandleWorld->bIsTearingDown == false )
		{
			// Notify listeners that all levels will be removed before we start tearing down the world.
			FWorldDelegates::PreLevelRemovedFromWorld.Broadcast ( nullptr , HandleWorld );
			HandleWorld->BeginTearingDown ( );

			// Force mark all streaming levels for stream out
			HandleWorld->bIsLevelStreamingFrozen = false;
			HandleWorld->SetShouldForceUnloadStreamingLevels ( true );

			// Make sure there are no pending visibility requests.
			HandleWorld->FlushLevelStreaming ( EFlushLevelStreamingType::Visibility );

			// send a message that all levels are going away (NULL means every sublevel is being removed
			// without a call to RemoveFromWorld for each)
			//if (WorldContext.World()->GetNumLevels() > 1)
			{
				// TODO: Consider actually broadcasting for each level?
				FWorldDelegates::LevelRemovedFromWorld.Broadcast ( nullptr , HandleWorld );
			}

			HandleWorld->EndPlay ( EEndPlayReason::Destroyed );

			// Do this after destroying pawns/playercontrollers, in case that spawns new things (e.g. dropped weapons)
			HandleWorld->CleanupWorld ( );

			HandleWorld->RemoveFromRoot ( );

			// mark everything else contained in the world to be deleted
			for ( auto LevelIt ( HandleWorld->GetLevelIterator ( ) ) ; LevelIt ; ++LevelIt )
			{
				const ULevel* Level = *LevelIt;
				if ( Level )
				{
					CastChecked < UWorld > ( Level->GetOuter ( ) )->MarkObjectsPendingKill ( );
				}
			}

			for ( ULevelStreaming* LevelStreaming : HandleWorld->GetStreamingLevels ( ) )
			{
				// If an unloaded levelstreaming still has a loaded level we need to mark its objects to be deleted as well
				if ( LevelStreaming->GetLoadedLevel ( ) && ( !LevelStreaming->ShouldBeLoaded ( ) || !LevelStreaming->ShouldBeVisible ( ) ) )
				{
					CastChecked < UWorld > ( LevelStreaming->GetLoadedLevel ( )->GetOuter ( ) )->MarkObjectsPendingKill ( );
				}
			}

			// Stop all audio to remove references to current level.
			if ( FAudioDevice* AudioDevice = HandleWorld->GetAudioDeviceRaw ( ) )
			{
				AudioDevice->Flush ( HandleWorld );
				AudioDevice->SetTransientPrimaryVolume ( 1.0f );
			}
		}
	}

	MultiLevelHandlerList.Empty ( );
}

void ULFPMultiLevelManager::Initialize ( FSubsystemCollectionBase& Collection )
{
	Super::Initialize ( Collection );
}

ULFPMultiLevelHandler* ULFPMultiLevelManager::LoadMultiLevel ( const TSoftObjectPtr < UWorld > Level )
{
	FWorldContext& OriginWorldContext = GEngine->GetWorldContextFromWorldChecked ( GetWorld ( ) );
	FWorldContext& WorldContext       = GEngine->CreateNewWorldContext ( OriginWorldContext.WorldType );

	FString TravelURL = FPackageName::ObjectPathToPackageName ( Level.ToString ( ) );
	FURL    URL       = FURL ( nullptr , *TravelURL , TRAVEL_Absolute );

	const FString OriginalURLMap = URL.Map;
	URL.Map                      = UWorld::RemovePIEPrefix ( URL.Map );

	// send a callback message
	FCoreUObjectDelegates::PreLoadMapWithContext.Broadcast ( WorldContext , URL.Map );
	FCoreUObjectDelegates::PreLoadMap.Broadcast ( URL.Map );

	double StartTime = FPlatformTime::Seconds ( );

	// make sure there is a matching PostLoadMap() no matter how we exit
	struct FPostLoadMapCaller
	{
		FPostLoadMapCaller ( ) : bCalled ( false )
		{
		}

		~FPostLoadMapCaller ( )
		{
			if ( !bCalled )
			{
				FCoreUObjectDelegates::PostLoadMapWithWorld.Broadcast ( nullptr );
			}
		}

		void Broadcast ( UWorld* World )
		{
			if ( ensure ( !bCalled ) )
			{
				bCalled = true;
				FCoreUObjectDelegates::PostLoadMapWithWorld.Broadcast ( World );
			}
		}

	private:

		bool bCalled;
	} PostLoadMapCaller;

	UPackage* WorldPackage = nullptr;
	UWorld*   NewWorld     = nullptr;
	{
		// Set the world type in the static map, so that UWorld::PostLoad can set the world type
		const FName URLMapFName                               = FName ( *URL.Map );
		UWorld::WorldTypePreLoadMap.FindOrAdd ( URLMapFName ) = EWorldType::Game;
		{
			// See if the level is already in memory
			WorldPackage = FindPackage ( nullptr , *URL.Map );

			bool bPackageAlreadyLoaded = ( WorldPackage != nullptr );

			// If the level isn't already in memory, load level from disk
			if ( WorldPackage == nullptr )
			{
				WorldPackage = LoadPackage ( nullptr , *URL.Map , LOAD_None );
			}
		}
		// Clean up the world type list now that PostLoad has occurred
		UWorld::WorldTypePreLoadMap.Remove ( URLMapFName );

		if ( WorldPackage == nullptr )
		{
			// it is now the responsibility of the caller to deal with a NULL return value and alert the user if necessary
			return nullptr;
		}

		// Find the newly loaded world.
		NewWorld = UWorld::FindWorldInPackage ( WorldPackage );

		// If the world was not found, it could be a redirector to a world. If so, follow it to the destination world.
		if ( !NewWorld )
		{
			NewWorld = UWorld::FollowWorldRedirectorInPackage ( WorldPackage );
			if ( NewWorld )
			{
				// Treat this as an already loaded package because we were loaded by the redirector
				WorldPackage = NewWorld->GetOutermost ( );
			}
		}

		// This can still be null if the package name is ambiguous, for example if there exists a umap and uasset with the same
		// name.
		if ( NewWorld == nullptr )
		{
			// it is now the responsibility of the caller to deal with a NULL return value and alert the user if necessary
			return nullptr;
		}


		NewWorld->PersistentLevel->HandleLegacyMapBuildData ( );


		ULFPMultiLevelHandler* NewHandler = NewObject < ULFPMultiLevelHandler > ( this );

		NewHandler->LoadedWorld = NewWorld;

		MultiLevelHandlerList.Add ( NewHandler );

		NewWorld->SetGameInstance ( GetWorld ( )->GetGameInstance ( ) );
		NewWorld->WorldType = WorldContext.WorldType;

		WorldContext.SetCurrentWorld ( NewWorld );
		WorldContext.LastURL      = URL;
		WorldContext.GameViewport = OriginWorldContext.GameViewport;

		WorldContext.OwningGameInstance = GetWorld ( )->GetGameInstance ( );

		{
			WorldContext.World ( )->AddToRoot ( );

			// The world should not have been initialized before this
			if ( ensure ( !WorldContext.World ( )->bIsWorldInitialized ) )
			{
				WorldContext.World ( )->InitWorld ( );
			}
		}

		WorldContext.World ( )->SetGameMode ( URL );

		// Process global shader results before we try to render anything
		// Do this before we register components, as USkinnedMeshComponents require the GPU skin cache global shaders when creating render state.
		if ( GShaderCompilingManager )
		{
			GShaderCompilingManager->ProcessAsyncResults ( false , true );
		}

		{
			DECLARE_SCOPE_CYCLE_COUNTER ( TEXT("LFPMultiLevelManager::LoadMultiMap.LoadPackagesFully") , STAT_LoadMap_LoadPackagesFully , STATGROUP_LoadTime );

			// load any per-map packages
			check ( WorldContext.World()->PersistentLevel );
			GEngine->LoadPackagesFully ( WorldContext.World ( ) , FULLYLOAD_Map , WorldContext.World ( )->PersistentLevel->GetOutermost ( )->GetName ( ) );

			// Make sure "always loaded" sub-levels are fully loaded
			WorldContext.World ( )->FlushLevelStreaming ( EFlushLevelStreamingType::Visibility );

			if ( !GIsEditor && !IsRunningDedicatedServer ( ) )
			{
				// If requested, duplicate dynamic levels here after the source levels are created.
				WorldContext.World ( )->DuplicateRequestedLevels ( FName ( *URL.Map ) );
			}
		}

		// Note that AI system will be created only if ai-system-creation conditions are met
		WorldContext.World ( )->CreateAISystem ( );

		// Initialize gameplay for the level.
		{
			FRegisterComponentContext Context ( WorldContext.World ( ) );
			WorldContext.World ( )->InitializeActorsForPlay ( URL , true , &Context );
		}

		// calling it after InitializeActorsForPlay has been called to have all potential bounding boxed initialized
		FNavigationSystem::AddNavigationSystemToWorld ( *WorldContext.World ( ) , FNavigationSystemRunMode::GameMode );

		if ( GEngine && GEngine->XRSystem.IsValid ( ) )
		{
			GEngine->XRSystem->OnBeginPlay ( WorldContext );
		}
		WorldContext.World ( )->BeginPlay ( );

		PostLoadMapCaller.Broadcast ( WorldContext.World ( ) );

		WorldContext.World ( )->bWorldWasLoadedThisTick = true;

		double StopTime = FPlatformTime::Seconds ( );

		UE_LOG ( LogLoad , Log , TEXT("Took %f seconds to LoadMap(%s)") , StopTime - StartTime , *URL.Map );
		WorldContext.OwningGameInstance->LoadComplete ( StopTime - StartTime , *URL.Map );

		// Successfully started local level.
		UE_LOGSTATUS ( Log , TEXT("Load map complete %s") , *URL.Map );

		// Capture Actor Inside World
		{
			for ( ULevel* WorldLevel : WorldContext.World ( )->GetLevels ( ) )
			{
				for ( const TObjectPtr < AActor >& LevelActor : WorldLevel->Actors )
				{
					if ( IsValid ( LevelActor ) && LevelActor->ActorHasTag ( "WorldCaptureActor" ) )
					{
						NewHandler->CaptureActorList.Add ( LevelActor );
					}
				}
			}
		}

		return NewHandler;
	}
}
