// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "DemoDisc1GameModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "DemoDisc1GameInstance.h"

void ADemoDisc1GameModeBase::StartPlay()
{
	Super::StartPlay();

	bLoadingCheckpoint = false;

	UWorld* World = GetWorld();
	if (!World) return;

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(World);
	if (!GameInstance) return;

	UDemoDisc1GameInstance* DD1GameInstance = Cast<UDemoDisc1GameInstance>(GameInstance);
	if (!DD1GameInstance) return;

	if (!DD1GameInstance->GetHasSpookyTransitioned())
	{
		if (NormalSoundMix)
		{
			UGameplayStatics::ClearSoundMixModifiers(World);
			UGameplayStatics::PushSoundMixModifier(World, NormalSoundMix);
		}
	}
	else
	{
		if (SpookySoundMix)
		{
			UGameplayStatics::ClearSoundMixModifiers(World);
			UGameplayStatics::PushSoundMixModifier(World, SpookySoundMix);
		}
	}
}

void ADemoDisc1GameModeBase::TriggerLoadLastCheckpoint(float Delay)
{
	if (bLoadingCheckpoint) return;

	bLoadingCheckpoint = true;

	OnPlayerDeath.Broadcast();

	UWorld* World = GetWorld();
	if (!World) return;

	World->GetTimerManager().ClearTimer(LoadCheckpointTimerHandle);

	World->GetTimerManager().SetTimer(LoadCheckpointTimerHandle, this, &ADemoDisc1GameModeBase::LoadLastCheckpoint, Delay, false);
}

void ADemoDisc1GameModeBase::LoadLastCheckpoint()
{
	bLoadingCheckpoint = false;

	UWorld* World = GetWorld();
	if (World) World->GetTimerManager().ClearTimer(LoadCheckpointTimerHandle);

	ResetLevel();
}
