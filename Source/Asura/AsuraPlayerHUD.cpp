// Fill out your copyright notice in the Description page of Project Settings.

#include "AsuraPlayerHUD.h"


AAsuraPlayerHUD::AAsuraPlayerHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{


	//CharSelectionUIWidget = CreateWidget<UCharacterSelectionUI>(GetOwningPlayerController(), );
	//CharSelectionUIWidget->SetIsEnabled(false);




}



void AAsuraPlayerHUD::CreateCharacterSelectionWidget()
{
	if (CharSelectionUIWidget != nullptr) return;
	CharSelectionUIWidget = CreateWidget<UCharacterSelectionUI>(GetOwningPlayerController(), CharSelectionUI.LoadSynchronous());

	CharSelectionUIWidget->AddToViewport(1);
	CharSelectionUIWidget->SetVisibility(ESlateVisibility::Visible);
}

void AAsuraPlayerHUD::CreateGameWidgets()
{
	CreateCharacterSelectionWidget();
}

void AAsuraPlayerHUD::RemoveGameWidgets()
{

}

void AAsuraPlayerHUD::ShowCharacterSelectionScreen() { GetCharacterSelectionUIWidget()->ShowWidget(); }
void AAsuraPlayerHUD::HideCharacterSelectionScreen() { GetCharacterSelectionUIWidget()->HideWidget(); }