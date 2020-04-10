// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenCrawlerAIController.h"

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetSystemLibrary.h"

#include "ArmyMenCrawlerCharacter.h"

void AArmyMenCrawlerAIController::BeginPlay()
{
	Super::BeginPlay();

	// Get Controlled pawn as ArmyMenCrawlerCharacter
	APawn* MyPawn = GetPawn();
	if (!MyPawn) return;

	ArmyMenCrawlerCharacter = Cast<AArmyMenCrawlerCharacter>(MyPawn);
}

void AArmyMenCrawlerAIController::Tick(float DeltaTime)
{
	if (!ArmyMenCrawlerCharacter)
	{
		// Get Controlled pawn as ArmyMenCrawlerCharacter
		APawn* MyPawn = GetPawn();
		if (!MyPawn) return;

		ArmyMenCrawlerCharacter = Cast<AArmyMenCrawlerCharacter>(MyPawn);
	}

	Super::Tick(DeltaTime);
}


void AArmyMenCrawlerAIController::TickAttacking()
{
	Super::TickAttacking();

	if (!ArmyMenCrawlerCharacter || !PlayerPawn) return;

	if (ArmyMenCrawlerCharacter->GetIsDead())
	{
		ChangeState(EArmyMenEnemyState::DEAD);
		return;
	}

	FVector PlayerDirection = (PlayerPawn->GetActorLocation() - ArmyMenCrawlerCharacter->GetActorLocation()).GetSafeNormal();
	float RightDotPlayer = FVector::DotProduct(ArmyMenCrawlerCharacter->GetActorRightVector(), PlayerDirection);

	ArmyMenCrawlerCharacter->TurnRight(RightDotPlayer);

	float PlayerDistance = FVector::Dist(ArmyMenCrawlerCharacter->GetActorLocation(), PlayerPawn->GetActorLocation());
	if (PlayerDistance > ArmyMenCrawlerCharacter->GetAttackRange())
	{
		ArmyMenCrawlerCharacter->MoveForward(1.0f);

	}
	else
	{
		ArmyMenCrawlerCharacter->Attack();
	}
}

void AArmyMenCrawlerAIController::TickIdle()
{
	Super::TickIdle();

	if (!ArmyMenCrawlerCharacter || !PlayerPawn) return;

	if (ArmyMenCrawlerCharacter->GetIsDead())
	{
		ChangeState(EArmyMenEnemyState::DEAD);
		return;
	}

	float PlayerDistance = FVector::Dist(ArmyMenCrawlerCharacter->GetActorLocation(), PlayerPawn->GetActorLocation());

	if (PlayerDistance <= ArmyMenCrawlerCharacter->GetVisionDistance())
	{
		UWorld* World = GetWorld();
		if (!World) return;

		FVector TraceStart = ArmyMenCrawlerCharacter->GetActorLocation();
		FVector TraceEnd = PlayerPawn->GetActorLocation();

		ETraceTypeQuery VisibleQuery = ETraceTypeQuery::TraceTypeQuery1;

		TArray<AActor *> ActorsToIgnore;
		ActorsToIgnore.Add(ArmyMenCrawlerCharacter);

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
				ChangeState(EArmyMenEnemyState::ATTACKING);
			}
		}
	}

}

void AArmyMenCrawlerAIController::NotifyTakeDamage()
{
	switch (CurrentState)
	{
	case EArmyMenEnemyState::ATTACKING:
		break;
	case EArmyMenEnemyState::DEAD:
		break;
	case EArmyMenEnemyState::IDLE:
		ChangeState(EArmyMenEnemyState::ATTACKING);
		break;
	default:
		break;
	}
}