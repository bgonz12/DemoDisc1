// Fill out your copyright notice in the Description page of Project Settings.


#include "EndLevelTriggerBox.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "LevelTransitioner.h"

AEndLevelTriggerBox::AEndLevelTriggerBox()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AEndLevelTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AEndLevelTriggerBox::BeginOverlap);
}

void AEndLevelTriggerBox::BeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	UWorld* World = GetWorld();
	if (!World) return;

	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(World);
	if (!GameMode)
	{
		UGameplayStatics::OpenLevel(World, NextLevelName);
		return;
	}
	
	ILevelTransitioner* LevelTransitioner = Cast<ILevelTransitioner>(GameMode);
	if (!LevelTransitioner)
	{
		UGameplayStatics::OpenLevel(World, NextLevelName);
		return;
	}

	LevelTransitioner->TransitionToLevel(NextLevelName);
}
