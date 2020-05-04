// Fill out your copyright notice in the Description page of Project Settings.


#include "SplashScreensGameModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

#include "DemoDisc1/SplashScreensUI.h"

void ASplashScreensGameModeBase::StartPlay()
{
	Super::StartPlay();

	UWorld* World = GetWorld();
	if (!World) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController) return;

	PlayerController->SetInputMode(FInputModeGameAndUI());
	PlayerController->bShowMouseCursor = true;

	if (SplashScreensUIClass)
	{
		SplashScreensUI = CreateWidget<USplashScreensUI>(PlayerController, SplashScreensUIClass);

		if (SplashScreensUI)
		{
			SplashScreensUI->AddToViewport();

			SplashScreensUI->PlayFadeInAnimation();

			OnTransitionToLevel.AddDynamic(SplashScreensUI, &USplashScreensUI::PlayFadeOutAnimation);

			World->GetTimerManager().ClearTimer(ChangeSplashScreenTimerHandle);
			World->GetTimerManager().SetTimer(ChangeSplashScreenTimerHandle, this, &ASplashScreensGameModeBase::ChangeSplashScreen, SplashScreenTime, true);
		}
	}
	else
	{
		ChangeLevel(FName("MainMenuLevel"));
	}
}

void ASplashScreensGameModeBase::ChangeSplashScreen()
{
	if (bIsTransitioningLevel)
	{
		return;
	}

	UWorld* World = GetWorld();
	if (!World) return;

	int CurrentSplashScreen = SplashScreensUI->GetCurrentSplashScreenIndex();
	int NumSplashScreens = SplashScreensUI->GetNumSplashScreens();

	if (CurrentSplashScreen < NumSplashScreens - 1)
	{
		SplashScreensUI->ChangeSplashScreen(CurrentSplashScreen + 1);
	}
	else
	{
		World->GetTimerManager().ClearTimer(ChangeSplashScreenTimerHandle);
		ChangeLevel(FName("MainMenuLevel"));
	}
}

void ASplashScreensGameModeBase::OpenLevel()
{
	UWorld* World = GetWorld();
	if (!World) return;

	World->GetTimerManager().ClearTimer(OpenLevelTimerHandle);

	UGameplayStatics::OpenLevel(World, LevelToOpen);
}

void ASplashScreensGameModeBase::ChangeLevel(FName LevelName)
{
	LevelToOpen = LevelName;

	UWorld* World = GetWorld();
	if (!World) return;

	if (SplashScreensUI)
	{
		SplashScreensUI->PlayFadeOutAnimation();
	}

	if (SilenceFadeSlow)
	{
		UGameplayStatics::PushSoundMixModifier(World, SilenceFadeSlow);
	}

	bIsTransitioningLevel = true;

	World->GetTimerManager().SetTimer(OpenLevelTimerHandle, this, &ASplashScreensGameModeBase::OpenLevel, 1.0f, false);
}


void ASplashScreensGameModeBase::QuitLevel()
{
	UWorld* World = GetWorld();
	if (!World) return;

	LevelToOpen = FName("MainMenuLevel");

	OnTransitionToLevel.Broadcast();

	if (LevelFadeOutSoundMix)
	{
		UGameplayStatics::PushSoundMixModifier(World, LevelFadeOutSoundMix);
	}

	bIsTransitioningLevel = true;

	World->GetTimerManager().SetTimer(OpenLevelTimerHandle, this, &ASplashScreensGameModeBase::OpenLevel, LevelTransitionTime, false);
}

USplashScreensUI* ASplashScreensGameModeBase::GetSplashScreensUI()
{
	return SplashScreensUI;
}