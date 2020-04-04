// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerEndLevelTriggerVolume.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "PlatformerCharacter.h"

void APlatformerEndLevelTriggerVolume::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &APlatformerEndLevelTriggerVolume::BeginOverlap);
}

void APlatformerEndLevelTriggerVolume::BeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	APlatformerCharacter* PlayerCharacter = Cast<APlatformerCharacter>(OtherActor);
	if (!PlayerCharacter) return;

	UWorld* World = GetWorld();
	if (!World) return;

	UGameplayStatics::OpenLevel(World, MenuLevelName);
}