// Fill out your copyright notice in the Description page of Project Settings.

#include "AsuraMenuPawn.h"

#include "AsuraPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "AsuraPlayerHUD.h"

// Sets default values
AAsuraMenuPawn::AAsuraMenuPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//AAsuraPlayerController* PlayerCont = Cast<AAsuraPlayerController>(GetController());
	//PlayerCont->PlayerHUD->GetCharacterSelectionUIWidget()->SetIsEnabled(true);
}

// Called when the game starts or when spawned
void AAsuraMenuPawn::BeginPlay()
{
	Super::BeginPlay();
	


}

// Called every frame
void AAsuraMenuPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAsuraMenuPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

