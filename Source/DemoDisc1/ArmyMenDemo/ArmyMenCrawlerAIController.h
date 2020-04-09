// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArmyMenEnemyAIController.h"
#include "ArmyMenCrawlerAIController.generated.h"

/**
 * 
 */
UCLASS()
class DEMODISC1_API AArmyMenCrawlerAIController : public AArmyMenEnemyAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	class AArmyMenCrawlerCharacter* ArmyMenCrawlerCharacter;

	virtual void TickAttacking() override;

	virtual void TickIdle() override;

public:
	virtual void NotifyTakeDamage() override;
};
