// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerGameModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "DemoDisc1/DemoDisc1GameInstance.h"
#include "PlatformerCheckpoint.h"

void APlatformerGameModeBase::StartPlay()
{
	Super::StartPlay();

	SetCollectibleCount(0);
}

void APlatformerGameModeBase::QuitLevel()
{
	UWorld* World = GetWorld();
	if (!World) return;

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(World);
	if (!GameInstance) return;

	UDemoDisc1GameInstance* DD1GameInstance = Cast<UDemoDisc1GameInstance>(GameInstance);
	if (!DD1GameInstance) return;

	DD1GameInstance->CompleteLevel();

	LevelToOpen = FName("PlatformerSplashScreensLevel");

	OnTransitionToLevel.Broadcast();

	if (LevelFadeOutSoundMix)
	{
		UGameplayStatics::PushSoundMixModifier(World, LevelFadeOutSoundMix);
	}

	World->GetTimerManager().SetTimer(OpenLevelTimerHandle, this, &APlatformerGameModeBase::OpenLevel, LevelTransitionTime, false);
}

void APlatformerGameModeBase::SetCollectibleCount(int Value)
{
	CollectibleCount = Value;

	OnCollectibleCountUpdated.Broadcast(Value);
}
