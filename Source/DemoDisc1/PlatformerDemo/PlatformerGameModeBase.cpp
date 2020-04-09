// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerGameModeBase.h"
#include "Engine/World.h"

#include "PlatformerCheckpoint.h"

void APlatformerGameModeBase::StartPlay()
{
	Super::StartPlay();

	SetCollectibleCount(0);

	bLoadingCheckpoint = false;
}

void APlatformerGameModeBase::TriggerLoadLastCheckpoint(float Delay)
{
	if (bLoadingCheckpoint) return;

	bLoadingCheckpoint = true;

	UWorld* World = GetWorld();
	if (!World) return;

	World->GetTimerManager().ClearTimer(LoadCheckpointTimerHandle);

	World->GetTimerManager().SetTimer(LoadCheckpointTimerHandle, this, &APlatformerGameModeBase::LoadLastCheckpoint, Delay, false);
}

void APlatformerGameModeBase::LoadLastCheckpoint()
{
	bLoadingCheckpoint = false;

	UWorld* World = GetWorld();
	if (World) World->GetTimerManager().ClearTimer(LoadCheckpointTimerHandle);

	ResetLevel();
}

void APlatformerGameModeBase::SetCollectibleCount(int Value)
{
	CollectibleCount = Value;

	OnCollectibleCountUpdated.Broadcast(Value);
}
