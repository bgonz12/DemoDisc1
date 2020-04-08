// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenSoldierAIController.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"

#include "ArmyMenEnemy.h"

void AArmyMenSoldierAIController::BeginPlay()
{
	Super::BeginPlay();

	// Get Controlled pawn as ArmyMenEnemy
	APawn* MyPawn = GetPawn();
	if (!MyPawn) return;

	ArmyMenEnemyCharacter = Cast<AArmyMenEnemy>(MyPawn);
}

void AArmyMenSoldierAIController::TickAttacking()
{
	Super::TickAttacking();

	if (!ArmyMenEnemyCharacter || !PlayerPawn) return;

	if (ArmyMenEnemyCharacter->GetIsDead())
	{
		ChangeState(EArmyMenEnemyState::DEAD);
		return;
	}

	FVector PlayerDirection = (PlayerPawn->GetActorLocation() - ArmyMenEnemyCharacter->GetActorLocation()).GetSafeNormal();
	float RightDotPlayer = FVector::DotProduct(ArmyMenEnemyCharacter->GetActorRightVector(), PlayerDirection);

	ArmyMenEnemyCharacter->TurnRight(RightDotPlayer);

	if (ArmyMenEnemyCharacter->GetAimTarget())
	{
		ArmyMenEnemyCharacter->Fire();
	}
}

void AArmyMenSoldierAIController::TickIdle()
{
	Super::TickIdle();

	if (!ArmyMenEnemyCharacter || !PlayerPawn) return;

	if (ArmyMenEnemyCharacter->GetIsDead())
	{
		ChangeState(EArmyMenEnemyState::DEAD);
		return;
	}

	float PlayerDistance = FVector::Dist(ArmyMenEnemyCharacter->GetActorLocation(), PlayerPawn->GetActorLocation());

	if (PlayerDistance <= ArmyMenEnemyCharacter->GetVisionDistance())
	{
		UWorld* World = GetWorld();
		if (!World) return;

		FVector TraceStart = ArmyMenEnemyCharacter->GetActorLocation();
		FVector TraceEnd = PlayerPawn->GetActorLocation();

		ETraceTypeQuery VisibleQuery = ETraceTypeQuery::TraceTypeQuery1;

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
				ChangeState(EArmyMenEnemyState::ATTACKING);
			}
		}
	}
}