// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapons/WeaponFormulas.h"

#include "AsuraCharacter.generated.h"



// TODO: MAXPRO: Temp variables for testing move them later
// https://docs.google.com/spreadsheets/d/1kCeAy43G3LiL0NMFVEgrLy0Uf1DXMjuyx_-7hRq47y4/edit#gid=17
const double MonsterAverageAccuracyAtLevelOne = 18.0;

// https://docs.google.com/spreadsheets/d/1kCeAy43G3LiL0NMFVEgrLy0Uf1DXMjuyx_-7hRq47y4/edit#gid=1
const double MonsterAverageEvasionAtLevelOne = 36.0;

/* Extended version of power function that can work
for float x and negative y*/
//#include<stdio.h>




inline float power(double x, int y)
{
	float temp;
	if (y == 0)
		return 1;
	temp = power(x, y / 2);
	if (y % 2 == 0)
		return temp*temp;
	else
	{
		if (y > 0)
			return x*temp*temp;
		else
			return (temp*temp) / x;
	}
}

UCLASS(abstract)
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
	uint64 TotalExperience = 0; // Player Starts at 0 exp
	//uint64 ExperienceToGain = 525; // 525 experience to level 2

	// Experience Map
	TMap<uint32, uint64> ExperienceToGainToNextLevel;

	void InitializeExpToGainMap();


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
	int32 EvasionRating = BaseEvasionRating; // gains 3 additional evasion rating per level.

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

	// TODO: MAXPRO: Verify this functionality and usefulness later.

	double DamagePerSecond = 0;
	
	// https://pathofexile.gamepedia.com/Accuracy#Mechanics
	double ChanceToHit = 0; // % can never be lower than 5% or higher than 95%

	void UpdateChanceToHit()
	{
		double UpdatedChanceToHit = 0;

		// Temp code , reinforce how we read the current monster level matching player level data later
		if (Level == 1)
		{
			double AttackersAccuracy = AccuracyRating;
			double DefendersEvasion = MonsterAverageEvasionAtLevelOne;
			
			UpdatedChanceToHit = UWeaponFormulas::GetAttackersChanceToHit(AttackersAccuracy, DefendersEvasion);

			//UpdatedChanceToHit =
			//	AttackersAccuracy / (AttackersAccuracy + (power(DefendersEvasion / 4, 0.8)));
		}

		ChanceToHit = UpdatedChanceToHit;
	}

	// https://pathofexile.gamepedia.com/Evasion
	double ChanceToEvade = 0;
	
	// TODO: MAXPRO: There is a more advanced system currently unimplemented involivng an entropy counter aoe on monsters.
	void UpdateChanceToEvade()
	{
		double UpdatedChanceToEvade = 0;

		// Temp code , reinforce how we read the current monster level matching player level data later
		if (Level == 1)
		{
			
			double AttackersAccuracy = MonsterAverageAccuracyAtLevelOne;
			double DefendersEvasion = EvasionRating;

			UpdatedChanceToEvade = UWeaponFormulas::GetDefendersChanceToEvade(AttackersAccuracy, DefendersEvasion);
			//UpdatedChanceToEvade =
			//	 1 - (AttackersAccuracy / (AttackersAccuracy + (power(DefendersEvasion / 4, 0.8))));
		}

		ChanceToEvade = UpdatedChanceToEvade;
	}

	double MainHandAttacksPerSecond = 1.2; // Same for all classes as of patch 2.1.1d
	uint32 MainHandMinPhysicalDamage = 2;
	uint32 MainHandMaxPhysicalDamage = 8;
	// TODO: MAXPRO: Add elemental damages later on.
	double MainHandAccuracyRating = 28;
	double MainHandCriticalStrikeDamageMultiplier = BaseCriticalStrikeMultiplier; // all classes start with base 150%

	int16 EnduranceCharges = 0;
	int16 MaxEnduranceCharges = BaseMaximumEnduranceCharges; // base starting is 3 can be increased later

	int16 FrenzyCharges = 0;
	int16 MaxFrenzyCharges = BaseMaximumFrenzyCharges; // base starting is 3 can be increased later

	int16 PowerCharges = 0;
	int16 MaxPowerCharges = BaseMaximumPowerCharges; // base starting is 3 can be increased later

	// TODO: MAXPRO: Add functionality to update the resitances based on event/gear changes later.
	int32 FireResistance = 0;
	int32 ColdResistance = 0;
	int32 LightningResistance = 0;
	int32 ChaosResistance = 0;

	


	// More info here - https://www.pathofexile.com/forum/view-thread/529328/page/1#p4775019
	double ManaRegenPerSecond = 0;
	void UpdateManaRegenPerSecond()
	{
		// Example:
		// With 995 mana, we have 17.4215 mana regen per second(995 * 1.75 / 100).
		// This base regeneration is 100 % , but we have 180 % total mana regeneration from skills, 
		// so we have 17.4215 x 1.80.This equals 31.3425 or your 31.4 mana regen.

		// TODO: MAXPRO:
		// Until we have mana regeneration gear we can just use the basic formula and modify it later.

		double UpdatedManaRegenPerSecond = ((Mana * BaseManaRegenPerSecond) / 100);

		ManaRegenPerSecond = UpdatedManaRegenPerSecond;
	}




	// ************************************* ATTACK BONUSES ************************************* 
	double MeleePhysicalDamage = 0; // %; 


	// *************************************  MINOR CHARACTER BASE STATS *************************************
	// (These are stats that all of the characters will share and will derive from this class)

	const double BaseManaRegenPerSecond = 1.75; //  % of Mana Regenerated per second

	const double BaseEnergyShieldRechargedPerSecond = 20.0; // % of Energy Shield Recharged per second

	const int32 BaseEvasionRating = 56; // 53 + 3 per level so 56 at level 1

	// CRITICAL STRIKE MULTIPLIER
	// Critical strikes deal more damage than normal, based on critical strike multiplier.
	// All characters have a base critical strike multiplier of 150%
	// The damage will be multiplied according to
	// CriticalStrikeDamage = Damage * (BaseCriticalStrikeMultiplier + AdditionalCriticalStrikeMultiplier)
	const uint32 BaseCriticalStrikeMultiplier = 150;


	// ************************************* DUAL WIELD (far from implemented) *************************************
	const double BaseBonusToAttackSpeedWhileDualWielding = 10.0; // % more Attack Speed while Dual Wielding
	const double BaseBonusToBlockChanceWhileDualWielding = 15.0; // % additional Block Chance while Dual Wielding
	const double BaseBonusToPhysicalAttackDamageWhileDualWielding = 20.0; // % more Attack Physical Damage while Dual Wielding

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


	// ************************************* PvP *************************************
	const double LessShieldDamageInPvP = 15.0; // % NOTE: pvp future is uncertain at the moment.




protected:

	// These functions should be pure virtual but looking at how you have to use a macro is annoying for now.
	// These functions will be called in the constructor of all of the derived classes, each setting their specific values.
	void SetStartingStrength(const uint16& StartingStrength) { Strength = StartingStrength; };
	void SetStartingDexterity(const uint16& StartingDexterity) { Dexterity = StartingDexterity; };
	void SetStartingIntelligence(const uint16& StartingIntelligence) { Intelligence = StartingIntelligence; };
	void UpdateStartingAccuracyRating() // This should only be called after the dexterity has been set
	{
		if (AccuracyRating == 1)
			UE_LOG(LogTemp, Warning, TEXT("The Dexterity was not set before trying to update the starting accuracy rating"));
		
		AccuracyRating = Dexterity * 2;
	}

	// We need a function that we can call that will update the stat values whenever necessary. 
	// For Example gear changes, level up, etc.. these will all impact the health and mana because of how 
	// the strength and intelligence values impact them.
	// TODO: MAXPRO: Later on we should change this using a delgate and adding the different functions to it that modify
	// the attributes in any way.
	// This function should also be called when the new character subclass is constructed 
	// to take into account the variable difference between the character classes.
	void OnAttributesChanged();

	void OnLevelUp();

	virtual void SetStartingStats(const uint16& STR, const uint16& DEX, const uint16& INT) PURE_VIRTUAL(AAsuraCharacter::SetStartingStats, ; );


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

