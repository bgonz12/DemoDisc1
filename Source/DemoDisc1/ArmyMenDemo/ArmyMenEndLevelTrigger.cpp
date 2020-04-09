// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenEndLevelTrigger.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "ArmyMenPlayerCharacter.h"

AArmyMenEndLevelTrigger::AArmyMenEndLevelTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AArmyMenEndLevelTrigger::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AArmyMenEndLevelTrigger::BeginOverlap);
}

void AArmyMenEndLevelTrigger::BeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	AArmyMenPlayerCharacter* PlayerCharacter = Cast<AArmyMenPlayerCharacter>(OtherActor);
	if (!PlayerCharacter) return;

	UWorld* World = GetWorld();
	if (!World) return;

	UGameplayStatics::OpenLevel(World, MenuLevelName);
}
