// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameModeBase.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#include "MainMenuUI.h"

void AMainMenuGameModeBase::StartPlay()
{
	Super::StartPlay();

	UWorld* World = GetWorld();
	if (!World) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController) return;

	PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->bShowMouseCursor = true;

	if (MainMenuUIClass)
	{
		MainMenuUI = CreateWidget<UMainMenuUI>(PlayerController, MainMenuUIClass);

		if (MainMenuUI)
		{
			MainMenuUI->AddToViewport();
		}
	}
}

UMainMenuUI * AMainMenuGameModeBase::GetMainMenuUI()
{
	return MainMenuUI;
}
