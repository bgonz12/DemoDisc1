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

	AArmyMenEnemy* MyCharacter = Cast<AArmyMenEnemy>(MyPawn);
	if (!MyCharacter) return;

	FVector PlayerDirection = (PlayerPawn->GetActorLocation() - MyCharacter->GetActorLocation()).GetSafeNormal();
	float RightDotPlayer = FVector::DotProduct(MyCharacter->GetActorRightVector(), PlayerDirection);

	MyCharacter->TurnRight(RightDotPlayer);
	MyCharacter->Fire();
}

void AArmyMenEnemyAIController::TickIdle()
{
	if (!PlayerPawn) return;

	APawn* MyPawn = GetPawn();
	if (!MyPawn) return;

	AArmyMenEnemy* MyCharacter = Cast<AArmyMenEnemy>(MyPawn);
	if (!MyCharacter) return;

	float PlayerDistance = FVector::Dist(MyCharacter->GetActorLocation(), PlayerPawn->GetActorLocation());

	if (PlayerDistance <= MyCharacter->GetVisionDistance())
	{
		UWorld* World = GetWorld();
		if (!World) return;

		FVector TraceStart = MyCharacter->GetActorLocation();
		FVector TraceEnd = PlayerPawn->GetActorLocation();

		ETraceTypeQuery VisibleQuery = ETraceTypeQuery::TraceTypeQuery1;

		TArray<AActor *> ActorsToIgnore;
		ActorsToIgnore.Add(MyCharacter);

		FHitResult OutHit;

		if (UKismetSystemLibrary::LineTraceSingle(World,
			TraceStart,
			TraceEnd,
			VisibleQuery,
			false, ActorsToIgnore,
			EDrawDebugTrace::ForOneFrame,
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
	case EArmyMenEnemyState::IDLE:
		break;
	}
}
