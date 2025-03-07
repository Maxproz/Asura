// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AsuraCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"

#include "AsuraPlayerState.h"
#include "AsuraPlayerController.h"
#include "Kismet/GameplayStatics.h"


AAsuraCharacter::AAsuraCharacter()
{

	InitializeExpToGainMap();

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/Classes/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	//AsuraPlayerState = Cast<AAsuraPlayerState>(UGameplayStatics::GetPlayerController(this->GetWorld(), 0)->PlayerState);
	//AsuraPlayerController = Cast<AAsuraPlayerController>(UGameplayStatics::GetPlayerController(this->GetWorld(), 0));
	//AsuraPlayerState = Cast<AAsuraPlayerState>(AsuraPlayerController->PlayerState);

}

void AAsuraCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (AAsuraPlayerController* PC = Cast<AAsuraPlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

void AAsuraCharacter::InitializeExpToGainMap()
{
	ExperienceToGainToNextLevel.Add(1, 525);
	ExperienceToGainToNextLevel.Add(2, 1235);
	ExperienceToGainToNextLevel.Add(3, 2021);
	ExperienceToGainToNextLevel.Add(4, 3403);
	ExperienceToGainToNextLevel.Add(5, 5002);
	ExperienceToGainToNextLevel.Add(6, 7138);
	ExperienceToGainToNextLevel.Add(7, 10053);
	ExperienceToGainToNextLevel.Add(8, 13804);
	ExperienceToGainToNextLevel.Add(9, 18512);
	ExperienceToGainToNextLevel.Add(10, 24297);

	// TODO: MAXPRO: Fill in the rest later if this system works...
	// https://pathofexile.gamepedia.com/Experience

}


// Need to fix this so when doing integer division and slicing we always round UP to gain stats and never lose potential ones.
void AAsuraCharacter::OnAttributesChanged()
{
	
	// DO STRENGTH
	// Every 2 Strength is +1 to life 
	int32 LifeToAdd = Strength / 2;
	Life = Life + LifeToAdd;

	// Every 5 Strength is +1% Melee Physical Damage
	int32 MeleePhysDamageBonusFromStrength = Strength / 5; // %
	MeleePhysicalDamage = MeleePhysicalDamage + MeleePhysDamageBonusFromStrength;
	
	// DO DEXTERITY
	// Every 1 Dexterity is +2 to accuracy rating
	int32 AccuracyRatingToAdd = Dexterity * 2;
	AccuracyRating = AccuracyRating + AccuracyRatingToAdd;

	// Every 5 Dexterity is +1% evasion rating
	int32 EvasionRatingToAdd = Dexterity / 5;
	EvasionRating = EvasionRating + EvasionRatingToAdd;


	// DO INTELLIGENCE
	// Every 2 Intelligence is +1 to mana 
	int32 ManaToAdd = Intelligence / 2;
	Mana = Mana + ManaToAdd;

	// Every 5 Intelligence is +1% Energy Shield
	int32 EnergyShieldBonusFromIntelligence = Intelligence / 5; // %
	int32 NewMaxEnergyShield = 0;
	int32 AmountOfEnergyShieldToAdd = (EnergyShieldBonusFromIntelligence * MaximumEnergyShield) / 100;

	NewMaxEnergyShield = MaximumEnergyShield + AmountOfEnergyShieldToAdd;
	MaximumEnergyShield = NewMaxEnergyShield;


}

void AAsuraCharacter::OnLevelUp()
{
	Life = Life + 12;
	Mana = Mana + 6;
	EvasionRating = EvasionRating + 3;
	AccuracyRating = AccuracyRating + 2;


}
