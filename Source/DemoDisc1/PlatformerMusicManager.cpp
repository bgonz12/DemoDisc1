// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerMusicManager.h"
#include "Components/AudioComponent.h"

#include "PlatformerDemo/PlatformerChaser.h"

// Called when the game starts
void APlatformerMusicManager::BeginPlay()
{
	Super::BeginPlay();

	ChaseValue = 0.0f;
	TargetChaseValue = 0.0f;

	if (!MusicTransitionChaser) return;
	
	MusicTransitionChaser->OnChaseStart.AddDynamic(this, &APlatformerMusicManager::TransitionToChase);
}

void APlatformerMusicManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ChaseValue = FMath::Lerp(ChaseValue, TargetChaseValue, MusicTransitionLerpSpeed * DeltaTime);

	if (AudioComponent)
	{
		AudioComponent->SetFloatParameter("Chase", ChaseValue);
	}
}

void APlatformerMusicManager::TransitionToChase()
{
	TargetChaseValue = 1.0f;
}
