// Fill out your copyright notice in the Description page of Project Settings.

#include "AsuraGameInstance.h"


namespace AsuraGameInstanceState
{
	const FName None = FName(TEXT("None"));
	const FName MainMenu = FName(TEXT("MainMenu"));
	const FName CharacterSelectScreen = FName(TEXT("CharacterSelectScreen"));
	const FName Playing = FName(TEXT("Playing"));
}

UAsuraGameInstance::UAsuraGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	

	CurrentState = AsuraGameInstanceState::None;
	LanPlayerName = "Player";

}

bool UAsuraGameInstance::Tick(float DeltaSeconds)
{
	// Dedicated server doesn't need to worry about game state
	if (IsRunningDedicatedServer() == true)
	{
		return true;
	}


	MaybeChangeState();


	return true;
}


void UAsuraGameInstance::Init()
{
	Super::Init();
	

	// Register delegate for ticker callback
	TickDelegate = FTickerDelegate::CreateUObject(this, &UAsuraGameInstance::Tick);
	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);
}

FString UAsuraGameInstance::GetPlayerName() const
{
	////if steam is running, return an empty string
	//if (IsOnlineSubsystemSteam())
	//	return "";
	////else retrun the saved player lan name
	//else
		return LanPlayerName;
}

void UAsuraGameInstance::StartGameInstance()
{
	GotoInitialState();

}

FName UAsuraGameInstance::GetInitialState()
{
	// On PC, go directly to the main menu
	return AsuraGameInstanceState::CharacterSelectScreen;
}

void UAsuraGameInstance::GotoInitialState()
{
	GotoState(GetInitialState());
}


void UAsuraGameInstance::GotoState(FName NewState)
{
	UE_LOG(LogTemp, Log, TEXT("GotoState: NewState: %s"), *NewState.ToString());

	PendingState = NewState;
}

void UAsuraGameInstance::MaybeChangeState()
{
	if ((PendingState != CurrentState) && (PendingState != AsuraGameInstanceState::None))
	{
		FName const OldState = CurrentState;

		// end current state
		EndCurrentState(PendingState);

		// begin new state
		BeginNewState(PendingState, OldState);

		// clear pending change
		PendingState = AsuraGameInstanceState::None;
	}
}

void UAsuraGameInstance::EndCurrentState(FName NextState)
{
	// per-state custom ending code here
	if (CurrentState == AsuraGameInstanceState::MainMenu)
	{
		EndMainMenuState();
	}
	else if (CurrentState == AsuraGameInstanceState::CharacterSelectScreen)
	{
		EndCharacterSelectionScreenState();
	}
	else if (CurrentState == AsuraGameInstanceState::Playing)
	{
		EndPlayingState();
	}

	CurrentState = AsuraGameInstanceState::None;
}

void UAsuraGameInstance::BeginNewState(FName NewState, FName PrevState)
{
	// per-state custom starting code here
	if (NewState == AsuraGameInstanceState::MainMenu)
	{
		BeginMainMenuState();
	}
	else if (NewState == AsuraGameInstanceState::CharacterSelectScreen)
	{
		BeginCharacterSelectionScreenState();
	}
	else if (NewState == AsuraGameInstanceState::Playing)
	{
		BeginPlayingState();
	}

	CurrentState = NewState;
}

void UAsuraGameInstance::BeginMainMenuState()
{
	//// Set presence to menu state for the owning player
	//SetPresenceForLocalPlayers(FVariantData(FString(TEXT("OnMenu"))));

	//// load startup map
	//LoadFrontEndMap(MainMenuMap);

	//// player 0 gets to own the UI
	//ULocalPlayer* const Player = GetFirstGamePlayer();


	//MainMenuUI = Cast<AFusionPlayerController_Menu>(Player->GetPlayerController(GetWorld()))->GetFusionHUD()->GetMainMenuUIWidget();

	//if (MainMenuUI.IsValid())
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, FString::Printf(TEXT("Showing The Valid Main Menu Widget")));
	//	MainMenuUI.Get()->ShowWidget();
	//}

}

void UAsuraGameInstance::BeginCharacterSelectionScreenState()
{


}

void UAsuraGameInstance::BeginPlayingState()
{

	

	//// Set presence for playing in a map
	//SetPresenceForLocalPlayers(FVariantData(FString(TEXT("InGame"))));

	//// Make sure viewport has focus
	//FSlateApplication::Get().SetAllUserFocusToGameViewport(); // TODO: Figure out if I need this later on.
}

void UAsuraGameInstance::EndMainMenuState()
{

	//if (MainMenuUI.IsValid())
	//{
	//	MainMenuUI.Get()->HideWidget();
	//	MainMenuUI = nullptr;
	//}

}

void UAsuraGameInstance::EndCharacterSelectionScreenState()
{

}

void UAsuraGameInstance::EndPlayingState()
{
	//// Clear the players' presence information
	//SetPresenceForLocalPlayers(FVariantData(FString(TEXT("OnMenu"))));

	//UWorld* const World = GetWorld();
	//AFusionGameState* const GameState = World != NULL ? World->GetGameState<AFusionGameState>() : NULL;

	//if (GameState)
	//{
	//	// Send round end events for local players
	//	for (int i = 0; i < LocalPlayers.Num(); ++i)
	//	{
	//		auto FusionPC = Cast<AFusionPlayerController>(LocalPlayers[i]->PlayerController);
	//		if (FusionPC)
	//		{
	//			// Assuming you can't win if you quit early
	//			FusionPC->ClientSendRoundEndEvent(false, GameState->ElapsedTime);
	//		}
	//	}

	//	// Give the game state a chance to cleanup first
	//	GameState->RequestFinishAndExitToMainMenu();
	//}
	//else
	//{
	//	// If there is no game state, make sure the session is in a good state
	//	CleanupSessionOnReturnToMenu();
	//}

}
