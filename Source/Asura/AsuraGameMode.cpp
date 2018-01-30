// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AsuraGameMode.h"
#include "AsuraPlayerController.h"
#include "AsuraCharacter.h"
#include "UObject/ConstructorHelpers.h"

// NOTE: MAXPRO: We want the inital setup to be in the menus.
#include "AsuraPlayerControllerMenus.h"
#include "AsuraMenuPawn.h"
#include "AsuraPlayerHUD.h"
#include "AsuraPlayerState.h"
#include "AsuraGameState.h"


AAsuraGameMode::AAsuraGameMode()
{
	// use our custom PlayerController class
	//PlayerControllerClass = AAsuraPlayerController::StaticClass();
	PlayerControllerClass = AAsuraPlayerController::StaticClass();
	//DefaultPawnClass = AAsuraMenuPawn::StaticClass();
	//HUDClass = AAsuraPlayerHUD::StaticClass();
	PlayerStateClass = AAsuraPlayerState::StaticClass();
	//GameStateClass = AAsuraGameState::StaticClass();

	
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Classes/MarauderCharacter_BP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;

	}

	static ConstructorHelpers::FClassFinder<AAsuraPlayerHUD> PlayerHUDBPClass(TEXT("/Game/CoreGameplayBlueprints/AsuraPlayerHUD_BP"));
	if (PlayerHUDBPClass.Class != NULL)
	{
		HUDClass = PlayerHUDBPClass.Class;

	}


}