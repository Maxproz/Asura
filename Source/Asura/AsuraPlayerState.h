// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AsuraPlayerState.generated.h"

UENUM()
enum class ECharacterClass : uint8
{
	CC_Marauder,
	CC_Ranger,
	CC_Witch,

	// TODO: MAXPRO: Add more later
};


/**
 * 
 */
UCLASS()
class ASURA_API AAsuraPlayerState : public APlayerState
{
	GENERATED_BODY()

private:

	ECharacterClass CurrentSelectedCharacterClass;

protected:

public:

	FORCEINLINE void SetCurrentSelectedCharacterClass(const ECharacterClass& Class) { CurrentSelectedCharacterClass = Class; }

	FORCEINLINE ECharacterClass GetCurrentSelectedCharacterClass() const { return CurrentSelectedCharacterClass; }
	


	
};
