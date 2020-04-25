// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenZombieSoldierAIController.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"

#include "ArmyMenEnemy.h"
#include "ArmyMenZombieSoldier.h"
#include "ArmyMenTargetComponent.h"

void AArmyMenZombieSoldierAIController::BeginPlay()
{
	Super::BeginPlay();

	// Get Controlled pawn as ArmyMenZombieSoldier
	if (!ArmyMenEnemyCharacter) return;

	ZombieSoldier = Cast<AArmyMenZombieSoldier>(ArmyMenEnemyCharacter);
}

void AArmyMenZombieSoldierAIController::TickDead()
{
	if (!ZombieSoldier|| ZombieSoldier->GetHasCrawlerSpawned())
	{
		return;
	}

	float PlayerDistance = FVector::Dist(ArmyMenEnemyCharacter->GetActorLocation(), PlayerPawn->GetActorLocation());

	if (PlayerDistance <= ZombieSoldier->GetCrawlerVisionDistance())
	{
		UWorld* World = GetWorld();
		if (!World) return;

		FVector TraceStart = ArmyMenEnemyCharacter->GetActorLocation();
		FVector TraceEnd = PlayerPawn->GetActorLocation();

		ETraceTypeQuery VisibleQuery = ETraceTypeQuery::TraceTypeQuery3;

		TArray<AActor *> ActorsToIgnore;
		ActorsToIgnore.Add(ArmyMenEnemyCharacter);

		FHitResult OutHit;

		if (UKismetSystemLibrary::LineTraceSingle(World,
			TraceStart,
			TraceEnd,
			VisibleQuery,
			false, ActorsToIgnore,
			EDrawDebugTrace::None,
			OutHit,
			true)
			)
		{
			if (OutHit.GetActor() == PlayerPawn)
			{
				ZombieSoldier->SpawnCrawler();
			}
		}
	}
}