// Fill out your copyright notice in the Description page of Project Settings.

#include "MarauderCharacter.h"

const uint32 MarauderStartingStrength = 32;
const uint32 MarauderStartingDexterity = 14;
const uint32 MarauderStartingIntelligence = 14;


AMarauderCharacter::AMarauderCharacter()
{
	SetStartingStats(MarauderStartingStrength, MarauderStartingDexterity, MarauderStartingIntelligence);
	UpdateStartingAccuracyRating();
	OnAttributesChanged(); // We update evasion rating and accuracy here first time, so now we can update the hit/evade.
	UpdateChanceToHit();
	UpdateChanceToEvade();
	UpdateManaRegenPerSecond(); // cannot be called until the players current mana value has been fully updated.


}

// 
void AMarauderCharacter::SetStartingStats(const uint16& STR, const uint16& DEX, const uint16& INT)
{
	SetStartingStrength(STR);
	SetStartingDexterity(DEX);
	SetStartingIntelligence(INT);
}
