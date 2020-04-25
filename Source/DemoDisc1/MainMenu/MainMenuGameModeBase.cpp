// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameModeBase.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

#include "MainMenuUI.h"
#include "DemoDisc1/DemoDisc1GameInstance.h"

void AMainMenuGameModeBase::StartPlay()
{
	Super::StartPlay();

	UWorld* World = GetWorld();
	if (!World) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController) return;

	PlayerController->SetInputMode(FInputModeGameAndUI());
	PlayerController->bShowMouseCursor = true;

	if (MainMenuUIClass)
	{
		MainMenuUI = CreateWidget<UMainMenuUI>(PlayerController, MainMenuUIClass);

		if (MainMenuUI)
		{
			MainMenuUI->SetMainMenuLevelTransitioner(this);
			MainMenuUI->AddToViewport();

			MainMenuUI->PlayCurtainFadeIn(0.0f);
		}
	}
}

void AMainMenuGameModeBase::TransitionToLevel(FName LevelName)
{
	Super::TransitionToLevel(LevelName);

	if (MainMenuUI)
	{
		MainMenuUI->PlayCurtainFadeOut(0.0f);
	}
}

void AMainMenuGameModeBase::QuitLevel()
{
	// Check if game is in spooky mode
	UWorld* World = GetWorld();
	if (!World) return;

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(World);
	if (!GameInstance) return;

	UDemoDisc1GameInstance* DD1GameInstance = Cast<UDemoDisc1GameInstance>(GameInstance);
	if (!DD1GameInstance) return;

	if (DD1GameInstance->GetHasSpookyTransitioned())
	{
		LevelToOpen = FName("EndGameLevel");
		OpenLevel();
	}
	else
	{
		APlayerController* FirstPlayerController = World->GetFirstPlayerController();
		if (!FirstPlayerController) return;

		UKismetSystemLibrary::QuitGame(World, FirstPlayerController, EQuitPreference::Quit, false);
	}
}

UMainMenuUI * AMainMenuGameModeBase::GetMainMenuUI()
{
	return MainMenuUI;
}
