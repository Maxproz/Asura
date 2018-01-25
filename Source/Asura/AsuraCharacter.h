// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AsuraCharacter.generated.h"

UCLASS(Blueprintable)
class AAsuraCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAsuraCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

// protected: // TODO: Maxpro: Can I use protected for at least some of these? test later


	// *************************************  MAJOR CHARACTER STATS *************************************
	uint32 Level = 1; // (All Characters start at level 1.
	uint32 PassiveSkillPoints = 0; // (characters dont get passive skill points until they at least reach lvl 2)
	
	// The following stats are the same for all new characters, and gain the same amount per level.
	// Characters start with different accuracy ratings, but all gain 2 base accuracy per level.

	// NOTE: MAXPRO: Setting this to signed just so we have some padding when the player dies and we dont get unexpected behaviour
	int32 Life = 50; // gains 12 additional life per level
	uint32 Mana = 40; // gains 6 additional mana per level
	int32 MaximumEnergyShield = 0; // (Will be changed depending on other sub classes intelligence value combined with energy shield gear)
	// More stats that can be set in the individual character derived classes
	int32 AccuracyRating = 1; // Determined by the derived characters dex
	// Every point of Dexterity gives 2 additional base accuracy, and characters gain 2 base accuracy when leveling up.
	int32 EvasionRating = 53; // gains 3 additional evasion rating per level.

	// *************************************  END *************************************

	// ************************************* ATTRIBUTES ************************************* 
	// All classes have a starting total of 60 attributes of different weights,
	// based on their alignment on the passive tree.The Scion starts with 20 of each attribute.
	
	// These will be set per derived character class. (They should never go negative or zero)
	uint32 Strength = 1;
	// Every 2 Strength is +1 to life 
	// Every 5 Strength is +1% Melee Physical Damage 

	uint32 Dexterity = 1;
	// Every 1 Dexterity = +2 Accuracy
	// Every 5 Dexterity = +1% Evasion

	uint32 Intelligence = 1;
	// Every 2 Intelligence = +1 Mana
	// Every 5 Intelligence = +1% Energy Shield

	// *************************************  END *************************************

	// ************************************* ATTACK BONUSES ************************************* 
	double MeleePhysicalDamage = 0; // %; 


	// *************************************  END *************************************

	// *************************************  MINOR CHARACTER BASE STATS *************************************
	// (These are stats that all of the characters will share and will derive from this class)

	const double BaseManaRegenPerSecond = 1.75; //  % of Mana Regenerated per second

	const double BaseEnergyShieldRechargedPerSecond = 20.0; // % of Energy Shield Recharged per second

	const int32 BaseEvasionRating = 53;

	// CRITICAL STRIKE MULTIPLIER
	// Critical strikes deal more damage than normal, based on critical strike multiplier.
	// All characters have a base critical strike multiplier of 150%
	// The damage will be multiplied according to
	// CriticalStrikeDamage = Damage * (BaseCriticalStrikeMultiplier + AdditionalCriticalStrikeMultiplier)
	const uint32 BaseCriticalStrikeMultiplier = 150;

	// *************************************  END *************************************

	// ************************************* DUAL WIELD (far from implemented) *************************************
	const double BaseBonusToAttackSpeedWhileDualWielding = 10.0; // % more Attack Speed while Dual Wielding
	const double BaseBonusToBlockChanceWhileDualWielding = 15.0; // % additional Block Chance while Dual Wielding
	const double BaseBonusToPhysicalAttackDamageWhileDualWielding = 20.0; // % more Attack Physical Damage while Dual Wielding

	// *************************************  END *************************************

	// ************************************* CHARGES *************************************
	// RAMPAGE FUNCTIONALITY (UNIMPLEMENTED)
	// TODO: Maybe rework the following into a charges class that this character class and the derives will use?
	const int16 BaseMaximumEnduranceCharges = 3;
	const int16 BaseMaximumFrenzyCharges = 3;
	const int16 BaseMaximumPowerCharges = 3;

	// endurance charge bonus's
	const double PhysicalDamageReductionPerEnduranceCharge = 4; // %
	const double BonusToAllElementalResistancesPerEnduranceCharge = 4; // %

	// Frenzy charge bonus's
	const double BonusToAttackSpeedPerFrenzyCharge = 4; // %
	const double BonusToCastSpeedPerFrenzyCharge = 4; // %
	const double BonusToDamagePerFrenzyCharge = 4; // %

	// Power charge bonus's
	const double BonusToCriticalStrikeChancePerPowerCharge = 40; // %

	// *************************************  END *************************************


	// ************************************* MAXIMUMS *************************************
	const double PercentOfMaximumLifePerSecondToMaximumLifeLeechRate = 20.0; // %
	const double PercentOfMaximumManaPerSecondToMaximumManaLeechRate = 20.0; // %

	const double BonusToMaximumBlockChance = 75.0; // %

	const double BonusToMaximumChaosResistance = 75.0; // %
	const double BonusToMaximumColdResistance = 75.0; // %
	const double BonusToMaximumFireResistance = 75.0; // %
	const double BonusToMaximumLightningResistance = 75.0; // %

	const uint16 BonusToMaximumAllowedCorruptedBloodRainStacks = 20;
	const uint16 BonusToMaximumAllowedCorruptedBloodStacks = 20;
	const uint16 BonusToMaximumAllowedExplosiveArrowStacks = 5;

	const double BonusToMaximumDodgeChance = 75.0; // %
	const double BonusToMaximumSpellDodgeChance = 75.0; // %

	const double BonusToMaximumPhysicalDamageReduction = 90.0; // %

	const uint16 BonusToMaximumAmountOfTrapsAtATime = 3;
	const uint16 BonusToMaximumAmountOfRemoteMinesAtATime = 5;

	const uint16 BonusToMaximumAmountOfTotemsAtATime = 1;

	// *************************************  END *************************************

	// ************************************* PvP *************************************
	const double LessShieldDamageInPvP = 15.0; // % NOTE: pvp future is uncertain at the moment.

	// *************************************  END *************************************





protected:

	// These functions should be pure virtual but looking at how you have to use a macro is annoying for now.
	// These functions will be called in the constructor of all of the derived classes, each setting their specific values.
	void SetStartingStrength(const uint16& StartingStrength) { Strength = StartingStrength; };
	void SetStartingDexterity(const uint16& StartingDexterity) { Dexterity = StartingDexterity; };
	void SetStartingIntelligence(const uint16& StartingIntelligence) { Intelligence = StartingIntelligence; };

	// We need a function that we can call that will update the stat values whenever necessary. 
	// For Example gear changes, level up, etc.. these will all impact the health and mana because of how 
	// the strength and intelligence values impact them.
	// TODO: MAXPRO: Later on we should change this using a delgate and adding the different functions to it that modify
	// the attributes in any way.
	// This function should also be called when the new character subclass is constructed 
	// to take into account the variable difference between the character classes.
	void OnAttributesChanged();

	void OnLevelUp();



private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;



};

