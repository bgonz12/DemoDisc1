// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ArmyMenEnemyAIController.generated.h"

UENUM()
enum EArmyMenEnemyState { ATTACKING, DEAD, IDLE };

/**
 * 
 */
UCLASS()
class DEMODISC1_API AArmyMenEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void Reset() override;

protected:
	class APawn* PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EArmyMenEnemyState> CurrentState;

	virtual void TickAttacking();

	virtual void TickIdle();

	virtual void ChangeState(EArmyMenEnemyState NewState);

public:
	virtual void NotifyTakeDamage();

	virtual void NotifyKill();
};
