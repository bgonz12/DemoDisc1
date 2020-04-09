// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenGameModeBase.h"
#include "Engine/World.h"

void AArmyMenGameModeBase::StartPlay()
{
	Super::StartPlay();

	bLoadingCheckpoint = false;
}

void AArmyMenGameModeBase::TriggerLoadLastCheckpoint(float Delay)
{
	if (bLoadingCheckpoint) return;

	bLoadingCheckpoint = true;

	UWorld* World = GetWorld();
	if (!World) return;

	World->GetTimerManager().ClearTimer(LoadCheckpointTimerHandle);

	World->GetTimerManager().SetTimer(LoadCheckpointTimerHandle, this, &AArmyMenGameModeBase::LoadLastCheckpoint, Delay, false);
}

void AArmyMenGameModeBase::LoadLastCheckpoint()
{
	bLoadingCheckpoint = false;

	UWorld* World = GetWorld();
	if (World) World->GetTimerManager().ClearTimer(LoadCheckpointTimerHandle);

	ResetLevel();
}