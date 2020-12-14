// Copyright Epic Games, Inc. All Rights Reserved.

#include "FinalAssignmentGameMode.h"
#include "FinalAssignmentPlayerController.h"
#include "FinalAssignmentCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFinalAssignmentGameMode::AFinalAssignmentGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AFinalAssignmentPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}