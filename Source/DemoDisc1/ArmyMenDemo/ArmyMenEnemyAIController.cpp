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

void AArmyMenEnemyAIController::Reset()
{
	Super::Reset();

	ChangeState(EArmyMenEnemyState::IDLE);
}

void AArmyMenEnemyAIController::TickAttacking()
{
}

void AArmyMenEnemyAIController::TickIdle()
{
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
