// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterSelectionUI.h"

#include "Runtime/UMG/Public/Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "AsuraPlayerController.h"
#include "AsuraPlayerState.h"
#include "AsuraPlayerHUD.h"

#include "AsuraCharacter.h"
#include "Characters/MarauderCharacter.h"

void UCharacterSelectionUI::NativeConstruct()
{
	Super::NativeConstruct();

	ChooseMarauderBtn->OnClicked.AddDynamic(this, &UCharacterSelectionUI::OnClickedChooseMarauderBtn);

}

void UCharacterSelectionUI::OnClickedChooseMarauderBtn()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("/Game/Levels/TopDownExampleMap"));


	AAsuraPlayerController* PlayerCont = Cast<AAsuraPlayerController>(GetOwningPlayer());
	PlayerCont->AsuraPlayerState->SetCurrentSelectedCharacterClass(ECharacterClass::CC_Marauder);
	PlayerCont->bCharacterSelected = true;



	//UGameplayStatics::OpenLevel(GetWorld(), FName("/Game/Levels/TopDownExampleMap"));
	//GetWorld()->ServerTravel(FString("/Game/Levels/TopDownExampleMap"));
	//GetWorld()->SeamlessTravel(FString("/Game/Levels/TopDownExampleMap"));
	if (PlayerCont->bCharacterSelected == true)
	{
		PlayerCont->bCharacterSelected = false;

		//UGameplayStatics::OpenLevel(GetWorld(), FName("/Game/Levels/TopDownExampleMap"));
		//PlayerCont->ClientTravel(FString("/Game/Levels/TopDownExampleMap"), ETravelType::TRAVEL_Relative, true);

		PlayerCont->AsuraPlayerHUD->GetCharacterSelectionUIWidget()->HideWidget();

		if (PlayerCont->AsuraPlayerState->GetCurrentSelectedCharacterClass() == ECharacterClass::CC_Marauder)
		{


			FTransform DefaultMarauderSpawn = FTransform(FQuat(0, 0, 0, 0), FVector(-900.0025, -10.0, 263.55352));
			AMarauderCharacter* PlayerCurrentCharPawn = GetWorld()->SpawnActor<AMarauderCharacter>(PlayerCont->MarauderClassTemplate,
				DefaultMarauderSpawn);

			//AActor* PlayerChar =
			//UGameplayStatics::BeginSpawningActorFromClass(GetWorld(), MarauderClassTemplate, DefaultMarauderSpawn, true);
			//UGameplayStatics::FinishSpawningActor(PlayerChar, DefaultMarauderSpawn);
			PlayerCont->UnPossess();
			PlayerCont->Possess(Cast<APawn>(PlayerCurrentCharPawn));

			PlayerCont->bCharacterSelected = false;

		}
		else
		{
			FTransform DefaultTestCharSpawn = FTransform(FQuat(0, 0, 0, 0), FVector(-880.0025, -140.0, 263.55703));

			AAsuraCharacter* PlayerCurrentCharPawn = GetWorld()->SpawnActor<AAsuraCharacter>(PlayerCont->TestClassTemplate,
				DefaultTestCharSpawn);
			//
			//AActor* PlayerChar =
			//UGameplayStatics::BeginSpawningActorFromClass(GetWorld(), TestClassTemplate, DefaultTestCharSpawn, true);
			//UGameplayStatics::FinishSpawningActor(PlayerChar, DefaultTestCharSpawn);


			PlayerCont->UnPossess();
			PlayerCont->Possess(Cast<APawn>(PlayerCurrentCharPawn));

			PlayerCont->bCharacterSelected = false;

		}
	}
}


void UCharacterSelectionUI::ShowWidget()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UCharacterSelectionUI::HideWidget()
{
	SetVisibility(ESlateVisibility::Hidden);
}