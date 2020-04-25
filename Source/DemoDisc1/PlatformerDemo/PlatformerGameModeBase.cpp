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

void APlatformerGameModeBase::QuitLevel()
{
	Super::QuitLevel();
}

void APlatformerGameModeBase::SetCollectibleCount(int Value)
{
	CollectibleCount = Value;

	OnCollectibleCountUpdated.Broadcast(Value);
}
