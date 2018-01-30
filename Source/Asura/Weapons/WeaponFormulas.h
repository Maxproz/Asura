// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WeaponFormulas.generated.h"


const double EulerE = 2.71828;

/**
 * 
 */
UCLASS()
class ASURA_API UWeaponFormulas : public UObject
{
	GENERATED_BODY()
	

public:
	
	// https://www.vcalc.com/wiki/vCalc/Weapon+Physical+DPS+Calculator
	UFUNCTION(Category = "Combat")
	static double GetWeaponPhysicalDPS(const uint32& MinPhysDmg, const uint32& MaxPhysDmg, const double& AttackSpeed)
	{
		double WeapPhysDPS = ((MinPhysDmg + MaxPhysDmg) / 2) * AttackSpeed;
		return WeapPhysDPS;
	}

	// TODO: MAXPRO: Add calulation that includes chaos dmg
	// https://www.vcalc.com/wiki/vCalc/Weapon+Elemental+DPS
	UFUNCTION(Category = "Combat")
	static double GetWeaponTotalDPS(const uint32& MinPhysDmg, const uint32& MaxPhysDmg,
		const uint32& MinFireDmg, const uint32& MaxFireDmg, 
		const uint32& MinColdDmg, const uint32& MaxColdDmg, 
		const uint32& MinLightningDmg, const uint32& MaxLightningDmg,
		const double& AttackSpeed)
	{
		double WeapTotalDPS = ((MinPhysDmg + MinColdDmg + MinFireDmg + MinLightningDmg 
			+ MaxPhysDmg + MaxFireDmg + MaxColdDmg + MaxLightningDmg) / 2) * AttackSpeed;
		return WeapTotalDPS;

	}
	
	// http://poecraft.com/article/5/defenses-armour
	UFUNCTION(Category = "Combat")
	static double GetPhysicalDmgReduction(const uint32& Armour, const uint32& PhysicalDamage)
	{
		// PhyscialDamageReduction is returned as a percentage
		double PhysDmgRed = ((Armour) / Armour + 10 * PhysicalDamage);
		return PhysDmgRed; // %
	}

	// https://pathofexile.gamepedia.com/Monster_damage
	UFUNCTION(Category = "Combat")
	static double GetMonsterDamage(const uint32& MonsterLevel)
	{
		double MonsterDamage = 17.16117 * pow(EulerE, (0.0495 * MonsterLevel)) - 13.1;
		return MonsterDamage; // %
	}

	// Accuracy Evasion Formulas are described in the link below, are used in the following 4 functions.
	// https://docs.google.com/spreadsheets/d/1kCeAy43G3LiL0NMFVEgrLy0Uf1DXMjuyx_-7hRq47y4/edit#gid=8
	UFUNCTION(Category = "Combat")
	static double GetAttackersChanceToHit(const double& AttackersAccuracy, const double& DefendersEvasion)
	{
		double AttackersChanceToHit = AttackersAccuracy / (AttackersAccuracy + (pow(DefendersEvasion / 4, 0.8)));
		return AttackersChanceToHit; // %
	}

	UFUNCTION(Category = "Combat")
	static double GetAttackersAccuracy(const double& AttackersChanceToHit, const double& DefendersEvasion)
	{
		double AttackersAccuracy = (AttackersChanceToHit * ((pow(DefendersEvasion / 4, 0.8)))) / 1 - AttackersChanceToHit;
		return AttackersAccuracy; // %
	}

	UFUNCTION(Category = "Combat")
	static double GetDefendersChanceToEvade(const double& AttackersAccuracy, const double& DefendersEvasion)
	{
		double DefendersChanceToEvade = 1 - (AttackersAccuracy /
			(AttackersAccuracy + ((pow(DefendersEvasion / 4, 0.8)))));
		
		return DefendersChanceToEvade; // %
	}

	UFUNCTION(Category = "Combat")
	static double GetDefendersEvasion(const double& AttackersAccuracy, const double& DefendersChanceToEvade)
	{
		double DefendersEvasion = 4 * (pow(((AttackersAccuracy * DefendersChanceToEvade) /
			(1 - DefendersChanceToEvade)), 1.25));
		return DefendersEvasion; // %
	}


};
