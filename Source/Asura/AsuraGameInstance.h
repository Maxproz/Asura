// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Runtime/Core/Public/Containers/Ticker.h"

#include "AsuraGameInstance.generated.h"


namespace AsuraGameInstanceState
{
	extern const FName None;
	extern const FName MainMenu;
	extern const FName CharacterSelectScreen;
	extern const FName Playing;
}

/**
 * 
 */
UCLASS()
class ASURA_API UAsuraGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

	
private:

	//UAsuraGameInstance(const FObjectInitializer& ObjectInitializer);

	FName CurrentState;

	FName PendingState;

	void MaybeChangeState();
	void EndCurrentState(FName NextState);
	void BeginNewState(FName NewState, FName PrevState);

	void BeginMainMenuState();
	//void BeginMessageMenuState();
	//void BeginLobbyState();
	void BeginCharacterSelectionScreenState();
	void BeginPlayingState();

	void EndMainMenuState();
	//void EndMessageMenuState();
	//void EndLobbyState();
	void EndCharacterSelectionScreenState();
	void EndPlayingState();


	/** Delegate for callbacks to Tick */
	FTickerDelegate TickDelegate;

	/** Handle to various registered delegates */
	FDelegateHandle TickDelegateHandle;

protected:

	
public:

	UAsuraGameInstance(const FObjectInitializer & ObjectInitializer);

	bool Tick(float DeltaSeconds);

	virtual void Init() override;
	virtual void StartGameInstance() override;

	FString GetPlayerName() const;

	//Lan player name to not use the Computer Name
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Lan")
	FString LanPlayerName;


	/** Sends the game to the specified state. */
	void GotoState(FName NewState);

	/** Obtains the initial welcome state, which can be different based on platform */
	FName GetInitialState();

	/** Sends the game to the initial startup/frontend state  */
	void GotoInitialState();

};
