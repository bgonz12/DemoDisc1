// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "DemoDisc1GameModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialParameterCollectionInstance.h"

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
		if (GlobalMaterialParamCollection)
		{
			UMaterialParameterCollectionInstance* Instance = World->GetParameterCollectionInstance(GlobalMaterialParamCollection);
			Instance->SetScalarParameterValue(FName("SpookyLerp"), 0.0f);
		}

		if (NormalSoundMix)
		{
			UGameplayStatics::SetBaseSoundMix(World, NormalSoundMix);
		}
	}
	else
	{
		if (GlobalMaterialParamCollection)
		{
			UMaterialParameterCollectionInstance* Instance = World->GetParameterCollectionInstance(GlobalMaterialParamCollection);
			Instance->SetScalarParameterValue(FName("SpookyLerp"), 1.0f);
		}

		if (SpookySoundMix)
		{
			UGameplayStatics::SetBaseSoundMix(World, SpookySoundMix);
		}
	}
}

void ADemoDisc1GameModeBase::LoadCheckpoint()
{
	bLoadingCheckpoint = false;

	UWorld* World = GetWorld();
	if (World) World->GetTimerManager().ClearTimer(LoadCheckpointTimerHandle);

	ResetLevel();
}

void ADemoDisc1GameModeBase::TriggerLoadCheckpoint(float Delay)
{
	if (bLoadingCheckpoint) return;

	bLoadingCheckpoint = true;

	OnLoadCheckpointTriggered.Broadcast();

	UWorld* World = GetWorld();
	if (!World) return;

	World->GetTimerManager().ClearTimer(LoadCheckpointTimerHandle);

	World->GetTimerManager().SetTimer(LoadCheckpointTimerHandle, this, &ADemoDisc1GameModeBase::LoadCheckpoint, Delay, false);
}