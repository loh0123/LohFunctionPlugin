#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LFPMarchingLibrary.generated.h"

UCLASS()
class LOHFUNCTIONPLUGIN_API ULFPMarchingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION( BlueprintPure , Category = "LFPMarchingLibrary | ID" )
	static bool GetMarchingIDBit( const uint8 MarchingID , const int32 BitIndex );

	UFUNCTION( BlueprintCallable , Category = "LFPMarchingLibrary | ID" )
	static void SetMarchingIDBit( uint8& MarchingID , const int32 BitIndex , const bool bNewValue );

public:

	UFUNCTION( BlueprintCallable , Category = "LFPMarchingLibrary | Rotation" )
	static uint8 RotateMarchingIDByX( const uint8 MarchingID , const bool bReverse );

	UFUNCTION( BlueprintCallable , Category = "LFPMarchingLibrary | Rotation" )
	static uint8 RotateMarchingIDByY( const uint8 MarchingID , const bool bReverse );

	UFUNCTION( BlueprintCallable , Category = "LFPMarchingLibrary | Rotation" )
	static uint8 RotateMarchingIDByZ( const uint8 MarchingID , const bool bReverse );

	UFUNCTION( BlueprintCallable , Category = "LFPMarchingLibrary | Rotation" )
	static uint8 RotateMarchingID( const uint8 MarchingID , const FIntVector& Rotation );

public:

	UFUNCTION( BlueprintCallable , Category = "LFPMarchingLibrary | Function" )
	static uint8 CalculateDualGridMarchingID( const uint8 FullMarchingID , const int32 CalculateIndex );
};
