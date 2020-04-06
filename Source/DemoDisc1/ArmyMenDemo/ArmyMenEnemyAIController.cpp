// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenEnemyAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetSystemLibrary.h"

#include "ArmyMenEnemy.h"

void AArmyMenEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	ChangeState(EArmyMenEnemyState::IDLE);

	// Get Controlled pawn as ArmyMenEnemy
	APawn* MyPawn = GetPawn();
	if (!MyPawn) return;

	ArmyMenEnemyCharacter = Cast<AArmyMenEnemy>(MyPawn);

	UWorld* World = GetWorld();
	if (!World) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController) return;

	PlayerPawn = PlayerController->GetPawn();
}

void AArmyMenEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurrentState)
	{
	case EArmyMenEnemyState::ATTACKING:
		TickAttacking();
		break;
	case EArmyMenEnemyState::DEAD:
		break;
	case EArmyMenEnemyState::IDLE:
		TickIdle();
		break;
	default:
		break;
	}
}

void AArmyMenEnemyAIController::TickAttacking()
{
	if(!ArmyMenEnemyCharacter || !PlayerPawn) return;

	if (ArmyMenEnemyCharacter->GetIsDead())
	{
		ChangeState(EArmyMenEnemyState::DEAD);
	}

	FVector PlayerDirection = (PlayerPawn->GetActorLocation() - ArmyMenEnemyCharacter->GetActorLocation()).GetSafeNormal();
	float RightDotPlayer = FVector::DotProduct(ArmyMenEnemyCharacter->GetActorRightVector(), PlayerDirection);

	ArmyMenEnemyCharacter->TurnRight(RightDotPlayer);

	if (ArmyMenEnemyCharacter->GetAimTarget())
	{
		ArmyMenEnemyCharacter->Fire();
	}
}

void AArmyMenEnemyAIController::TickIdle()
{
	if (!ArmyMenEnemyCharacter || !PlayerPawn) return;

	if (ArmyMenEnemyCharacter->GetIsDead())
	{
		ChangeState(EArmyMenEnemyState::DEAD);
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

void AArmyMenEnemyAIController::ChangeState(EArmyMenEnemyState NewState)
{
	CurrentState = NewState;

	switch (CurrentState)
	{
	case EArmyMenEnemyState::ATTACKING:
		break;
	case EArmyMenEnemyState::DEAD:
		break;
	case EArmyMenEnemyState::IDLE:
		break;
	default:
		break;
	}
}

void AArmyMenEnemyAIController::NotifyTakeDamage()
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

void AArmyMenEnemyAIController::NotifyKill()
{
	switch (CurrentState)
	{
	case EArmyMenEnemyState::DEAD:
		break;
	default:
		ChangeState(EArmyMenEnemyState::DEAD);
		break;
	}
}
