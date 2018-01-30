// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectionUI.generated.h"

/**
 * 
 */
UCLASS()
class ASURA_API UCharacterSelectionUI : public UUserWidget
{
	GENERATED_BODY()
	
	
public:

	void ShowWidget();
	void HideWidget();
	
};
