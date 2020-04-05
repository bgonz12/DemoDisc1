// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenEnemyAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#include "ArmyMenCharacter.h"

void AArmyMenEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	ChangeState(EArmyMenEnemyState::ATTACKING);

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
	case EArmyMenEnemyState::IDLE:
		TickIdle();
		break;
	}
}

void AArmyMenEnemyAIController::TickAttacking()
{
	if (!PlayerPawn) return;

	APawn* MyPawn = GetPawn();
	if (!MyPawn) return;

	AArmyMenCharacter* MyCharacter = Cast<AArmyMenCharacter>(MyPawn);
	if (!MyCharacter) return;

	FVector PlayerDirection = (PlayerPawn->GetActorLocation() - MyCharacter->GetActorLocation()).GetSafeNormal();
	float RightDotPlayer = FVector::DotProduct(MyCharacter->GetActorRightVector(), PlayerDirection);

	MyCharacter->TurnRight(RightDotPlayer);
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
	case EArmyMenEnemyState::IDLE:
		break;
	}
}
