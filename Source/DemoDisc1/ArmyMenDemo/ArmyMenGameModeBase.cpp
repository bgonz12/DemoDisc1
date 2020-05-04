// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenGameModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "DemoDisc1/DemoDisc1GameInstance.h"

void AArmyMenGameModeBase::QuitLevel()
{
	UWorld* World = GetWorld();
	if (!World) return;

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(World);
	if (!GameInstance) return;

	UDemoDisc1GameInstance* DD1GameInstance = Cast<UDemoDisc1GameInstance>(GameInstance);
	if (!DD1GameInstance) return;

	DD1GameInstance->CompleteLevel();

	LevelToOpen = FName("ArmyMenSplashScreensLevel");

	OnTransitionToLevel.Broadcast();

	if (LevelFadeOutSoundMix)
	{
		UGameplayStatics::PushSoundMixModifier(World, LevelFadeOutSoundMix);
	}

	World->GetTimerManager().SetTimer(OpenLevelTimerHandle, this, &AArmyMenGameModeBase::OpenLevel, LevelTransitionTime, false);
}