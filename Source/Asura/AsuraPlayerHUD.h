// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "UI/Menus/CharacterSelectionUI.h"

#include "AsuraPlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class ASURA_API AAsuraPlayerHUD : public AHUD
{
	GENERATED_BODY()
	
private:
	
	AAsuraPlayerHUD(const FObjectInitializer& ObjectInitializer);

	class UCharacterSelectionUI* CharSelectionUIWidget;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Menu Widgets")
	TAssetSubclassOf<UCharacterSelectionUI> CharSelectionUI;
public:
	
	void CreateCharacterSelectionWidget();
	void CreateGameWidgets();
	void RemoveGameWidgets();

	class UCharacterSelectionUI* GetCharacterSelectionUIWidget() const { return CharSelectionUIWidget; }
	
	void ShowCharacterSelectionScreen();
	void HideCharacterSelectionScreen();
};
