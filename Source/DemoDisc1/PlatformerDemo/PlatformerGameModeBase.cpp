// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerGameModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "PlatformerCheckpoint.h"

void APlatformerGameModeBase::StartPlay()
{
	Super::StartPlay();

	SetCollectibleCount(0);
}

void APlatformerGameModeBase::OpenLevel()
{
	UWorld* World = GetWorld();
	if (!World) return;

	World->GetTimerManager().ClearTimer(OpenLevelTimerHandle);

	UGameplayStatics::OpenLevel(World, LevelToOpen);
}

void APlatformerGameModeBase::TransitionToLevel(FName LevelName)
{
	LevelToOpen = LevelName;

	OnTransitionToLevel.Broadcast();

	UWorld* World = GetWorld();
	if (!World) return;

	if (SilenceFadeSlow)
	{
		UGameplayStatics::PushSoundMixModifier(World, SilenceFadeSlow);
	}

	World->GetTimerManager().SetTimer(OpenLevelTimerHandle, this, &APlatformerGameModeBase::OpenLevel, 2.0f, false);
}

void APlatformerGameModeBase::QuitLevel()
{
}

void APlatformerGameModeBase::SetCollectibleCount(int Value)
{
	CollectibleCount = Value;

	OnCollectibleCountUpdated.Broadcast(Value);
}
