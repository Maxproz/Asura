// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AsuraGameMode.h"
#include "AsuraPlayerController.h"
#include "AsuraCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAsuraGameMode::AAsuraGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AAsuraPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;

	}



}