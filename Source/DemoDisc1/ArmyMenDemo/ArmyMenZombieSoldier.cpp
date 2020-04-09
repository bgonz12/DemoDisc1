// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenZombieSoldier.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"

#include "ArmyMenCrawlerCharacter.h"

void AArmyMenZombieSoldier::Reset()
{
	Super::Reset();

	GetMesh()->SetVisibility(true);
}

void AArmyMenZombieSoldier::Kill()
{
	if (bIsDead) return;

	Super::Kill();

	UWorld* World = GetWorld();
	if (!World) return;

	World->GetTimerManager().ClearTimer(SpawnCrawlerTimerHandle);

	World->GetTimerManager().SetTimer(SpawnCrawlerTimerHandle, this, &AArmyMenZombieSoldier::SpawnCrawler, 1.0f, false);
}

void AArmyMenZombieSoldier::SpawnCrawler()
{
	UWorld* World = GetWorld();
	if (!World) return;

	World->GetTimerManager().ClearTimer(SpawnCrawlerTimerHandle);

	if (!CrawlerClass) return;

	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.Owner = this;

	AArmyMenCrawlerCharacter* Crawler = World->SpawnActor<AArmyMenCrawlerCharacter>(CrawlerClass, SpawnLocation, SpawnRotation, SpawnParams);
	Crawler->SetDestroyOnReset(true);

	GetMesh()->SetVisibility(false);
}
