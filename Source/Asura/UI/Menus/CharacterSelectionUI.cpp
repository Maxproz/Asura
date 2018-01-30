// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterSelectionUI.h"




void UCharacterSelectionUI::ShowWidget()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UCharacterSelectionUI::HideWidget()
{
	SetVisibility(ESlateVisibility::Hidden);
}