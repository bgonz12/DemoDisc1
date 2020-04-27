// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoDisc1GameInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialParameterCollectionInstance.h"

UDemoDisc1GameInstance::UDemoDisc1GameInstance()
{
	LevelsCompleted = 0;
	LevelsCompletedToTransition = 1;
	bHasSpookyTransitioned = false;
}

void UDemoDisc1GameInstance::CompleteLevel()
{
	LevelsCompleted++;
}

void UDemoDisc1GameInstance::TriggerSpookyTransition()
{
	OnSpookyTransition.Broadcast();

	bHasSpookyTransitioned = true;

	if (!GlobalMaterialParamCollection) return;
	
	UWorld* World = GetWorld();
	if (!World) return;

	if (SpookySoundMix)
	{
		UGameplayStatics::SetBaseSoundMix(World, SpookySoundMix);
	}

	UMaterialParameterCollectionInstance* inst;
	inst = World->GetParameterCollectionInstance(GlobalMaterialParamCollection);
	if (!inst) return;

	inst->SetScalarParameterValue(FName("SpookyLerp"), 1.0f);
}

bool UDemoDisc1GameInstance::GetIsTransitionTime()
{
	return !bHasSpookyTransitioned && LevelsCompleted >= LevelsCompletedToTransition;
}

bool UDemoDisc1GameInstance::GetHasSpookyTransitioned()
{
	return bHasSpookyTransitioned;
}
