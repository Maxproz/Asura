// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AsuraCharacter.h"
#include "MarauderCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ASURA_API AMarauderCharacter : public AAsuraCharacter
{
	GENERATED_BODY()
	
private:

	AMarauderCharacter();


protected:

	void SetStartingStats(const uint16& STR, const uint16& DEX, const uint16& INT) override;

public:


	
	
};
