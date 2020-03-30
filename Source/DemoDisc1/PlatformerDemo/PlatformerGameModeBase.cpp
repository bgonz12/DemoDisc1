// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerGameModeBase.h"
#include "Engine/World.h"

#include "PlatformerChaser.h"
#include "PlatformerCharacter.h"
#include "PlatformerCheckpoint.h"

void APlatformerGameModeBase::StartPlay()
{
	Super::StartPlay();

	bLoadingCheckpoint = false;

	UWorld* World = GetWorld();
	if (!World) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController) return;

	APawn* PlayerPawn = PlayerController->GetPawn();
	if (!PlayerPawn) return;

	PlayerCharacter = Cast<APlatformerCharacter>(PlayerPawn);
}

void APlatformerGameModeBase::TriggerLoadLastCheckpoint()
{
	if (bLoadingCheckpoint) return;

	bLoadingCheckpoint = true;

	UWorld* World = GetWorld();
	if (!World) return;

	World->GetTimerManager().ClearTimer(LoadCheckpointTimerHandle);

	World->GetTimerManager().SetTimer(LoadCheckpointTimerHandle, this, &APlatformerGameModeBase::LoadLastCheckpoint, 3.0f, false);
}

void APlatformerGameModeBase::LoadLastCheckpoint()
{
	bLoadingCheckpoint = false;

	UWorld* World = GetWorld();
	if (World) World->GetTimerManager().ClearTimer(LoadCheckpointTimerHandle);

	if (LastCheckpoint)
	{
		APlatformerChaser* Chaser = LastCheckpoint->GetCheckpointChaser();
		if (Chaser) Chaser->Reset();

	}

	if (PlayerCharacter) PlayerCharacter->Reset();

	//ResetLevel();
}

void APlatformerGameModeBase::SetCurrentCheckpoint(APlatformerCheckpoint* NewCheckpoint)
{
	LastCheckpoint = NewCheckpoint;
}