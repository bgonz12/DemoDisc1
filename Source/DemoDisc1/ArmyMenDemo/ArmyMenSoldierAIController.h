// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArmyMenEnemyAIController.h"
#include "ArmyMenSoldierAIController.generated.h"

/**
 * 
 */
UCLASS()
class DEMODISC1_API AArmyMenSoldierAIController : public AArmyMenEnemyAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

protected:
	class AArmyMenEnemy* ArmyMenEnemyCharacter;

	virtual void TickAttacking() override;

	virtual void TickIdle() override;
};
