// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArmyMenSoldierAIController.h"
#include "ArmyMenZombieSoldierAIController.generated.h"

/**
 * 
 */
UCLASS()
class DEMODISC1_API AArmyMenZombieSoldierAIController : public AArmyMenSoldierAIController
{
	GENERATED_BODY()

protected:
	class AArmyMenZombieSoldier* ZombieSoldier;

	virtual void BeginPlay() override;
	
	virtual void TickDead() override;
};
