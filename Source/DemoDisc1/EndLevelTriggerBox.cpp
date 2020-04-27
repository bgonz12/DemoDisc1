// Fill out your copyright notice in the Description page of Project Settings.


#include "EndLevelTriggerBox.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "DemoDisc1GameInstance.h"
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

	// Notify DemoDisc1GameInstance that a level has been completed
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(World);
	if (!GameInstance) return;

	UDemoDisc1GameInstance* DD1GameInstance = Cast<UDemoDisc1GameInstance>(GameInstance);
	if (!DD1GameInstance) return;

	DD1GameInstance->CompleteLevel();

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
