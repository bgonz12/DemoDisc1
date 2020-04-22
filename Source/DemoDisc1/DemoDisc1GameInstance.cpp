// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoDisc1GameInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialParameterCollectionInstance.h"

UDemoDisc1GameInstance::UDemoDisc1GameInstance()
{
	SpookyLevel = 0;
	SpookyLevelToTransition = 0;
	bHasSpookyTransitioned = false;
}

void UDemoDisc1GameInstance::Init()
{
	Super::Init();

	UWorld* World = GetWorld();
	if (!World) return;

	if (bHasSpookyTransitioned)
	{
		if (SpookySoundMix)
		{
			UGameplayStatics::ClearSoundMixModifiers(World);
			UGameplayStatics::PushSoundMixModifier(World, SpookySoundMix);
		}
	}
	else
	{
		if (NormalSoundMix)
		{
			UGameplayStatics::ClearSoundMixModifiers(World);
			UGameplayStatics::PushSoundMixModifier(World, NormalSoundMix);
		}
	}
}

bool UDemoDisc1GameInstance::GetIsTransitionTime()
{
	return !bHasSpookyTransitioned && SpookyLevel >= SpookyLevelToTransition;
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
		UGameplayStatics::ClearSoundMixModifiers(World);
		UGameplayStatics::PushSoundMixModifier(World, SpookySoundMix);
	}

	UMaterialParameterCollectionInstance* inst;
	inst = World->GetParameterCollectionInstance(GlobalMaterialParamCollection);
	if (!inst) return;

	inst->SetScalarParameterValue(FName("SpookyLerp"), 1.0f);
}

bool UDemoDisc1GameInstance::GetHasSpookyTransitioned()
{
	return bHasSpookyTransitioned;
}
